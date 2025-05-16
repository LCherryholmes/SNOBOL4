            '$'                                 =  '$'
            '%'                                 =  '%'
            '&'                                 =  '&'
            '('                                 =  '('
            ')'                                 =  ')'
            '*'                                 =  '*'
            '+'                                 =  '+'
            ','                                 =  ','
            '-'                                 =  '-'
            '.'                                 =  '.'
            '/'                                 =  '/'
            ';'                                 =  ';'
            '^'                                 =  '^'
            '|'                                 =  '|'
            '~'                                 =  '~'
            label                               =  $'_LABEL_'
            at_ident                            =  $'_AT_IDENT_'
            at_at_ident                         =  $'_AT_AT_IDENT_'
            SQL_command_statement               =  *alter_database_statement
+                                               |  *alter_table_statement
+                                               |  *begin_statement
+                                               |  *begin_transaction_statement
+                                               |  *break_statement
+                                               |  *checkpoint_statement
+                                               |  *close_statement
+                                               |  *commit_transaction_statement
+                                               |  *continue_statement
+                                               |  *create_database_statement
+                                               |  *create_index_statement
+                                               |  *create_schema_statement
+                                               |  *create_table_statement
+                                               |  *dbcc_statement
+                                               |  *deallocate_cursor_statement
+                                               |  *declare_cursor_statement
+                                               |  *declare_statement
+                                               |  *delete_statement
+                                               |  *disk_statement
+                                               |  *disk_init_statement
+                                               |  *drop_database_statement
+                                               |  *drop_default_statement
+                                               |  *drop_index_statement
+                                               |  *drop_procedure_statement
+                                               |  *drop_rule_statement
+                                               |  *drop_table_statement
+                                               |  *drop_trigger_statement
+                                               |  *drop_view_statement
+                                               |  *dump_statement
+                                               |  *execute_statement
+                                               |  *fetch_statement
+                                               |  *goto_statement
+                                               |  *grant_statement
+                                               |  *insert_statement
+                                               |  *kill_statement
+                                               |  *label_statement
+                                               |  *load_statement
+                                               |  *online_database_statement
+                                               |  *open_statement
+                                               |  *prepare_transaction_statement
+                                               |  *print_statement
+                                               |  *raiserror_statement
+                                               |  *readtext_statement
+                                               |  *reconfigure_statement
+                                               |  *return_statement
+                                               |  *revoke_statement
+                                               |  *rollback_transaction_statement
+                                               |  *rollback_trigger_statement
+                                               |  *save_transaction_statement
+                                               |  *select_expr
+                                               |  *set_statement
+                                               |  *setuser_statement
+                                               |  *shutdown_statement
+                                               |  *truncate_statement
+                                               |  *update_statement
+                                               |  *update_statistics_statement
+                                               |  *use_statement
+                                               |  *waitfor_statement
+                                               |  *while_statement
+                                               |  *writetext_statement
            SQL_matched_statement               =  IF *logical_expr *SQL_matched_statement ELSE *SQL_matched_statement
+                                               |  *SQL_command_statement
            SQL_nonbatch_statement              =  *create_default_statement
+                                               |  *create_procedure_statement
+                                               |  *create_rule_statement
+                                               |  *create_trigger_statement
+                                               |  *create_view_statement
            SQL_statement                       =  *SQL_matched_statement | *SQL_unmatched_statement
            SQL_statements                      =  *SQL_statement
+                                               |  *SQL_statements *SQL_statement
+                                               |  *error *SQL_statement
+                                               |  *error *eos
            SQL_unmatched_statement             =  IF *logical_expr *SQL_statement
+                                               |  IF
+                                                  *logical_expr
+                                                  *SQL_matched_statement
+                                                  ELSE
+                                                  *SQL_unmatched_statement
            aggregate_function                  =  COUNT $'(' $'*' $')'
+                                               |  MIN $'(' *expr $')'
+                                               |  MAX $'(' *expr $')'
+                                               |  AVG $'(' *aggregate_function_1 *expr $')'
+                                               |  COUNT $'(' *aggregate_function_2 *expr $')'
+                                               |  SUM $'(' *aggregate_function_3 *expr $')'
            aggregate_function_1                =  epsilon | *aggregate_function_1_1
            aggregate_function_1_1              =  ALL | DISTINCT
            aggregate_function_2                =  epsilon | *aggregate_function_2_1
            aggregate_function_2_1              =  ALL | DISTINCT
            aggregate_function_3                =  epsilon | *aggregate_function_3_1
            aggregate_function_3_1              =  ALL | DISTINCT
            alias                               =  *ident | $'_DQ_STRING_'
            all_privileges                      =  ALL *all_privileges_1
            all_privileges_1                    =  epsilon | PRIVILEGES
            alter_database_statement            =  ALTER
+                                                  DATABASE
+                                                  *database_name
+                                                  *alter_database_statement_1
+                                                  *alter_database_statement_2
+                                                  *alter_database_statement_3
+                                                  *alter_database_statement_4
            alter_database_statement_1          =  epsilon | ON *database_on_devices
            alter_database_statement_2          =  epsilon | LOG ON *database_on_devices
            alter_database_statement_3          =  epsilon | WITH OVERRIDE
            alter_database_statement_4          =  epsilon | FOR LOAD
            alter_table_statement               =  ALTER TABLE *table *alter_table_statement_1
            alter_table_statement_1             =  ADD *column_definitions
+                                               |  ADD *constraint_definition
+                                               |  DROP CONSTRAINT *constraint_name
+                                               |  PARTITION *number
+                                               |  REPLACE *column_name DEFAULT *expr
+                                               |  UNPARTITION
            begin_statement                     =  BEGIN *SQL_statements END
            begin_transaction_statement         =  BEGIN *begin_transaction_statement_1 *begin_transaction_statement_2
            begin_transaction_statement_1       =  TRANSACTION | TRAN
            begin_transaction_statement_2       =  epsilon | *transaction_name
            boolean_expr                        =  *boolean_expr_term | *boolean_expr OR *boolean_expr_term
            boolean_expr_factor                 =  *expr | NOT *boolean_expr_factor
            boolean_expr_term                   =  *boolean_expr_factor | *boolean_expr_term AND *boolean_expr_factor
            break_statement                     =  BREAK
            builtin_function                    =  *ident $'(' $')'
+                                               |  *ident $'(' *expr_list $')'
+                                               |  CONVERT $'(' *datatype $',' *expr $')'
+                                               |  CONVERT $'(' *datatype $',' *expr $',' *expr $')'
            checkpoint_statement                =  CHECKPOINT
            close_statement                     =  CLOSE *cursor_name
            column                              =  *ident
+                                               |  *ident $'.' *ident
+                                               |  *ident $'.' *ident $'.' *ident
+                                               |  *ident $'.' $'.' *ident $'.' *ident
+                                               |  *ident $'.' *ident $'.' *ident $'.' *ident
            column_definition                   =  *column_name *datatype *column_definition_1 *column_definition_2
            column_definition_1                 =  epsilon | DEFAULT *expr
            column_definition_2                 =  epsilon | *column_definition_2 *column_definition_2_1
            column_definition_2_1               =  IDENTITY
+                                               |  *column_definition_2_1_1 *column_definition_2_1_2
+                                               |  *column_definition_2_1_1 *column_definition_2_1_3
            column_definition_2_1_1             =  epsilon | CONSTRAINT *constraint_name
            column_definition_2_1_2             =  NULL | NOT NULL
            column_definition_2_1_3             =  UNIQUE *column_definition_2_1_3_1 *constraint_options
+                                               |  PRIMARY KEY *column_definition_2_1_3_2 *constraint_options
+                                               |  REFERENCES *table *column_definition_2_1_3_3
+                                               |  CHECK $'(' *condition $')'
            column_definition_2_1_3_1           =  epsilon | CLUSTERED | NONCLUSTERED
            column_definition_2_1_3_2           =  epsilon | CLUSTERED | NONCLUSTERED
            column_definition_2_1_3_3           =  epsilon | $'(' *column_name $')'
            column_definitions                  =  *column_definition | *column_definitions $',' *column_definition
            column_name                         =  *ident
            column_name_list                    =  *column_name | *column_name_list $',' *column_name
            command                             =  CREATE DATABASE
+                                               |  CREATE DEFAULT
+                                               |  CREATE PROCEDURE
+                                               |  CREATE RULE
+                                               |  CREATE TABLE
+                                               |  CREATE VIEW
            command_list                        =  *command | *command_list $',' *command
            commit_transaction_statement        =  COMMIT
+                                                  *commit_transaction_statement_1
+                                                  *commit_transaction_statement_2
            commit_transaction_statement_1      =  TRANSACTION | TRAN | WORK
            commit_transaction_statement_2      =  epsilon | *transaction_name
            condition                           =  *condition_term | *condition OR *condition_term
            condition_element                   =  *column $'_LEFT_OUTER_JOIN_' *column
+                                               |  *column $'_RIGHT_OUTER_JOIN_' *column
+                                               |  *expr $'_EQ_' *opt_any_or_all *expr
+                                               |  *expr $'_GT_' *opt_any_or_all *expr
+                                               |  *expr $'_LT_' *opt_any_or_all *expr
+                                               |  *expr $'_GEQ_' *opt_any_or_all *expr
+                                               |  *expr $'_LEQ_' *opt_any_or_all *expr
+                                               |  *expr $'_NEQ_1_' *opt_any_or_all *expr
+                                               |  *expr $'_NEQ_2_' *opt_any_or_all *expr
+                                               |  *expr $'_NGT_' *opt_any_or_all *expr
+                                               |  *expr $'_NLT_' *opt_any_or_all *expr
+                                               |  *expr IN $'(' *expr_list $')'
+                                               |  *expr NOT IN $'(' *expr_list $')'
+                                               |  *expr IN $'(' *select_statement $')'
+                                               |  *expr NOT IN $'(' *select_statement $')'
+                                               |  EXISTS *expr
+                                               |  *expr BETWEEN *expr AND *expr
+                                               |  *expr NOT BETWEEN *expr AND *expr
+                                               |  *expr LIKE *expr
+                                               |  *expr LIKE *expr ESCAPE *expr
+                                               |  *expr NOT LIKE *expr
+                                               |  *expr NOT LIKE *expr ESCAPE *expr
+                                               |  *expr IS NULL
+                                               |  *expr IS NOT NULL
+                                               |  $'(' *condition $')'
            condition_factor                    =  *condition_element | NOT *condition_factor
            condition_term                      =  *condition_factor | *condition_term AND *condition_factor
            constraint_definition               =  *constraint_definition_1 *constraint_definition_2
            constraint_definition_1             =  epsilon | CONSTRAINT *constraint_name
            constraint_definition_2             =  UNIQUE
+                                                  *constraint_definition_2_1
+                                                  $'('
+                                                  *column_list
+                                                  $')'
+                                                  *constraint_options
+                                               |  PRIMARY
+                                                  KEY
+                                                  *constraint_definition_2_2
+                                                  $'('
+                                                  *column_list
+                                                  $')'
+                                                  *constraint_options
+                                               |  FOREIGN
+                                                  KEY
+                                                  $'('
+                                                  *constraint_frm_column_list
+                                                  $')'
+                                                  REFERENCES
+                                                  *table
+                                                  *constraint_definition_2_3
+                                               |  CHECK $'(' *condition $')'
            constraint_definition_2_1           =  epsilon | CLUSTERED | NONCLUSTERED
            constraint_definition_2_2           =  epsilon | CLUSTERED | NONCLUSTERED
            constraint_definition_2_3           =  epsilon | $'(' *constraint_ref_column_list $')'
            column_list                         =  *column_name | *column_list $',' *column_name
            constraint_frm_column_list          =  *column_name | *constraint_frm_column_list $',' *column_name
            constraint_ref_column_list          =  *column_name | *constraint_ref_column_list $',' *column_name
            constraint_name                     =  *ident
            constraint_options                  =  *constraint_options_1 *constraint_options_2
            constraint_options_1                =  epsilon | WITH *constraint_options_1_1
            constraint_options_1_1              =  FILLFACTOR $'_EQ_' *number | MAX_ROWS_PER_PAGE $'_EQ_' *number
            constraint_options_2                =  epsilon | ON *segment_name
            continue_statement                  =  CONTINUE
            create_database_statement           =  CREATE
+                                                  DATABASE
+                                                  *database_name
+                                                  *create_database_statement_1
+                                                  *create_database_statement_2
+                                                  *create_database_statement_3
+                                                  *create_database_statement_4
            create_database_statement_1         =  epsilon | ON *database_on_devices
            create_database_statement_2         =  epsilon | LOG ON *database_on_devices
            create_database_statement_3         =  epsilon | WITH OVERRIDE
            create_database_statement_4         =  epsilon | FOR LOAD
            create_default_statement            =  CREATE DEFAULT *owner_object AS *expr
            create_index_option                 =  *ident
+                                               |  FILLFACTOR $'_EQ_' *number
+                                               |  MAX_ROWS_PER_PAGE $'_EQ_' *number
            create_index_options                =  *create_index_option
+                                               |  *create_index_options $',' *create_index_option
            create_index_statement              =  CREATE
+                                                  *create_index_statement_1
+                                                  *create_index_statement_2
+                                                  INDEX
+                                                  *index_name
+                                                  ON
+                                                  *table
+                                                  $'('
+                                                  *column_list
+                                                  $')'
+                                                  *create_index_statement_3
+                                                  *create_index_statement_4
            create_index_statement_1            =  epsilon | UNIQUE
            create_index_statement_2            =  epsilon | CLUSTERED | NONCLUSTERED
            create_index_statement_3            =  epsilon | WITH *create_index_options
            create_index_statement_4            =  epsilon | ON *segment_name
            create_procedure_parameter          =  *parameter
+                                                  *datatype
+                                                  *create_procedure_parameter_1
+                                                  *create_procedure_parameter_2
            create_procedure_parameter_1        =  epsilon | $'_EQ_' *expr
            create_procedure_parameter_2        =  epsilon | OUTPUT
            create_procedure_parameters         =  *create_procedure_parameter
+                                               |  *create_procedure_parameters $',' *create_procedure_parameter
            create_procedure_statement          =  CREATE
+                                                  *create_procedure_statement_1
+                                                  *owner_object
+                                                  *create_procedure_statement_2
+                                                  *create_procedure_statement_3
+                                                  *create_procedure_statement_4
+                                                  AS
+                                                  *SQL_statements
            create_procedure_statement_1        =  PROC | PROCEDURE
            create_procedure_statement_2        =  epsilon | $';' *number
            create_procedure_statement_3        =  epsilon | *create_procedure_statement_3_1
            create_procedure_statement_3_1      =  *create_procedure_parameters
+                                               |  $'(' *create_procedure_parameters $')'
            create_procedure_statement_4        =  epsilon | WITH RECOMPILE
            create_rule_statement               =  CREATE RULE *owner_object AS *condition
            create_schema_statement             =  CREATE
+                                                  SCHEMA
+                                                  AUTHORIZATION
+                                                  *authorization_name
+                                                  *create_object_statements
+                                                  *permission_statements
            create_object_statements            =  *create_object_statements *create_object_statement
+                                               |  *create_object_statement
            create_object_statement             =  *create_table_statement | *create_view_statement
            authorization_name                  =  *string
            permission_statements               =  epsilon | *permission_statements *permission_statement
            permission_statement                =  *grant_statement | *revoke_statement
            create_table_definition             =  epsilon | *column_definition | *constraint_definition
            create_table_definitions            =  *create_table_definition
+                                               |  *create_table_definitions $',' *create_table_definition
            create_table_statement              =  CREATE
+                                                  TABLE
+                                                  *table
+                                                  $'('
+                                                  *create_table_definitions
+                                                  $')'
+                                                  *create_table_statement_1
+                                                  *create_table_statement_2
            create_table_statement_1            =  epsilon | WITH MAX_ROWS_PER_PAGE $'_EQ_' *number
            create_table_statement_2            =  epsilon | ON *segment_name
            create_trigger_body                 =  *SQL_statement
+                                               |  *create_trigger_if_update_clause *SQL_statement
+                                               |  *create_trigger_body *SQL_statement
+                                               |  *create_trigger_body *create_trigger_if_update_clause *SQL_statement
            create_trigger_for_option           =  INSERT | UPDATE | DELETE
            create_trigger_for_options          =  *create_trigger_for_option
+                                               |  *create_trigger_for_options $',' *create_trigger_for_option
            create_trigger_if_update_clause     =  IF UPDATE $'(' *column_name $')' *create_trigger_if_update_clause_1
            create_trigger_if_update_clause_1   =  epsilon
+                                               |  *create_trigger_if_update_clause_1
+                                                  *create_trigger_if_update_clause_1_1
+                                                  UPDATE
+                                                  $'('
+                                                  *column_name
+                                                  $')'
            create_trigger_if_update_clause_1_1 =  AND | OR
            create_trigger_statement            =  CREATE
+                                                  TRIGGER
+                                                  *owner_object
+                                                  ON
+                                                  *owner_object
+                                                  FOR
+                                                  *create_trigger_for_options
+                                                  AS
+                                                  *create_trigger_body
            create_view_statement               =  CREATE
+                                                  VIEW
+                                                  *owner_object
+                                                  *create_view_statement_1
+                                                  AS
+                                                  *select_statement
+                                                  *create_view_statement_2
            create_view_statement_1             =  epsilon | $'(' *column_name_list $')'
            create_view_statement_2             =  epsilon | WITH CHECK OPTION
            cursor_name                         =  *ident
            database_device                     =  *ident | *local_variable
            database_name                       =  *ident | *local_variable
            database_name_list                  =  *database_name | *database_name_list $',' *database_name
            database_on_devices                 =  *database_on_devices_1 *database_on_devices_2
+                                               |  *database_on_devices $',' *database_device *database_on_devices_3
            database_on_devices_1               =  DEFAULT | *database_device
            database_on_devices_2               =  epsilon | $'_EQ_' *size
            database_on_devices_3               =  epsilon | $'_EQ_' *size
            datatype                            =  *ident
+                                               |  *ident $'(' *number $')'
+                                               |  *ident $'(' *number $',' *number $')'
+                                               |  DOUBLE PRECISION
+                                               |  *ident VARYING $'(' *number $')'
+                                               |  *ident VARYING
+                                               |  NATIONAL *ident
+                                               |  NATIONAL *ident $'(' *number $')'
+                                               |  NATIONAL *ident VARYING $'(' *number $')'
+                                               |  NATIONAL *ident VARYING
            dbcc_statement                      =  DBCC *ident | DBCC *ident $'(' *expr_list $')'
            deallocate_cursor_statement         =  DEALLOCATE CURSOR *cursor_name
            declare_cursor_statement            =  DECLARE *cursor_name CURSOR FOR *select_statement
            declare_local_variable              =  *local_variable *datatype
            declare_local_variables             =  *declare_local_variable
+                                               |  *declare_local_variables $',' *declare_local_variable
            declare_statement                   =  DECLARE *declare_local_variables
            delete_from_clause                  =  *delete_from_entity | *delete_from_clause $',' *delete_from_entity
            delete_from_entity                  =  *table_or_view *delete_from_entity_1 *index_access
            delete_from_entity_1                =  epsilon | *ident
            delete_statement                    =  DELETE *delete_statement_1 *table_or_view *delete_statement_2
            delete_statement_1                  =  epsilon | FROM
            delete_statement_2                  =  epsilon | *delete_statement_2_1
            delete_statement_2_1                =  FROM *delete_from_clause
+                                               |  FROM *delete_from_clause WHERE *condition
+                                               |  WHERE *condition
+                                               |  WHERE CURRENT OF *cursor_name
            disk_init_statement                 =  DISK
+                                                  INIT
+                                                  *disk_init_statement_1
+                                                  $','
+                                                  *disk_init_statement_2
+                                                  $','
+                                                  *disk_init_statement_3
+                                                  $','
+                                                  *disk_init_statement_4
+                                                  *disk_init_statement_5
+                                                  *disk_init_statement_6
            disk_init_statement_1               =  NAME $'_EQ_' $'_SQ_STRING_'
            disk_init_statement_2               =  PHYSNAME $'_EQ_' $'_SQ_STRING_'
            disk_init_statement_3               =  VDEVNO $'_EQ_' *number
            disk_init_statement_4               =  SIZE $'_EQ_' *number
            disk_init_statement_5               =  epsilon | $',' VSTART $'_EQ_' *number $',' CNTRLTYPE $'_EQ_' *number
            disk_init_statement_6               =  epsilon | $',' CONTIGUOUS
            disk_option                         =  *ident | *ident $'_EQ_' *expr
            disk_options                        =  *disk_option | *disk_options $',' *disk_option
            disk_statement                      =  DISK *ident *disk_statement_1
            disk_statement_1                    =  epsilon | *disk_options
            drop_database_statement             =  DROP DATABASE *database_name_list
            drop_default_statement              =  DROP DEFAULT *owner_object_list
            drop_index_statement                =  DROP INDEX *table_index_name_list
            drop_procedure_statement            =  DROP *drop_procedure_statement_1 *owner_object_list
            drop_procedure_statement_1          =  PROC | PROCEDURE
            drop_rule_statement                 =  DROP RULE *owner_object_list
            drop_table_statement                =  DROP TABLE *object_list
            drop_trigger_statement              =  DROP TRIGGER *owner_object_list
            drop_view_statement                 =  DROP VIEW *owner_object_list
            dump_option                         =  *ident $'_EQ_' *expr
            dump_options                        =  *dump_option | *dump_options $',' *dump_option
            dump_statement                      =  DUMP
+                                                  *dump_statement_1
+                                                  *database_name
+                                                  *dump_statement_2
+                                                  *dump_statement_3
+                                                  *dump_statement_4
+                                                  *dump_statement_5
+                                                  *dump_statement_6
            dump_statement_1                    =  DATABASE | TRAN | TRANSACTION
            dump_statement_2                    =  epsilon | TO *database_device
            dump_statement_3                    =  epsilon | AT *server_name
            dump_statement_4                    =  epsilon | *dump_options
            dump_statement_5                    =  epsilon
+                                               |  *dump_statement_5
+                                                  STRIPE
+                                                  ON
+                                                  *database_device
+                                                  *dump_statement_5_1
+                                                  *dump_statement_5_2
            dump_statement_5_1                  =  epsilon | AT *server_name
            dump_statement_5_2                  =  epsilon | *dump_options
            dump_statement_6                    =  epsilon | WITH *dump_with_options
            dump_with_option                    =  *ident | *ident $'_EQ_' *expr
            dump_with_options                   =  *dump_with_option | *dump_with_options $',' *dump_with_option
            eos                                 =  GO
            error_number                        =  $'_NUMBER_'
            execute_command                     =  *execute_command_1
+                                                  *server_procedure
+                                                  *execute_command_2
+                                                  *execute_command_3
+                                                  *execute_command_4
            execute_command_1                   =  epsilon | *return_status $'_EQ_'
            execute_command_2                   =  epsilon | $';' *number
            execute_command_3                   =  epsilon | *execute_parameters
            execute_command_4                   =  epsilon | WITH RECOMPILE
            execute_parameter                   =  *execute_value
+                                               |  *parameter $'_EQ_' *execute_value
+                                               |  *local_variable *execute_parameter_1
+                                               |  *parameter $'_EQ_' *local_variable *execute_parameter_2
            execute_parameter_1                 =  epsilon | *execute_parameter_1_1
            execute_parameter_1_1               =  OUT | OUTPUT
            execute_parameter_2                 =  epsilon | *execute_parameter_2_1
            execute_parameter_2_1               =  OUT | OUTPUT
            execute_parameters                  =  *execute_parameter | *execute_parameters $',' *execute_parameter
            execute_statement                   =  *execute_statement_1 *execute_command
            execute_statement_1                 =  EXEC | EXECUTE
            execute_value                       =  COMMON
+                                               |  FOREIGN
+                                               |  MRU
+                                               |  NULL
+                                               |  PREFETCH
+                                               |  PRIMARY
+                                               |  *ident
+                                               |  *string
+                                               |  *number
            real                                =  $'_REAL_'
            expr                                =  *expr_expr
            expr_element                        =  NULL
+                                               |  *string
+                                               |  *number
+                                               |  *real
+                                               |  $'$' *number
+                                               |  $'$' *real
+                                               |  *local_variable
+                                               |  *global_variable
+                                               |  *column
+                                               |  *builtin_function
+                                               |  *aggregate_function
+                                               |  IDENTITY $'(' *number $')'
+                                               |  $'(' *select_statement $')'
+                                               |  $'(' *expr $')'
            expr_expr                           =  *expr_term
+                                               |  *expr_expr $'+' *expr_term
+                                               |  *expr_expr $'-' *expr_term
+                                               |  *expr_expr $'&' *expr_term
+                                               |  *expr_expr $'|' *expr_term
+                                               |  *expr_expr $'^' *expr_term
            expr_factor                         =  *expr_element
+                                               |  $'+' *expr_factor
+                                               |  $'-' *expr_factor
+                                               |  $'~' *expr_factor
            expr_list                           =  *expr | *expr_list $',' *expr
            expr_term                           =  *expr_factor
+                                               |  *expr_term $'*' *expr_factor
+                                               |  *expr_term $'/' *expr_factor
+                                               |  *expr_term $'%' *expr_factor
            extended_value                      =  $'_NUMBER_'
            fetch_statement                     =  FETCH *cursor_name *fetch_statement_1
            fetch_statement_1                   =  epsilon | INTO *fetch_target_list
            fetch_target                        =  *local_variable
            fetch_target_list                   =  *fetch_target | *fetch_target_list $',' *fetch_target
            global_variable                     =  *at_at_ident
            goto_statement                      =  GOTO *ident
            grant_statement                     =  GRANT
+                                                  *grant_statement_1
+                                                  ON
+                                                  *owner_object
+                                                  *grant_statement_2
+                                                  TO
+                                                  *grant_statement_3
+                                                  *grant_statement_4
+                                               |  GRANT *grant_statement_5 TO *grant_statement_6
            grant_statement_1                   =  ALL *grant_statement_1_1 | *permission_list
            grant_statement_1_1                 =  epsilon | PRIVILEGES
            grant_statement_2                   =  epsilon | $'(' *column_name_list $')'
            grant_statement_3                   =  PUBLIC | *name_list
            grant_statement_4                   =  epsilon | WITH GRANT OPTION
            grant_statement_5                   =  ALL *grant_statement_5_1 | *command_list
            grant_statement_5_1                 =  epsilon | PRIVILEGES
            grant_statement_6                   =  NULL | PUBLIC | *name_list
            ident                               =  $'_IDENT_' | LOG
            index_access                        =  epsilon
+                                               |  $'(' INDEX *index_name *index_access_1 *index_access_2 $')'
            index_access_1                      =  epsilon | PREFETCH *size
            index_access_2                      =  epsilon | *index_access_2_1
            index_access_2_1                    =  LRU | MRU
            index_name                          =  *ident
            insert_statement                    =  INSERT
+                                                  *insert_statement_1
+                                                  *table_or_view
+                                                  *insert_statement_2
+                                                  *insert_statement_3
            insert_statement_1                  =  epsilon | INTO
            insert_statement_2                  =  epsilon | $'(' *column_name_list $')'
            insert_statement_3                  =  VALUES $'(' *expr_list $')' | *select_expr
            kill_statement                      =  KILL *number
            label_statement                     =  *label
            load_option                         =  *ident $'_EQ_' *expr
            load_options                        =  *load_option | *load_options $',' *load_option
            load_statement                      =  LOAD
+                                                  *load_statement_1
+                                                  *database_name
+                                                  *load_statement_2
+                                                  *database_device
+                                                  *load_statement_3
+                                                  *load_statement_4
+                                                  *load_statement_5
+                                                  *load_statement_6
            load_statement_1                    =  DATABASE | TRAN | TRANSACTION
            load_statement_2                    =  FROM | TO
            load_statement_3                    =  epsilon | AT *server_name
            load_statement_4                    =  epsilon | *load_options
            load_statement_5                    =  epsilon
+                                               |  *load_statement_5
+                                                  STRIPE
+                                                  ON
+                                                  *database_device
+                                                  *load_statement_5_1
+                                                  *load_statement_5_2
            load_statement_5_1                  =  epsilon | AT *server_name
            load_statement_5_2                  =  epsilon | *load_options
            load_statement_6                    =  epsilon | WITH *load_statement_6_1
            load_statement_6_1                  =  epsilon | *load_options
            local_variable                      =  *at_ident
            logical_expr                        =  *boolean_expr | *condition
            name_list                           =  *ident | *name_list $',' *ident
            number                              =  $'_NUMBER_'
            object                              =  *ident
+                                               |  *ident $'.' *ident
+                                               |  *ident $'.' $'.' *ident
+                                               |  *ident $'.' *ident $'.' *ident
            object_list                         =  *object | *object_list $',' *object
            online_database_statement           =  ONLINE DATABASE *database_name
            open_statement                      =  OPEN *cursor_name
            opt_any_or_all                      =  epsilon | *opt_any_or_all_1
            opt_any_or_all_1                    =  ANY | ALL
            owner_object                        =  *ident | *ident $'.' *ident
            owner_object_list                   =  *owner_object | *owner_object_list $',' *owner_object
            parameter                           =  *at_ident
            permission                          =  DELETE | EXEC | EXECUTE | INSERT | REFERENCES | SELECT | UPDATE
            permission_list                     =  *permission | *permission_list $',' *permission
            prepare_transaction_statement       =  PREPARE *prepare_transaction_statement_1
            prepare_transaction_statement_1     =  TRAN | TRANSACTION
            print_argument                      =  *number | *string | *local_variable | *global_variable
            print_arguments                     =  *print_argument | *print_arguments $',' *print_argument
            print_statement                     =  PRINT *print_arguments
            raiserror_argument                  =  *string | *local_variable
            raiserror_arguments                 =  *raiserror_argument | *raiserror_arguments $',' *raiserror_argument
            raiserror_extended_value            =  *extended_value $'_EQ_' *extended_value
            raiserror_extended_values           =  *raiserror_extended_value
+                                               |  *raiserror_extended_values $',' *raiserror_extended_value
            raiserror_statement                 =  RAISERROR
+                                                  *error_number
+                                                  *raiserror_statement_1
+                                                  *raiserror_statement_2
            raiserror_statement_1               =  epsilon | *raiserror_statement_1_1 *raiserror_arguments
            raiserror_statement_1_1             =  epsilon | $','
            raiserror_statement_2               =  epsilon | *raiserror_extended_values
            readtext_statement                  =  READTEXT
+                                                  *column
+                                                  *readtext_statement_1
+                                                  *number
+                                                  *number
+                                                  *readtext_statement_2
+                                                  *readtext_statement_3
+                                                  *readtext_statement_4
            readtext_statement_1                =  *local_variable | *number
            readtext_statement_2                =  epsilon | HOLDLOCK
            readtext_statement_3                =  epsilon | USING *ident
            readtext_statement_4                =  epsilon | AT ISOLATION *readtext_statement_4_1
            readtext_statement_4_1              =  READ UNCOMMITTED | READ COMMITTED | SERIALIZABLE
            reconfigure_statement               =  RECONFIGURE *reconfigure_statement_1
            reconfigure_statement_1             =  epsilon | WITH OVERRIDE
            return_statement                    =  RETURN | RETURN *expr
            return_status                       =  *at_ident
            revoke_statement                    =  REVOKE *revoke_statement_1
            revoke_statement_1                  =  *revoke_statement_1_1
+                                                  ON
+                                                  *owner_object
+                                                  *revoke_statement_1_2
+                                                  *revoke_statement_1_3
+                                                  *revoke_statement_1_4
+                                                  *revoke_statement_1_5
+                                               |  GRANT
+                                                  OPTION
+                                                  FOR
+                                                  *revoke_statement_1_6
+                                                  ON
+                                                  *owner_object
+                                                  *revoke_statement_1_7
+                                                  *revoke_statement_1_8
+                                                  *revoke_statement_1_9
+                                                  *revoke_statement_1_10
+                                               |  *revoke_statement_1_11 *revoke_statement_1_12 *revoke_statement_1_13
            revoke_statement_1_1                =  *all_privileges | *permission_list
            revoke_statement_1_10               =  epsilon | CASCADE
            revoke_statement_1_11               =  *all_privileges | *command_list
            revoke_statement_1_12               =  FROM | TO
            revoke_statement_1_13               =  PUBLIC | *name_list
            revoke_statement_1_2                =  epsilon | $'(' *column_name_list $')'
            revoke_statement_1_3                =  FROM | TO
            revoke_statement_1_4                =  PUBLIC | *name_list
            revoke_statement_1_5                =  epsilon | CASCADE
            revoke_statement_1_6                =  *all_privileges | *permission_list
            revoke_statement_1_7                =  epsilon | $'(' *column_name_list $')'
            revoke_statement_1_8                =  FROM | TO
            revoke_statement_1_9                =  PUBLIC | *name_list
            rollback_transaction_statement      =  ROLLBACK
+                                                  *rollback_transaction_statement_1
+                                                  *rollback_transaction_statement_2
            rollback_transaction_statement_1    =  TRANSACTION | TRAN | WORK
            rollback_transaction_statement_2    =  epsilon | *transaction_name
            rollback_trigger_statement          =  ROLLBACK TRIGGER *rollback_trigger_statement_1
            rollback_trigger_statement_1        =  epsilon | WITH *raiserror_statement
            row_aggregate                       =  AVG | SUM | MIN | MAX | COUNT
            save_transaction_statement          =  SAVE *save_transaction_statement_1 *savepoint_name
            save_transaction_statement_1        =  TRANSACTION | TRAN
            savepoint_name                      =  *ident
            segment_name                        =  *ident | $'_SQ_STRING_' | $'_DQ_STRING_' | *local_variable
            select_all_or_distinct              =  epsilon | *select_all_or_distinct_1
            select_all_or_distinct_1            =  ALL | DISTINCT
            select_at_isolation                 =  AT ISOLATION *select_at_isolation_1
            select_at_isolation_1               =  READ UNCOMMITTED | READ COMMITTED | SERIALIZABLE
            select_compute                      =  *row_aggregate $'(' *column_name $')'
            select_compute_list                 =  *select_compute | *select_compute_list $',' *select_compute
            select_expr                         =  *select_statement
+                                               |  *select_expr UNION *select_expr_term
+                                               |  *select_expr UNION ALL *select_expr_term
            select_expr_term                    =  *select_statement | $'(' *select_expr $')'
            select_for_browse                   =  FOR BROWSE
            select_for_read_only                =  FOR READ ONLY
            select_for_update                   =  FOR UPDATE *select_for_update_1
            select_for_update_1                 =  epsilon | OF *column_name_list
            select_item                         =  SYB_IDENTITY
+                                               |  *ident $'.' $'*'
+                                               |  *ident $'.' SYB_IDENTITY
+                                               |  *ident $'.' *ident $'.' $'*'
+                                               |  *alias $'_EQ_' *expr
+                                               |  *local_variable $'_EQ_' *expr
+                                               |  *expr
+                                               |  *expr *alias
+                                               |  *expr AS *alias
            select_item_list                    =  *select_item | *select_item_list $',' *select_item
            select_order_by_expr                =  *expr *select_order_by_expr_1
            select_order_by_expr_1              =  epsilon | *select_order_by_expr_1_1
            select_order_by_expr_1_1            =  ASC | DESC
            select_order_by_expr_list           =  *select_order_by_expr
+                                               |  *select_order_by_expr_list $',' *select_order_by_expr
            select_reference                    =  *table_or_view
+                                                  *select_reference_1
+                                                  *index_access
+                                                  *select_reference_2
+                                                  *select_reference_3
            select_reference_1                  =  epsilon | *ident
            select_reference_2                  =  epsilon | *select_reference_2_1
            select_reference_2_1                =  HOLDLOCK | NOHOLDLOCK
            select_reference_3                  =  epsilon | SHARED
            select_references                   =  *select_reference | *select_references $',' *select_reference
            select_statement                    =  SELECT
+                                                  *select_all_or_distinct
+                                                  *select_statement_1
+                                                  *select_statement_2
+                                                  *select_statement_3
+                                                  *select_statement_4
+                                                  *select_statement_5
+                                                  *select_statement_6
+                                                  *select_statement_7
+                                                  *select_statement_8
+                                                  *select_statement_9
            select_statement_1                  =  $'*' | *select_item_list
            select_statement_2                  =  epsilon | INTO *table
            select_statement_3                  =  epsilon | FROM *select_references
            select_statement_4                  =  epsilon | WHERE *condition
            select_statement_5                  =  epsilon | GROUP BY *select_statement_5_1 *expr_list
            select_statement_5_1                =  epsilon | ALL
            select_statement_6                  =  epsilon | HAVING *condition
            select_statement_7                  =  epsilon | ORDER BY *select_order_by_expr_list
            select_statement_8                  =  *select_compute_stmts
            select_compute_stmts                =  epsilon | *select_compute_stmts *select_compute_stmt
            select_compute_stmt                 =  COMPUTE *select_compute_list *select_statement_8_1
            select_statement_8_1                =  epsilon | BY *column_name_list
            select_statement_9                  =  epsilon | *select_statement_9_1
            select_statement_9_1                =  *select_for_read_only
+                                               |  *select_for_read_only *select_at_isolation
+                                               |  *select_for_read_only *select_for_browse
+                                               |  *select_for_read_only *select_at_isolation *select_for_browse
+                                               |  *select_for_update
+                                               |  *select_for_update *select_at_isolation
+                                               |  *select_for_update *select_for_browse
+                                               |  *select_for_update *select_at_isolation *select_for_browse
+                                               |  *select_at_isolation
+                                               |  *select_at_isolation *select_for_browse
+                                               |  *select_for_browse
            server_name                         =  *ident
            server_procedure                    =  *ident
+                                               |  *ident $'.' *ident
+                                               |  *ident $'.' $'.' *ident
+                                               |  *ident $'.' *ident $'.' *ident
+                                               |  *ident $'.' $'.' $'.' *ident
+                                               |  *ident $'.' $'.' *ident $'.' *ident
+                                               |  *ident $'.' *ident $'.' $'.' *ident
+                                               |  *ident $'.' *ident $'.' *ident $'.' *ident
            set_on_or_off                       =  ON | OFF
            set_statement                       =  SET *ident *set_on_or_off
+                                               |  SET *ident *ident
+                                               |  SET *ident *number
+                                               |  SET *ident *string
+                                               |  SET *ident *string *set_on_or_off
+                                               |  SET *ident ARITH_OVERFLOW *set_on_or_off
+                                               |  SET *ident NUMERIC_TRUNCATION *set_on_or_off
+                                               |  SET CHAR_CONVERT *set_statement_1
+                                               |  SET CURSOR ROWS *number FOR *cursor_name
+                                               |  SET TABLE COUNT *number
+                                               |  SET TRANSACTION ISOLATION LEVEL *number
            set_statement_1                     =  OFF | ON *set_statement_1_1 | *ident *set_statement_1_2
            set_statement_1_1                   =  epsilon | WITH *ident
            set_statement_1_2                   =  epsilon | WITH *ident
            setuser_statement                   =  SETUSER | SETUSER *string
            shutdown_statement                  =  SHUTDOWN *shutdown_statement_1 *shutdown_statement_2
            shutdown_statement_1                =  epsilon | *server_name
            shutdown_statement_2                =  epsilon | WITH *shutdown_statement_2_1
            shutdown_statement_2_1              =  WAIT | NOWAIT
            size                                =  $'_NUMBER_'
            statement                           =  *eos
+                                               |  *execute_command *eos
+                                               |  *execute_command *SQL_statements *eos
+                                               |  *SQL_statements *eos
+                                               |  *SQL_nonbatch_statement *eos
+                                               |  *error *SQL_nonbatch_statement *eos
            statements                          =  epsilon | *statements *statement
            string                              =  $'_SQ_STRING_' | $'_DQ_STRING_'
            table                               =  *ident
+                                               |  *ident $'.' *ident
+                                               |  *ident $'.' $'.' *ident
+                                               |  *ident $'.' *ident $'.' *ident
            table_index_name                    =  *table_name $'.' *index_name
            table_index_name_list               =  *table_index_name | *table_index_name_list $',' *table_index_name
            table_name                          =  *ident
            table_or_view                       =  *ident
+                                               |  *ident $'.' *ident
+                                               |  *ident $'.' $'.' *ident
+                                               |  *ident $'.' *ident $'.' *ident
            time                                =  *string
            transaction_name                    =  *ident
            truncate_statement                  =  TRUNCATE TABLE *table
            update_from_clause                  =  *update_from_entity | *update_from_clause $',' *update_from_entity
            update_from_entity                  =  *table_or_view *update_from_entity_1 *index_access
            update_from_entity_1                =  epsilon | *ident
            update_statement                    =  UPDATE
+                                                  *table_or_view
+                                                  SET
+                                                  *column
+                                                  $'_EQ_'
+                                                  *expr
+                                                  *update_statement_1
+                                                  *update_statement_2
            update_statement_1                  =  epsilon | *update_statement_1 $',' *column_name $'_EQ_' *expr
            update_statement_2                  =  epsilon | *update_statement_2_1
            update_statement_2_1                =  FROM *update_from_clause
+                                               |  FROM *update_from_clause WHERE *condition
+                                               |  WHERE *condition
+                                               |  WHERE CURRENT OF *cursor_name
            update_statistics_statement         =  UPDATE STATISTICS *table *update_statistics_statement_1
            update_statistics_statement_1       =  epsilon | *index_name
            use_statement                       =  USE *database_name
            waitfor_statement                   =  WAITFOR *waitfor_statement_1
            waitfor_statement_1                 =  DELAY *time | TIME *time | ERROREXIT | PROCESSEXIT | MIRROREXIT
            while_statement                     =  WHILE *logical_expr *SQL_command_statement
            writetext_statement                 =  WRITETEXT *column *expr *writetext_statement_1 *string
            writetext_statement_1               =  epsilon | WITH LOG
