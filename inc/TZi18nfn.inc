-INCLUDE    'ss.inc'
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserDefs()')                                                             :(UserDefsEnd)
UserDefs    u                 =     0
            usr               =     ARRAY('1:32')
*           &STLIMIT          =     -1
            doDebug           =     0
            doDebugAfter1st   =     TRUE
            doInclWhite       =     TRUE
            doInclNL          =     TRUE
            doReportFileName  =     TRUE
            doRemember        =     FALSE
            fndExt            =     ('CPP' | 'cpp' | 'C' | 'c' | 'H' | 'h') . extc
            fndCmd            =     'd:/mksnt/find //flash/e/dev/oracle ( -name "*.c" -o -name "*.cpp" -o -name "*.h" ) -print'
            fndSpecific       =     '/' ('common' | 'alo' | 'include') '/'
*           fndSpecific       =     '/' ('alo' | 'alm' | 'akm') '/'
*           fndSpecific       =     '/common/cmx/'
            fndExclude        =     'alo' SPAN(digits) BREAK('.') '.c'
+                             |     'AlxPv' ('D22' | 'Syb') '.cpp'
+                             |     '/common/acm/' ('acmcomp' | 'acmcrypt') '/'
+                             |     'akmgjcl.cpp'
+                             |     'akmwkman.cpp'
+                             |     'akmusrsv.cpp'
+                             |     'PDBAnalysiwsTypePage.cpp'
+                             |     'houtline.c'
+                             |     'l$uosio.c'
+                             |     'ysetup.c'
+                             |     'yypars.c'
+                             |     'yyreds.c'
+                             |     'aloiddlp'
+                             |     'al2iddlp'
+                             |     'AlxPvEdt.h'
+                             |     '/mvsincl/'
+                             |     '/ThirdParty/'
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

*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            whocares          =     '_vsnprintf '
+                                   'fprintf '
+                                   'printf '
+                                   'sprintf '
+                                   'vfprintf '
+                                   'vprintf '
+                                   'vsprintf '
+                                   'isalnum '
+                                   'isalpha '
+                                   'iscntrl '
+                                   'isdigit '
+                                   'isgraph '
+                                   'islower '
+                                   'isprint '
+                                   'ispunct '
+                                   'isspace '
+                                   'isupper '
+                                   'isxdigit '
+                                   'tolower '
+                                   'toupper'

            keywords          =

            yipper            =     '_stricoll '
+                                   '_strncoll '
+                                   '_strnicoll '
+                                   'fgetchar '
+                                   'fgets '
+                                   'fputchar '
+                                   'fputs '
+                                   'getc '
+                                   'getchar '
+                                   'gets '
+                                   'putc '
+                                   'putchar '
+                                   'puts '
+                                   'scanf '
+                                   'sscanf '
+                                   'strcat '
+                                   'strchr '
+                                   'strclen '
+                                   'strcmp '
+                                   'strcmpi '
+                                   'strcoll '
+                                   'strcpy '
+                                   'strcspn '
+                                   'strdup '
+                                   'strftime '
+                                   'stricmp '
+                                   'strlen '
+                                   'strlwr '
+                                   'strncat '
+                                   'strncmp '
+                                   'strncpy '
+                                   'strnicmp '
+                                   'strpbrk '
+                                   'strrchr '
+                                   'strrev '
+                                   'strspn '
+                                   'strstr '
+                                   'strtok '
+                                   'strupr '
+                                   'strxfrm'

            reswords          =     ''
            special           =     '} { ) ('
            operators         =     '~ || |= | ^= ^ ] [ ? >>= >> >= > == = <= <<= << < ; :: : /= / ... .* . ->* -> '
+                                   '-= -- - , += ++ + *= * &= && & %= % # != !'
            ident             =     ANY(&UCASE '_' &LCASE) FENCE(SPAN(&UCASE '_' &LCASE '0123456789') | epsilon)
            identifier        =     ident $ tx $ *notmatch(reswords, (POS(0) | ' ') tx (' ' | RPOS(0)))
            resword           =     ident $ tx $ *match(reswords, (POS(0) | ' ') tx (' ' | RPOS(0)))
            keyword           =     ident $ tx $ *match(keywords, (POS(0) | ' ') tx (' ' | RPOS(0)))
            Populate(.TX, ident, keywords, reswords, special, operators)
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            cTokens           =     $' ' *cToken FENCE(*cTokens | epsilon)
            cToken            =     (  *floatingLiteral
+                                   |  *integerLiteral
+                                   |  *characterLiteral
+                                   |  *stringLiteral
+                                   |  *identifier
+                                   |  *operator
+                                   )
            cBlock            =     $'{' ARBNO(*cBlockBody) $'}'
            cExpr             =     $'(' ARBNO(*cExprBody) $')'
            cBlockBody        =     $' ' *cToken | *cBlock | *cExpr
            cExprBody         =     $' ' *cToken | *cExpr

            cPoundDefine      =     $'#' $'  ' 'define' ARBNO($'  ' (*cToken | '{' | '}' | '(' | ')')) $'  ' nl
            cInteresting      =     $' '
+                                   (  epsilon . *assign(.c, *(IDENT(c) TABLE()))
+                                      *keyword . cKey . *assign(.c[cKey], *(c[cKey] + 1))
+                                      $'(' ARBNO(*cExprBody) $')'
+                                   ) . stuff . *Remember(stuff)

            cNotInteresting   =     ($'.' | $'->') $' ' (*keyword $'(' ARBNO(*cExprBody) $')')
            fileOrPath        =     icase('file') | icase('path')
            idFileOrPath      =     *identifier $ idTry $ *match(idTry, fileOrPath)
            cCharArray        =     ('char' | '_TCHAR') $' ' *idFileOrPath
+                                   $'[' $' ' NOTANY(']') BREAK(']') $']' BREAK('=;') ('=' | ';')
            cRecognizer       =     epsilon $ stuff
+                                   ARBNO(
+                                      *cPoundDefine
+                                   |  $' ' *cCharArray . stuff . *Remember(stuff)
+                                   |  $' ' *cToken
+                                   |  $'{'
+                                   |  $'}'
+                                   |  $'('
+                                   |  $')'
+                                   ) $' ' RPOS(0)

            parameters        =     $' ' ($'(' ARBNO(*cExprBody) $')') . params
            marker            =     (POS(0) | NOTANY(&UCASE '_' &LCASE '0123456789')) . mrk
            lpFunc            =     marker *keyword . func *parameters

            tcs               =     TABLE()

            tcs['lpStrcat']   =     'strcat'
            tcs['lpStrchr']   =     'strchr'
            tcs['lpStrcmp']   =     'strcmp'
            tcs['lpStrcpy']   =     'strcpy'
            tcs['lpStricmp']  =     'stricmp'
            tcs['lpStrlen']   =     'strlen'
            tcs['lpStrncat']  =     'strncat'
            tcs['lpStrncmp']  =     'strncmp'
            tcs['lpStrnicmp'] =     'strnicmp'
            tcs['lpStrrchr']  =     'strrchr'
            tcs['lpStrtok']   =     'strtok'
            tcs['lpStrstr']   =     '_tcsistr'

            tcs['_fstrcat']   =     'strcat'
            tcs['_fstrchr']   =     'strchr'
            tcs['_fstrcmp']   =     'strcmp'
            tcs['_fstrcpy']   =     'strcpy'
            tcs['_fstrcspn']  =     'strcspn'
            tcs['_fstrdup']   =     'strdup'
            tcs['_fstricmp']  =     'stricmp'
            tcs['_fstrlen']   =     'strlen'
            tcs['_fstrlwr']   =     'strlwr'
            tcs['_fstrncat']  =     'strncat'
            tcs['_fstrncmp']  =     'strncmp'
            tcs['_fstrncpy']  =     'strncpy'
            tcs['_fstrnicmp'] =     'strnicmp'
            tcs['_fstrnset']  =     'strnset'
            tcs['_fstrpbrk']  =     'strpbrk'
            tcs['_fstrrchr']  =     'strrchr'
            tcs['_fstrrev']   =     'strrev'
            tcs['_fstrset']   =     'strset'
            tcs['_fstrspn']   =     'strspn'
            tcs['_fstrstr']   =     'strstr'
            tcs['_fstrtok']   =     'strtok'
            tcs['_fstrupr']   =     'strupr'
            tcs['_nstrdup']   =     'strdup'

            tcs['lstrcmp']    =     'strcmp'
            tcs['lstrcmpi']   =     'stricmp'
            tcs['lstrcpyn']   =     'strncpy'
            tcs['lstrcpy']    =     'strcpy'
            tcs['lstrcat']    =     'strcat'
            tcs['lstrlen']    =     'strlen'

            tcs['__isascii']  =     'isascii'
            tcs['__iscsym']   =     'iscsym'
            tcs['__iscsymf']  =     'iscsymf'
            tcs['__toascii']  =     'toascii'
            tcs['_fgetchar']  =     'fgetchar'
            tcs['_fputchar']  =     'fputchar'
            tcs['_strcmpi']   =     'stricmp'
            tcs['_stricmp']   =     'stricmp'
            tcs['_strlwr']    =     'strlwr'
            tcs['_strnicmp']  =     'strnicmp'
            tcs['_strrev']    =     'strrev'
            tcs['_strupr']    =     'strupr'
            tcs['_tolower']   =     'tolower'
            tcs['_toupper']   =     'toupper'

            tcs['_stricoll']  =     '_tcsicoll'
            tcs['_strncoll']  =     '_tcsnccoll'
            tcs['_strnicoll'] =     '_tcsncicoll'
            tcs['_vsnprintf'] =     '_vsntprintf'    ;*
            tcs['fgetchar']   =     '_fgettchar'     ;*
            tcs['fgets']      =     '_fgetts'        ;*
            tcs['fprintf']    =     '_ftprintf'      ;*
            tcs['fputchar']   =     '_fputtchar'     ;*
            tcs['fputs']      =     '_fputts'        ;*
            tcs['getc']       =     '_gettc'         ;*
            tcs['getchar']    =     '_gettchar'      ;*
            tcs['gets']       =     '_getts'         ;*
            tcs['isalnum']    =     '_istalnum'
            tcs['isalpha']    =     '_istalpha'
            tcs['iscntrl']    =     '_istcntrl'
            tcs['isdigit']    =     '_istdigit'
            tcs['isgraph']    =     '_istgraph'
            tcs['islower']    =     '_istlower'
            tcs['isprint']    =     '_istprint'
            tcs['ispunct']    =     '_istpunct'
            tcs['isspace']    =     '_istspace'
            tcs['isupper']    =     '_istupper'
            tcs['isxdigit']   =     '_istxdigit'
            tcs['printf']     =     '_tprintf'       ;*
            tcs['putc']       =     '_puttc'
            tcs['putchar']    =     '_puttchar'
            tcs['puts']       =     '_putts'         ;*
            tcs['scanf']      =     '_tscanf'
            tcs['sprintf']    =     '_stprintf'      ;*
*           tcs['sscanf']     =     '_stscanf'
            tcs['strcat']     =     '_tcscat'
            tcs['strchr']     =     '_tcschr'
            tcs['strclen']    =     '_tcsclen'
            tcs['strcmp']     =     '_tcscmp'
            tcs['strcmpi']    =     '_tcsicmp'
            tcs['strcoll']    =     '_tcscoll'
            tcs['strcpy']     =     '_tcscpy'
            tcs['strcspn']    =     '_tcscspn'
            tcs['strdup']     =     '_tcsdup'
            tcs['strftime']   =     '_tcsftime'
            tcs['stricmp']    =     '_tcsicmp'
            tcs['strlen']     =     '_tcslen'
            tcs['strlwr']     =     '_tcslwr'
            tcs['strncat']    =     '_tcsncat'
            tcs['strncmp']    =     '_tcsncmp'
            tcs['strncpy']    =     '_tcsncpy'
            tcs['strnicmp']   =     '_tcsnicmp'
            tcs['strpbrk']    =     '_tcspbrk'
            tcs['strrchr']    =     '_tcsrchr'
            tcs['strrev']     =     '_tcsrev'
            tcs['strspn']     =     '_tcsspn'
            tcs['strstr']     =     '_tcsstr'
            tcs['strtok']     =     '_tcstok'
            tcs['strupr']     =     '_tcsupr'
            tcs['strxfrm']    =     '_tcsxfrm'      ;*
            tcs['tolower']    =     '_totlower'
            tcs['toupper']    =     '_totupper'
            tcs['vfprintf']   =     '_vftprintf'    ;*
            tcs['vprintf']    =     '_vtprintf'     ;*
            tcs['vsprintf']   =     '_vstprintf'    ;*

            u = u + 1; usr[u] = token(, *('*lpFunc'),  *lpFunc,  *(mrk tcs[func] params))

                                                                                             :(RETURN)
UserDefsEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserFinal()cArr,cCount,cKey,cTotal,i')                                   :(UserFinalEnd)
UserFinal   cArr              =     DIFFER(c) SORT(c, 1)                                     :f(RETURN)
            i                 =     0
UserFinal3  i                 =     i + 1
            cKey              =     cArr[i, 1]                                               :f(UserFinal5)
            cCount            =     cArr[i, 2]
            cTotal            =     cTotal + cCount
            OUTPUT            =     LPAD(cCount, 4) ' ' cKey                                 :(UserFinal3)
UserFinal5  OUTPUT            =     'Total: ' cTotal
            OUTPUT            =                                                              :(RETURN)
UserFinalEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserRpt()cArr,dlm,i,sspathnm,src')                                       :(UserRptEnd)
UserRpt     DIFFER(stuff)                                                                    :(RETURN)
            pathnm            'alxtchar.h'                                                   :s(RETURN)
            pathnm            'sbisys.h'                                                     :s(RETURN)
            sspathnm          =     pathnm
            sspathnm          POS(0) '//flash/e/dev/oracle/' = '$/dev/'
            ss_checkout('-maxm', sspathnm, '-gf -i-y')
*           ss_get('@-maxm', sspathnm,, '-gf -i-y')
            system('@-chmod', 'a+rw "' pathnm '"')
            src               =     Read(pathnm)                                             :f(error)
UserRpt10   i                 =     LT(i, u) i + 1                                           :f(UserRpt30)
UserRpt20   src               patr(usr[i]) = EVAL(repl(usr[i]))                              :s(UserRpt20)f(UserRpt10)
UserRpt30   Write(pathnm, src)                                                               :(RETURN)
UserRptEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserTokens()')                                                           :(UserTokensEnd)
UserTokens  tok[t = t + 1] = token(,, .cRecognizer)
*           tok[t = t + 1] = token(, *(Qize(tx)), *cInteresting . tx)
            tok[t = t + 1] = token(, *(spcpfx '*floatingLiteral'),  *floatingLiteral)
            tok[t = t + 1] = token(, *(spcpfx tx), *integerLiteral . tx)
            tok[t = t + 1] = token(, *(spcpfx tx), *characterLiteral . tx)
            tok[t = t + 1] = token(, *(spcpfx tx), *stringLiteral . tx)
            tok[t = t + 1] = token(, *(tx), *keyword)
            tok[t = t + 1] = token(, *("'" tx "'"), *identifier . tx)
            tok[t = t + 1] = token(, *("$'" tx "'"), *operator . tx)
            tok[t = t + 1] = token(, *("$'" tx "'"), *special . tx)

            dbg[.cBlock] = TRUE
            dbg[.cExpr]  = TRUE

                                                                                             :(RETURN)
UserTokensEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
