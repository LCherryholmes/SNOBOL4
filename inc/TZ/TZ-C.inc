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
            CONTINUE                            =  'continue'
            VOLATILE                            =  'volatile'
            REGISTER                            =  'register'
            UNSIGNED                            =  'unsigned'
            TYPEDEF                             =  'typedef'
            DFLT                                =  'default'
            DOUBLE                              =  'double'
            SIZEOF                              =  'sizeof'
            SWITCH                              =  'switch'
            RETURN                              =  'return'
            EXTERN                              =  'extern'
            STRUCT                              =  'struct'
            STATIC                              =  'static'
            SIGNED                              =  'signed'
            WHILE                               =  'while'
            BREAK                               =  'break'
            UNION                               =  'union'
            CONST                               =  'const'
            FLOAT                               =  'float'
            SHORT                               =  'short'
            ELSE                                =  'else'
            CASE                                =  'case'
            LONG                                =  'long'
            ENUM                                =  'enum'
            AUTO                                =  'auto'
            VOID                                =  'void'
            CHAR                                =  'char'
            GOTO                                =  'goto'
            FOR                                 =  'for'
            INT                                 =  'int'
            IF                                  =  'if'
            DO                                  =  'do'
            IDENTIFIER                          =  *LETTER !%(*LETTER | *DIGIT)
            LETTER                              =  ANY('$ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz')
            DIGIT                               =  ANY('0123456789')
            TranslationUnit                     =  %*ExternalDeclaration
            ExternalDeclaration                 =  *FunctionDefinition | *Declaration
            FunctionDefinition                  =  !*DeclarationSpecifiers
+                                                  *Declarator
+                                                  !*DeclarationList
+                                                  *CompoundStatement
            Declaration                         =  *DeclarationSpecifiers !*InitDeclaratorList $';'
            DeclarationList                     =  %*Declaration
            DeclarationSpecifiers               =  *StorageClassSpecifier !*DeclarationSpecifiers
+                                               |  *TypeSpecifier !*DeclarationSpecifiers
+                                               |  *TypeQualifier !*DeclarationSpecifiers
            StorageClassSpecifier               =  *AUTO | *REGISTER | *STATIC | *EXTERN | *TYPEDEF
            TypeSpecifier                       =  *VOID
+                                               |  *CHAR
+                                               |  *SHORT
+                                               |  *INT
+                                               |  *LONG
+                                               |  *FLOAT
+                                               |  *DOUBLE
+                                               |  *SIGNED
+                                               |  *UNSIGNED
+                                               |  *StructOrUnionSpecifier
+                                               |  *EnumSpecifier
+                                               |  *TypedefName
            TypeQualifier                       =  *CONST | *VOLATILE
            StructOrUnionSpecifier              =  *StructOrUnion
+                                                  (!*IDENTIFIER $'{' *StructDeclarationList $'}' | *IDENTIFIER)
            StructOrUnion                       =  *STRUCT | *UNION
            StructDeclarationList               =  %*StructDeclaration
            InitDeclaratorList                  =  *InitDeclarator !%($',' *InitDeclarator)
            InitDeclarator                      =  *Declarator !($'=' *Initializer)
            StructDeclaration                   =  *SpecifierQualifierList *StructDeclaratorList $';'
            SpecifierQualifierList              =  *TypeSpecifier !*SpecifierQualifierList
+                                               |  *TypeQualifier !*SpecifierQualifierList
            StructDeclaratorList                =  *StructDeclarator !%($',' *StructDeclarator)
            StructDeclarator                    =  *Declarator | !*Declarator $':' *ConstantExpression
            EnumSpecifier                       =  *ENUM (!*IDENTIFIER $'{' *EnumeratorList $'}' | *IDENTIFIER)
            EnumeratorList                      =  *Enumerator !%($',' *Enumerator)
            Enumerator                          =  *IDENTIFIER !($'=' *ConstantExpression)
            Declarator                          =  !*Pointer *DirectDeclarator
            DirectDeclarator                    =  (*IDENTIFIER | $'(' *Declarator $')')
+                                                  !%(
+                                                     $'[' !*ConstantExpression $']'
+                                                  |  $'(' *ParameterTypeList $')'
+                                                  |  $'(' !*IdentifierList $')'
+                                                  )
            Pointer                             =  $'*' !*TypeQualifierList !*Pointer
            TypeQualifierList                   =  %*TypeQualifier
            ParameterTypeList                   =  *ParameterList !($',' $'...')
            ParameterList                       =  *ParameterDeclaration !%($',' *ParameterDeclaration)
            ParameterDeclaration                =  *DeclarationSpecifiers (*Declarator | !*AbstractDeclarator)
            IdentifierList                      =  *IDENTIFIER !%($',' *IDENTIFIER)
            Initializer                         =  *AssignmentExpression | $'{' *InitializerList !$',' $'}'
            InitializerList                     =  *Initializer !%($',' *Initializer)
            TypeName                            =  *SpecifierQualifierList !*AbstractDeclarator
            AbstractDeclarator                  =  *Pointer | !*Pointer *DirectAbstractDeclarator
            DirectAbstractDeclarator            =  (  $'(' *AbstractDeclarator $')'
+                                                  |  $'[' !*ConstantExpression $']'
+                                                  |  $'(' !*ParameterTypeList $')'
+                                                  )
+                                                  !%($'[' !*ConstantExpression $']' | $'(' !*ParameterTypeList $')')
            TypedefName                         =  *IDENTIFIER
            Statement                           =  *LabeledStatement
+                                               |  *ExpressionStatement
+                                               |  *CompoundStatement
+                                               |  *SelectionStatement
+                                               |  *IterationStatement
+                                               |  *JumpStatement
            LabeledStatement                    =  *IDENTIFIER $':' *Statement
+                                               |  *CASE *ConstantExpression $':' *Statement
+                                               |  *DFLT $':' *Statement
            ExpressionStatement                 =  !*Expression $';'
            CompoundStatement                   =  $'{' !*DeclarationList !*StatementList $'}'
            StatementList                       =  %*Statement
            SelectionStatement                  =  *IF $'(' *Expression $')' *Statement !(*ELSE *Statement)
+                                               |  *SWITCH $'(' *Expression $')' *Statement
            IterationStatement                  =  *WHILE $'(' *Expression $')' *Statement
+                                               |  *DO *Statement *WHILE $'(' *Expression $')' $';'
+                                               |  *FOR
+                                                  $'('
+                                                  !*Expression
+                                                  $';'
+                                                  !*Expression
+                                                  $';'
+                                                  !*Expression
+                                                  $')'
+                                                  *Statement
            JumpStatement                       =  *GOTO *IDENTIFIER $';'
+                                               |  *CONTINUE $';'
+                                               |  *BREAK $';'
+                                               |  *RETURN !*Expression $';'
            Expression                          =  *AssignmentExpression !%($',' *AssignmentExpression)
            AssignmentExpression                =  *UnaryExpression *AssignmentOperator *AssignmentExpression
+                                               |  *ConditionalExpression
            AssignmentOperator                  =  $'='
+                                               |  $'*='
+                                               |  $'/='
+                                               |  $'%='
+                                               |  $'+='
+                                               |  $'-='
+                                               |  $'<<='
+                                               |  $'>>='
+                                               |  $'&='
+                                               |  $'^='
+                                               |  $'|='
            ConditionalExpression               =  *LogicalORExpression
+                                                  !($'?' *Expression $':' *ConditionalExpression)
            ConstantExpression                  =  *ConditionalExpression
            LogicalORExpression                 =  *LogicalANDExpression !($'||' *LogicalORExpression)
            LogicalANDExpression                =  *InclusiveORExpression !($'&&' *LogicalANDExpression)
            InclusiveORExpression               =  *ExclusiveORExpression !($'|' *InclusiveORExpression)
            ExclusiveORExpression               =  *ANDExpression !($'^' *ExclusiveORExpression)
            ANDExpression                       =  *EqualityExpression !($'&' *ANDExpression)
            EqualityExpression                  =  *RelationalExpression !(($'==' | $'!=') *EqualityExpression)
            RelationalExpression                =  *ShiftExpression
+                                                  !(($'<' | $'>' | $'<=' | $'>=') *RelationalExpression)
            ShiftExpression                     =  *AdditiveExpression !(($'<<' | $'>>') *ShiftExpression)
            AdditiveExpression                  =  *MultiplicativeExpression !(($'+' | $'-') *AdditiveExpression)
            MultiplicativeExpression            =  *CastExpression !(($'*' | $'/' | $'%') *MultiplicativeExpression)
            CastExpression                      =  $'(' *TypeName $')' *CastExpression | *UnaryExpression
            UnaryExpression                     =  *PostfixExpression
+                                               |  $'++' *UnaryExpression
+                                               |  $'--' *UnaryExpression
+                                               |  *UnaryOperator *CastExpression
+                                               |  *SIZEOF (*UnaryExpression | $'(' *TypeName $')')
            UnaryOperator                       =  $'&' | $'*' | $'+' | $'-' | $'~' | $'!'
            PostfixExpression                   =  *PrimaryExpression
+                                                  !%(
+                                                     $'[' *Expression $']'
+                                                  |  $'(' !*ArgumentExpressionList $')'
+                                                  |  $'.' *IDENTIFIER
+                                                  |  $'->' *IDENTIFIER
+                                                  |  $'++'
+                                                  |  $'--'
+                                                  )
            PrimaryExpression                   =  *IDENTIFIER | *Constant | $'(' *Expression $')'
            ArgumentExpressionList              =  *AssignmentExpression !%($',' *AssignmentExpression)
            Constant                            =  *INTEGER_LITERAL
+                                               |  *FLOATING_POINT_LITERAL
+                                               |  *CHARACTER_LITERAL
+                                               |  *STRING_LITERAL
