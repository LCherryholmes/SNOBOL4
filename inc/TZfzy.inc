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
            fndExt            =     ('INI' | 'ini') . extc
            fndCmd            =     'd:/mksnt/find d:/merge -name "*fzy.ini" -print'
*           fndSpecific       =     'd:/merge/alo/inifiles/oracfzy.ini'
            fndExclude        =
            keyint            =     ('?') . tx
            keyword           =     '???' . tx
            space             =     SPAN(' ')
            whitespace        =     SPAN(' ')

            fzyComment        =     ';' BREAK(nl) nl
            fzyEmpty          =     $'  ' nl
            fzyIgnore         =     *fzyEmpty | *fzyComment
            fzyIgnores        =     *fzyIgnore FENCE(*fzyIgnores | epsilon)
            fzyImpactDefSet   =     'ImpactDefinitionSet' '=' BREAK(nl) nl
            fzyNumOfFuzRules  =     'NumberOfFuzzyRules' '=' *intx nl

            fzyArgs           =     *idx                 FENCE(',' *fzyArgs | epsilon)
            fzyChgArgs        =     *fzyChgArg           FENCE(',' *fzyChgArgs | epsilon)
            fzyClrArgs        =     *fzyClrArg           FENCE(',' *fzyClrArgs | epsilon)
            fzyCtlArgs        =     *fzyCtlArg           FENCE(',' *fzyCtlArgs | epsilon)
            fzyEscArgs        =     *fzyEscArg           FENCE(',' *fzyEscArgs | epsilon)
            fzyEscChoicesArgs =     *fzyEscChoicesArg    FENCE(',' *fzyEscChoicesArgs | epsilon)
            fzyEscMaskArgs    =     *fzyEscMaskArg       FENCE(',' *fzyEscMaskArgs | epsilon)
            fzyEscValueArgs   =     *fzyEscValueArg      FENCE(',' *fzyEscValueArgs | epsilon)
            fzyPropagateFromArgs =  *fzyPropagateFromArg FENCE(',' *fzyPropagateFromArgs | epsilon)
            fzyRelTypeArgs    =     *fzyRelTypeArg       FENCE(',' *fzyRelTypeArgs | epsilon)

            fzyChgArg         =     FENCE(
+                                      icase('Add')
+                                   |  icase('Delete')
+                                   |  icase('HTMLReport')
+                                   |  icase('MigDepsOnly')
+                                   |  icase('Migrate')
+                                   |  icase('Modify')
+                                   |  icase('Move')
+                                   |  icase('Rebuild')
+                                   |  icase('Recompile')
+                                   )
            fzyClrArg         =     FENCE(
+                                      icase('Born')
+                                   |  icase('Defer')
+                                   |  icase('DropCreate')
+                                   |  icase('Precursor')
+                                   )
            fzyCtlArg         =     FENCE(
+                                      icase('Skiprel')
+                                   |  icase('Skip')
+                                   |  icase('Terminal')
+                                   |  icase('Term')
+                                   )
            fzyEscArg         =     FENCE(
+                                      icase('Born')
+                                   |  icase('Dead')
+                                   |  icase('Disable')
+                                   |  icase('DropCreate')
+                                   |  icase('HTMLReport')
+                                   |  icase('Grant')
+                                   |  icase('Implicit')
+                                   |  icase('Invalid')
+                                   |  icase('LocalAlter')
+                                   |  icase('MigDepsOnly')
+                                   |  icase('MigDep')
+                                   |  icase('MigRef')
+                                   |  icase('Migrate')
+                                   |  icase('ModifyLob')
+                                   |  icase('None')
+                                   |  icase('Precursor')
+                                   |  icase('Pseudo')
+                                   |  icase('Reference')
+                                   |  icase('Recompile')
+                                   |  icase('Recreate')
+                                   |  icase('Regrant')
+                                   |  icase('Rename')
+                                   |  icase('Replace')
+                                   |  icase('Revoke')
+                                   |  icase('SubAlter')
+                                   )
            fzyEscChoicesArg  =     FENCE(
+                                      icase('Born')
+                                   |  icase('Dead')
+                                   |  icase('Disable')
+                                   |  icase('DropCreate')
+                                   |  icase('HTMLReport')
+                                   |  icase('Invalid')
+                                   |  icase('LocalAlter')
+                                   |  icase('MigDepsOnly')
+                                   |  icase('MigDep')
+                                   |  icase('MigRef')
+                                   |  icase('Migrate')
+                                   |  icase('ModifyLob')
+                                   |  icase('None')
+                                   |  icase('Recompile')
+                                   |  icase('Recreate')
+                                   |  icase('Reference')
+                                   |  icase('Rename')
+                                   |  icase('Replace')
+                                   |  icase('SubAlter')
+                                   )
            fzyEscMaskArg     =     FENCE(
+                                      icase('Dead')
+                                   |  icase('Implicit')
+                                   |  icase('Invalid')
+                                   |  icase('Pseudo')
+                                   )
            fzyEscValueArg     =    FENCE(
+                                      icase('Dead')
+                                   |  icase('Implicit')
+                                   |  icase('Invalid')
+                                   |  icase('Pseudo')
+                                   )
            fzyRelTypeArg     =     FENCE(
+                                      icase('CollectionOf')
+                                   |  icase('ComponentOf')
+                                   |  icase('Contains')
+                                   |  icase('HasComponent')
+                                   |  icase('Owns')
+                                   |  icase('ReferedToBy')
+                                   |  icase('RefersTo')
+                                   )
            fzyPropagateFromArg =   FENCE(
+                                      icase('Primary')
+                                   |  icase('Secondary')
+                                   )

            object            =     FENCE(icase('Object') | icase('Obj'))
            primary           =     FENCE(icase('Primary') | icase('Pri'))
            propagateFrom     =     FENCE(icase('PropagateFrom') | icase('PropFrom'))
            secondary         =     FENCE(icase('Secondary') | icase('Sec'))

            fzyAryArgs        =     FENCE(*fzyObject FENCE(',' | epsilon) | epsilon)
+                                   (  $'  '
+                                      (  *fzyDetScr
+                                      |  *fzyEscChoices
+                                      |  *fzyEscMask $'  ' *fzyEscValue
+                                      )
+                                   | epsilon
+                                   )

            fzyChg            =     icase('Chg')           '(' *fzyChgArgs             $'  ' ')'
            fzyClr            =     icase('Clr')           '(' *fzyClrArgs             $'  ' ')'
            fzyCtl            =     icase('Ctl')           '(' *fzyCtlArg              $'  ' ')'
            fzyDetAll         =     icase('DetAll')        '('                         $'  ' ')'
            fzyDetScr         =     icase('DetScr')        '(' *idx '.?sl'             $'  ' ')'
            fzyEsc            =     icase('Esc')           '(' (*fzyEscArgs | epsilon) $'  ' ')'
            fzyEscChoices     =     icase('EscChoices')    '(' *fzyEscChoicesArgs      $'  ' ')'
            fzyEscMask        =     icase('EscMask')       '(' *fzyEscMaskArgs         $'  ' ')'
            fzyEscValue       =     icase('EscValue')      '(' *fzyEscValueArgs        $'  ' ')'
            fzyObject         =     *object                '(' *idx                    $'  ' ')'
            fzyPrimary        =     *primary               '(' *fzyAryArgs             $'  ' ')'
            fzyPropagateFrom  =     *propagateFrom         '(' *fzyPropagateFromArg    $'  ' ')'
            fzyProperty       =     icase('Property')      '(' (*fzyArgs | epsilon)    $'  ' ')'
            fzyRelType        =     icase('RelType')       '(' *fzyRelTypeArgs         $'  ' ')'
            fzySecondary      =     *secondary             '(' *fzyAryArgs             $'  ' ')'

            fzySpace          =     $'  ' FENCE(nl *fzyRuleNth $'  ' | epsilon)
            fzyIfExpr         =     FENCE(
+                                      *fzyChg
+                                   |  *fzyDetAll
+                                   |  *fzyDetScr
+                                   |  *fzyEscChoices
+                                   |  *fzyPrimary
+                                   |  *fzyPropagateFrom
+                                   |  *fzyProperty
+                                   |  *fzyRelType
+                                   |  *fzySecondary
+                                   )
            fzyThenExpr       =     FENCE(
+                                      *fzyClr
+                                   |  *fzyCtl
+                                   |  *fzyEsc
+                                   )
            fzyIfExprs        =     *fzySpace *fzyIfExpr FENCE(*fzyIfExprs | epsilon)
            fzyThenExprs      =     *fzySpace *fzyThenExpr FENCE(*fzyThenExprs | epsilon)
            fzyIfClause       =     *fzyRule1st $'  '
+                                   icase('if')   '(' *fzyIfExprs *fzySpace ')' *fzySpace
            fzyThenClause     =     icase('then') '(' *fzyThenExprs *fzySpace ')' $'  '
            fzyRule           =     *fzyIfClause *fzyThenClause
            fzyRule1st        =     'FuzzyRule' *intx $'  ' '='
            fzyRuleNth        =     'FuzzyRule' *intx '_' *intx $'  ' '='
            fzySectionTitle   =     '[' *idx ']'
            fzyParse          =     *fzySectionTitle nl
+                                   FENCE(*fzyIgnores | epsilon)
+                                   *fzyImpactDefSet
+                                   FENCE(*fzyIgnores | epsilon)
+                                   FENCE(*fzyNumOfFuzRules | epsilon)
+                                   ARBNO(FENCE(*fzyIgnores | *fzyRule nl))
+                                   FENCE(*fzyIgnores | epsilon)
+                                   FENCE(*fzyNumOfFuzRules | epsilon)
+                                   FENCE(*fzyIgnores | epsilon)
+                                   RPOS(0)
                                                                                             :(RETURN)
UserDefsEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserRpt()')                                                              :(UserRptEnd)
UserRpt     XDump('fzy', fzy)                                                                :(RETURN)
UserRptEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserTokens()')                                                           :(UserTokensEnd)
UserTokens  tok[t = t + 1] = token(,, .fzyParse)
            tok[t = t + 1] = token(,, .fzySectionTitle)
            tok[t = t + 1] = token(,, .fzyComment)
            tok[t = t + 1] = token(,, .fzyEmpty)
            tok[t = t + 1] = token(,, .fzyImpactDefSet)
            tok[t = t + 1] = token(,, .fzyNumOfFuzRules)
            tok[t = t + 1] = token(,, .fzyRule)
            tok[t = t + 1] = token(,, .fzyIfClause)
            tok[t = t + 1] = token(,, .fzyThenClause)
            tok[t = t + 1] = token(,, .fzyRule1st)
            tok[t = t + 1] = token(,, .fzyRuleNth)
            tok[t = t + 1] = token(,, .fzyChg)
            tok[t = t + 1] = token(,, .fzyClr)
            tok[t = t + 1] = token(,, .fzyCtl)
            tok[t = t + 1] = token(,, .fzyDetAll)
            tok[t = t + 1] = token(,, .fzyDetScr)
            tok[t = t + 1] = token(,, .fzyEsc)
            tok[t = t + 1] = token(,, .fzyEscChoices)
            tok[t = t + 1] = token(,, .fzyEscMask)
            tok[t = t + 1] = token(,, .fzyEscValue)
            tok[t = t + 1] = token(,, .fzyObject)
            tok[t = t + 1] = token(,, .fzyPrimary)
            tok[t = t + 1] = token(,, .fzyPropagateFrom)
            tok[t = t + 1] = token(,, .fzyProperty)
            tok[t = t + 1] = token(,, .fzyRelType)
            tok[t = t + 1] = token(,, .fzySecondary)
*           tok[t = t + 1] = token(,, .fzyChgArgs)
*           tok[t = t + 1] = token(,, .fzyCtlArgs)
*           tok[t = t + 1] = token(,, .fzyEscArgs)
*           tok[t = t + 1] = token(,, .fzyEscChoicesArgs)
            tok[t = t + 1] = token(,  *("'/'"),           '/')
            tok[t = t + 1] = token(,  *("bs"),            bs)
            tok[t = t + 1] = token(,  *("bs nl"),         bs nl)
            tok[t = t + 1] = token(,  *("tab"),           tab)
                                                                                             :(RETURN)
UserTokensEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
