   DEFINE('UserDefs()') :(UserDefsEnd)

UserDefs

   u   = 0
   usr = ARRAY('1:32')
   u = u + 1; usr[u] = token(, *('*ACMSCRC_line_col'),                *ACMSCRC_line_col,                *('ACMSCRC line col'))
   u = u + 1; usr[u] = token(, *('*Build_Log'),                       *Build_Log,                       *('Build Log'))
   u = u + 1; usr[u] = token(, *('*Building_static_library'),         *Building_static_library,         *('Building static library'))
   u = u + 1; usr[u] = token(, *('*Compiling'),                       *Compiling,                       *('Compiling'))
   u = u + 1; usr[u] = token(, *('*Compiling_to'),                    *Compiling_to,                    *('Compiling_to'))
   u = u + 1; usr[u] = token(, *('*Complete'),                        *Complete,                        *('Complete'))
   u = u + 1; usr[u] = token(, *('*Copyright'),                       *Copyright,                       *('Copyright'))
   u = u + 1; usr[u] = token(, *('*Creating_required_directory'),     *Creating_required_directory,     *('Creating required directory'))
   u = u + 1; usr[u] = token(, *('*Installing'),                      *Installing,                      *('Installing'))
   u = u + 1; usr[u] = token(, *('*LD_LIBRARY_PATH'),                 *LD_LIBRARY_PATH,                 *('LD_LIBRARY_PATH'))
   u = u + 1; usr[u] = token(, *('*Linking_dynamic_shared_library'),  *Linking_dynamic_shared_library,  *('Linking dynamic shared library'))
   u = u + 1; usr[u] = token(, *('*Preprocessing'),                   *Preprocessing,                   *('Preprocessing'))
   u = u + 1; usr[u] = token(, *('*Pro_C_C__'),                       *Pro_C_C__,                       *('Pro*C/C++'))
   u = u + 1; usr[u] = token(, *('*Server_subsystem'),                *Server_subsystem,                *('Server subsystem'))
   u = u + 1; usr[u] = token(, *('*System_default_option_values'),    *System_default_option_values,    *('System default option values'))
   u = u + 1; usr[u] = token(, *('*acomp_colon'),                     *acomp_colon,                     *(':'))
   u = u + 1; usr[u] = token(, *('*ar_archive'),                      *ar_archive,                      *('/usr/ccs/bin/ar'))
   u = u + 1; usr[u] = token(, *('*cc_colon'),                        *cc_colon,                        *(':'))
   u = u + 1; usr[u] = token(, *('*cc_compile'),                      *cc_compile,                      *('/opt/SUNWspro/bin/cc'))
   u = u + 1; usr[u] = token(, *('*cp_copy'),                         *cp_copy,                         *('/bin/cp'))
   u = u + 1; usr[u] = token(, *('*g_make'),                          *g_make,                          *('/sww/bin/g_make'))
   u = u + 1; usr[u] = token(, *('*g_make_Entering_directory'),       *g_make_Entering_directory,       *('g_make Entering directory'))
   u = u + 1; usr[u] = token(, *('*g_make_directory'),                *g_make_directory,                *('g_make directory'))
   u = u + 1; usr[u] = token(, *('*ld_link'),                         *ld_link,                         *('/usr/ccs/bin/ld'))
   u = u + 1; usr[u] = token(, *('*ls_l'),                            *ls_l,                            *('ls -l'))
   u = u + 1; usr[u] = token(, *('*warning'),                         *warning,                         *('warning'))

   keyint         =   ('?') . tx
   keyword        =   
+                 (   'ACMSCRC'
+                 |   'Build'
+                 |   'Building'
+                 |   'Compiling'
+                 |   'Complete'
+                 |   'Copyright'
+                 |   'Creating'
+                 |   'Entering'
+                 |   'Error'
+                 |   'Installing'
+                 |   'LD_LIBRARY_PATH'
+                 |   'Linking'
+                 |   'Log'
+                 |   'Oracle'
+                 |   'Preprocessing'
+                 |   'Server'
+                 |   'System'
+                 |   'Warning'
+                 |   'argument'
+                 |   'cc'
+                 |   'cd'
+                 |   'col'
+                 |   'default'
+                 |   'directory'
+                 |   'dynamic'
+                 |   'error'
+                 |   'executable'
+                 |   'for'
+                 |   'g_make'
+                 |   'in'
+                 |   'ld'
+                 |   'library'
+                 |   'line'
+                 |   'option'
+                 |   'pointer'
+                 |   'prototype'
+                 |   'required'
+                 |   'shared'
+                 |   'static'
+                 |   'subsystem'
+                 |   'to'
+                 |   'values'
+                 |   'warning'
+                 ) . tx

   pathid         =   *idx (('-' *intx | epsilon) '.' *intx '.' *intx | epsilon)
   pathdir        =   ('..' | '.' | *pathid)
   pathleaf       =   *pathid ('.' *idx | epsilon)
   pathName       =   *idx '.' *idx
+                 |   *pathdir '/' ARBNO(*pathdir '/') *pathleaf

   extra          =   '...'                     . tx . *assign(.tx, "'" tx "'")
+                 |   *pathName                      . *assign(.tx, "*pathName")
+                 |   ('--' SPAN('-'))          . tx . *assign(.tx, "'" tx "'")
+                 |   '-D' (SPAN(&UCASE '_'))   . tx . *assign(.tx, "'-D' *idx")
+                 |   '-l' (SPAN(&UCASE '_'))   . tx . *assign(.tx, "'-l' *idx")
+                 |   ('/opt/SUNWspro/bin/' ('cc' | 'CC')) . tx . *assign(.tx, "'" tx "'")
+                 |   ('/usr/ccs/bin/' ('ar' | 'ld'))      . tx . *assign(.tx, "'" tx "'")
+                 |   ('/bin/' ('cp'))                     . tx . *assign(.tx, "'" tx "'")
+                 |   ('/sww/bin/' ('g_make'))             . tx . *assign(.tx, "'" tx "'")
+                 |   'Pro*C/C++'                          . tx . *assign(.tx, "'" tx "'")
+                 |   '(c)'                                . tx . *assign(.tx, "'" tx "'")

   ACMSCRC_line_col               =  'ACMSCRC' $':' $' ' 'line' $':' *int $',' $' ' 'col' $':' *int $'-' BREAK(nl)
   Build_Log                      =  'Build' $' ' 'Log' $' ' 'for' *int
   Building_executable            =  '-------------' $' ' 'Building' $' ' 'executable' $' ' *pathName $' ' '...'
   Building_static_library        =  '-------------' $' ' 'Building' $' ' 'static' $' ' 'library' $' ' *pathName $' ' '...'
   Compiling                      =  '-------------' $' ' 'Compiling' $' ' *pathName $' ' '...'
   Compiling_to                   =  'Compiling' *id $'.' *id $' ' 'to' $' ' *pathName $' ' '...'
   Complete                       =  'Complete'
   Copyright                      =  '(c)' $' ' 'Copyright' BREAK(nl)
   Creating_required_directory    =  '-------------' $' ' 'Creating' $' ' 'required' $' ' 'directory' $' ' $' ' *pathName $' ' '...'
   Installing                     =  '-------------' $' ' 'Installing' $' ' (*pathName | *id) $' ' 'in' $' ' *pathName $' ' '...'
   LD_LIBRARY_PATH                =  'LD_LIBRARY_PATH' $'=' BREAK(nl)
   Linking_dynamic_shared_library =  '-------------' $' ' 'Linking' $' ' 'dynamic' $' ' 'shared' $' ' 'library' $' ' *pathName $' ' '...'
   Preprocessing                  =  '-------------' $' ' 'Preprocessing' $' ' *pathName $' ' '...'
   Pro_C_C__                      =  'Pro*C/C++' $':' BREAK(nl)
   Server_subsystem               =  '--------------' $' ' 'Server' $' ' 'subsystem' $' ' (*pathName | *id) $'-' $'(' BAL $')'
   System_default_option_values   =  'System' $' ' 'default' $' ' 'option' $' ' 'values' *id *id $':' $'/' *id $'/' *id $'/' *real $'.' *int $'/' *id $'/' *id $'.' *id
   acomp_colon                    =  'acomp' $':' ' ' BREAK(nl)
   ar_archive                     =  '/usr/ccs/bin/ar ' BREAK(nl)
   cc_colon                       =  'cc' $':' ' ' BREAK(nl)
   cc_compile                     =  '/opt/SUNWspro/bin/' ('CC' | 'cc') ' ' BREAK(nl)
   cp_copy                        =  '/bin/cp ' BREAK(nl)
   g_make                         =  '/sww/bin/g_make' BREAK(nl)
   g_make_Entering_directory      =  'g_make' $'[' *int $']' $':' $' ' 'Entering' $' ' 'directory' *tq
   g_make_directory               =  'g_make' $'[' *int $']' $':' *id $' ' 'directory' *tq
   ld_link                        =  '/usr/ccs/bin/ld ' BREAK(nl)
   ls_l                           =  '-' LEN(9) $' ' *int *id *id *int *id *int *int $':' *int $'  ' *pathName
   warning                        =  *dqsqlx $',' $' ' 'line' *int $':' $' ' 'warning' $':' BREAK(nl)
+                                    (  nl
+                                       $' ' 'prototype' $':' BREAK(':') ':' *dqsql $',' $' ' 'line' *int $'  ' nl
+                                       $' ' 'argument'  $':' BREAK(nl)
+                                    |  nl
+                                       $' ' 'pointer' $' ' 'to' BREAK(nl)
+                                    |  epsilon
+                                    )

  :(RETURN)

UserDefsEnd
