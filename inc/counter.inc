*---------------------------------------------------------------------------------------------------
* A stack of counters. To be used with conditional assignment within pattern matching.
* These routines are useful for counting items on the stack at multiple nesting levels which
* are suitable for reduction on the stack.
* Global: $'#N' -- link_counter()
*---------------------------------------------------------------------------------------------------
              DEFINE('InitCounter()')
              DEFINE('PushCounter()')
              DEFINE('IncCounter()')
              DEFINE('DecCounter()')
              DEFINE('TopCounter()')
              DEFINE('PopCounter()')
              DATA('link_counter(next,value)')                                      :(CounterEnd)
InitCounter   $'#N'          =                                                      :(RETURN)
PushCounter   OUTPUT         =    GT(xTrace, 4) 'PushCounter()'
              $'#N'          =    link_counter($'#N', 0)
              PushCounter    =    .dummy                                            :(NRETURN)
IncCounter    value($'#N')   =    value($'#N') + 1
              OUTPUT         =    GT(xTrace, 4) value($'#N') ' = IncCounter()'
              IncCounter     =    .dummy                                            :(NRETURN)
DecCounter    value($'#N')   =    value($'#N') - 1
              OUTPUT         =    GT(xTrace, 4) value($'#N') ' = DecCounter()'
              DecCounter     =    .dummy                                            :(NRETURN)
PopCounter    OUTPUT         =    GT(xTrace, 4) 'PopCounter()'
              $'#N'          =    DIFFER($'#N') next($'#N')                         :F(FRETURN)
              PopCounter     =    .dummy                                            :(NRETURN)
TopCounter    TopCounter     =    DIFFER($'#N') value($'#N')                        :F(FRETURN)
              OUTPUT         =    GT(xTrace, 4) TopCounter ' = TopCounter()'        :(RETURN)
CounterEnd
*---------------------------------------------------------------------------------------------------
* A stack of XML or HTML begin and end tags. To be used with unconditional assignment within
* pattern matching.
* Global: $'@B' -- link_tag()
*         $'@E' -- link_tag()
*---------------------------------------------------------------------------------------------------
            DATA('link_tag(next,value)')
*---------------------------------------------------------------------------------------------------
            DEFINE('InitBegTag()')
            DEFINE('PushBegTag(t)')
            DEFINE('PopBegTag()')
            DEFINE('TopBegTag()')
            DEFINE('DumpBegTag()b,list,v')                                  :(BegTagEnd)
InitBegTag  $'@B'           =                                               :(RETURN)
PushBegTag  OUTPUT          =   GT(xTrace, 4) 'PushBegTag(' upr(t) ')'
            $'@B'           =   link_tag($'@B', upr(t))
            PushBegTag      =   IDENT(t)  .value($'@B')                     :S(NRETURN)
            PushBegTag      =   DIFFER(t) .dummy                            :(NRETURN)
PopBegTag   OUTPUT          =   GT(xTrace, 4) (DIFFER($'@B') value($'@B'), 'FAIL') ' = PopBegTag()'
            $'@B'           =   DIFFER($'@B') next($'@B')                   :F(FRETURN)
            PopBegTag       =   .dummy                                      :(NRETURN)
TopBegTag   TopBegTag       =   DIFFER($'@B') value($'@B')                  :F(FRETURN)
            OUTPUT          =   GT(xTrace, 4) TopBegTag ' = TopBegTag()'    :(RETURN)
DumpBegTag  DumpBegTag      =   .dummy
            GT(xTrace, 5)                                                   :F(NRETURN)
            b               =   $'@B'
DumpBegTag3 v               =   DIFFER(b) value(b)                          :F(DumpBegTag9)
            list            =   list (DIFFER(list) ', ', '') v
            b               =   next(b)                                     :(DumpBegTag3)
DumpBegTag9 OUTPUT          =   '@B = (' list ')'                           :(NRETURN)
BegTagEnd
*---------------------------------------------------------------------------------------------------
            DEFINE('InitEndTag()')
            DEFINE('PushEndTag(t)')
            DEFINE('PopEndTag()')
            DEFINE('TopEndTag()')
            DEFINE('DumpEndTag()e,list,v')                                  :(EndTagEnd)
InitEndTag  $'@E'           =                                               :(RETURN)
PushEndTag  OUTPUT          =   GT(xTrace, 4) 'PushEndTag(' upr(t) ')'
            $'@E'           =   link_tag($'@E', upr(t))
            PushEndTag      =   IDENT(t)  .value($'@E')                     :S(NRETURN)
            PushEndTag      =   DIFFER(t) .dummy                            :(NRETURN)
PopEndTag   OUTPUT          =   GT(xTrace, 4) (DIFFER($'@E') value($'@E'), 'FAIL') ' = PopEndTag()'
            $'@E'           =   DIFFER($'@E') next($'@E')                   :F(FRETURN)
            PopEndTag       =   .dummy                                      :(NRETURN)
TopEndTag   TopEndTag       =   DIFFER($'@E') value($'@E')                  :F(FRETURN)
            OUTPUT          =   GT(xTrace, 4) TopEndTag ' = TopEndTag()'    :(RETURN)
DumpEndTag  DumpEndTag      =   .dummy
            GT(xTrace, 5)                                                   :F(NRETURN)
            e               =   $'@E'
DumpEndTag3 v               =   DIFFER(e) value(e)                          :F(DumpEndTag9)
            list            =   list (DIFFER(list) ', ', '') v
            e               =   next(e)                                     :(DumpEndTag3)
DumpEndTag9 OUTPUT          =   '@E = (' list ')'                           :(NRETURN)
EndTagEnd
*---------------------------------------------------------------------------------------------------
