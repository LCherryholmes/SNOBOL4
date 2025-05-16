*---------------------------------------------------------------------------------------------------
* Semantic building routines. These functions are called while building the parser
* patterns, not during pattern matching.
*---------------------------------------------------------------------------------------------------
               DEFINE('shift(p,t)')
               DEFINE('reduce(t,n)')
               OPSYN('~', 'shift', 2)
               OPSYN('&', 'reduce', 2)
               DEFINE('pop()')
               DEFINE('nPush()')
               DEFINE('nInc()')
               DEFINE('nDec()')
               DEFINE('nTop()')
               DEFINE('nPop()')                                                  :(semanticEnd)
*---------------------------------------------------------------------------------------------------
shift          shift          =  EVAL("p . thx . *Shift('" t "', thx)")          :(RETURN)
reduce         reduce         =  EVAL("epsilon . *Reduce(" t ", " n ")")         :(RETURN)
pop            pop            =  epsilon . *Pop(.dummy)                          :(RETURN)
*---------------------------------------------------------------------------------------------------
nPush          nPush          =  epsilon . *PushCounter()                        :(RETURN)
nInc           nInc           =  epsilon . *IncCounter()                         :(RETURN)
nDec           nDec           =  epsilon . *DecCounter()                         :(RETURN)
nTop           nTop           =  TopCounter()                                    :(RETURN)
nPop           nPop           =  epsilon . *PopCounter()                         :(RETURN)
*---------------------------------------------------------------------------------------------------
semanticEnd
