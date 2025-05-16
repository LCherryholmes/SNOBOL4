*---------------------------------------------------------------------------------------------------
* A general purpose stack. To be used directly or with conditional assignment within pattern
* matching. This stack holds the values from the pattern match which were produced as a
* result of either a Shift() or a Reduce() operation.
* Global: $'@S' -- link()
*---------------------------------------------------------------------------------------------------
               DEFINE('InitStack()')
               DEFINE('Push(x)')
               DEFINE('Pop(var)')
               DEFINE('Top()')
               DATA('link(next,value)')                                             :(StackEnd)
InitStack      $'@S'          =                                                     :(RETURN)
Push           OUTPUT         =    GT(xTrace, 4) 'Push(' t(x) ')'
               $'@S'          =    link($'@S', x)
               Push           =    IDENT(x)  .value($'@S')                          :S(NRETURN)
               Push           =    DIFFER(x) .dummy                                 :(NRETURN)
Pop            DIFFER($'@S')                                                        :F(FRETURN)
               IDENT(var)                                                           :F(Pop1)
               Pop            =    value($'@S')
               OUTPUT         =    GT(xTrace, 4) 'Pop() = ' t(Pop)
               $'@S'          =    next($'@S')                                      :(RETURN)
Pop1           Pop            =    .dummy
               $var           =    value($'@S')
               OUTPUT         =    GT(xTrace, 4) 'Pop() = ' t($var)
               $'@S'          =    next($'@S')                                      :(NRETURN)
Top            DIFFER($'@S')                                                        :F(FRETURN)
               Top            =    .value($'@S')
               OUTPUT         =    GT(xTrace, 4) 'Top() = ' t(Top)                  :(NRETURN)
StackEnd
