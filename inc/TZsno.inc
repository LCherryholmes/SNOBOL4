*-------------------------------------------------------------------------------------------------------------------------
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserDefs()')                                                             :(UserDefsEnd)
UserDefs    u                 =     0
            usr               =     ARRAY('1:32')
            doDebug           =     0
            doDebugAfter1st   =     FALSE
            doInclWhite       =     FALSE
            doInclNL          =     FALSE
            doReportFileName  =     FALSE
            doRemember        =     TRUE
            doDebug           =     0
            fndExt            =     ('SNO' | 'sno' | 'INC' | 'inc') . extc
            fndCmd            =     'd:/mksnt/find d:/bom ( -name "*.sno" -o -name "*.inc" ) -print'
            fndSpecific       =
            fndExclude        =     'snobol4/PHRASES.INC'
            keyint            =     ('?') . tx
            keyword           =     '???' . tx
            space             =     SPAN(' ')
            whitespace        =     SPAN(' ')

            snoInteger        =     SPAN(digits)
            snoDQ             =     '"' BREAK('"' nl) '"'
            snoSQ             =     "'" BREAK("'" nl) "'"
            snoString         =     *snoSQ | *snoDQ
            snoReal           =     (  SPAN(digits) ('.' FENCE(SPAN(digits) | epsilon) | epsilon)
+                                      ('E' | 'e') ('+' | '-' | epsilon) SPAN(digits)
+                                   |  SPAN(digits) '.' FENCE(SPAN(digits) | epsilon)
+                                   )
            snoId             =     ANY(&UCASE &LCASE) FENCE(SPAN('.' digits &UCASE '_' &LCASE) | epsilon)
            snoFunction       =     SPAN('.' digits &UCASE '_' &LCASE) $ tx $ *match(snoFunctions,      snoTxInList)
            snoBuiltinVar     =     SPAN('.' digits &UCASE '_' &LCASE) $ tx $ *match(snoBuiltinVars,    snoTxInList)
            snoProtKeyword    =     '&' SPAN(&UCASE &LCASE)            $ tx $ *match(snoProtKeywords,   snoTxInList)
            snoUnprotKeyword  =     '&' SPAN(&UCASE &LCASE)            $ tx $ *match(snoUnprotKeywords, snoTxInList)

            snoGray           =     *snoWhite | epsilon
            snoWhite          =     (  SPAN(' ' tab) FENCE(nl ('+' | '.') FENCE(SPAN(' ' tab) | epsilon) | epsilon)
+                                   |  nl ('+' | '.') FENCE(SPAN(' ' tab) | epsilon)
+                                   )

            snoABORT          =     'ABORT'        ;*
            snoARB            =     'ARB'          ;*
            snoBAL            =     'BAL'          ;*
            snoFAIL           =     'FAIL'         ;*
            snoFENCE          =     'FENCE'        ;*
            snoINPUT          =     'INPUT'        ;*
            snoOUTPUT         =     'OUTPUT'       ;*
            snoREM            =     'REM'          ;*
            snoTERMINAL       =     'TERMINAL'     ;*

            sno_ABORT         =     '&ABORT'       ;* The primitive pattern ABORT.
            sno_ALPHABET      =     '&ALPHABET'    ;* String of 256 ASCII characters in ascending order.
            sno_ARB           =     '&ARB'         ;* The primitive pattern ARB.
            sno_BAL           =     '&BAL'         ;* The primitive pattern BAL.
            sno_FAIL          =     '&FAIL'        ;* The primitive pattern FAIL.
            sno_FENCE         =     '&FENCE'       ;* The primitive pattern FENCE.
            sno_FILE          =     '&FILE'        ;* Source file name of the current statement being executed.
            sno_FNCLEVEL      =     '&FNCLEVEL'    ;* Integer depth of program-defined function calls.
            sno_LASTFILE      =     '&LASTFILE'    ;* Source file name of the previous statement executed.
            sno_LASTLINE      =     '&LASTLINE'    ;* Integer source file line number of the previous statement executed.
            sno_LASTNO        =     '&LASTNO'      ;* Integer statement number of the previous statement executed.
            sno_LCASE         =     '&LCASE'       ;* String of 26 lower-case alphabetic characters in ascending order.
            sno_LINE          =     '&LINE'        ;* Integer source file line number of the current statement being executed.
            sno_REM           =     '&REM'         ;* The primitive pattern REM.
            sno_RTNTYPE       =     '&RTNTYPE'     ;* String describing the type of return most recently made by a program-defined function.
            sno_STCOUNT       =     '&STCOUNT'     ;* Integer count of the number of statements executed.
            sno_STNO          =     '&STNO'        ;* Integer statement number of the current statement being executed.
            sno_SUCCEED       =     '&SUCCEED'     ;* The primitive pattern SUCCEED.
            sno_UCASE         =     '&UCASE'       ;* String of 26 upper-case alphabetic characters in ascending order.

            sno_ABEND         =     '&ABEND'       ;* Abnormal ending. Deprecated feature.
            sno_ANCHOR        =     '&ANCHOR'      ;* Initially 0, unanchored. Set to Non-zero for anchored pattern matching.
            sno_CASE          =     '&CASE'        ;* Initially 1, case folding during compilation with CODE() and EVAL(). 0, prevent case folding.
            sno_CODE          =     '&CODE'        ;* Integer code in the range 0 and 255 returned to the OS.
            sno_COMPARE       =     '&COMPARE'     ;* Set collating sequence for lexical comparisons. Deprecated feature.
            sno_DUMP          =     '&DUMP'        ;* Initially 0, no dump. 1, partial dump. 2 or 3, full dump.
            sno_ERRLIMIT      =     '&ERRLIMIT'    ;* Initially 0. Decrementing counter. While positive avoids execution errors. See also, SETEXIT().
            sno_ERRTEXT       =     '&ERRTEXT'     ;* String error message text of the last execution error.
            sno_ERRTYPE       =     '&ERRTYPE'     ;* Integer error code of the last execution error.
            sno_FTRACE        =     '&FTRACE'      ;* Initially 0. Function trace decrementing counter. When non-zero each call and return of a program-defined function will be listed.
            sno_INPUT         =     '&INPUT'       ;* Initially 1, normal input. Set to 0 to temporarily ignore all input associations of variables.
            sno_MAXLNGTH      =     '&MAXLNGTH'    ;* Integer size of the largest object or string permitted.
            sno_OUTPUT        =     '&OUTPUT'      ;* Initially 1, normal output. Set to 0 to temporarily ignore all output associations of variables.
            sno_PROFILE       =     '&PROFILE'     ;* Initially 0, disable statement profiling.
            sno_STLIMIT       =     '&STLIMIT'     ;* Initially 2147483647. The maximum number of statements permitted to be executed. Set to -1 for unlimited but this also disables debugging.
            sno_TRACE         =     '&TRACE'       ;* Initially 0. Decrementing counter. While positive tracing is permitted with TRACE().
            sno_TRIM          =     '&TRIM'        ;* Initially 0, disable trim. non-zero to strip trailing blanks from lines read from files.
            sno_FULLSCAN      =     '&FULLSCAN'    ;* Not present in SPITBOL. SNOBOL4, allows disabling of heuristics during pattern matching.

            snoANY            =     'ANY'          ;* Match one character from a set.
            snoAPPLY          =     'APPLY'        ;* Indirect call to a fuction.
            snoARBNO          =     'ARBNO'        ;* Match repeated pattern zero or more times.
            snoARG            =     'ARG'          ;* Get dummy argument name from function definition.
            snoARRAY          =     'ARRAY'        ;* Create an array.
            snoATAN           =     'ATAN'         ;* Arctangent.
            snoBACKSPACE      =     'BACKSPACE'    ;* Backspace file one record.
            snoBREAK          =     'BREAK'        ;* Match charcters not in set.
            snoBREAKX         =     'BREAKX'       ;* Extended BREAK().
            snoCHAR           =     'CHAR'         ;* Convert charcter code to string.
            snoCHOP           =     'CHOP'         ;* Discard fractional portion of real.
            snoCLEAR          =     'CLEAR'        ;* Clear variables.
            snoCODE           =     'CODE'         ;* Compile a string.
            snoCOLLECT        =     'COLLECT'      ;* Regenerate storage.
            snoCONVERT        =     'CONVERT'      ;* Convert to specified data type.
            snoCOPY           =     'COPY'         ;* Make copy of argument.
            snoCOS            =     'COS'          ;* Cosine of an angle.
            snoDATA           =     'DATA'         ;* Create new data type.
            snoDATATYPE       =     'DATATYPE'     ;* Get data type of argument.
            snoDATE           =     'DATE'         ;* Get current date and time.
            snoDEFINE         =     'DEFINE'       ;* Create program-defined function.
            snoDETACH         =     'DETACH'       ;* Remove I/O association.
            snoDIFFER         =     'DIFFER'       ;* Check if arguments are different.
            snoDUMP           =     'DUMP'         ;* Dump variables.
            snoDUPL           =     'DUPL'         ;* Duplicate string or pattern.
            snoEJECT          =     'EJECT'        ;* Eject to a new page.
            snoENDFILE        =     'ENDFILE'      ;* Close a file or pipe.
            snoEQ             =     'EQ'           ;* Equality test for numbers.
            snoEVAL           =     'EVAL'         ;* Compile and evaluate expression.
            snoEXIT           =     'EXIT'         ;* Exit to another application or create executable program file.
            snoEXP            =     'EXP'          ;* Compute e^n.
            snoFENCE          =     'FENCE'        ;* Generate fenced pattern.
            snoFIELD          =     'FIELD'        ;* Get field name of defined data type.
            snoGE             =     'GE'           ;* Greater than or equal test for numbers.
            snoGT             =     'GT'           ;* Greater than test for numbers.
            snoHOST           =     'HOST'         ;* Obtain host computer information and command line arguments.
            snoIDENT          =     'IDENT'        ;* Check if arguments are identical.
            snoINPUT          =     'INPUT'        ;* Open file or pipe for input.
            snoINTEGER        =     'INTEGER'      ;* Check if argument is an integer.
            snoITEM           =     'ITEM'         ;* Get array or table element.
            snoLE             =     'LE'           ;* Less than or equal test for numbers.
            snoLEN            =     'LEN'          ;* Matches fixed-length string.
            snoLEQ            =     'LEQ'          ;* Lexical equality test for strings.
            snoLGE            =     'LGE'          ;* Lexical greater than or equal test for strings.
            snoLGT            =     'LGT'          ;* Lexical greater than test for strings.
            snoLLE            =     'LLE'          ;* Lexical less than or equal test for strings.
            snoLLT            =     'LLT'          ;* Lexical less than test for strings.
            snoLN             =     'LN'           ;* Natural logarithm
            snoLNE            =     'LNE'          ;* Lexical not equal test for strings.
            snoLOAD           =     'LOAD'         ;* Load external function.
            snoLOCAL          =     'LOCAL'        ;* Get local variable name from function definition.
            snoLPAD           =     'LPAD'         ;* Pad left end of string.
            snoLT             =     'LT'           ;* Less than test for numbers.
            snoNE             =     'NE'           ;* Not equal test for numbers.
            snoNOTANY         =     'NOTANY'       ;* Match one character not in set.
            snoOPSYN          =     'OPSYN'        ;* Create operator synonym.
            snoOUTPUT         =     'OUTPUT'       ;* Open file or pipe for output.
            snoPOS            =     'POS'          ;* Verify scanner position.
            snoPROTOTYPE      =     'PROTOTYPE'    ;* Get prototype which created an array.
            snoREMDR          =     'REMDR'        ;* Get remainder after division.
            snoREPLACE        =     'REPLACE'      ;* Replace characters in string.
            snoREVERSE        =     'REVERSE'      ;* Swap string end-for-end.
            snoREWIND         =     'REWIND'       ;* Rewind file.
            snoRPAD           =     'RPAD'         ;* Pad right end of string.
            snoRPOS           =     'RPOS'         ;* Verify scanner position from end.
            snoRSORT          =     'RSORT'        ;* Sort array or table in descending order.
            snoRTAB           =     'RTAB'         ;* Match through position counting from end.
            snoSET            =     'SET'          ;* Set file position.
            snoSETEXIT        =     'SETEXIT'      ;* Set error exit.
            snoSIN            =     'SIN'          ;* Sine of an angle.
            snoSIZE           =     'SIZE'         ;* Get length of string.
            snoSORT           =     'SORT'         ;* Sort array or table in ascending order.
            snoSPAN           =     'SPAN'         ;* Match characters in set.
            snoSQRT           =     'SQRT'         ;* Square root of a number.
            snoSTOPTR         =     'STOPTR'       ;* Stop trace.
            snoSUBSTR         =     'SUBSTR'       ;* Extracat substring.
            snoTAB            =     'TAB'          ;* Match through fixed position.
            snoTABLE          =     'TABLE'        ;* Create a table.
            snoTAN            =     'TAN'          ;* Tangent of an angle.
            snoTIME           =     'TIME'         ;* Get execution time.
            snoTRACE          =     'TRACE'        ;* Trace an entity.
            snoTRIM           =     'TRIM'         ;* Remove trailing blanks and tabs.
            snoUNLOAD         =     'UNLOAD'       ;* Remove function definition.

            snoTxInList       =     (POS(0) | ' ') *upr(tx) (' ' | RPOS(0))
            snoSpecialNames   =     'ABORT CONTINUE END FRETURN NRETURN RETURN SCONTINUE'
            snoBuiltinVars    =     'ABORT ARB BAL FAIL FENCE INPUT OUTPUT REM TERMINAL'
            snoProtKeywords   =     'ABORT ALPHABET ARB BAL FAIL FENCE FILE FNCLEVEL '
+                                   'LASTFILE LASTLINE LASTNO LCASE LINE REM RTNTYPE '
+                                   'STCOUNT STNO SUCCEED UCASE'
            snoUnprotKeywords =     'ABEND ANCHOR CASE CODE COMPARE DUMP ERRLIMIT '
+                                   'ERRTEXT ERRTYPE FTRACE INPUT MAXLNGTH OUTPUT '
+                                   'PROFILE STLIMIT TRACE TRIM FULLSCAN'
            snoFunctions      =     'ANY APPLY ARBNO ARG ARRAY ATAN BACKSPACE BREAK BREAKX '
+                                   'CHAR CHOP CLEAR CODE COLLECT CONVERT COPY COS DATA '
+                                   'DATATYPE DATE DEFINE DETACH DIFFER DUMP DUPL EJECT '
+                                   'ENDFILE EQ EVAL EXIT EXP FENCE FIELD GE GT HOST '
+                                   'IDENT INPUT INTEGER ITEM LE LEN LEQ LGE LGT LLE '
+                                   'LLT LN LNE LOAD LOCAL LPAD LT NE NOTANY OPSYN OUTPUT '
+                                   'POS PROTOTYPE REMDR REPLACE REVERSE REWIND RPAD RPOS '
+                                   'RSORT RTAB SET SETEXIT SIN SIZE SORT SPAN SQRT STOPTR '
+                                   'SUBSTR TAB TABLE TAN TIME TRACE TRIM UNLOAD'

            $'='              =     *snoWhite '=' *snoWhite
            $'?'              =     *snoWhite '?' *snoWhite
            $'|'              =     *snoWhite '|' *snoWhite
            $'+'              =     *snoWhite '+' *snoWhite
            $'-'              =     *snoWhite '-' *snoWhite
            $'/'              =     *snoWhite '/' *snoWhite
            $'*'              =     *snoWhite '*' *snoWhite
            $'^'              =     *snoWhite '^' *snoWhite
            $'!'              =     *snoWhite '!' *snoWhite
            $'**'             =     *snoWhite '**' *snoWhite
            $'$'              =     *snoWhite '$' *snoWhite
            $'.'              =     *snoWhite '.' *snoWhite
            $'&'              =     *snoWhite '&' *snoWhite
            $'@'              =     *snoWhite '@' *snoWhite
            $'#'              =     *snoWhite '#' *snoWhite
            $'%'              =     *snoWhite '%' *snoWhite
            $'~'              =     *snoWhite '~' *snoWhite
            $','              =     *snoGray ',' *snoGray
            $'('              =     '(' *snoGray
            $'['              =     '[' *snoGray
            $'<'              =     '<' *snoGray
            $')'              =     *snoGray ')'
            $']'              =     *snoGray ']'
            $'>'              =     *snoGray '>'

            snoExprList       =     (*snoExpr | epsilon) FENCE($',' *snoExprList | epsilon)
            snoExpr           =     *snoExpr0
            snoExpr0          =     *snoExpr1  FENCE($'=' *snoExpr0 | epsilon)
            snoExpr1          =     *snoExpr2  FENCE($'?' *snoExpr1 | epsilon)
            snoExpr2          =     *snoExpr3  FENCE($'&' *snoExpr2 | epsilon)
            snoExpr3          =     *snoExpr4  FENCE($'|' *snoExpr3 | epsilon)
            snoExpr4          =     *snoExpr5  FENCE(*snoWhite *snoExpr4 | epsilon)
            snoExpr5          =     *snoExpr6  FENCE($'@' *snoExpr5 | epsilon)
            snoExpr6          =     *snoExpr7  FENCE($'+' *snoExpr6 | $'-' *snoExpr6 | epsilon)
            snoExpr7          =     *snoExpr8  FENCE($'#' *snoExpr7 | epsilon)
            snoExpr8          =     *snoExpr9  FENCE($'/' *snoExpr8 | epsilon)
            snoExpr9          =     *snoExpr10 FENCE($'*' *snoExpr9 | epsilon)
            snoExpr10         =     *snoExpr11 FENCE($'%' *snoExpr10 | epsilon)
            snoExpr11         =     *snoExpr12 FENCE(($'^' | $'!' | $'**') *snoExpr11 | epsilon)
            snoExpr12         =     *snoExpr13 FENCE($'$' *snoExpr12 | $'.' *snoExpr12 | epsilon)
            snoExpr13         =     *snoExpr14 FENCE($'~' *snoExpr13 | epsilon)
            snoExpr14         =     '@' *snoExpr14
+                             |     '~' *snoExpr14
+                             |     '?' *snoExpr14
+                             |     '&' *snoExpr14
+                             |     '+' *snoExpr14
+                             |     '-' *snoExpr14
+                             |     '*' *snoExpr14
+                             |     '$' *snoExpr14
+                             |     '.' *snoExpr14
+                             |     '!' *snoExpr14
+                             |     '%' *snoExpr14
+                             |     '/' *snoExpr14
+                             |     '#' *snoExpr14
+                             |     '=' *snoExpr14
+                             |     '|' *snoExpr14
+                             |     *snoExpr15
            snoExpr15         =     *snoExpr17 FENCE(*snoExpr16 | epsilon)
            snoExpr16         =     ($'[' *snoExprList $']' | $'<' *snoExprList $'>') FENCE(*snoExpr16 | epsilon)
            snoExpr17         =     FENCE(
+                                      $'(' *snoExpr ($',' *snoExprList | epsilon) $')'
+                                   |  *snoFunction $'(' *snoExprList $')'
+                                   |  *snoId $'(' *snoExprList $')'
+                                   |  *snoBuiltinVar
+                                   |  *snoId
+                                   |  *snoProtKeyword
+                                   |  *snoUnprotKeyword
+                                   |  *snoString
+                                   |  *snoReal
+                                   |  *snoInteger
+                                   )

            snoSorF           =     ('S' | 'F' | 's' | 'f')
            snoTarget         =     $'(' *snoExpr $')'
+                             |     $'<' *snoExpr $'>'
            snoGoto           =     *snoWhite ':' *snoGray
+                                   FENCE(
+                                      *snoTarget
+                                   |  *snoSorF *snoTarget
+                                      FENCE(
+                                         *snoGray *snoSorF *snoTarget
+                                      |  epsilon
+                                      )
+                                   )
            snoControl        =     '-' BREAK(nl ';')
            snoComment        =     '*' BREAK(nl)
            snoLabel          =     BREAK(' ' tab nl ';')
            snoStmt           =     *snoLabel
+                                   (  *snoWhite *snoExpr14
+                                      FENCE(
+                                         ($'=' *snoExpr | *snoWhite '=')
+                                      |  *snoWhite *snoExpr1
+                                         FENCE(
+                                            ($'=' *snoExpr | *snoWhite '=')
+                                         |  epsilon
+                                         )
+                                      |  epsilon
+                                      )
+                                   |  epsilon
+                                   )
+                                   FENCE(*snoGoto | epsilon)
+                                   *snoGray

            snoCommands       =     *snoCommand FENCE(*snoCommands | epsilon)
            snoCommand        =     FENCE(
+                                      *snoComment nl
+                                   |  *snoControl (nl | ';')
+                                   |  *snoStmt    (nl | ';')
+                                   )

            snoParse          =     ARBNO(*snoCommand)
+                                   (  icase('END') (' ' BREAK(nl) nl | nl) ARBNO(BREAK(nl) nl)
+                                   |  epsilon
+                                   )
+                                   RPOS(0)
                                                                                             :(RETURN)
UserDefsEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserRpt()')                                                              :(UserRptEnd)
UserRpt     DIFFER(sno)                                                                      :f(RETURN)
            XDump('sno', sno)                                                                :(RETURN)
UserRptEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserTokens()')                                                           :(UserTokensEnd)
UserTokens  tok[t = t + 1] = token(,, .snoParse)
            tok[t = t + 1] = token(,, .snoCommands)
            tok[t = t + 1] = token(,, .snoCommand)
            tok[t = t + 1] = token(,, .snoControl)
            tok[t = t + 1] = token(,, .snoComment)
            tok[t = t + 1] = token(,, .snoStmt)
            tok[t = t + 1] = token(,, .snoGoto)
            tok[t = t + 1] = token(,, .snoTarget)
            tok[t = t + 1] = token(,, .snoExpr)
            tok[t = t + 1] = token(,, .snoExpr0)
            tok[t = t + 1] = token(,, .snoExpr1)
            tok[t = t + 1] = token(,, .snoExpr2)
            tok[t = t + 1] = token(,, .snoExpr3)
            tok[t = t + 1] = token(,, .snoExpr4)
            tok[t = t + 1] = token(,, .snoExpr5)
            tok[t = t + 1] = token(,, .snoExpr6)
            tok[t = t + 1] = token(,, .snoExpr7)
            tok[t = t + 1] = token(,, .snoExpr8)
            tok[t = t + 1] = token(,, .snoExpr9)
            tok[t = t + 1] = token(,, .snoExpr10)
            tok[t = t + 1] = token(,, .snoExpr11)
            tok[t = t + 1] = token(,, .snoExpr12)
            tok[t = t + 1] = token(,, .snoExpr13)
            tok[t = t + 1] = token(,, .snoExpr14)
            tok[t = t + 1] = token(,, .snoExpr15)
            tok[t = t + 1] = token(,, .snoExpr16)
            tok[t = t + 1] = token(,, .snoExpr17)
            tok[t = t + 1] = token(, *("'" upr(tx) "'"), *snoFunction)
            tok[t = t + 1] = token(, *("'&" upr(tx) "'"), *snoProtKeyword)
            tok[t = t + 1] = token(, *("'&" upr(tx) "'"), *snoUnprotKeyword)
            tok[t = t + 1] = token(, *("'" upr(tx) "'"), *snoBuiltinVar)
            tok[t = t + 1] = token(,, .snoId)
            tok[t = t + 1] = token(,, .snoReal)
            tok[t = t + 1] = token(,, .snoInteger)
            tok[t = t + 1] = token(,, .snoDQ)
            tok[t = t + 1] = token(,, .snoSQ)
            tok[t = t + 1] = token(,, .snoString)
            tok[t = t + 1] = token(,, .snoWhite)
            tok[t = t + 1] = token(, *("tab"), tab)
            tok[t = t + 1] = token(, *("nl"), nl)
                                                                                             :(RETURN)
UserTokensEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
