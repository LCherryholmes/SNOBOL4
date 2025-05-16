*---------------------------------------------------------------------------------------------------
* Provide SPITBOL input/output semantics within SNOBOL4 programs.
* Make INPUT() and OUTPUT() functions still accessible.
* Map INPUT() and OUTPUT() functions to the following user defined functions.
* The recognition and interpretation of the options is incomplete.
*---------------------------------------------------------------------------------------------------
               IsSnobol4()                                                          :F(io_end)
               DEFINE('input_(name,channel,fileName)bch,cmd,maxreclen,opts,options')
               DEFINE('output_(name,channel,fileName)bch,cmd,maxreclen,opts,options')
               OPSYN('input__', 'INPUT')
               OPSYN('output__', 'OUTPUT')
               OPSYN('INPUT', 'input_')
               OPSYN('OUTPUT', 'output_')
               ioFileOptDash  =  (  '-l'
+                                   SPAN(digits) . maxreclen . *assign(.options, *(options maxreclen))
+                                |  '-m' SPAN(digits)
+                                |  '-a' . *assign(.options, *(options 'a'))
+                                |  '-w' . *assign(.options, *(options 'w'))
+                                )
               ioFileOptList  =  *ioFileOptDash (SPAN(' ,') *ioFileOptList | epsilon)
               ioFileOptPat   =  '[' *ioFileOptList ']'
               ioFileOptPat0  =  *ioFileOptPat | epsilon
               ioCmdDlmtPat1  =  LEN(1) $ bch BREAK(*bch) . cmd *bch
               ioCmdDlmtPat2  =  LEN(1) REM . cmd                                   :(io_end)
input_         io             =  .input__                                           :(io)
output_        io             =  .output__                                          :(io)
io             fileName       POS(0) '!' ioCmdDlmtPat1 ioFileOptPat0 = '|' cmd      :S(io1)
               fileName       POS(0) '!' ioCmdDlmtPat2 = '|' cmd                    :S(io1)
               fileName       ioFileOptPat =                                        :S(io1)
io1            options        =  IDENT(maxreclen) options 1024
               APPLY(io, name, channel, options, fileName)                          :S(RETURN)F(FRETURN)
io_end
