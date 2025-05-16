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
            fndExt            =     ('dsp' | 'DSP') . extc
            fndCmd            =     'd:/mksnt/find d:/brazos -name "*.dsp" -print'
            fndSpecific       =
            fndExclude        =
            keyint            =     ('?') . tx
            keyword           =     '???' . tx
            space             =     SPAN(' ')
            whitespace        =     SPAN(' ')

            verNo             =     ('60000' | '5.00' | '6.00')
            headerSection     =     '# Microsoft Developer Studio Project File - Name="' BREAK('"') '" - Package Owner=<4>' nl
+                                   '# Microsoft Developer Studio Generated Build File, Format Version ' *verNo nl
+                                   '# ** DO NOT EDIT **' nl nl
+                                   '# TARGTYPE '
+                                   (  '"Win32 (x86) Application"'
+                                   |  '"Win32 (x86) Console Application"'
+                                   |  '"Win32 (x86) Dynamic-Link Library"'
+                                   |  '"Win32 (x86) External Target"'
+                                   |  '"Win32 (x86) Static Library"'
+                                   )
+                                   ' ' *hex nl nl
+                                   'CFG=' BREAK(nl) nl

            messageSection    =     *messages
            messages          =     *message FENCE(*messages | epsilon)
            message           =     '!MESSAGE ' BREAK(nl bSlash) bSlash nl BREAK(nl) nl
+                             |     '!MESSAGE ' BREAK(nl) nl

            ifCfg             =     '!IF  "$(CFG)" == "' BREAK('"' nl) '"' nl nl
            elseIfCfg         =     (nl | epsilon) '!ELSEIF  "$(CFG)" == "' BREAK('"' nl) '"' nl nl
            endIf             =     (nl | epsilon) '!ENDIF' ' ' nl

            addDef            =     '# ADD '           *idx ' ' *propValue nl
            addBaseDef        =     '# ADD BASE '      *idx ' ' *propValue nl
            propDef           =     '# PROP '          *idx ' ' *propValue nl
            propBaseDef       =     '# PROP BASE '     *idx ' ' *propValue nl
            subtractDef       =     '# SUBTRACT '      *idx ' ' *propValue nl
            subtractBaseDef   =     '# SUBTRACT BASE ' *idx ' ' *propValue nl
            chgDef            =     (*addBaseDef | *addDef | *subtractDef)
            propValue         =     (  *intx
+                                   |  *pathArgs FENCE(' ' *switches | epsilon)
+                                   |  (' ' | epsilon) *switches
+                                   )
            pathNode          =     SPAN(digits &UCASE &LCASE '%-_')
            arg               =     (*switch | *pathName | '"' *pathName '"' | '"' BREAK('"') '"')
            pathArg           =     (*pathName | '"' *pathName '"' | '"' BREAK('"') '"')

            beginCustom       =     '# Begin Custom Build - Performing MIDL step' nl
            beginGroup        =     '# Begin Group "' BREAK('"' nl) '"' nl
            beginProject      =     '# Begin Project' nl
            beginSource       =     '# Begin Source File' nl
            beginSpecial      =     '# Begin Special Build Tool' nl
            beginTarget       =     '# Begin Target' nl
            endCustom         =     '# End Custom Build' nl
            endGroup          =     '# End Group' nl
            endProject        =     '# End Project' nl
            endSection        =     '# End Section' nl
            endSource         =     '# End Source File' nl
            endSpecial        =     '# End Special Build Tool' nl
            endTarget         =     '# End Target' nl
            nameDef           =     '# Name "' BREAK('"' nl) '"' nl
            propScc_LocalPath =     '# PROP ' 'Scc_LocalPath' ' "' BREAK('"' nl) '"' nl
            propScc_ProjName  =     '# PROP ' 'Scc_ProjName' ' ' ('""' BREAK('"' nl) '", ' (LEN(8) | epsilon) '"' | '""') nl
            beginSection      =     '# Section ' *idx ' : ' '{' BREAK('}') '}' nl
            bsc32Assign       =     'BSC32'  '=' *pathName nl
            cppAssign         =     'CPP'    '=' *pathName nl
            lib32Assign       =     'LIB32'  '=' *pathName ' ' '-' *idx nl
            link32Assign      =     'LINK32' '=' *pathName nl
            mtlAssign         =     'MTL'    '=' *pathName nl
            rscAssign         =     'RSC'    '=' *pathName nl
            switch            =
+                             (     '/' ('D' | 'd') ' ' ('"' BREAK('"') '"' | *idx '=' *idx)
+                             |     '/' ('F' ANY('Radopr')) '"' *pathName '"'
+                             |     '/' 'F' ('As' | ANY('DRr'))
+                             |     '/' 'G' (ANY('3RXZfisyz') | 'm' ('-' | epsilon))
+                             |     '/' 'I ' '"' BREAK('"') '"'
+                             |     '/' 'MD' ('d' | epsilon)
+                             |     '/' 'MT' ('d' | epsilon)
+                             |     '/' 'NOENTRY'
+                             |     '/' 'O' ('icf' | ANY('12diptxy') | 'b0' | 'b1')
+                             |     '/' 'W' ANY('1234X')
+                             |     '/' 'X'
+                             |     '/' ('Y' ANY('Xcu')) ('"' BREAK('"') '"' | epsilon)
+                             |     '/' 'Z' '<' *idx '>'
+                             |     '/' 'Z' (ANY('7Ii') | 'p1')
+                             |     '/' 'base:'       ('"' '@' *pathName ',' *idx '"' | '"' BREAK('"') '"' | '@' *pathName ',' *idx)
+                             |     '/' 'c'
+                             |     '/' 'debug'
+                             |     '/' 'def:'         '"' *pathName '"'
+                             |     '/' 'dll'
+                             |     '/' 'entry:'       '"' *idx '@' *intx '"'
+                             |     '/' 'export:'      *idx
+                             |     '/' 'fo'           '"' ('$(' *idx ')' bSlash | epsilon) *pathName '"'
+                             |     '/' 'h '           '"' *pathName '"'
+                             |     '/' 'i '           '"' (*pathName | '.') '"'
+                             |     '/' 'iid '         '"' *pathName '"'
+                             |     '/' 'implib:'      '"' *pathName '"'
+                             |     '/' 'incremental:' ('no' | 'yes')
+                             |     '/' 'l '           *hex
+                             |     '/' 'libpath:'     '"' BREAK('"') '"'
+                             |     '/' 'machine:'     ('I386' | 'IX86')
+                             |     '/' 'map'          (':"' *pathName '"' | ':"' 'FULL' '"' | epsilon)
+                             |     '/' 'nodefaultlib' (':"' BREAK('"') '"' | epsilon)
+                             |     '/' 'nologo'
+                             |     '/' 'out:'         '"' *pathName '"'
+                             |     '/' 'o'            (' NUL' | ' "NUL"' | ' "' *pathName '"' | epsilon)
+                             |     '/' 'pdb:'         ('"' *pathName '"' | 'none')
+                             |     '/' 'pdbtype:'     'sept'
+                             |     '/' 'subsystem:'   ('console' | 'windows')
+                             |     '/' 'stack:'       *hex
+                             |     '/' 'tlb '         '"' *pathName '"'
+                             |     '/' 'ut:'          '"' *pathName '"'
+                             |     '/' 'win32'        (' "NUL"' | epsilon)
+                             |     '/' 'mktyplib203'
+                             |     '/' 'profile'
+                             |     '/' 'u'
+                             |     '/' 'verbose'
+                             )
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            addBaseDefs       =     *addBaseDef             FENCE(*addBaseDefs      | epsilon)
            addDefs           =     *addDef                 FENCE(*addDefs          | epsilon)
            args              =     *arg                    FENCE(' ' *args         | epsilon)
            chgDefs           =     *chgDef                 FENCE(*chgDefs          | epsilon)
            groupBlocks       =     *groupBlock             FENCE(*groupBlocks      | epsilon)
            pathArgs          =     *pathArg                FENCE(' ' *pathArgs     | epsilon)
            pathNames         =     *pathName ' ' *pathName FENCE(' ' *pathNames0   | epsilon)
            pathNames0        =     *pathName               FENCE(' ' *pathNames0   | epsilon)
            propBaseDefs      =     *propBaseDef            FENCE(*propBaseDefs     | epsilon)
            propDefs          =     *propDef                FENCE(*propDefs         | epsilon)
            sourceBlocks      =     *sourceBlock            FENCE(*sourceBlocks     | epsilon)
            subtractBaseDefs  =     *subtractBaseDef        FENCE(*subtractBaseDefs | epsilon)
            subtractDefs      =     *subtractDef            FENCE(*subtractDefs     | epsilon)
            switches          =     *switch                 FENCE(' ' *switches     | epsilon)
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            dspParse          =     POS(0)
+                                   *headerSection
+                                   *messageSection nl
+                                   *projectBlock
+                                   ARBNO(*sectionBlock)
+                                   RPOS(0)

            projectBlock      =     *beginProject
+                                   (*propDef | epsilon)
+                                   *propScc_ProjName
+                                   *propScc_LocalPath
+                                   FENCE(*cppAssign | epsilon)
+                                   FENCE(*mtlAssign | epsilon)
+                                   FENCE(*rscAssign | epsilon)
+                                   nl
+                                   (  *ifCfg *projectBody
+                                      ARBNO(*elseIfCfg *projectBody)
+                                      *endIf nl
+                                   |  *propIfBlock
+                                   )
+                                   *targetBlock
+                                   *endProject

            projectBody       =     *propBlock
+                                   *bsc32Assign
+                                   ARBNO(*chgDef)
+                                   (  *link32Assign
+                                   |  *lib32Assign
+                                   )
+                                   ARBNO(*chgDef)
+                                   FENCE(*specialBlock | epsilon)
+                                   (nl | epsilon)

            propBlock         =     ARBNO(*propBaseDef)
+                                   ARBNO(*propDef)
+                                   ARBNO(*chgDef)

            propIfBlock       =     *ifCfg *propBlock
+                                   ARBNO(*elseIfCfg *propBlock)
+                                   *endIf nl

            targetBlock       =     *beginTarget nl
+                                   ARBNO(*nameDef) (nl | epsilon)
+                                   FENCE(*propIfBlock | epsilon)
+                                   ARBNO(*groupBlocks | *sourceBlocks)
+                                   *endTarget

            groupBlock        =     *beginGroup nl
+                                   ARBNO(*propDef)
+                                   ARBNO(*groupBlocks | *sourceBlocks)
+                                   *endGroup

            sourceBlock       =     *beginSource nl
+                                   'SOURCE' '=' BREAK(nl) nl (nl | epsilon)
+                                   (  *ifCfg ARBNO(*propDef) ARBNO(*chgDef)
+                                      *elseIfCfg ARBNO(*propDef) ARBNO(*chgDef)
+                                      *endIf
+                                   |  *ifCfg ARBNO(*propDef) *customBlock
+                                      *elseIfCfg ARBNO(*propDef) *customBlock
+                                      *endIf
+                                   |  ARBNO(*propDef)
+                                      ARBNO(*chgDef)
+                                   )
+                                   (nl | epsilon) *endSource

            customBlock       =     *beginCustom
+                                   'InputPath' '=' *pathName nl nl
+                                   'BuildCmds' '=' ' ' bSlash nl
+                                   tab 'midl' ' ' *switches ' ' '"' *pathName '"' nl
+                                   ARBNO(
+                                      nl '"' *pathName '" : $(SOURCE) "$(INTDIR)" "$(OUTDIR)"' nl
+                                      '   $(BuildCmds)' nl
+                                   )
+                                   *endCustom

            sectionBlock      =     *beginSection
+                                   ARBNO('# 	' *int ':' *int ':' *idx ':' (*pathName | *idx) nl)
+                                   *endSection

            specialBlock      =     *beginSpecial
+                                   'IntDir' '=' *pathName nl
+                                   'SOURCE' '=' '"$(InputPath)"' nl
+                                   'PostBuild_Desc' '=' BREAK(nl) nl
+                                   'PostBuild_Cmds' '=' BREAK(nl) nl
+                                   *endSpecial

                                                                                             :(RETURN)
UserDefsEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserRpt()')                                                              :(UserRptEnd)
UserRpt                                                                                      :(RETURN)
UserRptEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserTokens()')                                                           :(UserTokensEnd)
UserTokens  tok[t = t + 1] = token(,, .dspParse)
            tok[t = t + 1] = token(,, .headerSection)
            tok[t = t + 1] = token(,, .messageSection)
            tok[t = t + 1] = token(,, .projectBlock)
*           tok[t = t + 1] = token(,, .projectBody)
            tok[t = t + 1] = token(,, .targetBlock)
            tok[t = t + 1] = token(,, .groupBlocks)
            tok[t = t + 1] = token(,, .sourceBlocks)
            tok[t = t + 1] = token(,, .ifCfg)
            tok[t = t + 1] = token(,, .elseIfCfg)
            tok[t = t + 1] = token(,, .endIf)
            tok[t = t + 1] = token(,, .bsc32Assign)
            tok[t = t + 1] = token(,, .link32Assign)
            tok[t = t + 1] = token(,, .lib32Assign)
            tok[t = t + 1] = token(,, .nameDef)
            tok[t = t + 1] = token('LbPROPScc_ProjName', *("'" '# PROP Scc_ProjName "' tx '"' "'"), '# PROP Scc_ProjName "' ('"' BREAK('"' nl) '", ' LEN(8) | epsilon) . tx '"')
            tok[t = t + 1] = token(,, .propScc_ProjName)
            tok[t = t + 1] = token(,, .propScc_LocalPath)
            tok[t = t + 1] = token(,, .chgDefs)
            tok[t = t + 1] = token(,, .propBaseDefs)
            tok[t = t + 1] = token(,, .propDefs)
            tok[t = t + 1] = token(,, .propDef)
            tok[t = t + 1] = token(,, .addBaseDefs)
            tok[t = t + 1] = token(,, .addDefs)
            tok[t = t + 1] = token(,, .subtractBaseDefs)
            tok[t = t + 1] = token(,, .subtractDefs)
            tok[t = t + 1] = token(,, .customBlock)
            tok[t = t + 1] = token(,, .sectionBlock)
            tok[t = t + 1] = token(,, .beginProject)
            tok[t = t + 1] = token(,, .endProject)
            tok[t = t + 1] = token(,, .cppAssign)
            tok[t = t + 1] = token(,, .mtlAssign)
            tok[t = t + 1] = token(,, .rscAssign)
            tok[t = t + 1] = token(,, .beginTarget)
            tok[t = t + 1] = token(,, .endTarget)
            tok[t = t + 1] = token(,, .beginGroup)
            tok[t = t + 1] = token(,, .endGroup)
            tok[t = t + 1] = token(,, .beginSource)
            tok[t = t + 1] = token(,, .endSource)
            tok[t = t + 1] = token(,, .beginCustom)
            tok[t = t + 1] = token(,, .endCustom)
            tok[t = t + 1] = token(,, .beginSection)
            tok[t = t + 1] = token(,, .endSection)
            tok[t = t + 1] = token(,, .beginSpecial)
            tok[t = t + 1] = token(,, .endSpecial)
            tok[t = t + 1] = token(,, .hex)
            tok[t = t + 1] = token(,  *("'" tx "'"), ('C' *intx) . tx)
            tok[t = t + 1] = token(,  *("'" tx "'"), ('LNK' *intx) . tx)
            tok[t = t + 1] = token(,, .switches)
            tok[t = t + 1] = token(,  *("'/" tx ": '" "'" '"' "'" " *pathName " "'" '"' "'"), ('/' *idx . tx ': "' *pathName '"'))
            tok[t = t + 1] = token(,  *("'/" tx ":'" "'" '"' "'" " *pathName " "'" '"' "'"), ('/' *idx . tx ':"' *pathName '"'))
            tok[t = t + 1] = token(,  *("'" tx "'"), ('/' *idx ':' *idx) . tx)
            tok[t = t + 1] = token(,  *("'" tx "'"), ('/' *idx) . tx)
            tok[t = t + 1] = token(,, .pathNames)
            tok[t = t + 1] = token(,, .pathName)
            tok[t = t + 1] = token(,  *("'/'"), '/' . tx)
            tok[t = t + 1] = token(,  *("bSlash"), bSlash)
            tok[t = t + 1] = token(,  *("'" '"' "'" " *pathName " "'" '"' "'"), '"' *pathName '"')
            tok[t = t + 1] = token(,  *("tab"), tab)
                                                                                             :(RETURN)
UserTokensEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
