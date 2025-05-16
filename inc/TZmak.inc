*-------------------------------------------------------------------------------------------------------------------------
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserDefs()')                                                             :(UserDefsEnd)
UserDefs    u                 =     0
            usr               =     ARRAY('1:32')
            doDebug           =     0
            doDebugAfter1st   =     FALSE
            doInclWhite       =     FALSE
            doInclNL          =     TRUE
            doReportFileName  =     FALSE
            doRemember        =     TRUE
            fndExt            =     ('mak' | 'MAK') . extc
            fndCmd            =     'd:/mksnt/find e:/brazos -name "*.mak" -print'
*           fndSpecific       =     'common/pam/patrolam/pasetup'
            fndExclude        =     (  'common/cgs/cgsgrphs/cgsgbsd/cgsgbsd3.mak'
+                                   |  'common/cgs/cgsgrphs/cgsgrtd/cgsgrtd3.mak'
+                                   |  'ThirdParty/ObjStudio'
+                                   )
            keyint            =     ('?') . tx
            keyword           =     '???' . tx
            space             =     SPAN(' ')
            whitespace        =     SPAN(' ')

            pathNode          =     SPAN(digits &UCASE &LCASE '%-_')

            args              =     (*switch | *pathName | *qqPathName | '"' BREAK('"') '"') (' ' *args | epsilon)
            pathArgs          =     (*pathName | *qqPathName | '"' BREAK('"') '"') (' ' *pathargs | epsilon)
            pathNames0        =     *pathName (' ' *pathNames0 | epsilon)
            pathNames         =     *pathName ' ' *pathName (' ' *pathNames0 | epsilon)
            qqIntDirPathName  =     '"' '$(INTDIR)' (bSlash bSlash | bSlash *pathName) '"'
            qqOutDirPathName  =     '"' '$(OUTDIR)' (bSlash bSlash | bSlash *pathName) '"'
            qqPathName        =     '"' *pathName '"'
            sep               =     (' ' | bSlash nl ' ')
            switches          =     *switch . ts ((*idx . tz . *assign(.OUTPUT, "Lagging " ts tz) ' ' | epsilon) ' ' *switches | epsilon)
            switch            =
+                             (     '/' ('D' | 'd') ' ' ('"' BREAK('"') '"' | *idx '=' *idx)
+                             |     '/' ('F' ANY('Radopr')) *qqPathName
+                             |     '/' 'F' ('As' | ANY('DRr'))
+                             |     '/' 'G' (ANY('3RXZfiz') | 'm' ('-' | epsilon))
+                             |     '/' 'I ' '"' BREAK('"') '"'
+                             |     '/' 'MD' ('d' | epsilon)
+                             |     '/' 'MT' ('d' | epsilon)
+                             |     '/' 'NOENTRY'
+                             |     '/' 'O' (ANY('12dpx') | 'icf' | 'b0')
+                             |     '/' 'W' ANY('1234X')
+                             |     '/' 'X'
+                             |     '/' ('Y' ANY('Xcu')) ('"' BREAK('"') '"' | epsilon)
+                             |     '/' 'Z' '<' *idx '>'
+                             |     '/' 'Z' (ANY('7Ii') | 'p1')
+                             |     '/' 'base:'       ('"' '@' *pathName ',' *idx '"' | '"' BREAK('"') '"' | '@' *pathName ',' *idx)
+                             |     '/' 'c'
+                             |     '/' 'debug'
+                             |     '/' 'def:'         *qqPathName
+                             |     '/' 'dll'
+                             |     '/' 'entry:'       '"' *idx '@' *intx '"'
+                             |     '/' 'export:'      *idx
+                             |     '/' 'fo'           '"' ('$(' *idx ')' bSlash | epsilon) *pathName '"'
+                             |     '/' 'h '           *qqPathName
+                             |     '/' 'i '           (*qqPathName | '"."')
+                             |     '/' 'iid '         *qqPathName
+                             |     '/' 'implib:'      *qqPathName
+                             |     '/' 'incremental:' ('no' | 'yes')
+                             |     '/' 'l '           *hex
+                             |     '/' 'libpath:'     '"' BREAK('"') '"'
+                             |     '/' 'machine:'     ('I386' | 'IX86')
+                             |     '/' 'map'          (':' *qqPathName | ':"' 'FULL' '"' | epsilon)
+                             |     '/' 'nodefaultlib' (':"' BREAK('"') '"' | epsilon)
+                             |     '/' 'nologo'
+                             |     '/' 'out:'         *qqPathName
+                             |     '/' 'o'            (' NUL' | ' "NUL"' | ' ' *qqPathName | epsilon)
+                             |     '/' 'pdb:'         (*qqPathName | 'none')
+                             |     '/' 'pdbtype:'     'sept'
+                             |     '/' 'subsystem:'   ('console' | 'windows')
+                             |     '/' 'stack:'       *hex
+                             |     '/' 'tlb '         *qqPathName
+                             |     '/' 'ut:'          *qqPathName
+                             |     '/' 'win32'        (' "NUL"' | epsilon)
+                             |     '/' 'mktyplib203'
+                             |     '/' 'profile'
+                             |     '/' 'u'
+                             |     '/' 'verbose'
+                             )

            comment           =     '#' BREAK(nl)
            cmpCFG            =     '"$(' 'CFG' ')" ' ('==' | '!=') (bSlash nl | epsilon) ' "' BREAK('"') '"'
            cmpCFG_EQ         =     '"$(' 'CFG' ')" ' '==' ' "' BREAK('"') . CFG '"'
            cmdIF             =     '!IF ' (' ' | epsilon) *cmpCFG ((' && ' | ' || ') *cmpCFG | epsilon)
            cmdIF_CFG_EQ      =     '!IF ' (' ' | epsilon) *cmpCFG_EQ
            cmdIF_CFG_EQ_OR   =     '!IF ' (' ' | epsilon) *cmpCFG_EQ ' || ' *cmpCFG_EQ
            cmdELSEIF         =     '!ELSEIF  ' *cmpCFG
            cmdELSEIF_CFG_EQ  =     '!ELSEIF  ' *cmpCFG_EQ
            cmdELSE           =     '!ELSE' ' '
            cmdENDIF          =     '!ENDIF' ' '
            cmdIF_RECURSE     =     '!' 'IF' ' ' '"$(RECURSE)"' ' ' '==' ' ' '"0"' ' '
            message           =     '!MESSAGE ' BREAK(nl bSlash) bSlash nl BREAK(nl) nl
+                             |     '!MESSAGE ' BREAK(nl) nl
            cntPathname       =     tab '{' '$(INCLUDE)' '}' *qqPathName (' ' | epsilon) bSlash nl
+                             |     tab (*qqIntDirPathName | *qqPathName) (' ' | epsilon) bSlash nl
+                             |     tab *pathName (' ' | epsilon) bSlash nl
            endPathname       =     tab (*qqIntDirPathName | *qqPathName) nl
+                             |     tab *pathName nl
+                             |     tab nl

            flagsBSC32        =     *flagBSC32 FENCE(*sep *flagsBSC32 | epsilon)
            flags2BSC32       =     *flagBSC32 ' ' *flagsBSC32
            flagBSC32         =     '/nologo'
+                             |     '/o' *qqOutDirPathName

            flagsCPP          =     *flagCPP FENCE(*sep *flagsCPP | epsilon)
            flags2CPP         =     *flagCPP ' ' *flagsCPP
            flagCPP           =     '/'
+                             epsilon . *assign(.mak[CFG]['fCPP'], *(IDENT(mak[CFG]['fCPP']) TABLE()))
+                             epsilon . *assign(.val, *("''"))
+                             (     'nologo' . flg
+                             |     'Gz'  . flg
+                             |     'MD'  . flg  FENCE('d' . val | epsilon)
+                             |     'MT'  . flg  FENCE('d' . val | epsilon)
+                             |     'W'   . flg  ANY('1234') . val
+                             |     'GR'  . flg
+                             |     'GX'  . flg
+                             |     'ZI'  . flg
+                             |     'Zi'  . flg
+                             |     'O'   . flg  ANY('1234dp') . val
+                             |     (  'I'   . flg  *sep (*qqPathName | '"."') . val
+                                   |  'D'   . flg  *sep ('"' *idx '"') . val
+                                   |  'D'   . flg  *sep (*idx '=' *idx) . val
+                                   )
+                                   epsilon . *assign(.mak[CFG]['fCPP'][flg], *(IDENT(mak[CFG]['fCPP'][flg]) TABLE()))
+                                   epsilon . *assign(.mak[CFG]['fCPP'][flg][0], *(mak[CFG]['fCPP'][flg][0] + 1))
+                                   epsilon . *assign(.mak[CFG]['fCPP'][flg][mak[CFG]['fCPP'][flg][0]], *val)
+                             |     'Fp'  . flg  *qqIntDirPathName . val
+                             |     'Yc'  . flg  (*qqPathName . val | epsilon)
+                             |     'YX'  . flg  (*qqPathName . val | epsilon)
+                             |     'Yu'  . flg  *qqPathName . val
+                             |     'Fr'  . flg  *qqIntDirPathName . val
+                             |     'Fo'  . flg  *qqIntDirPathName . val
+                             |     'Fd'  . flg  (*qqIntDirPathName | *qqPathName) . val
+                             |     'FD'  . flg
+                             |     'c'   . flg
+                             |     'FR'  . flg  *qqIntDirPathName . val
+                             |     'G'   . flg  ANY('fimsy') . val
+                             |     'ML'  . flg  FENCE('d' . val | epsilon)
+                             |     'MT'  . flg
+                             |     'O'   . flg  FENCE(ANY('itxy') | 'b0' | 'b1') . val
+                             |     'W'   . flg  ANY('X') . val
+                             |     'Zp1' . flg
+                             |     'subsystem' . flg ':' ('console' | 'windows') . val
+                             )
+                             epsilon . *assign(.mak[CFG]['fCPP'][flg], *(IDENT(mak[CFG]['fCPP'][flg]) val))

            flagsLIB32        =     *flagLIB32 FENCE(*sep *flagsLIB32 | epsilon)
            flags2LIB32       =     *flagLIB32 ' ' *flagsLIB32
            flagLIB32         =     '/nologo'
+                             |     '/out:' *qqOutDirPathName
+                             |     '/o' *qqPathName

            flagsLINK32       =     *flagLINK32 FENCE(*sep *flagsLINK32 | epsilon)
            flags2LINK32      =     *flagLINK32 ' ' *flagsLINK32
            flagLINK32        =     '/nologo'
+                             |     '/base:'         ('"' '@' *pathName ',' *idx '"' | '@' *pathName ',' *idx)
+                             |     '/entry:'        '"' *idx '@' *intx '"'
+                             |     '/subsystem:'    ('console' | 'windows')
+                             |     '/dll'
+                             |     '/incremental:'  ('no' | 'yes')
+                             |     '/pdb:'          ('"$(OUTDIR)' bSlash *idx '.pdb"' | *qqOutDirPathName | 'none')
+                             |     '/map:'          ('"$(INTDIR)' bSlash *idx '.map"' | *qqIntDirPathName)
+                             |     '/debug'
+                             |     '/machine:'      ('I386' | 'IX86')
+                             |     '/nodefaultlib'  (':' ('"' *idx '"' | *qqPathName) | epsilon)
+                             |     '/def:'          ('".' bSlash *idx '.def"' | *qqPathName)
+                             |     '/out:'          ('"$(OUTDIR)' bSlash *idx ('.dll' | '.rll') '"' | *qqOutDirPathName)
+                             |     '/implib:'       ('"$(OUTDIR)' bSlash *idx '.lib"' | *qqPathName | *qqOutDirPathName)
+                             |     '/libpath:'      *qqPathName
+                             |     '/export:'       *idx
+                             |     '/pdbtype:'      'sept'
+                             |     '/NOENTRY'

            flagsMIDL         =     *flagMIDL FENCE(*sep *flagsMIDL | epsilon)
            flags2MIDL        =     *flagMIDL ' ' *flagsMIDL
            flagMIDL          =     '/Oicf'
+                             |     '/h' *sep *qqPathName
+                             |     '/iid' *sep *qqPathName

            flagsMTL          =     *flagMTL FENCE(*sep *flagsMTL | epsilon)
            flags2MTL         =     *flagMTL ' ' *flagsMTL
            flagMTL           =     '/nologo'
+                             |     '/D' *sep '"' *idx '"'
+                             |     '/tlb' ' ' *qqOutDirPathName
+                             |     '/mktyplib203'
+                             |     '/o' ' ' '"NUL"'
+                             |     '/win32'

            flagsRSC          =     *flagRSC FENCE(*sep *flagsRSC | epsilon)
            flags2RSC         =     *flagRSC ' ' *flagsRSC
            flagRSC           =     '/l' ' ' *hex
+                             |     '/fo' *qqIntDirPathName
+                             |     '/i' ' ' (*qqPathName | '"."')
+                             |     '/d' ' ' ('"_DEBUG"' | '"NDEBUG"' | '"_AFXDLL"' | '"_USRDLL"')

            setBSC32          =     'BSC32'        '=' *pathName nl
            setBSC32_FLAGS    =     'BSC32_FLAGS'  '=' *flagsBSC32 ' ' nl
            setBSC32_SBRS     =     'BSC32_SBRS'   '=' ' ' bSlash nl ARBNO(*cntPathname) *endPathname
            setCFG            =     'CFG'          '=' BREAK(nl)
            setCPP            =     'CPP'          '=' *pathName nl
            setCPP_OBJS       =     'CPP_OBJS'     '=' *pathDir '/' nl
            setCPP_PROJ       =     'CPP_PROJ'     '=' ('INTDIR' | *idx | *flagsCPP ' ') . CPP_PROJ nl
+                                   epsilon . *assign(.mak[CFG]['CPP_PROJ'], *CPP_PROJ)

            setCPPxPROJ       =    ('CPP_PROJ'     '=' BREAK(nl)) . tx nl
            setCPP_SBRS       =     'CPP_SBRS'     '=' (*pathDir '/' | '.') nl
            setCPP_SWITCHES   =     'CPP_SWITCHES' '=' ('INTDIR' | *idx | *flagsCPP ' ') nl
            setDEF_FILE       =     'DEF_FILE'     '=' ' ' bSlash nl ARBNO(*cntPathname) *endPathname
            setDEP_CPP        =     'DEP_CPP_' *idx '=' bSlash nl ARBNO(*cntPathname) *endPathname
            setDEP_RSC        =     'DEP_RSC_' *idx '=' bSlash nl ARBNO(*cntPathname) *endPathname
            setInputPath      =     'InputPath'    '=' *pathName . InputPath nl
+                                   epsilon . *assign(.mak[CFG]['InputPath'], *InputPath)

            setINTDIR         =     'INTDIR'       '=' *pathDir . INTDIR nl
+                                   epsilon . *assign(.mak[CFG]['INTDIR'], *INTDIR)

            setLIB32          =     'LIB32'        '=' (*pathName ' ' '-' 'lib') . LIB32 nl
+                                   epsilon . *assign(.mak[CFG]['LIB32'], *LIB32)

            setLIB32_FLAGS    =     'LIB32_FLAGS'  '=' *flagsLIB32 . LIB32_FLAGS ' ' nl
+                                   epsilon . *assign(.mak[CFG]['LIB32_FLAGS'], *LIB32_FLAGS)

            setLIB32_OBJS     =     'LIB32_OBJS'   '=' ' ' bSlash nl ARBNO(*cntPathname) *endPathname
            setLINK32         =     'LINK32'       '=' *pathName . LINK32 nl
+                                   epsilon . *assign(.mak[CFG]['LINK32'], *LINK32)

            setLINK32_FLAGS   =     'LINK32_FLAGS' '=' (ARBNO((*pathLeaf | *pathName) *sep) *flagsLINK32 . link32Flags ' ' | *idx) nl
+                                   epsilon . *assign(.mak[CFG]['LINK32_FLAGS'], *link32Flags)

            setLINK32xFLAGS   =    ('LINK32_FLAGS' '=' BREAK(nl)) . tx nl
            setLINK32_OBJS    =     'LINK32_OBJS'  '=' ' ' bSlash nl ARBNO(*cntPathname) *endPathname
            setMTL            =     'MTL'          '=' *pathName . MTL nl
+                                   epsilon . *assign(.mak[CFG]['MTL'], *MTL)

            setMTL_PROJ       =     'MTL_PROJ'     '=' *switches . MTL_PROJ ' ' nl
+                                   epsilon . *assign(.mak[CFG]['MTL_PROJ'], *MTL_PROJ)

            setMTL_SWITCHES   =     'MTL_SWITCHES' '=' *flagsMTL . MTL_SWITCHES ' ' nl
+                                   epsilon . *assign(.mak[CFG]['MTL_SWITCHES'], *MTL_SWITCHES)

            setMTLxSWITCHES   =    ('MTL_SWITCHES' '=' BREAK(nl)) . tx nl
            setNULL           =     'NULL'         '=' ('nul' | epsilon) nl
            setOUTDIR         =     'OUTDIR'       '=' *pathDir . OUTDIR nl
+                                   epsilon . *assign(.mak[CFG]['OUTDIR'], *OUTDIR)

            setRSC            =     'RSC'          '=' *pathName . RSC nl
+                                   epsilon . *assign(.mak[CFG]['RSC'], *RSC)

            setRSC_PROJ       =     'RSC_PROJ'     '=' *flagsRSC . RSC_PROJ ' ' nl
+                                   epsilon . *assign(.mak[CFG]['RSC_PROJ'], *RSC_PROJ)

            setRSCxPROJ       =    ('RSC_PROJ'     '=' BREAK(nl)) . tx nl
            setSOURCE         =     'SOURCE'       '=' *pathName nl
            targetALL         =     'ALL' ' ' ':' ARBNO(' ' (*qqPathName | *qqOutDirPathName)) . ALL nl
+                                   epsilon . *assign(.mak['ALL:'], *ALL)

            targetCLEAN       =     'CLEAN' ' ' ':' nl ARBNO(*actionErase) nl

            targetOUTDIR      =     '"$(OUTDIR)"' ' ' ':' nl
+                                   '    ' 'if' ' ' 'not' ' ' 'exist' ' ' '"$(OUTDIR)/$(NULL)"' ' ' 'mkdir' ' ' '"$(OUTDIR)"' nl
+                                   nl

            targetINTDIR      =     '"$(INTDIR)"' ' ' ':' nl
+                                   '    ' 'if' ' ' 'not' ' ' 'exist' ' ' '"$(INTDIR)/$(NULL)"' ' ' 'mkdir' ' ' '"$(INTDIR)"' nl
+                                   nl

            targetBSC32       =     *qqOutDirPathName ' ' ':' ' ' '"$(OUTDIR)"' ' ' '$(BSC32_SBRS)' nl
+                                   '    ' '$(BSC32)' ' ' '@' '<<' nl
+                                   '  ' '$(BSC32_FLAGS)' ' ' '$(BSC32_SBRS)' nl
+                                   '<<' nl

            targetMIDL        =     *qqPathName ARBNO(tab *qqPathName)
+                                   ' ' ':' ' ' '$(SOURCE)' ' ' '"$(INTDIR)"' ' ' '"$(OUTDIR)"' nl
+                                   tab '<<' *pathName ' ' nl
+                                   tab '@' 'echo' ' ' 'off' ' ' nl
+                                   tab 'midl' ' ' *flagsMIDL ' ' *qqPathName nl
+                                   '<<' ' ' nl

            targetMTL         =     *qqOutDirPathName ' ' ':' ' ' '$(SOURCE)' ' ' '"$(OUTDIR)"' nl
+                                   tab '$(MTL)' ' ' '@' '<<' nl
+                                   '  ' '$(MTL_SWITCHES)' ' ' '$(SOURCE)' nl
+                                   '<<' nl

            targetLIB32       =     *qqOutDirPathName ' ' ':' ' ' '"$(OUTDIR)"' ' ' '$(DEF_FILE)' ' ' '$(LIB32_OBJS)' nl
+                                   '    ' '$(LIB32)' ' ' '@' '<<' nl
+                                   '  ' '$(LIB32_FLAGS)' ' ' '$(DEF_FLAGS)' ' ' '$(LIB32_OBJS)' nl
+                                   '<<' nl

            targetLINK32      =     *qqOutDirPathName ' ' ':' ' ' '"$(OUTDIR)"' ' ' '$(DEF_FILE)' ' ' '$(LINK32_OBJS)' nl
+                                   '    ' '$(LINK32)' ' ' '@' '<<' nl
+                                   '  ' '$(LINK32_FLAGS)' (' ' '$(DEF_FLAGS)' | epsilon) ' ' '$(LINK32_OBJS)' nl
+                                   '<<' nl

            targetCPP         =     *qqIntDirPathName ARBNO(tab *qqIntDirPathName) ' ' ':'
+                                   ' ' '$(SOURCE)' ' ' '"$(INTDIR)"' ARBNO(' ' (*qqPathName | *qqIntDirPathName)) nl
+                                   (  tab '$(CPP)' ' ' '@' '<<' nl
+                                      '  ' '$(CPP_SWITCHES)' ' ' '$(SOURCE)' nl
+                                      '<<' nl
+                                   |  epsilon
+                                   )
+                                   (  tab '$(RSC)' ' ' ('$(RSC_PROJ)' | *flagsRSC) ' ' '$(SOURCE)'
+                                   |  tab '$(CPP)' ' ' '$(CPP_PROJ)' ' ' '$(SOURCE)'
+                                   |  epsilon
+                                   )

            targetRSC         =     *qqOutDirPathName ARBNO(tab *qqOutDirPathName) ' ' ':'
+                                   ' ' '$(SOURCE)'
+                                   ' ' ('$(DEP_RSC_' *idx ')' (bSlash nl | epsilon) ' ' | epsilon)
+                                   '"$(INTDIR)"' nl
+                                   tab '$(RSC)' ' ' ('$(RSC_PROJ)' | *flagsRSC) ' ' '$(SOURCE)' nl

            targetSource      =     *qqIntDirPathName ARBNO(tab *qqIntDirPathName) ' ' ':'
+                                   ' ' '$(SOURCE)'
+                                   ' ' ('$(DEP_CPP_' *idx ')' (bSlash nl | epsilon) ' ' | epsilon)
+                                   '"$(INTDIR)"'
+                                   (' ' *qqPathName | epsilon) nl

            targetIFSource    =     *cmdIF nl nl nl
+                                   *targetSource nl nl
+                                   *cmdELSEIF nl nl nl
+                                   *targetSource nl nl
+                                   *cmdENDIF nl

            targetInferences  =     *targetInference FENCE(*targetInferences | epsilon)
            targetInference   =     (  '.' ('c' | 'cpp' | 'cxx') '{' ('$(INTDIR)' | '$(CPP_OBJS)') '}' '.' 'obj' '::' nl
+                                   |  '.' ('c' | 'cpp' | 'cxx') '{' ('$(INTDIR)' | '$(CPP_SBRS)') '}' '.' 'sbr' '::' nl
+                                   )
+                                   '   ' '$(CPP)' ' ' '@' '<<' nl
+                                   '   ' '$(CPP_PROJ)' ' ' '$' '<' ' ' nl
+                                   '<<' nl nl

            includeDep        =     '!' 'IF' ' ' '"$(NO_EXTERNAL_DEPS)"' ' ' '!=' ' ' '"1"' nl
+                                   '!' 'IF' ' ' 'EXISTS' '(' '"' *idx '.dep"' ')' nl
+                                   '!' 'INCLUDE' ' ' '"' *idx '.dep"' nl
+                                   *cmdELSE nl
+                                   '!MESSAGE ' 'Warning: cannot find "' *idx '.dep"' nl
+                                   *cmdENDIF nl
+                                   *cmdENDIF nl

            actionErase       =     tab '-@' 'erase' ' ' (*qqPathName | *qqIntDirPathName | *qqOutDirPathName) nl

            customMacros      =     '# Begin Custom Macros' nl
+                                   'OutDir' '=' *pathDir nl
+                                   '# End Custom Macros' nl

            headerSection     =     '# Microsoft Developer Studio Generated NMAKE File, Based on ' *idx '.dsp' nl
+                                   *cmdIF nl
+                                   *setCFG nl
+                                   '!MESSAGE ' 'No configuration specified. Defaulting to ' BREAK(nl) nl
+                                   *cmdENDIF nl
+                                   nl
+                                   *cmdIF nl
+                                   '!MESSAGE ' 'Invalid configuration "$(CFG)" specified.' nl
+                                   '!MESSAGE ' 'You can specify a configuration when running NMAKE' nl
+                                   '!MESSAGE ' 'by defining the macro CFG on the command line. For example:' nl
+                                   '!MESSAGE '  nl
+                                   '!MESSAGE ' 'NMAKE /f "' *idx '.mak" CFG="' BREAK('"') '"' nl
+                                   '!MESSAGE '  nl
+                                   '!MESSAGE ' 'Possible choices for configuration are:' nl
+                                   '!MESSAGE '  nl
+                                   ARBNO(*message)
+                                   '!MESSAGE '  nl
+                                   '!ERROR ' 'An invalid configuration is specified.' nl
+                                   *cmdENDIF nl
+                                   nl
+                                   '!' 'IF' ' ' '"$(OS)"' ' ' '==' ' ' '"Windows_NT"' nl
+                                   *setNULL (nl | epsilon)
+                                   *cmdELSE nl
+                                   *setNULL (nl | epsilon)
+                                   *cmdENDIF nl

            makTarget         =     (*setCPP_SWITCHES | epsilon) nl *targetCPP nl nl (nl | epsilon)
+                             |     *setMTL_SWITCHES nl *targetMTL nl nl
+                             |     *setInputPath nl *targetMIDL *endPathname nl

            makBlock          =     *cmdIF_CFG_EQ nl nl
+                                   *makTarget
+                                   *cmdELSEIF_CFG_EQ . bangELSEIF nl nl
+                                   (*makTarget | epsilon)
+                                   *cmdENDIF nl nl

            makBody           =     *setOUTDIR *setINTDIR *customMacros nl
+                                   (  *targetALL nl nl
+                                   |  *cmdIF_RECURSE nl nl
+                                      *targetALL nl
+                                      *cmdELSE nl nl
+                                      *targetALL nl
+                                      *cmdENDIF nl nl
+                                   )
+                                   *targetCLEAN
+                                   *targetOUTDIR
+                                   *targetINTDIR
+                                   (*setCPP | epsilon)
+                                   *setCPP_PROJ (nl | epsilon)
+                                   (*targetInferences | epsilon)
+                                   (*setMTL | epsilon)
+                                   (*setMTL_PROJ | epsilon)
+                                   (*setRSC | epsilon)
+                                   (*setRSC_PROJ | epsilon)
+                                   *setBSC32
+                                   *setBSC32_FLAGS
+                                   *setBSC32_SBRS
+                                   (nl *targetBSC32 nl | epsilon)
+                                   (  *setLINK32
+                                      *setLINK32_FLAGS
+                                      (*setDEF_FILE | epsilon)
+                                      *setLINK32_OBJS nl
+                                      *targetLINK32 nl
+                                   |  *setLIB32
+                                      *setLIB32_FLAGS
+                                      *setLIB32_OBJS nl
+                                      *targetLIB32 nl
+                                   )

            makTop            =     (*setCPP (*setMTL | epsilon) *setRSC nl | epsilon)
+                                   *cmdIF_CFG_EQ nl nl
+                                   epsilon . *assign(.OUTPUT, *('CFG=' CFG))
+                                   epsilon . *assign(.mak[CFG], *(IDENT(mak[CFG]) TABLE()))
+                                   *makBody
+                                   *cmdELSEIF_CFG_EQ nl nl
+                                   epsilon . *assign(.OUTPUT, *('CFG=' CFG))
+                                   epsilon . *assign(.mak[CFG], *(IDENT(mak[CFG]) TABLE()))
+                                   *makBody
+                                   *cmdENDIF nl nl
+                                   (*targetInferences | epsilon) nl
+                                   *includeDep nl nl

            makParse          =     epsilon $ mak . *assign(.mak, *TABLE())
+                                   *headerSection nl
+                                   *makTop
+                                   *cmdIF_CFG_EQ_OR . bangIF nl
+                                   ARBNO(*setSOURCE (nl | epsilon) | *makBlock | *targetCPP nl nl (nl | epsilon))
+                                   nl
+                                   *cmdENDIF nl nl

                                                                                             :(RETURN)
UserDefsEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserRpt()i,makArr')                                                      :(UserRptEnd)
UserRpt     XDump('mak', mak)                                                                :(RETURN)
UserRptEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserTokens()')                                                           :(UserTokensEnd)
UserTokens  tok[t = t + 1] = token(,, .makParse)
            tok[t = t + 1] = token(,, .headerSection)
            tok[t = t + 1] = token(,, .makTop)
            tok[t = t + 1] = token(,, .makBody)
            tok[t = t + 1] = token(,, .makBlock)
            tok[t = t + 1] = token(,  *(SQize(tx) ' nl REM'),
+                               POS(0)
+                               (  '# IBM Developer' "'" 's Workframe/2 Make File Creation run at '
+                                  *intx ':' *intx ':' *intx ' on ' *intx '/' *intx '/' *intx
+                               ) . tx nl REM
+                            )
            tok[t = t + 1] = token(,  *(SQize(tx) ' nl REM'),
+                               POS(0)
+                               (  '#################' . tx nl
+                                  '# ' "'" 'make' "'" ' build parameters' nl
+                                  '#################'
+                               ) nl REM
+                            )
            tok[t = t + 1] = token(,, .customMacros)
            tok[t = t + 1] = token(,  *("'" tx "'"),                ('#' SPAN('#')) . tx)
            tok[t = t + 1] = token(,  *(SQize(tx)),                 *comment . tx)
            tok[t = t + 1] = token(,  *("'!MESSAGE ' " SQize(tx)),  '!MESSAGE ' BREAK(nl) . tx)
            tok[t = t + 1] = token(,  *("'!ERROR ' " SQize(tx)),    '!ERROR ' BREAK(nl) . tx)
            tok[t = t + 1] = token(,, .targetIFSource)
            tok[t = t + 1] = token(,, .cmdIF_CFG_EQ)
            tok[t = t + 1] = token(,, .cmdIF_CFG_EQ_OR)
            tok[t = t + 1] = token(,, .cmdIF)
            tok[t = t + 1] = token(,, .cmdELSEIF_CFG_EQ)
            tok[t = t + 1] = token(,, .cmdELSEIF)
            tok[t = t + 1] = token(,, .cmdELSE)
            tok[t = t + 1] = token(,, .cmdENDIF)
            tok[t = t + 1] = token(,, .cmdIF_RECURSE)
            tok[t = t + 1] = token(,, .setBSC32)
            tok[t = t + 1] = token(,, .setBSC32_FLAGS)
            tok[t = t + 1] = token(,, .setBSC32_SBRS)
            tok[t = t + 1] = token(,, .setCFG)
            tok[t = t + 1] = token(,, .setCPP)
            tok[t = t + 1] = token(,, .setCPP_OBJS)
            tok[t = t + 1] = token(,, .setCPP_PROJ)
            tok[t = t + 1] = token(,, .setCPP_SBRS)
            tok[t = t + 1] = token(,  *(Qize(tx)), *setCPPxPROJ)
            tok[t = t + 1] = token(,, .setCPP_SWITCHES)
            tok[t = t + 1] = token(,, .setDEF_FILE)
            tok[t = t + 1] = token(,, .setDEP_CPP)
            tok[t = t + 1] = token(,, .setDEP_RSC)
            tok[t = t + 1] = token(,, .setINTDIR)
            tok[t = t + 1] = token(,, .setInputPath)
            tok[t = t + 1] = token(,, .setLIB32)
            tok[t = t + 1] = token(,, .setLIB32_FLAGS)
            tok[t = t + 1] = token(,, .setLIB32_OBJS)
            tok[t = t + 1] = token(,, .setLINK32)
            tok[t = t + 1] = token(,, .setLINK32_FLAGS)
            tok[t = t + 1] = token(,  *(Qize(tx)), *setLINK32xFLAGS)
            tok[t = t + 1] = token(,, .setLINK32_OBJS)
            tok[t = t + 1] = token(,, .setMTL)
            tok[t = t + 1] = token(,, .setMTL_PROJ)
            tok[t = t + 1] = token(,, .setMTL_SWITCHES)
            tok[t = t + 1] = token(,  *(Qize(tx)), *setMTLxSWITCHES)
            tok[t = t + 1] = token(,, .setNULL)
            tok[t = t + 1] = token(,, .setOUTDIR)
            tok[t = t + 1] = token(,, .setRSC)
            tok[t = t + 1] = token(,, .setRSC_PROJ)
            tok[t = t + 1] = token(,  *(Qize(tx)), *setRSCxPROJ)
            tok[t = t + 1] = token(,, .setSOURCE)
            tok[t = t + 1] = token(,, .cntPathname)
            tok[t = t + 1] = token(,, .endPathname)
            tok[t = t + 1] = token(,, .actionErase)
            tok[t = t + 1] = token(,, .targetInferences)
            tok[t = t + 1] = token(,, .targetInference)
            tok[t = t + 1] = token(,, .targetALL)
            tok[t = t + 1] = token(,, .targetCLEAN)
            tok[t = t + 1] = token(,, .targetOUTDIR)
            tok[t = t + 1] = token(,, .targetINTDIR)
            tok[t = t + 1] = token(,, .targetBSC32)
            tok[t = t + 1] = token(,, .targetLIB32)
            tok[t = t + 1] = token(,, .targetLINK32)
            tok[t = t + 1] = token(,, .targetMIDL)
            tok[t = t + 1] = token(,, .targetMTL)
            tok[t = t + 1] = token(,, .targetCPP)
            tok[t = t + 1] = token(,, .targetRSC)
            tok[t = t + 1] = token(,, .targetSource)
            tok[t = t + 1] = token(,, .includeDep)
            tok[t = t + 1] = token(,  *(Qize('$(' tx ')')), ('$(' *idx . tx ')'))
            tok[t = t + 1] = token(,, .hex)
            tok[t = t + 1] = token(,  *(Qize(tx)),    ('C' *intx) . tx)
            tok[t = t + 1] = token(,  *(Qize(tx)),    ('LNK' *intx) . tx)
            tok[t = t + 1] = token(,  *("'/" tx ": '" " *qqPathName"), ('/' *idx . tx ': ' *qqPathName))
            tok[t = t + 1] = token(,  *("'/" tx ":'" " *qqPathName"),  ('/' *idx . tx ':' *qqPathName))
            tok[t = t + 1] = token(,  *(Qize(tx)),    ('/' *idx ':' *idx) . tx)
            tok[t = t + 1] = token(,  *(Qize(tx)),    ('/' *idx) . tx)
            tok[t = t + 1] = token(,, .pathNames)
            tok[t = t + 1] = token(,, .pathName)
            tok[t = t + 1] = token(,  *("'/'"), '/' . tx)
            tok[t = t + 1] = token(,  *("bSlash"), bSlash)
            tok[t = t + 1] = token(,  *("bSlash nl ' '"), bSlash nl ' ')
            tok[t = t + 1] = token(,, .qqIntDirPathName)
            tok[t = t + 1] = token(,, .qqOutDirPathName)
            tok[t = t + 1] = token(,, .qqPathName)
            tok[t = t + 1] = token(,  *("tab"),         tab)
                                                                                             :(RETURN)
UserTokensEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
