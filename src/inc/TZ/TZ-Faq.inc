            MailFile                            =  !%*MailMessage $' ' RPOS(0)
            MailMessage                         =  %(*SUBJECT | *FROM | *DATE) !%*BODY *END
            EOL                                 =  nl | cr | cr nl
            TWOEOLS                             =  (nl | cr nl) *EOL | cr cr ANY(nl)
            NOT_EOL                             =  NOTANY(nl cr)
            SUBJECT                             =  %*NOT_EOL
            FROM                                =  %*NOT_EOL
            DATE                                =  %*NOT_EOL
            BODY                                =  !%(NOTANY(nl cr '')) *EOL
            END                                 =  ''
