*---------------------------------------------------------------------------------------------------------------
-INCLUDE 'case.inc'
-INCLUDE 'datetime.inc'
-INCLUDE 'splitname.inc'
*---------------------------------------------------------------------------------------------------------------
               SSINIENV                 =   TABLE()
               SSINIENV['SNOBOL4']      =   'SNOBOL4'
               SSINIENV['SourceSafe']   =   'SourceSafe'
               SSINIENV['TakeControl']  =   'TakeControl'

               SSDIR                =   TABLE()
               SSDIR['SNOBOL4']     =   '//AusDcx01/Source/SNOBOL4'
               SSDIR['SourceSafe']  =   '//AusDcx01/Source/SourceSafe'
               SSDIR['TakeControl'] =   '//AusDcx01/Source/TakeControl'

               db        =   POS(0) ('SNOBOL4' | 'SourceSafe' | 'TakeControl') . ssDB RPOS(0)
               curprj    =   POS(0) ('$/' ARB) . ssCurPrj RPOS(0)
               ssSwitch  =   POS(0) '-vd' ARB . ssVerDate RPOS(0)
*---------------------------------------------------------------------------------------------------------------
               DEFINE('SSError(n)')                                                                :(SSErrorEnd)
SSError        SSError        =    .END
               auditLog       =    Datetime() '   ss: unexpected error: ' n
               OUTPUT         =    auditLog                                                         :(NRETURN)
SSErrorEnd
*---------------------------------------------------------------------------------------------------------------
               DEFINE('SSDateTime(datetime)ampm,dd,hh,mm,mo,ss,yy,yyyy')                           :(SSDateTimeEnd)
SSDateTime     datetime       =   IDENT(datetime) Datetime()
               datetime       POS(0) int . yyyy '/' int . mo '/' int . dd
+                             ' '    int . hh ':' int . mm
+                             (':' int . ss | epsilon) RPOS(0)                                     :F(SSError(10))
               ampm           =   LT(hh, 12) 'a'
               ampm           =   GE(hh, 12) 'p'
               hh             =   GT(hh, 12) hh - 12
               hh             =   EQ(hh, 0) '12'
               yy             =   SUBSTR(yyyy, 3, 2)
               SSDateTime     =   mo '/' dd '/' yy ';' hh ':' mm ampm                              :(RETURN)
SSDateTimeEnd
*---------------------------------------------------------------------------------------------------------------
               DEFINE('SS(ssNm,ssCmd,ssArgs)line,noecho,silent,sysout')
               ssLogDate      =   DATE()
               ssLogDate      =   SUBSTR(ssLogDate, 10, 2)
+                                 SUBSTR(ssLogDate, 13, 2)
+                                 SUBSTR(ssLogDate, 16, 2)
               ssLogFile      =   'sslog' ssLogDate '.txt'                                         :(SSEnd)
SS             ssCmd          POS(0) '@' . silent =                                                :S(SS)
               ssCmd          POS(0) '-' . noecho =                                                :S(SS)
               auditLog       =   Datetime() ' % ss ' ssCmd ' ' ssArgs
               OUTPUT         =   IDENT(silent) auditLog
               IDENT(testing)                                                                      :F(RETURN)
               ssCmd          =   ssCmd ' "-o&' ssLogFile '"'
               ssCmd          =   SSDIR[ssNm] '/win32/ss ' ssCmd ' ' ssArgs
               INPUT(.sysout, 9, '!!' ssCmd)                                                       :F(SS5)
SS1            line           =   sysout                                                           :F(SS2)
               auditLog       =   Datetime() '   ' line
               OUTPUT         =   IDENT(noecho) auditLog                                           :(SS1)
SS2            ENDFILE(9)
               INPUT(.sysout, 9, ssLogFile)                                                        :F(SS6)
SS3            line           =   sysout                                                           :F(SS4)
               auditLog       =   Datetime() '   ' line
               OUTPUT         =   IDENT(noecho) auditLog
               SS             =   SS line nl                                                       :(SS3)
SS4            ENDFILE(9)
               HOST(1, 'rm -f "' ssLogFile '"')                                                    :(RETURN)
SS5            auditLog       =   Datetime() ' *** Error: execution failed: ' '!!' ssCmd
               OUTPUT         =   auditLog                                                         :(FRETURN)
SS6            IDENT(ssCmd, 'move')                                                                :(RETURN)
               auditLog       =   Datetime() ' *** Error: unable to open log file: ' ssLogFile
               OUTPUT         =   auditLog                                                         :(FRETURN)
SSEnd
*---------------------------------------------------------------------------------------------------------------
               DEFINE('SSoutput(ssResponse)ssline')                                                :(SSoutputEnd)
SSoutput       ssResponse     POS(0) BREAK(nl) . ssline nl =                                       :F(RETURN)
               auditLog       =     Datetime() '   ' ssline
               OUTPUT         =     auditLog                                                       :(SSoutput)
SSoutputEnd
*---------------------------------------------------------------------------------------------------------------
               DEFINE('SSadd(ssNm,filenm,comment)ssResponse')                                      :(SSaddEnd)
SSadd          filenm         =   bslash(filenm)
               ssResponse     =   SS(ssNm, '-add', '-c"' comment '" "' filenm '"')
               ssResponse     POS(0) splitname(filenm)[2]                                          :S(RETURN)
               ssResponse     POS(0) 'An item with the name ' splitname(filenm)[2] ' already exists'
               SSoutput(ssResponse)                                                                :(FRETURN)
SSaddEnd
*---------------------------------------------------------------------------------------------------------------
               DEFINE('SScheckin(ssNm,ssFile,comment,options)ssMatch,ssOptionC,ssResponse')
                                                                                                   :(SScheckinEnd)
SScheckin      ssMatch        =   icase(splitname(ssFile)[2])
               ssOptionC      =   IDENT(comment)  '-c-'
               ssOptionC      =   DIFFER(comment) '-c"' comment '"'
               ssResponse     =   SS(ssNm, '-checkin', options ' ' ssOptionC ' "' ssFile '"')
               ssResponse     POS(0) ssMatch                                                       :S(RETURN)
               ssResponse     POS(0) 'File ' ssFile ' has not been changed.'                       :S(RETURN)
               ssResponse     POS(0) 'You do not have file ' ssFile ' currently checked out.'
               SSoutput(ssResponse)                                                                :(FRETURN)
SScheckinEnd
*---------------------------------------------------------------------------------------------------------------
               DEFINE('SScheckout(ssNm,ssFile,options)ssMatch,ssResponse,sysopts')                 :(SScheckoutEnd)
SScheckout     ssNm           POS(0) SPAN('@#-') . sysopts =
               ssMatch        =   icase(splitname(ssFile)[2])
               ssResponse     =   SS(ssNm, sysopts 'checkout', options ' "' ssFile '"')
               ssResponse     POS(0) ssMatch                                                       :S(RETURN)
               ssResponse     POS(0) 'Replacing local copy of ' ssMatch                            :S(RETURN)
               ssResponse     POS(0) 'Invalid DOS path: '
               ssResponse     POS(0) 'File ' ssMatch ' is checked out by '
               ssResponse     POS(0) 'You currently have file ' ssMatch ' checked out.'
               SSoutput(ssResponse)                                                                :(FRETURN)
SScheckoutEnd
*---------------------------------------------------------------------------------------------------------------
               DEFINE('SScp(ssNm,ssProj)ssPProj,ssResponse')                                       :(SScpEnd)
SScp           IDENT(ssProj, ssCurPrj)                                                             :S(RETURN)
               ssProj         =   IDENT(ssProj, '$') '$/'
               ssResponse     =   SS(ssNm, '-cp', '"' ssProj '"')                                  :F(SSError(20))
               IDENT(testing)                                                                      :F(RETURN)
               ssResponse     POS(0) 'Current project is ' ssProj                                  :S(SScp_2)
               ssResponse     POS(0) 'File or project "' ssProj '" does not exist'                 :S(SScp_3)F(SScp_3)
SScp_2         ssCurPrj       =   ssProj                                                           :(RETURN)
SScp_3         ssPProj        =   splitname(ssProj)[1]
               SScp(ssNm, ssPProj)                                                                 :F(SSError(30))
               SScreate(ssNm, ssProj, '-s -c-')                                                    :(RETURN)
SScp_4         SSoutput(' *** Error: Unrecognized response: ' ssResponse)                          :(FRETURN)
SScpEnd
*---------------------------------------------------------------------------------------------------------------
               DEFINE('SScreate(ssNm,ssProj,options)ssResponse')                                   :(SScreateEnd)
SScreate       ssResponse     =   SS(ssNm, '-create', options ' "' ssProj '"')
               ssResponse     POS(0) ssProj nl RPOS(0)                                             :S(RETURN)
               ssResponse     POS(0) ssProj nl 'Setting current project to ' ssProj                :F(SScreate9)
               ssCurPrj       =   ssProj                                                           :(RETURN)
SScreate9      SSoutput(ssResponse)                                                                :(FRETURN)
SScreateEnd
*---------------------------------------------------------------------------------------------------------------
               DEFINE('SSdestroy(ssNm,ssFile,options)ssResponse,sysopts')                          :(SSdestroyEnd)
SSdestroy      ssNm           POS(0) SPAN('@#-') . sysopts =
               ssResponse     =   SS(ssNm, sysopts 'destroy', options ' "' ssFile '"')
               SSoutput(ssResponse)                                                                :(RETURN)
SSdestroyEnd
*---------------------------------------------------------------------------------------------------------------
               DEFINE('SSdiff(ssNm,ssFile,filenm,options)ssextra,ssResponse,sysopts')              :(SSdiffEnd)
SSdiff         ssNm           POS(0) SPAN('@#-') . sysopts =
               ssextra        =   DIFFER(filenm) ' "' filenm '"'
               ssResponse     =   SS(ssNm, sysopts 'diff', options ' "' ssFile '"' ssextra)
               ssResponse     POS(0)
+                             'Diffing: ' ssFile nl
+                             'Against: ' BREAK(nl) nl
+                             nl
+                             'No differences.'                                                    :S(RETURN)
               SSoutput(ssResponse)                                                                :(FRETURN)
               auditLog       =   Datetime() '   Diffing: ' ssFile nl
+                                 Datetime() '   Against: ' filenm nl
+                                 Datetime() nl
+                                 Datetime() '   The files are different.'
               OUTPUT         =   auditLog                                                         :(FRETURN)
SSdiffEnd
*---------------------------------------------------------------------------------------------------------------
               DEFINE('SSget(ssNm,ssFile,ver,options)ssResponse,sysopts')                          :(SSgetEnd)
SSget          ssNm           POS(0) SPAN('@#-') . sysopts =
               options        =   DIFFER(ver) options ' -v' ver
               ssResponse     =   SS(ssNm, sysopts 'get', options ' "' ssFile '"')
               ssResponse     POS(0) splitname(ssFile)[2]                                          :S(RETURN)
               ssResponse     POS(0) 'Getting ' splitname(ssFile)[2]                               :S(RETURN)
               ssResponse     POS(0) 'Replacing local copy of ' splitname(ssFile)[2]               :S(RETURN)
               SSoutput(ssResponse)                                                                :(FRETURN)
SSgetEnd
*---------------------------------------------------------------------------------------------------------------
               DEFINE('SSlabel(ssNm,ssFile,comment,label)ssResponse')                              :(SSlabelEnd)
SSlabel        ssResponse     =   SS(ssNm, 'label', '-l"' label '" -c"' comment '" "' ssFile '"')  :(RETURN)
SSlabelEnd
*---------------------------------------------------------------------------------------------------------------
               DEFINE('SSlinks(ssNm,sspath)ssFile,sslink,ssProj,ssResponse,sysopts')
               $' '           =   SPAN(' ' nl)                                                     :(SSlinksEnd)
SSlinks        ssNm           POS(0) SPAN('@#-') . sysopts =
               sspath         POS(0)
+                             ('$' ARBNO('/' BREAK('/'))) . ssProj
+                             '/' ARBNO(NOTANY('/')) . ssFile
+                             RPOS(0)
               ssResponse     =   SS(ssNm, sysopts 'links', '"' sspath '"')
               ssResponse     POS(0) ssFile ' is not an existing filename or project'              :S(SSlinks9)
SSlinks2       ssResponse     POS(0) RPOS(0)                                                       :S(RETURN)
               ssResponse     POS(0) 'Projects'
+                             $' ' 'that'
+                             $' ' 'file'
+                             $' ' '"' ssFile '"'
+                             $' ' 'is'
+                             $' ' 'in...' nl =                                                    :S(SSlinks2)
               ssResponse     POS(0) ARB '(' ARB
+                             $' ' 'is'
+                             $' ' 'deleted'
+                             $' ' 'in'
+                             $' ' 'this'
+                             $' ' 'project)' nl =                                                 :S(SSlinks2)
               ssResponse     POS(0) '  ' ssProj nl =                                              :S(SSlinks2)
               ssResponse     POS(0) '  ' ARB . sslink nl =                                        :F(SSlinks9)
               SSlinks       =   SSlinks ' "' sslink '"'                                           :(SSlinks2)
SSlinks9       SSoutput(ssResponse)                                                                :(FRETURN)
SSlinksEnd
*---------------------------------------------------------------------------------------------------------------
               DEFINE('SSmove(ssNm,ssfromproj,sstoproj)ssResponse')                                :(SSmoveEnd)
SSmove         ssResponse     =   SS(ssNm, 'move', '"' ssfromproj '" "' sstoproj '"')              :(RETURN)
SSmoveEnd
*---------------------------------------------------------------------------------------------------------------
               DEFINE('SSphysical(ssNm,sspath)ssFile,ssProj,ssResponse,sysopts')                   :(SSphysicalEnd)
SSphysical     ssNm           POS(0) SPAN('@#-') . sysopts =
               sspath         POS(0)
+                             ('$' ARBNO('/' BREAK('/'))) . ssProj
+                             '/' ARBNO(NOTANY('/')) . ssFile
+                             RPOS(0)
               ssResponse     =   SS(ssNm, sysopts 'physical', '"' sspath '"')
               ssResponse     POS(0) icase(ssFile) ' is not an existing filename or project'       :S(SSphysica9)
               ssResponse     POS(0) icase(ssFile) SPAN(' ') LEN(8) . SSphysical nl                :S(RETURN)
SSphysica9     SSoutput(ssResponse)                                                                :(RETURN)
SSphysicalEnd
*---------------------------------------------------------------------------------------------------------------
               DEFINE('SSproperties(ssNm,sspath)ssFile,ssProj,ssResponse')
               digits        =   '0123456789'
               nl            =   CHAR(10)
               SSprops_resp =   POS(0)
+                                'File:  ' *sspath nl
+                                'Type:  ' ('Text' | 'Binary') . sstype nl
+                                'Size:  ' SPAN(digits) ' bytes'
+                                          (SPAN(' ') SPAN(digits) ' lines' | '') nl
+                                'Store only latest version:  ' ('No' | 'Yes') nl
+                                'Latest:' SPAN(' ') nl
+                                '  Version:  ' SPAN(digits) SPAN(' ') nl
+                                '  Date:  ' BREAK(nl) nl
+                                'Comment: ' ARB
+                                nl RPOS(0)                                                        :(SSpropertiesEnd)
SSproperties   sspath         POS(0)
+                             ('$' ARBNO('/' BREAK('/'))) . ssProj
+                             '/' ARBNO(NOTANY('/')) . ssFile
+                             RPOS(0)
               ssResponse     =   SS(ssNm, '@-properties', '"' sspath '"')
               ssResponse     POS(0) icase(ssFile) ' is not an existing filename or project'       :S(SSproperties9)
               ssResponse     SSprops_resp                                                         :F(SSproperties9)
               SSproperties  =   RPAD(sstype, 6) ' ' sspath                                        :(RETURN)
SSproperties9  SSoutput(ssResponse)                                                                :(RETURN)
SSpropertiesEnd
*---------------------------------------------------------------------------------------------------------------
               DEFINE('SSrename(ssNm,ssfromproj,sstoname)ssResponse')                              :(SSrenameEnd)
SSrename       ssResponse     =   SS(ssNm, 'rename', '"' ssfromproj '" "' sstoname '"')            :(RETURN)
SSrenameEnd
*---------------------------------------------------------------------------------------------------------------
               DEFINE('SSshare(ssNm,ssProj,ssFile,options)ssResponse')                             :(SSshareEnd)
SSshare        SScp(ssNm, ssProj)
               ssResponse     =   SS(ssNm, '-share', options ' "' ssFile '"')
               ssCurPrj       =
               ssResponse     POS(0) ssProj ':' nl splitname(ssFile)[2]                            :s(RETURN)
               ssResponse     POS(0) ssProj ':' nl 'Getting ' splitname(ssFile)[2]                 :s(RETURN)
               ssResponse     POS(0) ssProj ':' nl
+                             'Invalid DOS path: ' ARB nl
+                             'Sharing it into the current project,'
+                             ' but not Getting it.'
               SSoutput(ssResponse)                                                                :(FRETURN)
SSshareEnd
*---------------------------------------------------------------------------------------------------------------
               DEFINE('SSstatus(ssNm,ssFile)ssResponse')                                           :(SSstatusEnd)
SSstatus       ssResponse     =   SS(ssNm, '@-status', '"' ssFile '"')                             :F(SSError(40))
               IDENT(testing)                                                                      :F(FRETURN)
               ssResponse     POS(0) 'No checked out files found.'                                 :S(RETURN)
               ssResponse     POS(0) ssFile ' is not an existing filename or project'              :S(FRETURN)
               SSoutput(' *** Error: Unrecognized response: ' ssResponse)                          :(FRETURN)
SSstatusEnd
*---------------------------------------------------------------------------------------------------------------
               DEFINE('SSuncheckout(ssNm,ssFile,options)ssResponse')                               :(SSuncheckoutEnd)
SSuncheckout   ssResponse     =   SS(ssNm, '-uncheckout', options ' "' ssFile '"')                 :(RETURN)
               ssResponse     POS(0) splitname(ssFile)[2]                                          :S(RETURN)
               SSoutput(ssResponse)                                                                :(RETURN)
SSuncheckoutEnd
*---------------------------------------------------------------------------------------------------------------
               DEFINE('SSworkfold(ssNm,ssProj,dirnm)ssResponse,sysopts')
               workfolds      =   TABLE()                                                          :(SSworkfoldEnd)
SSworkfold     ssNm           POS(0) SPAN('@#-') . sysopts =
               dirnm          =   bslash(dirnm)
               ssProj         =   IDENT(ssProj, '$') '$/'
               DIFFER(workfolds[ssNm ':' ssProj], dirnm)                                           :F(RETURN)
               ssResponse     =   SS(ssNm, sysopts 'workfold', '"' ssProj '" "' dirnm '"')
               IDENT(testing)                                                                      :F(SSworkfol9)
               ssResponse     POS(0) dirnm
+                             ' has been established as the working folder'
+                             ' for project ' ssProj                                               :S(SSworkfol9)
               ssResponse     POS(0) 'File or project not found'
               SSoutput(ssResponse)                                                                :(FRETURN)
SSworkfol9     workfolds[ssNm ':' ssProj] = dirnm                                                  :(RETURN)
SSworkfoldEnd
