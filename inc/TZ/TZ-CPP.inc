            Input                               =  !%*TranslationUnit
            TranslationUnit                     =  %*Group
            NoMas                               =  $' ' RPOS(0)
            Group                               =  *GroupPart | %*IFSection
            GroupPart                           =  %(*Text !%*WS) | %*IFSection | *ControlLine
            ControlLine                         =  *Define | *Include | *UnDef | *Pragma | *Error | *LineInfo | *NoMas
            IFSection                           =  *IFGroup
            IFGroup                             =  *If *IfCondition
+                                               |  *ElIf *ElseIfCondition
+                                               |  *IFDef
+                                               |  *IFNDef
+                                               |  *Else
+                                               |  *EndIf
            IfCondition                         =  *CompoundConditionalExpression
            ElseIfCondition                     =  *CompoundConditionalExpression
            Include                             =  *RELATIVE | *STANDARD
            LineInfo                            =  *LINEINFO
            Define                              =  *MANIFEST !((%*MacroArgs | *MacroVals) !*MacroVals)
+                                               |  *MANIFEST *MacroArgs !*Define
+                                               |  *MANIFEST !(%*MacroArgs !*MacroVals)
+                                               |  *MANIFEST %*WS *Define
            UnDef                               =  *CONSTITUENT
            MacroArgs                           =  *MACROMV
            MacroVals                           =  *Values | %*MACRORV !%*Values | *NOTCMTRV !%*Values
            Pragma                              =  *PRAGMA_EXPRN
            IFDef                               =  *IFDEF_EXPRN
            IFNDef                              =  *IFNDEF_EXPRN
            Error                               =  *ERROR_EXPRN
            EndIf                               =  *ENDIF
            Else                                =  *ELSE
            If                                  =  *IF
            ElIf                                =  *ELIF
            Values                              =  *VALUES | *QuotedValue | *CMTVAL | *MOREVAL
            QuotedValue                         =  *QUOTED_VALUE
            Text                                =  %( (*OUTER_TEXT !*NewLines | *OTHER_TEXT)
+                                                     !*NewLines
+                                                     !(*OTHER_TEXT !*NewLines)
+                                                  )
+                                               |  %( (*QuotedText !*NewLines | *OTHER_TEXT)
+                                                     !*NewLines
+                                                     !*OTHER_TEXT
+                                                     !*NewLines
+                                                  )
+                                               |  *NewLines
            NewLines                            =  *NEWLINE | *ERRLINE | *LINLINE | *PRGLINE | *INCLINE
            QuotedText                          =  *QUOTED_TEXT
            CompoundConditionalExpression       =  *ConditionalExpression
+                                               |  *CompoundAndExpression | *CompoundOrExpression
            CompoundAndExpression               =  *ConditionalExpression !%(*And *ConditionalExpression)
            CompoundOrExpression                =  *ConditionalExpression !%(*Or *ConditionalExpression)
            ConditionalExpression               =  *LogicalOrExpression
            LogicalOrExpression                 =  *LogicalAndExpression !%(*Or *LogicalAndExpression)
            LogicalAndExpression                =  *EqualityExpression !%(*And *EqualityExpression)
            EqualityExpression                  =  *RelationalExpression !%(*EqualTo *RelationalExpression)
            RelationalExpression                =  *LessExpression !%(*LessThan *LessExpression)
            GreaterThanExpression               =  *Negation !%(*GreaterThan *Negation)
            GreaterThanOrEqualExpression        =  *GreaterThanExpression
+                                                  !%(*GreaterThanOrEqual *GreaterThanExpression)
            LessThanOrEqualExpression           =  *GreaterThanOrEqualExpression
+                                                  !%(*LessThanOrEqual *GreaterThanOrEqualExpression)
            LessExpression                      =  *LessThanOrEqualExpression !%(*LessThan *LessThanOrEqualExpression)
            Or                                  =  *OR
            And                                 =  *AND
            EqualTo                             =  *EQ
            LessThan                            =  *LT
            LessThanOrEqual                     =  *LE
            GreaterThan                         =  *GT
            GreaterThanOrEqual                  =  *GE
            Assertion                           =  !%*DEFINED *Expression
            Negation                            =  !%*NOT *Assertion
            Expression                          =  *NUMERIC | *ITEM
            $'_EQ'                              =  '=='
            $'_LT'                              =  '<'
            $'_GT'                              =  '>'
            $'_LE'                              =  '<='
            $'_GE'                              =  '>='
            $'_AND'                             =  '&&'
            $'_OR'                              =  '||'
            $'_LSH'                             =  '<<'
            $'_RSH'                             =  '>>'
            DIR                                 =  '#'
            CMT                                 =  '/'
            ECMT                                =  '*'
            COD                                 =  bSlash nl | bSlash cr | bSlash cr nl
            ENDL                                =  nl | cr | cr nl
            UNDIR                               =  %(NOTANY('#' nl cr '"' '/'))
            DEFD                                =  'defined'
            ENDREL                              =  '"'
            CP                                  =  ')'
            OP                                  =  '('
            NOPAR                               =  NOTANY('()')
            WSP                                 =  ' ' | tab
            STD                                 =  NOTANY('>')
            REL                                 =  NOTANY('"')
            NOTENDL                             =  NOTANY(nl cr)
            NOTENDLC                            =  NOTANY(nl cr '/')
            NOTCMT                              =  NOTANY(nl cr '/*"')
            NOTWS                               =  NOTANY(' ' tab)
            NOTWSQ                              =  NOTANY(' ' tab nl cr '"')
            NOTWQC                              =  NOTANY(' ' tab nl cr '/"')
            INTEGER_LITERAL                     =  *DECIMAL_LITERAL !(ANY('lL'))
+                                               |  *HEX_LITERAL !(ANY('lL'))
+                                               |  *OCTAL_LITERAL !(ANY('lL'))
            DECIMAL_LITERAL                     =  ANY('0123456789') (SPAN('0123456789') | epsilon)
            HEX_LITERAL                         =  '0' ANY('xX') SPAN('0123456789abcdefABCDEF')
            OCTAL_LITERAL                       =  '0' (SPAN('01234567') | epsilon)
            FP_LITERAL                          =  SPAN('0123456789')
+                                                  '.'
+                                                  (SPAN('0123456789') | epsilon)
+                                                  !*EXPONENT
+                                                  !(ANY('fFdD'))
+                                               |  '.' SPAN('0123456789') !*EXPONENT !(ANY('fFdD'))
+                                               |  SPAN('0123456789') *EXPONENT !(ANY('fFdD'))
+                                               |  SPAN('0123456789') !*EXPONENT ANY('fFdD')
            EXPONENT                            =  ANY('eE') !(ANY('+-')) SPAN('0123456789')
            NOTCHR                              =  '!'
            WS                                  =  ANY(' ' tab)
            OUTER_TEXT                          =  !%*WSP %*UNDIR *NOTCMT
            NEWLINE                             =  *ENDL
            OTHER_TEXT                          =  NOTANY('')
            QUOTED_TEXT                         =  NOTANY('"') !%(NOTANY('"') | bSlash '"')
            IF                                  =  'if'
            ELIF                                =  'elif'
            ELSE                                =  'else'
            ENDIF                               =  'endif'
            NOT                                 =  *NOTCHR
            DEFINED                             =  *DEFD
            EQ                                  =  *$'_EQ'
            LT                                  =  *$'_LT'
            GT                                  =  *$'_GT'
            LE                                  =  *$'_LE'
            GE                                  =  *$'_GE'
            AND                                 =  *$'_AND'
            OR                                  =  *$'_OR'
            LSH                                 =  *$'_LSH'
            RSH                                 =  *$'_RSH'
            NUMERIC                             =  %(*INTEGER_LITERAL | *FP_LITERAL)
            ITEM                                =  *MANIFEST
            INCLINE                             =  *ENDL
            STANDARD                            =  %*STD
            RELATIVE                            =  %*REL
            PRAGMA_EXPRN                        =  *NOTWS %*NOTENDL
            PRGLINE                             =  *ENDL
            IFDEF_EXPRN                         =  *NOTWS %*NOTENDL
            IFNDEF_EXPRN                        =  *NOTWS %*NOTENDL
            ERROR_EXPRN                         =  *NOTWS %*NOTENDL
            ERRLINE                             =  *ENDL
            CONSTITUENT                         =  *MANIFEST
            MANIFEST                            =  ANY('abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_')
+                                                  (SPAN('abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_0123456789') | epsilon)
+                                               |  SPAN('0123456789')
            LINLINE                             =  *ENDL
            LINEINFO                            =  %*NOTENDL
            VALUES                              =  *NOTWQC %*NOTCMT *NOTWQC
            CMTVAL                              =  %( NOTANY('/*') '/' NOTANY('/*') !%(NOTANY(' ' tab cr nl))
+                                                  |  NOTANY('/*') '*' NOTANY('/*') !%(NOTANY(' ' tab cr nl))
+                                                  )
            MOREVAL                             =  *MANIFEST
            QUOTED_VALUE                        =  NOTANY('"') !%NOTANY('"')
            MACROMV                             =  *MANIFEST
            MOREARG                             =  %*NOPAR
            NOTCMTRV                            =  %( NOTANY('/*') '/' NOTANY('/*') !%(NOTANY(' ' tab cr nl))
+                                                  |  NOTANY('/*') '*' NOTANY('/*') !%(NOTANY(' ' tab cr nl))
+                                                  )
            MACRORV                             =  %(*COD | *NOTENDLC)
