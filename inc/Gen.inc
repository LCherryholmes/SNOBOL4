*---------------------------------------------------------------------------------------------------
* Routines to manage generated output. Since SNOBOL4 naturally writes one line at a time,
* a way is needed to buffer up the output until a newline character is reached, and a way
* to automatically handle the indention of each line.
*
* IncLevel(delta) -- Increment indention level by delta
* DecLevel(delta) -- Decrement indention level by delta
* SetLevel(level) -- Set indention level
* GetLevel()      -- Get current indention level
*
* Gen(string) -- Generate string
* GenTab(integer) -- Generate tab (spaces) to specified or current margin level
* GenSetCont(character) -- Set continue character and begin with 1st line.
*
* Globals:
*    $'$B' -- buffer
*    $'$C' -- continuation character
*    $'$X' -- marks the spot for $'$C'
*    $'#L' -- indention level
*---------------------------------------------------------------------------------------------------
               DEFINE('IncLevel(delta)')
               DEFINE('DecLevel(delta)')
               DEFINE('SetLevel(level)')
               DEFINE('GetLevel()')                                                 :(LevelEnd)
IncLevel       IncLevel       =  .dummy
               delta          =  IDENT(delta) 2
               $'#L'          =  $'#L' + delta                                      :(NRETURN)
DecLevel       DecLevel       =  .dummy
               delta          =  IDENT(delta) 2
               $'#L'          =  $'#L' - delta                                      :(NRETURN)
SetLevel       SetLevel       =  .dummy
               $'#L'          =  level                                              :(NRETURN)
GetLevel       GetLevel       =  $'#L'                                              :(RETURN)
LevelEnd
*---------------------------------------------------------------------------------------------------
               DEFINE('Gen(str,outNm)ind,outline')
               DEFINE('GenTab(pos)')
               DEFINE('GenSetCont(cont)')
               indent         =  DUPL(' ', 120)                                     :(GenEnd)
Gen            Gen            =  .dummy
               outNm          =  IDENT(outNm) .OUTPUT
               indent         GT($'#L', 0) LEN($'#L' - SIZE($'$X')) . ind
               $'$B'          =  DIFFER($'$B') $'$B' str
               $'$B'          =  IDENT($'$B') $'$X' ind str
               $'$B'          BREAK(nl) . outline nl REM . $'$B'                    :F(NRETURN)
               $'$X'          =  $'$C'
               $outNm         =  outline
Gen10          $'$B'          BREAK(nl) . outline nl REM . $'$B'                    :F(NRETURN)
               $outNm         =  $'$C' ind outline                                  :(Gen10)
GenTab         GenTab         =  .dummy
               pos            =  IDENT(pos) $'#L'
               $'$B'          =  $'$B' ' ' DUPL(' ', pos - SIZE($'$B') - 1)         :S(NRETURN)
               $'$B'          =  $'$B' ' '                                          :(NRETURN)
GenSetCont     GenSetCont     =  .dummy
               $'$X'          =
               $'$C'          =  cont                                               :(NRETURN)
GenEnd
