*-------------------------------------------------------------------------------------------------------------------------
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('Optional(pattern)')
            OPSYN('!', 'Optional', 1)                                                        :S(OptionalEnd)F(error)
Optional    Optional          =     pattern | epsilon                                        :(RETURN)
*           Optional          =     pattern | epsilon ~ ''                                   :(RETURN)
OptionalEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('OneOrMore(pattern)name')
            OPSYN('#', 'OneOrMore', 1)                                                       :S(OneOrMoreEnd)F(error)
OneOrMore   $'#OneOrMore'     =     $'#OneOrMore' + 1
            name              =     '@OneOrMore' $'#OneOrMore'
*           $name             =     EVAL("pattern FENCE(*$'" name "' | epsilon)")
            $name             =     EVAL("pattern (*$'" name "' | epsilon)")
*           $name             =     pattern ARBNO(pattern)
*           $name             =     TZ(1, name, $name)
            OneOrMore         =     EVAL("*$'" name "'")                                     :(RETURN)
OneOrMoreEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('ZeroOrMore(pattern)name')
            OPSYN('%', 'ZeroOrMore', 1)                                                      :S(ZeroOrMoreEnd)F(error)
ZeroOrMore  $'#ZeroOrMore'    =     $'#ZeroOrMore' + 1
            name              =     '@ZeroOrMore' $'#ZeroOrMore'
*           $name             =     EVAL("(pattern FENCE(*$'" name "' | epsilon) | epsilon)")
            $name             =     #pattern | epsilon
*           $name             =     ARBNO(pattern)
*           $name             =     TZ(1, name, $name)
            ZeroOrMore        =     EVAL("*$'" name "'")                                     :(RETURN)
ZeroOrMoreEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('List(pattern,delimiter)name')
            OPSYN('%', 'List', 2)                                                            :S(ListEnd)F(error)
List        $'#List'          =     $'#List' + 1
            name              =     '@List' $'#List'
*           $name             =     EVAL("pattern FENCE(delimiter *$'" name "' | epsilon)")
            $name             =     EQ(doParseTree, TRUE)  EVAL("pattern (delimiter nInc() *$'" name "' | epsilon)")
            $name             =     EQ(doParseTree, FALSE) EVAL("pattern (delimiter *$'" name "' | epsilon)")
            $name             =     TZ(1, name, $name)
            List              =     EVAL("*$'" name "'")                                     :(RETURN)
ListEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
