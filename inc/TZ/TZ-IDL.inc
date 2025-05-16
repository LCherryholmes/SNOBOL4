            specification                       =  %*definition
            definition                          =  *type_dcl $';'
+                                               |  *const_dcl $';'
+                                               |  *except_dcl $';'
+                                               |  *interfacex $';'
+                                               |  *module $';'
            module                              =  module *identifier $'{' %*definition $'}'
            interfacex                          =  *interface_dcl | *forward_dcl
            interface_dcl                       =  *interface_header $'{' *interface_body $'}'
            forward_dcl                         =  interface *identifier
            interface_header                    =  interface *identifier !*inheritance_spec
            interface_body                      =  !%*export
            export                              =  *type_dcl $';'
+                                               |  *const_dcl $';'
+                                               |  *except_dcl $';'
+                                               |  *attr_dcl $';'
+                                               |  *op_dcl $';'
            inheritance_spec                    =  $':' *scoped_name !%($',' *scoped_name)
            scoped_name                         =  !$'::' *identifier !%($'::' *identifier)
            const_dcl                           =  const *const_type *identifier $'=' *const_exp
            const_type                          =  *integer_type
+                                               |  *char_type
+                                               |  *boolean_type
+                                               |  *floating_pt_type
+                                               |  *string_type
+                                               |  *scoped_name
            const_exp                           =  *or_expr
            or_expr                             =  *xor_expr !%($'|' *xor_expr)
            xor_expr                            =  *and_expr !%($'^' *and_expr)
            and_expr                            =  *shift_expr !%($'&' *shift_expr)
            shift_expr                          =  *add_expr !%(($'>>' | $'<<') *add_expr)
            add_expr                            =  *mult_expr !%(($'+' | $'-') *mult_expr)
            mult_expr                           =  *unary_expr !%(($'*' | $'/' | $'%') *unary_expr)
            unary_expr                          =  !*unary_operator *primary_expr
            unary_operator                      =  $'-' | $'+' | $'~'
            primary_expr                        =  *scoped_name | *literal | $'(' *const_exp $')'
            literal                             =  *integer_literal
+                                               |  *string_literal
+                                               |  *character_literal
+                                               |  *floating_pt_literal
+                                               |  *boolean_literal
            boolean_literal                     =  TRUE | FALSE
            positive_int_const                  =  *const_exp
            type_dcl                            =  typedef *type_declarator | *struct_type | *union_type | *enum_type
            type_declarator                     =  *type_spec *declarators
            type_spec                           =  *simple_type_spec | *constr_type_spec
            simple_type_spec                    =  *base_type_spec | *template_type_spec | *scoped_name
            base_type_spec                      =  *floating_pt_type
+                                               |  *integer_type
+                                               |  *char_type
+                                               |  *boolean_type
+                                               |  *octet_type
+                                               |  *any_type
            template_type_spec                  =  *sequence_type | *string_type
            constr_type_spec                    =  *struct_type | *union_type | *enum_type
            declarators                         =  *declarator !%($',' *declarator)
            declarator                          =  *complex_declarator | *simple_declarator
            simple_declarator                   =  *identifier
            complex_declarator                  =  *array_declarator
            floating_pt_type                    =  float | double
            integer_type                        =  *signed_int | *unsigned_int
            signed_int                          =  *signed_long_int | *signed_short_int
            signed_long_int                     =  long
            signed_short_int                    =  short
            unsigned_int                        =  *unsigned_long_int | *unsigned_short_int
            unsigned_long_int                   =  unsigned long
            unsigned_short_int                  =  unsigned short
            char_type                           =  char
            boolean_type                        =  boolean
            octet_type                          =  octet
            any_type                            =  any
            struct_type                         =  struct *identifier $'{' *member_list $'}'
            member_list                         =  %*member
            member                              =  *type_spec *declarators $';'
            union_type                          =  union
+                                                  *identifier
+                                                  switch
+                                                  $'('
+                                                  *switch_type_spec
+                                                  $')'
+                                                  $'{'
+                                                  *switch_body
+                                                  $'}'
            switch_type_spec                    =  *integer_type
+                                               |  *char_type
+                                               |  *boolean_type
+                                               |  *enum_type
+                                               |  *scoped_name
            switch_body                         =  %*casex
            casex                               =  %*case_label *element_spec $';'
            case_label                          =  case *const_exp $':' | default $':'
            element_spec                        =  *type_spec *declarator
            enum_type                           =  enum *identifier $'{' *enumerator !%($',' *enumerator) $'}'
            enumerator                          =  *identifier
            sequence_type                       =  sequence $'<' *simple_type_spec !($',' *positive_int_const) $'>'
            string_type                         =  string !($'<' *positive_int_const $'>')
            array_declarator                    =  *identifier %*fixed_array_size
            fixed_array_size                    =  $'[' *positive_int_const $']'
            attr_dcl                            =  !readonly
+                                                  attribute
+                                                  *param_type_spec
+                                                  *simple_declarator
+                                                  !%($',' *simple_declarator)
            except_dcl                          =  exception *identifier $'{' !%*member $'}'
            op_dcl                              =  !*op_attribute
+                                                  *op_type_spec
+                                                  *identifier
+                                                  *parameter_dcls
+                                                  !*raises_expr
+                                                  !*context_expr
            op_attribute                        =  oneway
            op_type_spec                        =  *param_type_spec | void
            parameter_dcls                      =  $'(' !(*param_dcl !%($',' *param_dcl)) $')'
            param_dcl                           =  *param_attribute *param_type_spec *simple_declarator
            param_attribute                     =  in | out | inout
            raises_expr                         =  raises $'(' *scoped_name !%($',' *scoped_name) $')'
            context_expr                        =  context $'(' *string_literal !%($',' *string_literal) $')'
            param_type_spec                     =  *base_type_spec | *string_type | *scoped_name
            identifier                          =  *ID
            integer_literal                     =  *OCTALINT | *DECIMALINT | *HEXADECIMALINT
            string_literal                      =  *STRING
            character_literal                   =  *CHARACTER
            floating_pt_literal                 =  *FLOATONE | *FLOATTWO
            ID                                  =  ANY('abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_')
+                                                  (SPAN('abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_') | epsilon)
            OCTALINT                            =  '0' (SPAN('01234567') | epsilon) !(ANY('uUlL'))
            DECIMALINT                          =  ANY('123456789') (SPAN('0123456789') | epsilon) !(ANY('uUlL'))
            HEXADECIMALINT                      =  ('0x' | '0X') SPAN('0123456789abcdefABCDEF') !(ANY('uUlL'))
            FLOATONE                            =  (  SPAN('0123456789') '.' (SPAN('0123456789') | epsilon)
+                                                  |  (SPAN('0123456789') | epsilon) '.' SPAN('0123456789')
+                                                  )
+                                                  !(ANY('eE') !(ANY('-+')) SPAN('0123456789'))
+                                                  !(ANY('fFlL'))
            FLOATTWO                            =  SPAN('0123456789')
+                                                  ANY('eE')
+                                                  !(ANY('-+'))
+                                                  SPAN('0123456789')
+                                                  !(ANY('fFlL'))
            CHARACTER                           =  "'"
+                                                  (  NOTANY("'" bSlash nl cr)
+                                                  |  bSlash
+                                                     (  ANY('ntvbrfa' bSlash "?'" '"')
+                                                     |  '0' (SPAN('01234567') | epsilon)
+                                                     |  ANY('123456789') (SPAN('0123456789') | epsilon)
+                                                     |  ('0x' | '0X') SPAN('0123456789abcdefABCDEF')
+                                                     )
+                                                  )
+                                                  "'"
            STRING                              =  '"'
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
