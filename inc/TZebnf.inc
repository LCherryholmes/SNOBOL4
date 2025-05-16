*-------------------------------------------------------------------------------------------------------------------------
-INCLUDE    'transl8pp.inc'

            u                 =     0
            usr               =     ARRAY('1:32')
            doDebug           =     0
            doDebugAfter1st   =     FALSE
            doInclWhite       =     TRUE
            doInclNL          =     FALSE
            doReportFileName  =     FALSE
            doRemember        =     TRUE
            doParseTree       =     FALSE
            fndExt            =     'ebnf' . extc
            fndCmd            =     'C:/mksnt/find C:/ -name "*.ebnf" -print'
            fndSpecific       =     'C:/IMCEDA/MSSQL/MSSQL_msdn.ebnf'
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
            operators         =     '} | { ] [ ? ; ::= ... ,,, ) ('
            ident             =     ANY(&UCASE '_' &LCASE) FENCE(SPAN('0123456789' &UCASE '_' &LCASE) | epsilon)
            identifier        =     ident $ tx $ *notmatch(reswords, (POS(0) | ' ') upr(tx) (' ' | RPOS(0)))
            resword           =     ident $ tx $ *match(reswords, (POS(0) | ' ') upr(tx) (' ' | RPOS(0)))
            keyword           =     ident $ tx $ *match(keywords, (POS(0) | ' ') upr(tx) (' ' | RPOS(0)))
            Populate(.TW, ident, keywords, reswords,, operators)
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            MATCH             =     $' ' "'" ARBNO(bSlash (bSlash | ANY("n'")) | BREAK("'" bSlash)) "'"
            MATCH_CASE        =     $' ' "`" ARBNO(bSlash (bSlash | ANY("n`")) | BREAK("`" bSlash)) "`"
            MATCH_NOSPACE     =     $' ' bSlash ARBNO(BREAK(bSlash) (bSlash bSlash | epsilon)) bSlash
            integer           =     $' ' SPAN('0123456789')
            STRING            =     $' ' '"' ARBNO(bSlash (bSlash | ANY('n"')) | BREAK('"' bSlash)) '"'
            SYMBOL            =     $' ' *identifier
            NONTERM           =     $' ' '<' BREAK('>' nl) '>'

            ebnf              =     nPush() *productions ('productions' & 'nTop()') nPop()
            productions       =     *production nInc() (*productions | epsilon)
            production        =     *name *alternates $';' ('bnf_production' & 2)

            alternates        =     nPush() *alternates_1 ('|' & '*(GT(nTop(), 1) nTop())') nPop()
            alternates_1      =     *subsequents nInc() ($'|' *alternates_1 | epsilon)

            subsequents       =     nPush() *subsequents_1 ('&' & '*(GT(nTop(), 1) nTop())') nPop()
            subsequents_1     =     *repetition nInc() (*subsequents_1 | epsilon)

            repetition        =     *element
+                                   (  (  $'...' ('+' & 1)
+                                      |  $',,,' (',' & 1)
+                                      )
+                                   |  epsilon
+                                   )
+                             |     (*name | epsilon) *optional

            optional          =     $'[' *alternates $']'
+                                   (  $'...' ('*' & 1)
+                                   |  $',,,' (',' & 1) ('?' & 1)
+                                   |  epsilon ('?' & 1)
+                                   )

            name              =     (*SYMBOL | *NONTERM) ~ 'identifier' ($'->' | $'::=')

            element           =     *SYMBOL        ~ 'identifier'
+                             |     $' ' ('@' *ident)  ~ 'identifier'
+                             |     $' ' ('@@' *ident) ~ 'identifier'
+                             |     *NONTERM       ~ 'identifier'
+                             |     *MATCH         ~ 'string'
+                             |     *MATCH_CASE    ~ 'string'
+                             |     *MATCH_NOSPACE ~ 'string'
+                             |     IDENT          ~ 'identifier'
+                             |     INTEGER        ~ 'identifier'
+                             |     REAL           ~ 'identifier'
+                             |     DQ_STRING      ~ 'identifier'
+                             |     SQ_STRING      ~ 'identifier'
+                             |     $'(' *alternates $')'

*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('Visit(x,fnc)i')                                                          :(VisitEnd)
Visit       APPLY(fnc, x)                                                                    :F(RETURN)
            i                 =     0
Visit_1     i                 =     LT(i, n(x)) i + 1                                        :F(RETURN)
            Visit(c(x)[i], fnc)                                                              :(Visit_1)
VisitEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('Norm(nm,x,place)p')                                                      :(NormEnd)
Norm        t(c(x)[place])    POS(0) ANY('|&?*+,') RPOS(0)                                   :F(RETURN)
            cnt               =     cnt + 1
            p                 =     tree('bnf_production',, 2, ARRAY('1:2'))
            c(p)[1]           =     tree('identifier', nm '$' cnt)
            c(p)[2]           =     c(x)[place]
            c(x)[place]       =     tree('identifier', nm '$' cnt)
            Insert(bnf, p, i + cnt)                                                          :(RETURN)
NormEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('PPure()i,name,n,np,p')                                                   :(PPureEnd)
PPure       i                 =     0
PPure1      i                 =     LT(i, n(bnf)) i + 1                                      :F(RETURN)
            DIFFER(c(bnf)[i])                                                                :F(error)
            IDENT(t(bnf), 'productions')                                                     :F(error)
            IDENT(t(c(bnf)[i]), 'bnf_production')                                            :F(error)
            IDENT(t(c(c(bnf)[i])[1]), 'identifier')                                          :F(error)
            np                =     c(c(bnf)[i])[2]
            name              =     v(c(c(bnf)[i])[1])
            t(np)             POS(0) '?' RPOS(0)                                             :S(PPureOpt0)
            t(np)             POS(0) ANY('*+,') RPOS(0)                                      :F(PPure1)
            sName             =     IDENT(t(c(np)[1]), 'identifier') v(c(np)[1])
            sName             =     DIFFER(t(c(np)[1]), 'identifier') name '$' 0
            p                 =     tree('bnf_production',, 2, ARRAY('1:2'))
            c(p)[1]           =     tree('identifier', sName)
            c(p)[2]           =     c(np)[1]
            IDENT(t(np), '*')                                                                :S(PPureStr)
            IDENT(t(np), '+')                                                                :S(PPurePls)
            IDENT(t(np), ',')                                                                :S(PPureLst)
PPureOpt0   n                 =     c(np)[1]
            DIFFER(t(n), '|')                                                                :F(PPureOpt1)
            p                 =     tree('|',, 1, ARRAY('1:1'))
            c(p)[1]           =     n
            n                 =     p
PPureOpt1   c(c(bnf)[i])[2]   =     Prepend(n, tree('epsilon'))                              :(PPure1)
PPureStr    n                 =     tree('|',, 2, ARRAY('1:2'))
            c(n)[1]           =     tree('epsilon')
            c(n)[2]           =     tree('&',, 2, ARRAY('1:2'))
            c(c(n)[2])[1]     =     tree('identifier', name)
            c(c(n)[2])[2]     =     tree('identifier', sName)                                :(PPure8)
PPurePls    n                 =     tree('|',, 2, ARRAY('1:2'))
            c(n)[1]           =     tree('identifier', sName)
            c(n)[2]           =     tree('&',, 2, ARRAY('1:2'))
            c(c(n)[2])[1]     =     tree('identifier', name)
            c(c(n)[2])[2]     =     tree('identifier', sName)                                :(PPure8)
PPureLst    n                 =     tree('|',, 2, ARRAY('1:2'))
            c(n)[1]           =     tree('identifier', sName)
            c(n)[2]           =     tree('&',, 3, ARRAY('1:3'))
            c(c(n)[2])[1]     =     tree('identifier', name)
            c(c(n)[2])[2]     =     tree('string', "','")
            c(c(n)[2])[3]     =     tree('identifier', sName)                                :(PPure8)
PPure8      DIFFER(t(c(np)[1]), 'identifier')                                                :F(PPure9)
            Insert(bnf, p, i + 1)
PPure9      c(c(bnf)[i])[2]   =     n                                                        :(PPure1)

PPureEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('PNorm()cnt,i,j,k,name,np')                                               :(PNormEnd)
PNorm       i                 =     0
PNorm01     i                 =     LT(i, n(bnf)) i + 1                                      :F(RETURN)
            cnt               =     0
            DIFFER(c(bnf)[i])                                                                :F(error)
            IDENT(t(bnf), 'productions')                                                     :F(error)
            IDENT(t(c(bnf)[i]), 'bnf_production')                                            :F(error)
            IDENT(t(c(c(bnf)[i])[1]), 'identifier')                                          :F(error)
            np                =     c(c(bnf)[i])[2]
            name              =     v(c(c(bnf)[i])[1])
            IDENT(t(np), '|')                                                                :S(PNormAlt00)
            IDENT(t(np), '&')                                                                :S(PNormSeq00)
            IDENT(t(np), '?')                                                                :S(PNormOth00)
            IDENT(t(np), '*')                                                                :S(PNormOth00)
            IDENT(t(np), '+')                                                                :S(PNormOth00)
            IDENT(t(np), ',')                                                                :S(PNormOth00)F(PNorm01)
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
PNormAlt00  j                 =     0
PNormAlt01  j                 =     LT(j, n(np)) j + 1                                       :F(PNorm01)
            IDENT(t(c(np)[j]), '&')                                                          :F(PNormAlt03)
            k                 =     0
PNormAlt02  k                 =     LT(k, n(c(np)[j])) k + 1                                 :F(PNormAlt01)
            Norm(name, c(np)[j], k)                                                          :(PNormAlt02)
PNormAlt03  Norm(name, np, j)                                                                :(PNormAlt01)
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
PNormSeq00  k                 =     0
PNormSeq01  k                 =     LT(k, n(np)) k + 1                                       :F(PNorm01)
            Norm(name, np, k)                                                                :(PNormSeq01)
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
PNormOth00  IDENT(t(c(np)[1]), '|')                                                          :F(PNormOth10)
            j                 =     0
PNormOth01  j                 =     LT(j, n(c(np)[1])) j + 1                                 :F(PNorm01)
            IDENT(t(c(c(np)[1])[j]), '&')                                                    :F(PNormOth03)
            k                 =     0
PNormOth02  k                 =     LT(k, n(c(c(np)[1])[j])) k + 1                           :F(PNormOth01)
            Norm(name, c(c(np)[1])[j], k)                                                    :(PNormOth02)
PNormOth03  Norm(name, c(np)[1], j)                                                          :(PNormOth01)
PNormOth10  IDENT(t(c(np)[1]), '&')                                                          :F(PNormOth20)
            k                 =     0
PNormOth11  k                 =     LT(k, n(c(np)[1])) k + 1                                 :F(PNorm01)
            Norm(name, c(np)[1], k)                                                          :(PNormOth11)
PNormOth20  Norm(name, np, k)                                                                :(PNorm01)
PNormEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
*           Detect:
*              Multiply defined productions
*              Unreferenced productions
*              Undefined references
*
            DEFINE('Xdef(x)prodNm')
            Tdefs             =     TABLE()
            Tdefs['at_at_identifier'] = 1
            Tdefs['at_identifier'] = 1
            Tdefs['identifier'] = 1
            Tdefs['binary_literal'] = 1
            Tdefs['integer_literal'] = 1
            Tdefs['money_literal'] = 1
            Tdefs['real_literal'] = 1
            Tdefs['string_literal'] = 1
            Tdefs['true']     = 1
            Tdefs['false']    = 1                                                            :(XdefEnd)
Xdef        DIFFER(x)                                                                        :F(RETURN)
Xdef10      IDENT(t(x), 'bnf_production')                                                    :F(RETURN)
            prodNm            =     v(c(x)[1])
            Tdefs[prodNm]     =     Tdefs[prodNm] + 1                                        :(RETURN)
XdefEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('Xref(x)idNm')
            Trefs             =     TABLE()
            Tundefs           =     TABLE()
            Tcaps             =     TABLE()                                                  :(XrefEnd)
Xref        DIFFER(x)                                                                        :F(RETURN)
            IDENT(t(x), 'bnf_production')                                                    :F(Xref10)
            Visit(c(x)[2], .Xref)                                                            :(FRETURN)
Xref10      IDENT(t(x), 'identifier')                                                        :F(Xref30)
            idNm              =     v(x)
            idNm              POS(0) SPAN(&UCASE '_' '0123456789') RPOS(0)                   :F(Xref20)
            Tcaps[idNm]       =     Tcaps[idNm] + 1                                          :(RETURN)
Xref20      idNm              POS(0) '@' =                                                   :F(Xref25)
            v(x)              =     idNm                                                     :(RETURN)
Xref25      Trefs[idNm]       =     Trefs[idNm] + 1
            IDENT(Tdefs[idNm])                                                               :F(RETURN)
            Tundefs[idNm]     =     Tundefs[idNm] + 1                                        :(RETURN)
Xref30      IDENT(t(x), 'string')                                                            :F(RETURN)
            v(x)              POS(0) SPAN('~`!@#$%^&*()-+={}[]|\":;?/<>,.' "'") RPOS(0)      :(RETURN)
            v(x)              POS(0) "'" RTAB(1) . v(x) "'"
            OUTPUT            =     v(x)                                                     :(RETURN)
XrefEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('Xinstr(x)c,t')                                                           :(XinstrEnd)
Xinstr      DIFFER(x)                                                                        :F(RETURN)
Xinstr10    IDENT(t(x), 'bnf_production')                                                    :F(Xinstr20)
            prodNm            =     v(c(x)[1])
            prodNm            POS(0) ('expression' | 'search_condition')                     :F(RETURN)
            subSeq            =     c(x)[2]
            IDENT(t(subSeq), '&')                                                            :F(RETURN)
            IDENT(t(c(subSeq)[2]), '*')                                                      :F(RETURN)
            c                 =     ARRAY('1:5')
            c[1]              =     tree('&nPush', 'nPush!')
            c[2]              =     c(subSeq)[1]
            c[3]              =     tree('*',, 1, ARRAY('1:1'))
            c(c[3])[1]        =     tree('&',, 2, ARRAY('1:2'))
            c(c(c[3])[1])[1]  =     c(c(subSeq)[2])[1]
            c(c(c[3])[1])[2]  =     tree('&nInc', 'nInc!')
            c[4]              =     tree('&reduce',, 2, ARRAY('1:2'))
            c(c[4])[1]        =     tree('string', "'~'")
            c(c[4])[2]        =     tree('string', "'*(GT(nTop(), 0) (2 * nTop() + 1))'")
            c[5]              =     tree('&nPop', 'nPop!')
            n(c(x)[2])        =     5
            c(c(x)[2])        =     c                                                        :(FRETURN)
Xinstr20    IDENT(t(x), '&')                                                                 :F(Xinstr30)
            c                 =     ARRAY('1:2')
            c[1]              =     tree('string', "'&'")
            c[2]              =     tree('string', n(x))
            Append(x, tree('&reduce',, 2, c))                                                :(RETURN)
Xinstr30    t(x)              POS(0) ANY('*+') . t RPOS(0)                                   :F(Xinstr40)
            c                 =     ARRAY('1:4')
            c[1]              =     tree('&nPush', 'nPush!')
            c[2]              =     tree(t,, 1, ARRAY('1:1'))
            c(c[2])[1]        =     tree('&',, 2, ARRAY('1:2'))
            c(c(c[2])[1])[1]  =     c(x)[1]
            c(c(c[2])[1])[2]  =     tree('&nInc', 'nInc!')
            c[3]              =     tree('&reduce',, 2, ARRAY('1:2'))
            c(c[3])[1]        =     tree('string', "'" t "'")
            c(c[3])[2]        =     tree('string', "'nTop()'")
            c[4]              =     tree('&nPop', 'nPop!')
            t(x)              =     '&'
            n(x)              =     4
            c(x)              =     c
            Visit(c(c(c[2])[1])[1], .Xinstr)                                                 :(FRETURN)
Xinstr40    t(x)              POS(0) ',' . t RPOS(0)                                         :F(RETURN)
            c                 =     ARRAY('1:4')
            c[1]              =     tree('&nPush', 'nPush!')
            c[2]              =     tree(',',, 2, ARRAY('1:2'))
            c(c[2])[1]        =     tree('&',, 2, ARRAY('1:2'))
            c(c(c[2])[1])[1]  =     c(x)[1]
            c(c(c[2])[1])[2]  =     tree('&nInc', 'nInc!')
            c(c[2])[2]        =     c(x)[2]
            c[3]              =     tree('&reduce',, 2, ARRAY('1:2'))
            c(c[3])[1]        =     tree('string', "'" t "'")
            c(c[3])[2]        =     tree('string', "'nTop()'")
            c[4]              =     tree('&nPop', 'nPop!')
            t(x)              =     '&'
            n(x)              =     4
            c(x)              =     c
            Visit(c(c(c[2])[1])[1], .Xinstr)                                                 :(FRETURN)
XinstrEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserRpt()')                                                              :(UserRptEnd)
UserRpt     bnf               =     Pop()                                                    :F(RETURN)
            DIFFER(bnf)                                                                      :F(RETURN)
            Visit(bnf, .Xdef)
            Visit(bnf, .Xref)
*           Visit(bnf, .Xinstr)
*----------
            Adefs             =     DIFFER(Tdefs) SORT(Tdefs)                                :F(UserRpt20)
            i                 =     0
UserRpt10   i                 =     i + 1
            prodNm            =     Adefs[i, 1]                                              :F(UserRpt20)
            prodCnt           =     Adefs[i, 2]
            refCnt            =     Trefs[prodNm]
            OUTPUT            =     GT(prodCnt, 1) 'Multiply defined: ' prodCnt ' ' prodNm
            OUTPUT            =     IDENT(refCnt) 'Unreferenced: ' prodNm                    :(UserRpt10)
*----------
UserRpt20   Aundefs           =     DIFFER(Tundefs) SORT(Tundefs)                            :F(UserRpt40)
            i                 =     0
UserRpt30   i                 =     i + 1
            prodNm            =     Aundefs[i, 1]                                            :F(UserRpt40)
            prodCnt           =     Aundefs[i, 2]
            OUTPUT            =     'Undefined reference: ' LPAD(prodCnt, 3) ' ' prodNm     :(UserRpt30)
*----------
UserRpt40   Acaps             =     DIFFER(Tcaps) SORT(Tcaps)                                :F(UserRpt60)
            i                 =     0
UserRpt50   i                 =     i + 1
            tokenNm           =     Acaps[i, 1]                                              :F(UserRpt60)
            tokenCnt          =     Acaps[i, 2]
            OUTPUT            =     LPAD(tokenCnt, 3) ' ' tokenNm                            :(UserRpt50)
*----------
UserRpt60   basenm            =     splitname(pathnm)[2]
            basenm            '.' fndExt RPOS(0) =

*           PNorm()
*           PPure()

            lispnm            =     basenm '.lisp'
            OUTPUT(.OUTPUT, 2, lispnm)                                                       :F(xerr)
            SetLevel(0)
            TDump(bnf)
            ENDFILE(2)

            incnm             =     'transl8-' basenm '.ebnf'
            OUTPUT(.OUTPUT, 2, incnm)                                                        :F(xerr)
            ppSetStyle('ebnf')
            pp(bnf)
            ENDFILE(2)

            snonm             =     'transl8-' basenm '.inc'
            OUTPUT(.OUTPUT, 2, snonm)                                                        :F(xerr)
            ppSetStyle('sno')
            ppOps             =     FALSE
            pp(bnf)
            ENDFILE(2)                                                                       :(RETURN)
UserRptEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserFinal()')                                                            :(UserFinalEnd)
UserFinal                                                                                    :(RETURN)
UserFinalEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserTokens()')                                                           :(UserTokensEnd)
UserTokens  tok[t = t + 1] = token(,, .ebnf)
            tok[t = t + 1] = token(, *(spcpfx '*MATCH'), *MATCH)
            tok[t = t + 1] = token(, *(spcpfx '*MATCH_CASE'), *MATCH_CASE)
            tok[t = t + 1] = token(, *(spcpfx '*MATCH_NOSPACE'), *MATCH_NOSPACE)
            tok[t = t + 1] = token(, *(spcpfx '*integer'), *integer)
            tok[t = t + 1] = token(, *(spcpfx '*STRING'), *STRING)
            tok[t = t + 1] = token(, *(tx), *resword . tx)
            tok[t = t + 1] = token(, *(tx), *keyword . tx)
            tok[t = t + 1] = token(, *(spcpfx '*SYMBOL'), *SYMBOL)
            tok[t = t + 1] = token(, *(spcpfx '*NONTERM'), *NONTERM)
            tok[t = t + 1] = token(, *("$'" tx "'"), *operator . tx)

            dbg[.MATCH] = TRUE
            dbg[.MATCH_CASE] = TRUE
            dbg[.MATCH_NOSPACE] = TRUE
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
            dbg[.name] = TRUE
            dbg[.element] = TRUE
            dbg[.semantic] = TRUE
            dbg[.rules] = TRUE
            dbg[.rule] = TRUE
            dbg[.lvalue] = TRUE
            dbg[.indexed] = TRUE
            dbg[.attribute] = TRUE
            dbg[.index_list] = TRUE
            dbg[.index] = TRUE
            dbg[.symbol] = TRUE
            dbg[.nonterm] = TRUE
            dbg[.expression] = TRUE
            dbg[.function] = TRUE
            dbg[.arg_list] = TRUE
            dbg[.argument] = TRUE
            dbg[.expr] = TRUE
            dbg[.expr_list] = TRUE

                                                                                             :(RETURN)
UserTokensEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
