            LCURLYBRACE                         =  '{'
            RCURLYBRACE                         =  '}'
            LSQUAREBRACKET                      =  '['
            RSQUAREBRACKET                      =  ']'
            LPARENTHESIS                        =  '('
            RPARENTHESIS                        =  ')'
            SCOPE                               =  '::'
            COLON                               =  ':'
            SEMICOLON                           =  ';'
            COMMA                               =  ','
            QUESTIONMARK                        =  '?'
            ELLIPSIS                            =  '...'
            ASSIGNEQUAL                         =  '='
            TIMESEQUAL                          =  '*='
            DIVIDEEQUAL                         =  '/='
            MODEQUAL                            =  '%='
            PLUSEQUAL                           =  '+='
            MINUSEQUAL                          =  '-='
            SHIFTLEFTEQUAL                      =  '<<='
            SHIFTRIGHTEQUAL                     =  '>>='
            BITWISEANDEQUAL                     =  '&='
            BITWISEXOREQUAL                     =  '^='
            BITWISEOREQUAL                      =  '|='
            OR                                  =  '||'
            AND                                 =  '&&'
            BITWISEOR                           =  '|'
            BITWISEXOR                          =  '^'
            AMPERSAND                           =  '&'
            EQUAL                               =  '=='
            NOTEQUAL                            =  '!='
            LESSTHAN                            =  '<'
            GREATERTHAN                         =  '>'
            LESSTHANOREQUALTO                   =  '<='
            GREATERTHANOREQUALTO                =  '>='
            SHIFTLEFT                           =  '<<'
            SHIFTRIGHT                          =  '>>'
            PLUS                                =  '+'
            MINUS                               =  '-'
            STAR                                =  '*'
            DIVIDE                              =  '/'
            MOD                                 =  '%'
            PLUSPLUS                            =  '++'
            MINUSMINUS                          =  '--'
            TILDE                               =  '~'
            NOT                                 =  '!'
            DOT                                 =  '.'
            POINTERTO                           =  '->'
            DOTSTAR                             =  '.*'
            ARROWSTAR                           =  '->*'
            AUTO                                =  'auto'
            BREAK                               =  'break'
            CASE                                =  'case'
            CATCH                               =  'catch'
            CHAR                                =  'char'
            CONST                               =  'const'
            CONTINUE                            =  'continue'
            $'_DEFAULT'                         =  'default'
            DELETE                              =  'delete'
            DO                                  =  'do'
            DOUBLE                              =  'double'
            ELSE                                =  'else'
            ENUM                                =  'enum'
            EXTERN                              =  'extern'
            FLOAT                               =  'float'
            FOR                                 =  'for'
            FRIEND                              =  'friend'
            GOTO                                =  'goto'
            IF                                  =  'if'
            INLINE                              =  'inline'
            INT                                 =  'int'
            LONG                                =  'long'
            NEW                                 =  'new'
            PRIVATE                             =  'private'
            PROTECTED                           =  'protected'
            PUBLIC                              =  'public'
            REDECLARED                          =  'redeclared'
            REGISTER                            =  'register'
            RETURN                              =  'return'
            SHORT                               =  'short'
            SIGNED                              =  'signed'
            SIZEOF                              =  'sizeof'
            STATIC                              =  'static'
            STRUCT                              =  'struct'
            CLASS                               =  'class'
            SWITCH                              =  'switch'
            TEMPLATE                            =  'template'
            THIS                                =  'this'
            TRY                                 =  'try'
            TYPEDEF                             =  'typedef'
            UNION                               =  'union'
            UNSIGNED                            =  'unsigned'
            VIRTUAL                             =  'virtual'
            VOID                                =  'void'
            VOLATILE                            =  'volatile'
            WHILE                               =  'while'
            OPERATOR                            =  'operator'
            TRUETOK                             =  'true'
            FALSETOK                            =  'false'
            THROW                               =  'throw'
            OCTALINT                            =  '0' (SPAN('01234567') | epsilon)
            OCTALLONG                           =  *OCTALINT 'l'
            UNSIGNED_OCTALINT                   =  *OCTALINT 'u'
            UNSIGNED_OCTALLONG                  =  *OCTALINT ('ul' | 'lu')
            DECIMALINT                          =  ANY('123456789') (SPAN('0123456789') | epsilon)
            DECIMALLONG                         =  *DECIMALINT ANY('ul')
            UNSIGNED_DECIMALINT                 =  *DECIMALINT 'u'
            UNSIGNED_DECIMALLONG                =  *DECIMALINT ('ul' | 'lu')
            HEXADECIMALINT                      =  '0x' SPAN('0123456789abcdef')
            HEXADECIMALLONG                     =  *HEXADECIMALINT !(ANY('ul'))
            UNSIGNED_HEXADECIMALINT             =  *HEXADECIMALINT 'u'
            UNSIGNED_HEXADECIMALLONG            =  *HEXADECIMALINT ('ul' | 'lu')
            FLOATONE                            =  (  SPAN('0123456789') '.' (SPAN('0123456789') | epsilon)
+                                                  |  (SPAN('0123456789') | epsilon) '.' SPAN('0123456789')
+                                                  )
+                                                  !('e' !(ANY('-+')) SPAN('0123456789'))
+                                                  !(ANY('fl'))
            FLOATTWO                            =  SPAN('0123456789') 'e' !(ANY('-+')) SPAN('0123456789') !(ANY('fl'))
            CHARACTER                           =  !'L'
+                                                  "'"
+                                                  (  NOTANY("'" bSlash nl cr)
+                                                  |  bSlash
+                                                     (  ANY('ntvbrfa' bSlash "?'" '"')
+                                                     |  '0' (SPAN('01234567') | epsilon)
+                                                     |  ANY('123456789') (SPAN('0123456789') | epsilon)
+                                                     |  ('0x' | '0X') SPAN('0123456789abcdefABCDEF')
+                                                     )
+                                                  )
+                                                  "'"
            STRING                              =  !'L'
+                                                  '"'
+                                                  !%(
+                                                     NOTANY('"' bSlash nl cr)
+                                                  |  bSlash
+                                                     (  ANY('ntvbrfa' bSlash "?'" '"')
+                                                     |  '0' (SPAN('01234567') | epsilon)
+                                                     |  ANY('123456789') (SPAN('0123456789') | epsilon)
+                                                     |  ('0x' | '0X') SPAN('0123456789abcdefABCDEF')
+                                                     )
+                                                  )
+                                                  '"'
            translation_unit                    =  !%*external_declaration $' ' RPOS(0)
            external_declaration                =  !*template_head *declaration
+                                               |  *enum_specifier !*init_declarator_list $';'
+                                               |  *dtor_definition
+                                               |  *ctor_definition
+                                               |  *function_definition
+                                               |  *conversion_function_decl_or_def
+                                               |  *template_head
+                                                  (  *ctor_definition
+                                                  |  *function_definition
+                                                  |  *declaration_specifiers !*init_declarator_list $';'
+                                                  )
+                                               |  *declaration
+                                               |  $';'
            function_definition                 =  *declaration_specifiers *function_declarator *func_decl_def
+                                               |  *function_declarator *func_decl_def
            func_decl_def                       =  $';' | *compound_statement
            linkage_specification               =  extern
+                                                  *STRING
+                                                  ($'{' !%*external_declaration $'}' !$';' | *declaration)
            declaration                         =  *declaration_specifiers !*init_declarator_list $';'
+                                               |  *linkage_specification
            type_modifiers                      =  *storage_class_specifier
+                                               |  *type_qualifier
+                                               |  inline
+                                               |  virtual
+                                               |  friend
            declaration_specifiers              =  %*type_modifiers
+                                                  !( *builtin_type_specifier
+                                                     !%(*builtin_type_specifier | *type_modifiers)
+                                                  |  (*class_specifier | *enum_specifier | *qualified_type)
+                                                     !%*type_modifiers
+                                                  )
+                                               |  *builtin_type_specifier
+                                                  !%(*builtin_type_specifier | *type_modifiers)
+                                               |  (*class_specifier | *enum_specifier | *qualified_type)
+                                                  !%*type_modifiers
            simple_type_specifier               =  *builtin_type_specifier | *qualified_type
            scope_override_lookahead            =  $'::' | *ID !($'<' *template_argument_list $'>') $'::'
            scope_override                      =  $'::' !%(*ID !($'<' *template_argument_list $'>') $'::')
+                                               |  %(*ID !($'<' *template_argument_list $'>') $'::')
            qualified_id                        =  !*scope_override
+                                                  (*ID !($'<' *template_argument_list $'>') | operator *optor)
            ptr_to_member                       =  *scope_override $'*'
            qualified_type                      =  *qualified_id
            type_qualifier                      =  const | volatile
            storage_class_specifier             =  auto | register | static | extern | typedef
            builtin_type_specifier              =  void | char | short | int | long | float | double | signed | unsigned
            init_declarator_list                =  *init_declarator !%($',' *init_declarator)
            init_declarator                     =  *declarator !($'=' *initializer | $'(' *expression_list $')')
            class_head                          =  (struct | union | class) !(*ID !*base_clause)
            class_specifier                     =  (struct | union | class)
+                                                  (  $'{' !%*member_declaration $'}'
+                                                  |  *ID !*base_clause $'{' !%*member_declaration $'}'
+                                                  |  *ID !($'<' *template_argument_list $'>')
+                                                  )
            base_clause                         =  $':' *base_specifier !%($',' *base_specifier)
            base_specifier                      =  !(virtual !*access_specifier | *access_specifier !virtual)
+                                                  !*scope_override
+                                                  *ID
+                                                  !($'<' *template_argument_list $'>')
            access_specifier                    =  public | protected | private
            member_declaration                  =  *declaration
+                                               |  *enum_specifier !*member_declarator_list $';'
+                                               |  *conversion_function_decl_or_def
+                                               |  *dtor_definition
+                                               |  *dtor_ctor_decl_spec *simple_dtor_declarator $';'
+                                               |  *ctor_definition
+                                               |  *dtor_ctor_decl_spec *ctor_declarator $';'
+                                               |  *function_definition
+                                               |  *declaration_specifiers !*member_declarator_list $';'
+                                               |  *function_declarator $';'
+                                               |  *qualified_id $';'
+                                               |  *access_specifier $':'
+                                               |  $';'
            member_declarator_list              =  *member_declarator
+                                                  !($'=' *OCTALINT)
+                                                  !%($',' *member_declarator !($'=' *OCTALINT))
            member_declarator                   =  *declarator
            conversion_function_decl_or_def     =  !*scope_override
+                                                  operator
+                                                  *declaration_specifiers
+                                                  !($'*' | $'&')
+                                                  $'('
+                                                  !*parameter_list
+                                                  $')'
+                                                  !*type_qualifier
+                                                  !*exception_spec
+                                                  *func_decl_def
            enum_specifier                      =  enum
+                                                  ($'{' *enumerator_list $'}' | *ID !($'{' *enumerator_list $'}'))
            enumerator_list                     =  *enumerator !%($',' *enumerator)
            enumerator                          =  *ID !($'=' *constant_expression)
            ptr_operator                        =  $'&' *cv_qualifier_seq
+                                               |  $'*' *cv_qualifier_seq
+                                               |  *ptr_to_member *cv_qualifier_seq
            cv_qualifier_seq                    =  !(const !volatile | volatile !const)
            declarator                          =  *ptr_operator *declarator | *direct_declarator
            direct_declarator                   =  $'~' *ID !*declarator_suffixes
+                                               |  $'(' *declarator $')' !*declarator_suffixes
+                                               |  *qualified_id !*declarator_suffixes
            declarator_suffixes                 =  %($'[' !*constant_expression $']')
+                                               |  $'(' !*parameter_list $')' !*type_qualifier !*exception_spec
            function_declarator_lookahead       =  !%*ptr_operator *qualified_id $'('
            function_declarator                 =  *ptr_operator *function_declarator | *function_direct_declarator
            function_direct_declarator          =  *qualified_id
+                                                  $'('
+                                                  !*parameter_list
+                                                  $')'
+                                                  !*type_qualifier
+                                                  !*exception_spec
+                                                  !($'=' *OCTALINT)
            dtor_ctor_decl_spec                 =  !(virtual !inline | inline !virtual)
            dtor_definition                     =  !*template_head
+                                                  *dtor_ctor_decl_spec
+                                                  *dtor_declarator
+                                                  *compound_statement
            ctor_definition                     =  *dtor_ctor_decl_spec
+                                                  *ctor_declarator
+                                                  !*exception_spec
+                                                  ($';' | !*ctor_initializer *compound_statement)
            ctor_declarator_lookahead           =  *qualified_id $'('
            ctor_declarator                     =  *qualified_id $'(' !*parameter_list $')' !*exception_spec
            ctor_initializer                    =  $':' *superclass_init !%($',' *superclass_init)
            superclass_init                     =  *qualified_id $'(' !*expression_list $')'
            dtor_declarator                     =  !*scope_override *simple_dtor_declarator
            simple_dtor_declarator              =  $'~'  *ID $'(' !*parameter_list $')'
            parameter_list                      =  *parameter_declaration_list !(!$',' $'...') | $'...'
            parameter_declaration_list          =  *parameter_declaration !%($',' *parameter_declaration)
            parameter_declaration               =  *declaration_specifiers
+                                                  (*declarator | *abstract_declarator)
+                                                  !($'=' *assignment_expression)
            initializer                         =  $'{' *initializer !%($',' *initializer) $'}' | *assignment_expression
            type_name                           =  *declaration_specifiers *abstract_declarator
            abstract_declarator                 =  !( $'(' *abstract_declarator $')' %*abstract_declarator_suffix
+                                                  |  %($'[' !*constant_expression $']')
+                                                  |  *ptr_operator *abstract_declarator
+                                                  )
            abstract_declarator_suffix          =  $'[' !*constant_expression $']' | $'(' !*parameter_list $')'
            template_head                       =  template $'<' *template_parameter_list $'>'
            template_parameter_list             =  *template_parameter !%($',' *template_parameter)
            template_parameter                  =  class *ID | *parameter_declaration
            template_id                         =  *ID $'<' *template_argument_list $'>'
            template_argument_list              =  *template_argument !%($',' *template_argument)
            template_argument                   =  *type_name | *shift_expression
            statement_list                      =  %*statement
            statement                           =  *declaration
+                                               |  *expression $';'
+                                               |  *compound_statement
+                                               |  *selection_statement
+                                               |  *jump_statement
+                                               |  $';'
+                                               |  *try_block
+                                               |  *throw_statement
+                                               |  *labeled_statement
+                                               |  *iteration_statement
            labeled_statement                   =  *ID $':' *statement
+                                               |  case *constant_expression $':' *statement
+                                               |  default $':' *statement
            compound_statement                  =  $'{' !*statement_list $'}'
            selection_statement                 =  if $'(' *expression $')' *statement !(else *statement)
+                                               |  switch $'(' *expression $')' *statement
            iteration_statement                 =  while $'(' *expression $')' *statement
+                                               |  do *statement while $'(' *expression $')' $';'
+                                               |  for
+                                                  $'('
+                                                  (*declaration | *expression $';' | $';')
+                                                  !*expression
+                                                  $';'
+                                                  !*expression
+                                                  $')'
+                                                  *statement
            jump_statement                      =  goto *ID $';'
+                                               |  continue $';'
+                                               |  break $';'
+                                               |  return !*expression $';'
            try_block                           =  try *compound_statement !%*handler
            handler                             =  catch $'(' *exception_declaration $')' *compound_statement
+                                               |  finally *compound_statement
            exception_declaration               =  *parameter_declaration_list | $'...'
            throw_statement                     =  throw !*assignment_expression $';'
            expression                          =  *assignment_expression !%($',' *assignment_expression)
            assignment_expression               =  *conditional_expression
+                                                  !( (  $'='
+                                                     |  $'*='
+                                                     |  $'/='
+                                                     |  $'%='
+                                                     |  $'+='
+                                                     |  $'-='
+                                                     |  $'<<='
+                                                     |  $'>>='
+                                                     |  $'&='
+                                                     |  $'^='
+                                                     |  $'|='
+                                                     )
+                                                     *assignment_expression
+                                                  )
            conditional_expression              =  *logical_or_expression
+                                                  !($'?' *conditional_expression $':' *conditional_expression)
            constant_expression                 =  *conditional_expression
            logical_or_expression               =  *logical_and_expression !%($'||' *logical_and_expression)
            logical_and_expression              =  *inclusive_or_expression !%($'&&' *inclusive_or_expression)
            inclusive_or_expression             =  *exclusive_or_expression !%($'|' *exclusive_or_expression)
            exclusive_or_expression             =  *and_expression !%($'^' *and_expression)
            and_expression                      =  *equality_expression !%($'&' *equality_expression)
            equality_expression                 =  *relational_expression !%(($'!=' | $'==') *relational_expression)
            relational_expression               =  *shift_expression
+                                                  !%(($'<' | $'>' | $'<=' | $'>=') *shift_expression)
            shift_expression                    =  *additive_expression !%(($'<<' | $'>>') *additive_expression)
            additive_expression                 =  *multiplicative_expression
+                                                  !%(($'+' | $'-') *multiplicative_expression)
            multiplicative_expression           =  *pm_expression !%(($'*' | $'/' | $'%') *pm_expression)
            pm_expression                       =  *cast_expression !%(($'.*' | $'->*') *cast_expression)
            cast_expression                     =  $'(' *type_name $')' *cast_expression | *unary_expression
            unary_expression                    =  $'++' *unary_expression
+                                               |  $'--' *unary_expression
+                                               |  *unary_operator *cast_expression
+                                               |  sizeof ($'(' *type_name $')' | *unary_expression)
+                                               |  *postfix_expression
            new_expression                      =  !$'::'
+                                                  new
+                                                  (  $'(' *type_name $')'
+                                                  |  !($'(' *expression_list $')')
+                                                     ($'(' *type_name $')' | *new_type_id)
+                                                  )
+                                                  !*new_initializer
            new_type_id                         =  *declaration_specifiers !*new_declarator
            new_declarator                      =  *direct_new_declarator
+                                               |  *ptr_operator *cv_qualifier_seq !*new_declarator
            direct_new_declarator               =  %($'[' *expression $']')
            new_initializer                     =  $'(' !*expression_list $')'
            delete_expression                   =  !$'::' delete !($'[' $']') *cast_expression
            unary_operator                      =  $'&' | $'*' | $'+' | $'-' | $'~' | $'!'
            postfix_expression                  =  *primary_expression
+                                                  !%(
+                                                     $'[' *expression $']'
+                                                  |  $'(' !*expression_list $')'
+                                                  |  $'.' *id_expression
+                                                  |  $'->' *id_expression
+                                                  |  $'++'
+                                                  |  $'--'
+                                                  )
+                                               |  *simple_type_specifier $'(' !*expression_list $')'
            id_expression                       =  !*scope_override (*ID | operator *optor | $'~' *ID)
            primary_expression                  =  this
+                                               |  %*STRING
+                                               |  $'(' *expression $')'
+                                               |  *new_expression
+                                               |  *delete_expression
+                                               |  *id_expression
+                                               |  *constant
            expression_list                     =  *assignment_expression !%($',' *assignment_expression)
            constant                            =  *OCTALINT
+                                               |  *OCTALLONG
+                                               |  *DECIMALINT
+                                               |  *DECIMALLONG
+                                               |  *HEXADECIMALINT
+                                               |  *HEXADECIMALLONG
+                                               |  *UNSIGNED_OCTALINT
+                                               |  *UNSIGNED_OCTALLONG
+                                               |  *UNSIGNED_DECIMALINT
+                                               |  *UNSIGNED_DECIMALLONG
+                                               |  *UNSIGNED_HEXADECIMALINT
+                                               |  *UNSIGNED_HEXADECIMALLONG
+                                               |  *CHARACTER
+                                               |  *FLOATONE
+                                               |  *FLOATTWO
+                                               |  true
+                                               |  false
            optor                               =  new !($'[' $']')
+                                               |  delete !($'[' $']')
+                                               |  $'+'
+                                               |  $'-'
+                                               |  $'*'
+                                               |  $'/'
+                                               |  $'%'
+                                               |  $'^'
+                                               |  $'&'
+                                               |  $'|'
+                                               |  $'~'
+                                               |  $'!'
+                                               |  $'='
+                                               |  $'<'
+                                               |  $'>'
+                                               |  $'+='
+                                               |  $'-='
+                                               |  $'*='
+                                               |  $'/='
+                                               |  $'%='
+                                               |  $'^='
+                                               |  $'&='
+                                               |  $'|='
+                                               |  $'<<'
+                                               |  $'>>'
+                                               |  $'>>='
+                                               |  $'<<='
+                                               |  $'=='
+                                               |  $'!='
+                                               |  $'<='
+                                               |  $'>='
+                                               |  $'&&'
+                                               |  $'||'
+                                               |  $'++'
+                                               |  $'--'
+                                               |  $','
+                                               |  $'->*'
+                                               |  $'->'
+                                               |  $'(' $')'
+                                               |  $'[' $']'
+                                               |  *declaration_specifiers !($'*' | $'&')
            exception_spec                      =  throw $'(' *exception_list $')'
            exception_list                      =  *type_name !%($',' *type_name)
            ID                                  =  ANY('abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_')
+                                                  (SPAN('abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_') | epsilon)
