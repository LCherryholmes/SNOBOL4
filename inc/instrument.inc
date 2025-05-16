*---------------------------------------------------------------------------------------------------
            DEFINE('Xinstr(x)c,t')                                                           :(XinstrEnd)
Xinstr      DIFFER(x)                                                                        :F(RETURN)
Xinstr10    IDENT(t(x), 'bnf_production')                                                    :F(Xinstr20)
            prodNm            =     v(c(x)[1])
            prodNm            POS(0) ('expression' | 'search_condition')                     :F(RETURN)
            subSeq            =     c(x)[2]
            IDENT(t(subSeq), '&')                                                            :F(RETURN)
            IDENT(t(c(subSeq)[2]), '*')                                                      :F(RETURN)
            c                 =     ARRAY('1:5')
            c[1]              =     tree('&nPush', 'nPush!')
            c[2]              =     c(subSeq)[1]
            c[3]              =     tree('*',, 1, ARRAY('1:1'))
            c(c[3])[1]        =     tree('&',, 2, ARRAY('1:2'))
            c(c(c[3])[1])[1]  =     c(c(subSeq)[2])[1]
            c(c(c[3])[1])[2]  =     tree('&nInc', 'nInc!')
            c[4]              =     tree('&reduce',, 2, ARRAY('1:2'))
            c(c[4])[1]        =     tree('string', "'~'")
            c(c[4])[2]        =     tree('string', "'*(GT(nTop(), 0) (2 * nTop() + 1))'")
            c[5]              =     tree('&nPop', 'nPop!')
            n(c(x)[2])        =     5
            c(c(x)[2])        =     c                                                        :(FRETURN)
Xinstr20    IDENT(t(x), '&')                                                                 :F(Xinstr30)
            c                 =     ARRAY('1:2')
            c[1]              =     tree('string', "'&'")
            c[2]              =     tree('string', n(x))
            Append(x, tree('&reduce',, 2, c))                                                :(RETURN)
Xinstr30    t(x)              POS(0) ANY('*+') . t RPOS(0)                                   :F(Xinstr40)
            c                 =     ARRAY('1:4')
            c[1]              =     tree('&nPush', 'nPush!')
            c[2]              =     tree(t,, 1, ARRAY('1:1'))
            c(c[2])[1]        =     tree('&',, 2, ARRAY('1:2'))
            c(c(c[2])[1])[1]  =     c(x)[1]
            c(c(c[2])[1])[2]  =     tree('&nInc', 'nInc!')
            c[3]              =     tree('&reduce',, 2, ARRAY('1:2'))
            c(c[3])[1]        =     tree('string', "'" t "'")
            c(c[3])[2]        =     tree('string', "'nTop()'")
            c[4]              =     tree('&nPop', 'nPop!')
            t(x)              =     '&'
            n(x)              =     4
            c(x)              =     c
            Visit(c(c(c[2])[1])[1], .Xinstr)                                                 :(FRETURN)
Xinstr40    t(x)              POS(0) ',' . t RPOS(0)                                         :F(RETURN)
            c                 =     ARRAY('1:4')
            c[1]              =     tree('&nPush', 'nPush!')
            c[2]              =     tree(',',, 2, ARRAY('1:2'))
            c(c[2])[1]        =     tree('&',, 2, ARRAY('1:2'))
            c(c(c[2])[1])[1]  =     c(x)[1]
            c(c(c[2])[1])[2]  =     tree('&nInc', 'nInc!')
            c(c[2])[2]        =     c(x)[2]
            c[3]              =     tree('&reduce',, 2, ARRAY('1:2'))
            c(c[3])[1]        =     tree('string', "'" t "'")
            c(c[3])[2]        =     tree('string', "'nTop()'")
            c[4]              =     tree('&nPop', 'nPop!')
            t(x)              =     '&'
            n(x)              =     4
            c(x)              =     c
            Visit(c(c(c[2])[1])[1], .Xinstr)                                                 :(FRETURN)
XinstrEnd
