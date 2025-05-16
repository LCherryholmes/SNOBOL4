            Input                               =  *MatchedBraces !%($nl | $cr) $' ' RPOS(0)
            MatchedBraces                       =  $'{' !*MatchedBraces $'}'
