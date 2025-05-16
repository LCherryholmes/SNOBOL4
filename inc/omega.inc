*---------------------------------------------------------------------------------------------------
            DEFINE('TV(lvl,pat,name)omega')                                                  :(TVEnd)
TV          omega             =     EQ(doParseTree, FALSE) "pat"
            omega             =     EQ(doParseTree, TRUE)  "(pat ~ 'identifier')"
            omega             =     omega ' $ tx *LEQ(lwr(tx), "' lwr(name) '")'
            TV                =     TZ(lvl, name, EVAL(omega))                               :S(RETURN)F(error);* Conflict TY also used here
TVEnd
*---------------------------------------------------------------------------------------------------
            DEFINE('TW(lvl,pat,name)omega')                                                  :(TWEnd)
TW          omega             =     EQ(doParseTree, FALSE) "pat"
            omega             =     EQ(doParseTree, TRUE)  "(pat ~ 'identifier')"
            omega             =     omega " $ tx *LEQ(upr(tx), '" upr(name) "')"
            TW                =     TZ(lvl, name, EVAL(omega))                               :S(RETURN)F(error);* Conflict TY also used here
TWEnd
*---------------------------------------------------------------------------------------------------
            DEFINE('TX(lvl,pat,name)omega')                                                  :(TXEnd)
TX          omega             =     EQ(doParseTree, FALSE) "pat"
            omega             =     EQ(doParseTree, TRUE)  "(pat ~ 'identifier')"
            omega             =     omega " $ tx *LEQ(tx, '" name "')"
            TX                =     TZ(lvl, name, EVAL(omega))                               :S(RETURN)F(error);* Conflict TY also used here
TXEnd
*---------------------------------------------------------------------------------------------------
            DEFINE('TY(lvl,name,pat)omega')                                                  :(TYEnd)
TY          TY                =     LE(xTrace, 0) pat
+                                   @txOfs $ *assign(.t8Max, *(GT(txOfs, t8Max) txOfs))      :S(RETURN)
            omega             =     "pat $ tz"
+                                   " @txOfs"
+                                   " $ *T8Trace(" lvl ", " Qize(name ': ') " tz, txOfs)"
            TY                =     EVAL(omega)                                              :S(RETURN)F(error)
TYEnd
*---------------------------------------------------------------------------------------------------
*           Instrument parser patterns for tracing:
*           TZ(integer, string, pattern)
            DEFINE('TZ(lvl,name,pat)omega')                                                  :(TZEnd)
TZ          TZ                =     LE(xTrace, 0) pat
+                                   @txOfs $ *assign(.t8Max, *(GT(txOfs, t8Max) txOfs))      :S(RETURN)
            omega             =     "@txOfs $ *T8Trace(" lvl ", '?' " Qize(name) ", txOfs)"
+                                   " pat $ tz"
+                                   " @txOfs"
+                                   " $ *T8Trace(" lvl ", " Qize(name ': ') " tz, txOfs)"
            TZ                =     EVAL(omega)                                              :S(RETURN)F(error)
TZEnd
