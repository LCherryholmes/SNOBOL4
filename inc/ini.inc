*-------------------------------------------------------------------------------------------
              eol = nl @iniOfs
*-------------------------------------------------------------------------------------------
              iniParse =
+             (
+                epsilon . *assign(.iniTbl, *TABLE(17))
+                ARBNO((
+                   (';' BREAK(nl)) eol
+                |  ('[' BREAK(']' nl) . iniSectName ']') eol
+                   epsilon . *assign(.iniSectName, INTEGER(iniSectName) +iniSectName)
+                   epsilon . *assign(.iniTbl[iniSectName], *TABLE(7))
+                   epsilon . *assign(.iniSectTbl, *iniTbl[iniSectName])
+                |  (BREAK('=' nl) . iniAttrName '=' BREAK(nl) . iniAttrValue) eol
+                   epsilon . *assign(.iniSectTbl[iniAttrName], *iniAttrValue)
+                |  (SPAN(' ' tab) | epsilon) eol
+                ))
+             )
*-------------------------------------------------------------------------------------------
              iniGenerate =
+             *(
+                export_table(iniTbl, .iniSectName, .iniSectTbl, *(
+                   '[' iniSectName ']' nl
+                   export_table(iniSectTbl, .iniAttrName, .iniAttrValue, *(
+                      iniAttrName '=' iniAttrValue nl
+                   ))
+                   nl
+                ))
+             )
*-------------------------------------------------------------------------------------------
              DEFINE('IniPos(iniOfs,iniMap)i')                                       :(IniPosEnd)
IniPos        i               =    iniOfs
IniPos1       i               =    IDENT(iniMap[i]) i - 1                            :S(IniPos1)
              IniPos          =    'Line: ' iniMap[i] ' Position: ' iniOfs - i + 1   :(RETURN)
IniPosEnd
*-------------------------------------------------------------------------------------------
              DEFINE('IniRead(iniFileName)iniFile,iniMap,iniOfs,iniTbl')             :(IniReadEnd)
IniRead       iniFile         =    Read(iniFileName, .iniMap)                        :F(IniReadErr1)
              iniFile         POS(0) iniParse RPOS(0)                                :F(IniReadErr2)
              IniRead         =    iniTbl                                            :(RETURN)
IniReadErr1   OUTPUT          =    'Error: unable to open input file: ' iniFileName  :(FRETURN)
IniReadErr2   OUTPUT          =    'Error: unable to parse file: ' iniFileName
              OUTPUT          =    IniPos(iniOfs, iniMap)                            :(FRETURN)
IniReadEnd
*-------------------------------------------------------------------------------------------
              DEFINE('IniWrite(iniFileName,iniTbl)iniFile,iniLine,iniOutput')        :(IniWriteEnd)
IniWrite      iniFile         =    EVAL(iniGenerate)                                 :F(IniWriteErr1)
              Write(iniFileName, iniFile)                                            :S(RETURN)f(IniWriteErr2)
IniWriteErr1  OUTPUT          =    "Warning: can't generate file: " iniFileName      :(FRETURN)
IniWriteErr2  OUTPUT          =    "Warning: can't open output file: " iniFileName   :(FRETURN)
IniWriteEnd
*-------------------------------------------------------------------------------------------
