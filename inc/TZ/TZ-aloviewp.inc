            '('                                 =  '('
            ')'                                 =  ')'
            '*'                                 =  '*'
            '+'                                 =  '+'
            ','                                 =  ','
            '-'                                 =  '-'
            '.'                                 =  '.'
            '/'                                 =  '/'
            ':'                                 =  ':'
            '@'                                 =  '@'
            column_reference                    =  *ident_kw *column_reference_1 *column_reference_2
+                                               |  ROWID *column_reference_3 *column_reference_4
+                                               |  ROWLABEL *column_reference_5 *column_reference_6
+                                               |  *ident_kw $'.' *ident_kw *column_reference_7 *column_reference_8
+                                               |  *ident_kw $'.' ROWID *column_reference_9 *column_reference_10
+                                               |  *ident_kw $'.' ROWLABEL *column_reference_11 *column_reference_12
+                                               |  *ident_kw
+                                                  $'.'
+                                                  *ident_kw
+                                                  $'.'
+                                                  *ident_kw
+                                                  *column_reference_13
+                                                  *column_reference_14
+                                               |  *ident_kw
+                                                  $'.'
+                                                  *ident_kw
+                                                  $'.'
+                                                  ROWID
+                                                  *column_reference_15
+                                                  *column_reference_16
+                                               |  *ident_kw
+                                                  $'.'
+                                                  *ident_kw
+                                                  $'.'
+                                                  ROWLABEL
+                                                  *column_reference_17
+                                                  *column_reference_18
            column_reference_1                  =  epsilon | $'@' *dblink
            column_reference_10                 =  epsilon | $'_OUTER_JOIN_'
            column_reference_11                 =  epsilon | $'@' *dblink
            column_reference_12                 =  epsilon | $'_OUTER_JOIN_'
            column_reference_13                 =  epsilon | $'@' *dblink
            column_reference_14                 =  epsilon | $'_OUTER_JOIN_'
            column_reference_15                 =  epsilon | $'@' *dblink
            column_reference_16                 =  epsilon | $'_OUTER_JOIN_'
            column_reference_17                 =  epsilon | $'@' *dblink
            column_reference_18                 =  epsilon | $'_OUTER_JOIN_'
            column_reference_2                  =  epsilon | $'_OUTER_JOIN_'
            column_reference_3                  =  epsilon | $'@' *dblink
            column_reference_4                  =  epsilon | $'_OUTER_JOIN_'
            column_reference_5                  =  epsilon | $'@' *dblink
            column_reference_6                  =  epsilon | $'_OUTER_JOIN_'
            column_reference_7                  =  epsilon | $'@' *dblink
            column_reference_8                  =  epsilon | $'_OUTER_JOIN_'
            column_reference_9                  =  epsilon | $'@' *dblink
            comparison                          =  $'_EQ_'
+                                               |  $'_NEQ_2_'
+                                               |  $'_NEQ_3_'
+                                               |  $'_NEQ_1_'
+                                               |  $'_LT_'
+                                               |  $'_LEQ_'
+                                               |  $'_GT_'
+                                               |  $'_GEQ_'
            condition                           =  *condition_term | *condition OR *condition_term
            condition_element                   =  *expr *comparison *expr
+                                               |  *expr *comparison ANY *expr_group
+                                               |  *expr *comparison SOME *expr_group
+                                               |  *expr *comparison ALL *expr_group
+                                               |  *expr *comparison *subquery
+                                               |  *expr *comparison ANY *subquery
+                                               |  *expr *comparison SOME *subquery
+                                               |  *expr *comparison ALL *subquery
+                                               |  *expr_group *equal_or_not *subquery
+                                               |  *expr_group *equal_or_not ANY *subquery
+                                               |  *expr_group *equal_or_not SOME *subquery
+                                               |  *expr_group *equal_or_not ALL *subquery
+                                               |  *expr_group *equal_or_not *expr_group_group
+                                               |  *expr_group *equal_or_not ANY *expr_group_group
+                                               |  *expr_group *equal_or_not SOME *expr_group_group
+                                               |  *expr_group *equal_or_not ALL *expr_group_group
+                                               |  *expr IN *expr_group
+                                               |  *expr NOT IN *expr_group
+                                               |  *expr IN *subquery
+                                               |  *expr NOT IN *subquery
+                                               |  *expr_group IN *expr_group_group
+                                               |  *expr_group NOT IN *expr_group_group
+                                               |  *expr_group IN *subquery
+                                               |  *expr_group NOT IN *subquery
+                                               |  *expr *condition_element_1 BETWEEN *expr AND *expr
+                                               |  *expr IS *condition_element_2 NULL
+                                               |  EXISTS *subquery
+                                               |  *expr LIKE *expr
+                                               |  *expr NOT LIKE *expr
+                                               |  *expr LIKE *expr ESCAPE *expr
+                                               |  *expr NOT LIKE *expr ESCAPE *expr
+                                               |  $'(' *condition $')'
            condition_element_1                 =  epsilon | NOT
            condition_element_2                 =  epsilon | NOT
            condition_factor                    =  *condition_element | NOT *condition_factor
            condition_term                      =  *condition_factor | *condition_term AND *condition_factor
            date_func                           =  ADD_MONTHS $'(' *expr $',' *expr $')'
+                                               |  LAST_DAY $'(' *expr $')'
+                                               |  NEW_TIME $'(' *expr $',' *expr $',' *expr $')'
+                                               |  NEXT_DAY $'(' *expr $',' *expr $')'
+                                               |  TO_DATE $'(' *expr *date_func_1 $')'
            date_func_1                         =  epsilon | $',' *expr *date_func_1_1
            date_func_1_1                       =  epsilon | $',' *expr
            dblink                              =  *ident_kw | *dblink $'.' *ident_kw
            decode_func                         =  DECODE
+                                                  $'('
+                                                  *expr
+                                                  $','
+                                                  *expr
+                                                  $','
+                                                  *expr
+                                                  *decode_func_1
+                                                  *decode_func_2
+                                                  $')'
            decode_func_1                       =  epsilon | *decode_func_1 $',' *expr $',' *expr
            decode_func_2                       =  epsilon | $',' *expr
            equal_or_not                        =  $'_EQ_' | $'_NEQ_2_' | $'_NEQ_3_' | $'_NEQ_1_'
            expr                                =  *expr_expr
            expr_element                        =  *column_reference
+                                               |  *sequence_reference
+                                               |  *number
+                                               |  *text
+                                               |  *date_func
+                                               |  *label_func
+                                               |  *number_func
+                                               |  *rowid_func
+                                               |  *text_func
+                                               |  *decode_func
+                                               |  *round_func
+                                               |  *trunc_func
+                                               |  *user_func
+                                               |  *misc_func
+                                               |  NULL
+                                               |  SYSDATE
+                                               |  LEVEL
+                                               |  HEXTORAW $'(' *expr $')'
+                                               |  $':' *expr_element_1 *expr_element_2
            expr_element_1                      =  *number | *variable
            expr_element_2                      =  epsilon | *expr_element_2_1 $':' *variable
            expr_element_2_1                    =  epsilon | INDICATOR
            expr_expr                           =  *expr_term
+                                               |  *expr_expr $'+' *expr_term
+                                               |  *expr_expr $'-' *expr_term
+                                               |  *expr_expr $'_CONCAT_' *expr_term
            expr_factor                         =  *expr_element
+                                               |  $'+' *expr_factor
+                                               |  $'-' *expr_factor
+                                               |  PRIOR *expr_factor
+                                               |  $'(' *expr_expr $')'
            expr_group                          =  $'(' *expr_list $')'
            expr_group_group                    =  $'(' *expr_group_list $')'
            expr_group_list                     =  *expr_group | *expr_group_list $',' *expr_group
            expr_list                           =  *expr | *expr_list $',' *expr
            expr_term                           =  *expr_factor
+                                               |  *expr_term $'*' *expr_factor
+                                               |  *expr_term $'/' *expr_factor
            ident                               =  $'_IDENT_' | $'_DQ_STRING_'
            ident_kw                            =  *ident | *key_word
            into_item                           =  $':' *variable *into_item_1
            into_item_1                         =  epsilon | $':' *variable
            key_word                            =  ABS
+                                               |  ACOS
+                                               |  ADD_MONTHS
+                                               |  ASCII
+                                               |  ASIN
+                                               |  ATAN
+                                               |  ATAN2
+                                               |  AVG
+                                               |  BITAND
+                                               |  CEIL
+                                               |  CHR
+                                               |  CONCAT
+                                               |  CONVERT
+                                               |  COS
+                                               |  COSH
+                                               |  COUNT
+                                               |  DECODE
+                                               |  DUMP
+                                               |  EXP
+                                               |  FLOOR
+                                               |  GLB
+                                               |  GREATEST
+                                               |  GREATEST_LB
+                                               |  HEXTORAW
+                                               |  INITCAP
+                                               |  INSTR
+                                               |  INSTRB
+                                               |  LAST_DAY
+                                               |  LEAST
+                                               |  LEAST_UB
+                                               |  LENGTH
+                                               |  LENGTHB
+                                               |  LN
+                                               |  LOG
+                                               |  LOWER
+                                               |  LPAD
+                                               |  LTRIM
+                                               |  LUB
+                                               |  MAX
+                                               |  MIN
+                                               |  MOD
+                                               |  MONTHS_BETWEEN
+                                               |  NEW_TIME
+                                               |  NEXT_DAY
+                                               |  NLSSORT
+                                               |  NLS_INITCAP
+                                               |  NLS_LOWER
+                                               |  NLS_UPPER
+                                               |  NVL
+                                               |  POWER
+                                               |  RAWTOHEX
+                                               |  RAWTOLAB
+                                               |  REPLACE
+                                               |  ROUND
+                                               |  ROWIDTOCHAR
+                                               |  RPAD
+                                               |  RTRIM
+                                               |  SIGN
+                                               |  SIN
+                                               |  SINH
+                                               |  SOUNDEX
+                                               |  SQRT
+                                               |  STDDEV
+                                               |  SUBSTR
+                                               |  SUBSTRB
+                                               |  SUM
+                                               |  TAN
+                                               |  TANH
+                                               |  TO_CHAR
+                                               |  TO_DATE
+                                               |  TO_LABEL
+                                               |  TO_MULTI_BYTE
+                                               |  TO_NUMBER
+                                               |  TO_SINGLE_BYTE
+                                               |  TRANSLATE
+                                               |  TRUNC
+                                               |  UPPER
+                                               |  USERENV
+                                               |  VARIANCE
+                                               |  VSIZE
            label_func                          =  LEAST_UB $'(' *expr *label_func_1 $')'
+                                               |  GREATEST_LB $'(' *expr *label_func_2 $')'
+                                               |  RAWTOLAB $'(' *expr $')'
+                                               |  TO_LABEL $'(' *expr *label_func_3 $')'
+                                               |  LUB $'(' *label_func_4 *expr $')'
+                                               |  GLB $'(' *label_func_5 *expr $')'
            label_func_1                        =  epsilon | *label_func_1 $',' *expr
            label_func_2                        =  epsilon | *label_func_2 $',' *expr
            label_func_3                        =  epsilon | $',' *expr
            label_func_4                        =  epsilon | *label_func_4_1
            label_func_4_1                      =  DISTINCT | ALL
            label_func_5                        =  epsilon | *label_func_5_1
            label_func_5_1                      =  DISTINCT | ALL
            misc_func                           =  NVL $'(' *expr $',' *expr $')'
+                                               |  COUNT $'(' *misc_func_1 *misc_func_2 $')'
+                                               |  MAX $'(' *misc_func_3 *expr $')'
+                                               |  MIN $'(' *misc_func_4 *expr $')'
+                                               |  SUM $'(' *misc_func_5 *expr $')'
+                                               |  GREATEST $'(' *expr *misc_func_6 $')'
+                                               |  LEAST $'(' *expr *misc_func_7 $')'
            misc_func_1                         =  epsilon | *misc_func_1_1
            misc_func_1_1                       =  DISTINCT | ALL
            misc_func_2                         =  *expr | $'*'
            misc_func_3                         =  epsilon | *misc_func_3_1
            misc_func_3_1                       =  DISTINCT | ALL
            misc_func_4                         =  epsilon | *misc_func_4_1
            misc_func_4_1                       =  DISTINCT | ALL
            misc_func_5                         =  epsilon | *misc_func_5_1
            misc_func_5_1                       =  DISTINCT | ALL
            misc_func_6                         =  epsilon | *misc_func_6 $',' *expr
            misc_func_7                         =  epsilon | *misc_func_7 $',' *expr
            number                              =  $'_NUMBER_'
            number_func                         =  UID
+                                               |  ABS $'(' *expr $')'
+                                               |  ACOS $'(' *expr $')'
+                                               |  ASIN $'(' *expr $')'
+                                               |  ATAN $'(' *expr $')'
+                                               |  ATAN2 $'(' *expr $',' *expr $')'
+                                               |  BITAND $'(' *expr $',' *expr $')'
+                                               |  CEIL $'(' *expr $')'
+                                               |  COS $'(' *expr $')'
+                                               |  COSH $'(' *expr $')'
+                                               |  EXP $'(' *expr $')'
+                                               |  FLOOR $'(' *expr $')'
+                                               |  LN $'(' *expr $')'
+                                               |  LOG $'(' *expr $',' *expr $')'
+                                               |  MOD $'(' *expr $',' *expr $')'
+                                               |  POWER $'(' *expr $',' *expr $')'
+                                               |  SIGN $'(' *expr $')'
+                                               |  SIN $'(' *expr $')'
+                                               |  SINH $'(' *expr $')'
+                                               |  SQRT $'(' *expr $')'
+                                               |  TAN $'(' *expr $')'
+                                               |  TANH $'(' *expr $')'
+                                               |  ASCII $'(' *expr $')'
+                                               |  INSTR $'(' *expr $',' *expr *number_func_1 $')'
+                                               |  INSTRB $'(' *expr $',' *expr *number_func_2 $')'
+                                               |  LENGTH $'(' *expr $')'
+                                               |  LENGTHB $'(' *expr $')'
+                                               |  NLSSORT $'(' *expr *number_func_3 $')'
+                                               |  MONTHS_BETWEEN $'(' *expr $',' *expr $')'
+                                               |  TO_NUMBER $'(' *expr *number_func_4 $')'
+                                               |  VSIZE $'(' *expr $')'
+                                               |  AVG $'(' *number_func_5 *expr $')'
+                                               |  STDDEV $'(' *number_func_6 *expr $')'
+                                               |  VARIANCE $'(' *number_func_7 *expr $')'
            number_func_1                       =  epsilon | $',' *expr *number_func_1_1
            number_func_1_1                     =  epsilon | $',' *expr
            number_func_2                       =  epsilon | $',' *expr *number_func_2_1
            number_func_2_1                     =  epsilon | $',' *expr
            number_func_3                       =  epsilon | $',' *expr
            number_func_4                       =  epsilon | $',' *expr *number_func_4_1
            number_func_4_1                     =  epsilon | $',' *expr
            number_func_5                       =  epsilon | *number_func_5_1
            number_func_5_1                     =  DISTINCT | ALL
            number_func_6                       =  epsilon | *number_func_6_1
            number_func_6_1                     =  DISTINCT | ALL
            number_func_7                       =  epsilon | *number_func_7_1
            number_func_7_1                     =  DISTINCT | ALL
            query_expr                          =  *query_expr_term
+                                               |  *query_expr UNION *query_expr_term
+                                               |  *query_expr UNION ALL *query_expr_term
+                                               |  *query_expr INTERSECT *query_expr_term
+                                               |  *query_expr MINUS *query_expr_term
            query_expr_term                     =  *query_select | $'(' *query_expr $')'
            query_select                        =  SELECT
+                                                  *query_select_1
+                                                  *query_select_2
+                                                  *query_select_3
+                                                  FROM
+                                                  *table_reference
+                                                  *query_select_4
+                                                  *query_select_5
+                                                  *query_select_6
+                                                  *query_select_7
            query_select_1                      =  epsilon | *query_select_1_1
            query_select_1_1                    =  ALL | DISTINCT | UNIQUE
            query_select_2                      =  $'*' | *select_item *query_select_2_1
            query_select_2_1                    =  epsilon | *query_select_2_1 $',' *select_item
            query_select_3                      =  epsilon | INTO *into_item *query_select_3_1
            query_select_3_1                    =  epsilon | *query_select_3_1 $',' *into_item
            query_select_4                      =  epsilon | *query_select_4 $',' *table_reference
            query_select_5                      =  epsilon | WHERE *condition
            query_select_6                      =  epsilon | *query_select_6 *query_select_6_1
            query_select_6_1                    =  START WITH *condition
+                                               |  CONNECT BY *condition
+                                               |  GROUP BY *expr_list
+                                               |  HAVING *condition
            query_select_7                      =  epsilon | WITH CHECK OPTION
            round_func                          =  ROUND $'(' *expr *round_func_1 $')'
            round_func_1                        =  epsilon | $',' *expr
            rowid_func                          =  CHARTOROWID $'(' *expr $')' | ROWNUM
            select_item                         =  *expr
+                                               |  *expr *ident_kw
+                                               |  *expr AS *ident_kw
+                                               |  *ident_kw $'.' $'*'
+                                               |  *ident_kw $'.' *ident_kw $'.' $'*'
            sequence_reference                  =  *ident_kw $'.' CURRVAL
+                                               |  *ident_kw $'.' NEXTVAL
+                                               |  *ident_kw $'.' *ident_kw $'.' CURRVAL
+                                               |  *ident_kw $'.' *ident_kw $'.' NEXTVAL
            subquery                            =  $'(' *query_expr $')'
            table_reference                     =  *ident_kw *table_reference_1
+                                               |  *ident_kw *table_reference_2 *ident_kw
+                                               |  *ident_kw $'.' *ident_kw *table_reference_3
+                                               |  *ident_kw $'.' *ident_kw *table_reference_4 *ident_kw
+                                               |  *subquery
+                                               |  *subquery *ident_kw
            table_reference_1                   =  epsilon | $'@' *dblink
            table_reference_2                   =  epsilon | $'@' *dblink
            table_reference_3                   =  epsilon | $'@' *dblink
            table_reference_4                   =  epsilon | $'@' *dblink
            text                                =  $'_SQ_STRING_'
            text_func                           =  USER
+                                               |  CHR $'(' *expr $')'
+                                               |  CONCAT $'(' *expr $',' *expr $')'
+                                               |  INITCAP $'(' *expr $')'
+                                               |  LOWER $'(' *expr $')'
+                                               |  LPAD $'(' *expr $',' *expr *text_func_1 $')'
+                                               |  LTRIM $'(' *expr *text_func_2 $')'
+                                               |  NLS_INITCAP $'(' *expr *text_func_3 $')'
+                                               |  NLS_LOWER $'(' *expr *text_func_4 $')'
+                                               |  NLS_UPPER $'(' *expr *text_func_5 $')'
+                                               |  REPLACE $'(' *expr $',' *expr *text_func_6 $')'
+                                               |  RPAD $'(' *expr $',' *expr *text_func_7 $')'
+                                               |  RTRIM $'(' *expr *text_func_8 $')'
+                                               |  SOUNDEX $'(' *expr $')'
+                                               |  SUBSTR $'(' *expr $',' *expr *text_func_9 $')'
+                                               |  SUBSTRB $'(' *expr $',' *expr *text_func_10 $')'
+                                               |  TRANSLATE $'(' *expr $',' *expr $',' *expr $')'
+                                               |  UPPER $'(' *expr $')'
+                                               |  TO_SINGLE_BYTE $'(' *expr $')'
+                                               |  TO_MULTI_BYTE $'(' *expr $')'
+                                               |  TO_CHAR $'(' *expr *text_func_11 $')'
+                                               |  RAWTOHEX $'(' *expr $')'
+                                               |  CONVERT $'(' *expr $',' *expr *text_func_12 $')'
+                                               |  ROWIDTOCHAR $'(' *expr $')'
+                                               |  DUMP $'(' *expr *text_func_13 $')'
+                                               |  USERENV $'(' *text $')'
            text_func_1                         =  epsilon | $',' *expr
            text_func_10                        =  epsilon | $',' *expr
            text_func_11                        =  epsilon | $',' *expr *text_func_11_1
            text_func_11_1                      =  epsilon | $',' *expr
            text_func_12                        =  epsilon | $',' *expr
            text_func_13                        =  epsilon | $',' *expr *text_func_13_1
            text_func_13_1                      =  epsilon | $',' *expr *text_func_13_1_1
            text_func_13_1_1                    =  epsilon | $',' *expr
            text_func_2                         =  epsilon | $',' *expr
            text_func_3                         =  epsilon | $',' *expr
            text_func_4                         =  epsilon | $',' *expr
            text_func_5                         =  epsilon | $',' *expr
            text_func_6                         =  epsilon | $',' *expr
            text_func_7                         =  epsilon | $',' *expr
            text_func_8                         =  epsilon | $',' *expr
            text_func_9                         =  epsilon | $',' *expr
            trunc_func                          =  TRUNC $'(' *expr *trunc_func_1 $')'
            trunc_func_1                        =  epsilon | $',' *expr
            user_func                           =  *ident $'(' *expr_list $')'
+                                               |  *ident_kw $'@' *dblink $'(' *expr_list $')'
+                                               |  *ident_kw $'.' *ident $'(' *expr_list $')'
+                                               |  *ident_kw $'.' *ident_kw $'@' *dblink $'(' *expr_list $')'
+                                               |  *ident_kw $'.' *ident_kw $'.' *ident $'(' *expr_list $')'
+                                               |  *ident_kw
+                                                  $'.'
+                                                  *ident_kw
+                                                  $'.'
+                                                  *ident_kw
+                                                  $'@'
+                                                  *dblink
+                                                  $'('
+                                                  *expr_list
+                                                  $')'
            variable                            =  $'_IDENT_'
            view                                =  *query_expr
