-INCLUDE    'nmake.inc'
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
            fndExt            =     ('nmake' | 'NMAKE') . extc
            fndCmd            =     'd:/mksnt/find //flash/e/dev -name "*.nmake" -print'
            fndSpecific       =
            fndExclude        =
            keyint            =     ('?') . tx
            keyword           =     '???' . tx

            blanks            =     SPAN(' ')
            whitespace        =     blanks
            space             =     blanks
            $' '              =     FENCE(whitespace | epsilon)
            $'  '             =     FENCE(space | epsilon)
                                                                                             :(RETURN)
UserDefsEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserTokens()')                                                           :(UserTokensEnd)
UserTokens  tok[t = t + 1] = token(,, .nmakeParse)
            tok[t = t + 1] = token(,, .blurbs)
            tok[t = t + 1] = token(,, .autoIncluding)
            tok[t = t + 1] = token(,, .creatingLib)
            tok[t = t + 1] = token(,, .compiling)
            tok[t = t + 1] = token(,, .generatingCode)
            tok[t = t + 1] = token(,, .skipping)
            tok[t = t + 1] = token(,, .tabIfNotExist)
            tok[t = t + 1] = token(,, .tabBscmakeExe)
            tok[t = t + 1] = token(,, .tabClExe)
            tok[t = t + 1] = token(,, .tabLinkExe)
            tok[t = t + 1] = token(,, .tabRcExe)
            tok[t = t + 1] = token(,, .warningCs)
            tok[t = t + 1] = token(,, .warningRCs)
            tok[t = t + 1] = token(,, .warningLNKs)
            tok[t = t + 1] = token(,, .errorCs)
            tok[t = t + 1] = token(,, .errorRCs)
            tok[t = t + 1] = token(,, .errorLNKs)
            tok[t = t + 1] = token(,, .modules2)
            tok[t = t + 1] = token(,, .module)
            tok[t = t + 1] = token(,  *("'" tx "'"), ('C' *intx) . tx)
            tok[t = t + 1] = token(,  *("'" tx "'"), ('LNK' *intx) . tx)
            tok[t = t + 1] = token(,, .switches)
            tok[t = t + 1] = token(,, .pathNames)
            tok[t = t + 1] = token(,, .pathName)
            tok[t = t + 1] = token(,  *("'/" tx ": '" "'" '"' "'" " *pathName " "'" '"' "'"), ('/' *idx . tx ': "' *pathName '"'))
            tok[t = t + 1] = token(,  *("'/" tx ":'" "'" '"' "'" " *pathName " "'" '"' "'"), ('/' *idx . tx ':"' *pathName '"'))
            tok[t = t + 1] = token(,  *("'" tx "'"), ('/' *idx ':' *idx) . tx)
            tok[t = t + 1] = token(,  *("'" tx "'"), ('/' *idx) . tx)
            tok[t = t + 1] = token(,, .pathNames)
            tok[t = t + 1] = token(,, .pathName)
            tok[t = t + 1] = token(,  *("'" tx "'"), SPAN(digits &UCASE &LCASE '_') . tx)
            tok[t = t + 1] = token(,  *("'/'"), '/' . tx)
            tok[t = t + 1] = token(,  *("bs"), bs)
            tok[t = t + 1] = token(,  *("'" '"' "'" " *pathName " "'" '"' "'"), '"' *pathName '"')
            tok[t = t + 1] = token(,  *("tab '" tx "' ' '"), tab BREAK(' ') . tx ' ')
            tok[t = t + 1] = token(,  *("tab"), tab)

            dbg[.moduleInfo]  = TRUE
            dbg[.moduleInfos] = TRUE
            dbg[.modules1]    = TRUE
            dbg[.pathExt]     = TRUE
            dbg[.pathNode]    = TRUE
            dbg[.pathId]      = TRUE
            dbg[.pathLeaf]    = TRUE
            dbg[.pathDrive]   = TRUE
            dbg[.pathDir]     = TRUE

                                                                                             :(RETURN)
UserTokensEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
