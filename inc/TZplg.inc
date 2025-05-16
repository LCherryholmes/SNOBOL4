   DEFINE('UserDefs()') :(UserDefsEnd)

UserDefs

   u   = 0
   usr = ARRAY('1:32')

   keyint         =   ('?') . tx
   keyword        =   
+                 (   'ANSI'
+                 |   'Active'
+                 |   'All'
+                 |   'Begining'
+                 |   'Build'
+                 |   'Building'
+                 |   'Calling'
+                 |   'Cannot'
+                 |   'Cleaning'
+                 |   'Code'
+                 |   'Command'
+                 |   'Compiling'
+                 |   'Configuration'
+                 |   'Contact'
+                 |   'Controller'
+                 |   'Copyright'
+                 |   'Corp'
+                 |   'Creating'
+                 |   'Creation'
+                 |   'Debug'
+                 |   'Dynamic'
+                 |   'Error'
+                 |   'File'
+                 |   'Fix'
+                 |   'For'
+                 |   'Generating'
+                 |   'Grid'
+                 |   'Inc'
+                 |   'Installed'
+                 |   'Library'
+                 |   'Lines'
+                 |   'Link'
+                 |   'Linking'
+                 |   'Log'
+                 |   'Maintenance'
+                 |   'Microsoft'
+                 |   'Model'
+                 |   'No'
+                 |   'Objective'
+                 |   'Output'
+                 |   'Pack'
+                 |   'Program'
+                 |   'Release'
+                 |   'Results'
+                 |   'See'
+                 |   'Software'
+                 |   'Stingray'
+                 |   'Studio'
+                 |   'This'
+                 |   'To'
+                 |   'Toolkit'
+                 |   'Type'
+                 |   'Using'
+                 |   'Utility'
+                 |   'Version'
+                 |   'View'
+                 |   'Warning'
+                 |   'When'
+                 |   'Win32'
+                 |   'Window'
+                 |   'Windows'
+                 |   'a'
+                 |   'actual'
+                 |   'all'
+                 |   'an'
+                 |   'and'
+                 |   'are'
+                 |   'argument'
+                 |   'as'
+                 |   'assignment'
+                 |   'at'
+                 |   'autolink'
+                 |   'automatically'
+                 |   'available'
+                 |   'based'
+                 |   'be'
+                 |   'been'
+                 |   'before'
+                 |   'being'
+                 |   'body'
+                 |   'browse'
+                 |   'browser'
+                 |   'build'
+                 |   'but'
+                 |   'by'
+                 |   'can'
+                 |   'cannot'
+                 |   'case'
+                 |   'characters'
+                 |   'class'
+                 |   'command'
+                 |   'comments'
+                 |   'compiled'
+                 |   'compiling'
+                 |   'conditional'
+                 |   'configuration'
+                 |   'constant'
+                 |   'contents'
+                 |   'control'
+                 |   'controlled'
+                 |   'conversion'
+                 |   'current'
+                 |   'data'
+                 |   'debug'
+                 |   'defined'
+                 |   'definition'
+                 |   'dialog'
+                 |   'did'
+                 |   'different'
+                 |   'differs'
+                 |   'directory'
+                 |   'due'
+                 |   'duplicate'
+                 |   'effect'
+                 |   'empty'
+                 |   'enables'
+                 |   'error'
+                 |   'exceeds'
+                 |   'executing'
+                 |   'expected'
+                 |   'expression'
+                 |   'failed'
+                 |   'fatal'
+                 |   'features'
+                 |   'file'
+                 |   'for'
+                 |   'formal'
+                 |   'found'
+                 |   'from'
+                 |   'function'
+                 |   'greater'
+                 |   'h1'
+                 |   'h2'
+                 |   'h3'
+                 |   'handle'
+                 |   'has'
+                 |   'having'
+                 |   'headers'
+                 |   'how'
+                 |   'html'
+                 |   'identifier'
+                 |   'if'
+                 |   'ignoring'
+                 |   'image'
+                 |   'in'
+                 |   'include'
+                 |   'indirection'
+                 |   'info'
+                 |   'information'
+                 |   'initialized'
+                 |   'instantiation'
+                 |   'integral'
+                 |   'intend'
+                 |   'intent'
+                 |   'is'
+                 |   'know'
+                 |   'levels'
+                 |   'library'
+                 |   'line'
+                 |   'lines'
+                 |   'link'
+                 |   'lists'
+                 |   'local'
+                 |   'loss'
+                 |   'macro'
+                 |   'map'
+                 |   'maximum'
+                 |   'may'
+                 |   'member'
+                 |   'mismatch'
+                 |   'missing'
+                 |   'more'
+                 |   'new'
+                 |   'newer'
+                 |   'nologo'
+                 |   'not'
+                 |   'notes'
+                 |   'object'
+                 |   'obtain'
+                 |   'of'
+                 |   'on'
+                 |   'only'
+                 |   'open'
+                 |   'operator'
+                 |   'or'
+                 |   'parameter'
+                 |   'paths'
+                 |   'possible'
+                 |   'previous'
+                 |   'project'
+                 |   'qualifiers'
+                 |   'redefinition'
+                 |   'reference'
+                 |   'referenced'
+                 |   'release'
+                 |   'released'
+                 |   'reserved'
+                 |   'resources'
+                 |   'retail'
+                 |   'return'
+                 |   'rights'
+                 |   'root'
+                 |   'see'
+                 |   'sensitive'
+                 |   'set'
+                 |   'should'
+                 |   'side'
+                 |   'size'
+                 |   'source'
+                 |   'specification'
+                 |   'specified'
+                 |   'statement'
+                 |   'such'
+                 |   'supplied'
+                 |   'supported'
+                 |   'syntax'
+                 |   'target'
+                 |   'template'
+                 |   'temporary'
+                 |   'text'
+                 |   'than'
+                 |   'the'
+                 |   'these'
+                 |   'to'
+                 |   'truncated'
+                 |   'truncation'
+                 |   'type'
+                 |   'types'
+                 |   'unknown'
+                 |   'unreferenced'
+                 |   'update'
+                 |   'used'
+                 |   'value'
+                 |   'variable'
+                 |   'version'
+                 |   'versions'
+                 |   'visit'
+                 |   'warning'
+                 |   'was'
+                 |   'were'
+                 |   'when'
+                 |   'which'
+                 |   'while'
+                 |   'will'
+                 |   'with'
+                 |   'within'
+                 |   'without'
+                 |   'you'
+                 ) . tx

   bs             =   '\'
   slash          =   '/' | bs

   pathext        =   (  'CPP' | 'C'   | 'cpp' | 'c'
+                     |  'bsc'
+                     |  'DEF' | 'def' | 'dll'
+                     |  'exe' | 'exp'
+                     |  'h'
+                     |  'idl' | 'ilk' | 'inl'
+                     |  'lib'
+                     |  'map'
+                     |  'obj' | 'ocx' | 'odl'
+                     |  'pch' | 'pdb' | 'plg'
+                     |  'rc'  | 'res' | 'rll'
+                     |  'tlb' | 'tmp' | 'txt'
+                     )
   pathid         =   *idx ('.' 'iso88591' | '~' *intx | epsilon)
   pathleaf       =   *idx ('.' *pathext | epsilon)
   pathdrive      =   (ANY(&UCASE &LCASE) ':' slash | slash | epsilon)
   pathdir        =   ('..' | '.' | *pathid) (slash *pathdir | epsilon)
   pathName       =   *pathdrive *pathdir slash *pathleaf
+                 |   *pathdrive *pathdir slash
+                 |   *idx '.' *pathext

   args           =   (*switch | *pathName | '"' *pathName '"') ($'  ' *args | epsilon)
   pathNames0     =   *pathName ($'  ' *pathNames0 | epsilon)
   pathNames      =   *pathName $'  ' *pathName ($'  ' *pathNames0 | epsilon)
   switches       =   *switch (' ' *switches | epsilon)
   switch         =
+                 (   '/' ('D' | 'd') ' ' '"' *idx '"'
+                 |   '/' 'D' *idx '=' *idx
+                 |   '/' 'F' ('As' | 'D')
+                 |   '/' 'F' ('R' | 'a' | 'd' | 'o' | 'p' | 'r') '"' *pathName '"'
+                 |   '/' 'G' ('R' | 'X' | 'i' | 'm' | 'z')
+                 |   '/' 'I ' '"' *pathName '"'
+                 |   '/' 'MDd'
+                 |   '/' 'NOENTRY'
+                 |   '/' 'Od'
+                 |   '/' 'W' ('2' | '3' | '4')
+                 |   '/' 'YX'
+                 |   '/' 'Yc' ('"' *idx '.h' '"' | epsilon)
+                 |   '/' 'Yu' '"' *pathName '"'
+                 |   '/' 'Z' ('I' | 'i')
+                 |   '/' 'base:' '"' '@' *pathName ',' *idx '"'
+                 |   '/' 'c'
+                 |   '/' 'debug'
+                 |   '/' 'def:' '"' *pathName '"'
+                 |   '/' 'dll'
+                 |   '/' 'entry:' '"' *idx '@' *intx '"'
+                 |   '/' 'export:' *idx
+                 |   '/' 'fo' '"' *pathName '"'
+                 |   '/' 'i ' '"' *pathName '"'
+                 |   '/' 'implib:' '"' *pathName '"'
+                 |   '/' 'incremental:' ('no' | 'yes')
+                 |   '/' 'l ' *hex
+                 |   '/' 'libpath:' '"' *pathName '"'
+                 |   '/' 'machine:' 'I386'
+                 |   '/' 'map:' '"' *pathName '"'
+                 |   '/' 'mktyplib203'
+                 |   '/' 'nodefaultlib'
+                 |   '/' 'nologo'
+                 |   '/' 'o ' '"' *pathName '"'
+                 |   '/' 'out:' '"' *pathName '"'
+                 |   '/' 'pdb:' ('"' *pathName '"' | 'none')
+                 |   '/' 'pdbtype:' 'sept'
+                 |   '/' 'subsystem:' ('console' | 'windows')
+                 |   '/' 'tlb ' '"' *pathName '"'
+                 |   '/' 'win32'
+                 )


   extra          =   
+                 (   '...'                             . tx . *assign(.tx, "'" tx "'")
+                 |   '--------------------'            . tx . *assign(.tx, "'" tx "'")
+                 |   ('C' *intx)                       . tx . *assign(.tx, "'" tx "'")
+                 |   ('LNK' *intx)                     . tx . *assign(.tx, "'" tx "'")
+                 |   ('Project' "'" 's')               . tx . *assign(.tx, '"' tx '"')
+                 |   ('don' "'" 't')                   . tx . *assign(.tx, '"' tx '"')
+                 |   'error(s)'                        . tx . *assign(.tx, "'" tx "'")
+                 |   'warning(s)'                      . tx . *assign(.tx, "'" tx "'")
+                 |   *switches                              . *assign(.tx, "*switches")
+                 |   *pathNames                             . *assign(.tx, "*pathNames")
+                 |   *pathName                              . *assign(.tx, "*pathName")
+                 |   '"bscmake.exe @' *pathName . tx '"'    . *assign(.tx, "'" '"bscmake.exe @' "' *pathName '" '"'  "'")
+                 |   '"cl.exe @'   *pathName . tx '"'       . *assign(.tx, "'" '"cl.exe @'      "' *pathName '" '"'  "'")
+                 |   '"link.exe @' *pathName . tx '"'       . *assign(.tx, "'" '"link.exe @'    "' *pathName '" '"'  "'")
+                 |   '"link.exe '  *args . tx ' "'          . *assign(.tx, "'" '"link.exe ' "' *args '" ' "' "'")
+                 |   '"midl.exe '  *args . tx ' "'          . *assign(.tx, "'" '"midl.exe ' "' *args '" ' "' "'")
+                 |   '"rc.exe '    *args . tx ' "'          . *assign(.tx, "'" '"rc.exe '   "' *args '" ' "' "'")
+                 |   ('/' *idx . tx ': "' *pathName '"')    . *assign(.tx, "'/" tx ": '" "'" '"' "'" " *pathName " "'" '"' "'")
+                 |   ('/' *idx . tx ':"' *pathName '"')     . *assign(.tx, "'/" tx ":'" "'" '"' "'" " *pathName " "'" '"' "'")
+                 |   ('/' *idx ':' *idx)               . tx . *assign(.tx, "'" tx "'")
+                 |   ('/' *idx)                        . tx . *assign(.tx, "'" tx "'")
+                 |   '/'                               . tx . *assign(.tx, "'/'")
+                 |   bs                                . tx . *assign(.tx, "bs")
+                 |   (  '<' ('/' | epsilon)
+                        (  'html'
+                        |  'body'
+                        |  'pre'
+                        |  'h1'
+                        |  'h3'
+                        )
+                        '>'
+                     )                                 . tx . *assign(.tx, "'" tx "'")
+                 |   '"' *pathName '"'                      . *assign(.tx, "'" '"' "'" " *pathName " "'" '"' "'")
+                 )

  :(RETURN)

UserDefsEnd
