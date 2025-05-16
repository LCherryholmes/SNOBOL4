            ident                               =  *ident_not_kw | *ident_1 | *ident_2
            ident_not_kw                        =  *DQ_STRING | *IDENT
            ident_1                             =  NAME
+                                               |  NEW
+                                               |  OLD
+                                               |  TYPE
+                                               |  VALUE
+                                               |  NUMBER
+                                               |  SIZE
+                                               |  ON
+                                               |  PRECISION
+                                               |  DEFAULT
+                                               |  SYNONYM
+                                               |  TRIGGER
+                                               |  INDEX
+                                               |  SCALE
+                                               |  PUBLIC
            ident_2                             =  MAX | MIN
            ident_proc                          =  *ident_not_kw | *ident_1
            number                              =  *NUMBER
            alias                               =  *IDENT | *SQ_STRING
            sq_string                           =  *SQ_STRING
            indicator_variable                  =  *ident
            variable_name                       =  *ident
            descriptor_variable                 =  *ident
            occurrences                         =  *ident
            dbspace                             =  *ident
            cursor_id                           =  *ident
            conn_nm_variable                    =  *ident
            user_id_variable                    =  *ident
            auth_variable                       =  *ident
            blobspace                           =  *ident
            correlation_name                    =  *ident
            count_variable                      =  *ident
            cursor_name                         =  *ident
            data_variable                       =  *ident
            datetime_unit                       =  *ident
            diagnostics                         =  *ident
            display_label                       =  *ident
            en_var                              =  *ident
            ex_var                              =  *ident
            error_text_variable                 =  *ident
            error_variable                      =  *ident
            field_host_variable                 =  *ident
            filename                            =  *ident
            function_name                       =  *ident
            host_variable                       =  *ident
            integer_host_variable               =  *ident
            item_number_variable                =  *ident
            paragraph_name                      =  *ident
            parameter_name                      =  *ident
            procedure_variable                  =  *ident
            program                             =  *ident
            sqlda_pointer                       =  *ident
            st_var                              =  *ident
            statement_variable_name             =  *ident
            storage_sqlda_pointer               =  *ident
            storage_variable_name               =  *ident
            violations                          =  *ident
            storage_indicator_variable          =  *ident
            storage_descriptor_variable         =  *ident
            row_position                        =  *ident | *number
            statement_id                        =  *ident | *PREPARE
            size                                =  *number
            numrows                             =  *number
            percent                             =  *number
            clustersize                         =  *number
            conf                                =  *number
            except_num                          =  *number
            float_precision                     =  *number
            item_number                         =  *number
            literal_integer                     =  *number
            max                                 =  *number
            percent_of_resources                =  *number
            precision                           =  *number
            y_precision                         =  *number
            f_precision                         =  *number
            reserve                             =  *number
            rounding_factor                     =  *number
            scale                               =  *number
            seconds                             =  *number
            select_number                       =  *number
            start                               =  *number
            truncating_factor                   =  *number
            value                               =  *number
            volume_number                       =  *number
            kbytes                              =  *Expression
            Expression_Subset                   =  *Expression
            integer_expression                  =  *Expression
            month_integer_expression            =  *Expression
            day_integer_expression              =  *Expression
            year_integer_expression             =  *Expression
            character_expression                =  *Expression
            datedatetime_expression             =  *Expression
            first_kbytes                        =  *Expression
            next_kbytes                         =  *Expression
            float_expression                    =  *Expression
            increment_expression                =  *Expression
            index                               =  *Expression
            left_expression                     =  *Expression
            right_expression                    =  *Expression
            non_date_expression                 =  *Expression
            num_expression                      =  *Expression
            radicand                            =  *Expression
            sqrt_radicand                       =  *Expression
            frag_expression                     =  *Condition
            first                               =  *Field_Qualifier
            last                                =  *Field_Qualifier
            SQL_Statements                      =  *SQL_Statement $';' | *SQL_Statements *SQL_Statement $';'
            SQL_Statement                       =  *ALLOCATE_DESCRIPTOR
+                                               |  *ALTER_FRAGMENT
+                                               |  *ALTER_INDEX
+                                               |  *ALTER_OPTICAL_CLUSTER
+                                               |  *ALTER_TABLE
+                                               |  *BEGIN_WORK
+                                               |  *CHECK_TABLE
+                                               |  *CLOSE
+                                               |  *CLOSE_DATABASE
+                                               |  *COMMIT_WORK
+                                               |  *CONNECT
+                                               |  *CREATE_AUDIT
+                                               |  *CREATE_DATABASE
+                                               |  *CREATE_INDEX
+                                               |  *CREATE_PROCEDURE
+                                               |  *CREATE_ROLE
+                                               |  *CREATE_SCHEMA
+                                               |  *CREATE_SYNONYM
+                                               |  *CREATE_TABLE
+                                               |  *CREATE_TRIGGER
+                                               |  *CREATE_VIEW
+                                               |  *DATABASE
+                                               |  *DEALLOCATE_DESCRIPTOR
+                                               |  *DECLARE
+                                               |  *DELETE
+                                               |  *DESCRIBE
+                                               |  *DISCONNECT
+                                               |  *DROP_AUDIT
+                                               |  *DROP_DATABASE
+                                               |  *DROP_INDEX
+                                               |  *DROP_OPTICAL_CLUSTER
+                                               |  *DROP_PROCEDURE
+                                               |  *DROP_ROLE
+                                               |  *DROP_SYNONYM
+                                               |  *DROP_TABLE
+                                               |  *DROP_TRIGGER
+                                               |  *DROP_VIEW
+                                               |  *EXECUTE
+                                               |  *EXECUTE_IMMEDIATE
+                                               |  *EXECUTE_PROCEDURE
+                                               |  *FETCH
+                                               |  *FLUSH
+                                               |  *FREE
+                                               |  *GET_DESCRIPTOR
+                                               |  *GET_DIAGNOSTICS
+                                               |  *GRANT
+                                               |  *GRANT_FRAGMENT
+                                               |  *INFO
+                                               |  *INSERT
+                                               |  *LOAD
+                                               |  *LOCK_TABLE
+                                               |  *OPEN
+                                               |  *OUTPUT
+                                               |  *PREPARE
+                                               |  *PUT
+                                               |  *RECOVER_TABLE
+                                               |  *RELEASE
+                                               |  *RENAME_COLUMN
+                                               |  *RENAME_DATABASE
+                                               |  *RENAME_TABLE
+                                               |  *REPAIR_TABLE
+                                               |  *RESERVE
+                                               |  *REVOKE
+                                               |  *REVOKE_FRAGMENT
+                                               |  *ROLLBACK_WORK
+                                               |  *ROLLFORWARD_DATABASE
+                                               |  *SELECT
+                                               |  *SET
+                                               |  *SET_CONNECTION
+                                               |  *SET_DATASKIP
+                                               |  *SET_DEBUG_FILE_TO
+                                               |  *SET_DESCRIPTOR
+                                               |  *SET_EXPLAIN
+                                               |  *SET_ISOLATION
+                                               |  *SET_LOCK_MODE_TO
+                                               |  *SET_LOG
+                                               |  *SET_MOUNTING_TIMEOUT
+                                               |  *SET_OPTIMIZATION
+                                               |  *SET_PDQPRIORITY
+                                               |  *SET_ROLE
+                                               |  *SET_SESSION_AUTHORIZATION
+                                               |  *SET_TRANSACTION
+                                               |  *START_DATABASE
+                                               |  *START_VIOLATIONS_TABLE
+                                               |  *STOP_VIOLATIONS_TABLE
+                                               |  *UNLOAD
+                                               |  *UNLOCK_TABLE
+                                               |  *UPDATE
+                                               |  *UPDATE_STATISTICS
+                                               |  *WHENEVER
            ALLOCATE_DESCRIPTOR                 =  ALLOCATE DESCRIPTOR *descriptor_variable !(WITH MAX *occurrences)
            ALTER_FRAGMENT                      =  ALTER
+                                                  FRAGMENT
+                                                  ON
+                                                  TABLE
+                                                  *db_owner_name
+                                                  (  *ATTACH_Clause
+                                                  |  *DETACH_Clause
+                                                  |  *INIT_Clause
+                                                  |  *ADD_DBSpace_Clause
+                                                  |  *DROP_DBSpace_Clause
+                                                  |  *MODIFY_DBSpace_Clause
+                                                  )
+                                               |  ALTER
+                                                  FRAGMENT
+                                                  ON
+                                                  INDEX
+                                                  *db_owner_name
+                                                  (  *INIT_Clause
+                                                  |  *ADD_DBSpace_Clause
+                                                  |  *DROP_DBSpace_Clause
+                                                  |  *MODIFY_DBSpace_Clause
+                                                  )
            ATTACH_Clause                       =  ATTACH *db_owner_name_as_clause_list
            db_owner_name_as_clause             =  *db_owner_name
+                                                  !(AS *frag_expression !((BEFORE | AFTER) *dbspace) !(AS REMAINDER))
            db_owner_name_as_clause_list        =  *db_owner_name_as_clause
+                                               |  *db_owner_name_as_clause_list $',' *db_owner_name_as_clause
            DETACH_Clause                       =  DETACH *dbspace *db_owner_name
            INIT_Clause                         =  INIT !(WITH ROWIDS) (*FRAGMENT_BY_Clause_for_Tables | IN *dbspace)
            FRAGMENT_BY_Clause_for_Tables       =  FRAGMENT
+                                                  BY
+                                                  (  ROUND ROBIN IN *dbspace_list
+                                                  |  EXPRESSION
+                                                     *frag_expression_in_clause_list
+                                                     !($',' REMAINDER IN *dbspace)
+                                                  )
            frag_expression_in_clause           =  *frag_expression IN *dbspace
            ADD_DBSpace_Clause                  =  ADD
+                                                  (  *dbspace
+                                                  |  *frag_expression_in_clause !((BEFORE | AFTER) *dbspace)
+                                                  |  REMAINDER IN *dbspace
+                                                  )
            DROP_DBSpace_Clause                 =  DROP *dbspace
            MODIFY_DBSpace_Clause               =  MODIFY *modify_dbspace_in_clause_list
            modify_dbspace_in_clause            =  *dbspace TO (*frag_expression_in_clause | REMAINDER IN *dbspace)
            ALTER_INDEX                         =  ALTER INDEX *db_owner_name TO !NOT CLUSTER
            ALTER_TABLE                         =  ALTER TABLE *db_owner_name *collection_of_clauses_list
            collection_of_clauses               =  *ADD_Clause
+                                               |  *DROP_Clause
+                                               |  *MODIFY_Clause
+                                               |  *ADD_CONSTRAINT_Clause
+                                               |  *DROP_CONSTRAINT_Clause
+                                               |  *MODIFY_NEXT_SIZE_Clause
+                                               |  *LOCK_MODE_Clause
+                                               |  (ADD ROWIDS | DROP ROWIDS)
            ADD_Clause                          =  ADD (*Add_Column_Clause | $'(' *add_column_clause_list $')')
            Add_Column_Clause                   =  *db_owner_object_column
+                                                  *Data_Type
+                                                  !*DEFAULT_Clause
+                                                  !*New_Column_Constraint_Definition
+                                                  !(BEFORE *db_owner_object_column)
            DEFAULT_Clause                      =  DEFAULT *Expression
            New_Column_Constraint_Definition    =  !(NOT NULL  *Constraint_Mode_Definitions)
+                                                  *new_column_constraint_definition_clause
+                                                  !(*Constraint_Mode_Definitions)
            new_column_constraint_definition_clause = UNIQUE | DISTINCT | PRIMARY KEY | *REFERENCES_Clause | *CHECK_Clause
            Constraint_Mode_Definitions         =  CONSTRAINT *db_owner_name
+                                               |  CONSTRAINT *db_owner_name DISABLED
+                                               |  CONSTRAINT *db_owner_name ENABLED
+                                               |  CONSTRAINT *db_owner_name FILTERING
+                                               |  CONSTRAINT *db_owner_name FILTERING WITHOUT ERROR
+                                               |  CONSTRAINT *db_owner_name FILTERING WITH ERROR
+                                               |  DISABLED
+                                               |  ENABLED
+                                               |  FILTERING
+                                               |  FILTERING WITHOUT ERROR
+                                               |  FILTERING WITH ERROR
            REFERENCES_Clause                   =  REFERENCES
+                                                  *db_owner_name
+                                                  !($'(' *column_name_list $')')
+                                                  !(ON DELETE CASCADE)
            CHECK_Clause                        =  CHECK $'(' *Condition $')'
            DROP_Clause                         =  DROP (*db_owner_object_column | $'(' *column_name_list $')')
            MODIFY_Clause                       =  MODIFY
+                                                  (*Modify_Column_Clause | $'(' *modify_column_clause_list $')')
            Modify_Column_Clause                =  *db_owner_object_column
+                                                  *Data_Type
+                                                  !*DEFAULT_Clause
+                                                  !*new_column_constraint_definition_list
            ADD_CONSTRAINT_Clause               =  ADD
+                                                  CONSTRAINT
+                                                  (  *Table_Level_Constraint_Definition
+                                                  |  $'(' *table_level_constraint_definition_list $')'
+                                                  )
            Table_Level_Constraint_Definition   =  (  (UNIQUE | DISTINCT | PRIMARY KEY) $'(' *column_name_list $')'
+                                                  |  FOREIGN KEY $'(' *column_name_list $')' *REFERENCES_Clause
+                                                  |  *CHECK_Clause
+                                                  )
+                                                  !(*Constraint_Mode_Definitions)
            DROP_CONSTRAINT_Clause              =  DROP CONSTRAINT (*db_owner_name | $'(' *db_owner_name_list $')')
            MODIFY_NEXT_SIZE_Clause             =  MODIFY NEXT SIZE *kbytes | NEXT SIZE *kbytes
            LOCK_MODE_Clause                    =  LOCK MODE $'(' (PAGE | ROW) $')'
            BEGIN_WORK                          =  BEGIN WORK
            CHECK_TABLE                         =  CHECK TABLE *db_owner_name
            CLOSE                               =  CLOSE *cursor_id
            CLOSE_DATABASE                      =  CLOSE DATABASE
            COMMIT_WORK                         =  COMMIT WORK
            CONNECT                             =  CONNECT
+                                                  TO
+                                                  *Database_Environment
+                                                  !(AS *conn_nm_variable)
+                                                  !(*USER_Clause)
+                                                  !(WITH CONCURRENT TRANSACTION)
            Database_Environment                =  *sq_string | *ident
            USER_Clause                         =  USER
+                                                  (*user_id_variable | *sq_string)
+                                                  USING
+                                                  (*auth_variable | *sq_string)
            CREATE_AUDIT                        =  CREATE AUDIT FOR *db_owner_name IN *sq_string
            CREATE_DATABASE                     =  CREATE DATABASE *Database_Name !(IN *dbspace) !(*OL_Log_Clause)
            OL_Log_Clause                       =  WITH !BUFFERED LOG !(IN *ident) !(MODE ANSI)
            CREATE_INDEX                        =  CREATE
+                                                  !(UNIQUE | DISTINCT)
+                                                  !CLUSTER
+                                                  INDEX
+                                                  *Index_Definition
+                                                  !(FILLFACTOR *percent)
+                                                  !(IN *dbspace | *FRAGMENT_BY_EXPRESSION_Clause)
+                                                  !*Object_Modes_for_Unique_Indexes
            Index_Definition                    =  *db_owner_name ON *db_owner_name $'(' *column_name_order_list $')'
            column_name_order                   =  *db_owner_object_column !(ASC | DESC)
            FRAGMENT_BY_EXPRESSION_Clause       =  FRAGMENT
+                                                  BY
+                                                  EXPRESSION
+                                                  *frag_expression_in_clause_list
+                                                  !($',' REMAINDER IN *dbspace)
            Object_Modes_for_Unique_Indexes     =  DISABLED | ENABLED | FILTERING !(WITHOUT ERROR | WITH ERROR)
            CREATE_PROCEDURE                    =  CREATE
+                                                  !DBA
+                                                  PROCEDURE
+                                                  !FROM
+                                                  *db_owner_name
+                                                  !( $'('
+                                                     !*parameter_list
+                                                     $')'
+                                                     !*RETURNING_Clause
+                                                     *Statement_Block
+                                                     END
+                                                     PROCEDURE
+                                                     !(DOCUMENT *quoted_string_list)
+                                                     !(WITH LISTING IN *sq_string)
+                                                  )
            parameter                           =  *variable_name
+                                                  (  (*SQL_Data_Type_Subset | LIKE *db_owner_object_column)
+                                                     !(DEFAULT *Default_Value)
+                                                  |  *references_type_default_null
+                                                  )
            RETURNING_Clause                    =  RETURNING *returning_sub_clause_list $';'
            returning_sub_clause                =  *SQL_Data_Type_Subset | *references_type_default_null
            Statement_Block                     =  !*define_list !*on_exception_list !*statement_block_clause_list
            statement_block_clause              =  *CALL
+                                               |  *CONTINUE
+                                               |  *EXIT
+                                               |  *FOR
+                                               |  *FOREACH
+                                               |  *IF
+                                               |  *LET
+                                               |  *RAISE_EXCEPTION
+                                               |  *RETURN
+                                               |  *SYSTEM
+                                               |  *TRACE
+                                               |  *WHILE
+                                               |  *SQL_Statement $';'
+                                               |  BEGIN *Statement_Block END
            CREATE_ROLE                         =  CREATE ROLE *role_name
            role_name                           =  *ident | *sq_string
            CREATE_SCHEMA                       =  CREATE
+                                                  SCHEMA
+                                                  AUTHORIZATION
+                                                  *user_name
+                                                  !*create_schema_sub_clause_list
            user_name                           =  *ident | *sq_string
            create_schema_sub_clause            =  *CREATE_TABLE
+                                               |  *CREATE_INDEX
+                                               |  *CREATE_VIEW
+                                               |  *CREATE_SYNONYM
+                                               |  *GRANT
+                                               |  *GRANT_FRAGMENT
+                                               |  *CREATE_TRIGGER
+                                               |  *CREATE_OPTICAL_CLUSTER
            CREATE_SYNONYM                      =  CREATE !(PUBLIC | PRIVATE) SYNONYM *db_owner_name FOR *db_owner_name
            CREATE_TABLE                        =  CREATE
+                                                  (  TABLE
+                                                     *db_owner_name
+                                                     $'('
+                                                     *column_or_table_constraint_definition_list
+                                                     $')'
+                                                     !(WITH ROWIDS)
+                                                  |  TEMP
+                                                     TABLE
+                                                     *db_owner_name
+                                                     $'('
+                                                     *temp_table_column_definition_list
+                                                     !($',' *temp_table_table_level_constraint_list)
+                                                     $')'
+                                                     !(WITH NO LOG | WITH ROWIDS | WITH NO LOG  WITH ROWIDS)
+                                                  |  TEMPORARY
+                                                     TABLE
+                                                     *db_owner_name
+                                                     $'('
+                                                     *temp_table_column_definition_list
+                                                     !($',' *temp_table_table_level_constraint_list)
+                                                     $')'
+                                                     !(WITH NO LOG | WITH ROWIDS | WITH NO LOG  WITH ROWIDS)
+                                                  )
+                                                  *Storage_Option
            column_or_table_constraint_definition = *Column_Definition | *Table_Level_Constraint_Definition
            column_or_table_constraint_definition_list = *column_or_table_constraint_definition
+                                               |  *column_or_table_constraint_definition_list
+                                                  $','
+                                                  *column_or_table_constraint_definition
            Column_Definition                   =  *db_owner_object_column
+                                                  *Data_Type
+                                                  !*DEFAULT_Clause
+                                                  !*Column_Level_Constraint_Definition
            Column_Level_Constraint_Definition  =  *column_not_null_constraint
+                                               |  *column_not_null_constraint *column_constraint_definition_list
+                                               |  *column_constraint_definition_list
            column_not_null_constraint          =  NOT NULL !(*Constraint_Mode_Definitions)
            column_constraint_definition        =  (  UNIQUE
+                                                  |  DISTINCT
+                                                  |  PRIMARY KEY
+                                                  |  *REFERENCES_Clause
+                                                  |  *CHECK_Clause
+                                                  )
+                                                  !(*Constraint_Mode_Definitions)
            column_constraint_definition_list   =  *column_constraint_definition
+                                               |  *column_constraint_definition_list *column_constraint_definition
            Temporary_Table_Column_Definition   =  *db_owner_object_column
+                                                  *Data_Type
+                                                  !*DEFAULT_Clause
+                                                  !(NOT NULL)
+                                                  !*Temp_Table_Column_Constraint_Definition
            Temp_Table_Column_Constraint_Definition = UNIQUE | DISTINCT | PRIMARY KEY | *CHECK_Clause
            Temp_Table_Table_Level_Constraint   =  (UNIQUE | DISTINCT | PRIMARY KEY) $'(' *column_name_list $')'
+                                               |  *CHECK_Clause
            Storage_Option                      =  !(IN *dbspace | *FRAGMENT_BY_Clause)
+                                                  *Extent_Option
+                                                  !*LOCK_MODE_Create_Clause
+                                               |  IN *sq_string
            FRAGMENT_BY_Clause                  =  FRAGMENT
+                                                  BY
+                                                  (  ROUND ROBIN IN *dbspace_list
+                                                  |  EXPRESSION
+                                                     *frag_expression_in_clause_list
+                                                     !($',' REMAINDER IN *dbspace)
+                                                  )
            Extent_Option                       =  !(EXTENT SIZE *first_kbytes) !(NEXT SIZE *next_kbytes)
            LOCK_MODE_Create_Clause             =  LOCK MODE (PAGE | ROW)
            CREATE_TRIGGER                      =  CREATE
+                                                  TRIGGER
+                                                  *owner_name
+                                                  (  INSERT
+                                                     ON
+                                                     *db_owner_name
+                                                     (  *Action_Clause
+                                                     |  *Insert_REFERENCING_Clause *Action_Clause_Referencing
+                                                     )
+                                                  |  DELETE
+                                                     ON
+                                                     *db_owner_name
+                                                     (  *Action_Clause
+                                                     |  *Delete_REFERENCING_Clause *Action_Clause_Referencing
+                                                     )
+                                                  |  *UPDATE_Clause
+                                                     ON
+                                                     *db_owner_name
+                                                     (  *Action_Clause
+                                                     |  *Update_REFERENCING_Clause *Action_Clause_Referencing
+                                                     )
+                                                  )
+                                                  *Trigger_Object_Modes
            UPDATE_Clause                       =  UPDATE !(OF *column_name_list)
            Action_Clause                       =  BEFORE
+                                                  *Triggered_Action_List
+                                                  !(FOR EACH ROW *Triggered_Action_List)
+                                                  !(AFTER *Triggered_Action_List)
+                                               |  FOR EACH ROW *Triggered_Action_List !(AFTER *Triggered_Action_List)
+                                               |  AFTER *Triggered_Action_List
            Insert_REFERENCING_Clause           =  REFERENCING NEW !AS *correlation_name
            Delete_REFERENCING_Clause           =  REFERENCING OLD !AS *correlation_name
            Update_REFERENCING_Clause           =  REFERENCING *update_referencing_sub_clause_list
            update_referencing_sub_clause       =  OLD !AS *correlation_name | NEW !AS *correlation_name
            Action_Clause_Referencing           =  !(BEFORE *Triggered_Action_List)
+                                                  FOR
+                                                  EACH
+                                                  ROW
+                                                  *Triggered_Action_List
+                                                  !(AFTER *Triggered_Action_List)
            Triggered_Action_List               =  *triggered_action | *Triggered_Action_List $',' *triggered_action
            triggered_action                    =  !(WHEN $'(' *Condition $')')
+                                                  $'('
+                                                  *triggered_action_sub_clause_list
+                                                  $')'
            triggered_action_sub_clause         =  *INSERT | *DELETE | *UPDATE | *EXECUTE_PROCEDURE | *host_variable
            triggered_action_sub_clause_list    =  *triggered_action_sub_clause
+                                               |  *triggered_action_sub_clause_list $',' *triggered_action_sub_clause
            Trigger_Object_Modes                =  !(DISABLED | ENABLED)
            CREATE_VIEW                         =  CREATE VIEW *db_owner_name AS *SELECT
+                                               |  CREATE VIEW *db_owner_name $'(' *column_name_list $')' AS *SELECT
            DATABASE                            =  DATABASE *Database_Name !EXCLUSIVE
            DEALLOCATE_DESCRIPTOR               =  DEALLOCATE DESCRIPTOR *descriptor_variable
            DECLARE                             =  DECLARE
+                                                  *cursor_id
+                                                  !SCROLL CURSOR !(WITH HOLD) FOR (*INSERT | *SELECT | *statement_id)
            DELETE                              =  DELETE
+                                                  FROM
+                                                  *db_owner_name
+                                                  !(WHERE (*Condition | CURRENT OF *cursor_name))
            DESCRIBE                            =  DESCRIBE
+                                                  *statement_id
+                                                  (USING SQL DESCRIPTOR *descriptor_variable | INTO *sqlda_pointer)
            DISCONNECT                          =  DISCONNECT !(CURRENT | ALL | *conn_nm_variable)
            DROP_AUDIT                          =  DROP AUDIT FOR *db_owner_name
            DROP_DATABASE                       =  DROP DATABASE *Database_Name
            DROP_INDEX                          =  DROP INDEX *db_owner_name
            DROP_PROCEDURE                      =  DROP PROCEDURE *db_owner_name
            DROP_ROLE                           =  DROP ROLE *role_name
            DROP_SYNONYM                        =  DROP SYNONYM *db_owner_name
            DROP_TABLE                          =  DROP TABLE *db_owner_name !(CASCADE | RESTRICT)
            DROP_TRIGGER                        =  DROP TRIGGER *owner_name
            DROP_VIEW                           =  DROP VIEW *db_owner_name !(CASCADE | RESTRICT)
            EXECUTE                             =  EXECUTE *statement_id !*USING_Clause !*EXECUTE_INTO_Clause
            USING_Clause                        =  USING
+                                                  (  *using_variable_list
+                                                  |  SQL DESCRIPTOR *storage_descriptor_variable
+                                                  |  DESCRIPTOR *storage_sqlda_pointer
+                                                  )
            variable_clause                     =  *storage_variable_name
+                                                  !( $':' *storage_indicator_variable
+                                                  |  INDICATOR *storage_indicator_variable
+                                                  )
            using_variable_list                 =  *variable_clause | *using_variable_list $',' *variable_clause
            EXECUTE_INTO_Clause                 =  INTO
+                                                  (  *execute_into_variable_list
+                                                  |  SQL DESCRIPTOR *storage_descriptor_variable
+                                                  |  DESCRIPTOR *storage_sqlda_pointer
+                                                  )
            execute_into_variable_list          =  *variable_clause | *execute_into_variable_list $',' *variable_clause
            EXECUTE_IMMEDIATE                   =  EXECUTE IMMEDIATE *statement_variable_name
            EXECUTE_PROCEDURE                   =  EXECUTE
+                                                  PROCEDURE
+                                                  *db_owner_name
+                                                  $'('
+                                                  !*argument_list
+                                                  $')'
+                                                  !(INTO *db_owner_object_column)
            Argument                            =  *Expression | *SELECT | *parameter_name $'=' (*Expression | *SELECT)
            FETCH                               =  FETCH
+                                                  !( NEXT
+                                                  |  PREVIOUS
+                                                  |  PRIOR
+                                                  |  FIRST
+                                                  |  LAST
+                                                  |  CURRENT
+                                                  |  RELATIVE !($'+' | $'-') *row_position
+                                                  |  ABSOLUTE *row_position
+                                                  )
+                                                  *cursor_id
+                                                  !( INTO *fetch_into_list
+                                                  |  USING !SQL DESCRIPTOR *descriptor_variable
+                                                  )
            fetch_into_clause                   =  *data_variable !(INDICATOR *indicator_variable)
            fetch_into_list                     =  *fetch_into_clause | *fetch_into_list $',' *fetch_into_clause
            FLUSH                               =  FLUSH *cursor_id
            FREE                                =  FREE *ident
            GET_DESCRIPTOR                      =  GET
+                                                  DESCRIPTOR
+                                                  *descriptor_variable
+                                                  (  *host_variable $'=' COUNT
+                                                  |  VALUE *item_number *described_item_info_list
+                                                  )
            Described_Item_Info                 =  *field_host_variable
+                                                  $'='
+                                                  (  TYPE
+                                                  |  LENGTH
+                                                  |  PRECISION
+                                                  |  SCALE
+                                                  |  NULLABLE
+                                                  |  INDICATOR
+                                                  |  NAME
+                                                  |  DATA
+                                                  |  ITYPE
+                                                  |  IDATA
+                                                  |  ILENGTH
+                                                  )
            GET_DIAGNOSTICS                     =  GET DIAGNOSTICS (*statement_clause_list | *EXCEPTION_Clause)
            Statement_Clause                    =  *st_var $'=' (MORE | NUMBER | ROW_COUNT)
            EXCEPTION_Clause                    =  EXCEPTION (*except_num | *en_var) *exception_sub_clause_list
            exception_sub_clause                =  *ex_var
+                                                  $'='
+                                                  (  CLASS_ORIGIN
+                                                  |  CONNECTION_ALIAS
+                                                  |  MESSAGE_LENGTH
+                                                  |  MESSAGE_TEXT
+                                                  |  RETURNED_SQLSTATE
+                                                  |  SERVER_NAME
+                                                  |  SUBCLASS_ORIGIN
+                                                  )
            user_name_clause                    =  *user_name | USER
            user_or_role_name_clause            =  *user_or_role_name | USER
            GRANT                               =  GRANT
+                                                  (  *Database_Level_Privileges TO *user_name_clause_list
+                                                  |  *role_name
+                                                     TO
+                                                     *user_or_role_name_clause_list
+                                                     !(WITH GRANT OPTION)
+                                                  |  (  *Table_Level_Privileges_Grant ON *db_owner_name
+                                                     |  EXECUTE ON *db_owner_name
+                                                     )
+                                                     TO
+                                                     *user_or_role_name_clause_list
+                                                     !(WITH GRANT OPTION)
+                                                     !(AS *grantor)
+                                                  )
            grantor                             =  *ident | *sq_string
            Database_Level_Privileges           =  RESOURCE | CONNECT | DBA
            Table_Level_Privileges_Grant        =  ALL !PRIVILEGES | *table_level_privileges_grant_clause_list
            table_level_privileges_grant_clause =  INSERT
+                                               |  DELETE
+                                               |  SELECT !($'(' *column_name_list $')')
+                                               |  UPDATE !($'(' *column_name_list $')')
+                                               |  REFERENCES !($'(' *column_name_list $')')
+                                               |  INDEX
+                                               |  ALTER
            GRANT_FRAGMENT                      =  GRANT
+                                                  FRAGMENT
+                                                  *Fragment_Level_Privileges
+                                                  ON
+                                                  *db_owner_name
+                                                  $'('
+                                                  *dbspace_list
+                                                  $')'
+                                                  TO
+                                                  *user_name_clause_list
+                                                  !(WITH GRANT OPTION)
+                                                  !(AS *grantor)
            Fragment_Level_Privileges           =  ALL | *fragment_privilege_clause_list
            fragment_privilege_clause           =  INSERT | DELETE | UPDATE
            INFO                                =  INFO
+                                                  (  TABLES
+                                                  |  (  COLUMNS
+                                                     |  INDEXES
+                                                     |  ACCESS
+                                                     |  PRIVILEGES
+                                                     |  REFERENCES
+                                                     |  STATUS
+                                                     |  FRAGMENTS
+                                                     )
+                                                     FOR
+                                                     *db_owner_name
+                                                  )
            INSERT                              =  INSERT
+                                                  INTO
+                                                  *db_owner_name
+                                                  !($'(' *column_name_list $')')
+                                                  (*VALUES_Clause | *SELECT | *EXECUTE_PROCEDURE)
            VALUES_Clause                       =  VALUES $'(' *values_sub_clause_list $')'
            values_sub_clause                   =  *variable_name_colon_or_dollar | *Expression
            variable_name_colon_or_dollar       =  *variable_name $':' *indicator_variable
+                                               |  *variable_name $'$' *indicator_variable
+                                               |  INDICATOR *indicator_variable
            LOAD                                =  LOAD
+                                                  FROM
+                                                  (*sq_string | *ident)
+                                                  !(DELIMITER *sq_string)
+                                                  INSERT
+                                                  INTO
+                                                  *db_owner_name
+                                                  !($'(' *column_name_list $')')
            LOCK_TABLE                          =  LOCK TABLE *db_owner_name IN (SHARE | EXCLUSIVE) MODE
            OPEN                                =  OPEN
+                                                  *cursor_id
+                                                  !( USING
+                                                     (  *variable_name_list
+                                                     |  SQL DESCRIPTOR *descriptor_variable
+                                                     |  DESCRIPTOR *sqlda_pointer
+                                                     )
+                                                  )
+                                                  !(WITH REOPTIMIZATION)
            OUTPUT                              =  OUTPUT TO (*filename | PIPE *program) !(WITHOUT HEADINGS) *SELECT
            PREPARE                             =  PREPARE *statement_id FROM *statement_id
            PUT                                 =  PUT
+                                                  *cursor_id
+                                                  !( FROM *variable_name_colon_or_dollar
+                                                  |  USING
+                                                     (SQL DESCRIPTOR *descriptor_variable | DESCRIPTOR *sqlda_pointer)
+                                                  )
            RECOVER_TABLE                       =  RECOVER TABLE *db_owner_name
            RENAME_COLUMN                       =  RENAME COLUMN *db_owner_object_column TO *db_owner_object_column
            RENAME_DATABASE                     =  RENAME DATABASE *Database_Name TO *Database_Name
            RENAME_TABLE                        =  RENAME TABLE *db_owner_name TO *db_owner_name
            REPAIR_TABLE                        =  REPAIR TABLE *db_owner_name
            REVOKE                              =  REVOKE
+                                                  (  *Table_Level_Privileges_Revoke ON *db_owner_name
+                                                  |  EXECUTE ON *db_owner_name
+                                                  |  *role_name
+                                                  |  *Database_Level_Privileges
+                                                  )
+                                                  FROM
+                                                  *user_name_clause_list
+                                                  !(CASCADE | RESTRICT)
            Table_Level_Privileges_Revoke       =  ALL !PRIVILEGES | *revoke_table_level_privileges_clause_list
            revoke_table_level_privileges_clause = INSERT | DELETE | SELECT | UPDATE | INDEX | ALTER | REFERENCES
            REVOKE_FRAGMENT                     =  REVOKE
+                                                  FRAGMENT
+                                                  *Fragment_Level_Privileges
+                                                  ON
+                                                  *db_owner_name
+                                                  !($'(' *dbspace_list $')')
+                                                  FROM
+                                                  *user_name_clause_list
            ROLLBACK_WORK                       =  ROLLBACK !WORK
            ROLLFORWARD_DATABASE                =  ROLLFORWARD DATABASE *Database_Name
            SELECT                              =  SELECT
+                                                  *Select_Clause
+                                                  !(*INTO_CLAUSE)
+                                                  FROM
+                                                  *additional_tables_list
+                                                  !*WHERE_Clause
+                                                  !*HAVING_Clause
+                                                  !*GROUP_BY_Clause
+                                                  !*ORDER__BY__Clause
+                                                  !(FOR READ ONLY | FOR UPDATE OF *column_name_list)
+                                                  !(*INTO_TEMP_Clause)
+                                                  !(UNION !ALL *SELECT)
            Select_Clause                       =  !(ALL | DISTINCT | UNIQUE) *select_list_list
            Select_List                         =  *Expression !(!AS *display_label) | *db_owner_name_dot_all
            select_list_list                    =  *Select_List | *select_list_list $',' *Select_List
            INTO_CLAUSE                         =  INTO *into_sub_clause_list
            into_sub_clause                     =  *data_variable
+                                                  !( ($':' *indicator_variable | $'$' *indicator_variable)
+                                                  |  INDICATOR *indicator_variable
+                                                  )
            additional_tables_list              =  *Additional_Tables | *additional_tables_list $',' *Additional_Tables
            Additional_Tables                   =  !(OUTER) *db_owner_name !(!AS *alias)
+                                               |  OUTER
+                                                  $'('
+                                                  *db_owner_name
+                                                  !(!AS *alias)
+                                                  !($',' *additional_tables_list)
+                                                  $')'
            WHERE_Clause                        =  WHERE *Condition
            GROUP_BY_Clause                     =  GROUP BY !*group_by_sub_clause_list
            group_by_sub_clause                 =  *select_number | *db_owner_object_column
            HAVING_Clause                       =  HAVING *Condition
            ORDER__BY__Clause                   =  ORDER BY *order_by_sub_clause_list
            order_by_sub_clause                 =  (  *select_number
+                                                  |  ROWID
+                                                  |  *db_owner_object_column !(*first $',' *last)
+                                                  )
+                                                  !(ASC | DESC)
            INTO_TEMP_Clause                    =  WITH CHECK OPTION
+                                               |  INTO TEMP *db_owner_name
+                                               |  INTO TEMP *db_owner_name WITH CHECK OPTION
+                                               |  INTO TEMP *db_owner_name WITH NO LOG
+                                               |  INTO TEMP *db_owner_name WITH NO LOG WITH CHECK OPTION
            SET                                 =  SET
+                                                  (*Table_Mode_Format | *List_Mode_Format | *Transaction_Mode_Format)
            Table_Mode_Format                   =  *contraints_or_indexes_or_triggers_list
+                                                  FOR
+                                                  *db_owner_name
+                                                  *Object_Modes_for_Constraints_and_Unique_Indexes
            contraints_or_indexes_or_triggers   =  CONSTRAINTS | INDEXES | TRIGGERS
            Object_Modes_for_Constraints_and_Unique_Indexes = DISABLED
+                                               |  ENABLED
+                                               |  FILTERING
+                                               |  FILTERING WITHOUT ERROR
+                                               |  FILTERING WITH ERROR
            List_Mode_Format                    =  CONSTRAINTS
+                                                  *db_owner_name_list
+                                                  *Object_Modes_for_Constraints_and_Unique_Indexes
+                                               |  INDEXES
+                                                  *db_owner_name_list
+                                                  *Object_Modes_for_Constraints_and_Unique_Indexes
+                                               |  TRIGGERS
+                                                  *owner_name_list
+                                                  *Object_Modes_for_Constraints_and_Unique_Indexes
            Transaction_Mode_Format             =  CONSTRAINTS (ALL | *db_owner_name_list) (IMMEDIATE | DEFERRED)
            SET_CONNECTION                      =  SET CONNECTION *Database_Environment
            SET_DATASKIP                        =  SET DATASKIP (DEFAULT | OFF | ON !*dbspace_list)
            SET_DEBUG_FILE_TO                   =  SET DEBUG FILE TO *character_expression !(WITH APPEND)
            SET_DESCRIPTOR                      =  SET
+                                                  DESCRIPTOR
+                                                  *descriptor_variable
+                                                  (  COUNT $'=' (*value | *count_variable)
+                                                  |  VALUE
+                                                     (*item_number | *item_number_variable)
+                                                     *item_descriptor_information_list
+                                                  )
            Item__Descriptor__Information       =  (  TYPE
+                                                  |  LENGTH
+                                                  |  PRECISION
+                                                  |  SCALE
+                                                  |  NULLABLE
+                                                  |  INDICATOR
+                                                  |  ITYPE
+                                                  |  ILENGTH
+                                                  )
+                                                  $'='
+                                                  (*literal_integer | *integer_host_variable)
+                                               |  (DATA | IDATA)
+                                                  $'='
+                                                  (*number | *Literal_DATETIME | *Literal_INTERVAL | *data_variable)
+                                               |  NAME *data_variable
            SET_EXPLAIN                         =  SET EXPLAIN (ON | OFF)
            SET_ISOLATION                       =  SET
+                                                  ISOLATION
+                                                  TO
+                                                  (DIRTY READ | COMMITTED READ | CURSOR STABILITY | REPEATABLE READ)
            SET_LOCK_MODE_TO                    =  SET LOCK MODE TO (WAIT !(*seconds) | NOT WAIT)
            SET_LOG                             =  SET !BUFFERED LOG
            SET_OPTIMIZATION                    =  SET OPTIMIZATION (HIGH | LOW)
            SET_PDQPRIORITY                     =  SET PDQPRIORITY (DEFAULT | LOW | OFF | HIGH | *percent_of_resources)
            SET_ROLE                            =  SET ROLE (*role_name | NULL | NONE)
            SET_SESSION_AUTHORIZATION           =  SET SESSION AUTHORIZATION TO USER
            SET_TRANSACTION                     =  SET TRANSACTION *set_transaction_clause_list
            set_transaction_clause              =  (READ WRITE | READ ONLY)
+                                               |  ISOLATION
+                                                  LEVEL
+                                                  (READ COMMITTED | READ UNCOMMITTED | REPEATABLE READ | SERIALIZABLE)
            set_transaction_clause_list         =  *set_transaction_clause
+                                               |  *set_transaction_clause_list $',' *set_transaction_clause
            START_DATABASE                      =  START
+                                                  DATABASE
+                                                  *Database_Name
+                                                  (WITH LOG IN *sq_string !(MODE ANSI) | WITH NO LOG)
            START_VIOLATIONS_TABLE              =  START
+                                                  VIOLATIONS
+                                                  TABLE
+                                                  FOR
+                                                  *db_owner_name
+                                                  !(USING *violations $',' *diagnostics)
+                                                  !(MAX ROWS *numrows)
            STOP_VIOLATIONS_TABLE               =  STOP VIOLATIONS TABLE FOR *db_owner_name
            UNLOAD                              =  UNLOAD TO (*sq_string | *ident) !(DELIMITER *sq_string) *SELECT
            UNLOCK_TABLE                        =  UNLOCK TABLE *db_owner_name
            UPDATE                              =  UPDATE
+                                                  *db_owner_name
+                                                  SET
+                                                  (*SET_Clause | *column_name_eq_expr_clause_list)
+                                                  !(*WHERE_Clause | WHERE CURRENT OF *cursor_id)
            SET_Clause                          =  !( ($'*' | $'(' *column_name_list $')')
+                                                     $'='
+                                                     $'('
+                                                     *Expression_list
+                                                     $')'
+                                                  )
            column_name_eq_expr_clause          =  *db_owner_object_column $'=' *Expression
            UPDATE_STATISTICS                   =  UPDATE
+                                                  STATISTICS
+                                                  !( FOR PROCEDURE !*db_owner_name
+                                                  |  *for_table_clause
+                                                  |  *for_table_clause *drop_distributions
+                                                  |  *drop_distributions
+                                                  |  LOW
+                                                  |  LOW *for_table_clause
+                                                  |  LOW *drop_distributions
+                                                  |  LOW *for_table_clause *drop_distributions
+                                                  |  MEDIUM *resolution_clause
+                                                  |  MEDIUM *for_table_clause *resolution_clause
+                                                  |  HIGH *resolution_clause_no_conf
+                                                  |  HIGH *for_table_clause *resolution_clause_no_conf
+                                                  )
            drop_distributions                  =  DROP DISTRIBUTIONS
            resolution_clause                   =  !(RESOLUTION *percent !*conf !(DISTRIBUTIONS ONLY))
            resolution_clause_no_conf           =  !(RESOLUTION *percent !(DISTRIBUTIONS ONLY))
            for_table_clause                    =  FOR TABLE !(*db_owner_name !($'(' *column_name_list $')'))
            WHENEVER                            =  WHENEVER
+                                                  (SQLERROR | NOT FOUND | SQLWARNING | ERROR)
+                                                  (  CONTINUE
+                                                  |  (GO TO | GOTO) *ident $':'
+                                                  |  STOP
+                                                  |  CALL *function_name
+                                                  |  PERFORM *paragraph_name
+                                                  )
            Condition                           =  *Condition_term | *Condition OR *Condition_term
            Condition_term                      =  *Condition_factor | *Condition_term AND *Condition_factor
            Condition_factor                    =  *Condition_element | NOT *Condition_factor
            Condition_element                   =  *Expression $'=' *opt_any_or_all *Expression
+                                               |  *Expression $'==' *opt_any_or_all *Expression
+                                               |  *Expression $'>' *opt_any_or_all *Expression
+                                               |  *Expression $'<' *opt_any_or_all *Expression
+                                               |  *Expression $'>=' *opt_any_or_all *Expression
+                                               |  *Expression $'<=' *opt_any_or_all *Expression
+                                               |  *Expression $'<>' *opt_any_or_all *Expression
+                                               |  *Expression $'!=' *opt_any_or_all *Expression
+                                               |  *Expression $'!>' *opt_any_or_all *Expression
+                                               |  *Expression $'!<' *opt_any_or_all *Expression
+                                               |  *Expression IN $'(' *Expression_list $')'
+                                               |  *Expression NOT IN $'(' *Expression_list $')'
+                                               |  *Expression IN $'(' *SELECT $')'
+                                               |  *Expression NOT IN $'(' *SELECT $')'
+                                               |  EXISTS *Expression
+                                               |  *Expression BETWEEN *Expression AND *Expression
+                                               |  *Expression NOT BETWEEN *Expression AND *Expression
+                                               |  *Expression LIKE *Expression
+                                               |  *Expression LIKE *Expression ESCAPE *Expression
+                                               |  *Expression NOT LIKE *Expression
+                                               |  *Expression NOT LIKE *Expression ESCAPE *Expression
+                                               |  *Expression IS NULL
+                                               |  *Expression IS NOT NULL
+                                               |  $'(' *Condition $')'
            opt_any_or_all                      =  !(ANY | ALL)
            Database_Name                       =  *ident
            Data_Type                           =  CHAR
+                                               |  CHARACTER
+                                               |  CHAR $'(' *size $')'
+                                               |  CHARACTER $'(' *size $')'
+                                               |  CHAR VARYING $'(' *max $',' *reserve $')'
+                                               |  CHAR VARYING $'(' *max $')'
+                                               |  CHARACTER VARYING $'(' *max $')'
+                                               |  CHARACTER VARYING $'(' *max $',' *reserve $')'
+                                               |  NCHAR !($'(' *size $')')
+                                               |  DATE
+                                               |  *datetime_with_qualifier
+                                               |  (DECIMAL | DEC | NUMERIC) !($'(' *precision !($',' *scale) $')')
+                                               |  FLOAT !($'(' *float_precision $')')
+                                               |  DOUBLE PRECISION
+                                               |  INTEGER | INT
+                                               |  INTERVAL *Field_Qualifier
+                                               |  MONEY !($'(' *precision !($',' *scale) $')')
+                                               |  SERIAL !($'(' *start $')')
+                                               |  SMALLFLOAT | REAL
+                                               |  SMALLINT
+                                               |  *INFORMIX_ODS_Specific_Data_Types
            INFORMIX_ODS_Specific_Data_Types    =  TEXT !(IN (TABLE | *blobspace))
+                                               |  BYTE !(IN (TABLE | *blobspace))
+                                               |  VARCHAR $'(' *max !($',' *reserve) $')'
+                                               |  NVARCHAR $'(' *max !($',' *reserve) $')'
            Expression                          =  *Expression_term
+                                               |  *Expression $'+' *Expression_term
+                                               |  *Expression $'-' *Expression_term
+                                               |  *Expression $'||' *Expression_term
            Expression_term                     =  *Expression_factor
+                                               |  *Expression_term $'*' *Expression_factor
+                                               |  *Expression_term $'/' *Expression_factor
            Expression_factor                   =  *Expression_element
+                                               |  $'+' *Expression_factor
+                                               |  $'-' *Expression_factor
            Expression_element                  =  *Column_Expressions
+                                               |  *Constant_Expressions
+                                               |  *Function_Expressions
+                                               |  *Aggregate_Expressions
+                                               |  *Procedure_Call_Expressions
+                                               |  $'(' *Expression $')'
+                                               |  $'(' *SELECT $')'
            Expression_list                     =  *Expression | *Expression_list $',' *Expression
            Column_Expressions                  =  *db_owner_object_column
+                                               |  *db_owner_object_column $'[' *number $',' *number $']'
+                                               |  ROWID
            Constant_Expressions                =  USER
+                                               |  NULL
+                                               |  (SITENAME | DBSERVERNAME)
+                                               |  *number
+                                               |  TODAY
+                                               |  *current_datetime
+                                               |  *Literal_DATETIME
+                                               |  *Literal_INTERVAL
+                                               |  *number UNITS *datetime_unit
+                                               |  *sq_string
            Function_Expressions                =  (  *Algebraic_Functions
+                                                  |  *DBINFO
+                                                  |  *Exponential_and_Logarithmic_Functions
+                                                  |  *HEX_Function
+                                                  |  *LENGTH_Function
+                                                  |  *Time_Functions
+                                                  |  *Trigonometric_Functions
+                                                  |  *TRIM_Function
+                                                  )
            HEX_Function                        =  HEX $'(' *integer_expression $')'
            Algebraic_Functions                 =  ABS $'(' *num_expression $')'
+                                               |  MOD $'(' *Expression_list $')'
+                                               |  POW $'(' *Expression_list $')'
+                                               |  ROOT $'(' *radicand !($',' *index) $')'
+                                               |  ROUND $'(' *Expression !($',' *rounding_factor) $')'
+                                               |  SQRT $'(' *sqrt_radicand $')'
+                                               |  TRUNC $'(' *Expression !($',' *truncating_factor) $')'
            DBINFO                              =  DBINFO $'(' (DBSPACE $',' *Expression | *sq_string) $')'
            Exponential_and_Logarithmic_Functions = EXP $'(' *float_expression $')'
+                                               |  LOGN $'(' *float_expression $')'
+                                               |  LOG10 $'(' *float_expression $')'
            LENGTH_Function                     =  LENGTH $'(' *db_owner_object_column $')'
            Time_Functions                      =  (  DATE $'(' *non_date_expression $')'
+                                                  |  (DAY | MONTH | WEEKDAY | YEAR) $'(' *datedatetime_expression $')'
+                                                  |  EXTEND $'(' *datedatetime_expression !($',' *first TO *last) $')'
+                                                  |  MDY
+                                                     $'('
+                                                     *month_integer_expression
+                                                     $','
+                                                     *day_integer_expression
+                                                     $','
+                                                     *year_integer_expression
+                                                     $')'
+                                                  )
            Trigonometric_Functions             =  (COS | SIN | TAN | ASIN | ACOS | ATAN | ATAN2) $'(' *Expression $')'
            TRIM_Function                       =  TRIM
+                                                  $'('
+                                                  !*ident
+                                                  !(LEADING | TRAILING | BOTH !*ident)
+                                                  FROM
+                                                  *ident
+                                                  $')'
            Aggregate_Expressions               =  AVG $'(' DISTINCT *Expression $')'
+                                               |  AVG $'(' UNIQUE *Expression $')'
+                                               |  AVG $'(' ALL *Expression $')'
+                                               |  AVG $'(' *Expression $')'
+                                               |  MAX $'(' DISTINCT *Expression $')'
+                                               |  MAX $'(' UNIQUE *Expression $')'
+                                               |  MAX $'(' ALL *Expression $')'
+                                               |  MAX $'(' *Expression $')'
+                                               |  MIN $'(' DISTINCT *Expression $')'
+                                               |  MIN $'(' UNIQUE *Expression $')'
+                                               |  MIN $'(' ALL *Expression $')'
+                                               |  MIN $'(' *Expression $')'
+                                               |  SUM $'(' DISTINCT *Expression $')'
+                                               |  SUM $'(' UNIQUE *Expression $')'
+                                               |  SUM $'(' ALL *Expression $')'
+                                               |  SUM $'(' *Expression $')'
+                                               |  RANGE $'(' DISTINCT *Expression $')'
+                                               |  RANGE $'(' UNIQUE *Expression $')'
+                                               |  RANGE $'(' ALL *Expression $')'
+                                               |  RANGE $'(' *Expression $')'
+                                               |  STDDEV $'(' DISTINCT *Expression $')'
+                                               |  STDDEV $'(' UNIQUE *Expression $')'
+                                               |  STDDEV $'(' ALL *Expression $')'
+                                               |  STDDEV $'(' *Expression $')'
+                                               |  VARIANCE $'(' DISTINCT *Expression $')'
+                                               |  VARIANCE $'(' UNIQUE *Expression $')'
+                                               |  VARIANCE $'(' ALL *Expression $')'
+                                               |  VARIANCE $'(' *Expression $')'
+                                               |  COUNT $'(' $'*' $')'
+                                               |  COUNT $'(' DISTINCT *Expression $')'
+                                               |  COUNT $'(' UNIQUE *Expression $')'
+                                               |  COUNT $'(' ALL *Expression $')'
+                                               |  COUNT $'(' *Expression $')'
            Procedure_Call_Expressions          =  *proc_db_owner_name
+                                                  $'('
+                                                  (*called_variable_eq_expr_list | *Expression_list)
+                                                  $')'
            called_variable_eq_expr_list        =  *called_variable_eq_expr
+                                               |  *called_variable_eq_expr_list $',' *called_variable_eq_expr
            called_variable_eq_expr             =  *ident $'=' *Expression
            Field_Qualifier                     =  YEAR
+                                                  !($'(' *y_precision $')')
+                                                  TO
+                                                  (  YEAR
+                                                  |  MONTH
+                                                  |  DAY
+                                                  |  HOUR
+                                                  |  MINUTE
+                                                  |  SECOND
+                                                  |  FRACTION !($'(' *f_precision $')')
+                                                  )
+                                               |  MONTH
+                                                  !($'(' *precision $')')
+                                                  TO
+                                                  (  MONTH
+                                                  |  DAY
+                                                  |  HOUR
+                                                  |  MINUTE
+                                                  |  SECOND
+                                                  |  FRACTION !($'(' *f_precision $')')
+                                                  )
+                                               |  DAY
+                                                  !($'(' *precision $')')
+                                                  TO
+                                                  (DAY | HOUR | MINUTE | SECOND | FRACTION !($'(' *f_precision $')'))
+                                               |  HOUR
+                                                  !($'(' *precision $')')
+                                                  TO
+                                                  (HOUR | MINUTE | SECOND | FRACTION !($'(' *f_precision $')'))
+                                               |  MINUTE
+                                                  !($'(' *precision $')')
+                                                  TO
+                                                  (MINUTE | SECOND | FRACTION !($'(' *f_precision $')'))
+                                               |  SECOND
+                                                  !($'(' *precision $')')
+                                                  TO
+                                                  (SECOND | FRACTION !($'(' *f_precision $')'))
+                                               |  FRACTION
+                                                  !($'(' *precision $')')
+                                                  TO
+                                                  FRACTION !($'(' *f_precision $')')
            Literal_DATETIME                    =  DATETIME $'(' *Numeric_Date $')' *Field_Qualifier
            Numeric_Date                        =  *number
+                                                  $'-'
+                                                  *number
+                                                  $'-'
+                                                  *number
+                                                  *number
+                                                  $':'
+                                                  *number
+                                                  $':'
+                                                  *number
+                                                  $'.'
+                                                  *number
+                                               |  *number $'-' *number $'-' *number *number $':' *number $':' *number
+                                               |  *number $'-' *number $'-' *number *number $':' *number
+                                               |  *number $'-' *number $'-' *number *number
+                                               |  *number $'-' *number $'-' *number
+                                               |  *number $'-' *number
+                                               |  *number
+                                               |  *number $'-' *number *number $':' *number $':' *number $'.' *number
+                                               |  *number $'-' *number *number $':' *number $':' *number
+                                               |  *number $'-' *number *number $':' *number
+                                               |  *number $'-' *number *number
+                                               |  *number *number $':' *number $':' *number $'.' *number
+                                               |  *number *number $':' *number $':' *number
+                                               |  *number *number $':' *number
+                                               |  *number *number
+                                               |  *number $':' *number $':' *number $'.' *number
+                                               |  *number $':' *number $':' *number
+                                               |  *number $':' *number
+                                               |  *number $':' *number $'.' *number
+                                               |  *number $'.' *number
            Literal_INTERVAL                    =  INTERVAL $'(' *Numeric_Date $')' *Field_Qualifier
            proc_db_owner_name                  =  *ident_proc
+                                               |  *ident $'.' *ident
+                                               |  *ident $':' *ident
+                                               |  *ident $':' *ident $'.' *ident
+                                               |  *ident $'@' *ident $':' *ident
+                                               |  *ident $'@' *ident $':' *ident $'.' *ident
+                                               |  *sq_string $'.' *ident
+                                               |  *ident $':' *sq_string
+                                               |  *ident $':' *sq_string $'.' *ident
+                                               |  *ident $'@' *ident $':' *sq_string
+                                               |  *ident $'@' *ident $':' *sq_string $'.' *ident
            db_owner_name                       =  *ident
+                                               |  *ident $'.' *ident
+                                               |  *ident $':' *ident
+                                               |  *ident $':' *ident $'.' *ident
+                                               |  *ident $'@' *ident $':' *ident
+                                               |  *ident $'@' *ident $':' *ident $'.' *ident
+                                               |  *sq_string $'.' *ident
+                                               |  *ident $':' *sq_string
+                                               |  *ident $':' *sq_string $'.' *ident
+                                               |  *ident $'@' *ident $':' *sq_string
+                                               |  *ident $'@' *ident $':' *sq_string $'.' *ident
            db_owner_object_column              =  *ident
+                                               |  *ident $'.' *ident
+                                               |  *ident $'.' *ident $'.' *ident
+                                               |  *ident $':' *ident $'.' *ident $'.' *ident
+                                               |  *ident $'@' *ident $':' *ident $'.' *ident $'.' *ident
+                                               |  *sq_string $'.' *ident
+                                               |  *ident $'.' *sq_string $'.' *ident
+                                               |  *ident $':' *ident $'.' *sq_string $'.' *ident
+                                               |  *ident $'@' *ident $':' *ident $'.' *sq_string $'.' *ident
            db_owner_name_dot_all               =  $'*'
+                                               |  *ident $'.' $'*'
+                                               |  *ident $'.' *ident $'.' $'*'
+                                               |  *ident $'@' *ident $':' *ident $'.' *ident $'.' $'*'
+                                               |  *sq_string $'.' *ident $'.' $'*'
+                                               |  *ident $'@' *ident $':' *sq_string $'.' *ident $'.' $'*'
            user_or_role_name                   =  *ident | *ident $'.' *ident | *sq_string | *sq_string $'.' *ident
            owner_name                          =  *ident | *ident $'.' *ident | *sq_string | *sq_string $'.' *ident
            CALL                                =  CALL
+                                                  *db_owner_name
+                                                  $'('
+                                                  !*argument_list
+                                                  $')'
+                                                  !(RETURNING *procedure_variable_list)
+                                                  $';'
            procedure_variable_list             =  *procedure_variable
+                                               |  *procedure_variable_list $',' *procedure_variable
            CONTINUE                            =  CONTINUE (FOR | WHILE | FOREACH) $';'
            DEFINE                              =  DEFINE
+                                                  !GLOBAL
+                                                  *variable_name_list
+                                                  (  *SQL_Data_Type_Subset !(DEFAULT *Default_Value)
+                                                  |  LIKE *db_owner_object_column
+                                                  |  PROCEDURE
+                                                  )
+                                                  $';'
            references_type_default_null        =  REFERENCES (BYTE | TEXT) !(DEFAULT NULL)
            Default_Value                       =  *number
+                                               |  *ident
+                                               |  *Literal_INTERVAL
+                                               |  *Literal_DATETIME
+                                               |  *current_datetime
+                                               |  USER
+                                               |  TODAY
+                                               |  NULL
+                                               |  DBSERVERNAME
+                                               |  SITENAME
            EXIT                                =  EXIT (FOR | WHILE | FOREACH) $';'
            current_datetime                    =  CURRENT !*Field_Qualifier
            FOR                                 =  FOR
+                                                  *variable_name
+                                                  (  IN $'(' *for_expr_sub_clause_list $')'
+                                                  |  $'='
+                                                     *left_expression
+                                                     TO
+                                                     *right_expression
+                                                     !(STEP *increment_expression)
+                                                  )
+                                                  *Statement_Block
+                                                  END
+                                                  FOR
+                                                  !$';'
            for_expr_sub_clause                 =  *left_expression TO *right_expression !(STEP *increment_expression)
+                                               |  *Expression
            for_expr_sub_clause_list            =  *for_expr_sub_clause
+                                               |  *for_expr_sub_clause_list $',' *for_expr_sub_clause
            FOREACH                             =  FOREACH
+                                                  (  EXECUTE
+                                                     PROCEDURE
+                                                     *db_owner_name
+                                                     $'('
+                                                     *parameter_eq_expr_subset_list
+                                                     $')'
+                                                     !(INTO *variable_name_list)
+                                                  |  *cursor_name !(WITH HOLD) FOR *SELECT
+                                                  |  !(WITH HOLD) *SELECT
+                                                  )
+                                                  *Statement_Block
+                                                  END
+                                                  FOREACH
+                                                  !$';'
            parameter_eq_expr_subset            =  !(*Expression_Subset | *parameter_name $'=' *Expression_Subset)
            parameter_eq_expr_subset_list       =  *parameter_eq_expr_subset
+                                               |  *parameter_eq_expr_subset_list $',' *parameter_eq_expr_subset
            IF                                  =  IF *Condition THEN END IF
+                                               |  IF *Condition THEN END IF $';'
+                                               |  IF *Condition THEN ELSE *if_statement_lists END IF
+                                               |  IF *Condition THEN ELSE *if_statement_lists END IF $';'
+                                               |  IF *Condition THEN *if_statement_lists END IF
+                                               |  IF *Condition THEN *if_statement_lists END IF $';'
+                                               |  IF
+                                                  *Condition
+                                                  THEN
+                                                  *if_statement_lists
+                                                  ELSE
+                                                  *if_statement_lists
+                                                  END
+                                                  IF
+                                               |  IF
+                                                  *Condition
+                                                  THEN
+                                                  *if_statement_lists
+                                                  ELSE
+                                                  *if_statement_lists
+                                                  END
+                                                  IF
+                                                  $';'
+                                               |  IF *Condition THEN *if_statement_lists *ELIF_clauses END IF
+                                               |  IF *Condition THEN *if_statement_lists *ELIF_clauses END IF $';'
+                                               |  IF *Condition THEN *ELIF_clauses END IF
+                                               |  IF *Condition THEN *ELIF_clauses END IF $';'
+                                               |  IF *Condition THEN *ELIF_clauses ELSE *if_statement_lists END IF
+                                               |  IF
+                                                  *Condition
+                                                  THEN
+                                                  *ELIF_clauses
+                                                  ELSE
+                                                  *if_statement_lists
+                                                  END
+                                                  IF
+                                                  $';'
+                                               |  IF
+                                                  *Condition
+                                                  THEN
+                                                  *if_statement_lists
+                                                  *ELIF_clauses
+                                                  ELSE
+                                                  *if_statement_lists
+                                                  END
+                                                  IF
+                                               |  IF
+                                                  *Condition
+                                                  THEN
+                                                  *if_statement_lists
+                                                  *ELIF_clauses
+                                                  ELSE
+                                                  *if_statement_lists
+                                                  END
+                                                  IF
+                                                  $';'
            ELIF_clauses                        =  *ELIF_clause | *ELIF_clauses *ELIF_clause
            ELIF_clause                         =  ELIF *Condition THEN *if_statement_lists
            IF_Statement_List                   =  BEGIN *Statement_Block END
+                                               |  *CALL
+                                               |  *CONTINUE
+                                               |  *EXIT
+                                               |  *FOR
+                                               |  *FOREACH
+                                               |  *IF
+                                               |  *LET
+                                               |  *RAISE_EXCEPTION
+                                               |  *RETURN
+                                               |  *SYSTEM
+                                               |  *TRACE
+                                               |  *WHILE
+                                               |  *SQL_Statement $';'
            if_statement_lists                  =  *IF_Statement_List | *if_statement_lists *IF_Statement_List
            LET                                 =  LET *variable_name_list $'=' *Expression_list $';'
            ON_EXCEPTION                        =  ON
+                                                  EXCEPTION
+                                                  !(IN $'(' *error_number_list $')')
+                                                  (*Statement_Block | *on_exception_set_clause *Statement_Block)
+                                                  END
+                                                  EXCEPTION
+                                                  !(WITH RESUME)
+                                                  !$';'
            error_number                        =  *Expression
            error_number_list                   =  *error_number | *error_number_list $',' *error_number
            on_exception_set_clause             =  SET
+                                                  *error_variable
+                                                  !($',' *error_variable !($',' *error_variable))
            RAISE_EXCEPTION                     =  RAISE
+                                                  EXCEPTION
+                                                  *Expression
+                                                  !($',' *Expression !($',' *Expression))
+                                                  $';'
            RETURN                              =  RETURN !(*Expression !($',' *Expression) !(WITH RESUME)) $';'
            SYSTEM                              =  SYSTEM *Expression $';'
            TRACE                               =  TRACE (OFF | PROCEDURE | *Expression) $';'
            WHILE                               =  WHILE *Condition *Statement_Block END WHILE !$';'
            ALTER_OPTICAL_CLUSTER               =  ALTER OPTICAL CLUSTER *owner_name *CLUSTERSIZE_Clause
            CLUSTERSIZE_Clause                  =  CLUSTERSIZE !*clustersize
            CREATE_OPTICAL_CLUSTER              =  CREATE
+                                                  OPTICAL
+                                                  CLUSTER
+                                                  *owner_name
+                                                  *FOR__Clause
+                                                  *ON__Clause
+                                                  !*CLUSTERSIZE_Clause
            FOR__Clause                         =  FOR *db_owner_name $'(' *column_name_list $')'
            ON__Clause                          =  ON $'(' *column_name_list $')'
            DROP_OPTICAL_CLUSTER                =  DROP OPTICAL CLUSTER *owner_name
            RELEASE                             =  RELEASE *variable_volume_clause
            RESERVE                             =  RESERVE *variable_volume_clause
            variable_volume_clause              =  *variable_name *volume_number
            SET_MOUNTING_TIMEOUT                =  SET MOUNTING TIMEOUT TO (WAIT | NOT WAIT | *seconds)
            datetime_with_qualifier             =  DATETIME *Field_Qualifier
            SQL_Data_Type_Subset                =  (CHAR | CHARACTER) !($'(' *size $')')
+                                               |  NCHAR !($'(' *size $')')
+                                               |  DATE
+                                               |  *datetime_with_qualifier
+                                               |  (DECIMAL | DEC | NUMERIC) !($'(' *precision !($',' *scale) $')')
+                                               |  FLOAT !($'(' *float_precision $')')
+                                               |  DOUBLE PRECISION
+                                               |  INTEGER | INT
+                                               |  INTERVAL *Field_Qualifier
+                                               |  MONEY !($'(' *precision !($',' *scale) $')')
+                                               |  SMALLFLOAT | REAL
+                                               |  SMALLINT
+                                               |  *INFORMIX_ODS_Specific_Data_Types
            db_owner_name_list                  =  *db_owner_name | *db_owner_name_list $',' *db_owner_name
            owner_name_list                     =  *owner_name | *owner_name_list $',' *owner_name
            column_name_list                    =  *db_owner_object_column
+                                               |  *column_name_list $',' *db_owner_object_column
            dbspace_list                        =  *dbspace | *dbspace_list $',' *dbspace
            frag_expression_in_clause_list      =  *frag_expression_in_clause
+                                               |  *frag_expression_in_clause_list $',' *frag_expression_in_clause
            modify_dbspace_in_clause_list       =  *modify_dbspace_in_clause
+                                               |  *modify_dbspace_in_clause_list $',' *modify_dbspace_in_clause
            collection_of_clauses_list          =  *collection_of_clauses
+                                               |  *collection_of_clauses_list $',' *collection_of_clauses
            add_column_clause_list              =  *Add_Column_Clause | *add_column_clause_list $',' *Add_Column_Clause
            new_column_constraint_definition_list = *New_Column_Constraint_Definition
+                                               |  *new_column_constraint_definition_list
+                                                  *New_Column_Constraint_Definition
            modify_column_clause_list           =  *Modify_Column_Clause
+                                               |  *modify_column_clause_list $',' *Modify_Column_Clause
            table_level_constraint_definition_list = *Table_Level_Constraint_Definition
+                                               |  *table_level_constraint_definition_list
+                                                  $','
+                                                  *Table_Level_Constraint_Definition
            column_name_order_list              =  *column_name_order | *column_name_order_list $',' *column_name_order
            quoted_string_list                  =  *ident | *sq_string | *quoted_string_list $',' (*ident | *sq_string)
            parameter_list                      =  *parameter | *parameter_list $',' *parameter
            returning_sub_clause_list           =  *returning_sub_clause
+                                               |  *returning_sub_clause_list $',' *returning_sub_clause
            temp_table_column_definition_list   =  *Temporary_Table_Column_Definition
+                                               |  *temp_table_column_definition_list
+                                                  $','
+                                                  *Temporary_Table_Column_Definition
            temp_table_table_level_constraint_list = *Temp_Table_Table_Level_Constraint
+                                               |  *temp_table_table_level_constraint_list
+                                                  $','
+                                                  *Temp_Table_Table_Level_Constraint
            define_list                         =  *DEFINE | *define_list *DEFINE
            on_exception_list                   =  *ON_EXCEPTION | *on_exception_list *ON_EXCEPTION
            statement_block_clause_list         =  *statement_block_clause
+                                               |  *statement_block_clause_list *statement_block_clause
            create_schema_sub_clause_list       =  *create_schema_sub_clause
+                                               |  *create_schema_sub_clause_list *create_schema_sub_clause
            update_referencing_sub_clause_list  =  *update_referencing_sub_clause
+                                               |  *update_referencing_sub_clause_list *update_referencing_sub_clause
            described_item_info_list            =  *Described_Item_Info
+                                               |  *described_item_info_list $',' *Described_Item_Info
            statement_clause_list               =  *Statement_Clause | *statement_clause_list $',' *Statement_Clause
            exception_sub_clause_list           =  *exception_sub_clause
+                                               |  *exception_sub_clause_list $',' *exception_sub_clause
            user_name_clause_list               =  *user_name_clause | *user_name_clause_list $',' *user_name_clause
            user_or_role_name_clause_list       =  *user_or_role_name_clause
+                                               |  *user_or_role_name_clause_list $',' *user_or_role_name_clause
            fragment_privilege_clause_list      =  *fragment_privilege_clause
+                                               |  *fragment_privilege_clause_list $',' *fragment_privilege_clause
            table_level_privileges_grant_clause_list = *table_level_privileges_grant_clause
+                                               |  *table_level_privileges_grant_clause_list
+                                                  $','
+                                                  *table_level_privileges_grant_clause
            argument_list                       =  *Argument | *argument_list $',' *Argument
            values_sub_clause_list              =  *values_sub_clause | *values_sub_clause_list $',' *values_sub_clause
            variable_name_list                  =  *variable_name | *variable_name_list $',' *variable_name
            revoke_table_level_privileges_clause_list = *revoke_table_level_privileges_clause
+                                               |  *revoke_table_level_privileges_clause_list
+                                                  $','
+                                                  *revoke_table_level_privileges_clause
            into_sub_clause_list                =  *into_sub_clause | *into_sub_clause_list $',' *into_sub_clause
            group_by_sub_clause_list            =  *group_by_sub_clause
+                                               |  *group_by_sub_clause_list $',' *group_by_sub_clause
            order_by_sub_clause_list            =  *order_by_sub_clause
+                                               |  *order_by_sub_clause_list $',' *order_by_sub_clause
            contraints_or_indexes_or_triggers_list = *contraints_or_indexes_or_triggers
+                                               |  *contraints_or_indexes_or_triggers_list
+                                                  $','
+                                                  *contraints_or_indexes_or_triggers
            item_descriptor_information_list    =  *Item__Descriptor__Information
+                                               |  *item_descriptor_information_list
+                                                  $','
+                                                  *Item__Descriptor__Information
            column_name_eq_expr_clause_list     =  *column_name_eq_expr_clause
+                                               |  *column_name_eq_expr_clause_list $',' *column_name_eq_expr_clause
