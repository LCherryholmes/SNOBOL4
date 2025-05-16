*-----------------------------------------------------------------------------------------------------------------------
* Trace.inc
*---------- ----------------- ----- -------------------------------------------------------- ---------------------------
            DEFINE('T8Trace(lvl,str,ofs)t8p')
            t8MaxLast         =     0                                                        :(T8TraceEnd)
T8Trace     T8Trace           =     .dummy
            GT(doDebug, 0)                                                                   :F(NRETURN)
            LE(lvl, doDebug)                                                                 :F(NRETURN)
            GT(doDebug, 1)                                                                   :S(T8Trace1)
            str               POS(0) '?'                                                     :S(NRETURN)
T8Trace1    str               POS(0) '?' = '? '                                              :S(T8Trace2)
            str               POS(0) = '  '
T8Trace2    t8p               =     T8Pos(strOfs + ofs, t8Map)
            GE(t8MaxLine, 621)                                                               :F(NRETURN)
            t8MaxLast         =     GE(t8Max, t8MaxLast) t8Max                               :F(NRETURN)
            OUTPUT            =     t8p str                                                  :(NRETURN)
T8TraceEnd
*---------- ----------------- ----- -------------------------------------------------------- --------------------------
            DEFINE('T8Pos(t8Ofs,t8Map)i')                                                    :(T8PosEnd)
T8Pos       T8Pos             =     IDENT(t8Map) LPAD(t8Ofs, 8)                              :S(RETURN)
            i                 =     +t8Ofs
            t8Max             =     GT(t8Ofs, t8Max) +t8Ofs
T8Pos1      i                 =     IDENT(t8Map[i]) i - 1                                    :S(T8Pos1)
            t8Line            =     t8Map[i]
            t8Pos             =     t8Ofs - i + 1
            i                 =     +t8Max
T8Pos2      i                 =     IDENT(t8Map[i]) i - 1                                    :S(T8Pos2)
            t8MaxLine         =     t8Map[i]
            t8MaxPos          =     t8Max - i + 1
            T8Pos             =     '(' LPAD(t8MaxLine, 5)
+                                   ', ' LPAD(t8MaxPos, 3)
+                                   ', ' LPAD(t8Line, 5)
+                                   ', ' LPAD(t8Pos, 3)
+                                   ')'                                                      :(RETURN)
T8PosEnd
