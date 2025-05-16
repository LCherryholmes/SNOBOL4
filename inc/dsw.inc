*-------------------------------------------------------------------------------------------------------------------------
              DATA('project('
+                     'project_name,'
+                     'project_dsppath,'
+                     'project_ssproj,'
+                     'project_ssphysical,'
+                     'project_wfpath,'
+                     'project_dependents'
+                  ')')
*-------------------------------------------------------------------------------------------
              dspProjNodePat =    SPAN(digits ' ' &UCASE '_' &LCASE)
              dspPathPat     =   '.' bs ARBNO(*dspProjNodePat ('.' *dspProjNodePat | epsilon) bs) *dspProjNodePat '.dsp'
              wfPathPat      =   '.' bs ARBNO(*dspProjNodePat ('.' *dspProjNodePat | epsilon) bs) *dspProjNodePat
              ssProjPat      =   '$' '/' ARBNO(*dspProjNodePat ('.' *dspProjNodePat | epsilon) '/') *dspProjNodePat
              ssPhysicalPat  =    LEN(8)
              eol            =    nl @dswOfs
*-------------------------------------------------------------------------------------------
              dswParse =
+             (
+                'Microsoft Developer Studio Workspace File, Format Version ' integer '.00' eol
+                '# WARNING: DO NOT EDIT OR DELETE THIS WORKSPACE FILE!' eol
+                '' . *assign(.dswWorkSpace, *TABLE()) eol
+                ARBNO(
+                   '###############################################################################' eol
+                   '' eol
+                   'Project: ' '"' *dspProjNodePat . proj_name '"' '=' (epsilon | '"') *dspPathPat . proj_dsppath (epsilon | '"') ' - Package Owner=<4>' eol
+                   '' eol
+                   'Package=<5>' eol
+                   '{{{' eol
+                   '    ' 'begin source code control' eol
+                   '    ' '"' *ssProjPat . proj_ssproj '"' ',' (' ' | epsilon) (*ssPhysicalPat | epsilon) . proj_ssphysical eol
+                   '    ' *wfPathPat . proj_wfpath eol
+                   '    ' 'end source code control' eol
+                   '}}}' eol
+                   '' eol
+                   'Package=<4>' eol
+                   '{{{' eol
+                   ARBNO(
+                      '    ' 'Begin Project Dependency' eol
+                      '    ' 'Project_Dep_Name ' *dspProjNodePat eol
+                      '    ' 'End Project Dependency' eol
+                   )
+                   '}}}' eol
+                   '' . *assign(.dswWorkSpace[lwr(proj_name)], *project(proj_name, proj_dsppath, proj_ssproj, proj_ssphysical, proj_wfpath)) eol
+                )
+                '###############################################################################' eol
+                '' eol
+                'Global:' eol
+                '' eol
+                'Package=<5>' eol
+                '{{{' eol
+                (
+                   '    ' 'begin source code control' eol
+                   '    ' '"' *ssProjPat '"' ',' (' ' | epsilon) (*ssPhysicalPat | epsilon) eol
+                   '    ' (*wfPathPat | '.') eol
+                   '    ' 'end source code control' eol
+                |  epsilon
+                )
+                '}}}' eol
+                '' eol
+                'Package=<3>' eol
+                '{{{' eol
+                '}}}' eol
+                '' eol
+                '###############################################################################' eol
+                '' eol
+             )
*-------------------------------------------------------------------------------------------
              dswGenerate =
+             *(
+                'Microsoft Developer Studio Workspace File, Format Version 6.00' nl
+                '# WARNING: DO NOT EDIT OR DELETE THIS WORKSPACE FILE!' nl
+                '' nl
+                export_table(dswWorkSpace, .dummy, .p, *(
+                   '###############################################################################' nl
+                   '' nl
+                   'Project: ' '"' project_name(p) '"' '=' project_dsppath(p) ' - Package Owner=<4>' nl
+                   '' nl
+                   'Package=<5>' nl
+                   '{{{' nl
+                   '    ' 'begin source code control' nl
+                   '    ' '"' project_ssproj(p) '"' ',' ' ' project_ssphysical(p) nl
+                   '    ' project_wfpath(p) nl
+                   '    ' 'end source code control' nl
+                   '}}}' nl
+                   '' nl
+                   'Package=<4>' nl
+                   '{{{' nl
+                   export_list(project_dependents(p), .pdn, *(
+                      '    ' 'Begin Project Dependency' nl
+                      '    ' 'Project_Dep_Name ' pdn nl
+                      '    ' 'End Project Dependency' nl
+                   ))
+                   '}}}' nl
+                   '' nl
+                ))
+                '###############################################################################' nl
+                '' nl
+                'Global:' nl
+                '' nl
+                'Package=<5>' nl
+                '{{{' nl
+                '}}}' nl
+                '' nl
+                'Package=<3>' nl
+                '{{{' nl
+                '}}}' nl
+                '' nl
+                '###############################################################################' nl
+                '' nl
+             )
*-------------------------------------------------------------------------------------------
              DEFINE('DswPos(dswOfs,dswMap)i')                                       :(DswPosEnd)
DswPos        i               =    dswOfs
DswPos1       i               =    IDENT(dswMap[i]) i - 1                            :s(DswPos1)
              DswPos          =    'Line: ' dswMap[i] ' Position: ' dswOfs - i + 1   :(RETURN)
DswPosEnd
*-------------------------------------------------------------------------------------------
              DEFINE('DswRead(dswFileName)dswFile,dswMap,dswOfs,dswWorkSpace')       :(DswReadEnd)
DswRead       dswFile         =    Read(dswFileName, .dswMap)                        :f(DswReadErr1)
              dswFile         POS(0) dswParse RPOS(0)                                :f(DswReadErr2)
              DswRead         =    dswWorkSpace                                      :(RETURN)
DswReadErr1   OUTPUT          =    'Error: unable to open input file: ' dswFileName  :(FRETURN)
DswReadErr2   OUTPUT          =    'Error: unable to parse file: ' dswFileName
              OUTPUT          =    DswPos(dswOfs, dswMap)                            :(FRETURN)
DswReadEnd
*-------------------------------------------------------------------------------------------
              DEFINE('DswWrite(dswFileName,dswWorkSpace)dswFile')                    :(DswWriteEnd)
DswWrite      dswFile         =    EVAL(dswGenerate)                                 :f(DswWriteErr1)
              Write(dswFileName, dswFile)                                            :s(RETURN)f(DswWriteErr2)
DswWriteErr1  OUTPUT          =    'Error: unable to generate file: ' dswFileName    :(FRETURN)
DswWriteErr2  OUTPUT          =    'Error: unable to open output file: ' dswFileName :(FRETURN)
DswWriteEnd
*-------------------------------------------------------------------------------------------
              DEFINE('Dependents(wsTbl,workDir)wsArr,arry,deps,dsp_in,dsp_infn,dsp_line,i,j,libs,list,nm,p')
              digits         =    '0123456789'
              dspIdent       =    ANY(&UCASE &LCASE '_') (SPAN(&UCASE &LCASE '_' digits) | '')
              dspAddLink32   =    POS(0) '# ADD LINK32 ' REM . libs
                                                                                     :(DependentsEnd)
Dependents    wsArr          =    SORT(wsTbl, 1)                                     :f(FRETURN)
Dependents1   i              =    i + 1
              p              =    wsArr[i, 2]                                        :f(RETURN)
              libs           =
              list           =
              arry           =
              deps           =
              dsp_infn       =    project_dsppath(p)
              dsp_infn       POS(0) '.' bs =
              dsp_infn       =    workDir bs dsp_infn
              INPUT(.dsp_in,  10, dsp_infn)                                          :f(Dependents90)
Dependents10  dsp_line       =    dsp_in                                             :f(Dependents11)
              dsp_line       dspAddLink32                                            :f(Dependents10)
              ENDFILE(10)                                                            :(Dependents14)
Dependents11  ENDFILE(10)                                                            :(Dependents1)
Dependents14  list           =    TABLE()
Dependents15  libs           '"' ARB '"' =                                           :s(Dependents15)
              libs           (dspIdent . nm icase('.lib')) =                         :f(Dependents20)
              DIFFER(wsTbl[lwr(nm)])                                                 :f(Dependents15)
              nm             =    project_name(wsTbl[lwr(nm)])
              list[nm]       =    1                                                  :(Dependents15)
Dependents20  DIFFER(list)                                                           :f(Dependents1)
              arry           =    SORT(list)
              DIFFER(arry)                                                           :f(Dependents1)
              j              =    0
Dependents25  j              =    j + 1
              dep            =    arry[j, 1]                                         :f(Dependents30)
              deps           =    IDENT(deps) dep                                    :s(Dependents25)
              deps           =    deps ',' dep                                       :(Dependents25)
Dependents30  project_dependents(p) = deps                                           :(Dependents1)
Dependents90  OUTPUT         =    'i/o error: ' dsp_infn                             :(END)
DependentsEnd
*-------------------------------------------------------------------------------------------
              DEFINE('DepthFirst(wsTbl,ordedTbl,this)dep,deps')                      :(DepthFirstEnd)
DepthFirst    deps           =    project_dependents(wsTbl[lwr(this)])
DepthFirst1   deps           POS(0) RPOS(0)                                          :s(DepthFirst2)
              deps           POS(0) ARB . that (',' | RPOS(0)) =                     :f(xerr)
              DepthFirst(wsTbl, ordedTbl, that)                                      :(DepthFirst1)
DepthFirst2   IDENT(ordedTbl[lwr(this)])                                             :f(RETURN)
              ordedTbl[lwr(this)] = wsTbl[lwr(this)]                                 :(RETURN)
DepthFirstEnd
*----------------------------------------------------------------------------------------------------------
