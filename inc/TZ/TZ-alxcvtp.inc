            '.'                                 =  '.'
            '('                                 =  '('
            ')'                                 =  ')'
            '@'                                 =  '@'
            '='                                 =  '='
            ';'                                 =  ';'
            msl                                 =  epsilon
+                                               |  *msl *dont_care
+                                               |  *msl $'.'
+                                               |  *msl METHOD
+                                               |  *msl OMS *dont_care
+                                               |  *msl OMS METHOD
+                                               |  *msl OMS $'.' *dont_care
+                                               |  *msl OMS $'.' $'.'
+                                               |  *msl OMS $'.' METHOD *opt_space $'=' *opt_space *DQ_STRING $';'
+                                               |  *msl OMSUSEDATABASE $'(' *SYMBOL $')' $';'
+                                               |  *msl OMSUSEDATABASE $'(' *DQ_STRING $')' $';'
+                                               |  *msl
+                                                  $'@'
+                                                  NEWUSER
+                                                  *opt_space
+                                                  $'='
+                                                  *opt_space
+                                                  *DQ_STRING
+                                                  *opt_space
+                                                  $';'
+                                               |  *msl
+                                                  CALL
+                                                  *opt_space
+                                                  $'('
+                                                  *opt_space
+                                                  SETAUTH
+                                                  *opt_space
+                                                  $')'
+                                                  *opt_space
+                                                  $';'
+                                               |  *msl
+                                                  CALL
+                                                  *opt_space
+                                                  $'('
+                                                  *opt_space
+                                                  RESETAUTH
+                                                  *opt_space
+                                                  $')'
+                                                  *opt_space
+                                                  $';'
+                                               |  *msl
+                                                  CALL
+                                                  *opt_space
+                                                  $'('
+                                                  *opt_space
+                                                  *SYMBOL
+                                                  *opt_space
+                                                  $')'
+                                                  *opt_space
+                                                  $';'
+                                               |  *msl EXEC *WHITE_SPACE SQL *WHITE_SPACE *sql_create $';'
+                                               |  *msl EXEC *WHITE_SPACE SQL *WHITE_SPACE *sql_command $';'
            opt_space                           =  epsilon | *WHITE_SPACE
            sql_create                          =  CREATE *WHITE_SPACE *sql_object *sql_create_body
            sql_object                          =  PROCEDURE | TRIGGER | VIEW | *SYMBOL
            sql_create_body                     =  epsilon
+                                               |  *sql_create_body BEGINBLOCK *sql_block ENDBLOCK
+                                               |  *sql_create_body *sql_dont_care
+                                               |  *sql_create_body CREATE
            sql_command                         =  epsilon
+                                               |  *sql_command BEGINBLOCK *sql_block ENDBLOCK
+                                               |  *sql_command *sql_dont_care
+                                               |  *sql_command *sql_dont_care CREATE
            sql_block                           =  *blk_dont_care | *sql_block *blk_dont_care
            dont_care                           =  $'@'
+                                               |  $'('
+                                               |  $')'
+                                               |  $';'
+                                               |  $'='
+                                               |  *DONT_CARE
+                                               |  *DQ_STRING
+                                               |  *NUMBER
+                                               |  *SQ_STRING
+                                               |  *SYMBOL
+                                               |  *WHITE_SPACE
+                                               |  CREATE
+                                               |  PROCEDURE
+                                               |  TRIGGER
+                                               |  VIEW
            sql_dont_care                       =  $'@'
+                                               |  $'('
+                                               |  $')'
+                                               |  $'.'
+                                               |  $'='
+                                               |  *DONT_CARE
+                                               |  *DQ_STRING
+                                               |  *NUMBER
+                                               |  *SQ_STRING
+                                               |  *SYMBOL
+                                               |  *WHITE_SPACE
+                                               |  OMS
+                                               |  SQL
+                                               |  METHOD
+                                               |  NEWUSER
+                                               |  CALL
+                                               |  SETAUTH
+                                               |  RESETAUTH
+                                               |  PROCEDURE
+                                               |  TRIGGER
+                                               |  VIEW
            blk_dont_care                       =  $'@'
+                                               |  $'('
+                                               |  $')'
+                                               |  $'.'
+                                               |  $';'
+                                               |  $'='
+                                               |  *DONT_CARE
+                                               |  *DQ_STRING
+                                               |  *NUMBER
+                                               |  *SQ_STRING
+                                               |  *SYMBOL
+                                               |  *WHITE_SPACE
+                                               |  EXEC
+                                               |  OMS
+                                               |  SQL
+                                               |  METHOD
+                                               |  NEWUSER
+                                               |  CALL
+                                               |  SETAUTH
+                                               |  RESETAUTH
+                                               |  CREATE
+                                               |  PROCEDURE
+                                               |  TRIGGER
+                                               |  VIEW
