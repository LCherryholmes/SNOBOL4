            '('                                 =  '('
            ')'                                 =  ')'
            '*'                                 =  '*'
            '+'                                 =  '+'
            '-'                                 =  '-'
            '/'                                 =  '/'
            ','                                 =  ','
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
            condition                           =  *cond
            cond                                =  *cond_1
+                                               |  NOT *cond_1
+                                               |  *compound_cond
+                                               |  *range_cond
+                                               |  *comparison_cond
+                                               |  *membership_cond
+                                               |  *null_cond
            cond_1                              =  *literal_cond | $'(' *cond $')'
            compound_cond                       =  *cond AND *cond | *cond OR *cond | *cond XOR *cond
            opt_inversion                       =  epsilon | NOT
            literal_cond                        =  TRUE | FALSE
            null_cond                           =  *expr IS *opt_inversion NULL
            range_cond                          =  *expr *opt_inversion BETWEEN *expr AND *expr
            comparison_cond                     =  *comparison_cond_1
            comparison_cond_1                   =  *comparison_cond_1 $'_EQ_' *expr
+                                               |  *comparison_cond_1 $'_NEQ_' *expr
+                                               |  *comparison_cond_1 $'_GT_' *expr
+                                               |  *comparison_cond_1 $'_LT_' *expr
+                                               |  *comparison_cond_1 $'_GEQ_' *expr
+                                               |  *comparison_cond_1 $'_LEQ_' *expr
+                                               |  *expr $'_EQ_' *expr
+                                               |  *expr $'_NEQ_' *expr
+                                               |  *expr $'_GT_' *expr
+                                               |  *expr $'_LT_' *expr
+                                               |  *expr $'_GEQ_' *expr
+                                               |  *expr $'_LEQ_' *expr
            membership_cond                     =  *expr *opt_inversion IN $'(' *expr_list $')'
