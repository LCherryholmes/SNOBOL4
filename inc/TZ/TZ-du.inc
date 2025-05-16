            SEP                                 =  '/'
            EOL                                 =  nl
            DIGITS                              =  SPAN('0123456789')
            FILENAME_START                      =  ANY('0123456789')
+                                               |  ANY('abcdefghijklmnopqrstuvwxyz')
+                                               |  ANY('ABCDEFGHIJKLMNOPQRSTUVWXYZ')
+                                               |  '_'
+                                               |  '.'
            FILENAME                            =  *FILENAME_START !%(*FILENAME_START | '-')
            filename                            =  *FILENAME | *DIGITS
            line                                =  *DIGITS *filename !%(*SEP *filename) *EOL
            input                               =  !%*line $' ' RPOS(0)
