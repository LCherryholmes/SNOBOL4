*-------------------------------------------------------------------------------------------------------------------------
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserDefs()')                                                             :(UserDefsEnd)
UserDefs    u                 =     0
            usr               =     ARRAY('1:32')
            doDebug           =     0
            doDebugAfter1st   =     FALSE
            doInclWhite       =     TRUE
            doInclNL          =     TRUE
            doReportFileName  =     FALSE
            doRemember        =     TRUE
            fndExt            =     '' . extc
            fndCmd            =     'd:/mksnt/find d:/bom -name "*.sql" -print'
*           fndSpecific       =     'udb0934.sql'
            fndExclude        =
            keyint            =     ('?') . tx

            blanks            =     SPAN(' ' tab cr ff)
            white             =     SPAN(' ' tab nl cr ff)
            cStyleComment     =     '/*' BREAKX('*') '*/'
            sqlStyleComment   =     '--' BREAK(nl) nl
            space             =     (blanks | cStyleComment | sqlStyleComment) FENCE(*space | epsilon)
            whitespace        =     (white | cStyleComment | sqlStyleComment)  FENCE(*whitespace | epsilon)
            $' '              =     FENCE(whitespace | epsilon)
            $'  '             =     FENCE(space | epsilon)

            keywords          =
+           'ACTION ADD AFTER AGE ALL ALWAYS AND ANY AS ASC ATOMIC ATTRIBUTES AVG BEFORE BEGIN BETWEEN '
+           'BIGINT BIT BLOB BLOCKED BY C CACHE CALL CALLED CALLER CAPTURE CASCADE CASCADED CASE '
+           'CHANGES CHAR CHARACTER CHECK CLIENT CLOB COBOL COLUMN COMMIT COMPACT CONCAT CONSTRAINT '
+           'CONTAINS COUNT COUNT_BIG CREATE CUBE CURRENT CURSOR DATA DATALINK DATE DAY DAYS DB '
+           'DB2DARI DB2GENERAL DB2GENRL DB2OPTIONS DB2SQL DBCLOB '
+           'DBINFO DEC DECIMAL DECLARE DEFAULT DEFAULTS DEFERRED DEFINITION DEGREE DELETE DESC '
+           'DETERMINISTIC DISABLE DISPATCH DISTINCT DOUBLE DYNAMIC EACH ELSE ENABLE END ESCAPE EXACT '
+           'EXCEPT EXCLUDING EXISTS EXPLAIN EXPRESSION EXTEND EXTENSION EXTERNAL FEDERATED FENCED '
+           'FETCH FILE FILTER FIRST FLOAT FOR FOREIGN FS FULL FUNCTION G GENERAL GENERATED '
+           'GENERATE_UNIQUE GLOBAL GRAPHIC GROUP GROUPING HASHING HAVING HOLD HOUR HOURS IDDL_CONTROL '
+           'IDENTITY IMMEDIATE IN INCLUDING INCREMENT INDEX INDICATOR INHERIT INITIALLY INLINE INNER '
+           'INOUT INPUT INSERT INT INTEGER INTEGRITY INTERSECT INTO IS JAVA JOIN K KEY LANGUAGE LEFT '
+           'LENGTH LIKE LINK LINKTYPE LOCAL LOCATOR LOGGED LONG M MAIN MAX MICROSECOND MICROSECONDS '
+           'MIN MINUTE MINUTES MODE MODIFIES MONTH MONTHS NAME NEW NEW_TABLE NO NODE NONE NOT NULL NULLS '
+           'NUM NUMERIC OF OLD OLD_TABLE OLE ON ONLY OPTIMIZATION OPTIMIZE OPTION OPTIONS OR ORDER OUT '
+           'OUTER PARAMETER PARTITIONING PATH PERMISSION PRECISION PREDICATES PRESERVE PRIMARY PRIVILEGES '
+           'PROCEDURE PROGRAM QUERY RAND READ READS REAL RECOVERY REF REFERENCES REFERENCING REFRESH '
+           'REPLACE REPLICATED RESTORE RESTRICT RESULT RETURN RETURNS RIGHT ROLLUP ROUND ROW ROWS SCHEMA '
+           'SCOPE SEARCH SECOND SECONDS SELECT SELECTIVITY SERVER SET SETS SIGNAL SIMPLE SMALLINT SNAPSHOT '
+           'SOME SPECIFIC SQL SQLSTATE START STATEMENT STATIC STDDEV STYLE SUB SUM SUMMARY SYSIBM TABLE '
+           'TEMPORARY THEN TIME TIMESTAMP TIMEZONE TO TREAT TRIGGER TYPE UNCHECKED UNDER UNION UNIQUE '
+           'UNLINK UPDATE URL USE USER USING VALUES VARCHAR VARGRAPHIC VARIANCE VARIANT VARYING VIEW WHEN '
+           'WITH WRITE YEAR YEARS YES'
            reswords          =     'CAST FROM WHERE'
            special           =     '} { ) ( ;'
            operators         =     '!= * , - + -> . / : < <= <> = > >= ? ^= ||'
            ident             =     ANY('@$#_' &UCASE &LCASE) FENCE(SPAN('@$#_' &UCASE &LCASE '0123456789') | epsilon)
            identifier        =     ident $ tx $ *notmatch(reswords, (POS(0) | ' ') upr(tx) (' ' | RPOS(0)))
            resword           =     ident $ tx $ *match(reswords, (POS(0) | ' ') upr(tx) (' ' | RPOS(0)))
            keyword           =     ident $ tx $ *match(keywords, (POS(0) | ' ') upr(tx) (' ' | RPOS(0)))

            Populate(.TW, ident, keywords, reswords, special, operators)

            $'_INTEGER_'                        =  $' ' SPAN('0123456789')
            $'_REAL_'                           =  $' '
+                                                  SPAN('0123456789')
+                                                  FENCE('.' (SPAN('0123456789') | epsilon) | epsilon)
+                                                  FENCE(ANY('Ee') !(ANY('+-')) SPAN('0123456789') | epsilon)
            $'_REAL_1_'                         =  $' '
+                                                  FENCE(SPAN('0123456789') | epsilon)
+                                                  '.'
+                                                  SPAN('0123456789')
+                                                  FENCE(ANY('Ee') !(ANY('+-')) SPAN('0123456789') | epsilon)
            $'_DQ_STRING_'                      =  $' ' '"' !%NOTANY('"') '"'
            $'_SQ_STRING_'                      =  $' ' "'" !%("'" "'" | NOTANY("'")) "'"
            sql_identifier                      =  $' ' (*identifier | $'_DQ_STRING_')

            stmts                               =  ARBNO(*explainable_stmt $';') $' ' RPOS(0)
            explainable_stmt                    =
+                                               (  *delete_stmt
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
+                                               )
            create_procedure_stmt               =  CREATE
+                                                  PROCEDURE
+                                                  *procedure_name
+                                                  $'('
+                                                  !(*create_procedure_argument !%($',' *create_procedure_argument))
+                                                  $')'
+                                                  %( SPECIFIC *specific_name
+                                                  |  !DYNAMIC RESULT SETS $'_INTEGER_'
+                                                  |  EXTERNAL !(NAME (*sql_identifier | $'_SQ_STRING_'))
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
+                                                  (*select_stmt | *sql_identifier)
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
+                                                     !%(*set_operator *$'_fullselect')
+                                                  )
            insert_stmt_value_list              =  $'(' *insert_value !%($',' *insert_value) $')' | *insert_value
            insert_value                        =  *expression | NULL | DEFAULT
            oid_column                          =  REF IS *oid_column_name USER GENERATED !UNCHECKED
            oid_column_definition               =  REF IS *oid_column_name USER GENERATED
            oid_column_name                     =  *sql_identifier
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
+                                                  !$'='
+                                                  ($'_INTEGER_' | *host_variable)
            set_transition_variable             =  SET
+                                                  (  *transition_variable $'=' (*expression | NULL | DEFAULT)
+                                                  |  $'('
+                                                     *transition_variable
+                                                     !%($',' *transition_variable)
+                                                     $')'
+                                                     $'='
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
+                                                  (*host_variable | *sql_identifier | *parameter_marker)
+                                                  !%($',' (*host_variable | *sql_identifier))
            $'_fullselect'                      =  *values_clause
+                                               |  *subselect !*where_clause !*group_by_clause !*having_clause
+                                               |  $'(' *fullselect $')'
            assignment_clause                   =  *assignment_clause_element !%($',' *assignment_clause_element)
            assignment_clause_element           =  *column_name $'=' (*expression | NULL | DEFAULT)
+                                               |  $'('
+                                                  *column_name
+                                                  !%($',' *column_name)
+                                                  $')'
+                                                  $'='
+                                                  $'('
+                                                  (  *assignment_clause_sub_element
+                                                     !%($',' *assignment_clause_sub_element)
+                                                  |  *fullselect
+                                                  )
+                                                  $')'
            assignment_clause_sub_element       =  *expression | NULL | DEFAULT
            authorization_name                  =  *sql_identifier
            case_expression                     =  CASE
+                                                  (*simple_when_clause | *searched_when_clause)
+                                                  !(ELSE (NULL | *result_expression))
+                                                  END
            cast_function                       =  *sql_identifier !($'.' *sql_identifier)
            cast_specification                  =  CAST
+                                                  $'('
+                                                  (*expression | NULL)
+                                                  AS
+                                                  *data_type
+                                                  !(SCOPE *typed_table_or_view_name)
+                                                  $')'
            check_condition                     =  *search_condition
            check_constraint                    =  *constraint_clause CHECK $'(' *check_condition $')'
            column                              =  *sql_identifier !($'.' *sql_identifier !($'.' *sql_identifier))
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
            constant                            =  $'_SQ_STRING_' | !($'+' | $'-') ($'_REAL_' | $'_REAL_1_' | $'_INTEGER_')
            numeric_constant                    =  !($'+' | $'-') ($'_REAL_' | $'_REAL_1_' | $'_INTEGER_')
            constraint_clause                   =  !(CONSTRAINT *constraint_name)
            constraint_name                     =  *sql_identifier
            copy_options                        =  !%( (INCLUDING | EXCLUDING) !COLUMN DEFAULTS
+                                                  |  EXCLUDING IDENTITY !(COLUMN ATTRIBUTES)
+                                                  |  INCLUDING IDENTITY !(COLUMN ATTRIBUTES)
+                                                  )
            correlation_clause                  =  !AS
+                                                  *correlation_name
+                                                  !($'(' *column_name !%($',' *column_name) $')')
            correlation_name                    =  *sql_identifier
            cursor_name                         =  *sql_identifier
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
            dereference_operation               =  *sql_identifier $'->' *sql_identifier
            diagnostic_string                   =  *expression
            distinct_type_name                  =  *two_part_name
            factor                              =  *element | $'+' *factor | $'-' *factor
            element                             =  *unsigned_constant *opt_labeled_duration
+                                               |  *dereference_operation
+                                               |  *method_invocation
+                                               |  *function *opt_labeled_duration
+                                               |  *column *opt_labeled_duration
+                                               |  $'(' *fullselect $')' *opt_labeled_duration
+                                               |  *special_register
+                                               |  *case_expression
+                                               |  *cast_specification
+                                               |  *subtype_treatment
+                                               |  *host_variable
+                                               |  *parameter_marker
            method_invocation                   =  *sql_identifier %($'.' $'.' *sql_identifier) !($'(' !*expression_list $')')
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
            expression_name                     =  *sql_identifier
            fetch_first_clause                  =  FETCH FIRST !$'_INTEGER_' (ROW | ROWS) ONLY
            file_link_options                   =  %( INTEGRITY ALL
+                                                  |  READ PERMISSION (FS | DB)
+                                                  |  WRITE PERMISSION (FS | BLOCKED)
+                                                  |  RECOVERY (NO | YES)
+                                                  |  ON UNLINK (RESTORE | DELETE)
+                                                  )
            forbitdata                          =  FOR BIT DATA
            from_clause                         =  FROM *table_reference !%($',' *table_reference)
            fullselect                          =  *$'_fullselect' !%(*set_operator *$'_fullselect')
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
            function_mapping_name               =  *sql_identifier
            function_name                       =  *two_part_name
            function_option_name                =  *sql_identifier
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
            group_name                          =  *sql_identifier
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
            host_variable                       =  $':' *sql_identifier !*indicator_variable
            indicator_variable                  =  !INDICATOR $':' *sql_identifier
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
            parameter_name                      =  *sql_identifier
            parameter_marker                    =  $'?'
            predicate                           =  *expression
+                                                  (  (  $'='
+                                                     |  $'!='
+                                                     |  $'^='
+                                                     |  $'<>'
+                                                     |  $'<'
+                                                     |  $'>'
+                                                     |  $'<='
+                                                     |  $'>='
+                                                     )
+                                                     *expression
+                                                  |  (  $'='
+                                                     |  $'!='
+                                                     |  $'^='
+                                                     |  $'<>'
+                                                     |  $'<'
+                                                     |  $'>'
+                                                     |  $'<='
+                                                     |  $'>='
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
+                                                  (  $'='
+                                                     ((SOME | ANY) $'(' *fullselect $')' | $'(' *expression_list $')')
+                                                  |  IN $'(' *fullselect $')'
+                                                  |  NOT IN $'(' *fullselect $')'
+                                                  )
+                                               |  NOT EXISTS $'(' *fullselect $')'
+                                               |  EXISTS $'(' *fullselect $')'
            type_predicate                      =  *type_predicate_element !%($',' *type_predicate_element)
            type_predicate_element              =  !ONLY *type_name
            predicate_specification             =  WHEN
+                                                  ($'=' | $'<>' | $'<' | $'>' | $'<=' | $'>=')
+                                                  (*constant | EXPRESSION AS *expression_name)
+                                                  (  *data_filter !*index_exploitation
+                                                  |  *index_exploitation !*data_filter
+                                                  )
            procedure_name                      =  *two_part_name
            read_only_clause                    =  FOR (READ | FETCH) ONLY
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
            columnDefinition                    =  $'*' | *sql_identifier $'.' $'*' | *expression !*correlation_clause
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
+                                                  |  *sql_identifier
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
            supertable_name                     =  *sql_identifier
            superview_name                      =  *sql_identifier
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
            tablespace_name                     =  *sql_identifier
            tablespace_options                  =  !(INDEX IN *tablespace_name) !(LONG IN *tablespace_name)
            term                                =  *factor
+                                                  !%(
+                                                     $'*' *factor
+                                                  |  $'/' *factor
+                                                  |  $'||' *factor
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
+                                                     |  OLD_TABLE !AS *sql_identifier
+                                                     |  NEW_TABLE !AS *sql_identifier
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
+                                                  |  BEGIN ATOMIC %(*triggered_SQL_stmt $';') END
+                                                  )
            two_part_name                       =  *sql_identifier !($'.' *sql_identifier)
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
            typed_table_or_view_name            =  *sql_identifier
            under_clause                        =  UNDER *supertable_name INHERIT SELECT PRIVILEGES
            unique_constraint                   =  *constraint_clause
+                                                  (UNIQUE | PRIMARY KEY)
+                                                  $'('
+                                                  *column_name
+                                                  !%($',' *column_name)
+                                                  $')'
            unsigned_constant                   =  $'_SQ_STRING_' | $'_REAL_' | $'_REAL_1_' | $'_INTEGER_'
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

                                                                                             :(RETURN)
UserDefsEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserRpt()')                                                              :(UserRptEnd)
UserRpt     udb               =     Pop()                                                    :f(RETURN)
            DIFFER(udb)                                                                      :f(RETURN)
*           XDump('udb', udb)
            TDump(udb)                                                                       :(RETURN)
UserRptEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserFinal()')                                                            :(UserFinalEnd)
UserFinal                                                                                    :(RETURN)
UserFinalEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserTokens()')                                                           :(UserTokensEnd)
UserTokens  tok[t = t + 1] = token(,, .stmts)
            tok[t = t + 1] = token(,  *(spcpfx "*$'_REAL_'"), *$'_REAL_')
            tok[t = t + 1] = token(,  *(spcpfx "*$'_REAL_1_'"), *$'_REAL_1_')
            tok[t = t + 1] = token(,  *(spcpfx "*$'_INTEGER_'"), *$'_INTEGER_')
            tok[t = t + 1] = token(,  *(spcpfx "*$'_DQ_STRING_'"), *$'_DQ_STRING_')
            tok[t = t + 1] = token(,  *(spcpfx "*$'_SQ_STRING_'"), *$'_SQ_STRING_')
            tok[t = t + 1] = token(,  *(tx), *resword . tx)
            tok[t = t + 1] = token(,  *(tx), *keyword . tx)
            tok[t = t + 1] = token(,  *("'" tx "'"), *identifier . tx)
            tok[t = t + 1] = token(,  *("$'" tx "'"), *operator . tx)
            tok[t = t + 1] = token(,  *("$'" tx "'"), ',' . tx)
            tok[t = t + 1] = token(,  *("$'" tx "'"), '(' . tx)
            tok[t = t + 1] = token(,  *("$'" tx "'"), ')' . tx)
            tok[t = t + 1] = token(,  *("$'" tx "'"), '{' . tx)
            tok[t = t + 1] = token(,  *("$'" tx "'"), '}' . tx)
            tok[t = t + 1] = token(,  *("$'" tx "'"), ';' . tx)

            dbg[.$'_fullselect']                         = TRUE
            dbg[.$'_INTEGER_']                           = TRUE
            dbg[.$'_REAL_']                              = TRUE
            dbg[.$'_REAL_1_']                            = TRUE
            dbg[.$'_DQ_STRING_']                         = TRUE
            dbg[.$'_SQ_STRING_']                         = TRUE
            dbg[.assignment_clause]                      = TRUE
            dbg[.assignment_clause_element]              = TRUE
            dbg[.assignment_clause_sub_element]          = TRUE
            dbg[.authorization_name]                     = TRUE
            dbg[.case_expression]                        = TRUE
            dbg[.cast_function]                          = TRUE
            dbg[.cast_specification]                     = TRUE
            dbg[.check_condition]                        = TRUE
            dbg[.check_constraint]                       = TRUE
            dbg[.columnDefinition]                       = TRUE
            dbg[.column]                                 = TRUE
            dbg[.column_default_spec]                    = TRUE
            dbg[.column_definition]                      = TRUE
            dbg[.column_name]                            = TRUE
            dbg[.column_option]                          = TRUE
            dbg[.column_options]                         = TRUE
            dbg[.column_start]                           = TRUE
            dbg[.common_table_expression]                = TRUE
            dbg[.comparison_string]                      = TRUE
            dbg[.constant]                               = TRUE
            dbg[.constraint_clause]                      = TRUE
            dbg[.constraint_name]                        = TRUE
            dbg[.copy_options]                           = TRUE
            dbg[.correlation_clause]                     = TRUE
            dbg[.correlation_name]                       = TRUE
            dbg[.create_procedure_argument]              = TRUE
            dbg[.create_procedure_stmt]                  = TRUE
            dbg[.create_summary_table_partition_key]     = TRUE
            dbg[.create_summary_table_stmt]              = TRUE
            dbg[.create_trigger_stmt]                    = TRUE
            dbg[.create_view_stmt]                       = TRUE
            dbg[.cursor_name]                            = TRUE
            dbg[.data_filter]                            = TRUE
            dbg[.data_type]                              = TRUE
            dbg[.data_type_basic]                        = TRUE
            dbg[.datalink_options]                       = TRUE
            dbg[.datetime_special_register]              = TRUE
            dbg[.declare_cursor]                         = TRUE
            dbg[.declare_global_temporary_table_column]  = TRUE
            dbg[.declare_global_temporary_table_stmt]    = TRUE
            dbg[.default_clause]                         = TRUE
            dbg[.default_value_clause]                   = TRUE
            dbg[.default_values_clause]                  = TRUE
            dbg[.delete_stmt]                            = TRUE
            dbg[.dereference_operation]                  = TRUE
            dbg[.diagnostic_string]                      = TRUE
            dbg[.distinct_type_name]                     = TRUE
            dbg[.element]                                = TRUE
            dbg[.element_list]                           = TRUE
            dbg[.element_list_element]                   = TRUE
            dbg[.explainable_stmt]                       = TRUE
            dbg[.exploitation_rule]                      = TRUE
            dbg[.expression]                             = TRUE
            dbg[.expression_list]                        = TRUE
            dbg[.expression_name]                        = TRUE
            dbg[.expression_or_expression_list]          = TRUE
            dbg[.factor]                                 = TRUE
            dbg[.fetch_first_clause]                     = TRUE
            dbg[.file_link_options]                      = TRUE
            dbg[.forbitdata]                             = TRUE
            dbg[.from_clause]                            = TRUE
            dbg[.fullselect]                             = TRUE
            dbg[.function]                               = TRUE
            dbg[.function_expression_list]               = TRUE
            dbg[.function_mapping_name]                  = TRUE
            dbg[.function_name]                          = TRUE
            dbg[.function_option_name]                   = TRUE
            dbg[.function_options]                       = TRUE
            dbg[.function_options_value]                 = TRUE
            dbg[.function_specification]                 = TRUE
            dbg[.grand_total]                            = TRUE
            dbg[.group_by_clause]                        = TRUE
            dbg[.group_by_element]                       = TRUE
            dbg[.group_name]                             = TRUE
            dbg[.grouping_expression_list]               = TRUE
            dbg[.grouping_set_element]                   = TRUE
            dbg[.grouping_set_list_element]              = TRUE
            dbg[.grouping_sets]                          = TRUE
            dbg[.gt_column_options]                      = TRUE
            dbg[.having_clause]                          = TRUE
            dbg[.host_variable]                          = TRUE
            dbg[.identity_clause]                        = TRUE
            dbg[.identity_clause_element]                = TRUE
            dbg[.index_exploitation]                     = TRUE
            dbg[.index_extension_name]                   = TRUE
            dbg[.index_name]                             = TRUE
            dbg[.indicator_variable]                     = TRUE
            dbg[.insert_stmt]                            = TRUE
            dbg[.insert_stmt_value_list]                 = TRUE
            dbg[.insert_value]                           = TRUE
            dbg[.integer_kmg]                            = TRUE
            dbg[.into_clause]                            = TRUE
            dbg[.join_condition]                         = TRUE
            dbg[.labeled_duration]                       = TRUE
            dbg[.lob_options]                            = TRUE
            dbg[.method_invocation]                      = TRUE
            dbg[.method_name]                            = TRUE
            dbg[.method_signature]                       = TRUE
            dbg[.method_signature_parameter]             = TRUE
            dbg[.nj_table_reference]                     = TRUE
            dbg[.numeric_constant]                       = TRUE
            dbg[.oid_column]                             = TRUE
            dbg[.oid_column_definition]                  = TRUE
            dbg[.oid_column_name]                        = TRUE
            dbg[.opt_all_distinct]                       = TRUE
            dbg[.opt_labeled_duration]                   = TRUE
            dbg[.optimize_for_clause]                    = TRUE
            dbg[.order_by_clause]                        = TRUE
            dbg[.order_by_clause_element]                = TRUE
            dbg[.outer]                                  = TRUE
            dbg[.parameter_marker]                       = TRUE
            dbg[.parameter_name]                         = TRUE
            dbg[.predicate]                              = TRUE
            dbg[.predicate_specification]                = TRUE
            dbg[.procedure_name]                         = TRUE
            dbg[.read_only_clause]                       = TRUE
            dbg[.referential_constraint]                 = TRUE
            dbg[.rehashable_table_options]               = TRUE
            dbg[.result_expression]                      = TRUE
            dbg[.root_view_definition]                   = TRUE
            dbg[.rule_clause]                            = TRUE
            dbg[.search_condition]                       = TRUE
            dbg[.search_condition_paren]                 = TRUE
            dbg[.searched_when_clause]                   = TRUE
            dbg[.select_clause]                          = TRUE
            dbg[.select_into_stmt]                       = TRUE
            dbg[.select_stmt]                            = TRUE
            dbg[.set_current_query_optimization_stmt]    = TRUE
            dbg[.set_operator]                           = TRUE
            dbg[.set_transition_variable]                = TRUE
            dbg[.set_transition_variable_list]           = TRUE
            dbg[.signal_sqlstate_stmt]                   = TRUE
            dbg[.simple_when_clause]                     = TRUE
            dbg[.sort_key]                               = TRUE
            dbg[.sort_key_expression]                    = TRUE
            dbg[.special_register]                       = TRUE
            dbg[.specific_name]                          = TRUE
            dbg[.sql_function]                           = TRUE
            dbg[.sql_function_parameter]                 = TRUE
            dbg[.sql_identifier]                         = TRUE
            dbg[.stmts]                                  = TRUE
            dbg[.string_constant]                        = TRUE
            dbg[.subselect]                              = TRUE
            dbg[.subtype_treatment]                      = TRUE
            dbg[.subview_definition]                     = TRUE
            dbg[.summary_fullselect]                     = TRUE
            dbg[.summary_table_definition]               = TRUE
            dbg[.summary_table_options]                  = TRUE
            dbg[.super_groups]                           = TRUE
            dbg[.supertable_name]                        = TRUE
            dbg[.superview_name]                         = TRUE
            dbg[.table_name]                             = TRUE
            dbg[.table_or_view_name]                     = TRUE
            dbg[.table_reference]                        = TRUE
            dbg[.table_reference_type_one]               = TRUE
            dbg[.table_reference_type_three]             = TRUE
            dbg[.table_reference_type_two]               = TRUE
            dbg[.tablespace_name]                        = TRUE
            dbg[.tablespace_options]                     = TRUE
            dbg[.term]                                   = TRUE
            dbg[.transition_variable]                    = TRUE
            dbg[.trigger_name]                           = TRUE
            dbg[.triggered_SQL_stmt]                     = TRUE
            dbg[.triggered_action]                       = TRUE
            dbg[.two_part_name]                          = TRUE
            dbg[.type_name]                              = TRUE
            dbg[.type_predicate]                         = TRUE
            dbg[.type_predicate_element]                 = TRUE
            dbg[.typed_element_list]                     = TRUE
            dbg[.typed_element_list_element]             = TRUE
            dbg[.typed_table_or_view_name]               = TRUE
            dbg[.under_clause]                           = TRUE
            dbg[.unique_constraint]                      = TRUE
            dbg[.unsigned_constant]                      = TRUE
            dbg[.update_clause]                          = TRUE
            dbg[.update_stmt]                            = TRUE
            dbg[.values_clause]                          = TRUE
            dbg[.values_into_stmt]                       = TRUE
            dbg[.values_row]                             = TRUE
            dbg[.values_row_list_element]                = TRUE
            dbg[.view_name]                              = TRUE
            dbg[.view_under_clause]                      = TRUE
            dbg[.view_with_options]                      = TRUE
            dbg[.view_with_options_value]                = TRUE
            dbg[.where_clause]                           = TRUE
            dbg[.with_options]                           = TRUE
                                                                                             :(RETURN)
UserTokensEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
