            Input                               =  *MatchedBraces $' ' RPOS(0)
            MatchedBraces                       =  $'{' !*MatchedBraces $'}'
