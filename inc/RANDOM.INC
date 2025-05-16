*---------------------------------------------------------------------------------------------------
* RANDOM(N) will return an integer uniformly
* distributed on 1,2,...,N.  If N=0, it will
* return a real uniformly distributed in the
* interval [0,1).
*---------------------------------------------------------------------------------------------------
        DEFINE('RANDOM(N)')
        RAN_VAR  =  1                   :(RANDOM_END)
RANDOM  RAN_VAR = REMDR(RAN_VAR * 4676, 414971)
        RANDOM  = RAN_VAR / 414971.0
        RANDOM  = NE(N, 0) CONVERT(RANDOM * N, 'INTEGER') + 1
                                        :(RETURN)
RANDOM_END
*---------------------------------------------------------------------------------------------------
* SEED() will use the minutes and seconds to
* seed the pseudo random number generator
*---------------------------------------------------------------------------------------------------
        DEFINE('SEED()')                :(SEED_END)
SEED    DATE() POS(0) BREAK(' ') ' ' BREAK(':') ':' BREAK(':') . RV1 ':' RTAB(0) . RV0
        RAN_VAR =  RV1 * 60 + RV0
                                        :(RETURN)
SEED_END
