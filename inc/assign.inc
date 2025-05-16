*---------------------------------------------------------------------------------------------------
* Assignment during pattern matching: The unevaluated expression may fail
* which causes the assignment not to occur, but the pattern that invoked
* the assignment will always continue.
*
* pattern . *assign(name, expression)
*---------------------------------------------------------------------------------------------------
            DEFINE('assign(name,expression)')            :(assign_end)
assign      assign   =     .dummy
            IDENT(DATATYPE(expression), 'EXPRESSION')    :F(assign1)
            $name    =     EVAL(expression)              :(NRETURN)
assign1     $name    =     expression                    :(NRETURN)
assign_end
