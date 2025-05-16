*---------- ----------- --- ------------------------------------------------------- -----------------------------
            DEFINE('HTMLDecode(html)ch,str')                                        :(HTMLDecodeEnd)
HTMLDecode  html        POS(0) RPOS(0)                                              :S(RETURN)
            html        POS(0) '&amp;' . *assign(.ch, '&') =                        :S(HTMLDecode1)
            html        POS(0) '&'                                                  :S(HTMLDecodeErr)
            html        POS(0) BREAK('&') . str =                                   :S(HTMLDecode2)
            html        POS(0) RTAB(0) . str =                                      :S(HTMLDecode2)
HTMLDecode1 HTMLDecode  =   HTMLDecode ch                                           :(HTMLDecode)
HTMLDecode2 HTMLDecode  =   HTMLDecode str                                          :(HTMLDecode)
HTMLDecodeErr OUTPUT = 'Error: ' html                                               :(abort)
HTMLDecodeEnd
*---------- ----------- --- ------------------------------------------------------- -----------------------------
            DEFINE('HTMLClean(html)ch')                                             :(HTMLCleanEnd)
HTMLClean   HTMLClean   =   HTMLDecode(html)
HTMLClean0  HTMLClean   POS(0) ' ' =                                                :S(HTMLClean0)
HTMLClean1  HTMLClean   ' ' RPOS(0) =                                               :S(HTMLClean1)
HTMLClean2  HTMLClean   ' .' RPOS(0) = '.'                                          :S(HTMLClean2)
HTMLClean3  HTMLClean   '  ' = ' '                                                  :S(HTMLClean3)
HTMLClean4  HTMLClean   ' / ' = '/'                                                 :S(HTMLClean4)
HTMLClean5  HTMLClean   ' /' = '/'                                                  :S(HTMLClean5)
HTMLClean6  HTMLClean   '/ ' = '/'                                                  :S(HTMLClean6)F(RETURN)
HTMLCleanEnd
*---------- ----------- --- ------------------------------------------------------- -----------------------------
            DEFINE('MacroName(mt)id,id1,id2,id3')                                   :(MacroNameEnd)
MacroName   id          =   ANY(&UCASE &LCASE) SPAN('0123456789' &UCASE '_' &LCASE)
            mt          ?   POS(0) RPOS(0)                                          :S(RETURN)
            mt          ?   POS(0) id . id1 RPOS(0)                                 :S(MacroName1)
            mt          ?   POS(0) id . id1 ' ' id . id2 RPOS(0)                    :S(MacroName2)
            mt          ?   POS(0) id . id1 ' ' id . id2 ' ' id . id3 RPOS(0)       :S(MacroName3)
            LEQ(DQize(mt), '"' mt '"')                                              :S(MacroName4)F(MacroName5)
MacroName1  MacroName   =   id1                                                     :(RETURN)
MacroName2  MacroName   =   id1 '_' id2                                             :(RETURN)
MacroName3  MacroName   =   id1 '_' id2 '_' id3                                     :(RETURN)
MacroName4  MacroName   =   '$"' mt '"'                                             :(RETURN)
MacroName5  MacroName   =   '$(' DQize(mt) ')'                                      :(RETURN)
MacroNameEnd
*---------- ----------- --- ------------------------------------------------------- -----------------------------
*            DEFINE('MacroValue(mt)wrd1,wrdn,wrdp,wrds,val')                         :(MacroValueEnd)
*MacroValue  wrd1        =   SPAN(&UCASE &LCASE "-'")
*            wrdn        =   (', ' | ' ') SPAN(&UCASE &LCASE "-'")
*            wrds        =   '{' wrd1 ARBNO(wrdn) '}' | wrd1 ARBNO(wrdn)
*            mt          ?   POS(0) wrds . val '/' =                                 :S(MacroValue0)
*            mt          ?   POS(0) wrdp (':' | ' :') REM . val                      :F(RETURN)
*            MacroValue  =   '"' val '" ;* NULL'                                     :(RETURN)
*MacroValue0 MacroValue  =   '"' val '" ;*'
*MacroValue1 mt          ?   POS(0) wrds . val ('/' | RPOS(0)) =                     :F(MacroValue9)
*            MacroValue  =   MacroValue ' "' val '"'                                 :(MacroValue1)
*MacroValue9
**           TERMINAL    =   DIFFER(mt) mt
*            MacroValue  =   DIFFER(mt)                                              :(RETURN)
*MacroValueEnd
*---------- ----------- --- ------------------------------------------------------- -----------------------------
            DEFINE('MacroVals(mt)i,n,val,vals,wrd1,wrdn,wrdp,wrds')                 :(MacroValsEnd)
MacroVals   wrd1        =   SPAN(&UCASE &LCASE "-'")
            wrdn        =   (', ' | ' ') SPAN(&UCASE &LCASE "-'")
            wrds        =   '{' wrd1 ARBNO(wrdn) '}' | wrd1 ARBNO(wrdn)
            wrdp        =   ('Insert' | 'insert' | 'Add' | 'add')
+                           ' if '
+                           ( 'allowed'
+                           | 'applicable'
+                           | 'appropriate'
+                           | 'necessary'
+                           | 'objections untimely'
+                           | 'requesting a hearing'
+                           )
+                           (' ' | epsilon)
+                       |   'if jury trial, add'
            mt          ?   POS(0) wrds . val '/' =                                 :S(MacroVals0)
            mt          ?   POS(0) wrdp (':' | ' :') (' ' | epsilon) REM . val      :F(RETURN)
            MacroVals   =   ARRAY('1:2')
            MacroVals[1] = val
            MacroVals[2] = NULL                                                     :(RETURN)
MacroVals0  vals        =   TABLE(10)
            vals[n = n + 1] = val
MacroVals1  mt          ?   POS(0) wrds . val ('/' | RPOS(0)) =                     :F(MacroVals5)
            vals[n = n + 1] = val                                                   :(MacroVals1)
MacroVals5  DIFFER(mt)                                                              :S(RETURN)
            MacroVals   =   ARRAY('1:' n)
MacroVals7  i           =   LT(i, n) i + 1                                          :F(RETURN)
            MacroVals[i] = vals[i]                                                  :(MacroVals7)
MacroValsEnd
*---------- ----------- --- ------------------------------------------------------- -----------------------------
