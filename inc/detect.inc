*---------------------------------------------------------------------------------------------------
* Detect:
*   Multiply defined productions
*   Unreferenced productions
*   Undefined references
*---------------------------------------------------------------------------------------------------
            DEFINE('Xdef(x)prodNm')
            Tdefs             =     TABLE()
            Tdefs['at_at_identifier'] = 1
            Tdefs['at_identifier'] = 1
            Tdefs['identifier'] = 1
            Tdefs['binary_literal'] = 1
            Tdefs['integer_literal'] = 1
            Tdefs['money_literal'] = 1
            Tdefs['real_literal'] = 1
            Tdefs['string_literal'] = 1
            Tdefs['true']     = 1
            Tdefs['false']    = 1                                                            :(XdefEnd)
Xdef        DIFFER(x)                                                                        :F(RETURN)
Xdef10      IDENT(t(x), 'bnf_production')                                                    :F(RETURN)
            prodNm            =     v(c(x)[1])
            Tdefs[prodNm]     =     Tdefs[prodNm] + 1                                        :(RETURN)
XdefEnd
*---------------------------------------------------------------------------------------------------
            DEFINE('Xref(x)idNm')
            Trefs             =     TABLE()
            Tundefs           =     TABLE()
            Tcaps             =     TABLE()                                                  :(XrefEnd)
Xref        DIFFER(x)                                                                        :F(RETURN)
            IDENT(t(x), 'bnf_production')                                                    :F(Xref10)
            Visit(c(x)[2], .Xref)                                                            :(FRETURN)
Xref10      IDENT(t(x), 'identifier')                                                        :F(Xref30)
            idNm              =     v(x)
            idNm              POS(0) SPAN(&UCASE '_' '0123456789') RPOS(0)                   :F(Xref20)
            Tcaps[idNm]       =     Tcaps[idNm] + 1                                          :(RETURN)
Xref20      idNm              POS(0) '@' =                                                   :F(Xref25)
            v(x)              =     idNm                                                     :(RETURN)
Xref25      Trefs[idNm]       =     Trefs[idNm] + 1
            IDENT(Tdefs[idNm])                                                               :F(RETURN)
            Tundefs[idNm]     =     Tundefs[idNm] + 1                                        :(RETURN)
Xref30      IDENT(t(x), 'string')                                                            :F(RETURN)
            v(x)              POS(0) SPAN('~`!@#$%^&*()-+={}[]|\":?/<>,.' semicolon "'") RPOS(0) :(RETURN);* PARSER error ;
            v(x)              POS(0) "'" RTAB(1) . v(x) "'"
            OUTPUT            =     v(x)                                                     :(RETURN)
XrefEnd
*---------------------------------------------------------------------------------------------------
            DEFINE('Xreport(x)i,idNm,prodCnt,prodNm,refCnt,tokenCnt,tokenNm')                :(XreportEnd)
Xreport     Adefs             =     DIFFER(Tdefs) SORT(Tdefs)                                :F(Xreport20)
            i                 =     0
Xreport10   i                 =     i + 1
            prodNm            =     Adefs[i, 1]                                              :F(Xreport20)
            prodCnt           =     Adefs[i, 2]
            refCnt            =     Trefs[prodNm]
            OUTPUT            =     GT(prodCnt, 1) 'Multiply defined: ' prodCnt ' ' prodNm
            OUTPUT            =     IDENT(refCnt) 'Unreferenced: ' prodNm                    :(Xreport10)

Xreport20   Aundefs           =     DIFFER(Tundefs) SORT(Tundefs)                            :F(Xreport40)
            i                 =     0
Xreport30   i                 =     i + 1
            prodNm            =     Aundefs[i, 1]                                            :F(Xreport40)
            prodCnt           =     Aundefs[i, 2]
            OUTPUT            =     'Undefined reference: ' LPAD(prodCnt, 3) ' ' prodNm      :(Xreport30)

Xreport40   Acaps             =     DIFFER(Tcaps) SORT(Tcaps)                                :F(Xreport60)
            i                 =     0
Xreport50   i                 =     i + 1
            tokenNm           =     Acaps[i, 1]                                              :F(Xreport60)
            tokenCnt          =     Acaps[i, 2]
            OUTPUT            =     LPAD(tokenCnt, 3) ' ' tokenNm                            :(Xreport50)

Xreport60                                                                                    :(RETURN)
XreportEnd
