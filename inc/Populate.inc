*---------------------------------------------------------------------------------------------------
            DEFINE('Populate(fold,idpat,keywords,reswords,special,operators)op,peel,w')      :(PopulateEnd)
Populate    peel              =     POS(0) (BREAK(' ') . w ' ' | (LEN(1) RTAB(0)) . w)
Populate10  keywords          peel =                                                         :F(Populate20)
            $w                =     $' ' APPLY(fold, 2, idpat, w)                            :(Populate10)
Populate20  reswords          peel =                                                         :F(Populate30)
            $w                =     $' ' APPLY(fold, 2, idpat, w)                            :(Populate20)
Populate30  special           peel =                                                         :F(Populate40)
            $w                =     EQ(doParseTree, TRUE)  $' ' TZ(2, w, w ~ 'op')
            $w                =     EQ(doParseTree, FALSE) $' ' TZ(2, w, w)                  :(Populate30)
Populate40  operators         peel =                                                         :F(Populate50)
            op                =     EQ(doParseTree, TRUE)  w ~ 'op'
            op                =     EQ(doParseTree, FALSE) w
            $w                =     $' ' TZ(2, w, op)
            operator          =     DIFFER(operator) operator | op                           :S(Populate40)
            operator          =     IDENT(operator) op                                       :(Populate40)
Populate50                                                                                   :(RETURN)
PopulateEnd
