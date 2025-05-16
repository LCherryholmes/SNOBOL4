*-------------------------------------------------------------------------------------------------------
* HTML.inc
*-------------------------------------------------------------------------------------------------------
            htmTags           =     'A B I P U '
+                                   'BR DD DL DT EM H1 H2 H3 H4 H5 H6 HR LI OL TD TH TR TT UL '
+                                   'BIG DFN DIR DIV IMG KBD MAP PRE SUB SUP VAR '
+                                   'ABBR AREA BASE BODY CITE CODE FONT FORM HEAD HTML LINK MENU META SAMP SPAN '
+                                   'EMBED INPUT LABEL PARAM SMALL STYLE TABLE TBODY TFOOT THEAD TITLE '
+                                   'APPLET BUTTON CENTER OPTION IFRAME OBJECT SCRIPT SELECT STRIKE STRONG '
+                                   'ADDRESS CAPTION ISINDEX '
+                                   'BASEFONT NOSCRIPT TEXTAREA '
+                                   'BLOCKQUOTE'
            htmAttrs          =     'ACCEPT-CHARSET ALLOWFULLSCREEN ALLOWSCRIPTACCESS ALLOWTRANSPARENCY ALT ACCESSKEY ACTION ALIGN '
+                                   'ALINK AUTOCOMPLETE BORDER BGCOLOR '
+                                   'BACKGROUND CELLPADDING CELLSPACING CHARSET CLASS CLASSID CLEAR CODE CODEBASE COLS COLOR '
+                                   'COORDS CHECKED COLSPAN COMPACT CONTENT DATA-COUNT DATA-TEXT DATA-URL DATA-VIA DIR ENCTYPE FOR '
+                                   'FRAMEBORDER HREF HEIGHT HSPACE '
+                                   'HTTP-EQUIV ID IMAGEANCHOR ISMAP LABEL LANG LANGUAGE LINK LONGDESC MARGINHEIGHT MARGINWIDTH MEDIA '
+                                   'METHOD MULTIPLE MAXLENGTH NAME NOWRAP NOHREF NOSHADE ONCLICK ONCONTEXTMENU ONFOCUS ONMOUSEOUT '
+                                   'ONMOUSEOVER ONSUBMIT PLACEHOLDER PROFILE PROMPT REF REL REV ROWS ROWSPAN SCOPE SCROLLING '
+                                   'SIZES SRC SIZE SHAPE SHARE_URL START SELECTED SPELLCHECK STYLE SUMMARY TABINDEX TARGET TEXT TYPE TITLE '
+                                   'USEMAP VALUE VLINK VSPACE VALIGN VERSION WIDTH WMODE XMLNS'
            htmXAttrs         =     'XML:LANG XMLNS:B XMLNS:DATA XMLNS:EXPR'
            htmVals           =     'ALL AQUA BASELINE BLUE BLACK BOTTOM CENTER CIRCLE COMPACT CHECKBOX CHECKED DISC '
+                                   'DEFAULT FILE FUCHSIA GET GRAY GREEN HIDDEN IMAGE ISMAP LEFT LIME MAROON MIDDLE '
+                                   'MULTIPLE NAVY NONE NOWRAP NOHREF NOSHADE OLIVE POLY POST PURPLE PASSWORD RED RECT '
+                                   'RADIO RESET RIGHT SLIVER SQUARE SUBMIT SELECTED TOP TEAL TEXT WHITE YELLOW'
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('HTMLDecode(html)ch,str')                                        :(HTMLDecodeEnd)
HTMLDecode  html        POS(0) RPOS(0)                                              :S(RETURN)
            html        POS(0) '&amp;' . *assign(.ch, '&') =                        :S(HTMLDecode1)
            html        POS(0) '&'                                                  :S(HTMLDecodeErr)
            html        POS(0) BREAK('&') . str =                                   :S(HTMLDecode2)
            html        POS(0) RTAB(0) . str =                                      :S(HTMLDecode2)
HTMLDecode1 HTMLDecode  =   HTMLDecode ch                                           :(HTMLDecode)
HTMLDecode2 HTMLDecode  =   HTMLDecode str                                          :(HTMLDecode)
HTMLDecodeErr OUTPUT = 'Error: ' html                                               :(abort)
HTMLDecodeEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('HPopulate(fold,idpat,attrs,xattrs,vals,special)pat,peel,w')              :(HPopulateEnd)
HPopulate   peel              =     POS(0) (BREAK(' ') . w ' ' | (LEN(1) RTAB(0)) . w)
HPopulate10 attrs             peel =                                                         :F(HPopulate20)
            pat               =     APPLY(fold, 2, idpat, w)
            $w                =     $'  ' pat                                                :(HPopulate10)
HPopulate20 xattrs            peel =                                                         :F(HPopulate30)
            pat               =     APPLY(fold, 2, idpat ':' idpat, w)
            $w                =     $'  ' pat                                                :(HPopulate20)
HPopulate30 vals              peel =                                                         :F(HPopulate40)
            pat               =     APPLY(fold, 2, idpat, w)
            $w                =     $'  ' (pat | '"' pat '"')                                :(HPopulate30)
HPopulate40 special           peel =                                                         :F(HPopulate50)
            $w                =     EQ(doParseTree, TRUE)  $'  ' TY(2, w, w ~ 'op')
            $w                =     EQ(doParseTree, FALSE) $'  ' TY(2, w, w)                 :(HPopulate40)
HPopulate50                                                                                  :(RETURN)
HPopulateEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            empty             =     epsilon ~ ''
            white             =     SPAN(' ' tab lf cr ff vt)
            $'  '             =     FENCE(white | epsilon)
            htmComment        =     '<!--' BREAKX('-') '-->'
            whitespace        =     (white | htmComment) FENCE(*whitespace | epsilon)
            $' '              =     FENCE(whitespace | epsilon)
            DIGIT             =     '0123456789'
            NUMBER            =     SPAN(DIGIT)
+                             |     '"' SPAN(DIGIT) '"'
+                             |     "'" SPAN(DIGIT) "'"
            SIZE_VALUE        =     '"' (ANY('+-') | epsilon) SPAN(DIGIT) '"'
            PERCENT           =     '"' SPAN(DIGIT) '%"'
            HEXDIGIT          =     '0123456789ABCDEFabcdef'
            RGB               =     '"#' ANY(HEXDIGIT) ANY(HEXDIGIT) ANY(HEXDIGIT) ANY(HEXDIGIT) ANY(HEXDIGIT) '"'
            STRING            =     '"' ARBNO(NOTANY('"' bSlash) BREAK('"' bSlash) | bSlash ANY('"' bSlash)) . htmxString '"'
+                             |     "'" ARBNO(NOTANY("'" bSlash) BREAK("'" bSlash) | bSlash ANY("'" bSlash)) . htmxString "'"
            keywords          =     htmTags ' ' htmAttrs ' ' htmVals
            special           =     '<!-- <! </ > < /> = & ; -->'
            FNMCHAR           =     &UCASE &LCASE
            NMCHAR            =     &UCASE &LCASE DIGIT '_.-'
            ident             =     ANY(FNMCHAR) FENCE(SPAN(NMCHAR) | epsilon)
            identifier        =     ident $ tx $ *notmatch(keywords, (POS(0) | ' ') upr(tx) (' ' | RPOS(0)))
            htmTag            =     ident $ tx $ *match(htmTags, (POS(0) | ' ') upr(tx) (' ' | RPOS(0)))
            htmAttr           =     ident $ tx $ *match(htmAttrs, (POS(0) | ' ') upr(tx) (' ' | RPOS(0)))
            htmXAttr          =     (ident ':' ident) $ tx $ *match(htmXAttrs, (POS(0) | ' ') upr(tx) (' ' | RPOS(0)))
            htmVal            =     ident $ tx $ *match(htmVals, (POS(0) | ' ') upr(tx) (' ' | RPOS(0)))
            htmVal            =     htmVal | '"' htmVal '"'
            htmTagBegin       =     '<' htmTag
            htmTagEnd         =     '</' htmTag
            $'<'              =     $' '  TY(1, '<', '<')
            $'>'              =     $'  ' TY(1, '>', '>')
            $'/>'             =     $'  ' TY(1, '/>', '/>')
            $'='              =     $'  ' TY(1, '=', '=') $'  '
            HPopulate(.TW, ident, htmAttrs, htmXAttrs, htmVals)
*---------- ----------------- ----- ------------------------------------------------------- -----------------------------
            hTags             =     htmTags
L01         hTags             POS(0) (BREAK(' ') . hT ' ' | (LEN(1) RTAB(0)) . hT) =        :F(L03)
            $('<'  hT    )    =     $' '  TW(1, '<'  ident, '<'  hT)
            $('<'  hT '>')    =     $' '  TW(1, '<'  ident, '<'  hT) $'>'
            $('<'  hT '/>')   =     $' '  TW(1, '<'  ident, '<'  hT) $'/>'
            $('</' hT    )    =     $' '  TW(1, '</' ident, '</' hT)
            $('</' hT '>')    =     $' '  TW(1, '</' ident, '</' hT) $'>'                   :(L01)
L03         NUMBER            =     $'  ' TY(2, 'NUMBER', NUMBER)
            SIZE_VALUE        =     $'  ' TY(2, 'SIZE_VALUE', SIZE_VALUE)
            PERCENT           =     $'  ' TY(2, 'PERCENT', PERCENT)
            RGB               =     $'  ' TY(2, 'RGB', RGB)
            STRING            =     $'  ' TY(2, 'STRING', STRING)
*---------- ----------------- ----- ------------------------------------------------------- -----------------------------
            htmTokens         =     *htmToken FENCE(*htmTokens | epsilon)
            htmToken          =     $' '
+                                   (  NUMBER
+                                   |  SIZE_VALUE
+                                   |  PERCENT
+                                   |  RGB
+                                   |  STRING
+                                   |  *identifier
+                                   |  *htmTagBegin
+                                   |  *htmTagEnd
+                                   |  *htmTag
+                                   |  *htmAttr
+                                   |  *htmVal
+                                   )
*---------- --------------------- ----- ----------------------------------------------------------------------------------
            htmRecognizer         =     *htmDOCTYPE *htmHTML

            htmDOCTYPE            =     $'  ' '<!' icase('DOCTYPE')
+                                       $'  ' icase('HTML')
+                                       $'  ' icase('PUBLIC')
+                                      !($'  ' STRING !($'  ' STRING))
+                                       BREAK('>') '>'

            htmData               =     #*htmDatum
            htmDatum              =     NOTANY('<') BREAK('<')
+                                 |     '<![CDATA[' BREAKX(']') ']]>'
*---------- --------------------- ----- ----------------------------------------------------------------------------------
            htmHTML               =     $'<HTML' *htmHTML_attrs $'>' *htmHEAD *htmBODY $'</HTML>'
            htmHEAD               =     $'<HEAD' *htmHEAD_attrs $'>'
+                                      %(   *htmBASE
+                                       |   *htmISINDEX
+                                       |   *htmLINK
+                                       |   *htmMETA
+                                       |   *htmNOSCRIPT
+                                       |   *htmSCRIPT
+                                       |   *htmSTYLE
+                                       |   *htmTITLE
+                                       )
+                                       $'</HEAD>'

            htmBODY               =     $'<BODY' *htmBODY_attrs $'>' %*htmBODY_cont $'</BODY>'
            htmBODY_cont          =     (   *htmADDRESS
+                                       |   *htmH
+                                       |   *htmBlock
+                                       |   *htmText
+                                       )
*
*           Inline elements
*
            htmA                  =    ($'<A' *htmA_attrs $'>'                  %*htmText               $'</A>') ;* $ OUTPUT
            htmABBR               =     $'<ABBR' *htmABBR_attrs $'>'            %*htmText               $'</ABBR>'
            htmB                  =     $'<B>'                                  %*htmText               $'</B>'
            htmCITE               =     $'<CITE>'                               %*htmText               $'</CITE>'
            htmCODE               =     $'<CODE>'                               %*htmText               $'</CODE>'
            htmDFN                =     $'<DFN>'                                %*htmText               $'</DFN>'
            htmFONT               =     $'<FONT' *htmFONT_attrs $'>'            %*htmText               $'</FONT>'
            htmI                  =     $'<I>'                                  %*htmText               $'</I>'
            htmLABEL              =     $'<LABEL' *htmLABEL_attrs $'>'          %*htmText               $'</LABEL>'
            htmSAMP               =     $'<SAMP>'                               %*htmText               $'</SAMP>'
            htmSELECT             =     $'<SELECT' *htmSELECT_attrs $'>'        #*htmOPTION             $'</SELECT>'
            htmSMALL              =     $'<SMALL>'                              %*htmText               $'</SMALL>'
            htmSTRIKE             =     $'<STRIKE>'                             %*htmText               $'</STRIKE>'
            htmSPAN               =     $'<SPAN' *htmSPAN_attrs $'>'            %(*htmText | *htmCENTER | *htmP) $'</SPAN>'
            htmSTRONG             =     $'<STRONG' *htmSTRONG_attrs $'>'        %*htmText               $'</STRONG>'
            htmSUB                =     $'<SUB>'                                %*htmText               $'</SUB>'
            htmSUP                =     $'<SUP>'                                %*htmText               $'</SUP>'
            htmTEXTAREA           =     $'<TEXTAREA' *htmTEXTAREA_attrs $'>'    !*htmData               $'</TEXTAREA>'
            htmTT                 =     $'<TT>'                                 %*htmText               $'</TT>'
            htmU                  =     $'<U>'                                  %*htmText               $'</U>'
            htmVAR                =     $'<VAR>'                                %*htmText               $'</VAR>'

            htmBASEFONT           =     $'<BASEFONT'    *htmBASEFONT_attrs  FENCE($'>' !$'</BASEFONT>' | $'/>')
            htmBR                 =     $'<BR'          *htmBR_attrs        FENCE($'>' !$'</BR>'       | $'/>')
            htmIMG                =     $'<IMG'         *htmIMG_attrs       FENCE($'>' !$'</IMG>'      | $'/>')
            htmINPUT              =     $'<INPUT'       *htmINPUT_attrs     FENCE($'>' !$'</INPUT>'    | $'/>')
*
*           Block-level or inline elements
*
            htmAPPLET             =     $'<APPLET' *htmAPPLET_attrs $'>'        %(*htmPARAM | *htmText) $'</APPLET>'
            htmBUTTON             =     $'<BUTTON' *htmBUTTON_attrs $'>'        %*htmText               $'</BUTTON>'
            htmIFRAME             =     $'<IFRAME' *htmIFRAME_attrs $'>'        %*htmText               $'</IFRAME>'
            htmOBJECT             =     $'<OBJECT' *htmOBJECT_attrs $'>'        %(*htmPARAM | *htmText) $'</OBJECT>'
            htmMAP                =     $'<MAP' *htmMAP_attrs $'>'              %*htmAREA               $'</MAP>'
            htmSCRIPT             =    ($'<SCRIPT' *htmSCRIPT_attrs $'>'        %(*htmData | *htmComment) $'</SCRIPT>') ;* $ OUTPUT

            htmAREA               =     $'<AREA' *htmAREA_attrs FENCE($'>' !$'</AREA>' | $'/>')
*
*           Block-level elements
*
            htmISINDEX            =     $'<ISINDEX'     *htmISINDEX_attrs   FENCE($'>' !$'</ISINDEX>' | $'/>')
            htmBASE               =     $'<BASE'        *htmBASE_attr       FENCE($'>' !$'</BASE>'    | $'/>')
            htmMETA               =     $'<META'        *htmMETA_attrs      FENCE($'>' !$'</META>'    | $'/>')
            htmLINK               =     $'<LINK'        *htmLINK_attrs      FENCE($'>' !$'</LINK>'    | $'/>')
            htmPARAM              =     $'<PARAM'       *htmPARAM_attrs     FENCE($'>' !$'</PARAM>'   | $'/>')
            htmEMBED              =     $'<EMBED'       *htmEMBED_attrs     FENCE($'>' !$'</EMBED>'   | $'/>')
            htmHR                 =     $'<HR'          *htmHR_attrs        FENCE($'>' !$'</HR>'      | $'/>')

            htmTITLE              =     $'<TITLE>'                              !*htmData               $'</TITLE>'
            htmNOSCRIPT           =     $'<NOSCRIPT>'                           %(*htmText | *htmBlock) $'</NOSCRIPT>'
            htmSTYLE              =     $'<STYLE' *htmSTYLE_attrs $'>'          !*htmData               $'</STYLE>'
            htmH                  =     $'<H1' *htmH_attrs $'>'                 %(*htmText | *htmDIV)   $'</H1>'
+                                 |     $'<H2' *htmH_attrs $'>'                 %(*htmText | *htmDIV)   $'</H2>'
+                                 |     $'<H3' *htmH_attrs $'>'                 %(*htmText | *htmDIV)   $'</H3>'
+                                 |     $'<H4' *htmH_attrs $'>'                 %(*htmText | *htmDIV)   $'</H4>'
+                                 |     $'<H5' *htmH_attrs $'>'                 %(*htmText | *htmDIV)   $'</H5>'
+                                 |     $'<H6' *htmH_attrs $'>'                 %(*htmText | *htmDIV)   $'</H6>'
            htmBIG                =     $'<BIG>'                                %*htmText               $'</BIG>'
            htmEM                 =     $'<EM>'                                 %*htmText               $'</EM>'
            htmKBD                =     $'<KBD>'                                %*htmText               $'</KBD>'
            htmOPTION             =     $'<OPTION' *htmOPTION_attrs $'>'        !*htmData               FENCE($'</OPTION>' | epsilon)
            htmP                  =    ($'<P' *htmP_attrs $'>'                  #(*htmText | *htmDIV | *htmUL) FENCE($'</P>' | epsilon)) ;* $ OUTPUT
            htmUL                 =     $'<UL' *htmUL_attrs $'>'                %*htmUL_LI              $'</UL>'
            htmUL_LI              =     $'<LI' *htmUL_LI_attrs $'>'             %(*htmText | *htmBlock | *htmH) FENCE($'</LI>' | epsilon)
            htmOL                 =     $'<OL' *htmOL_attrs $'>'                %*htmOL_LI              $'</OL>'
            htmOL_LI              =     $'<LI' *htmOL_LI_attrs $'>'             %(*htmText | *htmBlock) FENCE($'</LI>' | epsilon)
            htmDIR                =     $'<DIR' *htmDIR_MENU_attr $'>'          %*htmText               $'</DIR>'
            htmMENU               =     $'<MENU' *htmDIR_MENU_attr $'>'         %*htmText               $'</MENU>'
            htmPRE                =     $'<PRE' *htmPRE_attr $'>'               %*htmText               $'</PRE>'
            htmDL                 =     $'<DL' *htmDL_attrs $'>'                %(*htmDT | *htmDD)      $'</DL>'
            htmDT                 =     $'<DT' *htmDT_attrs $'>'                %(*htmText | *htmDIV) FENCE($'</DT>' | epsilon)
            htmDD                 =     $'<DD' *htmDD_attrs $'>'                %(*htmText | *htmBlock) FENCE($'</DD>' | epsilon)
            htmDIV                =    ($'<DIV' *htmDIV_attrs $'>'              %(*htmBODY_cont | *htmSTYLE) $'</DIV>') ;* $ OUTPUT
            htmCENTER             =     $'<CENTER' *htmCENTER_attrs $'>'        %*htmBODY_cont          $'</CENTER>'
            htmBLOCKQUOTE         =     $'<BLOCKQUOTE>'                         %*htmBODY_cont          $'</BLOCKQUOTE>'
            htmFORM               =     $'<FORM' *htmFORM_attrs $'>'            %*htmBODY_cont          $'</FORM>'
            htmTABLE              =     $'<TABLE' *htmTABLE_attrs $'>'          *htmTABLE_cont          $'</TABLE>'
            htmTHEAD              =     $'<THEAD>'                              #*htmTR                 $'</THEAD>'
            htmTFOOT              =     $'<TFOOT>'                              #*htmTR                 $'</TFOOT>'
            htmTBODY              =     $'<TBODY>'                              #*htmTR                 $'</TBODY>'
            htmCAPTION            =     $'<CAPTION' *htmCAPTION_attr $'>'       %*htmText               $'</CAPTION>'
            htmTR                 =     $'<TR' *htmTR_attrs $'>'                %(*htmTH | *htmTD | *htmSCRIPT) FENCE($'</TR>' | epsilon)
            htmTH                 =     $'<TH' *htmTH_TD_attrs $'>'             %*htmBODY_cont          FENCE($'</TH>' | epsilon)
            htmTD                 =     $'<TD' *htmTH_TD_attrs $'>'             %*htmBODY_cont          FENCE($'</TD>' | epsilon)
            htmADDRESS            =     $'<ADDRESS>'                            %(*htmP | *htmText)     $'</ADDRESS>'

            htmTABLE_cont         =     (   !*htmCAPTION
+                                           (   #*htmTR
+                                           |   !*htmTHEAD !*htmTFOOT *htmTBODY
+                                           )
+                                       |   *htmSCRIPT
+                                       )

            htmBlock              =     *htmP
+                                 |     *htmList
+                                 |     *htmPRE
+                                 |     *htmDL
+                                 |     *htmDIV
+                                 |     *htmCENTER
+                                 |     *htmBLOCKQUOTE
+                                 |     *htmFORM
+                                 |     *htmISINDEX
+                                 |     *htmHR
+                                 |     *htmTABLE
+                                 |     *htmIFRAME

            htmText               =     *htmData
+                                 |     *htmTT
+                                 |     *htmI
+                                 |     *htmB
+                                 |     *htmU
+                                 |     *htmSTRIKE
+                                 |     *htmBIG
+                                 |     *htmSMALL
+                                 |     *htmSUB
+                                 |     *htmSUP
+                                 |     *htmEM
+                                 |     *htmSTRONG
+                                 |     *htmDFN
+                                 |     *htmCODE
+                                 |     *htmSAMP
+                                 |     *htmKBD
+                                 |     *htmVAR
+                                 |     *htmCITE
+                                 |     *htmSPAN
+                                 |     *htmA
+                                 |     *htmBUTTON
+                                 |     *htmIMG
+                                 |     *htmAPPLET
+                                 |     *htmOBJECT
+                                 |     *htmFONT
+                                 |     *htmBASEFONT
+                                 |     *htmBR
+                                 |     *htmSCRIPT
+                                 |     *htmNOSCRIPT
+                                 |     *htmMAP
+                                 |     *htmLABEL
+                                 |     *htmINPUT
+                                 |     *htmSELECT
+                                 |     *htmTEXTAREA
+                                 |     *htmABBR
+                                 |     *htmEMBED

            htmList               =     *htmUL
+                                 |     *htmOL
+                                 |     *htmDIR
+                                 |     *htmMENU

            htmHTML_attrs         =    %(   VERSION $'=' STRING
+                                       |   LANG $'=' STRING
+                                       |   CLASS $'=' STRING
+                                       |   ID $'=' STRING
+                                       |   DIR $'=' STRING
+                                       |   XMLNS $'=' STRING
+                                       |   $'XML:LANG' $'=' STRING
+                                       |   $'XMLNS:B' $'=' STRING
+                                       |   $'XMLNS:DATA' $'=' STRING
+                                       |   $'XMLNS:EXPR' $'=' STRING
+                                       )

            htmHEAD_attrs         =     !(PROFILE $'=' STRING)

            htmDD_attrs           =    %(   CLASS $'=' STRING
+                                       |   ID $'=' STRING
+                                       )

            htmDT_attrs           =    %(   CLASS $'=' STRING
+                                       |   ID $'=' STRING
+                                       )

            htmBASE_attr          =     HREF $'=' STRING

            htmSCRIPT_attrs       =    %(   TYPE $'=' STRING
+                                       |   LANGUAGE $'=' STRING
+                                       |   SRC $'=' STRING
+                                       )

            htmIFRAME_attrs       =    %(   ALLOWTRANSPARENCY $'=' STRING
+                                       |   FRAMEBORDER $'=' NUMBER
+                                       |   HEIGHT $'=' STRING
+                                       |   ID $'=' STRING
+                                       |   MARGINHEIGHT $'=' NUMBER
+                                       |   MARGINWIDTH $'=' NUMBER
+                                       |   SCROLLING $'=' STRING
+                                       |   SRC $'=' STRING
+                                       |   STYLE $'=' STRING
+                                       |   TITLE $'=' STRING
+                                       |   WIDTH $'=' STRING
+                                       )

            htmOBJECT_attrs       =    %(   CLASSID $'=' STRING
+                                       |   HEIGHT $'=' STRING
+                                       |   ID $'=' STRING
+                                       |   WIDTH $'=' STRING
+                                       )

            htmEMBED_attrs        =    %(   ALLOWFULLSCREEN $'=' STRING
+                                       |   BGCOLOR $'=' STRING
+                                       |   ALLOWSCRIPTACCESS $'=' STRING
+                                       |   HEIGHT $'=' NUMBER
+                                       |   SRC $'=' STRING
+                                       |   TYPE $'=' STRING
+                                       |   WIDTH $'=' NUMBER
+                                       |   WMODE $'=' STRING
+                                       )

            htmSTRONG_attrs       =    %(   CLASS $'=' STRING
+                                       |   STYLE $'=' STRING
+                                       )

            htmISINDEX_attrs      =     !(PROMPT $'=' STRING)
            htmBASEFONT_attrs     =     !(SIZE $'=' NUMBER)
            htmMAP_attrs          =     !(NAME $'=' STRING)
            htmCENTER_attrs       =     !(STYLE $'=' STRING)

            htmSTYLE_attrs        =    %(   ID $'=' STRING
+                                       |   TYPE $'=' STRING
+                                       )

            htmMETA_attrs         =    %(  NAME $'=' STRING
+                                       |  CONTENT $'=' STRING
+                                       |  $'HTTP-EQUIV' $'=' STRING
+                                       )

            htmLINK_attrs         =    %(  REL $'=' STRING
+                                       |  REV $'=' STRING
+                                       |  HREF $'=' STRING
+                                       |  TITLE $'=' STRING
+                                       |  MEDIA $'=' STRING
+                                       |  SIZES $'=' STRING
+                                       |  TYPE $'=' STRING
+                                       |  CHARSET $'=' STRING
+                                       )

            htmBODY_attrs         =    %(  BACKGROUND $'=' STRING
+                                       |  BGCOLOR $'=' *htmCOLOR_val
+                                       |  TEXT $'=' *htmCOLOR_val
+                                       |  LINK $'=' *htmCOLOR_val
+                                       |  VLINK $'=' *htmCOLOR_val
+                                       |  ALINK $'=' *htmCOLOR_val
+                                       |  ID $'=' STRING
+                                       |  CLASS $'=' STRING
+                                       )

            htmH_attrs            =    %(  ALIGN $'=' *htmALIGN_val
+                                       |  CLASS $'=' STRING
+                                       |  ID $'=' STRING
+                                       )

            htmSPAN_attrs         =    %(   CLASS $'=' STRING
+                                       |   DIR $'=' STRING
+                                       |   ID $'=' STRING
+                                       |   ONCLICK $'=' STRING
+                                       |   STYLE $'=' STRING
+                                       |   TITLE $'=' STRING
+                                       )

            htmBUTTON_attrs       =    %(   ONCLICK $'=' STRING
+                                       |   TITLE $'=' STRING
+                                       |   TYPE $'=' STRING
+                                       )

            htmLABEL_attrs        =    %(   FOR $'=' STRING
+                                       |   ID $'=' STRING
+                                       |   CLASS $'=' STRING
+                                       )

            htmA_attrs            =    %(   ACCESSKEY $'=' STRING
+                                       |   CLASS $'=' STRING
+                                       |   $'DATA-COUNT' $'=' STRING
+                                       |   $'DATA-TEXT' $'=' STRING
+                                       |   $'DATA-URL' $'=' STRING
+                                       |   $'DATA-VIA' $'=' STRING
+                                       |   DIR $'=' STRING
+                                       |   HREF $'=' STRING
+                                       |   ID $'=' STRING
+                                       |   IMAGEANCHOR $'=' NUMBER
+                                       |   NAME $'=' STRING
+                                       |   ONCLICK $'=' STRING
+                                       |   ONCONTEXTMENU $'=' STRING
+                                       |   ONMOUSEOUT $'=' STRING
+                                       |   ONMOUSEOVER $'=' STRING
+                                       |   REL $'=' STRING
+                                       |   REV $'=' STRING
+                                       |   SHARE_URL $'=' STRING
+                                       |   STYLE $'=' STRING
+                                       |   TABINDEX $'=' STRING
+                                       |   TARGET $'=' STRING
+                                       |   TYPE $'=' STRING
+                                       |   TITLE $'=' STRING
+                                       )

            htmABBR_attrs         =    %(   CLASS $'=' STRING
+                                       |   TITLE $'=' STRING
+                                       )

            htmIMG_attrs          =    %(   ALIGN $'=' (*htmALIGN_special_val | STRING)
+                                       |   ALT $'=' STRING
+                                       |   BORDER $'=' NUMBER
+                                       |   CLASS $'=' STRING
+                                       |   HEIGHT $'=' STRING
+                                       |   HSPACE $'=' NUMBER
+                                       |   ID $'=' STRING
+                                       |   ISMAP !($'=' ISMAP)
+                                       |   LONGDESC $'=' STRING
+                                       |   SRC $'=' STRING
+                                       |   STYLE $'=' STRING
+                                       |   TITLE $'=' STRING
+                                       |   USEMAP $'=' STRING
+                                       |   VSPACE $'=' NUMBER
+                                       |   WIDTH $'=' STRING
+                                       )

            htmAPPLET_attrs       =    %(  CODEBASE $'=' STRING
+                                       |  CODE $'=' STRING
+                                       |  NAME $'=' STRING
+                                       |  ALT $'=' STRING
+                                       |  ALIGN $'=' *htmALIGN_special_val
+                                       |  HEIGHT $'=' NUMBER
+                                       |  WIDTH $'=' NUMBER
+                                       |  HSPACE $'=' NUMBER
+                                       |  VSPACE $'=' NUMBER
+                                       )

            htmPARAM_attrs        =    %(   NAME $'=' STRING
+                                       |   VALUE $'=' STRING
+                                       )

            htmFONT_attrs         =    !(  COLOR $'=' *htmCOLOR_val !(SIZE $'=' SIZE_VALUE)
+                                       |  SIZE $'=' SIZE_VALUE !(COLOR $'=' *htmCOLOR_val)
+                                       )

            htmBR_attrs           =    %(   CLEAR $'=' *htmCLEAR_val
+                                       |   STYLE $'=' STRING
+                                       )


            htmAREA_attrs         =    %(  SHAPE $'=' *htmSHAPE_val
+                                       |  COORDS $'=' STRING
+                                       |  NOHREF
+                                       |  NOHREF $'=' NOHREF
+                                       |  HREF $'=' STRING
+                                       |  ALT $'=' STRING
+                                       )

            htmINPUT_attrs        =    %(   ACCESSKEY $'=' STRING
+                                       |   ALIGN $'=' htmALIGN_special_val
+                                       |   ALT $'=' STRING
+                                       |   AUTOCOMPLETE $'=' STRING
+                                       |   BORDER $'=' NUMBER
+                                       |   CHECKED $'=' CHECKED
+                                       |   CHECKED
+                                       |   CLASS $'=' STRING
+                                       |   ID $'=' STRING
+                                       |   MAXLENGTH $'=' NUMBER
+                                       |   NAME $'=' STRING
+                                       |   ONCLICK $'=' STRING
+                                       |   ONFOCUS $'=' STRING
+                                       |   PLACEHOLDER $'=' STRING
+                                       |   SIZE $'=' NUMBER
+                                       |   SPELLCHECK $'=' STRING
+                                       |   SRC $'=' STRING
+                                       |   STYLE $'=' STRING
+                                       |   TABINDEX $'=' STRING
+                                       |   TITLE $'=' STRING
+                                       |   TYPE $'=' *htmTYPE_val
+                                       |   VALUE $'=' STRING
+                                       )

            htmSELECT_attrs       =    %(  NAME $'=' STRING
+                                       |  ID $'=' STRING
+                                       |  SIZE $'=' NUMBER
+                                       |  MULTIPLE !($'=' MULTIPLE)
+                                       )

            htmOPTION_attrs       =    %(   VALUE $'=' STRING
+                                       |   LABEL $'=' STRING
+                                       |   SELECTED !($'=' SELECTED)
+                                       )

            htmTEXTAREA_attrs     =     NAME $'=' STRING
+                                       (  ROWS $'=' NUMBER COLS $'=' NUMBER
+                                       |  COLS $'=' NUMBER ROWS $'=' NUMBER
+                                       )
+                                 |     ROWS $'=' NUMBER
+                                       (  NAME $'=' STRING COLS $'=' NUMBER
+                                       |  COLS $'=' NUMBER NAME $'=' STRING
+                                       )
+                                 |     COLS $'=' NUMBER
+                                       (  NAME $'=' STRING ROWS $'=' NUMBER
+                                       |  ROWS $'=' NUMBER NAME $'=' STRING
+                                       )

            htmP_attrs             =   %(   ALIGN $'=' *htmALIGN_val
+                                       |   CLASS $'=' STRING
+                                       )

            htmUL_attrs           =    %(  COMPACT !('=' COMPACT)
+                                       |  CLASS $'=' STRING
+                                       |  ID $'=' STRING
+                                       |  TYPE $'=' *htmTYPE_style_val
+                                       )
            htmUL_LI_attrs        =    %(  CLASS $'=' STRING
+                                       |  ID $'=' STRING
+                                       |  STYLE $'=' STRING
+                                       |  TYPE $'=' *htmTYPE_style_val
+                                       |  VALUE $'=' NUMBER
+                                       )

            htmOL_attrs           =    %(   CLASS $'=' STRING
+                                       |   COMPACT !($'=' COMPACT)
+                                       |   START $'=' NUMBER
+                                       |   TYPE $'=' (STRING | NUMBER)
+                                       )

            htmOL_LI_attrs        =    %(   CLASS $'=' STRING
+                                       |   TYPE $'=' (STRING | NUMBER)
+                                       |   VALUE $'=' NUMBER
+                                       )

            htmDIR_menu_attr      =     !(COMPACT !($'=' COMPACT))

            htmPRE_attr           =     !(WIDTH $'=' NUMBER)

            htmDL_attrs           =    %(   CLASS $'=' STRING
+                                       |   ID '=' STRING
+                                       |   COMPACT !('=' COMPACT)
+                                       )

            htmDIV_attrs          =    %(  ALIGN $'=' *htmALIGN_val
+                                       |  CLASS $'=' STRING
+                                       |  ID $'=' STRING
+                                       |  ONCLICK $'=' STRING
+                                       |  STYLE $'=' STRING
+                                       |  SUMMARY $'=' STRING
+                                       )

            htmFORM_attrs         =    %(  $'ACCEPT-CHARSET' $'=' STRING
+                                       |  ACTION $'=' STRING
+                                       |  METHOD $'=' *htmMETHOD_val
+                                       |  ENCTYPE $'=' STRING
+                                       |  ID $'=' STRING
+                                       |  NAME $'=' STRING
+                                       |  ONSUBMIT $'=' STRING
+                                       )

            htmHR_attrs           =    %(  ALIGN $'=' *htmALIGN_val
+                                       |  NOSHADE !($'=' NOSHADE)
+                                       |  SIZE $'=' NUMBER
+                                       |  WIDTH $'=' (NUMBER | PERCENT)
+                                       )

            htmTABLE_attrs        =    %(  ALIGN $'=' *htmALIGN_val
+                                       |  BORDER !($'=' (NUMBER | BORDER))
+                                       |  CELLPADDING $'=' NUMBER
+                                       |  CELLSPACING $'=' NUMBER
+                                       |  ID $'=' STRING
+                                       |  SUMMARY $'=' STRING
+                                       |  WIDTH $'=' (NUMBER | PERCENT)
+                                       )

            htmCAPTION_attr       =     !(ALIGN $'=' (TOP | BOTTOM))

            htmTR_attrs           =    !(  ALIGN $'=' *htmALIGN_val !(VALIGN $'=' *htmVALIGN_val)
+                                       |  VALIGN $'=' *htmVALIGN_val !(ALIGN $'=' *htmALIGN_val)
+                                       )

            htmTH_TD_attrs        =    %(  ALIGN $'=' *htmALIGN_val
+                                       |  CLASS $'=' STRING
+                                       |  COLSPAN $'=' NUMBER
+                                       |  HEIGHT $'=' NUMBER
+                                       |  ID $'=' STRING
+                                       |  NOWRAP !($'=' NOWRAP)
+                                       |  ROWSPAN $'=' NUMBER
+                                       |  SCOPE $'=' STRING
+                                       |  TITLE $'=' STRING
+                                       |  VALIGN $'=' *htmVALIGN_val
+                                       |  WIDTH $'=' NUMBER
+                                       )

            htmALIGN_val          =     LEFT
+                                 |     RIGHT
+                                 |     CENTER

            htmALIGN_special_val  =     TOP
+                                 |     MIDDLE
+                                 |     BOTTOM
+                                 |     LEFT
+                                 |     RIGHT

            htmCLEAR_val          =     LEFT
+                                 |     RIGHT
+                                 |     ALL
+                                 |     NONE

            htmCOLOR_val          =     RGB
+                                 |     AQUA
+                                 |     BLACK
+                                 |     BLUE
+                                 |     FUCHSIA
+                                 |     GRAY
+                                 |     GREEN
+                                 |     LIME
+                                 |     MAROON
+                                 |     NAVY
+                                 |     OLIVE
+                                 |     PURPLE
+                                 |     RED
+                                 |     SLIVER
+                                 |     TEAL
+                                 |     WHITE
+                                 |     YELLOW

            htmMETHOD_val         =     GET
+                                 |     POST

            htmSHAPE_val          =     RECT
+                                 |     CIRCLE
+                                 |     POLY
+                                 |     DEFAULT

            htmTYPE_val           =     TEXT
+                                 |     PASSWORD
+                                 |     CHECKBOX
+                                 |     RADIO
+                                 |     SUBMIT
+                                 |     RESET
+                                 |     FILE
+                                 |     HIDDEN
+                                 |     IMAGE

            htmTYPE_style_val     =     DISC
+                                 |     SQUARE
+                                 |     CIRCLE

            htmVALIGN_val         =     TOP
+                                 |     MIDDLE
+                                 |     BOTTOM
+                                 |     BASELINE
*---------- --------------------------------------------------------------------------------------------------------------
            htmPatterns =
+           'htmRecognizer/htmDOCTYPE/htmData/htmHTML/htmHTML_attrs/htmHEAD/htmTITLE/htmISINDEX/htmBASE/'
+           'htmSCRIPT/htmNOSCRIPT/htmSTYLE/htmMETA/htmMETA_attrs/htmLINK/htmLINK_attrs/htmBODY/'
+           'htmBODY_attrs/htmBODY_cont/htmH/htmH_attr/htmText/htmPhrase/htmSpecial/htmForms/htmTT/htmI/htmB/htmU/'
+           'htmSTRIKE/htmBIG/htmSMALL/htmSUB/htmSUP/htmEM/htmSTRONG/htmDFN/htmCODE/htmSAMP/htmKBD/htmVAR/htmCITE/htmA/'
+           'htmA_attrs/htmIMG/htmIMG_attrs/htmAPPLET/htmAPPLET_attrs/htmPARAM/htmPARAM_attrs/htmFONT/'
+           'htmFONT_attrs/htmBASEFONT/htmBR/htmMAP/htmAREA/htmAREA_attrs/htmINPUT/htmINPUT_attrs/htmSELECT/'
+           'htmSELECT_attrs/htmOPTION/htmOPTION_attrs/htmTEXTAREA/htmTEXTAREA_attrs/htmBlock/htmP/'
+           'htmP_attr/htmList/htmUL/htmUL_attrs/htmUL_LI/'
+           'htmUL_LI_attrs/htmOL/htmOL_attrs/htmOL_LI/htmOL_LI_attrs/htmOL_LI_attr_type/htmDIR/'
+           'htmMENU/htmDIR_menu_attr/htmPRE/htmPRE_attr/htmDL/htmDL_attrs/'
+           'htmDT/htmDD/htmDIV/htmCENTER/htmBLOCKQUOTE/htmFORM/htmFORM_attrs/htmHR/htmHR_attrs/'
+           'htmTABLE/htmTABLE_attrs/htmCAPTION/htmCAPTION_attr/htmTR/htmTR_attrs/'
+           'htmTH/htmTD/htmTH_TD_attrs/htmADDRESS/htmALIGN_val/htmALIGN_special_val/htmCLEAR_val/'
+           'htmCOLOR_val/htmMETHOD_val/htmSHAPE_val/htmTYPE_val/htmTYPE_style_val/htmVALIGN_val/'
*---------- ----------- --- --------------------------------------------------- ------------------------
            hPatterns   =     htmPatterns
H10         hPatterns   POS(0) BREAK('/') . hP '/' =                            :F(H20)
            $hP         =     TZ(3, hP, $hP)                                    :(H10)
H20
*---------- ----------- --- --------------------------------------------------- ------------------------
