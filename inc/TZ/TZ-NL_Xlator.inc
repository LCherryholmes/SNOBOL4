            ID                                  =  ANY('abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_')
+                                                  (SPAN('abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789') | epsilon)
            NUM                                 =  SPAN('0123456789')
            ExpressionList                      =  !%(*Expression $';') $' ' RPOS(0)
            Expression                          =  *Term !%($'+' *Term)
            Term                                =  *Factor !%($'*' *Factor)
            Factor                              =  *ID | *NUM | $'(' *Expression $')'
