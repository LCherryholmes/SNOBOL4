            '('                                 =  '('
            ')'                                 =  ')'
            '|'                                 =  '|'
            ','                                 =  ','
            '='                                 =  '='
            ';'                                 =  ';'
            '['                                 =  '['
            ']'                                 =  ']'
            '{'                                 =  '{'
            '}'                                 =  '}'
            '?'                                 =  '?'
            '.'                                 =  '.'
            ':'                                 =  ':'
            '#'                                 =  '#'
            '!'                                 =  '!'
            '$'                                 =  '$'
            '%'                                 =  '%'
            ebnf                                =  *productions
            productions                         =  *production | *productions *production
            production                          =  *name *alternates $';'
            alternates                          =  *subsequents | *alternates $'|' *subsequents
            subsequents                         =  *subsequents_1 | *semantic *subsequents_1
            subsequents_1                       =  *repetition | *subsequents_1 *repetition
            repetition                          =  *element_pair
+                                               |  *list
+                                               |  *list *semantic
+                                               |  *name *optional
+                                               |  *name *optional *semantic
+                                               |  *optional
+                                               |  *optional *semantic
            list                                =  *element_pair *ELLIPSIS | *element_pair *LISTSIS
            optional                            =  $'[' *alternates $']'
+                                               |  $'[' *alternates $']' *epsilon_semantic
+                                               |  $'[' *alternates $']' *ELLIPSIS
+                                               |  $'[' *alternates $']' *epsilon_semantic *ELLIPSIS
+                                               |  $'[' *alternates $']' *LISTSIS
+                                               |  $'[' *alternates $']' *epsilon_semantic *LISTSIS
            name                                =  *SYMBOL *DEFINES
            element_pair                        =  *element | *element *semantic
            element                             =  SET $'<' *symbol $'>'
+                                               |  CLR $'<' *symbol $'>'
+                                               |  *SYMBOL
+                                               |  *MATCH
+                                               |  IDENT
+                                               |  EOS
+                                               |  INTEGER
+                                               |  REAL
+                                               |  DQ_STRING
+                                               |  SQ_STRING
+                                               |  $'(' *alternates $')'
+                                               |  *name $'(' *alternates $')'
+                                               |  $'?'
+                                               |  $'^'
+                                               |  SCAN_EOL
+                                               |  OUT $'(' *expr_list $')'
+                                               |  *DOLDOL $'=' *expr
+                                               |  *expr
+                                               |  *MATCH_CASE
+                                               |  *MATCH_NOSPACE
            epsilon_semantic                    =  $'!' *semantic
            semantic                            =  $'{' $'}' | $'{' *rules $'}'
            rules                               =  *rule $';' | *rules *rule $';'
            rule                                =  *function
+                                               |  *lvalue $'=' *expression
+                                               |  *lvalue $'_DEFAULT_' *expression
+                                               |  *lvalue $'_PLUS_EQ_' *expression
+                                               |  *symbol $'=' NEW MAIN *symbol $'(' $')'
+                                               |  *symbol $'=' NEW EXTRA *symbol $'(' $')'
            lvalue                              =  *attribute | *indexed
            indexed                             =  *symbol $'[' *index_list $']'
+                                               |  *symbol $'[' *index_list $']' $'.' *symbol $'[' *index_list $']'
            attribute                           =  $'$' *symbol
+                                               |  $'$' *nonterm $'.' *symbol
+                                               |  $'$' $'.' *symbol
+                                               |  *symbol $'[' *index_list $']' $'.' *symbol
            index_list                          =  *index | *index_list $',' *index
            index                               =  *integer
+                                               |  $'_PLUS_PLUS_'
+                                               |  $'$'
+                                               |  *symbol $'_EQ_' $'$' *nonterm $'.' *symbol
            symbol                              =  *SYMBOL | NEW
            nonterm                             =  *SYMBOL | IDENT | INTEGER | REAL | SQ_STRING | DQ_STRING
            integer                             =  *INTEGER
            expression                          =  NEW *symbol $'(' $')'
+                                               |  NEW *symbol $'(' *symbol $')'
+                                               |  *attribute $'*' *attribute
+                                               |  *argument
+                                               |  *function
            function                            =  PROCESS $'(' $')' | *symbol $'(' $')' | *symbol $'(' *arg_list $')'
            arg_list                            =  *argument | *arg_list $',' *argument
            argument                            =  *integer
+                                               |  *integer $'.' *integer
+                                               |  *STRING
+                                               |  NULL
+                                               |  *attribute
+                                               |  *indexed
            expr                                =  *DOLDOL
+                                               |  *integer
+                                               |  $'$'
+                                               |  *STRING
+                                               |  $'#'
+                                               |  *FUNCTION $'(' *expr_list $')'
            expr_list                           =  *expr | *expr_list $',' *expr
