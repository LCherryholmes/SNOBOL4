            basic_expr                          =  *ID $'(' *expr $')' | $'(' *expr $')' | new *ID | *ID $'.' *ID
            expr                                =  TBD
            ID                                  =  SPAN('abcdefghijklmnopqrstuvwxyz')
