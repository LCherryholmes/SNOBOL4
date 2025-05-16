              DEFINE('exec(verb,args)cmd,sysout')                                   :(exec_end)
exec          cmd            =   DIFFER(exe) exe[verb]
              cmd            =   IDENT(cmd) verb
              INPUT(.sysout, 9, '!!' cmd ' ' args)                                  :F(FRETURN)
exec1         exec           =   exec sysout nl                                     :S(exec1)
              ENDFILE(9)                                                            :(RETURN)
exec_end
