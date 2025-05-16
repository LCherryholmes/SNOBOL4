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
            SQL_batches                         =  *SQL_batch | *SQL_batches *SQL_batch 
            SQL_batch                           =  *SQL_batch$1 *SQL_batch$2 GO FENCE 
            SQL_batch$1                         =  epsilon | *execute_clause 
            SQL_batch$2                         =  epsilon | *SQL_batch$2 *Transact_SQL_statement 
            Transact_SQL_statement              =  *Transact_SQL_statement$1 *Transact_SQL_statement$2 *Transact_SQL_statement$3 
            Transact_SQL_statement$1            =  epsilon | *label $':' 
            Transact_SQL_statement$2            =  *control_of_flow_statement | *sql_statement 
            Transact_SQL_statement$3            =  epsilon | $';' 
            control_of_flow_statement           =  *BEGIN_END_block
+                                               |  *IF_ELSE_statement
+                                               |  *WHILE_statement
+                                               |  BREAK
+                                               |  CONTINUE
+                                               |  GOTO *label
+                                               |  RETURN *control_of_flow_statement$1
+                                               |  WAITFOR *control_of_flow_statement$2 
            control_of_flow_statement$1         =  epsilon | *integer_expression 
            control_of_flow_statement$2         =  DELAY *time | TIME *time 
            BEGIN_END_block                     =  BEGIN *BEGIN_END_block$1 END 
            BEGIN_END_block$1                   =  epsilon | *BEGIN_END_block$1 *Transact_SQL_statement 
            IF_ELSE_statement                   =  IF *boolean_expression *Transact_SQL_statement *IF_ELSE_statement$1 
            IF_ELSE_statement$1                 =  epsilon | ELSE *Transact_SQL_statement 
            WHILE_statement                     =  WHILE *boolean_expression *Transact_SQL_statement 
            boolean_expression                  =  *search_condition1 
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
            sql_statement                       =  *ALTER_DATABASE_statement
+                                               |  *ALTER_FUNCTION_statement
+                                               |  *ALTER_PROCEDURE_statement
+                                               |  *ALTER_TABLE_statement
+                                               |  *ALTER_TRIGGER_statement
+                                               |  *ALTER_VIEW_statement
+                                               |  *BACKUP_statement
+                                               |  *BEGIN_DISTRIBUTED_TRANSACTION_statement
+                                               |  *BEGIN_TRANSACTION_statement
+                                               |  *BULK_INSERT_statement
+                                               |  *CHECKPOINT_statement
+                                               |  *CLOSE_statement
+                                               |  *COMMIT_TRANSACTION_statement
+                                               |  *COMMIT_statement
+                                               |  *CREATE_DATABASE_statement
+                                               |  *CREATE_DEFAULT_statement
+                                               |  *CREATE_FUNCTION_statement
+                                               |  *CREATE_INDEX_statement
+                                               |  *CREATE_PROCEDURE_statement
+                                               |  *CREATE_RULE_statement
+                                               |  *CREATE_SCHEMA_statement
+                                               |  *CREATE_STATISTICS_statement
+                                               |  *CREATE_TABLE_statement
+                                               |  *CREATE_TRIGGER_statement
+                                               |  *CREATE_VIEW_statement
+                                               |  *DBCC_statement
+                                               |  *DEALLOCATE_statement
+                                               |  *DECLARE_variable_statement
+                                               |  *DECLARE_CURSOR_statement
+                                               |  *DELETE_statement
+                                               |  *DENY_statement
+                                               |  *DROP_DATABASE_statement
+                                               |  *DROP_DEFAULT_statement
+                                               |  *DROP_FUNCTION_statement
+                                               |  *DROP_INDEX_statement
+                                               |  *DROP_PROCEDURE_statement
+                                               |  *DROP_RULE_statement
+                                               |  *DROP_STATISTICS_statement
+                                               |  *DROP_TABLE_statement
+                                               |  *DROP_TRIGGER_statement
+                                               |  *DROP_VIEW_statement
+                                               |  *DUMP_statement
+                                               |  *EXECUTE_statement
+                                               |  *FETCH_statement
+                                               |  *GRANT_statement
+                                               |  *INSERT_statement
+                                               |  *KILL_statement
+                                               |  *LOAD_statement
+                                               |  *OPEN_statement
+                                               |  *PRINT_statement
+                                               |  *RAISERROR_statement
+                                               |  *READTEXT_statement
+                                               |  *RECONFIGURE_statement
+                                               |  *RESTORE_statement
+                                               |  *RESTORE_FILELISTONLY_statement
+                                               |  *RESTORE_HEADERONLY_statement
+                                               |  *RESTORE_LABELONLY_statement
+                                               |  *RESTORE_VERIFYONLY_statement
+                                               |  *REVOKE_statement
+                                               |  *ROLLBACK_TRANSACTION_statement
+                                               |  *ROLLBACK_statement
+                                               |  *SAVE_TRANSACTION_statement
+                                               |  *SELECT_variable_statement
+                                               |  *SELECT_statement
+                                               |  *SET_variable_statement
+                                               |  *SET_statement
+                                               |  *SETUSER_statement
+                                               |  *SHUTDOWN_statement
+                                               |  *TRUNCATE_TABLE_statement
+                                               |  *UPDATE_statement
+                                               |  *UPDATE_STATISTICS_statement
+                                               |  *UPDATETEXT_statement
+                                               |  *USE_statement
+                                               |  *WRITETEXT_statement 
            data_type                           =  BIGINT
+                                               |  BINARY *data_type$1
+                                               |  BINARY VARYING *data_type$2
+                                               |  BIT
+                                               |  CHAR *data_type$3
+                                               |  CHAR VARYING *data_type$4
+                                               |  CHARACTER *data_type$5
+                                               |  CHARACTER VARYING *data_type$6
+                                               |  DEC *data_type$7
+                                               |  DECIMAL *data_type$8
+                                               |  DOUBLE PRECISION
+                                               |  CURSOR
+                                               |  DATETIME
+                                               |  FLOAT *data_type$9
+                                               |  IMAGE
+                                               |  INT
+                                               |  INTEGER
+                                               |  MONEY
+                                               |  NATIONAL CHAR *data_type$10
+                                               |  NATIONAL CHAR VARYING *data_type$11
+                                               |  NATIONAL CHARACTER *data_type$12
+                                               |  NATIONAL CHARACTER VARYING *data_type$13
+                                               |  NATIONAL TEXT
+                                               |  NCHAR *data_type$14
+                                               |  NCHAR VARYING *data_type$15
+                                               |  NCHARACTER *data_type$16
+                                               |  NCHARACTER VARYING *data_type$17
+                                               |  NTEXT
+                                               |  NUMERIC *data_type$18
+                                               |  NVARCHAR $'(' *n $')'
+                                               |  REAL
+                                               |  ROWVERSION
+                                               |  SMALLDATETIME
+                                               |  SMALLINT
+                                               |  SMALLMONEY
+                                               |  SQL_VARIANT
+                                               |  TABLE
+                                               |  TEXT
+                                               |  TIMESTAMP
+                                               |  TINYINT
+                                               |  UNIQUEIDENTIFIER
+                                               |  VARBINARY *data_type$19
+                                               |  VARCHAR *data_type$20
+                                               |  *identifier 
            data_type$1                         =  epsilon | $'(' *n $')' 
            data_type$2                         =  epsilon | $'(' *n $')' 
            data_type$3                         =  epsilon | $'(' *n $')' 
            data_type$4                         =  epsilon | $'(' *n $')' 
            data_type$5                         =  epsilon | $'(' *n $')' 
            data_type$6                         =  epsilon | $'(' *n $')' 
            data_type$7                         =  epsilon | $'(' *p *data_type$7$1 $')' 
            data_type$7$1                       =  epsilon | $',' *s 
            data_type$8                         =  epsilon | $'(' *p *data_type$8$1 $')' 
            data_type$8$1                       =  epsilon | $',' *s 
            data_type$9                         =  epsilon | $'(' *n $')' 
            data_type$10                        =  epsilon | $'(' *n $')' 
            data_type$11                        =  epsilon | $'(' *n $')' 
            data_type$12                        =  epsilon | $'(' *n $')' 
            data_type$13                        =  epsilon | $'(' *n $')' 
            data_type$14                        =  epsilon | $'(' *n $')' 
            data_type$15                        =  epsilon | $'(' *n $')' 
            data_type$16                        =  epsilon | $'(' *n $')' 
            data_type$17                        =  epsilon | $'(' *n $')' 
            data_type$18                        =  epsilon | $'(' *p *data_type$18$1 $')' 
            data_type$18$1                      =  epsilon | $',' *s 
            data_type$19                        =  epsilon | $'(' *n $')' 
            data_type$20                        =  epsilon | $'(' *n $')' 
            numeric_expression                  =  *expression 
            float_expression                    =  *expression 
            string_expression                   =  *expression 
            character_expression                =  *expression 
            integer_expression                  =  *expression 
            function_call                       =  ABS $'(' *numeric_expression $')'
+                                               |  ACOS $'(' *float_expression $')'
+                                               |  APP_NAME $'(' $')'
+                                               |  ASCII $'(' *character_expression $')'
+                                               |  ASIN $'(' *float_expression $')'
+                                               |  ATAN $'(' *float_expression $')'
+                                               |  ATN2 $'(' *float_expression $',' *float_expression $')'
+                                               |  AVG $'(' *function_call$1 *expression $')'
+                                               |  BINARY_CHECKSUM $'(' *function_call$2 $')'
+                                               |  CAST $'(' *expression AS *data_type $')'
+                                               |  CEILING $'(' *numeric_expression $')'
+                                               |  CHAR $'(' *integer_expression $')'
+                                               |  CHARINDEX $'(' *expression $',' *expression *function_call$3 $')'
+                                               |  CHECKSUM $'(' *function_call$4 $')'
+                                               |  CHECKSUM_AGG $'(' *function_call$5 *expression $')'
+                                               |  COALESCE $'(' *function_call$6 $')'
+                                               |  COLLATIONPROPERTY $'(' *collation_name $',' *string_expression $')'
+                                               |  COLUMNPROPERTY $'(' *expression $',' *column $',' *string_expression $')'
+                                               |  COL_LENGTH $'(' *table $',' *column $')'
+                                               |  COL_NAME $'(' *table_id $',' *column_id $')'
+                                               |  COS $'(' *float_expression $')'
+                                               |  COT $'(' *float_expression $')'
+                                               |  COUNT $'(' *function_call$7 $')'
+                                               |  COUNT_BIG $'(' *function_call$8 $')'
+                                               |  CURRENT_TIMESTAMP
+                                               |  CURRENT_USER
+                                               |  CURSOR_STATUS $'(' *function_call$9 $')'
+                                               |  DATABASEPROPERTY $'(' *string_expression $',' *string_expression $')'
+                                               |  DATABASEPROPERTYEX $'(' *string_expression $',' *string_expression $')'
+                                               |  DATALENGTH $'(' *expression $')'
+                                               |  DATEADD $'(' *datepart $',' *number $',' *date $')'
+                                               |  DATEDIFF $'(' *datepart $',' *startdate $',' *enddate $')'
+                                               |  DATENAME $'(' *datepart $',' *date $')'
+                                               |  DATEPART $'(' *datepart $',' *date $')'
+                                               |  DAY $'(' *date $')'
+                                               |  DB_ID $'(' *function_call$10 $')'
+                                               |  DEGREES $'(' *numeric_expression $')'
+                                               |  DIFFERENCE $'(' *character_expression $',' *character_expression $')'
+                                               |  EXP $'(' *float_expression $')'
+                                               |  FILEGROUPPROPERTY $'(' *filegroup_name $',' *string_expression $')'
+                                               |  FILEGROUP_ID $'(' *filegroup_name $')'
+                                               |  FILEGROUP_NAME $'(' *filegroup_id $')'
+                                               |  FILEPROPERTY $'(' *file_name $',' *string_expression $')'
+                                               |  FILE_ID $'(' *file_name $')'
+                                               |  FILE_NAME $'(' *file_id $')'
+                                               |  FLOOR $'(' *numeric_expression $')'
+                                               |  FN_GET_SQL $'(' *function_call$11 *Sql_Handle $')'
+                                               |  FN_HELPCOLLATIONS $'(' $')'
+                                               |  FN_LISTEXTENDEDPROPERTY
+                                                  $'('
+                                                  *function_call$12
+                                                  $','
+                                                  *function_call$13
+                                                  $','
+                                                  *function_call$14
+                                                  $','
+                                                  *function_call$15
+                                                  $','
+                                                  *function_call$16
+                                                  $','
+                                                  *function_call$17
+                                                  $','
+                                                  *function_call$18
+                                                  $')'
+                                               |  FN_SERVERSHAREDDRIVES $'(' $')'
+                                               |  FN_TRACE_GETEVENTINFO $'(' *function_call$19 *trace_id $')'
+                                               |  FN_TRACE_GETFILTERINFO $'(' *function_call$20 *trace_id $')'
+                                               |  FN_TRACE_GETINFO $'(' *function_call$21 *trace_id $')'
+                                               |  FN_TRACE_GETTABLE $'(' *function_call$22 *filename $',' *function_call$23 *number_files $')'
+                                               |  FN_VIRTUALFILESTATS $'(' *function_call$24 *database_id $',' *function_call$25 *file_id $')'
+                                               |  FN_VIRTUALSERVERNODES $'()'
+                                               |  FORMATMESSAGE $'(' *msg_number *function_call$26 $')'
+                                               |  FREETEXT $'(' *function_call$27 $',' *freetext_string $')'
+                                               |  FREETEXTTABLE $'(' *table $',' *function_call$28 $',' *freetext_string *function_call$29 $')'
+                                               |  FULLTEXTCATALOGPROPERTY $'(' *catalog_name $',' *string_expression $')'
+                                               |  FULLTEXTSERVICEPROPERTY $'(' *string_expression $')'
+                                               |  GETANSINULL $'(' *function_call$30 $')'
+                                               |  GETUTCDATE $'(' $')'
+                                               |  HAS_DBACCESS $'(' *database_name $')'
+                                               |  HOST_ID $'(' $')'
+                                               |  HOST_NAME $'(' $')'
+                                               |  IDENT_CURRENT $'(' *table $')'
+                                               |  IDENT_INCR $'(' *table_or_view $')'
+                                               |  IDENT_SEED $'(' *table_or_view $')'
+                                               |  INDEXKEY_PROPERTY $'(' *table_ID $',' *index_id $',' *key_ID $',' *string_expression $')'
+                                               |  INDEXPROPERTY $'(' *table_ID $',' *index $',' *string_expression $')'
+                                               |  INDEX_COL $'(' *expression $',' *expression $',' *expression $')'
+                                               |  ISDATE $'(' *expression $')'
+                                               |  ISNUMERIC $'(' *expression $')'
+                                               |  IS_MEMBER $'(' *expression $')'
+                                               |  IS_SRVROLEMEMBER $'(' *role *function_call$31 $')'
+                                               |  LEFT $'(' *character_expression $',' *integer_expression $')'
+                                               |  LEN $'(' *string_expression $')'
+                                               |  LOG $'(' *float_expression $')'
+                                               |  LOG10 $'(' *float_expression $')'
+                                               |  LOWER $'(' *character_expression $')'
+                                               |  LTRIM $'(' *character_expression $')'
+                                               |  MAX $'(' *function_call$32 *expression $')'
+                                               |  MIN $'(' *function_call$33 *expression $')'
+                                               |  MONTH $'(' *date $')'
+                                               |  NCHAR $'(' *integer_expression $')'
+                                               |  NULLIF $'(' *expression $',' *expression $')'
+                                               |  OBJECTPROPERTY $'(' *expression $',' *string_expression $')'
+                                               |  OBJECT_ID $'(' *string_expression *function_call$34 $')'
+                                               |  OBJECT_NAME $'(' *object_id $')'
+                                               |  OPENDATASOURCE $'(' *provider_name $',' *init_string $')'
+                                               |  PARSENAME $'(' *object_name $',' *object_piece $')'
+                                               |  PATINDEX $'(' $'%pattern%' $',' *expression $')'
+                                               |  PERMISSIONS $'(' *function_call$35 $')'
+                                               |  PI $'(' $')'
+                                               |  POWER $'(' *numeric_expression $',' *numeric_expression $')'
+                                               |  QUOTENAME $'(' *character_string *function_call$36 $')'
+                                               |  RADIANS $'(' *numeric_expression $')'
+                                               |  RAND $'(' *function_call$37 $')'
+                                               |  REPLACE $'(' *string_expression1 $',' *string_expression2 $',' *string_expression3 $')'
+                                               |  REPLICATE $'(' *character_expression $',' *integer_expression $')'
+                                               |  REVERSE $'(' *character_expression $')'
+                                               |  RIGHT $'(' *character_expression $',' *integer_expression $')'
+                                               |  ROUND $'(' *numeric_expression $',' *length *function_call$38 $')'
+                                               |  ROWCOUNT_BIG $'(' $')'
+                                               |  RTRIM $'(' *character_expression $')'
+                                               |  SCOPE_IDENTITY $'(' $')'
+                                               |  SERVERPROPERTY $'(' *propertyname $')'
+                                               |  SESSIONPROPERTY $'(' *expression $')'
+                                               |  SESSION_USER
+                                               |  SIGN $'(' *numeric_expression $')'
+                                               |  SIN $'(' *float_expression $')'
+                                               |  SOUNDEX $'(' *character_expression $')'
+                                               |  SPACE $'(' *integer_expression $')'
+                                               |  SQL_VARIANT_PROPERTY $'(' *expression $',' *string_expression $')'
+                                               |  SQRT $'(' *float_expression $')'
+                                               |  SQUARE $'(' *float_expression $')'
+                                               |  STATS_DATE $'(' *table_id $',' *index_id $')'
+                                               |  STDEV $'(' *expression $')'
+                                               |  STDEVP $'(' *expression $')'
+                                               |  STR $'(' *float_expression *function_call$39 $')'
+                                               |  STUFF $'(' *character_expression $',' *start $',' *length $',' *character_expression $')'
+                                               |  SUBSTRING $'(' *expression $',' *expression $',' *expression $')'
+                                               |  SUM $'(' *function_call$40 *expression $')'
+                                               |  SUSER_ID $'(' *function_call$41 $')'
+                                               |  SUSER_NAME $'(' *function_call$42 $')'
+                                               |  SUSER_SNAME $'(' *function_call$43 $')'
+                                               |  SYSTEM_USER
+                                               |  TAN $'(' *float_expression $')'
+                                               |  TEXTPTR $'(' *column $')'
+                                               |  TEXTVALID $'(' *table $'.' *column $',' *text_ptr $')'
+                                               |  TRIGGER_NESTLEVEL $'(' *function_call$44 $')'
+                                               |  TYPEPROPERTY $'(' *type $',' *string_expression $')'
+                                               |  UNICODE $'(' *ncharacter_expression $')'
+                                               |  UPPER $'(' *character_expression $')'
+                                               |  USER
+                                               |  USER_ID $'(' *function_call$45 $')'
+                                               |  USER_NAME $'(' *function_call$46 $')'
+                                               |  VAR $'(' *expression $')'
+                                               |  VARP $'(' *expression $')'
+                                               |  YEAR $'(' *date $')'
+                                               |  *rowset_function_limited
+                                               |  *system_function
+                                               |  *function $'(' *function_call$47 $')' 
            function_call$1                     =  epsilon | ALL | DISTINCT 
            function_call$2                     =  *function_call$2$0 | *function_call$2 $',' *function_call$2$0 
            function_call$2$0                   =  $'*' | *expression 
            function_call$3                     =  epsilon | $',' *start_location 
            function_call$4                     =  *function_call$4$0 | *function_call$4 $',' *function_call$4$0 
            function_call$4$0                   =  $'*' | *expression 
            function_call$5                     =  epsilon | ALL | DISTINCT 
            function_call$6                     =  *expression | *function_call$6 $',' *expression 
            function_call$7                     =  *function_call$7$1 *expression | $'*' 
            function_call$7$1                   =  epsilon | ALL | DISTINCT 
            function_call$8                     =  *function_call$8$1 *expression | $'*' 
            function_call$8$1                   =  epsilon | ALL | DISTINCT 
            function_call$9                     =  *local $',' *cursor_name | *global $',' *cursor_name | *variable $',' *cursor_variable 
            function_call$10                    =  epsilon | *database_name 
            function_call$11                    =  epsilon | *SqlHandle $'=' 
            function_call$12                    =  *default | *function_call$12$1 *property_name | NULL 
            function_call$12$1                  =  epsilon | *name $'=' 
            function_call$13                    =  *default | *function_call$13$1 *level0_object_type | NULL 
            function_call$13$1                  =  epsilon | *level0type $'=' 
            function_call$14                    =  *default | *function_call$14$1 *level0_object_name | NULL 
            function_call$14$1                  =  epsilon | *level0name $'=' 
            function_call$15                    =  *default | *function_call$15$1 *level1_object_type | NULL 
            function_call$15$1                  =  epsilon | *level1type $'=' 
            function_call$16                    =  *default | *function_call$16$1 *level1_object_name | NULL 
            function_call$16$1                  =  epsilon | *level1name $'=' 
            function_call$17                    =  *default | *function_call$17$1 *level2_object_type | NULL 
            function_call$17$1                  =  epsilon | *level2type $'=' 
            function_call$18                    =  *default | *function_call$18$1 *level2_object_name | NULL 
            function_call$18$1                  =  epsilon | *level2name $'=' 
            function_call$19                    =  epsilon | *traceid $'=' 
            function_call$20                    =  epsilon | *traceid $'=' 
            function_call$21                    =  epsilon | *traceid $'=' 
            function_call$22                    =  epsilon | *filename_var $'=' 
            function_call$23                    =  epsilon | *numfiles $'=' 
            function_call$24                    =  epsilon | *DatabaseID $'=' 
            function_call$25                    =  epsilon | *FileID $'=' 
            function_call$26                    =  epsilon | $',' *function_call$26$1 
            function_call$26$1                  =  *param_value | *function_call$26$1 $',' *param_value 
            function_call$27                    =  *column | $'*' 
            function_call$28                    =  *column | $'*' 
            function_call$29                    =  epsilon | $',' *top_n_by_rank 
            function_call$30                    =  epsilon | *database 
            function_call$31                    =  epsilon | $',' *login 
            function_call$32                    =  epsilon | ALL | DISTINCT 
            function_call$33                    =  epsilon | ALL | DISTINCT 
            function_call$34                    =  epsilon | $',' *string_expression 
            function_call$35                    =  epsilon | *objectid *function_call$35$1 
            function_call$35$1                  =  epsilon | $',' *column 
            function_call$36                    =  epsilon | $',' *quote_character 
            function_call$37                    =  epsilon | *seed 
            function_call$38                    =  epsilon | $',' *dont_know 
            function_call$39                    =  epsilon | $',' *length *function_call$39$1 
            function_call$39$1                  =  epsilon | $',' *decimal 
            function_call$40                    =  epsilon | ALL | DISTINCT 
            function_call$41                    =  epsilon | *login 
            function_call$42                    =  epsilon | *server_user_id 
            function_call$43                    =  epsilon | *server_user_sid 
            function_call$44                    =  epsilon | *object_id 
            function_call$45                    =  epsilon | *user 
            function_call$46                    =  epsilon | *expression 
            function_call$47                    =  epsilon | *expression % $',' 
            ALTER_DATABASE_statement            =  ALTER DATABASE *database_name *ALTER_DATABASE_statement$1 
            ALTER_DATABASE_statement$1          =  ADD FILE *ALTER_DATABASE_statement$1$1 *ALTER_DATABASE_statement$1$2
+                                               |  ADD LOG FILE *ALTER_DATABASE_statement$1$3
+                                               |  REMOVE FILE *logical_file_name
+                                               |  ADD FILEGROUP *filegroup_name
+                                               |  REMOVE FILEGROUP *filegroup_name
+                                               |  MODIFY FILE *alter_database_filespec
+                                               |  MODIFY NAME $'=' *new_dbname
+                                               |  MODIFY FILEGROUP *filegroup_name *ALTER_DATABASE_statement$1$4
+                                               |  SET *ALTER_DATABASE_statement$1$5 *ALTER_DATABASE_statement$1$6
+                                               |  COLLATE *collation_name 
            ALTER_DATABASE_statement$1$1        =  *alter_database_filespec | *ALTER_DATABASE_statement$1$1 $',' *alter_database_filespec 
            ALTER_DATABASE_statement$1$2        =  epsilon | TO FILEGROUP *filegroup_name 
            ALTER_DATABASE_statement$1$3        =  *alter_database_filespec | *ALTER_DATABASE_statement$1$3 $',' *alter_database_filespec 
            ALTER_DATABASE_statement$1$4        =  *filegroup_property | NAME $'=' *new_filegroup_name 
            ALTER_DATABASE_statement$1$5        =  *optionspec | *ALTER_DATABASE_statement$1$5 $',' *optionspec 
            ALTER_DATABASE_statement$1$6        =  epsilon | WITH *termination 
            alter_database_filespec             =  $'('
+                                                  NAME
+                                                  $'='
+                                                  *logical_file_name
+                                                  *alter_database_filespec$1
+                                                  *alter_database_filespec$2
+                                                  *alter_database_filespec$3
+                                                  *alter_database_filespec$4
+                                                  *alter_database_filespec$5
+                                                  $')' 
            alter_database_filespec$1           =  epsilon | $',' NEWNAME $'=' *new_logical_name 
            alter_database_filespec$2           =  epsilon | $',' FILENAME $'=' *os_file_name 
            alter_database_filespec$3           =  epsilon | $',' SIZE $'=' *size 
            alter_database_filespec$4           =  epsilon | $',' MAXSIZE $'=' *alter_database_filespec$4$1 
            alter_database_filespec$4$1         =  *max_size | UNLIMITED 
            alter_database_filespec$5           =  epsilon | $',' FILEGROWTH $'=' *growth_increment 
            optionspec                          =  *state_option | *cursor_option | *auto_option | *sql_option | *recovery_option 
            state_option                        =  SINGLE_USER | RESTRICTED_USER | MULTI_USER | OFFLINE | ONLINE | READ_ONLY | READ_WRITE 
            cursor_option                       =  CURSOR_CLOSE_ON_COMMIT *cursor_option$1 | CURSOR_DEFAULT *cursor_option$2 
            cursor_option$1                     =  ON | OFF 
            cursor_option$2                     =  LOCAL | GLOBAL 
            auto_option                         =  AUTO_CLOSE *auto_option$1
+                                               |  AUTO_CREATE_STATISTICS *auto_option$2
+                                               |  AUTO_SHRINK *auto_option$3
+                                               |  AUTO_UPDATE_STATISTICS *auto_option$4 
            auto_option$1                       =  ON | OFF 
            auto_option$2                       =  ON | OFF 
            auto_option$3                       =  ON | OFF 
            auto_option$4                       =  ON | OFF 
            sql_option                          =  ANSI_NULL_DEFAULT *sql_option$1
+                                               |  ANSI_NULLS *sql_option$2
+                                               |  ANSI_PADDING *sql_option$3
+                                               |  ANSI_WARNINGS *sql_option$4
+                                               |  ARITHABORT *sql_option$5
+                                               |  CONCAT_NULL_YIELDS_NULL *sql_option$6
+                                               |  NUMERIC_ROUNDABORT *sql_option$7
+                                               |  QUOTED_IDENTIFIER *sql_option$8
+                                               |  RECURSIVE_TRIGGERS *sql_option$9 
            sql_option$1                        =  ON | OFF 
            sql_option$2                        =  ON | OFF 
            sql_option$3                        =  ON | OFF 
            sql_option$4                        =  ON | OFF 
            sql_option$5                        =  ON | OFF 
            sql_option$6                        =  ON | OFF 
            sql_option$7                        =  ON | OFF 
            sql_option$8                        =  ON | OFF 
            sql_option$9                        =  ON | OFF 
            recovery_option                     =  RECOVERY *recovery_option$1 | TORN_PAGE_DETECTION *recovery_option$2 
            recovery_option$1                   =  FULL | BULK_LOGGED | SIMPLE 
            recovery_option$2                   =  ON | OFF 
            termination                         =  ROLLBACK AFTER *integer_literal *termination$1 | ROLLBACK IMMEDIATE | NO_WAIT 
            termination$1                       =  epsilon | SECONDS 
            ALTER_FUNCTION_statement            =  ALTER FUNCTION *function $'(' *ALTER_FUNCTION_statement$1 $')' RETURNS *ALTER_FUNCTION_statement$2 
            ALTER_FUNCTION_statement$1          =  epsilon | (*parameter_name *scalar_parameter_data_type !($'=' *default)) % $',' 
            ALTER_FUNCTION_statement$2          =  *scalar_return_data_type
+                                                  *ALTER_FUNCTION_statement$2$1
+                                                  *ALTER_FUNCTION_statement$2$2
+                                                  BEGIN
+                                                  *function_body
+                                                  RETURN
+                                                  *scalar_expression
+                                                  END
+                                               |  TABLE *ALTER_FUNCTION_statement$2$3 *ALTER_FUNCTION_statement$2$4 RETURN *ALTER_FUNCTION_statement$2$5
+                                               |  *return_variable
+                                                  TABLE
+                                                  $'('
+                                                  *ALTER_FUNCTION_statement$2$6
+                                                  $')'
+                                                  *ALTER_FUNCTION_statement$2$7
+                                                  *ALTER_FUNCTION_statement$2$8
+                                                  BEGIN
+                                                  *function_body
+                                                  RETURN
+                                                  END 
            ALTER_FUNCTION_statement$2$1        =  epsilon | WITH *ALTER_FUNCTION_statement$2$1$1 
            ALTER_FUNCTION_statement$2$1$1      =  *function_option | *ALTER_FUNCTION_statement$2$1$1 $',' *function_option 
            ALTER_FUNCTION_statement$2$2        =  epsilon | AS 
            ALTER_FUNCTION_statement$2$3        =  epsilon | WITH *ALTER_FUNCTION_statement$2$3$1 
            ALTER_FUNCTION_statement$2$3$1      =  *function_option | *ALTER_FUNCTION_statement$2$3$1 $',' *function_option 
            ALTER_FUNCTION_statement$2$4        =  epsilon | AS 
            ALTER_FUNCTION_statement$2$5        =  $'(' *select_stmt $')' | *select_stmt 
            ALTER_FUNCTION_statement$2$6        =  *ALTER_FUNCTION_statement$2$6$0 | *ALTER_FUNCTION_statement$2$6 $',' *ALTER_FUNCTION_statement$2$6$0 
            ALTER_FUNCTION_statement$2$6$0      =  *declared_column_definition | *declared_table_constraint 
            ALTER_FUNCTION_statement$2$7        =  epsilon | WITH *ALTER_FUNCTION_statement$2$7$1 
            ALTER_FUNCTION_statement$2$7$1      =  *function_option | *ALTER_FUNCTION_statement$2$7$1 $',' *function_option 
            ALTER_FUNCTION_statement$2$8        =  epsilon | AS 
            function_option                     =  ENCRYPTION | SCHEMABINDING 
            ALTER_PROCEDURE_statement           =  ALTER
+                                                  *ALTER_PROCEDURE_statement$1
+                                                  *procedure
+                                                  *ALTER_PROCEDURE_statement$2
+                                                  *ALTER_PROCEDURE_statement$3
+                                                  *ALTER_PROCEDURE_statement$4
+                                                  *ALTER_PROCEDURE_statement$5
+                                                  AS
+                                                  *ALTER_PROCEDURE_statement$6 
            ALTER_PROCEDURE_statement$1         =  PROC | PROCEDURE 
            ALTER_PROCEDURE_statement$2         =  epsilon | $';' *number 
            ALTER_PROCEDURE_statement$3         =  epsilon | (*parameter *data_type !VARYING !($'=' *default) !(OUT | OUTPUT)) % $',' 
            ALTER_PROCEDURE_statement$4         =  epsilon | WITH *ALTER_PROCEDURE_statement$4$1 
            ALTER_PROCEDURE_statement$4$1       =  RECOMPILE | ENCRYPTION | RECOMPILE $',' ENCRYPTION 
            ALTER_PROCEDURE_statement$5         =  epsilon | FOR REPLICATION 
            ALTER_PROCEDURE_statement$6         =  *sql_statement | *ALTER_PROCEDURE_statement$6 *sql_statement 
            ALTER_TABLE_statement               =  ALTER TABLE *table *ALTER_TABLE_statement$1 
            ALTER_TABLE_statement$1             =  *ALTER_TABLE_statement$1$1
+                                               |  ADD *ALTER_TABLE_statement$1$2
+                                               |  *ALTER_TABLE_statement$1$3 ADD *ALTER_TABLE_statement$1$4
+                                               |  DROP *ALTER_TABLE_statement$1$5
+                                               |  *ALTER_TABLE_statement$1$6 CONSTRAINT *ALTER_TABLE_statement$1$7
+                                               |  *ALTER_TABLE_statement$1$8 TRIGGER *ALTER_TABLE_statement$1$9 
            ALTER_TABLE_statement$1$1           =  epsilon | ALTER COLUMN *column_name *ALTER_TABLE_statement$1$1$1 
            ALTER_TABLE_statement$1$1$1         =  *new_data_type *ALTER_TABLE_statement$1$1$1$1 *ALTER_TABLE_statement$1$1$1$2 *ALTER_TABLE_statement$1$1$1$3
+                                               |  *ALTER_TABLE_statement$1$1$1$4 ROWGUIDCOL 
            ALTER_TABLE_statement$1$1$1$1       =  epsilon | $'(' *precision *ALTER_TABLE_statement$1$1$1$1$1 $')' 
            ALTER_TABLE_statement$1$1$1$1$1     =  epsilon | $',' *scale 
            ALTER_TABLE_statement$1$1$1$2       =  epsilon | *COLLATE_clause 
            ALTER_TABLE_statement$1$1$1$3       =  epsilon | NULL | NOT NULL 
            ALTER_TABLE_statement$1$1$1$4       =  ADD | DROP 
            ALTER_TABLE_statement$1$2           =  *ALTER_TABLE_statement$1$2$0 | *ALTER_TABLE_statement$1$2 $',' *ALTER_TABLE_statement$1$2$0 
            ALTER_TABLE_statement$1$2$0         =  *ALTER_TABLE_statement$1$2$1 | *column_name AS *computed_column_expression 
            ALTER_TABLE_statement$1$2$1         =  epsilon | *alter_table_column_definition 
            ALTER_TABLE_statement$1$3           =  epsilon | WITH CHECK | WITH NOCHECK 
            ALTER_TABLE_statement$1$4           =  *alter_table_constraint | *ALTER_TABLE_statement$1$4 $',' *alter_table_constraint 
            ALTER_TABLE_statement$1$5           =  *ALTER_TABLE_statement$1$5$0 | *ALTER_TABLE_statement$1$5 $',' *ALTER_TABLE_statement$1$5$0 
            ALTER_TABLE_statement$1$5$0         =  *ALTER_TABLE_statement$1$5$1 *constraint_name | COLUMN *column_name 
            ALTER_TABLE_statement$1$5$1         =  epsilon | CONSTRAINT 
            ALTER_TABLE_statement$1$6           =  *ALTER_TABLE_statement$1$6$1 CHECK | NOCHECK 
            ALTER_TABLE_statement$1$6$1         =  epsilon | WITH CHECK | WITH NOCHECK 
            ALTER_TABLE_statement$1$7           =  ALL | *ALTER_TABLE_statement$1$7$1 
            ALTER_TABLE_statement$1$7$1         =  *constraint_name | *ALTER_TABLE_statement$1$7$1 $',' *constraint_name 
            ALTER_TABLE_statement$1$8           =  ENABLE | DISABLE 
            ALTER_TABLE_statement$1$9           =  ALL | *ALTER_TABLE_statement$1$9$1 
            ALTER_TABLE_statement$1$9$1         =  *trigger_name | *ALTER_TABLE_statement$1$9$1 $',' *trigger_name 
            alter_table_column_definition       =  *column_name *data_type *alter_table_column_definition$1 
            alter_table_column_definition$1     =  epsilon | *alter_table_column_definition$1 *alter_table_column_definition$1$0 
            alter_table_column_definition$1$0   =  DEFAULT *constant_expression *alter_table_column_definition$1$1
+                                               |  IDENTITY *alter_table_column_definition$1$2
+                                               |  ROWGUIDCOL
+                                               |  *COLLATE_clause
+                                               |  *column_constraint 
            alter_table_column_definition$1$1   =  epsilon | WITH VALUES 
            alter_table_column_definition$1$2   =  epsilon | $'(' *seed $',' *increment $')' *alter_table_column_definition$1$2$1 
            alter_table_column_definition$1$2$1 =  epsilon | NOT FOR REPLICATION 
            column_constraint                   =  *column_constraint$1 *column_constraint$2 
            column_constraint$1                 =  epsilon | CONSTRAINT *constraint_name 
            column_constraint$2                 =  NULL
+                                               |  NOT NULL
+                                               |  *column_constraint$2$1 *column_constraint$2$2 *column_constraint$2$3 *column_constraint$2$4
+                                               |  *column_constraint$2$5
+                                                  REFERENCES
+                                                  *ref_table
+                                                  *column_constraint$2$6
+                                                  *column_constraint$2$7
+                                                  *column_constraint$2$8
+                                                  *column_constraint$2$9
+                                               |  CHECK *column_constraint$2$10 $'(' *logical_expression $')' 
            column_constraint$2$1               =  PRIMARY KEY | UNIQUE 
            column_constraint$2$2               =  epsilon | CLUSTERED | NONCLUSTERED 
            column_constraint$2$3               =  epsilon | WITH FILLFACTOR $'=' *fillfactor 
            column_constraint$2$4               =  epsilon | ON *column_constraint$2$4$1 
            column_constraint$2$4$1             =  *filegroup | DEFAULT 
            column_constraint$2$5               =  epsilon | FOREIGN KEY 
            column_constraint$2$6               =  epsilon | $'(' *ref_column $')' 
            column_constraint$2$7               =  epsilon | ON DELETE *column_constraint$2$7$1 
            column_constraint$2$7$1             =  CASCADE | NO ACTION 
            column_constraint$2$8               =  epsilon | ON UPDATE *column_constraint$2$8$1 
            column_constraint$2$8$1             =  CASCADE | NO ACTION 
            column_constraint$2$9               =  epsilon | NOT FOR REPLICATION 
            column_constraint$2$10              =  epsilon | NOT FOR REPLICATION 
            alter_table_constraint              =  *alter_table_constraint$1 *alter_table_constraint$2 
            alter_table_constraint$1            =  epsilon | CONSTRAINT *constraint_name 
            alter_table_constraint$2            =  *alter_table_constraint$2$1
+                                               |  FOREIGN
+                                                  KEY
+                                                  *alter_table_constraint$2$2
+                                                  REFERENCES
+                                                  *ref_table
+                                                  *alter_table_constraint$2$3
+                                                  *alter_table_constraint$2$4
+                                                  *alter_table_constraint$2$5
+                                                  *alter_table_constraint$2$6
+                                               |  DEFAULT *constant_expression *alter_table_constraint$2$7 *alter_table_constraint$2$8
+                                               |  CHECK *alter_table_constraint$2$9 $'(' *search_conditions $')' 
            alter_table_constraint$2$1          =  epsilon
+                                               |  *alter_table_constraint$2$1$1
+                                                  *alter_table_constraint$2$1$2
+                                                  $'('
+                                                  *alter_table_constraint$2$1$3
+                                                  $')'
+                                                  *alter_table_constraint$2$1$4
+                                                  *alter_table_constraint$2$1$5 
            alter_table_constraint$2$1$1        =  PRIMARY KEY | UNIQUE 
            alter_table_constraint$2$1$2        =  epsilon | CLUSTERED | NONCLUSTERED 
            alter_table_constraint$2$1$3        =  *column_name | *alter_table_constraint$2$1$3 $',' *column_name 
            alter_table_constraint$2$1$4        =  epsilon | WITH FILLFACTOR $'=' *fillfactor 
            alter_table_constraint$2$1$5        =  epsilon | ON *alter_table_constraint$2$1$5$1 
            alter_table_constraint$2$1$5$1      =  *filegroup | DEFAULT 
            alter_table_constraint$2$2          =  epsilon | $'(' *alter_table_constraint$2$2$1 $')' 
            alter_table_constraint$2$2$1        =  *column_name | *alter_table_constraint$2$2$1 $',' *column_name 
            alter_table_constraint$2$3          =  epsilon | $'(' *alter_table_constraint$2$3$1 $')' 
            alter_table_constraint$2$3$1        =  *ref_column | *alter_table_constraint$2$3$1 $',' *ref_column 
            alter_table_constraint$2$4          =  epsilon | ON DELETE *alter_table_constraint$2$4$1 
            alter_table_constraint$2$4$1        =  CASCADE | NO ACTION 
            alter_table_constraint$2$5          =  epsilon | ON UPDATE *alter_table_constraint$2$5$1 
            alter_table_constraint$2$5$1        =  CASCADE | NO ACTION 
            alter_table_constraint$2$6          =  epsilon | NOT FOR REPLICATION 
            alter_table_constraint$2$7          =  epsilon | FOR *column_name 
            alter_table_constraint$2$8          =  epsilon | WITH VALUES 
            alter_table_constraint$2$9          =  epsilon | NOT FOR REPLICATION 
            ALTER_TRIGGER_statement             =  ALTER TRIGGER *trigger_name ON *table_or_view *ALTER_TRIGGER_statement$1 *ALTER_TRIGGER_statement$2 
            ALTER_TRIGGER_statement$1           =  epsilon | WITH ENCRYPTION 
            ALTER_TRIGGER_statement$2           =  *ALTER_TRIGGER_statement$2$1
+                                                  *ALTER_TRIGGER_statement$2$2
+                                                  *ALTER_TRIGGER_statement$2$3
+                                                  *ALTER_TRIGGER_statement$2$4
+                                                  *ALTER_TRIGGER_statement$2$5
+                                                  *ALTER_TRIGGER_statement$2$6
+                                                  *ALTER_TRIGGER_statement$2$7
+                                                  AS
+                                                  *ALTER_TRIGGER_statement$2$8
+                                               |  *ALTER_TRIGGER_statement$2$9
+                                                  *ALTER_TRIGGER_statement$2$10
+                                                  *ALTER_TRIGGER_statement$2$11
+                                                  *ALTER_TRIGGER_statement$2$12
+                                                  *ALTER_TRIGGER_statement$2$13
+                                                  AS
+                                                  *ALTER_TRIGGER_statement$2$14
+                                                  *ALTER_TRIGGER_statement$2$15 
            ALTER_TRIGGER_statement$2$1         =  FOR | AFTER | INSTEAD OF 
            ALTER_TRIGGER_statement$2$2         =  epsilon | DELETE 
            ALTER_TRIGGER_statement$2$3         =  epsilon | $',' 
            ALTER_TRIGGER_statement$2$4         =  epsilon | INSERT 
            ALTER_TRIGGER_statement$2$5         =  epsilon | $',' 
            ALTER_TRIGGER_statement$2$6         =  epsilon | UPDATE 
            ALTER_TRIGGER_statement$2$7         =  epsilon | NOT FOR REPLICATION 
            ALTER_TRIGGER_statement$2$8         =  *ALTER_TRIGGER_statement$2$8$0 | *ALTER_TRIGGER_statement$2$8 *ALTER_TRIGGER_statement$2$8$0 
            ALTER_TRIGGER_statement$2$8$0       =  *control_of_flow_statement | *sql_statement 
            ALTER_TRIGGER_statement$2$9         =  FOR | AFTER | INSTEAD OF 
            ALTER_TRIGGER_statement$2$10        =  epsilon | INSERT 
            ALTER_TRIGGER_statement$2$11        =  epsilon | $',' 
            ALTER_TRIGGER_statement$2$12        =  epsilon | UPDATE 
            ALTER_TRIGGER_statement$2$13        =  epsilon | NOT FOR REPLICATION 
            ALTER_TRIGGER_statement$2$14        =  IF UPDATE $'(' *column_name $')' *ALTER_TRIGGER_statement$2$14$1
+                                               |  IF
+                                                  $'('
+                                                  COLUMNS_UPDATED
+                                                  $'('
+                                                  $')'
+                                                  *bitwise_operator
+                                                  *updated_bitmask
+                                                  $')'
+                                                  *comparison_operator
+                                                  *ALTER_TRIGGER_statement$2$14$2 
            ALTER_TRIGGER_statement$2$14$1      =  epsilon | *ALTER_TRIGGER_statement$2$14$1 *ALTER_TRIGGER_statement$2$14$1$0 
            ALTER_TRIGGER_statement$2$14$1$0    =  *ALTER_TRIGGER_statement$2$14$1$1 UPDATE $'(' *column_name $')' 
            ALTER_TRIGGER_statement$2$14$1$1    =  AND | OR 
            ALTER_TRIGGER_statement$2$14$2      =  *column_bitmask | *ALTER_TRIGGER_statement$2$14$2 *column_bitmask 
            ALTER_TRIGGER_statement$2$15        =  *ALTER_TRIGGER_statement$2$15$0 | *ALTER_TRIGGER_statement$2$15 *ALTER_TRIGGER_statement$2$15$0 
            ALTER_TRIGGER_statement$2$15$0      =  *control_of_flow_statement | *sql_statement 
            ALTER_VIEW_statement                =  ALTER VIEW *view *ALTER_VIEW_statement$1 *ALTER_VIEW_statement$2 AS *select_statement *ALTER_VIEW_statement$3 
            ALTER_VIEW_statement$1              =  epsilon | $'(' *ALTER_VIEW_statement$1$1 $')' 
            ALTER_VIEW_statement$1$1            =  *column_name | *ALTER_VIEW_statement$1$1 $',' *column_name 
            ALTER_VIEW_statement$2              =  epsilon | WITH *ALTER_VIEW_statement$2$1 
            ALTER_VIEW_statement$2$1            =  *view_attribute | *ALTER_VIEW_statement$2$1 $',' *view_attribute 
            ALTER_VIEW_statement$3              =  epsilon | WITH CHECK OPTION 
            view_attribute                      =  ENCRYPTION | SCHEMABINDING | VIEW_METADATA 
            BACKUP_statement                    =  BACKUP *BACKUP_statement$1 
            BACKUP_statement$1                  =  DATABASE *BACKUP_statement$1$1 TO *BACKUP_statement$1$2 *BACKUP_statement$1$3
+                                               |  DATABASE *BACKUP_statement$1$4 *BACKUP_statement$1$5 TO *BACKUP_statement$1$6 *BACKUP_statement$1$7
+                                               |  LOG *BACKUP_statement$1$8 TO *BACKUP_statement$1$9 *BACKUP_statement$1$10
+                                               |  LOG *BACKUP_statement$1$11 *BACKUP_statement$1$12
+                                               |  *BACKUP_statement$1$13 *BACKUP_statement$1$14 *BACKUP_statement$1$15 
            BACKUP_statement$1$1                =  *database_name | *database_name_var 
            BACKUP_statement$1$2                =  *backup_device | *BACKUP_statement$1$2 $',' *backup_device 
            BACKUP_statement$1$3                =  epsilon
+                                               |  WITH
+                                                  *BACKUP_statement$1$3$1
+                                                  *BACKUP_statement$1$3$2
+                                                  *BACKUP_statement$1$3$3
+                                                  *BACKUP_statement$1$3$4
+                                                  *BACKUP_statement$1$3$5
+                                                  *BACKUP_statement$1$3$6
+                                                  *BACKUP_statement$1$3$7
+                                                  *BACKUP_statement$1$3$8
+                                                  *BACKUP_statement$1$3$9
+                                                  *BACKUP_statement$1$3$10
+                                                  *BACKUP_statement$1$3$11
+                                                  *BACKUP_statement$1$3$12
+                                                  *BACKUP_statement$1$3$13
+                                                  *BACKUP_statement$1$3$14
+                                                  *BACKUP_statement$1$3$15
+                                                  *BACKUP_statement$1$3$16 
            BACKUP_statement$1$3$1              =  epsilon | BLOCKSIZE $'=' *BACKUP_statement$1$3$1$1 
            BACKUP_statement$1$3$1$1            =  *blocksize | *blocksize_variable 
            BACKUP_statement$1$3$2              =  epsilon | *BACKUP_statement$1$3$2$1 DESCRIPTION $'=' *BACKUP_statement$1$3$2$2 
            BACKUP_statement$1$3$2$1            =  epsilon | $',' 
            BACKUP_statement$1$3$2$2            =  *text | *text_variable 
            BACKUP_statement$1$3$3              =  epsilon | *BACKUP_statement$1$3$3$1 DIFFERENTIAL 
            BACKUP_statement$1$3$3$1            =  epsilon | $',' 
            BACKUP_statement$1$3$4              =  epsilon
+                                               |  *BACKUP_statement$1$3$4$1 EXPIREDATE $'=' *BACKUP_statement$1$3$4$2
+                                               |  RETAINDAYS $'=' *BACKUP_statement$1$3$4$3 
            BACKUP_statement$1$3$4$1            =  epsilon | $',' 
            BACKUP_statement$1$3$4$2            =  *date | *date_var 
            BACKUP_statement$1$3$4$3            =  *days | *days_var 
            BACKUP_statement$1$3$5              =  epsilon | *BACKUP_statement$1$3$5$1 PASSWORD $'=' *BACKUP_statement$1$3$5$2 
            BACKUP_statement$1$3$5$1            =  epsilon | $',' 
            BACKUP_statement$1$3$5$2            =  *password | *password_variable 
            BACKUP_statement$1$3$6              =  epsilon | *BACKUP_statement$1$3$6$1 FORMAT | NOFORMAT 
            BACKUP_statement$1$3$6$1            =  epsilon | $',' 
            BACKUP_statement$1$3$7              =  epsilon | *BACKUP_statement$1$3$7$1 *BACKUP_statement$1$3$7$2 
            BACKUP_statement$1$3$7$1            =  epsilon | $',' 
            BACKUP_statement$1$3$7$2            =  INIT | NOINIT 
            BACKUP_statement$1$3$8              =  epsilon | *BACKUP_statement$1$3$8$1 MEDIADESCRIPTION $'=' *BACKUP_statement$1$3$8$2 
            BACKUP_statement$1$3$8$1            =  epsilon | $',' 
            BACKUP_statement$1$3$8$2            =  *text | *text_variable 
            BACKUP_statement$1$3$9              =  epsilon | *BACKUP_statement$1$3$9$1 MEDIANAME $'=' *BACKUP_statement$1$3$9$2 
            BACKUP_statement$1$3$9$1            =  epsilon | $',' 
            BACKUP_statement$1$3$9$2            =  *media_name | *media_name_variable 
            BACKUP_statement$1$3$10             =  epsilon | *BACKUP_statement$1$3$10$1 MEDIAPASSWORD $'=' *BACKUP_statement$1$3$10$2 
            BACKUP_statement$1$3$10$1           =  epsilon | $',' 
            BACKUP_statement$1$3$10$2           =  *mediapassword | *mediapassword_variable 
            BACKUP_statement$1$3$11             =  epsilon | *BACKUP_statement$1$3$11$1 NAME $'=' *BACKUP_statement$1$3$11$2 
            BACKUP_statement$1$3$11$1           =  epsilon | $',' 
            BACKUP_statement$1$3$11$2           =  *backup_set_name | *backup_set_name_var 
            BACKUP_statement$1$3$12             =  epsilon | *BACKUP_statement$1$3$12$1 *BACKUP_statement$1$3$12$2 
            BACKUP_statement$1$3$12$1           =  epsilon | $',' 
            BACKUP_statement$1$3$12$2           =  NOSKIP | SKIP 
            BACKUP_statement$1$3$13             =  epsilon | *BACKUP_statement$1$3$13$1 *BACKUP_statement$1$3$13$2 
            BACKUP_statement$1$3$13$1           =  epsilon | $',' 
            BACKUP_statement$1$3$13$2           =  NOREWIND | REWIND 
            BACKUP_statement$1$3$14             =  epsilon | *BACKUP_statement$1$3$14$1 *BACKUP_statement$1$3$14$2 
            BACKUP_statement$1$3$14$1           =  epsilon | $',' 
            BACKUP_statement$1$3$14$2           =  NOUNLOAD | UNLOAD 
            BACKUP_statement$1$3$15             =  epsilon | *BACKUP_statement$1$3$15$1 RESTART 
            BACKUP_statement$1$3$15$1           =  epsilon | $',' 
            BACKUP_statement$1$3$16             =  epsilon | *BACKUP_statement$1$3$16$1 STATS *BACKUP_statement$1$3$16$2 
            BACKUP_statement$1$3$16$1           =  epsilon | $',' 
            BACKUP_statement$1$3$16$2           =  epsilon | $'=' *percentage 
            BACKUP_statement$1$4                =  *database_name | *database_name_var 
            BACKUP_statement$1$5                =  *file_or_filegroup | *BACKUP_statement$1$5 $',' *file_or_filegroup 
            BACKUP_statement$1$6                =  *backup_device | *BACKUP_statement$1$6 $',' *backup_device 
            BACKUP_statement$1$7                =  epsilon
+                                               |  WITH
+                                                  *BACKUP_statement$1$7$1
+                                                  *BACKUP_statement$1$7$2
+                                                  *BACKUP_statement$1$7$3
+                                                  *BACKUP_statement$1$7$4
+                                                  *BACKUP_statement$1$7$5
+                                                  *BACKUP_statement$1$7$6
+                                                  *BACKUP_statement$1$7$7
+                                                  *BACKUP_statement$1$7$8
+                                                  *BACKUP_statement$1$7$9
+                                                  *BACKUP_statement$1$7$10
+                                                  *BACKUP_statement$1$7$11
+                                                  *BACKUP_statement$1$7$12
+                                                  *BACKUP_statement$1$7$13
+                                                  *BACKUP_statement$1$7$14
+                                                  *BACKUP_statement$1$7$15
+                                                  *BACKUP_statement$1$7$16 
            BACKUP_statement$1$7$1              =  epsilon | BLOCKSIZE $'=' *BACKUP_statement$1$7$1$1 
            BACKUP_statement$1$7$1$1            =  *blocksize | *blocksize_variable 
            BACKUP_statement$1$7$2              =  epsilon | *BACKUP_statement$1$7$2$1 DESCRIPTION $'=' *BACKUP_statement$1$7$2$2 
            BACKUP_statement$1$7$2$1            =  epsilon | $',' 
            BACKUP_statement$1$7$2$2            =  *text | *text_variable 
            BACKUP_statement$1$7$3              =  epsilon | *BACKUP_statement$1$7$3$1 DIFFERENTIAL 
            BACKUP_statement$1$7$3$1            =  epsilon | $',' 
            BACKUP_statement$1$7$4              =  epsilon
+                                               |  *BACKUP_statement$1$7$4$1 EXPIREDATE $'=' *BACKUP_statement$1$7$4$2
+                                               |  RETAINDAYS $'=' *BACKUP_statement$1$7$4$3 
            BACKUP_statement$1$7$4$1            =  epsilon | $',' 
            BACKUP_statement$1$7$4$2            =  *date | *date_var 
            BACKUP_statement$1$7$4$3            =  *days | *days_var 
            BACKUP_statement$1$7$5              =  epsilon | *BACKUP_statement$1$7$5$1 PASSWORD $'=' *BACKUP_statement$1$7$5$2 
            BACKUP_statement$1$7$5$1            =  epsilon | $',' 
            BACKUP_statement$1$7$5$2            =  *password | *password_variable 
            BACKUP_statement$1$7$6              =  epsilon | *BACKUP_statement$1$7$6$1 FORMAT | NOFORMAT 
            BACKUP_statement$1$7$6$1            =  epsilon | $',' 
            BACKUP_statement$1$7$7              =  epsilon | *BACKUP_statement$1$7$7$1 *BACKUP_statement$1$7$7$2 
            BACKUP_statement$1$7$7$1            =  epsilon | $',' 
            BACKUP_statement$1$7$7$2            =  INIT | NOINIT 
            BACKUP_statement$1$7$8              =  epsilon | *BACKUP_statement$1$7$8$1 MEDIADESCRIPTION $'=' *BACKUP_statement$1$7$8$2 
            BACKUP_statement$1$7$8$1            =  epsilon | $',' 
            BACKUP_statement$1$7$8$2            =  *text | *text_variable 
            BACKUP_statement$1$7$9              =  epsilon | *BACKUP_statement$1$7$9$1 MEDIANAME $'=' *BACKUP_statement$1$7$9$2 
            BACKUP_statement$1$7$9$1            =  epsilon | $',' 
            BACKUP_statement$1$7$9$2            =  *media_name | *media_name_variable 
            BACKUP_statement$1$7$10             =  epsilon | *BACKUP_statement$1$7$10$1 MEDIAPASSWORD $'=' *BACKUP_statement$1$7$10$2 
            BACKUP_statement$1$7$10$1           =  epsilon | $',' 
            BACKUP_statement$1$7$10$2           =  *mediapassword | *mediapassword_variable 
            BACKUP_statement$1$7$11             =  epsilon | *BACKUP_statement$1$7$11$1 NAME $'=' *BACKUP_statement$1$7$11$2 
            BACKUP_statement$1$7$11$1           =  epsilon | $',' 
            BACKUP_statement$1$7$11$2           =  *backup_set_name | *backup_set_name_var 
            BACKUP_statement$1$7$12             =  epsilon | *BACKUP_statement$1$7$12$1 *BACKUP_statement$1$7$12$2 
            BACKUP_statement$1$7$12$1           =  epsilon | $',' 
            BACKUP_statement$1$7$12$2           =  NOSKIP | SKIP 
            BACKUP_statement$1$7$13             =  epsilon | *BACKUP_statement$1$7$13$1 *BACKUP_statement$1$7$13$2 
            BACKUP_statement$1$7$13$1           =  epsilon | $',' 
            BACKUP_statement$1$7$13$2           =  NOREWIND | REWIND 
            BACKUP_statement$1$7$14             =  epsilon | *BACKUP_statement$1$7$14$1 *BACKUP_statement$1$7$14$2 
            BACKUP_statement$1$7$14$1           =  epsilon | $',' 
            BACKUP_statement$1$7$14$2           =  NOUNLOAD | UNLOAD 
            BACKUP_statement$1$7$15             =  epsilon | *BACKUP_statement$1$7$15$1 RESTART 
            BACKUP_statement$1$7$15$1           =  epsilon | $',' 
            BACKUP_statement$1$7$16             =  epsilon | *BACKUP_statement$1$7$16$1 STATS *BACKUP_statement$1$7$16$2 
            BACKUP_statement$1$7$16$1           =  epsilon | $',' 
            BACKUP_statement$1$7$16$2           =  epsilon | $'=' *percentage 
            BACKUP_statement$1$8                =  *database_name | *database_name_var 
            BACKUP_statement$1$9                =  *backup_device | *BACKUP_statement$1$9 $',' *backup_device 
            BACKUP_statement$1$10               =  epsilon
+                                               |  WITH
+                                                  *BACKUP_statement$1$10$1
+                                                  *BACKUP_statement$1$10$2
+                                                  *BACKUP_statement$1$10$3
+                                                  *BACKUP_statement$1$10$4
+                                                  *BACKUP_statement$1$10$5
+                                                  *BACKUP_statement$1$10$6
+                                                  *BACKUP_statement$1$10$7
+                                                  *BACKUP_statement$1$10$8
+                                                  *BACKUP_statement$1$10$9
+                                                  *BACKUP_statement$1$10$10
+                                                  *BACKUP_statement$1$10$11
+                                                  *BACKUP_statement$1$10$12
+                                                  *BACKUP_statement$1$10$13
+                                                  *BACKUP_statement$1$10$14
+                                                  *BACKUP_statement$1$10$15
+                                                  *BACKUP_statement$1$10$16
+                                                  *BACKUP_statement$1$10$17 
            BACKUP_statement$1$10$1             =  epsilon | BLOCKSIZE $'=' *BACKUP_statement$1$10$1$1 
            BACKUP_statement$1$10$1$1           =  *blocksize | *blocksize_variable 
            BACKUP_statement$1$10$2             =  epsilon | *BACKUP_statement$1$10$2$1 DESCRIPTION $'=' *BACKUP_statement$1$10$2$2 
            BACKUP_statement$1$10$2$1           =  epsilon | $',' 
            BACKUP_statement$1$10$2$2           =  *text | *text_variable 
            BACKUP_statement$1$10$3             =  epsilon
+                                               |  *BACKUP_statement$1$10$3$1 EXPIREDATE $'=' *BACKUP_statement$1$10$3$2
+                                               |  RETAINDAYS $'=' *BACKUP_statement$1$10$3$3 
            BACKUP_statement$1$10$3$1           =  epsilon | $',' 
            BACKUP_statement$1$10$3$2           =  *date | *date_var 
            BACKUP_statement$1$10$3$3           =  *days | *days_var 
            BACKUP_statement$1$10$4             =  epsilon | *BACKUP_statement$1$10$4$1 PASSWORD $'=' *BACKUP_statement$1$10$4$2 
            BACKUP_statement$1$10$4$1           =  epsilon | $',' 
            BACKUP_statement$1$10$4$2           =  *password | *password_variable 
            BACKUP_statement$1$10$5             =  epsilon | *BACKUP_statement$1$10$5$1 FORMAT | NOFORMAT 
            BACKUP_statement$1$10$5$1           =  epsilon | $',' 
            BACKUP_statement$1$10$6             =  epsilon | *BACKUP_statement$1$10$6$1 *BACKUP_statement$1$10$6$2 
            BACKUP_statement$1$10$6$1           =  epsilon | $',' 
            BACKUP_statement$1$10$6$2           =  INIT | NOINIT 
            BACKUP_statement$1$10$7             =  epsilon | *BACKUP_statement$1$10$7$1 MEDIADESCRIPTION $'=' *BACKUP_statement$1$10$7$2 
            BACKUP_statement$1$10$7$1           =  epsilon | $',' 
            BACKUP_statement$1$10$7$2           =  *text | *text_variable 
            BACKUP_statement$1$10$8             =  epsilon | *BACKUP_statement$1$10$8$1 MEDIANAME $'=' *BACKUP_statement$1$10$8$2 
            BACKUP_statement$1$10$8$1           =  epsilon | $',' 
            BACKUP_statement$1$10$8$2           =  *media_name | *media_name_variable 
            BACKUP_statement$1$10$9             =  epsilon | *BACKUP_statement$1$10$9$1 MEDIAPASSWORD $'=' *BACKUP_statement$1$10$9$2 
            BACKUP_statement$1$10$9$1           =  epsilon | $',' 
            BACKUP_statement$1$10$9$2           =  *mediapassword | *mediapassword_variable 
            BACKUP_statement$1$10$10            =  epsilon | *BACKUP_statement$1$10$10$1 NAME $'=' *BACKUP_statement$1$10$10$2 
            BACKUP_statement$1$10$10$1          =  epsilon | $',' 
            BACKUP_statement$1$10$10$2          =  *backup_set_name | *backup_set_name_var 
            BACKUP_statement$1$10$11            =  epsilon | *BACKUP_statement$1$10$11$1 NO_TRUNCATE 
            BACKUP_statement$1$10$11$1          =  epsilon | $',' 
            BACKUP_statement$1$10$12            =  epsilon | *BACKUP_statement$1$10$12$1 *BACKUP_statement$1$10$12$2 
            BACKUP_statement$1$10$12$1          =  epsilon | $',' 
            BACKUP_statement$1$10$12$2          =  NORECOVERY | STANDBY $'=' *BACKUP_statement$1$10$12$2$1 
            BACKUP_statement$1$10$12$2$1        =  *undo_file_name | *undo_file_name_var 
            BACKUP_statement$1$10$13            =  epsilon | *BACKUP_statement$1$10$13$1 *BACKUP_statement$1$10$13$2 
            BACKUP_statement$1$10$13$1          =  epsilon | $',' 
            BACKUP_statement$1$10$13$2          =  NOREWIND | REWIND 
            BACKUP_statement$1$10$14            =  epsilon | *BACKUP_statement$1$10$14$1 *BACKUP_statement$1$10$14$2 
            BACKUP_statement$1$10$14$1          =  epsilon | $',' 
            BACKUP_statement$1$10$14$2          =  NOSKIP | SKIP 
            BACKUP_statement$1$10$15            =  epsilon | *BACKUP_statement$1$10$15$1 *BACKUP_statement$1$10$15$2 
            BACKUP_statement$1$10$15$1          =  epsilon | $',' 
            BACKUP_statement$1$10$15$2          =  NOUNLOAD | UNLOAD 
            BACKUP_statement$1$10$16            =  epsilon | *BACKUP_statement$1$10$16$1 RESTART 
            BACKUP_statement$1$10$16$1          =  epsilon | $',' 
            BACKUP_statement$1$10$17            =  epsilon | *BACKUP_statement$1$10$17$1 STATS *BACKUP_statement$1$10$17$2 
            BACKUP_statement$1$10$17$1          =  epsilon | $',' 
            BACKUP_statement$1$10$17$2          =  epsilon | $'=' *percentage 
            BACKUP_statement$1$11               =  *database_name | *database_name_var 
            BACKUP_statement$1$12               =  epsilon | WITH *BACKUP_statement$1$12$1 
            BACKUP_statement$1$12$1             =  NO_LOG | TRUNCATE_ONLY 
            BACKUP_statement$1$13               =  TRAN | TRANSACTION 
            BACKUP_statement$1$14               =  *transaction_name | *tran_name_variable 
            BACKUP_statement$1$15               =  epsilon | WITH *BACKUP_statement$1$15$1 
            BACKUP_statement$1$15$1             =  NO_LOG | TRUNCATE_ONLY 
            backup_device                       =  *logical_backup_device_name | *logical_backup_device_name_var | *backup_device$1 $'=' *backup_device$2 
            backup_device$1                     =  DISK | TAPE 
            backup_device$2                     =  *physical_backup_device_name | *physical_backup_device_name_var 
            file_or_filegroup                   =  FILE $'=' *file_or_filegroup$1 | FILEGROUP $'=' *file_or_filegroup$2 
            file_or_filegroup$1                 =  *logical_file_name | *logical_file_name_var 
            file_or_filegroup$2                 =  *logical_filegroup_name | *logical_filegroup_name_var 
            BEGIN_DISTRIBUTED_TRANSACTION_statement = BEGIN DISTRIBUTED *BEGIN_DISTRIBUTED_TRANSACTION_statement$1 *BEGIN_DISTRIBUTED_TRANSACTION_statement$2 
            BEGIN_DISTRIBUTED_TRANSACTION_statement$1 = TRAN | TRANSACTION 
            BEGIN_DISTRIBUTED_TRANSACTION_statement$2 = epsilon | *transaction_name | *tran_name_variable 
            BEGIN_TRANSACTION_statement         =  BEGIN *BEGIN_TRANSACTION_statement$1 *BEGIN_TRANSACTION_statement$2 
            BEGIN_TRANSACTION_statement$1       =  TRAN | TRANSACTION 
            BEGIN_TRANSACTION_statement$2       =  epsilon | *transaction_name | *tran_name_variable *BEGIN_TRANSACTION_statement$2$1 
            BEGIN_TRANSACTION_statement$2$1     =  epsilon | WITH MARK *BEGIN_TRANSACTION_statement$2$1$1 
            BEGIN_TRANSACTION_statement$2$1$1   =  epsilon | *description 
            BULK_INSERT_statement               =  BULK INSERT *table FROM *data_file *BULK_INSERT_statement$1 
            BULK_INSERT_statement$1             =  epsilon
+                                               |  WITH
+                                                  $'('
+                                                  *BULK_INSERT_statement$1$1
+                                                  *BULK_INSERT_statement$1$2
+                                                  *BULK_INSERT_statement$1$3
+                                                  *BULK_INSERT_statement$1$4
+                                                  *BULK_INSERT_statement$1$5
+                                                  *BULK_INSERT_statement$1$6
+                                                  *BULK_INSERT_statement$1$7
+                                                  *BULK_INSERT_statement$1$8
+                                                  *BULK_INSERT_statement$1$9
+                                                  *BULK_INSERT_statement$1$10
+                                                  *BULK_INSERT_statement$1$11
+                                                  *BULK_INSERT_statement$1$12
+                                                  *BULK_INSERT_statement$1$13
+                                                  *BULK_INSERT_statement$1$14
+                                                  *BULK_INSERT_statement$1$15
+                                                  *BULK_INSERT_statement$1$16
+                                                  *BULK_INSERT_statement$1$17
+                                                  $')' 
            BULK_INSERT_statement$1$1           =  epsilon | BATCHSIZE *BULK_INSERT_statement$1$1$1 
            BULK_INSERT_statement$1$1$1         =  epsilon | $'=' *batch_size 
            BULK_INSERT_statement$1$2           =  epsilon | *BULK_INSERT_statement$1$2$1 CHECK_CONSTRAINTS 
            BULK_INSERT_statement$1$2$1         =  epsilon | $',' 
            BULK_INSERT_statement$1$3           =  epsilon | *BULK_INSERT_statement$1$3$1 CODEPAGE *BULK_INSERT_statement$1$3$2 
            BULK_INSERT_statement$1$3$1         =  epsilon | $',' 
            BULK_INSERT_statement$1$3$2         =  epsilon | $'=' ACP | OEM | RAW | *code_page 
            BULK_INSERT_statement$1$4           =  epsilon | *BULK_INSERT_statement$1$4$1 DATAFILETYPE *BULK_INSERT_statement$1$4$2 
            BULK_INSERT_statement$1$4$1         =  epsilon | $',' 
            BULK_INSERT_statement$1$4$2         =  epsilon | $'=' *BULK_INSERT_statement$1$4$2$1 
            BULK_INSERT_statement$1$4$2$1       =  *char | *native | *widechar | *widenative 
            BULK_INSERT_statement$1$5           =  epsilon | *BULK_INSERT_statement$1$5$1 FIELDTERMINATOR *BULK_INSERT_statement$1$5$2 
            BULK_INSERT_statement$1$5$1         =  epsilon | $',' 
            BULK_INSERT_statement$1$5$2         =  epsilon | $'=' *field_terminator 
            BULK_INSERT_statement$1$6           =  epsilon | *BULK_INSERT_statement$1$6$1 FIRSTROW *BULK_INSERT_statement$1$6$2 
            BULK_INSERT_statement$1$6$1         =  epsilon | $',' 
            BULK_INSERT_statement$1$6$2         =  epsilon | $'=' *first_row 
            BULK_INSERT_statement$1$7           =  epsilon | *BULK_INSERT_statement$1$7$1 FIRE_TRIGGERS 
            BULK_INSERT_statement$1$7$1         =  epsilon | $',' 
            BULK_INSERT_statement$1$8           =  epsilon | *BULK_INSERT_statement$1$8$1 FORMATFILE $'=' *format_file_path 
            BULK_INSERT_statement$1$8$1         =  epsilon | $',' 
            BULK_INSERT_statement$1$9           =  epsilon | *BULK_INSERT_statement$1$9$1 KEEPIDENTITY 
            BULK_INSERT_statement$1$9$1         =  epsilon | $',' 
            BULK_INSERT_statement$1$10          =  epsilon | *BULK_INSERT_statement$1$10$1 KEEPNULLS 
            BULK_INSERT_statement$1$10$1        =  epsilon | $',' 
            BULK_INSERT_statement$1$11          =  epsilon | *BULK_INSERT_statement$1$11$1 KILOBYTES_PER_BATCH *BULK_INSERT_statement$1$11$2 
            BULK_INSERT_statement$1$11$1        =  epsilon | $',' 
            BULK_INSERT_statement$1$11$2        =  epsilon | $'=' *kilobytes_per_batch 
            BULK_INSERT_statement$1$12          =  epsilon | *BULK_INSERT_statement$1$12$1 LASTROW *BULK_INSERT_statement$1$12$2 
            BULK_INSERT_statement$1$12$1        =  epsilon | $',' 
            BULK_INSERT_statement$1$12$2        =  epsilon | $'=' *last_row 
            BULK_INSERT_statement$1$13          =  epsilon | *BULK_INSERT_statement$1$13$1 MAXERRORS *BULK_INSERT_statement$1$13$2 
            BULK_INSERT_statement$1$13$1        =  epsilon | $',' 
            BULK_INSERT_statement$1$13$2        =  epsilon | $'=' *max_errors 
            BULK_INSERT_statement$1$14          =  epsilon | *BULK_INSERT_statement$1$14$1 ORDER $'(' *BULK_INSERT_statement$1$14$2 $')' 
            BULK_INSERT_statement$1$14$1        =  epsilon | $',' 
            BULK_INSERT_statement$1$14$2        =  *BULK_INSERT_statement$1$14$2$0 | *BULK_INSERT_statement$1$14$2 $',' *BULK_INSERT_statement$1$14$2$0 
            BULK_INSERT_statement$1$14$2$0      =  *column *BULK_INSERT_statement$1$14$2$1 
            BULK_INSERT_statement$1$14$2$1      =  epsilon | ASC | DESC 
            BULK_INSERT_statement$1$15          =  epsilon | *BULK_INSERT_statement$1$15$1 ROWS_PER_BATCH *BULK_INSERT_statement$1$15$2 
            BULK_INSERT_statement$1$15$1        =  epsilon | $',' 
            BULK_INSERT_statement$1$15$2        =  epsilon | $'=' *rows_per_batch 
            BULK_INSERT_statement$1$16          =  epsilon | *BULK_INSERT_statement$1$16$1 ROWTERMINATOR *BULK_INSERT_statement$1$16$2 
            BULK_INSERT_statement$1$16$1        =  epsilon | $',' 
            BULK_INSERT_statement$1$16$2        =  epsilon | $'=' *row_terminator 
            BULK_INSERT_statement$1$17          =  epsilon | *BULK_INSERT_statement$1$17$1 TABLOCK 
            BULK_INSERT_statement$1$17$1        =  epsilon | $',' 
            CHECKPOINT_statement                =  CHECKPOINT 
            CLOSE_statement                     =  CLOSE *CLOSE_statement$1 
            CLOSE_statement$1                   =  *CLOSE_statement$1$1 *cursor_name | *cursor_variable_name 
            CLOSE_statement$1$1                 =  epsilon | GLOBAL 
            COLLATE_clause                      =  COLLATE *COLLATE_clause$1 
            COLLATE_clause$1                    =  *collation_name | DATABASE_DEFAULT 
            collation_name                      =  *identifier | *string_literal 
            COMMIT_TRANSACTION_statement        =  COMMIT *COMMIT_TRANSACTION_statement$1 *COMMIT_TRANSACTION_statement$2 
            COMMIT_TRANSACTION_statement$1      =  TRAN | TRANSACTION 
            COMMIT_TRANSACTION_statement$2      =  epsilon | *transaction_name | *tran_name_variable 
            COMMIT_statement                    =  COMMIT *COMMIT_statement$1 
            COMMIT_statement$1                  =  epsilon | WORK 
            CONTAINS_clause                     =  CONTAINS $'(' *CONTAINS_clause$1 $',' *string_literal $')' 
            CONTAINS_clause$1                   =  *column | $'*' 
            CONTAINSTABLE_clause                =  CONTAINSTABLE $'(' *table $',' *CONTAINSTABLE_clause$1 $',' *string_literal *CONTAINSTABLE_clause$2 $')' 
            CONTAINSTABLE_clause$1              =  *column | $'*' 
            CONTAINSTABLE_clause$2              =  epsilon | $',' *top_n_by_rank 
            CREATE_DATABASE_statement           =  CREATE
+                                                  DATABASE
+                                                  *database_name
+                                                  *CREATE_DATABASE_statement$1
+                                                  *CREATE_DATABASE_statement$2
+                                                  *CREATE_DATABASE_statement$3
+                                                  *CREATE_DATABASE_statement$4 
            CREATE_DATABASE_statement$1         =  epsilon | ON *CREATE_DATABASE_statement$1$1 *CREATE_DATABASE_statement$1$2 
            CREATE_DATABASE_statement$1$1       =  epsilon | *filespec % $',' 
            CREATE_DATABASE_statement$1$2       =  epsilon | $',' *CREATE_DATABASE_statement$1$2$1 
            CREATE_DATABASE_statement$1$2$1     =  *filegroup | *CREATE_DATABASE_statement$1$2$1 $',' *filegroup 
            CREATE_DATABASE_statement$2         =  epsilon | LOG ON *CREATE_DATABASE_statement$2$1 
            CREATE_DATABASE_statement$2$1       =  *filespec | *CREATE_DATABASE_statement$2$1 $',' *filespec 
            CREATE_DATABASE_statement$3         =  epsilon | COLLATE *collation_name 
            CREATE_DATABASE_statement$4         =  epsilon | FOR LOAD | FOR ATTACH 
            filespec                            =  *filespec$1 $'(' *filespec$2 FILENAME $'=' *os_file_name *filespec$3 *filespec$4 *filespec$5 $')'
+                                               |  DEFAULT $'=' *integer_literal 
            filespec$1                          =  epsilon | PRIMARY 
            filespec$2                          =  epsilon | NAME $'=' *logical_file_name $',' 
            filespec$3                          =  epsilon | $',' SIZE $'=' *size 
            filespec$4                          =  epsilon | $',' MAXSIZE $'=' *filespec$4$1 
            filespec$4$1                        =  *max_size | UNLIMITED 
            filespec$5                          =  epsilon | $',' FILEGROWTH $'=' *growth_increment 
            filegroup                           =  FILEGROUP *filegroup_name *filegroup$1 
            filegroup$1                         =  *filespec | *filegroup$1 $',' *filespec 
            CREATE_DEFAULT_statement            =  CREATE DEFAULT *default AS *constant_expression 
            CREATE_FUNCTION_statement           =  CREATE FUNCTION *function $'(' *CREATE_FUNCTION_statement$1 $')' RETURNS *CREATE_FUNCTION_statement$2 
            CREATE_FUNCTION_statement$1         =  epsilon | (*parameter_name !AS *scalar_parameter_data_type !($'=' *constant_expression)) % $',' 
            CREATE_FUNCTION_statement$2         =  *scalar_return_data_type
+                                                  *CREATE_FUNCTION_statement$2$1
+                                                  *CREATE_FUNCTION_statement$2$2
+                                                  BEGIN
+                                                  *function_body
+                                                  RETURN
+                                                  *scalar_expression
+                                                  END
+                                               |  TABLE *CREATE_FUNCTION_statement$2$3 *CREATE_FUNCTION_statement$2$4 RETURN *CREATE_FUNCTION_statement$2$5
+                                               |  *return_variable
+                                                  TABLE
+                                                  $'('
+                                                  *CREATE_FUNCTION_statement$2$6
+                                                  $')'
+                                                  *CREATE_FUNCTION_statement$2$7
+                                                  *CREATE_FUNCTION_statement$2$8
+                                                  BEGIN
+                                                  *function_body
+                                                  RETURN
+                                                  END 
            CREATE_FUNCTION_statement$2$1       =  epsilon | WITH *function_option *CREATE_FUNCTION_statement$2$1$1 
            CREATE_FUNCTION_statement$2$1$1     =  epsilon | #(!$',' *function_option) 
            CREATE_FUNCTION_statement$2$2       =  epsilon | AS 
            CREATE_FUNCTION_statement$2$3       =  epsilon | WITH *function_option *CREATE_FUNCTION_statement$2$3$1 
            CREATE_FUNCTION_statement$2$3$1     =  epsilon | #(!$',' *function_option) 
            CREATE_FUNCTION_statement$2$4       =  epsilon | AS 
            CREATE_FUNCTION_statement$2$5       =  $'(' *select_stmt $')' | *select_stmt 
            CREATE_FUNCTION_statement$2$6       =  *CREATE_FUNCTION_statement$2$6$0 | *CREATE_FUNCTION_statement$2$6 $',' *CREATE_FUNCTION_statement$2$6$0 
            CREATE_FUNCTION_statement$2$6$0     =  *declared_column_definition | *declared_table_constraint 
            CREATE_FUNCTION_statement$2$7       =  epsilon | WITH *function_option *CREATE_FUNCTION_statement$2$7$1 
            CREATE_FUNCTION_statement$2$7$1     =  epsilon | #(!$',' *function_option) 
            CREATE_FUNCTION_statement$2$8       =  epsilon | AS 
            CREATE_INDEX_statement              =  CREATE
+                                                  *CREATE_INDEX_statement$1
+                                                  *CREATE_INDEX_statement$2
+                                                  INDEX
+                                                  *index
+                                                  ON
+                                                  *table_or_view
+                                                  $'('
+                                                  *CREATE_INDEX_statement$3
+                                                  $')'
+                                                  *CREATE_INDEX_statement$4
+                                                  *CREATE_INDEX_statement$5 
            CREATE_INDEX_statement$1            =  epsilon | UNIQUE 
            CREATE_INDEX_statement$2            =  epsilon | CLUSTERED | NONCLUSTERED 
            CREATE_INDEX_statement$3            =  *CREATE_INDEX_statement$3$0 | *CREATE_INDEX_statement$3 $',' *CREATE_INDEX_statement$3$0 
            CREATE_INDEX_statement$3$0          =  *column *CREATE_INDEX_statement$3$1 
            CREATE_INDEX_statement$3$1          =  epsilon | ASC | DESC 
            CREATE_INDEX_statement$4            =  epsilon | WITH *CREATE_INDEX_statement$4$1 
            CREATE_INDEX_statement$4$1          =  *index_option | *CREATE_INDEX_statement$4$1 $',' *index_option 
            CREATE_INDEX_statement$5            =  epsilon | ON *filegroup 
            index_option                        =  PAD_INDEX
+                                               |  FILLFACTOR $'=' *fillfactor
+                                               |  IGNORE_DUP_KEY
+                                               |  DROP_EXISTING
+                                               |  STATISTICS_NORECOMPUTE
+                                               |  SORT_IN_TEMPDB
+                                               |  ALLOW_DUP_ROW 
            CREATE_PROCEDURE_statement          =  CREATE
+                                                  *CREATE_PROCEDURE_statement$1
+                                                  *procedure
+                                                  *CREATE_PROCEDURE_statement$2
+                                                  *CREATE_PROCEDURE_statement$3
+                                                  *CREATE_PROCEDURE_statement$4
+                                                  *CREATE_PROCEDURE_statement$5
+                                                  AS
+                                                  *CREATE_PROCEDURE_statement$6 
            CREATE_PROCEDURE_statement$1        =  PROC | PROCEDURE 
            CREATE_PROCEDURE_statement$2        =  epsilon | $';' *number 
            CREATE_PROCEDURE_statement$3        =  epsilon | $'(' *parameter_list $')' | *parameter_list 
            CREATE_PROCEDURE_statement$4        =  epsilon | WITH *CREATE_PROCEDURE_statement$4$1 
            CREATE_PROCEDURE_statement$4$1      =  RECOMPILE | ENCRYPTION | RECOMPILE $',' ENCRYPTION 
            CREATE_PROCEDURE_statement$5        =  epsilon | FOR REPLICATION 
            CREATE_PROCEDURE_statement$6        =  *Transact_SQL_statement | *CREATE_PROCEDURE_statement$6 *Transact_SQL_statement 
            parameter_list                      =  *parameter_list$0 | *parameter_list $',' *parameter_list$0 
            parameter_list$0                    =  *parameter *parameter_list$1 *data_type *parameter_list$2 *parameter_list$3 *parameter_list$4 
            parameter_list$1                    =  epsilon | AS 
            parameter_list$2                    =  epsilon | VARYING 
            parameter_list$3                    =  epsilon | $'=' *constant_expression 
            parameter_list$4                    =  epsilon | OUT | OUTPUT 
            CREATE_RULE_statement               =  CREATE RULE *rule AS *condition_expression 
            CREATE_SCHEMA_statement             =  CREATE SCHEMA AUTHORIZATION *owner_name *CREATE_SCHEMA_statement$1 
            CREATE_SCHEMA_statement$1           =  epsilon | #*schema_element 
            schema_element                      =  *table_definition | *view_definition | *grant_statement 
            CREATE_STATISTICS_statement         =  CREATE
+                                                  STATISTICS
+                                                  *statistics_name
+                                                  ON
+                                                  *table_or_view
+                                                  $'('
+                                                  *CREATE_STATISTICS_statement$1
+                                                  $')'
+                                                  *CREATE_STATISTICS_statement$2 
            CREATE_STATISTICS_statement$1       =  *column_name | *CREATE_STATISTICS_statement$1 $',' *column_name 
            CREATE_STATISTICS_statement$2       =  epsilon | WITH *CREATE_STATISTICS_statement$2$1 *CREATE_STATISTICS_statement$2$2 
            CREATE_STATISTICS_statement$2$1     =  epsilon | *CREATE_STATISTICS_statement$2$1$1 *CREATE_STATISTICS_statement$2$1$2 
            CREATE_STATISTICS_statement$2$1$1   =  epsilon | FULLSCAN | SAMPLE *number *CREATE_STATISTICS_statement$2$1$1$1 
            CREATE_STATISTICS_statement$2$1$1$1 =  PERCENT | ROWS 
            CREATE_STATISTICS_statement$2$1$2   =  epsilon | $',' 
            CREATE_STATISTICS_statement$2$2     =  epsilon | NORECOMPUTE 
            CREATE_TABLE_statement              =  CREATE
+                                                  TABLE
+                                                  *table
+                                                  $'('
+                                                  *CREATE_TABLE_statement$1
+                                                  *CREATE_TABLE_statement$2
+                                                  *CREATE_TABLE_statement$3
+                                                  $')'
+                                                  *CREATE_TABLE_statement$4
+                                                  *CREATE_TABLE_statement$5 
            CREATE_TABLE_statement$1            =  *create_table_column_definition | *column_name AS *computed_column_expression | *create_table_constraint 
            CREATE_TABLE_statement$2            =  epsilon | *CREATE_TABLE_statement$2 *CREATE_TABLE_statement$2$0 
            CREATE_TABLE_statement$2$0          =  *CREATE_TABLE_statement$2$1 *CREATE_TABLE_statement$2$2 
            CREATE_TABLE_statement$2$1          =  epsilon | $',' 
            CREATE_TABLE_statement$2$2          =  *create_table_column_definition | *column_name AS *computed_column_expression | *create_table_constraint 
            CREATE_TABLE_statement$3            =  epsilon | $',' 
            CREATE_TABLE_statement$4            =  epsilon | ON *CREATE_TABLE_statement$4$1 
            CREATE_TABLE_statement$4$1          =  *filegroup | DEFAULT 
            CREATE_TABLE_statement$5            =  epsilon | TEXTIMAGE_ON *CREATE_TABLE_statement$5$1 
            CREATE_TABLE_statement$5$1          =  *filegroup | DEFAULT 
            create_table_column_definition      =  *create_table_column_definition$1 *create_table_column_definition$2 
            create_table_column_definition$1    =  *column_name *data_type | TIMESTAMP 
            create_table_column_definition$2    =  epsilon | *create_table_column_definition$2 *create_table_column_definition$2$0 
            create_table_column_definition$2$0  =  *COLLATE_clause
+                                               |  DEFAULT *constant_expression
+                                               |  IDENTITY *create_table_column_definition$2$1
+                                               |  ROWGUIDCOL
+                                               |  *column_constraint 
            create_table_column_definition$2$1  =  epsilon | $'(' *seed $',' *increment $')' *create_table_column_definition$2$1$1 
            create_table_column_definition$2$1$1 = epsilon | NOT FOR REPLICATION 
            create_table_constraint             =  *create_table_constraint$1 *create_table_constraint$2 
            create_table_constraint$1           =  epsilon | CONSTRAINT *constraint_name 
            create_table_constraint$2           =  *create_table_constraint$2$1
+                                                  *create_table_constraint$2$2
+                                                  $'('
+                                                  *create_table_constraint$2$3
+                                                  $')'
+                                                  *create_table_constraint$2$4
+                                                  *create_table_constraint$2$5
+                                               |  FOREIGN
+                                                  KEY
+                                                  *create_table_constraint$2$6
+                                                  REFERENCES
+                                                  *ref_table
+                                                  *create_table_constraint$2$7
+                                                  *create_table_constraint$2$8
+                                                  *create_table_constraint$2$9
+                                                  *create_table_constraint$2$10
+                                               |  CHECK *create_table_constraint$2$11 $'(' *search_conditions $')' 
            create_table_constraint$2$1         =  PRIMARY KEY | UNIQUE 
            create_table_constraint$2$2         =  epsilon | CLUSTERED | NONCLUSTERED 
            create_table_constraint$2$3         =  *create_table_constraint$2$3$0 | *create_table_constraint$2$3 $',' *create_table_constraint$2$3$0 
            create_table_constraint$2$3$0       =  *column *create_table_constraint$2$3$1 
            create_table_constraint$2$3$1       =  epsilon | ASC | DESC 
            create_table_constraint$2$4         =  epsilon | WITH FILLFACTOR $'=' *fillfactor 
            create_table_constraint$2$5         =  epsilon | ON *create_table_constraint$2$5$1 
            create_table_constraint$2$5$1       =  *filegroup | DEFAULT 
            create_table_constraint$2$6         =  epsilon | $'(' *create_table_constraint$2$6$1 $')' 
            create_table_constraint$2$6$1       =  *column_name | *create_table_constraint$2$6$1 $',' *column_name 
            create_table_constraint$2$7         =  epsilon | $'(' *create_table_constraint$2$7$1 $')' 
            create_table_constraint$2$7$1       =  *ref_column | *create_table_constraint$2$7$1 $',' *ref_column 
            create_table_constraint$2$8         =  epsilon | ON DELETE *create_table_constraint$2$8$1 
            create_table_constraint$2$8$1       =  CASCADE | NO ACTION 
            create_table_constraint$2$9         =  epsilon | ON UPDATE *create_table_constraint$2$9$1 
            create_table_constraint$2$9$1       =  CASCADE | NO ACTION 
            create_table_constraint$2$10        =  epsilon | NOT FOR REPLICATION 
            create_table_constraint$2$11        =  epsilon | NOT FOR REPLICATION 
            CREATE_TRIGGER_statement            =  CREATE
+                                                  TRIGGER
+                                                  *trigger_name
+                                                  ON
+                                                  *table_or_view
+                                                  *CREATE_TRIGGER_statement$1
+                                                  *CREATE_TRIGGER_statement$2
+                                                  *CREATE_TRIGGER_statement$3
+                                                  *CREATE_TRIGGER_statement$4
+                                                  *CREATE_TRIGGER_statement$5
+                                                  *CREATE_TRIGGER_statement$6
+                                                  *CREATE_TRIGGER_statement$7
+                                                  *CREATE_TRIGGER_statement$8
+                                                  *CREATE_TRIGGER_statement$9
+                                                  AS
+                                                  *CREATE_TRIGGER_statement$10
+                                                  *CREATE_TRIGGER_statement$11 
            CREATE_TRIGGER_statement$1          =  epsilon | WITH ENCRYPTION 
            CREATE_TRIGGER_statement$2          =  FOR | AFTER | INSTEAD OF 
            CREATE_TRIGGER_statement$3          =  epsilon | INSERT 
            CREATE_TRIGGER_statement$4          =  epsilon | $',' 
            CREATE_TRIGGER_statement$5          =  epsilon | UPDATE 
            CREATE_TRIGGER_statement$6          =  epsilon | $',' 
            CREATE_TRIGGER_statement$7          =  epsilon | DELETE 
            CREATE_TRIGGER_statement$8          =  epsilon | WITH APPEND 
            CREATE_TRIGGER_statement$9          =  epsilon | NOT FOR REPLICATION 
            CREATE_TRIGGER_statement$10         =  epsilon
+                                               |  IF UPDATE $'(' *column_name $')' *CREATE_TRIGGER_statement$10$1
+                                               |  IF
+                                                  $'('
+                                                  COLUMNS_UPDATED
+                                                  $'('
+                                                  $')'
+                                                  *bitwise_operator
+                                                  *updated_bitmask
+                                                  $')'
+                                                  *comparison_operator
+                                                  *CREATE_TRIGGER_statement$10$2 
            CREATE_TRIGGER_statement$10$1       =  epsilon | *CREATE_TRIGGER_statement$10$1 *CREATE_TRIGGER_statement$10$1$0 
            CREATE_TRIGGER_statement$10$1$0     =  *CREATE_TRIGGER_statement$10$1$1 UPDATE $'(' *column_name $')' 
            CREATE_TRIGGER_statement$10$1$1     =  AND | OR 
            CREATE_TRIGGER_statement$10$2       =  *column_bitmask | *CREATE_TRIGGER_statement$10$2 *column_bitmask 
            CREATE_TRIGGER_statement$11         =  *CREATE_TRIGGER_statement$11$0 | *CREATE_TRIGGER_statement$11 *CREATE_TRIGGER_statement$11$0 
            CREATE_TRIGGER_statement$11$0       =  *control_of_flow_statement | *sql_statement 
            CREATE_VIEW_statement               =  CREATE
+                                                  VIEW
+                                                  *view
+                                                  *CREATE_VIEW_statement$1
+                                                  *CREATE_VIEW_statement$2
+                                                  AS
+                                                  *select_statement
+                                                  *CREATE_VIEW_statement$3 
            CREATE_VIEW_statement$1             =  epsilon | $'(' *CREATE_VIEW_statement$1$1 $')' 
            CREATE_VIEW_statement$1$1           =  *column_name | *CREATE_VIEW_statement$1$1 $',' *column_name 
            CREATE_VIEW_statement$2             =  epsilon | WITH *CREATE_VIEW_statement$2$1 
            CREATE_VIEW_statement$2$1           =  *view_attribute | *CREATE_VIEW_statement$2$1 $',' *view_attribute 
            CREATE_VIEW_statement$3             =  epsilon | WITH CHECK OPTION 
            DBCC_statement                      =  DBCC *DBCC_statement$1 
            DBCC_statement$1                    =  ADDINSTANCE $'(' *expression $',' *expression $')'
+                                               |  ADDEXTENDEDPROC $'(' *expression $',' *expression $')'
+                                               |  CHECKALLOC $'(' *database_name *DBCC_statement$1$1 $')' *DBCC_statement$1$2
+                                               |  CHECKCATALOG $'(' *database_name $')' *DBCC_statement$1$3
+                                               |  CHECKCONSTRAINTS *DBCC_statement$1$4 *DBCC_statement$1$5
+                                               |  CHECKDB $'(' *database_name *DBCC_statement$1$6 $')' *DBCC_statement$1$7
+                                               |  CHECKFILEGROUP $'(' *DBCC_statement$1$8 *DBCC_statement$1$9 $')' *DBCC_statement$1$10
+                                               |  CHECKIDENT $'(' *table_name *DBCC_statement$1$11 $')'
+                                               |  CHECKTABLE $'(' *DBCC_statement$1$12 *DBCC_statement$1$13 $')' *DBCC_statement$1$14
+                                               |  CLEANTABLE $'(' *DBCC_statement$1$15 $',' *DBCC_statement$1$16 *DBCC_statement$1$17 $')'
+                                               |  CONCURRENCYVIOLATION *DBCC_statement$1$18
+                                               |  DELETEINSTANCE $'(' *expression $',' *expression $')'
+                                               |  DBREPAIR $'(' *DBCC_statement$1$19 $')' *DBCC_statement$1$20
+                                               |  DBREINDEX $'(' *database $'.' *owner $'.' *table_name *DBCC_statement$1$21 $')' *DBCC_statement$1$22
+                                               |  *dllname $'(' FREE $')'
+                                               |  DROPCLEANBUFFERS
+                                               |  FLUSHPROCINDB $'(' *expression $')'
+                                               |  FREEPROCCACHE
+                                               |  HELP $'(' *DBCC_statement$1$23 $')'
+                                               |  INCREMENTINSTANCE $'(' *expression $',' *expression $',' *expression $',' *expression $')'
+                                               |  INDEXDEFRAG
+                                                  $'('
+                                                  *DBCC_statement$1$24
+                                                  $','
+                                                  *DBCC_statement$1$25
+                                                  $','
+                                                  *DBCC_statement$1$26
+                                                  $')'
+                                                  *DBCC_statement$1$27
+                                               |  INPUTBUFFER $'(' *spid $')'
+                                               |  NEWALLOC
+                                               |  OPENTRAN $'(' *DBCC_statement$1$28 $')' *DBCC_statement$1$29
+                                               |  OUTPUTBUFFER $'(' *spid $')'
+                                               |  PINTABLE $'(' *database_id $',' *table_id $')'
+                                               |  PROCCACHE
+                                               |  ROWLOCK
+                                               |  SETINSTANCE $'(' *expression $',' *expression $',' *expression $',' *expression $')'
+                                               |  SHOWCONTIG *DBCC_statement$1$30 *DBCC_statement$1$31
+                                               |  SHOW_STATISTICS *DBCC_statement$1$32 *DBCC_statement$1$33 *DBCC_statement$1$34
+                                               |  SHRINKDATABASE $'(' *database_name *DBCC_statement$1$35 *DBCC_statement$1$36 $')'
+                                               |  SHRINKFILE $'(' *DBCC_statement$1$37 *DBCC_statement$1$38 $')'
+                                               |  SQLPERF $'(' LOGSPACE $')'
+                                               |  TRACEOFF $'(' *DBCC_statement$1$39 $')'
+                                               |  TRACEON $'(' *DBCC_statement$1$40 $')'
+                                               |  TRACESTATUS $'(' *DBCC_statement$1$41 $')'
+                                               |  UNPINTABLE $'(' *database_id $',' *table_id $')'
+                                               |  UPDATEUSAGE *DBCC_statement$1$42 *DBCC_statement$1$43
+                                               |  USEROPTIONS
+                                               |  *identifier *DBCC_statement$1$44 *DBCC_statement$1$45 
            DBCC_statement$1$1                  =  epsilon | $',' NOINDEX | REPAIR_ALLOW_DATA_LOSS | REPAIR_FAST | REPAIR_REBUILD 
            DBCC_statement$1$2                  =  epsilon | WITH *DBCC_statement$1$2$1 *DBCC_statement$1$2$2 *DBCC_statement$1$2$3 
            DBCC_statement$1$2$1                =  epsilon | ALL_ERRORMSGS | NO_INFOMSGS 
            DBCC_statement$1$2$2                =  epsilon | $',' *DBCC_statement$1$2$2$1 
            DBCC_statement$1$2$2$1              =  epsilon | TABLOCK 
            DBCC_statement$1$2$3                =  epsilon | $',' *DBCC_statement$1$2$3$1 
            DBCC_statement$1$2$3$1              =  epsilon | ESTIMATEONLY 
            DBCC_statement$1$3                  =  epsilon | WITH NO_INFOMSGS 
            DBCC_statement$1$4                  =  epsilon | $'(' *DBCC_statement$1$4$1 $')' 
            DBCC_statement$1$4$1                =  *table_name | *constraint_name 
            DBCC_statement$1$5                  =  epsilon | WITH *DBCC_statement$1$5$1 
            DBCC_statement$1$5$1                =  ALL_ERRORMSGS | ALL_CONSTRAINTS 
            DBCC_statement$1$6                  =  epsilon | $',' NOINDEX | REPAIR_ALLOW_DATA_LOSS | REPAIR_FAST | REPAIR_REBUILD 
            DBCC_statement$1$7                  =  epsilon
+                                               |  WITH
+                                                  *DBCC_statement$1$7$1
+                                                  *DBCC_statement$1$7$2
+                                                  *DBCC_statement$1$7$3
+                                                  *DBCC_statement$1$7$4
+                                                  *DBCC_statement$1$7$5 
            DBCC_statement$1$7$1                =  epsilon | ALL_ERRORMSGS 
            DBCC_statement$1$7$2                =  epsilon | $',' *DBCC_statement$1$7$2$1 
            DBCC_statement$1$7$2$1              =  epsilon | NO_INFOMSGS 
            DBCC_statement$1$7$3                =  epsilon | $',' *DBCC_statement$1$7$3$1 
            DBCC_statement$1$7$3$1              =  epsilon | TABLOCK 
            DBCC_statement$1$7$4                =  epsilon | $',' *DBCC_statement$1$7$4$1 
            DBCC_statement$1$7$4$1              =  epsilon | ESTIMATEONLY 
            DBCC_statement$1$7$5                =  epsilon | $',' *DBCC_statement$1$7$5$1 
            DBCC_statement$1$7$5$1              =  epsilon | PHYSICAL_ONLY 
            DBCC_statement$1$8                  =  epsilon | *filegroup | *filegroup_id 
            DBCC_statement$1$9                  =  epsilon | $',' NOINDEX 
            DBCC_statement$1$10                 =  epsilon | WITH *DBCC_statement$1$10$1 *DBCC_statement$1$10$2 *DBCC_statement$1$10$3 
            DBCC_statement$1$10$1               =  epsilon | ALL_ERRORMSGS | NO_INFOMSGS 
            DBCC_statement$1$10$2               =  epsilon | $',' *DBCC_statement$1$10$2$1 
            DBCC_statement$1$10$2$1             =  epsilon | TABLOCK 
            DBCC_statement$1$10$3               =  epsilon | $',' *DBCC_statement$1$10$3$1 
            DBCC_statement$1$10$3$1             =  epsilon | ESTIMATEONLY 
            DBCC_statement$1$11                 =  epsilon | $',' *DBCC_statement$1$11$1 
            DBCC_statement$1$11$1               =  NORESEED | RESEED *DBCC_statement$1$11$1$1 
            DBCC_statement$1$11$1$1             =  epsilon | $',' *new_reseed_value 
            DBCC_statement$1$12                 =  *table_name | *view_name 
            DBCC_statement$1$13                 =  epsilon | $',' NOINDEX | *index_id | REPAIR_ALLOW_DATA_LOSS | REPAIR_FAST | REPAIR_REBUILD 
            DBCC_statement$1$14                 =  epsilon | WITH *DBCC_statement$1$14$1 *DBCC_statement$1$14$2 *DBCC_statement$1$14$3 *DBCC_statement$1$14$4 
            DBCC_statement$1$14$1               =  epsilon | ALL_ERRORMSGS | NO_INFOMSGS 
            DBCC_statement$1$14$2               =  epsilon | $',' *DBCC_statement$1$14$2$1 
            DBCC_statement$1$14$2$1             =  epsilon | TABLOCK 
            DBCC_statement$1$14$3               =  epsilon | $',' *DBCC_statement$1$14$3$1 
            DBCC_statement$1$14$3$1             =  epsilon | ESTIMATEONLY 
            DBCC_statement$1$14$4               =  epsilon | $',' *DBCC_statement$1$14$4$1 
            DBCC_statement$1$14$4$1             =  epsilon | PHYSICAL_ONLY 
            DBCC_statement$1$15                 =  *database_name | *database_id 
            DBCC_statement$1$16                 =  *table_name | *table_id | *view_name | *view_id 
            DBCC_statement$1$17                 =  epsilon | $',' *batch_size 
            DBCC_statement$1$18                 =  epsilon | $'(' *DBCC_statement$1$18$1 $')' 
            DBCC_statement$1$18$1               =  DISPLAY | RESET | STARTLOG | STOPLOG 
            DBCC_statement$1$19                 =  *expression | *DBCC_statement$1$19 $',' *expression 
            DBCC_statement$1$20                 =  epsilon | WITH NO_INFOMSGS 
            DBCC_statement$1$21                 =  epsilon | $',' *index_name *DBCC_statement$1$21$1 
            DBCC_statement$1$21$1               =  epsilon | $',' *fillfactor 
            DBCC_statement$1$22                 =  epsilon | WITH NO_INFOMSGS 
            DBCC_statement$1$23                 =  *string_literal | *local_variable | $'?' 
            DBCC_statement$1$24                 =  *database_name | *database_id | *integer_literal 
            DBCC_statement$1$25                 =  *table_name | *table_id | *view_name | *view_id 
            DBCC_statement$1$26                 =  *index_name | *index_id 
            DBCC_statement$1$27                 =  epsilon | WITH NO_INFOMSGS 
            DBCC_statement$1$28                 =  *database_name | *database_id 
            DBCC_statement$1$29                 =  epsilon | WITH TABLERESULTS *DBCC_statement$1$29$1 
            DBCC_statement$1$29$1               =  epsilon | $',' NO_INFOMSGS 
            DBCC_statement$1$30                 =  epsilon | $'(' *DBCC_statement$1$30$1 *DBCC_statement$1$30$2 $')' 
            DBCC_statement$1$30$1               =  *table_name | *table_id | *view_name | *view_id 
            DBCC_statement$1$30$2               =  epsilon | $',' *DBCC_statement$1$30$2$1 
            DBCC_statement$1$30$2$1             =  *index_name | *index_id 
            DBCC_statement$1$31                 =  epsilon | WITH *DBCC_statement$1$31$1 
            DBCC_statement$1$31$1               =  ALL_INDEXES | FAST *DBCC_statement$1$31$1$1 | TABLERESULTS *DBCC_statement$1$31$1$2 *DBCC_statement$1$31$1$3 
            DBCC_statement$1$31$1$1             =  epsilon | $',' ALL_INDEXES 
            DBCC_statement$1$31$1$2             =  epsilon | $',' ALL_INDEXES 
            DBCC_statement$1$31$1$3             =  epsilon | $',' *DBCC_statement$1$31$1$3$1 
            DBCC_statement$1$31$1$3$1           =  FAST | ALL_LEVELS 
            DBCC_statement$1$32                 =  epsilon | $'(' *DBCC_statement$1$32$1 $',' *DBCC_statement$1$32$2 $')' 
            DBCC_statement$1$32$1               =  *table_name | *variable_name 
            DBCC_statement$1$32$2               =  *target_name | *variable_name 
            DBCC_statement$1$33                 =  epsilon | WITH STAT_HEADER 
            DBCC_statement$1$34                 =  epsilon | JOIN DENSITY_VECTOR 
            DBCC_statement$1$35                 =  epsilon | $',' *target_percent 
            DBCC_statement$1$36                 =  epsilon | $',' *DBCC_statement$1$36$1 
            DBCC_statement$1$36$1               =  NOTRUNCATE | TRUNCATEONLY 
            DBCC_statement$1$37                 =  *file_name | *file_id 
            DBCC_statement$1$38                 =  *DBCC_statement$1$38$1 | *DBCC_statement$1$38$2 
            DBCC_statement$1$38$1               =  epsilon | $',' *target_size 
            DBCC_statement$1$38$2               =  epsilon | $',' *DBCC_statement$1$38$2$1 
            DBCC_statement$1$38$2$1             =  EMPTYFILE | NOTRUNCATE | TRUNCATEONLY 
            DBCC_statement$1$39                 =  *traceno | *DBCC_statement$1$39 $',' *traceno 
            DBCC_statement$1$40                 =  *traceno | *DBCC_statement$1$40 $',' *traceno 
            DBCC_statement$1$41                 =  *traceno | *DBCC_statement$1$41 $',' *traceno 
            DBCC_statement$1$42                 =  *expression *DBCC_statement$1$42$1 | $'(' *expression *DBCC_statement$1$42$2 $')' 
            DBCC_statement$1$42$1               =  epsilon | $',' *DBCC_statement$1$42$1$1 *DBCC_statement$1$42$1$2 
            DBCC_statement$1$42$1$1             =  *table_or_view_name | *at_identifier 
            DBCC_statement$1$42$1$2             =  epsilon | $',' *index_id 
            DBCC_statement$1$42$2               =  epsilon | $',' *DBCC_statement$1$42$2$1 *DBCC_statement$1$42$2$2 
            DBCC_statement$1$42$2$1             =  *table_or_view_name | *at_identifier 
            DBCC_statement$1$42$2$2             =  epsilon | $',' *index_id 
            DBCC_statement$1$43                 =  epsilon | WITH *DBCC_statement$1$43$1 *DBCC_statement$1$43$2 
            DBCC_statement$1$43$1               =  epsilon | COUNT_ROWS 
            DBCC_statement$1$43$2               =  epsilon | *DBCC_statement$1$43$2$1 NO_INFOMSGS 
            DBCC_statement$1$43$2$1             =  epsilon | $',' 
            DBCC_statement$1$44                 =  epsilon | $'(' *DBCC_statement$1$44$1 $')' 
            DBCC_statement$1$44$1               =  epsilon | *expression % $',' 
            DBCC_statement$1$45                 =  epsilon | WITH NO_INFOMSGS 
            dllname                             =  *identifier 
            new_reseed_value                    =  *integer_literal 
            owner                               =  *identifier 
            target_percent                      =  *integer_literal 
            target_size                         =  *integer_literal 
            traceno                             =  *integer_literal 
            view_id                             =  *identifier 
            DEALLOCATE_statement                =  DEALLOCATE *DEALLOCATE_statement$1 
            DEALLOCATE_statement$1              =  *DEALLOCATE_statement$1$1 *cursor_name | *cursor_variable_name 
            DEALLOCATE_statement$1$1            =  epsilon | GLOBAL 
            DECLARE_variable_statement          =  DECLARE *DECLARE_variable_statement$1 
            DECLARE_variable_statement$1        =  *DECLARE_variable_statement$1$0 | *DECLARE_variable_statement$1 $',' *DECLARE_variable_statement$1$0 
            DECLARE_variable_statement$1$0      =  *local_variable *DECLARE_variable_statement$1$1 *data_type
+                                               |  *cursor_variable_name CURSOR
+                                               |  *local_variable TABLE $'(' *DECLARE_variable_statement$1$2 $')' 
            DECLARE_variable_statement$1$1      =  epsilon | AS 
            DECLARE_variable_statement$1$2      =  *DECLARE_variable_statement$1$2$0 | *DECLARE_variable_statement$1$2 $',' *DECLARE_variable_statement$1$2$0 
            DECLARE_variable_statement$1$2$0    =  *declared_column_definition | *declared_table_constraint 
            declared_column_definition          =  *column_name
+                                                  *scalar_data_type
+                                                  *declared_column_definition$1
+                                                  *declared_column_definition$2
+                                                  *declared_column_definition$3
+                                                  *declared_column_definition$4 
            declared_column_definition$1        =  epsilon | *COLLATE_clause 
            declared_column_definition$2        =  epsilon | DEFAULT *constant_expression | IDENTITY *declared_column_definition$2$1 
            declared_column_definition$2$1      =  epsilon | $'(' *seed $',' *increment $')' 
            declared_column_definition$3        =  epsilon | ROWGUIDCOL 
            declared_column_definition$4        =  epsilon | *declared_column_constraint 
            declared_column_constraint          =  NULL | NOT NULL | PRIMARY KEY | UNIQUE | CHECK $'(' *logical_expression $')' 
            declared_table_constraint           =  *declared_table_constraint$1 $'(' *declared_table_constraint$2 $')' | CHECK $'(' *search_condition $')' 
            declared_table_constraint$1         =  PRIMARY KEY | UNIQUE 
            declared_table_constraint$2         =  *column_name | *declared_table_constraint$2 $',' *column_name 
            DECLARE_CURSOR_statement            =  DECLARE
+                                                  *cursor_name
+                                                  *DECLARE_CURSOR_statement$1
+                                                  *DECLARE_CURSOR_statement$2
+                                                  CURSOR
+                                                  *DECLARE_CURSOR_statement$3
+                                                  FOR
+                                                  *select_statement
+                                                  *DECLARE_CURSOR_statement$4 
            DECLARE_CURSOR_statement$1          =  epsilon | INSENSITIVE 
            DECLARE_CURSOR_statement$2          =  epsilon | SCROLL 
            DECLARE_CURSOR_statement$3          =  epsilon | *DECLARE_CURSOR_statement$3 *DECLARE_CURSOR_statement$3$0 
            DECLARE_CURSOR_statement$3$0        =  *DECLARE_CURSOR_statement$3$1
+                                               |  *DECLARE_CURSOR_statement$3$2
+                                               |  *DECLARE_CURSOR_statement$3$3
+                                               |  *DECLARE_CURSOR_statement$3$4
+                                               |  TYPE_WARNING 
            DECLARE_CURSOR_statement$3$1        =  LOCAL | GLOBAL 
            DECLARE_CURSOR_statement$3$2        =  FORWARD_ONLY | SCROLL 
            DECLARE_CURSOR_statement$3$3        =  STATIC | KEYSET | DYNAMIC | FAST_FORWARD 
            DECLARE_CURSOR_statement$3$4        =  READ_ONLY | SCROLL_LOCKS | OPTIMISTIC 
            DECLARE_CURSOR_statement$4          =  epsilon | FOR *DECLARE_CURSOR_statement$4$1 
            DECLARE_CURSOR_statement$4$1        =  READ ONLY | UPDATE *DECLARE_CURSOR_statement$4$1$1 
            DECLARE_CURSOR_statement$4$1$1      =  epsilon | OF *DECLARE_CURSOR_statement$4$1$1$1 
            DECLARE_CURSOR_statement$4$1$1$1    =  *column_name | *DECLARE_CURSOR_statement$4$1$1$1 $',' *column_name 
            DELETE_statement                    =  DELETE *DELETE_statement$1 *DELETE_statement$2 *DELETE_statement$3 *DELETE_statement$4 *DELETE_statement$5 
            DELETE_statement$1                  =  epsilon | FROM 
            DELETE_statement$2                  =  *DELETE_statement$2$1 *DELETE_statement$2$2 | *view | *rowset_function_limited 
            DELETE_statement$2$1                =  *table | *local_variable 
            DELETE_statement$2$2                =  epsilon | WITH $'(' *DELETE_statement$2$2$1 $')' 
            DELETE_statement$2$2$1              =  *table_hint_limited | *DELETE_statement$2$2$1 *table_hint_limited 
            DELETE_statement$3                  =  epsilon | FROM *DELETE_statement$3$1 
            DELETE_statement$3$1                =  *select_source | *DELETE_statement$3$1 $',' *select_source 
            DELETE_statement$4                  =  epsilon | WHERE *DELETE_statement$4$1 
            DELETE_statement$4$1                =  *search_condition | *DELETE_statement$4$1$1 
            DELETE_statement$4$1$1              =  epsilon | CURRENT OF *DELETE_statement$4$1$1$1 
            DELETE_statement$4$1$1$1            =  *DELETE_statement$4$1$1$1$1 *cursor_name | *cursor_variable_name 
            DELETE_statement$4$1$1$1$1          =  epsilon | GLOBAL 
            DELETE_statement$5                  =  epsilon | OPTION $'(' *DELETE_statement$5$1 $')' 
            DELETE_statement$5$1                =  *delete_query_hint | *DELETE_statement$5$1 $',' *delete_query_hint 
            select_source                       =  *select_source$1 *select_source$2 
            select_source$1                     =  *table_source | $'(' *select_source $')' 
            select_source$2                     =  epsilon | #*joined_table 
            table_source                        =  *table_source$1 *table_source$2 *table_source$3 *table_source$4
+                                               |  *view *table_source$5 *table_source$6
+                                               |  *rowset_function *table_source$7
+                                               |  $'::' *user_defined_function $'(' $')' *table_source$8
+                                               |  OPENXML
+                                               |  *derived_table *table_source$9 *table_alias *table_source$10 
            table_source$1                      =  *table | *local_variable 
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
            table_hint_limited                  =  FASTFIRSTROW
+                                               |  HOLDLOCK
+                                               |  PAGLOCK
+                                               |  READCOMMITTED
+                                               |  REPEATABLEREAD
+                                               |  ROWLOCK
+                                               |  SERIALIZABLE
+                                               |  TABLOCK
+                                               |  TABLOCKX
+                                               |  UPDLOCK 
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
            delete_query_hint                   =  *delete_query_hint$1 GROUP
+                                               |  *delete_query_hint$2 UNION
+                                               |  FAST *number_rows
+                                               |  FORCE ORDER
+                                               |  MAXDOP
+                                               |  ROBUST PLAN
+                                               |  KEEP PLAN 
            delete_query_hint$1                 =  HASH | ORDER 
            delete_query_hint$2                 =  CONCAT | HASH | MERGE 
            DENY_statement                      =  DENY *DENY_statement$1 
            DENY_statement$1                    =  *DENY_statement$1$1 TO *DENY_statement$1$2
+                                               |  *DENY_statement$1$3 *DENY_statement$1$4 TO *DENY_statement$1$5 *DENY_statement$1$6 
            DENY_statement$1$1                  =  ALL | *DENY_statement$1$1$1 
            DENY_statement$1$1$1                =  *statement | *DENY_statement$1$1$1 $',' *statement 
            DENY_statement$1$2                  =  *security_account | *DENY_statement$1$2 $',' *security_account 
            DENY_statement$1$3                  =  ALL *DENY_statement$1$3$1 | *DENY_statement$1$3$2 
            DENY_statement$1$3$1                =  epsilon | PRIVILEGES 
            DENY_statement$1$3$2                =  *permission | *DENY_statement$1$3$2 $',' *permission 
            DENY_statement$1$4                  =  *DENY_statement$1$4$1 ON *table_or_view
+                                               |  ON *table_or_view *DENY_statement$1$4$2
+                                               |  ON *DENY_statement$1$4$3
+                                               |  ON *user_defined_function 
            DENY_statement$1$4$1                =  epsilon | $'(' *DENY_statement$1$4$1$1 $')' 
            DENY_statement$1$4$1$1              =  *column_name | *DENY_statement$1$4$1$1 $',' *column_name 
            DENY_statement$1$4$2                =  epsilon | $'(' *DENY_statement$1$4$2$1 $')' 
            DENY_statement$1$4$2$1              =  *column_name | *DENY_statement$1$4$2$1 $',' *column_name 
            DENY_statement$1$4$3                =  *stored_procedure | *extended_procedure 
            DENY_statement$1$5                  =  *security_account | *DENY_statement$1$5 $',' *security_account 
            DENY_statement$1$6                  =  epsilon | CASCADE 
            DROP_DATABASE_statement             =  DROP DATABASE *DROP_DATABASE_statement$1 
            DROP_DATABASE_statement$1           =  *database_name | *DROP_DATABASE_statement$1 $',' *database_name 
            DROP_DEFAULT_statement              =  DROP DEFAULT *DROP_DEFAULT_statement$1 
            DROP_DEFAULT_statement$1            =  *default | *DROP_DEFAULT_statement$1 $',' *default 
            DROP_FUNCTION_statement             =  DROP FUNCTION *DROP_FUNCTION_statement$1 
            DROP_FUNCTION_statement$1           =  *function | *DROP_FUNCTION_statement$1 $',' *function 
            DROP_INDEX_statement                =  DROP INDEX *DROP_INDEX_statement$1 
            DROP_INDEX_statement$1              =  *index | *DROP_INDEX_statement$1 $',' *index 
            DROP_PROCEDURE_statement            =  DROP *DROP_PROCEDURE_statement$1 *DROP_PROCEDURE_statement$2 
            DROP_PROCEDURE_statement$1          =  PROC | PROCEDURE 
            DROP_PROCEDURE_statement$2          =  *procedure | *DROP_PROCEDURE_statement$2 $',' *procedure 
            DROP_RULE_statement                 =  DROP RULE *DROP_RULE_statement$1 
            DROP_RULE_statement$1               =  *rule | *DROP_RULE_statement$1 $',' *rule 
            DROP_STATISTICS_statement           =  DROP STATISTICS *DROP_STATISTICS_statement$1 
            DROP_STATISTICS_statement$1         =  *DROP_STATISTICS_statement$1$0 | *DROP_STATISTICS_statement$1 $',' *DROP_STATISTICS_statement$1$0 
            DROP_STATISTICS_statement$1$0       =  *table $'.' *statistics_name | *view $'.' *statistics_name 
            DROP_TABLE_statement                =  DROP TABLE *DROP_TABLE_statement$1 
            DROP_TABLE_statement$1              =  *table | *DROP_TABLE_statement$1 $',' *table 
            DROP_TRIGGER_statement              =  DROP TRIGGER *DROP_TRIGGER_statement$1 
            DROP_TRIGGER_statement$1            =  *trigger | *DROP_TRIGGER_statement$1 $',' *trigger 
            DROP_VIEW_statement                 =  DROP VIEW *DROP_VIEW_statement$1 
            DROP_VIEW_statement$1               =  *view | *DROP_VIEW_statement$1 $',' *view 
            DUMP_statement                      =  DUMP *DUMP_statement$1 *DUMP_statement$2 
            DUMP_statement$1                    =  DATABASE *database_name | *DUMP_statement$1$1 *transaction_name 
            DUMP_statement$1$1                  =  TRAN | TRANSACTION 
            DUMP_statement$2                    =  epsilon | WITH NO_LOG 
            EXECUTE_statement                   =  *EXECUTE_statement$1 *EXECUTE_statement$2 
            EXECUTE_statement$1                 =  EXEC | EXECUTE 
            EXECUTE_statement$2                 =  *execute_clause | $'(' *string_sum $')' 
            execute_clause                      =  *execute_clause$1 *execute_clause$2 *execute_clause$3 *execute_clause$4 
            execute_clause$1                    =  epsilon | *return_status $'=' 
            execute_clause$2                    =  *procedure *execute_clause$2$1 | *procedure_name_var 
            execute_clause$2$1                  =  epsilon | $';' *number 
            execute_clause$3                    =  epsilon | (!(*parameter $'=') *expression !(OUT | OUTPUT) | !DEFAULT) % $',' 
            execute_clause$4                    =  epsilon | WITH RECOMPILE 
            string_factor                       =  *string_variable | *global_variable | *string_literal 
            string_sum                          =  *string_factor *string_sum$1 
            string_sum$1                        =  epsilon | $'+' *string_sum 
            FETCH_statement                     =  FETCH *FETCH_statement$1 *FETCH_statement$2 *FETCH_statement$3 
            FETCH_statement$1                   =  epsilon | *FETCH_statement$1$1 FROM 
            FETCH_statement$1$1                 =  epsilon | NEXT | PRIOR | FIRST | LAST | ABSOLUTE *FETCH_statement$1$1$1 | RELATIVE *FETCH_statement$1$1$2 
            FETCH_statement$1$1$1               =  *n | *nvar 
            FETCH_statement$1$1$2               =  *n | *nvar 
            FETCH_statement$2                   =  *FETCH_statement$2$1 *cursor_name | *cursor_variable_name 
            FETCH_statement$2$1                 =  epsilon | GLOBAL 
            FETCH_statement$3                   =  epsilon | INTO *FETCH_statement$3$1 
            FETCH_statement$3$1                 =  *variable_name | *FETCH_statement$3$1 $',' *variable_name 
            GRANT_statement                     =  GRANT *GRANT_statement$1 
            GRANT_statement$1                   =  *GRANT_statement$1$1 TO *GRANT_statement$1$2
+                                               |  *GRANT_statement$1$3 *GRANT_statement$1$4 TO *GRANT_statement$1$5 *GRANT_statement$1$6 *GRANT_statement$1$7 
            GRANT_statement$1$1                 =  ALL | *GRANT_statement$1$1$1 
            GRANT_statement$1$1$1               =  *statement | *GRANT_statement$1$1$1 $',' *statement 
            GRANT_statement$1$2                 =  *security_account | *GRANT_statement$1$2 $',' *security_account 
            GRANT_statement$1$3                 =  ALL *GRANT_statement$1$3$1 | *GRANT_statement$1$3$2 
            GRANT_statement$1$3$1               =  epsilon | PRIVILEGES 
            GRANT_statement$1$3$2               =  *permission | *GRANT_statement$1$3$2 $',' *permission 
            GRANT_statement$1$4                 =  *GRANT_statement$1$4$1 ON *table_or_view
+                                               |  ON *table_or_view *GRANT_statement$1$4$2
+                                               |  ON *GRANT_statement$1$4$3
+                                               |  ON *user_defined_function 
            GRANT_statement$1$4$1               =  epsilon | $'(' *GRANT_statement$1$4$1$1 $')' 
            GRANT_statement$1$4$1$1             =  *column_name | *GRANT_statement$1$4$1$1 $',' *column_name 
            GRANT_statement$1$4$2               =  epsilon | $'(' *GRANT_statement$1$4$2$1 $')' 
            GRANT_statement$1$4$2$1             =  *column_name | *GRANT_statement$1$4$2$1 $',' *column_name 
            GRANT_statement$1$4$3               =  *stored_procedure | *extended_procedure 
            GRANT_statement$1$5                 =  *security_account | *GRANT_statement$1$5 $',' *security_account 
            GRANT_statement$1$6                 =  epsilon | WITH GRANT OPTION 
            GRANT_statement$1$7                 =  epsilon | AS *GRANT_statement$1$7$1 
            GRANT_statement$1$7$1               =  *group | *role 
            GROUPING_clause                     =  GROUPING $'(' *column_name $')' 
            IDENTITY_clause                     =  IDENTITY *IDENTITY_clause$1 | IDENTITY $'(' *data_type *IDENTITY_clause$2 $')' AS *column_name 
            IDENTITY_clause$1                   =  epsilon | $'(' *seed $',' *increment $')' 
            IDENTITY_clause$2                   =  epsilon | $',' *seed $',' *increment 
            NOT_IN_clause                       =  *test_expression *NOT_IN_clause$1 IN $'(' *NOT_IN_clause$2 $')' 
            NOT_IN_clause$1                     =  epsilon | NOT 
            NOT_IN_clause$2                     =  *subquery | *NOT_IN_clause$2$1 
            NOT_IN_clause$2$1                   =  *expression | *NOT_IN_clause$2$1 $',' *expression 
            INSERT_statement                    =  INSERT *INSERT_statement$1 *INSERT_statement$2 *INSERT_statement$3 *INSERT_statement$4 | DEFAULT VALUES 
            INSERT_statement$1                  =  epsilon | INTO 
            INSERT_statement$2                  =  *INSERT_statement$2$1 *INSERT_statement$2$2 | *view | *rowset_function_limited 
            INSERT_statement$2$1                =  *table | *local_variable 
            INSERT_statement$2$2                =  epsilon | WITH $'(' *INSERT_statement$2$2$1 $')' 
            INSERT_statement$2$2$1              =  *table_hint_limited | *INSERT_statement$2$2$1 *table_hint_limited 
            INSERT_statement$3                  =  epsilon | $'(' *column_list $')' 
            INSERT_statement$4                  =  VALUES $'(' *INSERT_statement$4$1 $')' | *derived_table | *EXECUTE_statement 
            INSERT_statement$4$1                =  *INSERT_statement$4$1$0 | *INSERT_statement$4$1 $',' *INSERT_statement$4$1$0 
            INSERT_statement$4$1$0              =  DEFAULT | NULL | *expression 
            IS_clause                           =  *expression IS *IS_clause$1 NULL 
            IS_clause$1                         =  epsilon | NOT 
            KILL_statement                      =  KILL *KILL_statement$1 *KILL_statement$2 
            KILL_statement$1                    =  *spid | UOW 
            KILL_statement$2                    =  epsilon | WITH STATUSONLY 
            LIKE_clause                         =  *match_expression *LIKE_clause$1 LIKE *pattern *LIKE_clause$2 
            LIKE_clause$1                       =  epsilon | NOT 
            LIKE_clause$2                       =  epsilon | ESCAPE *escape_character 
            LOAD_statement                      =  LOAD *LOAD_statement$1 
            LOAD_statement$1                    =  DATABASE | TRANSACTION | HEADERONLY 
            NOT_clause                          =  *NOT_clause$1 *boolean_expression 
            NOT_clause$1                        =  epsilon | NOT 
            OPEN_statement                      =  OPEN *OPEN_statement$1 
            OPEN_statement$1                    =  *OPEN_statement$1$1 *cursor_name | *cursor_variable_name 
            OPEN_statement$1$1                  =  epsilon | GLOBAL 
            OPENXML_clause                      =  OPENXML
+                                                  $'('
+                                                  *idoc
+                                                  $'int'
+                                                  *OPENXML_clause$1
+                                                  $','
+                                                  *rowpattern
+                                                  $'nvarchar'
+                                                  *OPENXML_clause$2
+                                                  $','
+                                                  *OPENXML_clause$3
+                                                  $')'
+                                                  *OPENXML_clause$4 
            OPENXML_clause$1                    =  epsilon | IN 
            OPENXML_clause$2                    =  epsilon | IN 
            OPENXML_clause$3                    =  epsilon | *flags $'byte' *OPENXML_clause$3$1 
            OPENXML_clause$3$1                  =  epsilon | IN 
            OPENXML_clause$4                    =  epsilon | WITH $'(' *SchemaDeclaration | *TableName $')' 
            PRINT_statement                     =  PRINT *PRINT_statement$1 
            PRINT_statement$1                   =  *string_literal | *local_variable | $'@@FUNCTION' | *string_expression 
            RAISERROR_statement                 =  RAISERROR *RAISERROR_statement$1 *RAISERROR_statement$2 
            RAISERROR_statement$1               =  $'(' *RAISERROR_statement$1$1 $',' *severity $',' *state *RAISERROR_statement$1$2 $')' | *msg_id *msg_str 
            RAISERROR_statement$1$1             =  *msg_id | *msg_str 
            RAISERROR_statement$1$2             =  epsilon | $',' *RAISERROR_statement$1$2$1 
            RAISERROR_statement$1$2$1           =  *argument | *RAISERROR_statement$1$2$1 $',' *argument 
            RAISERROR_statement$2               =  epsilon | WITH *RAISERROR_statement$2$1 
            RAISERROR_statement$2$1             =  *RAISERROR_statement$2$1$0 | *RAISERROR_statement$2$1 $',' *RAISERROR_statement$2$1$0 
            RAISERROR_statement$2$1$0           =  LOG | NOWAIT | SETERROR 
            msg_id                              =  *integer_expression 
            msg_str                             =  *string_literal 
            severity                            =  *integer_expression 
            state                               =  *integer_expression 
            argument                            =  *expression 
            READTEXT_statement                  =  READTEXT *table $'.' *column_name *text_ptr *offset *size *READTEXT_statement$1 
            READTEXT_statement$1                =  epsilon | HOLDLOCK 
            RECONFIGURE_statement               =  RECONFIGURE *RECONFIGURE_statement$1 
            RECONFIGURE_statement$1             =  epsilon | WITH OVERRIDE 
            RESTORE_statement                   =  RESTORE *RESTORE_statement$1 
            RESTORE_statement$1                 =  DATABASE *RESTORE_statement$1$1 *RESTORE_statement$1$2 *RESTORE_statement$1$3
+                                               |  DATABASE *RESTORE_statement$1$4 *RESTORE_statement$1$5 *RESTORE_statement$1$6 *RESTORE_statement$1$7
+                                               |  DATABASE *RESTORE_statement$1$8 *RESTORE_statement$1$9 *RESTORE_statement$1$10 *RESTORE_statement$1$11
+                                               |  LOG *RESTORE_statement$1$12 *RESTORE_statement$1$13 *RESTORE_statement$1$14 
            RESTORE_statement$1$1               =  *database_name | *database_name_var 
            RESTORE_statement$1$2               =  epsilon | FROM *RESTORE_statement$1$2$1 
            RESTORE_statement$1$2$1             =  *backup_device | *RESTORE_statement$1$2$1 $',' *backup_device 
            RESTORE_statement$1$3               =  epsilon
+                                               |  WITH
+                                                  *RESTORE_statement$1$3$1
+                                                  *RESTORE_statement$1$3$2
+                                                  *RESTORE_statement$1$3$3
+                                                  *RESTORE_statement$1$3$4
+                                                  *RESTORE_statement$1$3$5
+                                                  *RESTORE_statement$1$3$6
+                                                  *RESTORE_statement$1$3$7
+                                                  *RESTORE_statement$1$3$8
+                                                  *RESTORE_statement$1$3$9
+                                                  *RESTORE_statement$1$3$10
+                                                  *RESTORE_statement$1$3$11
+                                                  *RESTORE_statement$1$3$12
+                                                  *RESTORE_statement$1$3$13 
            RESTORE_statement$1$3$1             =  epsilon | RESTRICTED_USER 
            RESTORE_statement$1$3$2             =  epsilon | *RESTORE_statement$1$3$2$1 FILE $'=' *RESTORE_statement$1$3$2$2 
            RESTORE_statement$1$3$2$1           =  epsilon | $',' 
            RESTORE_statement$1$3$2$2           =  *file_number | *file_number_variable 
            RESTORE_statement$1$3$3             =  epsilon | *RESTORE_statement$1$3$3$1 PASSWORD $'=' *RESTORE_statement$1$3$3$2 
            RESTORE_statement$1$3$3$1           =  epsilon | $',' 
            RESTORE_statement$1$3$3$2           =  *password | *password_variable 
            RESTORE_statement$1$3$4             =  epsilon | *RESTORE_statement$1$3$4$1 MEDIANAME $'=' *RESTORE_statement$1$3$4$2 
            RESTORE_statement$1$3$4$1           =  epsilon | $',' 
            RESTORE_statement$1$3$4$2           =  *media_name | *media_name_variable 
            RESTORE_statement$1$3$5             =  epsilon | *RESTORE_statement$1$3$5$1 MEDIAPASSWORD $'=' *RESTORE_statement$1$3$5$2 
            RESTORE_statement$1$3$5$1           =  epsilon | $',' 
            RESTORE_statement$1$3$5$2           =  *mediapassword | *mediapassword_variable 
            RESTORE_statement$1$3$6             =  epsilon | (!$',' MOVE *logical_file_name TO *operating_system_file_name) % $',' 
            RESTORE_statement$1$3$7             =  epsilon | *RESTORE_statement$1$3$7$1 KEEP_REPLICATION 
            RESTORE_statement$1$3$7$1           =  epsilon | $',' 
            RESTORE_statement$1$3$8             =  epsilon | *RESTORE_statement$1$3$8$1 *RESTORE_statement$1$3$8$2 
            RESTORE_statement$1$3$8$1           =  epsilon | $',' 
            RESTORE_statement$1$3$8$2           =  NORECOVERY | RECOVERY | STANDBY $'=' *RESTORE_statement$1$3$8$2$1 
            RESTORE_statement$1$3$8$2$1         =  *undo_file_name | *undo_file_name_var 
            RESTORE_statement$1$3$9             =  epsilon | *RESTORE_statement$1$3$9$1 *RESTORE_statement$1$3$9$2 
            RESTORE_statement$1$3$9$1           =  epsilon | $',' 
            RESTORE_statement$1$3$9$2           =  NOREWIND | REWIND 
            RESTORE_statement$1$3$10            =  epsilon | *RESTORE_statement$1$3$10$1 *RESTORE_statement$1$3$10$2 
            RESTORE_statement$1$3$10$1          =  epsilon | $',' 
            RESTORE_statement$1$3$10$2          =  NOUNLOAD | UNLOAD 
            RESTORE_statement$1$3$11            =  epsilon | *RESTORE_statement$1$3$11$1 REPLACE 
            RESTORE_statement$1$3$11$1          =  epsilon | $',' 
            RESTORE_statement$1$3$12            =  epsilon | *RESTORE_statement$1$3$12$1 RESTART 
            RESTORE_statement$1$3$12$1          =  epsilon | $',' 
            RESTORE_statement$1$3$13            =  epsilon | *RESTORE_statement$1$3$13$1 STATS *RESTORE_statement$1$3$13$2 
            RESTORE_statement$1$3$13$1          =  epsilon | $',' 
            RESTORE_statement$1$3$13$2          =  epsilon | $'=' *percentage 
            RESTORE_statement$1$4               =  *database_name | *database_name_var 
            RESTORE_statement$1$5               =  *file_or_filegroup | *RESTORE_statement$1$5 $',' *file_or_filegroup 
            RESTORE_statement$1$6               =  epsilon | FROM *RESTORE_statement$1$6$1 
            RESTORE_statement$1$6$1             =  *backup_device | *RESTORE_statement$1$6$1 $',' *backup_device 
            RESTORE_statement$1$7               =  epsilon
+                                               |  WITH
+                                                  PARTIAL
+                                                  *RESTORE_statement$1$7$1
+                                                  *RESTORE_statement$1$7$2
+                                                  *RESTORE_statement$1$7$3
+                                                  *RESTORE_statement$1$7$4
+                                                  *RESTORE_statement$1$7$5
+                                                  *RESTORE_statement$1$7$6
+                                                  *RESTORE_statement$1$7$7
+                                                  *RESTORE_statement$1$7$8
+                                                  *RESTORE_statement$1$7$9
+                                                  *RESTORE_statement$1$7$10
+                                                  *RESTORE_statement$1$7$11
+                                                  *RESTORE_statement$1$7$12 
            RESTORE_statement$1$7$1             =  epsilon | *RESTORE_statement$1$7$1$1 FILE $'=' *RESTORE_statement$1$7$1$2 
            RESTORE_statement$1$7$1$1           =  epsilon | $',' 
            RESTORE_statement$1$7$1$2           =  *file_number | *file_number_variable 
            RESTORE_statement$1$7$2             =  epsilon | *RESTORE_statement$1$7$2$1 PASSWORD $'=' *RESTORE_statement$1$7$2$2 
            RESTORE_statement$1$7$2$1           =  epsilon | $',' 
            RESTORE_statement$1$7$2$2           =  *password | *password_variable 
            RESTORE_statement$1$7$3             =  epsilon | *RESTORE_statement$1$7$3$1 MEDIANAME $'=' *RESTORE_statement$1$7$3$2 
            RESTORE_statement$1$7$3$1           =  epsilon | $',' 
            RESTORE_statement$1$7$3$2           =  *media_name | *media_name_variable 
            RESTORE_statement$1$7$4             =  epsilon | *RESTORE_statement$1$7$4$1 MEDIAPASSWORD $'=' *RESTORE_statement$1$7$4$2 
            RESTORE_statement$1$7$4$1           =  epsilon | $',' 
            RESTORE_statement$1$7$4$2           =  *mediapassword | *mediapassword_variable 
            RESTORE_statement$1$7$5             =  epsilon | (!$',' MOVE *logical_file_name TO *operating_system_file_name) % $',' 
            RESTORE_statement$1$7$6             =  epsilon | *RESTORE_statement$1$7$6$1 NORECOVERY 
            RESTORE_statement$1$7$6$1           =  epsilon | $',' 
            RESTORE_statement$1$7$7             =  epsilon | *RESTORE_statement$1$7$7$1 *RESTORE_statement$1$7$7$2 
            RESTORE_statement$1$7$7$1           =  epsilon | $',' 
            RESTORE_statement$1$7$7$2           =  NOREWIND | REWIND 
            RESTORE_statement$1$7$8             =  epsilon | *RESTORE_statement$1$7$8$1 *RESTORE_statement$1$7$8$2 
            RESTORE_statement$1$7$8$1           =  epsilon | $',' 
            RESTORE_statement$1$7$8$2           =  NOUNLOAD | UNLOAD 
            RESTORE_statement$1$7$9             =  epsilon | *RESTORE_statement$1$7$9$1 REPLACE 
            RESTORE_statement$1$7$9$1           =  epsilon | $',' 
            RESTORE_statement$1$7$10            =  epsilon | *RESTORE_statement$1$7$10$1 RESTRICTED_USER 
            RESTORE_statement$1$7$10$1          =  epsilon | $',' 
            RESTORE_statement$1$7$11            =  epsilon | *RESTORE_statement$1$7$11$1 RESTART 
            RESTORE_statement$1$7$11$1          =  epsilon | $',' 
            RESTORE_statement$1$7$12            =  epsilon | *RESTORE_statement$1$7$12$1 STATS *RESTORE_statement$1$7$12$2 
            RESTORE_statement$1$7$12$1          =  epsilon | $',' 
            RESTORE_statement$1$7$12$2          =  epsilon | $'=' *percentage 
            RESTORE_statement$1$8               =  *database_name | *database_name_var 
            RESTORE_statement$1$9               =  *file_or_filegroup | *RESTORE_statement$1$9 $',' *file_or_filegroup 
            RESTORE_statement$1$10              =  epsilon | FROM *RESTORE_statement$1$10$1 
            RESTORE_statement$1$10$1            =  *backup_device | *RESTORE_statement$1$10$1 $',' *backup_device 
            RESTORE_statement$1$11              =  epsilon
+                                               |  WITH
+                                                  *RESTORE_statement$1$11$1
+                                                  *RESTORE_statement$1$11$2
+                                                  *RESTORE_statement$1$11$3
+                                                  *RESTORE_statement$1$11$4
+                                                  *RESTORE_statement$1$11$5
+                                                  *RESTORE_statement$1$11$6
+                                                  *RESTORE_statement$1$11$7
+                                                  *RESTORE_statement$1$11$8
+                                                  *RESTORE_statement$1$11$9
+                                                  *RESTORE_statement$1$11$10
+                                                  *RESTORE_statement$1$11$11
+                                                  *RESTORE_statement$1$11$12 
            RESTORE_statement$1$11$1            =  epsilon | RESTRICTED_USER 
            RESTORE_statement$1$11$2            =  epsilon | *RESTORE_statement$1$11$2$1 FILE $'=' *RESTORE_statement$1$11$2$2 
            RESTORE_statement$1$11$2$1          =  epsilon | $',' 
            RESTORE_statement$1$11$2$2          =  *file_number | *file_number_variable 
            RESTORE_statement$1$11$3            =  epsilon | *RESTORE_statement$1$11$3$1 PASSWORD $'=' *RESTORE_statement$1$11$3$2 
            RESTORE_statement$1$11$3$1          =  epsilon | $',' 
            RESTORE_statement$1$11$3$2          =  *password | *password_variable 
            RESTORE_statement$1$11$4            =  epsilon | *RESTORE_statement$1$11$4$1 MEDIANAME $'=' *RESTORE_statement$1$11$4$2 
            RESTORE_statement$1$11$4$1          =  epsilon | $',' 
            RESTORE_statement$1$11$4$2          =  *media_name | *media_name_variable 
            RESTORE_statement$1$11$5            =  epsilon | *RESTORE_statement$1$11$5$1 MEDIAPASSWORD $'=' *RESTORE_statement$1$11$5$2 
            RESTORE_statement$1$11$5$1          =  epsilon | $',' 
            RESTORE_statement$1$11$5$2          =  *mediapassword | *mediapassword_variable 
            RESTORE_statement$1$11$6            =  epsilon | (!$',' MOVE *logical_file_name TO *operating_system_file_name) % $',' 
            RESTORE_statement$1$11$7            =  epsilon | *RESTORE_statement$1$11$7$1 NORECOVERY 
            RESTORE_statement$1$11$7$1          =  epsilon | $',' 
            RESTORE_statement$1$11$8            =  epsilon | *RESTORE_statement$1$11$8$1 *RESTORE_statement$1$11$8$2 
            RESTORE_statement$1$11$8$1          =  epsilon | $',' 
            RESTORE_statement$1$11$8$2          =  NOREWIND | REWIND 
            RESTORE_statement$1$11$9            =  epsilon | *RESTORE_statement$1$11$9$1 *RESTORE_statement$1$11$9$2 
            RESTORE_statement$1$11$9$1          =  epsilon | $',' 
            RESTORE_statement$1$11$9$2          =  NOUNLOAD | UNLOAD 
            RESTORE_statement$1$11$10           =  epsilon | *RESTORE_statement$1$11$10$1 REPLACE 
            RESTORE_statement$1$11$10$1         =  epsilon | $',' 
            RESTORE_statement$1$11$11           =  epsilon | *RESTORE_statement$1$11$11$1 RESTART 
            RESTORE_statement$1$11$11$1         =  epsilon | $',' 
            RESTORE_statement$1$11$12           =  epsilon | *RESTORE_statement$1$11$12$1 STATS *RESTORE_statement$1$11$12$2 
            RESTORE_statement$1$11$12$1         =  epsilon | $',' 
            RESTORE_statement$1$11$12$2         =  epsilon | $'=' *percentage 
            RESTORE_statement$1$12              =  *database_name | *database_name_var 
            RESTORE_statement$1$13              =  epsilon | FROM *RESTORE_statement$1$13$1 
            RESTORE_statement$1$13$1            =  *backup_device | *RESTORE_statement$1$13$1 $',' *backup_device 
            RESTORE_statement$1$14              =  epsilon
+                                               |  WITH
+                                                  *RESTORE_statement$1$14$1
+                                                  *RESTORE_statement$1$14$2
+                                                  *RESTORE_statement$1$14$3
+                                                  *RESTORE_statement$1$14$4
+                                                  *RESTORE_statement$1$14$5
+                                                  *RESTORE_statement$1$14$6
+                                                  *RESTORE_statement$1$14$7
+                                                  *RESTORE_statement$1$14$8
+                                                  *RESTORE_statement$1$14$9
+                                                  *RESTORE_statement$1$14$10
+                                                  *RESTORE_statement$1$14$11
+                                                  *RESTORE_statement$1$14$12
+                                                  *RESTORE_statement$1$14$13 
            RESTORE_statement$1$14$1            =  epsilon | RESTRICTED_USER 
            RESTORE_statement$1$14$2            =  epsilon | *RESTORE_statement$1$14$2$1 FILE $'=' *RESTORE_statement$1$14$2$2 
            RESTORE_statement$1$14$2$1          =  epsilon | $',' 
            RESTORE_statement$1$14$2$2          =  *file_number | *file_number_variable 
            RESTORE_statement$1$14$3            =  epsilon | *RESTORE_statement$1$14$3$1 PASSWORD $'=' *RESTORE_statement$1$14$3$2 
            RESTORE_statement$1$14$3$1          =  epsilon | $',' 
            RESTORE_statement$1$14$3$2          =  *password | *password_variable 
            RESTORE_statement$1$14$4            =  epsilon | (!$',' MOVE *logical_file_name TO *operating_system_file_name) % $',' 
            RESTORE_statement$1$14$5            =  epsilon | *RESTORE_statement$1$14$5$1 MEDIANAME $'=' *RESTORE_statement$1$14$5$2 
            RESTORE_statement$1$14$5$1          =  epsilon | $',' 
            RESTORE_statement$1$14$5$2          =  *media_name | *media_name_variable 
            RESTORE_statement$1$14$6            =  epsilon | *RESTORE_statement$1$14$6$1 MEDIAPASSWORD $'=' *RESTORE_statement$1$14$6$2 
            RESTORE_statement$1$14$6$1          =  epsilon | $',' 
            RESTORE_statement$1$14$6$2          =  *mediapassword | *mediapassword_variable 
            RESTORE_statement$1$14$7            =  epsilon | *RESTORE_statement$1$14$7$1 KEEP_REPLICATION 
            RESTORE_statement$1$14$7$1          =  epsilon | $',' 
            RESTORE_statement$1$14$8            =  epsilon | *RESTORE_statement$1$14$8$1 *RESTORE_statement$1$14$8$2 
            RESTORE_statement$1$14$8$1          =  epsilon | $',' 
            RESTORE_statement$1$14$8$2          =  NORECOVERY | RECOVERY | STANDBY $'=' *RESTORE_statement$1$14$8$2$1 
            RESTORE_statement$1$14$8$2$1        =  *undo_file_name | *undo_file_name_var 
            RESTORE_statement$1$14$9            =  epsilon | *RESTORE_statement$1$14$9$1 *RESTORE_statement$1$14$9$2 
            RESTORE_statement$1$14$9$1          =  epsilon | $',' 
            RESTORE_statement$1$14$9$2          =  NOREWIND | REWIND 
            RESTORE_statement$1$14$10           =  epsilon | *RESTORE_statement$1$14$10$1 *RESTORE_statement$1$14$10$2 
            RESTORE_statement$1$14$10$1         =  epsilon | $',' 
            RESTORE_statement$1$14$10$2         =  NOUNLOAD | UNLOAD 
            RESTORE_statement$1$14$11           =  epsilon | *RESTORE_statement$1$14$11$1 RESTART 
            RESTORE_statement$1$14$11$1         =  epsilon | $',' 
            RESTORE_statement$1$14$12           =  epsilon | *RESTORE_statement$1$14$12$1 STATS *RESTORE_statement$1$14$12$2 
            RESTORE_statement$1$14$12$1         =  epsilon | $',' 
            RESTORE_statement$1$14$12$2         =  epsilon | $'=' *percentage 
            RESTORE_statement$1$14$13           =  epsilon
+                                               |  *RESTORE_statement$1$14$13$1 STOPAT $'=' *RESTORE_statement$1$14$13$2
+                                               |  *RESTORE_statement$1$14$13$3 STOPATMARK $'=' *mark_name *RESTORE_statement$1$14$13$4
+                                               |  *RESTORE_statement$1$14$13$5 STOPBEFOREMARK $'=' *mark_name *RESTORE_statement$1$14$13$6 
            RESTORE_statement$1$14$13$1         =  epsilon | $',' 
            RESTORE_statement$1$14$13$2         =  *date_time | *date_time_var 
            RESTORE_statement$1$14$13$3         =  epsilon | $',' 
            RESTORE_statement$1$14$13$4         =  epsilon | AFTER *datetime 
            RESTORE_statement$1$14$13$5         =  epsilon | $',' 
            RESTORE_statement$1$14$13$6         =  epsilon | AFTER *datetime 
            RESTORE_FILELISTONLY_statement      =  RESTORE FILELISTONLY FROM *backup_device *RESTORE_FILELISTONLY_statement$1 
            RESTORE_FILELISTONLY_statement$1    =  epsilon
+                                               |  WITH
+                                                  *RESTORE_FILELISTONLY_statement$1$1
+                                                  *RESTORE_FILELISTONLY_statement$1$2
+                                                  *RESTORE_FILELISTONLY_statement$1$3
+                                                  *RESTORE_FILELISTONLY_statement$1$4 
            RESTORE_FILELISTONLY_statement$1$1  =  epsilon | FILE $'=' *file_number 
            RESTORE_FILELISTONLY_statement$1$2  =  epsilon | *RESTORE_FILELISTONLY_statement$1$2$1 PASSWORD $'=' *RESTORE_FILELISTONLY_statement$1$2$2 
            RESTORE_FILELISTONLY_statement$1$2$1 = epsilon | $',' 
            RESTORE_FILELISTONLY_statement$1$2$2 = *password | *password_variable 
            RESTORE_FILELISTONLY_statement$1$3  =  epsilon | *RESTORE_FILELISTONLY_statement$1$3$1 MEDIAPASSWORD $'=' *RESTORE_FILELISTONLY_statement$1$3$2 
            RESTORE_FILELISTONLY_statement$1$3$1 = epsilon | $',' 
            RESTORE_FILELISTONLY_statement$1$3$2 = *mediapassword | *mediapassword_variable 
            RESTORE_FILELISTONLY_statement$1$4  =  epsilon | *RESTORE_FILELISTONLY_statement$1$4$1 *RESTORE_FILELISTONLY_statement$1$4$2 
            RESTORE_FILELISTONLY_statement$1$4$1 = epsilon | $',' 
            RESTORE_FILELISTONLY_statement$1$4$2 = NOUNLOAD | UNLOAD 
            RESTORE_HEADERONLY_statement        =  RESTORE HEADERONLY FROM *backup_device *RESTORE_HEADERONLY_statement$1 
            RESTORE_HEADERONLY_statement$1      =  epsilon
+                                               |  WITH
+                                                  *RESTORE_HEADERONLY_statement$1$1
+                                                  *RESTORE_HEADERONLY_statement$1$2
+                                                  *RESTORE_HEADERONLY_statement$1$3
+                                                  *RESTORE_HEADERONLY_statement$1$4 
            RESTORE_HEADERONLY_statement$1$1    =  NOUNLOAD | UNLOAD 
            RESTORE_HEADERONLY_statement$1$2    =  epsilon | *RESTORE_HEADERONLY_statement$1$2$1 FILE $'=' *file_number 
            RESTORE_HEADERONLY_statement$1$2$1  =  epsilon | $',' 
            RESTORE_HEADERONLY_statement$1$3    =  epsilon | *RESTORE_HEADERONLY_statement$1$3$1 PASSWORD $'=' *RESTORE_HEADERONLY_statement$1$3$2 
            RESTORE_HEADERONLY_statement$1$3$1  =  epsilon | $',' 
            RESTORE_HEADERONLY_statement$1$3$2  =  *password | *password_variable 
            RESTORE_HEADERONLY_statement$1$4    =  epsilon | *RESTORE_HEADERONLY_statement$1$4$1 MEDIAPASSWORD $'=' *RESTORE_HEADERONLY_statement$1$4$2 
            RESTORE_HEADERONLY_statement$1$4$1  =  epsilon | $',' 
            RESTORE_HEADERONLY_statement$1$4$2  =  *mediapassword | *mediapassword_variable 
            RESTORE_LABELONLY_statement         =  RESTORE LABELONLY FROM *backup_device *RESTORE_LABELONLY_statement$1 *RESTORE_LABELONLY_statement$2 
            RESTORE_LABELONLY_statement$1       =  epsilon | WITH *RESTORE_LABELONLY_statement$1$1 
            RESTORE_LABELONLY_statement$1$1     =  NOUNLOAD | UNLOAD 
            RESTORE_LABELONLY_statement$2       =  epsilon | *RESTORE_LABELONLY_statement$2$1 MEDIAPASSWORD $'=' *RESTORE_LABELONLY_statement$2$2 
            RESTORE_LABELONLY_statement$2$1     =  epsilon | $',' 
            RESTORE_LABELONLY_statement$2$2     =  *mediapassword | *mediapassword_variable 
            RESTORE_VERIFYONLY_statement        =  RESTORE VERIFYONLY FROM *RESTORE_VERIFYONLY_statement$1 *RESTORE_VERIFYONLY_statement$2 
            RESTORE_VERIFYONLY_statement$1      =  *backup_device | *RESTORE_VERIFYONLY_statement$1 $',' *backup_device 
            RESTORE_VERIFYONLY_statement$2      =  epsilon
+                                               |  WITH
+                                                  *RESTORE_VERIFYONLY_statement$2$1
+                                                  *RESTORE_VERIFYONLY_statement$2$2
+                                                  *RESTORE_VERIFYONLY_statement$2$3
+                                                  *RESTORE_VERIFYONLY_statement$2$4
+                                                  *RESTORE_VERIFYONLY_statement$2$5
+                                                  *RESTORE_VERIFYONLY_statement$2$6 
            RESTORE_VERIFYONLY_statement$2$1    =  epsilon | FILE $'=' *file_number 
            RESTORE_VERIFYONLY_statement$2$2    =  epsilon | *RESTORE_VERIFYONLY_statement$2$2$1 *RESTORE_VERIFYONLY_statement$2$2$2 
            RESTORE_VERIFYONLY_statement$2$2$1  =  epsilon | $',' 
            RESTORE_VERIFYONLY_statement$2$2$2  =  NOUNLOAD | UNLOAD 
            RESTORE_VERIFYONLY_statement$2$3    =  epsilon | *RESTORE_VERIFYONLY_statement$2$3$1 LOADHISTORY 
            RESTORE_VERIFYONLY_statement$2$3$1  =  epsilon | $',' 
            RESTORE_VERIFYONLY_statement$2$4    =  epsilon | *RESTORE_VERIFYONLY_statement$2$4$1 PASSWORD $'=' *RESTORE_VERIFYONLY_statement$2$4$2 
            RESTORE_VERIFYONLY_statement$2$4$1  =  epsilon | $',' 
            RESTORE_VERIFYONLY_statement$2$4$2  =  *password | *password_variable 
            RESTORE_VERIFYONLY_statement$2$5    =  epsilon | *RESTORE_VERIFYONLY_statement$2$5$1 MEDIAPASSWORD $'=' *RESTORE_VERIFYONLY_statement$2$5$2 
            RESTORE_VERIFYONLY_statement$2$5$1  =  epsilon | $',' 
            RESTORE_VERIFYONLY_statement$2$5$2  =  *mediapassword | *mediapassword_variable 
            RESTORE_VERIFYONLY_statement$2$6    =  epsilon | *RESTORE_VERIFYONLY_statement$2$6$1 *RESTORE_VERIFYONLY_statement$2$6$2 
            RESTORE_VERIFYONLY_statement$2$6$1  =  epsilon | $',' 
            RESTORE_VERIFYONLY_statement$2$6$2  =  NOREWIND | REWIND 
            REVOKE_statement                    =  REVOKE *REVOKE_statement$1 
            REVOKE_statement$1                  =  *REVOKE_statement$1$1 FROM *REVOKE_statement$1$2
+                                               |  *REVOKE_statement$1$3
+                                                  *REVOKE_statement$1$4
+                                                  *REVOKE_statement$1$5
+                                                  *REVOKE_statement$1$6
+                                                  *REVOKE_statement$1$7
+                                                  *REVOKE_statement$1$8
+                                                  *REVOKE_statement$1$9 
            REVOKE_statement$1$1                =  ALL | *REVOKE_statement$1$1$1 
            REVOKE_statement$1$1$1              =  *statement | *REVOKE_statement$1$1$1 $',' *statement 
            REVOKE_statement$1$2                =  *security_account | *REVOKE_statement$1$2 $',' *security_account 
            REVOKE_statement$1$3                =  epsilon | GRANT OPTION FOR 
            REVOKE_statement$1$4                =  ALL *REVOKE_statement$1$4$1 | *REVOKE_statement$1$4$2 
            REVOKE_statement$1$4$1              =  epsilon | PRIVILEGES 
            REVOKE_statement$1$4$2              =  *permission | *REVOKE_statement$1$4$2 $',' *permission 
            REVOKE_statement$1$5                =  *REVOKE_statement$1$5$1 ON *table_or_view
+                                               |  ON *table_or_view *REVOKE_statement$1$5$2
+                                               |  ON *REVOKE_statement$1$5$3
+                                               |  ON *user_defined_function 
            REVOKE_statement$1$5$1              =  epsilon | $'(' *REVOKE_statement$1$5$1$1 $')' 
            REVOKE_statement$1$5$1$1            =  *column_name | *REVOKE_statement$1$5$1$1 $',' *column_name 
            REVOKE_statement$1$5$2              =  epsilon | $'(' *REVOKE_statement$1$5$2$1 $')' 
            REVOKE_statement$1$5$2$1            =  *column_name | *REVOKE_statement$1$5$2$1 $',' *column_name 
            REVOKE_statement$1$5$3              =  *stored_procedure | *extended_procedure 
            REVOKE_statement$1$6                =  TO | FROM 
            REVOKE_statement$1$7                =  *security_account | *REVOKE_statement$1$7 $',' *security_account 
            REVOKE_statement$1$8                =  epsilon | CASCADE 
            REVOKE_statement$1$9                =  epsilon | AS *REVOKE_statement$1$9$1 
            REVOKE_statement$1$9$1              =  *group | *role 
            ROLLBACK_TRANSACTION_statement      =  ROLLBACK *ROLLBACK_TRANSACTION_statement$1 *ROLLBACK_TRANSACTION_statement$2 
            ROLLBACK_TRANSACTION_statement$1    =  TRAN | TRANSACTION 
            ROLLBACK_TRANSACTION_statement$2    =  epsilon | *transaction_name | *tran_name_variable | *savepoint_name | *savepoint_variable 
            ROLLBACK_statement                  =  ROLLBACK *ROLLBACK_statement$1 
            ROLLBACK_statement$1                =  epsilon | WORK 
            SAVE_TRANSACTION_statement          =  SAVE *SAVE_TRANSACTION_statement$1 *SAVE_TRANSACTION_statement$2 
            SAVE_TRANSACTION_statement$1        =  TRAN | TRANSACTION 
            SAVE_TRANSACTION_statement$2        =  *savepoint_name | *savepoint_variable 
            SELECT_variable_statement           =  SELECT
+                                                  *SELECT_variable_statement$1
+                                                  *SELECT_variable_statement$2
+                                                  *SELECT_variable_statement$3
+                                                  *SELECT_variable_statement$4
+                                                  *SELECT_variable_statement$5 
            SELECT_variable_statement$1         =  *SELECT_variable_statement$1$0 | *SELECT_variable_statement$1 $',' *SELECT_variable_statement$1$0 
            SELECT_variable_statement$1$0       =  *local_variable $'=' *expression 
            SELECT_variable_statement$2         =  epsilon | FROM *SELECT_variable_statement$2$1 
            SELECT_variable_statement$2$1       =  *select_source | *SELECT_variable_statement$2$1 $',' *select_source 
            SELECT_variable_statement$3         =  epsilon | WHERE *search_condition 
            SELECT_variable_statement$4         =  epsilon | GROUP BY *SELECT_variable_statement$4$1 *SELECT_variable_statement$4$2 
            SELECT_variable_statement$4$1       =  epsilon | ALL 
            SELECT_variable_statement$4$2       =  *group_by_expression | *SELECT_variable_statement$4$2 $',' *group_by_expression 
            SELECT_variable_statement$5         =  epsilon | HAVING *search_condition 
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
            SELECT_Clause                       =  SELECT *SELECT_Clause$1 *SELECT_Clause$2 *select_list 
            SELECT_Clause$1                     =  epsilon | ALL | DISTINCT 
            SELECT_Clause$2                     =  epsilon | TOP *n *SELECT_Clause$2$1 *SELECT_Clause$2$2 
            SELECT_Clause$2$1                   =  epsilon | PERCENT 
            SELECT_Clause$2$2                   =  epsilon | WITH TIES 
            INTO_Clause                         =  epsilon | INTO *new_table 
            WHERE_Clause                        =  epsilon | WHERE *search_condition | *old_outer_join 
            old_outer_join                      =  *column_name *old_outer_join$1 *column_name 
            old_outer_join$1                    =  $'*' $'=' | $'=' $'*' 
            GROUP_BY_Clause                     =  epsilon | GROUP BY *GROUP_BY_Clause$1 *GROUP_BY_Clause$2 *GROUP_BY_Clause$3 
            GROUP_BY_Clause$1                   =  epsilon | ALL 
            GROUP_BY_Clause$2                   =  *group_by_expression | *GROUP_BY_Clause$2 $',' *group_by_expression 
            GROUP_BY_Clause$3                   =  epsilon | WITH *GROUP_BY_Clause$3$1 
            GROUP_BY_Clause$3$1                 =  CUBE | ROLLUP 
            HAVING_Clause                       =  epsilon | HAVING *search_condition 
            UNION_Operator                      =  *UNION_Operator$1 UNION *UNION_Operator$2 *query_specification | $'(' *query_expression $')' *UNION_Operator$3 
            UNION_Operator$1                    =  *query_specification | $'(' *query_expression $')' 
            UNION_Operator$2                    =  epsilon | ALL 
            UNION_Operator$3                    =  epsilon | *UNION_Operator$3 *UNION_Operator$3$0 
            UNION_Operator$3$0                  =  UNION *UNION_Operator$3$1 *UNION_Operator$3$2 
            UNION_Operator$3$1                  =  epsilon | ALL 
            UNION_Operator$3$2                  =  *query_specification | $'(' *query_expression $')' 
            ORDER_BY_Clause                     =  epsilon | ORDER BY *ORDER_BY_Clause$1 
            ORDER_BY_Clause$1                   =  *ORDER_BY_Clause$1$0 | *ORDER_BY_Clause$1 $',' *ORDER_BY_Clause$1$0 
            ORDER_BY_Clause$1$0                 =  *order_by_expression *ORDER_BY_Clause$1$1 
            ORDER_BY_Clause$1$1                 =  epsilon | ASC | DESC 
            COMPUTE_Clause                      =  epsilon | COMPUTE *COMPUTE_Clause$1 *COMPUTE_Clause$2 
            COMPUTE_Clause$1                    =  *COMPUTE_Clause$1$0 | *COMPUTE_Clause$1 $',' *COMPUTE_Clause$1$0 
            COMPUTE_Clause$1$0                  =  *COMPUTE_Clause$1$1 $'(' *expression $')' 
            COMPUTE_Clause$1$1                  =  AVG | COUNT | MAX | MIN | STDEV | STDEVP | VAR | VARP | SUM 
            COMPUTE_Clause$2                    =  epsilon | BY *COMPUTE_Clause$2$1 
            COMPUTE_Clause$2$1                  =  *expression | *COMPUTE_Clause$2$1 $',' *expression 
            FOR_Clause                          =  epsilon | FOR *FOR_Clause$1 
            FOR_Clause$1                        =  BROWSE | XML *FOR_Clause$1$1 *FOR_Clause$1$2 *FOR_Clause$1$3 *FOR_Clause$1$4 
            FOR_Clause$1$1                      =  RAW | AUTO | EXPLICIT 
            FOR_Clause$1$2                      =  epsilon | $',' XMLDATA 
            FOR_Clause$1$3                      =  epsilon | $',' ELEMENTS 
            FOR_Clause$1$4                      =  epsilon | $',' BINARY BASE64 
            OPTION_Clause                       =  epsilon | OPTION $'(' *OPTION_Clause$1 $')' 
            OPTION_Clause$1                     =  *select_query_hint | *OPTION_Clause$1 $',' *select_query_hint 
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
            SET_variable_statement              =  SET *SET_variable_statement$1 *SET_variable_statement$2 
            SET_variable_statement$1            =  *local_variable $'=' *SET_variable_statement$1$1 | *cursor_variable $'=' *SET_variable_statement$1$2 
            SET_variable_statement$1$1          =  *expression | $'{' FN *identifier $'(' *SET_variable_statement$1$1$1 $')' $'}' 
            SET_variable_statement$1$1$1        =  epsilon | *expression % $',' 
            SET_variable_statement$1$2          =  *cursor_variable
+                                               |  *cursor_name
+                                               |  CURSOR
+                                                  *SET_variable_statement$1$2$1
+                                                  *SET_variable_statement$1$2$2
+                                                  *SET_variable_statement$1$2$3
+                                                  *SET_variable_statement$1$2$4
+                                                  *SET_variable_statement$1$2$5
+                                                  FOR
+                                                  *select_statement
+                                                  *SET_variable_statement$1$2$6 
            SET_variable_statement$1$2$1        =  epsilon | LOCAL 
            SET_variable_statement$1$2$2        =  epsilon | FORWARD_ONLY | SCROLL 
            SET_variable_statement$1$2$3        =  epsilon | STATIC | KEYSET | DYNAMIC | FAST_FORWARD 
            SET_variable_statement$1$2$4        =  epsilon | READ_ONLY | SCROLL_LOCKS | OPTIMISTIC 
            SET_variable_statement$1$2$5        =  epsilon | TYPE_WARNING 
            SET_variable_statement$1$2$6        =  epsilon | FOR *SET_variable_statement$1$2$6$1 
            SET_variable_statement$1$2$6$1      =  READ ONLY | UPDATE *SET_variable_statement$1$2$6$1$1 
            SET_variable_statement$1$2$6$1$1    =  epsilon | OF *SET_variable_statement$1$2$6$1$1$1 
            SET_variable_statement$1$2$6$1$1$1  =  *column_name | *SET_variable_statement$1$2$6$1$1$1 $',' *column_name 
            SET_variable_statement$2            =  epsilon | $';' 
            SET_statement                       =  SET *SET_statement$1 
            SET_statement$1                     =  ANSI_DEFAULTS *SET_statement$1$1
+                                               |  ANSI_NULL_DFLT_OFF *SET_statement$1$2
+                                               |  ANSI_NULL_DFLT_ON *SET_statement$1$3
+                                               |  ANSI_NULLS *SET_statement$1$4
+                                               |  ANSI_PADDING *SET_statement$1$5
+                                               |  ANSI_WARNINGS *SET_statement$1$6
+                                               |  ARITHABORT *SET_statement$1$7
+                                               |  ARITHIGNORE *SET_statement$1$8
+                                               |  CONCAT_NULL_YIELDS_NULL *SET_statement$1$9
+                                               |  CONTEXT_INFO *SET_statement$1$10
+                                               |  CURSOR_CLOSE_ON_COMMIT *SET_statement$1$11
+                                               |  DATEFIRST *SET_statement$1$12
+                                               |  DATEFORMAT *SET_statement$1$13
+                                               |  DEADLOCK_PRIORITY *SET_statement$1$14
+                                               |  DISABLE_DEF_CNST_CHK
+                                               |  FIPS_FLAGGER *level
+                                               |  FMTONLY *SET_statement$1$15
+                                               |  FORCEPLAN *SET_statement$1$16
+                                               |  IDENTITY_INSERT *table *SET_statement$1$17
+                                               |  IMPLICIT_TRANSACTIONS *SET_statement$1$18
+                                               |  LANGUAGE *SET_statement$1$19
+                                               |  LOCK_TIMEOUT *timeout_period
+                                               |  NOCOUNT *SET_statement$1$20
+                                               |  NOEXEC *SET_statement$1$21
+                                               |  NUMERIC_ROUNDABORT *SET_statement$1$22
+                                               |  OFFSETS *keyword_list
+                                               |  PARSEONLY *SET_statement$1$23
+                                               |  QUERY_GOVERNOR_COST_LIMIT *value
+                                               |  QUOTED_IDENTIFIER *SET_statement$1$24
+                                               |  REMOTE_PROC_TRANSACTIONS *SET_statement$1$25
+                                               |  ROWCOUNT *SET_statement$1$26
+                                               |  SHOWPLAN_ALL *SET_statement$1$27
+                                               |  SHOWPLAN_TEXT *SET_statement$1$28
+                                               |  STATISTICS IO *SET_statement$1$29
+                                               |  STATISTICS PROFILE *SET_statement$1$30
+                                               |  STATISTICS TIME *SET_statement$1$31
+                                               |  TEXTSIZE *number
+                                               |  TRANSACTION ISOLATION LEVEL *SET_statement$1$32
+                                               |  XACT_ABORT *SET_statement$1$33 
            SET_statement$1$1                   =  ON | OFF 
            SET_statement$1$2                   =  ON | OFF 
            SET_statement$1$3                   =  ON | OFF 
            SET_statement$1$4                   =  ON | OFF 
            SET_statement$1$5                   =  ON | OFF 
            SET_statement$1$6                   =  ON | OFF 
            SET_statement$1$7                   =  ON | OFF 
            SET_statement$1$8                   =  ON | OFF 
            SET_statement$1$9                   =  ON | OFF 
            SET_statement$1$10                  =  *binary | *binary_var 
            SET_statement$1$11                  =  ON | OFF 
            SET_statement$1$12                  =  *number | *number_var 
            SET_statement$1$13                  =  *format | *format_var 
            SET_statement$1$14                  =  LOW | NORMAL | *deadlock_var 
            SET_statement$1$15                  =  ON | OFF 
            SET_statement$1$16                  =  ON | OFF 
            SET_statement$1$17                  =  ON | OFF 
            SET_statement$1$18                  =  ON | OFF 
            SET_statement$1$19                  =  *SET_statement$1$19$1 *language | *language_var 
            SET_statement$1$19$1                =  epsilon | N 
            SET_statement$1$20                  =  ON | OFF 
            SET_statement$1$21                  =  ON | OFF 
            SET_statement$1$22                  =  ON | OFF 
            SET_statement$1$23                  =  ON | OFF 
            SET_statement$1$24                  =  ON | OFF 
            SET_statement$1$25                  =  ON | OFF 
            SET_statement$1$26                  =  *number | *number_var 
            SET_statement$1$27                  =  ON | OFF 
            SET_statement$1$28                  =  ON | OFF 
            SET_statement$1$29                  =  ON | OFF 
            SET_statement$1$30                  =  ON | OFF 
            SET_statement$1$31                  =  ON | OFF 
            SET_statement$1$32                  =  READ COMMITTED | READ UNCOMMITTED | REPEATABLE READ | SERIALIZABLE 
            SET_statement$1$33                  =  ON | OFF 
            SETUSER_statement                   =  SETUSER *SETUSER_statement$1 
            SETUSER_statement$1                 =  epsilon | *username *SETUSER_statement$1$1 *SETUSER_statement$1$2 
            SETUSER_statement$1$1               =  epsilon | WITH NORESET 
            SETUSER_statement$1$2               =  epsilon | $',' *at_identifier $',' *at_identifier 
            SHUTDOWN_statement                  =  SHUTDOWN *SHUTDOWN_statement$1 
            SHUTDOWN_statement$1                =  epsilon | WITH NOWAIT 
            TRUNCATE_TABLE_statement            =  TRUNCATE TABLE *table 
            UPDATE_statement                    =  UPDATE *UPDATE_statement$1 SET *UPDATE_statement$2 *UPDATE_statement$3 *UPDATE_statement$4 
            UPDATE_statement$1                  =  *UPDATE_statement$1$1 *UPDATE_statement$1$2 | *view | *rowset_function_limited 
            UPDATE_statement$1$1                =  *table | *local_variable 
            UPDATE_statement$1$2                =  epsilon | WITH $'(' *UPDATE_statement$1$2$1 $')' 
            UPDATE_statement$1$2$1              =  *table_hint_limited | *UPDATE_statement$1$2$1 *table_hint_limited 
            UPDATE_statement$2                  =  *UPDATE_statement$2$0 | *UPDATE_statement$2 $',' *UPDATE_statement$2$0 
            UPDATE_statement$2$0                =  *column $'=' *UPDATE_statement$2$1 | *variable $'=' *expression | *variable $'=' *column $'=' *expression 
            UPDATE_statement$2$1                =  *expression | DEFAULT | NULL 
            UPDATE_statement$3                  =  *UPDATE_statement$3$1 *UPDATE_statement$3$2 | *UPDATE_statement$3$3 
            UPDATE_statement$3$1                =  epsilon | FROM *UPDATE_statement$3$1$1 
            UPDATE_statement$3$1$1              =  *select_source | *UPDATE_statement$3$1$1 $',' *select_source 
            UPDATE_statement$3$2                =  epsilon | WHERE *search_condition 
            UPDATE_statement$3$3                =  epsilon | WHERE CURRENT OF *UPDATE_statement$3$3$1 
            UPDATE_statement$3$3$1              =  *UPDATE_statement$3$3$1$1 *cursor_name | *cursor_variable_name 
            UPDATE_statement$3$3$1$1            =  epsilon | GLOBAL 
            UPDATE_statement$4                  =  epsilon | OPTION $'(' *UPDATE_statement$4$1 $')' 
            UPDATE_statement$4$1                =  *update_query_hint | *UPDATE_statement$4$1 $',' *update_query_hint 
            update_query_hint                   =  *update_query_hint$1 GROUP
+                                               |  *update_query_hint$2 UNION
+                                               |  *update_query_hint$3 JOIN
+                                               |  FAST *number_rows
+                                               |  FORCE ORDER
+                                               |  MAXDOP
+                                               |  ROBUST PLAN
+                                               |  KEEP PLAN 
            update_query_hint$1                 =  HASH | ORDER 
            update_query_hint$2                 =  CONCAT | HASH | MERGE 
            update_query_hint$3                 =  LOOP | MERGE | HASH 
            UPDATE_STATISTICS_statement         =  UPDATE
+                                                  STATISTICS
+                                                  *table_or_view
+                                                  *UPDATE_STATISTICS_statement$1
+                                                  *UPDATE_STATISTICS_statement$2
+                                                  *UPDATE_STATISTICS_statement$3 
            UPDATE_STATISTICS_statement$1       =  epsilon | *index | $'(' *UPDATE_STATISTICS_statement$1$1 $')' 
            UPDATE_STATISTICS_statement$1$1     =  *statistics_name | *UPDATE_STATISTICS_statement$1$1 $',' *statistics_name 
            UPDATE_STATISTICS_statement$2       =  epsilon | WITH *UPDATE_STATISTICS_statement$2$1 | RESAMPLE 
            UPDATE_STATISTICS_statement$2$1     =  epsilon | *UPDATE_STATISTICS_statement$2$1$1 | SAMPLE *number *UPDATE_STATISTICS_statement$2$1$2 
            UPDATE_STATISTICS_statement$2$1$1   =  epsilon | FULLSCAN 
            UPDATE_STATISTICS_statement$2$1$2   =  PERCENT | ROWS 
            UPDATE_STATISTICS_statement$3       =  epsilon | *UPDATE_STATISTICS_statement$3$1 *UPDATE_STATISTICS_statement$3$2 *UPDATE_STATISTICS_statement$3$3 
            UPDATE_STATISTICS_statement$3$1     =  epsilon | $',' 
            UPDATE_STATISTICS_statement$3$2     =  epsilon | ALL | COLUMNS | INDEX 
            UPDATE_STATISTICS_statement$3$3     =  epsilon | *UPDATE_STATISTICS_statement$3$3$1 NORECOMPUTE 
            UPDATE_STATISTICS_statement$3$3$1   =  epsilon | $',' 
            UPDATETEXT_statement                =  UPDATETEXT
+                                                  *table
+                                                  $'.'
+                                                  *dest_column_name
+                                                  *dest_text_ptr
+                                                  *UPDATETEXT_statement$1
+                                                  *UPDATETEXT_statement$2
+                                                  *UPDATETEXT_statement$3
+                                                  *UPDATETEXT_statement$4 
            UPDATETEXT_statement$1              =  NULL | *insert_offset 
            UPDATETEXT_statement$2              =  NULL | *delete_length 
            UPDATETEXT_statement$3              =  epsilon | WITH LOG 
            UPDATETEXT_statement$4              =  epsilon | *inserted_data | *table_name $'.' *src_column_name *src_text_ptr 
            USE_statement                       =  USE *database 
            WRITETEXT_statement                 =  WRITETEXT *table $'.' *column_name *text_ptr *WRITETEXT_statement$1 *data 
            WRITETEXT_statement$1               =  epsilon | WITH LOG 
            DatabaseID                          =  *at_identifier 
            FileID                              =  *at_identifier 
            SqlHandle                           =  *at_identifier 
            backup_set_name_var                 =  *at_identifier 
            binary_var                          =  *at_identifier 
            blocksize_variable                  =  *at_identifier 
            cursor_variable                     =  *at_identifier 
            cursor_variable_name                =  *at_identifier 
            database_name_var                   =  *at_identifier 
            date_time_var                       =  *at_identifier 
            date_var                            =  *at_identifier 
            days_var                            =  *at_identifier 
            deadlock_var                        =  *at_identifier 
            file_number_variable                =  *at_identifier 
            filename_var                        =  *at_identifier 
            format_var                          =  *at_identifier 
            global_variable                     =  *at_at_identifier 
            language_var                        =  *at_identifier 
            level0name                          =  *at_identifier 
            level0type                          =  *at_identifier 
            level1name                          =  *at_identifier 
            level1type                          =  *at_identifier 
            level2name                          =  *at_identifier 
            level2type                          =  *at_identifier 
            local_variable                      =  *at_identifier 
            logical_backup_device_name_var      =  *at_identifier 
            logical_file_name_var               =  *at_identifier 
            logical_filegroup_name_var          =  *at_identifier 
            media_name_variable                 =  *at_identifier 
            mediapassword_variable              =  *at_identifier 
            number_var                          =  *at_identifier 
            numfiles                            =  *at_identifier 
            nvar                                =  *at_identifier 
            parameter                           =  *at_identifier 
            parameter_name                      =  *at_identifier 
            password_variable                   =  *at_identifier 
            physical_backup_device_name_var     =  *at_identifier 
            procedure_name_var                  =  *at_identifier 
            return_status                       =  *at_identifier 
            return_variable                     =  *at_identifier 
            savepoint_variable                  =  *at_identifier 
            string_variable                     =  *at_identifier 
            text_variable                       =  *at_identifier 
            traceid                             =  *at_identifier 
            tran_name_variable                  =  *at_identifier 
            undo_file_name_var                  =  *at_identifier 
            variable                            =  *identifier 
            variable_name                       =  *at_identifier 
            dont_know                           =  *identifier 
            SchemaDeclaration                   =  *dont_know 
            Sql_Handle                          =  *dont_know 
            TableName                           =  *dont_know 
            alias                               =  *table_or_view | *identifier 
            column                              =  *column$1 *identifier 
            column$1                            =  epsilon | *identifier $'.' 
            base64                              =  *dont_know 
            batch_size                          =  *dont_know 
            binary                              =  *dont_know 
            catalog                             =  *dont_know 
            catalog_name                        =  *dont_know 
            char                                =  *dont_know 
            character_string                    =  *expression 
            code_page                           =  *dont_know 
            column_id                           =  *dont_know 
            column_list                         =  *identifier | *column_list $',' *identifier 
            condition_expression                =  *dont_know 
            data                                =  *dont_know 
            data_file                           =  *dont_know 
            datasource                          =  *dont_know 
            date_expression                     =  *expression 
            date_time                           =  *dont_know 
            datetime_expression                 =  *dont_know 
            decimal                             =  *expression 
            delete_length                       =  *integer_literal 
            description                         =  *dont_know 
            dest_column_name                    =  *identifier 
            dest_text_ptr                       =  *local_variable 
            enddate                             =  *dont_know 
            field_terminator                    =  *dont_know 
            filegroup_id                        =  *dont_know 
            filegroup_property                  =  *dont_know 
            filename                            =  *dont_know 
            first_row                           =  *dont_know 
            flags                               =  *dont_know 
            format                              =  *dont_know 
            format_file_path                    =  *dont_know 
            global                              =  *dont_know 
            grant_statement                     =  *dont_know 
            idoc                                =  *dont_know 
            index_val                           =  *integer_literal 
            init_string                         =  *dont_know 
            insert_offset                       =  *integer_literal 
            inserted_data                       =  *local_variable 
            join_hint                           =  *dont_know 
            key_ID                              =  *dont_know 
            key_id                              =  *dont_know 
            keyword_list                        =  *dont_know 
            kilobytes_per_batch                 =  *dont_know 
            label                               =  *identifier 
            language                            =  *dont_know 
            last_row                            =  *dont_know 
            level                               =  *dont_know 
            level0_object_name                  =  *dont_know 
            level0_object_type                  =  *dont_know 
            level1_object_name                  =  *dont_know 
            level1_object_type                  =  *dont_know 
            level2_object_name                  =  *dont_know 
            level2_object_type                  =  *dont_know 
            linked_server                       =  *dont_know 
            literal                             =  *dont_know 
            literal_value                       =  *binary_literal
+                                               |  *literal_value$1 *real_literal
+                                               |  *literal_value$2 *integer_literal
+                                               |  *string_literal
+                                               |  *money_literal 
            literal_value$1                     =  epsilon | $'+' | $'-' 
            literal_value$2                     =  epsilon | $'+' | $'-' 
            local                               =  *dont_know 
            logical_backup_device_name          =  *dont_know 
            logical_filegroup_name              =  *dont_know 
            match_expression                    =  *dont_know 
            max_errors                          =  *dont_know 
            msg_number                          =  *dont_know 
            name                                =  *identifier 
            native                              =  *dont_know 
            ncharacter_expression               =  *dont_know 
            new_data_type                       =  *data_type 
            new_dbname                          =  *dont_know 
            new_filegroup_name                  =  *dont_know 
            new_logical_name                    =  *dont_know 
            number_files                        =  *dont_know 
            object_name                         =  *dont_know 
            object_piece                        =  *dont_know 
            objectid                            =  *expression 
            offset                              =  *at_identifier 
            param_value                         =  *dont_know 
            pattern                             =  *dont_know 
            physical_backup_device_name         =  *dont_know 
            precision                           =  *dont_know 
            property_name                       =  *dont_know 
            propertyname                        =  *string_expression 
            provider_string                     =  *dont_know 
            quote_character                     =  *dont_know 
            row_terminator                      =  *dont_know 
            rowpattern                          =  *dont_know 
            rows_per_batch                      =  *dont_know 
            rowset_function                     =  OPENROWSET $'(' *rowset_function$1 $')' 
            rowset_function$1                   =  epsilon | *expression % $',' 
            scalar_data_type                    =  *data_type 
            scalar_subquery                     =  *query_specification *scalar_subquery$1 
            scalar_subquery$1                   =  epsilon | ORDER BY *scalar_subquery$1$1 
            scalar_subquery$1$1                 =  *scalar_subquery$1$1$0 | *scalar_subquery$1$1 $',' *scalar_subquery$1$1$0 
            scalar_subquery$1$1$0               =  *order_by_expression *scalar_subquery$1$1$1 
            scalar_subquery$1$1$1               =  epsilon | ASC | DESC 
            scale                               =  *dont_know 
            schema                              =  *dont_know 
            server_user_id                      =  *dont_know 
            server_user_sid                     =  *dont_know 
            spid                                =  *dont_know 
            src_column_name                     =  *identifier 
            src_text_ptr                        =  *local_variable 
            start_location                      =  *dont_know 
            startdate                           =  *dont_know 
            string_expr                         =  *string_literal 
            string_expression1                  =  *expression 
            string_expression2                  =  *expression 
            string_expression3                  =  *expression 
            style                               =  *expression 
            system_function                     =  CONVERT $'(' *data_type $',' *expression *system_function$1 $')'
+                                               |  DB_NAME $'(' *system_function$2 $')'
+                                               |  GETDATE $'(' $')'
+                                               |  NEWID $'(' $')'
+                                               |  ISNULL $'(' *expression $',' *expression $')'
+                                               |  SUSER_SID $'(' *system_function$3 $')' 
            system_function$1                   =  epsilon | $',' *style 
            system_function$2                   =  epsilon | *database_id 
            system_function$3                   =  epsilon | *login 
            table_definition                    =  *dont_know 
            test_expression                     =  *dont_know 
            time_expression                     =  *string_expression 
            timeout_period                      =  *integer_literal 
            tsql_string                         =  *string_literal 
            type                                =  *dont_know 
            user                                =  *string_expression 
            user_id                             =  *dont_know 
            username                            =  *local_variable 
            view_definition                     =  *dont_know 
            view_hint                           =  *dont_know 
            widechar                            =  *dont_know 
            widenative                          =  *dont_know 
            backup_set_name                     =  *identifier 
            bitwise_operator                    =  $'&' | $'|' 
            blocksize                           =  *integer_expression 
            column_alias                        =  *identifier | *string_literal 
            column_bitmask                      =  *integer_expression 
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
            computed_column_expression          =  *expression 
            constant_expression                 =  *literal_value
+                                               |  NULL
+                                               |  *true
+                                               |  *false
+                                               |  *system_function
+                                               |  *local_variable
+                                               |  *global_variable
+                                               |  $'(' *constant_expression $')' 
            constraint_name                     =  *identifier 
            cursor_name                         =  *identifier 
            database                            =  *identifier 
            database_id                         =  *identifier 
            date                                =  *date_expression 
            datepart                            =  YEAR | QUARTER | MONTH | DAYOFYEAR | DAY | WEEK | HOUR | MINUTE | SECOND | MILLISECOND | *identifier 
            datetime                            =  *datetime_expression 
            days                                =  *integer_expression 
            derived_table                       =  *select_statement 
            escape_character                    =  *string_literal 
            extended_procedure                  =  *identifier 
            file_id                             =  *integer_literal 
            file_name                           =  *string_literal 
            file_number                         =  *integer_literal 
            filegroup_name                      =  *string_literal 
            fillfactor                          =  *integer_literal 
            freetext_string                     =  *string_literal 
            function_body                       =  *Transact_SQL_statement | *function_body *Transact_SQL_statement 
            group                               =  *identifier 
            group_by_expression                 =  *expression 
            growth_increment                    =  *integer_literal 
            increment                           =  *integer_literal 
            index_id                            =  *expression 
            length                              =  *expression 
            logical_expression                  =  *boolean_expression 
            logical_file_name                   =  *string_literal 
            login                               =  *string_literal 
            mark_name                           =  *string_literal 
            max_size                            =  *integer_literal 
            media_name                          =  *string_literal 
            mediapassword                       =  *string_literal 
            n                                   =  *integer_literal 
            new_table                           =  *identifier 
            number                              =  *integer_literal 
            number_rows                         =  *integer_literal 
            object                              =  *identifier 
            object_id                           =  *identifier 
            object_type                         =  *string_expression 
            operating_system_file_name          =  *string_literal 
            order_by_expression                 =  *integer_literal | *expression 
            os_file_name                        =  *string_literal 
            p                                   =  *integer_literal 
            password                            =  *string_literal 
            percentage                          =  *integer_literal 
            permission                          =  SELECT | INSERT | DELETE | REFERENCES | UPDATE | EXEC | EXECUTE 
            property                            =  *string_literal 
            provider_name                       =  *identifier 
            query                               =  *string_literal 
            ref_column                          =  *identifier 
            role                                =  *identifier 
            rowset_function_limited             =  OPENQUERY $'(' *linked_server $',' *query $')'
+                                               |  OPENROWSET $'(' *provider_name $',' *rowset_function_limited$1 $',' *rowset_function_limited$2 $')' 
            rowset_function_limited$1           =  *datasource $';' *user_id $';' *password | *provider_string 
            rowset_function_limited$2           =  *rowset_function_limited$2$1 *rowset_function_limited$2$2 *object | *query 
            rowset_function_limited$2$1         =  epsilon | *catalog $'.' 
            rowset_function_limited$2$2         =  epsilon | *schema $'.' 
            s                                   =  *integer_literal 
            savepoint_name                      =  *identifier 
            scalar_expression                   =  *expression 
            scalar_parameter_data_type          =  *data_type 
            scalar_return_data_type             =  *data_type 
            search_conditions                   =  *string_literal 
            security_account                    =  *identifier | PUBLIC | NULL 
            seed                                =  *integer_literal 
            select_statement                    =  *SELECT_statement 
            select_stmt                         =  *query_specification 
            size                                =  *integer_literal | *at_identifier 
            start                               =  *integer_literal 
            statement                           =  CREATE DATABASE
+                                               |  CREATE DEFAULT
+                                               |  CREATE FUNCTION
+                                               |  CREATE PROCEDURE
+                                               |  CREATE RULE
+                                               |  CREATE TABLE
+                                               |  CREATE VIEW
+                                               |  BACKUP DATABASE
+                                               |  BACKUP LOG 
            stored_procedure                    =  *identifier 
            subquery                            =  *select_statement 
            table_ID                            =  *identifier 
            table_alias                         =  *identifier 
            table_id                            =  *identifier 
            target_name                         =  *identifier 
            text                                =  *string_literal 
            text_ptr                            =  *string_literal | *at_identifier 
            time                                =  *time_expression 
            top_n_by_rank                       =  *integer_literal 
            trace_id                            =  *identifier 
            transaction_name                    =  *identifier 
            undo_file_name                      =  *string_literal | *local_variable 
            updated_bitmask                     =  *integer_literal 
            user_defined_function               =  *identifier 
            value                               =  *literal 
            default                             =  *default$1 *default_name 
            default$1                           =  epsilon | *owner_name $'.' 
            function                            =  *function$1 *function_name 
            function$1                          =  epsilon | *database_name $'.' *function$1$1 $'.' | *owner_name $'.' 
            function$1$1                        =  epsilon | *owner_name 
            procedure                           =  *procedure$1 *procedure$2 
            procedure$1                         =  epsilon | *servername $'.' 
            procedure$2                         =  *procedure$2$1 *procedure_name 
            procedure$2$1                       =  epsilon | *database_name $'.' *procedure$2$1$1 $'.' | *owner_name $'.' 
            procedure$2$1$1                     =  epsilon | *owner_name 
            servername                          =  *identifier 
            rule                                =  *rule$1 *rule_name 
            rule$1                              =  epsilon | *owner_name $'.' 
            index                               =  *index$1 *index_name 
            index$1                             =  epsilon | *table_or_view $'.' 
            ref_table                           =  *ref_table$1 *table_name 
            ref_table$1                         =  epsilon | *database_name $'.' *ref_table$1$1 $'.' | *owner_name $'.' 
            ref_table$1$1                       =  epsilon | *owner_name 
            table                               =  *table$1 *table_name 
            table$1                             =  epsilon | *database_name $'.' *table$1$1 $'.' | *owner_name $'.' 
            table$1$1                           =  epsilon | *owner_name 
            table_or_view                       =  *table_or_view$1 *table_or_view_name 
            table_or_view$1                     =  epsilon | *database_name $'.' *table_or_view$1$1 $'.' | *owner_name $'.' 
            table_or_view$1$1                   =  epsilon | *owner_name 
            trigger                             =  *trigger$1 *rule_name 
            trigger$1                           =  epsilon | *owner_name $'.' 
            view                                =  *view$1 *view_name 
            view$1                              =  epsilon | *database_name $'.' *view$1$1 $'.' | *owner_name $'.' 
            view$1$1                            =  epsilon | *owner_name 
            database_name                       =  *identifier 
            default_name                        =  *identifier 
            function_name                       =  *identifier 
            index_name                          =  *identifier 
            owner_name                          =  *identifier 
            procedure_name                      =  *identifier 
            rule_name                           =  *identifier 
            schema_name                         =  *identifier 
            statistics_name                     =  *identifier 
            table_name                          =  *identifier 
            trigger_name                        =  *identifier 
            view_name                           =  *identifier 
            table_or_view_name                  =  *identifier 
