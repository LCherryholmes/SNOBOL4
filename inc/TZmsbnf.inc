*-------------------------------------------------------------------------------------------------------------------------
-INCLUDE    'transl8pp.inc'
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserDefs()')                                                             :(UserDefsEnd)
UserDefs    u                 =     0
            usr               =     ARRAY('1:32')
            doDebug           =     0
            doDebugAfter1st   =     FALSE
            doInclWhite       =     TRUE
            doInclNL          =     FALSE
            doReportFileName  =     FALSE
            doRemember        =     TRUE
            fndExt            =     'msbnf' . extc
            fndCmd            =     'C:/mksnt/find C:/Docume~1/lcherryh/MyDocu~1 -name "*.msbnf" -print'
            fndSpecific       =     'C:/Docume~1/lcherryh/MyDocu~1/IMCEDA/MSSQL/MSSQL_msdn.msbnf'
            fndExclude        =
            spcpfx            =
            spcpfx            =     EQ(doInclWhite, TRUE) "$' ' "
            keyint            =     ('?') . tx

            blanks            =     SPAN(' ' tab cr ff)
            white             =     SPAN(' ' tab cr ff nl)
            cStyleComment     =     '/*' BREAKX('*') '*/'
            cppStyleComment   =     '//' BREAK(nl) nl
            sqlStyleComment   =     '--' BREAK(nl) nl
            space             =     (blanks | cStyleComment | cppStyleComment | sqlStyleComment)
+                                   FENCE(*space | epsilon)
            whitespace        =     (white | cStyleComment | cppStyleComment | sqlStyleComment)
+                                   FENCE(*whitespace | epsilon)
            $' '              =     FENCE(whitespace | epsilon)
            $'  '             =     FENCE(space | epsilon)
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            keywords          =
            reswords          =     'DQ_STRING IDENT INTEGER REAL SQ_STRING'
            operators         =     '} | { ] [ ::= ,...n +...n ...n ;'
            ident             =     ANY(&UCASE '_' &LCASE) FENCE(SPAN('0123456789' &UCASE '_' &LCASE) | epsilon)
            identifier        =     ident $ tx $ *notmatch(reswords, (POS(0) | ' ') upr(tx) (' ' | RPOS(0)))
            resword           =     ident $ tx $ *match(reswords, (POS(0) | ' ') upr(tx) (' ' | RPOS(0)))
            keyword           =     ident $ tx $ *match(keywords, (POS(0) | ' ') upr(tx) (' ' | RPOS(0)))
            Populate(.TW, ident, keywords, reswords,, operators)
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            MATCH             =     $' ' "'" ARBNO(bSlash (bSlash | ANY("n'")) | BREAK("'" bSlash)) "'"
            STICK             =     $' ' '"' ARBNO(bSlash (bSlash | ANY('n"')) | BREAK('"' bSlash)) '"'
            CHARS             =     $' ' (SPAN('~`!@#$%^&*()-+=:<>,.?/') | bSlash ANY('{}|[];' '"' "'"))
            integer           =     $' ' SPAN('0123456789')
            STRING            =     $' ' '"' ARBNO(bSlash (bSlash | ANY('n"')) | BREAK('"' bSlash)) '"'
            SYMBOL            =     $' ' *identifier
            NONTERM           =     $' ' '<' BREAK('>' nl) '>'

            ebnf              =     nPush() *productions ('productions' & 'nTop()') nPop()
            productions       =     *production nInc() (*productions | epsilon)
            production        =     *defines *alternates $';' ('bnf_production' & 2)

            alternates        =     nPush() *alternates_1 ('|' & '*(GT(nTop(), 1) nTop())') nPop()
            alternates_1      =     *subsequents nInc() ($'|' *alternates_1 | epsilon)

            subsequents       =     nPush() *subsequents_1 ('&' & '*(GT(nTop(), 1) nTop())') nPop()
            subsequents_1     =     *repetition nInc() (*subsequents_1 | epsilon)

            repetition        =     *element
+                                   (  (  $'[' $'...n' $']' ('+' & 1)
+                                      |  $'[' $',...n' $']' (',' & 1)
+                                      )
+                                   |  epsilon
+                                   )
+                             |     (*defines | epsilon) *optional

            optional          =     $'[' *alternates $']'
+                                   (  $'[' $'...n' $']' ('*' & 1)
+                                   |  $'[' $',...n' $']' (',' & 1) ('?' & 1)
+                                   |  epsilon ('?' & 1)
+                                   )

            defines           =     (*SYMBOL | *NONTERM) ~ 'identifier' $'::='

            element           =     *SYMBOL        ~ 'identifier'
+                             |     *NONTERM       ~ 'identifier'
+                             |     *MATCH         ~ 'string'
+                             |     *STICK         ~ 'string'
+                             |     IDENT          ~ 'identifier'
+                             |     $' ' ('@' *SYMBOL)  ~ 'identifier'
+                             |     $' ' ('@@' *SYMBOL) ~ 'identifier'
+                             |     INTEGER        ~ 'identifier'
+                             |     REAL           ~ 'identifier'
+                             |     DQ_STRING      ~ 'identifier'
+                             |     SQ_STRING      ~ 'identifier'
+                             |     *CHARS         ~ 'string'
+                             |     $'{' *alternates $'}'

                                                                                             :(RETURN)
UserDefsEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('Visit(x,fnc)i')                                                          :(VisitEnd)
Visit       APPLY(fnc, x)                                                                    :F(RETURN)
            i                 =     0
Visit_1     i                 =     LT(i, n(x)) i + 1                                        :F(RETURN)
            Visit(c(x)[i], fnc)                                                              :(Visit_1)
VisitEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('Xform(x)n,v')                                                            :(XformEnd)
Xform       DIFFER(x)                                                                        :F(RETURN)
Xform_2     IDENT(t(x), 'identifier')                                                        :F(RETURN)
            v                 =     v(x)
Xform_5     v                 POS(0) ('@@' | '@' | '') SPAN('0123456789' &UCASE '_') RPOS(0) :F(Xform_7)
            v(x)              =     "'" v(x) "'"
            t(x)              =     'string'                                                 :(RETURN)
Xform_7     v                 POS(0) '<' BREAK('>') . v '>'                                  :F(FRETURN)
            v(x)              =     v                                                        :(RETURN)
XformEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserRpt()')                                                              :(UserRptEnd)
UserRpt     bnf               =     Pop()                                                    :F(RETURN)
            DIFFER(bnf)                                                                      :F(RETURN)
            Visit(bnf, .Xform)

            basenm            =     splitname(pathnm)[2]
            basenm            '.' fndExt RPOS(0) =

            lispnm            =     basenm '.lisp'
            OUTPUT(.OUTPUT, 2, lispnm)                                                       :F(xerr)
            SetLevel(0)
            TDump(bnf)
            ENDFILE(2)

            incnm             =     'transl8-' basenm '.inc'
            OUTPUT(.OUTPUT, 2, incnm)                                                        :F(xerr)
            ppOps             =     TRUE
            pp(bnf)
            ENDFILE(2)

            ebnfnm             =     'transl8-' basenm '.ebnf'
            OUTPUT(.OUTPUT, 2, ebnfnm)                                                       :F(xerr)
            ppSetStyle('ebnf')
            ppOps             =     FALSE
            GenSetCont()
            SetLevel(0)
            pp(bnf)
            ENDFILE(2)
                                                                                             :(RETURN)
UserRptEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserFinal()')                                                            :(UserFinalEnd)
UserFinal                                                                                    :(RETURN)
UserFinalEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserTokens()')                                                           :(UserTokensEnd)
UserTokens  tok[t = t + 1] = token(,, .ebnf)
            tok[t = t + 1] = token(, *(spcpfx '*MATCH'), *MATCH)
            tok[t = t + 1] = token(, *(spcpfx '*integer'), *integer)
            tok[t = t + 1] = token(, *(spcpfx '*STRING'), *STRING)
            tok[t = t + 1] = token(, *(tx), *resword . tx)
            tok[t = t + 1] = token(, *(tx), *keyword . tx)
            tok[t = t + 1] = token(, *(spcpfx '*SYMBOL'), *SYMBOL)
            tok[t = t + 1] = token(, *(spcpfx '*NONTERM'), *NONTERM)
            tok[t = t + 1] = token(, *("$'" tx "'"), *operator . tx)

            dbg[.MATCH] = TRUE
            dbg[.CHARS] = TRUE
            dbg[.integer] = TRUE
            dbg[.STRING] = TRUE
            dbg[.SYMBOL] = TRUE
            dbg[.operator] = TRUE
            dbg[.productions] = TRUE
            dbg[.production] = TRUE
            dbg[.alternates] = TRUE
            dbg[.subsequents] = TRUE
            dbg[.subsequents_1] = TRUE
            dbg[.repetition] = TRUE
            dbg[.optional] = TRUE
            dbg[.defines] = TRUE
            dbg[.element] = TRUE

                                                                                             :(RETURN)
UserTokensEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
