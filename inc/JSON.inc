*-------------------------------------------------------------------------------------------------------
* JSON.inc - Java Serializable Object Notation
*---------- ----------- --- ------------------------------------------------------- --------------------
            $'  '       =   SPAN(' ' tab cr lf)
            $' '        =   FENCE($'  ' | epsilon)
            $'{'        =   $' ' TY(1, '{', '{')
            $'}'        =   $' ' TY(1, '}', '}')
            $'['        =   $' ' TY(1, '[', '[')
            $']'        =   $' ' TY(1, ']', ']')
            $':'        =   $' ' TY(1, ':', ':')
            $','        =   $' ' TY(1, ',', ',')
*---------- ----------- --- ------------------------------------------------------- --------------------
            jInt        =   (FENCE('+' | '-' | epsilon) SPAN('0123456789')) . jxN
            jEscChar    =   bSlash
+                           (  ANY('ntbrf' '"' bSlash fSlash "'")
+                           |  ANY('01234567') FENCE(ANY('01234567') | epsilon)
+                           |  ANY('0123') ANY('01234567') ANY('01234567')
+                           |  'u' LEN(4) $ jxU $ *match(jxU, POS(0) SPAN('0123456789ABCDEFabcdef') RPOS(0))
+                           )
            jNullVal    =   'null' epsilon . jxVal
            jTrueFalse  =   ('true' | 'false') . jxVal
            jIdent      =   ANY(&UCASE '_' &LCASE) FENCE(SPAN(&UCASE '_' &LCASE '0123456789') | epsilon)
            jVar        =   '"' (jIdent FENCE(' ' jIdent | epsilon) | jInt) . jxVar '"'
            jString     =   '"' (ARBNO(BREAK('"' bSlash lf) | jEscChar)) . jxVal '"'
            jStrVal     =   jString . *assign(.jxVal, JSONDecode(jxVal))
            jBoolVal    =   jTrueFalse | '"' jTrueFalse '"'
            jRealVal    =   (('+' | '-' | epsilon) SPAN('0123456789') '.' SPAN('0123456789')) . jxVal
            jIntVal     =   (jInt . jxVal | '"' jInt . jxVal '"')
*---------- ----------- --- ----------------------------------------------------------------------------
            jMos        =   TABLE()
            jMos['Jan'] =   '01'
            jMos['Feb'] =   '02'
            jMos['Mar'] =   '03'
            jMos['Apr'] =   '04'
            jMos['May'] =   '05'
            jMos['Jun'] =   '06'
            jMos['Jul'] =   '07'
            jMos['Aug'] =   '08'
            jMos['Sep'] =   '09'
            jMos['Oct'] =   '10'
            jMos['Nov'] =   '11'
            jMos['Dec'] =   '12'
            jMonthName  =   (   'Jan' | 'Feb' | 'Mar' | 'Apr' | 'May' | 'Jun'
+                           |   'Jul' | 'Aug' | 'Sep' | 'Oct' | 'Nov' | 'Dec'
+                           ) . jxMonthName . *assign(.jxMonth, jMos[jxMonthName])
            jDayName    =   'Sun' | 'Mon' | 'Tue' | 'Wed' | 'Thu' | 'Fri' | 'Sat'
            jNum2       =   SPAN('0123456789') $ jxN . jxN *EQ(SIZE(jxN), 2)
            jNum3       =   SPAN('0123456789') $ jxN . jxN *EQ(SIZE(jxN), 3)
            jNum4       =   SPAN('0123456789') $ jxN . jxN *EQ(SIZE(jxN), 4)
            jYear       =   jNum4 . jxYear
            jMonth      =   jNum2 . jxMonth
            jDay        =   jNum2 . jxDay
            jHour       =   jNum2 . jxHour
            jMinute     =   jNum2 . jxMinute
            jSecond     =   jNum2 . jxSecond
            jDatetime   =   '"' . *assign(.jxHour, '00')
+                               . *assign(.jxMinute, '00')
+                               . *assign(.jxSecond, '00')
+                           (   jDayName ', ' jDay ' ' jMonthName ' ' jYear ' ' jHour ':' jMinute ':' jSecond ' +' jNum4
+                           |   jDayName ' ' jMonthName ' ' jDay ' ' jHour ':' jMinute ':' jSecond ' +' jNum4 ' ' jYear
+                           |   jYear '-' jMonth '-' jDay
+                           |   jYear '-' jMonth '-' jDay 'T' jHour ':' jMinute ':' jSecond
+                           |   jYear '-' jMonth '-' jDay 'T' jHour ':' jMinute ':' jSecond ('.' jNum3 | epsilon) 'Z'
+                           |   jYear '-' jMonth '-' jDay 'T' jHour ':' jMinute ':' jSecond '+' jNum4
+                           |   jYear '-' jMonth '-' jDay 'T' jHour ':' jMinute ':' jSecond '+' jNum2 ':' jNum2
+                           |   jYear '-' jMonth '-' jDay ' ' jHour ':' jMinute ':' jSecond ' +' jNum4
+                           )
+                           '"' . *assign(.jxDatetime, jxYear '-' jxMonth '-' jxDay ' ' jxHour ':' jxMinute ':' jxSecond)
            jDateVal    =   jDatetime . *assign(.jxVal, jxDatetime)
*---------- ----------- --- ------------------------------------------------------- --------------------
            jBoolVal    =   $' ' TY(2, 'jBoolVal', jBoolVal)
            jDateVal    =   $' ' TY(2, 'jDateVal', jDateVal)
            jIntVal     =   $' ' TY(2, 'jIntVal', jIntVal)
            jNullVal    =   $' ' TY(2, 'jNullVal', jNullVal)
            jRealVal    =   $' ' TY(2, 'jRealVal', jRealVal)
            jStrVal     =   $' ' TY(2, 'jStrVal', jStrVal)
            jVar        =   $' ' TY(2, 'jVar', jVar)
*---------- ----------- --- ------------------------------------------------------- --------------------
            jRecognizer =   POS(0) FENCE *jParser $' ' RPOS(0)
            jParser     =   *jObject . *Reduce('JSON', 1)
            jObject     =   $'{' nPush()
+                               !(*jField nInc() ARBNO($',' *jField nInc()))
+                           $'}' . *Reduce('{}', nTop()) nPop()
+                           FENCE
            jArray      =   $'[' nPush()
+                               !(*jElement nInc() ARBNO($',' *jElement nInc()))
+                           $']' . *Reduce('[]', nTop()) nPop()
+                           FENCE
            jField      =   *jVar . *Shift('Name', jxVar)
+                           $':' *jElement . *Reduce(':', 2)
            jElement    =   *jRealVal  epsilon . *Shift('Real', jxVal)
+                       |   *jIntVal   epsilon . *Shift('Integer', jxVal)
+                       |   *jBoolVal  epsilon . *Shift('Bool', jxVal)
+                       |   *jDateVal  epsilon . *Shift('Datetime', jxVal)
+                       |   *jStrVal   epsilon . *Shift('String', jxVal)
+                       |   *jNullVal  epsilon . *Shift('Null')
+                       |   *jArray
+                       |   *jObject
*---------- ----------- --- ------------------------------------------------------- --------------------
            jRecognizer =   epsilon $ t8Max
+                           TZ(1, 'jRecognizer', jRecognizer)
            jParser     =   TZ(1, 'jParser', jParser)
            jObject     =   TZ(1, 'jObject', jObject)
            jArray      =   TZ(1, 'jArray', jArray)
            jField      =   TZ(1, 'jField', jField)
            jElement    =   TZ(1, 'jElement', jElement)
*---------- ----------- --- ------------------------------------------------------- --------------------
            jpTab       =   4
            jpPretty    =   FENCE $ jpxP            . *assign(.jpxL, 0)
+                                                   . *assign(.jpxP, NULL)
+                           POS(0) *jpObject
+                           $' ' RPOS(0)

            jpObject    =   $'{'                    . *assign(.jpxP, jpxP '{' nl)
+                                                   . *assign(.jpxL, jpxL + 1)
+                                                   . *assign(.jpxP, jpxP DUPL(' ', jpxL * jpTab))
+                         !(*jpField ARBNO($','     . *assign(.jpxP, jpxP nl DUPL(' ', (jpxL - 1) * jpTab) RPAD(',', jpTab))
+                                    *jpField))
+                           $'}'                    . *assign(.jpxP, jpxP nl)
+                                                   . *assign(.jpxL, jpxL - 1)
+                                                   . *assign(.jpxP, jpxP DUPL(' ', jpxL * jpTab) '}')

            jpArray     =   $'['                    . *assign(.jpxP, jpxP '[' nl)
+                                                   . *assign(.jpxL, jpxL + 1)
+                                                   . *assign(.jpxP, jpxP DUPL(' ', jpxL * jpTab))
+                         !(*jpElement ARBNO($','   . *assign(.jpxP, jpxP nl DUPL(' ', (jpxL - 1) * jpTab) RPAD(',', jpTab))
+                                       *jpElement))
+                           $']'                    . *assign(.jpxP, jpxP nl)
+                                                   . *assign(.jpxL, jpxL - 1)
+                                                   . *assign(.jpxP, jpxP DUPL(' ', jpxL * jpTab) ']')

            jpField     =   $' ' *jVar       . jpxA . *assign(.jpxP, jpxP jpxA)
+                           $':'                    . *assign(.jpxP, jpxP ' : ')
+                           *jpElement

            jpElement   =   *jpObject
+                       |   *jpArray
+                       |   $' ' jRealVal   . jpxA . *assign(.jpxP, jpxP jpxA)
+                       |   $' ' jIntVal    . jpxA . *assign(.jpxP, jpxP jpxA)
+                       |   $' ' jBoolVal   . jpxA . *assign(.jpxP, jpxP jpxA)
+                       |   $' ' jStrVal    . jpxA . *assign(.jpxP, jpxP jpxA)
+                       |   $' ' jNullVal   . jpxA . *assign(.jpxP, jpxP jpxA)
*---------- ----------- --- ------------------------------------------------------- --------------------
            jpPretty    =   epsilon $ t8Max jpPretty
*           jpPretty    =   epsilon $ t8Max
*+                          TZ(1, 'jpPretty', jpPretty)
*           jpObject    =   TZ(1, 'jpObject', jpObject)
*           jpArray     =   TZ(1, 'jpArray', jpArray)
*           jpField     =   TZ(1, 'jpField', jpField)
*           jpElement   =   TZ(1, 'jpElement', jpElement)
*---------- ----------- --- ------------------------------------------------------ --------------------
            DEFINE('JSONDecode(str)ch,h,h0,h1,h2,h3,xch0,xch1,xch2,xch3,xchs')
            jHex        =   '0123456789ABCDEF'                                     :(JSONDecodeEnd)
JSONDecode  str         FENCE POS(0) RPOS(0)                                       :S(RETURN)
            str         FENCE bSlash 'u' LEN(4) . xchs =                           :S(JSONDecode1)
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
+                             ) =                                                   :S(JSONDecode2)
            str         FENCE bSlash =                                              :S(error)
            str         FENCE LEN(1) . ch =                                         :S(JSONDecode2)F(error)
JSONDecode1 xchs        =   REPLACE(xchs, &LCASE, &UCASE)
            xchs        FENCE
+                       LEN(1) . xch3
+                       LEN(1) . xch2
+                       LEN(1) . xch1
+                       LEN(1) . xch0
+                       RPOS(0)                                                     :F(JSONDecode3)
            jHex        BREAK(xch3) @h3                                             :F(JSONDecode3)
            jHex        BREAK(xch2) @h2                                             :F(JSONDecode3)
            jHex        BREAK(xch1) @h1                                             :F(JSONDecode3)
            jHex        BREAK(xch0) @h0                                             :F(JSONDecode3)
            h           =   ((h3 * 16 + h2) * 16 + h1) * 16 + h0
            xchs        =   wchar_to_utf8(h)
            JSONDecode  =   JSONDecode xchs                                         :(JSONDecode)
JSONDecode2 JSONDecode  =   JSONDecode ch                                           :(JSONDecode)
JSONDecode3 OUTPUT      =   'JSONDecode: Warning: ' bSlash 'u' xchs                 :(JSONDecode)
JSONDecodeEnd
*---------- ----------- --- ------------------------------------------------------ --------------------
