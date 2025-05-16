*-------------------------------------------------------------------------------------------------------------------------
*=================== ======== ===== ======================================================== =============================
-INCLUDE 'pp.inc'
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('Ucvt(hex)')
            UcvtMap           =     'A:10,B:11,C:12,D:13,E:14,F:15'                          :(UcvtEnd)
Ucvt        hex               POS(0) RPOS(0)                                                 :S(UcvtRet)
            hex               POS(0) ANY(digits) . h =                                       :S(Ucvt10)
            hex               POS(0) ANY('ABCDEFabcdef') . h =                               :F(error)
            UcvtMap           (POS(0) | ',') upr(h) ':' SPAN(digits) . h (',' | RPOS(0))     :F(error)
Ucvt10      Ucvt              =     (16 * Ucvt) + h                                          :(Ucvt)
UcvtRet     Ucvt              =     CHAR(Ucvt)                                               :(RETURN)
UcvtEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('Intize(qqstr)iq,qqdlm')                                                  :(IntizeEnd)
Intize      qqstr             POS(0) ("'" | '"') $ qqdlm
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
+                             *qqdlm RPOS(0)                                                 :S(RETURN)F(FRETURN)
IntizeEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('Extize(str)')                                                            :(ExtizeEnd)
Extize
ExtizeEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('Merge(x)a,aC,aCnt,bnfCnt,c,i,j,k,l,m,mN,mC,n,reCnt,pA,pB,pL,pN,pT')      :(MergeEnd)
Merge       DIFFER(x)                                                                        :F(RETURN)
            IDENT(t(x), 'productions')                                                       :F(xerr)
            n                 =     n(x)
            c                 =     c(x)
            pT                =     TABLE()
Merge0      i                 =     0
Merge1      i                 =     LT(i, n) i + 1                                           :F(Merge5)
            DIFFER(c[i])                                                                     :F(Merge1)
            reCnt             =     IDENT(t(c[i]), 're_production') reCnt + 1                :S(Merge1)
            IDENT(t(c[i]), 'bnf_production')                                                 :F(xerr)
            pN                =     v(c(c[i])[1])
            pA                =     c(c[i])[2]
            bnfCnt            =     IDENT(pT[pN]) bnfCnt + 1
            pT[pN]            =     IDENT(pT[pN]) TABLE()
            pT[pN][0]         =     pT[pN][0] + 1
            pT[pN][pT[pN][0]] =     pA                                                       :(Merge1)
Merge5      mN                =     reCnt + bnfCnt
            mC                =     ARRAY('1:' mN)
            Merge             =     tree('productions',, mN, mC)
            m                 =     0
            i                 =     0
Merge10     i                 =     LT(i, n) i + 1                                           :F(Merge20)
            DIFFER(c[i])                                                                     :F(Merge10)
            m                 =     IDENT(t(c[i]), 're_production') m + 1                    :F(Merge10)
            mC[m]             =     c[i]                                                     :(Merge10)
Merge20     a                 =     CONVERT(pT, 'ARRAY')
            i                 =     0
Merge23     i                 =     i + 1
            pN                =     a[i, 1]                                                  :F(Merge40)
            pL                =     a[i, 2]
            aCnt              =     0
            j                 =     0
Merge25     j                 =     LT(j, pL[0]) j + 1                                       :F(Merge30)
            aCnt              =     IDENT(pL[j]) aCnt + 1                                    :S(Merge25)
            aCnt              =     DIFFER(t(pL[j]), '|') aCnt + 1                           :S(Merge25)
            aCnt              =     aCnt + n(pL[j])                                          :(Merge25)
Merge30     pB                =     ARRAY('1:2')
            pB[1]             =     tree('identifier', pN)
            mC[m = m + 1]     =     tree('bnf_production',, 2, pB)
            pB[2]             =     EQ(aCnt, 1) pL[1]                                        :S(Merge23)
            aC                =     ARRAY('1:' aCnt)
            pB[2]             =     tree('|',, aCnt, aC)
            k                 =     0
            j                 =     0
Merge35     j                 =     LT(j, pL[0]) j + 1                                       :F(Merge23)
            DIFFER(t(pL[j]), '|')                                                            :F(Merge37)
            aC[k = k + 1]     =     pL[j]                                                    :(Merge35)
Merge37     l                 =     0
Merge39     l                 =     LT(l, n(pL[j])) l + 1                                    :F(Merge35)
            aC[k = k + 1]     =     c(pL[j])[l]                                              :(Merge39)
Merge40                                                                                      :(RETURN)
MergeEnd
