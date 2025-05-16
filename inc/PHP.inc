*-------------------------------------------------------------------------------------------------------
* PHP.inc
*---------- ----------- --- ------------------------------------------------------- --------------------
            $'  '       =   SPAN(' ' tab cr lf)
            $' '        =   FENCE($'  ' | epsilon)
            $'{'        =   $' ' TY(1, '{', '{')
            $'}'        =   $' ' TY(1, '}', '}')
            $':'        =   $' ' TY(1, ':', ':')
            $';'        =   $' ' TY(1, ';', ';')
*---------- --------------- --- ------------------------------------------------------------------------
            phpInt          =   SPAN('0123456789') $ phpxN . phpxN
            phpYear         =   phpInt *EQ(SIZE(phpxN), 4)
            phpMonth        =   phpInt *EQ(SIZE(phpxN), 2)
            phpDay          =   phpInt *EQ(SIZE(phpxN), 2)
            phpHour         =   phpInt *EQ(SIZE(phpxN), 2)
            phpMinute       =   phpInt *EQ(SIZE(phpxN), 2)
            phpSecond       =   phpInt *EQ(SIZE(phpxN), 2)
            phpDate         =   (phpYear '-' phpMonth '-' phpDay) . phpxDate
            phpTime         =   (phpHour ':' phpMinute ':' phpSecond) . phpxTime
            phpDateExtra    =   '+' phpInt *EQ(SIZE(phpxN), 4)
            phpDateTime     =   $' ' TY(2, 'phpDateTime',
+                                          '"'
+                                          (phpDate 'T' phpTime phpDateExtra)
+                                          '"' . *assign(.phpxDateTime, phpxDate ' ' phpxTime)
+                                    )
*---------- --------------- --- ------------------------------------------------------------------------
            phpString       =   's' $':' *phpInt $':' '"' *LEN(phpxN) . phpxVal '"'
            phpInteger      =   'i' $':' *phpInt . phpxVal
            phpStrVal       =   $' ' TY(2, 'phpStrVal', phpString)
            phpIntVal       =   $' ' TY(2, 'phpIntVal', phpInteger)
            phpVar          =   $' ' TY(2, 'phpVar',    phpString)
*---------- --------------- --- ------------------------------------------------------------------------
            phpElement      =   *phpIntVal   epsilon . *Shift('Integer', phpxVal)
+                           |   *phpStrVal   epsilon . *Shift('String', phpxVal)
+                           |   *phpList
+                           |   *phpAggregate
            phpList         =   'a' $':' *phpInt $':'
+                               $'{' nPush() !(*phpListItem nInc() ARBNO($',' *phpListItem nInc()))
+                               $'}' . *Reduce('[]', nTop()) nPop()
            phpListItem     =   *phpIntVal $';' *phpElement $';'
            phpAggregate    =   'a' $':' *phpInt $':'
+                               $'{' nPush() *phpTerm nInc() ARBNO($',' *phpTerm nInc())
+                               $'}' . *Reduce('{}', nTop()) nPop()
            phpTerm         =   *phpVar . *Shift('Name', phpxVar) $';'
+                               *phpElement . *Reduce(':', 2) $';'
            phpParser       =   *phpAggregate . *Reduce('PHP', 1)
            phpRecognizer   =   POS(0) FENCE *phpParser $' ' RPOS(0)
*---------- --------------- --- ------------------------------------------------------ --------------------
            phpElement      =   TZ(1, 'phpElement', phpElement)
            phpList         =   TZ(1, 'phpList', phpList)
            phpListItem     =   TZ(1, 'phpListItem', phpListItem)
            phpAggregate    =   TZ(1, 'phpAggregate', phpAggregate)
            phpTerm         =   TZ(1, 'phpTerm', phpTerm)
            phpParser       =   TZ(1, 'phpParser', phpParser)
            phpRecognizer   =   epsilon $ t8Max
+                               TZ(1, 'phpRecognizer', phpRecognizer)
*---------- ----------- --- ------------------------------------------------------ --------------------
            DEFINE('PHPDecode(str)ch,h0,h1,xch0,xch1,xchs')
            phpHex      =   '0123456789ABCDEF'                                     :(PHPDecodeEnd)
PHPDecode   str         FENCE POS(0) RPOS(0)                                       :S(RETURN)
            str         FENCE bSlash 'u' LEN(4) . xchs =                           :S(PHPDecode1)
            str         FENCE bSlash
+                             (    bSlash . ch
+                             |    fSlash . ch
+                             |    '"' . ch
+                             |    "'" . ch
+                             |    'b' . *assign(.ch, CHAR(8))
+                             |    't' . *assign(.ch, CHAR(9))
+                             |    'n' . *assign(.ch, CHAR(10))
+                             |    'f' . *assign(.ch, CHAR(12))
+                             |    'r' . *assign(.ch, CHAR(13))
+                             ) =                                                   :S(PHPDecode2)
            str         FENCE bSlash =                                              :S(error)
            str         FENCE LEN(1) . ch =                                         :S(PHPDecode2)F(error)
PHPDecode1  xchs        =   REPLACE(xchs, &LCASE, &UCASE)
            xchs        FENCE '00' LEN(1) . xch1 LEN(1) . xch0 RPOS(0)              :F(PHPDecode3)
            phpHex      BREAK(xch1) @h1                                             :F(PHPDecode3)
            phpHex      BREAK(xch0) @h0                                             :F(PHPDecode3)
            PHPDecode   =   PHPDecode CHAR(h1 * 16 + h0)                            :(PHPDecode)
PHPDecode2  PHPDecode   =   PHPDecode ch                                            :(PHPDecode)
PHPDecode3
*           OUTPUT      =   'PHPDecode: Warning: ' bSlash 'u' xchs
                                                                                    :(PHPDecode)
PHPDecodeEnd
*---------- ----------- --- ------------------------------------------------------ --------------------
