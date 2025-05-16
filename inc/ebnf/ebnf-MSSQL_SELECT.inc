            boolean_expression                  =  *search_condition1
            search_condition                    =  *search_condition1
            search_condition1                   =  *search_condition2 *search_condition1$1
            search_condition1$1                 =  epsilon | *search_condition1$1 *search_condition1$1$0
            search_condition1$1$0               =  OR *search_condition2
            search_condition2                   =  *search_condition3 *search_condition2$1
            search_condition2$1                 =  epsilon | *search_condition2$1 *search_condition2$1$0
            search_condition2$1$0               =  AND *search_condition3
            search_condition3                   =  *search_condition4 | NOT *search_condition3
            search_condition4                   =  *search_condition5 *search_condition4$1
            search_condition4$1                 =  epsilon | *search_condition4$1 *search_condition4$1$0
            search_condition4$1$0               =  $'^' *search_condition5 | $'|' *search_condition5
            search_condition5                   =  *search_condition6 *search_condition5$1
+                                               |  CONTAINS $'(' *search_condition5$2 $',' *string_literal $')'
+                                               |  FREETEXT $'(' *search_condition5$3 $',' *freetext_string $')'
+                                               |  EXISTS $'(' *subquery $')'
            search_condition5$1                 =  epsilon
+                                               |  *comparison_operator *search_condition5$1$1 $'(' *subquery $')'
+                                               |  *search_condition5$1$2 *search_condition6
+                                               |  *search_condition5$1$3 LIKE *search_condition6 *search_condition5$1$4
+                                               |  *search_condition5$1$5 BETWEEN *search_condition6 AND *search_condition6
+                                               |  IS *search_condition5$1$6 NULL
+                                               |  *search_condition5$1$7 IN $'(' *search_condition5$1$8 $')'
            search_condition5$1$1               =  ALL | SOME | ANY
            search_condition5$1$2               =  *comparison_operator | $'*=' | $'=*'
            search_condition5$1$3               =  epsilon | NOT
            search_condition5$1$4               =  epsilon | ESCAPE *search_condition6
            search_condition5$1$5               =  epsilon | NOT
            search_condition5$1$6               =  epsilon | NOT
            search_condition5$1$7               =  epsilon | NOT
            search_condition5$1$8               =  *subquery | *search_condition5$1$8$1
            search_condition5$1$8$1             =  *search_condition6 | *search_condition5$1$8$1 $',' *search_condition6
            search_condition5$2                 =  *column | $'*'
            search_condition5$3                 =  *column | $'*'
            search_condition6                   =  *search_condition7 *search_condition6$1
            search_condition6$1                 =  epsilon | *search_condition6$1 *search_condition6$1$0
            search_condition6$1$0               =  $'+' *search_condition7 | $'-' *search_condition7 | $'&' *search_condition7
            search_condition7                   =  *search_condition8 *search_condition7$1
            search_condition7$1                 =  epsilon | *search_condition7$1 *search_condition7$1$0
            search_condition7$1$0               =  $'*' *search_condition8 | $'/' *search_condition8 | $'%' *search_condition8
            search_condition8                   =  *search_condition9 *search_condition8$1
+                                               |  $'+' *search_condition8
+                                               |  $'-' *search_condition8
+                                               |  $'~' *search_condition8
            search_condition8$1                 =  epsilon | *COLLATE_clause
            search_condition9                   =  *constant
+                                               |  *search_condition9$1 *column_name
+                                               |  *local_variable
+                                               |  *global_variable
+                                               |  *function_call
+                                               |  *CASE_expression
+                                               |  $'(' *scalar_subquery $')'
+                                               |  $'(' *search_condition $')'
            search_condition9$1                 =  epsilon | *alias $'.'
            expression                          =  *expression1
            expression1                         =  *expression2 *expression1$1
            expression1$1                       =  epsilon | *expression1$1 *expression1$1$0
            expression1$1$0                     =  $'^' *expression2 | $'|' *expression2
            expression2                         =  *expression3 *expression2$1
            expression2$1                       =  epsilon
+                                               |  $'=' *expression3
+                                               |  $'>' *expression3
+                                               |  $'<' *expression3
+                                               |  $'>=' *expression3
+                                               |  $'<=' *expression3
+                                               |  $'<>' *expression3
+                                               |  $'!<' *expression3
+                                               |  $'!=' *expression3
+                                               |  $'!>' *expression3
            expression3                         =  *expression4 *expression3$1
            expression3$1                       =  epsilon | *expression3$1 *expression3$1$0
            expression3$1$0                     =  $'+' *expression4 | $'-' *expression4 | $'&' *expression4
            expression4                         =  *expression5 *expression4$1
            expression4$1                       =  epsilon | *expression4$1 *expression4$1$0
            expression4$1$0                     =  $'*' *expression5 | $'/' *expression5 | $'%' *expression5
            expression5                         =  *expression6 *expression5$1 | $'+' *expression5 | $'-' *expression5 | $'~' *expression5
            expression5$1                       =  epsilon | *COLLATE_clause
            expression6                         =  *constant
+                                               |  *expression6$1 *column_name
+                                               |  *local_variable
+                                               |  *global_variable
+                                               |  *function_call
+                                               |  *CASE_expression
+                                               |  $'(' *scalar_subquery $')'
+                                               |  $'(' *expression $')'
            expression6$1                       =  epsilon | *alias $'.'
            constant                            =  NULL | *real_literal | *binary_literal | *integer_literal | *string_literal | *money_literal
            CASE_expression                     =  CASE *CASE_expression$1
            CASE_expression$1                   =  *expression *CASE_expression$1$1 *CASE_expression$1$2 END | *CASE_expression$1$3 *CASE_expression$1$4 END
            CASE_expression$1$1                 =  *CASE_expression$1$1$0 | *CASE_expression$1$1 *CASE_expression$1$1$0
            CASE_expression$1$1$0               =  WHEN *expression THEN *expression
            CASE_expression$1$2                 =  epsilon | ELSE *expression
            CASE_expression$1$3                 =  *CASE_expression$1$3$0 | *CASE_expression$1$3 *CASE_expression$1$3$0
            CASE_expression$1$3$0               =  WHEN *boolean_expression THEN *expression
            CASE_expression$1$4                 =  epsilon | ELSE *expression
            function_call                       =  *function pop() $'(' *function_call$1 $')'
            function_call$1                     =  epsilon | *function_call$1$1
            function_call$1$1                   =  *expression | *function_call$1$1 $',' *expression
            COLLATE_clause                      =  COLLATE *COLLATE_clause$1
            COLLATE_clause$1                    =  *collation_name | DATABASE_DEFAULT
            collation_name                      =  *identifier | *string_literal
            select_source                       =  *select_source$1 *select_source$2
            select_source$1                     =  *table_source | $'(' *select_source $')'
            select_source$2                     =  epsilon | *select_source$2$1
            select_source$2$1                   =  *joined_table | *select_source$2$1 *joined_table
            table_source                        =  *table_source$1 *table_source$2 *table_source$3 *table_source$4
+                                               |  *view pop() *table_source$5 *table_source$6
+                                               |  *rowset_function *table_source$7
+                                               |  $'::' *user_defined_function $'(' $')' *table_source$8
+                                               |  OPENXML
+                                               |  *derived_table *table_source$9 *table_alias *table_source$10
            table_source$1                      =  *table pop() | *local_variable
            table_source$2                      =  epsilon | *table_source$2$1 *table_alias
            table_source$2$1                    =  epsilon | AS
            table_source$3                      =  epsilon | *table_source$3$1 $'(' *table_hint *table_source$3$2 $')'
            table_source$3$1                    =  epsilon | WITH
            table_source$3$2                    =  epsilon | *table_source$3$2 *table_source$3$2$0
            table_source$3$2$0                  =  *table_source$3$2$1 *table_hint
            table_source$3$2$1                  =  epsilon | $','
            table_source$4                      =  epsilon | $'<' *table_source$4$1 $'>' *table_source$4$2
            table_source$4$1                    =  *table_source$4$1$0 | *table_source$4$1 $',' *table_source$4$1$0
            table_source$4$1$0                  =  *local_variable | NULL
            table_source$4$2                    =  epsilon | *identifier
            table_source$5                      =  epsilon | *table_source$5$1 *table_alias
            table_source$5$1                    =  epsilon | AS
            table_source$6                      =  epsilon | WITH $'(' *table_source$6$1 $')'
            table_source$6$1                    =  *view_hint | *table_source$6$1 $',' *view_hint
            table_source$7                      =  epsilon | *table_source$7$1 *table_alias
            table_source$7$1                    =  epsilon | AS
            table_source$8                      =  epsilon | *table_source$8$1 *table_alias
            table_source$8$1                    =  epsilon | AS
            table_source$9                      =  epsilon | AS
            table_source$10                     =  epsilon | $'(' *table_source$10$1 $')'
            table_source$10$1                   =  *column_alias | *table_source$10$1 $',' *column_alias
            joined_table                        =  *joined_table$1 *joined_table$2 JOIN *select_source ON *search_condition | CROSS JOIN *select_source
            joined_table$1                      =  epsilon | INNER | *joined_table$1$1 *joined_table$1$2
            joined_table$1$1                    =  LEFT | RIGHT | FULL
            joined_table$1$2                    =  epsilon | OUTER
            joined_table$2                      =  epsilon | *join_hint
            table_hint                          =  INDEX $'(' *table_hint$1 $')'
+                                               |  INDEX $'=' *index_val
+                                               |  FASTFIRSTROW
+                                               |  HOLDLOCK
+                                               |  NOLOCK
+                                               |  PAGLOCK
+                                               |  READCOMMITTED
+                                               |  READPAST
+                                               |  READUNCOMMITTED
+                                               |  REPEATABLEREAD
+                                               |  ROWLOCK
+                                               |  SERIALIZABLE
+                                               |  TABLOCK
+                                               |  TABLOCKX
+                                               |  UPDLOCK
            table_hint$1                        =  *index_val | *table_hint$1 $',' *index_val
            SELECT_statement                    =  *query_expression *SELECT_statement$1 *SELECT_statement$2 *SELECT_statement$3 *SELECT_statement$4
            SELECT_statement$1                  =  epsilon | ORDER BY *SELECT_statement$1$1
            SELECT_statement$1$1                =  *SELECT_statement$1$1$0 | *SELECT_statement$1$1 $',' *SELECT_statement$1$1$0
            SELECT_statement$1$1$0              =  *order_by_expression *SELECT_statement$1$1$1
            SELECT_statement$1$1$1              =  epsilon | ASC | DESC
            SELECT_statement$2                  =  epsilon | *SELECT_statement$2 *SELECT_statement$2$0
            SELECT_statement$2$0                =  COMPUTE *SELECT_statement$2$1 *SELECT_statement$2$2
            SELECT_statement$2$1                =  *SELECT_statement$2$1$0 | *SELECT_statement$2$1 $',' *SELECT_statement$2$1$0
            SELECT_statement$2$1$0              =  *SELECT_statement$2$1$1 $'(' *expression $')'
            SELECT_statement$2$1$1              =  AVG | COUNT | MAX | MIN | SUM
            SELECT_statement$2$2                =  epsilon | BY *SELECT_statement$2$2$1
            SELECT_statement$2$2$1              =  *expression | *SELECT_statement$2$2$1 $',' *expression
            SELECT_statement$3                  =  epsilon | FOR *SELECT_statement$3$1
            SELECT_statement$3$1                =  BROWSE | XML *SELECT_statement$3$1$1 *SELECT_statement$3$1$2 *SELECT_statement$3$1$3 *SELECT_statement$3$1$4
            SELECT_statement$3$1$1              =  RAW | AUTO | EXPLICIT
            SELECT_statement$3$1$2              =  epsilon | $',' XMLDATA
            SELECT_statement$3$1$3              =  epsilon | $',' ELEMENTS
            SELECT_statement$3$1$4              =  epsilon | $',' BINARY *base64
            SELECT_statement$4                  =  epsilon | OPTION $'(' *SELECT_statement$4$1 $')'
            SELECT_statement$4$1                =  *select_query_hint | *SELECT_statement$4$1 $',' *select_query_hint
            query_expression                    =  *query_expression$1 *query_expression$2
            query_expression$1                  =  *query_specification | $'(' *query_expression $')'
            query_expression$2                  =  epsilon | *query_expression$2 *query_expression$2$0
            query_expression$2$0                =  UNION *query_expression$2$1 *query_expression$2$2
            query_expression$2$1                =  epsilon | ALL
            query_expression$2$2                =  *query_specification | $'(' *query_expression $')'
            query_specification                 =  SELECT
+                                                  *query_specification$1
+                                                  *query_specification$2
+                                                  *select_list
+                                                  *query_specification$3
+                                                  *query_specification$4
+                                                  *query_specification$5
+                                                  *query_specification$6
+                                                  *query_specification$7
            query_specification$1               =  epsilon | ALL | DISTINCT
            query_specification$2               =  epsilon | *query_specification$2$1 *query_specification$2$2
            query_specification$2$1             =  TOP *integer_literal | TOP *integer_literal PERCENT
            query_specification$2$2             =  epsilon | WITH TIES
            query_specification$3               =  epsilon | INTO *new_table
            query_specification$4               =  epsilon | FROM *query_specification$4$1
            query_specification$4$1             =  *select_source | *query_specification$4$1 $',' *select_source
            query_specification$5               =  epsilon | WHERE *search_condition
            query_specification$6               =  epsilon | GROUP BY *query_specification$6$1 *query_specification$6$2 *query_specification$6$3
            query_specification$6$1             =  epsilon | ALL
            query_specification$6$2             =  *group_by_expression | *query_specification$6$2 $',' *group_by_expression
            query_specification$6$3             =  epsilon | WITH *query_specification$6$3$1
            query_specification$6$3$1           =  CUBE | ROLLUP
            query_specification$7               =  epsilon | HAVING *search_condition
            select_list                         =  *select_list$0 | *select_list $',' *select_list$0
            select_list$0                       =  $'*' | *identifier $'.' $'*' | *column_alias $'=' *expression | *select_list$1 *select_list$2
            select_list$1                       =  *column_name | *expression | IDENTITYCOL | ROWGUIDCOL
            select_list$2                       =  epsilon | *select_list$2$1 *column_alias
            select_list$2$1                     =  epsilon | AS
            select_query_hint                   =  *select_query_hint$1 GROUP
+                                               |  *select_query_hint$2 UNION
+                                               |  *select_query_hint$3 JOIN
+                                               |  FAST *number_rows
+                                               |  FORCE ORDER
+                                               |  MAXDOP *number
+                                               |  ROBUST PLAN
+                                               |  KEEP PLAN
+                                               |  KEEPFIXED PLAN
+                                               |  EXPAND VIEWS
            select_query_hint$1                 =  HASH | ORDER
            select_query_hint$2                 =  CONCAT | HASH | MERGE
            select_query_hint$3                 =  LOOP | MERGE | HASH
            global_variable                     =  *at_at_identifier
            local_variable                      =  *at_identifier
            dont_know                           =  *identifier
            alias                               =  *table_or_view pop() | *identifier
            column                              =  *column$1 *identifier
            column$1                            =  epsilon | *identifier $'.'
            base64                              =  *dont_know
            index_val                           =  *integer_literal
            join_hint                           =  *dont_know
            rowset_function                     =  OPENROWSET $'(' *rowset_function$1 $')'
            rowset_function$1                   =  epsilon | *rowset_function$1$1
            rowset_function$1$1                 =  *expression | *rowset_function$1$1 $',' *expression
            scalar_subquery                     =  *query_specification *scalar_subquery$1
            scalar_subquery$1                   =  epsilon | ORDER BY *scalar_subquery$1$1
            scalar_subquery$1$1                 =  *scalar_subquery$1$1$0 | *scalar_subquery$1$1 $',' *scalar_subquery$1$1$0
            scalar_subquery$1$1$0               =  *order_by_expression *scalar_subquery$1$1$1
            scalar_subquery$1$1$1               =  epsilon | ASC | DESC
            view_hint                           =  *dont_know
            column_alias                        =  *identifier | *string_literal
            column_name                         =  *identifier
            comparison_operator                 =  $'='
+                                               |  $'>'
+                                               |  $'<'
+                                               |  $'>='
+                                               |  $'>' $'='
+                                               |  $'<='
+                                               |  $'<' $'='
+                                               |  $'<>'
+                                               |  $'<' $'>'
+                                               |  $'!<'
+                                               |  $'!' $'<'
+                                               |  $'!='
+                                               |  $'!' $'='
+                                               |  $'!>'
+                                               |  $'!' $'>'
            derived_table                       =  *select_statement
            freetext_string                     =  *string_literal
            group_by_expression                 =  *expression
            new_table                           =  *identifier
            number                              =  *integer_literal
            number_rows                         =  *integer_literal
            order_by_expression                 =  *integer_literal | *expression
            select_statement                    =  *SELECT_statement
            subquery                            =  *select_statement
            table_alias                         =  *identifier
            user_defined_function               =  *identifier
            function                            =  *function$1 (*function_name) ~ 'id' ("'function'" & '3')
            function$1                          =  (*database_name) ~ 'id' $'.' (*owner_name | epsilon) ~ 'id' $'.'
+                                               |  epsilon ~ 'id' (*owner_name) ~ 'id' $'.'
+                                               |  epsilon ~ 'id' epsilon ~ 'id'
            table                               =  *table$1 (*table_name) ~ 'id' ("'table'" & '3')
            table$1                             =  (*database_name) ~ 'id' $'.' (*owner_name | epsilon) ~ 'id' $'.'
+                                               |  epsilon ~ 'id' (*owner_name) ~ 'id' $'.'
+                                               |  epsilon ~ 'id' epsilon ~ 'id'
            table_or_view                       =  *table_or_view$1 (*table_or_view_name) ~ 'id' ("'table_or_view'" & '3')
            table_or_view$1                     =  (*database_name) ~ 'id' $'.' (*owner_name | epsilon) ~ 'id' $'.'
+                                               |  epsilon ~ 'id' (*owner_name) ~ 'id' $'.'
+                                               |  epsilon ~ 'id' epsilon ~ 'id'
            view                                =  *view$1 (*view_name) ~ 'id' ("'view'" & '3')
            view$1                              =  (*database_name) ~ 'id' $'.' (*owner_name | epsilon) ~ 'id' $'.'
+                                               |  epsilon ~ 'id' (*owner_name) ~ 'id' $'.'
+                                               |  epsilon ~ 'id' epsilon ~ 'id'
            database_name                       =  *identifier
            function_name                       =  *identifier
            owner_name                          =  *identifier
            table_name                          =  *identifier
            view_name                           =  *identifier
            table_or_view_name                  =  *identifier
