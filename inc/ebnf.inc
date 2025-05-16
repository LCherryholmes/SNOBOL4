*---------------------------------------------------------------------------------------------------
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
*---------------------------------------------------------------------------------------------------
            keywords          =
            reswords          =     'SHIFT REDUCE POP'
            operators         =     '} | { ] [ ? ' semicolon ' <- := ::= -> ... ,,, ) ( < > ++ -- # , + - * /'
            ident             =     ANY(&UCASE '_' &LCASE) FENCE(SPAN('0123456789' &UCASE '_' &LCASE) | epsilon)
            identifier        =     ident $ tx $ *notmatch(reswords, (POS(0) | ' ') upr(tx) (' ' | RPOS(0)))
            resword           =     ident $ tx $ *match(reswords, (POS(0) | ' ') upr(tx) (' ' | RPOS(0)))
            keyword           =     ident $ tx $ *match(keywords, (POS(0) | ' ') upr(tx) (' ' | RPOS(0)))
            Populate(.TW, ident, keywords, reswords,, operators)
*---------------------------------------------------------------------------------------------------
            left_arrow        =     '<-'
+                             |     ':='
+                             |     '::='
+                             |     $' '
+                                   ( LEFTWARDS_ARROW
+                                   | LEFTWARDS_DOUBLE_ARROW
+                                   | LONG_LEFTWARDS_ARROW
+                                   | LONG_LEFTWARDS_DOUBLE_ARROW
+                                   | LEFTWARDS_ARROW_WITH_SMALL_TRIANGLE_ARROWHEAD
+                                   | LEFTWARDS_ARROW_WITH_MEDIUM_TRIANGLE_ARROWHEAD
+                                   | LEFTWARDS_ARROW_WITH_LARGE_TRIANGLE_ARROWHEAD
+                                   | LEFTWARDS_ARROW_WITH_SMALL_EQUILATERAL_ARROWHEAD
+                                   | LEFTWARDS_ARROW_WITH_EQUILATERAL_ARROWHEAD
+                                   | HEAVY_LEFTWARDS_ARROW_WITH_EQUILATERAL_ARROWHEAD
+                                   | HEAVY_LEFTWARDS_ARROW_WITH_LARGE_EQUILATERAL_ARROWHEAD
+                                   | LEFTWARDS_TRIANGLE_HEADED_ARROW_WITH_NARROW_SHAFT
+                                   | LEFTWARDS_TRIANGLE_HEADED_ARROW_WITH_MEDIUM_SHAFT
+                                   | LEFTWARDS_TRIANGLE_HEADED_ARROW_WITH_BOLD_SHAFT
+                                   | LEFTWARDS_TRIANGLE_HEADED_ARROW_WITH_HEAVY_SHAFT
+                                   | LEFTWARDS_TRIANGLE_HEADED_ARROW_WITH_VERY_HEAVY_SHAFT
+                                   | LEFTWARDS_SQUARED_ARROW
+                                   | LEFTWARDS_HEAVY_ARROW
+                                   | LEFTWARDS_SANS_SERIF_ARROW
+                                   | WIDE_HEADED_LEFTWARDS_LIGHT_BARB_ARROW
+                                   | WIDE_HEADED_LEFTWARDS_BARB_ARROW
+                                   | WIDE_HEADED_LEFTWARDS_MEDIUM_BARB_ARROW
+                                   )
            right_arrow       =     $'->'
+                             |     $' '
+                                   ( RIGHTWARDS_ARROW
+                                   | RIGHTWARDS_DOUBLE_ARROW
+                                   | LONG_RIGHTWARDS_ARROW
+                                   | LONG_RIGHTWARDS_DOUBLE_ARROW
+                                   | RIGHTWARDS_ARROW_WITH_SMALL_TRIANGLE_ARROWHEAD
+                                   | RIGHTWARDS_ARROW_WITH_MEDIUM_TRIANGLE_ARROWHEAD
+                                   | RIGHTWARDS_ARROW_WITH_LARGE_TRIANGLE_ARROWHEAD
+                                   | RIGHTWARDS_ARROW_WITH_SMALL_EQUILATERAL_ARROWHEAD
+                                   | RIGHTWARDS_ARROW_WITH_EQUILATERAL_ARROWHEAD
+                                   | HEAVY_RIGHTWARDS_ARROW_WITH_EQUILATERAL_ARROWHEAD
+                                   | HEAVY_RIGHTWARDS_ARROW_WITH_LARGE_EQUILATERAL_ARROWHEAD
+                                   | RIGHTWARDS_TRIANGLE_HEADED_ARROW_WITH_NARROW_SHAFT
+                                   | RIGHTWARDS_TRIANGLE_HEADED_ARROW_WITH_MEDIUM_SHAFT
+                                   | RIGHTWARDS_TRIANGLE_HEADED_ARROW_WITH_BOLD_SHAFT
+                                   | RIGHTWARDS_TRIANGLE_HEADED_ARROW_WITH_HEAVY_SHAFT
+                                   | RIGHTWARDS_TRIANGLE_HEADED_ARROW_WITH_VERY_HEAVY_SHAFT
+                                   | RIGHTWARDS_SQUARED_ARROW
+                                   | RIGHTWARDS_HEAVY_ARROW
+                                   | RIGHTWARDS_SANS_SERIF_ARROW
+                                   | WIDE_HEADED_RIGHTWARDS_LIGHT_BARB_ARROW
+                                   | WIDE_HEADED_RIGHTWARDS_BARB_ARROW
+                                   | WIDE_HEADED_RIGHTWARDS_MEDIUM_BARB_ARROW
+                                   )
            arrow             =     left_arrow | right_arrow
            vertical_bar      =     $'|' | $' ' VERTICAL_ELLIPSIS
*---------------------------------------------------------------------------------------------------
            MATCH             =     $' ' "'" ARBNO(bSlash (bSlash | ANY("n'")) | BREAK("'" bSlash)) "'"
            STRING            =     $' ' '"' ARBNO(bSlash (bSlash | ANY('n"')) | BREAK('"' bSlash)) '"'
            INTEGER           =     $' ' SPAN('0123456789')
            SYMBOL            =     $' ' *identifier
*---------------------------------------------------------------------------------------------------
            ebnf              =     nPush() *productions ("'productions'" & 'nTop()') nPop()
            productions       =     *production nInc() (*productions | epsilon)
            production        =     SYMBOL ~ 'identifier' arrow *alternates $semicolon ("'bnf_production'" & 2)

            alternates        =     nPush() *alternates_1 ("'|'" & '*(GT(nTop(), 1) nTop())') nPop()
            alternates_1      =     *subsequents nInc() (vertical_bar *alternates_1 | epsilon)

            subsequents       =     nPush() *subsequents_1 ("'&'" & '*(GT(nTop(), 1) nTop())') nPop()
            subsequents_1     =     *repetition nInc() (*subsequents_1 | epsilon)

            repetition        =     *element
+                                   (  $'...' ("'+'" & 1)
+                                   |  $',,,' ("','" & 1)
+                                   |  epsilon
+                                   )
+                             |     $'[' *alternates $']'
+                                   (  $'...' ("'*'" & 1)
+                                   |  $',,,' ("','" & 1) ("'?'" & 1)
+                                   |  epsilon ("'?'" & 1)
+                                   )
+                             |     SHIFT $'[' *symbol $',' *alternates $']' ("'?'" & 1) ("'Shift[]'" & 2)

            symbol            =     (SYMBOL ~ 'identifier' | STRING ~ 'string')

            element           =     SYMBOL ~ 'identifier'
+                             |     MATCH ~ 'string'
+                             |     POP $'(' $')' ("'Pop()'" & 0)
+                             |     REDUCE $'(' *symbol $',' *expression $')' ("'Reduce()'" & 2)
+                             |     SHIFT $'('
+                                   (  *symbol
+                                      (  $',' *alternates ("'Shift()'" & 2)
+                                      |  epsilon          ("'Shift()'" & 1)
+                                      )
+                                   |  epsilon             ("'Shift()'" & 0)
+                                   )
+                                   $')'
+                             |     $'<'  ("'&nPush'" & 0)
+                             |     $'>'  ("'&nPop'"  & 0)
+                             |     $'++' ("'&nInc'"  & 0)
+                             |     $'--' ("'&nDec'"  & 0)
+                             |     $'(' *alternates $')'

            expression        =     *expression1

            expression1       =     *expression2
+                                   (  $'+' *expression1 ("'.+.'" & 2)
+                                   |  $'-' *expression1 ("'.-.'" & 2)
+                                   |  epsilon
+                                   )

            expression2       =     *expression3
+                                   (  $'*' *expression2 ("'.*.'" & 2)
+                                   |  $'/' *expression2 ("'./.'" & 2)
+                                   |  epsilon
+                                   )

            expression3       =     $'+' *expression3 ("'+.'" & 1)
+                             |     $'-' *expression3 ("'-.'" & 1)
+                             |     *expression4

            expression4       =     INTEGER ~ 'integer'
+                             |     $'#' ~ '#'
+                             |     $'(' *expression $')' ("()" & 1)
