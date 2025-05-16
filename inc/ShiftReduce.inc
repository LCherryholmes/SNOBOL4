*---------------------------------------------------------------------------------------------------
* Shift(t,v) -- push a tree of type t with value v onto the stack
*
* Reduce(t, n) -- pop n trees from the stack and push a tree of type t that contains these
* n trees as children in the order they were stacked. If either the t or n parameters are
* unevaluated expressions they will be evaluated on-the-fly here within this routine. If the
* evaluation of an unevaluated expression fails then there is no reduction of the stack.
*---------------------------------------------------------------------------------------------------
               DEFINE('Shift(t,v)s')                                                :(ShiftEnd)
Shift          v              POS(0) whitespace =
               s              =    tree(t, v)
               Push(s)
               OUTPUT         =    GT(xTrace, 3) 'Shift(' t ', ' v ')'
*              OUTPUT         =    GT(xTrace, 4) ' = ' TLump(s, 1024)
               Shift          =    IDENT(v) .v(s)                                   :S(NRETURN)
               Shift          =    DIFFER(v) .dummy                                 :(NRETURN)
ShiftEnd
*---------------------------------------------------------------------------------------------------
               DEFINE('Reduce(t,n)c,i,r')                                           :(ReduceEnd)
Reduce         Reduce         =    .dummy
               IDENT(DATATYPE(t), 'EXPRESSION')                                     :F(Reduce0)
               t              =    EVAL(t)                                          :F(NRETURN)
Reduce0        IDENT(DATATYPE(n), 'EXPRESSION')                                     :F(Reduce1)
               n              =    EVAL(n)                                          :F(NRETURN)
Reduce1        OUTPUT         =    GT(xTrace, 3) 'Reduce(' t ', ' n ')'
               c              =    GE(n, 1) ARRAY('1:' n)
               i              =    n + 1
Reduce2        i              =    GT(i, 1) i - 1                                   :F(Reduce3)
               c[i]           =    Pop()                                            :(Reduce2)
Reduce3        r              =    tree(t,, n, c)
*--            (GT(xTrace, 4) TDump(r))
               Push(r)                                                              :(NRETURN)
ReduceEnd
