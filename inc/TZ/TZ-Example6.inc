            basic_expr                          =  *ID ($'(' *expr $')' | $'.' *ID) | $'(' *expr $')' | new *ID
            expr                                =  TBD
            ID                                  =  SPAN('abcdefghijklmnopqrstuvwxyz')
