            sql_prog                            =  *schema | *select_stmt | *view | *module
            schema                              =  *Create *Schema *Authorization *Identifier
+                                               |  *Create *Schema *Authorization *Identifier *schemaelements
            schemaelements                      =  *schemaelement | *schemaelements *schemaelement
            schemaelement                       =  *basetable | *view | *privilege
            basetable                           =  *Create *Table *Identifier $'(' *basetableelement_list $')'
+                                               |  *Create
+                                                  *Table
+                                                  *Identifier
+                                                  $'.'
+                                                  *Identifier
+                                                  $'('
+                                                  *basetableelement_list
+                                                  $')'
            basetableelement_list               =  *basetableelement | *basetableelement_list $',' *basetableelement
            basetableelement                    =  *column | *unique
            column                              =  *Identifier *type
+                                               |  *Identifier *type *Not Null
+                                               |  *Identifier *type *Not Null *Unique
            unique                              =  *Unique $'(' *identifier_list $')'
            view                                =  *Create
+                                                  *View
+                                                  *Identifier
+                                                  $'('
+                                                  *identifier_list
+                                                  $')'
+                                                  *As
+                                                  *queryspec
+                                                  *With
+                                                  *Check
+                                                  *Option
+                                               |  *Create *View *Identifier $'(' *identifier_list $')' *As *queryspec
+                                               |  *Create *View *Identifier *As *queryspec *With *Check *Option
+                                               |  *Create *View *Identifier *As *queryspec
+                                               |  *Create
+                                                  *View
+                                                  *Identifier
+                                                  $'.'
+                                                  *Identifier
+                                                  $'('
+                                                  *identifier_list
+                                                  $')'
+                                                  *As
+                                                  *queryspec
+                                                  *With
+                                                  *Check
+                                                  *Option
+                                               |  *Create
+                                                  *View
+                                                  *Identifier
+                                                  $'.'
+                                                  *Identifier
+                                                  $'('
+                                                  *identifier_list
+                                                  $')'
+                                                  *As
+                                                  *queryspec
+                                               |  *Create
+                                                  *View
+                                                  *Identifier
+                                                  $'.'
+                                                  *Identifier
+                                                  *As
+                                                  *queryspec
+                                                  *With
+                                                  *Check
+                                                  *Option
+                                               |  *Create *View *Identifier $'.' *Identifier *As *queryspec
            privilege                           =  *Grant *privileges *On *Identifier *To *grantee_list
+                                               |  *Grant
+                                                  *privileges
+                                                  *On
+                                                  *Identifier
+                                                  *To
+                                                  *grantee_list
+                                                  *With
+                                                  *Grant
+                                                  *Option
+                                               |  *Grant
+                                                  *privileges
+                                                  *On
+                                                  *Identifier
+                                                  $'.'
+                                                  *Identifier
+                                                  *To
+                                                  *grantee_list
+                                               |  *Grant
+                                                  *privileges
+                                                  *On
+                                                  *Identifier
+                                                  $'.'
+                                                  *Identifier
+                                                  *To
+                                                  *grantee_list
+                                                  *With
+                                                  *Grant
+                                                  *Option
            privileges                          =  *All *Privileges | *All | *operation_list
            grantee_list                        =  *Public
+                                               |  *Identifier
+                                               |  *grantee_list $',' *Public
+                                               |  *grantee_list $',' *Identifier
            operation_list                      =  *operation | *operation_list $',' *operation
            operation                           =  *Select
+                                               |  *Insert
+                                               |  *Delete
+                                               |  *Update
+                                               |  *Update $'(' *identifier_list $')'
            module                              =  *Module *Identifier *Language *language *cursor *procedure
+                                               |  *Module *Identifier *Language *language *procedure
+                                               |  *Module *Language *language *cursor *procedure
+                                               |  *Module *Language *language *procedure
            language                            =  *Cobol | *Fortran | *Pascal | *PL1
            cursor                              =  *Declare *Identifier *Cursor *For *queryexpr *orderby
+                                               |  *Declare *Identifier *Cursor *For *queryexpr
            orderby                             =  *Order *By *orderspec_list
            orderspec_list                      =  *orderspec | *orderspec_list $',' *orderspec
            orderspec                           =  *Integer *Asc | *Integer *Desc | *col *Asc | *col *Desc
            procedure                           =  *Procedure *Identifier *parameter_list $';' *statements $';'
            parameter_list                      =  *parameter | *parameter_list *parameter
            parameter                           =  *Identifier *type | *SQLCode
            statements                          =  *statement | *statements *statement
            statement                           =  *close_stmt
+                                               |  *commit_stmt
+                                               |  *delete_stmt
+                                               |  *fetch_stmt
+                                               |  *insert_stmt
+                                               |  *open_stmt
+                                               |  *roll_stmt
+                                               |  *select_stmt
+                                               |  *update_stmt
            close_stmt                          =  *Close *Identifier
            commit_stmt                         =  *Commit *Work
            delete_stmt                         =  *Delete *From *Identifier *Where *Current *Of *Identifier
+                                               |  *Delete *From *Identifier *where
+                                               |  *Delete
+                                                  *From
+                                                  *Identifier
+                                                  $'.'
+                                                  *Identifier
+                                                  *Where
+                                                  *Current
+                                                  *Of
+                                                  *Identifier
+                                               |  *Delete *From *Identifier $'.' *Identifier *where
            fetch_stmt                          =  *Fetch *Identifier *Into *col_list
            insert_stmt                         =  *Insert
+                                                  *Into
+                                                  *Identifier
+                                                  $'('
+                                                  *identifier_list
+                                                  $')'
+                                                  *Values
+                                                  $'('
+                                                  *atomnull_list
+                                                  $')'
+                                               |  *Insert *Into *Identifier $'(' *identifier_list $')' *queryspec
+                                               |  *Insert *Into *Identifier *Values $'(' *atomnull_list $')'
+                                               |  *Insert *Into *Identifier *queryspec
+                                               |  *Insert
+                                                  *Into
+                                                  *Identifier
+                                                  $'.'
+                                                  *Identifier
+                                                  $'('
+                                                  *identifier_list
+                                                  $')'
+                                                  *Values
+                                                  $'('
+                                                  *atomnull_list
+                                                  $')'
+                                               |  *Insert
+                                                  *Into
+                                                  *Identifier
+                                                  $'.'
+                                                  *Identifier
+                                                  $'('
+                                                  *identifier_list
+                                                  $')'
+                                                  *queryspec
+                                               |  *Insert
+                                                  *Into
+                                                  *Identifier
+                                                  $'.'
+                                                  *Identifier
+                                                  *Values
+                                                  $'('
+                                                  *atomnull_list
+                                                  $')'
+                                               |  *Insert *Into *Identifier $'.' *Identifier *queryspec
            atomnull_list                       =  *atomnull | *atomnull_list $',' *atomnull
            atomnull                            =  *atom | Null
            open_stmt                           =  *Open *Identifier
            roll_stmt                           =  *Rollback *Work
            select_stmt                         =  *Select *Distinct *selection *Into *col_list *tableexpr
+                                               |  *Select *All *selection *Into *col_list *tableexpr
+                                               |  *Select *selection *Into *col_list *tableexpr
            update_stmt                         =  *Update
+                                                  *Identifier
+                                                  *Set
+                                                  *assignment_list
+                                                  *Where
+                                                  *Current
+                                                  *Of
+                                                  *Identifier
+                                               |  *Update *Identifier *Set *assignment_list
+                                               |  *Update *Identifier *Set *assignment_list *where
+                                               |  *Update
+                                                  *Identifier
+                                                  $'.'
+                                                  *Identifier
+                                                  *Set
+                                                  *assignment_list
+                                                  *Where
+                                                  *Current
+                                                  *Of
+                                                  *Identifier
+                                               |  *Update *Identifier $'.' *Identifier *Set *assignment_list
+                                               |  *Update *Identifier $'.' *Identifier *Set *assignment_list *where
            assignment_list                     =  *assignment | *assignment_list $',' *assignment
            assignment                          =  *Identifier *EQ *expr | *Identifier *EQ Null
            queryexpr                           =  *queryspec | $'(' *queryexpr $')'
            queryspec                           =  *Select *Distinct *selection *tableexpr
+                                               |  *Select *All *selection *tableexpr
+                                               |  *Select *selection *tableexpr
            selection                           =  *expr_list | $'*'
            expr_list                           =  *expr | *expr_list $',' *expr
            tableexpr                           =  *from *where *groupby *having
+                                               |  *from *where *groupby
+                                               |  *from *where *having
+                                               |  *from *where
+                                               |  *from *groupby *having
+                                               |  *from *groupby
+                                               |  *from *having
+                                               |  *from
            from                                =  *From *table_range_list
            table_range_list                    =  *table_range | *table_range_list $',' *table_range
            table_range                         =  *Identifier *Identifier
+                                               |  *Identifier
+                                               |  *Identifier $'.' *Identifier *Identifier
+                                               |  *Identifier $'.' *Identifier
            where                               =  *Where *cond
            groupby                             =  *Group *By *col_list
            col_list                            =  *col | *col_list $',' *col
            having                              =  *Having *cond
            cond                                =  *pred
+                                               |  *Not *cond
+                                               |  *cond *And *cond
+                                               |  *cond *Or *cond
+                                               |  $'(' *cond $')'
            pred                                =  *in | *compare | *between | *like | *null | *allany | *existence
            compare                             =  *expr *EQ *expr
+                                               |  *expr *OJN *EQ *expr
+                                               |  *expr *EQ *expr *OJN
+                                               |  *expr *NE *expr
+                                               |  *expr *LT *expr
+                                               |  *expr *GT *expr
+                                               |  *expr *LE *expr
+                                               |  *expr *GE *expr
+                                               |  *expr *EQ *subq
+                                               |  *expr *NE *subq
+                                               |  *expr *LT *subq
+                                               |  *expr *GT *subq
+                                               |  *expr *LE *subq
+                                               |  *expr *GE *subq
            subq                                =  *subquery_list | *allany *subquery_list
            allany                              =  *All | *Any | *Some
            between                             =  *expr *Not *Between *expr *And *expr
+                                               |  *expr *Between *expr *And *expr
            like                                =  *col *Not *Like *atom
+                                               |  *col *Not *Like *atom *Escape *atom
+                                               |  *col *Like *atom
+                                               |  *col *Like *atom *Escape *atom
            null                                =  *col *Is *Not Null | *col *Is Null
            in                                  =  *expr *In *subquery_list
+                                               |  *expr *In $'(' *subquery_list $')'
+                                               |  *expr *In $'(' *string_list $')'
            string_list                         =  *string | *string_list $',' *string
            string                              =  *Const_String
            existence                           =  *Exists *subquery_list
            subquery_list                       =  *subquery
+                                               |  *subquery_list *Union *subquery
+                                               |  *subquery_list *Union *All *subquery
+                                               |  *subquery_list *Minus *subquery
+                                               |  *subquery_list *Intersect *subquery
            subquery                            =  $'(' *Select *Distinct *selection *tableexpr $')'
+                                               |  $'(' *Select *All *selection *tableexpr $')'
+                                               |  $'(' *Select *selection *tableexpr $')'
            expr                                =  *expr *Add *expr
+                                               |  *expr *Sub *expr
+                                               |  *expr *Mul *expr
+                                               |  *expr *Div *expr
+                                               |  *expr *Concat *expr
+                                               |  *expr *Union *expr
+                                               |  *expr *Union *All *expr
+                                               |  *primexpr
            primexpr                            =  *atom | *funcref | *Sub *primexpr | *Add *primexpr | $'(' *expr $')'
            atom                                =  *col | *constant
            funcref                             =  *single_value_fn
+                                               |  *group_value_fn
+                                               |  *list_fn
+                                               |  *str_fn
+                                               |  *date_fn
+                                               |  *convert_fn
            convert_fn                          =  *To_Char $'(' *expr $')'
+                                               |  *To_Date $'(' *expr $')'
+                                               |  *To_Multi_Byte $'(' *expr $')'
+                                               |  *To_Single_Byte $'(' *expr $')'
+                                               |  *To_Number $'(' *expr $')'
+                                               |  *CharToRowID $'(' *expr $')'
+                                               |  *RowIDToChar $'(' *expr $')'
+                                               |  *RawToHex $'(' *expr $')'
+                                               |  *HexToRaw $'(' *expr $')'
+                                               |  *Translate
+                                                  $'('
+                                                  *Const_String
+                                                  $','
+                                                  *Const_String
+                                                  $','
+                                                  *Const_String
+                                                  $')'
+                                               |  *Decode $'(' *expr_list $')'
            date_fn                             =  *Add_Months $'(' *expr $',' *Const_Integer $')'
+                                               |  *Months_Between $'(' *expr $',' *expr $')'
+                                               |  *New_Time $'(' *expr $',' *Const_String $',' *Const_String $')'
+                                               |  *Next_Day $'(' *expr $',' *Const_String $')'
+                                               |  *Last_Day $'(' *expr $')'
            str_fn                              =  *str_fn_1parm $'(' *expr $')'
+                                               |  *str_fn_3parm $'(' *expr $',' *expr $',' *expr $')'
+                                               |  *substr
+                                               |  *instr
+                                               |  *ltrim
+                                               |  *rtrim
            str_fn_1parm                        =  *Length | *Soundex | *Lower | *Upper | *InitCap
            ltrim                               =  *LTrim $'(' *expr $')' | *LTrim $'(' *expr $',' *expr $')'
            rtrim                               =  *RTrim $'(' *expr $')' | *RTrim $'(' *expr $',' *expr $')'
            str_fn_3parm                        =  *LPad | *RPad
            substr                              =  *SubStr $'(' *expr $',' *Const_Integer $',' *Const_Integer $')'
+                                               |  *SubStr $'(' *expr $',' *Const_Integer $')'
            instr                               =  *INSTR
+                                                  $'('
+                                                  *expr
+                                                  $','
+                                                  *expr
+                                                  $','
+                                                  *Const_Integer
+                                                  $','
+                                                  *Const_Integer
+                                                  $')'
+                                               |  *INSTR $'(' *expr $',' *expr $',' *Const_Integer $')'
+                                               |  *INSTR $'(' *expr $',' *expr $')'
            single_value_fn                     =  *numfn_1parm $'(' *expr $')'
+                                               |  *numfn_2parm $'(' *expr $',' *expr $')'
            group_value_fn                      =  *group_numfn_1parm $'(' *expr $')'
+                                               |  *group_numfn_1parm $'(' *Distinct *expr $')'
+                                               |  *group_numfn_1parm $'(' *All *expr $')'
            list_fn                             =  *numfn_xparm $'(' *Distinct *expr_list $')'
+                                               |  *numfn_xparm $'(' *All *expr_list $')'
+                                               |  *numfn_xparm $'(' *expr_list $')'
            numfn_1parm                         =  *Abs
+                                               |  *Ceil
+                                               |  *Floor
+                                               |  *SQRT
+                                               |  *Exp
+                                               |  *Ln
+                                               |  *Sign
+                                               |  *Sin
+                                               |  *SinH
+                                               |  *Cos
+                                               |  *CosH
+                                               |  *Tan
+                                               |  *TanH
+                                               |  *VSize
            group_numfn_1parm                   =  *Avg | *Max | *Min | *StdDev | *Sum | *Count | *Variance
            numfn_2parm                         =  *Mod | *Power | *Log | *Nvl | *Round | *Trunc
            numfn_xparm                         =  *Greatest | *Least
            identifier_list                     =  *Identifier | *identifier_list $',' *Identifier
            constant                            =  *Const_Integer | *Const_Real | *Const_String
            type                                =  *Integer
+                                               |  *Real
+                                               |  *String
+                                               |  *Char $'(' *Const_Integer $')'
+                                               |  *Decimal $'(' *Const_Integer $')'
            col                                 =  *Identifier
+                                               |  *Identifier $'.' *Identifier
+                                               |  *Identifier $'.' *Identifier $'.' *Identifier
