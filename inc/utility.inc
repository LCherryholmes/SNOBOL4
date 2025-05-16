*---------------------------------------------------------------------------------------------------------------
* utility.inc
*---------------------------------------------------------------------------------------------------------------
-INCLUDE      'global.inc'
-INCLUDE      'case.inc'
-INCLUDE      'exec.inc'
*---------------------------------------------------------------------------------------------------------------
              DEFINE('Utility()idResult,unameResult')                               :(UtilityEnd)
Utility       env            =   TABLE()
              exe            =   TABLE()
-INCLUDE      'env.inc'
              idResult       =   exec('id')
              idResult       POS(0) 'uid=' SPAN(digits) '(' BREAK(')') . userId ')'
              userId         POS(0) SPAN(&UCASE) bSlash =
              userId         =   upr(userId)
              unameResult    =   exec('uname', '-n')
              unameResult    POS(0) BREAK(nl) . nodeName nl
              nodeName       =   upr(nodeName)
              DIFFER(userId)                                                        :F(FRETURN)
              DIFFER(nodeName)                                                      :S($nodeName)F(FRETURN)
*---------------------------------------------------------------------------------------------------------------
ISRLAPX73     mksnt              =   'C:/mksnt'
              env['MKSNT']       =   mksnt
              env['HOME']        =   'C:/SNOBOL4'
              env['studioDirNm'] =   'C:/PROGRA~1/MIAF9D~1'
              env['VSCommonDir'] =   'C:/PROGRA~1/MIAF9D~1/Common'
              env['MSDevDir']    =   env['VSCommonDir'] '/MSDev98'
              env['MSVCDir']     =   env['studioDirNm'] '/VC98'
              env['VcOsDir']     =   'WINDOWS'
              env['MSSQLDir']    =   'C:/PROGRA~1/MICROS~4/MSSQL$~1/Binn'
              env['MS80Dir']     =   'C:/PROGRA~1/MICROS~4/80/Tools/Binn'
              env['MS90Dir']     =   'C:/PROGRA~1/MICROS~4/90/Tools/Binn'
              env['SLSDir']      =   'C:/LITESP~1/Dev/bin/debug'
              rootDir            =   'C:'
              rootLogDir         =   env['HOME'] '/Logs'
              webLogDir          =   env['HOME'] '/Web/Logs'
              reportDir          =   env['HOME'] '/Web/Rpts'
                                                                                    :(utility1)
*---------------------------------------------------------------------------------------------------------------
utility1      exe['bom']     =   env['HOME']  '/bom'
              exe['cat']     =   env['MKSNT'] '/cat'
              exe['chmod']   =   env['MKSNT'] '/chmod'
              exe['cksum']   =   env['MKSNT'] '/cksum'
              exe['cmp']     =   env['MKSNT'] '/cmp'
              exe['comm']    =   env['MKSNT'] '/comm'
              exe['cp']      =   env['MKSNT'] '/cp'
              exe['dep']     =   env['HOME']  '/dep'
              exe['diff']    =   env['MKSNT'] '/diff'
              exe['expand']  =   env['MKSNT'] '/expand'
              exe['find']    =   env['MKSNT'] '/find'
              exe['id']      =   env['MKSNT'] '/id'
              exe['ls']      =   env['MKSNT'] '/ls'
              exe['ls-l']    =   env['HOME']  '/ls-l'
              exe['mkdir']   =   env['MKSNT'] '/mkdir'
              exe['mv']      =   env['MKSNT'] '/mv'
              exe['nmake']   =   'nmake'
              exe['perl']    =   env['PERL']  '/perl'
              exe['pkzip']   =   env['PKZIP'] '/pkzip'
              exe['rm']      =   env['MKSNT'] '/rm'
              exe['sort']    =   env['MKSNT'] '/sort'
              exe['ssdb']    =   env['HOME']  '/ssdb'
              exe['sshist']  =   env['HOME']  '/sshist'
              exe['ssls']    =   env['HOME']  '/ssls'
              exe['uname']   =   env['MKSNT'] '/uname'
			  exe['wc']		 =   env['MKSNT'] '/wc'
              exe['blat']    =   env['blatDir'] '/blat'
              exe['textcopy'] =  env['MSSQLDir'] '/textcopy'
              exe['SQLLiteSpeed'] =  env['SLSDir'] '/SQLLiteSpeed'
              exe['OR']      =   env['SLSDir'] '/OR'
              exe['bcp']     =   env['MS80Dir'] '/bcp'
*             exe['bcp']     =   env['MS90Dir'] '/bcp'
              exe['isql']    =   env['MS80Dir'] '/isql'
              exe['osql']    =   env['MS80Dir'] '/osql'
*             exe['osql']    =   env['MS90Dir'] '/osql'
                                                                                    :(RETURN)
*---------------------------------------------------------------------------------------------------------------
UtilityEnd
