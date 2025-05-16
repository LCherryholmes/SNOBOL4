*-------------------------------------------------------------------------------------------------------------------------
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
            fndExt            =     'java' . extc
            fndCmd            =     'd:/mksnt/find d:/jdk1.3 -name "*.java" -print'
*           fndSpecific       =     'ReferenceQueue.java'
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

            keywords          =     'abstract boolean break byte case catch char class '
+                                   'const continue default double do else extends false '
+                                   'finally final float for goto if implements import '
+                                   'instanceof interface int long native new null package '
+                                   'private protected public return short static strictfp '
+                                   'super switch synchronized this throws throw transient '
+                                   'true try void volatile while'
            ident             =     ANY(&UCASE '_' &LCASE) FENCE(SPAN(&UCASE '_' &LCASE '0123456789') | epsilon)
            identifier        =     ident $ tx $ *notmatch(keywords, (POS(0) | ' ') tx (' ' | RPOS(0)))
            keyword           =     ident $ tx $ *match(keywords, (POS(0) | ' ') tx (' ' | RPOS(0)))
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            abstract          =     $' ' TX(2, ident, 'abstract')
            boolean           =     $' ' TX(2, ident, 'boolean')
            break             =     $' ' TX(2, ident, 'break')
            byte              =     $' ' TX(2, ident, 'byte')
            case              =     $' ' TX(2, ident, 'case')
            catch             =     $' ' TX(2, ident, 'catch')
            char              =     $' ' TX(2, ident, 'char')
            class             =     $' ' TX(2, ident, 'class')
            const             =     $' ' TX(2, ident, 'const')
            continue          =     $' ' TX(2, ident, 'continue')
            default           =     $' ' TX(2, ident, 'default')
            double            =     $' ' TX(2, ident, 'double')
            do                =     $' ' TX(2, ident, 'do')
            else              =     $' ' TX(2, ident, 'else')
            extends           =     $' ' TX(2, ident, 'extends')
            false             =     $' ' TX(2, ident, 'false')
            finally           =     $' ' TX(2, ident, 'finally')
            final             =     $' ' TX(2, ident, 'final')
            float             =     $' ' TX(2, ident, 'float')
            for               =     $' ' TX(2, ident, 'for')
            goto              =     $' ' TX(2, ident, 'goto')
            if                =     $' ' TX(2, ident, 'if')
            implements        =     $' ' TX(2, ident, 'implements')
            import            =     $' ' TX(2, ident, 'import')
            instanceof        =     $' ' TX(2, ident, 'instanceof')
            interface         =     $' ' TX(2, ident, 'interface')
            int               =     $' ' TX(2, ident, 'int')
            long              =     $' ' TX(2, ident, 'long')
            native            =     $' ' TX(2, ident, 'native')
            new               =     $' ' TX(2, ident, 'new')
            null              =     $' ' TX(2, ident, 'null')
            package           =     $' ' TX(2, ident, 'package')
            private           =     $' ' TX(2, ident, 'private')
            protected         =     $' ' TX(2, ident, 'protected')
            public            =     $' ' TX(2, ident, 'public')
            return            =     $' ' TX(2, ident, 'return')
            short             =     $' ' TX(2, ident, 'short')
            static            =     $' ' TX(2, ident, 'static')
            strictfp          =     $' ' TX(2, ident, 'strictfp')
            super             =     $' ' TX(2, ident, 'super')
            switch            =     $' ' TX(2, ident, 'switch')
            synchronized      =     $' ' TX(2, ident, 'synchronized')
            this              =     $' ' TX(2, ident, 'this')
            throws            =     $' ' TX(2, ident, 'throws')
            throw             =     $' ' TX(2, ident, 'throw')
            transient         =     $' ' TX(2, ident, 'transient')
            true              =     $' ' TX(2, ident, 'true')
            try               =     $' ' TX(2, ident, 'try')
            void              =     $' ' TX(2, ident, 'void')
            volatile          =     $' ' TX(2, ident, 'volatile')
            while             =     $' ' TX(2, ident, 'while')
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            $'!'              =     $' ' TZ(2, '!', '!')
            $'!='             =     $' ' TZ(2, '!=', '!=')
            $'%'              =     $' ' TZ(2, '%', '%')
            $'%='             =     $' ' TZ(2, '%=', '%=')
            $'&&'             =     $' ' TZ(2, '&&', '&&')
            $'&'              =     $' ' TZ(2, '&', '&')
            $'&='             =     $' ' TZ(2, '&=', '&=')
            $'('              =     $' ' TZ(2, '(', '(')
            $')'              =     $' ' TZ(2, ')', ')')
            $'*'              =     $' ' TZ(2, '*', '*')
            $'*='             =     $' ' TZ(2, '*=', '*=')
            $'+'              =     $' ' TZ(2, '+', '+')
            $'++'             =     $' ' TZ(2, '++', '++')
            $'+='             =     $' ' TZ(2, '+=', '+=')
            $','              =     $' ' TZ(2, ',', ',')
            $'-'              =     $' ' TZ(2, '-', '-')
            $'--'             =     $' ' TZ(2, '--', '--')
            $'-='             =     $' ' TZ(2, '-=', '-=')
            $'.'              =     $' ' TZ(2, '.', '.')
            $'/'              =     $' ' TZ(2, '/', '/')
            $'/='             =     $' ' TZ(2, '/=', '/=')
            $':'              =     $' ' TZ(2, ':', ':')
            $';'              =     $' ' TZ(2, ';', ';')
            $'<'              =     $' ' TZ(2, '<', '<')
            $'<<'             =     $' ' TZ(2, '<<', '<<')
            $'<<='            =     $' ' TZ(2, '<<=', '<<=')
            $'<='             =     $' ' TZ(2, '<=', '<=')
            $'='              =     $' ' TZ(2, '=', '=')
            $'=='             =     $' ' TZ(2, '==', '==')
            $'>'              =     $' ' TZ(2, '>', '>')
            $'>='             =     $' ' TZ(2, '>=', '>=')
            $'>>'             =     $' ' TZ(2, '>>', '>>')
            $'>>='            =     $' ' TZ(2, '>>=', '>>=')
            $'>>>'            =     $' ' TZ(2, '>>>', '>>>')
            $'>>>='           =     $' ' TZ(2, '>>>=', '>>>=')
            $'?'              =     $' ' TZ(2, '?', '?')
            $'['              =     $' ' TZ(2, '[', '[')
            $']'              =     $' ' TZ(2, ']', ']')
            $'^'              =     $' ' TZ(2, '^', '^')
            $'^='             =     $' ' TZ(2, '^=', '^=')
            $'{'              =     $' ' TZ(2, '{', '{')
            $'|'              =     $' ' TZ(2, '|', '|')
            $'|='             =     $' ' TZ(2, '|=', '|=')
            $'||'             =     $' ' TZ(2, '||', '||')
            $'}'              =     $' ' TZ(2, '}', '}')
            $'~'              =     $' ' TZ(2, '~', '~')
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            compilationUnit   =     (*packageDeclaration | epsilon)
+                                   ARBNO(*importDeclaration)
+                                   ARBNO(*typeDeclaration)
+                                   $' ' RPOS(0)

            packageDeclaration =    package *name $';'

            importDeclaration =     import *name ($'.' $'*' | epsilon) $';'

            typeDeclaration   =     FENCE(
+                                      *classDeclaration
+                                   |  *interfaceDeclaration
+                                   |  $';'
+                                   )

            classDeclaration  =     ARBNO(abstract | final | public | strictfp) *unmodifiedClassDeclaration

            unmodifiedClassDeclaration = class $' ' *identifier (extends *name | epsilon) (implements *nameList | epsilon) *classBody

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
+                                   interface $' ' *identifier (extends *nameList | epsilon)
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

            variableDeclaratorId =  $' ' *identifier (*arrayNoDims | epsilon)

            variableInitializer  =  (*arrayInitializer | *expression)

            arrayInitializer  =     $'{' (*variableInitializer ARBNO($',' *variableInitializer) | epsilon) ($',' | epsilon) $'}'

            methodDeclaration =     ARBNO(public | protected | private | static | abstract | final | native | synchronized | strictfp)
+                                   *resultType *methodDeclarator (throws *nameList | epsilon)
+                                   ( *block | $';' )

            methodDeclarator  =     $' ' *identifier *formalParameters (*arrayNoDims | epsilon)

            formalParameters  =     $'(' (*formalParameter ARBNO($',' *formalParameter) | epsilon) $')'

            formalParameter   =     (final | epsilon) *type *variableDeclaratorId

            constructorDeclaration  =
+                                   (public | protected | private | epsilon)
+                                   $' ' *identifier *formalParameters (throws *nameList | epsilon)
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
            name              =     $' ' *identifier FENCE($'.' *name | epsilon)
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
+                                         |  super $'.' $' ' *identifier
+                                         |  $'(' *expression $')'
+                                         |  *allocationExpression
+                                         |  *resultType $'.' class
+                                         |  *name
+                                         )

            primarySuffixes            =  *primarySuffix FENCE(*primarySuffixes | epsilon)
            primarySuffix              =  (  $'.' this
+                                         |  $'.' *allocationExpression
+                                         |  $'[' *expression $']'
+                                         |  $'.' $' ' *identifier
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

            labeledStatement           =  $' ' *identifier $':' *statement
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
            breakStatement             =  break ($' ' *identifier | epsilon) $';'
            continueStatement          =  continue ($' ' *identifier | epsilon) $';'
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
UserRpt     DIFFER(java)                                                                     :f(RETURN)
            XDump('java', java)                                                              :(RETURN)
UserRptEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserTokens()')                                                           :(UserTokensEnd)
UserTokens  tok[t = t + 1] = token(,, .compilationUnit)
            tok[t = t + 1] = token(,, .packageDeclaration)
            tok[t = t + 1] = token(,, .importDeclaration)
            tok[t = t + 1] = token(,, .classDeclaration)
            tok[t = t + 1] = token(,, .interfaceDeclaration)
            tok[t = t + 1] = token(,, .nestedClassDeclaration)
            tok[t = t + 1] = token(,, .nestedInterfaceDeclaration)
            tok[t = t + 1] = token(,, .methodDeclaration)
            tok[t = t + 1] = token(,, .constructorDeclaration)
            tok[t = t + 1] = token(,, .fieldDeclaration)
            tok[t = t + 1] = token(,, .localVariableDeclaration)
            tok[t = t + 1] = token(,, .labeledStatement)
            tok[t = t + 1] = token(,, .block)
            tok[t = t + 1] = token(,, .switchStatement)
            tok[t = t + 1] = token(,, .ifStatement)
            tok[t = t + 1] = token(,, .whileStatement)
            tok[t = t + 1] = token(,, .doStatement)
            tok[t = t + 1] = token(,, .forStatement)
            tok[t = t + 1] = token(,, .breakStatement)
            tok[t = t + 1] = token(,, .continueStatement)
            tok[t = t + 1] = token(,, .returnStatement)
            tok[t = t + 1] = token(,, .throwStatement)
            tok[t = t + 1] = token(,, .synchronizedStatement)
            tok[t = t + 1] = token(,, .tryStatement)
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
