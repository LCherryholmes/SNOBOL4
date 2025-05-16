*---------------------------------------------------------------------------------------------------
               DEFINE('Norm(nm,x,place)p')                                          :(NormEnd)
Norm           t(c(x)[place])    POS(0) ANY('|&?*+,') RPOS(0)                       :F(RETURN)
               cnt               =     cnt + 1
               p                 =     tree('bnf_production',, 2, ARRAY('1:2'))
               c(p)[1]           =     tree('identifier', nm '$' cnt)
               c(p)[2]           =     c(x)[place]
               c(x)[place]       =     tree('identifier', nm '$' cnt)
               Insert(bnf, p, i + cnt)                                              :(RETURN)
NormEnd
*---------------------------------------------------------------------------------------------------
               DEFINE('PNorm()cnt,i,j,k,name,np')                                   :(PNormEnd)
PNorm          i                 =     0
PNorm01        i                 =     LT(i, n(bnf)) i + 1                          :F(RETURN)
               cnt               =     0
               DIFFER(c(bnf)[i])                                                    :F(error)
               IDENT(t(bnf), 'productions')                                         :F(error)
               IDENT(t(c(bnf)[i]), 'bnf_production')                                :F(error)
               IDENT(t(c(c(bnf)[i])[1]), 'identifier')                              :F(error)
               np                =     c(c(bnf)[i])[2]
               name              =     v(c(c(bnf)[i])[1])
               IDENT(t(np), '|')                                                    :S(PNormAlt00)
               IDENT(t(np), '&')                                                    :S(PNormSeq00)
               IDENT(t(np), '?')                                                    :S(PNormOth00)
               IDENT(t(np), '*')                                                    :S(PNormOth00)
               IDENT(t(np), '+')                                                    :S(PNormOth00)
               IDENT(t(np), ',')                                                    :S(PNormOth00)F(PNorm01)
*---------------------------------------------------------------------------------------------------
PNormAlt00     j                 =     0
PNormAlt01     j                 =     LT(j, n(np)) j + 1                           :F(PNorm01)
               IDENT(t(c(np)[j]), '&')                                              :F(PNormAlt03)
               k                 =     0
PNormAlt02     k                 =     LT(k, n(c(np)[j])) k + 1                     :F(PNormAlt01)
               Norm(name, c(np)[j], k)                                              :(PNormAlt02)
PNormAlt03     Norm(name, np, j)                                                    :(PNormAlt01)
*---------------------------------------------------------------------------------------------------
PNormSeq00     k                 =     0
PNormSeq01     k                 =     LT(k, n(np)) k + 1                           :F(PNorm01)
               Norm(name, np, k)                                                    :(PNormSeq01)
*---------------------------------------------------------------------------------------------------
PNormOth00     IDENT(t(c(np)[1]), '|')                                              :F(PNormOth10)
               j                 =     0
PNormOth01     j                 =     LT(j, n(c(np)[1])) j + 1                     :F(PNorm01)
               IDENT(t(c(c(np)[1])[j]), '&')                                        :F(PNormOth03)
               k                 =     0
PNormOth02     k                 =     LT(k, n(c(c(np)[1])[j])) k + 1               :F(PNormOth01)
               Norm(name, c(c(np)[1])[j], k)                                        :(PNormOth02)
PNormOth03     Norm(name, c(np)[1], j)                                              :(PNormOth01)
PNormOth10     IDENT(t(c(np)[1]), '&')                                              :F(PNormOth20)
               k                 =     0
PNormOth11     k                 =     LT(k, n(c(np)[1])) k + 1                     :F(PNorm01)
               Norm(name, c(np)[1], k)                                              :(PNormOth11)
PNormOth20     Norm(name, np, 1)                                                    :(PNorm01)
PNormEnd
*---------------------------------------------------------------------------------------------------
               DEFINE('PPure()i,name,n,np,p')                                       :(PPureEnd)
PPure          i                 =     0
PPure1         i                 =     LT(i, n(bnf)) i + 1                          :F(RETURN)
               DIFFER(c(bnf)[i])                                                    :F(error)
               IDENT(t(bnf), 'productions')                                         :F(error)
               IDENT(t(c(bnf)[i]), 'bnf_production')                                :F(error)
               IDENT(t(c(c(bnf)[i])[1]), 'identifier')                              :F(error)
               np                =     c(c(bnf)[i])[2]
               name              =     v(c(c(bnf)[i])[1])
               t(np)             POS(0) '?' RPOS(0)                                 :S(PPureOpt0)
               t(np)             POS(0) ANY('*+,') RPOS(0)                          :F(PPure1)
               sName             =     IDENT(t(c(np)[1]), 'identifier') v(c(np)[1])
               sName             =     DIFFER(t(c(np)[1]), 'identifier') name '$' 0
               p                 =     tree('bnf_production',, 2, ARRAY('1:2'))
               c(p)[1]           =     tree('identifier', sName)
               c(p)[2]           =     c(np)[1]
               IDENT(t(np), '*')                                                    :S(PPureStr)
               IDENT(t(np), '+')                                                    :S(PPurePls)
               IDENT(t(np), ',')                                                    :S(PPureLst)
PPureOpt0      n                 =     c(np)[1]
               DIFFER(t(n), '|')                                                    :F(PPureOpt1)
               p                 =     tree('|',, 1, ARRAY('1:1'))
               c(p)[1]           =     n
               n                 =     p
PPureOpt1      c(c(bnf)[i])[2]   =     Prepend(n, tree('epsilon'))                  :(PPure1)
PPureStr       n                 =     tree('|',, 2, ARRAY('1:2'))
               c(n)[1]           =     tree('epsilon')
               c(n)[2]           =     tree('&',, 2, ARRAY('1:2'))
               c(c(n)[2])[1]     =     tree('identifier', name)
               c(c(n)[2])[2]     =     tree('identifier', sName)                    :(PPure8)
PPurePls       n                 =     tree('|',, 2, ARRAY('1:2'))
               c(n)[1]           =     tree('identifier', sName)
               c(n)[2]           =     tree('&',, 2, ARRAY('1:2'))
               c(c(n)[2])[1]     =     tree('identifier', name)
               c(c(n)[2])[2]     =     tree('identifier', sName)                    :(PPure8)
PPureLst       n                 =     tree('|',, 2, ARRAY('1:2'))
               c(n)[1]           =     tree('identifier', sName)
               c(n)[2]           =     tree('&',, 3, ARRAY('1:3'))
               c(c(n)[2])[1]     =     tree('identifier', name)
               c(c(n)[2])[2]     =     tree('string', "','")
               c(c(n)[2])[3]     =     tree('identifier', sName)                    :(PPure8)
PPure8         DIFFER(t(c(np)[1]), 'identifier')                                    :F(PPure9)
               Insert(bnf, p, i + 1)
PPure9         c(c(bnf)[i])[2]   =     n                                            :(PPure1)
PPureEnd
