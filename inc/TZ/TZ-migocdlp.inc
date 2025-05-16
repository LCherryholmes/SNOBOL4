            '.'                                 =  '.'
            '@'                                 =  '@'
            ','                                 =  ','
            '('                                 =  '('
            ')'                                 =  ')'
            ';'                                 =  ';'
            cdl_file                            =  *REPOSTUFF *CDL
            REPOSTUFF                           =  *repos_statements | epsilon
            repos_statements                    =  *true_release_statement *target_statement
+                                               |  *target_statement *true_release_statement
            target_statement                    =  TARGET *id $'.' *id $'.' *id
            true_release_statement              =  TRUE_RELEASE *BLOCK_TEXT
            CDL                                 =  *ORA_preamble
+                                               |  *SQS_preamble
+                                               |  *SYB_preamble
+                                               |  *INF_preamble
+                                               |  *DB2_preamble
+                                               |  *ORA_preamble *ORA_statementList
+                                               |  *SQS_preamble *SYB_statementList
+                                               |  *SYB_preamble *SYB_statementList
+                                               |  *INF_preamble *INF_statementList
+                                               |  *DB2_preamble *DB2_statementList
            INF_preamble                        =  DBMS INFORMIX
            ORA_preamble                        =  epsilon | DBMS ORACLE
            SQS_preamble                        =  DBMS SQL_SERVER
            SYB_preamble                        =  DBMS SYBASE
            DB2_preamble                        =  DBMS DB2
            INF_statementList                   =  *INF_statement | *INF_statementList *INF_statement
            ORA_statementList                   =  *ORA_statement | *ORA_statementList *ORA_statement
            SYB_statementList                   =  *SYB_statement | *SYB_statementList *SYB_statement
            DB2_statementList                   =  *DB2_statement | *DB2_statementList *DB2_statement
            INF_statement                       =  OCDL *stmt_no *inf_s END_OCDL | OCDL *stmt_no *error END_OCDL
            ORA_statement                       =  OCDL *stmt_no *ora_s END_OCDL | OCDL *stmt_no *error END_OCDL
            SYB_statement                       =  OCDL *stmt_no *syb_s END_OCDL | OCDL *stmt_no *error END_OCDL
            DB2_statement                       =  OCDL *stmt_no *db2_s END_OCDL | OCDL *stmt_no *error END_OCDL
            stmt_no                             =  epsilon | *number
            block                               =  BEGINBLOCK *block_text ENDBLOCK
            block_text                          =  *BLOCK_TEXT | *block_text *BLOCK_TEXT
            attr                                =  *id *factor
            attrs                               =  *attr | *attrs *attr
            cmplx_attrs                         =  *attrs | $'(' *attrs_list $')' | *attrs $'(' *attrs_list $')'
            attrs_list                          =  *nested_attrs | *attrs_list $',' *nested_attrs
            nested_attrs                        =  *attrs | $'(' *attrs_list $')' | *attrs $'(' *attrs_list $')'
            factor                              =  *block | *lstring | NULL | *number | *string | *symbol
            number                              =  *NUMBER
            string                              =  *STRING
            symbol                              =  *SYMBOL
            lstring                             =  *lstring_beg *lstring_mid *lstring_end
            lstring_beg                         =  *LONG_STRING_BEG
            lstring_end                         =  *LONG_STRING_END
            lstring_mid                         =  epsilon | *lstring_mid *LONG_STRING_MID
            nm_1                                =  *id
            nm_2                                =  *id $'.' *id
            nm_3                                =  *id $'.' *id $'.' *id
            nm_4                                =  *id $'.' *id $'.' *id $'.' *id
            nm_5                                =  *id $'.' *id $'.' *id $'.' *id $'.' *id
            id_d_1                              =  *id_d_2 | *id_d_2 $'@' *id
            id_d_2                              =  *id | *id_d_2 $'.' *id
            nm_d                                =  *id $'.' *id_d_1
            nm_n                                =  *id $'.' *number | *number
            nm_c                                =  *nm_5 | *nm_5 $';' *number
            nm_g                                =  *nm_3 | *nm_3 $';' *number
            id                                  =  *STRING
+                                               |  *SYMBOL
+                                               |  *UND_SYMBOL
+                                               |  BEGINBLOCK
+                                               |  ENDBLOCK
+                                               |  DBMS
+                                               |  OCDL
+                                               |  END_OCDL
+                                               |  TIME
+                                               |  ORGN
+                                               |  TARGET
+                                               |  TRUE_RELEASE
+                                               |  DEST
+                                               |  INFORMIX
+                                               |  ORACLE
+                                               |  SQL_SERVER
+                                               |  SYBASE
+                                               |  DB2
+                                               |  NULL
+                                               |  CREATE
+                                               |  BLOBSPACE
+                                               |  CHECK
+                                               |  DBSPACE
+                                               |  DATABASE
+                                               |  FOREIGN_KEY
+                                               |  INDEX
+                                               |  PRIMARY_KEY
+                                               |  PROCEDURE
+                                               |  ROLE
+                                               |  SYNONYM
+                                               |  TABLE
+                                               |  TRIGGER
+                                               |  UNIQUE_KEY
+                                               |  USER
+                                               |  VIEW
+                                               |  CLUSTER
+                                               |  DATABASE_LINK
+                                               |  DIRECTORY
+                                               |  FUNCTION
+                                               |  PACKAGE
+                                               |  PACKAGE_BODY
+                                               |  PROFILE
+                                               |  REFRESH_GROUP
+                                               |  ROLLBACK_SEGMENT
+                                               |  SEQUENCE
+                                               |  SNAPSHOT
+                                               |  SNAPSHOT_CLUSTER_KEY
+                                               |  SNAPSHOT_LOG
+                                               |  TABLE_CLUSTER_KEY
+                                               |  TABLESPACE
+                                               |  DEFAULT
+                                               |  GROUP
+                                               |  LOGICAL_COMMONKEY
+                                               |  LOGICAL_FOREIGNKEY
+                                               |  LOGICAL_PRIMARYKEY
+                                               |  LOGIN
+                                               |  RULE
+                                               |  SEGMENT
+                                               |  USERMESSAGE
+                                               |  ALIAS
+                                               |  DISTINCT_TYPE
+                                               |  EVENT_MONITOR
+                                               |  SUMMARY_TABLE
+                                               |  BUFFERPOOL
+                                               |  NODEGROUP
+                                               |  SCHEMA
            inf_s                               =  CREATE BLOBSPACE *nm_2 *cmplx_attrs
+                                               |  CREATE CHECK *nm_3 *cmplx_attrs
+                                               |  CREATE DBSPACE *nm_2 *cmplx_attrs
+                                               |  CREATE DATABASE *nm_1 *cmplx_attrs
+                                               |  CREATE FOREIGN_KEY *nm_3 *cmplx_attrs
+                                               |  CREATE INDEX *nm_3 *cmplx_attrs
+                                               |  CREATE PRIMARY_KEY *nm_3 *cmplx_attrs
+                                               |  CREATE PROCEDURE *nm_3 *cmplx_attrs
+                                               |  CREATE ROLE *nm_2 *cmplx_attrs
+                                               |  CREATE SYNONYM *nm_3 *cmplx_attrs
+                                               |  CREATE TABLE *nm_3 *cmplx_attrs
+                                               |  CREATE TRIGGER *nm_3 *cmplx_attrs
+                                               |  CREATE UNIQUE_KEY *nm_3 *cmplx_attrs
+                                               |  CREATE USER *nm_2 *cmplx_attrs
+                                               |  CREATE VIEW *nm_3 *cmplx_attrs
            ora_s                               =  CREATE CHECK *nm_2 *cmplx_attrs
+                                               |  CREATE CLUSTER *nm_2 *cmplx_attrs
+                                               |  CREATE DATABASE_LINK *nm_d *cmplx_attrs
+                                               |  CREATE DIRECTORY *nm_1 *cmplx_attrs
+                                               |  CREATE FOREIGN_KEY *nm_2 *cmplx_attrs
+                                               |  CREATE FUNCTION *nm_2 *cmplx_attrs
+                                               |  CREATE INDEX *nm_2 *cmplx_attrs
+                                               |  CREATE PACKAGE *nm_2 *cmplx_attrs
+                                               |  CREATE PACKAGE_BODY *nm_2 *cmplx_attrs
+                                               |  CREATE PRIMARY_KEY *nm_2 *cmplx_attrs
+                                               |  CREATE PROCEDURE *nm_2 *cmplx_attrs
+                                               |  CREATE PROFILE *nm_1 *cmplx_attrs
+                                               |  CREATE REFRESH_GROUP *nm_2 *cmplx_attrs
+                                               |  CREATE ROLE *nm_1 *cmplx_attrs
+                                               |  CREATE ROLLBACK_SEGMENT *nm_1 *cmplx_attrs
+                                               |  CREATE SEQUENCE *nm_2 *cmplx_attrs
+                                               |  CREATE SNAPSHOT *nm_2 *cmplx_attrs
+                                               |  CREATE SNAPSHOT_CLUSTER_KEY *nm_2 *cmplx_attrs
+                                               |  CREATE SNAPSHOT_LOG *nm_2 *cmplx_attrs
+                                               |  CREATE SYNONYM *nm_2 *cmplx_attrs
+                                               |  CREATE TABLE *nm_2 *cmplx_attrs
+                                               |  CREATE TABLE_CLUSTER_KEY *nm_2 *cmplx_attrs
+                                               |  CREATE TABLESPACE *nm_1 *cmplx_attrs
+                                               |  CREATE TRIGGER *nm_2 *cmplx_attrs
+                                               |  CREATE UNIQUE_KEY *nm_2 *cmplx_attrs
+                                               |  CREATE USER *nm_1 *cmplx_attrs
+                                               |  CREATE VIEW *nm_2 *cmplx_attrs
            syb_s                               =  CREATE DEFAULT *nm_3 *cmplx_attrs
+                                               |  CREATE FOREIGN_KEY *nm_4 *cmplx_attrs
+                                               |  CREATE GROUP *nm_2 *cmplx_attrs
+                                               |  CREATE INDEX *nm_4 *cmplx_attrs
+                                               |  CREATE LOGICAL_COMMONKEY *nm_c *cmplx_attrs
+                                               |  CREATE LOGICAL_FOREIGNKEY *nm_5 *cmplx_attrs
+                                               |  CREATE LOGICAL_PRIMARYKEY *nm_3 *cmplx_attrs
+                                               |  CREATE LOGIN *nm_2 *cmplx_attrs
+                                               |  CREATE PRIMARY_KEY *nm_4 *cmplx_attrs
+                                               |  CREATE PROCEDURE *nm_g *cmplx_attrs
+                                               |  CREATE RULE *nm_3 *cmplx_attrs
+                                               |  CREATE SEGMENT *nm_2 *cmplx_attrs
+                                               |  CREATE TABLE *nm_3 *cmplx_attrs
+                                               |  CREATE TRIGGER *nm_3 *cmplx_attrs
+                                               |  CREATE UNIQUE_KEY *nm_4 *cmplx_attrs
+                                               |  CREATE USER *nm_2 *cmplx_attrs
+                                               |  CREATE USERMESSAGE *nm_n *cmplx_attrs
+                                               |  CREATE VIEW *nm_3 *cmplx_attrs
            db2_s                               =  CREATE ALIAS *nm_2 *cmplx_attrs
+                                               |  CREATE CHECK *nm_3 *cmplx_attrs
+                                               |  CREATE DISTINCT_TYPE *nm_2 *cmplx_attrs
+                                               |  CREATE EVENT_MONITOR *nm_1 *cmplx_attrs
+                                               |  CREATE FOREIGN_KEY *nm_3 *cmplx_attrs
+                                               |  CREATE FUNCTION *nm_3 *cmplx_attrs
+                                               |  CREATE INDEX *nm_2 *cmplx_attrs
+                                               |  CREATE PACKAGE *nm_2 *cmplx_attrs
+                                               |  CREATE PRIMARY_KEY *nm_3 *cmplx_attrs
+                                               |  CREATE SUMMARY_TABLE *nm_2 *cmplx_attrs
+                                               |  CREATE TABLE *nm_2 *cmplx_attrs
+                                               |  CREATE TABLESPACE *nm_1 *cmplx_attrs
+                                               |  CREATE TRIGGER *nm_2 *cmplx_attrs
+                                               |  CREATE VIEW *nm_2 *cmplx_attrs
+                                               |  CREATE BUFFERPOOL *nm_1 *cmplx_attrs
+                                               |  CREATE NODEGROUP *nm_1 *cmplx_attrs
+                                               |  CREATE PROCEDURE *nm_3 *cmplx_attrs
+                                               |  CREATE SCHEMA *nm_1 *cmplx_attrs
+                                               |  CREATE UNIQUE_KEY *nm_3 *cmplx_attrs
