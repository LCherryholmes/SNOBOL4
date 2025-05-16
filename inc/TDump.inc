*---------------------------------------------------------------------------------------------------
* TDump(x) - Recursive routine to dump tree x to output in a lisp-like parenthetical
* representation. Uses TLump(x, len) to build string for output on one line, but if it will
* not fit then uses multiple line format.
*
* TLump(x) - Recursive function to return as a string tree x in a
* lisp-like parenthetical representation.
*---------------------------------------------------------------------------------------------------
               DEFINE('TValue(x)i')                                                 :(TValueEnd)
TValue
*              DIFFER(t(x), '.')                                                    :F(TValue3)
               TValue         =  IDENT(v(x)) "."                                    :S(TValue3)
               TValue         =  IDENT(t(x), 'Name') v(x)                           :S(RETURN)
               TValue         =  IDENT(t(x), 'float') v(x)                          :S(RETURN)
               TValue         =  IDENT(t(x), 'integer') v(x)                        :S(RETURN)
               TValue         =  IDENT(t(x), 'bool') v(x)                           :S(RETURN)
               TValue         =  IDENT(t(x), 'datetime') "'" SqlSQize(v(x)) "'"     :S(RETURN)
               TValue         =  IDENT(t(x), 'character') "'" SqlSQize(v(x)) "'"    :S(RETURN)
               TValue         =  IDENT(t(x), 'string') "'" SqlSQize(v(x)) "'"       :S(RETURN)
               TValue         =  IDENT(t(x), 'identifier') v(x)                     :S(RETURN)
               TValue         =  t(x)                                               :S(RETURN)
TValue3        i              =  0
TValue5        i              =  LT(i, n(x)) i + 1                                  :F(RETURN)
               TValue         =  TValue (DIFFER(TValue) '.', '') v(c(x)[i])         :(TValue5)
TValueEnd
*---------------------------------------------------------------------------------------------------
               DEFINE('TDump(x,outNm)i,t')                                          :(TDumpEnd)
TDump          outNm          =  IDENT(outNm) .OUTPUT
               x              =  IDENT(DATATYPE(x), 'NAME') $x
               Gen(TLump(x, 140 - GetLevel()) nl, outNm)                            :S(RETURN)
               NULL           *IDENT(n(x))                                          :F(TDump0);*  | *IDENT(t(x), '.')
               Gen(TValue(x) nl, outNm)                                             :(RETURN)
TDump0         t(x)           POS(0) ANY(&UCASE &LCASE)
+                             (SPAN( digits &UCASE '_' &LCASE) | epsilon) RPOS(0)   :F(TDump1)
               t              =  t(x)                                               :(TDump2)
TDump1         t              =  '"' t(x) '"'                                       :(TDump2)
TDump2         Gen('(' t nl, outNm)
               IncLevel()
               i              =  0
TDump3         i              =  LT(i, n(x)) i + 1                                  :F(TDump4)
               TDump(c(x)[i], outNm)                                                :(TDump3)
TDump4         DecLevel()
               Gen(')' nl, outNm)                                                   :(RETURN)
TDumpEnd
*---------------------------------------------------------------------------------------------------
               DEFINE('TLump(x,len)i,t')                                            :(TLumpEnd)
TLump          GT(len, 0)                                                           :F(FRETURN)
               TLump          =  IDENT(x) '()'                                      :S(RETURN)
               NULL           *IDENT(n(x))                                          :F(TLump0);* | *IDENT(t(x), '.')
               TLump          =  TValue(x)
               LE(SIZE(TLump), len)                                                 :S(RETURN)F(FRETURN)
TLump0         TLump          =  '('
               t(x)           POS(0) ANY(&UCASE &LCASE)
+                             (SPAN( digits &UCASE '_' &LCASE) | epsilon) RPOS(0)   :F(TLump1)
               t              =  t(x)                                               :(TLump2)
TLump1         t              =  '"' t(x) '"'                                       :(TLump2)
TLump2         TLump          =  TLump t
               i              =  0
TLump3         i              =  LT(i, n(x)) i + 1                                  :F(TLump4)
               TLump          =  TLump ' ' TLump(c(x)[i], len - SIZE(TLump) - 2)    :S(TLump3)F(FRETURN)
TLump4         TLump          =  TLump ')'                                          :(RETURN)
TLumpEnd
