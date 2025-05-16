            ABSTRACT                            =  'abstract'
            BOOLEAN                             =  'boolean'
            BREAK                               =  'break'
            BYTE                                =  'byte'
            CASE                                =  'case'
            CATCH                               =  'catch'
            CHAR                                =  'char'
            CLASS                               =  'class'
            CONST                               =  'const'
            CONTINUE                            =  'continue'
            $'_DEFAULT'                         =  'default'
            DO                                  =  'do'
            DOUBLE                              =  'double'
            ELSE                                =  'else'
            EXTENDS                             =  'extends'
            FALSE                               =  'false'
            FINAL                               =  'final'
            FINALLY                             =  'finally'
            FLOAT                               =  'float'
            FOR                                 =  'for'
            GOTO                                =  'goto'
            IF                                  =  'if'
            IMPLEMENTS                          =  'implements'
            IMPORT                              =  'import'
            INSTANCEOF                          =  'instanceof'
            INT                                 =  'int'
            INTERFACE                           =  'interface'
            LONG                                =  'long'
            NATIVE                              =  'native'
            NEW                                 =  'new'
            NULL                                =  'null'
            PACKAGE                             =  'package'
            PRIVATE                             =  'private'
            PROTECTED                           =  'protected'
            PUBLIC                              =  'public'
            RETURN                              =  'return'
            SHORT                               =  'short'
            STATIC                              =  'static'
            SUPER                               =  'super'
            SWITCH                              =  'switch'
            SYNCHRONIZED                        =  'synchronized'
            THIS                                =  'this'
            THROW                               =  'throw'
            THROWS                              =  'throws'
            TRANSIENT                           =  'transient'
            TRUE                                =  'true'
            TRY                                 =  'try'
            VOID                                =  'void'
            VOLATILE                            =  'volatile'
            WHILE                               =  'while'
            STRICTFP                            =  'strictfp'
            INTEGER_LITERAL                     =  *DECIMAL_LITERAL !(ANY('lL'))
+                                               |  *HEX_LITERAL !(ANY('lL'))
+                                               |  *OCTAL_LITERAL !(ANY('lL'))
            DECIMAL_LITERAL                     =  ANY('123456789') (SPAN('0123456789') | epsilon)
            HEX_LITERAL                         =  '0' ANY('xX') SPAN('0123456789abcdefABCDEF')
            OCTAL_LITERAL                       =  '0' (SPAN('01234567') | epsilon)
            FLOATING_POINT_LITERAL              =  SPAN('0123456789')
+                                                  '.'
+                                                  (SPAN('0123456789') | epsilon)
+                                                  !*EXPONENT
+                                                  !(ANY('fFdD'))
+                                               |  '.' SPAN('0123456789') !*EXPONENT !(ANY('fFdD'))
+                                               |  SPAN('0123456789') *EXPONENT !(ANY('fFdD'))
+                                               |  SPAN('0123456789') !*EXPONENT ANY('fFdD')
            EXPONENT                            =  ANY('eE') !(ANY('+-')) SPAN('0123456789')
            CHARACTER_LITERAL                   =  "'"
+                                                  (  NOTANY("'" bSlash nl cr)
+                                                  |  bSlash
+                                                     (  ANY('ntbrf' bSlash "'" '"')
+                                                     |  ANY('01234567') !ANY('01234567')
+                                                     |  ANY('0123') ANY('01234567') ANY('01234567')
+                                                     )
+                                                  )
+                                                  "'"
            STRING_LITERAL                      =  '"'
+                                                  !%(
+                                                     NOTANY('"' bSlash nl cr)
+                                                  |  bSlash
+                                                     (  ANY('ntbrf' bSlash "'" '"')
+                                                     |  ANY('01234567') !ANY('01234567')
+                                                     |  ANY('0123') ANY('01234567') ANY('01234567')
+                                                     )
+                                                  )
+                                                  '"'
            IDENTIFIER                          =  *LETTER !%(*LETTER | *DIGIT)
            LETTER                              =  ANY('$ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyzÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖØÙÚÛÜÝÞßàáâãäåæçèéêëìíîïðñòóôõöøùúûüýþÿ')
            DIGIT                               =  ANY('0123456789')
            LPAREN                              =  '('
            RPAREN                              =  ')'
            LBRACE                              =  '{'
            RBRACE                              =  '}'
            LBRACKET                            =  '['
            RBRACKET                            =  ']'
            SEMICOLON                           =  ';'
            COMMA                               =  ','
            DOT                                 =  '.'
            ASSIGN                              =  '='
            GT                                  =  '>'
            LT                                  =  '<'
            BANG                                =  '!'
            TILDE                               =  '~'
            HOOK                                =  '?'
            COLON                               =  ':'
            EQ                                  =  '=='
            LE                                  =  '<='
            GE                                  =  '>='
            NE                                  =  '!='
            SC_OR                               =  '||'
            SC_AND                              =  '&&'
            INCR                                =  '++'
            DECR                                =  '--'
            PLUS                                =  '+'
            MINUS                               =  '-'
            STAR                                =  '*'
            SLASH                               =  '/'
            BIT_AND                             =  '&'
            BIT_OR                              =  '|'
            XOR                                 =  '^'
            REM                                 =  '%'
            LSHIFT                              =  '<<'
            RSIGNEDSHIFT                        =  '>>'
            RUNSIGNEDSHIFT                      =  '>>>'
            PLUSASSIGN                          =  '+='
            MINUSASSIGN                         =  '-='
            STARASSIGN                          =  '*='
            SLASHASSIGN                         =  '/='
            ANDASSIGN                           =  '&='
            ORASSIGN                            =  '|='
            XORASSIGN                           =  '^='
            REMASSIGN                           =  '%='
            LSHIFTASSIGN                        =  '<<='
            RSIGNEDSHIFTASSIGN                  =  '>>='
            RUNSIGNEDSHIFTASSIGN                =  '>>>='
            CompilationUnit                     =  !*PackageDeclaration
+                                                  !%*ImportDeclaration
+                                                  !%*TypeDeclaration
+                                                  $' ' RPOS(0)
            PackageDeclaration                  =  package *Name $';'
            ImportDeclaration                   =  import *Name !($'.' $'*') $';'
            TypeDeclaration                     =  *ClassDeclaration | *InterfaceDeclaration | $';'
            ClassDeclaration                    =  !%(abstract | final | public | strictfp) *UnmodifiedClassDeclaration
            UnmodifiedClassDeclaration          =  class
+                                                  *IDENTIFIER
+                                                  !(extends *Name)
+                                                  !(implements *NameList)
+                                                  *ClassBody
            ClassBody                           =  $'{' !%*ClassBodyDeclaration $'}'
            NestedClassDeclaration              =  !%(
+                                                     static
+                                                  |  abstract
+                                                  |  final
+                                                  |  public
+                                                  |  protected
+                                                  |  private
+                                                  |  strictfp
+                                                  )
+                                                  *UnmodifiedClassDeclaration
            ClassBodyDeclaration                =  *Initializer
+                                               |  *NestedClassDeclaration
+                                               |  *NestedInterfaceDeclaration
+                                               |  *ConstructorDeclaration
+                                               |  *MethodDeclaration
+                                               |  *FieldDeclaration
            MethodDeclarationLookahead          =  !%(
+                                                     public
+                                                  |  protected
+                                                  |  private
+                                                  |  static
+                                                  |  abstract
+                                                  |  final
+                                                  |  native
+                                                  |  synchronized
+                                                  |  strictfp
+                                                  )
+                                                  *ResultType
+                                                  *IDENTIFIER
+                                                  $'('
            InterfaceDeclaration                =  !%(abstract | public | strictfp) *UnmodifiedInterfaceDeclaration
            NestedInterfaceDeclaration          =  !%(
+                                                     static
+                                                  |  abstract
+                                                  |  final
+                                                  |  public
+                                                  |  protected
+                                                  |  private
+                                                  |  strictfp
+                                                  )
+                                                  *UnmodifiedInterfaceDeclaration
            UnmodifiedInterfaceDeclaration      =  interface
+                                                  *IDENTIFIER
+                                                  !(extends *NameList)
+                                                  $'{'
+                                                  !%*InterfaceMemberDeclaration
+                                                  $'}'
            InterfaceMemberDeclaration          =  *NestedClassDeclaration
+                                               |  *NestedInterfaceDeclaration
+                                               |  *MethodDeclaration
+                                               |  *FieldDeclaration
            FieldDeclaration                    =  !%(
+                                                     public
+                                                  |  protected
+                                                  |  private
+                                                  |  static
+                                                  |  final
+                                                  |  transient
+                                                  |  volatile
+                                                  )
+                                                  *Type
+                                                  *VariableDeclarator
+                                                  !%($',' *VariableDeclarator)
+                                                  $';'
            VariableDeclarator                  =  *VariableDeclaratorId !($'=' *VariableInitializer)
            VariableDeclaratorId                =  *IDENTIFIER !%($'[' $']')
            VariableInitializer                 =  *ArrayInitializer | *Expression
            ArrayInitializer                    =  $'{'
+                                                  !(*VariableInitializer !%($',' *VariableInitializer))
+                                                  !$','
+                                                  $'}'
            MethodDeclaration                   =  !%(
+                                                     public
+                                                  |  protected
+                                                  |  private
+                                                  |  static
+                                                  |  abstract
+                                                  |  final
+                                                  |  native
+                                                  |  synchronized
+                                                  |  strictfp
+                                                  )
+                                                  *ResultType
+                                                  *MethodDeclarator
+                                                  !(throws *NameList)
+                                                  (*Block | $';')
            MethodDeclarator                    =  *IDENTIFIER *FormalParameters !%($'[' $']')
            FormalParameters                    =  $'(' !(*FormalParameter !%($',' *FormalParameter)) $')'
            FormalParameter                     =  !final *Type *VariableDeclaratorId
            ConstructorDeclaration              =  !(public | protected | private)
+                                                  *IDENTIFIER
+                                                  *FormalParameters
+                                                  !(throws *NameList)
+                                                  $'{'
+                                                  !*ExplicitConstructorInvocation
+                                                  !%*BlockStatement
+                                                  $'}'
            ExplicitConstructorInvocation       =  this *Arguments $';'
+                                               |  !(*PrimaryExpression $'.') super *Arguments $';'
            Initializer                         =  !static *Block
            Type                                =  (*PrimitiveType | *Name) !%($'[' $']')
            PrimitiveType                       =  boolean | char | byte | short | int | long | float | double
            ResultType                          =  void | *Type
            Name                                =  *IDENTIFIER !%($'.' *IDENTIFIER)
            NameList                            =  *Name !%($',' *Name)
            Expression                          =  *ConditionalExpression !(*AssignmentOperator *Expression)
            AssignmentOperator                  =  $'='
+                                               |  $'*='
+                                               |  $'/='
+                                               |  $'%='
+                                               |  $'+='
+                                               |  $'-='
+                                               |  $'<<='
+                                               |  $'>>='
+                                               |  $'>>>='
+                                               |  $'&='
+                                               |  $'^='
+                                               |  $'|='
            ConditionalExpression               =  *ConditionalOrExpression
+                                                  !($'?' *Expression $':' *ConditionalExpression)
            ConditionalOrExpression             =  *ConditionalAndExpression !%($'||' *ConditionalAndExpression)
            ConditionalAndExpression            =  *InclusiveOrExpression !%($'&&' *InclusiveOrExpression)
            InclusiveOrExpression               =  *ExclusiveOrExpression !%($'|' *ExclusiveOrExpression)
            ExclusiveOrExpression               =  *AndExpression !%($'^' *AndExpression)
            AndExpression                       =  *EqualityExpression !%($'&' *EqualityExpression)
            EqualityExpression                  =  *InstanceOfExpression !%(($'==' | $'!=') *InstanceOfExpression)
            InstanceOfExpression                =  *RelationalExpression !(instanceof *Type)
            RelationalExpression                =  *ShiftExpression !%(($'<' | $'>' | $'<=' | $'>=') *ShiftExpression)
            ShiftExpression                     =  *AdditiveExpression
+                                                  !%(($'<<' | $'>>' | $'>>>') *AdditiveExpression)
            AdditiveExpression                  =  *MultiplicativeExpression
+                                                  !%(($'+' | $'-') *MultiplicativeExpression)
            MultiplicativeExpression            =  *UnaryExpression !%(($'*' | $'/' | $'%') *UnaryExpression)
            UnaryExpression                     =  ($'+' | $'-') *UnaryExpression
+                                               |  *PreIncrementExpression
+                                               |  *PreDecrementExpression
+                                               |  *UnaryExpressionNotPlusMinus
            PreIncrementExpression              =  $'++' *PrimaryExpression
            PreDecrementExpression              =  $'--' *PrimaryExpression
            UnaryExpressionNotPlusMinus         =  ($'~' | $'!') *UnaryExpression | *CastExpression | *PostfixExpression
            CastLookahead                       =  $'(' *PrimitiveType
+                                               |  $'(' *Name $'[' $']'
+                                               |  $'('
+                                                  *Name
+                                                  $')'
+                                                  ($'~' | $'!' | $'(' | *IDENTIFIER | this | super | new | *Literal)
            PostfixExpression                   =  *PrimaryExpression !($'++' | $'--')
            CastExpression                      =  $'(' *Type $')' *UnaryExpression
+                                               |  $'(' *Type $')' *UnaryExpressionNotPlusMinus
            PrimaryExpression                   =  *PrimaryPrefix !%*PrimarySuffix
            PrimaryPrefix                       =  *Literal
+                                               |  this
+                                               |  super $'.' *IDENTIFIER
+                                               |  $'(' *Expression $')'
+                                               |  *AllocationExpression
+                                               |  *ResultType $'.' class
+                                               |  *Name
            PrimarySuffix                       =  $'.' this
+                                               |  $'.' *AllocationExpression
+                                               |  $'[' *Expression $']'
+                                               |  $'.' *IDENTIFIER
+                                               |  *Arguments
            Literal                             =  *INTEGER_LITERAL
+                                               |  *FLOATING_POINT_LITERAL
+                                               |  *CHARACTER_LITERAL
+                                               |  *STRING_LITERAL
+                                               |  *BooleanLiteral
+                                               |  *NullLiteral
            BooleanLiteral                      =  true | false
            NullLiteral                         =  null
            Arguments                           =  $'(' !*ArgumentList $')'
            ArgumentList                        =  *Expression !%($',' *Expression)
            AllocationExpression                =  new *PrimitiveType *ArrayDimsAndInits
+                                               |  new *Name (*ArrayDimsAndInits | *Arguments !*ClassBody)
            ArrayDimsAndInits                   =  %($'[' *Expression $']') !%($'[' $']')
+                                               |  %($'[' $']') *ArrayInitializer
            Statement                           =  *LabeledStatement
+                                               |  *Block
+                                               |  *EmptyStatement
+                                               |  *StatementExpression $';'
+                                               |  *SwitchStatement
+                                               |  *IfStatement
+                                               |  *WhileStatement
+                                               |  *DoStatement
+                                               |  *ForStatement
+                                               |  *BreakStatement
+                                               |  *ContinueStatement
+                                               |  *ReturnStatement
+                                               |  *ThrowStatement
+                                               |  *SynchronizedStatement
+                                               |  *TryStatement
            LabeledStatement                    =  *IDENTIFIER $':' *Statement
            Block                               =  $'{' !%*BlockStatement $'}'
            BlockStatement                      =  *LocalVariableDeclaration $';'
+                                               |  *Statement
+                                               |  *UnmodifiedClassDeclaration
+                                               |  *UnmodifiedInterfaceDeclaration
            LocalVariableDeclaration            =  !final *Type *VariableDeclarator !%($',' *VariableDeclarator)
            EmptyStatement                      =  $';'
            StatementExpression                 =  *PreIncrementExpression
+                                               |  *PreDecrementExpression
+                                               |  *PrimaryExpression
+                                                  !($'++' | $'--' | *AssignmentOperator *Expression)
            SwitchStatement                     =  switch
+                                                  $'('
+                                                  *Expression
+                                                  $')'
+                                                  $'{'
+                                                  !%(*SwitchLabel !%*BlockStatement)
+                                                  $'}'
            SwitchLabel                         =  case *Expression $':' | default $':'
            IfStatement                         =  if $'(' *Expression $')' *Statement !(else *Statement)
            WhileStatement                      =  while $'(' *Expression $')' *Statement
            DoStatement                         =  do *Statement while $'(' *Expression $')' $';'
            ForStatement                        =  for
+                                                  $'('
+                                                  !*ForInit
+                                                  $';'
+                                                  !*Expression
+                                                  $';'
+                                                  !*ForUpdate
+                                                  $')'
+                                                  *Statement
            ForInit                             =  *LocalVariableDeclaration | *StatementExpressionList
            StatementExpressionList             =  *StatementExpression !%($',' *StatementExpression)
            ForUpdate                           =  *StatementExpressionList
            BreakStatement                      =  break !*IDENTIFIER $';'
            ContinueStatement                   =  continue !*IDENTIFIER $';'
            ReturnStatement                     =  return !*Expression $';'
            ThrowStatement                      =  throw *Expression $';'
            SynchronizedStatement               =  synchronized $'(' *Expression $')' *Block
            TryStatement                        =  try
+                                                  *Block
+                                                  !%(catch $'(' *FormalParameter $')' *Block)
+                                                  !(finally *Block)
