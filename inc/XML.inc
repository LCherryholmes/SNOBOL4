*-------------------------------------------------------------------------------------------------------
* XML.inc
*---------- --------------- --- -------------------------------------------------------- -----------------------------
            xmlWhite        =   SPAN(' ' tab lf cr ff vt)
            $'  '           =   FENCE(xmlWhite | epsilon)
            xmlComment      =   '<!--' BREAKX('-') '-->'
            xmlWhitespace   =   (xmlWhite | xmlComment) FENCE(*xmlWhitespace | epsilon)
            $' '            =   FENCE(xmlWhitespace | epsilon)
            xmlDIGIT        =   '0123456789'
            xmlNUMBER       =   SPAN(xmlDIGIT)
+                           |   '"' SPAN(xmlDIGIT) '"'
+                           |   "'" SPAN(xmlDIGIT) "'"
            xmlSTRING       =   '"' ARBNO(NOTANY('"' bSlash) BREAK('"' bSlash) | bSlash ANY('"' bSlash)) . xmlxString '"'
+                           |   "'" ARBNO(NOTANY("'" bSlash) BREAK("'" bSlash) | bSlash ANY("'" bSlash)) . xmlxString "'"
            xmlIDENT        =   ANY(&UCASE &LCASE) FENCE(SPAN(&UCASE &LCASE xmlDIGIT '_.-') | epsilon)
            xmlDATUM        =   NOTANY('<') BREAK('<')
+                           |   '<![CDATA[' BREAKX(']') ']]>'
            $'<'            =   $' '  TY(1, '<', '<')
            $'/>'           =   $'  ' TY(1, '/>', '/>')
            $'</'           =   $'  ' TY(1, '</', '</')
            $'>'            =   $'  ' TY(1, '>', '>')
            $'='            =   $'  ' TY(1, '=', '=') $'  '
            $'<?'           =   $'  ' TY(1, '<?', '<?')
            $'?>'           =   $'  ' TY(1, '?>', '?>')
            xmlNUMBER       =   $'  ' TY(2, 'xmlNUMBER', xmlNUMBER)
            xmlSTRING       =   $'  ' TY(2, 'xmlSTRING', xmlSTRING)
*---------- --------------- --- -------------------------------------------------------- -----------------------------
            xmlIdent        =   (xmlIDENT FENCE(':' xmlIDENT | epsilon)) $ xmlxIdent . xmlxIdent
            xmlData         =   xmlDATUM . xmlx . *Shift('Data', XMLDecode(xmlx))
            xmlName         =   *xmlIdent . *Shift('Name')
            xmlValue        =   (xmlNUMBER | xmlSTRING) . xmlx . *Shift('Value', XMLDecode(xmlx))
            xmlAttribute    =   $'  ' *xmlName $'=' *xmlValue . *Reduce('=', 2)
            xmlPushTag      =   epsilon $ *PushBegTag(xmlxTag)
+                           |   epsilon $ *PopBegTag()
+                               FAIL
            xmlPopTag       =   epsilon $ *PushEndTag(TopBegTag()) $ *PopBegTag()
+                           |   epsilon $ *PushBegTag(TopEndTag()) $ *PopEndTag()
+                               FAIL
            xmlElement      =   $'<' *xmlIdent $ xmlxTag . xmlxTag
+                               nPush()
+                               ARBNO(*xmlAttribute nInc())
+                               (   $'/>' . *Reduce(upr(xmlxTag), nTop())
+                               |   $'>'
+                                   *xmlPushTag
+                                   ARBNO((*xmlElement | *xmlData) nInc())
+                                   $'</' *xmlIdent *LEQ(upr(xmlxIdent), TopBegTag())
+                                   $'>' . *Reduce(upr(xmlxIdent), nTop())
+                                   *xmlPopTag
+                               )
+                               nPop()
            xmlParser       =   $'<?' 'xml' $'  ' 'version="1.0"' $'  ' 'encoding="' ('UTF-8' | 'utf-8') '"' $'?>'
+                               *xmlElement . *Reduce('XML', 1)
            xmlRecognizer   =   POS(0) FENCE *xmlParser $' ' RPOS(0)
*---------- --------------- --- -------------------------------------------------------- -----------------------------
            xmlIdent        =   TY(1, 'xmlIdent', xmlIdent)
            xmlDatum        =   TZ(1, 'xmlDatum', xmlDatum)
            xmlAttribute    =   TZ(1, 'xmlAttribute', xmlAttribute)
            xmlElement      =   TZ(1, 'xmlElement', xmlElement)
            xmlRecognizer   =   epsilon $ t8Max
+                               TZ(1, 'xmlRecognizer', xmlRecognizer)
*-------------------------------------------------------------------------------------------------------
            xmlCh              = TABLE()
            xmlCh['iexcl']     = '¡'
            xmlCh['cent']      = '¢'
            xmlCh['pound']     = '£'
            xmlCh['curren']    = '¤'
            xmlCh['yen']       = '¥'
            xmlCh['brvbar']    = '¦'
            xmlCh['sect']      = '§'
            xmlCh['uml']       = '¨'
            xmlCh['copy']      = '©'
            xmlCh['ordf']      = 'ª'
            xmlCh['laquo']     = '«'
            xmlCh['not']       = '¬'
*           xmlCh['shy']       =
            xmlCh['reg']       = '®'
            xmlCh['macr']      = '¯'
            xmlCh['deg']       = '°'
            xmlCh['plusmn']    = '±'
            xmlCh['sup2']      = '²'
            xmlCh['sup3']      = '³'
            xmlCh['acute']     = '´'
            xmlCh['micro']     = 'µ'
            xmlCh['para']      = '¶'
            xmlCh['middot']    = '·'
            xmlCh['cedil']     = '¸'
            xmlCh['sup1']      = '¹'
            xmlCh['ordm']      = 'º'
            xmlCh['raquo']     = '»'
            xmlCh['frac14']    = '¼'
            xmlCh['frac12']    = '½'
            xmlCh['frac34']    = '¾'
            xmlCh['iquest']    = '¿'
            xmlCh['Agrave']    = 'À'
            xmlCh['Aacute']    = 'Á'
            xmlCh['Acirc']     = 'Â'
            xmlCh['Atilde']    = 'Ã'
            xmlCh['Auml']      = 'Ä'
            xmlCh['Aring']     = 'Å'
            xmlCh['AElig']     = 'Æ'
            xmlCh['Ccedil']    = 'Ç'
            xmlCh['Egrave']    = 'È'
            xmlCh['Eacute']    = 'É'
            xmlCh['Ecirc']     = 'Ê'
            xmlCh['Euml']      = 'Ë'
            xmlCh['Igrave']    = 'Ì'
            xmlCh['Iacute']    = 'Í'
            xmlCh['Icirc']     = 'Î'
            xmlCh['Iuml']      = 'Ï'
            xmlCh['ETH']       = 'Ð'
            xmlCh['Ntilde']    = 'Ñ'
            xmlCh['Ograve']    = 'Ò'
            xmlCh['Oacute']    = 'Ó'
            xmlCh['Ocirc']     = 'Ô'
            xmlCh['Otilde']    = 'Õ'
            xmlCh['Ouml']      = 'Ö'
            xmlCh['times']     = '×'
            xmlCh['Oslash']    = 'Ø'
            xmlCh['Ugrave']    = 'Ù'
            xmlCh['Uacute']    = 'Ú'
            xmlCh['Ucirc']     = 'Û'
            xmlCh['Uuml']      = 'Ü'
            xmlCh['Yacute']    = 'Ý'
            xmlCh['THORN']     = 'Þ'
            xmlCh['szlig']     = 'ß'
            xmlCh['agrave']    = 'à'
            xmlCh['aacute']    = 'á'
            xmlCh['acirc']     = 'â'
            xmlCh['atilde']    = 'ã'
            xmlCh['auml']      = 'ä'
            xmlCh['aring']     = 'å'
            xmlCh['aelig']     = 'æ'
            xmlCh['ccedil']    = 'ç'
            xmlCh['egrave']    = 'è'
            xmlCh['eacute']    = 'é'
            xmlCh['ecirc']     = 'ê'
            xmlCh['euml']      = 'ë'
            xmlCh['igrave']    = 'ì'
            xmlCh['iacute']    = 'í'
            xmlCh['icirc']     = 'î'
            xmlCh['iuml']      = 'ï'
            xmlCh['eth']       = 'ð'
            xmlCh['ntilde']    = 'ñ'
            xmlCh['ograve']    = 'ò'
            xmlCh['oacute']    = 'ó'
            xmlCh['ocirc']     = 'ô'
            xmlCh['otilde']    = 'õ'
            xmlCh['ouml']      = 'ö'
            xmlCh['divide']    = '÷'
            xmlCh['oslash']    = 'ø'
            xmlCh['ugrave']    = 'ù'
            xmlCh['uacute']    = 'ú'
            xmlCh['ucirc']     = 'û'
            xmlCh['uuml']      = 'ü'
            xmlCh['yacute']    = 'ý'
            xmlCh['thorn']     = 'þ'
            xmlCh['yuml']      = 'ÿ'
            xmlCh['OElig']     = 'Œ'
            xmlCh['oelig']     = 'œ'
            xmlCh['Scaron']    = 'Š'
            xmlCh['scaron']    = 'š'
            xmlCh['Yuml']      = 'Ÿ'
            xmlCh['fnof']      = 'ƒ'
            xmlCh['circ']      = 'ˆ'
            xmlCh['tilde']     = '˜ '
            xmlCh['Alpha']     = 'Α'
            xmlCh['Beta']      = 'Β'
            xmlCh['Gamma']     = 'Γ'
            xmlCh['Delta']     = 'Δ'
            xmlCh['Epsilon']   = 'Ε'
            xmlCh['Zeta']      = 'Ζ'
            xmlCh['Eta']       = 'Η'
            xmlCh['Theta']     = 'Θ'
            xmlCh['Iota']      = 'Ι'
            xmlCh['Kappa']     = 'Κ'
            xmlCh['Lambda']    = 'Λ'
            xmlCh['Mu']        = 'Μ'
            xmlCh['Nu']        = 'Ν'
            xmlCh['Xi']        = 'Ξ'
            xmlCh['Omicron']   = 'Ο'
            xmlCh['Pi']        = 'Π'
            xmlCh['Rho']       = 'Ρ'
            xmlCh['Sigma']     = 'Σ'
            xmlCh['Tau']       = 'Τ'
            xmlCh['Upsilon']   = 'Υ'
            xmlCh['Phi']       = 'Φ'
            xmlCh['Chi']       = 'Χ'
            xmlCh['Psi']       = 'Ψ'
            xmlCh['Omega']     = 'Ω'
            xmlCh['alpha']     = 'α'
            xmlCh['beta']      = 'β'
            xmlCh['gamma']     = 'γ'
            xmlCh['delta']     = 'δ'
            xmlCh['epsilon']   = 'ε'
            xmlCh['zeta']      = 'ζ'
            xmlCh['eta']       = 'η'
            xmlCh['theta']     = 'θ'
            xmlCh['iota']      = 'ι'
            xmlCh['kappa']     = 'κ'
            xmlCh['lambda']    = 'λ'
            xmlCh['mu']        = 'μ'
            xmlCh['nu']        = 'ν'
            xmlCh['xi']        = 'ξ'
            xmlCh['omicron']   = 'ο'
            xmlCh['pi']        = 'π'
            xmlCh['rho']       = 'ρ'
            xmlCh['sigmaf']    = 'ς'
            xmlCh['sigma']     = 'σ'
            xmlCh['tau']       = 'τ'
            xmlCh['upsilon']   = 'υ'
            xmlCh['phi']       = 'φ'
            xmlCh['chi']       = 'χ'
            xmlCh['psi']       = 'ψ'
            xmlCh['omega']     = 'ω'
            xmlCh['thetasym']  = 'ϑ'
            xmlCh['upsih']     = 'ϒ'
            xmlCh['piv']       = 'ϖ'
            xmlCh['ndash']     = '–'
            xmlCh['mdash']     = '—'
            xmlCh['lsquo']     = '‘'
            xmlCh['rsquo']     = '’'
            xmlCh['sbquo']     = '‚'
            xmlCh['ldquo']     = '“'
            xmlCh['rdquo']     = '”'
            xmlCh['bdquo']     = '„'
            xmlCh['dagger']    = '†'
            xmlCh['Dagger']    = '‡'
            xmlCh['bull']      = '•'
            xmlCh['hellip']    = '…'
            xmlCh['permil']    = '‰'
            xmlCh['prime']     = '′'
            xmlCh['Prime']     = '″'
            xmlCh['lsaquo']    = '‹'
            xmlCh['rsaquo']    = '›'
            xmlCh['oline']     = '‾'
            xmlCh['frasl']     = '⁄'
            xmlCh['euro']      = '€'
            xmlCh['image']     = 'ℑ'
            xmlCh['weierp']    = '℘'
            xmlCh['real']      = 'ℜ'
            xmlCh['trade']     = '™'
            xmlCh['alefsym']   = 'ℵ'
            xmlCh['larr']      = '←'
            xmlCh['uarr']      = '↑'
            xmlCh['rarr']      = '→'
            xmlCh['darr']      = '↓'
            xmlCh['harr']      = '↔'
            xmlCh['crarr']     = '↵'
            xmlCh['lArr']      = '⇐'
            xmlCh['uArr']      = '⇑'
            xmlCh['rArr']      = '⇒'
            xmlCh['dArr']      = '⇓'
            xmlCh['hArr']      = '⇔'
            xmlCh['forall']    = '∀'
            xmlCh['part']      = '∂'
            xmlCh['exist']     = '∃'
            xmlCh['empty']     = '∅'
            xmlCh['nabla']     = '∇'
            xmlCh['isin']      = '∈'
            xmlCh['notin']     = '∉'
            xmlCh['ni']        = '∋'
            xmlCh['prod']      = '∏'
            xmlCh['sum']       = '∑'
            xmlCh['minus']     = '−'
            xmlCh['lowast']    = '∗'
            xmlCh['radic']     = '√'
            xmlCh['prop']      = '∝'
            xmlCh['infin']     = '∞'
            xmlCh['ang']       = '∠'
            xmlCh['and']       = '∧'
            xmlCh['or']        = '∨'
            xmlCh['cap']       = '∩'
            xmlCh['cup']       = '∪'
            xmlCh['int']       = '∫'
            xmlCh['there4']    = '∴'
            xmlCh['sim']       = '∼'
            xmlCh['cong']      = '≅'
            xmlCh['asymp']     = '≈'
            xmlCh['ne']        = '≠'
            xmlCh['equiv']     = '≡'
            xmlCh['le']        = '≤'
            xmlCh['ge']        = '≥'
            xmlCh['sub']       = '⊂'
            xmlCh['sup']       = '⊃'
            xmlCh['nsub']      = '⊄'
            xmlCh['sube']      = '⊆'
            xmlCh['supe']      = '⊇'
            xmlCh['oplus']     = '⊕'
            xmlCh['otimes']    = '⊗'
            xmlCh['perp']      = '⊥'
            xmlCh['sdot']      = '⋅'
            xmlCh['lceil']     = '⌈'
            xmlCh['rceil']     = '⌉'
            xmlCh['lfloor']    = '⌊'
            xmlCh['rfloor']    = '⌋'
            xmlCh['lang']      = '〈'
            xmlCh['rang']      = '〉'
            xmlCh['loz']       = '◊'
            xmlCh['spades']    = '♠'
            xmlCh['clubs']     = '♣'
            xmlCh['hearts']    = '♥'
            xmlCh['diams']     = '♦'

            xmlDec         = TABLE()
            xmlDec['8211'] = '–'
            xmlDec['8212'] = '—'
            xmlDec['8216'] = '‘'
            xmlDec['8217'] = '’'
            xmlDec['8218'] = '‚'
            xmlDec['8220'] = '“'
            xmlDec['8221'] = '”'
            xmlDec['8222'] = '„'
            xmlDec['8224'] = '†'
            xmlDec['8225'] = '‡'
            xmlDec['8226'] = '•'
            xmlDec['8230'] = '…'
            xmlDec['8240'] = '‰'
            xmlDec['8364'] = '€'
            xmlDec['8482'] = '™'
*---------- ---------- --- -------------------------------------------- ------------------------------------
            DEFINE('XMLDecode(xml)ch,str,n')                            :(XMLDecodeEnd)
XMLDecode   xml        POS(0) RPOS(0)                                   :S(RETURN)
            xml        POS(0) '&quot;'   . *assign(.ch, '"') =          :S(XMLDecode1)
            xml        POS(0) '&amp;'    . *assign(.ch, '&') =          :S(XMLDecode1)
            xml        POS(0) '&apos;'   . *assign(.ch, "'") =          :S(XMLDecode1)
            xml        POS(0) '&lt;'     . *assign(.ch, '<') =          :S(XMLDecode1)
            xml        POS(0) '&gt;'     . *assign(.ch, '>') =          :S(XMLDecode1)
            xml        POS(0) '&nbsp;'   . *assign(.ch, ' ') =          :S(XMLDecode1)
            xml        POS(0) '&' SPAN(&UCASE &LCASE) . xch ';' =       :S(XMLDecode2)
            xml        POS(0) '&#' SPAN('0123456789') . n ';' =         :S(XMLDecode3)
            xml        POS(0) '&' . ch =                                :S(XMLDecode1) ;* :S(XMLDecodeE1)
            xml        POS(0) BREAK('&') . str =                        :S(XMLDecode4)
            xml        POS(0) RTAB(0) . str =                           :S(XMLDecode4)
XMLDecode1  XMLDecode  =   XMLDecode ch                                 :(XMLDecode)
XMLDecode2  XMLDecode  =   XMLDecode DIFFER(xmlCh[xch]) xmlCh[lwr(xch)] :F(XMLDecodeE2)
XMLDecode3  XMLDecode  =   XMLDecode LT(n, 256) CHAR(n)                 :S(XMLDecode)
            XMLDecode  =   XMLDecode DIFFER(xmlDec[n]) xmlDec[n]        :S(XMLDecode)F(XMLDecodeE3)
XMLDecode4  XMLDecode  =   XMLDecode str                                :(XMLDecode)
XMLDecodeE1 OUTPUT     =   'XMLDecode Error #1: ' SUBSTR(xml, 1, 16)    :(error)
XMLDecodeE2 OUTPUT     =   'XMLDecode Error #2: &' xch ';'              :(XMLDecode)
XMLDecodeE3
*           OUTPUT     =   'XMLDecode Error #3: &#' n ';'
                                                                        :(XMLDecode)
XMLDecodeEnd
*---------- ---------- --- -------------------------------------------- ------------------------------------
