            '('                                 =  '('
            ')'                                 =  ')'
            ssp                                 =  epsilon | *ssp  | *ssp *sql GO | *ssp *create_procedure GO
            sql                                 =  *sql_body
+                                               |  *create_stmt
+                                               |  *drop_stmt
+                                               |  $'(' $')'
+                                               |  $'('  $')'
+                                               |  $'(' *sql $')'
+                                               |  $'('  *sql $')'
+                                               |  *sql *sql_body
+                                               |  *sql *create_stmt
+                                               |  *sql *drop_stmt
+                                               |  *sql 
+                                               |  *sql $'(' $')'
+                                               |  *sql $'('  $')'
+                                               |  *sql $'(' *sql $')'
+                                               |  *sql $'('  *sql $')'
            sql_body                            =  *GENERIC
+                                               |  *ID
+                                               |  *TEMP_ID
+                                               |  *DQ_STRING
+                                               |  *SQ_STRING
+                                               |  *NUMBER
+                                               |  TABLE
+                                               |  PROCEDURE
+                                               |  PROC
            create_stmt                         =  CREATE  *ID
+                                               |  CREATE  TABLE  *ID
+                                               |  CREATE  TABLE  *TEMP_ID *create_body
            create_body                         =  $'(' *sql $')' | $'('  *sql $')' | $'(' *sql $')' | $'('  *sql $')'
            drop_stmt                           =  DROP  *ID
+                                               |  DROP  PROCEDURE
+                                               |  DROP  PROC
+                                               |  DROP  TABLE  *ID
+                                               |  DROP  TABLE  *TEMP_ID
            create_procedure                    =  CREATE  PROCEDURE *blocks | CREATE  PROC *blocks
            blocks                              =  *block | *blocks *block | *blocks *create_stmt
            block                               =  
+                                               |  *GENERIC
+                                               |  *ID
+                                               |  *TEMP_ID
+                                               |  *DQ_STRING
+                                               |  *SQ_STRING
+                                               |  *NUMBER
+                                               |  CREATE
+                                               |  DROP
+                                               |  TABLE
+                                               |  PROCEDURE
+                                               |  PROC
+                                               |  $'('
+                                               |  $')'
