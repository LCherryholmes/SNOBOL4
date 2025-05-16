            '('                                 =  '('
            ')'                                 =  ')'
            '*'                                 =  '*'
            '+'                                 =  '+'
            ','                                 =  ','
            '-'                                 =  '-'
            '.'                                 =  '.'
            '/'                                 =  '/'
            ';'                                 =  ';'
            '='                                 =  '='
            '@'                                 =  '@'
            '\''                                =  "'"
            file                                =  !*commands
            commands                            =  %*command
            command                             =  *terminator | *sqlplus_command | *ddl_command
            terminator                          =  $';' | $'_EOT_'
            ddl_command                         =  *DDL_command *terminator | *error *terminator
            sqlplus_command                     =  *SQLPLUS_command $nl | *error $nl
            plsql_begin                         =  DECLARE | BEGIN | BEGINBLOCK | $'_IDENT_' | identifier
            plsql_block                         =  $'_PLSQL_TEXT_'
            SQLPLUS_command                     =  *SQLPLUS_connect
+                                               |  EXIT
+                                               |  PROMPT
+                                               |  PROMPT $'_STRING_'
+                                               |  REMARK
+                                               |  REMARK $'_STRING_'
+                                               |  START
+                                               |  START $'_STRING_'
+                                               |  SET
+                                               |  SPOOL
+                                               |  DISCONNECT
            SQLPLUS_connect                     =  CONNECT $'_STRING_'
+                                               |  CONNECT $'_STRING_' $'@' $'_STRING_'
+                                               |  CONNECT $'_STRING_' $'/' $'_STRING_'
+                                               |  CONNECT $'_STRING_' $'/' $'_STRING_' $'@' $'_STRING_'
            DDL_command                         =  *create_table
+                                               |  *alter_table
+                                               |  *comment
+                                               |  *create_index
+                                               |  *alter_index
+                                               |  *create_synonym
+                                               |  *create_snapshot
+                                               |  *alter_rollback_segment
+                                               |  *alter_tablespace
+                                               |  *alter_trigger
+                                               |  *create_cluster
+                                               |  *alter_cluster
+                                               |  *create_database_link
+                                               |  *create_directory
+                                               |  *create_function
+                                               |  *create_package
+                                               |  *create_package_body
+                                               |  *create_procedure
+                                               |  *create_profile
+                                               |  *create_refresh_group
+                                               |  *create_role
+                                               |  *create_rollback_segment
+                                               |  *create_sequence
+                                               |  *alter_sequence
+                                               |  *create_snapshot_log
+                                               |  *create_tablespace
+                                               |  *create_trigger
+                                               |  *create_user
+                                               |  *create_view
+                                               |  *alter_session
+                                               |  *alter_snapshot
+                                               |  *alter_snapshot_log
+                                               |  *alter_user
+                                               |  *alter_view
+                                               |  *alter_function
+                                               |  *alter_procedure
+                                               |  *alter_package
+                                               |  *audit
+                                               |  *grant
+                                               |  *rename
+                                               |  *commit
+                                               |  *insert
+                                               |  *select
+                                               |  *delete
+                                               |  *update
+                                               |  *call
+                                               |  *drop_command
            drop_command                        =  *drop_cluster
+                                               |  *drop_database_link
+                                               |  *drop_directory
+                                               |  *drop_function
+                                               |  *drop_index
+                                               |  *drop_package
+                                               |  *drop_package_body
+                                               |  *drop_procedure
+                                               |  *drop_profile
+                                               |  *drop_refresh_group
+                                               |  *drop_role
+                                               |  *drop_rollback
+                                               |  *drop_snapshot
+                                               |  *drop_snapshotlog
+                                               |  *drop_sequence
+                                               |  *drop_synonym
+                                               |  *drop_table
+                                               |  *drop_tablespace
+                                               |  *drop_trigger
+                                               |  *drop_type
+                                               |  *drop_user
+                                               |  *drop_view
            audit                               =  AUDIT
+                                                  *audit_0
+                                                  ON
+                                                  (*object | DEFAULT | DIRECTORY *directory_name)
+                                                  !(BY (SESSION | ACCESS))
+                                                  !(WHENEVER SUCCESSFUL | WHENEVER NOT SUCCESSFUL)
            audit_0                             =  ALL | *audit_1 | *audit_0 $',' *audit_1
            audit_1                             =  ALTER
+                                               |  AUDIT
+                                               |  COMMENT
+                                               |  DELETE
+                                               |  EXECUTE
+                                               |  GRANT
+                                               |  INDEX
+                                               |  INSERT
+                                               |  LOCK
+                                               |  RENAME
+                                               |  SELECT
+                                               |  UPDATE
            drop_cluster                        =  DROP CLUSTER *object !(INCLUDING TABLES) !(CASCADE CONSTRAINTS)
            drop_database_link                  =  DROP !PUBLIC DATABASE LINK *dblink
            drop_directory                      =  DROP DIRECTORY *directory_name
            drop_function                       =  DROP FUNCTION *object
            drop_index                          =  DROP INDEX *object
            drop_package                        =  DROP PACKAGE *object
            drop_package_body                   =  DROP PACKAGE BODY *object
            drop_procedure                      =  DROP PROCEDURE *object
            drop_profile                        =  DROP PROFILE *profile_name !CASCADE
            drop_role                           =  DROP ROLE *role_name
            drop_rollback                       =  DROP ROLLBACK SEGMENT *object_name
            drop_sequence                       =  DROP SEQUENCE *object
            drop_snapshot                       =  DROP SNAPSHOT *object
            drop_snapshotlog                    =  DROP SNAPSHOT LOG ON *object
            drop_synonym                        =  DROP !PUBLIC SYNONYM *object
            drop_table                          =  DROP TABLE *object !(CASCADE CONSTRAINTS)
            drop_tablespace                     =  DROP
+                                                  TABLESPACE
+                                                  *object_name
+                                                  !(INCLUDING CONTENTS)
+                                                  !(CASCADE CONSTRAINTS)
            drop_trigger                        =  DROP TRIGGER *object
            drop_type                           =  DROP TYPE *object !FORCE
            drop_user                           =  DROP USER *object_name !CASCADE
            drop_view                           =  DROP VIEW *object
            distribution                        =  *role_name | PUBLIC
            distribution_list                   =  *distribution *distribution_list_1
            distribution_list_1                 =  !(*distribution_list_1 $',' *distribution)
            grant                               =  *grant_object_priv | *grant_system_priv
            common_column                       =  *id
            common_column_list                  =  *common_column % $','
            grant_object_priv                   =  GRANT
+                                                  (  (*object_privilege | ALL !PRIVILEGES)
+                                                     !($'(' *common_column_list $')')
+                                                  ) % $','
+                                                  ON
+                                                  *object
+                                                  TO
+                                                  *distribution_list
+                                                  !(WITH GRANT OPTION)
            grant_system_priv                   =  GRANT
+                                                  *grant_system_priv_1
+                                                  TO
+                                                  *distribution_list
+                                                  !(WITH ADMIN OPTION)
            grant_system_priv_1                 =  ALL PRIVILEGES
+                                               |  *grant_system_priv_1_1
+                                               |  *grant_system_priv_1 $',' *grant_system_priv_1_1
            grant_system_priv_1_1               =  *system_privilege | *role_name
            object_privilege                    =  ALTER
+                                               |  DELETE
+                                               |  EXECUTE
+                                               |  INDEX
+                                               |  INSERT
+                                               |  REFERENCES
+                                               |  SELECT
+                                               |  UPDATE
            system_privilege                    =  ALTER ANY CLUSTER
+                                               |  ALTER ANY INDEX
+                                               |  ALTER ANY PROCEDURE
+                                               |  ALTER ANY ROLE
+                                               |  ALTER ANY SEQUENCE
+                                               |  ALTER ANY SNAPSHOT
+                                               |  ALTER ANY TABLE
+                                               |  ALTER ANY TRIGGER
+                                               |  ALTER DATABASE
+                                               |  ALTER PROFILE
+                                               |  ALTER RESOURCE COST
+                                               |  ALTER ROLLBACK SEGMENT
+                                               |  ALTER SESSION
+                                               |  ALTER SYSTEM
+                                               |  ALTER TABLESPACE
+                                               |  ALTER USER
+                                               |  ANALYZE ANY
+                                               |  AUDIT ANY
+                                               |  AUDIT SYSTEM
+                                               |  BACKUP ANY TABLE
+                                               |  BECOME USER
+                                               |  COMMENT ANY TABLE
+                                               |  CREATE ANY CLUSTER
+                                               |  CREATE ANY INDEX
+                                               |  CREATE ANY PROCEDURE
+                                               |  CREATE ANY SEQUENCE
+                                               |  CREATE ANY SNAPSHOT
+                                               |  CREATE ANY SYNONYM
+                                               |  CREATE ANY TABLE
+                                               |  CREATE ANY TRIGGER
+                                               |  CREATE ANY VIEW
+                                               |  CREATE CLUSTER
+                                               |  CREATE DATABASE LINK
+                                               |  CREATE PROCEDURE
+                                               |  CREATE PROFILE
+                                               |  CREATE PUBLIC DATABASE LINK
+                                               |  CREATE PUBLIC SYNONYM
+                                               |  CREATE ROLE
+                                               |  CREATE ROLLBACK SEGMENT
+                                               |  CREATE SESSION
+                                               |  CREATE SEQUENCE
+                                               |  CREATE SNAPSHOT
+                                               |  CREATE SYNONYM
+                                               |  CREATE TABLE
+                                               |  CREATE TABLESPACE
+                                               |  CREATE TRIGGER
+                                               |  CREATE USER
+                                               |  CREATE VIEW
+                                               |  DELETE ANY TABLE
+                                               |  DROP ANY CLUSTER
+                                               |  DROP ANY INDEX
+                                               |  DROP ANY PROCEDURE
+                                               |  DROP ANY ROLE
+                                               |  DROP ANY SEQUENCE
+                                               |  DROP ANY SNAPSHOT
+                                               |  DROP ANY SYNONYM
+                                               |  DROP ANY TABLE
+                                               |  DROP ANY TRIGGER
+                                               |  DROP ANY VIEW
+                                               |  DROP PROFILE
+                                               |  DROP PUBLIC DATABASE LINK
+                                               |  DROP PUBLIC SYNONYM
+                                               |  DROP ROLLBACK SEGMENT
+                                               |  DROP TABLESPACE
+                                               |  DROP USER
+                                               |  EXECUTE ANY PROCEDURE
+                                               |  FORCE ANY TRANSACTION
+                                               |  FORCE TRANSACTION
+                                               |  GRANT ANY PRIVILEGE
+                                               |  GRANT ANY ROLE
+                                               |  INSERT ANY TABLE
+                                               |  LOCK ANY TABLE
+                                               |  MANAGE TABLESPACE
+                                               |  RESTRICTED SESSION
+                                               |  SELECT ANY SEQUENCE
+                                               |  SELECT ANY TABLE
+                                               |  UNLIMITED TABLESPACE
+                                               |  UPDATE ANY TABLE
            commit                              =  COMMIT
            insert                              =  INSERT
+                                                  INTO
+                                                  *object
+                                                  !($'(' *common_column_list $')')
+                                                  (VALUES $'(' *expr_list $')' | *subquery) % $','
            rename                              =  RENAME *id TO *id
            delete                              =  DELETE
+                                                  !*hint
+                                                  !FROM
+                                                  *table_expression_clause
+                                                  !*simple_where_clause
+                                                  !*returning_clause
            update                              =  UPDATE
+                                                  !*hint
+                                                  *table_expression_clause
+                                                  *set_clause
+                                                  !*simple_where_clause
+                                                  !*returning_clause
            returning_clause                    =  RETURNING *expr_list INTO *common_column_list
            set_clause                          =  SET *set_clause_1 | SET *set_clause_1
            set_clause_1                        =  *set_clause_1_0
+                                               |  *set_clause_1 $',' *set_clause_1_0
+                                               |  *set_clause_1_0
+                                               |  *set_clause_1 *set_clause_1_0
            set_clause_1_0                      =  $'(' *common_column_list $')' $'=' $'(' *subquery $')'
+                                               |  *id $'=' (*expr | $'(' *subquery $')')
+                                               |  *id $'=' *parameter_value
            simple_where_clause                 =  WHERE *condition
            select                              =  *subquery | *subquery *for_update_clause
            subquery                            =  SELECT
+                                                  *hint
+                                                  !(DISTINCT | UNIQUE | ALL)
+                                                  ($'*' | (*object $'.' $'*' | *expr !(!AS *alias)) % $',')
+                                                  FROM
+                                                  *table_expression_clause
+                                                  !*where_clause
+                                                  !%(*hierarchical_query_clause | *group_by_clause)
+                                                  !(*subquery_5_1 *subquery | *subquery_5_1 $'(' *subquery $')')
+                                                  !*order_by_clause
            subquery_5_1                        =  UNION | UNION ALL | INTERSECT | MINUS
            order_by_clause                     =  ORDER BY (*expr !(ASC | DESC)) % $','
            outer_join                          =  *object_name
+                                                  $'.'
+                                                  *id
+                                                  !( $'=' *object_name $'.' *id $'(' $'+' $')'
+                                                  |  $'(' $'+' $')' $'=' *object_name $'.' *id
+                                                  )
            group_by_clause                     =  GROUP
+                                                  BY
+                                                  (  CUBE $'(' *expr % $',' $')'
+                                                  |  *expr % $','
+                                                  |  ROLLUP $'(' *expr % $',' $')'
+                                                  )
+                                                  !(HAVING *condition)
            hierarchical_query_clause           =  !(START WITH *condition) CONNECT BY *condition
            table_expression_clause             =  (  (  *object
+                                                        !( *sample_clause
+                                                        |  SUBPARTITION $'(' *subpartition $')'
+                                                        |  PARTITION $'(' *partition $')'
+                                                        |  $'@' *dblink
+                                                        )
+                                                     |  $'(' *subquery !*with_clause $')'
+                                                     |  *table_collection_expression
+                                                     )
+                                                     *optional_alias
+                                                  ) % $','
            optional_alias                      =  !*alias
            where_clause                        =  WHERE (*condition | *outer_join)
            with_clause                         =  WITH READ ONLY | WITH CHECK OPTION *optional_constraint_name
            sample_clause                       =  SAMPLE !BLOCK $'(' *id $')'
            call                                =  CALL
+                                                  *call_1
+                                                  *call_1
+                                                  *id
+                                                  !($'@' *dblink)
+                                                  $'('
+                                                  *expr_list
+                                                  $')'
+                                                  !(INTO $':' *id !(!INDICATOR $':' *id))
            call_1                              =  !(*id $'.')
            alter_cluster                       =  ALTER
+                                                  CLUSTER
+                                                  *object
+                                                  %( *physical_attribute_clause
+                                                  |  SIZE *n_bytes
+                                                  |  *allocate_extent_clause
+                                                  |  *deallocate_unused_clause
+                                                  )
+                                                  !*parallel_clause
            alter_index                         =  ALTER INDEX *object *alter_index_attributes
            alter_index_attributes              =  %*alter_index_attribute
            alter_index_attribute               =  *physical_attribute_clause | *alter_index_option
            alter_index_option                  =  *rebuild_option | *deallocate_unused_clause | *allocate_extent_clause
            rebuild_option                      =  REBUILD *optional_rebuild_options
            optional_rebuild_options            =  !(*optional_rebuild_options *optional_rebuild_option)
            optional_rebuild_option             =  *parallel_option | *recoverable_option | TABLESPACE *object_name
            parallel_option                     =  PARALLEL *n | NOPARALLEL
            recoverable_option                  =  RECOVERABLE | UNRECOVERABLE
            alter_view                          =  ALTER VIEW *object COMPILE
            alter_rollback_segment              =  ALTER
+                                                  ROLLBACK
+                                                  SEGMENT
+                                                  *object_name
+                                                  (ONLINE | OFFLINE | *storage_clause | SHRINK TO *n_bytes)
            alter_tablespace                    =  ALTER
+                                                  TABLESPACE
+                                                  *object_name
+                                                  !(LOGGING | NOLOGGING)
+                                                  !( ONLINE
+                                                  |  OFFLINE
+                                                  |  OFFLINE NORMAL
+                                                  |  OFFLINE TEMPORARY
+                                                  |  OFFLINE IMMEDIATE
+                                                  |  READ ONLY
+                                                  |  READ WRITE
+                                                  |  DEFAULT *storage_clause
+                                                  |  MINIMUM EXTENT *n_bytes
+                                                  |  BEGIN BACKUP
+                                                  |  END BACKUP
+                                                  |  PERMANENT
+                                                  |  TEMPORARY
+                                                  |  COALESCE
+                                                  |  *datafile_clauses
+                                                  )
            datafile_clauses                    =  ADD (DATAFILE | TEMPFILE) (*filespec !*autoextend_clause) % $','
+                                               |  RENAME DATAFILE *filename % $',' TO *filename % $','
            filespec                            =  *filename !(SIZE *n_bytes) !REUSE
            autoextend_clause                   =  AUTOEXTEND OFF | AUTOEXTEND ON !(NEXT *n_bytes) !*maxsize_clause
            maxsize_clause                      =  MAXSIZE (UNLIMITED | *n_bytes)
            alter_trigger                       =  ALTER TRIGGER *object (ENABLE | DISABLE | COMPILE !IDDL_DEBUG)
            comment                             =  COMMENT ON *comment_on_column | COMMENT ON *comment_on_table
            comment_on_column                   =  COLUMN
+                                                  (  *identifier $'.' *identifier $'.' *identifier
+                                                  |  *identifier $'.' *identifier
+                                                  )
+                                                  IS
+                                                  $'_SQ_STRING_'
            comment_on_table                    =  TABLE *object IS $'_SQ_STRING_'
            create_database_link                =  CREATE
+                                                  !SHARED
+                                                  !PUBLIC
+                                                  DATABASE
+                                                  LINK
+                                                  *dblink
+                                                  !(CONNECT TO *object_name IDENTIFIED BY *password)
+                                                  !(USING $'_SQ_STRING_')
            create_directory                    =  CREATE *or_replace DIRECTORY *directory_name AS *pathname
            alter_package                       =  ALTER
+                                                  PACKAGE
+                                                  *object
+                                                  COMPILE
+                                                  !IDDL_DEBUG
+                                                  !(PACKAGE | SPECIFICATION | BODY)
            alter_function                      =  ALTER FUNCTION *object COMPILE !IDDL_DEBUG
            alter_procedure                     =  ALTER PROCEDURE *object COMPILE !IDDL_DEBUG
            create_function                     =  CREATE
+                                                  *or_replace
+                                                  FUNCTION
+                                                  *object
+                                                  !( $'('
+                                                     (*id !(IN | OUT | IN OUT | INOUT) !NOCOPY *plsql_datatype) % $','
+                                                     $')'
+                                                  )
+                                                  !( RETURN
+                                                     *plsql_datatype
+                                                     !%(*invoker_rights_clause | DETERMINISTIC | PARALLEL_ENABLE)
+                                                  )
+                                                  (  WRAPPED *plsql_block
+                                                  |  IS *create_function_3_1
+                                                  |  AS *create_function_3_1
+                                                  )
            create_function_3_1                 =  *call_spec | *plsql_begin *plsql_block
            invoker_rights_clause               =  AUTHID (CURRENT_USER | DEFINER)
            call_spec                           =  LANGUAGE *Java_declaration | LANGUAGE *C_declaration
            Java_declaration                    =  JAVA NAME $'_SQ_STRING_'
            C_declaration                       =  C !(NAME *id) LIBRARY *id !(WITH CONTEXT) !(PARAMETERS $'(' $')')
            create_package                      =  CREATE
+                                                  *or_replace
+                                                  PACKAGE
+                                                  *object
+                                                  (IS *plsql_block | AS *plsql_block | WRAPPED *plsql_block)
            create_package_body                 =  CREATE
+                                                  *or_replace
+                                                  PACKAGE
+                                                  BODY
+                                                  *object
+                                                  (IS *plsql_block | AS *plsql_block | WRAPPED *plsql_block)
            create_procedure                    =  CREATE
+                                                  *or_replace
+                                                  PROCEDURE
+                                                  *object
+                                                  !( $'('
+                                                     (*id !(IN | OUT | IN OUT | INOUT) !NOCOPY *plsql_datatype) % $','
+                                                     $')'
+                                                  )
+                                                  !*invoker_rights_clause
+                                                  (  (IS | AS) (*plsql_begin *plsql_block | *call_spec)
+                                                  |  WRAPPED *plsql_block
+                                                  )
            create_profile                      =  CREATE
+                                                  PROFILE
+                                                  *profile_name
+                                                  LIMIT
+                                                  %(*resource_parameters | *password_parameters)
            resource_parameters                 =  SESSIONS_PER_USER *resource_parameters_1
+                                               |  CPU_PER_SESSION *resource_parameters_1
+                                               |  CPU_PER_CALL *resource_parameters_1
+                                               |  CONNECT_TIME *resource_parameters_1
+                                               |  IDLE_TIME *resource_parameters_1
+                                               |  LOGICAL_READS_PER_SESSION *resource_parameters_1
+                                               |  LOGICAL_READS_PER_CALL *resource_parameters_1
+                                               |  COMPOSITE_LIMIT *resource_parameters_1
+                                               |  PRIVATE_SGA *resource_parameters_1
            password_parameters                 =  FAILED_LOGIN_ATTEMPTS *password_parameters_1
+                                               |  PASSWORD_LIFE_TIME *password_parameters_1
+                                               |  PASSWORD_LOCK_TIME *password_parameters_1
+                                               |  PASSWORD_GRACE_TIME *password_parameters_1
+                                               |  PASSWORD_REUSE_MAX *password_parameters_1
+                                               |  PASSWORD_REUSE_TIME *password_parameters_1
+                                               |  PASSWORD_VERIFY_FUNCTION (*identifier | NULL | DEFAULT)
            resource_parameters_1               =  *n_bytes | UNLIMITED | DEFAULT
            password_parameters_1               =  *resource_parameters_1
            rg_assoc_list                       =  *rg_assoc % $','
            rg_assoc                            =  *identifier $'_ASSOC_' *boolean_literal
+                                               |  *identifier $'_ASSOC_' *identifier
+                                               |  *identifier $'_ASSOC_' $'_SQ_STRING_'
+                                               |  *identifier $'_ASSOC_' SYSDATE
            rg_name                             =  $'_SQ_STRING_'
            rg_list                             =  $'_SQ_STRING_'
            rg_next_date                        =  SYSDATE | $'_STRING_' | $'_SQ_STRING_'
            rg_interval                         =  $'_SQ_STRING_'
            rg_implicit_destroy                 =  *boolean_literal
            rg_lax                              =  *boolean_literal
            rg_job                              =  $'_NUMBER_'
            rg_rollback_seg                     =  $'_SQ_STRING_'
            rg_push_deferred_rpc                =  *boolean_literal
            rg_refresh_after_errors             =  *boolean_literal
            rg_purge_option                     =  $'_NUMBER_'
            rg_parallelism                      =  $'_NUMBER_'
            rg_heap_size                        =  $'_NUMBER_'
            drop_refresh_group                  =  BEGIN *drop_rg_1 $'(' *drop_rg_2 $')' $';' END
+                                               |  *drop_rg_1 $'(' *drop_rg_2 $')'
            drop_rg_1                           =  EXECUTE SYS $'.' DBMS_REFRESH $'.' DESTROY
+                                               |  EXECUTE DBMS_REFRESH $'.' DESTROY
+                                               |  DBMS_REFRESH $'.' DESTROY
+                                               |  SYS $'.' DBMS_REFRESH $'.' DESTROY
            drop_rg_2                           =  *rg_assoc | *rg_name
            create_refresh_group                =  BEGIN *create_rg_1 $'(' *create_rg_2 $')' $';' END
+                                               |  *create_rg_1 $'(' *create_rg_2 $')'
            create_rg_1                         =  EXECUTE SYS $'.' DBMS_REFRESH $'.' MAKE
+                                               |  EXECUTE DBMS_REFRESH $'.' MAKE
+                                               |  DBMS_REFRESH $'.' MAKE
+                                               |  SYS $'.' DBMS_REFRESH $'.' MAKE

            create_rg_2                         =  *rg_assoc_list
+                                               |  *rg_name
+                                                  $','
+                                                  *rg_list
+                                                  $','
+                                                  *rg_next_date
+                                                  $','
+                                                  *rg_interval
+                                                  !( $','
+                                                     *rg_implicit_destroy
+                                                     !( $','
+                                                        *rg_lax
+                                                        !( $','
+                                                           *rg_job
+                                                           !( $','
+                                                              *rg_rollback_seg
+                                                              !( $','
+                                                                 *rg_push_deferred_rpc
+                                                                 !( $','
+                                                                    *rg_refresh_after_errors
+                                                                    !( $','
+                                                                       *rg_purge_option
+                                                                       !($',' *rg_parallelism !($',' *rg_heap_size))
+                                                                    )
+                                                                 )
+                                                              )
+                                                           )
+                                                        )
+                                                     )
+                                                  )
            create_role                         =  CREATE
+                                                  ROLE
+                                                  *role_name
+                                                  !( NOT IDENTIFIED
+                                                  |  IDENTIFIED (BY *password | EXTERNALLY | GLOBALLY)
+                                                  )
            create_rollback_segment             =  CREATE
+                                                  !PUBLIC
+                                                  ROLLBACK
+                                                  SEGMENT
+                                                  *object_name
+                                                  *create_rollback_segment_2
            create_rollback_segment_2           =  !( *create_rollback_segment_2
+                                                     (TABLESPACE *object_name | *storage_clause)
+                                                  )
            alter_sequence                      =  ALTER SEQUENCE *object !%*alter_sequence_spec
            alter_sequence_spec                 =  INCREMENT BY *integer
+                                               |  NOMAXVALUE
+                                               |  MAXVALUE *integer
+                                               |  NOMINVALUE
+                                               |  MINVALUE *integer
+                                               |  CYCLE
+                                               |  NOCYCLE
+                                               |  CACHE *integer
+                                               |  NOCACHE
+                                               |  ORDER
+                                               |  NOORDER
            create_sequence                     =  CREATE SEQUENCE *object !%*create_sequence_spec
            create_sequence_spec                =  INCREMENT BY *integer
+                                               |  START WITH *integer
+                                               |  NOMAXVALUE
+                                               |  MAXVALUE *integer
+                                               |  NOMINVALUE
+                                               |  MINVALUE *integer
+                                               |  CYCLE
+                                               |  NOCYCLE
+                                               |  CACHE *integer
+                                               |  NOCACHE
+                                               |  ORDER
+                                               |  NOORDER
            integer                             =  $'_NUMBER_' | $'-' $'_NUMBER_' | $'_REAL_' | $'-' $'_REAL_'
            materialized_view_snapshot          =  MATERIALIZED VIEW | SNAPSHOT
            create_snapshot                     =  CREATE
+                                                  *materialized_view_snapshot
+                                                  *object
+                                                  !%( *physical_attribute_clause
+                                                  |  TABLESPACE *object_name
+                                                  |  LOGGING
+                                                  |  NOLOGGING
+                                                  |  CACHE
+                                                  |  NOCACHE
+                                                  )
+                                                  !*parallel_clause
+                                                  !*partitioning_clauses
+                                                  !*snapshot_cluster_spec
+                                                  !( USING
+                                                     INDEX
+                                                     (TABLESPACE *object_name | *physical_attributes_clause)
+                                                  )
+                                                  !( REFRESH
+                                                     !(FORCE | FAST | COMPLETE)
+                                                     !(START WITH *expr)
+                                                     !(NEXT *expr)
+                                                     !(USING *create_snapshot_use_options)
+                                                     !(WITH (PRIMARY KEY | ROWID))
+                                                  )
+                                                  !(FOR UPDATE)
+                                                  !(ENABLE QUERY REWRITE | DISABLE QUERY REWRITE)
+                                                  AS *subquery
            snapshot_cluster_spec               =  CLUSTER *object $'(' *column_list $')'
            create_snapshot_use_options         =  %*create_snapshot_use_option
            create_snapshot_use_option          =  DEFAULT *database_type ROLLBACK SEGMENT
+                                               |  *database_type ROLLBACK SEGMENT *object_name
            database_type                       =  !(MASTER | LOCAL)
            create_snapshot_log                 =  CREATE
+                                                  *materialized_view_snapshot
+                                                  LOG
+                                                  ON
+                                                  *object
+                                                  !%( *physical_attribute_clause
+                                                  |  TABLESPACE *object_name
+                                                  |  LOGGING
+                                                  |  NOLOGGING
+                                                  |  CACHE
+                                                  |  NOCACHE
+                                                  )
+                                                  !*parallel_clause
+                                                  !*partitioning_clauses
+                                                  !(WITH *rowid_primarykey *snapshot_filter_columns)
+                                                  !(INCLUDING NEW VALUES | EXCLUDING NEW VALUES)
            rowid_primarykey                    =  !( PRIMARY KEY
+                                                  |  ROWID
+                                                  |  PRIMARY KEY $',' ROWID
+                                                  |  ROWID $',' PRIMARY KEY
+                                                  )
            snapshot_filter_columns             =  !($'(' *common_column_list $')')
            create_synonym                      =  CREATE !PUBLIC SYNONYM *object FOR *object !($'@' *dblink)
            number_sign                         =  !($'-' | $'+')
            number_value                        =  $'_NUMBER_' | $'_REAL_'
            value                               =  *number_sign *number_value
+                                               |  MAXVALUE
+                                               |  $'_SQ_STRING_'
+                                               |  TO_DATE $'(' $'_SQ_STRING_' $',' $'_SQ_STRING_' $')'
+                                               |  TO_DATE
+                                                  $'('
+                                                  $'_SQ_STRING_'
+                                                  $','
+                                                  $'_SQ_STRING_'
+                                                  $','
+                                                  $'_SQ_STRING_'
+                                                  $')'
            value_list                          =  *value % $','
            compression_clause                  =  COMPRESS *optional_n | NOCOMPRESS
            optional_n                          =  !*n
            create_tablespace                   =  CREATE
+                                                  TABLESPACE
+                                                  *object_name
+                                                  !(DATAFILE (*filespec !*autoextend_clause) % $',')
+                                                  *create_tablespace_2
            create_tablespace_2                 =  !( *create_tablespace_2
+                                                     (  ONLINE
+                                                     |  OFFLINE
+                                                     |  PERMANENT
+                                                     |  TEMPORARY
+                                                     |  NOLOGGING
+                                                     |  LOGGING
+                                                     |  MINIMUM EXTENT *n_bytes
+                                                     |  DEFAULT *storage_clause
+                                                     |  *extent_management_clause
+                                                     )
+                                                  )
            extent_management_clause            =  EXTENT
+                                                  MANAGEMENT
+                                                  (  DICTIONARY
+                                                  |  LOCAL !(AUTOALLOCATE | UNIFORM | UNIFORM SIZE *n_bytes)
+                                                  )
            create_trigger                      =  CREATE
+                                                  *or_replace
+                                                  TRIGGER
+                                                  *object
+                                                  (BEFORE | AFTER | INSTEAD OF)
+                                                  *create_trigger_2_1 ON *database_object
+                                                  *referencing_clause
+                                                  !(WHEN $'(' *condition $')')
+                                                  (*call | *plsql_begin *plsql_block)
            create_trigger_2_1                  =  *create_trigger_2_1_1 | *create_trigger_2_1 OR *create_trigger_2_1_1
            create_trigger_2_1_1                =  DELETE
+                                               |  INSERT
+                                               |  UPDATE !(OF *trigger_column_list)
+                                               |  CREATE
+                                               |  ALTER
+                                               |  DROP
+                                               |  SERVERERROR
+                                               |  LOGON
+                                               |  LOGOFF
+                                               |  STARTUP
+                                               |  SHUTDOWN
            trigger_column_list                 =  *identifier % $','
            referencing_clause                  =  !( REFERENCING
+                                                     %(OLD *optional_as *identifier | NEW *optional_as *identifier)
+                                                  )
+                                                  !(FOR EACH ROW)
            optional_as                         =  !AS
            database_object                     =  *object
            create_user                         =  CREATE
+                                                  USER
+                                                  *object_name
+                                                  IDENTIFIED
+                                                  (BY *password | EXTERNALLY)
+                                                  *create_user_2
            create_user_2                       =  !(*create_user_2 *create_user_spec)
            create_user_spec                    =  DEFAULT TABLESPACE *object_name
+                                               |  TEMPORARY TABLESPACE *object_name
+                                               |  QUOTA (*n_bytes | UNLIMITED) ON *object_name
+                                               |  PROFILE *profile_name
+                                               |  DEFAULT ROLE
+                                               |  PASSWORD EXPIRE
+                                               |  ACCOUNT LOCK
+                                               |  ACCOUNT UNLOCK
+                                               |  DEFAULT
+                                                  ROLE
+                                                  (  *create_user_spec_2_1
+                                                  |  ALL
+                                                  |  ALL EXCEPT *create_user_spec_2_1
+                                                  |  NONE
+                                                  )
            create_user_spec_2_1                =  *role_name % $','
            alter_session                       =  ALTER
+                                                  SESSION
+                                                  (  ADVISE (COMMIT | ROLLBACK | NOTHING)
+                                                  |  CLOSE DATABASE LINK *dblink
+                                                  |  (ENABLE | DISABLE) COMMIT IN PROCEDURE
+                                                  |  (ENABLE | DISABLE | FORCE)
+                                                     PARALLEL
+                                                     (DML | DDL)
+                                                     !(PARALLEL $'_NUMBER_')
+                                                  |  *set_clause
+                                                  )
            alter_user                          =  ALTER
+                                                  USER
+                                                  (  *object_name
+                                                     %( IDENTIFIED (BY *password | EXTERNALLY | GLOBALLY AS *id)
+                                                     |  DEFAULT TABLESPACE *object_name
+                                                     |  TEMPORARY TABLESPACE *object_name
+                                                     |  QUOTA (UNLIMITED | *n_bytes) ON *object_name
+                                                     |  PROFILE *profile_name
+                                                     |  DEFAULT
+                                                        ROLE
+                                                        (  *alter_user_1_1_3_1
+                                                        |  ALL
+                                                        |  ALL EXCEPT *alter_user_1_1_3_1
+                                                        |  NONE
+                                                        )
+                                                     |  PASSWORD EXPIRE
+                                                     |  ACCOUNT (LOCK | UNLOCK)
+                                                     )
+                                                  |  *object_name % $',' *proxy_clause
+                                                  )
            alter_user_1_1_3_1                  =  *role_name % $','
            parameter_value                     =  *id | $'_SQ_STRING_' | $'_NUMBER_' | REAL
            proxy_clause                        =  (GRANT | REVOKE)
+                                                  CONNECT
+                                                  THROUGH
+                                                  *id
+                                                  !(WITH (ROLE !(ALL EXCEPT) *role_name % $',' | NONE))
            alter_snapshot                      =  ALTER
+                                                  *materialized_view_snapshot
+                                                  *object
+                                                  !( *physical_attributes_clause
+                                                  |  *LOB_storage_clause % $','
+                                                  |  *modify_LOB_storage_clause % $','
+                                                  |  *partitioning_clauses
+                                                  |  *parallel_clause
+                                                  |  LOGGING
+                                                  |  NOLOGGING
+                                                  |  CACHE
+                                                  |  NOCACHE
+                                                  )
+                                                  !(USING INDEX *physical_attributes_clause)
+                                                  !*refresh_clause
+                                                  !(COMPILE | ENABLE QUERY REWRITE | DISABLE QUERY REWRITE)
            refresh_clause                      =  REFRESH
+                                                  %( FAST
+                                                  |  COMPLETE
+                                                  |  FORCE
+                                                  |  ON DEMAND
+                                                  |  ON COMMIT
+                                                  |  START WITH *expr
+                                                  |  NEXT *expr
+                                                  |  WITH PRIMARY KEY
+                                                  |  USING
+                                                     (  DEFAULT MASTER ROLLBACK SEGMENT
+                                                     |  MASTER ROLLBACK SEGMENT *object_name
+                                                     )
+                                                  )
            alter_snapshot_log                  =  ALTER
+                                                  *materialized_view_snapshot
+                                                  LOG
+                                                  ON
+                                                  *object
+                                                  !%( *physical_attribute_clause
+                                                  |  *partitioning_clauses
+                                                  |  *parallel_clause
+                                                  |  LOGGING
+                                                  |  NOLOGGING
+                                                  |  CACHE
+                                                  |  NOCACHE
+                                                  )
+                                                  !(ADD (PRIMARY KEY | ROWID) !*common_column_list)
+                                                  !(INCLUDING NEW VALUES | EXCLUDING NEW VALUES)
            create_view                         =  CREATE
+                                                  *or_replace
+                                                  !(FORCE | NOFORCE)
+                                                  VIEW
+                                                  *object
+                                                  !( $'(' *alias % $',' $')'
+                                                  |  OF
+                                                     *object
+                                                     !( WITH
+                                                        OBJECT
+                                                        (IDENTIFIER | OID)
+                                                        !(DEFAULT | $'(' *id % $',' $')')
+                                                     )
+                                                  )
+                                                  AS
+                                                  *subquery
+                                                  !*with_clause
            create_index                        =  CREATE
+                                                  !(UNIQUE | BITMAP)
+                                                  INDEX
+                                                  *object
+                                                  ON
+                                                  (*cluster_index_clause | *table_index_clause)
            cluster_index_clause                =  CLUSTER *object *index_attributes
            table_index_clause                  =  *object
+                                                  *optional_alias
+                                                  $'('
+                                                  (*index_expr_list !(ASC | DESC)) % $','
+                                                  $')'
+                                                  (  *domain_index_clause
+                                                  |  *table_index_clause_2_1
+                                                     !(*global_index_clause | *local_index_clause)
+                                                     *table_index_clause_2_1
+                                                  )
            table_index_clause_2_1              =  !*index_attributes
            index_attributes                    =  !%*index_attribute
            index_attribute                     =  *physical_attribute_clause
+                                               |  ONLINE
+                                               |  COMPUTE STATISTICS
+                                               |  NOSORT
+                                               |  REVERSE
+                                               |  *parallel_clause
+                                               |  LOGGING
+                                               |  NOLOGGING
+                                               |  TABLESPACE *object_name
+                                               |  TABLESPACE DEFAULT
+                                               |  COMPRESS *n
+                                               |  NOCOMPRESS
            index_expr_list                     =  *object_name | expr
            domain_index_clause                 =  INDEXTYPE IS *object_name !(PARAMETERS $'(' $'_SQ_STRING_' $')')
            global_index_clause                 =  GLOBAL
+                                                  PARTITION
+                                                  BY
+                                                  RANGE
+                                                  $'('
+                                                  *column_list
+                                                  $')'
+                                                  $'('
+                                                  *global_partition_clause % $','
+                                                  $')'
            global_partition_clause             =  PARTITION
+                                                  !*partition
+                                                  VALUES
+                                                  LESS
+                                                  THAN
+                                                  $'('
+                                                  *value_list
+                                                  $')'
+                                                  !%( *physical_attribute_clause
+                                                  |  TABLESPACE *object_name
+                                                  |  LOGGING
+                                                  |  NOLOGGING
+                                                  )
            local_index_clause                  =  LOCAL
+                                                  (  *on_range_partitioned_table_clause
+                                                  |  *on_composite_partitioned_table_clause
+                                                  |  epsilon
+                                                  )
            on_range_partitioned_table_clause   =  $'('
+                                                  (PARTITION !(*partition !*segment_attributes_clause)) % $','
+                                                  $')'
            store_in_default_tablespace_list    =  STORE IN $'(' (DEFAULT | *object_name % $',') $')'
            on_composite_partitioned_table_clause = *store_in_default_tablespace_list
+                                                  *on_composite_partitioned_table_clause_1
+                                               |  *on_composite_partitioned_table_clause_1
            on_composite_partitioned_table_clause_1 = $'('
+                                                  (  PARTITION
+                                                     !( *partition
+                                                        !*segment_attributes_clause
+                                                        !*index_subpartition_clause
+                                                     )
+                                                  ) % $','
+                                                  $')'
            index_subpartition_clause           =  *store_in_default_tablespace_list
+                                               |  $'('
+                                                  (SUBPARTITION !(*subpartition !(TABLESPACE *object_name))) % $','
+                                                  $')'
            create_cluster                      =  CREATE
+                                                  CLUSTER
+                                                  *object
+                                                  $'('
+                                                  (*identifier *datatype) % $','
+                                                  $')'
+                                                  !%( *parallel_clause
+                                                  |  CACHE
+                                                  |  NOCACHE
+                                                  |  *physical_attribute_clause
+                                                  |  SIZE *n_bytes
+                                                  |  TABLESPACE *object_name
+                                                  |  INDEX
+                                                  |  !(SINGLE TABLE) HASHKEYS *n
+                                                  |  HASH IS *expr
+                                                  )
            create_table                        =  CREATE
+                                                  !(GLOBAL TEMPORARY)
+                                                  TABLE
+                                                  *object
+                                                  (*relational_table | *object_table)
            alter_table                         =  ALTER
+                                                  TABLE
+                                                  *object
+                                                  !( %( ADD
+                                                        *add_column_options
+                                                        *alter_table_add_column_options_1
+                                                        *alter_table_add_column_options_2
+                                                     |  ADD
+                                                        $'('
+                                                        *add_column_options
+                                                        $')'
+                                                        *alter_table_add_column_options_1
+                                                        *alter_table_add_column_options_2
+                                                     |  MODIFY *modify_column_option
+                                                     |  MODIFY $'(' *modify_column_options $')'
+                                                     |  *move_table_clause
+                                                     |  *physical_attribute_clause
+                                                     |  LOGGING
+                                                     |  NOLOGGING
+                                                     |  *modify_collection_retrieval_clause
+                                                     |  *storage_clauses
+                                                     |  MODIFY CONSTRAINT *constraint_name *constraint_state
+                                                     |  *drop_constraint_clause
+                                                     |  *drop_column_clause
+                                                     |  *allocate_extent_clause
+                                                     |  *deallocate_unused_clause
+                                                     |  CACHE
+                                                     |  NOCACHE
+                                                     |  MONITORING
+                                                     |  NOMONITORING
+                                                     )
+                                                  |  RENAME TO *object
+                                                  |  *records_per_block_clause
+                                                  |  *alter_overflow_clause
+                                                  |  *partitioning_clauses
+                                                  )
+                                                  !*parallel_clause
+                                                  !%( *enable_disable_clause
+                                                  |  (ENABLE | DISABLE) (TABLE LOCK | ALL TRIGGERS)
+                                                  )
            alter_table_add_column_options_1    =  !*LOB_storage_clause
            alter_table_add_column_options_2    =  !($'(' *partition_LOB_storage_clause % $',' $')')
            storage_clause                      =  STORAGE *storage_clause_1 | STORAGE $'(' *storage_clause_1 $')'
            storage_clause_1                    =  %*storage_spec
            storage_spec                        =  INITIAL *n_bytes
+                                               |  NEXT *n_bytes
+                                               |  MINEXTENTS *n
+                                               |  MAXEXTENTS *n
+                                               |  MAXEXTENTS UNLIMITED
+                                               |  PCTINCREASE *n
+                                               |  FREELISTS *n
+                                               |  FREELIST GROUPS *n
+                                               |  OPTIMAL NULL
+                                               |  OPTIMAL *n_bytes
+                                               |  BUFFER_POOL KEEP
+                                               |  BUFFER_POOL RECYCLE
+                                               |  BUFFER_POOL DEFAULT
            parallel_clause                     =  NOPARALLEL
+                                               |  PARALLEL
+                                                  !( *n
+                                                  |  $'('
+                                                     !( *degree_spec
+                                                     |  *inst_spec
+                                                     |  *degree_spec *inst_spec
+                                                     |  *inst_spec *degree_spec
+                                                     )
+                                                     $')'
+                                                  )
            degree_spec                         =  DEGREE *n | DEGREE DEFAULT
            inst_spec                           =  INSTANCES *n | INSTANCES DEFAULT
            LOB_parameters                      =  *LOB_parameter
+                                               |  *LOB_parameters *LOB_parameter
+                                               |  *LOB_parameters *storage_clause
            LOB_parameter                       =  TABLESPACE *object_name
+                                               |  TABLESPACE DEFAULT
+                                               |  CHUNK $'_NUMBER_'
+                                               |  PCTVERSION $'_NUMBER_'
+                                               |  CACHE
+                                               |  NOCACHE
+                                               |  ENABLE *LOB_parameter_1
+                                               |  DISABLE *LOB_parameter_1
+                                               |  LOGGING
+                                               |  NOLOGGING
            LOB_parameter_1                     =  STORAGE IN ROW
            LOB_storage_clause                  =  LOB
+                                                  $'('
+                                                  *LOB_item % $','
+                                                  $')'
+                                                  STORE
+                                                  AS
+                                                  (  $'(' *LOB_parameters $')'
+                                                  |  *object_name $'(' *LOB_parameters $')'
+                                                  |  *object_name
+                                                  )
            OID_clause                          =  OBJECT IDENTIFIER IS (SYSTEM GENERATED | PRIMARY KEY)
            OID_index_clause                    =  OIDINDEX
+                                                  !*object
+                                                  $'('
+                                                  %(*physical_attribute_clause | TABLESPACE *object_name)
+                                                  $')'
            add_column_options                  =  (  *identifier
+                                                     *datatype
+                                                     !(DEFAULT *expr)
+                                                     !*column_ref_constraint
+                                                     !%*column_constraint
+                                                  |  *table_constraint
+                                                  |  *table_ref_constraint
+                                                  ) % $','
            add_hash_partition_clause           =  ADD
+                                                  PARTITION
+                                                  !( *partition
+                                                     !(TABLESPACE *object_name)
+                                                     !%(*LOB_storage_clause | *varray_storage_clause)
+                                                     !*parallel_clause
+                                                  )
            add_overflow_clause                 =  ADD
+                                                  OVERFLOW
+                                                  !*segment_attributes_clause
+                                                  !($'(' PARTITION *segment_attributes_clause % $',' $')')
            add_range_partition_clause          =  ADD
+                                                  PARTITION
+                                                  !*partition
+                                                  VALUES
+                                                  LESS
+                                                  THAN
+                                                  $'('
+                                                  *value_list
+                                                  $')'
+                                                  !*partition_description
            add_subpartition_clause             =  ADD SUBPARTITION !(*subpartition *subpartition_description)
            allocate_extent_clause              =  ALLOCATE
+                                                  EXTENT
+                                                  !( $'('
+                                                     %(SIZE *n_bytes | DATAFILE *filename | INSTANCE $'_NUMBER_')
+                                                     $')'
+                                                  )
            alter_overflow_clause               =  %(PCTTHRESHOLD $'_NUMBER_' | INCLUDING *identifier)
+                                               |  *overflow_clause
+                                               |  *add_overflow_clause
            coalesce_partition_clause           =  COALESCE PARTITION !*parallel_clause
            collection_expression               =  *subquery | *object_name | *expr
            collection_item                     =  *id $'.' *id
            column_constraint                   =  *optional_constraint_name
+                                                  (  UNIQUE
+                                                  |  PRIMARY KEY
+                                                  |  NOT NULL
+                                                  |  NULL
+                                                  |  REFERENCES
+                                                     *object
+                                                     !($'(' *id $')')
+                                                     !(ON DELETE (CASCADE | SET NULL))
+                                                  |  CHECK $'(' *condition $')'
+                                                  )
+                                                  *constraint_state
            column_ref_constraint               =  SCOPE IS *object
+                                               |  WITH ROWID
+                                               |  *optional_constraint_name *references_clause
            composite_partitioning_clause       =  PARTITION
+                                                  BY
+                                                  RANGE
+                                                  $'('
+                                                  *column_list
+                                                  $')'
+                                                  !*subpartition_clause
+                                                  $'('
+                                                  *partition_definition % $','
+                                                  $')'
            constraint_state                    =  !( *constraint_state_1_1
+                                                  |  *constraint_state_1_2
+                                                  |  *constraint_state_1_1 *constraint_state_1_2
+                                                  |  *constraint_state_1_2 *constraint_state_1_1
+                                                  )
+                                                  !(RELY | NORELY)
+                                                  !*using_index_clause
+                                                  !(ENABLE | DISABLE)
+                                                  !(VALIDATE | NOVALIDATE)
+                                                  !(EXCEPTIONS INTO *object)
            constraint_state_1_1                =  INITIALLY IMMEDIATE | INITIALLY DEFERRED
            constraint_state_1_2                =  NOT DEFERRABLE | DEFERRABLE
            deallocate_unused_clause            =  DEALLOCATE UNUSED !(KEEP *n_bytes)
            drop_column_clause                  =  SET
+                                                  UNUSED
+                                                  (COLUMN *id | $'(' *id % $',' $')')
+                                                  !%(CASCADE CONSTRAINTS | INVALIDATE)
+                                               |  DROP
+                                                  (COLUMN *id | $'(' *id % $',' $')')
+                                                  !%(CASCADE CONSTRAINTS | INVALIDATE)
+                                                  !(CHECKPOINT $'_NUMBER_')
+                                               |  DROP (UNUSED COLUMNS | COLUMNS CONTINUE) !(CHECKPOINT $'_NUMBER_')
            drop_constraint_clause              =  DROP
+                                                  (  CONSTRAINT *constraint_name
+                                                  |  PRIMARY KEY
+                                                  |  UNIQUE $'(' *id % $',' $')'
+                                                  )
+                                                  !CASCADE
            drop_partition_clause               =  DROP PARTITION *partition
            enable_disable_clause               =  (ENABLE | DISABLE)
+                                                  !(VALIDATE | NOVALIDATE)
+                                                  (  UNIQUE $'(' *id % $',' $')'
+                                                  |  PRIMARY KEY
+                                                  |  CONSTRAINT *constraint_name
+                                                  )
+                                                  !*using_index_clause
+                                                  !(EXCEPTIONS INTO *object)
+                                                  !CASCADE
            exchange_partition_or_subpartition_clause = EXCHANGE
+                                                  (PARTITION *partition | SUBPARTITION *subpartition)
+                                                  WITH
+                                                  TABLE
+                                                  *object
+                                                  !((INCLUDING | EXCLUDING) INDEXES)
+                                                  !((WITH | WITHOUT) VALIDATION)
+                                                  !(EXCEPTIONS INTO *object)
            for_update_clause                   =  FOR
+                                                  UPDATE
+                                                  !(OF (*id $'.' *id | *id $'.' *id $'.' *id) % $',')
+                                                  !NOWAIT
            foreign_key_clause                  =  FOREIGN
+                                                  KEY
+                                                  $'('
+                                                  *column_list
+                                                  $')'
+                                                  REFERENCES
+                                                  *object
+                                                  !($'(' *identifier % $',' $')')
+                                                  !(ON DELETE (CASCADE | SET NULL))
            hash_partitioning_clause            =  PARTITION
+                                                  BY
+                                                  HASH
+                                                  $'('
+                                                  *column_list
+                                                  $')'
+                                                  !( PARTITIONS $'_NUMBER_' *store_in_tablespace_list
+                                                  |  $'('
+                                                     (PARTITION !(*partition *partitioning_storage_clause)) % $','
+                                                     $')'
+                                                  )
            index_organized_overflow_clause     =  !(INCLUDING *identifier) OVERFLOW !*segment_attributes_clause
            index_organized_table_clause        =  !( !%( *segment_attribute_clause
+                                                     |  PCTTHRESHOLD $'_NUMBER_'
+                                                     |  *compression_clause
+                                                     )
+                                                     !*index_organized_overflow_clause
+                                                  )
            merge_partitions_clause             =  MERGE
+                                                  PARTITIONS
+                                                  *partition
+                                                  $','
+                                                  *partition
+                                                  !(INTO PARTITION !(*partition *subpartition_description))
            modify_LOB_storage_clause           =  MODIFY
+                                                  LOB
+                                                  $'('
+                                                  *LOB_item
+                                                  $')'
+                                                  $'('
+                                                  *modify_LOB_storage_parameters
+                                                  $')'
            modify_LOB_storage_parameters       =  %( *storage_clause
+                                                  |  PCTVERSION $'_NUMBER_'
+                                                  |  CACHE
+                                                  |  NOCACHE (LOGGING | NOLOGGING)
+                                                  |  *allocate_extent_clause
+                                                  |  *deallocate_unused_clause
+                                                  )
            modify_collection_retrieval_clause  =  MODIFY NESTED TABLE *collection_item RETURN AS (LOCATOR | VALUE)
            modify_column_options               =  *modify_column_option % $','
            modify_column_option                =  *identifier !*datatype !(DEFAULT *expr) !%*column_constraint
+                                               |  (NESTED TABLE | VARRAY)
+                                                  *collection_item
+                                                  !(RETURN AS (LOCATOR | VALUE))
            modify_default_attributes_clause    =  MODIFY
+                                                  DEFAULT
+                                                  ATTRIBUTES
+                                                  !(FOR PARTITION *partition)
+                                                  !*segment_attributes_clause
+                                                  !(PCTTHRESHOLD $'_NUMBER_')
+                                                  !(COMPRESS | NOCOMPRESS)
+                                                  !*overflow_clause
+                                                  !%(LOB *LOB_item *LOB_parameters)
            modify_partition_clause             =  MODIFY
+                                                  PARTITION
+                                                  *partition
+                                                  (  *partition_attributes
+                                                  |  *add_subpartition_clause
+                                                  |  COALESCE SUBPARTITION !*parallel_clause
+                                                  |  !REBUILD UNUSABLE LOCAL INDEXES
+                                                  )
            modify_subpartition_clause          =  MODIFY
+                                                  SUBPARTITION
+                                                  *subpartition
+                                                  (  *allocate_extent_clause
+                                                  |  *deallocate_unused_clause
+                                                  |  %(LOB *LOB_item *modify_LOB_storage_parameters)
+                                                  |  !REBUILD UNUSABLE LOCAL INDEXES
+                                                  )
            modify_varray_storage_clause        =  MODIFY VARRAY *id !*modify_LOB_storage_parameters
            move_partition_clause               =  MOVE PARTITION *partition *partition_description !*parallel_clause
            move_subpartition_clause            =  MOVE SUBPARTITION *subpartition *subpartition_description
            move_table_clause                   =  MOVE !ONLINE *index_organized_table_clause !%*LOB_storage_clause
            nested_table_storage_clause         =  NESTED
+                                                  TABLE
+                                                  *id
+                                                  STORE
+                                                  AS
+                                                  *object
+                                                  !($'(' $'(' *object_properties $')' *physical_properties $')')
+                                                  !(RETURN AS (LOCATOR | VALUE))
            object_properties                   =  *id !(DEFAULT *expr) !*column_ref_constraint !%*column_constraint
+                                               |  *table_constraint
+                                               |  *table_ref_constraint
            object_table                        =  OF
+                                                  *object
+                                                  !($'(' *object_properties $')')
+                                                  !(ON COMMIT (DELETE | PRESERVE) ROWS)
+                                                  !*OID_clause
+                                                  !*OID_index_clause
+                                                  *physical_properties
+                                                  *table_properties
            optional_constraint_name            =  !(CONSTRAINT *constraint_name)
            overflow_clause                     =  OVERFLOW
+                                                  %( *physical_attribute_clause
+                                                  |  *allocate_extent_clause
+                                                  |  *deallocate_unused_clause
+                                                  |  LOGGING
+                                                  |  NOLOGGING
+                                                  )
            partition_LOB_storage_clause        =  PARTITION
+                                                  *partition
+                                                  %*LOB_storage_clause
+                                                  !($'(' SUBPARTITION *subpartition %*LOB_storage_clause $')')
            partition_attributes                =  !%( *physical_attribute_clause
+                                                  |  LOGGING
+                                                  |  NOLOGGING
+                                                  |  *allocate_extent_clause
+                                                  |  *deallocate_unused_clause
+                                                  )
+                                                  !(OVERFLOW *physical_attributes_clause)
+                                                  !%(LOB *LOB_item *modify_LOB_storage_parameters)
            partition_definition                =  PARTITION
+                                                  !*partition
+                                                  VALUES
+                                                  LESS
+                                                  THAN
+                                                  $'('
+                                                  *value_list
+                                                  $')'
+                                                  !%(*segment_attribute_clause | COMPRESS | NOCOMPRESS)
+                                                  !(OVERFLOW !*segment_attributes_clause)
+                                                  !%(*LOB_storage_clause | *varray_storage_clause)
+                                                  !*partition_level_subpartitioning
            partition_description               =  !*segment_attributes_clause
+                                                  !*compression_clause
+                                                  !(OVERFLOW !*segment_attributes_clause)
+                                                  !%(*LOB_storage_clause | *varray_storage_clause)
+                                                  !*partition_level_subpartitioning
            partition_level_subpartitioning     =  !(SUBPARTITIONS $'_NUMBER_') *store_in_tablespace_list
+                                               |  $'('
+                                                  (SUBPARTITION !(*subpartition *partitioning_storage_clause)) % $','
+                                                  $')'
            partitioning_clauses                =  *modify_default_attributes_clause
+                                               |  *modify_partition_clause
+                                               |  *modify_subpartition_clause
+                                               |  *move_partition_clause
+                                               |  *move_subpartition_clause
+                                               |  *add_range_partition_clause
+                                               |  *add_hash_partition_clause
+                                               |  *coalesce_partition_clause
+                                               |  *drop_partition_clause
+                                               |  *rename_partition_or_subpartition_clause
+                                               |  *truncate_partition_or_subpartition_clause
+                                               |  *split_partition_clause
+                                               |  *merge_partitions_clause
+                                               |  *exchange_partition_or_subpartition_clause
+                                               |  *row_movement_clause
            partitioning_storage_clause         =  !(TABLESPACE *object_name)
+                                                  !%(*LOB_storage_clause | *varray_storage_clause)
            physical_attributes_clause          =  !%*physical_attribute_clause
            physical_attribute_clause           =  *storage_clause
+                                               |  PCTFREE $'_NUMBER_'
+                                               |  PCTUSED $'_NUMBER_'
+                                               |  INITRANS $'_NUMBER_'
+                                               |  MAXTRANS $'_NUMBER_'
            physical_properties                 =  !( *segment_attributes_clause
+                                                  |  ORGANIZATION
+                                                     (  HEAP !*segment_attributes_clause
+                                                     |  INDEX *index_organized_table_clause
+                                                     )
+                                                  |  CLUSTER *object $'(' *identifier % $',' $')'
+                                                  )
+                                                  !%( *LOB_storage_clause
+                                                  |  *varray_storage_clause
+                                                  |  *nested_table_storage_clause
+                                                  )
            records_per_block_clause            =  (MINIMIZE | NOMINIMIZE) RECORDS_PER_BLOCK
            references_clause                   =  REFERENCES
+                                                  *object
+                                                  !(ON DELETE (CASCADE | SET NULL))
+                                                  *constraint_state
            relational_properties               =  *relational_properties_
            relational_properties_              =  (  *identifier
+                                                     *datatype
+                                                     !(DEFAULT *expr)
+                                                     !*column_ref_constraint
+                                                     !%*column_constraint
+                                                  |  *table_constraint
+                                                  |  *table_ref_constraint
+                                                  ) % $','
            relational_table                    =  !($'(' *relational_properties $')')
+                                                  !(ON COMMIT (DELETE | PRESERVE) ROWS)
+                                                  *physical_properties
+                                                  *table_properties
            rename_partition_or_subpartition_clause = RENAME (PARTITION | SUBPARTITION) *id TO *id
            row_movement_clause                 =  (ENABLE | DISABLE) ROW MOVEMENT
            segment_attributes_clause           =  %*segment_attribute_clause
            segment_attribute_clause            =  *physical_attribute_clause
+                                               |  TABLESPACE *object_name
+                                               |  LOGGING
+                                               |  NOLOGGING
            split_partition_clause              =  SPLIT
+                                                  PARTITION
+                                                  *partition
+                                                  AT
+                                                  $'('
+                                                  *value_list
+                                                  $')'
+                                                  !(INTO $'(' *partition_description $',' *partition_description $')')
+                                                  !*parallel_clause
            storage_clauses                     =  *modify_LOB_storage_clause % $','
+                                               |  *varray_storage_clause % $','
+                                               |  %*modify_varray_storage_clause
+                                               |  *nested_table_storage_clause % $','
            subpartition_clause                 =  SUBPARTITION
+                                                  BY
+                                                  HASH
+                                                  $'('
+                                                  *column_list
+                                                  $')'
+                                                  !(SUBPARTITIONS $'_NUMBER_')
+                                                  *store_in_tablespace_list
            store_in_tablespace_list            =  !(STORE IN $'(' *object_name % $',' $')')
            subpartition_description            =  !(TABLESPACE *object_name)
+                                                  !%(*LOB_storage_clause | *varray_storage_clause)
+                                                  !*parallel_clause
            table_collection_expression         =  TABLE $'(' *collection_expression $')' !($'(' $'+' $')')
            table_constraint                    =  *optional_constraint_name
+                                                  (  CHECK $'(' *condition $')'
+                                                  |  *foreign_key_clause
+                                                  |  UNIQUE $'(' *column_list $')'
+                                                  |  PRIMARY KEY $'(' *column_list $')'
+                                                  )
+                                                  *constraint_state
            column_list                         =  *identifier % $','
            table_properties                    =  *table_properties_1 !(AS *subquery)
            table_properties_1                  =  !(*table_properties_1_1 | *table_properties_1 *table_properties_1_1)
            table_properties_1_1                =  *partitioning_clause
+                                               |  *segment_attribute_clause
+                                               |  CACHE
+                                               |  NOCACHE
+                                               |  MONITORING
+                                               |  NOMONITORING
+                                               |  *parallel_clause
+                                               |  %*enable_disable_clause
            partitioning_clause                 =  (*hash_partitioning_clause | *composite_partitioning_clause)
+                                                  !*row_movement_clause
            table_ref_constraint                =  SCOPE FOR $'(' *identifier $')' IS *object
+                                               |  REF $'(' *identifier $')' WITH ROWID
+                                               |  *optional_constraint_name
+                                                  FOREIGN
+                                                  KEY
+                                                  $'('
+                                                  *identifier
+                                                  $')'
+                                                  *references_clause
            truncate_partition_or_subpartition_clause = TRUNCATE
+                                                  (PARTITION *partition | SUBPARTITION *subpartition)
+                                                  !((DROP | REUSE) STORAGE)
            using_index_clause                  =  USING
+                                                  INDEX
+                                                  !%( *local_index_clause
+                                                  |  *global_index_clause
+                                                  |  PCTFREE $'_NUMBER_'
+                                                  |  INITRANS $'_NUMBER_'
+                                                  |  MAXTRANS $'_NUMBER_'
+                                                  |  TABLESPACE *object_name
+                                                  |  *storage_clause
+                                                  |  NOSORT
+                                                  |  LOGGING
+                                                  |  NOLOGGING
+                                                  )
            varray_storage_clause               =  VARRAY
+                                                  *id
+                                                  STORE
+                                                  AS
+                                                  LOB
+                                                  (  *object_name
+                                                  |  $'(' *LOB_parameters $')'
+                                                  |  *object_name $'(' *LOB_parameters $')'
+                                                  )
            expr                                =  expr | *simple_expression_id
            $'_expr'                            =  *simple_expression
+                                               |  *compound_expression
+                                               |  *variable_expression
+                                               |  *built_in_function_expression
+                                               |  *user_def_function_expression
+                                               |  *type_constructor_expression
+                                               |  *CAST_expression
+                                               |  *expression_list
            expr_list                           =  *expr % $','
            expression_list                     =  $'(' *expr_list $')'
            CAST_expression                     =  CAST
+                                                  $'('
+                                                  (*expr | $'(' *subquery $')' | MULTISET $'(' *subquery $')')
+                                                  AS
+                                                  *id
+                                                  $')'
            EXISTS_condition                    =  EXISTS $'(' *subquery $')'
            LIKE_condition                      =  *LIKE_string !NOT LIKE *LIKE_string !(ESCAPE $'_SQ_STRING_')
            LIKE_string                         =  *id | $'_SQ_STRING_'
            NULL_condition                      =  *expr IS !NOT NULL
            compound_condition                  =  $'(' *condition $')'
+                                               |  NOT *condition
+                                               |  *condition (AND | OR) *condition
            compound_expression                 =  $'(' *expr $')'
+                                               |  ($'+' | $'-' | PRIOR) *expr
+                                               |  *expr ($'*' | $'/' | $'+' | $'-' | $'_CONCAT_') *expr
            condition                           =  *simple_comparison_condition
+                                               |  *group_comparison_condition
+                                               |  *membership_condition
+                                               |  *range_condition
+                                               |  *NULL_condition
+                                               |  *EXISTS_condition
+                                               |  *LIKE_condition
+                                               |  *compound_condition
            group_comparison_condition          =  *expr
+                                                  ($'=' | $'_NEQ_' | $'_GT_' | $'_LT_' | $'_GEQ_' | $'_LEQ_')
+                                                  (ANY | SOME | ALL)
+                                                  (*expr_list | $'(' *subquery $')')
+                                               |  *expr_list
+                                                  ($'=' | $'_NEQ_')
+                                                  (ANY | SOME | ALL)
+                                                  $'('
+                                                  (*expr | *subquery) % $','
+                                                  $')'
            membership_condition                =  *expr !NOT IN (*expr_list | $'(' *subquery $')')
+                                               |  *expr_list !NOT IN $'(' (*expr | *subquery) % $',' $')'
            range_condition                     =  *expr !NOT BETWEEN *expr AND *expr
            simple_comparison_condition         =  *expr
+                                                  ($'=' | $'_NEQ_' | $'_GT_' | $'_LT_' | $'_GEQ_' | $'_LEQ_')
+                                                  (*expr | $'(' *subquery $')')
+                                               |  *expr_list ($'=' | $'_NEQ_') $'(' *subquery $')'
            simple_expression                   =  NULL | $'_REAL_' | $'_NUMBER_' | $'.' $'_NUMBER_' | $'_SQ_STRING_'
            simple_expression_id                =  !(!(*id $'.') *id $'.') *id
            type_constructor_expression         =  !(*id $'.') *id $'(' (*expr | *subquery) % $',' $')'
            built_in_function_expression        =  *function_name !($'(' ($'*' | !(DISTINCT | ALL) !*expr_list) $')')
            function_name                       =  *id | SYSDATE | USER
            user_def_function_expression        =  !%(*id $'.') *id !($'@' *id) $'(' !*expr_list $')'
            variable_expression                 =  $':' *id !(!INDICATOR $':' *id)
            hint                                =  epsilon
            alias                               =  *identifier
            constraint_name                     =  *identifier
            LOB_item                            =  *identifier
            partition                           =  *identifier
            subpartition                        =  *identifier
            directory_name                      =  *identifier
            object_name                         =  *identifier
            filename                            =  $'_SQ_STRING_'
            pathname                            =  $'_SQ_STRING_'
            profile_name                        =  *identifier | DEFAULT
            role_name                           =  *identifier | CONNECT | RESOURCE
            password                            =  *identifier
            object                              =  *identifier | *identifier $'.' *identifier
            dblink                              =  *identifier
+                                               |  *identifier $'@' *identifier
+                                               |  *identifier $'.' *database_link_domains
+                                               |  *identifier $'.' *database_link_domains $'@' *identifier
            database_link_domains               =  *identifier | *database_link_domains $'.' *identifier
            datatype                            =  RAW $'(' *n $')'
+                                               |  ROWID
+                                               |  CHAR
+                                               |  CHAR $'(' *n $')'
+                                               |  NCHAR
+                                               |  NCHAR $'(' *n $')'
+                                               |  VARCHAR2 $'(' *n $')'
+                                               |  NVARCHAR2 $'(' *n $')'
+                                               |  DATE
+                                               |  NUMBER
+                                               |  NUMBER $'(' *n $')'
+                                               |  NUMBER $'(' $'*' $')'
+                                               |  NUMBER $'(' *n $',' *n $')'
+                                               |  NUMBER $'(' $'*' $',' *n $')'
+                                               |  NUMBER $'(' *n $',' $'-' *n $')'
+                                               |  NUMBER $'(' $'*' $',' $'-' *n $')'
+                                               |  MLSLABEL
+                                               |  LONG RAW
+                                               |  LONG
+                                               |  LONG VARCHAR
+                                               |  BLOB
+                                               |  CLOB
+                                               |  NCLOB
+                                               |  BFILE
+                                               |  *ANSI_type
            ANSI_type                           =  CHARACTER
+                                               |  CHARACTER $'(' *n $')'
+                                               |  CHARACTER VARYING $'(' *n $')'
+                                               |  CHAR VARYING $'(' *n $')'
+                                               |  VARCHAR $'(' *n $')'
+                                               |  NATIONAL CHAR $'(' *n $')'
+                                               |  NATIONAL CHARACTER $'(' *n $')'
+                                               |  NATIONAL CHARACTER VARYING $'(' *n $')'
+                                               |  NATIONAL CHAR VARYING $'(' *n $')'
+                                               |  NCHAR VARYING $'(' *n $')'
+                                               |  NUMERIC
+                                               |  NUMERIC $'(' *n $')'
+                                               |  NUMERIC $'(' $'*' $')'
+                                               |  NUMERIC $'(' *n $',' *n $')'
+                                               |  NUMERIC $'(' $'*' $',' *n $')'
+                                               |  NUMERIC $'(' *n $',' $'-' *n $')'
+                                               |  NUMERIC $'(' $'*' $',' $'-' *n $')'
+                                               |  DECIMAL
+                                               |  DECIMAL $'(' *n $')'
+                                               |  DECIMAL $'(' $'*' $')'
+                                               |  DECIMAL $'(' *n $',' *n $')'
+                                               |  DECIMAL $'(' $'*' $',' *n $')'
+                                               |  DECIMAL $'(' *n $',' $'-' *n $')'
+                                               |  DECIMAL $'(' $'*' $',' $'-' *n $')'
+                                               |  DEC
+                                               |  DEC $'(' *n $')'
+                                               |  DEC $'(' $'*' $')'
+                                               |  DEC $'(' *n $',' *n $')'
+                                               |  DEC $'(' $'*' $',' *n $')'
+                                               |  DEC $'(' *n $',' $'-' *n $')'
+                                               |  DEC $'(' $'*' $',' $'-' *n $')'
+                                               |  INTEGER
+                                               |  INT
+                                               |  SMALLINT
+                                               |  FLOAT
+                                               |  FLOAT $'(' $'*' $')'
+                                               |  FLOAT $'(' *n $')'
+                                               |  REAL
+                                               |  DOUBLE PRECISION
            plsql_datatype                      =  BINARY_INTEGER
+                                               |  BOOLEAN
+                                               |  NATURAL
+                                               |  NATURALN
+                                               |  PLS_INTEGER
+                                               |  POSITIVE
+                                               |  POSITIVEN
+                                               |  RECORD
+                                               |  SIGNTYPE
+                                               |  STRING
+                                               |  TABLE
+                                               |  VARRAY
+                                               |  RAW
+                                               |  ROWID
+                                               |  CHAR
+                                               |  NCHAR
+                                               |  VARCHAR2
+                                               |  NVARCHAR2
+                                               |  DATE
+                                               |  NUMBER
+                                               |  MLSLABEL
+                                               |  LONG RAW
+                                               |  LONG
+                                               |  LONG VARCHAR
+                                               |  BLOB
+                                               |  CLOB
+                                               |  NCLOB
+                                               |  BFILE
+                                               |  CHARACTER
+                                               |  CHARACTER VARYING
+                                               |  CHAR VARYING
+                                               |  VARCHAR
+                                               |  NATIONAL CHAR
+                                               |  NATIONAL CHARACTER
+                                               |  NATIONAL CHARACTER VARYING
+                                               |  NATIONAL CHAR VARYING
+                                               |  NCHAR VARYING
+                                               |  NUMERIC
+                                               |  DECIMAL
+                                               |  DEC
+                                               |  INTEGER
+                                               |  INT
+                                               |  SMALLINT
+                                               |  FLOAT
+                                               |  REAL
+                                               |  DOUBLE PRECISION
            boolean_literal                     =  TRUE | FALSE | NULL
            id                                  =  *identifier
            identifier                          =  $'_IDENT_'
+                                               |  $'_DQ_STRING_'
+                                               |  BEGIN
+                                               |  BEGINBLOCK
+                                               |  DECLARE
+                                               |  LANGUAGE
+                                               |  identifier
+                                               |  CALL
            $'_identifier'                      =  ACCOUNT
+                                               |  ACTIVATE
+                                               |  ADMIN
+                                               |  ADVISE
+                                               |  AFTER
+                                               |  ALLOCATE
+                                               |  ALL_ROWS
+                                               |  ANALYZE
+                                               |  ARCHIVE
+                                               |  ARCHIVELOG
+                                               |  ARRAY
+                                               |  AT
+                                               |  ATTRIBUTES
+                                               |  AUTHENTICATED
+                                               |  AUTHID
+                                               |  AUTHORIZATION
+                                               |  AUTOALLOCATE
+                                               |  AUTOEXTEND
+                                               |  AUTOMATIC
+                                               |  AVG
+                                               |  BACKUP
+                                               |  BECOME
+                                               |  BEFORE
+                                               |  BFILE
+                                               |  BFILENAME
+                                               |  BINARY_INTEGER
+                                               |  BITMAP
+                                               |  BLOB
+                                               |  BLOCK
+                                               |  BODY
+                                               |  BOOLEAN
+                                               |  BUFFER_POOL
+                                               |  C
+                                               |  CACHE
+                                               |  CACHE_INSTANCES
+                                               |  CANCEL
+                                               |  CASCADE
+                                               |  CAST
+                                               |  CFILE
+                                               |  CHAINED
+                                               |  CHANGE
+                                               |  CHARACTER
+                                               |  CHAR_CS
+                                               |  CHECKPOINT
+                                               |  CHOOSE
+                                               |  CHUNK
+                                               |  CLEAR
+                                               |  CLOB
+                                               |  CLONE
+                                               |  CLOSE
+                                               |  CLOSE_CACHED_OPEN_CURSORS
+                                               |  COALESCE
+                                               |  COBOL
+                                               |  COLUMNS
+                                               |  COMMIT
+                                               |  COMMITTED
+                                               |  COMPATABILITY
+                                               |  COMPILE
+                                               |  COMPLETE
+                                               |  COMPOSITE_LIMIT
+                                               |  COMPUTE
+                                               |  CONNECT_TIME
+                                               |  CONSTRAINT
+                                               |  CONSTRAINTS
+                                               |  CONTENTS
+                                               |  CONTEXT
+                                               |  CONTINUE
+                                               |  CONTROLFILE
+                                               |  CONVERT
+                                               |  COST
+                                               |  COUNT
+                                               |  CPU_PER_CALL
+                                               |  CPU_PER_SESSION
+                                               |  CUBE
+                                               |  CURRENT_SCHEMA
+                                               |  CURRENT_USER
+                                               |  CURSOR
+                                               |  CYCLE
+                                               |  DANGLING
+                                               |  DATABASE
+                                               |  DATAFILE
+                                               |  DATAFILES
+                                               |  DATAOBJNO
+                                               |  DBA
+                                               |  DBMS_REFRESH
+                                               |  DDL
+                                               |  DEALLOCATE
+                                               |  DEC
+                                               |  DEFERRABLE
+                                               |  DEFERRED
+                                               |  DEFINER
+                                               |  DEGREE
+                                               |  DEMAND
+                                               |  DEREF
+                                               |  DESTROY
+                                               |  DETERMINISTIC
+                                               |  DICTIONARY
+                                               |  DIRECTORY
+                                               |  DISABLE
+                                               |  DISCONNECT
+                                               |  DISMOUNT
+                                               |  DISTRIBUTED
+                                               |  DML
+                                               |  DOUBLE
+                                               |  DUMP
+                                               |  EACH
+                                               |  EMPTY_BLOB
+                                               |  EMPTY_CLOB
+                                               |  ENABLE
+                                               |  END
+                                               |  ENFORCE
+                                               |  ENTRY
+                                               |  ESCAPE
+                                               |  ESTIMATE
+                                               |  EVENTS
+                                               |  EXCEPT
+                                               |  EXCEPTIONS
+                                               |  EXCHANGE
+                                               |  EXCLUDING
+                                               |  EXEC
+                                               |  EXECUTE
+                                               |  EXIT
+                                               |  EXPIRE
+                                               |  EXPLAIN
+                                               |  EXTENT
+                                               |  EXTENTS
+                                               |  EXTERNALLY
+                                               |  FAILED_LOGIN_ATTEMPTS
+                                               |  FALSE
+                                               |  FAST
+                                               |  FETCH
+                                               |  FIRST_ROWS
+                                               |  FLAGGER
+                                               |  FLUSH
+                                               |  FORCE
+                                               |  FOREIGN
+                                               |  FORTRAN
+                                               |  FOUND
+                                               |  FREELIST
+                                               |  FREELISTS
+                                               |  FULL
+                                               |  FUNCTION
+                                               |  GENERATED
+                                               |  GLOBAL
+                                               |  GLOBALLY
+                                               |  GLOBAL_NAME
+                                               |  GO
+                                               |  GOTO
+                                               |  GROUPS
+                                               |  HASH
+                                               |  HASHKEYS
+                                               |  HEADER
+                                               |  HEAP
+                                               |  IDDL_DEBUG
+                                               |  IDENTIFIER
+                                               |  IDLE_TIME
+                                               |  IF
+                                               |  INCLUDING
+                                               |  INDEXTYPE
+                                               |  INDEXED
+                                               |  INDEXES
+                                               |  INDICATOR
+                                               |  IND_PARTITION
+                                               |  INITIALLY
+                                               |  INITRANS
+                                               |  INOUT
+                                               |  INSTANCE
+                                               |  INSTANCES
+                                               |  INSTEAD
+                                               |  INT
+                                               |  INTERMEDIATE
+                                               |  INVALIDATE
+                                               |  ISOLATION
+                                               |  ISOLATION_LEVEL
+                                               |  JAVA
+                                               |  K
+                                               |  KEEP
+                                               |  KEY
+                                               |  KILL
+                                               |  LAYER
+                                               |  LESS
+                                               |  LIBRARY
+                                               |  LIMIT
+                                               |  LINK
+                                               |  LIST
+                                               |  LISTS
+                                               |  LOB
+                                               |  LOCAL
+                                               |  LOCATOR
+                                               |  LOGFILE
+                                               |  LOGGING
+                                               |  LOGICAL_READS_PER_CALL
+                                               |  LOGICAL_READS_PER_SESSION
+                                               |  LOGOFF
+                                               |  LOGON
+                                               |  LOOP
+                                               |  M
+                                               |  MAKE
+                                               |  MANAGE
+                                               |  MANAGEMENT
+                                               |  MANUAL
+                                               |  MASTER
+                                               |  MAX
+                                               |  MAXARCHLOGS
+                                               |  MAXDATAFILES
+                                               |  MAXINSTANCES
+                                               |  MAXLOGFILES
+                                               |  MAXLOGHISTORY
+                                               |  MAXLOGMEMBERS
+                                               |  MAXSIZE
+                                               |  MAXTRANS
+                                               |  MAXVALUE
+                                               |  MEMBER
+                                               |  MERGE
+                                               |  MIN
+                                               |  MINEXTENTS
+                                               |  MINIMIZE
+                                               |  MINIMUM
+                                               |  MINVALUE
+                                               |  MODULE
+                                               |  MONITORING
+                                               |  MOUNT
+                                               |  MOVE
+                                               |  MOVEMENT
+                                               |  MTS_DISPATCHERS
+                                               |  MULTISET
+                                               |  N
+                                               |  NAME
+                                               |  NATIONAL
+                                               |  NATURAL
+                                               |  NATURALN
+                                               |  NCHAR
+                                               |  NCHAR_CS
+                                               |  NCLOB
+                                               |  NEEDED
+                                               |  NESTED
+                                               |  NETWORK
+                                               |  NEW
+                                               |  NEXT
+                                               |  NLS_CALENDAR
+                                               |  NLS_CHARACTERSET
+                                               |  NLS_ISO_CURRENCY
+                                               |  NLS_LANGUAGE
+                                               |  NLS_NUMERIC_CHARACTERS
+                                               |  NLS_SORT
+                                               |  NLS_SPECIAL_CHARS
+                                               |  NLS_TERRITORY
+                                               |  NO
+                                               |  NOARCHIVELOG
+                                               |  NOCACHE
+                                               |  NOCOPY
+                                               |  NOCYCLE
+                                               |  NOFORCE
+                                               |  NOLOGGING
+                                               |  NOMAXVALUE
+                                               |  NOMINIMIZE
+                                               |  NOMINVALUE
+                                               |  NOMONITORING
+                                               |  NONE
+                                               |  NOORDER
+                                               |  NOOVERIDE
+                                               |  NOPARALLEL
+                                               |  NORELY
+                                               |  NORESETLOGS
+                                               |  NOREVERSE
+                                               |  NORMAL
+                                               |  NOSORT
+                                               |  NOTHING
+                                               |  NOVALIDATE
+                                               |  NUMERIC
+                                               |  NVARCHAR2
+                                               |  OBJECT
+                                               |  OBJNO
+                                               |  OBJNO_REUSE
+                                               |  OFF
+                                               |  OID
+                                               |  OIDINDEX
+                                               |  OLD
+                                               |  ONLY
+                                               |  OPCODE
+                                               |  OPEN
+                                               |  OPTIMAL
+                                               |  OPTIMIZER_GOAL
+                                               |  ORGANIZATION
+                                               |  OUT
+                                               |  OVERFLOW
+                                               |  OWN
+                                               |  PACKAGE
+                                               |  PARALLEL
+                                               |  PARALLEL_ENABLE
+                                               |  PARAMETERS
+                                               |  PARTITION
+                                               |  PARTITIONS
+                                               |  PASCAL
+                                               |  PASSWORD
+                                               |  PASSWORD_GRACE_TIME
+                                               |  PASSWORD_LIFE_TIME
+                                               |  PASSWORD_LOCK_TIME
+                                               |  PASSWORD_REUSE_MAX
+                                               |  PASSWORD_REUSE_TIME
+                                               |  PASSWORD_VERIFY_FUNCTION
+                                               |  PCTINCREASE
+                                               |  PCTTHRESHOLD
+                                               |  PCTUSED
+                                               |  PCTVERSION
+                                               |  PERCENT
+                                               |  PERMANENT
+                                               |  PLAN
+                                               |  PLI
+                                               |  PLS_INTEGER
+                                               |  PLSQL_DEBUG
+                                               |  POSITIVE
+                                               |  POSITIVEN
+                                               |  POST_TRANSACTION
+                                               |  PRECISION
+                                               |  PRESERVE
+                                               |  PRIMARY
+                                               |  PRIVATE
+                                               |  PRIVATE_SGA
+                                               |  PRIVILEGE
+                                               |  PROCEDURE
+                                               |  PROFILE
+                                               |  PROMPT
+                                               |  PURGE
+                                               |  QUERY
+                                               |  QUEUE
+                                               |  QUOTA
+                                               |  RANGE
+                                               |  RBA
+                                               |  READ
+                                               |  REAL
+                                               |  REBUILD
+                                               |  RECORD
+                                               |  RECORDS_PER_BLOCK
+                                               |  RECOVER
+                                               |  RECOVERABLE
+                                               |  RECOVERY
+                                               |  RECYCLE
+                                               |  REF
+                                               |  REFERENCES
+                                               |  REFERENCING
+                                               |  REFRESH
+                                               |  RELY
+                                               |  REMARK
+                                               |  REPLACE
+                                               |  RESET
+                                               |  RESETLOGS
+                                               |  RESIZE
+                                               |  RESTRICTED
+                                               |  RETURN
+                                               |  RETURNING
+                                               |  REUSE
+                                               |  REVERSE
+                                               |  REWRITE
+                                               |  ROLE
+                                               |  ROLES
+                                               |  ROLLBACK
+                                               |  ROLLUP
+                                               |  RULE
+                                               |  SAMPLE
+                                               |  SAVEPOINT
+                                               |  SCAN_INSTANCES
+                                               |  SCHEMA
+                                               |  SCN
+                                               |  SCOPE
+                                               |  SD_ALL
+                                               |  SD_INHIBIT
+                                               |  SD_SHOW
+                                               |  SECTION
+                                               |  SEGMENT
+                                               |  SEG_BLOCK
+                                               |  SEG_FILE
+                                               |  SEQUENCE
+                                               |  SERIALIZABLE
+                                               |  SERVERERROR
+                                               |  SESSIONS_PER_USER
+                                               |  SESSION_CACHED_CURSORS
+                                               |  SHARED
+                                               |  SHARED_POOL
+                                               |  SHRINK
+                                               |  SHUTDOWN
+                                               |  SIGNTYPE
+                                               |  SINGLE
+                                               |  SKIP_UNUSABLE_INDEXES
+                                               |  SNAPSHOT
+                                               |  SOME
+                                               |  SORT
+                                               |  SPECIFICATION
+                                               |  SPLIT
+                                               |  SPOOL
+                                               |  SQLCODE
+                                               |  SQLERROR
+                                               |  SQL_TRACE
+                                               |  STANDBY
+                                               |  STARTUP
+                                               |  STATEMENT_ID
+                                               |  STATISTICS
+                                               |  STOP
+                                               |  STORAGE
+                                               |  STORE
+                                               |  STRING
+                                               |  STRUCTURE
+                                               |  SUBPARTITION
+                                               |  SUBPARTITIONS
+                                               |  SUM
+                                               |  SWITCH
+                                               |  SYS
+                                               |  SYSDBA
+                                               |  SYSOPER
+                                               |  SYSTEM
+                                               |  TABLES
+                                               |  TABLESPACE
+                                               |  TABLESPACE_NO
+                                               |  TABNO
+                                               |  TEMPORARY
+                                               |  THAN
+                                               |  THE
+                                               |  THREAD
+                                               |  THROUGH
+                                               |  TIMESTAMP
+                                               |  TOPLEVEL
+                                               |  TO_DATE
+                                               |  TRACING
+                                               |  TRANSACTION
+                                               |  TRANSITIONAL
+                                               |  TRIGGERS
+                                               |  TRUE
+                                               |  TRUNCATE
+                                               |  TX
+                                               |  TYPE
+                                               |  UBA
+                                               |  UNARCHIVED
+                                               |  UNIFORM
+                                               |  UNDER
+                                               |  UNDO
+                                               |  UNLIMITED
+                                               |  UNLOCK
+                                               |  UNRECOVERABLE
+                                               |  UNTIL
+                                               |  UNUSABLE
+                                               |  UNUSED
+                                               |  USAGE
+                                               |  USE
+                                               |  USING
+                                               |  VALIDATION
+                                               |  VALUE
+                                               |  VARRAY
+                                               |  VARYING
+                                               |  WHEN
+                                               |  WHILE
+                                               |  WITHOUT
+                                               |  WORK
+                                               |  WRAPPED
+                                               |  WRITE
+                                               |  XID
            n                                   =  $'_NUMBER_'
            n_bytes                             =  *n | *n K | *n M
            or_replace                          =  !(OR REPLACE)
