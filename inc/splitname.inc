*----------------------------------------------------------------------------------------------------
*------------ --------------------------------------------------------------------- -----------------
              DEFINE('splitname(apath)')                                            :(splitname_end)
splitname     splitname      =   ARRAY('2')
              apath          POS(0)
+                            (  ('$' | ANY(&LCASE &UCASE) ':' | '//' BREAK('/') | '.')
+                               ARBNO('/' BREAK('/'))
+                            ) . splitname[1]
+                            '/' ARBNO(NOTANY('/')) . splitname[2]
+                            RPOS(0)                                                :(RETURN)
splitname_end
