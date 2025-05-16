*---------------------------------------------------------------------------------------------------
* Qize(s) - Quote-ize a string. Make a SNOBOL4 expression from the string.
*---------------------------------------------------------------------------------------------------
               DEFINE('Qize(str)part')
               QizeWierd      =    bSlash bs ff nl cr tab                           :(QizeEnd)
Qize           Qize           =    IDENT(str) "''"                                  :S(RETURN)
Qize0          IDENT(str)                                                           :S(RETURN)
               Qize           =    DIFFER(Qize) Qize ' '
               str            POS(0)
+                             (  bSlash . *assign(.part, *'bSlash')
+                             |  bs     . *assign(.part, *'bs')
+                             |  ff     . *assign(.part, *'ff')
+                             |  nl     . *assign(.part, *'nl')
+                             |  cr     . *assign(.part, *'cr')
+                             |  tab    . *assign(.part, *'tab')
+                             ) =                                                   :S(Qize3)
               str            POS(0)
+                             (BREAK('"' "'" QizeWierd) '"' ARBNO(NOTANY("'" QizeWierd))) . part
+                             RTAB(0) . str                                         :S(Qize1)
               str            POS(0)
+                             (BREAK("'" '"' QizeWierd) "'" ARBNO(NOTANY('"' QizeWierd))) . part
+                             RTAB(0) . str                                         :S(Qize2)
               str            POS(0) BREAK(QizeWierd) . part =                      :S(Qize1)
               str            POS(0) REM . part =                                   :S(Qize1)F(error)
Qize1          Qize           =    Qize "'" part "'"                                :(Qize0)
Qize2          Qize           =    Qize '"' part '"'                                :(Qize0)
Qize3          Qize           =    Qize part                                        :(Qize0)
QizeEnd
*---------------------------------------------------------------------------------------------------
               DEFINE('SQize(str)part')                                             :(SQizeEnd)
SQize          IDENT(str)                                                           :S(RETURN)
               SQize          =    DIFFER(SQize) SQize ' '
               str            POS(0) BREAK("'") . part "'" =                        :S(SQize1)
               str            POS(0) REM . part =                                   :S(SQize2)F(error)
SQize1         SQize          =    SQize "'" part "'" ' "' "'" '"'                  :(SQize)
SQize2         SQize          =    SQize "'" part "'"                               :(SQize)
SQizeEnd
*---------------------------------------------------------------------------------------------------
               DEFINE('DQize(str)part')                                             :(DQizeEnd)
DQize          IDENT(str)                                                           :S(RETURN)
               DQize          =    DIFFER(DQize) DQize ' '
               str            POS(0) BREAK('"') . part '"' =                        :S(DQize1)
               str            POS(0) REM . part =                                   :S(DQize2)F(error)
DQize1         DQize          =    DQize '"' part '"' " '" '"' "'"                  :(DQize)
DQize2         DQize          =    DQize '"' part '"'                               :(DQize)
DQizeEnd
*---------------------------------------------------------------------------------------------------
               DEFINE('SqlSQize(str)part')                                          :(SqlSQizeEnd)
SqlSQize       IDENT(str)                                                           :S(RETURN)
               str            POS(0) BREAK("'") . part "'" =                        :S(SqlSQize1)
               str            POS(0) REM . part =                                   :S(SqlSQize2)F(error)
SqlSQize1      SqlSQize       =    SqlSQize part "''"                               :(SqlSQize)
SqlSQize2      SqlSQize       =    SqlSQize part                                    :(SqlSQize)
SqlSQizeEnd
*---------------------------------------------------------------------------------------------------
               DEFINE('Intize(qqstr)iq,qqdlm')                                      :(IntizeEnd)
Intize         qqstr          POS(0) ("'" | '"') $ qqdlm
+                             ARBNO(
+                                bSlash
+                                (  bSlash . *assign(.Intize, *(Intize bSlash))
+                                |  '"' . *assign(.Intize, *(Intize '"'))
+                                |  "'" . *assign(.Intize, *(Intize "'"))
+                                |  'b' . *assign(.Intize, *(Intize bs))
+                                |  'f' . *assign(.Intize, *(Intize ff))
+                                |  'n' . *assign(.Intize, *(Intize lf))
+                                |  'r' . *assign(.Intize, *(Intize cr))
+                                |  't' . *assign(.Intize, *(Intize tab))
+                                |  'u'
+                                   (  '00' LEN(2) . iq . *assign(.Intize, *(Intize Ucvt(iq)))
+                                   |  LEN(4) . iq . *assign(.Intize, *(Intize bSlash 'u' iq))
+                                   )
+                                )
+                             |  BREAK(*(qqdlm bSlash)) . iq . *assign(.Intize, *(Intize iq))
+                             )
+                             *qqdlm RPOS(0)                                        :S(RETURN)F(FRETURN)
IntizeEnd
*---------------------------------------------------------------------------------------------------
            DEFINE('Extize(str)')                                                   :(ExtizeEnd)
Extize
ExtizeEnd
