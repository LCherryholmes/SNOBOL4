*---------- --------------- --- --------------------------------------------------- --------------------------------
            $' '            =   SPAN(' ')
            digit           =   '0123456789'
            statDateTime    =   ANY(digit) ANY(digit)
+                               '/' ANY(digit) ANY(digit)
+                               '/' ANY(digit) ANY(digit)
+                               '_' ANY(digit) ANY(digit)
+                               ':' ANY(digit) ANY(digit)
+                               ':' ANY(digit) ANY(digit)
            statId          =   'ev_' SPAN(&UCASE '_') . sId
            statInt         =   SPAN('0123456789')
            statReal        =   *statInt '.' *statInt
            statPercent     =   *statReal '%' | '-'
            statHeader      =   'script test_wait_event2.ksh on platform ' BREAK(nl) nl
+                               'Time that examined'
+                               ' : Start : ' *statDateTime . statStartTime
+                               ' , End : ' *statDateTime . statEndTime
+                               nl nl
+                               'START Compare part : oracle categories vers. collector categories' nl
+                               nl
+                               'Category' $' ' 'Collector' $' ' 'Oracle' $' ' 'Percent' nl
+                               '--------' $' ' '---------' $' ' '------' $' ' '-------' nl
            statSubLine     =   'SUB' . sType
+                               ': ' *statId
+                               $' ' *statReal . sCollector
+                               $' ' *statReal . sOracle
+                               $' ' *statPercent . sPercentage
+                               nl
            statCatLine     =   'CAT' . sType
+                               ': ' *statId
+                               $' ' *statReal . sCollector
+                               $' ' *statReal . sOracle
+                               $' ' *statPercent . sPercentage
+                               nl
            statFooter      =   'TEST test_wait_event2.ksh FINISHED SUCCESSFULY!' nl

            statParse       =   POS(0)
+                               *statHeader
+                               ARBNO(*statSubLine) nl
+                               ARBNO(*statCatLine) nl
+                               *statFooter
+                               REM
+                               RPOS(0)
