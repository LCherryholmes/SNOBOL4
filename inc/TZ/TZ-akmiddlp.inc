            '('                                 =  '('
            ')'                                 =  ')'
            '*'                                 =  '*'
            ','                                 =  ','
            '-'                                 =  '-'
            '+'                                 =  '+'
            '.'                                 =  '.'
            ';'                                 =  ';'
            '/'                                 =  '/'
            '='                                 =  '='
            '@'                                 =  '@'
            condition                           =  $'_CONDITION_'
            query                               =  $'_QUERY_BODY_'
            commands                            =  *command | *commands *command
            command                             =  *ddl_command
            ddl_command                         =  *DDL_command | *DDL_command $'_EOT_' | *error $';' | *error $'_EOT_'
            skip_command                        =  COMMIT
+                                               |  COMMIT WORK
+                                               |  ROLLBACK
+                                               |  ROLLBACK ON
+                                               |  ROLLBACK WORK
+                                               |  LABEL
+                                               |  LABEL ON
+                                               |  DELETE *error
+                                               |  GRANT *error
+                                               |  INSERT *error
+                                               |  LOCK *error
+                                               |  REVOKE *error
+                                               |  SELECT *error
+                                               |  UPDATE *error
+                                               |  SET CURRENT *error
            DDL_command                         =  *skip_command $';'
+                                               |  *set_command $';'
+                                               |  *modify_command $';'
+                                               |  *alter_command $';'
+                                               |  *create_command $';'
+                                               |  *drop_command $';'
            comment_command                     =  *comment_on_table | *comment_on_column | *comment_on_alias
            label_command                       =  *label_on_table | *label_on_column | *label_on_alias
            modify_command                      =  *comment_command | *label_command
            comment_on_column                   =  COMMENT ON COLUMN *comment_on_column_1 IS *comment_string
            comment_on_column_1                 =  *identifier $'.' *identifier $'.' *column_name
+                                               |  *identifier $'.' *column_name
            comment_on_alias                    =  COMMENT ON ALIAS *comment_on_alias_1 IS *comment_string
            comment_on_alias_1                  =  *identifier $'.' *identifier $'.' *alias_name
+                                               |  *identifier $'.' *alias_name
            comment_on_table                    =  COMMENT ON *comment_on_table_1 $'(' *comment_on_column_list $')'
+                                               |  COMMENT ON TABLE *comment_on_table_1 IS *comment_string
            comment_on_table_1                  =  *identifier $'.' *identifier | *identifier
            comment_on_column_list_1            =  *column_name IS *comment_string
            comment_on_column_list              =  *comment_on_column_list_1
+                                               |  *comment_on_column_list $',' *comment_on_column_list_1
            comment_string                      =  $'_SQ_STRING_'
            label_on_column                     =  LABEL ON COLUMN *label_on_column_1 IS *label_string
            label_on_column_1                   =  *identifier $'.' *identifier $'.' *column_name
+                                               |  *identifier $'.' *column_name
            label_on_alias                      =  LABEL ON ALIAS *label_on_alias_1 IS *label_string
            label_on_alias_1                    =  *identifier $'.' *identifier $'.' *alias_name
+                                               |  *identifier $'.' *alias_name
            label_on_table                      =  LABEL ON *label_on_table_1 $'(' *label_on_column_list $')'
+                                               |  LABEL ON TABLE *label_on_table_1 IS *label_string
            label_on_table_1                    =  *identifier $'.' *identifier | *identifier
            label_on_column_list_1              =  *column_name IS *label_string
            label_on_column_list                =  *label_on_column_list_1
+                                               |  *label_on_column_list $',' *label_on_column_list_1
            label_string                        =  $'_SQ_STRING_'
            as                                  =  AS
            set_command                         =  SET CURRENT SQLID $'=' *set_command_1
            set_command_1                       =  $'_SQ_STRING_' | $'_STRING_' | *identifier
            alter_command                       =  ALTER ALIAS *error
+                                               |  ALTER CHECK *error
+                                               |  ALTER FOREIGN KEY *error
+                                               |  ALTER INDEX *error
+                                               |  ALTER PRIMARY KEY *error
+                                               |  *alter_table
+                                               |  ALTER STOGROUP *error
+                                               |  ALTER SYNONYM *error
+                                               |  ALTER TABLESPACE *error
+                                               |  ALTER UNIQUE KEY *error
+                                               |  ALTER VIEW *error
            create_command                      =  *create_alias
+                                               |  *create_database
+                                               |  *create_index
+                                               |  *create_stogroup
+                                               |  *create_synonym
+                                               |  *create_table
+                                               |  *create_tablespace
+                                               |  *create_view
            drop_command                        =  *drop_alias
+                                               |  *drop_database
+                                               |  *drop_index
+                                               |  *drop_stogroup
+                                               |  *drop_synonym
+                                               |  *drop_table
+                                               |  *drop_tablespace
+                                               |  *drop_view
            authorization_name                  =  *identifier
            bp_name                             =  *identifier
            catalog_name                        =  *identifier
            column_name                         =  *identifier
            constraint_name                     =  *identifier
            database_name                       =  *identifier
            index_name                          =  *identifier
            member_name                         =  *identifier
            program_name                        =  *identifier
            stogroup_name                       =  *identifier
            synonym_name                        =  *identifier
            table_name                          =  *identifier
            tablespace_name                     =  *identifier
            view_name                           =  *identifier
            alias_name                          =  *identifier
            alias                               =  *alias_name
+                                               |  *schema_name $'.' *alias_name
+                                               |  *schema_name $'.' *alias_name $'.' *identifier
            database                            =  *database_name | *schema_name $'.' *database_name
            constraint                          =  *constraint_name | *schema_name $'.' *constraint_name
            stogroup                            =  *stogroup_name | *schema_name $'.' *stogroup_name
            index                               =  *index_name | *schema_name $'.' *index_name
            synonym                             =  *synonym_name | *schema_name $'.' *synonym_name
            table                               =  *table_name | *schema_name $'.' *table_name
            tablespace                          =  *tablespace_name | *schema_name $'.' *tablespace_name
            view                                =  *view_name | *schema_name $'.' *view_name
            alter_table                         =  ALTER TABLE *table *alter_table_1
            alter_table_1                       =  *alter_table_1_1 | *alter_table_1 *alter_table_1_1
            alter_table_1_1                     =  *alter_add
+                                               |  *alter_drop
+                                               |  VALIDPROC *program_name
+                                               |  AUDIT NONE
+                                               |  AUDIT CHANGES
+                                               |  AUDIT ALL
+                                               |  DATA CAPTURE CHANGES
+                                               |  DATA CAPTURE NONE
            alter_add                           =  ADD RESTRICT ON DROP
+                                               |  ADD PRIMARY KEY $'(' *constant_list $')'
+                                               |  PRIMARY KEY $'(' *constant_list $')'
+                                               |  ADD *check_constraint
+                                               |  ADD *referential_constraint
+                                               |  *referential_constraint
+                                               |  ADD *alter_column_definition_0
            alter_drop                          =  DROP PRIMARY KEY
+                                               |  DROP FOREIGN KEY *constraint
+                                               |  DROP CONSTRAINT *constraint
+                                               |  DROP CHECK *constraint
+                                               |  DROP RESTRICT ON DROP
            alter_column_definition_0           =  *column_name *datatype *alter_column_definition_1
            alter_column_definition_1           =  epsilon | *alter_column_definition_1 *alter_column_definition_1_1
            alter_column_definition_1_1         =  NOT NULL
+                                               |  FOR SBCS DATA
+                                               |  FOR MIXED DATA
+                                               |  FOR BIT DATA
+                                               |  WITH DEFAULT *column_definition_1_2
+                                               |  DEFAULT *column_definition_1_2
+                                               |  *references_clause
+                                               |  *check_constraint
+                                               |  FIELDPROC *program_name
+                                               |  FIELDPROC *program_name $'(' *constant_list $')'
            drop_alias                          =  DROP ALIAS *alias
            drop_database                       =  DROP DATABASE *database
            drop_index                          =  DROP INDEX *index
            drop_stogroup                       =  DROP STOGROUP *stogroup
            drop_synonym                        =  DROP SYNONYM *synonym
            drop_table                          =  DROP TABLE *table
            drop_tablespace                     =  DROP TABLESPACE *tablespace
            drop_view                           =  DROP VIEW *view
            create_alias                        =  CREATE ALIAS *alias FOR *create_alias_1
            create_alias_1                      =  *identifier
+                                               |  *identifier $'.' *identifier
+                                               |  *identifier $'.' *identifier $'.' *identifier
            create_database                     =  CREATE DATABASE *database *create_database_1
            create_database_1                   =  epsilon | *create_database_1 *create_database_1_1
            create_database_1_1                 =  BUFFERPOOL *identifier
+                                               |  ROSHARE OWNER
+                                               |  ROSHARE READ
+                                               |  AS WORKFILE *create_database_1_2
+                                               |  STOGROUP SYSDEFLT
+                                               |  CCSID ASCII
+                                               |  CCSID EBCDIC
            create_database_1_2                 =  epsilon | FOR *member_name
            create_index                        =  CREATE
+                                                  *create_index_0
+                                                  *create_index_1
+                                                  INDEX
+                                                  *index
+                                                  ON
+                                                  *create_index_2
+                                                  $'('
+                                                  *indexed_column_list
+                                                  $')'
+                                                  *index_blocks
+                                                  *create_index_3
+                                                  *create_index_4
            create_index_0                      =  epsilon | TYPE *n
            create_index_1                      =  epsilon | UNIQUE | UNIQUE WHERE NOT NULL
            create_index_2                      =  *table
            create_index_4                      =  epsilon | *create_index_4 *create_index_4_1
            create_index_4_1                    =  SUBPAGES *n
+                                               |  BUFFERPOOL *bp_name
+                                               |  CLOSE NO
+                                               |  CLOSE YES
+                                               |  DSETPASS *password
+                                               |  DEFER YES
+                                               |  DEFER NO
+                                               |  PIECESIZE *n_bytes
            create_index_3                      =  epsilon | CLUSTER *partition_clause
            indexed_column                      =  *column_name *indexed_column_list_1
            constant_list                       =  *constant_list_1 | *constant_list $',' *constant_list_1
            constant_list_1                     =  *column_name | $'_SQ_STRING_' | $'_NUMBER_'
            indexed_column_list                 =  *indexed_column | *indexed_column_list $',' *indexed_column
            indexed_column_list_1               =  epsilon | ASC | DESC
            partition_clause                    =  epsilon | $'(' *partition_clause_1 $')'
            partition_clause_1                  =  *partition_clause_1_1
+                                               |  *partition_clause_1 $',' *partition_clause_1_1
            partition_clause_1_1                =  PART *n VALUES $'(' *constant_list $')' *index_blocks
            using_block                         =  USING *using_block_1
            using_block_1                       =  VCAT *catalog_name | STOGROUP *stogroup_name *using_block_2
            using_block_2                       =  epsilon | *using_block_2 *using_block_2_1
            using_block_2_1                     =  PRIQTY *n | SECQTY *n | ERASE YES | ERASE NO
            gbpcache_block                      =  GBPCACHE CHANGED | GBPCACHE ALL
            free_block                          =  FREEPAGE *n | PCTFREE *n
            index_block                         =  *using_block | *gbpcache_block | *free_block
            index_blocks                        =  epsilon | *index_blocks *index_block
            create_stogroup                     =  CREATE STOGROUP *error
            create_synonym                      =  CREATE
+                                                  *create_synonym_1
+                                                  SYNONYM
+                                                  *synonym
+                                                  FOR
+                                                  *authorization_name
+                                                  $'.'
+                                                  *table
            create_synonym_1                    =  epsilon | PUBLIC
            create_table                        =  CREATE
+                                                  *global_temporary
+                                                  TABLE
+                                                  *table
+                                                  *create_table_0
+                                                  *create_table_2
            global_temporary                    =  epsilon | GLOBAL TEMPORARY
            create_table_0                      =  $'(' *create_table_1 $')' | LIKE *table_name
            create_table_1                      =  *create_table_1_1 | *create_table_1 $',' *create_table_1_1
            create_table_1_1                    =  *column_definition
+                                               |  *unique_constraint
+                                               |  *referential_constraint
+                                               |  *check_constraint
            column_definition                   =  epsilon | *column_definition_0
            column_definition_0                 =  *column_name *datatype *column_definition_1
            column_definition_1                 =  epsilon | *column_definition_1 *column_definition_1_1
            column_definition_1_1               =  NOT NULL
+                                               |  UNIQUE
+                                               |  PRIMARY KEY
+                                               |  FOR SBCS DATA
+                                               |  FOR MIXED DATA
+                                               |  FOR BIT DATA
+                                               |  WITH DEFAULT *column_definition_1_2
+                                               |  DEFAULT *column_definition_1_2
+                                               |  *references_clause
+                                               |  *check_constraint
+                                               |  FIELDPROC *program_name
+                                               |  FIELDPROC *program_name $'(' *constant_list $')'
            column_definition_1_2               =  epsilon
+                                               |  USER
+                                               |  CURRENT SQLID
+                                               |  NULL
+                                               |  $'_SQ_STRING_'
+                                               |  G $'_SQ_STRING_'
+                                               |  N $'_SQ_STRING_'
+                                               |  X $'_SQ_STRING_'
+                                               |  $'_STRING_'
+                                               |  G $'_STRING_'
+                                               |  N $'_STRING_'
+                                               |  X $'_STRING_'
+                                               |  $'_NUMBER_'
+                                               |  $'_REAL_'
            unique_constraint                   =  PRIMARY KEY $'(' *constant_list $')'
+                                               |  UNIQUE $'(' *constant_list $')'
            referential_constraint              =  FOREIGN KEY *constraint $'(' *constant_list $')' *references_clause
+                                               |  FOREIGN KEY $'(' *constant_list $')' *references_clause
            references_clause                   =  REFERENCES *table *references_clause_1 *references_clause_2
            references_clause_1                 =  epsilon | $'(' *constant_list $')'
            references_clause_2                 =  epsilon
+                                               |  ON DELETE RESTRICT
+                                               |  ON DELETE NO ACTION
+                                               |  ON DELETE CASCADE
+                                               |  ON DELETE SET NULL
            check_constraint                    =  CHECK $'(' *condition $')'
+                                               |  CONSTRAINT *constraint CHECK $'(' *condition $')'
            create_table_2                      =  epsilon | *create_table_2 *create_table_2_1
            create_table_2_1                    =  IN *table
+                                               |  IN DATABASE *table
+                                               |  EDITPROC *program_name
+                                               |  VALIDPROC *program_name
+                                               |  AUDIT NONE
+                                               |  AUDIT CHANGES
+                                               |  AUDIT ALL
+                                               |  OBID *n
+                                               |  DATA CAPTURE NONE
+                                               |  DATA CAPTURE CHANGES
+                                               |  WITH RESTRICT ON DROP
+                                               |  CCSID ASCII
+                                               |  CCSID EBCDIC
            create_tablespace                   =  CREATE
+                                                  *create_tablespace_1
+                                                  TABLESPACE
+                                                  *create_tablespace_2
+                                                  *index_blocks
+                                                  *create_tablespace_3
+                                                  *create_tablespace_4
            tablespace_block                    =  *index_block | COMPRESS YES | COMPRESS NO
            tablespace_blocks                   =  epsilon | *tablespace_blocks *tablespace_block
            create_tablespace_1                 =  epsilon | LARGE
            create_tablespace_2                 =  *tablespace | *tablespace IN *database_name
            create_tablespace_3                 =  epsilon | SEGSIZE *n | NUMPARTS *n *create_tablespace_3_1
            create_tablespace_3_1               =  epsilon | $'(' *create_tablespace_3_2 $')'
            create_tablespace_3_2               =  PART *n *tablespace_blocks
+                                               |  *create_tablespace_3_2 $',' PART *n *tablespace_blocks
            create_tablespace_4                 =  epsilon | *create_tablespace_4 *create_tablespace_4_1
            create_tablespace_4_1               =  BUFFERPOOL *bp_name
+                                               |  LOCKSIZE ANY
+                                               |  LOCKSIZE TABLESPACE
+                                               |  LOCKSIZE TABLE
+                                               |  LOCKSIZE PAGE
+                                               |  LOCKSIZE ROW
+                                               |  LOCKMAX SYSTEM
+                                               |  LOCKMAX *n
+                                               |  DSETPASS *password
+                                               |  COMPRESS YES
+                                               |  COMPRESS NO
+                                               |  CCSID ASCII
+                                               |  CCSID EBCDIC
+                                               |  LOCKPART YES
+                                               |  LOCKPART NO
+                                               |  MAXROWS *n
            create_view                         =  CREATE VIEW *view *create_view_1 *as *query *create_view_2
            create_view_1                       =  epsilon | $'(' *indexed_column_list $')'
            create_view_2                       =  epsilon
+                                               |  WITH CHECK OPTION
+                                               |  WITH CASCADED CHECK OPTION
+                                               |  WITH LOCAL CHECK OPTION
            datatype                            =  GRAPHIC
+                                               |  GRAPHIC $'(' *n $')'
+                                               |  LONG VARGRAPHIC
+                                               |  VARGRAPHIC $'(' *n $')'
+                                               |  RAW $'(' *n $')'
+                                               |  ROWID
+                                               |  CHAR
+                                               |  CHAR $'(' *n $')'
+                                               |  CHARACTER
+                                               |  CHARACTER $'(' *n $')'
+                                               |  VARCHAR $'(' *n $')'
+                                               |  VARCHAR2 $'(' *n $')'
+                                               |  CHAR VARYING $'(' *n $')'
+                                               |  CHARACTER VARYING $'(' *n $')'
+                                               |  DATE
+                                               |  NUMBER $'(' *n $',' *n $')'
+                                               |  NUMBER $'(' $'*' $',' *n $')'
+                                               |  NUMBER $'(' *n $',' $'-' *n $')'
+                                               |  NUMBER $'(' $'*' $',' $'-' *n $')'
+                                               |  NUMERIC
+                                               |  NUMERIC $'(' *n $')'
+                                               |  NUMERIC $'(' $'*' $')'
+                                               |  NUMERIC $'(' *n $',' *n $')'
+                                               |  NUMERIC $'(' $'*' $',' *n $')'
+                                               |  NUMERIC $'(' *n $',' $'-' *n $')'
+                                               |  NUMERIC $'(' $'*' $',' $'-' *n $')'
+                                               |  DEC
+                                               |  DEC $'(' *n $')'
+                                               |  DEC $'(' $'*' $')'
+                                               |  DEC $'(' *n $',' *n $')'
+                                               |  DEC $'(' $'*' $',' *n $')'
+                                               |  DEC $'(' *n $',' $'-' *n $')'
+                                               |  DEC $'(' $'*' $',' $'-' *n $')'
+                                               |  DECIMAL
+                                               |  DECIMAL $'(' *n $')'
+                                               |  DECIMAL $'(' $'*' $')'
+                                               |  DECIMAL $'(' *n $',' *n $')'
+                                               |  DECIMAL $'(' $'*' $',' *n $')'
+                                               |  DECIMAL $'(' *n $',' $'-' *n $')'
+                                               |  DECIMAL $'(' $'*' $',' $'-' *n $')'
+                                               |  NUMBER
+                                               |  NUMBER $'(' *n $')'
+                                               |  NUMBER $'(' $'*' $')'
+                                               |  FLOAT
+                                               |  FLOAT $'(' $'*' $')'
+                                               |  FLOAT $'(' *n $')'
+                                               |  REAL
+                                               |  DOUBLE
+                                               |  DOUBLE PRECISION
+                                               |  INTEGER
+                                               |  INT
+                                               |  SMALLINT
+                                               |  MLSLABEL
+                                               |  LONG RAW
+                                               |  LONG
+                                               |  LONG VARCHAR
+                                               |  TIME
+                                               |  TIMESTAMP
            identifier                          =  $'_IDENT_'
+                                               |  $'_DQ_STRING_'
+                                               |  ACTION
+                                               |  ADD
+                                               |  AFTER
+                                               |  ALIAS
+                                               |  ALL
+                                               |  ALLOW
+                                               |  ALTER
+                                               |  AND
+                                               |  ANY
+                                               |  AS
+                                               |  ASC
+                                               |  ASCII
+                                               |  ASUTIME
+                                               |  AUDIT
+                                               |  AUX
+                                               |  AUXILIARY
+                                               |  BEFORE
+                                               |  BEGIN
+                                               |  BETWEEN
+                                               |  BIT
+                                               |  BUFFERPOOL
+                                               |  BY
+                                               |  CALL
+                                               |  CAPTURE
+                                               |  CASCADE
+                                               |  CASCADED
+                                               |  CASE
+                                               |  CAST
+                                               |  CCSID
+                                               |  CHANGED
+                                               |  CHANGES
+                                               |  CHAR
+                                               |  CHARACTER
+                                               |  CHECK
+                                               |  CLOSE
+                                               |  CLUSTER
+                                               |  COLLECTION
+                                               |  COLLID
+                                               |  COLUMN
+                                               |  COMMENT
+                                               |  COMMIT
+                                               |  COMPRESS
+                                               |  CONCAT
+                                               |  CONNECTION
+                                               |  CONTAINS
+                                               |  COUNT
+                                               |  CREATE
+                                               |  CURRENT
+                                               |  CURRENT_DATE
+                                               |  CURRENT_LC_CTYPE
+                                               |  CURRENT_PATH
+                                               |  CURRENT_TIME
+                                               |  CURRENT_TIMESTAMP
+                                               |  CURSOR
+                                               |  DATA
+                                               |  DATE
+                                               |  DAY
+                                               |  DAYS
+                                               |  DB2SQL
+                                               |  DBINFO
+                                               |  DEC
+                                               |  DECIMAL
+                                               |  DEFAULT
+                                               |  DEFER
+                                               |  DELETE
+                                               |  DESC
+                                               |  DESCRIPTOR
+                                               |  DETERMINISTIC
+                                               |  DISALLOW
+                                               |  DISTINCT
+                                               |  DOUBLE
+                                               |  DROP
+                                               |  DSETPASS
+                                               |  DSNDB04
+                                               |  DSSIZE
+                                               |  EBCDIC
+                                               |  EDITPROC
+                                               |  ELSE
+                                               |  END
+                                               |  ERASE
+                                               |  ESCAPE
+                                               |  EXCEPT
+                                               |  EXECUTE
+                                               |  EXISTS
+                                               |  EXTERNAL
+                                               |  FAST
+                                               |  FENCED
+                                               |  FIELDPROC
+                                               |  FINAL
+                                               |  FLOAT
+                                               |  FOR
+                                               |  FOREIGN
+                                               |  FREEPAGE
+                                               |  FROM
+                                               |  FULL
+                                               |  FUNCTION
+                                               |  G
+                                               |  GBPCACHE
+                                               |  GENERAL
+                                               |  GENERATED
+                                               |  GLOBAL
+                                               |  GO
+                                               |  GOTO
+                                               |  GRANT
+                                               |  GRAPHIC
+                                               |  GROUP
+                                               |  HAVING
+                                               |  HOUR
+                                               |  HOURS
+                                               |  IMMEDIATE
+                                               |  IN
+                                               |  INDEX
+                                               |  INNER
+                                               |  INOUT
+                                               |  INSERT
+                                               |  INT
+                                               |  INTEGER
+                                               |  INTO
+                                               |  IS
+                                               |  ISOBID
+                                               |  JOIN
+                                               |  K
+                                               |  KEY
+                                               |  LABEL
+                                               |  LANGUAGE
+                                               |  LARGE
+                                               |  LC_CTYPE
+                                               |  LEFT
+                                               |  LIKE
+                                               |  LOCAL
+                                               |  LOCALE
+                                               |  LOCATOR
+                                               |  LOCATORS
+                                               |  LOCK
+                                               |  LOCKMAX
+                                               |  LOCKPART
+                                               |  LOCKSIZE
+                                               |  LONG
+                                               |  M
+                                               |  MAXROWS
+                                               |  MICROSECOND
+                                               |  MICROSECONDS
+                                               |  MINUTE
+                                               |  MINUTES
+                                               |  MIXED
+                                               |  MLSLABEL
+                                               |  MODIFIES
+                                               |  MONTH
+                                               |  MONTHS
+                                               |  N
+                                               |  NAME
+                                               |  NO
+                                               |  NONE
+                                               |  NOT
+                                               |  NULL
+                                               |  NULLS
+                                               |  NUMBER
+                                               |  NUMERIC
+                                               |  NUMPARTS
+                                               |  OBID
+                                               |  OF
+                                               |  ON
+                                               |  OPTIMIZATION
+                                               |  OPTIMIZE
+                                               |  OPTION
+                                               |  OR
+                                               |  ORDER
+                                               |  OUT
+                                               |  OUTER
+                                               |  OWNER
+                                               |  PACKAGE
+                                               |  PAGE
+                                               |  PARAMETER
+                                               |  PART
+                                               |  PATH
+                                               |  PCTFREE
+                                               |  PIECESIZE
+                                               |  PLAN
+                                               |  PRECISION
+                                               |  PRIMARY
+                                               |  PRIQTY
+                                               |  PRIVILEGES
+                                               |  PROCEDURE
+                                               |  PROGRAM
+                                               |  PSID
+                                               |  PUBLIC
+                                               |  QUERYNO
+                                               |  RAW
+                                               |  READ
+                                               |  READS
+                                               |  REAL
+                                               |  REFERENCES
+                                               |  RENAME
+                                               |  RESTRICT
+                                               |  RESULT
+                                               |  RETURN
+                                               |  RETURNS
+                                               |  REVOKE
+                                               |  RIGHT
+                                               |  ROLLBACK
+                                               |  ROSHARE
+                                               |  ROW
+                                               |  ROWID
+                                               |  RUN
+                                               |  SBCS
+                                               |  SCHEMA
+                                               |  SCRATCHPAD
+                                               |  SECOND
+                                               |  SECONDS
+                                               |  SECQTY
+                                               |  SECURITY
+                                               |  SEGSIZE
+                                               |  SELECT
+                                               |  SET
+                                               |  SIMPLE
+                                               |  SMALLINT
+                                               |  SOME
+                                               |  SOURCE
+                                               |  SPECIFIC
+                                               |  SQLID
+                                               |  STANDARD
+                                               |  STAY
+                                               |  STOGROUP
+                                               |  STORES
+                                               |  STYLE
+                                               |  SUBPAGES
+                                               |  SYNONYM
+                                               |  SYSDEFLT
+                                               |  SYSFUN
+                                               |  SYSIBM
+                                               |  SYSPROC
+                                               |  SYSTEM
+                                               |  TABLE
+                                               |  TABLESPACE
+                                               |  TEMPORARY
+                                               |  THEN
+                                               |  TIME
+                                               |  TIMESTAMP
+                                               |  TO
+                                               |  TRIGGER
+                                               |  TYPE
+                                               |  UNION
+                                               |  UNIQUE
+                                               |  UPDATE
+                                               |  USER
+                                               |  USING
+                                               |  VALIDPROC
+                                               |  VALUES
+                                               |  VARCHAR
+                                               |  VARCHAR2
+                                               |  VARIANT
+                                               |  VARYING
+                                               |  VCAT
+                                               |  VIEW
+                                               |  VOLUMES
+                                               |  WHEN
+                                               |  WHERE
+                                               |  WITH
+                                               |  WLM
+                                               |  WORK
+                                               |  WORKFILE
+                                               |  X
+                                               |  YEAR
+                                               |  YEARS
+                                               |  YES
            n                                   =  $'_NUMBER_'
            n_bytes                             =  *n | *n K | *n M | *n G
            password                            =  *identifier
            schema_name                         =  *identifier
