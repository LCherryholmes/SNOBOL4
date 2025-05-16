*-- -------------------------------------------------------------------
*   CONTAINS search condition pattern

*   Lexical SNOBOL4 Patterns
    wrd                 =   SPAN(&UCASE &LCASE "-'")
    word                =   $' ' wrd
+                       |   $' ' '"' $' ' wrd $' ' '"'
    word_prefix         =   $' ' '"' $' ' wrd $' ' '*' $' ' '"'
    phrase              =   $' ' '"' $' ' wrd $'  ' wrd ARBNO($'  ' wrd) $' ' '"'
    phrase_prefix       =   $' ' '"' $' ' wrd $'  ' wrd ARBNO($'  ' wrd) $' ' '*' $' ' '"'
    real_number         =   $' ' (SPAN('0123456789') '.' SPAN('0123456789'))

*   Gramatical/Syntactical SNOBOL4 Patterns
    search_condition    =   *search_condition1
    search_condition1   =   *search_condition2 ARBNO((OR | $'|') *search_condition2)
    search_condition2   =   *search_condition3 ARBNO((AND (NOT | epsilon) | $'&!' | $'&') *search_condition3)
    search_condition3   =   *search_condition4 | *weighted_term | *generation_term
    search_condition4   =   *search_condition5 ARBNO((NEAR | $'~') *search_condition5)
    search_condition5   =   *search_condition6 ARBNO((BY | $'+') *search_condition6)
    search_condition6   =   *basic_term | $'(' *search_condition1 $')'
    weighted_term       =   ISABOUT $'(' *weighted_factor ARBNO($',' *weighted_factor) $')'
    generation_term     =   FORMSOF $'(' (INFLECTIONAL | THESAURUS) $',' *simple_term ARBNO($',' *simple_term) $')'
    weighted_factor     =   (*generation_term | *proximity_term) (WEIGHT $'(' *weight_value $')' | epsilon)
    proximity_term      =   *basic_term ARBNO((NEAR | $'~') *basic_term)
    basic_term          =   *simple_term | *prefix_term
    simple_term         =   *word | *phrase
    prefix_term         =   *word_prefix | *phrase_prefix
    weight_value        =   *real_number
