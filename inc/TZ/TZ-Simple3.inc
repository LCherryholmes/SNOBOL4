            LBRACE                              =  '{'
            RBRACE                              =  '}'
            Input                               =  *MatchedBraces $' ' RPOS(0)
            MatchedBraces                       =  *LBRACE !*MatchedBraces *RBRACE
