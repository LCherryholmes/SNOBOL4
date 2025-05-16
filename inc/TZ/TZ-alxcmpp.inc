            '.'                                 =  '.'
            '='                                 =  '='
            ';'                                 =  ';'
            MSL                                 =  epsilon
+                                               |  *MSL *dont_care
+                                               |  *MSL $'.'
+                                               |  *MSL _METHOD
+                                               |  *MSL OMS *dont_care
+                                               |  *MSL OMS _METHOD
+                                               |  *MSL OMS $'.' *dont_care
+                                               |  *MSL OMS $'.' $'.'
+                                               |  *MSL OMS $'.' _METHOD *WHITE_SPACE $'=' *WHITE_SPACE *DQ_STRING $';'
+                                               |  *MSL OMS $'.' _METHOD *WHITE_SPACE $'=' *DQ_STRING $';'
+                                               |  *MSL OMS $'.' _METHOD $'=' *WHITE_SPACE *DQ_STRING $';'
+                                               |  *MSL OMS $'.' _METHOD $'=' *DQ_STRING $';'
+                                               |  *MSL EXEC *WHITE_SPACE SQL *WHITE_SPACE *sql_command $';'
            sql_command                         =  epsilon
+                                               |  *sql_command *sql_dont_care
+                                               |  *sql_command BEGINBLOCK *sql_block ENDBLOCK
            sql_block                           =  *blk_dont_care | *sql_block *blk_dont_care
            dont_care                           =  *DONT_CARE
+                                               |  *SYMBOL
+                                               |  *DQ_STRING
+                                               |  *SQ_STRING
+                                               |  *NUMBER
+                                               |  *WHITE_SPACE
+                                               |  $'='
+                                               |  $';'
            sql_dont_care                       =  *DONT_CARE
+                                               |  *SYMBOL
+                                               |  *DQ_STRING
+                                               |  *SQ_STRING
+                                               |  *NUMBER
+                                               |  *WHITE_SPACE
+                                               |  $'.'
+                                               |  $'='
+                                               |  OMS
+                                               |  _METHOD
            blk_dont_care                       =  *DONT_CARE
+                                               |  *SYMBOL
+                                               |  *DQ_STRING
+                                               |  *SQ_STRING
+                                               |  *NUMBER
+                                               |  *WHITE_SPACE
+                                               |  $'.'
+                                               |  $'='
+                                               |  $';'
+                                               |  EXEC
+                                               |  SQL
+                                               |  OMS
+                                               |  _METHOD
