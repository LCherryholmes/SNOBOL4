*-------------------------------------------------------------------------------------------------------
-INCLUDE 'datetime.inc'
-INCLUDE 'dq.inc'
*------------ --------------------------------------------------------------------- --------------------
              DEFINE('system(verb,args,errName,outFile)'
+                'cmd,cmdLine,errFile,errInfo,line,noCat,noDate,noEcho,silent,stdout,syserr,sysout'
+             )                                                                     :(system_end)
system        verb           POS(0) '@' . silent =                                  :S(system)
              verb           POS(0) '-' . noEcho =                                  :S(system)
              verb           POS(0) '#' . noDate =                                  :S(system)
              verb           POS(0) '!' . noCat  =                                  :S(system)
              cmd            =   DIFFER(exe) exe[verb]
              cmd            =   IDENT(cmd) verb
              cmd            =   dq(cmd)
              auditLog       =   Datetime() ' % ' verb ' ' args
              OUTPUT         =   IDENT(silent) auditLog
              IDENT(testing)                                                        :F(RETURN)
              errFile        =   'stderr-' REPLACE(Datetime(), '/: ', '---') '.txt'
              cmdLine        =   IDENT(timing) 'C:/mksnt/sh -c ' "'" cmd ' ' args ' 2> ' errFile "'"
              cmdLine        =   DIFFER(timing) 'C:/mksnt/sh -c ' '"time ' cmd ' ' args ' 2> ' errFile '"'
              INPUT(.sysout, 9, '!!' cmdLine)                                       :F(FRETURN)
              DIFFER(outFile)                                                       :F(system20)
              OUTPUT(.stdout, 10, outFile)                                          :S(system20)
              auditLog       =   Datetime() '*** system(): Error: "' outFile '" failed to open. -- ' cmd ' ' args
              TERMINAL       =   auditLog
              outFile        =
system20      line           =   sysout                                             :F(system30)
              auditLog       =   Datetime() '   ' line
              OUTPUT         =   IDENT(noEcho) DIFFER(noDate) line
              OUTPUT         =   IDENT(noEcho) IDENT(noDate) auditLog
              system         =   IDENT(noCat) system line nl
              stdout         =   line                                               :(system20)
system30      (DIFFER(outFile) ENDFILE(10))
              ENDFILE(9)
              errInfo        =
              INPUT(.syserr, 11, errFile)                                           :S(system40)
              auditLog       =   Datetime() '*** system(): Error: Unable to open "' errFile '". -- ' cmd ' ' args
              TERMINAL       =   auditLog                                           :(system60)
system40      line           =   syserr                                             :F(system50)
              auditLog       =   Datetime() ' + ' line
              OUTPUT         =   IDENT(noEcho) DIFFER(noDate) line
              OUTPUT         =   IDENT(noEcho) IDENT(noDate) auditLog
              errInfo        =   errInfo line nl                                    :S(system40)
system50      ENDFILE(11)
              HOST(1, 'rm -f "' errFile '"')                                        :F(error)
system60      DIFFER(errName)                                                       :F(RETURN)
              IsType(errName, 'name,string')                                        :F(error)
              $errName       =   errInfo                                            :(RETURN)
system_end
