*---------------------------------------------------------------------------------------------------
* This program will generate random test strings given a grammar.
*---------------------------------------------------------------------------------------------------
-INCLUDE 'tree.inc'
-INCLUDE 'RANDOM.INC'
*---------------------------------------------------------------------------------------------------
               DEFINE('LookUp(bnf,name)i,tProd,tName,tBody')                  :(LookUpEnd)
LookUp         IDENT(t(bnf), 'productions')                                   :F(error)
LookUp10       i        =  LT(i, n(bnf)) i + 1                                :F(FRETURN)
               tProd    =  c(bnf)[i]
               IDENT(t(tProd), 'bnf_production')                              :F(error)
               tName    =  c(tProd)[1]
               tBody    =  c(tProd)[2]
               IDENT(t(tName), 'identifier')                                  :F(error)
               LookUp   =  IDENT(v(tName), name) tBody                        :S(RETURN)F(LookUp10)
LookUpEnd
*---------------------------------------------------------------------------------------------------
               DEFINE('TGen(tBnf,start)i,tStart')                             :(TGenEnd)
TGen           SEED()
               tStart   =  LookUp(tBnf, start)                                :F(error)
TGen10         i        =  LT(i, 10) i + 1                                    :F(RETURN)
               OUTPUT   =  tt(tStart)                                         :(TGen10)
TGenEnd
*---------------------------------------------------------------------------------------------------
               DEFINE('tt(x)i,r')                                             :(ttEnd)
tt             DIFFER(x)                                                      :F(error)
               DIFFER(t(x))                                                   :S($('tt_' t(x)))F(error)
tt_string      v(x)     POS(0) "'" BREAK("'") . tt "'" RPOS(0)                :F(error)   ;* Literal string
               tt       =  ' ' tt                                             :(RETURN)
tt_identifier  tt       =  ' ' IDENT(v(x), 'identifier') 'x'                  :S(RETURN)  ;* Reference
               tt       =  ' ' IDENT(v(x), 'at_identifier') '@x'              :S(RETURN)
               tt       =  ' ' IDENT(v(x), 'at_at_identifier') '@@x'          :S(RETURN)
               tt       =  ' ' IDENT(v(x), 'real_literal') RANDOM(0) * 100.0  :S(RETURN)
               tt       =  ' ' IDENT(v(x), 'integer_literal') RANDOM(100) - 1 :S(RETURN)
               tt       =  ' ' IDENT(v(x), 'binary_literal') '0x7FFF'         :S(RETURN)
               tt       =  ' ' IDENT(v(x), 'string_literal') "'Hello World!'" :S(RETURN)
               tt       =  ' ' IDENT(v(x), 'money_literal') '$10.99'          :S(RETURN)
               tt       =  ' ' IDENT(v(x), 'true') 'TRUE'                     :S(RETURN)
               tt       =  ' ' IDENT(v(x), 'false') 'FALSE'                   :S(RETURN)
               tt       =  tt(LookUp(bnf, v(x)))                              :S(RETURN)F(tt_error)
tt_&           i        =  LT(i, n(x)) i + 1                                  :F(RETURN)  ;* Subsequents
               tt       =  tt tt(c(x)[i])                                     :($'tt_&')
tt_|           tt       =  tt(c(x)[RANDOM(n(x))])                             :(RETURN)   ;* Alternates
tt_?           tt       =  LT(RANDOM(0), 0.10) tt(c(x)[1])                    :(RETURN)   ;* Optional, Zero or one
tt_*           r        =  LT(RANDOM(0), 0.10) RANDOM(3)                      :F(RETURN)  ;* Zero or more
tt_*10         i        =  LT(i, r) i + 1                                     :F(RETURN)
               tt       =  tt tt(c(x)[1])                                     :($'tt_*10')
tt_+           r        =  RANDOM(3) ;* One or more
tt_+10         i        =  LT(i, r) i + 1                                     :F(RETURN)
               tt       =  tt tt(c(x)[1])                                     :($'tt_+10')
tt_,           r        =  RANDOM(2) ;* Comma seperated list
               tt       =  tt(c(x)[1])
tt_,10         i        =  LT(i, r) i + 1                                     :F(RETURN)
               tt       =  tt ',' tt(c(x)[1])                                 :($'tt_,10')
tt_error       OUTPUT   =  'Lookup failure: ' v(x)                            :(END)
ttEnd
