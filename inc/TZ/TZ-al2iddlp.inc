            '('                                 =  '('
            ')'                                 =  ')'
            '*'                                 =  '*'
            '+'                                 =  '+'
            ','                                 =  ','
            '-'                                 =  '-'
            '.'                                 =  '.'
            '/'                                 =  '/'
            ':'                                 =  ':'
            ';'                                 =  ';'
            '?'                                 =  '?'
            ACTIVATE_DATABASE_cmd               =  ACTIVATE
+                                                  *ACTIVATE_DATABASE_cmd_1
+                                                  *database_alias
+                                                  *ACTIVATE_DATABASE_cmd_2
            ACTIVATE_DATABASE_cmd_1             =  DATABASE | DB
            ACTIVATE_DATABASE_cmd_2             =  epsilon | USER *username *ACTIVATE_DATABASE_cmd_2_1
            ACTIVATE_DATABASE_cmd_2_1           =  epsilon | USING *password
            ADD_NODE_cmd                        =  ADD NODE *ADD_NODE_cmd_1
            ADD_NODE_cmd_1                      =  epsilon | LIKE NODE *node_number | WITHOUT TABLESPACES
            ALTER_BUFFERPOOL_stmt               =  ALTER BUFFERPOOL *bufferpool_name *ALTER_BUFFERPOOL_stmt_1
            ALTER_BUFFERPOOL_stmt_1             =  NODE *node_number SIZE *number_of_pages
+                                               |  SIZE *number_of_pages
+                                               |  NOT EXTENDED STORAGE
+                                               |  EXTENDED STORAGE
+                                               |  ADD NODEGROUP *nodegroup_name
            ALTER_NODEGROUP_stmt                =  ALTER NODEGROUP *nodegroup_name *ALTER_NODEGROUP_stmt_1
            ALTER_NODEGROUP_stmt_1              =  *ALTER_NODEGROUP_stmt_1_0
+                                               |  *ALTER_NODEGROUP_stmt_1 $',' *ALTER_NODEGROUP_stmt_1_0
            ALTER_NODEGROUP_stmt_1_0            =  ADD
+                                                  *ALTER_NODEGROUP_stmt_1_1
+                                                  $'('
+                                                  *ALTER_NODEGROUP_stmt_1_2
+                                                  $')'
+                                                  *ALTER_NODEGROUP_stmt_1_3
+                                               |  DROP *ALTER_NODEGROUP_stmt_1_4 $'(' *ALTER_NODEGROUP_stmt_1_5 $')'
            ALTER_NODEGROUP_stmt_1_1            =  NODE | NODES
            ALTER_NODEGROUP_stmt_1_2            =  *ALTER_NODEGROUP_stmt_1_2_0
+                                               |  *ALTER_NODEGROUP_stmt_1_2 $',' *ALTER_NODEGROUP_stmt_1_2_0
            ALTER_NODEGROUP_stmt_1_2_0          =  *node_number *ALTER_NODEGROUP_stmt_1_2_1
            ALTER_NODEGROUP_stmt_1_2_1          =  epsilon | TO *node_number
            ALTER_NODEGROUP_stmt_1_3            =  epsilon | LIKE NODE *node_number | WITHOUT TABLESPACES
            ALTER_NODEGROUP_stmt_1_4            =  NODE | NODES
            ALTER_NODEGROUP_stmt_1_5            =  *ALTER_NODEGROUP_stmt_1_5_0
+                                               |  *ALTER_NODEGROUP_stmt_1_5 $',' *ALTER_NODEGROUP_stmt_1_5_0
            ALTER_NODEGROUP_stmt_1_5_0          =  *node_number *ALTER_NODEGROUP_stmt_1_5_1
            ALTER_NODEGROUP_stmt_1_5_1          =  epsilon | TO *node_number
            ALTER_TABLESPACE_stmt               =  ALTER TABLESPACE *tablespace_name *ALTER_TABLESPACE_stmt_1
            ALTER_TABLESPACE_stmt_1             =  *ALTER_TABLESPACE_stmt_1_0
+                                               |  *ALTER_TABLESPACE_stmt_1 *ALTER_TABLESPACE_stmt_1_0
            ALTER_TABLESPACE_stmt_1_0           =  ADD *ALTER_TABLESPACE_stmt_1_1
+                                               |  PREFETCHSIZE *number_of_pages_kmg
+                                               |  BUFFERPOOL *bufferpool_name
+                                               |  OVERHEAD *number_of_milliseconds
+                                               |  TRANSFERRATE *number_of_milliseconds
+                                               |  DROPPED TABLE RECOVERY *ALTER_TABLESPACE_stmt_1_2
+                                               |  SWITCH ONLINE
            ALTER_TABLESPACE_stmt_1_1           =  *database_container_clause *ALTER_TABLESPACE_stmt_1_1_1
+                                               |  *system_container_clause *on_nodes_clause
            ALTER_TABLESPACE_stmt_1_1_1         =  epsilon | *on_nodes_clause
            ALTER_TABLESPACE_stmt_1_2           =  ON | OFF
            ALTER_TABLE_stmt                    =  ALTER TABLE *table_name *ALTER_TABLE_stmt_1
            ALTER_TABLE_stmt_1                  =  *not_volatile | *ALTER_TABLE_stmt_1_1
            ALTER_TABLE_stmt_1_1                =  *ALTER_TABLE_stmt_1_1_0
+                                               |  *ALTER_TABLE_stmt_1_1 *ALTER_TABLE_stmt_1_1_0
            ALTER_TABLE_stmt_1_1_0              =  ADD *ALTER_TABLE_stmt_1_1_1
+                                               |  *ALTER_TABLE_stmt_1_1_2 *ALTER_TABLE_stmt_1_1_3
            ALTER_TABLE_stmt_1_1_1              =  *ALTER_TABLE_stmt_1_1_1_1 *column_definition
+                                               |  *unique_constraint
+                                               |  *referential_constraint
+                                               |  *check_constraint
+                                               |  *partitioning_key_definition
            ALTER_TABLE_stmt_1_1_1_1            =  epsilon | COLUMN
            ALTER_TABLE_stmt_1_1_2              =  ALTER *ALTER_TABLE_stmt_1_1_2_1 *column_alteration
+                                               |  DROP *ALTER_TABLE_stmt_1_1_2_2
+                                               |  DATA CAPTURE *ALTER_TABLE_stmt_1_1_2_3
+                                               |  ACTIVATE NOT LOGGED INITIALLY *ALTER_TABLE_stmt_1_1_2_4
+                                               |  PCTFREE $'_INTEGER_'
+                                               |  LOCKSIZE *ALTER_TABLE_stmt_1_1_2_5
+                                               |  APPEND *ALTER_TABLE_stmt_1_1_2_6
+                                               |  VOLATILE *ALTER_TABLE_stmt_1_1_2_7
            ALTER_TABLE_stmt_1_1_2_1            =  epsilon | COLUMN
            ALTER_TABLE_stmt_1_1_2_2            =  PRIMARY KEY
+                                               |  *ALTER_TABLE_stmt_1_1_2_2_1 *constraint_name
+                                               |  PARTITIONING KEY
            ALTER_TABLE_stmt_1_1_2_2_1          =  FOREIGN KEY | UNIQUE | CHECK | CONSTRAINT
            ALTER_TABLE_stmt_1_1_2_3            =  NONE | CHANGES *ALTER_TABLE_stmt_1_1_2_3_1
            ALTER_TABLE_stmt_1_1_2_3_1          =  epsilon | INCLUDE LONGVAR COLUMNS
            ALTER_TABLE_stmt_1_1_2_4            =  epsilon | WITH EMPTY TABLE
            ALTER_TABLE_stmt_1_1_2_5            =  ROW | TABLE
            ALTER_TABLE_stmt_1_1_2_6            =  ON | OFF
            ALTER_TABLE_stmt_1_1_2_7            =  epsilon | CARDINALITY
            ALTER_TABLE_stmt_1_1_3              =  epsilon | *not_volatile
            ALTER_TYPE_stmt                     =  ALTER TYPE *type_name *ALTER_TYPE_stmt_1
            ALTER_TYPE_stmt_1                   =  *ALTER_TYPE_stmt_1_0 | *ALTER_TYPE_stmt_1 $',' *ALTER_TYPE_stmt_1_0
            ALTER_TYPE_stmt_1_0                 =  ADD ATTRIBUTE *attribute_definition | DROP ATTRIBUTE *attribute_name
            ALTER_VIEW_stmt                     =  ALTER VIEW *view_name *ALTER_VIEW_stmt_1
            ALTER_VIEW_stmt_1                   =  *ALTER_VIEW_stmt_1_0 | *ALTER_VIEW_stmt_1 *ALTER_VIEW_stmt_1_0
            ALTER_VIEW_stmt_1_0                 =  ALTER
+                                                  *ALTER_VIEW_stmt_1_1
+                                                  *column_name
+                                                  ADD
+                                                  SCOPE
+                                                  *typed_table_or_view_name
            ALTER_VIEW_stmt_1_1                 =  epsilon | COLUMN
            ATTACH_cmd                          =  ATTACH *ATTACH_cmd_1 *ATTACH_cmd_2
            ATTACH_cmd_1                        =  epsilon | TO *nodename
            ATTACH_cmd_2                        =  epsilon | USER *username *ATTACH_cmd_2_1
            ATTACH_cmd_2_1                      =  epsilon | USING *password
            BACKUP_DATABASE_cmd                 =  BACKUP
+                                                  *BACKUP_DATABASE_cmd_1
+                                                  *BACKUP_DATABASE_cmd_2
+                                                  *BACKUP_DATABASE_cmd_3
+                                                  *BACKUP_DATABASE_cmd_4
+                                                  *BACKUP_DATABASE_cmd_5
+                                                  *BACKUP_DATABASE_cmd_6
+                                                  *BACKUP_DATABASE_cmd_7
+                                                  *BACKUP_DATABASE_cmd_8
            BACKUP_DATABASE_cmd_1               =  DATABASE | DB
            BACKUP_DATABASE_cmd_2               =  epsilon | *database_alias USER *username *BACKUP_DATABASE_cmd_2_1
            BACKUP_DATABASE_cmd_2_1             =  epsilon | USING *password
            BACKUP_DATABASE_cmd_3               =  epsilon | TABLESPACE $'(' *BACKUP_DATABASE_cmd_3_1 $')'
            BACKUP_DATABASE_cmd_3_1             =  *tablespace_name | *BACKUP_DATABASE_cmd_3_1 $',' *tablespace_name
            BACKUP_DATABASE_cmd_4               =  epsilon
+                                               |  *BACKUP_DATABASE_cmd_4_1 USE ADSM *BACKUP_DATABASE_cmd_4_2
+                                               |  TO *BACKUP_DATABASE_cmd_4_3
+                                               |  LOAD *library_name *BACKUP_DATABASE_cmd_4_4
            BACKUP_DATABASE_cmd_4_1             =  epsilon | ONLINE
            BACKUP_DATABASE_cmd_4_2             =  epsilon | OPEN *num_sessions SESSIONS
            BACKUP_DATABASE_cmd_4_3             =  *target_area | *BACKUP_DATABASE_cmd_4_3 $',' *target_area
            BACKUP_DATABASE_cmd_4_4             =  epsilon | OPEN *num_sessions SESSIONS
            BACKUP_DATABASE_cmd_5               =  epsilon | WITH *num_buffers BUFFERS
            BACKUP_DATABASE_cmd_6               =  epsilon | BUFFER *buffer_size
            BACKUP_DATABASE_cmd_7               =  epsilon | PARALLELISM $'_INTEGER_'
            BACKUP_DATABASE_cmd_8               =  epsilon | WITHOUT PROMPTING
            BEGIN_DECLARE_SECTION_stmt          =  BEGIN DECLARE SECTION
            BIND_cmd                            =  BIND
+                                                  *filename
+                                                  *BIND_cmd_1
+                                                  *BIND_cmd_2
+                                                  *BIND_cmd_3
+                                                  *BIND_cmd_4
+                                                  *BIND_cmd_5
+                                                  *BIND_cmd_6
+                                                  *BIND_cmd_7
+                                                  *BIND_cmd_8
+                                                  *BIND_cmd_9
+                                                  *BIND_cmd_10
+                                                  *BIND_cmd_11
+                                                  *BIND_cmd_12
+                                                  *BIND_cmd_13
+                                                  *BIND_cmd_14
+                                                  *BIND_cmd_15
+                                                  *BIND_cmd_16
            BIND_cmd_1                          =  epsilon | BLOCKING *BIND_cmd_1_1
            BIND_cmd_1_1                        =  ALL | NO | UNAMBIG
            BIND_cmd_2                          =  epsilon | COLLECTION *schema_name
            BIND_cmd_3                          =  epsilon | DATETIME *BIND_cmd_3_1
            BIND_cmd_3_1                        =  epsilon | DEF | EUR | ISO | JIS | LOC | USA
            BIND_cmd_4                          =  epsilon | DEGREE *BIND_cmd_4_1
            BIND_cmd_4_1                        =  *degree_of_parallelism | ANY
            BIND_cmd_5                          =  epsilon | EXPLAIN *BIND_cmd_5_1
            BIND_cmd_5_1                        =  NO | ALL | YES
            BIND_cmd_6                          =  epsilon | EXPLSNAP *BIND_cmd_6_1
            BIND_cmd_6_1                        =  NO | ALL | YES
            BIND_cmd_7                          =  epsilon | FUNCPATH *schema_name *BIND_cmd_7_1
            BIND_cmd_7_1                        =  epsilon | $',' *BIND_cmd_7_1_1
            BIND_cmd_7_1_1                      =  *BIND_cmd_7_1_1_0 | *BIND_cmd_7_1_1 $',' *BIND_cmd_7_1_1_0
            BIND_cmd_7_1_1_0                    =  *schema_name
            BIND_cmd_8                          =  epsilon | GRANT *BIND_cmd_8_1
            BIND_cmd_8_1                        =  *authid | PUBLIC
            BIND_cmd_9                          =  epsilon | GRANT_GROUP *group_name
            BIND_cmd_10                         =  epsilon | GRANT_USER *user_name
            BIND_cmd_11                         =  epsilon | INSERT *BIND_cmd_11_1
            BIND_cmd_11_1                       =  BUF | DEF
            BIND_cmd_12                         =  epsilon | ISOLATION *BIND_cmd_12_1
            BIND_cmd_12_1                       =  CS | RR | RS | UR
            BIND_cmd_13                         =  epsilon | MESSAGES *message_file
            BIND_cmd_14                         =  epsilon | QUERYOPT *optimization_level
            BIND_cmd_15                         =  epsilon | SQLERROR *BIND_cmd_15_1
            BIND_cmd_15_1                       =  CHECK | NOPACKAGE
            BIND_cmd_16                         =  epsilon | SQLWARN *BIND_cmd_16_1
            BIND_cmd_16_1                       =  NO | YES
            CALL_stmt                           =  CALL *procedure_name *CALL_stmt_1
            CALL_stmt_1                         =  epsilon
+                                               |  $'(' *CALL_stmt_1_1 $')'
+                                               |  USING DESCRIPTOR *descriptor_name
            CALL_stmt_1_1                       =  epsilon | *CALL_stmt_1_1_1
            CALL_stmt_1_1_1                     =  *host_variable | *CALL_stmt_1_1_1 $',' *host_variable
            CATALOG_APPCLU_NODE_cmd             =  CATALOG
+                                                  APPCLU
+                                                  NODE
+                                                  *nodename
+                                                  *CATALOG_APPCLU_NODE_cmd_1
+                                                  REMOTE
+                                                  *partner_lu
+                                                  *CATALOG_APPCLU_NODE_cmd_2
+                                                  *CATALOG_APPCLU_NODE_cmd_3
            CATALOG_APPCLU_NODE_cmd_1           =  epsilon | LOCAL *local_lu
            CATALOG_APPCLU_NODE_cmd_2           =  epsilon | MODE *mode
            CATALOG_APPCLU_NODE_cmd_3           =  epsilon | WITH *comment_string
            CATALOG_APPC_NODE_cmd               =  CATALOG
+                                                  *CATALOG_APPC_NODE_cmd_1
+                                                  APPC
+                                                  NODE
+                                                  *nodename
+                                                  REMOTE
+                                                  *symbolic_dest_name
+                                                  *CATALOG_APPC_NODE_cmd_2
+                                                  *CATALOG_APPC_NODE_cmd_3
+                                                  *CATALOG_APPC_NODE_cmd_4
+                                                  *CATALOG_APPC_NODE_cmd_5
+                                                  *CATALOG_APPC_NODE_cmd_6
            CATALOG_APPC_NODE_cmd_1             =  epsilon | ADMIN
            CATALOG_APPC_NODE_cmd_2             =  epsilon | SECURITY *CATALOG_APPC_NODE_cmd_2_1
            CATALOG_APPC_NODE_cmd_2_1           =  PROGRAM | NONE | SAME
            CATALOG_APPC_NODE_cmd_3             =  epsilon | REMOTE_INSTANCE *instance_name
            CATALOG_APPC_NODE_cmd_4             =  epsilon | SYSTEM *system_name
            CATALOG_APPC_NODE_cmd_5             =  epsilon | OSTYPE *operating_system_type
            CATALOG_APPC_NODE_cmd_6             =  epsilon | WITH *comment_string
            CATALOG_APPN_NODE_cmd               =  CATALOG
+                                                  APPN
+                                                  NODE
+                                                  *nodename
+                                                  *CATALOG_APPN_NODE_cmd_1
+                                                  REMOTE
+                                                  *partner_lu
+                                                  *CATALOG_APPN_NODE_cmd_2
+                                                  *CATALOG_APPN_NODE_cmd_3
+                                                  WITH
+                                                  *comment_string
            CATALOG_APPN_NODE_cmd_1             =  epsilon | NETWORKID *netid
            CATALOG_APPN_NODE_cmd_2             =  epsilon | LOCAL *local_lu
            CATALOG_APPN_NODE_cmd_3             =  epsilon | MODE *mode
            CATALOG_DATABASE_cmd                =  CATALOG
+                                                  *CATALOG_DATABASE_cmd_1
+                                                  *database_name
+                                                  *CATALOG_DATABASE_cmd_2
+                                                  *CATALOG_DATABASE_cmd_3
+                                                  *CATALOG_DATABASE_cmd_4
+                                                  *CATALOG_DATABASE_cmd_5
            CATALOG_DATABASE_cmd_1              =  DATABASE | DB
            CATALOG_DATABASE_cmd_2              =  epsilon | AS *alias
            CATALOG_DATABASE_cmd_3              =  epsilon | ON *path_or_drive | AT NODE *nodename
            CATALOG_DATABASE_cmd_4              =  epsilon | AUTHENTICATION *CATALOG_DATABASE_cmd_4_1
            CATALOG_DATABASE_cmd_4_1            =  SERVER | CLIENT | DCS | DCE SERVER PRINCIPAL *principalname
            CATALOG_DATABASE_cmd_5              =  epsilon | WITH *comment_string
            CATALOG_DCS_DATABASE_cmd            =  CATALOG
+                                                  DCS
+                                                  *CATALOG_DCS_DATABASE_cmd_1
+                                                  *database_name
+                                                  *CATALOG_DCS_DATABASE_cmd_2
+                                                  *CATALOG_DCS_DATABASE_cmd_3
+                                                  *CATALOG_DCS_DATABASE_cmd_4
+                                                  *CATALOG_DCS_DATABASE_cmd_5
            CATALOG_DCS_DATABASE_cmd_1          =  DATABASE | DB
            CATALOG_DCS_DATABASE_cmd_2          =  epsilon | AS *target_database_name
            CATALOG_DCS_DATABASE_cmd_3          =  epsilon | AR *library_name
            CATALOG_DCS_DATABASE_cmd_4          =  epsilon | PARMS *parameter_string
            CATALOG_DCS_DATABASE_cmd_5          =  epsilon | WITH *comment_string
            CATALOG_GLOBAL_DATABASE_cmd         =  CATALOG
+                                                  GLOBAL
+                                                  *CATALOG_GLOBAL_DATABASE_cmd_1
+                                                  *database_global_name
+                                                  AS
+                                                  *alias
+                                                  USING
+                                                  DIRECTORY
+                                                  DCE
+                                                  *CATALOG_GLOBAL_DATABASE_cmd_2
            CATALOG_GLOBAL_DATABASE_cmd_1       =  DATABASE | DB
            CATALOG_GLOBAL_DATABASE_cmd_2       =  epsilon | WITH *comment_string
            CATALOG_IPX_SPX_NODE_cmd            =  CATALOG
+                                                  *CATALOG_IPX_SPX_NODE_cmd_1
+                                                  IPXSPX
+                                                  NODE
+                                                  *nodename
+                                                  REMOTE
+                                                  *file_server
+                                                  SERVER
+                                                  *object_name
+                                                  *CATALOG_IPX_SPX_NODE_cmd_2
+                                                  *CATALOG_IPX_SPX_NODE_cmd_3
+                                                  *CATALOG_IPX_SPX_NODE_cmd_4
+                                                  *CATALOG_IPX_SPX_NODE_cmd_5
            CATALOG_IPX_SPX_NODE_cmd_1          =  epsilon | ADMIN
            CATALOG_IPX_SPX_NODE_cmd_2          =  epsilon | REMOTE_INSTANCE *instance_name
            CATALOG_IPX_SPX_NODE_cmd_3          =  epsilon | SYSTEM *system_name
            CATALOG_IPX_SPX_NODE_cmd_4          =  epsilon | OSTYPE *operating_system_type
            CATALOG_IPX_SPX_NODE_cmd_5          =  epsilon | WITH *comment_string
            CATALOG_LOCAL_NODE_cmd              =  CATALOG
+                                                  *CATALOG_LOCAL_NODE_cmd_1
+                                                  LOCAL
+                                                  NODE
+                                                  *nodename
+                                                  *CATALOG_LOCAL_NODE_cmd_2
+                                                  *CATALOG_LOCAL_NODE_cmd_3
+                                                  *CATALOG_LOCAL_NODE_cmd_4
+                                                  *CATALOG_LOCAL_NODE_cmd_5
            CATALOG_LOCAL_NODE_cmd_1            =  epsilon | ADMIN
            CATALOG_LOCAL_NODE_cmd_2            =  epsilon | INSTANCE *instancename
            CATALOG_LOCAL_NODE_cmd_3            =  epsilon | SYSTEM *system_name
            CATALOG_LOCAL_NODE_cmd_4            =  epsilon | OSTYPE *operating_system_type
            CATALOG_LOCAL_NODE_cmd_5            =  epsilon | WITH *comment_string
            CATALOG_NAMED_PIPE_NODE_cmd         =  CATALOG
+                                                  *CATALOG_NAMED_PIPE_NODE_cmd_1
+                                                  NPIPE
+                                                  NODE
+                                                  *nodename
+                                                  REMOTE
+                                                  *computername
+                                                  INSTANCE
+                                                  *instancename
+                                                  *CATALOG_NAMED_PIPE_NODE_cmd_2
+                                                  *CATALOG_NAMED_PIPE_NODE_cmd_3
+                                                  *CATALOG_NAMED_PIPE_NODE_cmd_4
            CATALOG_NAMED_PIPE_NODE_cmd_1       =  epsilon | ADMIN
            CATALOG_NAMED_PIPE_NODE_cmd_2       =  epsilon | SYSTEM *system_name
            CATALOG_NAMED_PIPE_NODE_cmd_3       =  epsilon | OSTYPE *operating_system_type
            CATALOG_NAMED_PIPE_NODE_cmd_4       =  epsilon | WITH *comment_string
            CATALOG_NETBIOS_NODE_cmd            =  CATALOG
+                                                  *CATALOG_NETBIOS_NODE_cmd_1
+                                                  NETBIOS
+                                                  NODE
+                                                  *nodename
+                                                  REMOTE
+                                                  *server_name
+                                                  ADAPTER
+                                                  *adapter_number
+                                                  *CATALOG_NETBIOS_NODE_cmd_2
+                                                  *CATALOG_NETBIOS_NODE_cmd_3
+                                                  *CATALOG_NETBIOS_NODE_cmd_4
+                                                  *CATALOG_NETBIOS_NODE_cmd_5
            CATALOG_NETBIOS_NODE_cmd_1          =  epsilon | ADMIN
            CATALOG_NETBIOS_NODE_cmd_2          =  epsilon | REMOTE_INSTANCE *instance_name
            CATALOG_NETBIOS_NODE_cmd_3          =  epsilon | SYSTEM *system_name
            CATALOG_NETBIOS_NODE_cmd_4          =  epsilon | OSTYPE *operating_system_type
            CATALOG_NETBIOS_NODE_cmd_5          =  epsilon | WITH *comment_string
            CATALOG_ODBC_DATA_SOURCE_cmd        =  CATALOG
+                                                  *CATALOG_ODBC_DATA_SOURCE_cmd_1
+                                                  ODBC
+                                                  DATA
+                                                  SOURCE
+                                                  *data_source_name
            CATALOG_ODBC_DATA_SOURCE_cmd_1      =  epsilon | USER | SYSTEM
            CATALOG_TCP_IP_NODE_cmd             =  CATALOG
+                                                  *CATALOG_TCP_IP_NODE_cmd_1
+                                                  TCPIP
+                                                  NODE
+                                                  *nodename
+                                                  REMOTE
+                                                  *hostname
+                                                  SERVER
+                                                  *service_name
+                                                  *CATALOG_TCP_IP_NODE_cmd_2
+                                                  *CATALOG_TCP_IP_NODE_cmd_3
+                                                  *CATALOG_TCP_IP_NODE_cmd_4
+                                                  *CATALOG_TCP_IP_NODE_cmd_5
+                                                  *CATALOG_TCP_IP_NODE_cmd_6
            CATALOG_TCP_IP_NODE_cmd_1           =  epsilon | ADMIN
            CATALOG_TCP_IP_NODE_cmd_2           =  epsilon | SECURITY SOCKS
            CATALOG_TCP_IP_NODE_cmd_3           =  epsilon | REMOTE_INSTANCE *instance_name
            CATALOG_TCP_IP_NODE_cmd_4           =  epsilon | SYSTEM *system_name
            CATALOG_TCP_IP_NODE_cmd_5           =  epsilon | OSTYPE *operating_system_type
            CATALOG_TCP_IP_NODE_cmd_6           =  epsilon | WITH *comment_string
            CHANGE_DATABASE_COMMENT_cmd         =  CHANGE
+                                                  *CHANGE_DATABASE_COMMENT_cmd_1
+                                                  *database_alias
+                                                  COMMENT
+                                                  *CHANGE_DATABASE_COMMENT_cmd_2
+                                                  WITH
+                                                  *comment_string
            CHANGE_DATABASE_COMMENT_cmd_1       =  DATABASE | DB
            CHANGE_DATABASE_COMMENT_cmd_2       =  epsilon | ON *path_or_drive
            CHANGE_ISOLATION_LEVEL_cmd          =  CHANGE
+                                                  *CHANGE_ISOLATION_LEVEL_cmd_1
+                                                  TO
+                                                  *CHANGE_ISOLATION_LEVEL_cmd_2
            CHANGE_ISOLATION_LEVEL_cmd_1        =  SQLISL | ISOLATION
            CHANGE_ISOLATION_LEVEL_cmd_2        =  CS | NC | RR | RS | UR
            CLOSE_stmt                          =  CLOSE *cursor_name *CLOSE_stmt_1
            CLOSE_stmt_1                        =  epsilon | WITH RELEASE
            COMMENT_ON_stmt                     =  COMMENT ON *COMMENT_ON_stmt_1
            COMMENT_ON_stmt_1                   =  ALIAS *alias_name IS *string_constant
+                                               |  COLUMN *table_or_view_column IS *string_constant
+                                               |  CONSTRAINT *table_constraint_name IS *string_constant
+                                               |  FUNCTION *function_name *COMMENT_ON_stmt_1_1 IS *string_constant
+                                               |  SPECIFIC FUNCTION *specific_name IS *string_constant
+                                               |  INDEX *index_name IS *string_constant
+                                               |  NODEGROUP *nodegroup_name IS *string_constant
+                                               |  PACKAGE *package_name IS *string_constant
+                                               |  PROCEDURE *procedure_name *COMMENT_ON_stmt_1_2 IS *string_constant
+                                               |  SPECIFIC PROCEDURE *specific_name IS *string_constant
+                                               |  SCHEMA *schema_name IS *string_constant
+                                               |  TABLE *table_or_view_name IS *string_constant
+                                               |  TABLESPACE *tablespace_name IS *string_constant
+                                               |  TRIGGER *trigger_name IS *string_constant
+                                               |  *COMMENT_ON_stmt_1_3 TYPE *type_name IS *string_constant
+                                               |  *table_or_view_name $'(' *COMMENT_ON_stmt_1_4 $')'
            COMMENT_ON_stmt_1_1                 =  epsilon | $'(' *COMMENT_ON_stmt_1_1_1 $')'
            COMMENT_ON_stmt_1_1_1               =  *COMMENT_ON_stmt_1_1_1_0
+                                               |  *COMMENT_ON_stmt_1_1_1 $',' *COMMENT_ON_stmt_1_1_1_0
            COMMENT_ON_stmt_1_1_1_0             =  *data_type
            COMMENT_ON_stmt_1_2                 =  epsilon | $'(' *COMMENT_ON_stmt_1_2_1 $')'
            COMMENT_ON_stmt_1_2_1               =  *COMMENT_ON_stmt_1_2_1_0
+                                               |  *COMMENT_ON_stmt_1_2_1 $',' *COMMENT_ON_stmt_1_2_1_0
            COMMENT_ON_stmt_1_2_1_0             =  *data_type
            COMMENT_ON_stmt_1_3                 =  epsilon | DISTINCT
            COMMENT_ON_stmt_1_4                 =  *COMMENT_ON_stmt_1_4_0
+                                               |  *COMMENT_ON_stmt_1_4 $',' *COMMENT_ON_stmt_1_4_0
            COMMENT_ON_stmt_1_4_0               =  *column_name IS *string_constant
            COMMIT_stmt                         =  COMMIT *COMMIT_stmt_1
            COMMIT_stmt_1                       =  epsilon | WORK
            CONNECT_stmt                        =  CONNECT *CONNECT_stmt_1
            CONNECT_stmt_1                      =  epsilon
+                                               |  TO *server_name *CONNECT_stmt_1_1 *CONNECT_stmt_1_2
+                                               |  RESET
+                                               |  *authorization
            CONNECT_stmt_1_1                    =  epsilon | *lock_block
            CONNECT_stmt_1_2                    =  epsilon | *authorization
            CREATE_ALIAS_stmt                   =  CREATE
+                                                  *CREATE_ALIAS_stmt_1
+                                                  *alias_name
+                                                  FOR
+                                                  *table_or_view_or_alias_name
            CREATE_ALIAS_stmt_1                 =  ALIAS | SYNONYM
            CREATE_BUFFERPOOL_stmt              =  CREATE
+                                                  BUFFERPOOL
+                                                  *bufferpool_name
+                                                  *CREATE_BUFFERPOOL_stmt_1
+                                                  SIZE
+                                                  *number_of_pages
+                                                  *CREATE_BUFFERPOOL_stmt_2
+                                                  *CREATE_BUFFERPOOL_stmt_3
+                                                  *CREATE_BUFFERPOOL_stmt_4
            CREATE_BUFFERPOOL_stmt_1            =  epsilon | ALL NODES | NODEGROUP *CREATE_BUFFERPOOL_stmt_1_1
            CREATE_BUFFERPOOL_stmt_1_1          =  *CREATE_BUFFERPOOL_stmt_1_1_0
+                                               |  *CREATE_BUFFERPOOL_stmt_1_1 $',' *CREATE_BUFFERPOOL_stmt_1_1_0
            CREATE_BUFFERPOOL_stmt_1_1_0        =  *nodegroup_name
            CREATE_BUFFERPOOL_stmt_2            =  epsilon | *except_on_nodes_clause
            CREATE_BUFFERPOOL_stmt_3            =  epsilon | PAGESIZE *integer_k
            CREATE_BUFFERPOOL_stmt_4            =  epsilon | NOT EXTENDED STORAGE | EXTENDED STORAGE
            CREATE_DATABASE_cmd                 =  CREATE
+                                                  *CREATE_DATABASE_cmd_1
+                                                  *database_name
+                                                  *CREATE_DATABASE_cmd_2
+                                                  *CREATE_DATABASE_cmd_3
+                                                  *CREATE_DATABASE_cmd_4
+                                                  *CREATE_DATABASE_cmd_5
+                                                  *CREATE_DATABASE_cmd_6
+                                                  *CREATE_DATABASE_cmd_7
+                                                  *CREATE_DATABASE_cmd_8
+                                                  *CREATE_DATABASE_cmd_9
+                                                  *CREATE_DATABASE_cmd_10
+                                                  *CREATE_DATABASE_cmd_11
+                                                  *CREATE_DATABASE_cmd_12
            CREATE_DATABASE_cmd_1               =  DATABASE | DB
            CREATE_DATABASE_cmd_2               =  epsilon | AT NODE | *Create_Database_options
            CREATE_DATABASE_cmd_3               =  epsilon | ON *path_or_drive
            CREATE_DATABASE_cmd_4               =  epsilon | ALIAS *database_alias
            CREATE_DATABASE_cmd_5               =  epsilon | USING CODESET *codeset TERRITORY *territory
            CREATE_DATABASE_cmd_6               =  epsilon | COLLATE USING *CREATE_DATABASE_cmd_6_1
            CREATE_DATABASE_cmd_6_1             =  SYSTEM | COMPATIBILITY | IDENTITY
            CREATE_DATABASE_cmd_7               =  epsilon | NUMSEGS *numsegs
            CREATE_DATABASE_cmd_8               =  epsilon | DFT_EXTENT_SZ *dft_extentsize
            CREATE_DATABASE_cmd_9               =  epsilon | CATALOG TABLESPACE *tblspace_defn
            CREATE_DATABASE_cmd_10              =  epsilon | USER TABLESPACE *tblspace_defn
            CREATE_DATABASE_cmd_11              =  epsilon | TEMPORARY TABLESPACE *tblspace_defn
            CREATE_DATABASE_cmd_12              =  epsilon | WITH *comment_string
            CREATE_DISTINCT_TYPE_stmt           =  CREATE
+                                                  DISTINCT
+                                                  TYPE
+                                                  *distinct_type_name
+                                                  AS
+                                                  *source_data_type
+                                                  *CREATE_DISTINCT_TYPE_stmt_1
            CREATE_DISTINCT_TYPE_stmt_1         =  epsilon | WITH COMPARISONS
            CREATE_EVENT_MONITOR_stmt           =  CREATE
+                                                  EVENT
+                                                  MONITOR
+                                                  *event_monitor_name
+                                                  FOR
+                                                  *CREATE_EVENT_MONITOR_stmt_1
+                                                  WRITE
+                                                  TO
+                                                  *CREATE_EVENT_MONITOR_stmt_2
+                                                  *CREATE_EVENT_MONITOR_stmt_3
+                                                  *CREATE_EVENT_MONITOR_stmt_4
            CREATE_EVENT_MONITOR_stmt_1         =  *CREATE_EVENT_MONITOR_stmt_1_0
+                                               |  *CREATE_EVENT_MONITOR_stmt_1 $',' *CREATE_EVENT_MONITOR_stmt_1_0
            CREATE_EVENT_MONITOR_stmt_1_0       =  DATABASE
+                                               |  TABLES
+                                               |  DEADLOCKS
+                                               |  TABLESPACES
+                                               |  BUFFERPOOLS
+                                               |  *CREATE_EVENT_MONITOR_stmt_1_1
            CREATE_EVENT_MONITOR_stmt_1_1       =  CONNECTIONS *CREATE_EVENT_MONITOR_stmt_1_1_1
+                                               |  STATEMENTS *CREATE_EVENT_MONITOR_stmt_1_1_2
+                                               |  TRANSACTIONS *CREATE_EVENT_MONITOR_stmt_1_1_3
            CREATE_EVENT_MONITOR_stmt_1_1_1     =  epsilon | WHERE *event_condition
            CREATE_EVENT_MONITOR_stmt_1_1_2     =  epsilon | WHERE *event_condition
            CREATE_EVENT_MONITOR_stmt_1_1_3     =  epsilon | WHERE *event_condition
            CREATE_EVENT_MONITOR_stmt_2         =  PIPE *pipe_name *CREATE_EVENT_MONITOR_stmt_2_1
+                                               |  FILE *path_name *CREATE_EVENT_MONITOR_stmt_2_2
            CREATE_EVENT_MONITOR_stmt_2_1       =  epsilon | *start_option
            CREATE_EVENT_MONITOR_stmt_2_2       =  epsilon | *CREATE_EVENT_MONITOR_stmt_2_2_1
            CREATE_EVENT_MONITOR_stmt_2_2_1     =  *file_options | *CREATE_EVENT_MONITOR_stmt_2_2_1 *file_options
            CREATE_EVENT_MONITOR_stmt_3         =  epsilon | ON NODE *node_number
            CREATE_EVENT_MONITOR_stmt_4         =  epsilon | LOCAL | GLOBAL
            CREATE_FUNCTION_stmt                =  CREATE
+                                                  FUNCTION
+                                                  *function_name
+                                                  $'('
+                                                  *CREATE_FUNCTION_stmt_1
+                                                  $')'
+                                                  *CREATE_FUNCTION_stmt_2
            CREATE_FUNCTION_stmt_1              =  epsilon | *CREATE_FUNCTION_stmt_1_1
            CREATE_FUNCTION_stmt_1_1            =  *CREATE_FUNCTION_stmt_1_1_0
+                                               |  *CREATE_FUNCTION_stmt_1_1 $',' *CREATE_FUNCTION_stmt_1_1_0
            CREATE_FUNCTION_stmt_1_1_0          =  *data_type *CREATE_FUNCTION_stmt_1_1_1
            CREATE_FUNCTION_stmt_1_1_1          =  epsilon | AS LOCATOR
            CREATE_FUNCTION_stmt_2              =  *CREATE_FUNCTION_stmt_2_0
+                                               |  *CREATE_FUNCTION_stmt_2 *CREATE_FUNCTION_stmt_2_0
            CREATE_FUNCTION_stmt_2_0            =  RETURNS *CREATE_FUNCTION_stmt_2_1
+                                               |  RETURNS TABLE $'(' *CREATE_FUNCTION_stmt_2_2 $')'
+                                               |  SPECIFIC *specific_name
+                                               |  EXTERNAL *CREATE_FUNCTION_stmt_2_3
+                                               |  LANGUAGE *CREATE_FUNCTION_stmt_2_4
+                                               |  PARAMETER STYLE *CREATE_FUNCTION_stmt_2_5
+                                               |  NOT DETERMINISTIC
+                                               |  VARIANT
+                                               |  DETERMINISTIC
+                                               |  NOT VARIANT
+                                               |  FENCED
+                                               |  NOT FENCED
+                                               |  RETURNS NULL ON NULL INPUT
+                                               |  NOT NULL CALL
+                                               |  CALLED ON NULL INPUT
+                                               |  NULL CALL
+                                               |  NO SQL
+                                               |  NO EXTERNAL ACTION
+                                               |  EXTERNAL ACTION
+                                               |  NO SCRATCHPAD
+                                               |  SCRATCHPAD
+                                               |  NO FINAL CALL
+                                               |  FINAL CALL
+                                               |  ALLOW PARALLEL
+                                               |  DISALLOW PARALLEL
+                                               |  NO DBINFO
+                                               |  DBINFO
+                                               |  CARDINALITY $'_INTEGER_'
+                                               |  SOURCE *CREATE_FUNCTION_stmt_2_6
            CREATE_FUNCTION_stmt_2_1            =  *data_type *CREATE_FUNCTION_stmt_2_1_1
+                                               |  *data_type CAST FROM *data_type *CREATE_FUNCTION_stmt_2_1_2
            CREATE_FUNCTION_stmt_2_1_1          =  epsilon | AS LOCATOR
            CREATE_FUNCTION_stmt_2_1_2          =  epsilon | AS LOCATOR
            CREATE_FUNCTION_stmt_2_2            =  *CREATE_FUNCTION_stmt_2_2_0
+                                               |  *CREATE_FUNCTION_stmt_2_2 $',' *CREATE_FUNCTION_stmt_2_2_0
            CREATE_FUNCTION_stmt_2_2_0          =  *column_name *data_type *CREATE_FUNCTION_stmt_2_2_1
            CREATE_FUNCTION_stmt_2_2_1          =  epsilon | AS LOCATOR
            CREATE_FUNCTION_stmt_2_3            =  epsilon | NAME *CREATE_FUNCTION_stmt_2_3_1
            CREATE_FUNCTION_stmt_2_3_1          =  *identifier | $'_SQ_STRING_'
            CREATE_FUNCTION_stmt_2_4            =  C | JAVA | OLE
            CREATE_FUNCTION_stmt_2_5            =  DB2SQL | DB2GENERAL | JAVA
            CREATE_FUNCTION_stmt_2_6            =  *function_name
+                                               |  *function_name $'(' *CREATE_FUNCTION_stmt_2_6_1 $')'
+                                               |  SPECIFIC *specific_name
            CREATE_FUNCTION_stmt_2_6_1          =  epsilon | *CREATE_FUNCTION_stmt_2_6_1_1
            CREATE_FUNCTION_stmt_2_6_1_1        =  *data_type | *CREATE_FUNCTION_stmt_2_6_1_1 $',' *data_type
            CREATE_INDEX_stmt                   =  CREATE
+                                                  *unique_clause
+                                                  INDEX
+                                                  *index_name
+                                                  ON
+                                                  *table_name
+                                                  $'('
+                                                  *CREATE_INDEX_stmt_1
+                                                  $')'
+                                                  *CREATE_INDEX_stmt_2
            CREATE_INDEX_stmt_1                 =  *CREATE_INDEX_stmt_1_0
+                                               |  *CREATE_INDEX_stmt_1 $',' *CREATE_INDEX_stmt_1_0
            CREATE_INDEX_stmt_1_0               =  *column_name *CREATE_INDEX_stmt_1_1
            CREATE_INDEX_stmt_1_1               =  epsilon | ASC | DESC
            CREATE_INDEX_stmt_2                 =  epsilon | *CREATE_INDEX_stmt_2_1
            CREATE_INDEX_stmt_2_1               =  *CREATE_INDEX_stmt_2_1_0
+                                               |  *CREATE_INDEX_stmt_2_1 *CREATE_INDEX_stmt_2_1_0
            CREATE_INDEX_stmt_2_1_0             =  INCLUDE $'(' *CREATE_INDEX_stmt_2_1_1 $')'
+                                               |  CLUSTER
+                                               |  PCTFREE $'_INTEGER_'
+                                               |  MINPCTUSED $'_INTEGER_'
+                                               |  DISALLOW REVERSE SCANS
+                                               |  ALLOW REVERSE SCANS
            CREATE_INDEX_stmt_2_1_1             =  *CREATE_INDEX_stmt_2_1_1_0
+                                               |  *CREATE_INDEX_stmt_2_1_1 $',' *CREATE_INDEX_stmt_2_1_1_0
            CREATE_INDEX_stmt_2_1_1_0           =  *column_name
            CREATE_NODEGROUP_stmt               =  CREATE NODEGROUP *nodegroup_name *CREATE_NODEGROUP_stmt_1
            CREATE_NODEGROUP_stmt_1             =  epsilon
+                                               |  ON ALL NODES
+                                               |  ON *CREATE_NODEGROUP_stmt_1_1 $'(' *CREATE_NODEGROUP_stmt_1_2 $')'
            CREATE_NODEGROUP_stmt_1_1           =  NODES | NODE
            CREATE_NODEGROUP_stmt_1_2           =  epsilon | *CREATE_NODEGROUP_stmt_1_2_1
            CREATE_NODEGROUP_stmt_1_2_1         =  *CREATE_NODEGROUP_stmt_1_2_1_0
+                                               |  *CREATE_NODEGROUP_stmt_1_2_1 $',' *CREATE_NODEGROUP_stmt_1_2_1_0
            CREATE_NODEGROUP_stmt_1_2_1_0       =  *node_number *CREATE_NODEGROUP_stmt_1_2_1_1
            CREATE_NODEGROUP_stmt_1_2_1_1       =  epsilon | TO *node_number
            CREATE_PROCEDURE_stmt               =  CREATE
+                                                  PROCEDURE
+                                                  *procedure_name
+                                                  $'('
+                                                  *CREATE_PROCEDURE_stmt_1
+                                                  $')'
+                                                  *CREATE_PROCEDURE_stmt_2
            CREATE_PROCEDURE_stmt_1             =  epsilon | *CREATE_PROCEDURE_stmt_1_1
            CREATE_PROCEDURE_stmt_1_1           =  *CREATE_PROCEDURE_stmt_1_1_0
+                                               |  *CREATE_PROCEDURE_stmt_1_1 $',' *CREATE_PROCEDURE_stmt_1_1_0
            CREATE_PROCEDURE_stmt_1_1_0         =  *CREATE_PROCEDURE_stmt_1_1_1 *parameter_name *data_type
            CREATE_PROCEDURE_stmt_1_1_1         =  epsilon | IN | OUT | INOUT
            CREATE_PROCEDURE_stmt_2             =  *CREATE_PROCEDURE_stmt_2_0
+                                               |  *CREATE_PROCEDURE_stmt_2 *CREATE_PROCEDURE_stmt_2_0
            CREATE_PROCEDURE_stmt_2_0           =  SPECIFIC *specific_name
+                                               |  *CREATE_PROCEDURE_stmt_2_1 RESULT SETS $'_INTEGER_'
+                                               |  EXTERNAL *CREATE_PROCEDURE_stmt_2_2
+                                               |  LANGUAGE *CREATE_PROCEDURE_stmt_2_3
+                                               |  PARAMETER STYLE *CREATE_PROCEDURE_stmt_2_4
+                                               |  NOT DETERMINISTIC
+                                               |  DETERMINISTIC
+                                               |  FENCED
+                                               |  NOT FENCED
+                                               |  NO DBINFO
+                                               |  DBINFO
+                                               |  NULL CALL
+                                               |  CALLED ON NULL INPUT
+                                               |  PROGRAM TYPE *CREATE_PROCEDURE_stmt_2_5
            CREATE_PROCEDURE_stmt_2_1           =  epsilon | DYNAMIC
            CREATE_PROCEDURE_stmt_2_2           =  epsilon | NAME *CREATE_PROCEDURE_stmt_2_2_1
            CREATE_PROCEDURE_stmt_2_2_1         =  *identifier | $'_SQ_STRING_'
            CREATE_PROCEDURE_stmt_2_3           =  C | JAVA | COBOL
            CREATE_PROCEDURE_stmt_2_4           =  DB2DARI
+                                               |  *CREATE_PROCEDURE_stmt_2_4_1
+                                               |  *CREATE_PROCEDURE_stmt_2_4_2 *CREATE_PROCEDURE_stmt_2_4_3
+                                               |  DB2SQL
+                                               |  JAVA
            CREATE_PROCEDURE_stmt_2_4_1         =  DB2GENERAL | DB2GENRL
            CREATE_PROCEDURE_stmt_2_4_2         =  SIMPLE CALL | GENERAL
            CREATE_PROCEDURE_stmt_2_4_3         =  epsilon | WITH NULLS
            CREATE_PROCEDURE_stmt_2_5           =  SUB | MAIN
            CREATE_SCHEMA_stmt                  =  CREATE SCHEMA *CREATE_SCHEMA_stmt_1 *CREATE_SCHEMA_stmt_2
            CREATE_SCHEMA_stmt_1                =  *schema_name
+                                               |  AUTHORIZATION *authorization_name
+                                               |  *schema_name AUTHORIZATION *authorization_name
            CREATE_SCHEMA_stmt_2                =  epsilon | *CREATE_SCHEMA_stmt_2_1
            CREATE_SCHEMA_stmt_2_1              =  *CREATE_SCHEMA_stmt_2_1_0
+                                               |  *CREATE_SCHEMA_stmt_2_1 *CREATE_SCHEMA_stmt_2_1_0
            CREATE_SCHEMA_stmt_2_1_0            =  *schema_SQL_stmt
            CREATE_SUMMARY_TABLE_stmt           =  CREATE
+                                                  SUMMARY
+                                                  TABLE
+                                                  *table_name
+                                                  AS
+                                                  $'('
+                                                  *summary_fullselect
+                                                  $')'
+                                                  *summary_table_options
+                                                  *CREATE_SUMMARY_TABLE_stmt_1
            CREATE_SUMMARY_TABLE_stmt_1         =  epsilon | *CREATE_SUMMARY_TABLE_stmt_1_1
            CREATE_SUMMARY_TABLE_stmt_1_1       =  *CREATE_SUMMARY_TABLE_stmt_1_1_0
+                                               |  *CREATE_SUMMARY_TABLE_stmt_1_1 *CREATE_SUMMARY_TABLE_stmt_1_1_0
            CREATE_SUMMARY_TABLE_stmt_1_1_0     =  DATA CAPTURE NONE
+                                               |  DATA CAPTURE CHANGES
+                                               |  IN *tablespace_name *tablespace_options
+                                               |  PARTITIONING
+                                                  KEY
+                                                  $'('
+                                                  *CREATE_SUMMARY_TABLE_stmt_1_1_1
+                                                  $')'
+                                                  *CREATE_SUMMARY_TABLE_stmt_1_1_2
+                                               |  REPLICATED
+                                               |  NOT LOGGED INITIALLY
            CREATE_SUMMARY_TABLE_stmt_1_1_1     =  *CREATE_SUMMARY_TABLE_stmt_1_1_1_0
+                                               |  *CREATE_SUMMARY_TABLE_stmt_1_1_1
+                                                  $','
+                                                  *CREATE_SUMMARY_TABLE_stmt_1_1_1_0
            CREATE_SUMMARY_TABLE_stmt_1_1_1_0   =  *column_name
            CREATE_SUMMARY_TABLE_stmt_1_1_2     =  epsilon | USING HASHING
            CREATE_TABLESPACE_stmt              =  CREATE
+                                                  *CREATE_TABLESPACE_stmt_1
+                                                  TABLESPACE
+                                                  *tablespace_name
+                                                  *CREATE_TABLESPACE_stmt_2
+                                                  *CREATE_TABLESPACE_stmt_3
+                                                  MANAGED
+                                                  BY
+                                                  *CREATE_TABLESPACE_stmt_4
+                                                  *CREATE_TABLESPACE_stmt_5
            CREATE_TABLESPACE_stmt_1            =  epsilon | REGULAR | LONG | TEMPORARY
            CREATE_TABLESPACE_stmt_2            =  epsilon | IN *CREATE_TABLESPACE_stmt_2_1 *nodegroup_name
            CREATE_TABLESPACE_stmt_2_1          =  epsilon | NODEGROUP
            CREATE_TABLESPACE_stmt_3            =  epsilon | PAGESIZE *integer_k
            CREATE_TABLESPACE_stmt_4            =  SYSTEM *system_containers | DATABASE *database_containers
            CREATE_TABLESPACE_stmt_5            =  epsilon | *CREATE_TABLESPACE_stmt_5_1
            CREATE_TABLESPACE_stmt_5_1          =  *CREATE_TABLESPACE_stmt_5_1_0
+                                               |  *CREATE_TABLESPACE_stmt_5_1 *CREATE_TABLESPACE_stmt_5_1_0
            CREATE_TABLESPACE_stmt_5_1_0        =  EXTENTSIZE *number_of_pages_kmg
+                                               |  PREFETCHSIZE *number_of_pages_kmg
+                                               |  BUFFERPOOL *bufferpool_name
+                                               |  OVERHEAD *number_of_milliseconds
+                                               |  TRANSFERRATE *number_of_milliseconds
+                                               |  DROPPED TABLE RECOVERY *CREATE_TABLESPACE_stmt_5_1_1
            CREATE_TABLESPACE_stmt_5_1_1        =  ON | OFF
            CREATE_TABLE_stmt                   =  CREATE TABLE *table_name *CREATE_TABLE_stmt_1 *CREATE_TABLE_stmt_2
            CREATE_TABLE_stmt_1                 =  $'(' *CREATE_TABLE_stmt_1_1 $')'
+                                               |  OF *type_name *typed_table_options
+                                               |  LIKE *table_name
            CREATE_TABLE_stmt_1_1               =  *CREATE_TABLE_stmt_1_1_0
+                                               |  *CREATE_TABLE_stmt_1_1 $',' *CREATE_TABLE_stmt_1_1_0
            CREATE_TABLE_stmt_1_1_0             =  *column_definition
+                                               |  *unique_constraint
+                                               |  *referential_constraint
+                                               |  *check_constraint
            CREATE_TABLE_stmt_2                 =  epsilon | *CREATE_TABLE_stmt_2_1
            CREATE_TABLE_stmt_2_1               =  *CREATE_TABLE_stmt_2_1_0
+                                               |  *CREATE_TABLE_stmt_2_1 *CREATE_TABLE_stmt_2_1_0
            CREATE_TABLE_stmt_2_1_0             =  DATA CAPTURE NONE
+                                               |  DATA CAPTURE CHANGES
+                                               |  IN *tablespace_name *tablespace_options
+                                               |  PARTITIONING
+                                                  KEY
+                                                  $'('
+                                                  *CREATE_TABLE_stmt_2_1_1
+                                                  $')'
+                                                  *CREATE_TABLE_stmt_2_1_2
+                                               |  NOT LOGGED INITIALLY
            CREATE_TABLE_stmt_2_1_1             =  *CREATE_TABLE_stmt_2_1_1_0
+                                               |  *CREATE_TABLE_stmt_2_1_1 $',' *CREATE_TABLE_stmt_2_1_1_0
            CREATE_TABLE_stmt_2_1_1_0           =  *column_name
            CREATE_TABLE_stmt_2_1_2             =  epsilon | USING HASHING
            CREATE_TRIGGER_stmt                 =  CREATE
+                                                  TRIGGER
+                                                  *trigger_name
+                                                  *CREATE_TRIGGER_stmt_1
+                                                  *CREATE_TRIGGER_stmt_2
+                                                  ON
+                                                  *table_name
+                                                  *CREATE_TRIGGER_stmt_3
+                                                  *CREATE_TRIGGER_stmt_4
+                                                  MODE
+                                                  DB2SQL
+                                                  *CREATE_TRIGGER_stmt_5
            CREATE_TRIGGER_stmt_1               =  NO CASCADE BEFORE | AFTER
            CREATE_TRIGGER_stmt_2               =  INSERT | DELETE | UPDATE *CREATE_TRIGGER_stmt_2_1
            CREATE_TRIGGER_stmt_2_1             =  epsilon | OF *CREATE_TRIGGER_stmt_2_1_1
            CREATE_TRIGGER_stmt_2_1_1           =  *CREATE_TRIGGER_stmt_2_1_1_0
+                                               |  *CREATE_TRIGGER_stmt_2_1_1 $',' *CREATE_TRIGGER_stmt_2_1_1_0
            CREATE_TRIGGER_stmt_2_1_1_0         =  *column_name
            CREATE_TRIGGER_stmt_3               =  epsilon | REFERENCING *CREATE_TRIGGER_stmt_3_1
            CREATE_TRIGGER_stmt_3_1             =  *CREATE_TRIGGER_stmt_3_1_0
+                                               |  *CREATE_TRIGGER_stmt_3_1 *CREATE_TRIGGER_stmt_3_1_0
            CREATE_TRIGGER_stmt_3_1_0           =  OLD *CREATE_TRIGGER_stmt_3_1_1 *correlation_name
+                                               |  NEW *CREATE_TRIGGER_stmt_3_1_2 *correlation_name
+                                               |  OLD_TABLE *CREATE_TRIGGER_stmt_3_1_3 *identifier
+                                               |  NEW_TABLE *CREATE_TRIGGER_stmt_3_1_4 *identifier
            CREATE_TRIGGER_stmt_3_1_1           =  epsilon | AS
            CREATE_TRIGGER_stmt_3_1_2           =  epsilon | AS
            CREATE_TRIGGER_stmt_3_1_3           =  epsilon | AS
            CREATE_TRIGGER_stmt_3_1_4           =  epsilon | AS
            CREATE_TRIGGER_stmt_4               =  FOR EACH ROW | FOR EACH STATEMENT
            CREATE_TRIGGER_stmt_5               =  *triggered_action | *error $'_EOS_'
            CREATE_TYPE_structured_stmt         =  CREATE
+                                                  TYPE
+                                                  *type_name
+                                                  *CREATE_TYPE_structured_stmt_1
+                                                  AS
+                                                  $'('
+                                                  *CREATE_TYPE_structured_stmt_2
+                                                  $')'
+                                                  WITHOUT
+                                                  COMPARISONS
+                                                  NOT
+                                                  FINAL
+                                                  MODE
+                                                  DB2SQL
            CREATE_TYPE_structured_stmt_1       =  epsilon | UNDER *supertype_name
            CREATE_TYPE_structured_stmt_2       =  *attribute_definition
+                                               |  *CREATE_TYPE_structured_stmt_2 $',' *attribute_definition
            CREATE_VIEW_stmt                    =  CREATE VIEW *view_name *CREATE_VIEW_stmt_1 AS *CREATE_VIEW_stmt_2
            CREATE_VIEW_stmt_1                  =  epsilon
+                                               |  $'(' *CREATE_VIEW_stmt_1_1 $')'
+                                               |  OF
+                                                  *type_name
+                                                  MODE
+                                                  DB2SQL
+                                                  $'('
+                                                  *OID_column
+                                                  *CREATE_VIEW_stmt_1_2
+                                                  $')'
+                                               |  OF
+                                                  *type_name
+                                                  MODE
+                                                  DB2SQL
+                                                  *view_under_clause
+                                                  *CREATE_VIEW_stmt_1_3
+                                                  *CREATE_VIEW_stmt_1_4
            CREATE_VIEW_stmt_1_1                =  *CREATE_VIEW_stmt_1_1_0
+                                               |  *CREATE_VIEW_stmt_1_1 $',' *CREATE_VIEW_stmt_1_1_0
            CREATE_VIEW_stmt_1_1_0              =  *column_name
            CREATE_VIEW_stmt_1_2                =  epsilon | $',' *view_with_options
            CREATE_VIEW_stmt_1_3                =  epsilon | $'(' *view_with_options $')'
            CREATE_VIEW_stmt_1_4                =  epsilon | EXTEND
            CREATE_VIEW_stmt_2                  =  *CREATE_VIEW_stmt_2_1
+                                                  *fullselect
+                                                  *CREATE_VIEW_stmt_2_2
+                                                  *CREATE_VIEW_stmt_2_3
+                                               |  *error $'_EOS_'
            CREATE_VIEW_stmt_2_1                =  epsilon | WITH *CREATE_VIEW_stmt_2_1_1
            CREATE_VIEW_stmt_2_1_1              =  *common_table_expression
+                                               |  *CREATE_VIEW_stmt_2_1_1 $',' *common_table_expression
            CREATE_VIEW_stmt_2_2                =  epsilon | *order_by_clause
            CREATE_VIEW_stmt_2_3                =  epsilon | WITH *CREATE_VIEW_stmt_2_3_1 CHECK OPTION
            CREATE_VIEW_stmt_2_3_1              =  epsilon | CASCADED | LOCAL
            Create_Database_options             =  *identifier
            DEACTIVATE_DATABASE_cmd             =  DEACTIVATE
+                                                  *DEACTIVATE_DATABASE_cmd_1
+                                                  *database_alias
+                                                  *DEACTIVATE_DATABASE_cmd_2
            DEACTIVATE_DATABASE_cmd_1           =  DATABASE | DB
            DEACTIVATE_DATABASE_cmd_2           =  epsilon | USER *username *DEACTIVATE_DATABASE_cmd_2_1
            DEACTIVATE_DATABASE_cmd_2_1         =  epsilon | USING *password
            DECLARE_CURSOR_stmt                 =  DECLARE
+                                                  *cursor_name
+                                                  CURSOR
+                                                  *DECLARE_CURSOR_stmt_1
+                                                  FOR
+                                                  *DECLARE_CURSOR_stmt_2
            DECLARE_CURSOR_stmt_1               =  epsilon | WITH HOLD
            DECLARE_CURSOR_stmt_2               =  *select_stmt | *statement_name
            DELETE_stmt                         =  DELETE FROM *DELETE_stmt_1 *DELETE_stmt_2 *DELETE_stmt_3
            DELETE_stmt_1                       =  *table_or_view_name | ONLY $'(' *table_or_view_name $')'
            DELETE_stmt_2                       =  epsilon | *DELETE_stmt_2_1 *correlation_name
            DELETE_stmt_2_1                     =  epsilon | AS
            DELETE_stmt_3                       =  epsilon | WHERE *search_condition | WHERE CURRENT OF *cursor_name
            DEREGISTER_cmd                      =  DEREGISTER
+                                                  *DEREGISTER_cmd_1
+                                                  *DEREGISTER_cmd_2
+                                                  *registry
+                                                  USER
+                                                  *username
+                                                  *DEREGISTER_cmd_3
            DEREGISTER_cmd_1                    =  epsilon | DB2 SERVER
            DEREGISTER_cmd_2                    =  epsilon | IN
            DEREGISTER_cmd_3                    =  epsilon | PASSWORD *password
            DESCRIBE_cmd                        =  DESCRIBE *DESCRIBE_cmd_1
            DESCRIBE_cmd_1                      =  *fullselect | *DESCRIBE_cmd_1_1 *DESCRIBE_cmd_1_2
            DESCRIBE_cmd_1_1                    =  TABLE *table_name | INDEXES FOR TABLE *table_name
            DESCRIBE_cmd_1_2                    =  epsilon | SHOW DETAIL
            DESCRIBE_stmt                       =  DESCRIBE *statement_name INTO *descriptor_name
            DETACH_cmd                          =  DETACH
            DISCONNECT_stmt                     =  DISCONNECT *DISCONNECT_stmt_1
            DISCONNECT_stmt_1                   =  *server_name | CURRENT | ALL *DISCONNECT_stmt_1_1
            DISCONNECT_stmt_1_1                 =  epsilon | SQL
            DROP_DATABASE_cmd                   =  DROP *DROP_DATABASE_cmd_1 *database_alias *DROP_DATABASE_cmd_2
            DROP_DATABASE_cmd_1                 =  DATABASE | DB
            DROP_DATABASE_cmd_2                 =  epsilon | AT NODE
            DROP_NODE_VERIFY_cmd                =  DROP NODE VERIFY
            DROP_stmt                           =  DROP *DROP_stmt_1
            DROP_stmt_1                         =  ALIAS *alias_name
+                                               |  BUFFERPOOL *bufferpool_name
+                                               |  EVENT MONITOR *event_monitor_name
+                                               |  *DROP_stmt_1_1 *routine_name *DROP_stmt_1_2
+                                               |  SPECIFIC FUNCTION *specific_name
+                                               |  INDEX *index_name
+                                               |  NODEGROUP *nodegroup_name
+                                               |  PACKAGE *package_name
+                                               |  SPECIFIC PROCEDURE *specific_name
+                                               |  SCHEMA *schema_name RESTRICT
+                                               |  TABLE *table_name
+                                               |  TABLESPACE *tablespace_name
+                                               |  TRIGGER *trigger_name
+                                               |  *DROP_stmt_1_3 TYPE *type_name
+                                               |  VIEW *view_name
            DROP_stmt_1_1                       =  FUNCTION | PROCEDURE
            DROP_stmt_1_2                       =  epsilon | $'(' *DROP_stmt_1_2_1 $')'
            DROP_stmt_1_2_1                     =  *data_type | *DROP_stmt_1_2_1 $',' *data_type
            DROP_stmt_1_3                       =  epsilon | DISTINCT
            ECHO_cmd                            =  ECHO $'_DQ_STRING_'
            END_DECLARE_SECTION_stmt            =  END DECLARE SECTION
            ESQL_stmt                           =  *BEGIN_DECLARE_SECTION_stmt
+                                               |  *DECLARE_CURSOR_stmt
+                                               |  *END_DECLARE_SECTION_stmt
            EXECUTE_IMMEDIATE_stmt              =  EXECUTE IMMEDIATE *host_variable
            EXECUTE_stmt                        =  EXECUTE *statement_name *EXECUTE_stmt_1
            EXECUTE_stmt_1                      =  epsilon
+                                               |  USING *EXECUTE_stmt_1_1
+                                               |  USING DESCRIPTOR *descriptor_name
            EXECUTE_stmt_1_1                    =  *host_variable | *EXECUTE_stmt_1_1 $',' *host_variable
            EXPLAIN_FOR_clause                  =  FOR *explainable_SQL_stmt
            EXPLAIN_FOR_or_WITH_SNAPSHOT_clause =  FOR SNAPSHOT | WITH SNAPSHOT
            EXPLAIN_SET_QUERYNO_clause          =  SET QUERYNO $'_EQ_' *string_constant
            EXPLAIN_SET_QUERYTAG_clause         =  SET QUERYTAG $'_EQ_' *string_constant
            EXPLAIN_stmt                        =  EXPLAIN *EXPLAIN_stmt_1 *EXPLAIN_stmt_2
            EXPLAIN_stmt_1                      =  PLAN SELECTION | ALL | PLAN
            EXPLAIN_stmt_2                      =  *EXPLAIN_FOR_clause
+                                               |  *EXPLAIN_FOR_or_WITH_SNAPSHOT_clause *EXPLAIN_FOR_clause
+                                               |  *EXPLAIN_SET_QUERYNO_clause *EXPLAIN_FOR_clause
+                                               |  *EXPLAIN_FOR_or_WITH_SNAPSHOT_clause
+                                                  *EXPLAIN_SET_QUERYNO_clause
+                                                  *EXPLAIN_FOR_clause
+                                               |  *EXPLAIN_SET_QUERYTAG_clause *EXPLAIN_FOR_clause
+                                               |  *EXPLAIN_FOR_or_WITH_SNAPSHOT_clause
+                                                  *EXPLAIN_SET_QUERYTAG_clause
+                                                  *EXPLAIN_FOR_clause
+                                               |  *EXPLAIN_SET_QUERYNO_clause
+                                                  *EXPLAIN_SET_QUERYTAG_clause
+                                                  *EXPLAIN_FOR_clause
+                                               |  *EXPLAIN_FOR_or_WITH_SNAPSHOT_clause
+                                                  *EXPLAIN_SET_QUERYNO_clause
+                                                  *EXPLAIN_SET_QUERYTAG_clause
+                                                  *EXPLAIN_FOR_clause
            EXPORT_cmd                          =  EXPORT
+                                                  TO
+                                                  *filename
+                                                  OF
+                                                  *filetype
+                                                  *EXPORT_cmd_1
+                                                  *EXPORT_cmd_2
+                                                  *EXPORT_cmd_3
+                                                  *EXPORT_cmd_4
+                                                  *EXPORT_cmd_5
+                                                  *fullselect
            EXPORT_cmd_1                        =  epsilon | LOBS TO *EXPORT_cmd_1_1
            EXPORT_cmd_1_1                      =  *lob_path | *EXPORT_cmd_1_1 $',' *lob_path
            EXPORT_cmd_2                        =  epsilon | LOBFILE *EXPORT_cmd_2_1
            EXPORT_cmd_2_1                      =  *filename | *EXPORT_cmd_2_1 $',' *filename
            EXPORT_cmd_3                        =  epsilon | MODIFIED BY *filetype_mod
            EXPORT_cmd_4                        =  epsilon | METHOD N $'(' *EXPORT_cmd_4_1 $')'
            EXPORT_cmd_4_1                      =  *column_name | *EXPORT_cmd_4_1 $',' *column_name
            EXPORT_cmd_5                        =  epsilon | MESSAGES *message_file
            FETCH_stmt                          =  FETCH *cursor_name *FETCH_stmt_1 *FETCH_stmt_2
            FETCH_stmt_1                        =  epsilon | FROM
            FETCH_stmt_2                        =  INTO *FETCH_stmt_2_1 | USING DESCRIPTOR *descriptor_name
            FETCH_stmt_2_1                      =  *host_variable | *FETCH_stmt_2_1 $',' *host_variable
            FLUSH_EVENT_MONITOR_stmt            =  FLUSH EVENT MONITOR *event_monitor_name *FLUSH_EVENT_MONITOR_stmt_1
            FLUSH_EVENT_MONITOR_stmt_1          =  epsilon | BUFFER
            FORCE_APPLICATION_cmd               =  FORCE APPLICATION *FORCE_APPLICATION_cmd_1 *FORCE_APPLICATION_cmd_2
            FORCE_APPLICATION_cmd_1             =  ALL | $'(' *FORCE_APPLICATION_cmd_1_1 $')'
            FORCE_APPLICATION_cmd_1_1           =  *application_handle
+                                               |  *FORCE_APPLICATION_cmd_1_1 $',' *application_handle
            FORCE_APPLICATION_cmd_2             =  epsilon | MODE ASYNC
            FREE_LOCATOR_stmt                   =  FREE LOCATOR *FREE_LOCATOR_stmt_1
            FREE_LOCATOR_stmt_1                 =  *variable_name | *FREE_LOCATOR_stmt_1 $',' *variable_name
            GET_ADMIN_CONFIGURATION_cmd         =  GET ADMIN *GET_ADMIN_CONFIGURATION_cmd_1
            GET_ADMIN_CONFIGURATION_cmd_1       =  CONFIGURATION | CONFIG | CFG
            GET_AUTHORIZATIONS_cmd              =  GET AUTHORIZATIONS
            GET_CONNECTIONS_STATE_cmd           =  GET CONNECTION STATE
            GET_DATABASE_CONFIGURATION_cmd      =  GET
+                                                  *GET_DATABASE_CONFIGURATION_cmd_1
+                                                  *GET_DATABASE_CONFIGURATION_cmd_2
+                                                  FOR
+                                                  *database_alias
            GET_DATABASE_CONFIGURATION_cmd_1    =  DATABASE | DB
            GET_DATABASE_CONFIGURATION_cmd_2    =  CONFIGURATION | CONFIG | CFG
            GET_DATABASE_MANAGER_CONFIGURATION_cmd = GET
+                                                  *GET_DATABASE_MANAGER_CONFIGURATION_cmd_1
+                                                  *GET_DATABASE_MANAGER_CONFIGURATION_cmd_2
            GET_DATABASE_MANAGER_CONFIGURATION_cmd_1 = DATABASE MANAGER | DB MANAGER | DBM
            GET_DATABASE_MANAGER_CONFIGURATION_cmd_2 = CONFIGURATION | CONFIG | CFG
            GET_DATABASE_MANAGER_MONITOR_SWITCHES_cmd = GET *GET_DATABASE_MANAGER_MONITOR_SWITCHES_cmd_1 MONITOR SWITCHES
            GET_DATABASE_MANAGER_MONITOR_SWITCHES_cmd_1 = DATABASE MANAGER | DB MANAGER | DBM
            GET_INSTANCE_cmd                    =  GET INSTANCE
            GET_MONITOR_SWITCHES_cmd            =  GET MONITOR SWITCHES
            GET_SNAPSHOT_cmd                    =  GET SNAPSHOT FOR *GET_SNAPSHOT_cmd_1
            GET_SNAPSHOT_cmd_1                  =  DATABASE MANAGER
+                                               |  DB MANAGER
+                                               |  DBM
+                                               |  ALL DATABASES
+                                               |  ALL APPLICATIONS
+                                               |  ALL BUFFERPOOLS
+                                               |  APPLICATION *GET_SNAPSHOT_cmd_1_1
+                                               |  FCM FOR ALL NODES
+                                               |  LOCKS FOR APPLICATION *appl_id
+                                               |  *GET_SNAPSHOT_cmd_1_2 ON *database_alias
            GET_SNAPSHOT_cmd_1_1                =  APPLID *appl_id | AGENTID *agentid
            GET_SNAPSHOT_cmd_1_2                =  ALL
+                                               |  *GET_SNAPSHOT_cmd_1_2_1
+                                               |  APPLICATIONS
+                                               |  TABLES
+                                               |  TABLESPACES
+                                               |  LOCKS
+                                               |  BUFFERPOOLS
            GET_SNAPSHOT_cmd_1_2_1              =  DATABASE | DB
            GRANT_stmt                          =  GRANT *GRANT_stmt_1 ON *GRANT_stmt_2 TO *GRANT_stmt_3 *GRANT_stmt_4
            GRANT_stmt_1                        =  ALL *GRANT_stmt_1_1 | *GRANT_stmt_1_2
            GRANT_stmt_1_1                      =  epsilon | PRIVILEGES
            GRANT_stmt_1_2                      =  *GRANT_stmt_1_2_0 | *GRANT_stmt_1_2 $',' *GRANT_stmt_1_2_0
            GRANT_stmt_1_2_0                    =  BINDADD
+                                               |  CONNECT
+                                               |  CREATETAB
+                                               |  CREATE_NOT_FENCED
+                                               |  IMPLICIT_SCHEMA
+                                               |  DBADM
+                                               |  BIND
+                                               |  CONTROL
+                                               |  EXECUTE
+                                               |  ALTERIN
+                                               |  CREATEIN
+                                               |  DROPIN
+                                               |  ALTER
+                                               |  DELETE
+                                               |  INDEX
+                                               |  INSERT
+                                               |  SELECT
+                                               |  *GRANT_stmt_1_2_1 *GRANT_stmt_1_2_2
            GRANT_stmt_1_2_1                    =  REFERENCES | UPDATE
            GRANT_stmt_1_2_2                    =  epsilon | $'(' *GRANT_stmt_1_2_2_1 $')'
            GRANT_stmt_1_2_2_1                  =  *column_name | *GRANT_stmt_1_2_2_1 $',' *column_name
            GRANT_stmt_2                        =  DATABASE
+                                               |  INDEX *index_name
+                                               |  PACKAGE *package_name
+                                               |  SCHEMA *schema_name
+                                               |  *GRANT_stmt_2_1 *table_or_view_name
            GRANT_stmt_2_1                      =  epsilon | TABLE
            GRANT_stmt_3                        =  *GRANT_stmt_3_0 | *GRANT_stmt_3 $',' *GRANT_stmt_3_0
            GRANT_stmt_3_0                      =  *GRANT_stmt_3_1 *authorization_name | PUBLIC
            GRANT_stmt_3_1                      =  epsilon | USER | GROUP
            GRANT_stmt_4                        =  epsilon | WITH GRANT OPTION
            HELP_cmd                            =  HELP *HELP_cmd_1
            HELP_cmd_1                          =  epsilon | *character_string
            IMPORT_cmd                          =  IMPORT
+                                                  FROM
+                                                  *filename
+                                                  OF
+                                                  *filetype
+                                                  *IMPORT_cmd_1
+                                                  *IMPORT_cmd_2
+                                                  *IMPORT_cmd_3
+                                                  *IMPORT_cmd_4
+                                                  *IMPORT_cmd_5
+                                                  *IMPORT_cmd_6
+                                                  *IMPORT_cmd_7
            IMPORT_cmd_1                        =  epsilon | LOBS FROM *IMPORT_cmd_1_1
            IMPORT_cmd_1_1                      =  *lob_path | *IMPORT_cmd_1_1 $',' *lob_path
            IMPORT_cmd_2                        =  epsilon | MODIFIED BY *IMPORT_cmd_2_1
            IMPORT_cmd_2_1                      =  *filetype_mod | *IMPORT_cmd_2_1 *filetype_mod
            IMPORT_cmd_3                        =  epsilon | METHOD *IMPORT_cmd_3_1
            IMPORT_cmd_3_1                      =  L $'(' *IMPORT_cmd_3_1_1 $')' *IMPORT_cmd_3_1_2
+                                               |  N $'(' *IMPORT_cmd_3_1_3 $')'
+                                               |  P $'(' *IMPORT_cmd_3_1_4 $')'
            IMPORT_cmd_3_1_1                    =  *IMPORT_cmd_3_1_1_0 | *IMPORT_cmd_3_1_1 $',' *IMPORT_cmd_3_1_1_0
            IMPORT_cmd_3_1_1_0                  =  *column_start *column_end
            IMPORT_cmd_3_1_2                    =  epsilon | NULL INDICATORS $'(' *IMPORT_cmd_3_1_2_1 $')'
            IMPORT_cmd_3_1_2_1                  =  *IMPORT_cmd_3_1_2_1_0
+                                               |  *IMPORT_cmd_3_1_2_1 $',' *IMPORT_cmd_3_1_2_1_0
            IMPORT_cmd_3_1_2_1_0                =  $'_INTEGER_'
            IMPORT_cmd_3_1_3                    =  *column_name | *IMPORT_cmd_3_1_3 $',' *column_name
            IMPORT_cmd_3_1_4                    =  *column_position | *IMPORT_cmd_3_1_4 $',' *column_position
            IMPORT_cmd_4                        =  epsilon | COMMITCOUNT $'_INTEGER_'
            IMPORT_cmd_5                        =  epsilon | RESTARTCOUNT $'_INTEGER_'
            IMPORT_cmd_6                        =  epsilon | MESSAGES *message_file
            IMPORT_cmd_7                        =  *IMPORT_cmd_7_1 INTO *table_name *IMPORT_cmd_7_2
+                                               |  CREATE INTO *table_name *IMPORT_cmd_7_3 *tblspace_specs
            IMPORT_cmd_7_1                      =  INSERT | INSERT_UPDATE | REPLACE | REPLACE_CREATE
            IMPORT_cmd_7_2                      =  epsilon | $'(' *IMPORT_cmd_7_2_1 $')'
            IMPORT_cmd_7_2_1                    =  *insert_column | *IMPORT_cmd_7_2_1 $',' *insert_column
            IMPORT_cmd_7_3                      =  epsilon | $'(' *IMPORT_cmd_7_3_1 $')'
            IMPORT_cmd_7_3_1                    =  *insert_column | *IMPORT_cmd_7_3_1 $',' *insert_column
            INCLUDE_stmt                        =  INCLUDE *INCLUDE_stmt_1
            INCLUDE_stmt_1                      =  SQLCA | SQLDA | *include_name
            INITIALIZE_TAPE_cmd                 =  INITIALIZE TAPE *INITIALIZE_TAPE_cmd_1 *INITIALIZE_TAPE_cmd_2
            INITIALIZE_TAPE_cmd_1               =  epsilon | ON *device
            INITIALIZE_TAPE_cmd_2               =  epsilon | USING *blksize
            INSERT_stmt                         =  INSERT INTO *table_or_view_name *INSERT_stmt_1 *INSERT_stmt_2
            INSERT_stmt_1                       =  epsilon | $'(' *INSERT_stmt_1_1 $')'
            INSERT_stmt_1_1                     =  *column_name | *INSERT_stmt_1_1 $',' *column_name
            INSERT_stmt_2                       =  VALUES *INSERT_stmt_2_1
+                                               |  *INSERT_stmt_2_2 *subselect *INSERT_stmt_2_3
            INSERT_stmt_2_1                     =  *INSERT_stmt_2_1_0 | *INSERT_stmt_2_1 $',' *INSERT_stmt_2_1_0
            INSERT_stmt_2_1_0                   =  *INSERT_value | $'(' *INSERT_value $',' *INSERT_stmt_2_1_1 $')'
            INSERT_stmt_2_1_1                   =  *INSERT_value | *INSERT_stmt_2_1_1 $',' *INSERT_value
            INSERT_stmt_2_2                     =  epsilon | WITH *INSERT_stmt_2_2_1
            INSERT_stmt_2_2_1                   =  *common_table_expression
+                                               |  *INSERT_stmt_2_2_1 $',' *common_table_expression
            INSERT_stmt_2_3                     =  epsilon | *INSERT_stmt_2_3_1
            INSERT_stmt_2_3_1                   =  *INSERT_stmt_2_3_1_0 | *INSERT_stmt_2_3_1 *INSERT_stmt_2_3_1_0
            INSERT_stmt_2_3_1_0                 =  *set_operator fullselect
            INSERT_value                        =  *expression | NULL | DEFAULT
            INVOKE_STORED_PROCEDURE_cmd         =  INVOKE *program_name *INVOKE_STORED_PROCEDURE_cmd_1
            INVOKE_STORED_PROCEDURE_cmd_1       =  epsilon | USING *server_input_data
            LIST_ACTIVE_DATABASES_cmd           =  LIST ACTIVE DATABASES
            LIST_APPLICATIONS_cmd               =  LIST APPLICATIONS *LIST_APPLICATIONS_cmd_1 *LIST_APPLICATIONS_cmd_2
            LIST_APPLICATIONS_cmd_1             =  epsilon | FOR *LIST_APPLICATIONS_cmd_1_1 *database_alias
            LIST_APPLICATIONS_cmd_1_1           =  DATABASE | DB
            LIST_APPLICATIONS_cmd_2             =  epsilon | SHOW DETAIL
            LIST_BACKUP_HISTORY_cmd             =  LIST
+                                                  *LIST_BACKUP_HISTORY_cmd_1
+                                                  *LIST_BACKUP_HISTORY_cmd_2
+                                                  FOR
+                                                  *LIST_BACKUP_HISTORY_cmd_3
+                                                  *database_alias
            LIST_BACKUP_HISTORY_cmd_1           =  BACKUP | HISTORY
            LIST_BACKUP_HISTORY_cmd_2           =  ALL | SINCE *timestamp | CONTAINING *object_name
            LIST_BACKUP_HISTORY_cmd_3           =  epsilon | DATABASE | DB
            LIST_COMMAND_OPTIONS_cmd            =  LIST COMMAND OPTIONS
            LIST_DATABASE_DIRECTORY_cmd         =  LIST
+                                                  *LIST_DATABASE_DIRECTORY_cmd_1
+                                                  DIRECTORY
+                                                  *LIST_DATABASE_DIRECTORY_cmd_2
            LIST_DATABASE_DIRECTORY_cmd_1       =  DATABASE | DB
            LIST_DATABASE_DIRECTORY_cmd_2       =  epsilon | ON *path_or_drive
            LIST_DCS_APPLICATIONS_cmd           =  LIST DCS APPLICATIONS *LIST_DCS_APPLICATIONS_cmd_1
            LIST_DCS_APPLICATIONS_cmd_1         =  epsilon | SHOW DETAIL
            LIST_DCS_DIRECTORY_cmd              =  LIST DCS DIRECTORY
            LIST_DRDA_INDOUBT_TRANSACTIONS_cmd  =  LIST DRDA INDOUBT TRANSACTIONS *LIST_DRDA_INDOUBT_TRANSACTIONS_cmd_1
            LIST_DRDA_INDOUBT_TRANSACTIONS_cmd_1 = epsilon | WITH PROMPTING
            LIST_INDOUBT_TRANSACTIONS_cmd       =  LIST INDOUBT TRANSACTIONS *LIST_INDOUBT_TRANSACTIONS_cmd_1
            LIST_INDOUBT_TRANSACTIONS_cmd_1     =  epsilon | WITH PROMPTING
            LIST_NODEGROUPS_cmd                 =  LIST NODEGROUPS *LIST_NODEGROUPS_cmd_1
            LIST_NODEGROUPS_cmd_1               =  epsilon | SHOW DETAIL
            LIST_NODES_cmd                      =  LIST NODES
            LIST_NODE_DIRECTORY_cmd             =  LIST
+                                                  *LIST_NODE_DIRECTORY_cmd_1
+                                                  NODE
+                                                  DIRECTORY
+                                                  *LIST_NODE_DIRECTORY_cmd_2
            LIST_NODE_DIRECTORY_cmd_1           =  epsilon | ADMIN
            LIST_NODE_DIRECTORY_cmd_2           =  epsilon | SHOW DETAIL
            LIST_ODBC_DATA_SOURCES_cmd          =  LIST *LIST_ODBC_DATA_SOURCES_cmd_1 ODBC DATA SOURCES
            LIST_ODBC_DATA_SOURCES_cmd_1        =  epsilon | USER | SYSTEM
            LIST_PACKAGES_TABLES_cmd            =  LIST *LIST_PACKAGES_TABLES_cmd_1 *LIST_PACKAGES_TABLES_cmd_2
            LIST_PACKAGES_TABLES_cmd_1          =  PACKAGES | TABLES
            LIST_PACKAGES_TABLES_cmd_2          =  epsilon | FOR *LIST_PACKAGES_TABLES_cmd_2_1
            LIST_PACKAGES_TABLES_cmd_2_1        =  USER | ALL | SCHEMA | SYSTEM
            LIST_TABLESPACES_cmd                =  LIST TABLESPACES *LIST_TABLESPACES_cmd_1
            LIST_TABLESPACES_cmd_1              =  epsilon | SHOW DETAIL
            LIST_TABLESPACE_CONTAINERS_cmd      =  LIST
+                                                  TABLESPACE
+                                                  CONTAINERS
+                                                  FOR
+                                                  *tablespace_id
+                                                  *LIST_TABLESPACE_CONTAINERS_cmd_1
            LIST_TABLESPACE_CONTAINERS_cmd_1    =  epsilon | SHOW DETAIL
            LOAD_QUERY_cmd                      =  LOAD QUERY *remote_file *LOAD_QUERY_cmd_1
            LOAD_QUERY_cmd_1                    =  epsilon | TO *local_message_file
            LOCK_TABLE_stmt                     =  LOCK TABLE *table_name IN *LOCK_TABLE_stmt_1 MODE
            LOCK_TABLE_stmt_1                   =  SHARE | EXCLUSIVE
            MIGRATE_DATABASE_cmd                =  MIGRATE
+                                                  *MIGRATE_DATABASE_cmd_1
+                                                  *database_alias
+                                                  *MIGRATE_DATABASE_cmd_2
            MIGRATE_DATABASE_cmd_1              =  DATABASE | DB
            MIGRATE_DATABASE_cmd_2              =  epsilon | USER *username *MIGRATE_DATABASE_cmd_2_1
            MIGRATE_DATABASE_cmd_2_1            =  epsilon | USING *password
            OID_column                          =  REF IS *OID_column_name USER GENERATED
            OID_column_definition               =  REF IS *OID_column_name USER GENERATED
            OID_column_name                     =  *identifier
            OPEN_stmt                           =  OPEN *cursor_name *OPEN_stmt_1
            OPEN_stmt_1                         =  epsilon | USING *OPEN_stmt_1_1 | USING DESCRIPTOR *descriptor_name
            OPEN_stmt_1_1                       =  *host_variable | *OPEN_stmt_1_1 $',' *host_variable
            PREPARE_stmt                        =  PREPARE *statement_name *PREPARE_stmt_1 FROM *host_variable
            PREPARE_stmt_1                      =  epsilon | INTO *descriptor_name
            PRUNE_HISTORY_cmd                   =  PRUNE HISTORY *timestamp *PRUNE_HISTORY_cmd_1
            PRUNE_HISTORY_cmd_1                 =  epsilon | WITH FORCE OPTION
            QUERY_CLIENT_cmd                    =  QUERY CLIENT
            QUIESCE_TABLESPACES_FOR_TABLE_cmd   =  QUIESCE
+                                                  TABLESPACES
+                                                  FOR
+                                                  TABLE
+                                                  *table_name
+                                                  *QUIESCE_TABLESPACES_FOR_TABLE_cmd_1
            QUIESCE_TABLESPACES_FOR_TABLE_cmd_1 =  SHARE | INTENT TO UPDATE | EXCLUSIVE | RESET
            QUIT_cmd                            =  QUIT
            REBIND_cmd                          =  REBIND *REBIND_cmd_1 *package_name
            REBIND_cmd_1                        =  epsilon | PACKAGE
            REDISTRIBUTE_NODEGROUP_cmd          =  REDISTRIBUTE NODEGROUP *nodegroup *REDISTRIBUTE_NODEGROUP_cmd_1
            REDISTRIBUTE_NODEGROUP_cmd_1        =  UNIFORM
+                                               |  USING DISTFILE *distfile
+                                               |  USING TARGETMAP *targetmap
+                                               |  CONTINUE
+                                               |  ROLLBACK
            REFRESH_TABLE_stmt                  =  REFRESH TABLE *table_name
            REGISTER_cmd                        =  REGISTER
+                                                  *REGISTER_cmd_1
+                                                  *REGISTER_cmd_2
+                                                  *registry
+                                                  USER
+                                                  *username
+                                                  *REGISTER_cmd_3
            REGISTER_cmd_1                      =  epsilon | DB2 SERVER
            REGISTER_cmd_2                      =  epsilon | IN
            REGISTER_cmd_3                      =  epsilon | PASSWORD *password
            RELEASE_stmt                        =  RELEASE *RELEASE_stmt_1
            RELEASE_stmt_1                      =  *server_name | CURRENT | ALL *RELEASE_stmt_1_1
            RELEASE_stmt_1_1                    =  epsilon | SQL
            RENAME_TABLE_stmt                   =  RENAME *RENAME_TABLE_stmt_1 *source_table_name TO *target_identifier
            RENAME_TABLE_stmt_1                 =  epsilon | TABLE
            REORGANIZE_TABLE_cmd                =  REORG
+                                                  TABLE
+                                                  *table_name
+                                                  *REORGANIZE_TABLE_cmd_1
+                                                  *REORGANIZE_TABLE_cmd_2
            REORGANIZE_TABLE_cmd_1              =  epsilon | INDEX *index_name
            REORGANIZE_TABLE_cmd_2              =  epsilon | USE *tablespace_name
            REORGCHK_cmd                        =  REORGCHK *REORGCHK_cmd_1 *REORGCHK_cmd_2
            REORGCHK_cmd_1                      =  epsilon | *REORGCHK_cmd_1_1 STATISTICS
            REORGCHK_cmd_1_1                    =  UPDATE | CURRENT
            REORGCHK_cmd_2                      =  epsilon | ON TABLE *REORGCHK_cmd_2_1
            REORGCHK_cmd_2_1                    =  USER | SYSTEM | ALL | *table_name
            RESET_ADMIN_CONFIGURATION_cmd       =  RESET ADMIN *RESET_ADMIN_CONFIGURATION_cmd_1
            RESET_ADMIN_CONFIGURATION_cmd_1     =  CONFIGURATION | CONFIG | CFG
            RESET_DATABASE_CONFIGURATION_cmd    =  RESET
+                                                  *RESET_DATABASE_CONFIGURATION_cmd_1
+                                                  *RESET_DATABASE_CONFIGURATION_cmd_2
+                                                  FOR
+                                                  *database_alias
            RESET_DATABASE_CONFIGURATION_cmd_1  =  DATABASE | DB
            RESET_DATABASE_CONFIGURATION_cmd_2  =  CONFIGURATION | CONFIG | CFG
            RESET_DATABASE_MANAGER_CONFIGURATION_cmd = RESET
+                                                  *RESET_DATABASE_MANAGER_CONFIGURATION_cmd_1
+                                                  *RESET_DATABASE_MANAGER_CONFIGURATION_cmd_2
            RESET_DATABASE_MANAGER_CONFIGURATION_cmd_1 = DATABASE MANAGER | DB MANAGER | DBM
            RESET_DATABASE_MANAGER_CONFIGURATION_cmd_2 = CONFIGURATION | CONFIG | CFG
            RESET_MONITOR_cmd                   =  RESET MONITOR *RESET_MONITOR_cmd_1
            RESET_MONITOR_cmd_1                 =  ALL | FOR *RESET_MONITOR_cmd_1_1 *database_alias
            RESET_MONITOR_cmd_1_1               =  DATABASE | DB
            RESTART_DATABASE_cmd                =  RESTART
+                                                  *RESTART_DATABASE_cmd_1
+                                                  *database_alias
+                                                  *RESTART_DATABASE_cmd_2
            RESTART_DATABASE_cmd_1              =  DATABASE | DB
            RESTART_DATABASE_cmd_2              =  epsilon | USER *username *RESTART_DATABASE_cmd_2_1
            RESTART_DATABASE_cmd_2_1            =  epsilon | USING *password
            RESTORE_DATABASE_cmd                =  RESTORE *RESTORE_DATABASE_cmd_1 *source_database_alias
            RESTORE_DATABASE_cmd_1              =  DATABASE | DB
            REVOKE_stmt                         =  REVOKE
+                                                  *REVOKE_stmt_1
+                                                  ON
+                                                  *REVOKE_stmt_2
+                                                  FROM
+                                                  *REVOKE_stmt_3
+                                                  *REVOKE_stmt_4
            REVOKE_stmt_1                       =  ALL *REVOKE_stmt_1_1 | *REVOKE_stmt_1_2
            REVOKE_stmt_1_1                     =  epsilon | PRIVILEGES
            REVOKE_stmt_1_2                     =  *REVOKE_stmt_1_2_0 | *REVOKE_stmt_1_2 $',' *REVOKE_stmt_1_2_0
            REVOKE_stmt_1_2_0                   =  BINDADD
+                                               |  CONNECT
+                                               |  CREATETAB
+                                               |  CREATE_NOT_FENCED
+                                               |  IMPLICIT_SCHEMA
+                                               |  DBADM
+                                               |  BIND
+                                               |  CONTROL
+                                               |  EXECUTE
+                                               |  ALTERIN
+                                               |  CREATEIN
+                                               |  DROPIN
+                                               |  ALTER
+                                               |  DELETE
+                                               |  INDEX
+                                               |  INSERT
+                                               |  SELECT
+                                               |  *REVOKE_stmt_1_2_1 *REVOKE_stmt_1_2_2
            REVOKE_stmt_1_2_1                   =  REFERENCES | UPDATE
            REVOKE_stmt_1_2_2                   =  epsilon | $'(' *REVOKE_stmt_1_2_2_1 $')'
            REVOKE_stmt_1_2_2_1                 =  *column_name | *REVOKE_stmt_1_2_2_1 $',' *column_name
            REVOKE_stmt_2                       =  DATABASE
+                                               |  INDEX *index_name
+                                               |  PACKAGE *package_name
+                                               |  SCHEMA *schema_name
+                                               |  *REVOKE_stmt_2_1 *table_or_view_name
            REVOKE_stmt_2_1                     =  epsilon | TABLE
            REVOKE_stmt_3                       =  *REVOKE_stmt_3_0 | *REVOKE_stmt_3 $',' *REVOKE_stmt_3_0
            REVOKE_stmt_3_0                     =  *REVOKE_stmt_3_1 *authorization_name | PUBLIC
            REVOKE_stmt_3_1                     =  epsilon | USER | GROUP
            REVOKE_stmt_4                       =  epsilon | WITH GRANT OPTION
            REWIND_TAPE_cmd                     =  REWIND TAPE *REWIND_TAPE_cmd_1
            REWIND_TAPE_cmd_1                   =  epsilon | ON *device
            ROLLBACK_stmt                       =  ROLLBACK *ROLLBACK_stmt_1
            ROLLBACK_stmt_1                     =  epsilon | WORK
            ROLLFORWARD_DATABASE_cmd            =  ROLLFORWARD *ROLLFORWARD_DATABASE_cmd_1 *database_alias
            ROLLFORWARD_DATABASE_cmd_1          =  DATABASE | DB
            RUNSTATS_cmd                        =  RUNSTATS ON TABLE *table_name *RUNSTATS_cmd_1 *RUNSTATS_cmd_2
            RUNSTATS_cmd_1                      =  epsilon
+                                               |  WITH DISTRIBUTION *RUNSTATS_cmd_1_1
+                                               |  *RUNSTATS_cmd_1_2 *RUNSTATS_cmd_1_3 *RUNSTATS_cmd_1_4
            RUNSTATS_cmd_1_1                    =  epsilon | AND *RUNSTATS_cmd_1_1_1 *RUNSTATS_cmd_1_1_2
            RUNSTATS_cmd_1_1_1                  =  epsilon | DETAILED
            RUNSTATS_cmd_1_1_2                  =  INDEXES ALL | INDEX *index_name
            RUNSTATS_cmd_1_2                    =  AND | FOR
            RUNSTATS_cmd_1_3                    =  epsilon | DETAILED
            RUNSTATS_cmd_1_4                    =  INDEXES ALL | INDEX *index_name
            RUNSTATS_cmd_2                      =  epsilon | SHRLEVEL *RUNSTATS_cmd_2_1
            RUNSTATS_cmd_2_1                    =  CHANGE | REFERENCE
            SELECT_INTO_stmt                    =  *select_clause
+                                                  INTO
+                                                  *SELECT_INTO_stmt_1
+                                                  *from_clause
+                                                  *SELECT_INTO_stmt_2
+                                                  *SELECT_INTO_stmt_3
+                                                  *SELECT_INTO_stmt_4
            SELECT_INTO_stmt_1                  =  *host_variable | *SELECT_INTO_stmt_1 $',' *host_variable
            SELECT_INTO_stmt_2                  =  epsilon | *where_clause
            SELECT_INTO_stmt_3                  =  epsilon | *group_by_clause
            SELECT_INTO_stmt_4                  =  epsilon | *having_clause
            SET_CLIENT_cmd                      =  SET CLIENT
            SET_CONNECTION_stmt                 =  SET CONNECTION *server_name
            SET_CURRENT_DEGREE_stmt             =  SET
+                                                  CURRENT
+                                                  DEGREE
+                                                  *SET_CURRENT_DEGREE_stmt_1
+                                                  *SET_CURRENT_DEGREE_stmt_2
            SET_CURRENT_DEGREE_stmt_1           =  epsilon | $'_EQ_'
            SET_CURRENT_DEGREE_stmt_2           =  *string_constant | *host_variable
            SET_CURRENT_EXPLAIN_MODE_stmt       =  SET
+                                                  CURRENT
+                                                  EXPLAIN
+                                                  MODE
+                                                  *SET_CURRENT_EXPLAIN_MODE_stmt_1
+                                                  *SET_CURRENT_EXPLAIN_MODE_stmt_2
            SET_CURRENT_EXPLAIN_MODE_stmt_1     =  epsilon | $'_EQ_'
            SET_CURRENT_EXPLAIN_MODE_stmt_2     =  NO
+                                               |  YES
+                                               |  EXPLAIN
+                                               |  RECOMMEND INDEXES
+                                               |  EVALUATE INDEXES
+                                               |  *host_variable
            SET_CURRENT_EXPLAIN_SNAPSHOT_stmt   =  SET
+                                                  CURRENT
+                                                  EXPLAIN
+                                                  SNAPSHOT
+                                                  *SET_CURRENT_EXPLAIN_SNAPSHOT_stmt_1
+                                                  *SET_CURRENT_EXPLAIN_SNAPSHOT_stmt_2
            SET_CURRENT_EXPLAIN_SNAPSHOT_stmt_1 =  epsilon | $'_EQ_'
            SET_CURRENT_EXPLAIN_SNAPSHOT_stmt_2 =  NO | YES | EXPLAIN | *host_variable
            SET_CURRENT_PACKAGESET_stmt         =  SET
+                                                  CURRENT
+                                                  PACKAGESET
+                                                  *SET_CURRENT_PACKAGESET_stmt_1
+                                                  *SET_CURRENT_PACKAGESET_stmt_2
            SET_CURRENT_PACKAGESET_stmt_1       =  epsilon | $'_EQ_'
            SET_CURRENT_PACKAGESET_stmt_2       =  *string_constant | *host_variable
            SET_CURRENT_QUERY_OPTIMIZATION_stmt =  SET
+                                                  CURRENT
+                                                  QUERY
+                                                  OPTIMIZATION
+                                                  *SET_CURRENT_QUERY_OPTIMIZATION_stmt_1
+                                                  *SET_CURRENT_QUERY_OPTIMIZATION_stmt_2
            SET_CURRENT_QUERY_OPTIMIZATION_stmt_1 = epsilon | $'_EQ_'
            SET_CURRENT_QUERY_OPTIMIZATION_stmt_2 = $'_INTEGER_' | *host_variable
            SET_CURRENT_REFRESH_AGE_stmt        =  SET
+                                                  CURRENT
+                                                  REFRESH
+                                                  AGE
+                                                  *SET_CURRENT_REFRESH_AGE_stmt_1
+                                                  *SET_CURRENT_REFRESH_AGE_stmt_2
            SET_CURRENT_REFRESH_AGE_stmt_1      =  epsilon | $'_EQ_'
            SET_CURRENT_REFRESH_AGE_stmt_2      =  *numeric_constant | ANY | *host_variable
            SET_EVENT_MONITOR_STATE_stmt        =  SET
+                                                  EVENT
+                                                  MONITOR
+                                                  *event_monitor_name
+                                                  STATE
+                                                  *SET_EVENT_MONITOR_STATE_stmt_1
+                                                  *SET_EVENT_MONITOR_STATE_stmt_2
            SET_EVENT_MONITOR_STATE_stmt_1      =  epsilon | $'_EQ_'
            SET_EVENT_MONITOR_STATE_stmt_2      =  $'_INTEGER_' | *host_variable
            SET_INTEGRITY_stmt                  =  SET *SET_INTEGRITY_stmt_1 FOR *SET_INTEGRITY_stmt_2
            SET_INTEGRITY_stmt_1                =  epsilon | INTEGRITY | CONSTRAINTS
            SET_INTEGRITY_stmt_2                =  *SET_INTEGRITY_stmt_2_1 *SET_INTEGRITY_stmt_2_2
+                                               |  *SET_INTEGRITY_stmt_2_3 IMMEDIATE UNCHECKED
            SET_INTEGRITY_stmt_2_1              =  *table_name | *SET_INTEGRITY_stmt_2_1 $',' *table_name
            SET_INTEGRITY_stmt_2_2              =  OFF
+                                               |  TO DATALINK RECONCILE PENDING
+                                               |  IMMEDIATE
+                                                  CHECKED
+                                                  *SET_INTEGRITY_stmt_2_2_1
+                                                  *SET_INTEGRITY_stmt_2_2_2
            SET_INTEGRITY_stmt_2_2_1            =  epsilon | INCREMENTAL
            SET_INTEGRITY_stmt_2_2_2            =  epsilon | *exception_clause
            SET_INTEGRITY_stmt_2_3              =  *SET_INTEGRITY_stmt_2_3_0
+                                               |  *SET_INTEGRITY_stmt_2_3 $',' *SET_INTEGRITY_stmt_2_3_0
            SET_INTEGRITY_stmt_2_3_0            =  *table_name *integrity_options
            SET_PATH_stmt                       =  SET *SET_PATH_stmt_1 PATH *SET_PATH_stmt_2 *SET_PATH_stmt_3
            SET_PATH_stmt_1                     =  epsilon | CURRENT *SET_PATH_stmt_1_1
            SET_PATH_stmt_1_1                   =  epsilon | FUNCTION
            SET_PATH_stmt_2                     =  epsilon | $'_EQ_'
            SET_PATH_stmt_3                     =  *SET_PATH_stmt_3_0 | *SET_PATH_stmt_3 $',' *SET_PATH_stmt_3_0
            SET_PATH_stmt_3_0                   =  *schema_name
+                                               |  SYSTEM PATH
+                                               |  USER
+                                               |  CURRENT *SET_PATH_stmt_3_1 PATH
+                                               |  *string_constant
            SET_PATH_stmt_3_1                   =  epsilon | FUNCTION
            SET_RUNTIME_DEGREE_cmd              =  SET
+                                                  RUNTIME
+                                                  DEGREE
+                                                  FOR
+                                                  *SET_RUNTIME_DEGREE_cmd_1
+                                                  *SET_RUNTIME_DEGREE_cmd_2
            SET_RUNTIME_DEGREE_cmd_1            =  ALL | $'(' *SET_RUNTIME_DEGREE_cmd_1_1 $')'
            SET_RUNTIME_DEGREE_cmd_1_1          =  *application_handle
+                                               |  *SET_RUNTIME_DEGREE_cmd_1_1 $',' *application_handle
            SET_RUNTIME_DEGREE_cmd_2            =  epsilon | TO *degree
            SET_SCHEMA_stmt                     =  SET *SET_SCHEMA_stmt_1 SCHEMA *SET_SCHEMA_stmt_2 *SET_SCHEMA_stmt_3
            SET_SCHEMA_stmt_1                   =  epsilon | CURRENT
            SET_SCHEMA_stmt_2                   =  epsilon | $'_EQ_'
            SET_SCHEMA_stmt_3                   =  *schema_name | USER | *string_constant
            SET_TABLESPACE_CONTAINERS_cmd       =  SET TABLESPACE CONTAINERS FOR *tablespace_id
            SET_TAPE_POSITION_cmd               =  SET TAPE POSITION *SET_TAPE_POSITION_cmd_1 TO $'_INTEGER_'
            SET_TAPE_POSITION_cmd_1             =  epsilon | ON *device
            SET_transition_variable             =  SET *SET_transition_variable_1
            SET_transition_variable_1           =  *transition_variable $'_EQ_' *SET_transition_variable_1_1
+                                               |  $'('
+                                                  *SET_transition_variable_1_2
+                                                  $')'
+                                                  $'_EQ_'
+                                                  $'('
+                                                  *SET_transition_variable_1_3
+                                                  $')'
            SET_transition_variable_1_1         =  *expression | NULL | DEFAULT
            SET_transition_variable_1_2         =  *transition_variable
+                                               |  *SET_transition_variable_1_2 $',' *transition_variable
            SET_transition_variable_1_3         =  *SET_transition_variable_1_3_0
+                                               |  *SET_transition_variable_1_3 $',' *SET_transition_variable_1_3_0
            SET_transition_variable_1_3_0       =  *expression | NULL | DEFAULT
            SIGNAL_SQLSTATE_stmt                =  SIGNAL SQLSTATE *string_constant $'(' *diagnostic_string $')'
            SQL_stmt                            =  *ALTER_BUFFERPOOL_stmt
+                                               |  *ALTER_NODEGROUP_stmt
+                                               |  *ALTER_TABLE_stmt
+                                               |  *ALTER_TABLESPACE_stmt
+                                               |  *ALTER_TYPE_stmt
+                                               |  *ALTER_VIEW_stmt
+                                               |  *CALL_stmt
+                                               |  *CLOSE_stmt
+                                               |  *COMMENT_ON_stmt
+                                               |  *COMMIT_stmt
+                                               |  *CONNECT_stmt
+                                               |  *CREATE_ALIAS_stmt
+                                               |  *CREATE_BUFFERPOOL_stmt
+                                               |  *CREATE_DISTINCT_TYPE_stmt
+                                               |  *CREATE_EVENT_MONITOR_stmt
+                                               |  *CREATE_FUNCTION_stmt
+                                               |  *CREATE_INDEX_stmt
+                                               |  *CREATE_NODEGROUP_stmt
+                                               |  *CREATE_PROCEDURE_stmt
+                                               |  *CREATE_SCHEMA_stmt
+                                               |  *CREATE_TABLE_stmt
+                                               |  *CREATE_SUMMARY_TABLE_stmt
+                                               |  *CREATE_TABLESPACE_stmt
+                                               |  *CREATE_TRIGGER_stmt
+                                               |  *CREATE_TYPE_structured_stmt
+                                               |  *CREATE_VIEW_stmt
+                                               |  *DELETE_stmt
+                                               |  *DESCRIBE_stmt
+                                               |  *DISCONNECT_stmt
+                                               |  *DROP_stmt
+                                               |  *EXECUTE_stmt
+                                               |  *EXECUTE_IMMEDIATE_stmt
+                                               |  *EXPLAIN_stmt
+                                               |  *FETCH_stmt
+                                               |  *FLUSH_EVENT_MONITOR_stmt
+                                               |  *FREE_LOCATOR_stmt
+                                               |  *GRANT_stmt
+                                               |  *INCLUDE_stmt
+                                               |  *INSERT_stmt
+                                               |  *LOCK_TABLE_stmt
+                                               |  *OPEN_stmt
+                                               |  *PREPARE_stmt
+                                               |  *REFRESH_TABLE_stmt
+                                               |  *RELEASE_stmt
+                                               |  *RENAME_TABLE_stmt
+                                               |  *REVOKE_stmt
+                                               |  *ROLLBACK_stmt
+                                               |  *SELECT_INTO_stmt
+                                               |  *SET_CONNECTION_stmt
+                                               |  *SET_INTEGRITY_stmt
+                                               |  *SET_CURRENT_DEGREE_stmt
+                                               |  *SET_CURRENT_EXPLAIN_MODE_stmt
+                                               |  *SET_CURRENT_EXPLAIN_SNAPSHOT_stmt
+                                               |  *SET_CURRENT_PACKAGESET_stmt
+                                               |  *SET_CURRENT_QUERY_OPTIMIZATION_stmt
+                                               |  *SET_CURRENT_REFRESH_AGE_stmt
+                                               |  *SET_EVENT_MONITOR_STATE_stmt
+                                               |  *SET_PATH_stmt
+                                               |  *SET_SCHEMA_stmt
+                                               |  *SET_transition_variable
+                                               |  *SIGNAL_SQLSTATE_stmt
+                                               |  *UPDATE_stmt
+                                               |  *VALUES_stmt
+                                               |  *WHENEVER_stmt
            START_DATABASE_MANAGER_cmd          =  START *START_DATABASE_MANAGER_cmd_1
            START_DATABASE_MANAGER_cmd_1        =  DATABASE MANAGER | DB MANAGER | DBM
            STOP_DATABASE_MANAGER_cmd           =  STOP *STOP_DATABASE_MANAGER_cmd_1
            STOP_DATABASE_MANAGER_cmd_1         =  DATABASE MANAGER | DB MANAGER | DBM
            TERMINATE_cmd                       =  TERMINATE
            UNCATALOG_DATABASE_cmd              =  UNCATALOG *UNCATALOG_DATABASE_cmd_1 *database_alias
            UNCATALOG_DATABASE_cmd_1            =  DATABASE | DB
            UNCATALOG_DCS_DATABASE_cmd          =  UNCATALOG DCS *UNCATALOG_DCS_DATABASE_cmd_1 *database_alias
            UNCATALOG_DCS_DATABASE_cmd_1        =  DATABASE | DB
            UNCATALOG_NODE_cmd                  =  UNCATALOG NODE *nodename
            UNCATALOG_ODBC_DATA_SOURCE_cmd      =  UNCATALOG
+                                                  *UNCATALOG_ODBC_DATA_SOURCE_cmd_1
+                                                  ODBC
+                                                  DATA
+                                                  SOURCE
+                                                  *data_source_name
            UNCATALOG_ODBC_DATA_SOURCE_cmd_1    =  epsilon | USER | SYSTEM
            UPDATE_ADMIN_CONFIGURATION_cmd      =  UPDATE
+                                                  ADMIN
+                                                  *UPDATE_ADMIN_CONFIGURATION_cmd_1
+                                                  USING
+                                                  *UPDATE_ADMIN_CONFIGURATION_cmd_2
            UPDATE_ADMIN_CONFIGURATION_cmd_1    =  CONFIGURATION | CONFIG | CFG
            UPDATE_ADMIN_CONFIGURATION_cmd_2    =  *UPDATE_ADMIN_CONFIGURATION_cmd_2_0
+                                               |  *UPDATE_ADMIN_CONFIGURATION_cmd_2
+                                                  *UPDATE_ADMIN_CONFIGURATION_cmd_2_0
            UPDATE_ADMIN_CONFIGURATION_cmd_2_0  =  *config_keyword *value
            UPDATE_COMMAND_OPTIONS_cmd          =  UPDATE COMMAND OPTIONS USING *UPDATE_COMMAND_OPTIONS_cmd_1
            UPDATE_COMMAND_OPTIONS_cmd_1        =  *UPDATE_COMMAND_OPTIONS_cmd_1_0
+                                               |  *UPDATE_COMMAND_OPTIONS_cmd_1 *UPDATE_COMMAND_OPTIONS_cmd_1_0
            UPDATE_COMMAND_OPTIONS_cmd_1_0      =  *option_letter *UPDATE_COMMAND_OPTIONS_cmd_1_1
            UPDATE_COMMAND_OPTIONS_cmd_1_1      =  ON *value | OFF
            UPDATE_DATABASE_CONFIGURATION_cmd   =  UPDATE
+                                                  *UPDATE_DATABASE_CONFIGURATION_cmd_1
+                                                  *UPDATE_DATABASE_CONFIGURATION_cmd_2
+                                                  FOR
+                                                  *database_alias
+                                                  USING
+                                                  *UPDATE_DATABASE_CONFIGURATION_cmd_3
            UPDATE_DATABASE_CONFIGURATION_cmd_1 =  DATABASE | DB
            UPDATE_DATABASE_CONFIGURATION_cmd_2 =  CONFIGURATION | CONFIG | CFG
            UPDATE_DATABASE_CONFIGURATION_cmd_3 =  *UPDATE_DATABASE_CONFIGURATION_cmd_3_0
+                                               |  *UPDATE_DATABASE_CONFIGURATION_cmd_3
+                                                  *UPDATE_DATABASE_CONFIGURATION_cmd_3_0
            UPDATE_DATABASE_CONFIGURATION_cmd_3_0 = *config_keyword *value
            UPDATE_DATABASE_MANAGER_CONFIGURATION_cmd = UPDATE
+                                                  *UPDATE_DATABASE_MANAGER_CONFIGURATION_cmd_1
+                                                  *UPDATE_DATABASE_MANAGER_CONFIGURATION_cmd_2
+                                                  USING
+                                                  *UPDATE_DATABASE_MANAGER_CONFIGURATION_cmd_3
            UPDATE_DATABASE_MANAGER_CONFIGURATION_cmd_1 = DATABASE MANAGER | DB MANAGER | DBM
            UPDATE_DATABASE_MANAGER_CONFIGURATION_cmd_2 = CONFIGURATION | CONFIG | CFG
            UPDATE_DATABASE_MANAGER_CONFIGURATION_cmd_3 = *UPDATE_DATABASE_MANAGER_CONFIGURATION_cmd_3_0
+                                               |  *UPDATE_DATABASE_MANAGER_CONFIGURATION_cmd_3
+                                                  *UPDATE_DATABASE_MANAGER_CONFIGURATION_cmd_3_0
            UPDATE_DATABASE_MANAGER_CONFIGURATION_cmd_3_0 = *config_keyword *value
            UPDATE_MONITOR_SWITCHES_cmd         =  UPDATE MONITOR SWITCHES USING *UPDATE_MONITOR_SWITCHES_cmd_1
            UPDATE_MONITOR_SWITCHES_cmd_1       =  *UPDATE_MONITOR_SWITCHES_cmd_1_0
+                                               |  *UPDATE_MONITOR_SWITCHES_cmd_1 *UPDATE_MONITOR_SWITCHES_cmd_1_0
            UPDATE_MONITOR_SWITCHES_cmd_1_0     =  *switch_name *UPDATE_MONITOR_SWITCHES_cmd_1_1
            UPDATE_MONITOR_SWITCHES_cmd_1_1     =  ON | OFF
            UPDATE_RECOVERY_HISTORY_FILE_cmd    =  UPDATE HISTORY FOR
            UPDATE_stmt                         =  UPDATE *UPDATE_stmt_1 *UPDATE_stmt_2 *UPDATE_stmt_3
            UPDATE_stmt_1                       =  *table_or_view_name | ONLY $'(' *table_or_view_name $')'
            UPDATE_stmt_2                       =  epsilon | *UPDATE_stmt_2_1 *correlation_name
            UPDATE_stmt_2_1                     =  epsilon | AS
            UPDATE_stmt_3                       =  SET *assignment_clause *UPDATE_stmt_3_1
+                                               |  SET *assignment_clause WHERE CURRENT OF *cursor_name
            UPDATE_stmt_3_1                     =  epsilon | WHERE *search_condition
            VALUES_stmt                         =  *VALUES_stmt_1 INTO *VALUES_stmt_2
            VALUES_stmt_1                       =  *expression | *expression_list
            VALUES_stmt_2                       =  *host_variable | *VALUES_stmt_2 $',' *host_variable
            WHENEVER_stmt                       =  WHENEVER *WHENEVER_stmt_1 *WHENEVER_stmt_2
            WHENEVER_stmt_1                     =  NOT FOUND | SQLERROR | SQLWARNING
            WHENEVER_stmt_2                     =  CONTINUE | *WHENEVER_stmt_2_1 *WHENEVER_stmt_2_2 *host_label
            WHENEVER_stmt_2_1                   =  GOTO | GO TO
            WHENEVER_stmt_2_2                   =  epsilon | $':'
            $'_fullselect'                      =  *subselect | *values_clause | $'(' *fullselect $')'
            adapter_number                      =  $'_INTEGER_'
            agentid                             =  *identifier
            alias                               =  *identifier
            alias_name                          =  *identifier | *identifier $'.' *identifier
            appl_id                             =  *identifier
            application_handle                  =  *identifier
            assignment_clause                   =  *assignment_clause_0 | *assignment_clause $',' *assignment_clause_0
            assignment_clause_0                 =  *column_name $'_EQ_' *assignment_clause_1
+                                               |  $'('
+                                                  *assignment_clause_2
+                                                  $')'
+                                                  $'_EQ_'
+                                                  $'('
+                                                  *assignment_clause_3
+                                                  $')'
            assignment_clause_1                 =  *expression | NULL | DEFAULT
            assignment_clause_2                 =  *column_name | *assignment_clause_2 $',' *column_name
            assignment_clause_3                 =  *assignment_clause_3_1 | *fullselect
            assignment_clause_3_1               =  *assignment_clause_3_1_0
+                                               |  *assignment_clause_3_1 $',' *assignment_clause_3_1_0
            assignment_clause_3_1_0             =  *expression | NULL | DEFAULT
            attribute_definition                =  *attribute_name
+                                                  *data_type
+                                                  *attribute_definition_1
+                                                  *attribute_definition_2
            attribute_definition_1              =  epsilon | *attribute_definition_1_1
            attribute_definition_1_1            =  *lob_options | *attribute_definition_1_1 *lob_options
            attribute_definition_2              =  epsilon | *datalink_options
            attribute_name                      =  *identifier
            authid                              =  *identifier
            authorization                       =  USER *authorization_name USING *authorization_1 *authorization_2
            authorization_1                     =  *password | *host_variable
            authorization_2                     =  epsilon | NEW *authorization_2_1
            authorization_2_1                   =  *password | *host_variable
            authorization_name                  =  *identifier
            blksize                             =  $'_INTEGER_'
            buffer_size                         =  $'_INTEGER_'
            bufferpool_name                     =  *identifier
            case_expression                     =  CASE *case_expression_1 *case_expression_2 END
            case_expression_1                   =  *searched_when_clause | *simple_when_clause
            case_expression_2                   =  epsilon | ELSE NULL | ELSE *result_expression
            cast_function                       =  *identifier | *identifier $'.' *identifier
            cast_specification                  =  CAST
+                                                  $'('
+                                                  *cast_specification_1
+                                                  AS
+                                                  *data_type
+                                                  *cast_specification_2
+                                                  $')'
            cast_specification_1                =  *expression | NULL | *parameter_marker
            cast_specification_2                =  epsilon | SCOPE *typed_table_or_view_name
            character_string                    =  $'_SQ_STRING_'
            check_condition                     =  *search_condition
            check_constraint                    =  *constraint_clause CHECK $'(' *check_condition $')'
            codeset                             =  *identifier
            column                              =  *identifier
+                                               |  *identifier $'.' *identifier
+                                               |  *identifier $'.' *identifier $'.' *identifier
            column_alteration                   =  *column_name *column_alteration_1
            column_alteration_1                 =  SET DATA TYPE *column_alteration_1_1 $'(' $'_INTEGER_' $')'
+                                               |  ADD SCOPE *typed_table_or_view_name
            column_alteration_1_1               =  VARCHAR | CHARACTER VARYING | CHAR VARYING
            column_definition                   =  *column_name *data_type *column_definition_1
            column_definition_1                 =  epsilon | *column_options_w_forbit
            column_end                          =  $'_INTEGER_'
            column_name                         =  *identifier
            column_option                       =  NOT NULL
+                                               |  *default_clause
+                                               |  *lob_options
+                                               |  *datalink_options
+                                               |  SCOPE *typed_table_or_view_name
+                                               |  *column_option_1
            column_option_1                     =  *constraint_clause PRIMARY KEY
+                                               |  *constraint_clause UNIQUE
+                                               |  *constraint_clause
+                                                  REFERENCES
+                                                  *table_name
+                                                  *column_option_1_1
+                                                  *rule_clause
+                                               |  *constraint_clause CHECK $'(' *check_condition $')'
            column_option_1_1                   =  epsilon | $'(' *column_option_1_1_1 $')'
            column_option_1_1_1                 =  *column_option_1_1_1_0
+                                               |  *column_option_1_1_1 $',' *column_option_1_1_1_0
            column_option_1_1_1_0               =  *column_name
            column_options                      =  *column_options_0 | *column_options *column_options_0
            column_options_0                    =  *column_option
            column_options_w_forbit             =  *column_option *column_options_w_forbit_1
            column_options_w_forbit_1           =  epsilon | *column_options_w_forbit_1_1
            column_options_w_forbit_1_1         =  *column_options_w_forbit_1_1_0
+                                               |  *column_options_w_forbit_1_1 *column_options_w_forbit_1_1_0
            column_options_w_forbit_1_1_0       =  *column_option | *forbitdata
            column_position                     =  $'_INTEGER_'
            column_start                        =  $'_INTEGER_'
            command                             =  *ACTIVATE_DATABASE_cmd
+                                               |  *ADD_NODE_cmd
+                                               |  *ATTACH_cmd
+                                               |  *BACKUP_DATABASE_cmd
+                                               |  *BIND_cmd
+                                               |  *CATALOG_APPCLU_NODE_cmd
+                                               |  *CATALOG_APPC_NODE_cmd
+                                               |  *CATALOG_APPN_NODE_cmd
+                                               |  *CATALOG_DATABASE_cmd
+                                               |  *CATALOG_DCS_DATABASE_cmd
+                                               |  *CATALOG_GLOBAL_DATABASE_cmd
+                                               |  *CATALOG_IPX_SPX_NODE_cmd
+                                               |  *CATALOG_LOCAL_NODE_cmd
+                                               |  *CATALOG_NAMED_PIPE_NODE_cmd
+                                               |  *CATALOG_NETBIOS_NODE_cmd
+                                               |  *CATALOG_ODBC_DATA_SOURCE_cmd
+                                               |  *CATALOG_TCP_IP_NODE_cmd
+                                               |  *CHANGE_DATABASE_COMMENT_cmd
+                                               |  *CHANGE_ISOLATION_LEVEL_cmd
+                                               |  *CREATE_DATABASE_cmd
+                                               |  *DEACTIVATE_DATABASE_cmd
+                                               |  *DEREGISTER_cmd
+                                               |  *DESCRIBE_cmd
+                                               |  *DETACH_cmd
+                                               |  *DROP_DATABASE_cmd
+                                               |  *DROP_NODE_VERIFY_cmd
+                                               |  *EXPORT_cmd
+                                               |  *FORCE_APPLICATION_cmd
+                                               |  *GET_ADMIN_CONFIGURATION_cmd
+                                               |  *GET_AUTHORIZATIONS_cmd
+                                               |  *GET_CONNECTIONS_STATE_cmd
+                                               |  *GET_DATABASE_CONFIGURATION_cmd
+                                               |  *GET_DATABASE_MANAGER_CONFIGURATION_cmd
+                                               |  *GET_DATABASE_MANAGER_MONITOR_SWITCHES_cmd
+                                               |  *GET_INSTANCE_cmd
+                                               |  *GET_MONITOR_SWITCHES_cmd
+                                               |  *GET_SNAPSHOT_cmd
+                                               |  *HELP_cmd
+                                               |  *IMPORT_cmd
+                                               |  *INITIALIZE_TAPE_cmd
+                                               |  *INVOKE_STORED_PROCEDURE_cmd
+                                               |  *LIST_ACTIVE_DATABASES_cmd
+                                               |  *LIST_APPLICATIONS_cmd
+                                               |  *LIST_BACKUP_HISTORY_cmd
+                                               |  *LIST_COMMAND_OPTIONS_cmd
+                                               |  *LIST_DATABASE_DIRECTORY_cmd
+                                               |  *LIST_DCS_APPLICATIONS_cmd
+                                               |  *LIST_DCS_DIRECTORY_cmd
+                                               |  *LIST_DRDA_INDOUBT_TRANSACTIONS_cmd
+                                               |  *LIST_INDOUBT_TRANSACTIONS_cmd
+                                               |  *LIST_NODEGROUPS_cmd
+                                               |  *LIST_NODES_cmd
+                                               |  *LIST_NODE_DIRECTORY_cmd
+                                               |  *LIST_ODBC_DATA_SOURCES_cmd
+                                               |  *LIST_PACKAGES_TABLES_cmd
+                                               |  *LIST_TABLESPACES_cmd
+                                               |  *LIST_TABLESPACE_CONTAINERS_cmd
+                                               |  *LOAD_QUERY_cmd
+                                               |  *MIGRATE_DATABASE_cmd
+                                               |  *PRUNE_HISTORY_cmd
+                                               |  *QUERY_CLIENT_cmd
+                                               |  *QUIESCE_TABLESPACES_FOR_TABLE_cmd
+                                               |  *QUIT_cmd
+                                               |  *REBIND_cmd
+                                               |  *REDISTRIBUTE_NODEGROUP_cmd
+                                               |  *REGISTER_cmd
+                                               |  *REORGANIZE_TABLE_cmd
+                                               |  *REORGCHK_cmd
+                                               |  *RESET_ADMIN_CONFIGURATION_cmd
+                                               |  *RESET_DATABASE_CONFIGURATION_cmd
+                                               |  *RESET_DATABASE_MANAGER_CONFIGURATION_cmd
+                                               |  *RESET_MONITOR_cmd
+                                               |  *RESTART_DATABASE_cmd
+                                               |  *RESTORE_DATABASE_cmd
+                                               |  *REWIND_TAPE_cmd
+                                               |  *ROLLFORWARD_DATABASE_cmd
+                                               |  *RUNSTATS_cmd
+                                               |  *SET_CLIENT_cmd
+                                               |  *SET_RUNTIME_DEGREE_cmd
+                                               |  *SET_TABLESPACE_CONTAINERS_cmd
+                                               |  *SET_TAPE_POSITION_cmd
+                                               |  *START_DATABASE_MANAGER_cmd
+                                               |  *STOP_DATABASE_MANAGER_cmd
+                                               |  *TERMINATE_cmd
+                                               |  *UNCATALOG_DATABASE_cmd
+                                               |  *UNCATALOG_DCS_DATABASE_cmd
+                                               |  *UNCATALOG_NODE_cmd
+                                               |  *UNCATALOG_ODBC_DATA_SOURCE_cmd
+                                               |  *UPDATE_ADMIN_CONFIGURATION_cmd
+                                               |  *UPDATE_COMMAND_OPTIONS_cmd
+                                               |  *UPDATE_DATABASE_CONFIGURATION_cmd
+                                               |  *UPDATE_DATABASE_MANAGER_CONFIGURATION_cmd
+                                               |  *UPDATE_MONITOR_SWITCHES_cmd
+                                               |  *UPDATE_RECOVERY_HISTORY_FILE_cmd
            comment_string                      =  $'_DQ_STRING_'
            common_table_expression             =  *table_name *common_table_expression_1 AS $'(' *fullselect $')'
            common_table_expression_1           =  epsilon | $'(' *common_table_expression_1_1 $')'
            common_table_expression_1_1         =  *column_name | *common_table_expression_1_1 $',' *column_name
            comparison_string                   =  $'_SQ_STRING_'
            computername                        =  *identifier
            config_keyword                      =  *identifier
            constant                            =  $'_SQ_STRING_' | *constant_1 $'_INTEGER_' | *constant_2 $'_REAL_'
            constant_1                          =  epsilon | $'+' | $'-'
            constant_2                          =  epsilon | $'+' | $'-'
            constraint_clause                   =  epsilon | CONSTRAINT *constraint_name
            constraint_name                     =  *identifier
            container_clause                    =  $'(' *container_clause_1 $')'
            container_clause_1                  =  *container_clause_1_0
+                                               |  *container_clause_1 $',' *container_clause_1_0
            container_clause_1_0                =  *container_clause_1_1 $'_SQ_STRING_' *number_of_pages_kmg
            container_clause_1_1                =  FILE | DEVICE
            container_string                    =  $'_SQ_STRING_'
            correlation_clause                  =  *correlation_clause_1 *correlation_name *correlation_clause_2
            correlation_clause_1                =  epsilon | AS
            correlation_clause_2                =  epsilon | $'(' *correlation_clause_2_1 $')'
            correlation_clause_2_1              =  *column_name | *correlation_clause_2_1 $',' *column_name
            correlation_name                    =  *identifier
            cursor_name                         =  *identifier
            data_source_name                    =  *identifier
            data_type                           =  *data_type_1
            data_type_1                         =  SMALLINT
+                                               |  *data_type_1_1
+                                               |  BIGINT
+                                               |  *data_type_1_2
+                                               |  DOUBLE *data_type_1_3
+                                               |  *data_type_1_4 *data_type_1_5
+                                               |  *data_type_1_6 *data_type_1_7
+                                               |  GRAPHIC *data_type_1_8
+                                               |  VARGRAPHIC $'(' $'_INTEGER_' $')'
+                                               |  LONG VARGRAPHIC
+                                               |  DATE
+                                               |  TIME
+                                               |  TIMESTAMP
+                                               |  *data_type_1_9 $'(' *integer_kmg $')'
+                                               |  DATALINK *data_type_1_10
+                                               |  *distinct_type_name
+                                               |  REF $'(' *type_name $')'
            data_type_1_1                       =  INTEGER | INT
            data_type_1_2                       =  FLOAT *data_type_1_2_1 | REAL
            data_type_1_2_1                     =  epsilon | $'(' $'_INTEGER_' $')'
            data_type_1_3                       =  epsilon | PRECISION
            data_type_1_4                       =  DECIMAL | DEC | NUMERIC | NUM
            data_type_1_5                       =  epsilon | $'(' $'_INTEGER_' *data_type_1_5_1 $')'
            data_type_1_5_1                     =  epsilon | $',' $'_INTEGER_'
            data_type_1_6                       =  *data_type_1_6_1 *data_type_1_6_2
+                                               |  *data_type_1_6_3 $'(' $'_INTEGER_' $')'
+                                               |  LONG VARCHAR
            data_type_1_6_1                     =  CHARACTER | CHAR
            data_type_1_6_2                     =  epsilon | $'(' $'_INTEGER_' $')'
            data_type_1_6_3                     =  VARCHAR | *data_type_1_6_3_1 VARYING
            data_type_1_6_3_1                   =  CHARACTER | CHAR
            data_type_1_7                       =  epsilon | FOR BIT DATA
            data_type_1_8                       =  epsilon | $'(' $'_INTEGER_' $')'
            data_type_1_9                       =  BLOB | CLOB | DBCLOB
            data_type_1_10                      =  epsilon | $'(' $'_INTEGER_' $')'
            database_alias                      =  *identifier
            database_container_clause           =  $'(' *database_container_clause_1 $')'
            database_container_clause_1         =  *database_container_clause_1_0
+                                               |  *database_container_clause_1 $',' *database_container_clause_1_0
            database_container_clause_1_0       =  *database_container_clause_1_1 $'_SQ_STRING_' *number_of_pages_kmg
            database_container_clause_1_1       =  FILE | DEVICE
            database_containers                 =  *database_containers_0 | *database_containers *database_containers_0
            database_containers_0               =  USING *container_clause *database_containers_1
            database_containers_1               =  epsilon | *on_nodes_clause
            database_global_name                =  *identifier
            database_name                       =  *identifier
            datalink_options                    =  LINKTYPE URL *datalink_options_1
            datalink_options_1                  =  epsilon | NO LINK CONTROL | FILE LINK CONTROL *datalink_options_1_1
            datalink_options_1_1                =  *file_link_options | MODE DB2OPTIONS
            datetime_special_register           =  CURRENT DATE | CURRENT TIME | CURRENT TIMESTAMP
            default_clause                      =  *default_clause_1 DEFAULT *default_clause_2
            default_clause_1                    =  epsilon | WITH
            default_clause_2                    =  epsilon | *default_values_clause
            default_value_clause                =  *constant | *datetime_special_register | USER
            default_values_clause               =  *constant
+                                               |  *datetime_special_register
+                                               |  USER
+                                               |  NULL
+                                               |  *cast_function $'(' *default_value_clause $')'
            degree                              =  $'_INTEGER_'
            degree_of_parallelism               =  $'_INTEGER_'
            dereference_operation               =  *identifier $'_DEREF_' *attribute_name
            descriptor_name                     =  *identifier
            device                              =  *identifier
            dft_extentsize                      =  $'_INTEGER_'
            diagnostic_string                   =  *expression
            distfile                            =  *identifier
            distinct_type_name                  =  *identifier | *identifier $'.' *identifier
            element                             =  *column *element_1
+                                               |  *unsigned_constant *element_2
+                                               |  *function *element_3
+                                               |  *special_register
+                                               |  *case_expression
+                                               |  *cast_specification
+                                               |  *dereference_operation
+                                               |  $'(' *fullselect $')'
+                                               |  $'(' *expression $')' *element_4
            element_1                           =  epsilon | *labeled_duration
            element_2                           =  epsilon | *labeled_duration
            element_3                           =  epsilon | *labeled_duration
            element_4                           =  epsilon | *labeled_duration
            event_condition                     =  *event_condition_1 *event_condition_2 *event_condition_3
            event_condition_1                   =  epsilon | NOT
            event_condition_2                   =  *event_condition_2_1 *event_condition_2_2 *comparison_string
+                                               |  $'(' *event_condition $')'
            event_condition_2_1                 =  APPL_ID | AUTH_ID | APPL_NAME
            event_condition_2_2                 =  $'_EQ_'
+                                               |  $'_NEQ_2_'
+                                               |  $'_NEQ_3_'
+                                               |  $'_NEQ_1_'
+                                               |  $'_GT_'
+                                               |  $'_GEQ_'
+                                               |  $'_LT_'
+                                               |  $'_LEQ_'
+                                               |  LIKE
+                                               |  NOT LIKE
            event_condition_3                   =  epsilon | *event_condition_3_1
            event_condition_3_1                 =  *event_condition_3_1_0 | *event_condition_3_1 *event_condition_3_1_0
            event_condition_3_1_0               =  *event_condition_3_1_1 *event_condition_3_1_2 *event_condition_3_1_3
            event_condition_3_1_1               =  AND | OR
            event_condition_3_1_2               =  epsilon | NOT
            event_condition_3_1_3               =  *event_condition_3_1_3_1 *event_condition_3_1_3_2 *comparison_string
+                                               |  $'(' *event_condition $')'
            event_condition_3_1_3_1             =  APPL_ID | AUTH_ID | APPL_NAME
            event_condition_3_1_3_2             =  $'_EQ_'
+                                               |  $'_NEQ_2_'
+                                               |  $'_NEQ_3_'
+                                               |  $'_NEQ_1_'
+                                               |  $'_GT_'
+                                               |  $'_GEQ_'
+                                               |  $'_LT_'
+                                               |  $'_LEQ_'
+                                               |  LIKE
+                                               |  NOT LIKE
            event_monitor_name                  =  *identifier
            except_on_nodes_clause              =  EXCEPT
+                                                  ON
+                                                  *except_on_nodes_clause_1
+                                                  $'('
+                                                  *except_on_nodes_clause_2
+                                                  $')'
            except_on_nodes_clause_1            =  NODE | NODES
            except_on_nodes_clause_2            =  *except_on_nodes_clause_2_0
+                                               |  *except_on_nodes_clause_2 $',' *except_on_nodes_clause_2_0
            except_on_nodes_clause_2_0          =  *node_number *except_on_nodes_clause_2_1 SIZE *number_of_pages
            except_on_nodes_clause_2_1          =  epsilon | TO *node_number
            exception_clause                    =  FOR EXCEPTION *exception_clause_1
            exception_clause_1                  =  *exception_clause_1_0
+                                               |  *exception_clause_1 $',' *exception_clause_1_0
            exception_clause_1_0                =  IN *table_name USE *table_name
            explainable_SQL_stmt                =  *DELETE_stmt
+                                               |  *INSERT_stmt
+                                               |  *select_stmt
+                                               |  *UPDATE_stmt
+                                               |  *VALUES_stmt
            expression                          =  *term | *expression $'+' *term | *expression $'-' *term
            expression_list                     =  *expression $',' *expression | *expression_list $',' *expression
            factor                              =  *element | $'+' *factor | $'-' *factor
            fetch_first_clause                  =  FETCH FIRST *fetch_first_clause_1 *fetch_first_clause_2 ONLY
            fetch_first_clause_1                =  epsilon | $'_INTEGER_'
            fetch_first_clause_2                =  ROW | ROWS
            file_link_options                   =  *file_link_options_0 | *file_link_options *file_link_options_0
            file_link_options_0                 =  INTEGRITY ALL
+                                               |  READ PERMISSION *file_link_options_1
+                                               |  WRITE PERMISSION *file_link_options_2
+                                               |  RECOVERY *file_link_options_3
+                                               |  ON UNLINK *file_link_options_4
            file_link_options_1                 =  FS | DB
            file_link_options_2                 =  FS | BLOCKED
            file_link_options_3                 =  NO | YES
            file_link_options_4                 =  RESTORE | DELETE
            file_options                        =  *start_option
+                                               |  MAXFILES *file_options_1
+                                               |  MAXFILESIZE *file_options_2
+                                               |  BUFFERSIZE *pages
+                                               |  BLOCKED
+                                               |  NONBLOCKED
+                                               |  APPEND
+                                               |  REPLACE
            file_options_1                      =  NONE | *number_of_files
            file_options_2                      =  *pages | NONE
            file_server                         =  *identifier
            filename                            =  *identifier $'.' *identifier
            filetype                            =  *identifier
            filetype_mod                        =  *identifier
            forbitdata                          =  FOR BIT DATA
            from_clause                         =  FROM *from_clause_1
            from_clause_1                       =  *table_reference | *from_clause_1 $',' *table_reference
            fullselect                          =  fullselect *fullselect_1
            fullselect_1                        =  epsilon | *fullselect_1_1
            fullselect_1_1                      =  *fullselect_1_1_0 | *fullselect_1_1 *fullselect_1_1_0
            fullselect_1_1_0                    =  *set_operator fullselect
            function                            =  AVG $'(' *function_1 *expression $')'
+                                               |  COUNT $'(' $'*' $')'
+                                               |  COUNT $'(' *function_2 *expression $')'
+                                               |  COUNT_BIG $'(' $'*' $')'
+                                               |  COUNT_BIG $'(' *function_3 *expression $')'
+                                               |  GROUPING $'(' *expression $')'
+                                               |  MAX $'(' *function_4 *expression $')'
+                                               |  MIN $'(' *function_5 *expression $')'
+                                               |  STDDEV $'(' *function_6 *expression $')'
+                                               |  SUM $'(' *function_7 *expression $')'
+                                               |  VARIANCE $'(' *function_8 *expression $')'
+                                               |  *function_name $'(' *function_9 $')'
+                                               |  BIGINT $'(' *function_10 $')'
+                                               |  CHAR $'(' *function_11 $')'
+                                               |  CONCAT $'(' *function_12 $')'
+                                               |  DATE $'(' *function_13 $')'
+                                               |  DAY $'(' *function_14 $')'
+                                               |  DAYS $'(' *function_15 $')'
+                                               |  DECIMAL $'(' *function_16 $')'
+                                               |  DOUBLE $'(' *function_17 $')'
+                                               |  FLOAT $'(' *function_18 $')'
+                                               |  GRAPHIC $'(' *function_19 $')'
+                                               |  HOUR $'(' *function_20 $')'
+                                               |  INSERT $'(' *function_21 $')'
+                                               |  INTEGER $'(' *function_22 $')'
+                                               |  LEFT $'(' *function_23 $')'
+                                               |  MICROSECOND $'(' *function_24 $')'
+                                               |  MINUTE $'(' *function_25 $')'
+                                               |  MONTH $'(' *function_26 $')'
+                                               |  REAL $'(' *function_27 $')'
+                                               |  REPLACE $'(' *function_28 $')'
+                                               |  RIGHT $'(' *function_29 $')'
+                                               |  SECOND $'(' *function_30 $')'
+                                               |  SMALLINT $'(' *function_31 $')'
+                                               |  TIME $'(' *function_32 $')'
+                                               |  TIMESTAMP $'(' *function_33 $')'
+                                               |  YEAR $'(' *function_34 $')'
            function_1                          =  epsilon | ALL | DISTINCT
            function_2                          =  epsilon | ALL | DISTINCT
            function_3                          =  epsilon | ALL | DISTINCT
            function_4                          =  epsilon | ALL | DISTINCT
            function_5                          =  epsilon | ALL | DISTINCT
            function_6                          =  epsilon | ALL | DISTINCT
            function_7                          =  epsilon | ALL | DISTINCT
            function_8                          =  epsilon | ALL | DISTINCT
            function_9                          =  *expression | *function_9 $',' *expression
            function_10                         =  *expression | *function_10 $',' *expression
            function_11                         =  *expression | *function_11 $',' *expression
            function_12                         =  *expression | *function_12 $',' *expression
            function_13                         =  *expression | *function_13 $',' *expression
            function_14                         =  *expression | *function_14 $',' *expression
            function_15                         =  *expression | *function_15 $',' *expression
            function_16                         =  *expression | *function_16 $',' *expression
            function_17                         =  *expression | *function_17 $',' *expression
            function_18                         =  *expression | *function_18 $',' *expression
            function_19                         =  *expression | *function_19 $',' *expression
            function_20                         =  *expression | *function_20 $',' *expression
            function_21                         =  *expression | *function_21 $',' *expression
            function_22                         =  *expression | *function_22 $',' *expression
            function_23                         =  *expression | *function_23 $',' *expression
            function_24                         =  *expression | *function_24 $',' *expression
            function_25                         =  *expression | *function_25 $',' *expression
            function_26                         =  *expression | *function_26 $',' *expression
            function_27                         =  *expression | *function_27 $',' *expression
            function_28                         =  *expression | *function_28 $',' *expression
            function_29                         =  *expression | *function_29 $',' *expression
            function_30                         =  *expression | *function_30 $',' *expression
            function_31                         =  *expression | *function_31 $',' *expression
            function_32                         =  *expression | *function_32 $',' *expression
            function_33                         =  *expression | *function_33 $',' *expression
            function_34                         =  *expression | *function_34 $',' *expression
            function_name                       =  *identifier | *identifier $'.' *identifier
            grand_total                         =  $'(' $')'
            group_by_clause                     =  GROUP BY *group_by_clause_1
            group_by_clause_1                   =  *group_by_clause_1_0 | *group_by_clause_1 $',' *group_by_clause_1_0
            group_by_clause_1_0                 =  *expression | *grouping_sets | *super_groups
            group_name                          =  *identifier
            grouping_expression_list            =  *grouping_expression_list_0
+                                               |  *grouping_expression_list $',' *grouping_expression_list_0
            grouping_expression_list_0          =  *expression | $'(' *expression_list $')'
            grouping_sets                       =  GROUPING SETS $'(' *grouping_sets_1 $')'
            grouping_sets_1                     =  *grouping_sets_1_0 | *grouping_sets_1 $',' *grouping_sets_1_0
            grouping_sets_1_0                   =  *expression
+                                               |  *super_groups
+                                               |  $'(' *grouping_sets_1_1 $',' *grouping_sets_1_2 $')'
            grouping_sets_1_1                   =  *expression | *super_groups
            grouping_sets_1_2                   =  *grouping_sets_1_2_0 | *grouping_sets_1_2 $',' *grouping_sets_1_2_0
            grouping_sets_1_2_0                 =  *expression | *super_groups
            having_clause                       =  HAVING *search_condition
            host_label                          =  *identifier
            host_variable                       =  *identifier
            hostname                            =  *identifier
            identifier                          =  $'_IDENT_' | $'_DQ_STRING_' | *keyword
            include_name                        =  *identifier | $'_SQ_STRING_'
            index_name                          =  *identifier | *identifier $'.' *identifier
            insert_column                       =  *identifier
            instance_name                       =  *identifier
            instancename                        =  *identifier
            integer_k                           =  $'_INTEGER_' *integer_k_1
            integer_k_1                         =  epsilon | K
            integer_kmg                         =  $'_INTEGER_' *integer_kmg_1
            integer_kmg_1                       =  epsilon | K | M | G
            integrity_options                   =  ALL | *integrity_options_1
            integrity_options_1                 =  FOREIGN KEY | CHECK | DATALINK RECONCILE PENDING | SUMMARY
            join_condition                      =  *search_condition
            joined_table                        =  *table_reference
+                                                  *joined_table_1
+                                                  JOIN
+                                                  *table_reference
+                                                  ON
+                                                  *join_condition
+                                               |  $'(' *joined_table $')'
            joined_table_1                      =  epsilon | INNER | *joined_table_1_1 *joined_table_1_2
            joined_table_1_1                    =  LEFT | RIGHT | FULL
            joined_table_1_2                    =  epsilon | OUTER
            keyword                             =  ACTION
+                                               |  ACTIVATE
+                                               |  ACTIVE
+                                               |  ADAPTER
+                                               |  ADD
+                                               |  ADMIN
+                                               |  ADSM
+                                               |  AFTER
+                                               |  AGE
+                                               |  AGENTID
+                                               |  ALIAS
+                                               |  ALL
+                                               |  ALLOW
+                                               |  ALTER
+                                               |  ALTERIN
+                                               |  AND
+                                               |  ANY
+                                               |  APPC
+                                               |  APPCLU
+                                               |  APPEND
+                                               |  APPLICATION
+                                               |  APPLICATIONS
+                                               |  APPLID
+                                               |  APPL_ID
+                                               |  APPL_NAME
+                                               |  APPN
+                                               |  AR
+                                               |  AS
+                                               |  ASC
+                                               |  ASYNC
+                                               |  AT
+                                               |  ATOMIC
+                                               |  ATTACH
+                                               |  ATTRIBUTE
+                                               |  AUTHENTICATION
+                                               |  AUTHORIZATION
+                                               |  AUTHORIZATIONS
+                                               |  AUTH_ID
+                                               |  AUTOSTART
+                                               |  AVG
+                                               |  BACKUP
+                                               |  BEFORE
+                                               |  BEGIN
+                                               |  BETWEEN
+                                               |  BIGINT
+                                               |  BIND
+                                               |  BINDADD
+                                               |  BIT
+                                               |  BLOB
+                                               |  BLOCKED
+                                               |  BLOCKING
+                                               |  BUF
+                                               |  BUFFER
+                                               |  BUFFERPOOL
+                                               |  BUFFERPOOLS
+                                               |  BUFFERS
+                                               |  BUFFERSIZE
+                                               |  BY
+                                               |  C
+                                               |  CALL
+                                               |  CALLED
+                                               |  CAPTURE
+                                               |  CARDINALITY
+                                               |  CASCADE
+                                               |  CASCADED
+                                               |  CASE
+                                               |  CAST
+                                               |  CATALOG
+                                               |  CFG
+                                               |  CHANGE
+                                               |  CHANGES
+                                               |  CHAR
+                                               |  CHARACTER
+                                               |  CHECK
+                                               |  CHECKED
+                                               |  CLIENT
+                                               |  CLOB
+                                               |  CLOSE
+                                               |  CLUSTER
+                                               |  COBOL
+                                               |  CODESET
+                                               |  COLLATE
+                                               |  COLLECTION
+                                               |  COLUMN
+                                               |  COLUMNS
+                                               |  COMMAND
+                                               |  COMMENT
+                                               |  COMMIT
+                                               |  COMMITCOUNT
+                                               |  COMPACT
+                                               |  COMPARISONS
+                                               |  COMPATIBILITY
+                                               |  CONCAT
+                                               |  CONFIG
+                                               |  CONFIGURATION
+                                               |  CONNECT
+                                               |  CONNECTION
+                                               |  CONNECTIONS
+                                               |  CONSTRAINT
+                                               |  CONSTRAINTS
+                                               |  CONTAINERS
+                                               |  CONTAINING
+                                               |  CONTINUE
+                                               |  CONTROL
+                                               |  COUNT
+                                               |  COUNT_BIG
+                                               |  CREATE
+                                               |  CREATEIN
+                                               |  CREATETAB
+                                               |  CREATE_NOT_FENCED
+                                               |  CS
+                                               |  CUBE
+                                               |  CURRENT
+                                               |  CURSOR
+                                               |  DATA
+                                               |  DATABASE
+                                               |  DATABASES
+                                               |  DATALINK
+                                               |  DATE
+                                               |  DATETIME
+                                               |  DAY
+                                               |  DAYS
+                                               |  DB
+                                               |  DB2
+                                               |  DB2DARI
+                                               |  DB2GENERAL
+                                               |  DB2GENRL
+                                               |  DB2OPTIONS
+                                               |  DB2SQL
+                                               |  DBADM
+                                               |  DBCLOB
+                                               |  DBINFO
+                                               |  DBM
+                                               |  DCE
+                                               |  DCS
+                                               |  DEACTIVATE
+                                               |  DEADLOCKS
+                                               |  DEC
+                                               |  DECIMAL
+                                               |  DECLARE
+                                               |  DEF
+                                               |  DEFAULT
+                                               |  DEFERRED
+                                               |  DEFINITION
+                                               |  DEGREE
+                                               |  DELETE
+                                               |  DEREGISTER
+                                               |  DESC
+                                               |  DESCRIBE
+                                               |  DESCRIPTOR
+                                               |  DETACH
+                                               |  DETAIL
+                                               |  DETAILED
+                                               |  DETERMINISTIC
+                                               |  DEVICE
+                                               |  DFT_EXTENT_SZ
+                                               |  DIRECTORY
+                                               |  DISALLOW
+                                               |  DISCONNECT
+                                               |  DISTFILE
+                                               |  DISTINCT
+                                               |  DISTRIBUTION
+                                               |  DOUBLE
+                                               |  DRDA
+                                               |  DROP
+                                               |  DROPIN
+                                               |  DROPPED
+                                               |  DYNAMIC
+                                               |  EACH
+                                               |  ELSE
+                                               |  EMPTY
+                                               |  END
+                                               |  ESCAPE
+                                               |  EUR
+                                               |  EVALUATE
+                                               |  EVENT
+                                               |  EXCEPT
+                                               |  EXCEPTION
+                                               |  EXCLUSIVE
+                                               |  EXCLUSIZE
+                                               |  EXECUTE
+                                               |  EXISTS
+                                               |  EXPLAIN
+                                               |  EXPLSNAP
+                                               |  EXPORT
+                                               |  EXTEND
+                                               |  EXTENDED
+                                               |  EXTENTSIZE
+                                               |  EXTERNAL
+                                               |  FCM
+                                               |  FENCED
+                                               |  FETCH
+                                               |  FILE
+                                               |  FINAL
+                                               |  FIRST
+                                               |  FLOAT
+                                               |  FLUSH
+                                               |  FOR
+                                               |  FORCE
+                                               |  FOREIGN
+                                               |  FOUND
+                                               |  FREE
+                                               |  FROM
+                                               |  FS
+                                               |  FULL
+                                               |  FUNCPATH
+                                               |  FUNCTION
+                                               |  G
+                                               |  GENERAL
+                                               |  GENERATED
+                                               |  GET
+                                               |  GLOBAL
+                                               |  GO
+                                               |  GOTO
+                                               |  GRANT
+                                               |  GRANT_GROUP
+                                               |  GRANT_USER
+                                               |  GRAPHIC
+                                               |  GROUP
+                                               |  GROUPING
+                                               |  HASHING
+                                               |  HAVING
+                                               |  HELP
+                                               |  HIERARCHY
+                                               |  HISTORY
+                                               |  HOLD
+                                               |  HOUR
+                                               |  HOURS
+                                               |  IDENTITY
+                                               |  IMMEDIATE
+                                               |  IMPLICIT_SCHEMA
+                                               |  IMPORT
+                                               |  IN
+                                               |  INCLUDE
+                                               |  INCREMENTAL
+                                               |  INDEX
+                                               |  INDEXES
+                                               |  INDICATORS
+                                               |  INDOUBT
+                                               |  INHERIT
+                                               |  INITIALIZE
+                                               |  INITIALLY
+                                               |  INNER
+                                               |  INOUT
+                                               |  INPUT
+                                               |  INSERT
+                                               |  INSERT_UPDATE
+                                               |  INSTANCE
+                                               |  INT
+                                               |  INTEGER
+                                               |  INTEGRITY
+                                               |  INTENT
+                                               |  INTERSECT
+                                               |  INTO
+                                               |  INVOKE
+                                               |  IPXSPX
+                                               |  IS
+                                               |  ISO
+                                               |  ISOLATION
+                                               |  JAVA
+                                               |  JIS
+                                               |  JOIN
+                                               |  K
+                                               |  KEY
+                                               |  L
+                                               |  LANGUAGE
+                                               |  LEFT
+                                               |  LIKE
+                                               |  LINK
+                                               |  LINKTYPE
+                                               |  LIST
+                                               |  LOAD
+                                               |  LOBFILE
+                                               |  LOBS
+                                               |  LOC
+                                               |  LOCAL
+                                               |  LOCATOR
+                                               |  LOCK
+                                               |  LOCKS
+                                               |  LOCKSIZE
+                                               |  LOGGED
+                                               |  LONG
+                                               |  LONGVAR
+                                               |  M
+                                               |  MAIN
+                                               |  MANAGED
+                                               |  MANAGER
+                                               |  MANUALSTART
+                                               |  MAX
+                                               |  MAXFILES
+                                               |  MAXFILESIZE
+                                               |  MESSAGES
+                                               |  METHOD
+                                               |  MICROSECOND
+                                               |  MICROSECONDS
+                                               |  MIGRATE
+                                               |  MIN
+                                               |  MINPCTUSED
+                                               |  MINUTE
+                                               |  MINUTES
+                                               |  MODE
+                                               |  MODIFIED
+                                               |  MONITOR
+                                               |  MONTH
+                                               |  MONTHS
+                                               |  N
+                                               |  NAME
+                                               |  NC
+                                               |  NETBIOS
+                                               |  NETWORKID
+                                               |  NEW
+                                               |  NEW_TABLE
+                                               |  NO
+                                               |  NODE
+                                               |  NODEGROUP
+                                               |  NODEGROUPS
+                                               |  NODES
+                                               |  NONBLOCKED
+                                               |  NONE
+                                               |  NOPACKAGE
+                                               |  NOT
+                                               |  NPIPE
+                                               |  NULL
+                                               |  NULLS
+                                               |  NUM
+                                               |  NUMERIC
+                                               |  NUMSEGS
+                                               |  ODBC
+                                               |  OF
+                                               |  OFF
+                                               |  OLD
+                                               |  OLD_TABLE
+                                               |  OLE
+                                               |  ON
+                                               |  ONLINE
+                                               |  ONLY
+                                               |  OPEN
+                                               |  OPTIMIZATION
+                                               |  OPTIMIZE
+                                               |  OPTION
+                                               |  OPTIONS
+                                               |  OR
+                                               |  ORDER
+                                               |  OSTYPE
+                                               |  OUT
+                                               |  OUTER
+                                               |  OVERHEAD
+                                               |  P
+                                               |  PACKAGE
+                                               |  PACKAGES
+                                               |  PACKAGESET
+                                               |  PAGESIZE
+                                               |  PARALLEL
+                                               |  PARALLELISM
+                                               |  PARAMETER
+                                               |  PARMS
+                                               |  PARTITIONING
+                                               |  PASSWORD
+                                               |  PATH
+                                               |  PCTFREE
+                                               |  PENDING
+                                               |  PERMISSION
+                                               |  PIPE
+                                               |  PLAN
+                                               |  POSITION
+                                               |  PRECISION
+                                               |  PREFETCHSIZE
+                                               |  PREPARE
+                                               |  PRIMARY
+                                               |  PRINCIPAL
+                                               |  PRIVILEGES
+                                               |  PROCEDURE
+                                               |  PROGRAM
+                                               |  PROMPTING
+                                               |  PRUNE
+                                               |  PUBLIC
+                                               |  QUERY
+                                               |  QUERYNO
+                                               |  QUERYOPT
+                                               |  QUERYTAG
+                                               |  QUIESCE
+                                               |  QUIT
+                                               |  READ
+                                               |  REAL
+                                               |  REBIND
+                                               |  RECOMMEND
+                                               |  RECONCILE
+                                               |  RECOVERY
+                                               |  REDISTRIBUTE
+                                               |  REF
+                                               |  REFERENCE
+                                               |  REFERENCES
+                                               |  REFERENCING
+                                               |  REFRESH
+                                               |  REGISTER
+                                               |  REGULAR
+                                               |  RELEASE
+                                               |  REMOTE
+                                               |  REMOTE_INSTANCE
+                                               |  RENAME
+                                               |  REORG
+                                               |  REORGCHK
+                                               |  REPLACE
+                                               |  REPLACE_CREATE
+                                               |  REPLICATED
+                                               |  RESET
+                                               |  RESTART
+                                               |  RESTARTCOUNT
+                                               |  RESTORE
+                                               |  RESTRICT
+                                               |  RESULT
+                                               |  RETURNS
+                                               |  REVERSE
+                                               |  REVOKE
+                                               |  REWIND
+                                               |  RIGHT
+                                               |  ROLLBACK
+                                               |  ROLLFORWARD
+                                               |  ROLLUP
+                                               |  ROW
+                                               |  ROWS
+                                               |  RR
+                                               |  RS
+                                               |  RUNSTATS
+                                               |  RUNTIME
+                                               |  SAME
+                                               |  SCANS
+                                               |  SCHEMA
+                                               |  SCOPE
+                                               |  SCRATCHPAD
+                                               |  SECOND
+                                               |  SECONDS
+                                               |  SECTION
+                                               |  SECURITY
+                                               |  SELECT
+                                               |  SELECTION
+                                               |  SERVER
+                                               |  SESSIONS
+                                               |  SET
+                                               |  SETS
+                                               |  SHARE
+                                               |  SHOW
+                                               |  SHRLEVEL
+                                               |  SIGNAL
+                                               |  SIMPLE
+                                               |  SINCE
+                                               |  SINGLE
+                                               |  SIZE
+                                               |  SMALLINT
+                                               |  SNAPSHOT
+                                               |  SOCKS
+                                               |  SOME
+                                               |  SOURCE
+                                               |  SOURCES
+                                               |  SPECIFIC
+                                               |  SQL
+                                               |  SQLCA
+                                               |  SQLDA
+                                               |  SQLERROR
+                                               |  SQLISL
+                                               |  SQLSTATE
+                                               |  SQLWARN
+                                               |  SQLWARNING
+                                               |  START
+                                               |  STATE
+                                               |  STATEMENT
+                                               |  STATEMENTS
+                                               |  STATISTICS
+                                               |  STDDEV
+                                               |  STOP
+                                               |  STORAGE
+                                               |  STYLE
+                                               |  SUB
+                                               |  SUM
+                                               |  SUMMARY
+                                               |  SWITCH
+                                               |  SWITCHES
+                                               |  SYNONYM
+                                               |  SYSTEM
+                                               |  TABLE
+                                               |  TABLES
+                                               |  TABLESPACE
+                                               |  TABLESPACES
+                                               |  TAPE
+                                               |  TARGETMAP
+                                               |  TCPIP
+                                               |  TEMPORARY
+                                               |  TERMINATE
+                                               |  TERRITORY
+                                               |  THEN
+                                               |  TIME
+                                               |  TIMESTAMP
+                                               |  TIMEZONE
+                                               |  TO
+                                               |  TRANSACTIONS
+                                               |  TRANSFERRATE
+                                               |  TRIGGER
+                                               |  TYPE
+                                               |  UNAMBIG
+                                               |  UNCATALOG
+                                               |  UNCHECKED
+                                               |  UNDER
+                                               |  UNIFORM
+                                               |  UNION
+                                               |  UNIQUE
+                                               |  UNLINK
+                                               |  UPDATE
+                                               |  UR
+                                               |  URL
+                                               |  USA
+                                               |  USE
+                                               |  USER
+                                               |  USING
+                                               |  VALUES
+                                               |  VARCHAR
+                                               |  VARGRAPHIC
+                                               |  VARIANCE
+                                               |  VARIANT
+                                               |  VARYING
+                                               |  VERIFY
+                                               |  VIEW
+                                               |  VOLATILE
+                                               |  WHEN
+                                               |  WHENEVER
+                                               |  WHERE
+                                               |  WITH
+                                               |  WITHOUT
+                                               |  WORK
+                                               |  WRITE
+                                               |  YEAR
+                                               |  YEARS
+                                               |  YES
+                                               |  BOTH
+                                               |  MATCH
+                                               |  OVERLAPS
            labeled_duration                    =  YEAR
+                                               |  YEARS
+                                               |  MONTH
+                                               |  MONTHS
+                                               |  DAY
+                                               |  DAYS
+                                               |  HOUR
+                                               |  HOURS
+                                               |  MINUTE
+                                               |  MINUTES
+                                               |  SECOND
+                                               |  SECONDS
+                                               |  MICROSECOND
+                                               |  MICROSECONDS
            library_name                        =  *identifier
            lob_options                         =  LOGGED | NOT LOGGED | NOT COMPACT | COMPACT
            lob_path                            =  *identifier
            local_lu                            =  $'_INTEGER_'
            local_message_file                  =  $'_SQ_STRING_'
            lock_block                          =  IN SHARE MODE | IN EXCLUSIZE MODE *lock_block_1
            lock_block_1                        =  epsilon | ON SINGLE NODE
            message_file                        =  *identifier $'.' *identifier
            mode                                =  *identifier
            netid                               =  *identifier
            new_column_name                     =  *identifier
            node_number                         =  $'_INTEGER_'
            nodegroup                           =  *identifier
            nodegroup_name                      =  *identifier
            nodename                            =  *identifier
            not_volatile                        =  NOT VOLATILE *not_volatile_1
            not_volatile_1                      =  epsilon | CARDINALITY
            num_buffers                         =  $'_INTEGER_'
            num_sessions                        =  $'_INTEGER_'
            number_of_files                     =  $'_INTEGER_'
            number_of_milliseconds              =  $'_INTEGER_' | $'_REAL_'
            number_of_pages                     =  $'_INTEGER_'
            number_of_pages_kmg                 =  $'_INTEGER_' *number_of_pages_kmg_1
            number_of_pages_kmg_1               =  epsilon | K | M | G
            numeric_constant                    =  $'_INTEGER_'
            numsegs                             =  $'_INTEGER_'
            object_name                         =  *identifier | *identifier $'.' *identifier
            on_nodes_clause                     =  ON *on_nodes_clause_1 $'(' *on_nodes_clause_2 $')'
            on_nodes_clause_1                   =  NODE | NODES
            on_nodes_clause_2                   =  *on_nodes_clause_2_0 | *on_nodes_clause_2 $',' *on_nodes_clause_2_0
            on_nodes_clause_2_0                 =  *node_number *on_nodes_clause_2_1
            on_nodes_clause_2_1                 =  epsilon | TO *node_number
            operating_system_type               =  *identifier
            optimization_level                  =  $'_INTEGER_'
            optimize_for_clause                 =  OPTIMIZE FOR $'_INTEGER_' *optimize_for_clause_1
            optimize_for_clause_1               =  ROWS | ROW
            option_letter                       =  *identifier
            order_by_clause                     =  ORDER BY *order_by_clause_1
            order_by_clause_1                   =  *order_by_clause_1_0 | *order_by_clause_1 $',' *order_by_clause_1_0
            order_by_clause_1_0                 =  *sort_key *order_by_clause_1_1
            order_by_clause_1_1                 =  epsilon | ASC | DESC
            package_name                        =  *identifier | *identifier $'.' *identifier
            pages                               =  $'_INTEGER_'
            parameter_marker                    =  $'?'
            parameter_name                      =  *identifier
            parameter_string                    =  $'_SQ_STRING_'
            partitioning_key_definition         =  PARTITIONING
+                                                  KEY
+                                                  $'('
+                                                  *partitioning_key_definition_1
+                                                  $')'
+                                                  *partitioning_key_definition_2
            partitioning_key_definition_1       =  *column_name | *partitioning_key_definition_1 $',' *column_name
            partitioning_key_definition_2       =  epsilon | USING HASHING
            partner_lu                          =  $'_INTEGER_'
            password                            =  $'_SQ_STRING_'
            path_name                           =  $'_SQ_STRING_'
            path_or_drive                       =  $'_SQ_STRING_'
            pipe_name                           =  $'_SQ_STRING_'
            predicate                           =  *expression *predicate_1 *expression
+                                               |  *expression *predicate_2 *predicate_3 $'(' *fullselect $')'
+                                               |  $'('
+                                                  *expression_list
+                                                  $')'
+                                                  $'_EQ_'
+                                                  *predicate_4
+                                                  $'('
+                                                  *fullselect
+                                                  $')'
+                                               |  $'(' *expression_list $')' $'_EQ_' $'(' *expression_list $')'
+                                               |  *expression NOT BETWEEN *expression AND *expression
+                                               |  *expression BETWEEN *expression AND *expression
+                                               |  EXISTS $'(' *fullselect $')'
+                                               |  *expression IN *predicate_5
+                                               |  *expression NOT IN *predicate_6
+                                               |  $'(' *expression_list $')' IN $'(' *fullselect $')'
+                                               |  $'(' *expression_list $')' NOT IN $'(' *fullselect $')'
+                                               |  *predicate_7 *predicate_8
+                                               |  *expression IS *predicate_9 NULL
+                                               |  *expression *predicate_10 OF DYNAMIC TYPE $'(' *predicate_11 $')'
            predicate_1                         =  $'_EQ_'
+                                               |  $'_NEQ_2_'
+                                               |  $'_NEQ_3_'
+                                               |  $'_NEQ_1_'
+                                               |  $'_LT_'
+                                               |  $'_GT_'
+                                               |  $'_LEQ_'
+                                               |  $'_GEQ_'
            predicate_2                         =  $'_EQ_'
+                                               |  $'_NEQ_2_'
+                                               |  $'_NEQ_3_'
+                                               |  $'_NEQ_1_'
+                                               |  $'_LT_'
+                                               |  $'_GT_'
+                                               |  $'_LEQ_'
+                                               |  $'_GEQ_'
            predicate_3                         =  SOME | ANY | ALL
            predicate_4                         =  SOME | ANY
            predicate_5                         =  *expression | $'(' *expression_list $')'
            predicate_6                         =  *expression | $'(' *expression_list $')'
            predicate_7                         =  *expression LIKE *expression | *expression NOT LIKE *expression
            predicate_8                         =  epsilon | ESCAPE *expression
            predicate_9                         =  epsilon | NOT
            predicate_10                        =  epsilon | IS
            predicate_11                        =  *predicate_11_0 | *predicate_11 $',' *predicate_11_0
            predicate_11_0                      =  *predicate_11_1 *type_name
            predicate_11_1                      =  epsilon | ONLY
            principalname                       =  *identifier
            procedure_name                      =  *identifier | *identifier $'.' *identifier
            program_name                        =  *identifier
            read_only_clause                    =  FOR *read_only_clause_1 ONLY
            read_only_clause_1                  =  READ | FETCH
            referential_constraint              =  *constraint_clause
+                                                  FOREIGN
+                                                  KEY
+                                                  $'('
+                                                  *referential_constraint_1
+                                                  $')'
+                                                  REFERENCES
+                                                  *table_name
+                                                  *referential_constraint_2
+                                                  *rule_clause
            referential_constraint_1            =  *referential_constraint_1_0
+                                               |  *referential_constraint_1 $',' *referential_constraint_1_0
            referential_constraint_1_0          =  *column_name
            referential_constraint_2            =  epsilon | $'(' *referential_constraint_2_1 $')'
            referential_constraint_2_1          =  *referential_constraint_2_1_0
+                                               |  *referential_constraint_2_1 $',' *referential_constraint_2_1_0
            referential_constraint_2_1_0        =  *column_name
            registry                            =  *identifier
            remote_file                         =  $'_SQ_STRING_'
            result_expression                   =  *expression
            routine_name                        =  *identifier
            rule_clause                         =  *rule_clause_1
            rule_clause_1                       =  epsilon | *rule_clause_1_1
            rule_clause_1_1                     =  *rule_clause_1_1_0 | *rule_clause_1_1 *rule_clause_1_1_0
            rule_clause_1_1_0                   =  ON DELETE *rule_clause_1_1_1 | ON UPDATE *rule_clause_1_1_2
            rule_clause_1_1_1                   =  NO ACTION | RESTRICT | CASCADE | SET NULL
            rule_clause_1_1_2                   =  NO ACTION | RESTRICT
            schema_SQL_stmt                     =  *CREATE_TABLE_stmt
+                                               |  *CREATE_VIEW_stmt
+                                               |  *CREATE_INDEX_stmt
+                                               |  *COMMENT_ON_stmt
+                                               |  *GRANT_stmt
            schema_name                         =  *identifier
            search_condition                    =  *search_condition_term | *search_condition OR *search_condition_term
            search_condition_element            =  *predicate | $'(' *search_condition $')'
            search_condition_factor             =  *search_condition_element | NOT *search_condition_factor
            search_condition_term               =  *search_condition_factor
+                                               |  *search_condition_term AND *search_condition_factor
            searched_when_clause                =  *searched_when_clause_0
+                                               |  *searched_when_clause *searched_when_clause_0
            searched_when_clause_0              =  WHEN *search_condition THEN *searched_when_clause_1
            searched_when_clause_1              =  *result_expression | NULL
            select_clause                       =  SELECT *select_clause_1 *select_clause_2
            select_clause_1                     =  epsilon | ALL | DISTINCT
            select_clause_2                     =  *select_clause_2_0 | *select_clause_2 $',' *select_clause_2_0
            select_clause_2_0                   =  $'*' | *expression *select_clause_2_1 | *identifier $'.' $'*'
            select_clause_2_1                   =  epsilon | *select_clause_2_1_1 *new_column_name
            select_clause_2_1_1                 =  epsilon | AS
            select_stmt                         =  *select_stmt_1 *select_stmt_2 *select_stmt_3 *select_stmt_4
            select_stmt_1                       =  WITH *select_stmt_1_1 *fullselect | *fullselect
            select_stmt_1_1                     =  *common_table_expression
+                                               |  *select_stmt_1_1 $',' *common_table_expression
            select_stmt_2                       =  epsilon | *order_by_clause
            select_stmt_3                       =  epsilon | *fetch_first_clause
            select_stmt_4                       =  epsilon | *select_stmt_4_1
            select_stmt_4_1                     =  *select_stmt_4_1_0 | *select_stmt_4_1 *select_stmt_4_1_0
            select_stmt_4_1_0                   =  *read_only_clause | *update_clause | *optimize_for_clause
            server_input_data                   =  $'_SQ_STRING_'
            server_name                         =  *identifier
            service_name                        =  *identifier
            set_operator                        =  UNION | UNION ALL | EXCEPT | EXCEPT ALL | INTERSECT | INTERSECT ALL
            simple_when_clause                  =  *expression *simple_when_clause_1
            simple_when_clause_1                =  *simple_when_clause_1_0
+                                               |  *simple_when_clause_1 *simple_when_clause_1_0
            simple_when_clause_1_0              =  WHEN *expression THEN *simple_when_clause_1_1
            simple_when_clause_1_1              =  *result_expression | NULL
            sort_key                            =  *sort_key_expression
            sort_key_expression                 =  *expression
            source_data_type                    =  *source_data_type_1
            source_data_type_1                  =  SMALLINT
+                                               |  *source_data_type_1_1
+                                               |  BIGINT
+                                               |  *source_data_type_1_2
+                                               |  DOUBLE *source_data_type_1_3
+                                               |  *source_data_type_1_4 *source_data_type_1_5
+                                               |  *source_data_type_1_6 *source_data_type_1_7
+                                               |  GRAPHIC *source_data_type_1_8
+                                               |  VARGRAPHIC $'(' $'_INTEGER_' $')'
+                                               |  LONG VARGRAPHIC
+                                               |  DATE
+                                               |  TIME
+                                               |  TIMESTAMP
+                                               |  *source_data_type_1_9 $'(' *integer_kmg $')'
+                                               |  DATALINK *source_data_type_1_10
            source_data_type_1_1                =  INTEGER | INT
            source_data_type_1_2                =  FLOAT *source_data_type_1_2_1 | REAL
            source_data_type_1_2_1              =  epsilon | $'(' $'_INTEGER_' $')'
            source_data_type_1_3                =  epsilon | PRECISION
            source_data_type_1_4                =  DECIMAL | DEC | NUMERIC | NUM
            source_data_type_1_5                =  epsilon | $'(' $'_INTEGER_' *source_data_type_1_5_1 $')'
            source_data_type_1_5_1              =  epsilon | $',' $'_INTEGER_'
            source_data_type_1_6                =  *source_data_type_1_6_1 *source_data_type_1_6_2
+                                               |  VARCHAR $'(' $'_INTEGER_' $')'
+                                               |  LONG VARCHAR
            source_data_type_1_6_1              =  CHARACTER | CHAR
            source_data_type_1_6_2              =  epsilon | $'(' $'_INTEGER_' $')'
            source_data_type_1_7                =  epsilon | FOR BIT DATA
            source_data_type_1_8                =  epsilon | $'(' $'_INTEGER_' $')'
            source_data_type_1_9                =  BLOB | CLOB | DBCLOB
            source_data_type_1_10               =  epsilon | $'(' $'_INTEGER_' $')'
            source_database_alias               =  *identifier
            source_table_name                   =  *identifier
            special_register                    =  CURRENT DATE
+                                               |  CURRENT DEGREE
+                                               |  CURRENT EXPLAIN MODE
+                                               |  CURRENT EXPLAIN SNAPSHOT
+                                               |  CURRENT NODE
+                                               |  CURRENT PATH
+                                               |  CURRENT QUERY OPTIMIZATION
+                                               |  CURRENT REFRESH AGE
+                                               |  CURRENT SCHEMA
+                                               |  CURRENT SERVER
+                                               |  CURRENT TIME
+                                               |  CURRENT TIMESTAMP
+                                               |  CURRENT TIMEZONE
+                                               |  USER
            specific_name                       =  *identifier | *identifier $'.' *identifier
            start_option                        =  MANUALSTART | AUTOSTART
            statement                           =  *statement_1
            statement_1                         =  *command | *ECHO_cmd | *SQL_stmt | *ESQL_stmt | *error
            statement_name                      =  *identifier
            statements                          =  epsilon
+                                               |  *statement
+                                               |  *statements $'_EOS_'
+                                               |  *statements $'_EOS_' *statement
            string_constant                     =  $'_SQ_STRING_'
            subselect                           =  *select_clause *from_clause *subselect_1 *subselect_2 *subselect_3
            subselect_1                         =  epsilon | *where_clause
            subselect_2                         =  epsilon | *group_by_clause
            subselect_3                         =  epsilon | *having_clause
            summary_fullselect                  =  *fullselect
            summary_table_options               =  DEFINITION ONLY
+                                               |  DATA INITIALLY DEFERRED REFRESH *summary_table_options_1
            summary_table_options_1             =  DEFERRED | IMMEDIATE
            super_groups                        =  ROLLUP $'(' *grouping_expression_list $')'
+                                               |  CUBE $'(' *grouping_expression_list $')'
+                                               |  *grand_total
            supertable_name                     =  *identifier
            supertype_name                      =  *identifier
            superview_name                      =  *identifier
            switch_name                         =  *identifier
            symbolic_dest_name                  =  *identifier
            system_container_clause             =  $'(' *system_container_clause_1 $')'
            system_container_clause_1           =  *system_container_clause_1_0
+                                               |  *system_container_clause_1 $',' *system_container_clause_1_0
            system_container_clause_1_0         =  $'_SQ_STRING_'
            system_containers                   =  *system_containers_0 | *system_containers *system_containers_0
            system_containers_0                 =  USING $'(' *system_containers_1 $')' *system_containers_2
            system_containers_1                 =  *system_containers_1_0
+                                               |  *system_containers_1 $',' *system_containers_1_0
            system_containers_1_0               =  $'_SQ_STRING_'
            system_containers_2                 =  epsilon | *on_nodes_clause
            system_name                         =  *identifier
            table_constraint_name               =  *identifier $'.' *identifier
+                                               |  *identifier $'.' *identifier $'.' *identifier
            table_name                          =  *identifier | *identifier $'.' *identifier
            table_or_view_column                =  *identifier $'.' *identifier
+                                               |  *identifier $'.' *identifier $'.' *identifier
            table_or_view_name                  =  *identifier | *identifier $'.' *identifier
            table_or_view_or_alias_name         =  *identifier | *identifier $'.' *identifier
            table_reference                     =  *table_reference_1 *table_reference_2
+                                               |  TABLE
+                                                  $'('
+                                                  *function_name
+                                                  $'('
+                                                  *table_reference_3
+                                                  $')'
+                                                  $')'
+                                                  *correlation_clause
+                                               |  $'(' *fullselect $')' *correlation_clause
+                                               |  TABLE $'(' *fullselect $')' *correlation_clause
+                                               |  *joined_table
            table_reference_1                   =  *table_or_view_name
+                                               |  *table_reference_1_1 $'(' *table_or_view_name $')'
            table_reference_1_1                 =  ONLY | OUTER
            table_reference_2                   =  epsilon | *correlation_clause
            table_reference_3                   =  epsilon | *table_reference_3_1
            table_reference_3_1                 =  *expression | *table_reference_3_1 $',' *expression
            tablespace_id                       =  *identifier
            tablespace_name                     =  *identifier
            tablespace_options                  =  *tablespace_options_1 *tablespace_options_2
            tablespace_options_1                =  epsilon | INDEX IN *tablespace_name
            tablespace_options_2                =  epsilon | LONG IN *tablespace_name
            target_area                         =  *identifier
            target_database_name                =  *identifier
            target_identifier                   =  *identifier
            targetmap                           =  *identifier
            tblspace_defn                       =  MANAGED
+                                                  BY
+                                                  *tblspace_defn_1
+                                                  *tblspace_defn_2
+                                                  *tblspace_defn_3
+                                                  *tblspace_defn_4
+                                                  *tblspace_defn_5
            tblspace_defn_1                     =  SYSTEM USING $'(' *tblspace_defn_1_1 $')'
+                                               |  DATABASE USING $'(' *tblspace_defn_1_2 $')'
            tblspace_defn_1_1                   =  *container_string | *tblspace_defn_1_1 $',' *container_string
            tblspace_defn_1_2                   =  *tblspace_defn_1_2_0 | *tblspace_defn_1_2 $',' *tblspace_defn_1_2_0
            tblspace_defn_1_2_0                 =  *tblspace_defn_1_2_1 *container_string *number_of_pages
            tblspace_defn_1_2_1                 =  FILE | DEVICE
            tblspace_defn_2                     =  epsilon | EXTENTSIZE *number_of_pages
            tblspace_defn_3                     =  epsilon | PREFETCHSIZE *number_of_pages
            tblspace_defn_4                     =  epsilon | OVERHEAD *number_of_milliseconds
            tblspace_defn_5                     =  epsilon | TRANSFERRATE *number_of_milliseconds
            tblspace_specs                      =  epsilon | IN *tablespace_name *tblspace_specs_1 *tblspace_specs_2
            tblspace_specs_1                    =  epsilon | INDEX IN *tablespace_name
            tblspace_specs_2                    =  epsilon | LONG IN *tablespace_name
            term                                =  *factor
+                                               |  *term $'*' *factor
+                                               |  *term $'/' *factor
+                                               |  *term $'_CONCAT_' *factor
+                                               |  *term CONCAT *factor
            territory                           =  *identifier
            timestamp                           =  $'_SQ_STRING_'
            transition_variable                 =  *column_name | *correlation_name $'.' *column_name
            trigger_name                        =  *identifier | *identifier $'.' *identifier
            triggered_SQL_stmt                  =  *fullselect
+                                               |  *SET_transition_variable
+                                               |  *SIGNAL_SQLSTATE_stmt
+                                               |  *INSERT_stmt
+                                               |  *UPDATE_stmt
+                                               |  *DELETE_stmt
            triggered_action                    =  *triggered_action_1 *triggered_action_2
            triggered_action_1                  =  epsilon | WHEN $'(' *search_condition $')'
            triggered_action_2                  =  *triggered_SQL_stmt | BEGIN ATOMIC *triggered_action_2_1 END
            triggered_action_2_1                =  *triggered_action_2_1_0
+                                               |  *triggered_action_2_1 *triggered_action_2_1_0
            triggered_action_2_1_0              =  *triggered_SQL_stmt $';'
            type_name                           =  *identifier | *identifier $'.' *identifier
            typed_element_list                  =  $'(' *typed_element_list_1 $')'
            typed_element_list_1                =  *typed_element_list_1_0
+                                               |  *typed_element_list_1 $',' *typed_element_list_1_0
            typed_element_list_1_0              =  *OID_column_definition
+                                               |  *with_options
+                                               |  *unique_constraint
+                                               |  *referential_constraint
+                                               |  *check_constraint
            typed_table_options                 =  *typed_table_options_1 *typed_table_options_2
            typed_table_options_1               =  epsilon | HIERARCHY *table_name | *under_clause
            typed_table_options_2               =  epsilon | *typed_element_list
            typed_table_or_view_name            =  *identifier
            under_clause                        =  UNDER *supertable_name INHERIT SELECT PRIVILEGES
            unique_clause                       =  epsilon | UNIQUE
            unique_constraint                   =  *constraint_clause
+                                                  *unique_constraint_1
+                                                  $'('
+                                                  *unique_constraint_2
+                                                  $')'
            unique_constraint_1                 =  UNIQUE | PRIMARY KEY
            unique_constraint_2                 =  *unique_constraint_2_0
+                                               |  *unique_constraint_2 $',' *unique_constraint_2_0
            unique_constraint_2_0               =  *column_name
            unsigned_constant                   =  $'_SQ_STRING_' | $'_INTEGER_' | $'_REAL_'
            update_clause                       =  FOR UPDATE *update_clause_1
            update_clause_1                     =  epsilon | OF *update_clause_1_1
            update_clause_1_1                   =  *column_name | *update_clause_1_1 $',' *column_name
            user_name                           =  *identifier
            username                            =  *identifier
            value                               =  $'_INTEGER_' | $'_SQ_STRING_'
            values_clause                       =  VALUES *values_clause_1
            values_clause_1                     =  *values_row | *values_clause_1 $',' *values_row
            values_row                          =  *expression | NULL | $'(' *values_row_1 $',' *values_row_2 $')'
            values_row_1                        =  *expression | NULL
            values_row_2                        =  *values_row_2_0 | *values_row_2 $',' *values_row_2_0
            values_row_2_0                      =  *expression | NULL
            variable_name                       =  *identifier
            view_name                           =  *identifier | *identifier $'.' *identifier
            view_under_clause                   =  UNDER *superview_name INHERIT SELECT PRIVILEGES
            view_with_options                   =  *column_name WITH OPTIONS *view_with_options_1
            view_with_options_1                 =  *view_with_options_1_0
+                                               |  *view_with_options_1 $',' *view_with_options_1_0
            view_with_options_1_0               =  SCOPE *typed_table_or_view_name | READ ONLY
            where_clause                        =  WHERE *search_condition
            with_options                        =  *column_name WITH OPTIONS *column_options
