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
+                                               |  *create_table_statement
+                                               |  *dbcc_statement
+                                               |  *deallocate_cursor_statement
+                                               |  *declare_cursor_statement
+                                               |  *declare_statement
+                                               |  *delete_statement
+                                               |  *disk_init_statement
+                                               |  *disk_statement
+                                               |  *drop_database_statement
+                                               |  *drop_default_statement
+                                               |  *drop_index_statement
+                                               |  *drop_procedure_statement
+                                               |  *drop_rule_statement
+                                               |  *drop_table_statement
+                                               |  *drop_trigger_statement
+                                               |  *drop_view_statement
+                                               |  *dump_database_statement
+                                               |  *dump_transaction_statement
+                                               |  *execute_statement
+                                               |  *encrypted_statement
+                                               |  *fetch_statement
+                                               |  *goto_statement
+                                               |  *grant_statement
+                                               |  *insert_statement
+                                               |  *kill_statement
+                                               |  *label_statement
+                                               |  *load_database_statement
+                                               |  *load_header_statement
+                                               |  *load_transaction_statement
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
+                                               |  *save_transaction_statement
+                                               |  *select_expr
+                                               |  *set_statement
+                                               |  *setuser_statement
+                                               |  *shutdown_statement
+                                               |  *truncate_statement
+                                               |  *update_statement
+                                               |  *update_statistics_statement
+                                               |  *updatetext_statement
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
            alias                               =  *new_ident | $'_DQ_STRING_' | $'_SQ_STRING_' | NAME
            all_privileges                      =  ALL *all_privileges_1
            all_privileges_1                    =  epsilon | PRIVILEGES
            alter_database_statement            =  ALTER
+                                                  DATABASE
+                                                  *database_name
+                                                  *alter_database_statement_1
+                                                  *alter_database_statement_2
            alter_database_statement_1          =  epsilon | ON *database_on_devices
            alter_database_statement_2          =  epsilon | FOR LOAD
            alter_table_nocheck                 =  epsilon | WITH CHECK | WITH NOCHECK
            alter_table_statement               =  ALTER TABLE *table *alter_table_nocheck *alter_table_statement_1
            alter_table_statement_1             =  ADD *column_definitions
+                                               |  ADD *constraint_definitions
+                                               |  DROP *constraint_keyword_name
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
            column_definition                   =  *column_name *column_data *column_rowguid *column_definition_2
            column_data                         =  *datatype
            column_properties                   =  IDENTITY *seed_increment
            seed_increment                      =  epsilon | $'(' *number $',' *number $')'
            column_rowguid                      =  epsilon | ROWGUIDCOL
            column_definition_2                 =  epsilon | *column_definition_2 *column_definition_2_1
            column_definition_2_1               =  *column_definition_2_1_1 *column_definition_2_1_4
+                                               |  *column_definition_2_1_1 *column_definition_2_1_2
+                                               |  *column_definition_2_1_1 *column_properties
+                                               |  *column_definition_2_1_1 *column_definition_2_1_3
            column_definition_2_1_1             =  epsilon | CONSTRAINT *constraint_name
            column_definition_2_1_2             =  NULL | NOT NULL
            column_definition_2_1_4             =  DEFAULT *expr *optional_for_column
            column_definition_2_1_3             =  UNIQUE *column_definition_2_1_3_1 *constraint_options
+                                               |  PRIMARY KEY *column_definition_2_1_3_2 *constraint_options
+                                               |  REFERENCES
+                                                  *table
+                                                  *column_definition_2_1_3_3
+                                                  *check_not_for_replication
+                                               |  CHECK *check_not_for_replication $'(' *condition $')'
            column_definition_2_1_3_1           =  epsilon | CLUSTERED | NONCLUSTERED
            column_definition_2_1_3_2           =  epsilon | CLUSTERED | NONCLUSTERED
            column_definition_2_1_3_3           =  epsilon | $'(' *column_name $')'
            column_definitions                  =  *column_definition | *column_definitions $',' *column_definition
            column_name                         =  *ident | NAME
            column_name_list                    =  *column_name | *column_name_list $',' *column_name
            optional_for_column                 =  epsilon | FOR *column_name
            on_filegroup                        =  ON *filegroup_name
            filegroup_name                      =  DEFAULT | *sq_string | *local_variable | *identifier
            command                             =  CREATE DATABASE
+                                               |  CREATE DEFAULT
+                                               |  CREATE PROCEDURE
+                                               |  CREATE RULE
+                                               |  CREATE TABLE
+                                               |  CREATE VIEW
+                                               |  DUMP TABLE
+                                               |  DUMP DATABASE
+                                               |  DUMP TRANSACTION
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
            constraint_definitions              =  *constraint_definition
+                                               |  *constraint_definitions $',' *constraint_definition
            constraint_definition               =  *constraint_definition_1 *constraint_definition_2
            constraint_definition_1             =  epsilon | CONSTRAINT *constraint_name
            constraint_definition_2             =  DEFAULT *expr *optional_for_column
+                                               |  UNIQUE
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
+                                                  *check_not_for_replication
+                                               |  CHECK *check_not_for_replication $'(' *condition $')'
            check_not_for_replication           =  epsilon | NOT FOR REPLICATION
            constraint_definition_2_1           =  epsilon | CLUSTERED | NONCLUSTERED
            constraint_definition_2_2           =  epsilon | CLUSTERED | NONCLUSTERED
            constraint_definition_2_3           =  epsilon | $'(' *constraint_ref_column_list $')'
            column_list                         =  *column_name | *column_list $',' *column_name
            constraint_frm_column_list          =  *column_name | *constraint_frm_column_list $',' *column_name
            constraint_keyword                  =  epsilon | CONSTRAINT
            constraint_keyword_name             =  *constraint_keyword *constraint_name
            constraint_ref_column_list          =  *column_name | *constraint_ref_column_list $',' *column_name
            constraint_name                     =  *ident
            constraint_options                  =  *constraint_options_1 *constraint_options_2
            constraint_options_1                =  epsilon | WITH *constraint_options_1_1
            constraint_options_1_1              =  FILLFACTOR $'_EQ_' *number | MAX_ROWS_PER_PAGE $'_EQ_' *number
            constraint_options_2                =  epsilon | *on_filegroup
            continue_statement                  =  CONTINUE
            create_database_statement           =  CREATE
+                                                  DATABASE
+                                                  *database_name
+                                                  *create_database_statement_1
+                                                  *create_database_statement_2
+                                                  *create_database_statement_3
            create_database_statement_1         =  epsilon | ON *database_on
            create_database_statement_2         =  epsilon | LOG ON *database_on_devices | LOG ON *filespec_s
            create_database_statement_3         =  epsilon | FOR *load_or_attach
            database_on                         =  *database_on_devices | *database_on_files
            load_or_attach                      =  LOAD | ATTACH
            database_on_files                   =  *optional_primary *filespec_s
            filespec_s                          =  *filespec
+                                               |  *filespec_s $',' *filespec
+                                               |  *filespec_s $',' *filegroup_s
            filespec                            =  $'('
+                                                  *optional_logical_filename
+                                                  *filename
+                                                  *optional_file_parameter_s
+                                                  $')'
            optional_logical_filename           =  epsilon | NAME $'_EQ_' *logical_filename $','
            logical_filename                    =  *new_ident | $'_SQ_STRING_'
            filename                            =  FILENAME $'_EQ_' $'_SQ_STRING_'
            optional_file_parameter_s           =  epsilon | *optional_file_parameter_s *file_parameter
            file_parameter                      =  $',' SIZE $'_EQ_' *size
+                                               |  $',' MAXSIZE $'_EQ_' *maxsize_or_unlimited
+                                               |  $',' FILEGROWTH $'_EQ_' *size
            size                                =  *number | *number MB | *number KB | *number $'%'
            optional_primary                    =  epsilon | PRIMARY
            maxsize_or_unlimited                =  *size | UNLIMITED
            filegroup_s                         =  FILEGROUP *ident *filespec_s
            database_on_devices                 =  *database_on_devices_1 *database_on_devices_2
+                                               |  *database_on_devices $',' *database_device *database_on_devices_2
            database_on_devices_1               =  DEFAULT | *database_device
            database_on_devices_2               =  epsilon | $'_EQ_' *size
            create_default_statement            =  CREATE DEFAULT *owner_object AS *expr
            create_index_option                 =  epsilon
+                                               |  FILLFACTOR $'_EQ_' *number
+                                               |  PAD_INDEX
+                                               |  ALLOW_DUP_ROW
+                                               |  IGNORE_DUP_ROW
+                                               |  IGNORE_DUP_KEY
+                                               |  SORTED_DATA
+                                               |  SORTED_DATA_REORG
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
            create_index_statement_4            =  epsilon | *on_filegroup
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
            create_procedure_statement_4        =  FOR REPLICATION *with_encryption
+                                               |  WITH RECOMPILE *with_encryption
+                                               |  *with_encryption
            create_rule_statement               =  CREATE RULE *owner_object AS *condition
            create_table_definition             =  epsilon | *column_definition | *constraint_definition
            create_table_definitions            =  *create_table_definition
+                                               |  *create_table_definitions $',' *create_table_definition
            create_table_statement              =  CREATE
+                                                  TABLE
+                                                  *table
+                                                  $'('
+                                                  *create_table_definitions
+                                                  $')'
+                                                  *create_table_statement_2
+                                                  *create_table_statement_3
            create_table_statement_2            =  epsilon | *on_filegroup
            create_table_statement_3            =  epsilon | TEXTIMAGE_ON *new_ident
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
+                                                  *with_encryption
+                                                  AS
+                                                  *create_trigger_body
            create_view_statement               =  CREATE
+                                                  VIEW
+                                                  *owner_object
+                                                  *create_view_statement_1
+                                                  *with_encryption
+                                                  AS
+                                                  *select_expr
+                                                  *create_view_statement_2
            create_view_statement_1             =  epsilon | $'(' *column_name_list $')'
            create_view_statement_2             =  epsilon | WITH CHECK OPTION
            cursor_name                         =  *ident
            database_device                     =  *ident | *local_variable
            database_name                       =  *ident | *local_variable
            database_name_list                  =  *database_name | *database_name_list $',' *database_name
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
            date                                =  *ident | *local_variable
            date_format                         =  *ident
            dbcc_statement                      =  DBCC *ident | DBCC *ident $'(' *expr_list $')'
            deallocate_cursor_statement         =  DEALLOCATE *cursor_name
            declare_cursor_statement            =  DECLARE *cursor_name CURSOR FOR *select_statement
            declare_local_variable              =  *local_variable *datatype
            declare_local_variables             =  *declare_local_variable
+                                               |  *declare_local_variables $',' *declare_local_variable
            declare_statement                   =  DECLARE *declare_local_variables
            delete_statement                    =  DELETE
+                                                  *delete_statement_1
+                                                  *table_or_view
+                                                  *delete_statement_2
+                                                  *delete_statement_3
            delete_statement_1                  =  epsilon | FROM
            delete_statement_2                  =  epsilon | FROM *delete_tables
            delete_statement_3                  =  epsilon | *delete_statement_3_1
            delete_statement_3_1                =  WHERE *condition | WHERE CURRENT OF *cursor_name
            delete_tables                       =  *delete_table | *delete_tables $',' *delete_table
            delete_table                        =  *table_or_view | *table_or_view *alias
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
            disk_init_statement_1               =  NAME $'_EQ_' *string
            disk_init_statement_2               =  PHYSNAME $'_EQ_' *string
            disk_init_statement_3               =  VDEVNO $'_EQ_' *number
            disk_init_statement_4               =  SIZE $'_EQ_' *number
            disk_init_statement_5               =  epsilon | $',' VSTART $'_EQ_' *number
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
            dump_database_statement             =  DUMP
+                                                  DATABASE
+                                                  *database_name
+                                                  TO
+                                                  *dump_devices
+                                                  *dump_database_statement_1
            dump_database_statement_1           =  epsilon | WITH *dump_database_options
            dump_database_options               =  *dump_database_option
+                                               |  *dump_database_options $',' *dump_database_option
            dump_database_option                =  *dump_transaction_option | *stats_percentage
            dump_device                         =  *dump_name_or_device *dump_volume_optional
            dump_device_name                    =  *ident | *local_variable
            dump_device_type                    =  DISK | FLOPPY | PIPE | TAPE
            dump_devices                        =  *dump_device | *dump_devices $',' *dump_device
            dump_device_var                     =  $'_SQ_STRING_' | *local_variable
            dump_name_or_device                 =  *dump_device_name | *dump_device_type $'_EQ_' *dump_device_var
            dump_transaction_option             =  *unload_nounload
+                                               |  *init_noinit
+                                               |  *skip_noskip
+                                               |  *expire_date
+                                               |  *retain_days
            dump_transaction_options            =  *dump_transaction_option
+                                               |  *dump_transaction_options $',' *dump_transaction_option
            dump_transaction_statement          =  DUMP
+                                                  TRANSACTION
+                                                  *database_name
+                                                  TO
+                                                  *dump_devices
+                                                  *dump_transaction_statement_1
            dump_transaction_statement_1        =  WITH *dump_truncate_option *dump_transaction_options
            dump_truncate_option                =  TRUNCATE_ONLY
            dump_volume_optional                =  VOLUME $'_EQ_' *database_device
            eos                                 =  GO
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
            execute_parameter_1_1               =  OUTPUT
            execute_parameter_2                 =  epsilon | *execute_parameter_2_1
            execute_parameter_2_1               =  OUTPUT
            execute_parameters                  =  *execute_parameter | *execute_parameters $',' *execute_parameter
            execute_statement                   =  *execute_statement_1 *execute_command
            execute_statement_1                 =  EXEC | EXECUTE
            execute_value                       =  COMMON
+                                               |  FOREIGN
+                                               |  MRU
+                                               |  NULL
+                                               |  PREFETCH
+                                               |  PRIMARY
+                                               |  REPLACE
+                                               |  *new_ident
+                                               |  *string
+                                               |  *number
            expire_date                         =  EXPIREDATE $'_EQ_' *date
            expr                                =  *expr_expr
            expr_element                        =  NULL
+                                               |  *number
+                                               |  NAME
+                                               |  *real
+                                               |  $'$' *number
+                                               |  $'$' *real
+                                               |  *local_variable
+                                               |  *global_variable
+                                               |  *column
+                                               |  *sq_string
+                                               |  *nls_element
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
            nls_element                         =  IDDL_N *sq_string
            encrypted_statement                 =  $'_LT_' ENCRYPTED $'_GT_'
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
            grant_statement_3                   =  *name_list
            grant_statement_4                   =  epsilon | WITH GRANT OPTION
            grant_statement_5                   =  ALL *grant_statement_5_1 | *command_list
            grant_statement_5_1                 =  epsilon | PRIVILEGES
            grant_statement_6                   =  NULL | *name_list
            ident                               =  *new_ident | *dq_string
            new_ident                           =  *identifier | LOG
            identifier                          =  $'_IDENT_' | PUBLIC | IDDL_N | $'_DELIM_IDENT_'
            index_name                          =  *ident
            init_noinit                         =  INIT | NOINIT
            insert_expr                         =  *expr | DEFAULT
            insert_expr_list                    =  *insert_expr | *insert_expr_list $',' *insert_expr
            insert_statement                    =  INSERT
+                                                  *insert_statement_1
+                                                  *table_or_view
+                                                  *insert_statement_2
+                                                  *insert_statement_3
            insert_statement_1                  =  epsilon | INTO
            insert_statement_2                  =  epsilon | $'(' *column_name_list $')'
            insert_statement_3                  =  DEFAULT VALUES | VALUES $'(' *insert_expr_list $')' | *select_expr
            kill_statement                      =  KILL *number
            label_statement                     =  *label
            load_option                         =  *ident $'_EQ_' *expr
+                                               |  *unload_nounload
+                                               |  *skip_noskip
+                                               |  FILE $'_EQ_' *number
            load_database_statement             =  LOAD
+                                                  DATABASE
+                                                  *database_name
+                                                  FROM
+                                                  *dump_devices
+                                                  *load_database_statement_1
            load_database_statement_1           =  WITH *load_database_options
            load_database_option                =  *load_option | *stats_percentage
            load_database_options               =  *load_database_option
+                                               |  *load_database_options $',' *load_database_option
            load_header_statement               =  LOAD HEADERONLY FROM *dump_device
            load_transaction_options            =  *load_option | *load_transaction_options $',' *load_option
            load_transaction_statement          =  LOAD
+                                                  TRANSACTION
+                                                  *database_name
+                                                  FROM
+                                                  *dump_devices
+                                                  *load_transaction_statement_1
            load_transaction_statement_1        =  WITH *load_transaction_options
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
            optional_percentage                 =  epsilon | $'_EQ_' *number
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
            raiserror_argument                  =  $',' *datatype | $',' *local_variable
            raiserror_arguments                 =  *raiserror_argument | *raiserror_arguments *raiserror_argument
            raiserror_statement                 =  RAISERROR
+                                                  $'('
+                                                  *raiserror_statement_1
+                                                  $','
+                                                  *raiserror_statement_2
+                                                  $','
+                                                  *raiserror_statement_3
+                                                  *raiserror_statement_4
+                                                  $')'
+                                                  *raiserror_statement_5
            raiserror_statement_1               =  *number | $'_SQ_STRING_' | $'_DQ_STRING_'
            raiserror_statement_2               =  *number
            raiserror_statement_3               =  *number
            raiserror_statement_4               =  epsilon | *raiserror_arguments
            raiserror_statement_5               =  epsilon | WITH LOG | WITH NOWAIT
            readtext_statement                  =  READTEXT
+                                                  *column
+                                                  *readtext_statement_1
+                                                  *number
+                                                  *number
+                                                  *readtext_statement_2
            readtext_statement_1                =  *local_variable | *number
            readtext_statement_2                =  epsilon | HOLDLOCK
            real                                =  $'_REAL_'
            retain_days                         =  RETAINDAYS $'_EQ_' *date
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
            revoke_statement_1_13               =  *name_list
            revoke_statement_1_2                =  epsilon | $'(' *column_name_list $')'
            revoke_statement_1_3                =  FROM | TO
            revoke_statement_1_4                =  *name_list
            revoke_statement_1_5                =  epsilon | CASCADE
            revoke_statement_1_6                =  *all_privileges | *permission_list
            revoke_statement_1_7                =  epsilon | $'(' *column_name_list $')'
            revoke_statement_1_8                =  FROM | TO
            revoke_statement_1_9                =  *name_list
            rollback_transaction_statement      =  ROLLBACK
+                                                  *rollback_transaction_statement_1
+                                                  *rollback_transaction_statement_2
            rollback_transaction_statement_1    =  TRANSACTION | TRAN
            rollback_transaction_statement_2    =  epsilon | *transaction_name
            row_aggregate                       =  AVG | SUM | MIN | MAX | COUNT
            save_transaction_statement          =  SAVE *save_transaction_statement_1 *savepoint_name
            save_transaction_statement_1        =  TRANSACTION | TRAN
            savepoint_name                      =  *ident
            select_all_or_distinct              =  epsilon | *select_all_or_distinct_1
            select_all_or_distinct_1            =  ALL | DISTINCT
            select_compute                      =  *row_aggregate $'(' *column_name $')'
            select_compute_list                 =  *select_compute | *select_compute_list $',' *select_compute
            select_expr                         =  *select_statement
+                                               |  *select_expr UNION *select_expr_term
+                                               |  *select_expr UNION ALL *select_expr_term
            select_expr_term                    =  *select_statement | $'(' *select_expr $')'
            select_for_browse                   =  FOR BROWSE
            select_item                         =  SYB_IDENTITY
+                                               |  *ident $'.' $'*'
+                                               |  *ident $'.' SYB_IDENTITY
+                                               |  *ident $'.' *ident $'.' $'*'
+                                               |  $'*'
+                                               |  *alias $'_EQ_' *expr
+                                               |  *local_variable $'_EQ_' *expr
+                                               |  ROWGUIDCOL
+                                               |  *expr
+                                               |  *expr *alias
+                                               |  *expr AS *alias
            select_item_list                    =  *select_item | *select_item_list $',' *select_item
            select_order_by_expr                =  *expr *select_order_by_expr_1
            select_order_by_expr_1              =  epsilon | *select_order_by_expr_1_1
            select_order_by_expr_1_1            =  ASC | DESC
            select_order_by_expr_list           =  *select_order_by_expr
+                                               |  *select_order_by_expr_list $',' *select_order_by_expr
            select_reference                    =  *table_reference | *joined_table
            table_reference                     =  *table_or_view *select_reference_1 *select_reference_2
            joined_table                        =  *joined_table_1 *join_type *joined_table_1 ON *condition
+                                               |  *table_reference CROSS JOIN *table_reference
            joined_table_1                      =  *select_reference | $'(' *select_reference $')'
            join_type                           =  *join_type_1 *join_hint JOIN
            join_type_1                         =  INNER | *join_type_1_1 *join_type_1_2
            join_type_1_1                       =  LEFT | RIGHT | FULL
            join_type_1_2                       =  epsilon | OUTER
            join_hint                           =  epsilon | LOOP | HASH | MERGE | REMOTE
            select_reference_1                  =  epsilon | *select_reference_1_1 *ident
            select_reference_1_1                =  epsilon | AS
            select_reference_2                  =  epsilon
+                                               |  $'(' *select_optimizer_hints $')'
+                                               |  WITH $'(' *select_optimizer_hints $')'
            select_optimizer_hints              =  *select_optimizer_hint
+                                               |  *select_optimizer_hints $',' *select_optimizer_hint
            select_optimizer_hint               =  HOLDLOCK
+                                               |  NOLOCK
+                                               |  UPDLOCK
+                                               |  TABLOCK
+                                               |  PAGLOCK
+                                               |  TABLOCKX
+                                               |  FASTFIRSTROW
+                                               |  INDEX $'_EQ_' *select_optimizer_index
            select_optimizer_index              =  *ident | *number
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
            select_statement_1                  =  *select_item_list
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
            select_statement_9                  =  epsilon | *select_for_browse
            server_procedure                    =  *ident
+                                               |  *ident $'.' *ident
+                                               |  *ident $'.' $'.' *ident
+                                               |  *ident $'.' *ident $'.' *ident
+                                               |  *ident $'.' $'.' $'.' *ident
+                                               |  *ident $'.' $'.' *ident $'.' *ident
+                                               |  *ident $'.' *ident $'.' $'.' *ident
+                                               |  *ident $'.' *ident $'.' *ident $'.' *ident
            set_ansi_null_dflt                  =  ANSI_NULL_DFLT_OFF | ANSI_NULL_DFLT_ON
            set_low_or_normal                   =  LOW | NORMAL
            set_on_or_off                       =  ON | OFF
            set_statement                       =  SET *set_statement_1
            set_statement_1                     =  *set_statement_1_1 *set_on_or_off
+                                               |  DATEFIRST *number
+                                               |  DATEFORMAT *date_format
+                                               |  DEADLOCKPRIORITY *set_low_or_normal
+                                               |  LANGUAGE *ident
+                                               |  ROWCOUNT *number
+                                               |  TEXTSIZE *number
+                                               |  QUOTED_IDENTIFIER *set_on_or_off
+                                               |  ANSI_NULLS *set_on_or_off
+                                               |  TRANSACTION ISOLATION LEVEL *transaction_level_type
            set_statement_1_1                   =  *set_ansi_null_dflt
+                                               |  ARITHABORT
+                                               |  ARITHIGNORE
+                                               |  FMTONLY
+                                               |  FORCEPLAN
+                                               |  IDENTITY_INSERT *table_name
+                                               |  NOCOUNT
+                                               |  NOEXEC
+                                               |  OFFSETS *set_stmt_keyword_list
+                                               |  PARSEONLY
+                                               |  PROCID
+                                               |  SHOWPLAN
+                                               |  STATISTICS IO
+                                               |  STATISTICS TIME
            set_stmt_keyword_list               =  COMPUTE
+                                               |  EXECUTE
+                                               |  FROM
+                                               |  PARAM
+                                               |  PROCEDURE
+                                               |  SELECT
+                                               |  STATEMENT
+                                               |  ORDER
+                                               |  TABLE
            setuser_statement                   =  SETUSER | SETUSER *string *setuser_statement_1
            setuser_statement_1                 =  epsilon | WITH NORESET
            shutdown_statement                  =  SHUTDOWN *shutdown_statement_1
            shutdown_statement_1                =  epsilon | WITH NOWAIT
            skip_noskip                         =  SKIP | NOSKIP
            statement                           =  *eos
+                                               |  *execute_command *eos
+                                               |  *execute_command *SQL_statements *eos
+                                               |  *SQL_statements *eos
+                                               |  *SQL_nonbatch_statement *eos
+                                               |  *error *SQL_nonbatch_statement *eos
            statements                          =  epsilon | *statements *statement
            stats_percentage                    =  STATS *optional_percentage
            string                              =  *sq_string | *nls_element | *dq_string
            sq_string                           =  $'_SQ_STRING_'
            dq_string                           =  $'_DQ_STRING_'
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
            transaction_level_type              =  READ COMMITTED | READ UNCOMMITTED | REPEATABLE READ | SERIALIZABLE
            transaction_name                    =  *ident
            truncate_statement                  =  TRUNCATE TABLE *table
            unload_nounload                     =  UNLOAD | NOUNLOAD
            update_column_or_variable           =  *update_column_expr | *update_variable | *update_variable_and_column
            update_column_list                  =  *update_column | *update_column_list $',' *update_column
            update_column                       =  *column $'_EQ_' *update_column_or_variable
            update_column_expr                  =  DEFAULT | *expr
            update_statement                    =  UPDATE
+                                                  *table_or_view
+                                                  SET
+                                                  *update_statement_1
+                                                  *update_statement_2
+                                                  *update_statement_3
            update_statement_1                  =  *update_column_list
            update_statement_2                  =  epsilon | FROM *update_statement_2_1
            update_statement_2_1                =  *select_reference | *update_statement_2_1 $',' *select_reference
            update_statement_3                  =  epsilon | WHERE *condition
            update_variable                     =  *ident $'_EQ_' *expr
            update_variable_and_column          =  *ident $'_EQ_' *column $'_EQ_' *expr
            update_statistics_statement         =  UPDATE STATISTICS *table *update_statistics_statement_1
            update_statistics_statement_1       =  epsilon | *index_name
            updatetext_statement                =  UPDATETEXT
+                                                  *column_name
+                                                  *expr
+                                                  *updatetext_statement_1
+                                                  *updatetext_statement_1
+                                                  *updatetext_statement_2
+                                                  *updatetext_statement_3
            updatetext_statement_1              =  NULL | *number
            updatetext_statement_2              =  WITH LOG
            updatetext_statement_3              =  *datatype | *column *local_variable
            use_statement                       =  USE *database_name
            waitfor_statement                   =  WAITFOR *waitfor_statement_1
            waitfor_statement_1                 =  DELAY *time | TIME *time | ERROREXIT | PROCESSEXIT | MIRROREXIT
            while_statement                     =  WHILE *logical_expr *SQL_command_statement
            with_encryption                     =  epsilon | WITH ENCRYPTION
            writetext_statement                 =  WRITETEXT *column *expr *writetext_statement_1 *string
            writetext_statement_1               =  epsilon | WITH LOG
