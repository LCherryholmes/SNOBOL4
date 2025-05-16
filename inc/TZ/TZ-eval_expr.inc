            '('                                 =  '('
            ')'                                 =  ')'
            '*'                                 =  '*'
            '+'                                 =  '+'
            '-'                                 =  '-'
            '/'                                 =  '/'
            ','                                 =  ','
            expression                          =  *expr
            expr                                =  $'_IDENT_' | $'_REAL_' | $'_INT_' | *compound_expr | *function_expr
            expr_list                           =  *expr | *expr_list $',' *expr
            compound_expr                       =  $'(' *expr $')'
+                                               |  *compound_expr_1 *expr $'*'
+                                               |  *expr MOD *expr
+                                               |  *expr $'*' *expr
+                                               |  *expr $'/' *expr
+                                               |  *expr $'+' *expr
+                                               |  *expr $'-' *expr
+                                               |  *expr $'_BIT_AND_' *expr
+                                               |  *expr $'_BIT_OR_' *expr
+                                               |  *expr $'_BIT_XOR_' *expr
            compound_expr_1                     =  $'+' | $'-'
            function_expr                       =  $'_IDENT_' $'(' *function_args $')'
            function_args                       =  epsilon | *expr_list
