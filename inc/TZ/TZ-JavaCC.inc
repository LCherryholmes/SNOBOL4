            $'_OPTIONS'                         =  'options'
            $'_LOOKAHEAD'                       =  'LOOKAHEAD'
            $'_IGNORE_CASE'                     =  'IGNORE_CASE'
            $'_PARSER_BEGIN'                    =  'PARSER_BEGIN'
            $'_PARSER_END'                      =  'PARSER_END'
            $'_JAVACODE'                        =  'JAVACODE'
            $'_TOKEN'                           =  'TOKEN'
            $'_SPECIAL_TOKEN'                   =  'SPECIAL_TOKEN'
            $'_MORE'                            =  'MORE'
            $'_SKIP'                            =  'SKIP'
            $'_TOKEN_MGR_DECLS'                 =  'TOKEN_MGR_DECLS'
            $'_EOF'                             =  'EOF'
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
            PLUSASSIGN                          =  '+='
            MINUSASSIGN                         =  '-='
            STARASSIGN                          =  '*='
            SLASHASSIGN                         =  '/='
            ANDASSIGN                           =  '&='
            ORASSIGN                            =  '|='
            XORASSIGN                           =  '^='
            REMASSIGN                           =  '%='
            javacc_input                        =  *javacc_options
+                                                  PARSER_BEGIN
+                                                  $'('
+                                                  *identifier
+                                                  $')'
+                                                  *CompilationUnit
+                                                  PARSER_END
+                                                  $'('
+                                                  *identifier
+                                                  $')'
+                                                  %*production
+                                                  $' ' RPOS(0)
            javacc_options                      =  !(options $'{' %*option_binding $'}')
            option_binding                      =  (*IDENTIFIER | LOOKAHEAD | IGNORE_CASE | static)
+                                                  $'='
+                                                  (*IntegerLiteral | *BooleanLiteral | *StringLiteral)
+                                                  $';'
            production                          =  *javacode_production
+                                               |  *regular_expr_production
+                                               |  *token_manager_decls
+                                               |  *bnf_production
            javacode_production                 =  JAVACODE
+                                                  *ResultType
+                                                  *identifier
+                                                  *FormalParameters
+                                                  !(throws *Name !%($',' *Name))
+                                                  !*node_descriptor
+                                                  *Block
            bnf_production                      =  *ResultType
+                                                  *identifier
+                                                  *FormalParameters
+                                                  !(throws *Name !%($',' *Name))
+                                                  !*node_descriptor
+                                                  $':'
+                                                  *Block
+                                                  $'{'
+                                                  *expansion_choices
+                                                  $'}'
            regular_expr_production             =  !($'<' $'*' $'>' | $'<' *IDENTIFIER !%($',' *IDENTIFIER) $'>')
+                                                  *regexpr_kind
+                                                  !($'[' IGNORE_CASE $']')
+                                                  $':'
+                                                  $'{'
+                                                  *regexpr_spec
+                                                  !%($'|' *regexpr_spec)
+                                                  $'}'
            token_manager_decls                 =  TOKEN_MGR_DECLS $':' *ClassBody
            regexpr_kind                        =  TOKEN | SPECIAL_TOKEN | SKIP | MORE
            regexpr_spec                        =  *regular_expression !*Block !($':' *IDENTIFIER)
            expansion_choices                   =  *expansion !%($'|' *expansion)
            expansion                           =  !(LOOKAHEAD $'(' *local_lookahead $')')
+                                                  %(*expansion_unit !*node_descriptor)
            local_lookahead                     =  !*IntegerLiteral
+                                                  !$','
+                                                  !*expansion_choices
+                                                  !$','
+                                                  !($'{' *Expression $'}')
            expansion_unit                      =  LOOKAHEAD $'(' *local_lookahead $')'
+                                               |  *Block
+                                               |  $'[' *expansion_choices $']'
+                                               |  try
+                                                  $'{'
+                                                  *expansion_choices
+                                                  $'}'
+                                                  !%(catch $'(' *Name *IDENTIFIER $')' *Block)
+                                                  !(finally *Block)
+                                               |  !(*PrimaryExpression $'=')
+                                                  (*regular_expression | *identifier *Arguments)
+                                               |  $'(' *expansion_choices $')' !($'+' | $'*' | $'?')
            regular_expression                  =  *StringLiteral
+                                               |  $'<'
+                                                  !(!$'#' *identifier $':')
+                                                  *complex_regular_expression_choices
+                                                  $'>'
+                                               |  $'<' *identifier $'>'
+                                               |  $'<' EOF $'>'
            complex_regular_expression_choices  =  *complex_regular_expression !%($'|' *complex_regular_expression)
            complex_regular_expression          =  %*complex_regular_expression_unit
            complex_regular_expression_unit     =  *StringLiteral
+                                               |  $'<' *identifier $'>'
+                                               |  *character_list
+                                               |  $'(' *complex_regular_expression_choices $')' !($'+' | $'*' | $'?')
            character_list                      =  !$'~'
+                                                  $'['
+                                                  !(*character_descriptor !%($',' *character_descriptor))
+                                                  $']'
            character_descriptor                =  *StringLiteral !($'-' *StringLiteral)
            identifier                          =  *IDENTIFIER
            node_descriptor                     =  $'#'
+                                                  (*IDENTIFIER | *VOID)
+                                                  !($'(' !$'>' *node_descriptor_expression $')')
            JavaIdentifier                      =  *IDENTIFIER
+                                               |  options
+                                               |  LOOKAHEAD
+                                               |  IGNORE_CASE
+                                               |  PARSER_BEGIN
+                                               |  PARSER_END
+                                               |  JAVACODE
+                                               |  TOKEN
+                                               |  SPECIAL_TOKEN
+                                               |  MORE
+                                               |  SKIP
+                                               |  TOKEN_MGR_DECLS
+                                               |  EOF
            ShiftOps                            =  $'<' $'<' | $'>' $'>' !$'>'
            OtherAssignmentOps                  =  $'<' $'<=' | $'>' !$'>' $'>='
            CompilationUnit                     =  !*PackageDeclaration !%*ImportDeclaration !%*TypeDeclaration
            JavaCompilationUnit                 =  *CompilationUnit $' ' RPOS(0)
            PackageDeclaration                  =  package *Name $';'
            ImportDeclaration                   =  import *Name !($'.' $'*') $';'
            TypeDeclaration                     =  *ClassDeclaration | *InterfaceDeclaration | $';'
            ClassDeclaration                    =  !%(abstract | final | public) *UnmodifiedClassDeclaration
            UnmodifiedClassDeclaration          =  class
+                                                  *JavaIdentifier
+                                                  !(extends *Name)
+                                                  !(implements *NameList)
+                                                  *ClassBody
            ClassBody                           =  $'{' !%*ClassBodyDeclaration $'}'
            NestedClassDeclaration              =  !%(static | abstract | final | public | protected | private)
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
+                                                  )
+                                                  *ResultType
+                                                  *JavaIdentifier
+                                                  $'('
            InterfaceDeclaration                =  !%(abstract | public) *UnmodifiedInterfaceDeclaration
            NestedInterfaceDeclaration          =  !%(static | abstract | final | public | protected | private)
+                                                  *UnmodifiedInterfaceDeclaration
            UnmodifiedInterfaceDeclaration      =  interface
+                                                  *JavaIdentifier
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
            VariableDeclaratorId                =  *JavaIdentifier !%($'[' $']')
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
+                                                  )
+                                                  *ResultType
+                                                  *MethodDeclarator
+                                                  !(throws *NameList)
+                                                  (*Block | $';')
            MethodDeclarator                    =  *JavaIdentifier *FormalParameters !%($'[' $']')
            FormalParameters                    =  $'(' !(*FormalParameter !%($',' *FormalParameter)) $')'
            FormalParameter                     =  !final *Type *VariableDeclaratorId
            ConstructorDeclaration              =  !(public | protected | private)
+                                                  *JavaIdentifier
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
            Name                                =  *JavaIdentifier !%($'.' *JavaIdentifier)
            NameList                            =  *Name !%($',' *Name)
            Expression                          =  *ConditionalExpression !(*AssignmentOperator *Expression)
            AssignmentOperator                  =  $'='
+                                               |  $'*='
+                                               |  $'/='
+                                               |  $'%='
+                                               |  $'+='
+                                               |  $'-='
+                                               |  $'&='
+                                               |  $'^='
+                                               |  $'|='
+                                               |  *OtherAssignmentOps
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
            ShiftExpression                     =  *AdditiveExpression !%(*ShiftOps *AdditiveExpression)
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
+                                                  (  $'~'
+                                                  |  $'!'
+                                                  |  $'('
+                                                  |  *JavaIdentifier
+                                                  |  this
+                                                  |  super
+                                                  |  new
+                                                  |  *Literal
+                                                  )
            PostfixExpression                   =  *PrimaryExpression !($'++' | $'--')
            CastExpression                      =  $'(' *Type $')' *UnaryExpression
+                                               |  $'(' *Type $')' *UnaryExpressionNotPlusMinus
            PrimaryExpression                   =  *PrimaryPrefix !%*PrimarySuffix
            PrimaryPrefix                       =  *Literal
+                                               |  this
+                                               |  super $'.' *JavaIdentifier
+                                               |  $'(' *Expression $')'
+                                               |  *AllocationExpression
+                                               |  *ResultType $'.' class
+                                               |  *Name
            PrimarySuffix                       =  $'.' this
+                                               |  $'.' *AllocationExpression
+                                               |  $'[' *Expression $']'
+                                               |  $'.' *JavaIdentifier
+                                               |  *Arguments
            Literal                             =  *INTEGER_LITERAL
+                                               |  *FLOATING_POINT_LITERAL
+                                               |  *CHARACTER_LITERAL
+                                               |  *STRING_LITERAL
+                                               |  *BooleanLiteral
+                                               |  *NullLiteral
            IntegerLiteral                      =  *INTEGER_LITERAL
            BooleanLiteral                      =  true | false
            StringLiteral                       =  *STRING_LITERAL
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
            LabeledStatement                    =  *JavaIdentifier $':' *Statement
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
            BreakStatement                      =  break !*JavaIdentifier $';'
            ContinueStatement                   =  continue !*JavaIdentifier $';'
            ReturnStatement                     =  return !*Expression $';'
            ThrowStatement                      =  throw *Expression $';'
            SynchronizedStatement               =  synchronized $'(' *Expression $')' *Block
            TryStatement                        =  try
+                                                  *Block
+                                                  !%(catch $'(' *FormalParameter $')' *Block)
+                                                  !(finally *Block)
