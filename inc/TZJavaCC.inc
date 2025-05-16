*-------------------------------------------------------------------------------------------------------------------------
-INCLUDE    'transl8pp.inc'
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserDefs()')                                                             :(UserDefsEnd)
UserDefs    u                 =     0
            usr               =     ARRAY('1:32')
            doDebug           =     0
            doDebugAfter1st   =     FALSE
            doInclWhite       =     TRUE
            doInclNL          =     TRUE
            doReportFileName  =     FALSE
            doRemember        =     TRUE
            fndExt            =     'jj' . extc
            fndCmd            =     'd:/mksnt/find d:/bom -name "*.jj" -print'
            fndSpecific       =     'udb.jj'
*           fndSpecific       =     'CPLUSPLUS.jj'
            fndExclude        =
            keyint            =     ('?') . tx

            blanks            =     SPAN(' ' tab nl cr ff)
            cStyleComment     =     '/*' BREAKX('*') '*/'
            cppStyleComment   =     '//' BREAK(nl) nl
            white             =     blanks | cStyleComment | cppStyleComment
            whitespace        =     white FENCE(*whitespace | epsilon)
            space             =     whitespace
            $' '              =     FENCE(whitespace | epsilon)
            $'  '             =     FENCE(space | epsilon)
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            exponent          =     ('E' | 'e') ('+' | '-' | epsilon) SPAN('0123456789')
            floatingLiteral   =     (  SPAN('0123456789')
+                                      '.' (SPAN('0123456789') | epsilon) (exponent | epsilon) (ANY('FfDd') | epsilon)
+                                   |  '.' SPAN('0123456789') (exponent | epsilon) (ANY('FfDd') | epsilon)
+                                   |  SPAN('0123456789') exponent (ANY('FfDd') | epsilon)
+                                   |  SPAN('0123456789') (exponent | epsilon) ANY('FfDd')
+                                   )
            decimalLiteral    =     ANY('123456789') FENCE(SPAN('0123456789') | epsilon)
            hexLiteral        =     '0' ('X' | 'x') SPAN('0123456789ABCDEFabcdef')
            octalLiteral      =     '0' FENCE(SPAN('01234567') | epsilon)
            integerLiteral    =     (decimalLiteral | hexLiteral | octalLiteral) ('L' | 'l' | epsilon)
            escapedCharacter  =     (  bSlash
+                                      (  ANY('ntbrf' '"' bSlash "'")
+                                      |  ANY('01234567') FENCE(ANY('01234567') | epsilon)
+                                      |  ANY('0123') ANY('01234567') ANY('01234567')
+                                      |  'u' LEN(4) $ tx $ *match(tx, POS(0) SPAN('0123456789ABCDEFabcdef') RPOS(0))
+                                      )
+                                   )

            characterLiteral  =     "'" (NOTANY("'" bSlash cr lf) | escapedCharacter) "'"
            stringLiteral     =     '"' ARBNO(BREAK('"' bSlash cr lf) | escapedCharacter) '"'

            keywords          =     'EOF IGNORE_CASE JAVACODE LOOKAHEAD MORE PARSER_BEGIN PARSER_END '
+                                   'SKIP SPECIAL_TOKEN TOKEN_MGR_DECLS TOKEN '
+                                   'abstract boolean break byte case catch char class '
+                                   'const continue default double do else extends false '
+                                   'finally final float for goto if implements import '
+                                   'instanceof interface int long native new null options package '
+                                   'private protected public return short static strictfp '
+                                   'super switch synchronized this throws throw transient '
+                                   'true try void volatile while'
            operators         =     '~ } || |= | { ^= ^ ] [ ? >>>= >>> >>= >> >= > == = <= <<= << < ; : /= / . -= -- - '
+                                   ', += ++ + *= * ) ( &= && & %= % # != !'
            ident             =     ANY(&UCASE '_' &LCASE) FENCE(SPAN(&UCASE '_' &LCASE '0123456789') | epsilon)
            identifier        =     ident $ tx $ *notmatch(keywords, (POS(0) | ' ') tx (' ' | RPOS(0)))
            keyword           =     ident $ tx $ *match(keywords, (POS(0) | ' ') tx (' ' | RPOS(0)))
            Populate(.TX, ident, keywords,,, operators)
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            javaTokens        =     *javaToken FENCE(*javaTokens | epsilon)
            javaToken         =     $' '
+                                   (  *floatingLiteral
+                                   |  *integerLiteral
+                                   |  *characterLiteral
+                                   |  *stringLiteral
+                                   |  *ident
+                                   |  *operator
+                                   )
            javaBlock         =     $'{' ARBNO(*javaBlockBody) $'}'
            javaExpr          =     $'(' ARBNO(*javaExprBody) $')'
            javaBlockBody     =     *javaToken | *javaExpr | *javaBlock
            javaExprBody      =     *javaToken | *javaExpr

            javacc_input      =     *javacc_options
+                                   PARSER_BEGIN $'(' $' ' *identifier $')'
+                                   *compilationUnit
+                                   PARSER_END $'(' $' ' *identifier $')'
+                                   nPush() *production ARBNO(*production) ('productions' & 'nTop()') nPop()
+                                   $' ' RPOS(0)

            javacc_options    =     (options $'{' *option_binding ARBNO(*option_binding) $'}' | epsilon)

            option_binding    =     ($' ' *identifier | LOOKAHEAD | IGNORE_CASE | static)
+                                   $'='
+                                   ($' ' *integerLiteral | *booleanLiteral | $' ' *stringLiteral)
+                                   $';'

            production        =     (  *javacode_production
+                                   |  *regular_expr_production nInc()
+                                   |  *token_manager_decls
+                                   |  *bnf_production nInc()
+                                   )

            javacode_production =   JAVACODE
+                                   *resultType $' ' *identifier *formalParameters
+                                   (throws *name ARBNO($',' *name) | epsilon)
+                                   (*node_descriptor | epsilon)
+                                   *block

            bnf_production    =     *resultType $' ' *identifier ~ 'identifier' *formalParameters
+                                   (throws *name ARBNO($',' *name) | epsilon)
+                                   (*node_descriptor | epsilon)
+                                   $':'
+                                   *block
+                                   $'{' *bnf_alternates $'}'
+                                   ('bnf_production' & 2)

            regular_expr_production =  (  $'<' $'*' $'>'
+                                      |  $'<' $' ' *identifier ARBNO($',' $' ' *identifier) $'>'
+                                      |  epsilon
+                                      )
+                                      *regexpr_kind ~ 'identifier'
+                                      ($'[' IGNORE_CASE $']' | epsilon) $':'
+                                      $'{'
+                                      nPush()
+                                      *regexpr_spec
+                                      nInc()
+                                      ARBNO($'|' *regexpr_spec nInc())
+                                      $'}' ('re_spec' & 'nTop()') nPop() ('re_production' & 2)

            token_manager_decls     =  TOKEN_MGR_DECLS $':' *classBody

            regexpr_kind            =  (  TOKEN
+                                      |  SPECIAL_TOKEN
+                                      |  SKIP
+                                      |  MORE
+                                      )

            regexpr_spec            =  *regular_expression (*block | epsilon) ($':' $' ' *identifier | epsilon)
            local_lookahead         =  ($' ' *integerLiteral | epsilon)
+                                      ($',' | epsilon)
+                                      (*bnf_alternates . *Pop(.dummy) | epsilon)
+                                      ($',' | epsilon)
+                                      ($'{' *expression $'}' | epsilon)

            bnf_alternates          =  nPush() *bnf_subsequents nInc()
+                                      ARBNO($'|' *bnf_subsequents nInc())
+                                      ('|' & '*(GT(nTop(), 1) nTop())')
+                                      nPop()

            bnf_subsequents         =  nPush()
+                                      (LOOKAHEAD $'(' *local_lookahead $')' | epsilon)
+                                      *bnf_element (*node_descriptor | epsilon) nInc()
+                                      ARBNO(*bnf_element (*node_descriptor | epsilon) nInc())
+                                      ('&' & '*(GT(nTop(), 1) nTop())')
+                                      nPop()

            bnf_element             =  (  LOOKAHEAD $'(' *local_lookahead $')' epsilon ~ ''
+                                      |  *block nDec()
+                                      |  $'[' *bnf_alternates ('?' & 1) $']'
+                                      |  try $'{' *bnf_alternates ('{}' & 1) $'}'
+                                         ARBNO(catch $'(' *name $' ' *identifier $')' *block)
+                                         (finally *block | epsilon)
+                                      |  (*primaryExpression $'=' | epsilon)
+                                         (  *regular_expression
+                                         |  $' ' *identifier ~ 'identifier' *arguments
+                                         )
+                                      |  $'(' *bnf_alternates $')'
+                                         (  $'+' ('+' & 1)
+                                         |  $'*' ('*' & 1)
+                                         |  $'?' ('?' & 1)
+                                         |  epsilon
+                                         )
+                                      )

            regular_expression      =  (  $' ' *stringLiteral ~ 'string'
+                                      |  $'<'
+                                         ( ($'#' | epsilon) $' ' *identifier ~ 'identifier' $':'
+                                         | epsilon ~ ''
+                                         )
+                                         *re_alternates
+                                         ('re' & 2)
+                                         $'>'
+                                      |  $'<' $' ' *identifier ~ 'identifier' $'>'
+                                      |  $'<' EOF ~ 'identifier' $'>'
+                                      )

            re_alternates           =  nPush()
+                                      *re_subsequents nInc()
+                                      ARBNO($'|' *re_subsequents nInc())
+                                      ('|' & '*(GT(nTop(), 1) nTop())')
+                                      nPop()

            re_subsequents          =  nPush()
+                                      *re_element nInc()
+                                      ARBNO(*re_element nInc())
+                                      ('&' & '*(GT(nTop(), 1) nTop())')
+                                      nPop()

            re_element              =
+                                      (  $' ' *stringLiteral ~ 'string'
+                                      |  $'<' $' ' *identifier ~ 'identifier' $'>'
+                                      |  *character_list
+                                      |  $'(' *re_alternates $')'
+                                         (  $'+' ('+' & 1)
+                                         |  $'*' ('*' & 1)
+                                         |  $'?' ('?' & 1)
+                                         | epsilon
+                                         )
+                                      )

            character_list          =  $'['
+                                      (  nPush()
+                                         *character_descriptor nInc()
+                                         ARBNO($',' *character_descriptor nInc()) ('[]' & 'nTop()')
+                                         nPop()
+                                      |  epsilon ~ '' ('[]' & 1)
+                                      )
+                                      $']'
+                                   |  $'~' $'['
+                                      (  nPush()
+                                         *character_descriptor nInc()
+                                         ARBNO($',' *character_descriptor nInc()) ('~[]' & 'nTop()')
+                                         nPop()
+                                      |  epsilon ~ '' ('~[]' & 1)
+                                      )
+                                      $']'

            character_descriptor    =  $' ' *stringLiteral ~ 'string'
+                                      (  $'-' $' ' *stringLiteral ~ 'string' ('-' & 2)
+                                      |  epsilon ('-' & 1)
+                                      )

            node_descriptor   =     $"#" ($' ' *identifier | void) (*javaExpr | epsilon)

            javaIdentifier    =     (  $' ' *identifier
+                                   |  options
+                                   |  LOOKAHEAD
+                                   |  IGNORE_CASE
+                                   |  PARSER_BEGIN
+                                   |  PARSER_END
+                                   |  JAVACODE
+                                   |  TOKEN
+                                   |  SPECIAL_TOKEN
+                                   |  MORE
+                                   |  SKIP
+                                   |  TOKEN_MGR_DECLS
+                                   |  EOF
+                                   )

            compilationUnit   =     (*packageDeclaration | epsilon)
+                                   ARBNO(*importDeclaration)
+                                   ARBNO(*typeDeclaration)

            javaCompilationUnit =   *compilationUnit $' ' RPOS(0)

            packageDeclaration =    package *name $';'

            importDeclaration =     import *name ($'.' $'*' | epsilon) $';'

            typeDeclaration   =     FENCE(
+                                      *classDeclaration
+                                   |  *interfaceDeclaration
+                                   |  $';'
+                                   )

            classDeclaration  =     ARBNO(abstract | final | public | strictfp) *unmodifiedClassDeclaration

            unmodifiedClassDeclaration = class $' ' *javaIdentifier (extends *name | epsilon) (implements *nameList | epsilon) *classBody

            classBody         =     $'{' ARBNO(*classBodyDeclaration) $'}'

            nestedClassDeclaration =
+                                   ARBNO(static | abstract | final | public | protected | private | strictfp)
+                                   *unmodifiedClassDeclaration

            classBodyDeclaration =  FENCE(
+                                      *initializer
+                                   |  *nestedClassDeclaration
+                                   |  *nestedInterfaceDeclaration
+                                   |  *constructorDeclaration
+                                   |  *methodDeclaration
+                                   |  *fieldDeclaration
+                                   |  $';'
+                                   )

            interfaceDeclaration = ARBNO(abstract | public | strictfp) *unmodifiedInterfaceDeclaration

            nestedInterfaceDeclaration =
+                                   ARBNO(static | abstract | final | public | protected | private | strictfp)
+                                   *unmodifiedInterfaceDeclaration

            unmodifiedInterfaceDeclaration   =
+                                   interface $' ' *javaIdentifier (extends *nameList | epsilon)
+                                   $'{' ARBNO(*interfaceMemberDeclaration) $'}'

            interfaceMemberDeclaration =
+                                   (  *nestedClassDeclaration
+                                   |  *nestedInterfaceDeclaration
+                                   |  *methodDeclaration
+                                   |  *fieldDeclaration
+                                   |  $';'
+                                   )

            fieldDeclaration  =
+                                   ARBNO(public | protected | private | static | final | transient | volatile)
+                                   *type *variableDeclarator ARBNO($',' *variableDeclarator) $';'

            variableDeclarator   =  *variableDeclaratorId FENCE($'=' *variableInitializer | epsilon)

            variableDeclaratorId =  $' ' *javaIdentifier (*arrayNoDims | epsilon)

            variableInitializer  =  (*arrayInitializer | *expression)

            arrayInitializer  =     $'{' (*variableInitializer ARBNO($',' *variableInitializer) | epsilon) ($',' | epsilon) $'}'

            methodDeclaration =     ARBNO(public | protected | private | static | abstract | final | native | synchronized | strictfp)
+                                   *resultType *methodDeclarator (throws *nameList | epsilon)
+                                   ( *block | $';' )

            methodDeclarator  =     $' ' *javaIdentifier *formalParameters (*arrayNoDims | epsilon)

            formalParameters  =     $'(' (*formalParameter ARBNO($',' *formalParameter) | epsilon) $')'

            formalParameter   =     (final | epsilon) *type *variableDeclaratorId

            constructorDeclaration  =
+                                   (public | protected | private | epsilon)
+                                   $' ' *javaIdentifier *formalParameters (throws *nameList | epsilon)
+                                   $'{'
+                                   (*explicitConstructorInvocation | epsilon)
+                                   ARBNO(*blockStatement)
+                                   $'}'

            explicitConstructorInvocation =
+                                   (  this *arguments $';'
+                                   |  (*primaryExpression $'.' | epsilon) super *arguments $';'
+                                   )

            initializer       =     (static | epsilon) *block

            type              =     (*primitiveType | *name) FENCE(*arrayNoDims | epsilon)

            primitiveType     =     (  boolean
+                                   |  char
+                                   |  byte
+                                   |  short
+                                   |  int
+                                   |  long
+                                   |  float
+                                   |  double
+                                   )

            resultType        =     (void | *type)
            name              =     $' ' *javaIdentifier FENCE($'.' *name | epsilon)
            nameList          =     *name FENCE($',' *nameList | epsilon)

            expression        =     *conditionalExpression (*assignmentOperator *expression | epsilon)

            assignmentOperator =    (  $'='
+                                   |  $'*='
+                                   |  $'/='
+                                   |  $'%='
+                                   |  $'+='
+                                   |  $'-='
+                                   |  $'<<='
+                                   |  $'>>='
+                                   |  $'>>>='
+                                   |  $'&='
+                                   |  $'^='
+                                   |  $'|='
+                                   )

            conditionalExpression      =  *conditionalOrExpression  ($'?' *expression $':' *conditionalExpression | epsilon)
            conditionalOrExpression    =  *conditionalAndExpression ($'||' *conditionalOrExpression | epsilon)
            conditionalAndExpression   =  *inclusiveOrExpression    ($'&&' *conditionalAndExpression | epsilon)
            inclusiveOrExpression      =  *exclusiveOrExpression    ($'|'  *inclusiveOrExpression | epsilon)
            exclusiveOrExpression      =  *andExpression            ($'^'  *exclusiveOrExpression | epsilon)
            andExpression              =  *equalityExpression       ($'&'  *andExpression | epsilon)
            equalityExpression         =  *instanceOfExpression     (($'==' | $'!=') *equalityExpression | epsilon)
            instanceOfExpression       =  *relationalExpression     (instanceof *type | epsilon)
            relationalExpression       =  *shiftExpression          (($'<' | $'>' | $'<=' | $'>=') *relationalExpression | epsilon)
            shiftExpression            =  *additiveExpression       (($'<<' | $'>>' | $'>>>')      *shiftExpression | epsilon)
            additiveExpression         =  *multiplicativeExpression (($'+' | $'-')                 *additiveExpression | epsilon)
            multiplicativeExpression   =  *unaryExpression          (($'*' | $'/' | $'%')          *multiplicativeExpression | epsilon)

            unaryExpression            =  (  ($'+' | $'-') *unaryExpression
+                                         |  *preIncrementExpression
+                                         |  *preDecrementExpression
+                                         |  *unaryExpressionNotPlusMinus
+                                         )
            preIncrementExpression     =  $'++' *primaryExpression
            preDecrementExpression     =  $'--' *primaryExpression

            unaryExpressionNotPlusMinus = (  ($'~' | $'!') *unaryExpression
+                                         |  *castExpression
+                                         |  *postfixExpression
+                                         )

            postfixExpression          =  *primaryExpression ($'++' | $'--' | epsilon)

            castExpression             =  (  $'(' *type $')' *unaryExpression
+                                         |  $'(' *type $')' *unaryExpressionNotPlusMinus
+                                         )

            primaryExpression          =  *primaryPrefix (*primarySuffixes | epsilon)

            primaryPrefix              =  (  *literal
+                                         |  this
+                                         |  super $'.' $' ' *javaIdentifier
+                                         |  $'(' *expression $')'
+                                         |  *allocationExpression
+                                         |  *resultType $'.' class
+                                         |  *name
+                                         )

            primarySuffixes            =  *primarySuffix FENCE(*primarySuffixes | epsilon)
            primarySuffix              =  (  $'.' this
+                                         |  $'.' *allocationExpression
+                                         |  $'[' *expression $']'
+                                         |  $'.' $' ' *javaIdentifier
+                                         |  *arguments
+                                         )

            literal                    =  (  $' ' *floatingLiteral
+                                         |  $' ' *integerLiteral
+                                         |  $' ' *characterLiteral
+                                         |  $' ' *stringLiteral
+                                         |  *booleanLiteral
+                                         |  *nullLiteral
+                                         )

            booleanLiteral             =  true | false
            nullLiteral                =  null
            arguments                  =  $'(' (*argumentList | epsilon) $')'
            argumentList               =  *expression FENCE($',' *argumentList | epsilon)
            allocationExpression       =  (  new *primitiveType *arrayDimsAndInits
+                                         |  new *name
+                                            (  *arrayDimsAndInits
+                                            |  *arguments (*classBody | epsilon)
+                                            )
+                                         )
            arrayDims                  =  $'[' *expression $']' FENCE(*arrayDims | epsilon)
            arrayNoDims                =  $'[' $']' FENCE(*arrayNoDims | epsilon)
            arrayDimsAndInits          =  (  *arrayDims FENCE(*arrayNoDims | epsilon)
+                                         |  *arrayNoDims *arrayInitializer
+                                         )

            statement                  =  FENCE(
+                                            *labeledStatement
+                                         |  *block
+                                         |  $';'
+                                         |  *statementExpression $';'
+                                         |  *switchStatement
+                                         |  *ifStatement
+                                         |  *whileStatement
+                                         |  *doStatement
+                                         |  *forStatement
+                                         |  *breakStatement
+                                         |  *continueStatement
+                                         |  *returnStatement
+                                         |  *throwStatement
+                                         |  *synchronizedStatement
+                                         |  *tryStatement
+                                         )

            labeledStatement           =  $' ' *javaIdentifier $':' *statement
            block                      =  $'{' ARBNO(*blockStatement) $'}'
            blockStatement             =  (  *localVariableDeclaration $';'
+                                         |  *statement
+                                         |  *unmodifiedClassDeclaration
+                                         |  *unmodifiedInterfaceDeclaration
+                                         )
            localVariableDeclaration   =  (final | epsilon) *type *variableDeclarator ARBNO($',' *variableDeclarator)
            statementExpression        =  (  *preIncrementExpression
+                                         |  *preDecrementExpression
+                                         |  *primaryExpression ($'++' | $'--' | *assignmentOperator *expression | epsilon)
+                                         )
            switchStatement            =  switch $'(' *expression $')'
+                                         $'{'
+                                         ARBNO(*switchLabel ARBNO(*blockStatement))
+                                         $'}'
            switchLabel                =  (  case *expression $':'
+                                         |  default $':'
+                                         )
            ifStatement                =  if $'(' *expression $')' *statement FENCE(else *statement | epsilon)
            whileStatement             =  while $'(' *expression $')' *statement
            doStatement                =  do *statement while $'(' *expression $')' $';'
            forStatement               =  for $'('
+                                         (*forInit | epsilon) $';'
+                                         (*expression | epsilon) $';'
+                                         (*forUpdate | epsilon)
+                                         $')' *statement
            forInit                    =  (  *localVariableDeclaration
+                                         |  *statementExpressionList
+                                         )
            statementExpressionList    =  *statementExpression FENCE($',' *statementExpressionList | epsilon)
            forUpdate                  =  *statementExpressionList
            breakStatement             =  break ($' ' *javaIdentifier | epsilon) $';'
            continueStatement          =  continue ($' ' *javaIdentifier | epsilon) $';'
            returnStatement            =  return (*expression | epsilon) $';'
            throwStatement             =  throw *expression $';'
            synchronizedStatement      =  synchronized $'(' *expression $')' *block
            catchClause                =  catch $'(' *formalParameter $')' *block
            catchClauses               =  *catchClause FENCE(*catchClauses | epsilon)
            tryStatement               =  try *block FENCE(*catchClauses | epsilon) (finally *block | epsilon)

                                                                                             :(RETURN)
UserDefsEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserRpt()')                                                              :(UserRptEnd)
UserRpt     jj                =     Pop()                                                    :f(RETURN)
            DIFFER(jj)                                                                       :f(RETURN)
            basenm            =     splitname(pathnm)[2]
            basenm            '.' fndExt RPOS(0) =
            lispnm            =     basenm '.lisp'
            OUTPUT(.OUTPUT, 2, lispnm)                                                       :f(xerr)
            SetLevel(0)
            TDump(jj)
            ENDFILE(2)
            incnm             =     'transl8-' basenm '.inc'
            OUTPUT(.OUTPUT, 2, incnm)                                                        :f(xerr)
            ppOps             =     TRUE
            pp(jj)
            ENDFILE(2)                                                                       :(RETURN)
UserRptEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserFinal()')                                                            :(UserFinalEnd)
UserFinal                                                                                    :(RETURN)
UserFinalEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserTokens()')                                                           :(UserTokensEnd)
UserTokens  tok[t = t + 1] = token(,, .javacc_input)
            tok[t = t + 1] = token(,, .javacc_options)
            tok[t = t + 1] = token(,, .production)
            tok[t = t + 1] = token(,, .javacode_production)
            tok[t = t + 1] = token(,, .regular_expr_production)
            tok[t = t + 1] = token(,, .token_manager_decls)
            tok[t = t + 1] = token(,, .bnf_production)
            tok[t = t + 1] = token(,, .floatingLiteral)
            tok[t = t + 1] = token(,, .integerLiteral)
            tok[t = t + 1] = token(,, .characterLiteral)
            tok[t = t + 1] = token(,, .stringLiteral)
            tok[t = t + 1] = token(, *(tx), *keyword)
            tok[t = t + 1] = token(,, .identifier)
            tok[t = t + 1] = token('!=')
            tok[t = t + 1] = token('!')
            tok[t = t + 1] = token('%=')
            tok[t = t + 1] = token('%')
            tok[t = t + 1] = token('&&')
            tok[t = t + 1] = token('&=')
            tok[t = t + 1] = token('&')
            tok[t = t + 1] = token('(')
            tok[t = t + 1] = token(')')
            tok[t = t + 1] = token('*=')
            tok[t = t + 1] = token('*')
            tok[t = t + 1] = token('++')
            tok[t = t + 1] = token('+=')
            tok[t = t + 1] = token('+')
            tok[t = t + 1] = token(',')
            tok[t = t + 1] = token('--')
            tok[t = t + 1] = token('-=')
            tok[t = t + 1] = token('-')
            tok[t = t + 1] = token('.')
            tok[t = t + 1] = token('/=')
            tok[t = t + 1] = token('/')
            tok[t = t + 1] = token(':')
            tok[t = t + 1] = token(';')
            tok[t = t + 1] = token('<<=')
            tok[t = t + 1] = token('<<')
            tok[t = t + 1] = token('<=')
            tok[t = t + 1] = token('<')
            tok[t = t + 1] = token('==')
            tok[t = t + 1] = token('=')
            tok[t = t + 1] = token('>>>=')
            tok[t = t + 1] = token('>>>')
            tok[t = t + 1] = token('>>=')
            tok[t = t + 1] = token('>>')
            tok[t = t + 1] = token('>=')
            tok[t = t + 1] = token('>')
            tok[t = t + 1] = token('?')
            tok[t = t + 1] = token('[')
            tok[t = t + 1] = token(']')
            tok[t = t + 1] = token('^=')
            tok[t = t + 1] = token('^')
            tok[t = t + 1] = token('{')
            tok[t = t + 1] = token('|=')
            tok[t = t + 1] = token('||')
            tok[t = t + 1] = token('|')
            tok[t = t + 1] = token('}')
            tok[t = t + 1] = token('~')

            dbg[.javaBlock]                        = TRUE
            dbg[.javaExpr]                         = TRUE
            dbg[.option_binding]                   = TRUE
            dbg[.regexpr_kind]                     = TRUE
            dbg[.regexpr_spec]                     = TRUE
            dbg[.bnf_alternates]                   = TRUE
            dbg[.bnf_subsequents]                  = TRUE
            dbg[.local_lookahead]                  = TRUE
            dbg[.bnf_element]                      = TRUE
            dbg[.regular_expression]               = TRUE
            dbg[.re_alternates]                    = TRUE
            dbg[.re_subsequents]                   = TRUE
            dbg[.re_element]                       = TRUE
            dbg[.character_list]                   = TRUE
            dbg[.character_descriptor]             = TRUE

            dbg[.compilationUnit]                  = TRUE
            dbg[.packageDeclaration]               = TRUE
            dbg[.importDeclaration]                = TRUE
            dbg[.classDeclaration]                 = TRUE
            dbg[.interfaceDeclaration]             = TRUE
            dbg[.nestedClassDeclaration]           = TRUE
            dbg[.nestedInterfaceDeclaration]       = TRUE
            dbg[.methodDeclaration]                = TRUE
            dbg[.constructorDeclaration]           = TRUE
            dbg[.fieldDeclaration]                 = TRUE
            dbg[.localVariableDeclaration]         = TRUE
            dbg[.labeledStatement]                 = TRUE
            dbg[.block]                            = TRUE
            dbg[.switchStatement]                  = TRUE
            dbg[.ifStatement]                      = TRUE
            dbg[.whileStatement]                   = TRUE
            dbg[.doStatement]                      = TRUE
            dbg[.forStatement]                     = TRUE
            dbg[.breakStatement]                   = TRUE
            dbg[.continueStatement]                = TRUE
            dbg[.returnStatement]                  = TRUE
            dbg[.throwStatement]                   = TRUE
            dbg[.synchronizedStatement]            = TRUE
            dbg[.tryStatement]                     = TRUE

            dbg[.additiveExpression]               = TRUE
            dbg[.allocationExpression]             = TRUE
            dbg[.andExpression]                    = TRUE
            dbg[.argumentList]                     = TRUE
            dbg[.arguments]                        = TRUE
            dbg[.arrayDimsAndInits]                = TRUE
            dbg[.arrayDims]                        = TRUE
            dbg[.arrayInitializer]                 = TRUE
            dbg[.arrayNoDims]                      = TRUE
            dbg[.assignmentOperator]               = TRUE
            dbg[.blockStatement]                   = TRUE
            dbg[.booleanLiteral]                   = TRUE
            dbg[.castExpression]                   = TRUE
            dbg[.classBodyDeclaration]             = TRUE
            dbg[.classBody]                        = TRUE
            dbg[.conditionalAndExpression]         = TRUE
            dbg[.conditionalExpression]            = TRUE
            dbg[.conditionalOrExpression]          = TRUE
            dbg[.decimalLiteral]                   = TRUE
            dbg[.equalityExpression]               = TRUE
            dbg[.escapedCharacter]                 = TRUE
            dbg[.exclusiveOrExpression]            = TRUE
            dbg[.explicitConstructorInvocation]    = TRUE
            dbg[.exponent]                         = TRUE
            dbg[.expression]                       = TRUE
            dbg[.forInit]                          = TRUE
            dbg[.forUpdate]                        = TRUE
            dbg[.formalParameter]                  = TRUE
            dbg[.formalParameters]                 = TRUE
            dbg[.hexLiteral]                       = TRUE
            dbg[.inclusiveOrExpression]            = TRUE
            dbg[.initializer]                      = TRUE
            dbg[.instanceOfExpression]             = TRUE
            dbg[.interfaceMemberDeclaration]       = TRUE
            dbg[.literal]                          = TRUE
            dbg[.methodDeclarator]                 = TRUE
            dbg[.multiplicativeExpression]         = TRUE
            dbg[.nameList]                         = TRUE
            dbg[.name]                             = TRUE
            dbg[.name]                             = TRUE
            dbg[.nullLiteral]                      = TRUE
            dbg[.octalLiteral]                     = TRUE
            dbg[.postfixExpression]                = TRUE
            dbg[.preDecrementExpression]           = TRUE
            dbg[.preIncrementExpression]           = TRUE
            dbg[.primaryExpression]                = TRUE
            dbg[.primaryPrefix]                    = TRUE
            dbg[.primarySuffix]                    = TRUE
            dbg[.primitiveType]                    = TRUE
            dbg[.relationalExpression]             = TRUE
            dbg[.resultType]                       = TRUE
            dbg[.shiftExpression]                  = TRUE
            dbg[.statementExpressionList]          = TRUE
            dbg[.statementExpression]              = TRUE
            dbg[.statement]                        = TRUE
            dbg[.switchLabel]                      = TRUE
            dbg[.typeDeclaration]                  = TRUE
            dbg[.type]                             = TRUE
            dbg[.unaryExpressionNotPlusMinus]      = TRUE
            dbg[.unaryExpression]                  = TRUE
            dbg[.unmodifiedClassDeclaration]       = TRUE
            dbg[.unmodifiedInterfaceDeclaration]   = TRUE
            dbg[.variableDeclaratorId]             = TRUE
            dbg[.variableDeclarator]               = TRUE
            dbg[.variableInitializer]              = TRUE
                                                                                             :(RETURN)
UserTokensEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
