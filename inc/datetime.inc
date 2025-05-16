*---------------------------------------------------------------------------------------------------
            DEFINE('Datetime()dom,dt,mo,time,year')                 :(DatetimeEnd)
Datetime    dt          =   DATE()
            dt          POS(0) SPAN('0123456789') . mo
+                       '/' SPAN('0123456789') . dom
+                       '/' SPAN('0123456789') . year
+                       ' ' (  SPAN('0123456789')
+                              ':' SPAN('0123456789')
+                              ':' SPAN('0123456789')
+                           ) . time
+                       RPOS(0)
            year        =   LT(year, 90) year + 2000
            year        =   GE(year, 90) LE(year, 99) year + 1900
            Datetime    =   year '-' mo '-' dom ' ' time            :(RETURN)
DatetimeEnd
*---------------------------------------------------------------------------------------------------
            DEFINE('Day(date)d,m,y')
            dayList     =   '0Sun1Mon2Tues3Wednes4Thurs5Fri6Satur7' :(DayEnd)
Day         date        =   IDENT(date) SUBSTR(Datetime(), 1, 10)
            date        POS(0) SPAN('0123456789') . y
+                       ('/' | '-') SPAN('0123456789') . m
+                       ('/' | '-') SPAN('0123456789') . d
+                       RPOS(0)
            m           =   LE(m, 2) m + 12                         :F(Day1)
            y           =   y - 1
Day1        m           =   m - 3
            Day         =   (y / 400) * 146097
+                           + (REMDR(y, 400) / 100) * 36524
+                           + (REMDR(y, 100) / 4) * 1461
+                           + REMDR(y, 4) * 365
            Day         =   Day + ((153 * m) + 2) / 5 + d + 2
            d           =   REMDR(Day, 7)
            dayList     d BREAK('01234567') . Day
            Day         =   Day 'day'                               :(RETURN)
DayEnd
*---------------------------------------------------------------------------------------------------
            DEFINE('IsLeap(year)')                                  :(IsLeapEnd)
IsLeap      EQ(REMDR(year, 400), 0)                                 :S(RETURN)
            EQ(REMDR(year, 100), 0)                                 :S(FRETURN)
            EQ(REMDR(year, 4), 0)                                   :S(RETURN)F(FRETURN)
IsLeapEnd
*---------------------------------------------------------------------------------------------------
            DEFINE('DaysInYear(iYYYY)')                             :(DaysInYearEnd)
DaysInYear  DaysInYear  =   (IsLeap(iYYYY) 366, 365)                :(RETURN)
DaysInYearEnd
*---------------------------------------------------------------------------------------------------
            DEFINE('Julian2date(dy,year)d,m,t,x')
            jMap0       =   '(334,12)(304,11)(273,10)(243,9)'
+                           '(212,8)(181,7)(151,6)(120,5)'
+                           '(90,4)(59,3)(31,2)(0,1)'
            jMap1       =   '(335,12)(305,11)(274,10)(244,9)'
+                           '(213,8)(182,7)(152,6)(121,5)'
+                           '(91,4)(60,3)(31,2)(0,1)'
            j2mo        =   '(' SPAN('0123456789') $ x *GT(dy, x)
+                           ',' SPAN('0123456789') $ m
+                           ')'                                     :(Julian2dateEnd)
Julian2date t           =   jMap0
            t           =   EQ(REMDR(year, 4), 0)   jMap1
            t           =   EQ(REMDR(year, 100), 0) jMap0
            t           =   EQ(REMDR(year, 400), 0) jMap1
            t           j2mo                                        :F(FRETURN)
            d           =   dy - x
            LE(d, 31)                                               :F(FRETURN)
            Julian2date =   LPAD(year, 4, 0)
+                           '-' LPAD(m, 2, 0)
+                           '-' LPAD(d, 2, 0)                       :(RETURN)
Julian2dateEnd
*---------------------------------------------------------------------------------------------------
            DEFINE('Date2julian(d)dom,m,mo,t,x,year')
            mo2j        =   '(' SPAN('0123456789') $ x
+                           ',' SPAN('0123456789') $ m *EQ(m, mo)
+                           ')'                                     :(Date2julianEnd)
Date2julian d           POS(0) SPAN('0123456789') . year
+                       ('/' | '-') SPAN('0123456789') . mo
+                       ('/' | '-') SPAN('0123456789') . dom
+                       RPOS(0)
            t           =   jMap0
            t           =   EQ(REMDR(year, 4), 0)   jMap1
            t           =   EQ(REMDR(year, 100), 0) jMap0
            t           =   EQ(REMDR(year, 400), 0) jMap1
            t           mo2j                                        :F(FRETURN)
            Date2julian =   x + dom                                 :(RETURN)
Date2julianEnd
*---------------------------------------------------------------------------------------------------
            jA = ARRAY('0:1,0:11')
            jA[0,  0] =   0 ;  jA[1,  0] =   0
            jA[0,  1] =  31 ;  jA[1,  1] =  31
            jA[0,  2] =  59 ;  jA[1,  2] =  60
            jA[0,  3] =  90 ;  jA[1,  3] =  91
            jA[0,  4] = 120 ;  jA[1,  4] = 121
            jA[0,  5] = 151 ;  jA[1,  5] = 152
            jA[0,  6] = 181 ;  jA[1,  6] = 182
            jA[0,  7] = 212 ;  jA[1,  7] = 213
            jA[0,  8] = 243 ;  jA[1,  8] = 244
            jA[0,  9] = 273 ;  jA[1,  9] = 274
            jA[0, 10] = 304 ;  jA[1, 10] = 305
            jA[0, 11] = 334 ;  jA[1, 11] = 335
*---------------------------------------------------------------------------------------------------
            DATA('SQLDATE(dtDay,dtTime)')
*---------------------------------------------------------------------------------------------------
            DEFINE('DTDecode(dt)'
+               'i300thSecs,iDIY,iDays,iJ,iYYYY,'
+               'xiDOM,xiHH,xiMM,xiMOY,xiSS,xiYYYY'
+           )                                                       :(DTDecodeEnd)
DTDecode    dt          POS(0) SPAN('0123456789') . xiYYYY
+                       ('/' | '-') SPAN('0123456789') . xiMOY
+                       ('/' | '-') SPAN('0123456789') . xiDOM
+                       ' ' SPAN('0123456789') . xiHH
+                       ':' SPAN('0123456789') . xiMM
+                       ':' SPAN('0123456789') . xiSS
+                       RPOS(0)
            iDays       =   0
            iYYYY       =   GE(xiYYYY, 1900) 1900 - 1               :F(DTDecode3)
DTDecode2   iDays       =   LT(iYYYY = iYYYY + 1, xiYYYY)
+                           iDays + DaysInYear(iYYYY)               :S(DTDecode2)F(DTDecode5)
DTDecode3   iYYYY       =   1899 + 1
DTDecode4   iDays       =   GE(iYYYY = iYYYY - 1, xiYYYY)
+                           iDays - DaysInYear(iYYYY)               :S(DTDecode4)F(DTDecode5)
DTDecode5   iDIY        =   DaysInYear(xiYYYY)
            iJ          =   (EQ(iDIY, 365) 0, 1)
            iDays       =   iDays + jA[iJ, xiMOY - 1]
            iDays       =   iDays + xiDOM - 1
            i300thSecs  =   ((xiHH * 60 + xiMM) * 60 + xiSS) * 300
            iDays       =   EQ(i300thSecs, 25920000) iDays + 1
            i300thSecs  =   EQ(i300thSecs, 25920000) 0
            DTDecode    =   SQLDATE(iDays,i300thSecs)               :(RETURN)
DTDecodeEnd
*---------------------------------------------------------------------------------------------------
            DEFINE('DTEncode(SDT)'
+               'i300thSecs,iDIY,iDOY,iDays,iJ,iSecs,'
+               'xiDOM,xiHH,xiMM,xiMOY,xiSS,xiTT,xiYYYY'
+           )                                                       :(DTEncodeEnd)
DTEncode    IDENT(DATATYPE(SDT), 'SQLDATE')                         :F(error)
            iDOY        =   0  ;* days since January 1 - between 0 and 365
            iDIY        =   0  ;* days in the year - either 365 or 366
            iDays       =   dtDay(SDT)  ;* days since Jan 1 1900 (it may be less than 0)!!!
            iDOY        =   iDays
            xiYYYY      =   GE(iDays, 0) 1900 - 1                   :F(DTEncode3)
DTEncode2   iDIY        =   DaysInYear(xiYYYY = xiYYYY + 1)
            iDOY        =   GE(iDOY - iDIY, 0) iDOY - iDIY          :S(DTEncode2)F(DTEncode5)
DTEncode3   xiYYYY      =   1899 + 1
DTEncode4   iDIY        =   DaysInYear(xiYYYY = xiYYYY - 1)
            iDOY        =   LT(iDOY + iDIY, 0) iDOY + iDIY          :S(DTEncode4)
            iDOY        =   iDOY + iDIY
DTEncode5   iJ          =   (EQ(iDIY, 365) 0, 1)
            xiMOY       =   12
DTEncode8   xiMOY       =   GT(jA[iJ, xiMOY - 1], iDOY) xiMOY - 1   :S(DTEncode8)
            xiDOM       =   iDOY - jA[iJ, xiMOY - 1] + 1  ;* day of the month - between 1 and 31
            i300thSecs  =   dtTime(SDT)  ;* 300ths of a second since midnight
            iSecs       =   i300thSecs / 300  ;* seconds since midnight
            xiTT        =   ((REMDR(i300thSecs, 300) * 1000) + 150) / 300  ;* milli-seconds ticks after the second
            xiHH        =   iSecs / 3600  ;* hours since midnight - between 0 and 23
            xiMM        =   REMDR(iSecs, 3600) / 60  ;* minutes after the hour - between 0 and 59
            xiSS        =   REMDR(iSecs, 3600) - (xiMM * 60)  ;* seconds after the minute - between 0 and 59
            DTEncode    =   LPAD(xiYYYY, 4, 0)
+                           '-' LPAD(xiMOY, 2, 0)
+                           '-' LPAD(xiDOM, 2, 0)
+                           ' ' LPAD(xiHH, 2, 0)
+                           ':' LPAD(xiMM, 2, 0)
+                           ':' LPAD(xiSS, 2, 0)                    :(RETURN)
DTEncodeEnd
*---------------------------------------------------------------------------------------------------
            DEFINE('DTDiff(xSDT,ySDT)iDays,iSecs')                  :(DTDiffEnd)
DTDiff      iDays       =   (dtDay(xSDT) - dtDay(ySDT))
            iSecs       =   (dtTime(xSDT) - dtTime(ySDT)) / 300
            DTDiff      =   iDays * 86400 + iSecs                   :S(RETURN)
DTDiffEnd
*---------------------------------------------------------------------------------------------------
            DEFINE('DTSubtract(xSDT,iSecs)'
+               'i300th,i300thDiff,iDays,iDaysDiff'
+)                                                                  :(DTSubtractEnd)
DTSubtract  iDaysDiff   =   iSecs / 86400
            i300thDiff  =   REMDR(iSecs, 86400) * 300
            iDays       =   dtDay(xSDT)
            i300th      =   dtTime(xSDT) - i300thDiff
            iDays       =   GE(i300thDiff) LT(i300th) iDays - 1
            i300th      =   GE(i300thDiff) LT(i300th) i300th + 25920000
            iDays       =   LT(i300thDiff) GE(i300th, 25920000) iDays + 1
            i300th      =   LT(i300thDiff) GE(i300th, 25920000) i300th - 25920000
            iDays       =   iDays - iDaysDiff
            DTSubtract  =   SQLDATE(iDays, i300th)                  :S(RETURN)
DTSubtractEnd
*---------------------------------------------------------------------------------------------------
