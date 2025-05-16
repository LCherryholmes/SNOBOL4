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
            target_statement                    =  _TARGET *id $'.' *id $'.' *id
            true_release_statement              =  _TRUERELEASE *BLOCK_TEXT
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
            INF_preamble                        =  _DBMS INFORMIX
            ORA_preamble                        =  epsilon | _DBMS ORACLE
            SQS_preamble                        =  _DBMS SQL_SERVER
            SYB_preamble                        =  _DBMS SYBASE
            DB2_preamble                        =  _DBMS DB2
            INF_statement                       =  _OCDL *stmt_no *inf_s _END_OCDL | _OCDL *stmt_no *error _END_OCDL
            ORA_statement                       =  _OCDL *stmt_no *ora_s _END_OCDL | _OCDL *stmt_no *error _END_OCDL
            SYB_statement                       =  _OCDL *stmt_no *syb_s _END_OCDL | _OCDL *stmt_no *error _END_OCDL
            DB2_statement                       =  _OCDL *stmt_no *db2_s _END_OCDL | _OCDL *stmt_no *error _END_OCDL
            INF_statementList                   =  *INF_statement | *INF_statementList *INF_statement
            ORA_statementList                   =  *ORA_statement | *ORA_statementList *ORA_statement
            SYB_statementList                   =  *SYB_statement | *SYB_statementList *SYB_statement
            DB2_statementList                   =  *DB2_statement | *DB2_statementList *DB2_statement
            stmt_no                             =  epsilon | *number
            block                               =  _BEGINBLOCK *block_text _ENDBLOCK
            block_text                          =  *BLOCK_TEXT | *block_text *BLOCK_TEXT
            change                              =  *id CHANGED TO *factor | *id CHANGED FROM *factor TO *factor
            changes                             =  *change | *changes *change
            attr                                =  *id *factor
            attrs                               =  *attr | *attrs *attr
            simpl_attrs                         =  epsilon | *attrs
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
            nm_n_1                              =  *number
            nm_n                                =  *id $'.' *number | *number
            nm_num                              =  *number $'.' *string
            nm_c                                =  *nm_5 | *nm_5 $';' *number
            nm_g                                =  *nm_3 | *nm_3 $';' *number
            id                                  =  *STRING
+                                               |  *SYMBOL
+                                               |  *UND_SYMBOL
+                                               |  ACTION
+                                               |  ADD
+                                               |  AFTER
+                                               |  ALIAS
+                                               |  ALL
+                                               |  ALTER
+                                               |  ANY
+                                               |  AS
+                                               |  AUDIT
+                                               |  BEFORE
+                                               |  BEXCEPTIONNODE
+                                               |  BIT
+                                               |  BLOBSPACE
+                                               |  BNODEGROUP
+                                               |  BUFFERPOOL
+                                               |  BY
+                                               |  CAPTURE
+                                               |  CASCADE
+                                               |  CCSID
+                                               |  CHANGED
+                                               |  CHANGES
+                                               |  CHAR
+                                               |  CHECK
+                                               |  CHUNK
+                                               |  CLOSE
+                                               |  CLUSTER
+                                               |  COLCOMMENT
+                                               |  COLLABEL
+                                               |  COLUMN
+                                               |  COLUMNS
+                                               |  COMMENT
+                                               |  CONTAINER
+                                               |  CREATE
+                                               |  CURRENT
+                                               |  DATA
+                                               |  DATABASE
+                                               |  DATE
+                                               |  DB2
+                                               |  DBSPACE
+                                               |  DECIMAL
+                                               |  DEFAULT
+                                               |  DEFAULTVALUE
+                                               |  DEFLT
+                                               |  DELETE
+                                               |  DIRECTORY
+                                               |  DROP
+                                               |  DROPRESTRICT
+                                               |  DSETPASS
+                                               |  EBCDIC
+                                               |  EDITPROC
+                                               |  ERASE
+                                               |  EXTENT
+                                               |  FIELDPROC
+                                               |  FILE
+                                               |  FILEGROUP
+                                               |  FLOAT
+                                               |  FOR
+                                               |  FOREIGN
+                                               |  FRAGMENT
+                                               |  FROM
+                                               |  FUNCTION
+                                               |  GRAPHIC
+                                               |  GROUP
+                                               |  HAVING
+                                               |  HTMLREPORT
+                                               |  INDEX
+                                               |  INFORMIX
+                                               |  INTEGER
+                                               |  KEY
+                                               |  LABEL
+                                               |  LOCAL
+                                               |  LOCATION
+                                               |  LOCKMAX
+                                               |  LOCKSIZE
+                                               |  LOGIN
+                                               |  LONG
+                                               |  MEMBER
+                                               |  MIGRATE
+                                               |  MIGRATEDEPSONLY
+                                               |  MODIFY
+                                               |  MOVE
+                                               |  N
+                                               |  NAME
+                                               |  NO
+                                               |  NOCOLCOMMENT
+                                               |  NOCOLLABEL
+                                               |  NOCOLUMNS
+                                               |  NOCOMMENT
+                                               |  NODE
+                                               |  NODEGROUP
+                                               |  NOLABEL
+                                               |  NONE
+                                               |  NOSETPASS
+                                               |  NOT
+                                               |  NOTNULL
+                                               |  NULL
+                                               |  NUMPARTS
+                                               |  ON
+                                               |  OPTION
+                                               |  ORACLE
+                                               |  OWNER
+                                               |  PACKAGE
+                                               |  PAGE
+                                               |  PARAMETER
+                                               |  PART
+                                               |  PARTITION
+                                               |  PARTS
+                                               |  PIECESIZE
+                                               |  POSITION
+                                               |  PROCEDURE
+                                               |  PROFILE
+                                               |  QUALIFIED
+                                               |  QUALIFIER
+                                               |  QUOTA
+                                               |  READ
+                                               |  REBUILD
+                                               |  RECOMPILE
+                                               |  REFERENCETB
+                                               |  RELEASE
+                                               |  RESOURCE
+                                               |  RESTRICT
+                                               |  ROLE
+                                               |  ROSHARE
+                                               |  ROW
+                                               |  RULE
+                                               |  SBCS
+                                               |  SCHEMA
+                                               |  SEGMENT
+                                               |  SEGSIZE
+                                               |  SELECT
+                                               |  SEQUENCE
+                                               |  SET
+                                               |  SMALLINT
+                                               |  SNAPSHOT
+                                               |  SQLID
+                                               |  SQL_SERVER
+                                               |  SSID
+                                               |  SUBPAGES
+                                               |  SUBPARTITION
+                                               |  SYBASE
+                                               |  SYNONYM
+                                               |  SYSTEM
+                                               |  TABLE
+                                               |  TABLESPACE
+                                               |  TIME
+                                               |  TIMESTAMP
+                                               |  TO
+                                               |  TRIGGER
+                                               |  TRUNCATE
+                                               |  TYPE
+                                               |  UNIQUE
+                                               |  USER
+                                               |  USERMESSAGE
+                                               |  VALIDPROC
+                                               |  VARCHAR
+                                               |  VARGRAPHIC
+                                               |  VIEW
+                                               |  VOLUMES
+                                               |  WHERE
+                                               |  WITH
+                                               |  X
+                                               |  YES
            inf_simpl_changes                   =  *changes
            inf_cmplx_changes                   =  *changes
+                                               |  $'(' *inf_sub_changes $')'
+                                               |  *changes $'(' *inf_sub_changes $')'
            inf_sub_changes                     =  *inf_sub_change | *inf_sub_changes $',' *inf_sub_change
            ora_simpl_changes                   =  *changes
            ora_cmplx_changes                   =  *changes
+                                               |  $'(' *ora_sub_changes $')'
+                                               |  *changes $'(' *ora_sub_changes $')'
            ora_sub_alters                      =  *changes
+                                               |  $'(' *ora_sub_changes $')'
+                                               |  *changes $'(' *ora_sub_changes $')'
            ora_sub_changes                     =  *ora_sub_change | *ora_sub_changes $',' *ora_sub_change
            syb_simpl_changes                   =  *changes
            syb_cmplx_changes                   =  *changes
+                                               |  $'(' *syb_sub_changes $')'
+                                               |  *changes $'(' *syb_sub_changes $')'
            syb_sub_changes                     =  *syb_sub_change | *syb_sub_changes $',' *syb_sub_change
            db2_cmplx_changes                   =  *changes
+                                               |  $'(' *db2_sub_changes $')'
+                                               |  *changes $'(' *db2_sub_changes $')'
            db2_sub_changes                     =  *db2_sub_change | *db2_sub_changes $',' *db2_sub_change
            inf_sub_change                      =  CREATE COLUMN *attrs
+                                               |  DROP COLUMN *nm_1
+                                               |  CREATE FRAGMENT *attrs
+                                               |  DROP FRAGMENT *nm_1
+                                               |  CREATE CHUNK *attrs
+                                               |  DROP CHUNK *nm_num
+                                               |  MODIFY COLUMN *nm_1 *id CHANGED TO *factor
+                                               |  MODIFY COLUMN *nm_1 *id CHANGED FROM *factor TO *factor
+                                               |  MODIFY COLUMN *nm_1 FROM POSITION *number TO POSITION *number
+                                               |  MODIFY FRAGMENT *nm_1 *id CHANGED TO *factor
+                                               |  MODIFY FRAGMENT *nm_1 *id CHANGED FROM *factor TO *factor
+                                               |  MODIFY FRAGMENT *nm_1 FROM POSITION *number TO POSITION *number
+                                               |  MODIFY CHUNK *nm_num *id CHANGED TO *factor
+                                               |  MODIFY CHUNK *nm_num *id CHANGED FROM *factor TO *factor
+                                               |  MODIFY CHUNK *nm_num FROM POSITION *number TO POSITION *number
            ora_sub_change                      =  CREATE COLUMN *attrs
+                                               |  CREATE EXTENT *attrs
+                                               |  CREATE FILE *attrs
+                                               |  CREATE MEMBER *attrs
+                                               |  CREATE QUOTA *attrs
+                                               |  CREATE OVERFLOW_TABLE *cmplx_attrs
+                                               |  CREATE LOB *attrs
+                                               |  CREATE LOB_PARTITION *attrs
+                                               |  CREATE LOB_SUBPARTITION *attrs
+                                               |  CREATE PARTITION *cmplx_attrs
+                                               |  CREATE PARTITION_KEY_COLUMN *attrs
+                                               |  CREATE SUBPARTITION *cmplx_attrs
+                                               |  CREATE SUBPARTITION_KEY_COLUMN *attrs
+                                               |  DROP COLUMN *nm_1
+                                               |  DROP MEMBER *nm_2
+                                               |  DROP QUOTA *nm_1
+                                               |  DROP EXTENT *number
+                                               |  DROP FILE *string
+                                               |  DROP OVERFLOW_TABLE *nm_1
+                                               |  DROP LOB *nm_1
+                                               |  DROP LOB_PARTITION *nm_1
+                                               |  DROP LOB_SUBPARTITION *nm_1
+                                               |  DROP PARTITION *nm_1
+                                               |  DROP PARTITION_KEY_COLUMN *nm_1
+                                               |  DROP SUBPARTITION *nm_1
+                                               |  DROP SUBPARTITION_KEY_COLUMN *nm_1
+                                               |  MODIFY COLUMN *nm_1 *id CHANGED TO *factor
+                                               |  MODIFY COLUMN *nm_1 *id CHANGED FROM *factor TO *factor
+                                               |  MODIFY COLUMN *nm_1 FROM POSITION *number TO POSITION *number
+                                               |  MODIFY EXTENT *number *id CHANGED TO *factor
+                                               |  MODIFY EXTENT *number *id CHANGED FROM *factor TO *factor
+                                               |  MODIFY FILE *string *id CHANGED TO *factor
+                                               |  MODIFY FILE *string *id CHANGED FROM *factor TO *factor
+                                               |  MODIFY FILE *string FROM POSITION *number TO POSITION *number
+                                               |  MODIFY MEMBER *nm_2 FROM POSITION *number TO POSITION *number
+                                               |  MODIFY QUOTA *nm_1 *id CHANGED TO *factor
+                                               |  MODIFY QUOTA *nm_1 *id CHANGED FROM *factor TO *factor
+                                               |  MODIFY QUOTA *nm_1 FROM POSITION *number TO POSITION *number
+                                               |  MODIFY RESOURCE *nm_1 *id CHANGED TO *factor
+                                               |  MODIFY RESOURCE *nm_1 *id CHANGED FROM *factor TO *factor
+                                               |  MODIFY LOB *nm_1 *id CHANGED TO *factor
+                                               |  MODIFY LOB *nm_1 *id CHANGED FROM *factor TO *factor
+                                               |  MODIFY LOB_PARTITION *nm_1 FROM POSITION *number TO POSITION *number
+                                               |  MODIFY LOB_PARTITION *nm_1 *id CHANGED FROM *factor TO *factor
+                                               |  MODIFY
+                                                  LOB_SUBPARTITION
+                                                  *nm_1
+                                                  FROM
+                                                  POSITION
+                                                  *number
+                                                  TO
+                                                  POSITION
+                                                  *number
+                                               |  MODIFY LOB_SUBPARTITION *nm_1 *id CHANGED FROM *factor TO *factor
+                                               |  MODIFY PARTITION *nm_1 FROM POSITION *number TO POSITION *number
+                                               |  MODIFY PARTITION *nm_1 *id CHANGED FROM *factor TO *factor
+                                               |  MODIFY PARTITION_KEY_COLUMN *nm_1 *id CHANGED TO *factor
+                                               |  MODIFY
+                                                  PARTITION_KEY_COLUMN
+                                                  *nm_1
+                                                  *id
+                                                  CHANGED
+                                                  FROM
+                                                  *factor
+                                                  TO
+                                                  *factor
+                                               |  MODIFY
+                                                  PARTITION_KEY_COLUMN
+                                                  *nm_1
+                                                  FROM
+                                                  POSITION
+                                                  *number
+                                                  TO
+                                                  POSITION
+                                                  *number
+                                               |  MODIFY SUBPARTITION *nm_1 FROM POSITION *number TO POSITION *number
+                                               |  MODIFY SUBPARTITION *nm_1 *id CHANGED FROM *factor TO *factor
+                                               |  MODIFY SUBPARTITION_KEY_COLUMN *nm_1 *id CHANGED TO *factor
+                                               |  MODIFY
+                                                  SUBPARTITION_KEY_COLUMN
+                                                  *nm_1
+                                                  *id
+                                                  CHANGED
+                                                  FROM
+                                                  *factor
+                                                  TO
+                                                  *factor
+                                               |  MODIFY
+                                                  SUBPARTITION_KEY_COLUMN
+                                                  *nm_1
+                                                  FROM
+                                                  POSITION
+                                                  *number
+                                                  TO
+                                                  POSITION
+                                                  *number
+                                               |  ALTER OVERFLOW_TABLE *nm_1 *ora_sub_alters
+                                               |  ALTER LOB *nm_1 *ora_sub_alters
+                                               |  ALTER LOB_PARTITION *nm_1 *ora_sub_alters
+                                               |  ALTER LOB_SUBPARTITION *nm_1 *ora_sub_alters
+                                               |  ALTER PARTITION *nm_1 *ora_sub_alters
+                                               |  ALTER SUBPARTITION *nm_1 *ora_sub_alters
            syb_sub_change                      =  CREATE ALIAS *attrs
+                                               |  CREATE COLUMN *attrs
+                                               |  CREATE DATABASE_DEVICE *attrs
+                                               |  CREATE SEGMENT_DEVICE *attrs
+                                               |  DROP ALIAS *nm_2
+                                               |  DROP COLUMN *nm_1
+                                               |  DROP COLUMN *nm_2
+                                               |  DROP DATABASE_DEVICE *nm_1
+                                               |  DROP SEGMENT_DEVICE *nm_1
+                                               |  MODIFY COLUMN *nm_1 *id CHANGED TO *factor
+                                               |  MODIFY COLUMN *nm_2 *id CHANGED TO *factor
+                                               |  MODIFY DATABASE_DEVICE *nm_1 *id CHANGED TO *factor
+                                               |  MODIFY COLUMN *nm_1 *id CHANGED FROM *factor TO *factor
+                                               |  MODIFY COLUMN *nm_2 *id CHANGED FROM *factor TO *factor
+                                               |  MODIFY DATABASE_DEVICE *nm_1 *id CHANGED FROM *factor TO *factor
+                                               |  MODIFY ALIAS *nm_2 FROM POSITION *number TO POSITION *number
+                                               |  MODIFY COLUMN *nm_1 FROM POSITION *number TO POSITION *number
+                                               |  MODIFY COLUMN *nm_2 FROM POSITION *number TO POSITION *number
+                                               |  MODIFY
+                                                  SEGMENT_DEVICE
+                                                  *nm_1
+                                                  FROM
+                                                  POSITION
+                                                  *number
+                                                  TO
+                                                  POSITION
+                                                  *number
            db2_sub_change                      =  CREATE COLUMN *attrs
+                                               |  CREATE CONTAINER *attrs
+                                               |  CREATE PARAMETER *attrs
+                                               |  CREATE RETURN_TYPE *attrs
+                                               |  CREATE TABLE_COLUMN *attrs
+                                               |  CREATE NODE *attrs
+                                               |  CREATE BNODEGROUP *attrs
+                                               |  CREATE BEXCEPTIONNODE *attrs
+                                               |  DROP COLUMN *nm_1
+                                               |  DROP CONTAINER *nm_n_1
+                                               |  DROP CONTAINER *nm_num
+                                               |  DROP PARAMETER *nm_n
+                                               |  DROP RETURN_TYPE *nm_1
+                                               |  DROP TABLE_COLUMN *nm_1
+                                               |  DROP NODE *nm_n
+                                               |  DROP BNODEGROUP *nm_1
+                                               |  DROP BEXCEPTIONNODE *nm_n
+                                               |  MODIFY COLUMN *nm_1 *id CHANGED TO *factor
+                                               |  MODIFY COLUMN *nm_1 *id CHANGED FROM *factor TO *factor
+                                               |  MODIFY COLUMN *nm_1 FROM POSITION *number TO POSITION *number
+                                               |  MODIFY CONTAINER *nm_n_1 *id CHANGED TO *factor
+                                               |  MODIFY CONTAINER *nm_n_1 *id CHANGED FROM *factor TO *factor
+                                               |  MODIFY CONTAINER *nm_n_1 FROM POSITION *number TO POSITION *number
+                                               |  MODIFY CONTAINER *nm_num *id CHANGED TO *factor
+                                               |  MODIFY CONTAINER *nm_num *id CHANGED FROM *factor TO *factor
+                                               |  MODIFY CONTAINER *nm_num FROM POSITION *number TO POSITION *number
+                                               |  MODIFY PARAMETER *nm_n *id CHANGED TO *factor
+                                               |  MODIFY PARAMETER *nm_n *id CHANGED FROM *factor TO *factor
+                                               |  MODIFY PARAMETER *nm_n FROM POSITION *number TO POSITION *number
+                                               |  MODIFY RETURN_TYPE *nm_1 *id CHANGED TO *factor
+                                               |  MODIFY RETURN_TYPE *nm_1 *id CHANGED FROM *factor TO *factor
+                                               |  MODIFY RETURN_TYPE *nm_1 FROM POSITION *number TO POSITION *number
+                                               |  MODIFY TABLE_COLUMN *nm_1 *id CHANGED TO *factor
+                                               |  MODIFY TABLE_COLUMN *nm_1 *id CHANGED FROM *factor TO *factor
+                                               |  MODIFY TABLE_COLUMN *nm_1 FROM POSITION *number TO POSITION *number
+                                               |  MODIFY NODE *nm_n *id CHANGED TO *factor
+                                               |  MODIFY NODE *nm_n *id CHANGED FROM *factor TO *factor
+                                               |  MODIFY NODE *nm_n FROM POSITION *number TO POSITION *number
+                                               |  MODIFY BNODEGROUP *nm_1 *id CHANGED TO *factor
+                                               |  MODIFY BNODEGROUP *nm_1 *id CHANGED FROM *factor TO *factor
+                                               |  MODIFY BNODEGROUP *nm_1 FROM POSITION *number TO POSITION *number
+                                               |  MODIFY BEXCEPTIONNODE *nm_n *id CHANGED TO *factor
+                                               |  MODIFY BEXCEPTIONNODE *nm_n *id CHANGED FROM *factor TO *factor
            inf_s                               =  ALTER BLOBSPACE *nm_2 *inf_cmplx_changes
+                                               |  ALTER CHECK *nm_3 *inf_simpl_changes
+                                               |  ALTER DBSPACE *nm_2 *inf_cmplx_changes
+                                               |  ALTER DATABASE *nm_1 *inf_simpl_changes
+                                               |  ALTER FOREIGN_KEY *nm_3 *inf_cmplx_changes
+                                               |  ALTER INDEX *nm_3 *inf_cmplx_changes
+                                               |  ALTER PRIMARY_KEY *nm_3 *inf_cmplx_changes
+                                               |  ALTER PROCEDURE *nm_3 *inf_simpl_changes
+                                               |  ALTER ROLE *nm_2 *inf_simpl_changes
+                                               |  ALTER SYNONYM *nm_3 *inf_simpl_changes
+                                               |  ALTER TABLE *nm_3 *inf_cmplx_changes
+                                               |  ALTER TRIGGER *nm_3 *inf_simpl_changes
+                                               |  ALTER UNIQUE_KEY *nm_3 *inf_cmplx_changes
+                                               |  ALTER USER *nm_2 *inf_simpl_changes
+                                               |  ALTER VIEW *nm_3 *inf_cmplx_changes
+                                               |  CREATE BLOBSPACE *nm_2 *cmplx_attrs
+                                               |  CREATE CHECK *nm_3 *simpl_attrs
+                                               |  CREATE DBSPACE *nm_2 *cmplx_attrs
+                                               |  CREATE DATABASE *nm_1 *simpl_attrs
+                                               |  CREATE FOREIGN_KEY *nm_3 *cmplx_attrs
+                                               |  CREATE INDEX *nm_3 *cmplx_attrs
+                                               |  CREATE PRIMARY_KEY *nm_3 *cmplx_attrs
+                                               |  CREATE PROCEDURE *nm_3 *simpl_attrs
+                                               |  CREATE ROLE *nm_2 *simpl_attrs
+                                               |  CREATE SYNONYM *nm_3 *simpl_attrs
+                                               |  CREATE TABLE *nm_3 *cmplx_attrs
+                                               |  CREATE TRIGGER *nm_3 *simpl_attrs
+                                               |  CREATE UNIQUE_KEY *nm_3 *cmplx_attrs
+                                               |  CREATE USER *nm_2 *simpl_attrs
+                                               |  CREATE VIEW *nm_3 *cmplx_attrs
+                                               |  DROP BLOBSPACE *nm_2
+                                               |  DROP CHECK *nm_3
+                                               |  DROP DBSPACE *nm_2
+                                               |  DROP DATABASE *nm_1
+                                               |  DROP FOREIGN_KEY *nm_3
+                                               |  DROP INDEX *nm_3
+                                               |  DROP PRIMARY_KEY *nm_3
+                                               |  DROP PROCEDURE *nm_3
+                                               |  DROP ROLE *nm_2
+                                               |  DROP SYNONYM *nm_3
+                                               |  DROP TABLE *nm_3
+                                               |  DROP TRIGGER *nm_3
+                                               |  DROP UNIQUE_KEY *nm_3
+                                               |  DROP USER *nm_2
+                                               |  DROP VIEW *nm_3
+                                               |  MIGRATE BLOBSPACE *nm_2
+                                               |  MIGRATE CHECK *nm_3
+                                               |  MIGRATE DBSPACE *nm_2
+                                               |  MIGRATE DATABASE *nm_1
+                                               |  MIGRATE FOREIGN_KEY *nm_3
+                                               |  MIGRATE INDEX *nm_3
+                                               |  MIGRATE PRIMARY_KEY *nm_3
+                                               |  MIGRATE PROCEDURE *nm_3
+                                               |  MIGRATE ROLE *nm_2
+                                               |  MIGRATE SYNONYM *nm_3
+                                               |  MIGRATE TABLE *nm_3
+                                               |  MIGRATE TRIGGER *nm_3
+                                               |  MIGRATE UNIQUE_KEY *nm_3
+                                               |  MIGRATE USER *nm_2
+                                               |  MIGRATE VIEW *nm_3
+                                               |  REBUILD BLOBSPACE *nm_2
+                                               |  REBUILD DBSPACE *nm_2
+                                               |  REBUILD DATABASE *nm_1
+                                               |  REBUILD FOREIGN_KEY *nm_3
+                                               |  REBUILD INDEX *nm_3
+                                               |  REBUILD PRIMARY_KEY *nm_3
+                                               |  REBUILD TABLE *nm_3
+                                               |  REBUILD UNIQUE_KEY *nm_3
+                                               |  TRUNCATE TABLE *nm_3
            ora_s                               =  ALTER CHECK *nm_2 *ora_simpl_changes
+                                               |  ALTER CLUSTER *nm_2 *ora_cmplx_changes
+                                               |  ALTER DATABASE_LINK *nm_d *ora_simpl_changes
+                                               |  ALTER FOREIGN_KEY *nm_2 *ora_cmplx_changes
+                                               |  ALTER FUNCTION *nm_2 *ora_cmplx_changes
+                                               |  ALTER INDEX *nm_2 *ora_cmplx_changes
+                                               |  ALTER PACKAGE *nm_2 *ora_cmplx_changes
+                                               |  ALTER PACKAGE_BODY *nm_2 *ora_cmplx_changes
+                                               |  ALTER PRIMARY_KEY *nm_2 *ora_cmplx_changes
+                                               |  ALTER PROCEDURE *nm_2 *ora_cmplx_changes
+                                               |  ALTER PROFILE *nm_1 *ora_cmplx_changes
+                                               |  ALTER REFRESH_GROUP *nm_2 *ora_cmplx_changes
+                                               |  ALTER ROLE *nm_1 *ora_simpl_changes
+                                               |  ALTER ROLLBACK_SEGMENT *nm_1 *ora_simpl_changes
+                                               |  ALTER SEQUENCE *nm_2 *ora_simpl_changes
+                                               |  ALTER SNAPSHOT *nm_2 *ora_cmplx_changes
+                                               |  ALTER SNAPSHOT_LOG *nm_2 *ora_simpl_changes
+                                               |  ALTER SNAPSHOT_CLUSTER_KEY *nm_2 *ora_cmplx_changes
+                                               |  ALTER SYNONYM *nm_2 *ora_simpl_changes
+                                               |  ALTER TABLE *nm_2 *ora_cmplx_changes
+                                               |  ALTER TABLE_CLUSTER_KEY *nm_2 *ora_cmplx_changes
+                                               |  ALTER TABLESPACE *nm_1 *ora_cmplx_changes
+                                               |  ALTER TRIGGER *nm_2 *ora_cmplx_changes
+                                               |  ALTER UNIQUE_KEY *nm_2 *ora_cmplx_changes
+                                               |  ALTER USER *nm_1 *ora_cmplx_changes
+                                               |  ALTER VIEW *nm_2 *ora_cmplx_changes
+                                               |  ALTER DIRECTORY *nm_1 *ora_simpl_changes
+                                               |  CREATE CHECK *nm_2 *simpl_attrs
+                                               |  CREATE CLUSTER *nm_2 *cmplx_attrs
+                                               |  CREATE DATABASE_LINK *nm_d *simpl_attrs
+                                               |  CREATE DIRECTORY *nm_1 *simpl_attrs
+                                               |  CREATE FOREIGN_KEY *nm_2 *cmplx_attrs
+                                               |  CREATE FUNCTION *nm_2 *cmplx_attrs
+                                               |  CREATE INDEX *nm_2 *cmplx_attrs
+                                               |  CREATE PACKAGE *nm_2 *cmplx_attrs
+                                               |  CREATE PACKAGE_BODY *nm_2 *cmplx_attrs
+                                               |  CREATE PRIMARY_KEY *nm_2 *cmplx_attrs
+                                               |  CREATE PROCEDURE *nm_2 *cmplx_attrs
+                                               |  CREATE PROFILE *nm_1 *cmplx_attrs
+                                               |  CREATE REFRESH_GROUP *nm_2 *cmplx_attrs
+                                               |  CREATE ROLE *nm_1 *simpl_attrs
+                                               |  CREATE ROLLBACK_SEGMENT *nm_1 *simpl_attrs
+                                               |  CREATE SEQUENCE *nm_2 *simpl_attrs
+                                               |  CREATE SNAPSHOT *nm_2 *cmplx_attrs
+                                               |  CREATE SNAPSHOT_CLUSTER_KEY *nm_2 *cmplx_attrs
+                                               |  CREATE SNAPSHOT_LOG *nm_2 *simpl_attrs
+                                               |  CREATE SYNONYM *nm_2 *simpl_attrs
+                                               |  CREATE TABLE *nm_2 *cmplx_attrs
+                                               |  CREATE TABLE_CLUSTER_KEY *nm_2 *cmplx_attrs
+                                               |  CREATE TABLESPACE *nm_1 *cmplx_attrs
+                                               |  CREATE TRIGGER *nm_2 *cmplx_attrs
+                                               |  CREATE UNIQUE_KEY *nm_2 *cmplx_attrs
+                                               |  CREATE USER *nm_1 *cmplx_attrs
+                                               |  CREATE VIEW *nm_2 *cmplx_attrs
+                                               |  DROP CHECK *nm_2
+                                               |  DROP CLUSTER *nm_2
+                                               |  DROP DATABASE_LINK *nm_d
+                                               |  DROP DIRECTORY *nm_1
+                                               |  DROP FOREIGN_KEY *nm_2
+                                               |  DROP FUNCTION *nm_2
+                                               |  DROP INDEX *nm_2
+                                               |  DROP PACKAGE *nm_2
+                                               |  DROP PACKAGE_BODY *nm_2
+                                               |  DROP PRIMARY_KEY *nm_2
+                                               |  DROP PROCEDURE *nm_2
+                                               |  DROP PROFILE *nm_1
+                                               |  DROP REFRESH_GROUP *nm_2
+                                               |  DROP ROLE *nm_1
+                                               |  DROP ROLLBACK_SEGMENT *nm_1
+                                               |  DROP SEQUENCE *nm_2
+                                               |  DROP SNAPSHOT *nm_2
+                                               |  DROP SNAPSHOT_CLUSTER_KEY *nm_2
+                                               |  DROP SNAPSHOT_LOG *nm_2
+                                               |  DROP SYNONYM *nm_2
+                                               |  DROP TABLE *nm_2
+                                               |  DROP TABLE_CLUSTER_KEY *nm_2
+                                               |  DROP TABLESPACE *nm_1
+                                               |  DROP TRIGGER *nm_2
+                                               |  DROP UNIQUE_KEY *nm_2
+                                               |  DROP USER *nm_1
+                                               |  DROP VIEW *nm_2
+                                               |  MIGRATE CHECK *nm_2
+                                               |  MIGRATE CLUSTER *nm_2
+                                               |  MIGRATE DATABASE_LINK *nm_d
+                                               |  MIGRATE FOREIGN_KEY *nm_2
+                                               |  MIGRATE FUNCTION *nm_2
+                                               |  MIGRATE INDEX *nm_2
+                                               |  MIGRATE PACKAGE *nm_2
+                                               |  MIGRATE PACKAGE_BODY *nm_2
+                                               |  MIGRATE PRIMARY_KEY *nm_2
+                                               |  MIGRATE PROCEDURE *nm_2
+                                               |  MIGRATE PROFILE *nm_1
+                                               |  MIGRATE REFRESH_GROUP *nm_2
+                                               |  MIGRATE ROLE *nm_1
+                                               |  MIGRATE ROLLBACK_SEGMENT *nm_1
+                                               |  MIGRATE SEQUENCE *nm_2
+                                               |  MIGRATE SNAPSHOT *nm_2
+                                               |  MIGRATE SNAPSHOT_LOG *nm_2
+                                               |  MIGRATE SNAPSHOT_CLUSTER_KEY *nm_2
+                                               |  MIGRATE SYNONYM *nm_2
+                                               |  MIGRATE TABLE *nm_2
+                                               |  MIGRATE TABLESPACE *nm_1
+                                               |  MIGRATE TRIGGER *nm_2
+                                               |  MIGRATE UNIQUE_KEY *nm_2
+                                               |  MIGRATE USER *nm_1
+                                               |  MIGRATE VIEW *nm_2
+                                               |  MIGRATE VIEW *nm_1
+                                               |  HTMLREPORT CHECK *nm_2
+                                               |  HTMLREPORT CLUSTER *nm_2
+                                               |  HTMLREPORT DATABASE_LINK *nm_d
+                                               |  HTMLREPORT FOREIGN_KEY *nm_2
+                                               |  HTMLREPORT FUNCTION *nm_2
+                                               |  HTMLREPORT INDEX *nm_2
+                                               |  HTMLREPORT PACKAGE *nm_2
+                                               |  HTMLREPORT PACKAGE_BODY *nm_2
+                                               |  HTMLREPORT PRIMARY_KEY *nm_2
+                                               |  HTMLREPORT PROCEDURE *nm_2
+                                               |  HTMLREPORT PROFILE *nm_1
+                                               |  HTMLREPORT REFRESH_GROUP *nm_2
+                                               |  HTMLREPORT ROLE *nm_1
+                                               |  HTMLREPORT ROLLBACK_SEGMENT *nm_1
+                                               |  HTMLREPORT SEQUENCE *nm_2
+                                               |  HTMLREPORT SNAPSHOT *nm_2
+                                               |  HTMLREPORT SNAPSHOT_LOG *nm_2
+                                               |  HTMLREPORT SNAPSHOT_CLUSTER_KEY *nm_2
+                                               |  HTMLREPORT SYNONYM *nm_2
+                                               |  HTMLREPORT TABLE *nm_2
+                                               |  HTMLREPORT TABLESPACE *nm_1
+                                               |  HTMLREPORT TRIGGER *nm_2
+                                               |  HTMLREPORT UNIQUE_KEY *nm_2
+                                               |  HTMLREPORT USER *nm_1
+                                               |  HTMLREPORT VIEW *nm_2
+                                               |  HTMLREPORT DIRECTORY *nm_1
+                                               |  REBUILD CLUSTER *nm_2
+                                               |  REBUILD INDEX *nm_2
+                                               |  REBUILD PRIMARY_KEY *nm_2
+                                               |  REBUILD ROLLBACK_SEGMENT *nm_1
+                                               |  REBUILD SNAPSHOT *nm_2
+                                               |  REBUILD SNAPSHOT_LOG *nm_2
+                                               |  REBUILD SNAPSHOT_CLUSTER_KEY *nm_2
+                                               |  REBUILD TABLE *nm_2
+                                               |  REBUILD TABLESPACE *nm_1
+                                               |  REBUILD UNIQUE_KEY *nm_2
+                                               |  RECOMPILE FUNCTION *nm_2
+                                               |  RECOMPILE PACKAGE *nm_2
+                                               |  RECOMPILE PACKAGE_BODY *nm_2
+                                               |  RECOMPILE PROCEDURE *nm_2
+                                               |  RECOMPILE SNAPSHOT *nm_2
+                                               |  RECOMPILE SNAPSHOT_CLUSTER_KEY *nm_2
+                                               |  RECOMPILE TRIGGER *nm_2
+                                               |  RECOMPILE VIEW *nm_2
            syb_s                               =  ALTER CHECK *nm_3 *syb_simpl_changes
+                                               |  ALTER DATABASE *nm_1 *syb_cmplx_changes
+                                               |  ALTER DEFAULT *nm_3 *syb_simpl_changes
+                                               |  ALTER FOREIGN_KEY *nm_4 *syb_cmplx_changes
+                                               |  ALTER GROUP *nm_2 *syb_simpl_changes
+                                               |  ALTER INDEX *nm_4 *syb_cmplx_changes
+                                               |  ALTER LOGICAL_COMMONKEY *nm_c *syb_cmplx_changes
+                                               |  ALTER LOGICAL_FOREIGNKEY *nm_5 *syb_cmplx_changes
+                                               |  ALTER LOGICAL_PRIMARYKEY *nm_3 *syb_cmplx_changes
+                                               |  ALTER LOGIN *nm_2 *syb_simpl_changes
+                                               |  ALTER PRIMARY_KEY *nm_4 *syb_cmplx_changes
+                                               |  ALTER PROCEDURE *nm_g *syb_simpl_changes
+                                               |  ALTER RULE *nm_3 *syb_simpl_changes
+                                               |  ALTER SEGMENT *nm_2 *syb_cmplx_changes
+                                               |  ALTER TABLE *nm_3 *syb_cmplx_changes
+                                               |  ALTER TRIGGER *nm_3 *syb_simpl_changes
+                                               |  ALTER UNIQUE_KEY *nm_4 *syb_cmplx_changes
+                                               |  ALTER USER *nm_2 *syb_cmplx_changes
+                                               |  ALTER USERMESSAGE *nm_n *syb_simpl_changes
+                                               |  ALTER VIEW *nm_3 *syb_cmplx_changes
+                                               |  CREATE CHECK *nm_3 *simpl_attrs
+                                               |  CREATE DATABASE *nm_1 *cmplx_attrs
+                                               |  CREATE DEFAULT *nm_3 *simpl_attrs
+                                               |  CREATE FOREIGN_KEY *nm_4 *cmplx_attrs
+                                               |  CREATE GROUP *nm_2 *simpl_attrs
+                                               |  CREATE INDEX *nm_4 *cmplx_attrs
+                                               |  CREATE LOGICAL_COMMONKEY *nm_c *cmplx_attrs
+                                               |  CREATE LOGICAL_FOREIGNKEY *nm_5 *cmplx_attrs
+                                               |  CREATE LOGICAL_PRIMARYKEY *nm_3 *cmplx_attrs
+                                               |  CREATE LOGIN *nm_2 *simpl_attrs
+                                               |  CREATE PRIMARY_KEY *nm_4 *cmplx_attrs
+                                               |  CREATE PROCEDURE *nm_g *simpl_attrs
+                                               |  CREATE RULE *nm_3 *simpl_attrs
+                                               |  CREATE SEGMENT *nm_2 *cmplx_attrs
+                                               |  CREATE TABLE *nm_3 *cmplx_attrs
+                                               |  CREATE TRIGGER *nm_3 *simpl_attrs
+                                               |  CREATE UNIQUE_KEY *nm_4 *cmplx_attrs
+                                               |  CREATE USER *nm_2 *cmplx_attrs
+                                               |  CREATE USERMESSAGE *nm_n *simpl_attrs
+                                               |  CREATE VIEW *nm_3 *cmplx_attrs
+                                               |  DROP CHECK *nm_3
+                                               |  DROP DATABASE *nm_1
+                                               |  DROP DEFAULT *nm_3
+                                               |  DROP FOREIGN_KEY *nm_4
+                                               |  DROP GROUP *nm_2
+                                               |  DROP INDEX *nm_4
+                                               |  DROP LOGICAL_COMMONKEY *nm_c
+                                               |  DROP LOGICAL_FOREIGNKEY *nm_5
+                                               |  DROP LOGICAL_PRIMARYKEY *nm_3
+                                               |  DROP LOGIN *nm_2
+                                               |  DROP PRIMARY_KEY *nm_4
+                                               |  DROP PROCEDURE *nm_g
+                                               |  DROP RULE *nm_3
+                                               |  DROP SEGMENT *nm_2
+                                               |  DROP TABLE *nm_3
+                                               |  DROP TRIGGER *nm_3
+                                               |  DROP UNIQUE_KEY *nm_4
+                                               |  DROP USER *nm_2
+                                               |  DROP USERMESSAGE *nm_n
+                                               |  DROP VIEW *nm_3
+                                               |  MIGRATE CHECK *nm_3
+                                               |  MIGRATE DATABASE *nm_1
+                                               |  MIGRATE DEFAULT *nm_3
+                                               |  MIGRATE FOREIGN_KEY *nm_4
+                                               |  MIGRATE GROUP *nm_2
+                                               |  MIGRATE INDEX *nm_4
+                                               |  MIGRATE LOGICAL_COMMONKEY *nm_c
+                                               |  MIGRATE LOGICAL_FOREIGNKEY *nm_5
+                                               |  MIGRATE LOGICAL_PRIMARYKEY *nm_3
+                                               |  MIGRATE LOGIN *nm_2
+                                               |  MIGRATE PRIMARY_KEY *nm_4
+                                               |  MIGRATE PROCEDURE *nm_g
+                                               |  MIGRATE RULE *nm_3
+                                               |  MIGRATE SEGMENT *nm_2
+                                               |  MIGRATE TABLE *nm_3
+                                               |  MIGRATE TRIGGER *nm_3
+                                               |  MIGRATE UNIQUE_KEY *nm_4
+                                               |  MIGRATE USER *nm_2
+                                               |  MIGRATE USERMESSAGE *nm_n
+                                               |  MIGRATE VIEW *nm_3
+                                               |  MIGRATEDEPSONLY DATABASE *nm_1
+                                               |  MIGRATEDEPSONLY FOREIGN_KEY *nm_4
+                                               |  MIGRATEDEPSONLY INDEX *nm_4
+                                               |  MIGRATEDEPSONLY PRIMARY_KEY *nm_4
+                                               |  MIGRATEDEPSONLY PROCEDURE *nm_g
+                                               |  MIGRATEDEPSONLY TABLE *nm_3
+                                               |  MIGRATEDEPSONLY TRIGGER *nm_3
+                                               |  MIGRATEDEPSONLY UNIQUE_KEY *nm_4
+                                               |  MIGRATEDEPSONLY USER *nm_2
+                                               |  MIGRATEDEPSONLY VIEW *nm_3
+                                               |  REBUILD INDEX *nm_4
+                                               |  REBUILD PRIMARY_KEY *nm_4
+                                               |  REBUILD PROCEDURE *nm_g
+                                               |  REBUILD TABLE *nm_3
+                                               |  REBUILD TRIGGER *nm_3
+                                               |  REBUILD UNIQUE_KEY *nm_4
+                                               |  REBUILD VIEW *nm_3
+                                               |  RECOMPILE TABLE *nm_3
            db2_s                               =  ALTER ALIAS *nm_2 *db2_cmplx_changes
+                                               |  ALTER CHECK *nm_3 *db2_cmplx_changes
+                                               |  ALTER DISTINCT_TYPE *nm_2 *db2_cmplx_changes
+                                               |  ALTER EVENT_MONITOR *nm_1 *db2_cmplx_changes
+                                               |  ALTER FOREIGN_KEY *nm_3 *db2_cmplx_changes
+                                               |  ALTER FUNCTION *nm_3 *db2_cmplx_changes
+                                               |  ALTER INDEX *nm_2 *db2_cmplx_changes
+                                               |  ALTER PACKAGE *nm_2 *db2_cmplx_changes
+                                               |  ALTER PRIMARY_KEY *nm_3 *db2_cmplx_changes
+                                               |  ALTER TABLE *nm_2 *db2_cmplx_changes
+                                               |  ALTER TABLESPACE *nm_1 *db2_cmplx_changes
+                                               |  ALTER SUMMARY_TABLE *nm_2 *db2_cmplx_changes
+                                               |  ALTER TRIGGER *nm_2 *db2_cmplx_changes
+                                               |  ALTER VIEW *nm_2 *db2_cmplx_changes
+                                               |  ALTER BUFFERPOOL *nm_1 *db2_cmplx_changes
+                                               |  ALTER NODEGROUP *nm_1 *db2_cmplx_changes
+                                               |  ALTER PROCEDURE *nm_3 *db2_cmplx_changes
+                                               |  ALTER SCHEMA *nm_1 *db2_cmplx_changes
+                                               |  ALTER UNIQUE_KEY *nm_3 *db2_cmplx_changes
+                                               |  CREATE ALIAS *nm_2 *cmplx_attrs
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
+                                               |  DROP ALIAS *nm_2
+                                               |  DROP CHECK *nm_3
+                                               |  DROP EVENT_MONITOR *nm_1
+                                               |  DROP FOREIGN_KEY *nm_3
+                                               |  DROP FUNCTION *nm_3
+                                               |  DROP INDEX *nm_2
+                                               |  DROP PACKAGE *nm_2
+                                               |  DROP PRIMARY_KEY *nm_3
+                                               |  DROP TABLE *nm_2
+                                               |  DROP TABLESPACE *nm_1
+                                               |  DROP SUMMARY_TABLE *nm_2
+                                               |  DROP TRIGGER *nm_2
+                                               |  DROP VIEW *nm_2
+                                               |  DROP BUFFERPOOL *nm_1
+                                               |  DROP NODEGROUP *nm_1
+                                               |  DROP PROCEDURE *nm_3
+                                               |  DROP UNIQUE_KEY *nm_3
+                                               |  DROP SCHEMA *nm_1
+                                               |  DROP DISTINCT_TYPE *nm_2
+                                               |  MIGRATE ALIAS *nm_2
+                                               |  MIGRATE CHECK *nm_3
+                                               |  MIGRATE DISTINCT_TYPE *nm_2
+                                               |  MIGRATE EVENT_MONITOR *nm_1
+                                               |  MIGRATE FOREIGN_KEY *nm_3
+                                               |  MIGRATE FUNCTION *nm_3
+                                               |  MIGRATE INDEX *nm_2
+                                               |  MIGRATE PRIMARY_KEY *nm_3
+                                               |  MIGRATE TABLE *nm_2
+                                               |  MIGRATE TABLESPACE *nm_1
+                                               |  MIGRATE SUMMARY_TABLE *nm_2
+                                               |  MIGRATE TRIGGER *nm_2
+                                               |  MIGRATE VIEW *nm_2
+                                               |  MIGRATE BUFFERPOOL *nm_1
+                                               |  MIGRATE NODEGROUP *nm_1
+                                               |  MIGRATE PROCEDURE *nm_3
+                                               |  MIGRATE SCHEMA *nm_1
+                                               |  MIGRATE UNIQUE_KEY *nm_3
+                                               |  RECOMPILE PACKAGE *nm_2
+                                               |  REBUILD ALIAS *nm_2
+                                               |  REBUILD CHECK *nm_3
+                                               |  REBUILD EVENT_MONITOR *nm_1
+                                               |  REBUILD FOREIGN_KEY *nm_3
+                                               |  REBUILD FUNCTION *nm_3
+                                               |  REBUILD INDEX *nm_2
+                                               |  REBUILD PRIMARY_KEY *nm_3
+                                               |  REBUILD TABLE *nm_2
+                                               |  REBUILD TABLESPACE *nm_1
+                                               |  REBUILD SUMMARY_TABLE *nm_2
+                                               |  REBUILD TRIGGER *nm_2
+                                               |  REBUILD VIEW *nm_2
+                                               |  REBUILD BUFFERPOOL *nm_1
+                                               |  REBUILD NODEGROUP *nm_1
+                                               |  REBUILD PROCEDURE *nm_3
+                                               |  REBUILD SCHEMA *nm_1
+                                               |  REBUILD UNIQUE_KEY *nm_3
