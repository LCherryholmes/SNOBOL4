            DDL_commands                        =  *DDL_command $';' | *DDL_commands *DDL_command $';'
            DDL_command                         =  *alter_table
+                                               |  *comment_on_column
+                                               |  *comment_on_table
+                                               |  *create_cluster
+                                               |  *create_database_link
+                                               |  *create_function
+                                               |  *create_index
+                                               |  *create_package
+                                               |  *create_package_body
+                                               |  *create_procedure
+                                               |  *create_profile
+                                               |  *create_role
+                                               |  *create_rollback
+                                               |  *create_sequence
+                                               |  *create_synonym
+                                               |  *create_snapshot
+                                               |  *create_snapshot_log
+                                               |  *create_table
+                                               |  *create_tablespace
+                                               |  *create_trigger
+                                               |  *create_user
+                                               |  *create_view
            alias                               =  *identifier
            alias_list                          =  *alias !%($',' *alias)
            allocate_spec                       =  SIZE *n_bytes | DATAFILE *file_name | INSTANCE *n
            alter_table                         =  ALTER TABLE *table %*alter_table_spec
            alter_table_spec                    =  ADD $'(' *new_constraint_list $')'
+                                               |  ALLOCATE EXTENT !%*allocate_spec
            cluster                             =  *schema_name $'.' *cluster_name | *cluster_name
            cluster_name                        =  *identifier
            column_constraint                   =  !(CONSTRAINT *constraint_name) *def_column_constraint
            column_list                         =  *column_name !%($',' *column_name)
            column_name                         =  *identifier | CONSTRAINT | PRECISION
            comment_on_column                   =  COMMENT
+                                                  ON
+                                                  COLUMN
+                                                  (  *identifier $'.' *identifier $'.' *column_name
+                                                  |  *identifier $'.' *column_name
+                                                  )
+                                                  IS
+                                                  *SQ_STRING
            comment_on_table                    =  COMMENT
+                                                  ON
+                                                  TABLE
+                                                  (*identifier $'.' *identifier | *identifier)
+                                                  IS
+                                                  *SQ_STRING
            connect_string                      =  *SQ_STRING
            constraint_name                     =  *identifier
            create_cluster                      =  CREATE
+                                                  CLUSTER
+                                                  *cluster
+                                                  $'('
+                                                  *create_cluster_column_list
+                                                  $')'
+                                                  %*create_cluster_spec
            create_cluster_column_list          =  *column_name *datatype !%($',' *column_name *datatype)
            create_cluster_spec                 =  PCTUSED *n
+                                               |  PCTFREE *n
+                                               |  SIZE *n_bytes
+                                               |  INITRANS *n
+                                               |  MAXTRANS *n
+                                               |  TABLESPACE *tablespace_name
+                                               |  STORAGE $'(' %*storage_spec $')'
+                                               |  INDEX
+                                               |  !(HASH IS *column_name) HASHKEYS *n
            create_database_link                =  CREATE
+                                                  !PUBLIC
+                                                  DATABASE
+                                                  LINK
+                                                  *database_link_name
+                                                  !(CONNECT TO *user_name IDENTIFIED BY *password)
+                                                  USING
+                                                  *connect_string
            create_function                     =  CREATE *or_replace FUNCTION *function *function_body
            create_index                        =  CREATE
+                                                  !UNIQUE
+                                                  INDEX
+                                                  *index
+                                                  ON
+                                                  (*table $'(' *indexed_column_list $')' | CLUSTER *cluster)
+                                                  !%*index_storage
            create_package                      =  CREATE *or_replace PACKAGE *package *plsql_block
            create_package_body                 =  CREATE *or_replace PACKAGE BODY *package *plsql_block
            create_procedure                    =  CREATE *or_replace PROCEDURE *procedure *procedure_body
            create_profile                      =  CREATE PROFILE *profile_name LIMIT %*profile_spec
            create_role                         =  CREATE
+                                                  ROLE
+                                                  *role_name
+                                                  (NOT IDENTIFIED | IDENTIFIED (BY *password | EXTERNALLY))
            create_rollback                     =  CREATE
+                                                  !PUBLIC
+                                                  ROLLBACK
+                                                  SEGMENT
+                                                  *rollback_name
+                                                  !(TABLESPACE *tablespace_name)
+                                                  !(STORAGE *storage_spec)
            create_sequence                     =  CREATE SEQUENCE *sequence %*create_sequence_spec
            create_sequence_spec                =  INCREMENT BY *n
+                                               |  START WITH *n
+                                               |  MAXVALUE *n
+                                               |  NOMAXVALUE
+                                               |  MINVALUE *n
+                                               |  NOMINVALUE
+                                               |  CYCLE | NOCYCLE
+                                               |  CACHE *n
+                                               |  NOCACHE
+                                               |  ORDER | NOORDER
            create_snapshot                     =  CREATE
+                                                  SNAPSHOT
+                                                  *snapshot
+                                                  !%*table_storage
+                                                  !(CLUSTER *cluster_name $'(' *column_list $')')
+                                                  !( REFRESH
+                                                     !(FAST | COMPLETE | FORCE)
+                                                     !(START WITH *date_expression)
+                                                     !(NEXT *date_expression)
+                                                  )
+                                                  !(AS *query)
            create_snapshot_log                 =  CREATE SNAPSHOT LOG ON *snapshot !%*table_storage
            create_synonym                      =  CREATE
+                                                  !PUBLIC
+                                                  SYNONYM
+                                                  *synonym
+                                                  FOR
+                                                  *table
+                                                  !($'@' *database_link_name)
            create_table                        =  CREATE
+                                                  TABLE
+                                                  *table
+                                                  $'('
+                                                  (*new_column_list | *new_constraint_list)
+                                                  $')'
+                                                  !%*table_storage
+                                                  !(CLUSTER *cluster $'(' *column_list $')')
+                                                  !(ENABLE *enable_spec)
+                                                  !(DISABLE *disable_spec)
+                                                  !(AS *query)
            create_tablespace                   =  CREATE
+                                                  TABLESPACE
+                                                  *tablespace_name
+                                                  !(DATAFILE *file_spec_list)
+                                                  !(DEFAULT STORAGE $'(' %*storage_spec $')')
+                                                  !(ONLINE | OFFLINE)
            create_trigger                      =  CREATE
+                                                  *or_replace
+                                                  TRIGGER
+                                                  *trigger
+                                                  *trigger_sync
+                                                  *trigger_ref
+                                                  *trigger_when
+                                                  *plsql_block
            create_user                         =  CREATE
+                                                  USER
+                                                  *user_name
+                                                  IDENTIFIED
+                                                  (BY *password | EXTERNALLY)
+                                                  %*create_user_spec
            create_user_spec                    =  DEFAULT TABLESPACE *tablespace_name
+                                               |  TEMPORARY TABLESPACE *tablespace_name
+                                               |  QUOTA (*n_bytes | UNLIMITED) ON *tablespace_name
+                                               |  PROFILE *profile_name
            create_view                         =  CREATE
+                                                  *or_replace
+                                                  !(FORCE | NOFORCE)
+                                                  VIEW
+                                                  *view
+                                                  !($'(' *alias_list $')')
+                                                  AS
+                                                  *query
+                                                  !(WITH CHECK OPTION !(CONSTRAINT *constraint_name))
            database_link_name                  =  *identifier
            datatype                            =  *datatype_binary
+                                               |  *datatype_character
+                                               |  *datatype_date
+                                               |  *datatype_decimal
+                                               |  *datatype_float
+                                               |  *datatype_integer
+                                               |  MLSLABEL
            datatype_binary                     =  RAW $'(' *n $')' | ROWID | LONG RAW
            datatype_character                  =  CHAR !($'(' *n $')')
+                                               |  CHARACTER !($'(' *n $')')
+                                               |  VARCHAR $'(' *n $')'
+                                               |  VARCHAR2 $'(' *n $')'
+                                               |  CHAR VARYING $'(' *n $')'
+                                               |  CHARACTER VARYING $'(' *n $')'
+                                               |  LONG
+                                               |  LONG VARCHAR
            datatype_date                       =  DATE
            datatype_decimal                    =  NUMBER $'(' ($'*' | *n) $',' !$'-' *n $')'
+                                               |  NUMERIC !($'(' ($'*' | *n) !($',' !$'-' *n) $')')
+                                               |  DECIMAL !($'(' ($'*' | *n) !($',' !$'-' *n) $')')
+                                               |  DEC !($'(' ($'*' | *n) !($',' !$'-' *n) $')')
            datatype_float                      =  NUMBER | FLOAT !($'(' *n $')') | REAL | DOUBLE PRECISION
            datatype_integer                    =  NUMBER $'(' *n $')' | INTEGER | INT | SMALLINT
            date_expression                     =  *date_literal | NULL
            date_literal                        =  *SQ_STRING
            def_column_constraint               =  NOT NULL
+                                               |  NULL
+                                               |  UNIQUE !*def_index_constraint !*def_exceptions_constraint
+                                               |  PRIMARY KEY !*def_index_constraint !*def_exceptions_constraint
+                                               |  REFERENCES *table !($'(' *column_name $')') !(ON DELETE CASCADE)
+                                               |  CHECK $'(' *condition $')'
+                                               |  DISABLE
            def_exceptions_constraint           =  EXCEPTIONS INTO *table
            def_index_constraint                =  USING INDEX %*index_storage
            def_table_constraint                =  UNIQUE $'(' *column_list $')'
+                                               |  PRIMARY KEY $'(' *column_list $')'
+                                               |  FOREIGN
+                                                  KEY
+                                                  $'('
+                                                  *column_list
+                                                  $')'
+                                                  REFERENCES
+                                                  *table
+                                                  !($'(' *column_list $')')
+                                                  !(ON DELETE CASCADE)
+                                               |  CHECK $'(' *condition $')'
+                                               |  !*def_index_constraint !*def_exceptions_constraint
+                                               |  DISABLE
            disable_spec                        =  (UNIQUE | PRIMARY KEY | CONSTRAINT *constraint_name) !CASCADE
+                                               |  ALL TRIGGERS
            enable_spec                         =  (  UNIQUE $'(' *column_list $')'
+                                                  |  PRIMARY KEY
+                                                  |  CONSTRAINT *constraint_name
+                                                  )
+                                                  !(USING INDEX %*index_storage)
+                                                  !(EXCEPTIONS INTO *table)
+                                               |  ALL TRIGGERS
            file_name                           =  *SQ_STRING
            file_spec                           =  *file_name !(SIZE *n_bytes) !REUSE
            file_spec_list                      =  *file_spec !%($',' *file_spec)
            function                            =  *schema_name $'.' *function_name | *function_name
            function_name                       =  *identifier
            identifier                          =  *IDENT | *DQ_STRING | NEW | OLD
            index                               =  *schema_name $'.' *index_name | *index_name
            index_name                          =  *identifier
            index_storage                       =  PCTFREE *n
+                                               |  INITRANS *n
+                                               |  MAXTRANS *n
+                                               |  TABLESPACE *tablespace_name
+                                               |  STORAGE $'(' %*storage_spec $')'
+                                               |  NOSORT
+                                               |  NOPARALLEL
+                                               |  PARALLEL $'(' %*parallel_spec $')'
            indexed_column_list                 =  *column_name !(ASC | DESC) !%($',' *column_name !(ASC | DESC))
            n                                   =  *NUMBER
            n_bytes                             =  *n !(K | M)
            new_column_list                     =  *column_name
+                                                  *datatype
+                                                  !(DEFAULT *expression)
+                                                  !%*column_constraint
+                                                  !%(
+                                                     $','
+                                                     *column_name
+                                                     *datatype
+                                                     !(DEFAULT *expression)
+                                                     !%*column_constraint
+                                                  )
            new_constraint_list                 =  *table_constraint !%($',' *table_constraint)
            or_replace                          =  !(OR REPLACE)
            package                             =  *schema_name $'.' *package_name | *package_name
            package_name                        =  *identifier
            parallel_spec                       =  DEGREE *n | INSTANCES *n
            procedure                           =  *schema_name $'.' *procedure_name | *procedure_name
            procedure_name                      =  *identifier
            password                            =  *identifier
            profile_name                        =  *identifier | DEFAULT
            profile_spec                        =  *resource_name (*n | UNLIMITED | DEFAULT)
+                                               |  PRIVATE_SGA (*n_bytes | UNLIMITED | DEFAULT)
            resource_name                       =  SESSIONS_PER_USER
+                                               |  CPU_PER_SESSION
+                                               |  CPU_PER_CALL
+                                               |  CONNECT_TIME
+                                               |  IDLE_TIME
+                                               |  LOGICAL_READS_PER_SESSION
+                                               |  LOGICAL_READS_PER_CALL
+                                               |  COMPOSITE_LIMIT
            role_name                           =  *identifier
            rollback_name                       =  *identifier
            schema_name                         =  *identifier
            sequence                            =  *schema_name $'.' *sequence_name | *sequence_name
            sequence_name                       =  *identifier
            snapshot                            =  *schema_name $'.' *snapshot_name | *snapshot_name
            snapshot_name                       =  *identifier
            storage_spec                        =  INITIAL *n_bytes
+                                               |  NEXT *n_bytes
+                                               |  MINEXTENTS *n
+                                               |  MAXEXTENTS *n
+                                               |  PCTINCREASE *n
+                                               |  OPTIMAL (NULL | *n_bytes)
+                                               |  FREELISTS *n
+                                               |  FREELIST GROUPS *n
            synonym                             =  *schema_name $'.' *synonym_name | *synonym_name
            synonym_name                        =  *identifier
            table                               =  *schema_name $'.' *table_name | *table_name
            table_constraint                    =  !(CONSTRAINT *constraint_name) *def_table_constraint
            table_name                          =  *identifier
            tablespace_name                     =  *identifier
            table_storage                       =  PCTFREE *n
+                                               |  PCTUSED *n
+                                               |  INITRANS *n
+                                               |  MAXTRANS *n
+                                               |  TABLESPACE *tablespace_name
+                                               |  STORAGE $'(' %*storage_spec $')'
            trigger                             =  *schema_name $'.' *trigger_name | *trigger_name
            trigger_name                        =  *identifier
            trigger_new                         =  NEW !AS *identifier
            trigger_old                         =  OLD !AS *identifier
            trigger_ref                         =  REFERENCING
+                                                  !( *trigger_old
+                                                  |  *trigger_new
+                                                  |  *trigger_old *trigger_new
+                                                  |  *trigger_new *trigger_old
+                                                  )
            trigger_sync                        =  (BEFORE | AFTER) *trigger_sync_list ON *table
            trigger_sync_list                   =  (DELETE | INSERT | UPDATE !(OF *column_list))
+                                                  !%(OR (DELETE | INSERT | UPDATE !(OF *column_list)))
            trigger_when                        =  FOR EACH ROW !(WHEN $'(' *condition $')')
            user_name                           =  *identifier
            view                                =  *schema_name $'.' *view_name | *view_name
            view_name                           =  *identifier
