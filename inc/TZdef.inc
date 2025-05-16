-INCLUDE    'ss.inc'
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserDefs()')                                                             :(UserDefsEnd)
UserDefs    u                 =     0
            usr               =     ARRAY('1:32')
            doDebug           =     0
            doDebugAfter1st   =     FALSE
            doInclWhite       =     TRUE
            doInclNL          =     TRUE
            doReportFileName  =     TRUE
            doRemember        =     TRUE
            fndExt            =     ('cpp' | 'inl') . extc
            fndCmd            =     'd:/mksnt/find //flash/e/dev ( -name "*obj.cpp" -o -name "*attr.cpp" -o -name "*attr.inl" ) -print'
*           fndCmd            =     'd:/mksnt/find //flash/e/dev ( -name "*obj.cpp" ) -print'
*           fndCmd            =     'd:/mksnt/find //flash/e/dev ( -name "*attr.cpp" -o -name "*attr.inl" ) -print'
            fndSpecific       =     'def/'
            fndExclude        =     'alodef/'
            spcpfx            =
            spcpfx            =     EQ(doInclWhite, TRUE) "$' ' "
            keyint            =     ('?') . tx

            blanks            =     (bs nl | SPAN(' ' tab cr ff))
            white             =     (bs nl | SPAN(' ' tab cr ff nl))
            cStyleComment     =     '/*' BREAKX('*') '*/'
            cppStyleComment   =     '//' BREAK(nl) nl
            space             =     (blanks | cStyleComment | cppStyleComment) FENCE(*space | epsilon)
            whitespace        =     (white | cStyleComment | cppStyleComment) FENCE(*whitespace | epsilon)
            $' '              =     FENCE(whitespace | epsilon)
            $'  '             =     FENCE(space | epsilon)
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            exponent          =     ('E' | 'e') ('+' | '-' | epsilon) SPAN('0123456789')
            floatingLiteral   =     (  SPAN('0123456789')
+                                      '.' (SPAN('0123456789') | epsilon) (exponent | epsilon) (ANY('Ll') | epsilon)
+                                   |  '.' SPAN('0123456789') (exponent | epsilon) (ANY('Ll') | epsilon)
+                                   |  SPAN('0123456789') exponent (ANY('Ll') | epsilon)
+                                   |  SPAN('0123456789') (exponent | epsilon) ANY('Ll')
+                                   )
            decimalLiteral    =     ANY('123456789') FENCE(SPAN('0123456789') | epsilon)
            hexLiteral        =     '0' ('X' | 'x') SPAN('0123456789ABCDEFabcdef')
            octalLiteral      =     '0' FENCE(SPAN('01234567') | epsilon)
            integerLiteral    =     (decimalLiteral | hexLiteral | octalLiteral) (ANY('Ll') | epsilon)
            escapedCharacter  =     (  bs
+                                      (  ANY('abfnrtv' '"' bs "'" nl)
+                                      |  ANY('01234567') FENCE(ANY('01234567') | epsilon)
+                                      |  ANY('0123') ANY('01234567') ANY('01234567')
+                                      |  ANY('Xx') SPAN('0123456789ABCDEFabcdef')
+                                      )
+                                   )

            characterLiteral  =     "'" (escapedCharacter | NOTANY("'" bs cr lf)) "'"
            stringLiteral     =     '"' ARBNO(escapedCharacter | BREAK('"' bs cr lf)) '"'

            keywords          =     '_TCHAR ATTRLEN ATTRRANGE ATTRDEFDATA OBJDEFDATA'
            reswords          =     'char const include int static'
            special           =     '} { ) ('
            operators         =     '~ || |= | ^= ^ ] [ ? >>= >> >= > == = <= <<= << < ; :: : /= / ... .* . ->* -> '
+                                   '-= -- - , += ++ + *= * &= && & %= % # != !'
            ident             =     ANY(&UCASE '_' &LCASE) FENCE(SPAN(&UCASE '_' &LCASE '0123456789') | epsilon)
            identifier        =     ident $ tx $ *notmatch(reswords, (POS(0) | ' ') tx (' ' | RPOS(0)))
            resword           =     ident $ tx $ *match(reswords, (POS(0) | ' ') tx (' ' | RPOS(0)))
            keyword           =     ident $ tx $ *match(keywords, (POS(0) | ' ') tx (' ' | RPOS(0)))
            Populate(.TX, ident, keywords, reswords, special, operators)
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            cTokens           =     *cToken FENCE(*cTokens | epsilon)
            cToken            =     $' '
+                                   (  *floatingLiteral
+                                   |  *integerLiteral
+                                   |  *characterLiteral
+                                   |  *stringLiteral
+                                   |  *identifier
+                                   |  *operator
+                                   )
            cBlock            =     $'{' ARBNO(*cBlockBody) $'}'
            cExpr             =     $'(' ARBNO(*cExprBody) $')'
            cBlockBody        =     *cToken | *cBlock | *cExpr
            cExprBody         =     *cToken | *cExpr
            cChunk            =     $'{' (%*cBlockBody) % $',' $'}'

*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            cObjUniqueKeys    =     ($'_TCHAR' | char) $'*' $' ' *identifier $'[' $']' $'=' $'{' BREAK('}') $'}' $';'
            cObjRecognizer    =     %( $'#' include $'<' BREAK('>') $'>' $' '
+                                   |  $'#' include $' ' *stringLiteral $' '
+                                   ) . defProlog1
+                                   %(*cObjUniqueKeys) . defProlog2
+                                   $' ' . defProlog3
+                                   OBJDEFDATA $' ' *identifier . objDefNm $'[' $']' $'='
+                                   $'{'
+                                      $'{' $' ' '0' $'}' $','
+                                      epsilon . *assign(.obj, *TABLE())
+                                      epsilon . *assign(.spc, *TABLE())
+                                      (  $' ' . defOBJDEFSpace
+                                         epsilon . *assign(.spc[0],      *(spc[0] + 1))
+                                         epsilon . *assign(.spc[spc[0]], *defOBJDEFSpace)
+                                         *OBJDEFStruct
+                                         epsilon . *assign(.obj[0],      *(obj[0] + 1))
+                                         epsilon . *assign(.obj[obj[0]], *objdef)
+                                      |  *cChunk . objdefTxt . *Remember(objdefTxt)
+                                      ) % $','
+                                   !$',' $'}' $';'
+                                   (const int $' ' *identifier $'=' $' ' *identifier $'(' $' ' *identifier $')' $';' $' ') . defEpilog1
+                                   (const char $'*' $' ' *identifier $'=' $' ' *identifier $';' $' ') . defEpilog2

            OBJDEFStruct      =     epsilon . *assign(.objdef, *objdef())
+                                   $'{' $' ' *stringLiteral . *pszObjInternalName(objdef)
+                                   $',' $' ' *stringLiteral . *pszObjExternalName(objdef)
+                                   $',' $' ' (*stringLiteral | '0') . *pszObjParentIntName(objdef)
+                                   $',' $' ' *integerLiteral . *wObjInternalID(objdef)
+                                   $',' $' ' *integerLiteral . *wBmpOffset(objdef)
+                                   $',' $' ' *integerLiteral . *wMenuSection(objdef)
+                                   $',' $' ' *integerLiteral . *wMenuGroup(objdef)
+                                   $',' $' ' (*stringLiteral | '0') . *pszObjVisibility(objdef)
+                                   $',' $' ' (*stringLiteral | '0') . *pszXT_Extractor(objdef)
+                                   $',' $' ' (*stringLiteral | '0') . *pszXTXT_Table(objdef)
+                                   $',' $' ' (*stringLiteral | '0') . *pszNameSpace(objdef)
+                                   $',' $' ' (*stringLiteral | '0') . *pszDBVerQualifier(objdef)
+                                   $',' $' ' *identifier . *apszUniqueKeys(objdef)
+                                   !( $','
+                                      !( $' ' (*identifier | '0') . *pAttributes(objdef)
+                                         !($',' $' ' !%*cExprBody . *dwFlags(objdef))
+                                      )
+                                   )
+                                   $'}'

*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            cAttrRecognizer   =     !%($'#' include $'<' BREAK('>') $'>' $' '
+                                   |  $'#' include $' ' *stringLiteral $' '
+                                   ) . defProlog1
+                                   !%(!static ATTRLEN $' ' *identifier $'[' $']' $'=' *cChunk $';' $' ') . defProlog2
+                                   !%(!static ATTRRANGE $' ' *identifier $'[' $']' $'=' *cChunk $';' $' ') . defProlog3
+                                   epsilon . *assign(.attr, *TABLE())
+                                   %(
+                                      !static ATTRDEFDATA $' ' *identifier . attrDefNm $'[' $']' $'='
+                                      epsilon . *assign(.attr[attrDefNm], *TABLE())
+                                      $'{'
+                                      (  *ATTRDEFStruct
+                                         epsilon . *assign(.attr[attrDefNm][0], *(attr[attrDefNm][0] + 1))
+                                         epsilon . *assign(.attr[attrDefNm][attr[attrDefNm][0]], *attrdef)
+                                      |  $'{' $' ' '0' $'}'
+                                      |  *cChunk . attrdef . *Remember(attrdef)
+                                      ) % $','
+                                      $'}' $';'
+                                   )

            ATTRDEFStruct     =     epsilon . *assign(.attrdef, *attrdef())
+                                   $'{' $' ' (*identifier | *stringLiteral) . *pszAttrName(attrdef)
+                                   $',' $' ' (*identifier | '0') . *pLength(attrdef)
+                                   $',' $' ' (*identifier | '0') . *eDBMSMinValidVersion(attrdef)
+                                   $',' $' ' (*identifier | '0') . *eDBMSMaxValidVersion(attrdef)
+                                   $',' $' ' (*identifier | '0') . *pRange(attrdef)
+                                   $',' $' ' (*identifier | '0') . *wFormat(attrdef)
+                                   !($',' $' ' %*cExprBody . *dwFlags(attrdef))
+                                   $'}'

            cRecognizer       =     epsilon $ obj $ attr (*cObjRecognizer | *cAttrRecognizer) $' ' RPOS(0)

            cStuff            =     ARBNO(
+                                      *cToken
+                                   |  $'{'
+                                   |  $'}'
+                                   |  $'('
+                                   |  $')'
+                                   )

                                                                                             :(RETURN)
UserDefsEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserFinal()')                                                            :(UserFinalEnd)
UserFinal                                                                                    :(RETURN)
UserFinalEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DATA('objdef('
+              'pszObjInternalName,'
+              'pszObjExternalName,'
+              'pszObjParentIntName,'
+              'wObjInternalID,'
+              'wBmpOffset,'
+              'wMenuSection,'
+              'wMenuGroup,'
+              'pszObjVisibility,'
+              'pszXT_Extractor,'
+              'pszXTXT_Table,'
+              'pszNameSpace,'
+              'pszDBVerQualifier,'
+              'apszUniqueKeys,'
+              'pAttributes,'
+              'dwFlags'
+              ')'
+           )

            DATA('attrdef('
+              'pszAttrName,'
+              'pLength,'
+              'eDBMSMinValidVersion,'
+              'eDBMSMaxValidVersion,'
+              'pRange,'
+              'wFormat,'
+              'dwFlags'
+              ')'
+           )

            DEFINE('UserRpt()'
+              'attrArr,attrdef,attrdefs,basenm,cpp,cppnm,filenm,i,intName,j,'
+              'prefix,keyVar,keys,objdef,src,static'
+           )                                                                                :(UserRptEnd)
UserRpt     basenm            =     pathnm
            basenm            '.' fndExt RPOS(0) =
            cppnm             =     basenm '.cxx'
            filenm            =     splitname(pathnm)[2]                                     :f(error)
            filenm            POS(0) ARB . prefix ('obj' | 'attr')                           :f(error)
            basenm            'cmxattr'                                                      :f(UserRpt10)
            static            =     'static '
UserRpt10   DIFFER(obj)                                                                      :f(UserRpt30)
UserRpt11   defProlog2        'const ' ('_TCHAR' | 'char') $'*' = 'char *'                   :s(UserRpt11)
            src               =     defProlog1 defProlog2 defProlog3
            src               =     src 'OBJDEFDATA ' objDefNm '[] =' nl
            src               =     src '{' nl
            src               =     src '   { 0 },'
            i                 =     0
UserRpt20   i                 =     LT(i, obj[0]) i + 1                                      :f(UserRpt25)
            dlm               =     NE(i, obj[0]) ','
            dlm               =     EQ(i, obj[0])
            objdef            =     obj[i]
            intName           =     pszObjInternalName(objdef)
            intName           POS(0) '"' BREAK('"') . intName '"' RPOS(0)
            keys              =     apszUniqueKeys(objdef)
            keyVar            =     (DIFFER(keys, '0') prefix '_keys_' intName, '0')
            src               =     src spc[i]
+                                   '{ ' RPAD(pszObjInternalName(objdef) ',', 12)
+                                   ' ' RPAD(pszObjExternalName(objdef) ',', 31)
+                                   ' ' RPAD(pszObjParentIntName(objdef) ',', 13)
+                                   ' ' LPAD(wObjInternalID(objdef), 4) ','
+                                   ' ' LPAD(wBmpOffset(objdef), 3) ','
+                                   ' ' LPAD(wMenuSection(objdef), 1) ','
+                                   ' ' LPAD(wMenuGroup(objdef), 3) ','
+                                   ' ' RPAD(pszObjVisibility(objdef) ',', 8)
+                                   ' ' RPAD(pszXT_Extractor(objdef) ',', 16)
+                                   ' ' RPAD(pszXTXT_Table(objdef) ',', 12)
+                                   ' ' RPAD(pszNameSpace(objdef) ',', 14)
+                                   ' ' RPAD(pszDBVerQualifier(objdef) ',', 10)
+                                   ' ' RPAD(keyVar ',', 19)
+                                   ' ' RPAD((DIFFER(pAttributes(objdef)) pAttributes(objdef), 0) ',', 22)
+                                   ' ' (DIFFER(dwFlags(objdef)) dwFlags(objdef), 0)
+                                   ' }' dlm                                                 :(UserRpt20)
UserRpt25   src               =     src nl '};'
            src               =     src defEpilog1 defEpilog2                                :(UserRpt40)
UserRpt30   DIFFER(attr)                                                                     :f(RETURN)
            src               =     defProlog1 defProlog2 defProlog3
            attrArr           =     CONVERT(attr, 'ARRAY')                                   :f(xerr)
            i                 =     0
UserRpt33   i                 =     i + 1
            attrDefNm         =     attrArr[i, 1]                                            :f(UserRpt40)
            attrdefs          =     attrArr[i, 2]
            src               =     src static 'ATTRDEFDATA ' attrDefNm '[] =' nl
            src               =     src '{' nl
            j                 =     0
UserRpt35   j                 =     LT(j, attrdefs[0]) j + 1                                 :f(UserRpt37)
            attrdef           =     attrdefs[j]
            dwFlags(attrdef)  =     IDENT(dwFlags(attrdef)) 0
            src               =     src
+                                   '   { ' RPAD(pszAttrName(attrdef) ',', 33)
+                                   ' ' RPAD(pLength(attrdef) ',', 14)
+                                   ' ' RPAD(eDBMSMinValidVersion(attrdef) ',', 16)
+                                   ' ' RPAD(eDBMSMaxValidVersion(attrdef) ',', 21)
+                                   ' ' RPAD(pRange(attrdef) ',', 16)
+                                   ' ' RPAD(wFormat(attrdef) ',', 18)
+                                   ' ' (DIFFER(dwFlags(attrdef)) dwFlags(attrdef), 0)
+                                   ' },' nl                                                 :(UserRpt35)

UserRpt37   src               =     src '   { 0 }' nl
            src               =     src '};' nl nl                                           :(UserRpt33)
UserRpt40   OUTPUT(.cpp, 4, cppnm)                                                           :f(xerr)
UserRpt45   src               POS(0) BREAK(nl) . cpp nl =                                    :s(UserRpt45)
            ENDFILE(4)                                                                       :(RETURN)
UserRptEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserTokens()')                                                           :(UserTokensEnd)
UserTokens  tok[t = t + 1] = token(,, .cRecognizer)
            tok[t = t + 1] = token(, *(spcpfx '*floatingLiteral'),  *floatingLiteral)
            tok[t = t + 1] = token(, *(spcpfx '*integerLiteral'),   *integerLiteral)
            tok[t = t + 1] = token(, *(spcpfx '*characterLiteral'), *characterLiteral)
            tok[t = t + 1] = token(, *(spcpfx '*stringLiteral'),    *stringLiteral)
            tok[t = t + 1] = token(, *(tx), *resword)
            tok[t = t + 1] = token(, *(tx), *keyword)
            tok[t = t + 1] = token(, *(spcpfx '*identifier'), *identifier . tx)
            tok[t = t + 1] = token(, *("$'" tx "'"), *operator . tx)
            tok[t = t + 1] = token('{')
            tok[t = t + 1] = token('}')
            tok[t = t + 1] = token('(')
            tok[t = t + 1] = token(')')

            dbg[.cBlock]            = TRUE
            dbg[.cExpr]             = TRUE
            dbg[.cObjUniqueKeys]    = TRUE

                                                                                             :(RETURN)
UserTokensEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
