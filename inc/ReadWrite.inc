*---------------------------------------------------------------------------------------------------
* Read(fileName, rdMapName) - Read the specified file into one string with lines seperated
* by newline characters. Also create a map table indexed by offsets of each line with its
* corresponding line number.
*---------------------------------------------------------------------------------------------------
               DEFINE('Read(fileName,rdMapName)'
+                  'rdInput,rdIn,rdLine,rdLineNo,rdMap,rdOfs'
+              )                                                                     :(ReadEnd)
Read           INPUT(.rdInput, 8, fileName '[-m10 -l131072]')                        :F(FRETURN)
               rdMap          =    TABLE()
               rdOfs          =    0
               rdLineNo       =    1
               Read           =
Read3          rdMap[rdOfs]   =    rdLineNo
               rdLine         =
Read5          rdIn           =    rdInput                                          :F(Read9)
               rdLine         =    rdLine rdIn
               LT(SIZE(rdIn), 131072)                                               :F(Read5)
               rdLine         RPOS(1) cr =
               rdOfs          =    rdOfs + SIZE(rdLine) + 1
               rdLineNo       =    rdLineNo + 1
               Read           =    Read rdLine nl                                   :(Read3)
Read9          ENDFILE(8)
               DIFFER(rdMapName)                                                    :F(RETURN)
               $rdMapName     =    rdMap                                            :(RETURN)
ReadEnd
*---------------------------------------------------------------------------------------------------
               DEFINE('Write(fileName,fileStr)wrLine,wrOutput')                     :(WriteEnd)
Write          OUTPUT(.wrOutput, 8, fileName)                                       :F(FRETURN)
Write1         fileStr        POS(0) RPOS(0)                                        :S(Write9)
               fileStr        POS(0) BREAK(nl) . wrLine nl =                        :S(Write3)
               fileStr        POS(0) RTAB(0) . wrLine =                             :S(Write3)F(err)
Write3         wrOutput       =    wrLine                                           :(Write1)
Write9         ENDFILE(8)                                                           :(RETURN)
WriteEnd
*---------------------------------------------------------------------------------------------------
               DEFINE('LineMap(str,lmMapName)lmLineNo,lmMap,lmOfs,xOfs')            :(LineMapEnd)
LineMap        lmMap          =    TABLE()
               lmOfs          =    0
               lmLineNo       =    1
LineMap3       lmMap[lmOfs]   =    lmLineNo
               str            POS(0) BREAK(nl) nl @xOfs =                           :F(LineMap9)
               lmOfs          =    lmOfs + xOfs
               lmLineNo       =    lmLineNo + 1                                     :(LineMap3)
LineMap9       $lmMapName     =    lmMap                                            :(RETURN)
LineMapEnd
