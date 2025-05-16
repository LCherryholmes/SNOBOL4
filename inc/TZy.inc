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
            fndExt            =     'y' . extc
            fndCmd            =     'd:/mksnt/find //flash/e/dev -name "*.y" -print'
*           fndSpecific       =     'aloiddlp.y'
            fndExclude        =     'eval.y' | 'scpyacc.y' | '-' BREAK('.') '.y'
            spcpfx            =
            spcpfx            =     EQ(doInclWhite, TRUE) "$' ' "
            keyint            =     ('?') . tx

            blanks            =     (bSlash nl | SPAN(' ' tab cr ff))
            white             =     (bSlash nl | SPAN(' ' tab cr ff nl))
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
            escapedCharacter  =     (  bSlash
+                                      (  ANY('abfnrtv' '"' bSlash "'" nl)
+                                      |  ANY('01234567') FENCE(ANY('01234567') | epsilon)
+                                      |  ANY('0123') ANY('01234567') ANY('01234567')
+                                      |  ANY('Xx') SPAN('0123456789ABCDEFabcdef')
+                                      )
+                                   )

            characterLiteral  =     "'" (escapedCharacter | NOTANY("'" bSlash cr lf)) "'"
            stringLiteral     =     '"' ARBNO(escapedCharacter | BREAK('"' bSlash cr lf)) '"'

            keywords          =     'break case continue default delete do else for goto '
+                                   'if left new prec right start struct switch token type union while'
            reswords          =
            special           =     '} { ) ( %} %{ %% $$ '
            operators         =     '~ || |= | ^= ^ ] [ ? >>= >> >= > == = <= <<= << < ; :: : /= / ... .* . '
+                                   '->* -> -= -- - , += ++ + *= * ) ( &= && & %= % # != !'
            ident             =     ANY(&UCASE '_' &LCASE) FENCE(SPAN(&UCASE '_' &LCASE '0123456789') | epsilon)
            identifier        =     ident $ tx $ *notmatch(reswords, (POS(0) | ' ') tx (' ' | RPOS(0)))
            resword           =     ident $ tx $ *match(reswords, (POS(0) | ' ') tx (' ' | RPOS(0)))
            keyword           =     ident $ tx $ *match(keywords, (POS(0) | ' ') tx (' ' | RPOS(0)))
            $'$#'             =     $' ' TZ(2, '$#', '$' SPAN('0123456789'))
            $'@#'             =     $' ' TZ(2, '@#', '@' SPAN('0123456789'))
            $'$<>$'           =     $' ' TZ(2, '$<>$', '$<' ident '>$')
            $'$<>#'           =     $' ' TZ(2, '$<>#', '$<' ident '>' SPAN('0123456789'))
            Populate(.TX, ident, keywords, reswords, special, operators)
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            cTokens           =     *cToken FENCE(*cTokens | epsilon)
            cToken            =     $' '
+                                   (  *floatingLiteral
+                                   |  *integerLiteral
+                                   |  *characterLiteral
+                                   |  *stringLiteral
+                                   |  *identifier
+                                   |  *resword
+                                   |  $'$$'
+                                   |  $'$#'
+                                   |  $'@#'
+                                   |  $'$<>$'
+                                   |  $'$<>#'
+                                   |  *operator
+                                   )
            cBlock            =     $'{' ARBNO(*cBlockBody) $'}'
            cExpr             =     $'(' ARBNO(*cExprBody) $')'
            cBlockBody        =     *cToken | *cBlock | *cExpr
            cExprBody         =     *cToken | *cExpr

            pct_block         =     $'%{' ARBNO(*cBlockBody) $'%}'
            pct_union         =     $'%' union $'{' ARBNO(*cBlockBody) $'}'
            pct_type          =     $'%' type   $'<' $' ' *identifier $'>' %($' ' *identifier)
            pct_token         =     $'%' token ($'<' $' ' *identifier $'>' | epsilon)
+                                   epsilon ~ ''
+                                   nPush() *pct_token_names ('re_spec' & 'nTop()') nPop()
+                                   ('re_production' & 2)
            pct_token_names   =     $' ' *pct_token_name nInc() FENCE(*pct_token_names | epsilon)
            pct_token_name    =     (  (*identifier ~ 'identifier') (epsilon ~ 'string')
+                                   |  (*characterLiteral ~ 'identifier') ~ 'string'
+                                   ) ('re' & 2)
            pct_left          =     $'%' left   %($' ' (*identifier | *characterLiteral))
            pct_right         =     $'%' right  %($' ' (*identifier | *characterLiteral))
            pct_start         =     $'%' start  $' ' *identifier

            yProduction       =     $' ' *identifier ~ 'identifier' $':' *yAlternates ('bnf_production' & 2)
            yAlternates       =     nPush() *yyAlternates ('|' & '*(GT(nTop(), 1) nTop())') nPop()
            yyAlternates      =     *ySubsequents nInc() ($'|' *yyAlternates | epsilon)
            ySubsequents      =     nPush() (*yySubsequents | epsilon)
+                                   ('epsilon' & '*(EQ(nTop(), 0))')
+                                   ('&' & '*(GT(nTop(), 1) nTop())')
+                                   nPop()
            yySubsequents     =     *yElement (*yySubsequents | epsilon)
            yElement          =     $' ' *identifier ~ 'identifier'  nInc()
+                             |     $' ' *characterLiteral ~ 'string' nInc()
+                             |     *cBlock
+                             |     $'[' ARBNO(*cBlockBody) $']'
+                             |     $'%' prec
+                             |     $';'
            yRecognizer       =     nPush()
+                                   ARBNO(
+                                      *pct_block
+                                   |  *pct_union
+                                   |  *pct_token nInc()
+                                   |  *pct_type
+                                   |  *pct_left
+                                   |  *pct_right
+                                   |  *pct_start
+                                   )
+                                   $'%%'
+                                   ARBNO(*yProduction nInc())
+                                   ('productions' & 'nTop()')
+                                   nPop()
+                                   $' ' RPOS(0)

                                                                                             :(RETURN)
UserDefsEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserRpt()')                                                              :(UserRptEnd)
UserRpt     yy                =     Pop()                                                    :f(RETURN)
            DIFFER(yy)                                                                       :f(RETURN)
            basenm            =     splitname(pathnm)[2]
            basenm            '.' fndExt RPOS(0) =
            lispnm            =     basenm '.lisp'
            OUTPUT(.OUTPUT, 2, lispnm)                                                       :f(xerr)
            SetLevel(0)
            yy                =     Merge(yy)

            DEFINE('XProds(xn)bnfId,c')
            DEFINE('XRefs(xn)')
            DEFINE('X1Plus(xn)')
            DEFINE('X1List(xn)')
            DEFINE('XEpsilon(xn)c')
            DEFINE('XNest(xn)bnfId,c')
            DEFINE('XSubst(xn)')
            DEFINE('XScrub(xn)c')                                                            :(XEnd)
XProds      c                 =     c($xn)
            prods[v(c[1])]    =     c[2]
            bnfId             =     tree('identifier', ARB)
            Find(.c[2], bnfId, .XRefs)                                                       :(RETURN)
XRefs       refs[v($xn)]      =     refs[v($xn)] + 1                                         :(RETURN)
X1Plus      $xn               =     tree('bnf_production')
            Append($xn, tree('identifier', prod1Name))
            Append($xn, tree('+'))
            Append(c($xn)[2], tree('identifier', prod2Name))
            prods[prod1Name]  =     c($xn)[2]
            refs[prod1Name]   =     refs[prod1Name] - 1
            refs[prod2Name]   =     refs[prod2Name] - 1                                      :(RETURN)
X1List      $xn               =     tree('bnf_production')
            Append($xn, tree('identifier', prod1Name))
            Append($xn, tree(','))
            Append(c($xn)[2], tree('identifier', prod2Name))
            prods[prod1Name]  =     c($xn)[2]
            refs[prod1Name]   =     refs[prod1Name] - 1
            refs[prod2Name]   =     refs[prod2Name] - 1                                      :(RETURN)
XEpsilon    c                 =     c($xn)
            Remove(c[2], 1)
            c[2]              =     IDENT(t(c[2]), '|') EQ(n(c[2]), 1) c(c[2])[1]
            c[2]              =     Append(tree('?'), c[2])
            prods[v(c[1])]    =     c[2]                                                     :(RETURN)
XNest       c                 =     c($xn)
            prod              =     v(c[1])
            bnfId             =     tree('identifier', BREAKX('_') '_' SPAN('0123456789'))
            Find(.c[2], bnfId, .XSubst)                                                      :(RETURN)
XSubst      DIFFER(v($xn), prod)                                                             :f(RETURN)
            EQ(refs[v($xn)], 1)                                                              :f(RETURN)
            refs[v($xn)]      =     refs[v($xn)] - 1
            $xn               =     prods[v($xn)]                                            :(RETURN)
XScrub      c                 =     c($xn)
            EQ(refs[v(c[1])], 0)                                                             :f(RETURN)
            $xn               =
            prods[v(c[1])]    =                                                              :(RETURN)
XEnd

            bnfProduction     =     tree('bnf_production')
            Append(bnfProduction, tree('identifier', ARB))
            Append(bnfProduction, tree(ARB, ARB, ARB))
            prods             =     TABLE()
            refs              =     TABLE()
            Find(.yy, bnfProduction, .XProds)

            bnf1Plus          =     tree('bnf_production')
            Append(bnf1Plus, tree('identifier', ARB . prod1Name))
            Append(bnf1Plus, tree('|'))
            Append(c(bnf1Plus)[2], tree('identifier', ARB . prod2Name))
            Append(c(bnf1Plus)[2], tree('&'))
            Append(c(c(bnf1Plus)[2])[2], tree('identifier', *prod1Name))
            Append(c(c(bnf1Plus)[2])[2], tree('identifier', *prod2Name))
            Find(.yy, bnf1Plus, .X1Plus)

            bnf1Plus          =     tree('bnf_production')
            Append(bnf1Plus, tree('identifier', ARB . prod1Name))
            Append(bnf1Plus, tree('|'))
            Append(c(bnf1Plus)[2], tree('&'))
            Append(c(c(bnf1Plus)[2])[1], tree('identifier', *prod1Name))
            Append(c(c(bnf1Plus)[2])[1], tree('identifier', ARB . prod2Name))
            Append(c(bnf1Plus)[2], tree('identifier', *prod2Name))
            Find(.yy, bnf1Plus, .X1Plus)

            bnf1List          =     tree('bnf_production')
            Append(bnf1List, tree('identifier', ARB . prod1Name))
            Append(bnf1List, tree('|'))
            Append(c(bnf1List)[2], tree('identifier', ARB . prod2Name))
            Append(c(bnf1List)[2], tree('&'))
            Append(c(c(bnf1List)[2])[2], tree('identifier', *prod1Name))
            Append(c(c(bnf1List)[2])[2], tree('string', "','"))
            Append(c(c(bnf1List)[2])[2], tree('identifier', *prod2Name))
            Find(.yy, bnf1List, .X1List)

            bnfEpsilon        =     tree('bnf_production')
            Append(bnfEpsilon, tree('identifier', ARB))
            Append(bnfEpsilon, tree('|'))
            Append(c(bnfEpsilon)[2], tree('epsilon'))
            n(c(bnfEpsilon)[2]) =   ARB
            Find(.yy, bnfEpsilon, .XEpsilon)

            XDump('refs', refs)
            TDump(yy)
            Find(.yy, bnfProduction, .XNest)
            XDump('refs', refs)
            TDump(yy)
            bnfProduction     =     tree('bnf_production')
            Append(bnfProduction, tree('identifier', BREAKX('_') '_' SPAN('0123456789')))
            Append(bnfProduction, tree(ARB, ARB, ARB))
            Find(.yy, bnfProduction, .XScrub)

            ENDFILE(2)
            incnm             =     'transl8-' basenm '.ebnf'
            OUTPUT(.OUTPUT, 2, incnm)                                                        :f(xerr)
            ppOps             =     TRUE
            ppSetStyle('ebnf')
            pp(yy)
            ENDFILE(2)                                                                       :(RETURN)
UserRptEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserFinal()')                                                            :(UserFinalEnd)
UserFinal                                                                                    :(RETURN)
UserFinalEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserTokens()')                                                           :(UserTokensEnd)
UserTokens  tok[t = t + 1] = token(,, .yRecognizer)
*           tok[t = t + 1] = token(,, .yProduction)
            tok[t = t + 1] = token(,, .pct_union)
            tok[t = t + 1] = token(,, .pct_token)
            tok[t = t + 1] = token(,, .pct_type)
            tok[t = t + 1] = token(,, .pct_start)
            tok[t = t + 1] = token(, *(spcpfx '*floatingLiteral'),  *floatingLiteral)
            tok[t = t + 1] = token(, *(spcpfx '*integerLiteral'),   *integerLiteral)
            tok[t = t + 1] = token(, *(spcpfx '*characterLiteral'), *characterLiteral)
            tok[t = t + 1] = token(, *(spcpfx '*stringLiteral'),    *stringLiteral)
            tok[t = t + 1] = token(, *(tx), *resword . tx)
            tok[t = t + 1] = token(, *(tx), *keyword . tx)
            tok[t = t + 1] = token(, *(spcpfx '*identifier'), *identifier)
*           tok[t = t + 1] = token(, *(spcpfx "'" tx "'"), *identifier . tx)
            tok[t = t + 1] = token('%{')
            tok[t = t + 1] = token('%}')
            tok[t = t + 1] = token('%%')
            tok[t = t + 1] = token('$$')
            tok[t = t + 1] = token(, *("$'" tx "'"), $'$#' . tx)
            tok[t = t + 1] = token(, *("$'" tx "'"), $'@#' . tx)
            tok[t = t + 1] = token(, *("$'$<>$'"), $'$<>$' . tx)
            tok[t = t + 1] = token(, *("$'$<>#'"), $'$<>#' . tx)
            tok[t = t + 1] = token(, *("$'" tx "'"), *operator . tx)
            tok[t = t + 1] = token('{')
            tok[t = t + 1] = token('}')
            tok[t = t + 1] = token('(')
            tok[t = t + 1] = token(')')

            dbg[.cBlock]      = TRUE
            dbg[.cExpr]       = TRUE
            dbg[.identifier]  = TRUE
            dbg[.operator]    = TRUE

                                                                                             :(RETURN)
UserTokensEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
