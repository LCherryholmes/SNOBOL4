*-------------------------------------------------------------------------------------------------------------------------
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserDefs()')                                                             :(UserDefsEnd)
UserDefs    u                 =     0
            usr               =     ARRAY('1:32')
            doDebug           =     4
            doDebugAfter1st   =     FALSE
            doInclWhite       =     FALSE
            doInclNL          =     TRUE
            doReportFileName  =     FALSE
            doRemember        =     TRUE
            fndExt            =     ('dsp' | 'DSP') . extc
            fndCmd            =     'C:/mksnt/find C:/SNOBOL4 -name "*.ksh.out" -print'
            fndSpecific       =     'C:/SNOBOL4/script_report_test_wait_event2.ksh.out'
            fndExclude        =
            keyint            =     ('?') . tx
            keyword           =     'CAT SUB' . tx
            space             =     SPAN(' ')
            whitespace        =     SPAN(' ')

-INCLUDEE 'Stat.inc'
                                                                                             :(RETURN)
UserDefsEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserRpt()')                                                              :(UserRptEnd)
UserRpt                                                                                      :(RETURN)
UserRptEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserFinal()')                                                            :(UserFinalEnd)
UserFinal                                                                                    :(RETURN)
UserFinalEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserTokens()')                                                           :(UserTokensEnd)
UserTokens
            tok[t = t + 1] = token(,, .statParse)
            tok[t = t + 1] = token(,, .statHeader)
            tok[t = t + 1] = token(,, .statSubLine)
            tok[t = t + 1] = token(,, .statCatLine)
            tok[t = t + 1] = token(,, .statFooter)
            tok[t = t + 1] = token(,, .statDateTime)
            tok[t = t + 1] = token(,, .statId)
                                                                                             :(RETURN)
UserTokensEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
