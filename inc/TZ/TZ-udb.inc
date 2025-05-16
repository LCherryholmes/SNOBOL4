            $'_CONCAT_'                         =  '||'
            $'_EQ_'                             =  '='
            $'_DEREF_'                          =  '->'
            $'_NEQ_1_'                          =  '<>'
            $'_NEQ_2_'                          =  '!='
            $'_NEQ_3_'                          =  '^='
            $'_LT_'                             =  '<'
            $'_LEQ_'                            =  '<='
            $'_GT_'                             =  '>'
            $'_GEQ_'                            =  '>='
            $'_BSLASH_'                         =  bSlash
            $'_INTEGER_'                        =  SPAN('0123456789')
            $'_REAL_'                           =  SPAN('0123456789')
+                                                  !('.' (SPAN('0123456789') | epsilon))
+                                                  !('E' !(ANY('+-')) SPAN('0123456789'))
            $'_REAL_1_'                         =  (SPAN('0123456789') | epsilon)
+                                                  '.'
+                                                  SPAN('0123456789')
+                                                  !('E' !(ANY('+-')) SPAN('0123456789'))
            $'_DQ_STRING_'                      =  '"' !%NOTANY('"') '"'
            $'_SQ_STRING_'                      =  "'" !%("'" "'" | NOTANY("'")) "'"
            SEMICOLON                           =  ';'
            $'_ADD'                             =  'ADD'
            $'_AFTER'                           =  'AFTER'
            $'_ALIAS'                           =  'ALIAS'
            $'_ALL'                             =  'ALL'
            $'_ALTER'                           =  'ALTER'
            $'_AND'                             =  'AND'
            $'_ANY'                             =  'ANY'
            $'_AS'                              =  'AS'
            $'_ASC'                             =  'ASC'
            $'_AT'                              =  'AT'
            $'_ATOMIC'                          =  'ATOMIC'
            $'_AUTHORIZATION'                   =  'AUTHORIZATION'
            $'_AVG'                             =  'AVG'
            $'_BEFORE'                          =  'BEFORE'
            $'_BEGIN'                           =  'BEGIN'
            $'_BETWEEN'                         =  'BETWEEN'
            $'_BIGINT'                          =  'BIGINT'
            $'_BIT'                             =  'BIT'
            $'_BLOB'                            =  'BLOB'
            $'_BUFFERPOOL'                      =  'BUFFERPOOL'
            $'_BY'                              =  'BY'
            $'_CALL'                            =  'CALL'
            $'_CALLED'                          =  'CALLED'
            $'_CALLER'                          =  'CALLER'
            $'_CAPTURE'                         =  'CAPTURE'
            $'_CASCADE'                         =  'CASCADE'
            $'_CASCADED'                        =  'CASCADED'
            $'_CASE'                            =  'CASE'
            $'_CAST'                            =  'CAST'
            $'_CHAR'                            =  'CHAR'
            $'_CHARACTER'                       =  'CHARACTER'
            $'_CHECK'                           =  'CHECK'
            $'_CLIENT'                          =  'CLIENT'
            $'_CLOB'                            =  'CLOB'
            $'_CLOSE'                           =  'CLOSE'
            $'_COBOL'                           =  'COBOL'
            $'_COLUMN'                          =  'COLUMN'
            $'_COMMENT'                         =  'COMMENT'
            $'_COMMIT'                          =  'COMMIT'
            $'_CONCAT'                          =  'CONCAT'
            $'_CONNECT'                         =  'CONNECT'
            $'_CONNECTION'                      =  'CONNECTION'
            $'_CONSTRAINT'                      =  'CONSTRAINT'
            $'_CONSTRAINTS'                     =  'CONSTRAINTS'
            $'_CONTAINS'                        =  'CONTAINS'
            $'_CONTINUE'                        =  'CONTINUE'
            $'_COUNT'                           =  'COUNT'
            $'_COUNT_BIG'                       =  'COUNT_BIG'
            $'_CREATE'                          =  'CREATE'
            $'_CURRENT'                         =  'CURRENT'
            $'_CURSOR'                          =  'CURSOR'
            $'_DATA'                            =  'DATA'
            $'_DATABASE'                        =  'DATABASE'
            $'_DATALINK'                        =  'DATALINK'
            $'_DATE'                            =  'DATE'
            $'_DAY'                             =  'DAY'
            $'_DAYS'                            =  'DAYS'
            $'_DB2GENERAL'                      =  'DB2GENERAL'
            $'_DB2SQL'                          =  'DB2SQL'
            $'_DBCLOB'                          =  'DBCLOB'
            $'_DEC'                             =  'DEC'
            $'_DECIMAL'                         =  'DECIMAL'
            $'_DECLARE'                         =  'DECLARE'
            $'_DEFERRED'                        =  'DEFERRED'
            $'_DELETE'                          =  'DELETE'
            $'_DESC'                            =  'DESC'
            $'_DESCRIPTOR'                      =  'DESCRIPTOR'
            $'_DISALLOW'                        =  'DISALLOW'
            $'_DISCONNECT'                      =  'DISCONNECT'
            $'_DISTINCT'                        =  'DISTINCT'
            $'_DOUBLE'                          =  'DOUBLE'
            $'_DROP'                            =  'DROP'
            $'_DYNAMIC'                         =  'DYNAMIC'
            $'_EACH'                            =  'EACH'
            $'_ELSE'                            =  'ELSE'
            $'_END'                             =  'END'
            $'_ESCAPE'                          =  'ESCAPE'
            $'_EXCEPT'                          =  'EXCEPT'
            $'_EXCEPTION'                       =  'EXCEPTION'
            $'_EXCLUSIVE'                       =  'EXCLUSIVE'
            $'_EXECUTE'                         =  'EXECUTE'
            $'_EXISTS'                          =  'EXISTS'
            $'_EXPLAIN'                         =  'EXPLAIN'
            $'_EXTERNAL'                        =  'EXTERNAL'
            $'_FETCH'                           =  'FETCH'
            $'_FILE'                            =  'FILE'
            $'_FIRST'                           =  'FIRST'
            $'_FLOAT'                           =  'FLOAT'
            $'_FOR'                             =  'FOR'
            $'_FOREIGN'                         =  'FOREIGN'
            $'_FOUND'                           =  'FOUND'
            $'_FREE'                            =  'FREE'
            $'_FROM'                            =  'FROM'
            $'_FULL'                            =  'FULL'
            $'_FUNCTION'                        =  'FUNCTION'
            $'_G'                               =  'G'
            $'_GENERATE_UNIQUE'                 =  'GENERATE_UNIQUE'
            $'_GLOBAL'                          =  'GLOBAL'
            $'_GO'                              =  'GO'
            $'_GOTO'                            =  'GOTO'
            $'_GRANT'                           =  'GRANT'
            $'_GRAPHIC'                         =  'GRAPHIC'
            $'_GROUP'                           =  'GROUP'
            $'_GROUPING'                        =  'GROUPING'
            $'_HAVING'                          =  'HAVING'
            $'_HOLD'                            =  'HOLD'
            $'_HOUR'                            =  'HOUR'
            $'_HOURS'                           =  'HOURS'
            $'_IMMEDIATE'                       =  'IMMEDIATE'
            $'_IN'                              =  'IN'
            $'_INDEX'                           =  'INDEX'
            $'_INDICATOR'                       =  'INDICATOR'
            $'_INITIALLY'                       =  'INITIALLY'
            $'_INNER'                           =  'INNER'
            $'_INOUT'                           =  'INOUT'
            $'_INPUT'                           =  'INPUT'
            $'_INSERT'                          =  'INSERT'
            $'_INT'                             =  'INT'
            $'_INTEGER'                         =  'INTEGER'
            $'_INTEGRITY'                       =  'INTEGRITY'
            $'_INTERSECT'                       =  'INTERSECT'
            $'_INTO'                            =  'INTO'
            $'_IS'                              =  'IS'
            $'_JAVA'                            =  'JAVA'
            $'_JOIN'                            =  'JOIN'
            $'_K'                               =  'K'
            $'_KEY'                             =  'KEY'
            $'_LANGUAGE'                        =  'LANGUAGE'
            $'_LEFT'                            =  'LEFT'
            $'_LIKE'                            =  'LIKE'
            $'_LINKTYPE'                        =  'LINKTYPE'
            $'_LOCAL'                           =  'LOCAL'
            $'_LOCATOR'                         =  'LOCATOR'
            $'_LOCK'                            =  'LOCK'
            $'_LONG'                            =  'LONG'
            $'_M'                               =  'M'
            $'_MAX'                             =  'MAX'
            $'_MICROSECOND'                     =  'MICROSECOND'
            $'_MICROSECONDS'                    =  'MICROSECONDS'
            $'_MIN'                             =  'MIN'
            $'_MINUTE'                          =  'MINUTE'
            $'_MINUTES'                         =  'MINUTES'
            $'_MODE'                            =  'MODE'
            $'_MODIFIES'                        =  'MODIFIES'
            $'_NEW'                             =  'NEW'
            $'_NEW_TABLE'                       =  'NEW_TABLE'
            $'_NO'                              =  'NO'
            $'_NOT'                             =  'NOT'
            $'_NULL'                            =  'NULL'
            $'_NUMERIC'                         =  'NUMERIC'
            $'_OF'                              =  'OF'
            $'_OLD'                             =  'OLD'
            $'_OLD_TABLE'                       =  'OLD_TABLE'
            $'_OLE'                             =  'OLE'
            $'_ON'                              =  'ON'
            $'_ONLY'                            =  'ONLY'
            $'_OPEN'                            =  'OPEN'
            $'_OPTIMIZATION'                    =  'OPTIMIZATION'
            $'_OPTIMIZE'                        =  'OPTIMIZE'
            $'_OPTION'                          =  'OPTION'
            $'_OR'                              =  'OR'
            $'_ORDER'                           =  'ORDER'
            $'_OUT'                             =  'OUT'
            $'_OUTER'                           =  'OUTER'
            $'_PACKAGE'                         =  'PACKAGE'
            $'_PARAMETER'                       =  'PARAMETER'
            $'_PATH'                            =  'PATH'
            $'_PLAN'                            =  'PLAN'
            $'_PREPARE'                         =  'PREPARE'
            $'_PRESERVE'                        =  'PRESERVE'
            $'_PRIMARY'                         =  'PRIMARY'
            $'_PRIVILEGES'                      =  'PRIVILEGES'
            $'_PROCEDURE'                       =  'PROCEDURE'
            $'_PROGRAM'                         =  'PROGRAM'
            $'_QUERYNO'                         =  'QUERYNO'
            $'_RAND'                            =  'RAND'
            $'_READ'                            =  'READ'
            $'_READS'                           =  'READS'
            $'_REAL'                            =  'REAL'
            $'_RECOVERY'                        =  'RECOVERY'
            $'_REFERENCES'                      =  'REFERENCES'
            $'_REFERENCING'                     =  'REFERENCING'
            $'_REFRESH'                         =  'REFRESH'
            $'_RELEASE'                         =  'RELEASE'
            $'_RENAME'                          =  'RENAME'
            $'_RESET'                           =  'RESET'
            $'_RESTRICT'                        =  'RESTRICT'
            $'_RESULT'                          =  'RESULT'
            $'_RETURN'                          =  'RETURN'
            $'_RETURNS'                         =  'RETURNS'
            $'_REVOKE'                          =  'REVOKE'
            $'_RIGHT'                           =  'RIGHT'
            $'_ROLLBACK'                        =  'ROLLBACK'
            $'_ROUND'                           =  'ROUND'
            $'_ROW'                             =  'ROW'
            $'_ROWS'                            =  'ROWS'
            $'_RUN'                             =  'RUN'
            $'_SECOND'                          =  'SECOND'
            $'_SECONDS'                         =  'SECONDS'
            $'_SECTION'                         =  'SECTION'
            $'_SELECT'                          =  'SELECT'
            $'_SELECTIVITY'                     =  'SELECTIVITY'
            $'_SET'                             =  'SET'
            $'_SETS'                            =  'SETS'
            $'_SHARE'                           =  'SHARE'
            $'_SIZE'                            =  'SIZE'
            $'_SMALLINT'                        =  'SMALLINT'
            $'_SOME'                            =  'SOME'
            $'_SOURCE'                          =  'SOURCE'
            $'_SPECIFIC'                        =  'SPECIFIC'
            $'_SQL'                             =  'SQL'
            $'_SQLSTATE'                        =  'SQLSTATE'
            $'_STATEMENT'                       =  'STATEMENT'
            $'_STATIC'                          =  'STATIC'
            $'_STYLE'                           =  'STYLE'
            $'_SUM'                             =  'SUM'
            $'_SUMMARY'                         =  'SUMMARY'
            $'_SYNONYM'                         =  'SYNONYM'
            $'_TABLE'                           =  'TABLE'
            $'_TABLESPACE'                      =  'TABLESPACE'
            $'_TEMPORARY'                       =  'TEMPORARY'
            $'_THEN'                            =  'THEN'
            $'_TIME'                            =  'TIME'
            $'_TIMESTAMP'                       =  'TIMESTAMP'
            $'_TO'                              =  'TO'
            $'_TRIGGER'                         =  'TRIGGER'
            $'_UNION'                           =  'UNION'
            $'_UNIQUE'                          =  'UNIQUE'
            $'_UPDATE'                          =  'UPDATE'
            $'_USER'                            =  'USER'
            $'_USING'                           =  'USING'
            $'_VALUES'                          =  'VALUES'
            $'_VARCHAR'                         =  'VARCHAR'
            $'_VARGRAPHIC'                      =  'VARGRAPHIC'
            $'_VARYING'                         =  'VARYING'
            $'_VIEW'                            =  'VIEW'
            $'_WHEN'                            =  'WHEN'
            $'_WHENEVER'                        =  'WHENEVER'
            $'_WHERE'                           =  'WHERE'
            $'_WITH'                            =  'WITH'
            $'_WORK'                            =  'WORK'
            $'_WRITE'                           =  'WRITE'
            $'_YEAR'                            =  'YEAR'
            $'_YEARS'                           =  'YEARS'
            $'_IDENT_'                          =  ANY('@$#_abcdefghijklmnopqrstuvwxyz')
+                                                  (SPAN('@$#_abcdefghijklmnopqrstuvwxyz0123456789') | epsilon)
            explainable_stmt                    =  *delete_stmt
+                                               |  *insert_stmt
+                                               |  *update_stmt
+                                               |  *create_procedure_stmt
+                                               |  *create_trigger_stmt
+                                               |  *create_summary_table_stmt
+                                               |  *create_view_stmt
+                                               |  *values_into_stmt
+                                               |  *values_clause
+                                               |  *select_into_stmt
+                                               |  *select_stmt
+                                               |  *declare_cursor
+                                               |  *declare_global_temporary_table_stmt
            create_procedure_stmt               =  CREATE
+                                                  PROCEDURE
+                                                  *procedure_name
+                                                  $'('
+                                                  !(*create_procedure_argument !%($',' *create_procedure_argument))
+                                                  $')'
+                                                  %( SPECIFIC *specific_name
+                                                  |  !DYNAMIC RESULT SETS $'_INTEGER_'
+                                                  |  EXTERNAL !(NAME (*identifier | $'_SQ_STRING_'))
+                                                  |  MODIFIES SQL DATA
+                                                  |  NO (SQL | DBINFO)
+                                                  |  CONTAINS SQL
+                                                  |  READS SQL DATA
+                                                  |  NOT (DETERMINISTIC | FENCED)
+                                                  |  DETERMINISTIC
+                                                  |  LANGUAGE (C | JAVA | COBOL | SQL | OLE)
+                                                  |  PARAMETER
+                                                     STYLE
+                                                     (  DB2DARI
+                                                     |  DB2GENERAL | DB2GENRL
+                                                     |  (SIMPLE CALL | GENERAL) !(WITH NULLS)
+                                                     |  DB2SQL
+                                                     |  JAVA
+                                                     )
+                                                  |  FENCED
+                                                  |  DBINFO
+                                                  |  NULL CALL
+                                                  |  CALLED ON NULL INPUT
+                                                  |  PROGRAM TYPE (SUB | MAIN)
+                                                  )
            create_procedure_argument           =  !(IN | OUT | INOUT) *parameter_name *data_type
            create_summary_table_stmt           =  CREATE
+                                                  SUMMARY
+                                                  TABLE
+                                                  *table_name
+                                                  AS
+                                                  $'('
+                                                  *summary_fullselect
+                                                  $')'
+                                                  *summary_table_options
+                                                  !%( DATA CAPTURE (NONE | CHANGES)
+                                                  |  IN *tablespace_name *tablespace_options
+                                                  |  PARTITIONING
+                                                     KEY
+                                                     $'('
+                                                     *create_summary_table_partition_key
+                                                     !%($',' *create_summary_table_partition_key)
+                                                     $')'
+                                                     !(USING HASHING)
+                                                  |  REPLICATED
+                                                  |  NOT LOGGED INITIALLY
+                                                  )
            create_summary_table_partition_key  =  *column_name
            create_view_stmt                    =  CREATE
+                                                  !FEDERATED
+                                                  VIEW
+                                                  *view_name
+                                                  !( $'(' *column_name !%($',' *column_name) $')'
+                                                  |  *root_view_definition
+                                                  |  *subview_definition
+                                                  )
+                                                  AS
+                                                  !(WITH *common_table_expression !%($',' *common_table_expression))
+                                                  *fullselect
+                                                  !*order_by_clause
+                                                  !(WITH !(CASCADED | LOCAL) CHECK OPTION)
            declare_cursor                      =  DECLARE
+                                                  *cursor_name
+                                                  CURSOR
+                                                  !(WITH HOLD)
+                                                  !(WITH RETURN !(TO !(CALLER | CLIENT)))
+                                                  FOR
+                                                  (*select_stmt | *identifier)
            declare_global_temporary_table_stmt =  DECLARE
+                                                  GLOBAL
+                                                  TEMPORARY
+                                                  TABLE
+                                                  *table_name
+                                                  (  $'('
+                                                     *declare_global_temporary_table_column
+                                                     !%($',' *declare_global_temporary_table_column)
+                                                     $')'
+                                                  |  LIKE *table_name *copy_options
+                                                  |  AS $'(' *fullselect $')' DEFINITION ONLY *copy_options
+                                                  )
+                                                  !%( WITH REPLACE
+                                                  |  ON COMMIT (DELETE | PRESERVE) ROWS
+                                                  |  NOT LOGGED
+                                                  |  IN *tablespace_name
+                                                  |  PARTITIONING
+                                                     KEY
+                                                     $'('
+                                                     *column_name
+                                                     !%($',' *column_name)
+                                                     $')'
+                                                     !(USING HASHING)
+                                                  )
            declare_global_temporary_table_column = *column_name *data_type *gt_column_options
            delete_stmt                         =  DELETE
+                                                  FROM
+                                                  (*table_or_view_name | ONLY $'(' *table_or_view_name $')')
+                                                  !(!AS *correlation_name)
+                                                  !(WHERE (*search_condition | CURRENT OF *cursor_name))
            insert_stmt                         =  INSERT
+                                                  INTO
+                                                  *table_or_view_name
+                                                  !($'(' *column_name !%($',' *column_name) $')')
+                                                  (  VALUES *insert_stmt_value_list !%($',' *insert_stmt_value_list)
+                                                  |  !( WITH
+                                                        *common_table_expression
+                                                        !%($',' *common_table_expression)
+                                                     )
+                                                     ($'(' *subselect $')' | *subselect)
+                                                     !%(*set_operator fullselect)
+                                                  )
            insert_stmt_value_list              =  $'(' *insert_value !%($',' *insert_value) $')' | *insert_value
            insert_value                        =  *expression | NULL | DEFAULT
            oid_column                          =  REF IS *oid_column_name USER GENERATED !UNCHECKED
            oid_column_definition               =  REF IS *oid_column_name USER GENERATED
            oid_column_name                     =  *identifier
            select_into_stmt                    =  *select_clause
+                                                  *into_clause
+                                                  *from_clause
+                                                  !*where_clause
+                                                  !*group_by_clause
+                                                  !*having_clause
            set_current_query_optimization_stmt =  SET
+                                                  CURRENT
+                                                  QUERY
+                                                  OPTIMIZATION
+                                                  !$'_EQ_'
+                                                  ($'_INTEGER_' | *host_variable)
            set_transition_variable             =  SET
+                                                  (  *transition_variable $'_EQ_' (*expression | NULL | DEFAULT)
+                                                  |  $'('
+                                                     *transition_variable
+                                                     !%($',' *transition_variable)
+                                                     $')'
+                                                     $'_EQ_'
+                                                     $'('
+                                                     (  *set_transition_variable_list
+                                                        !%($',' *set_transition_variable_list)
+                                                     |  *fullselect
+                                                     )
+                                                     $')'
+                                                  )
            set_transition_variable_list        =  *expression | NULL | DEFAULT
            signal_sqlstate_stmt                =  SIGNAL SQLSTATE *string_constant $'(' *diagnostic_string $')'
            update_stmt                         =  UPDATE
+                                                  (*table_or_view_name | ONLY $'(' *table_or_view_name $')')
+                                                  !(!AS *correlation_name)
+                                                  SET
+                                                  *assignment_clause
+                                                  !(WHERE CURRENT OF *cursor_name | WHERE *search_condition)
            into_clause                         =  INTO
+                                                  (*host_variable | *identifier | *parameter_marker)
+                                                  !%($',' (*host_variable | *identifier))
            $'_fullselect'                      =  *values_clause
+                                               |  *subselect !*where_clause !*group_by_clause !*having_clause
+                                               |  $'(' *fullselect $')'
            assignment_clause                   =  *assignment_clause_element !%($',' *assignment_clause_element)
            assignment_clause_element           =  *column_name $'_EQ_' (*expression | NULL | DEFAULT)
+                                               |  $'('
+                                                  *column_name
+                                                  !%($',' *column_name)
+                                                  $')'
+                                                  $'_EQ_'
+                                                  $'('
+                                                  (  *assignment_clause_sub_element
+                                                     !%($',' *assignment_clause_sub_element)
+                                                  |  *fullselect
+                                                  )
+                                                  $')'
            assignment_clause_sub_element       =  *expression | NULL | DEFAULT
            authorization_name                  =  *identifier
            case_expression                     =  CASE
+                                                  (*simple_when_clause | *searched_when_clause)
+                                                  !(ELSE (NULL | *result_expression))
+                                                  END
            cast_function                       =  *identifier !($'.' *identifier)
            cast_specification                  =  CAST
+                                                  $'('
+                                                  (*expression | NULL)
+                                                  AS
+                                                  *data_type
+                                                  !(SCOPE *typed_table_or_view_name)
+                                                  $')'
            check_condition                     =  *search_condition
            check_constraint                    =  *constraint_clause CHECK $'(' *check_condition $')'
            column                              =  *identifier !($'.' *identifier !($'.' *identifier))
            column_default_spec                 =  *default_clause
+                                               |  GENERATED
+                                                  (ALWAYS | BY DEFAULT)
+                                                  AS
+                                                  ($'(' *expression $')' | *identity_clause)
            column_definition                   =  *column_name *data_type !*column_options
            column_name                         =  *dereference_operation
+                                               |  *method_invocation
+                                               |  *two_part_name
+                                               |  $'_SQ_STRING_'
            column_option                       =  NOT NULL
+                                               |  *lob_options
+                                               |  *datalink_options
+                                               |  SCOPE *typed_table_or_view_name
+                                               |  *constraint_clause
+                                                  (  PRIMARY KEY
+                                                  |  UNIQUE
+                                                  |  REFERENCES
+                                                     *table_name
+                                                     !($'(' *column_name !%($',' *column_name) $')')
+                                                     *rule_clause
+                                                  |  CHECK $'(' *check_condition $')'
+                                                  )
+                                               |  *column_default_spec
+                                               |  INLINE LENGTH $'_INTEGER_'
            column_options                      =  *column_option !%(*column_option | *forbitdata)
            column_start                        =  $'_INTEGER_'
            common_table_expression             =  *table_name
+                                                  !($'(' *column_name !%($',' *column_name) $')')
+                                                  AS
+                                                  $'('
+                                                  *fullselect
+                                                  $')'
            comparison_string                   =  $'_SQ_STRING_'
            constant                            =  $'_SQ_STRING_' | !($'+' | $'-') ($'_INTEGER_' | *real)
            numeric_constant                    =  !($'+' | $'-') ($'_INTEGER_' | *real)
            constraint_clause                   =  !(CONSTRAINT *constraint_name)
            constraint_name                     =  *identifier
            copy_options                        =  !%( (INCLUDING | EXCLUDING) !COLUMN DEFAULTS
+                                                  |  EXCLUDING IDENTITY !(COLUMN ATTRIBUTES)
+                                                  |  INCLUDING IDENTITY !(COLUMN ATTRIBUTES)
+                                                  )
            correlation_clause                  =  !AS
+                                                  *correlation_name
+                                                  !($'(' *column_name !%($',' *column_name) $')')
            correlation_name                    =  *identifier
            cursor_name                         =  *identifier
            data_filter                         =  FILTER USING (*function | *case_expression)
            data_type                           =  *data_type_basic
+                                               |  SYSIBM $'.' *data_type_basic
+                                               |  *distinct_type_name | REF $'(' *type_name $')'
            data_type_basic                     =  SMALLINT
+                                               |  INTEGER
+                                               |  INT
+                                               |  BIGINT
+                                               |  FLOAT !($'(' $'_INTEGER_' $')') | REAL
+                                               |  DOUBLE !PRECISION
+                                               |  (DECIMAL | DEC | NUMERIC | NUM)
+                                                  !($'(' $'_INTEGER_' !($',' $'_INTEGER_') $')')
+                                               |  (  (CHARACTER | CHAR) !($'(' $'_INTEGER_' $')')
+                                                  |  (VARCHAR | (CHARACTER | CHAR) VARYING) $'(' $'_INTEGER_' $')'
+                                                  |  LONG VARCHAR
+                                                  )
+                                                  !(FOR BIT DATA)
+                                               |  GRAPHIC !($'(' $'_INTEGER_' $')')
+                                               |  VARGRAPHIC $'(' $'_INTEGER_' $')'
+                                               |  LONG VARGRAPHIC
+                                               |  DATE
+                                               |  TIME
+                                               |  TIMESTAMP
+                                               |  (BLOB | CLOB | DBCLOB) $'(' *integer_kmg $')'
+                                               |  DATALINK !($'(' $'_INTEGER_' $')')
            datalink_options                    =  LINKTYPE
+                                                  URL
+                                                  !( NO LINK IDDL_CONTROL
+                                                  |  FILE LINK IDDL_CONTROL (*file_link_options | MODE DB2OPTIONS)
+                                                  )
            datetime_special_register           =  CURRENT (DATE | TIME | TIMESTAMP)
            default_clause                      =  !WITH DEFAULT !*default_values_clause
            default_value_clause                =  *constant | *datetime_special_register | USER
            default_values_clause               =  *constant
+                                               |  *datetime_special_register
+                                               |  USER
+                                               |  NULL
+                                               |  *cast_function $'(' *default_value_clause $')'
            dereference_operation               =  *identifier $'_DEREF_' *identifier
            diagnostic_string                   =  *expression
            distinct_type_name                  =  *two_part_name
            factor                              =  *element | $'+' *factor | $'-' *factor
            element                             =  *unsigned_constant *opt_labeled_duration
+                                               |  *dereference_operation
+                                               |  *method_invocation
+                                               |  *function *opt_labeled_duration | *column *opt_labeled_duration
+                                               |  $'(' *fullselect $')' *opt_labeled_duration
+                                               |  *special_register
+                                               |  *case_expression
+                                               |  *cast_specification
+                                               |  *subtype_treatment
+                                               |  *host_variable
+                                               |  *parameter_marker
            method_invocation                   =  *identifier %($'.' $'.' *identifier) !($'(' !*expression_list $')')
            subtype_treatment                   =  TREAT $'(' *expression AS *data_type $')'
            opt_labeled_duration                =  !*labeled_duration
            element_list                        =  $'(' *element_list_element !%($',' *element_list_element) $')'
            element_list_element                =  *column_definition
+                                               |  *unique_constraint
+                                               |  *referential_constraint
+                                               |  *check_constraint
            exploitation_rule                   =  WHEN
+                                                  KEY
+                                                  $'('
+                                                  *parameter_name
+                                                  $')'
+                                                  USE
+                                                  *method_name
+                                                  $'('
+                                                  *parameter_name
+                                                  !%($',' *parameter_name)
+                                                  $')'
            expression                          =  ($'(' *expression $')' | *term) !%($'+' *term | $'-' *term)
            expression_or_expression_list       =  $'(' *expression_list $')' | *expression
            expression_list                     =  *expression !%($',' *expression)
            expression_name                     =  *identifier
            fetch_first_clause                  =  FETCH FIRST !$'_INTEGER_' (ROW | ROWS) ONLY
            file_link_options                   =  %( INTEGRITY ALL
+                                                  |  READ PERMISSION (FS | DB)
+                                                  |  WRITE PERMISSION (FS | BLOCKED)
+                                                  |  RECOVERY (NO | YES)
+                                                  |  ON UNLINK (RESTORE | DELETE)
+                                                  )
            forbitdata                          =  FOR BIT DATA
            from_clause                         =  FROM *table_reference !%($',' *table_reference)
            fullselect                          =  fullselect !%(*set_operator fullselect)
            function                            =  AVG $'(' *opt_all_distinct *expression $')'
+                                               |  COUNT $'(' ($'*' $')' | *opt_all_distinct *expression $')')
+                                               |  COUNT_BIG $'(' ($'*' $')' | *opt_all_distinct *expression $')')
+                                               |  GENERATE_UNIQUE $'(' $')'
+                                               |  GROUPING $'(' *expression $')'
+                                               |  MAX $'(' *opt_all_distinct *expression $')'
+                                               |  MIN $'(' *opt_all_distinct *expression $')'
+                                               |  STDDEV $'(' *opt_all_distinct *expression $')'
+                                               |  SUM $'(' *opt_all_distinct *expression $')'
+                                               |  VARIANCE $'(' *opt_all_distinct *expression $')'
+                                               |  *function_name $'(' *function_expression_list $')'
+                                               |  BLOB $'(' *function_expression_list $')'
+                                               |  BIGINT $'(' *function_expression_list $')'
+                                               |  CHAR $'(' *function_expression_list $')'
+                                               |  CONCAT $'(' *function_expression_list $')'
+                                               |  DATE $'(' *function_expression_list $')'
+                                               |  DAY $'(' *function_expression_list $')'
+                                               |  DAYS $'(' *function_expression_list $')'
+                                               |  DECIMAL $'(' *opt_all_distinct *function_expression_list $')'
+                                               |  DOUBLE $'(' *function_expression_list $')'
+                                               |  FLOAT $'(' *function_expression_list $')'
+                                               |  GRAPHIC $'(' *function_expression_list $')'
+                                               |  HOUR $'(' *function_expression_list $')'
+                                               |  INSERT $'(' *function_expression_list $')'
+                                               |  INTEGER $'(' *function_expression_list $')'
+                                               |  LEFT $'(' *function_expression_list $')'
+                                               |  MICROSECOND $'(' *function_expression_list $')'
+                                               |  MINUTE $'(' *function_expression_list $')'
+                                               |  MONTH $'(' !*function_expression_list $')'
+                                               |  RAND $'(' !*function_expression_list $')'
+                                               |  REAL $'(' *function_expression_list $')'
+                                               |  REPLACE $'(' *function_expression_list $')'
+                                               |  ROUND $'(' *function_expression_list $')'
+                                               |  RIGHT $'(' *function_expression_list $')'
+                                               |  SECOND $'(' *function_expression_list $')'
+                                               |  SMALLINT $'(' *function_expression_list $')'
+                                               |  TIME $'(' *function_expression_list $')'
+                                               |  TIMESTAMP $'(' *function_expression_list $')'
+                                               |  YEAR $'(' *function_expression_list $')'
            opt_all_distinct                    =  !(ALL | DISTINCT)
            function_expression_list            =  *expression_list
            function_mapping_name               =  *identifier
            function_name                       =  *two_part_name
            function_option_name                =  *identifier
            function_options                    =  OPTIONS
+                                                  $'('
+                                                  *function_options_value
+                                                  !%($',' *function_options_value)
+                                                  $')'
            function_options_value              =  !ADD *function_option_name *string_constant
            function_specification              =  FUNCTION
+                                                  *function_name
+                                                  !($'(' !(*data_type !%($',' *data_type)) $')')
+                                               |  SPECIFIC FUNCTION *specific_name
            grand_total                         =  $'(' $')'
            group_by_clause                     =  GROUP BY *group_by_element !%($',' *group_by_element)
            group_by_element                    =  *expression | *grouping_sets | *super_groups
            group_name                          =  *identifier
            grouping_expression_list            =  *expression_or_expression_list
+                                                  !%($',' *expression_or_expression_list)
            grouping_sets                       =  GROUPING
+                                                  SETS
+                                                  $'('
+                                                  *grouping_set_element
+                                                  !%($',' *grouping_set_element)
+                                                  $')'
            grouping_set_element                =  *super_groups
+                                               |  *expression
+                                               |  $'('
+                                                  *grouping_set_list_element
+                                                  !%($',' *grouping_set_list_element)
+                                                  $')'
            grouping_set_list_element           =  *expression | *super_groups
            gt_column_options                   =  !%( NOT NULL
+                                                  |  *default_clause
+                                                  |  GENERATED (ALWAYS | BY DEFAULT) AS *identity_clause
+                                                  )
            having_clause                       =  HAVING *search_condition
            host_variable                       =  $':' *identifier !*indicator_variable
            indicator_variable                  =  !INDICATOR $':' *identifier
            identity_clause                     =  IDENTITY
+                                                  !( $'('
+                                                     *identity_clause_element
+                                                     !%($',' *identity_clause_element)
+                                                     $')'
+                                                  )
            identity_clause_element             =  START WITH !$'-' $'_INTEGER_'
+                                               |  INCREMENT BY !$'-' $'_INTEGER_'
+                                               |  NO CACHE
+                                               |  CACHE $'_INTEGER_'
            index_exploitation                  =  SEARCH
+                                                  BY
+                                                  !EXACT
+                                                  INDEX
+                                                  EXTENSION
+                                                  *index_extension_name
+                                                  %*exploitation_rule
            index_extension_name                =  *two_part_name
            index_name                          =  *two_part_name
            integer_kmg                         =  $'_INTEGER_' !(K | M | G)
            join_condition                      =  *search_condition
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
            lob_options                         =  %(LOGGED | NOT (LOGGED | COMPACT) | COMPACT)
            method_name                         =  *two_part_name
            method_signature                    =  *method_name
+                                                  $'('
+                                                  *method_signature_parameter
+                                                  !%($',' *method_signature_parameter)
+                                                  $')'
+                                                  !( RETURNS
+                                                     *data_type
+                                                     !(AS LOCATOR | CAST FROM *data_type !(AS LOCATOR))
+                                                  )
            method_signature_parameter          =  !*parameter_name *data_type !(AS LOCATOR)
            optimize_for_clause                 =  OPTIMIZE FOR $'_INTEGER_' (ROWS | ROW)
            order_by_clause                     =  ORDER BY *order_by_clause_element !%($',' *order_by_clause_element)
            order_by_clause_element             =  *sort_key !(ASC | DESC)
            parameter_name                      =  *identifier
            parameter_marker                    =  $'?'
            predicate                           =  *expression
+                                                  (  (  $'_EQ_'
+                                                     |  $'_NEQ_2_'
+                                                     |  $'_NEQ_3_'
+                                                     |  $'_NEQ_1_'
+                                                     |  $'_LT_'
+                                                     |  $'_GT_'
+                                                     |  $'_LEQ_'
+                                                     |  $'_GEQ_'
+                                                     )
+                                                     *expression
+                                                  |  (  $'_EQ_'
+                                                     |  $'_NEQ_2_'
+                                                     |  $'_NEQ_3_'
+                                                     |  $'_NEQ_1_'
+                                                     |  $'_LT_'
+                                                     |  $'_GT_'
+                                                     |  $'_LEQ_'
+                                                     |  $'_GEQ_'
+                                                     )
+                                                     (SOME | ANY | ALL)
+                                                     $'('
+                                                     *fullselect
+                                                     $')'
+                                                  |  NOT
+                                                     (  BETWEEN *expression AND *expression
+                                                     |  IN *expression_or_expression_list
+                                                     )
+                                                  |  BETWEEN *expression AND *expression
+                                                  |  IN *expression_or_expression_list
+                                                  |  IS !NOT NULL
+                                                  |  !IS OF DYNAMIC TYPE $'(' *type_predicate $')'
+                                                  |  (LIKE *expression | NOT LIKE *expression) !(ESCAPE *expression)
+                                                  )
+                                               |  $'('
+                                                  *expression_list
+                                                  $')'
+                                                  (  $'_EQ_'
+                                                     ((SOME | ANY) $'(' *fullselect $')' | $'(' *expression_list $')')
+                                                  |  IN $'(' *fullselect $')'
+                                                  |  NOT IN $'(' *fullselect $')'
+                                                  )
+                                               |  NOT EXISTS $'(' *fullselect $')'
+                                               |  EXISTS $'(' *fullselect $')'
            type_predicate                      =  *type_predicate_element !%($',' *type_predicate_element)
            type_predicate_element              =  !ONLY *type_name
            predicate_specification             =  WHEN
+                                                  ($'_EQ_' | $'_NEQ_1_' | $'_LT_' | $'_GT_' | $'_LEQ_' | $'_GEQ_')
+                                                  (*constant | EXPRESSION AS *expression_name)
+                                                  (  *data_filter !*index_exploitation
+                                                  |  *index_exploitation !*data_filter
+                                                  )
            procedure_name                      =  *two_part_name
            read_only_clause                    =  FOR (READ | FETCH) ONLY
            real                                =  $'_REAL_' | $'_REAL_1_'
            referential_constraint              =  *constraint_clause
+                                                  FOREIGN
+                                                  KEY
+                                                  $'('
+                                                  *column_name
+                                                  !%($',' *column_name)
+                                                  $')'
+                                                  REFERENCES
+                                                  *table_name
+                                                  !($'(' *column_name !%($',' *column_name) $')')
+                                                  *rule_clause
            rehashable_table_options            =  DATA
+                                                  INITIALLY
+                                                  DEFERRED
+                                                  REFRESH
+                                                  (DEFERRED | IMMEDIATE)
+                                                  !(ENABLE QUERY OPTIMIZATION | DISABLE QUERY OPTIMIZATION)
            result_expression                   =  *expression
            root_view_definition                =  MODE DB2SQL $'(' *oid_column !($',' *view_with_options) $')'
            rule_clause                         =  !%( ON
+                                                     (  DELETE (NO ACTION | RESTRICT | CASCADE | SET NULL)
+                                                     |  UPDATE (NO ACTION | RESTRICT)
+                                                     )
+                                                  )
            search_condition                    =  (  NOT *search_condition
+                                                  |  *predicate !(SELECTIVITY *numeric_constant)
+                                                  |  $'(' *search_condition $')'
+                                                  )
+                                                  !%((AND | OR) *search_condition)
            search_condition_paren              =  *search_condition | $'(' *search_condition_paren $')'
            searched_when_clause                =  %(WHEN *search_condition_paren THEN (*result_expression | NULL))
            select_clause                       =  SELECT
+                                                  !(ALL | DISTINCT)
+                                                  *columnDefinition
+                                                  !%($',' *columnDefinition)
            columnDefinition                    =  $'*' | *identifier $'.' $'*' | *expression !*correlation_clause
            select_stmt                         =  (  WITH
+                                                     *common_table_expression
+                                                     !%($',' *common_table_expression)
+                                                     *fullselect
+                                                  |  *fullselect
+                                                  )
+                                                  !*order_by_clause
+                                                  !*fetch_first_clause
+                                                  !%(*read_only_clause | *update_clause | *optimize_for_clause)
            set_operator                        =  UNION !ALL | EXCEPT !ALL | INTERSECT !ALL
            simple_when_clause                  =  *expression %(WHEN *expression THEN (*result_expression | NULL))
            sort_key                            =  *sort_key_expression
            sort_key_expression                 =  *expression
            special_register                    =  CURRENT
+                                                  (  DATE
+                                                  |  DEGREE
+                                                  |  EXPLAIN (MODE | SNAPSHOT)
+                                                  |  FUNCTION PATH
+                                                  |  NODE
+                                                  |  PATH
+                                                  |  QUERY OPTIMIZATION
+                                                  |  REFRESH AGE
+                                                  |  SCHEMA
+                                                  |  SERVER
+                                                  |  TIME
+                                                  |  TIMESTAMP
+                                                  |  TIMEZONE
+                                                  |  *identifier
+                                                  )
+                                               |  USER
            specific_name                       =  *two_part_name
            string_constant                     =  $'_SQ_STRING_'
            subselect                           =  *select_clause *from_clause
+                                                  !*where_clause
+                                                  !*group_by_clause
+                                                  !*having_clause
            subview_definition                  =  MODE
+                                                  DB2SQL
+                                                  *view_under_clause
+                                                  !($'(' *view_with_options $')')
+                                                  !EXTEND
            summary_fullselect                  =  *fullselect
            summary_table_definition            =  $'(' *fullselect $')' *rehashable_table_options
            summary_table_options               =  DEFINITION ONLY *copy_options
+                                               |  DATA
+                                                  INITIALLY
+                                                  DEFERRED
+                                                  REFRESH
+                                                  (DEFERRED | IMMEDIATE)
+                                                  !(ENABLE QUERY OPTIMIZATION | DISABLE QUERY OPTIMIZATION)
            super_groups                        =  ROLLUP $'(' *grouping_expression_list $')'
+                                               |  CUBE $'(' *grouping_expression_list $')'
+                                               |  *grand_total
            supertable_name                     =  *identifier
            superview_name                      =  *identifier
            table_name                          =  *two_part_name
            table_or_view_name                  =  *two_part_name
            table_reference                     =  (  $'(' *table_reference $')'
+                                                  |  *table_reference_type_one
+                                                  |  *table_reference_type_two
+                                                  |  *table_reference_type_three
+                                                  )
+                                                  !%(
+                                                     $'(' *table_reference $')'
+                                                  |  !(INNER | *outer) JOIN *table_reference ON *join_condition
+                                                  )
            outer                               =  (LEFT | RIGHT | FULL) !OUTER
            table_reference_type_one            =  (*table_or_view_name | (ONLY | OUTER) $'(' *table_or_view_name $')')
+                                                  !*correlation_clause
            table_reference_type_two            =  TABLE
+                                                  $'('
+                                                  *function_name
+                                                  $'('
+                                                  !*function_expression_list
+                                                  $')'
+                                                  $')'
+                                                  *correlation_clause
            table_reference_type_three          =  !TABLE $'(' *fullselect $')' *correlation_clause
            nj_table_reference                  =  *table_reference_type_one
+                                               |  *table_reference_type_two
+                                               |  *table_reference_type_three
            tablespace_name                     =  *identifier
            tablespace_options                  =  !(INDEX IN *tablespace_name) !(LONG IN *tablespace_name)
            term                                =  *factor
+                                                  !%(
+                                                     $'*' *factor
+                                                  |  $'/' *factor
+                                                  |  $'_CONCAT_' *factor
+                                                  |  CONCAT *factor
+                                                  )
            transition_variable                 =  *two_part_name
            create_trigger_stmt                 =  CREATE
+                                                  TRIGGER
+                                                  *trigger_name
+                                                  (NO CASCADE BEFORE | AFTER)
+                                                  (  INSERT
+                                                  |  DELETE
+                                                  |  UPDATE !(OF *columnDefinition !%($',' *columnDefinition))
+                                                  )
+                                                  ON
+                                                  *table_name
+                                                  !( REFERENCING
+                                                     !%(
+                                                        OLD !AS *correlation_name
+                                                     |  NEW !AS *correlation_name
+                                                     |  OLD_TABLE !AS *identifier
+                                                     |  NEW_TABLE !AS *identifier
+                                                     )
+                                                  )
+                                                  FOR
+                                                  EACH
+                                                  (ROW | STATEMENT)
+                                                  MODE
+                                                  DB2SQL
+                                                  *triggered_action
            trigger_name                        =  *two_part_name
            triggered_SQL_stmt                  =  *fullselect
+                                               |  *set_transition_variable
+                                               |  *signal_sqlstate_stmt
+                                               |  *insert_stmt
+                                               |  *update_stmt
+                                               |  *delete_stmt
            triggered_action                    =  !(WHEN $'(' *search_condition $')')
+                                                  (  *triggered_SQL_stmt
+                                                  |  BEGIN ATOMIC %(*triggered_SQL_stmt *SEMICOLON) END
+                                                  )
            two_part_name                       =  *identifier !($'.' *identifier)
            type_name                           =  *two_part_name
            typed_element_list                  =  $'('
+                                                  *typed_element_list_element
+                                                  !%($',' *typed_element_list_element)
+                                                  $')'
            typed_element_list_element          =  *oid_column_definition
+                                               |  *with_options
+                                               |  *unique_constraint
+                                               |  *referential_constraint
+                                               |  *check_constraint
            typed_table_or_view_name            =  *identifier
            under_clause                        =  UNDER *supertable_name INHERIT SELECT PRIVILEGES
            unique_constraint                   =  *constraint_clause
+                                                  (UNIQUE | PRIMARY KEY)
+                                                  $'('
+                                                  *column_name
+                                                  !%($',' *column_name)
+                                                  $')'
            unsigned_constant                   =  $'_SQ_STRING_' | $'_INTEGER_' | *real
            update_clause                       =  FOR UPDATE !(OF *column_name !%($',' *column_name))
            values_into_stmt                    =  VALUES *expression_or_expression_list *into_clause
            values_clause                       =  VALUES *values_row !%($',' *values_row)
            values_row                          =  $'(' *values_row_list_element !%($',' *values_row_list_element) $')'
+                                               |  *values_row_list_element
            values_row_list_element             =  *expression | NULL
            view_name                           =  *two_part_name
            view_under_clause                   =  UNDER *superview_name INHERIT SELECT PRIVILEGES
            view_with_options                   =  *column_name
+                                                  WITH
+                                                  OPTIONS
+                                                  *view_with_options_value
+                                                  !%($',' *view_with_options_value)
            view_with_options_value             =  SCOPE *typed_table_or_view_name | READ ONLY
            where_clause                        =  WHERE *search_condition_paren
            with_options                        =  *column_name WITH OPTIONS *column_options
            sql_function                        =  (  RETURNS
+                                                     (  *data_type
+                                                     |  (ROW | TABLE)
+                                                        $'('
+                                                        *sql_function_parameter
+                                                        !%($',' *sql_function_parameter)
+                                                        $')'
+                                                     )
+                                                  |  SPECIFIC *specific_name
+                                                  |  LANGUAGE SQL
+                                                  |  READS SQL DATA
+                                                  |  CONTAINS SQL
+                                                  |  NOT (DETERMINISTIC | VARIANT)
+                                                  |  VARIANT
+                                                  |  DETERMINISTIC
+                                                  |  NO EXTERNAL ACTION
+                                                  |  EXTERNAL ACTION
+                                                  |  STATIC DISPATCH
+                                                  |  CALLED ON NULL INPUT
+                                                  |  NULL CALL
+                                                  )
+                                                  !(PREDICATES $'(' *predicate_specification $')')
+                                                  RETURN
+                                                  (  *expression
+                                                  |  NULL
+                                                  |  !(WITH *expression !%($',' *expression)) *fullselect
+                                                  )
            sql_function_parameter              =  *column_name *data_type
            identifier                          =  $'_IDENT_' | $'_DQ_STRING_'
