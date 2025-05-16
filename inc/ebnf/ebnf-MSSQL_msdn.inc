            SQL_batches                         =  nPush() *SQL_batch nInc() ARBNO(*SQL_batch nInc()) ("'SQL_batches'" & 'nTop()') nPop()
            SQL_batch                           =  (  *CREATE_FUNCTION_statement ("'SQL_batch'" & '1')
+                                                  |  *CREATE_PROCEDURE_statement ("'SQL_batch'" & '1')
+                                                  |  *CREATE_TRIGGER_statement ("'SQL_batch'" & '1')
+                                                  |  nPush() (*execute_clause | epsilon) ARBNO(*Transact_SQL_statement nInc()) ("'SQL_batch'" & 'nTop()') nPop()
+                                                  )
+                                                  GO FENCE
            Transact_SQL_statement              =  (*label $':' | epsilon) (*control_of_flow_statement | *sql_statement) ($';' | epsilon)
            control_of_flow_statement           =  *BEGIN_END_block
+                                               |  *IF_ELSE_statement
+                                               |  *WHILE_statement
+                                               |  BREAK ("'BREAK_statement'" & '0')
+                                               |  CONTINUE ("'CONTINUE_statement'" & '0')
+                                               |  GOTO *label ("'GOTO_statement'" & '0')
+                                               |  RETURN (*integer_expression | epsilon) ("'RETURN_statement'" & '0')
+                                               |  WAITFOR (DELAY *time | TIME *time) ("'WAITFOR_statement'" & '0')
            BEGIN_END_block                     =  nPush() BEGIN ARBNO(*Transact_SQL_statement nInc()) END ("'BEGIN_END_block'" & 'nTop()') nPop()
            IF_ELSE_statement                   =  IF
+                                                  *boolean_expression
+                                                  *Transact_SQL_statement
+                                                  (  nPush() *ELSE_IF_statements (*ELSE_statement | epsilon ~ '') ("'IF_ELSE_IF_statement'" & 'nTop() + 2') nPop()
+                                                  |  *ELSE_statement ("'IF_ELSE_statement'" & '2')
+                                                  |  ("'IF_statement'" & '1')
+                                                  )
            ELSE_statement                      =  ELSE *Transact_SQL_statement
            ELSE_IF_statements                  =  ELSE IF *boolean_expression *Transact_SQL_statement nInc() (*ELSE_IF_statements | *epsilon)
            WHILE_statement                     =  WHILE *boolean_expression *Transact_SQL_statement ("'WHILE_statement'" & '1')
            boolean_expression                  =  *search_condition1
            search_condition                    =  *search_condition1
            search_condition1                   =  *search_condition2 ARBNO(OR *search_condition2)
            search_condition2                   =  *search_condition3 ARBNO(AND *search_condition3)
            search_condition3                   =  *search_condition4 | NOT *search_condition3
            search_condition4                   =  *search_condition5 ARBNO($'^' *search_condition5 | $'|' *search_condition5)
            search_condition5                   =  *search_condition6
+                                                  (  *comparison_operator (ALL | SOME | ANY) $'(' *subquery $')'
+                                                  |  (*comparison_operator | $'*=' | $'=*') *search_condition6
+                                                  |  (NOT | epsilon) LIKE *search_condition6 (ESCAPE *search_condition6 | epsilon)
+                                                  |  (NOT | epsilon) BETWEEN *search_condition6 AND *search_condition6
+                                                  |  IS (NOT | epsilon) NULL
+                                                  |  (NOT | epsilon) IN $'(' (*subquery | *search_condition6 % $',') $')'
+                                                  |  epsilon
+                                                  )
+                                               |  CONTAINS $'(' (*column | $'*') $',' *string_literal $')'
+                                               |  FREETEXT $'(' (*column | $'*') $',' *freetext_string $')'
+                                               |  EXISTS $'(' *subquery $')'
            search_condition6                   =  *search_condition7 ARBNO($'+' *search_condition7 | $'-' *search_condition7 | $'&' *search_condition7)
            search_condition7                   =  *search_condition8 ARBNO($'*' *search_condition8 | $'/' *search_condition8 | $'%' *search_condition8)
            search_condition8                   =  *search_condition9 (*COLLATE_clause | epsilon)
+                                               |  $'+' *search_condition8
+                                               |  $'-' *search_condition8
+                                               |  $'~' *search_condition8
            search_condition9                   =  *constant
+                                               |  (*alias $'.' | epsilon) *column_name
+                                               |  *local_variable
+                                               |  *global_variable
+                                               |  *function_call
+                                               |  *CASE_expression
+                                               |  $'(' *scalar_subquery $')'
+                                               |  $'(' *search_condition $')'
            expression                          =  *expression1
            expression1                         =  *expression2 ARBNO($'^' *expression2 | $'|' *expression2)
            expression2                         =  *expression3
+                                                  (  $'=' *expression3
+                                                  |  $'>' *expression3
+                                                  |  $'<' *expression3
+                                                  |  $'>=' *expression3
+                                                  |  $'<=' *expression3
+                                                  |  $'<>' *expression3
+                                                  |  $'!<' *expression3
+                                                  |  $'!=' *expression3
+                                                  |  $'!>' *expression3
+                                                  |  epsilon
+                                                  )
            expression3                         =  *expression4 ARBNO($'+' *expression4 | $'-' *expression4 | $'&' *expression4)
            expression4                         =  *expression5 ARBNO($'*' *expression5 | $'/' *expression5 | $'%' *expression5)
            expression5                         =  *expression6 (*COLLATE_clause | epsilon) | $'+' *expression5 | $'-' *expression5 | $'~' *expression5
            expression6                         =  *constant
+                                               |  (*alias $'.' | epsilon) *column_name
+                                               |  *local_variable
+                                               |  *global_variable
+                                               |  *function_call
+                                               |  *CASE_expression
+                                               |  $'(' *scalar_subquery $')'
+                                               |  $'(' *expression $')'
            constant                            =  NULL | *real_literal | *binary_literal | *integer_literal | *string_literal | *money_literal
            CASE_expression                     =  CASE
+                                                  (  *expression
+                                                     WHEN *expression THEN *expression ARBNO(WHEN *expression THEN *expression)
+                                                     (ELSE *expression | epsilon)
+                                                     END
+                                                  |  WHEN *boolean_expression THEN *expression ARBNO(WHEN *boolean_expression THEN *expression)
+                                                     (ELSE *expression | epsilon)
+                                                     END
+                                                  )
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
+                                               |  *CREATE_INDEX_statement
+                                               |  *CREATE_RULE_statement
+                                               |  *CREATE_SCHEMA_statement
+                                               |  *CREATE_STATISTICS_statement
+                                               |  *CREATE_TABLE_statement
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
+                                               |  *SELECT_statement ("'SELECT_statement'" & '0')
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
+                                               |  BINARY ($'(' *n $')' | epsilon)
+                                               |  BINARY VARYING ($'(' *n $')' | epsilon)
+                                               |  BIT
+                                               |  CHAR ($'(' *n $')' | epsilon)
+                                               |  CHAR VARYING ($'(' *n $')' | epsilon)
+                                               |  CHARACTER ($'(' *n $')' | epsilon)
+                                               |  CHARACTER VARYING ($'(' *n $')' | epsilon)
+                                               |  DEC ($'(' *p ($',' *s | epsilon) $')' | epsilon)
+                                               |  DECIMAL ($'(' *p ($',' *s | epsilon) $')' | epsilon)
+                                               |  DOUBLE PRECISION
+                                               |  CURSOR
+                                               |  DATETIME
+                                               |  FLOAT ($'(' *n $')' | epsilon)
+                                               |  IMAGE
+                                               |  INT
+                                               |  INTEGER
+                                               |  MONEY
+                                               |  NATIONAL CHAR ($'(' *n $')' | epsilon)
+                                               |  NATIONAL CHAR VARYING ($'(' *n $')' | epsilon)
+                                               |  NATIONAL CHARACTER ($'(' *n $')' | epsilon)
+                                               |  NATIONAL CHARACTER VARYING ($'(' *n $')' | epsilon)
+                                               |  NATIONAL TEXT
+                                               |  NCHAR ($'(' *n $')' | epsilon)
+                                               |  NCHAR VARYING ($'(' *n $')' | epsilon)
+                                               |  NCHARACTER ($'(' *n $')' | epsilon)
+                                               |  NCHARACTER VARYING ($'(' *n $')' | epsilon)
+                                               |  NTEXT
+                                               |  NUMERIC ($'(' *p ($',' *s | epsilon) $')' | epsilon)
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
+                                               |  VARBINARY ($'(' *n $')' | epsilon)
+                                               |  VARCHAR ($'(' *n $')' | epsilon)
+                                               |  *identifier
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
+                                               |  AVG $'(' (ALL | DISTINCT | epsilon) *expression $')'
+                                               |  BINARY_CHECKSUM $'(' ($'*' | *expression) % $',' $')'
+                                               |  CAST $'(' *expression AS *data_type $')'
+                                               |  CEILING $'(' *numeric_expression $')'
+                                               |  CHAR $'(' *integer_expression $')'
+                                               |  CHARINDEX $'(' *expression $',' *expression ($',' *start_location | epsilon) $')'
+                                               |  CHECKSUM $'(' ($'*' | *expression) % $',' $')'
+                                               |  CHECKSUM_AGG $'(' (ALL | DISTINCT | epsilon) *expression $')'
+                                               |  COALESCE $'(' *expression % $',' $')'
+                                               |  COLLATIONPROPERTY $'(' *collation_name $',' *string_expression $')'
+                                               |  COLUMNPROPERTY $'(' *expression $',' *column $',' *string_expression $')'
+                                               |  COL_LENGTH $'(' *table pop() $',' *column $')'
+                                               |  COL_NAME $'(' *table_id $',' *column_id $')'
+                                               |  COS $'(' *float_expression $')'
+                                               |  COT $'(' *float_expression $')'
+                                               |  COUNT $'(' ((ALL | DISTINCT | epsilon) *expression | $'*') $')'
+                                               |  COUNT_BIG $'(' ((ALL | DISTINCT | epsilon) *expression | $'*') $')'
+                                               |  CURRENT_TIMESTAMP
+                                               |  CURRENT_USER
+                                               |  CURSOR_STATUS $'(' (*local $',' *cursor_name | *global $',' *cursor_name | *variable $',' *cursor_variable) $')'
+                                               |  DATABASEPROPERTY $'(' *string_expression $',' *string_expression $')'
+                                               |  DATABASEPROPERTYEX $'(' *string_expression $',' *string_expression $')'
+                                               |  DATALENGTH $'(' *expression $')'
+                                               |  DATEADD $'(' *datepart $',' *number $',' *date $')'
+                                               |  DATEDIFF $'(' *datepart $',' *startdate $',' *enddate $')'
+                                               |  DATENAME $'(' *datepart $',' *date $')'
+                                               |  DATEPART $'(' *datepart $',' *date $')'
+                                               |  DAY $'(' *date $')'
+                                               |  DB_ID $'(' (*database_name | epsilon) $')'
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
+                                               |  FN_GET_SQL $'(' (*SqlHandle $'=' | epsilon) *Sql_Handle $')'
+                                               |  FN_HELPCOLLATIONS $'(' $')'
+                                               |  FN_LISTEXTENDEDPROPERTY
+                                                  $'('
+                                                  (*default | (*name $'=' | epsilon) *property_name | NULL)
+                                                  $','
+                                                  (*default | (*level0type $'=' | epsilon) *level0_object_type | NULL)
+                                                  $','
+                                                  (*default | (*level0name $'=' | epsilon) *level0_object_name | NULL)
+                                                  $','
+                                                  (*default | (*level1type $'=' | epsilon) *level1_object_type | NULL)
+                                                  $','
+                                                  (*default | (*level1name $'=' | epsilon) *level1_object_name | NULL)
+                                                  $','
+                                                  (*default | (*level2type $'=' | epsilon) *level2_object_type | NULL)
+                                                  $','
+                                                  (*default | (*level2name $'=' | epsilon) *level2_object_name | NULL)
+                                                  $')'
+                                               |  FN_SERVERSHAREDDRIVES $'(' $')'
+                                               |  FN_TRACE_GETEVENTINFO $'(' (*traceid $'=' | epsilon) *trace_id $')'
+                                               |  FN_TRACE_GETFILTERINFO $'(' (*traceid $'=' | epsilon) *trace_id $')'
+                                               |  FN_TRACE_GETINFO $'(' (*traceid $'=' | epsilon) *trace_id $')'
+                                               |  FN_TRACE_GETTABLE
+                                                  $'('
+                                                  (*filename_var $'=' | epsilon)
+                                                  *filename
+                                                  $','
+                                                  (*numfiles $'=' | epsilon)
+                                                  *number_files
+                                                  $')'
+                                               |  FN_VIRTUALFILESTATS $'(' (*DatabaseID $'=' | epsilon) *database_id $',' (*FileID $'=' | epsilon) *file_id $')'
+                                               |  FN_VIRTUALSERVERNODES $'()'
+                                               |  FORMATMESSAGE $'(' *msg_number ($',' *param_value % $',' | epsilon) $')'
+                                               |  FREETEXT $'(' (*column | $'*') $',' *freetext_string $')'
+                                               |  FREETEXTTABLE $'(' *table pop() $',' (*column | $'*') $',' *freetext_string ($',' *top_n_by_rank | epsilon) $')'
+                                               |  FULLTEXTCATALOGPROPERTY $'(' *catalog_name $',' *string_expression $')'
+                                               |  FULLTEXTSERVICEPROPERTY $'(' *string_expression $')'
+                                               |  GETANSINULL $'(' (*database | epsilon) $')'
+                                               |  GETUTCDATE $'(' $')'
+                                               |  HAS_DBACCESS $'(' *database_name $')'
+                                               |  HOST_ID $'(' $')'
+                                               |  HOST_NAME $'(' $')'
+                                               |  IDENT_CURRENT $'(' *table pop() $')'
+                                               |  IDENT_INCR $'(' *table_or_view pop() $')'
+                                               |  IDENT_SEED $'(' *table_or_view pop() $')'
+                                               |  INDEXKEY_PROPERTY $'(' *table_ID $',' *index_id $',' *key_ID $',' *string_expression $')'
+                                               |  INDEXPROPERTY $'(' *table_ID $',' *index $',' *string_expression $')'
+                                               |  INDEX_COL $'(' *expression $',' *expression $',' *expression $')'
+                                               |  ISDATE $'(' *expression $')'
+                                               |  ISNUMERIC $'(' *expression $')'
+                                               |  IS_MEMBER $'(' *expression $')'
+                                               |  IS_SRVROLEMEMBER $'(' *role ($',' *login | epsilon) $')'
+                                               |  LEFT $'(' *character_expression $',' *integer_expression $')'
+                                               |  LEN $'(' *string_expression $')'
+                                               |  LOG $'(' *float_expression $')'
+                                               |  LOG10 $'(' *float_expression $')'
+                                               |  LOWER $'(' *character_expression $')'
+                                               |  LTRIM $'(' *character_expression $')'
+                                               |  MAX $'(' (ALL | DISTINCT | epsilon) *expression $')'
+                                               |  MIN $'(' (ALL | DISTINCT | epsilon) *expression $')'
+                                               |  MONTH $'(' *date $')'
+                                               |  NCHAR $'(' *integer_expression $')'
+                                               |  NULLIF $'(' *expression $',' *expression $')'
+                                               |  OBJECTPROPERTY $'(' *expression $',' *string_expression $')'
+                                               |  OBJECT_ID $'(' *string_expression ($',' *string_expression | epsilon) $')'
+                                               |  OBJECT_NAME $'(' *object_id $')'
+                                               |  OPENDATASOURCE $'(' *provider_name $',' *init_string $')'
+                                               |  PARSENAME $'(' *object_name $',' *object_piece $')'
+                                               |  PATINDEX $'(' $'%pattern%' $',' *expression $')'
+                                               |  PERMISSIONS $'(' (*objectid ($',' *column | epsilon) | epsilon) $')'
+                                               |  PI $'(' $')'
+                                               |  POWER $'(' *numeric_expression $',' *numeric_expression $')'
+                                               |  QUOTENAME $'(' *character_string ($',' *quote_character | epsilon) $')'
+                                               |  RADIANS $'(' *numeric_expression $')'
+                                               |  RAND $'(' (*seed | epsilon) $')'
+                                               |  REPLACE $'(' *string_expression1 $',' *string_expression2 $',' *string_expression3 $')'
+                                               |  REPLICATE $'(' *character_expression $',' *integer_expression $')'
+                                               |  REVERSE $'(' *character_expression $')'
+                                               |  RIGHT $'(' *character_expression $',' *integer_expression $')'
+                                               |  ROUND $'(' *numeric_expression $',' *length ($',' *dont_know | epsilon) $')'
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
+                                               |  STR $'(' *float_expression ($',' *length ($',' *decimal | epsilon) | epsilon) $')'
+                                               |  STUFF $'(' *character_expression $',' *start $',' *length $',' *character_expression $')'
+                                               |  SUBSTRING $'(' *expression $',' *expression $',' *expression $')'
+                                               |  SUM $'(' (ALL | DISTINCT | epsilon) *expression $')'
+                                               |  SUSER_ID $'(' (*login | epsilon) $')'
+                                               |  SUSER_NAME $'(' (*server_user_id | epsilon) $')'
+                                               |  SUSER_SNAME $'(' (*server_user_sid | epsilon) $')'
+                                               |  SYSTEM_USER
+                                               |  TAN $'(' *float_expression $')'
+                                               |  TEXTPTR $'(' *column $')'
+                                               |  TEXTVALID $'(' *table pop() $'.' *column $',' *text_ptr $')'
+                                               |  TRIGGER_NESTLEVEL $'(' (*object_id | epsilon) $')'
+                                               |  TYPEPROPERTY $'(' *type $',' *string_expression $')'
+                                               |  UNICODE $'(' *ncharacter_expression $')'
+                                               |  UPPER $'(' *character_expression $')'
+                                               |  USER
+                                               |  USER_ID $'(' (*user | epsilon) $')'
+                                               |  USER_NAME $'(' (*expression | epsilon) $')'
+                                               |  VAR $'(' *expression $')'
+                                               |  VARP $'(' *expression $')'
+                                               |  YEAR $'(' *date $')'
+                                               |  *rowset_function_limited
+                                               |  *system_function
+                                               |  *function pop() $'(' (*expression % $',' | epsilon) $')'
            ALTER_DATABASE_statement            =  ALTER
+                                                  DATABASE
+                                                  (*database_name) ~ 'id'
+                                                  (  ADD FILE *alter_database_filespec % $',' (TO FILEGROUP *filegroup_name | epsilon)
+                                                  |  ADD LOG FILE *alter_database_filespec % $','
+                                                  |  REMOVE FILE *logical_file_name
+                                                  |  ADD FILEGROUP *filegroup_name
+                                                  |  REMOVE FILEGROUP *filegroup_name
+                                                  |  MODIFY FILE *alter_database_filespec
+                                                  |  MODIFY NAME $'=' *new_dbname
+                                                  |  MODIFY FILEGROUP *filegroup_name (*filegroup_property | NAME $'=' *new_filegroup_name)
+                                                  |  SET *optionspec % $',' (WITH *termination | epsilon)
+                                                  |  COLLATE *collation_name
+                                                  )
+                                                  ("'ALTER_DATABASE_statement'" & '1')
            alter_database_filespec             =  $'('
+                                                  NAME
+                                                  $'='
+                                                  *logical_file_name
+                                                  ($',' NEWNAME $'=' *new_logical_name | epsilon)
+                                                  ($',' FILENAME $'=' *os_file_name | epsilon)
+                                                  ($',' SIZE $'=' *size | epsilon)
+                                                  ($',' MAXSIZE $'=' (*max_size | UNLIMITED) | epsilon)
+                                                  ($',' FILEGROWTH $'=' *growth_increment | epsilon)
+                                                  $')'
            optionspec                          =  *state_option | *cursor_option | *auto_option | *sql_option | *recovery_option
            state_option                        =  SINGLE_USER | RESTRICTED_USER | MULTI_USER | OFFLINE | ONLINE | READ_ONLY | READ_WRITE
            cursor_option                       =  CURSOR_CLOSE_ON_COMMIT (ON | OFF) | CURSOR_DEFAULT (LOCAL | GLOBAL)
            auto_option                         =  AUTO_CLOSE (ON | OFF)
+                                               |  AUTO_CREATE_STATISTICS (ON | OFF)
+                                               |  AUTO_SHRINK (ON | OFF)
+                                               |  AUTO_UPDATE_STATISTICS (ON | OFF)
            sql_option                          =  ANSI_NULL_DEFAULT (ON | OFF)
+                                               |  ANSI_NULLS (ON | OFF)
+                                               |  ANSI_PADDING (ON | OFF)
+                                               |  ANSI_WARNINGS (ON | OFF)
+                                               |  ARITHABORT (ON | OFF)
+                                               |  CONCAT_NULL_YIELDS_NULL (ON | OFF)
+                                               |  NUMERIC_ROUNDABORT (ON | OFF)
+                                               |  QUOTED_IDENTIFIER (ON | OFF)
+                                               |  RECURSIVE_TRIGGERS (ON | OFF)
            recovery_option                     =  RECOVERY (FULL | BULK_LOGGED | SIMPLE) | TORN_PAGE_DETECTION (ON | OFF)
            termination                         =  ROLLBACK AFTER *integer_literal (SECONDS | epsilon) | ROLLBACK IMMEDIATE | NO_WAIT
            ALTER_FUNCTION_statement            =  ALTER
+                                                  FUNCTION
+                                                  *function
+                                                  $'('
+                                                  ((*parameter_name *scalar_parameter_data_type ($'=' *default | epsilon)) % $',' | epsilon)
+                                                  $')'
+                                                  RETURNS
+                                                  (  *scalar_return_data_type
+                                                     (WITH *function_option % $',' | epsilon)
+                                                     (AS | epsilon)
+                                                     BEGIN
+                                                     *function_body
+                                                     RETURN
+                                                     *scalar_expression
+                                                     END
+                                                  |  TABLE
+                                                     (WITH *function_option % $',' | epsilon)
+                                                     (AS | epsilon)
+                                                     RETURN
+                                                     ($'(' *select_stmt $')' | *select_stmt)
+                                                     epsilon ~ ''
+                                                  |  *return_variable
+                                                     TABLE
+                                                     $'('
+                                                     (*declared_column_definition | *declared_table_constraint) % $','
+                                                     $')'
+                                                     (WITH *function_option % $',' | epsilon)
+                                                     (AS | epsilon)
+                                                     BEGIN
+                                                     *function_body
+                                                     RETURN
+                                                     END
+                                                  )
+                                                  ("'ALTER_FUNCTION_statement'" & '2')
            function_option                     =  ENCRYPTION | SCHEMABINDING
            ALTER_PROCEDURE_statement           =  ALTER
+                                                  (PROC | PROCEDURE)
+                                                  *procedure
+                                                  ($';' *number | epsilon)
+                                                  (  (*parameter *data_type (VARYING | epsilon) ($'=' *default | epsilon) (OUT | OUTPUT | epsilon)) % $','
+                                                  |  epsilon
+                                                  )
+                                                  (WITH (RECOMPILE | ENCRYPTION | RECOMPILE $',' ENCRYPTION) | epsilon)
+                                                  (FOR REPLICATION | epsilon)
+                                                  AS
+                                                  nPush()
+                                                  *sql_statement nInc() ARBNO(*sql_statement nInc())
+                                                  ("'sql_statements'" & 'nTop()')
+                                                  nPop()
+                                                  ("'ALTER_PROCEDURE_statement'" & '2')
            ALTER_TABLE_statement               =  ALTER
+                                                  TABLE
+                                                  *table
+                                                  (  (  ALTER
+                                                        COLUMN
+                                                        *column_name
+                                                        (  *new_data_type
+                                                           ($'(' *precision ($',' *scale | epsilon) $')' | epsilon)
+                                                           (*COLLATE_clause | epsilon)
+                                                           (NULL | NOT NULL | epsilon)
+                                                        |  (ADD | DROP) ROWGUIDCOL
+                                                        )
+                                                     |  epsilon
+                                                     )
+                                                  |  ADD ((*alter_table_column_definition | epsilon) | *column_name AS *computed_column_expression) % $','
+                                                  |  (WITH CHECK | WITH NOCHECK | epsilon) ADD *alter_table_constraint % $','
+                                                  |  DROP ((CONSTRAINT | epsilon) *constraint_name | COLUMN *column_name) % $','
+                                                  |  ((WITH CHECK | WITH NOCHECK | epsilon) CHECK | NOCHECK) CONSTRAINT (ALL | *constraint_name % $',')
+                                                  |  (ENABLE | DISABLE) TRIGGER (ALL | *trigger_name % $',')
+                                                  )
+                                                  ("'ALTER_TABLE_statement'" & '1')
            alter_table_column_definition       =  *column_name
+                                                  *data_type
+                                                  ARBNO(
+                                                     DEFAULT *constant_expression (WITH VALUES | epsilon)
+                                                  |  IDENTITY ($'(' *seed $',' *increment $')' (NOT FOR REPLICATION | epsilon) | epsilon)
+                                                  |  ROWGUIDCOL
+                                                  |  *COLLATE_clause
+                                                  |  *column_constraint
+                                                  )
            column_constraint                   =  (CONSTRAINT *constraint_name | epsilon)
+                                                  (  NULL
+                                                  |  NOT NULL
+                                                  |  (PRIMARY KEY | UNIQUE)
+                                                     (CLUSTERED | NONCLUSTERED | epsilon)
+                                                     (WITH FILLFACTOR $'=' *fillfactor | epsilon)
+                                                     (ON (*filegroup | DEFAULT) | epsilon)
+                                                  |  (FOREIGN KEY | epsilon)
+                                                     REFERENCES
+                                                     *ref_table
+                                                     ($'(' *ref_column $')' | epsilon)
+                                                     (ON DELETE (CASCADE | NO ACTION) | epsilon)
+                                                     (ON UPDATE (CASCADE | NO ACTION) | epsilon)
+                                                     (NOT FOR REPLICATION | epsilon)
+                                                  |  CHECK (NOT FOR REPLICATION | epsilon) $'(' *logical_expression $')'
+                                                  )
            alter_table_constraint              =  (CONSTRAINT *constraint_name | epsilon)
+                                                  (  (  (PRIMARY KEY | UNIQUE)
+                                                        (CLUSTERED | NONCLUSTERED | epsilon)
+                                                        $'('
+                                                        *column_name % $','
+                                                        $')'
+                                                        (WITH FILLFACTOR $'=' *fillfactor | epsilon)
+                                                        (ON (*filegroup | DEFAULT) | epsilon)
+                                                     |  epsilon
+                                                     )
+                                                  |  FOREIGN
+                                                     KEY
+                                                     ($'(' *column_name % $',' $')' | epsilon)
+                                                     REFERENCES
+                                                     *ref_table
+                                                     ($'(' *ref_column % $',' $')' | epsilon)
+                                                     (ON DELETE (CASCADE | NO ACTION) | epsilon)
+                                                     (ON UPDATE (CASCADE | NO ACTION) | epsilon)
+                                                     (NOT FOR REPLICATION | epsilon)
+                                                  |  DEFAULT *constant_expression (FOR *column_name | epsilon) (WITH VALUES | epsilon)
+                                                  |  CHECK (NOT FOR REPLICATION | epsilon) $'(' *search_conditions $')'
+                                                  )
            ALTER_TRIGGER_statement             =  ALTER
+                                                  TRIGGER
+                                                  *trigger_name
+                                                  ON
+                                                  *table_or_view
+                                                  (WITH ENCRYPTION | epsilon)
+                                                  (  (FOR | AFTER | INSTEAD OF)
+                                                     (DELETE | epsilon)
+                                                     ($',' | epsilon)
+                                                     (INSERT | epsilon)
+                                                     ($',' | epsilon)
+                                                     (UPDATE | epsilon)
+                                                     (NOT FOR REPLICATION | epsilon)
+                                                     AS
+                                                     nPush()
+                                                     (*control_of_flow_statement nInc() | *sql_statement nInc())
+                                                     ARBNO(*control_of_flow_statement nInc() | *sql_statement nInc())
+                                                     ("'statements'" & 'nTop()')
+                                                     nPop()
+                                                  |  (FOR | AFTER | INSTEAD OF)
+                                                     (INSERT | epsilon)
+                                                     ($',' | epsilon)
+                                                     (UPDATE | epsilon)
+                                                     (NOT FOR REPLICATION | epsilon)
+                                                     AS
+                                                     (  IF UPDATE $'(' *column_name $')' ARBNO((AND | OR) UPDATE $'(' *column_name $')')
+                                                     |  IF
+                                                        $'('
+                                                        COLUMNS_UPDATED
+                                                        $'('
+                                                        $')'
+                                                        *bitwise_operator
+                                                        *updated_bitmask
+                                                        $')'
+                                                        *comparison_operator
+                                                        *column_bitmask ARBNO(*column_bitmask)
+                                                     )
+                                                     nPush()
+                                                     (*control_of_flow_statement nInc() | *sql_statement nInc())
+                                                     ARBNO(*control_of_flow_statement nInc() | *sql_statement nInc())
+                                                     ("'statements'" & 'nTop()')
+                                                     nPop()
+                                                  )
+                                                  ("'ALTER_TRIGGER_statement'" & '2')
            ALTER_VIEW_statement                =  ALTER
+                                                  VIEW
+                                                  *view
+                                                  ($'(' *column_name % $',' $')' | epsilon)
+                                                  (WITH *view_attribute % $',' | epsilon)
+                                                  AS
+                                                  *select_statement
+                                                  (WITH CHECK OPTION | epsilon)
+                                                  ("'ALTER_VIEW_statement'" & '1')
            view_attribute                      =  ENCRYPTION | SCHEMABINDING | VIEW_METADATA
            BACKUP_statement                    =  BACKUP
+                                                  (  DATABASE
+                                                     (*database_name | *database_name_var)
+                                                     TO
+                                                     *backup_device % $','
+                                                     (  WITH
+                                                        (BLOCKSIZE $'=' (*blocksize | *blocksize_variable) | epsilon)
+                                                        (($',' | epsilon) DESCRIPTION $'=' (*text | *text_variable) | epsilon)
+                                                        (($',' | epsilon) DIFFERENTIAL | epsilon)
+                                                        (($',' | epsilon) EXPIREDATE $'=' (*date | *date_var) | RETAINDAYS $'=' (*days | *days_var) | epsilon)
+                                                        (($',' | epsilon) PASSWORD $'=' (*password | *password_variable) | epsilon)
+                                                        (($',' | epsilon) (FORMAT | NOFORMAT) | epsilon)
+                                                        (($',' | epsilon) (INIT | NOINIT) | epsilon)
+                                                        (($',' | epsilon) MEDIADESCRIPTION $'=' (*text | *text_variable) | epsilon)
+                                                        (($',' | epsilon) MEDIANAME $'=' (*media_name | *media_name_variable) | epsilon)
+                                                        (($',' | epsilon) MEDIAPASSWORD $'=' (*mediapassword | *mediapassword_variable) | epsilon)
+                                                        (($',' | epsilon) NAME $'=' (*backup_set_name | *backup_set_name_var) | epsilon)
+                                                        (($',' | epsilon) (NOSKIP | SKIP) | epsilon)
+                                                        (($',' | epsilon) (NOREWIND | REWIND) | epsilon)
+                                                        (($',' | epsilon) (NOUNLOAD | UNLOAD) | epsilon)
+                                                        (($',' | epsilon) RESTART | epsilon)
+                                                        (($',' | epsilon) STATS ($'=' *percentage | epsilon) | epsilon)
+                                                     |  epsilon
+                                                     )
+                                                  |  DATABASE
+                                                     (*database_name | *database_name_var)
+                                                     *file_or_filegroup % $','
+                                                     TO
+                                                     *backup_device % $','
+                                                     (  WITH
+                                                        (BLOCKSIZE $'=' (*blocksize | *blocksize_variable) | epsilon)
+                                                        (($',' | epsilon) DESCRIPTION $'=' (*text | *text_variable) | epsilon)
+                                                        (($',' | epsilon) DIFFERENTIAL | epsilon)
+                                                        (($',' | epsilon) EXPIREDATE $'=' (*date | *date_var) | RETAINDAYS $'=' (*days | *days_var) | epsilon)
+                                                        (($',' | epsilon) PASSWORD $'=' (*password | *password_variable) | epsilon)
+                                                        (($',' | epsilon) (FORMAT | NOFORMAT) | epsilon)
+                                                        (($',' | epsilon) (INIT | NOINIT) | epsilon)
+                                                        (($',' | epsilon) MEDIADESCRIPTION $'=' (*text | *text_variable) | epsilon)
+                                                        (($',' | epsilon) MEDIANAME $'=' (*media_name | *media_name_variable) | epsilon)
+                                                        (($',' | epsilon) MEDIAPASSWORD $'=' (*mediapassword | *mediapassword_variable) | epsilon)
+                                                        (($',' | epsilon) NAME $'=' (*backup_set_name | *backup_set_name_var) | epsilon)
+                                                        (($',' | epsilon) (NOSKIP | SKIP) | epsilon)
+                                                        (($',' | epsilon) (NOREWIND | REWIND) | epsilon)
+                                                        (($',' | epsilon) (NOUNLOAD | UNLOAD) | epsilon)
+                                                        (($',' | epsilon) RESTART | epsilon)
+                                                        (($',' | epsilon) STATS ($'=' *percentage | epsilon) | epsilon)
+                                                     |  epsilon
+                                                     )
+                                                  |  LOG
+                                                     (*database_name | *database_name_var)
+                                                     TO
+                                                     *backup_device % $','
+                                                     (  WITH
+                                                        (BLOCKSIZE $'=' (*blocksize | *blocksize_variable) | epsilon)
+                                                        (($',' | epsilon) DESCRIPTION $'=' (*text | *text_variable) | epsilon)
+                                                        (($',' | epsilon) EXPIREDATE $'=' (*date | *date_var) | RETAINDAYS $'=' (*days | *days_var) | epsilon)
+                                                        (($',' | epsilon) PASSWORD $'=' (*password | *password_variable) | epsilon)
+                                                        (($',' | epsilon) FORMAT | NOFORMAT | epsilon)
+                                                        (($',' | epsilon) (INIT | NOINIT) | epsilon)
+                                                        (($',' | epsilon) MEDIADESCRIPTION $'=' (*text | *text_variable) | epsilon)
+                                                        (($',' | epsilon) MEDIANAME $'=' (*media_name | *media_name_variable) | epsilon)
+                                                        (($',' | epsilon) MEDIAPASSWORD $'=' (*mediapassword | *mediapassword_variable) | epsilon)
+                                                        (($',' | epsilon) NAME $'=' (*backup_set_name | *backup_set_name_var) | epsilon)
+                                                        (($',' | epsilon) NO_TRUNCATE | epsilon)
+                                                        (($',' | epsilon) (NORECOVERY | STANDBY $'=' (*undo_file_name | *undo_file_name_var)) | epsilon)
+                                                        (($',' | epsilon) (NOREWIND | REWIND) | epsilon)
+                                                        (($',' | epsilon) (NOSKIP | SKIP) | epsilon)
+                                                        (($',' | epsilon) (NOUNLOAD | UNLOAD) | epsilon)
+                                                        (($',' | epsilon) RESTART | epsilon)
+                                                        (($',' | epsilon) STATS ($'=' *percentage | epsilon) | epsilon)
+                                                     |  epsilon
+                                                     )
+                                                  |  LOG (*database_name | *database_name_var) (WITH (NO_LOG | TRUNCATE_ONLY) | epsilon)
+                                                  |  (TRAN | TRANSACTION) (*transaction_name | *tran_name_variable) (WITH (NO_LOG | TRUNCATE_ONLY) | epsilon)
+                                                  )
+                                                  ("'BACKUP_statement'" & '0')
            backup_device                       =  *logical_backup_device_name
+                                               |  *logical_backup_device_name_var
+                                               |  (DISK | TAPE) $'=' (*physical_backup_device_name | *physical_backup_device_name_var)
            file_or_filegroup                   =  FILE $'=' (*logical_file_name | *logical_file_name_var)
+                                               |  FILEGROUP $'=' (*logical_filegroup_name | *logical_filegroup_name_var)
            BEGIN_DISTRIBUTED_TRANSACTION_statement = BEGIN
+                                                  DISTRIBUTED
+                                                  (TRAN | TRANSACTION)
+                                                  (*transaction_name | *tran_name_variable | epsilon)
+                                                  ("'BEGIN_DISTRIBUTED_TRANSACTION_statement'" & '0')
            BEGIN_TRANSACTION_statement         =  BEGIN
+                                                  (TRAN | TRANSACTION)
+                                                  (*transaction_name | *tran_name_variable (WITH MARK (*description | epsilon) | epsilon) | epsilon)
+                                                  ("'BEGIN_TRANSACTION_statement'" & '0')
            BULK_INSERT_statement               =  BULK
+                                                  INSERT
+                                                  *table
+                                                  FROM
+                                                  *data_file
+                                                  (  WITH
+                                                     $'('
+                                                     (BATCHSIZE ($'=' *batch_size | epsilon) | epsilon)
+                                                     (($',' | epsilon) CHECK_CONSTRAINTS | epsilon)
+                                                     (($',' | epsilon) CODEPAGE ($'=' ACP | OEM | RAW | *code_page | epsilon) | epsilon)
+                                                     (($',' | epsilon) DATAFILETYPE ($'=' (*char | *native | *widechar | *widenative) | epsilon) | epsilon)
+                                                     (($',' | epsilon) FIELDTERMINATOR ($'=' *field_terminator | epsilon) | epsilon)
+                                                     (($',' | epsilon) FIRSTROW ($'=' *first_row | epsilon) | epsilon)
+                                                     (($',' | epsilon) FIRE_TRIGGERS | epsilon)
+                                                     (($',' | epsilon) FORMATFILE $'=' *format_file_path | epsilon)
+                                                     (($',' | epsilon) KEEPIDENTITY | epsilon)
+                                                     (($',' | epsilon) KEEPNULLS | epsilon)
+                                                     (($',' | epsilon) KILOBYTES_PER_BATCH ($'=' *kilobytes_per_batch | epsilon) | epsilon)
+                                                     (($',' | epsilon) LASTROW ($'=' *last_row | epsilon) | epsilon)
+                                                     (($',' | epsilon) MAXERRORS ($'=' *max_errors | epsilon) | epsilon)
+                                                     (($',' | epsilon) ORDER $'(' (*column (ASC | DESC | epsilon)) % $',' $')' | epsilon)
+                                                     (($',' | epsilon) ROWS_PER_BATCH ($'=' *rows_per_batch | epsilon) | epsilon)
+                                                     (($',' | epsilon) ROWTERMINATOR ($'=' *row_terminator | epsilon) | epsilon)
+                                                     (($',' | epsilon) TABLOCK | epsilon)
+                                                     $')'
+                                                  |  epsilon
+                                                  )
+                                                  ("'BULK_INSERT_statement'" & '1')
            CHECKPOINT_statement                =  CHECKPOINT ("'CHECKPOINT_statement'" & '0')
            CLOSE_statement                     =  CLOSE ((GLOBAL | epsilon) *cursor_name | *cursor_variable_name) ("'CLOSE_statement'" & '0')
            COLLATE_clause                      =  COLLATE (*collation_name | DATABASE_DEFAULT)
            collation_name                      =  *identifier | *string_literal
            COMMIT_TRANSACTION_statement        =  COMMIT
+                                                  (TRAN | TRANSACTION)
+                                                  (*transaction_name | *tran_name_variable | epsilon)
+                                                  ("'COMMIT_TRANSACTION_statement'" & '0')
            COMMIT_statement                    =  COMMIT (WORK | epsilon) ("'COMMIT_statement'" & '0')
            CONTAINS_clause                     =  CONTAINS $'(' (*column | $'*') $',' *string_literal $')'
            CONTAINSTABLE_clause                =  CONTAINSTABLE $'(' *table pop() $',' (*column | $'*') $',' *string_literal ($',' *top_n_by_rank | epsilon) $')'
            CREATE_DATABASE_statement           =  CREATE
+                                                  DATABASE
+                                                  (*database_name) ~ 'id'
+                                                  (ON (*filespec % $',' | epsilon) ($',' *filegroup % $',' | epsilon) | epsilon)
+                                                  (LOG ON *filespec % $',' | epsilon)
+                                                  (COLLATE *collation_name | epsilon)
+                                                  (FOR LOAD | FOR ATTACH | epsilon)
+                                                  ("'CREATE_DATABASE_statement'" & '1')
            filespec                            =  (PRIMARY | epsilon)
+                                                  $'('
+                                                  (NAME $'=' *logical_file_name $',' | epsilon)
+                                                  FILENAME
+                                                  $'='
+                                                  *os_file_name
+                                                  ($',' SIZE $'=' *size | epsilon)
+                                                  ($',' MAXSIZE $'=' (*max_size | UNLIMITED) | epsilon)
+                                                  ($',' FILEGROWTH $'=' *growth_increment | epsilon)
+                                                  $')'
+                                               |  DEFAULT $'=' *integer_literal
            filegroup                           =  FILEGROUP *filegroup_name *filespec % $','
            CREATE_DEFAULT_statement            =  CREATE DEFAULT *default AS *constant_expression ("'CREATE_DEFAULT_statement'" & '0')
            CREATE_FUNCTION_statement           =  CREATE
+                                                  FUNCTION
+                                                  *function
+                                                  $'('
+                                                  (  (*parameter_name (AS | epsilon) *scalar_parameter_data_type ($'=' *constant_expression | epsilon)) % $','
+                                                  |  epsilon
+                                                  )
+                                                  $')'
+                                                  RETURNS
+                                                  (  *scalar_return_data_type
+                                                     (  WITH
+                                                        *function_option
+                                                        (($',' | epsilon) *function_option ARBNO(($',' | epsilon) *function_option) | epsilon)
+                                                     |  epsilon
+                                                     )
+                                                     (AS | epsilon)
+                                                     BEGIN
+                                                     *function_body
+                                                     RETURN
+                                                     *scalar_expression
+                                                     END
+                                                  |  TABLE
+                                                     (  WITH
+                                                        *function_option
+                                                        (($',' | epsilon) *function_option ARBNO(($',' | epsilon) *function_option) | epsilon)
+                                                     |  epsilon
+                                                     )
+                                                     (AS | epsilon)
+                                                     RETURN
+                                                     ($'(' *select_stmt $')' | *select_stmt)
+                                                     epsilon ~ ''
+                                                  |  *return_variable
+                                                     TABLE
+                                                     $'('
+                                                     (*declared_column_definition | *declared_table_constraint) % $','
+                                                     $')'
+                                                     (  WITH
+                                                        *function_option
+                                                        (($',' | epsilon) *function_option ARBNO(($',' | epsilon) *function_option) | epsilon)
+                                                     |  epsilon
+                                                     )
+                                                     (AS | epsilon)
+                                                     BEGIN
+                                                     *function_body
+                                                     RETURN
+                                                     END
+                                                  )
+                                                  ("'CREATE_FUNCTION_statement'" & '2')
            CREATE_INDEX_statement              =  CREATE
+                                                  (UNIQUE | epsilon)
+                                                  (CLUSTERED | NONCLUSTERED | epsilon)
+                                                  INDEX
+                                                  *index
+                                                  ON
+                                                  *table_or_view
+                                                  $'('
+                                                  (*column (ASC | DESC | epsilon)) % $','
+                                                  $')'
+                                                  (WITH *index_option % $',' | epsilon)
+                                                  (ON *filegroup | epsilon)
+                                                  ("'CREATE_INDEX_statement'" & '1')
            index_option                        =  PAD_INDEX
+                                               |  FILLFACTOR $'=' *fillfactor
+                                               |  IGNORE_DUP_KEY
+                                               |  DROP_EXISTING
+                                               |  STATISTICS_NORECOMPUTE
+                                               |  SORT_IN_TEMPDB
+                                               |  ALLOW_DUP_ROW
            CREATE_PROCEDURE_statement          =  CREATE
+                                                  (PROC | PROCEDURE)
+                                                  *procedure
+                                                  ($';' *number | epsilon)
+                                                  ($'(' *parameter_list $')' | *parameter_list | epsilon)
+                                                  (WITH (RECOMPILE | ENCRYPTION | RECOMPILE $',' ENCRYPTION) | epsilon)
+                                                  (FOR REPLICATION | epsilon)
+                                                  AS
+                                                  nPush()
+                                                  *Transact_SQL_statement nInc() ARBNO(*Transact_SQL_statement nInc())
+                                                  ("'statements'" & 'nTop()')
+                                                  nPop()
+                                                  ("'CREATE_PROCEDURE_statement'" & '2')
            parameter_list                      =  (  *parameter
+                                                     (AS | epsilon)
+                                                     *data_type
+                                                     (VARYING | epsilon)
+                                                     ($'=' *constant_expression | epsilon)
+                                                     (OUT | OUTPUT | epsilon)
+                                                  ) % $','
            CREATE_RULE_statement               =  CREATE RULE *rule AS *condition_expression ("'CREATE_RULE_statement'" & '0')
            CREATE_SCHEMA_statement             =  CREATE
+                                                  SCHEMA
+                                                  AUTHORIZATION
+                                                  *owner_name
+                                                  (*schema_element ARBNO(*schema_element) | epsilon)
+                                                  ("'CREATE_SCHEMA_statement'" & '0')
            schema_element                      =  *table_definition | *view_definition | *grant_statement
            CREATE_STATISTICS_statement         =  CREATE
+                                                  STATISTICS
+                                                  *statistics_name
+                                                  ON
+                                                  *table_or_view
+                                                  $'('
+                                                  *column_name % $','
+                                                  $')'
+                                                  (  WITH
+                                                     ((FULLSCAN | SAMPLE *number (PERCENT | ROWS) | epsilon) ($',' | epsilon) | epsilon)
+                                                     (NORECOMPUTE | epsilon)
+                                                  |  epsilon
+                                                  )
+                                                  ("'CREATE_STATISTICS_statement'" & '1')
            CREATE_TABLE_statement              =  CREATE
+                                                  TABLE
+                                                  *table
+                                                  $'('
+                                                  (*create_table_column_definition | *column_name AS *computed_column_expression | *create_table_constraint)
+                                                  ARBNO(
+                                                     ($',' | epsilon)
+                                                     (*create_table_column_definition | *column_name AS *computed_column_expression | *create_table_constraint)
+                                                  )
+                                                  ($',' | epsilon)
+                                                  $')'
+                                                  (ON (*filegroup | DEFAULT) | epsilon)
+                                                  (TEXTIMAGE_ON (*filegroup | DEFAULT) | epsilon)
+                                                  ("'CREATE_TABLE_statement'" & '1')
            create_table_column_definition      =  (*column_name *data_type | TIMESTAMP)
+                                                  ARBNO(
+                                                     *COLLATE_clause
+                                                  |  DEFAULT *constant_expression
+                                                  |  IDENTITY ($'(' *seed $',' *increment $')' (NOT FOR REPLICATION | epsilon) | epsilon)
+                                                  |  ROWGUIDCOL
+                                                  |  *column_constraint
+                                                  )
            create_table_constraint             =  (CONSTRAINT *constraint_name | epsilon)
+                                                  (  (PRIMARY KEY | UNIQUE)
+                                                     (CLUSTERED | NONCLUSTERED | epsilon)
+                                                     $'('
+                                                     (*column (ASC | DESC | epsilon)) % $','
+                                                     $')'
+                                                     (WITH FILLFACTOR $'=' *fillfactor | epsilon)
+                                                     (ON (*filegroup | DEFAULT) | epsilon)
+                                                  |  FOREIGN
+                                                     KEY
+                                                     ($'(' *column_name % $',' $')' | epsilon)
+                                                     REFERENCES
+                                                     *ref_table
+                                                     ($'(' *ref_column % $',' $')' | epsilon)
+                                                     (ON DELETE (CASCADE | NO ACTION) | epsilon)
+                                                     (ON UPDATE (CASCADE | NO ACTION) | epsilon)
+                                                     (NOT FOR REPLICATION | epsilon)
+                                                  |  CHECK (NOT FOR REPLICATION | epsilon) $'(' *search_conditions $')'
+                                                  )
            CREATE_TRIGGER_statement            =  CREATE
+                                                  TRIGGER
+                                                  *trigger_name
+                                                  ON
+                                                  *table_or_view
+                                                  (WITH ENCRYPTION | epsilon)
+                                                  (FOR | AFTER | INSTEAD OF)
+                                                  (INSERT | epsilon)
+                                                  ($',' | epsilon)
+                                                  (UPDATE | epsilon)
+                                                  ($',' | epsilon)
+                                                  (DELETE | epsilon)
+                                                  (WITH APPEND | epsilon)
+                                                  (NOT FOR REPLICATION | epsilon)
+                                                  AS
+                                                  (  IF UPDATE $'(' *column_name $')' ARBNO((AND | OR) UPDATE $'(' *column_name $')')
+                                                  |  IF
+                                                     $'('
+                                                     COLUMNS_UPDATED
+                                                     $'('
+                                                     $')'
+                                                     *bitwise_operator
+                                                     *updated_bitmask
+                                                     $')'
+                                                     *comparison_operator
+                                                     *column_bitmask ARBNO(*column_bitmask)
+                                                  |  epsilon
+                                                  )
+                                                  nPush()
+                                                  (*control_of_flow_statement nInc() | *sql_statement nInc())
+                                                  ARBNO(*control_of_flow_statement nInc() | *sql_statement nInc())
+                                                  ("'statements'" & 'nTop()')
+                                                  nPop()
+                                                  ("'CREATE_TRIGGER_statement'" & '2')
            CREATE_VIEW_statement               =  CREATE
+                                                  VIEW
+                                                  *view
+                                                  ($'(' *column_name % $',' $')' | epsilon)
+                                                  (WITH *view_attribute % $',' | epsilon)
+                                                  AS
+                                                  *select_statement
+                                                  (WITH CHECK OPTION | epsilon)
+                                                  ("'CREATE_VIEW_statement'" & '1')
            DBCC_statement                      =  DBCC
+                                                  (  ADDINSTANCE $'(' *expression $',' *expression $')'
+                                                  |  ADDEXTENDEDPROC $'(' *expression $',' *expression $')'
+                                                  |  CHECKALLOC
+                                                     $'('
+                                                     *database_name
+                                                     ($',' NOINDEX | REPAIR_ALLOW_DATA_LOSS | REPAIR_FAST | REPAIR_REBUILD | epsilon)
+                                                     $')'
+                                                     (  WITH
+                                                        (ALL_ERRORMSGS | NO_INFOMSGS | epsilon)
+                                                        ($',' (TABLOCK | epsilon) | epsilon)
+                                                        ($',' (ESTIMATEONLY | epsilon) | epsilon)
+                                                     |  epsilon
+                                                     )
+                                                  |  CHECKCATALOG $'(' *database_name $')' (WITH NO_INFOMSGS | epsilon)
+                                                  |  CHECKCONSTRAINTS
+                                                     ($'(' (*table_name | *constraint_name) $')' | epsilon)
+                                                     (WITH (ALL_ERRORMSGS | ALL_CONSTRAINTS) | epsilon)
+                                                  |  CHECKDB
+                                                     $'('
+                                                     *database_name
+                                                     ($',' NOINDEX | REPAIR_ALLOW_DATA_LOSS | REPAIR_FAST | REPAIR_REBUILD | epsilon)
+                                                     $')'
+                                                     (  WITH
+                                                        (ALL_ERRORMSGS | epsilon)
+                                                        ($',' (NO_INFOMSGS | epsilon) | epsilon)
+                                                        ($',' (TABLOCK | epsilon) | epsilon)
+                                                        ($',' (ESTIMATEONLY | epsilon) | epsilon)
+                                                        ($',' (PHYSICAL_ONLY | epsilon) | epsilon)
+                                                     |  epsilon
+                                                     )
+                                                  |  CHECKFILEGROUP
+                                                     $'('
+                                                     (*filegroup | *filegroup_id | epsilon)
+                                                     ($',' NOINDEX | epsilon)
+                                                     $')'
+                                                     (  WITH
+                                                        (ALL_ERRORMSGS | NO_INFOMSGS | epsilon)
+                                                        ($',' (TABLOCK | epsilon) | epsilon)
+                                                        ($',' (ESTIMATEONLY | epsilon) | epsilon)
+                                                     |  epsilon
+                                                     )
+                                                  |  CHECKIDENT $'(' *table_name ($',' (NORESEED | RESEED ($',' *new_reseed_value | epsilon)) | epsilon) $')'
+                                                  |  CHECKTABLE
+                                                     $'('
+                                                     (*table_name | *view_name)
+                                                     ($',' NOINDEX | *index_id | REPAIR_ALLOW_DATA_LOSS | REPAIR_FAST | REPAIR_REBUILD | epsilon)
+                                                     $')'
+                                                     (  WITH
+                                                        (ALL_ERRORMSGS | NO_INFOMSGS | epsilon)
+                                                        ($',' (TABLOCK | epsilon) | epsilon)
+                                                        ($',' (ESTIMATEONLY | epsilon) | epsilon)
+                                                        ($',' (PHYSICAL_ONLY | epsilon) | epsilon)
+                                                     |  epsilon
+                                                     )
+                                                  |  CLEANTABLE
+                                                     $'('
+                                                     (*database_name | *database_id)
+                                                     $','
+                                                     (*table_name | *table_id | *view_name | *view_id)
+                                                     ($',' *batch_size | epsilon)
+                                                     $')'
+                                                  |  CONCURRENCYVIOLATION ($'(' (DISPLAY | RESET | STARTLOG | STOPLOG) $')' | epsilon)
+                                                  |  DELETEINSTANCE $'(' *expression $',' *expression $')'
+                                                  |  DBREPAIR $'(' *expression % $',' $')' (WITH NO_INFOMSGS | epsilon)
+                                                  |  DBREINDEX
+                                                     $'('
+                                                     *database
+                                                     $'.'
+                                                     *owner
+                                                     $'.'
+                                                     *table_name
+                                                     ($',' *index_name ($',' *fillfactor | epsilon) | epsilon)
+                                                     $')'
+                                                     (WITH NO_INFOMSGS | epsilon)
+                                                  |  *dllname $'(' FREE $')'
+                                                  |  DROPCLEANBUFFERS
+                                                  |  FLUSHPROCINDB $'(' *expression $')'
+                                                  |  FREEPROCCACHE
+                                                  |  HELP $'(' (*string_literal | *local_variable | $'?') $')'
+                                                  |  INCREMENTINSTANCE $'(' *expression $',' *expression $',' *expression $',' *expression $')'
+                                                  |  INDEXDEFRAG
+                                                     $'('
+                                                     (*database_name | *database_id | *integer_literal)
+                                                     $','
+                                                     (*table_name | *table_id | *view_name | *view_id)
+                                                     $','
+                                                     (*index_name | *index_id)
+                                                     $')'
+                                                     (WITH NO_INFOMSGS | epsilon)
+                                                  |  INPUTBUFFER $'(' *spid $')'
+                                                  |  NEWALLOC
+                                                  |  OPENTRAN
+                                                     $'('
+                                                     (*database_name | *database_id)
+                                                     $')'
+                                                     (WITH TABLERESULTS ($',' NO_INFOMSGS | epsilon) | epsilon)
+                                                  |  OUTPUTBUFFER $'(' *spid $')'
+                                                  |  PINTABLE $'(' *database_id $',' *table_id $')'
+                                                  |  PROCCACHE
+                                                  |  ROWLOCK
+                                                  |  SETINSTANCE $'(' *expression $',' *expression $',' *expression $',' *expression $')'
+                                                  |  SHOWCONTIG
+                                                     (  $'(' (*table_name | *table_id | *view_name | *view_id) ($',' (*index_name | *index_id) | epsilon) $')'
+                                                     |  epsilon
+                                                     )
+                                                     (  WITH
+                                                        (  ALL_INDEXES
+                                                        |  FAST ($',' ALL_INDEXES | epsilon)
+                                                        |  TABLERESULTS ($',' ALL_INDEXES | epsilon) ($',' (FAST | ALL_LEVELS) | epsilon)
+                                                        )
+                                                     |  epsilon
+                                                     )
+                                                  |  SHOW_STATISTICS
+                                                     ($'(' (*table_name | *variable_name) $',' (*target_name | *variable_name) $')' | epsilon)
+                                                     (WITH STAT_HEADER | epsilon)
+                                                     (JOIN DENSITY_VECTOR | epsilon)
+                                                  |  SHRINKDATABASE
+                                                     $'('
+                                                     *database_name
+                                                     ($',' *target_percent | epsilon)
+                                                     ($',' (NOTRUNCATE | TRUNCATEONLY) | epsilon)
+                                                     $')'
+                                                  |  SHRINKFILE
+                                                     $'('
+                                                     (*file_name | *file_id)
+                                                     (($',' *target_size | epsilon) | ($',' (EMPTYFILE | NOTRUNCATE | TRUNCATEONLY) | epsilon))
+                                                     $')'
+                                                  |  SQLPERF $'(' LOGSPACE $')'
+                                                  |  TRACEOFF $'(' *traceno % $',' $')'
+                                                  |  TRACEON $'(' *traceno % $',' $')'
+                                                  |  TRACESTATUS $'(' *traceno % $',' $')'
+                                                  |  UNPINTABLE $'(' *database_id $',' *table_id $')'
+                                                  |  UPDATEUSAGE
+                                                     (  *expression ($',' (*table_or_view_name | *at_identifier) ($',' *index_id | epsilon) | epsilon)
+                                                     |  $'(' *expression ($',' (*table_or_view_name | *at_identifier) ($',' *index_id | epsilon) | epsilon) $')'
+                                                     )
+                                                     (WITH (COUNT_ROWS | epsilon) (($',' | epsilon) NO_INFOMSGS | epsilon) | epsilon)
+                                                  |  USEROPTIONS
+                                                  |  *identifier ($'(' (*expression % $',' | epsilon) $')' | epsilon) (WITH NO_INFOMSGS | epsilon)
+                                                  )
+                                                  ("'DBCC_statement'" & '0')
            dllname                             =  *identifier
            new_reseed_value                    =  *integer_literal
            owner                               =  *identifier
            target_percent                      =  *integer_literal
            target_size                         =  *integer_literal
            traceno                             =  *integer_literal
            view_id                             =  *identifier
            DEALLOCATE_statement                =  DEALLOCATE ((GLOBAL | epsilon) *cursor_name | *cursor_variable_name) ("'DEALLOCATE_statement'" & '0')
            DECLARE_variable_statement          =  DECLARE
+                                                  (  *local_variable (AS | epsilon) *data_type
+                                                  |  *cursor_variable_name CURSOR
+                                                  |  *local_variable TABLE $'(' (*declared_column_definition | *declared_table_constraint) % $',' $')'
+                                                  ) % $','
+                                                  ("'DECLARE_variable_statement'" & '0')
            declared_column_definition          =  *column_name
+                                                  *scalar_data_type
+                                                  (*COLLATE_clause | epsilon)
+                                                  (DEFAULT *constant_expression | IDENTITY ($'(' *seed $',' *increment $')' | epsilon) | epsilon)
+                                                  (ROWGUIDCOL | epsilon)
+                                                  (*declared_column_constraint | epsilon)
            declared_column_constraint          =  NULL | NOT NULL | PRIMARY KEY | UNIQUE | CHECK $'(' *logical_expression $')'
            declared_table_constraint           =  (PRIMARY KEY | UNIQUE) $'(' *column_name % $',' $')' | CHECK $'(' *search_condition $')'
            DECLARE_CURSOR_statement            =  DECLARE
+                                                  *cursor_name
+                                                  (INSENSITIVE | epsilon)
+                                                  (SCROLL | epsilon)
+                                                  CURSOR
+                                                  ARBNO(
+                                                     LOCAL
+                                                  |  GLOBAL
+                                                  |  FORWARD_ONLY
+                                                  |  SCROLL
+                                                  |  STATIC
+                                                  |  KEYSET
+                                                  |  DYNAMIC
+                                                  |  FAST_FORWARD
+                                                  |  READ_ONLY
+                                                  |  SCROLL_LOCKS
+                                                  |  OPTIMISTIC
+                                                  |  TYPE_WARNING
+                                                  )
+                                                  FOR
+                                                  *select_statement
+                                                  (FOR (READ ONLY | UPDATE (OF *column_name % $',' | epsilon)) | epsilon)
+                                                  ("'DECLARE_CURSOR_statement'" & '0')
            DELETE_statement                    =  DELETE
+                                                  (FROM | epsilon)
+                                                  (  (*table | epsilon ~ '' *local_variable)
+                                                     (WITH $'(' *table_hint_limited ARBNO(*table_hint_limited) $')' | epsilon)
+                                                  |  *view
+                                                  |  epsilon ~ '' *rowset_function_limited
+                                                  )
+                                                  (FROM *select_source % $',' | epsilon)
+                                                  (  WHERE (*search_condition | (CURRENT OF ((GLOBAL | epsilon) *cursor_name | *cursor_variable_name) | epsilon))
+                                                  |  epsilon
+                                                  )
+                                                  (OPTION $'(' *delete_query_hint % $',' $')' | epsilon)
+                                                  ("'DELETE_statement'" & '1')
            select_source                       =  (*table_source | $'(' *select_source $')') (*joined_table ARBNO(*joined_table) | epsilon)
            table_source                        =  (*table pop() | *local_variable)
+                                                  ((AS | epsilon) *table_alias | epsilon)
+                                                  ((WITH | epsilon) $'(' *table_hint ARBNO(($',' | epsilon) *table_hint) $')' | epsilon)
+                                                  ($'<' (*local_variable | NULL) % $',' $'>' (*identifier | epsilon) | epsilon)
+                                               |  *view pop() ((AS | epsilon) *table_alias | epsilon) (WITH $'(' *view_hint % $',' $')' | epsilon)
+                                               |  *rowset_function ((AS | epsilon) *table_alias | epsilon)
+                                               |  $'::' *user_defined_function $'(' $')' ((AS | epsilon) *table_alias | epsilon)
+                                               |  OPENXML
+                                               |  *derived_table (AS | epsilon) *table_alias ($'(' *column_alias % $',' $')' | epsilon)
            joined_table                        =  (INNER | (LEFT | RIGHT | FULL) (OUTER | epsilon) | epsilon)
+                                                  (*join_hint | epsilon)
+                                                  JOIN
+                                                  *select_source
+                                                  ON
+                                                  *search_condition
+                                               |  CROSS JOIN *select_source
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
            table_hint                          =  INDEX $'(' *index_val % $',' $')'
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
            delete_query_hint                   =  (HASH | ORDER) GROUP
+                                               |  (CONCAT | HASH | MERGE) UNION
+                                               |  FAST *number_rows
+                                               |  FORCE ORDER
+                                               |  MAXDOP
+                                               |  ROBUST PLAN
+                                               |  KEEP PLAN
            DENY_statement                      =  DENY
+                                                  (  epsilon ~ '' (ALL | *statement % $',') TO *security_account % $','
+                                                  |  (ALL (PRIVILEGES | epsilon) | *permission % $',')
+                                                     (  ($'(' *column_name % $',' $')' | epsilon) ON *table_or_view
+                                                     |  ON *table_or_view ($'(' *column_name % $',' $')' | epsilon)
+                                                     |  ON (*stored_procedure | *extended_procedure)
+                                                     |  ON epsilon ~ '' *user_defined_function
+                                                     )
+                                                     TO
+                                                     *security_account % $','
+                                                     (CASCADE | epsilon)
+                                                  )
+                                                  ("'DENY_statement'" & '1')
            DROP_DATABASE_statement             =  nPush() DROP DATABASE ((*database_name) ~ 'id' nInc()) % $',' ("'DROP_DATABASE_statement'" & 'nTop()') nPop()
            DROP_DEFAULT_statement              =  nPush() DROP DEFAULT *default % $',' ("'DROP_DEFAULT_statement'" & 'nTop()') nPop()
            DROP_FUNCTION_statement             =  nPush() DROP FUNCTION (*function nInc()) % $',' ("'DROP_FUNCTION_statement'" & 'nTop()') nPop()
            DROP_INDEX_statement                =  nPush() DROP INDEX *index % $',' ("'DROP_INDEX_statement'" & 'nTop()') nPop()
            DROP_PROCEDURE_statement            =  nPush() DROP (PROC | PROCEDURE) (*procedure nInc()) % $',' ("'DROP_PROCEDURE_statement'" & 'nTop()') nPop()
            DROP_RULE_statement                 =  nPush() DROP RULE *rule % $',' ("'DROP_RULE_statement'" & 'nTop()') nPop()
            DROP_STATISTICS_statement           =  nPush()
+                                                  DROP
+                                                  STATISTICS
+                                                  (*table_or_view nInc() $'.' *statistics_name) % $','
+                                                  ("'DROP_STATISTICS_statement'" & 'nTop()')
+                                                  nPop()
            DROP_TABLE_statement                =  nPush() DROP TABLE (*table nInc()) % $',' ("'DROP_TABLE_statement'" & 'nTop()') nPop()
            DROP_TRIGGER_statement              =  nPush() DROP TRIGGER *trigger % $',' ("'DROP_TRIGGER_statement'" & 'nTop()') nPop()
            DROP_VIEW_statement                 =  nPush() DROP VIEW (*view nInc()) % $',' ("'DROP_VIEW_statement'" & 'nTop()') nPop()
            DUMP_statement                      =  DUMP
+                                                  (DATABASE (*database_name) ~ 'id' | (TRAN | TRANSACTION) (*transaction_name) ~ 'id')
+                                                  (WITH NO_LOG | epsilon)
+                                                  ("'DUMP_statement'" & '1')
            EXECUTE_statement                   =  (EXEC | EXECUTE) (*execute_clause | $'(' *string_sum $')') ("'EXECUTE_statement'" & '0')
            execute_clause                      =  (*return_status $'=' | epsilon)
+                                                  (*procedure pop() ($';' *number | epsilon) | *procedure_name_var)
+                                                  (((*parameter $'=' | epsilon) *expression (OUT | OUTPUT | epsilon) | (DEFAULT | epsilon)) % $',' | epsilon)
+                                                  (WITH RECOMPILE | epsilon)
            string_factor                       =  *string_variable | *global_variable | *string_literal
            string_sum                          =  *string_factor ($'+' *string_sum | epsilon)
            FETCH_statement                     =  FETCH
+                                                  ((NEXT | PRIOR | FIRST | LAST | ABSOLUTE (*n | *nvar) | RELATIVE (*n | *nvar) | epsilon) FROM | epsilon)
+                                                  ((GLOBAL | epsilon) *cursor_name | *cursor_variable_name)
+                                                  (INTO *variable_name % $',' | epsilon)
+                                                  ("'FETCH_statement'" & '0')
            GRANT_statement                     =  GRANT
+                                                  (  epsilon ~ '' (ALL | *statement % $',') TO *security_account % $','
+                                                  |  (ALL (PRIVILEGES | epsilon) | *permission % $',')
+                                                     (  ($'(' *column_name % $',' $')' | epsilon) ON *table_or_view
+                                                     |  ON *table_or_view ($'(' *column_name % $',' $')' | epsilon)
+                                                     |  ON (*stored_procedure | *extended_procedure)
+                                                     |  ON epsilon ~ '' *user_defined_function
+                                                     )
+                                                     TO
+                                                     *security_account % $','
+                                                     (WITH GRANT OPTION | epsilon)
+                                                     (AS (*group | *role) | epsilon)
+                                                  )
+                                                  ("'GRANT_statement'" & '1')
            GROUPING_clause                     =  GROUPING $'(' *column_name $')'
            IDENTITY_clause                     =  IDENTITY ($'(' *seed $',' *increment $')' | epsilon)
+                                               |  IDENTITY $'(' *data_type ($',' *seed $',' *increment | epsilon) $')' AS *column_name
            NOT_IN_clause                       =  *test_expression (NOT | epsilon) IN $'(' (*subquery | *expression % $',') $')'
            INSERT_statement                    =  (  INSERT
+                                                     (INTO | epsilon)
+                                                     (  (*table | epsilon ~ '' *local_variable)
+                                                        (WITH $'(' *table_hint_limited ARBNO(*table_hint_limited) $')' | epsilon)
+                                                     |  *view
+                                                     |  epsilon ~ '' *rowset_function_limited
+                                                     )
+                                                     ($'(' *column_list $')' | epsilon)
+                                                     (VALUES $'(' (DEFAULT | NULL | *expression) % $',' $')' | *derived_table | *EXECUTE_statement pop())
+                                                  |  DEFAULT VALUES
+                                                  )
+                                                  ("'INSERT_statement'" & '1')
            IS_clause                           =  *expression IS (NOT | epsilon) NULL
            KILL_statement                      =  KILL (*spid | UOW) (WITH STATUSONLY | epsilon) ("'KILL_statement'" & '0')
            LIKE_clause                         =  *match_expression (NOT | epsilon) LIKE *pattern (ESCAPE *escape_character | epsilon)
            LOAD_statement                      =  LOAD (DATABASE | TRANSACTION | HEADERONLY) ("'LOAD_statement'" & '0')
            NOT_clause                          =  (NOT | epsilon) *boolean_expression
            OPEN_statement                      =  OPEN ((GLOBAL | epsilon) *cursor_name | *cursor_variable_name) ("'OPEN_statement'" & '0')
            OPENXML_clause                      =  OPENXML
+                                                  $'('
+                                                  *idoc
+                                                  $'int'
+                                                  (IN | epsilon)
+                                                  $','
+                                                  *rowpattern
+                                                  $'nvarchar'
+                                                  (IN | epsilon)
+                                                  $','
+                                                  (*flags $'byte' (IN | epsilon) | epsilon)
+                                                  $')'
+                                                  (WITH $'(' *SchemaDeclaration | *TableName $')' | epsilon)
            PRINT_statement                     =  PRINT (*string_literal | *local_variable | $'@@FUNCTION' | *string_expression) ("'PRINT_statement'" & '0')
            RAISERROR_statement                 =  RAISERROR
+                                                  ($'(' (*msg_id | *msg_str) $',' *severity $',' *state ($',' *argument % $',' | epsilon) $')' | *msg_id *msg_str)
+                                                  (WITH (LOG | NOWAIT | SETERROR) % $',' | epsilon)
+                                                  ("'RAISERROR_statement'" & '0')
            msg_id                              =  *integer_expression
            msg_str                             =  *string_literal
            severity                            =  *integer_expression
            state                               =  *integer_expression
            argument                            =  *expression
            READTEXT_statement                  =  READTEXT *table $'.' *column_name *text_ptr *offset *size (HOLDLOCK | epsilon) ("'READTEXT_statement'" & '1')
            RECONFIGURE_statement               =  RECONFIGURE (WITH OVERRIDE | epsilon) ("'RECONFIGURE_statement'" & '0')
            RESTORE_statement                   =  RESTORE
+                                                  (  DATABASE
+                                                     (*database_name | *database_name_var)
+                                                     (FROM *backup_device % $',' | epsilon)
+                                                     (  WITH
+                                                        (RESTRICTED_USER | epsilon)
+                                                        (($',' | epsilon) FILE $'=' (*file_number | *file_number_variable) | epsilon)
+                                                        (($',' | epsilon) PASSWORD $'=' (*password | *password_variable) | epsilon)
+                                                        (($',' | epsilon) MEDIANAME $'=' (*media_name | *media_name_variable) | epsilon)
+                                                        (($',' | epsilon) MEDIAPASSWORD $'=' (*mediapassword | *mediapassword_variable) | epsilon)
+                                                        ((($',' | epsilon) MOVE *logical_file_name TO *operating_system_file_name) % $',' | epsilon)
+                                                        (($',' | epsilon) KEEP_REPLICATION | epsilon)
+                                                        (  ($',' | epsilon) (NORECOVERY | RECOVERY | STANDBY $'=' (*undo_file_name | *undo_file_name_var))
+                                                        |  epsilon
+                                                        )
+                                                        (($',' | epsilon) (NOREWIND | REWIND) | epsilon)
+                                                        (($',' | epsilon) (NOUNLOAD | UNLOAD) | epsilon)
+                                                        (($',' | epsilon) REPLACE | epsilon)
+                                                        (($',' | epsilon) RESTART | epsilon)
+                                                        (($',' | epsilon) STATS ($'=' *percentage | epsilon) | epsilon)
+                                                     |  epsilon
+                                                     )
+                                                  |  DATABASE
+                                                     (*database_name | *database_name_var)
+                                                     *file_or_filegroup % $','
+                                                     (FROM *backup_device % $',' | epsilon)
+                                                     (  WITH
+                                                        PARTIAL
+                                                        (($',' | epsilon) FILE $'=' (*file_number | *file_number_variable) | epsilon)
+                                                        (($',' | epsilon) PASSWORD $'=' (*password | *password_variable) | epsilon)
+                                                        (($',' | epsilon) MEDIANAME $'=' (*media_name | *media_name_variable) | epsilon)
+                                                        (($',' | epsilon) MEDIAPASSWORD $'=' (*mediapassword | *mediapassword_variable) | epsilon)
+                                                        ((($',' | epsilon) MOVE *logical_file_name TO *operating_system_file_name) % $',' | epsilon)
+                                                        (($',' | epsilon) NORECOVERY | epsilon)
+                                                        (($',' | epsilon) (NOREWIND | REWIND) | epsilon)
+                                                        (($',' | epsilon) (NOUNLOAD | UNLOAD) | epsilon)
+                                                        (($',' | epsilon) REPLACE | epsilon)
+                                                        (($',' | epsilon) RESTRICTED_USER | epsilon)
+                                                        (($',' | epsilon) RESTART | epsilon)
+                                                        (($',' | epsilon) STATS ($'=' *percentage | epsilon) | epsilon)
+                                                     |  epsilon
+                                                     )
+                                                  |  DATABASE
+                                                     (*database_name | *database_name_var)
+                                                     *file_or_filegroup % $','
+                                                     (FROM *backup_device % $',' | epsilon)
+                                                     (  WITH
+                                                        (RESTRICTED_USER | epsilon)
+                                                        (($',' | epsilon) FILE $'=' (*file_number | *file_number_variable) | epsilon)
+                                                        (($',' | epsilon) PASSWORD $'=' (*password | *password_variable) | epsilon)
+                                                        (($',' | epsilon) MEDIANAME $'=' (*media_name | *media_name_variable) | epsilon)
+                                                        (($',' | epsilon) MEDIAPASSWORD $'=' (*mediapassword | *mediapassword_variable) | epsilon)
+                                                        ((($',' | epsilon) MOVE *logical_file_name TO *operating_system_file_name) % $',' | epsilon)
+                                                        (($',' | epsilon) NORECOVERY | epsilon)
+                                                        (($',' | epsilon) (NOREWIND | REWIND) | epsilon)
+                                                        (($',' | epsilon) (NOUNLOAD | UNLOAD) | epsilon)
+                                                        (($',' | epsilon) REPLACE | epsilon)
+                                                        (($',' | epsilon) RESTART | epsilon)
+                                                        (($',' | epsilon) STATS ($'=' *percentage | epsilon) | epsilon)
+                                                     |  epsilon
+                                                     )
+                                                  |  LOG
+                                                     (*database_name | *database_name_var)
+                                                     (FROM *backup_device % $',' | epsilon)
+                                                     (  WITH
+                                                        (RESTRICTED_USER | epsilon)
+                                                        (($',' | epsilon) FILE $'=' (*file_number | *file_number_variable) | epsilon)
+                                                        (($',' | epsilon) PASSWORD $'=' (*password | *password_variable) | epsilon)
+                                                        ((($',' | epsilon) MOVE *logical_file_name TO *operating_system_file_name) % $',' | epsilon)
+                                                        (($',' | epsilon) MEDIANAME $'=' (*media_name | *media_name_variable) | epsilon)
+                                                        (($',' | epsilon) MEDIAPASSWORD $'=' (*mediapassword | *mediapassword_variable) | epsilon)
+                                                        (($',' | epsilon) KEEP_REPLICATION | epsilon)
+                                                        (  ($',' | epsilon) (NORECOVERY | RECOVERY | STANDBY $'=' (*undo_file_name | *undo_file_name_var))
+                                                        |  epsilon
+                                                        )
+                                                        (($',' | epsilon) (NOREWIND | REWIND) | epsilon)
+                                                        (($',' | epsilon) (NOUNLOAD | UNLOAD) | epsilon)
+                                                        (($',' | epsilon) RESTART | epsilon)
+                                                        (($',' | epsilon) STATS ($'=' *percentage | epsilon) | epsilon)
+                                                        (  ($',' | epsilon) STOPAT $'=' (*date_time | *date_time_var)
+                                                        |  ($',' | epsilon) STOPATMARK $'=' *mark_name (AFTER *datetime | epsilon)
+                                                        |  ($',' | epsilon) STOPBEFOREMARK $'=' *mark_name (AFTER *datetime | epsilon)
+                                                        |  epsilon
+                                                        )
+                                                     |  epsilon
+                                                     )
+                                                  )
+                                                  ("'RESTORE_statement'" & '0')
            RESTORE_FILELISTONLY_statement      =  RESTORE
+                                                  FILELISTONLY
+                                                  FROM
+                                                  *backup_device
+                                                  (  WITH
+                                                     (FILE $'=' *file_number | epsilon)
+                                                     (($',' | epsilon) PASSWORD $'=' (*password | *password_variable) | epsilon)
+                                                     (($',' | epsilon) MEDIAPASSWORD $'=' (*mediapassword | *mediapassword_variable) | epsilon)
+                                                     (($',' | epsilon) (NOUNLOAD | UNLOAD) | epsilon)
+                                                  |  epsilon
+                                                  )
+                                                  ("'RESTORE_FILELISTONLY_statement'" & '0')
            RESTORE_HEADERONLY_statement        =  RESTORE
+                                                  HEADERONLY
+                                                  FROM
+                                                  *backup_device
+                                                  (  WITH
+                                                     (NOUNLOAD | UNLOAD)
+                                                     (($',' | epsilon) FILE $'=' *file_number | epsilon)
+                                                     (($',' | epsilon) PASSWORD $'=' (*password | *password_variable) | epsilon)
+                                                     (($',' | epsilon) MEDIAPASSWORD $'=' (*mediapassword | *mediapassword_variable) | epsilon)
+                                                  |  epsilon
+                                                  )
+                                                  ("'RESTORE_HEADERONLY_statement'" & '0')
            RESTORE_LABELONLY_statement         =  RESTORE
+                                                  LABELONLY
+                                                  FROM
+                                                  *backup_device
+                                                  (WITH (NOUNLOAD | UNLOAD) | epsilon)
+                                                  (($',' | epsilon) MEDIAPASSWORD $'=' (*mediapassword | *mediapassword_variable) | epsilon)
+                                                  ("'RESTORE_LABELONLY_statement'" & '0')
            RESTORE_VERIFYONLY_statement        =  RESTORE
+                                                  VERIFYONLY
+                                                  FROM
+                                                  *backup_device % $','
+                                                  (  WITH
+                                                     (FILE $'=' *file_number | epsilon)
+                                                     (($',' | epsilon) (NOUNLOAD | UNLOAD) | epsilon)
+                                                     (($',' | epsilon) LOADHISTORY | epsilon)
+                                                     (($',' | epsilon) PASSWORD $'=' (*password | *password_variable) | epsilon)
+                                                     (($',' | epsilon) MEDIAPASSWORD $'=' (*mediapassword | *mediapassword_variable) | epsilon)
+                                                     (($',' | epsilon) (NOREWIND | REWIND) | epsilon)
+                                                  |  epsilon
+                                                  )
+                                                  ("'RESTORE_VERIFYONLY_statement'" & '0')
            REVOKE_statement                    =  REVOKE
+                                                  (  epsilon ~ '' (ALL | *statement % $',') FROM *security_account % $','
+                                                  |  (GRANT OPTION FOR | epsilon)
+                                                     (ALL (PRIVILEGES | epsilon) | *permission % $',')
+                                                     (  ($'(' *column_name % $',' $')' | epsilon) ON *table_or_view
+                                                     |  ON *table_or_view ($'(' *column_name % $',' $')' | epsilon)
+                                                     |  ON (*stored_procedure | *extended_procedure)
+                                                     |  ON epsilon ~ '' *user_defined_function
+                                                     )
+                                                     (TO | FROM)
+                                                     *security_account % $','
+                                                     (CASCADE | epsilon)
+                                                     (AS (*group | *role) | epsilon)
+                                                  )
+                                                  ("'REVOKE_statement'" & '1')
            ROLLBACK_TRANSACTION_statement      =  ROLLBACK
+                                                  (TRAN | TRANSACTION)
+                                                  (*transaction_name | *tran_name_variable | *savepoint_name | *savepoint_variable | epsilon)
+                                                  ("'ROLLBACK_TRANSACTION_statement'" & '0')
            ROLLBACK_statement                  =  ROLLBACK (WORK | epsilon) ("'ROLLBACK_statement'" & '0')
            SAVE_TRANSACTION_statement          =  SAVE (TRAN | TRANSACTION) (*savepoint_name | *savepoint_variable) ("'SAVE_TRANSACTION_statement'" & '0')
            SELECT_variable_statement           =  SELECT
+                                                  (*local_variable $'=' *expression) % $','
+                                                  (FROM *select_source % $',' | epsilon)
+                                                  (WHERE *search_condition | epsilon)
+                                                  (GROUP BY (ALL | epsilon) *group_by_expression % $',' | epsilon)
+                                                  (HAVING *search_condition | epsilon)
+                                                  ("'SELECT_variable_statement'" & '0')
            SELECT_statement                    =  *query_expression
+                                                  (ORDER BY (*order_by_expression (ASC | DESC | epsilon)) % $',' | epsilon)
+                                                  ARBNO(COMPUTE ((AVG | COUNT | MAX | MIN | SUM) $'(' *expression $')') % $',' (BY *expression % $',' | epsilon))
+                                                  (  FOR
+                                                     (  BROWSE
+                                                     |  XML
+                                                        (RAW | AUTO | EXPLICIT)
+                                                        ($',' XMLDATA | epsilon)
+                                                        ($',' ELEMENTS | epsilon)
+                                                        ($',' BINARY *base64 | epsilon)
+                                                     )
+                                                  |  epsilon
+                                                  )
+                                                  (OPTION $'(' *select_query_hint % $',' $')' | epsilon)
            query_expression                    =  (*query_specification | $'(' *query_expression $')')
+                                                  ARBNO(UNION (ALL | epsilon) (*query_specification | $'(' *query_expression $')'))
            query_specification                 =  SELECT
+                                                  (ALL | DISTINCT | epsilon)
+                                                  ((TOP *integer_literal | TOP *integer_literal PERCENT) (WITH TIES | epsilon) | epsilon)
+                                                  *select_list
+                                                  (INTO *new_table | epsilon)
+                                                  (FROM *select_source % $',' | epsilon)
+                                                  (WHERE *search_condition | epsilon)
+                                                  (GROUP BY (ALL | epsilon) *group_by_expression % $',' (WITH (CUBE | ROLLUP) | epsilon) | epsilon)
+                                                  (HAVING *search_condition | epsilon)
            select_list                         =  (  $'*'
+                                                  |  *identifier $'.' $'*'
+                                                  |  *column_alias $'=' *expression
+                                                  |  (*column_name | *expression | IDENTITYCOL | ROWGUIDCOL) ((AS | epsilon) *column_alias | epsilon)
+                                                  ) % $','
            SELECT_Clause                       =  SELECT (ALL | DISTINCT | epsilon) (TOP *n (PERCENT | epsilon) (WITH TIES | epsilon) | epsilon) *select_list
            INTO_Clause                         =  (INTO *new_table | epsilon)
            WHERE_Clause                        =  (WHERE *search_condition | *old_outer_join | epsilon)
            old_outer_join                      =  *column_name ($'*' $'=' | $'=' $'*') *column_name
            GROUP_BY_Clause                     =  (GROUP BY (ALL | epsilon) *group_by_expression % $',' (WITH (CUBE | ROLLUP) | epsilon) | epsilon)
            HAVING_Clause                       =  (HAVING *search_condition | epsilon)
            UNION_Operator                      =  (*query_specification | $'(' *query_expression $')') UNION (ALL | epsilon) *query_specification
+                                               |  $'(' *query_expression $')' ARBNO(UNION (ALL | epsilon) (*query_specification | $'(' *query_expression $')'))
            ORDER_BY_Clause                     =  (ORDER BY (*order_by_expression (ASC | DESC | epsilon)) % $',' | epsilon)
            COMPUTE_Clause                      =  (  COMPUTE
+                                                     ((AVG | COUNT | MAX | MIN | STDEV | STDEVP | VAR | VARP | SUM) $'(' *expression $')') % $','
+                                                     (BY *expression % $',' | epsilon)
+                                                  |  epsilon
+                                                  )
            FOR_Clause                          =  (  FOR
+                                                     (  BROWSE
+                                                     |  XML
+                                                        (RAW | AUTO | EXPLICIT)
+                                                        ($',' XMLDATA | epsilon)
+                                                        ($',' ELEMENTS | epsilon)
+                                                        ($',' BINARY BASE64 | epsilon)
+                                                     )
+                                                  |  epsilon
+                                                  )
            OPTION_Clause                       =  (OPTION $'(' *select_query_hint % $',' $')' | epsilon)
            select_query_hint                   =  (HASH | ORDER) GROUP
+                                               |  (CONCAT | HASH | MERGE) UNION
+                                               |  (LOOP | MERGE | HASH) JOIN
+                                               |  FAST *number_rows
+                                               |  FORCE ORDER
+                                               |  MAXDOP *number
+                                               |  ROBUST PLAN
+                                               |  KEEP PLAN
+                                               |  KEEPFIXED PLAN
+                                               |  EXPAND VIEWS
            SET_variable_statement              =  SET
+                                                  (  *local_variable $'=' (*expression | $'{' FN *identifier $'(' (*expression % $',' | epsilon) $')' $'}')
+                                                  |  *cursor_variable
+                                                     $'='
+                                                     (  *cursor_variable
+                                                     |  *cursor_name
+                                                     |  CURSOR
+                                                        (LOCAL | epsilon)
+                                                        (FORWARD_ONLY | SCROLL | epsilon)
+                                                        (STATIC | KEYSET | DYNAMIC | FAST_FORWARD | epsilon)
+                                                        (READ_ONLY | SCROLL_LOCKS | OPTIMISTIC | epsilon)
+                                                        (TYPE_WARNING | epsilon)
+                                                        FOR
+                                                        *select_statement
+                                                        (FOR (READ ONLY | UPDATE (OF *column_name % $',' | epsilon)) | epsilon)
+                                                     )
+                                                  )
+                                                  ($';' | epsilon)
+                                                  ("'SET_variable_statement'" & '0')
            SET_statement                       =  SET
+                                                  (  ANSI_DEFAULTS (ON | OFF)
+                                                  |  ANSI_NULL_DFLT_OFF (ON | OFF)
+                                                  |  ANSI_NULL_DFLT_ON (ON | OFF)
+                                                  |  ANSI_NULLS (ON | OFF)
+                                                  |  ANSI_PADDING (ON | OFF)
+                                                  |  ANSI_WARNINGS (ON | OFF)
+                                                  |  ARITHABORT (ON | OFF)
+                                                  |  ARITHIGNORE (ON | OFF)
+                                                  |  CONCAT_NULL_YIELDS_NULL (ON | OFF)
+                                                  |  CONTEXT_INFO (*binary | *binary_var)
+                                                  |  CURSOR_CLOSE_ON_COMMIT (ON | OFF)
+                                                  |  DATEFIRST (*number | *number_var)
+                                                  |  DATEFORMAT (*format | *format_var)
+                                                  |  DEADLOCK_PRIORITY (LOW | NORMAL | *deadlock_var)
+                                                  |  DISABLE_DEF_CNST_CHK
+                                                  |  FIPS_FLAGGER *level
+                                                  |  FMTONLY (ON | OFF)
+                                                  |  FORCEPLAN (ON | OFF)
+                                                  |  IDENTITY_INSERT *table pop() (ON | OFF)
+                                                  |  IMPLICIT_TRANSACTIONS (ON | OFF)
+                                                  |  LANGUAGE ((N | epsilon) *language | *language_var)
+                                                  |  LOCK_TIMEOUT *timeout_period
+                                                  |  NOCOUNT (ON | OFF)
+                                                  |  NOEXEC (ON | OFF)
+                                                  |  NUMERIC_ROUNDABORT (ON | OFF)
+                                                  |  OFFSETS *keyword_list
+                                                  |  PARSEONLY (ON | OFF)
+                                                  |  QUERY_GOVERNOR_COST_LIMIT *value
+                                                  |  QUOTED_IDENTIFIER (ON | OFF)
+                                                  |  REMOTE_PROC_TRANSACTIONS (ON | OFF)
+                                                  |  ROWCOUNT (*number | *number_var)
+                                                  |  SHOWPLAN_ALL (ON | OFF)
+                                                  |  SHOWPLAN_TEXT (ON | OFF)
+                                                  |  STATISTICS IO (ON | OFF)
+                                                  |  STATISTICS PROFILE (ON | OFF)
+                                                  |  STATISTICS TIME (ON | OFF)
+                                                  |  TEXTSIZE *number
+                                                  |  TRANSACTION ISOLATION LEVEL (READ COMMITTED | READ UNCOMMITTED | REPEATABLE READ | SERIALIZABLE)
+                                                  |  XACT_ABORT (ON | OFF)
+                                                  )
+                                                  ("'SET_statement'" & '0')
            SETUSER_statement                   =  SETUSER
+                                                  (*username (WITH NORESET | epsilon) ($',' *at_identifier $',' *at_identifier | epsilon) | epsilon)
+                                                  ("'SETUSER_statement'" & '0')
            SHUTDOWN_statement                  =  SHUTDOWN (WITH NOWAIT | epsilon) ("'SHUTDOWN_statement'" & '0')
            TRUNCATE_TABLE_statement            =  TRUNCATE TABLE *table ("'TRUNCATE_TABLE_statement'" & '1')
            UPDATE_statement                    =  UPDATE
+                                                  (  (*table | epsilon ~ '' *local_variable)
+                                                     (WITH $'(' *table_hint_limited ARBNO(*table_hint_limited) $')' | epsilon)
+                                                  |  *view
+                                                  |  epsilon ~ '' *rowset_function_limited
+                                                  )
+                                                  SET
+                                                  (  *column $'=' (*expression | DEFAULT | NULL)
+                                                  |  *variable $'=' *expression
+                                                  |  *variable $'=' *column $'=' *expression
+                                                  ) % $','
+                                                  (  (FROM *select_source % $',' | epsilon) (WHERE *search_condition | epsilon)
+                                                  |  (WHERE CURRENT OF ((GLOBAL | epsilon) *cursor_name | *cursor_variable_name) | epsilon)
+                                                  )
+                                                  (OPTION $'(' *update_query_hint % $',' $')' | epsilon)
+                                                  ("'UPDATE_statement'" & '1')
            update_query_hint                   =  (HASH | ORDER) GROUP
+                                               |  (CONCAT | HASH | MERGE) UNION
+                                               |  (LOOP | MERGE | HASH) JOIN
+                                               |  FAST *number_rows
+                                               |  FORCE ORDER
+                                               |  MAXDOP
+                                               |  ROBUST PLAN
+                                               |  KEEP PLAN
            UPDATE_STATISTICS_statement         =  UPDATE
+                                                  STATISTICS
+                                                  *table_or_view
+                                                  (*index | $'(' *statistics_name % $',' $')' | epsilon)
+                                                  (WITH ((FULLSCAN | epsilon) | SAMPLE *number (PERCENT | ROWS) | epsilon) | RESAMPLE | epsilon)
+                                                  (($',' | epsilon) (ALL | COLUMNS | INDEX | epsilon) (($',' | epsilon) NORECOMPUTE | epsilon) | epsilon)
+                                                  ("'UPDATE_STATISTICS_statement'" & '1')
            UPDATETEXT_statement                =  UPDATETEXT
+                                                  *table
+                                                  $'.'
+                                                  *dest_column_name
+                                                  *dest_text_ptr
+                                                  (NULL | *insert_offset)
+                                                  (NULL | *delete_length)
+                                                  (WITH LOG | epsilon)
+                                                  (*inserted_data | *table_name $'.' *src_column_name *src_text_ptr | epsilon)
+                                                  ("'UPDATETEXT_statement'" & '1')
            USE_statement                       =  USE (*database) ~ 'id' ("'USE_statement'" & '1')
            WRITETEXT_statement                 =  WRITETEXT *table $'.' *column_name *text_ptr (WITH LOG | epsilon) *data ("'WRITETEXT_statement'" & '1')
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
            alias                               =  *table_or_view pop() | *identifier
            column                              =  (*identifier $'.' | epsilon) *identifier
            base64                              =  *dont_know
            batch_size                          =  *dont_know
            binary                              =  *dont_know
            catalog                             =  *dont_know
            catalog_name                        =  *dont_know
            char                                =  *dont_know
            character_string                    =  *expression
            code_page                           =  *dont_know
            column_id                           =  *dont_know
            column_list                         =  *identifier % $','
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
+                                               |  ($'+' | $'-' | epsilon) *real_literal
+                                               |  ($'+' | $'-' | epsilon) *integer_literal
+                                               |  *string_literal
+                                               |  *money_literal
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
            rowset_function                     =  OPENROWSET $'(' (*expression % $',' | epsilon) $')'
            scalar_data_type                    =  *data_type
            scalar_subquery                     =  *query_specification (ORDER BY (*order_by_expression (ASC | DESC | epsilon)) % $',' | epsilon)
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
            system_function                     =  CONVERT $'(' *data_type $',' *expression ($',' *style | epsilon) $')'
+                                               |  DB_NAME $'(' (*database_id | epsilon) $')'
+                                               |  GETDATE $'(' $')'
+                                               |  NEWID $'(' $')'
+                                               |  ISNULL $'(' *expression $',' *expression $')'
+                                               |  SUSER_SID $'(' (*login | epsilon) $')'
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
            extended_procedure                  =  *procedure
            file_id                             =  *integer_literal
            file_name                           =  *string_literal
            file_number                         =  *integer_literal
            filegroup_name                      =  *string_literal
            fillfactor                          =  *integer_literal
            freetext_string                     =  *string_literal
            function_body                       =  nPush()
+                                                  *Transact_SQL_statement nInc() ARBNO(*Transact_SQL_statement nInc())
+                                                  ("'function_body'" & 'nTop()')
+                                                  nPop()
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
+                                               |  OPENROWSET
+                                                  $'('
+                                                  *provider_name
+                                                  $','
+                                                  (*datasource $';' *user_id $';' *password | *provider_string)
+                                                  $','
+                                                  ((*catalog $'.' | epsilon) (*schema $'.' | epsilon) *object | *query)
+                                                  $')'
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
            stored_procedure                    =  *procedure
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
            default                             =  (*owner_name $'.' | epsilon) *default_name
            function                            =  (  (*database_name) ~ 'id' $'.' (*owner_name | epsilon) ~ 'id' $'.'
+                                                  |  epsilon ~ 'id' (*owner_name) ~ 'id' $'.'
+                                                  |  epsilon ~ 'id' epsilon ~ 'id'
+                                                  )
+                                                  (*function_name) ~ 'id'
+                                                  ("'function'" & '3')
            procedure                           =  (  (*servername) ~ 'id' $'.' (*database_name | epsilon) ~ 'id' $'.' (*owner_name | epsilon) ~ 'id' $'.'
+                                                  |  epsilon ~ 'id' (*database_name) ~ 'id' $'.' (*owner_name | epsilon) ~ 'id' $'.'
+                                                  |  epsilon ~ 'id' epsilon ~ 'id' (*owner_name) ~ 'id' $'.'
+                                                  |  epsilon ~ 'id' epsilon ~ 'id' epsilon ~ 'id'
+                                                  )
+                                                  (*procedure_name) ~ 'id'
+                                                  ("'procedure'" & '4')
            servername                          =  *identifier
            rule                                =  (*owner_name $'.' | epsilon) *rule_name
            index                               =  (*table_or_view pop() $'.' | epsilon) *index_name
            ref_table                           =  (*database_name $'.' (*owner_name | epsilon) $'.' | *owner_name $'.' | epsilon) *table_name
            table                               =  (  (*database_name) ~ 'id' $'.' (*owner_name | epsilon) ~ 'id' $'.'
+                                                  |  epsilon ~ 'id' (*owner_name) ~ 'id' $'.'
+                                                  |  epsilon ~ 'id' epsilon ~ 'id'
+                                                  )
+                                                  (*table_name) ~ 'id'
+                                                  ("'table'" & '3')
            table_or_view                       =  (  (*database_name) ~ 'id' $'.' (*owner_name | epsilon) ~ 'id' $'.'
+                                                  |  epsilon ~ 'id' (*owner_name) ~ 'id' $'.'
+                                                  |  epsilon ~ 'id' epsilon ~ 'id'
+                                                  )
+                                                  (*table_or_view_name) ~ 'id'
+                                                  ("'table_or_view'" & '3')
            trigger                             =  (*owner_name $'.' | epsilon) *rule_name
            view                                =  (  (*database_name) ~ 'id' $'.' (*owner_name | epsilon) ~ 'id' $'.'
+                                                  |  epsilon ~ 'id' (*owner_name) ~ 'id' $'.'
+                                                  |  epsilon ~ 'id' epsilon ~ 'id'
+                                                  )
+                                                  (*view_name) ~ 'id'
+                                                  ("'view'" & '3')
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
