*---------------------------------------------------------------------------------------
*   build.inc %version: 11 %	%date_modified: Fri Jun 08 14:45:09 2001 %
*---------------------------------------------------------------------------------------
*   BEGIN('html/docs/build-inc-bld.txt')
*   bld_ss_db:                   Source Safe database name (see "ss.inc" for available values).
*   bld_ss_root_proj:            Top-level Source Safe project name. Root project of a branch.
*   bld_ss_build_proj:           Source Safe project name where DSW files can be found.
*   bld_ss_xtra_var:             Name of variable that contains source safe extraction rules in the form of
*                                a table of tables. The 1st key is the category. The 2nd key is
*                                the source safe project pattern. The value is the string of options and
*                                specifications. The 'r' option specifies a recursive get operation. 'P'
*                                denotes a project. 'F' denotes a file.
*   bld_id:                      A single character identifier for the river. Used in criteria fields for
*                                extraction rules and copy rules.
*   bld_log_dir_var:             Name of variable that contains the path to the Log folder on the local build
*                                machine.
*   bld_web_log_dir_var:         Name of variable that contains the path to the Web Log folder on ausbuild.
*   bld_rpt_dir_var:             Name of variable that contains the path to the reports folder on ausbuild.
*                                This folder is used by the Web pages. It contains the build reports.
*   bld_wrk_dir_var:             Name of variable that contains the path name of the working directory.
*   bld_stg_mach_var:            Name of variable that contains the name of the machine used for the
*                                staging area.
*   bld_img_dir_var:             Name of variable that contains the path name of the directory where the
*                                compressed install shield images are placed.
*   bld_inc_paths_var:           Name of variable that contains an array of expressions that are
*                                evaluated to build a custom INCLUDE environment variable for each project.
*   bld_lib_paths_var:           Name of variable that contains an array of expressions that are
*                                evaluated to build a custom LIB environment variable for each project.
*   bld_stg_client_dirs_var:     Name of variable that contains the heirarchical directory structure of the
*                                windows client. It is in the form of a list delimited by newline
*                                characters.
*   bld_stg_ntsrv_dirs_var:      Name of variable that contains the heirarchical directory structure of the
*                                windows server. It is in the form of a list delimited by newline
*                                characters.
*   bld_copy_macros_var:         Name of variable that contains copy macros for use by the copy rules. It
*                                is in the form of a table. The key to the table is the name of the
*                                variable to be set. The value of the table is an expression. These
*                                variables are set in the order that they are specified before the
*                                execution of the copy rules. This mechanism is mainly for convenience and
*                                and for the brevity of the copy rules.
*   bld_copy_rules_var:          Name of variable that contains copy rules which are used to copy from the
*                                build area to the staging area. It is in the form of a table of tables.
*                                The first key is the category. The second key is an integer sequence number.
*                                The values are of the 'cpr' datatype.
*   bld_stg_mnt_expr:            An expression in terms of the host and mode which evaluates to the mount
*                                point of the staging area (ie: the name of the shared directory).
*   bld_stg_drp_expr:            An expression in terms of the host and mode which evaluates to the drop
*                                directory within the staging area.
*   bld_stg_img_expr:            An expression in terms of the host and mode which evaluates to the image
*                                subdirectory within the drop directory.
*   bld_img_dir_expr:            An expression in terms of the host and mode which evaluates to the
*                                directory which is the location of the compressed images.
*   bld_pub_dir:                 The name of the subdirectory where the documentation from tech pubs is
*                                located.
*   bld_client_dsw1_list:        A comma delimited list of workspaces with project dependents used for
*                                building the windows client.
*   bld_client_dsw0_list:        A comma delimited list of workspaces without project dependents used for
*                                building the windows client.
*   bld_ntsrv_dsw1_list:         A comma delimited list of workspaces with project dependents used for
*                                building the windows server.
*   bld_ntsrv_dsw0_list:         A comma delimited list of workspaces without project dependents used for
*                                building the windows server.
*   bld_niqi_client_product:     NiQi product name for the windows client, specified by the '-p' switch.
*   bld_niqi_ntsrv_product:      NiQi product name for the windows server, specified by the '-p' switch.
*   bld_niqi_name_expr:          An expression that evaluates to the argument for the '-u' switch.
*   bld_niqi_userids_var:        The name of a variable that contains a semicolon delimited list of email
*                                addresses for notification purposes.
*   bld_ss_msl_projs:            A newline delimited list of source safe projects that contain MSL files.
*   END()

*----------------------------------------------------------------------------------------------------------
*    Define a build Data type
*----------------------------------------------------------------------------------------------------------
            DATA('bld(' 'bld_ss_db,'
+                       'bld_ss_root_proj,'
+                       'bld_ss_build_proj,'
+                       'bld_ss_xtra_var,'
+                       'bld_id,'
+                       'bld_categories,'
+                       'bld_log_dir_var,'
+                       'bld_web_log_dir_var,'
+                       'bld_rpt_dir_var,'
+                       'bld_wrk_dir_var,'
+                       'bld_stg_mach_var,'
+                       'bld_img_dir_var,'
+                       'bld_inc_paths_var,'
+                       'bld_lib_paths_var,'
+                       'bld_client_dsw1_list,'
+                       'bld_client_dsw0_list,'
+                       'bld_ntsrv_dsw1_list,'
+                       'bld_ntsrv_dsw0_list,'
+                       'bld_stg_client_dirs_var,'
+                       'bld_stg_ntsrv_dirs_var,'
+                       'bld_copy_macros_var,'
+                       'bld_copy_rules_var,'
+                       'bld_stg_mnt_expr,'
+                       'bld_stg_drp_expr,'
+                       'bld_stg_img_expr,'
+                       'bld_img_dir_expr,'
+                       'bld_pub_dir,'
+                       'bld_niqi_client_product,'
+                       'bld_niqi_ntsrv_product,'
+                       'bld_niqi_name_expr,'
+                       'bld_niqi_userids_var,'
+                       'bld_ss_msl_projs'
+                ')'
+               )
*---------------------------------------------------------------------------------------------------------------

            saPfx             = TABLE()
            saPfx['client']   = 'cli_'
            saPfx['ntsrv']    = 'ntsrv_'

            saSfx             = TABLE()
            saSfx['client']   = 'image'
            saSfx['ntsrv']    = 'ntimg'

            build             = TABLE()
            build['bom']      = bld('maxm', '$/bom')

*---------------------------------------------------------------------------------------------------------------
*    River definitions
*---------------------------------------------------------------------------------------------------------------

*---------------------------------------------------------------------------------------------------------------
            build['ganges']   = bld(
+                                  'maxm',
+                                  '$/ganges',
+                                  '$/ganges/common/build',
+                                  .ssCMXtra,
+                                  'G',
+                                  'cmn,ali',
+                                  .rootLogDir,
+                                  .webLogDir,
+                                  .reportDir,
+                                  .gangesBuildDir,
+                                  .gangesStageMach,
+                                  .gangesImageDir,
+                                  .incCMPaths,
+                                  .libCMPaths,
+                                  'ali3-2.dsw,common3-2.dsw',
+                                  'ali03-2.dsw,common03-2.dsw',
+                                  'PDBNtSrv3-2.dsw',
+                                  'PDBNtSrv03-2.dsw',
+                                  .stgClientCMDirs,
+                                  .stgNtsrvCMDirs,
+                                  .cpmCMTbl,
+                                  .cprCMTbl,
+                                  *(saPfx[host] mode),
+                                  *(saPfx[host] mode '/drop.ganges'),
+                                  *(saPfx[host] mode '/drop.ganges/' saSfx[host]),
+                                  *('ganges/dev/' host '/' mode),
+                                  'pdb_3_3_01_(ganges)',
+                                  'PATROL DB-Admin Client 3.3.01 CD2',
+                                  'PATROL DB-Admin Server 3.3.01 CD2',
+                                  *(mode '.ganges'),
+                                  .gangesNiQiUserids,
+                                  (  'ali/scripts'        nl
+                                     'common/cmx/scripts' nl
+                                     'common/jzs/scripts' nl
+                                     'common/sch/scripts' nl
+                                     'common/scripts'     nl
+                                  )
+                               )
*---------------------------------------------------------------------------------------------------------------
            build['sqlx']     = bld(
+                                  'maxm',
+                                  '$/SQLExplorer/5.0/MMC',
+                                  '$/SQLExplorer/5.0/MMC',
+                                  .ssSEXtra,
+                                  'S',
+                                  'sqlx',
+                                  .rootLogDir,
+                                  .webLogDir,
+                                  .reportDir,
+                                  .sqlxBuildDir,
+                                  .sqlxStageMach,
+                                  .sqlxImageDir,
+                                  .incSEPaths,
+                                  .libSEPaths,
+                                  'SQLExplorer.dsw',
+                                  'SQLExplorer.dsw',
+                                  '',
+                                  '',
+                                  .stgClientSEDirs,
+                                  .stgNtsrvSEDirs,
+                                  .cpmSETbl,
+                                  .cprSETbl,
+                                  *('sql_explorer/5.0/' mode),
+                                  *('sql_explorer/5.0/' mode),
+                                  *('sql_explorer/5.0/' mode),
+                                  *('sql_explorer/5.0/' mode 'Installs'),
+                                  'pqo/src_4.0/4.0_stand_alone',
+                                  '',
+                                  '',
+                                  '',
+                                  .sqlxNiQiUserids,
+                                  ''
+                               )
*---------------------------------------------------------------------------------------------------------------
            build['dev']      = bld(
+                                  'maxm',
+                                  '$/dev',
+                                  '$/dev/common/build',
+                                  .ssCMXtra,
+                                  'D',
+                                  'cmn,akm,al2,alo,alm,als',
+                                  .rootLogDir,
+                                  .webLogDir,
+                                  .reportDir,
+                                  .devBuildDir,
+                                  .devStageMach,
+                                  .devImageDir,
+                                  .incCMPaths,
+                                  .libCMPaths,
+                                  'common.dsw,alo.dsw,al2.dsw,alm.dsw,akm.dsw,als.dsw',
+                                  'common0.dsw,alo0.dsw,al20.dsw,alm0.dsw,akm0.dsw,als0.dsw',
+                                  'PDBNtSrv.dsw',
+                                  'PDBNtSrv0.dsw',
+                                  .stgClientCMDirs,
+                                  .stgNtsrvCMDirs,
+                                  .cpmCMTbl,
+                                  .cprCMTbl,
+                                  *(saPfx[host] mode),
+                                  *(saPfx[host] mode '/drop3.5.01'),
+                                  *(saPfx[host] mode '/drop3.5.01/' saSfx[host]),
+                                  *('dev/' host '/' mode),
+                                  'pdb_3_3_01',
+                                  'PATROL DB-Admin Client 3.5.01',
+                                  'PATROL DB-Admin Server 3.5.01',
+                                  *(mode '.1'),
+                                  .devNiQiUserids,
+                                  (  'alo/scripts'        nl
+                                     'al2/scripts'        nl
+                                     'alm/scripts'        nl
+                                     'als/scripts'        nl
+                                     'akm/scripts'        nl
+                                     'common/cmx/scripts' nl
+                                     'common/jzs/scripts' nl
+                                     'common/sch/scripts' nl
+                                     'common/scripts'     nl
+                                  )
+                               )
*---------------------------------------------------------------------------------------------------------------
            build['mvs']      = bld(
+                                  'maxm',
+                                  '$/mvs71',
+                                  '$/mvs71/common/build',
+                                  .ssCMXtra,
+                                  'M',
+                                  'cmn,akm',
+                                  .rootLogDir,
+                                  .webLogDir,
+                                  .reportDir,
+                                  .mvsBuildDir,
+                                  .mvsStageMach,
+                                  .mvsImageDir,
+                                  .incCMPaths,
+                                  .libCMPaths,
+                                  'common.dsw,akm.dsw',
+                                  'common0.dsw,akm0.dsw',
+                                  '',
+                                  '',
+                                  .stgClientCMDirs,
+                                  .stgNtsrvCMDirs,
+                                  .cpmCMTbl,
+                                  .cprCMTbl,
+                                  *(saPfx[host] mode),
+                                  *(saPfx[host] mode '/drop3.2.10m'),
+                                  *(saPfx[host] mode '/drop3.2.10m/' saSfx[host]),
+                                  *('3.2.10m/dev/' host '/' mode),
+                                  'pdb_3_3_01',
+                                  'PATROL DB-Admin Client 3.2.10M',
+                                  '',
+                                  *(mode '.MVS'),
+                                  .devNiQiUserids,
+                                  (  'common/cmx/scripts' nl
+                                     'common/jzs/scripts' nl
+                                     'common/sch/scripts' nl
+                                     'common/scripts'     nl
+                                     'akm/scripts'        nl
+                                  )
+                               )
*---------------------------------------------------------------------------------------------------------------
            build['cm33']     = bld(
+                                  'maxm',
+                                  '$/cm33',
+                                  '$/cm33/common/build',
+                                  .ssCMXtra,
+                                  '3',
+                                  'cmn,al2,alo',
+                                  .rootLogDir,
+                                  .webLogDir,
+                                  .reportDir,
+                                  .cm33BuildDir,
+                                  .cm33StageMach,
+                                  .cm33ImageDir,
+                                  .incCMPaths,
+                                  .libCMPaths,
+                                  'common.dsw,alo.dsw,al2.dsw',
+                                  'common0.dsw,alo0.dsw,al20.dsw',
+                                  'PDBNtSrv.dsw',
+                                  'PDBNtSrv0.dsw',
+                                  .stgClientCMDirs,
+                                  .stgNtsrvCMDirs,
+                                  .cpmCMTbl,
+                                  .cprCMTbl,
+                                  *(saPfx[host] mode),
+                                  *(saPfx[host] mode '/drop3.3.01'),
+                                  *(saPfx[host] mode '/drop3.3.01/' saSfx[host]),
+                                  *('cm33/dev/' host '/' mode),
+                                  'pdb_3_3_01',
+                                  'PATROL DB-Admin Client 3.3.01',
+                                  'PATROL DB-Admin Server 3.3.01',
+                                  *(mode '.1'),
+                                  .devNiQiUserids,
+                                  (  'alo/scripts'        nl
+                                     'al2/scripts'        nl
+                                     'common/cmx/scripts' nl
+                                     'common/jzs/scripts' nl
+                                     'common/sch/scripts' nl
+                                     'common/scripts'     nl
+                                  )
+                               )
*---------------------------------------------------------------------------------------------------------------
            build['cm34']     = bld(
+                                  'maxm',
+                                  '$/cm34',
+                                  '$/cm34/common/build',
+                                  .ssCMXtra,
+                                  '4',
+                                  'cmn,alo',
+                                  .rootLogDir,
+                                  .webLogDir,
+                                  .reportDir,
+                                  .cm34BuildDir,
+                                  .cm34StageMach,
+                                  .cm34ImageDir,
+                                  .incCMPaths,
+                                  .libCMPaths,
+                                  'common.dsw,alo.dsw',
+                                  'common0.dsw,alo0.dsw',
+                                  'PDBNtSrv.dsw',
+                                  'PDBNtSrv0.dsw',
+                                  .stgClientCMDirs,
+                                  .stgNtsrvCMDirs,
+                                  .cpmCMTbl,
+                                  .cprCMTbl,
+                                  *(saPfx[host] mode),
+                                  *(saPfx[host] mode '/drop3.4.01'),
+                                  *(saPfx[host] mode '/drop3.4.01/' saSfx[host]),
+                                  *('cm34/dev/' host '/' mode),
+                                  'pdb_3_4_01',
+                                  'PATROL DB-Admin Client 3.4.01',
+                                  'PATROL DB-Admin Server 3.4.01',
+                                  *(mode '.1'),
+                                  .devNiQiUserids,
+                                  (  'alo/scripts'        nl
+                                     'common/cmx/scripts' nl
+                                     'common/jzs/scripts' nl
+                                     'common/sch/scripts' nl
+                                     'common/scripts'     nl
+                                  )
+                               )
*---------------------------------------------------------------------------------------------------------------
*---------------------------------------------------------------------------------------------------------------
            build['cm35']     = bld(
+                                  'maxm',
+                                  '$/cm35',
+                                  '$/cm35/common/build',
+                                  .ssCMXtra,
+                                  '5',
+                                  'cmn,alm,al2,alo,als',
+                                  .rootLogDir,
+                                  .webLogDir,
+                                  .reportDir,
+                                  .devBuildDir,
+                                  .devStageMach,
+                                  .devImageDir,
+                                  .incCMPaths,
+                                  .libCMPaths,
+                                  'common.dsw,alo.dsw,al2.dsw,alm.dsw,als.dsw',
+                                  'common0.dsw,alo0.dsw,al20.dsw,alm0.dsw,als0.dsw',
+                                  'PDBNtSrv.dsw',
+                                  'PDBNtSrv0.dsw',
+                                  .stgClientCMDirs,
+                                  .stgNtsrvCMDirs,
+                                  .cpmCMTbl,
+                                  .cprCMTbl,
+                                  *(saPfx[host] mode),
+                                  *(saPfx[host] mode '/drop3.5.01'),
+                                  *(saPfx[host] mode '/drop3.5.01/' saSfx[host]),
+                                  *('dev/' host '/' mode),
+                                  'pdb_3_5_01',
+                                  'PATROL DB-Admin Client 3.5.01',
+                                  'PATROL DB-Admin Server 3.5.01',
+                                  *(mode '.1'),
+                                  .devNiQiUserids,
+                                  (  'alo/scripts'        nl
+                                     'al2/scripts'        nl
+                                     'alm/scripts'        nl
+                                     'als/scripts'        nl
+                                     'common/cmx/scripts' nl
+                                     'common/jzs/scripts' nl
+                                     'common/sch/scripts' nl
+                                     'common/scripts'     nl
+                                  )
+                               )
*---------------------------------------------------------------------------------------------------------------
            build['hsdc']     = bld(
+                                  'hsdc',
+                                  '$',
+                                  '$',
+                                  .ssHSDCXtra,
+                                  'H',
+                                  'cmn',
+                                  .rootLogDir,
+                                  .webLogDir,
+                                  .reportDir,
+                                  .hsdcBuildDir,
+                                  .hsdcStageMach,
+                                  .hsdcImageDir,
+                                  .incHSDCPaths,
+                                  .libHSDCPaths,
+                                  'HSDC.dsw',
+                                  'HSDC0.dsw',
+                                  ,
+                                  ,
+                                  .stgClientHSDCDirs,
+                                  .stgServerHSDCDirs,
+                                  .cpmHSDCTbl,
+                                  .cprHSDCTbl,
+                                  *(),
+                                  *(),
+                                  *(),
+                                  *()
+                               )
*---------------------------------------------------------------------------------------------------------------

*---------------------------------------------------------------------------------------------------------------
*
*           patrol-db change manager windows client/ntsrv extraction rules
*
            ssCMXtra        = TABLE()
            ssCMXtra['akm'] = TABLE()
            ssCMXtra['al2'] = TABLE()
            ssCMXtra['ali'] = TABLE()
            ssCMXtra['alm'] = TABLE()
            ssCMXtra['alo'] = TABLE()
            ssCMXtra['als'] = TABLE()
            ssCMXtra['cmn'] = TABLE()

            ssCMXtra['akm']['akm/product']                                   = 'F'
            ssCMXtra['akm']['akm/version']                                   = 'F'
            ssCMXtra['akm']['akm/inifiles/*.ini']                            = 'F'

            ssCMXtra['al2']['al2/product']                                   = 'F'
            ssCMXtra['al2']['al2/version']                                   = 'F'
            ssCMXtra['al2']['al2/mds/*.mds']                                 = 'F'
            ssCMXtra['al2']['al2/inifiles/*.ini']                            = 'F'
            ssCMXtra['al2']['al2/en_US.iso88591/images']                     = 'P'

            ssCMXtra['ali']['ali/product']                                   = 'F'
            ssCMXtra['ali']['ali/version']                                   = 'F'
            ssCMXtra['ali']['ali/inifiles/*.ini']                            = 'F'
            ssCMXtra['ali']['ali/mds/*.mds']                                 = 'F'

            ssCMXtra['alm']['alm/product']                                   = 'F'
            ssCMXtra['alm']['alm/version']                                   = 'F'
            ssCMXtra['alm']['alm/inifiles/*.ini']                            = 'F'
            ssCMXtra['alm']['alm/mds/*.mds']                                 = 'F'

            ssCMXtra['alo']['alo/product']                                   = 'F'
            ssCMXtra['alo']['alo/version']                                   = 'F'
            ssCMXtra['alo']['alo/alold/NT/*.exe']                            = 'F'
            ssCMXtra['alo']['alo/alounl/NT/*.cat']                           = 'F'
            ssCMXtra['alo']['alo/alounl/NT/*.exe']                           = 'F'
            ssCMXtra['alo']['alo/alounl/NT/locale/*.nls']                    = 'F'
            ssCMXtra['alo']['alo/alounl/admin/alo*']                         = 'F'
            ssCMXtra['alo']['alo/inifiles/*.ini']                            = 'F'
            ssCMXtra['alo']['alo/mds/*.mds']                                 = 'F'
            ssCMXtra['alo']['alo/en_US.iso88591/images']                     = 'P'
            ssCMXtra['alo']['common/OEMIntegration']                         = 'Pr'

            ssCMXtra['als']['als/product']                                   = 'F'
            ssCMXtra['als']['als/version']                                   = 'F'
            ssCMXtra['als']['als/mds/*.mds']                                 = 'F'
            ssCMXtra['als']['als/inifiles/*.ini']                            = 'F'

            ssCMXtra['cmn']['common/jzs/jzsbridge/version']                  = 'F'
            ssCMXtra['cmn']['common/build/nt/version']                       = 'F'
            ssCMXtra['cmn']['common/server/acmwinnt/patroldb/patroldb.ini']  = 'F'
            ssCMXtra['cmn']['common/server/acmwinnt/patroldb/shakeout.bat']  = 'F'
            ssCMXtra['cmn']['common/server/jzs/jzsexe/psapi.dll']            = 'F'
            ssCMXtra['cmn']['common/server/jzs/jzsexe/psapi.lib']            = 'F'
            ssCMXtra['cmn']['common/server/unix/scripts/shakeout.msl']       = 'F'
            ssCMXtra['cmn']['common/server/unix/scripts/shakeout_db2.msl']   = 'F'
            ssCMXtra['cmn']['pdbbases.txt']                                  = 'F'
            ssCMXtra['cmn']['ThirdParty']                                    = 'Pr'
            ssCMXtra['cmn']['common/build/client/bin']                       = 'Pr'
            ssCMXtra['cmn']['common/build/client/icons']                     = 'Pr'
            ssCMXtra['cmn']['common/build/client/tag']                       = 'Pr'
            ssCMXtra['cmn']['common/build/client/util']                      = 'Pr'
            ssCMXtra['cmn']['common/build/client/windows/common']            = 'Pr'
            ssCMXtra['cmn']['common/build/client/windows/nt']                = 'Pr'
            ssCMXtra['cmn']['common/build/client/windows/win95']             = 'Pr'
            ssCMXtra['cmn']['common/cgs']                                    = 'Pr'
            ssCMXtra['cmn']['common/cgs/cgshctl/include']                    = 'Pr'
            ssCMXtra['cmn']['common/cmx/cmxmig/mkcdl/dependencies']          = 'Pr'
            ssCMXtra['cmn']['common/cmx/inifiles']                           = 'Pr'
            ssCMXtra['cmn']['common/en_US.iso88591/images']                  = 'P'
            ssCMXtra['cmn']['common/en_US.iso88591/msgfiles/*.msg']          = 'F'
            ssCMXtra['cmn']['common/inifiles']                               = 'Pr'
            ssCMXtra['cmn']['common/lib']                                    = 'Pr'
            ssCMXtra['cmn']['common/patapi/NT']                              = 'Pr'
            ssCMXtra['cmn']['common/pdbkm']                                  = 'Pr'
            ssCMXtra['cmn']['common/resources']                              = 'Pr'
            ssCMXtra['cmn']['include']                                       = 'Pr'
            ssCMXtra['cmn']['common/alx/alxcmdwz/*.tpl']                     = 'F'
*---------------------------------------------------------------------------------------------------------------
*
*           patrol-db change manager windows client/ntsrv include path expressions
*
            incCMPaths        =   ARRAY('0:18')
            incCMPaths[1]     =   *(env['MSVCDir'] '/include')
            incCMPaths[2]     =   *(env['MSVCDir'] '/mfc/include')
            incCMPaths[3]     =   *(env['MSVCDir'] '/atl/include')
            incCMPaths[4]     =   *(workDir '/ThirdParty/ObjChart/include')
            incCMPaths[5]     =   *(workDir '/ThirdParty/ObjStudio/common/common 6.11/include')
            incCMPaths[6]     =   *(workDir '/ThirdParty/ObjStudio/common/MVC 6.11/include')
            incCMPaths[7]     =   *(workDir '/ThirdParty/ObjStudio/OT603/include')
            incCMPaths[8]     =   *(workDir '/ThirdParty/ObjStudio/OG701/include')
            incCMPaths[9]     =   *(workDir '/ThirdParty/XTL/include')
            incCMPaths[10]    =   *(workDir '/common/resources')
            incCMPaths[11]    =   *(workDir '/common/cgs/cgshctl/include')
            incCMPaths[12]    =   *(oraInclDirNm)
            incCMPaths[13]    =   *(mssInclDirNm)
            incCMPaths[14]    =   *(infInclDirNm)
            incCMPaths[15]    =   *(sybInclDirNm)
            incCMPaths[16]    =   *(udbInclDirNm)
            incCMPaths[17]    =   *(workDir '/include')
            incCMPaths[18]    =   *(workDir '/include/EventLog')
*---------------------------------------------------------------------------------------------------------------
*
*           patrol-db change manager windows client/ntsrv lib path expressions
*
            libCMPaths        =   ARRAY('0:11')
            libCMPaths[1]     =   *(env['MSVCDir'] '/lib')
            libCMPaths[2]     =   *(env['MSVCDir'] '/mfc/lib')
            libCMPaths[3]     =   *(workDir '/ThirdParty/' libMode)
            libCMPaths[4]     =   *(workDir '/common/lib')
            libCMPaths[5]     =   *(workDir '/common/patapi/nt')
            libCMPaths[6]     =   *(oraLibDirNm)
            libCMPaths[7]     =   *(mssLibDirNm)
            libCMPaths[8]     =   *(infLibDirNm)
            libCMPaths[9]     =   *(sybLibDirNm)
            libCMPaths[10]    =   *(udbLibDirNm)
            libCMPaths[11]    =   *(workDir '/' libMode)
*----------------------------------------------------------------------------------------------------------
*
*           patrol-db change manager windows client staging area directory structure
*
            stgClientCMDirs   =    'image' nl
+                                  'image/common' nl
+                                  'image/common/tag' nl
+                                  'image/common/bin' nl
+                                  'image/common/bin/charmaps' nl
+                                  'image/common/bin/en_US.iso88591' nl
+                                  'image/common/bin/en_US.iso88591/common' nl
+                                  'image/common/bin/en_US.iso88591/common/help' nl
+                                  'image/common/bin/en_US.iso88591/common/images' nl
+                                  'image/common/bin/en_US.iso88591/db2' nl
+                                  'image/common/bin/en_US.iso88591/db2/help' nl
+                                  'image/common/bin/en_US.iso88591/db2/help/sqlx' nl
+                                  'image/common/bin/en_US.iso88591/db22' nl
+                                  'image/common/bin/en_US.iso88591/db22/help' nl
+                                  'image/common/bin/en_US.iso88591/db22/images' nl
+                                  'image/common/bin/en_US.iso88591/infmx' nl
+                                  'image/common/bin/en_US.iso88591/infmx/help' nl
+                                  'image/common/bin/en_US.iso88591/ora' nl
+                                  'image/common/bin/en_US.iso88591/ora/help' nl
+                                  'image/common/bin/en_US.iso88591/ora/help/sqlx' nl
+                                  'image/common/bin/en_US.iso88591/ora/images' nl
+                                  'image/common/bin/en_US.iso88591/sqlsrv' nl
+                                  'image/common/bin/en_US.iso88591/sqlsrv/help' nl
+                                  'image/common/bin/en_US.iso88591/syb' nl
+                                  'image/common/bin/en_US.iso88591/syb/help' nl
+                                  'image/common/bin/iconv ' nl
+                                  'image/common/bin/iconv/tables' nl
+                                  'image/common/bin/iconv/tables/ascii' nl
+                                  'image/common/bin/iconv/tables/binary' nl
+                                  'image/common/bin/locale' nl
+                                  'image/common/bin/locale/de_DE.iso88591' nl
+                                  'image/common/bin/locale/de_DE.iso88591/ML_MESSAGES' nl
+                                  'image/common/bin/locale/en_GB.iso88591' nl
+                                  'image/common/bin/locale/en_GB.iso88591/ML_MESSAGES' nl
+                                  'image/common/bin/locale/en_US.iso88591' nl
+                                  'image/common/bin/locale/en_US.iso88591/ML_MESSAGES' nl
+                                  'image/common/bin/locale/fr_FR.iso88591 ' nl
+                                  'image/common/bin/locale/fr_FR.iso88591/ML_MESSAGES' nl
+                                  'image/common/bin/locale/ja_JP.CP932' nl
+                                  'image/common/bin/locale/ja_JP.CP932/ML_MESSAGES' nl
+                                  'image/common/bin/locale/ja_JP.SJIS' nl
+                                  'image/common/bin/locale/ja_JP.SJIS/ML_MESSAGES' nl
+                                  'image/common/bin/locale/ja_JP.eucJP' nl
+                                  'image/common/bin/locale/ja_JP.eucJP/ML_MESSAGES' nl
+                                  'image/common/bin/locale/ko_KR.eucKR' nl
+                                  'image/common/bin/locale/ko_KR.eucKR/ML_MESSAGES' nl
+                                  'image/common/config' nl
+                                  'image/common/config/en_US.iso88591' nl
+                                  'image/common/doc' nl
+                                  'image/common/doc/books' nl
+                                  'image/common/icons' nl
+                                  'image/common/mc' nl
+                                  'image/common/mc/APPS' nl
+                                  'image/common/mc/bin' nl
+                                  'image/common/mc/config' nl
+                                  'image/common/mc/config/en_US.iso88591' nl
+                                  'image/common/sch' nl
+                                  'image/common/util' nl
+                                  'image/common/windows' nl
+                                  'image/common/windows/product' nl
+                                  'image/common/windows/system' nl
+                                  'image/common/windows/system/common' nl
+                                  'image/common/windows/system/nt' nl
+                                  'image/common/windows/system/win95' nl
+                                  'image/db2' nl
+                                  'image/db2/bin' nl
+                                  'image/db2/bin/SQLX' nl
+                                  'image/db2/bin/mc' nl
+                                  'image/db2/bin/md' nl
+                                  'image/db2/bin/mm' nl
+                                  'image/db2/config' nl
+                                  'image/db2/config/SQLX' nl
+                                  'image/db2/config/mc' nl
+                                  'image/db2/config/md' nl
+                                  'image/db2/config/md/en_US.iso88591' nl
+                                  'image/db2/config/mm' nl
+                                  'image/db2/config/mm/en_US.iso88591' nl
+                                  'image/db22' nl
+                                  'image/db22/bin' nl
+                                  'image/db22/bin/mc' nl
+                                  'image/db22/bin/md' nl
+                                  'image/db22/bin/mm' nl
+                                  'image/db22/bin/sqlx' nl
+                                  'image/db22/config' nl
+                                  'image/db22/config/md' nl
+                                  'image/db22/config/md/en_US.iso88591' nl
+                                  'image/db22/config/mm' nl
+                                  'image/infmx' nl
+                                  'image/infmx/bin' nl
+                                  'image/infmx/bin/md' nl
+                                  'image/infmx/bin/mm' nl
+                                  'image/infmx/config' nl
+                                  'image/infmx/config/md' nl
+                                  'image/infmx/config/md/en_US.iso88591' nl
+                                  'image/infmx/config/mm' nl
+                                  'image/ora' nl
+                                  'image/ora/bin' nl
+                                  'image/ora/bin/md' nl
+                                  'image/ora/bin/mm' nl
+                                  'image/ora/bin/sqlx' nl
+                                  'image/ora/config' nl
+                                  'image/ora/config/md' nl
+                                  'image/ora/config/md/en_US.iso88591' nl
+                                  'image/ora/config/mm' nl
+                                  'image/ora/config/sqlx' nl
+                                  'image/ora/oem' nl
+                                  'image/ora/oem/1x' nl
+                                  'image/ora/oem/2x' nl
+                                  'image/ora/pifs' nl
+                                  'image/oss' nl
+                                  'image/oss/ossinteg' nl
+                                  'image/special' nl
+                                  'image/sqlsrv' nl
+                                  'image/sqlsrv/bin' nl
+                                  'image/sqlsrv/bin/md' nl
+                                  'image/sqlsrv/bin/mm' nl
+                                  'image/sqlsrv/config' nl
+                                  'image/sqlsrv/config/md' nl
+                                  'image/sqlsrv/config/md/en_US.iso88591' nl
+                                  'image/sqlsrv/config/mm' nl
+                                  'image/syb' nl
+                                  'image/syb/bin' nl
+                                  'image/syb/bin/md' nl
+                                  'image/syb/bin/mm' nl
+                                  'image/syb/config' nl
+                                  'image/syb/config/md' nl
+                                  'image/syb/config/md/en_US.iso88591' nl
+                                  'image/syb/config/mm' nl
*----------------------------------------------------------------------------------------------------------
*
*           patrol-db change manager windows server staging area directory structure
*
            stgNtsrvCMDirs    =    'bat' nl
+                                  'exe' nl
+                                  'ntimg' nl
+                                  'ntimg/bin' nl
+                                  'ntimg/bin/common' nl
+                                  'ntimg/bin/icons' nl
+                                  'ntimg/bin/ntsrv' nl
+                                  'ntimg/bin/ntsrv/db2' nl
+                                  'ntimg/bin/ntsrv/de_DE.iso88591' nl
+                                  'ntimg/bin/ntsrv/en_GB.iso88591' nl
+                                  'ntimg/bin/ntsrv/en_US.iso88591' nl
+                                  'ntimg/bin/ntsrv/en_US.iso88591/images' nl
+                                  'ntimg/bin/ntsrv/en_US.iso88591/common' nl
+                                  'ntimg/bin/ntsrv/en_US.iso88591/common/images' nl
+                                  'ntimg/bin/ntsrv/en_US.iso88591/ora' nl
+                                  'ntimg/bin/ntsrv/en_US.iso88591/ora/images' nl
+                                  'ntimg/bin/ntsrv/en_US.iso88591/db2' nl
+                                  'ntimg/bin/ntsrv/en_US.iso88591/db2/images' nl
+                                  'ntimg/bin/ntsrv/fr_FR.iso88591' nl
+                                  'ntimg/bin/ntsrv/infmx' nl
+                                  'ntimg/bin/ntsrv/ja_JP.CP932' nl
+                                  'ntimg/bin/ntsrv/ja_JP.SJIS' nl
+                                  'ntimg/bin/ntsrv/ja_JP.eucJP' nl
+                                  'ntimg/bin/ntsrv/ko_KR.eucKR' nl
+                                  'ntimg/bin/ntsrv/locale' nl
+                                  'ntimg/bin/ntsrv/locale/en_US.iso88591' nl
+                                  'ntimg/bin/ntsrv/mls' nl
+                                  'ntimg/bin/ntsrv/mls/charmaps' nl
+                                  'ntimg/bin/ntsrv/mls/iconv' nl
+                                  'ntimg/bin/ntsrv/mls/iconv/tables' nl
+                                  'ntimg/bin/ntsrv/mls/iconv/tables/binary' nl
+                                  'ntimg/bin/ntsrv/mls/locale' nl
+                                  'ntimg/bin/ntsrv/mls/locale/de_DE.iso88591' nl
+                                  'ntimg/bin/ntsrv/mls/locale/de_DE.iso88591/ML_MESSAGES' nl
+                                  'ntimg/bin/ntsrv/mls/locale/en_GB.iso88591' nl
+                                  'ntimg/bin/ntsrv/mls/locale/en_GB.iso88591/ML_MESSAGES' nl
+                                  'ntimg/bin/ntsrv/mls/locale/en_US.iso88591' nl
+                                  'ntimg/bin/ntsrv/mls/locale/en_US.iso88591/ML_MESSAGES' nl
+                                  'ntimg/bin/ntsrv/mls/locale/fr_CA.iso88591' nl
+                                  'ntimg/bin/ntsrv/mls/locale/fr_CA.iso88591/ML_MESSAGES' nl
+                                  'ntimg/bin/ntsrv/mls/locale/fr_FR.iso88591' nl
+                                  'ntimg/bin/ntsrv/mls/locale/fr_FR.iso88591/ML_MESSAGES' nl
+                                  'ntimg/bin/ntsrv/mls/locale/ja_JP.CP932' nl
+                                  'ntimg/bin/ntsrv/mls/locale/ja_JP.CP932/ML_MESSAGES' nl
+                                  'ntimg/bin/ntsrv/mls/locale/ja_JP.SJIS' nl
+                                  'ntimg/bin/ntsrv/mls/locale/ja_JP.SJIS/ML_MESSAGES' nl
+                                  'ntimg/bin/ntsrv/mls/locale/ja_JP.eucJP' nl
+                                  'ntimg/bin/ntsrv/mls/locale/ja_JP.eucJP/ML_MESSAGES' nl
+                                  'ntimg/bin/ntsrv/mls/locale/ko_KR.eucKR' nl
+                                  'ntimg/bin/ntsrv/mls/locale/ko_KR.eucKR/ML_MESSAGES' nl
+                                  'ntimg/bin/ntsrv/mls/locale/zh_CN.gb' nl
+                                  'ntimg/bin/ntsrv/mls/locale/zh_CN.gb/ML_MESSAGES' nl
+                                  'ntimg/bin/ntsrv/mls/locale/zh_TW.big5' nl
+                                  'ntimg/bin/ntsrv/mls/locale/zh_TW.big5/ML_MESSAGES' nl
+                                  'ntimg/bin/ntsrv/mls/locale/zh_TW.ccdc' nl
+                                  'ntimg/bin/ntsrv/mls/locale/zh_TW.ccdc/ML_MESSAGES' nl
+                                  'ntimg/bin/ntsrv/mls/locale/zh_TW.eucTW' nl
+                                  'ntimg/bin/ntsrv/mls/locale/zh_TW.eucTW/ML_MESSAGES' nl
+                                  'ntimg/bin/ntsrv/ora' nl
+                                  'ntimg/bin/ntsrv/ora/udo' nl
+                                  'ntimg/bin/ntsrv/ora/udo/locale' nl
+                                  'ntimg/bin/ntsrv/sqlsrv' nl
+                                  'ntimg/bin/ntsrv/syb' nl
+                                  'ntimg/bin/ntsrv/syb/sybase' nl
+                                  'ntimg/bin/ntsrv/zh_CN.gb' nl
+                                  'ntimg/bin/ntsrv/zh_TW.big5' nl
+                                  'ntimg/bin/ntsrv/zh_TW.ccdc' nl
+                                  'ntimg/bin/ntsrv/zh_TW.eucTW' nl
+                                  'ntimg/bin/ssa' nl
+                                  'ntimg/bin/ssa/db2' nl
+                                  'ntimg/bin/ssa/infmx' nl
+                                  'ntimg/bin/ssa/ora' nl
+                                  'ntimg/bin/ssa/sqlsrv' nl
+                                  'ntimg/bin/ssa/syb' nl
+                                  'ntimg/bin/util' nl
+                                  'ntimg/config' nl
+                                  'ntimg/config/ntsrv' nl
+                                  'ntimg/config/ssa' nl
+                                  'ntimg/config/ssa/db2' nl
+                                  'ntimg/config/ssa/infmx' nl
+                                  'ntimg/config/ssa/ora' nl
+                                  'ntimg/config/ssa/sqlsrv' nl
+                                  'ntimg/config/ssa/syb' nl
+                                  'ntimg/doc' nl
+                                  'ntimg/doc/books' nl
+                                  'ntimg/pdbkm' nl
+                                  'ntimg/pdbkm/en_US.iso88591' nl
+                                  'ntimg/pdbkm/help' nl
+                                  'ntimg/pdbkm/images' nl
+                                  'ntimg/pdbkm/km' nl
+                                  'ntimg/pdbkm/psl' nl
+                                  'ntimg/windows' nl
+                                  'ntimg/windows/system' nl
+                                  '"Script Files"' nl
*----------------------------------------------------------------------------------------------------------
*
*           patrol-db change manager copy macros referenced by the copy rules
*
            cpmCMTbl                  =    TABLE()
            cpmCMTbl[.pdb]            =    *(bldWorkDir)
            cpmCMTbl[.dllDir]         =    *(pdb '/' mode)
            cpmCMTbl[.srcDir]         =    *(pdb)
            cpmCMTbl[.ThirdParty]     =    *(pdb '/ThirdParty')
            cpmCMTbl[.system32]       =    *(pdb '/ThirdParty/WindowsSystem32')
            cpmCMTbl[.common]         =    *(pdb '/common')
            cpmCMTbl[.server]         =    *(common '/server')
            cpmCMTbl[.pdbkm]          =    *(common '/pdbkm')
            cpmCMTbl[.mkcdl]          =    *(common '/cmx/cmxmig/mkcdl')
            cpmCMTbl[.pubDir]         =    *(pubDrive '/' bldPubDir)
            cpmCMTbl[.cm33PubDir]     =    *(pubDrive '/pdb_3_3_01' )
            cpmCMTbl[.db2PubDir]      =    *(pubDrive '/CM_7_1_01')
            cpmCMTbl[.udoDir]         =    *(srcDir '/alo')
            cpmCMTbl[.almPubDir]      =    *('\\Baddog\cli_release\drop3.2.01\image\common\bin\en_US.iso88591\sqlsrv\help' )
*----------------------------------------------------------------------------------------------------------
*   BEGIN('html/docs/build-inc-cpr.txt')
*   cpr_criteria: A string of one character criteria. Capital letters specify to which river(s) the copy
*                 rule applies. 'c' denotes windows client. 's' denotes windows server. 'r' denotes release
*                 mode. 'd' denotes debug mode.
*   cpr_command:  Specifies either 'cp' for copy or 'rm' for remove.
*   cpr_options:  The command line switches for the command.
*   cpr_src:      An expression that evaluates to a wildcard pattern that specifies the files in the build
*                 area as source files to the command.
*   cpr_tgt:      The directory name in the staging area that is the target of the command.
*   END()
            DATA('cpr(cpr_criteria,cpr_command,cpr_options,cpr_src,cpr_tgt)')
*----------------------------------------------------------------------------------------------------------
*
*           patrol-db change manager copy rules (used to copy to the staging area)
*
            cprCMTbl          =   TABLE()
            cprTbl            =   cprCMTbl
            cprTbl['akm']     =   TABLE()
            cprTbl['al2']     =   TABLE()
            cprTbl['ali']     =   TABLE()
            cprTbl['alm']     =   TABLE()
            cprTbl['alo']     =   TABLE()
            cprTbl['als']     =   TABLE()
            cprTbl['cmn']     =   TABLE()
            cprTbl['pse']     =   TABLE()

            c = 0
            cprTbl['akm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/akm/inifiles/clmgmkw.ini'),           'db2/config/mc/mcdb2.ini')                       ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cdr', 'cp', '-vp',   *(db2PubDir '/akm/src/hlp/*.chm'),               'common/bin/en_US.iso88591/db2/help')            ;* DM3
            cprTbl['akm'][c = c + 1]  = cpr('cdr', 'cp', '-vp',   *(db2PubDir '/clm/src/hlp/*.chm'),               'common/bin/en_US.iso88591/db2/help')            ;* DM3
            cprTbl['akm'][c = c + 1]  = cpr('cdr', 'cp', '-vp',   *(db2PubDir '/pse/src/hlp/*.chm'),               'common/bin/en_US.iso88591/db2/help/sqlx')       ;* DM3
            cprTbl['akm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/akmusr32.dll'),                       'db2/bin/md')                                    ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/akmusr32.dll'),                       'db2/bin/mm')                                    ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/akmfiles.dll'),                       'db2/bin/md')                                    ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/akmcmjb3.dll'),                       'db2/bin/md')                                    ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/akmtpl32.dll'),                       'db2/bin/md')                                    ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/akmdef32.dll'),                       'db2/bin/md')                                    ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/akmed.dll'),                          'db2/bin/md')                                    ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/akmlibdef.dll'),                      'db2/bin/md')                                    ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/akmvalidate.dll'),                    'db2/bin/md')                                    ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/akmfiles.dll'),                       'db2/bin/md')                                    ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/akmid32.dll'),                        'db2/bin/md')                                    ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/akmscmg3.dll'),                       'db2/bin/md')                                    ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/akmscr32.dll'),                       'db2/bin/md')                                    ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/akmsql32.dll'),                       'db2/bin/md')                                    ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/akmusr32.dll'),                       'db2/bin/md')                                    ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/akmutl32.dll'),                       'db2/bin/md')                                    ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/akmwiz.dll'),                         'db2/bin/md')                                    ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/akmcmjb3.lib'),                       'db2/bin/md')                                    ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/akmlibdef.lib'),                      'db2/bin/md')                                    ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/akmvalidate.lib'),                    'db2/bin/md')                                    ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/akmdef32.lib'),                       'db2/bin/md')                                    ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/akmed.lib'),                          'db2/bin/md')                                    ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/akmfiles.lib'),                       'db2/bin/md')                                    ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/akmid32.lib'),                        'db2/bin/md')                                    ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/akmscmg3.lib'),                       'db2/bin/md')                                    ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/akmscr32.lib'),                       'db2/bin/md')                                    ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/akmsql32.lib'),                       'db2/bin/md')                                    ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/akmusr32.lib'),                       'db2/bin/md')                                    ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/akmutl32.lib'),                       'db2/bin/md')                                    ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/akmwiz.lib'),                         'db2/bin/md')                                    ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/akm/version'),                        'db2/bin')                                       ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/akm/product'),                        'db2/bin')                                       ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/akm/scripts/*err*.m*'),               'db2/bin/md')                                    ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/akm/scripts/*.b*'),                   'db2/bin/md')                                    ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/akm/scripts/d2mxfuco.m51'),           'db2/bin/md')                                    ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/akm/scripts/bin/*.b*'),               'db2/bin/md')                                    ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/akm/inifiles/adkgmkw.ini'),           'db2/config/md/mddb2.ini')                       ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/akm/inifiles/adk*.ini'),              'db2/config/md')                                 ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/akm/inifiles/d2*.ini'),               'db2/config/md')                                 ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/akm/inifiles/akmutil.ini'),           'db2/config/md')                                 ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/akm/inifiles/monitors.ini'),          'db2/config/md')                                 ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/AKMUSR32.DLL'),                       'db2/bin/mm')                                    ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/AKMUTL32.DLL'),                       'db2/bin/mm')                                    ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/cmxcomp3.dll'),                       'db2/bin/mm')                                    ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/AKMUSR32.LIB'),                       'db2/bin/mm')                                    ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/AKMUTL32.LIB'),                       'db2/bin/mm')                                    ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/cmxcomp3.lib'),                       'db2/bin/mm')                                    ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/akm/inifiles/akmgmkw.ini'),           'db2/config/mm/mmdb2.ini')                       ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/akm/inifiles/akm*.ini'),              'db2/config/mm')                                 ;* DM
            cprTbl['akm'][c = c + 1]  = cpr('cdr', 'rm', '-f',    ,                                                'common/bin/en_US.iso88591/db2/help/altermvs.chm') ;* 3

            c = 0
            cprTbl['al2'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/al2/en_US.iso88591/images/*'),        'common/bin/en_US.iso88591/db22/images')         ;* BDGM3
            cprTbl['al2'][c = c + 1]  = cpr('cdr', 'cp', '-vp',   *(pubDir '/ald/src/hlp/alterdb2.chm'),           'common/bin/en_US.iso88591/db22/help')           ;* BDM3
            cprTbl['al2'][c = c + 1]  = cpr('cdr', 'cp', '-vp',   *(pubDir '/ald/src/hlp/*.chm'),                  'common/bin/en_US.iso88591/db22/help')           ;* DM3
            cprTbl['al2'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/al2cfa32.dll'),                       'db22/bin/md')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/al2cfa32.dll'),                       'db22/bin/mm')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/al2def32.dll'),                       'db22/bin/md')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/al2def32.dll'),                       'db22/bin/mm')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/al2ed32.dll'),                        'db22/bin/md')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/al2ed32.dll'),                        'db22/bin/mm')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/al2id32.dll'),                        'db22/bin/md')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/al2id32.dll'),                        'db22/bin/mm')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/al2iddl3.dll'),                       'db22/bin/md')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/al2iddl3.dll'),                       'db22/bin/mm')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/al2sql23.dll'),                       'db22/bin/md')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/al2sql23.dll'),                       'db22/bin/mm')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/al2usr32.dll'),                       'db22/bin/md')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/al2usr32.dll'),                       'db22/bin/mm')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('cdr', 'cp', '-vp',   *(dllDir '/al2tpl32.dll'),                       'db22/bin/md')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/al2utl32.dll'),                       'db22/bin/md')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/al2utl32.dll'),                       'db22/bin/mm')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/al2vld32.dll'),                       'db22/bin/mm')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/cmxcomp3.dll'),                       'db22/bin/mm')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/al2/mds/d22msess.mds'),               'db22/bin/md')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/al2vld32.lib'),                       'db22/bin/md')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/al2vld32.lib'),                       'db22/bin/mm')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/al2cfa32.lib'),                       'db22/bin/md')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/al2cfa32.lib'),                       'db22/bin/mm')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/al2def32.lib'),                       'db22/bin/md')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/al2def32.lib'),                       'db22/bin/mm')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/al2ed32.lib'),                        'db22/bin/md')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/al2ed32.lib'),                        'db22/bin/mm')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/al2id32.lib'),                        'db22/bin/md')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/al2id32.lib'),                        'db22/bin/mm')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/al2iddl3.lib'),                       'db22/bin/md')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/al2iddl3.lib'),                       'db22/bin/mm')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/al2sql23.lib'),                       'db22/bin/md')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/al2sql23.lib'),                       'db22/bin/mm')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/al2usr32.lib'),                       'db22/bin/md')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/al2usr32.lib'),                       'db22/bin/mm')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/al2utl32.lib'),                       'db22/bin/md')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/cmxcomp3.lib'),                       'db22/bin/md')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/cmxcomp3.lib'),                       'db22/bin/mm')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/al2/version'),                        'db22/bin')                                      ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/al2/product'),                        'db22/bin')                                      ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(server '/unix/scripts/shakeout_db2.msl'),      'db22/bin/md')                                   ;* BDG3
            cprTbl['al2'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/al2/mds/*.mds'),                      'db22/bin/md')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/al2/scripts/*.bsl'),                  'db22/bin/md')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/al2/inifiles/aclgmkw.ini'),           'db22/config/md/mddb22.ini')                     ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/al2/inifiles/d22*.ini'),              'db22/config/md')                                ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/al2utl32.lib'),                       'db22/bin/mm')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('cdr', 'rm', '-f',    ,                                                'common/bin/en_US.iso88591/db22/images/makefile') ;* BDGM3
            cprTbl['al2'][c = c + 1]  = cpr('cdr', 'rm', '-f',    ,                                                'common/bin/en_US.iso88591/db22/images/unixlist') ;* BDGM3
            cprTbl['al2'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/ald6_1_0svp.dll'),                    'bin/ntsrv/db2')                                 ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/ald7_1_0svp.dll'),                    'bin/ntsrv/db2')                                 ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/aldmpx32.dll'),                       'bin/ntsrv/db2')                                 ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/aldsvp32.dll'),                       'bin/ntsrv/db2')                                 ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/pdbdb2.exe'),                         'bin/ntsrv/db2')                                 ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(srcDir '/al2/en_US.iso88591/images/*.*'),      'bin/ntsrv/en_US.iso88591/db2/images')           ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(srcDir '/al2/scripts/aldserr.msl'),            'bin/ntsrv/db2')                                 ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/al2usr32.dll'),                       'bin/ssa/db2')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/al2iddl3.dll'),                       'bin/ssa/db2')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/al2tpl32.dll'),                       'bin/ssa/db2')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/al2id32.dll'),                        'bin/ssa/db2')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/al2cfa32.dll'),                       'bin/ssa/db2')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/al2def32.dll'),                       'bin/ssa/db2')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(srcDir '/al2/scripts/*.bsl'),                  'bin/ssa/db2')                                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(srcDir '/al2/inifiles/*.ini'),                 'config/ssa/db2')                                ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('sdr', 'rm', '-f',    ,                                                'config/ssa/db2/aclhosts.ini')                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('sdr', 'rm', '-f',    ,                                                'config/ssa/db2/aclsprof.ini')                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('sdr', 'rm', '-f',    ,                                                'config/ssa/db2/aclgmkw.ini')                    ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('sdr', 'rm', '-f',    ,                                                'pdbkm/psl/40.cat')                              ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('sdr', 'rm', '-f',    ,                                                'pdbkm/psl/Build.sh')                            ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('sdr', 'rm', '-f',    ,                                                'pdbkm/psl/Install.sh')                          ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('sdr', 'rm', '-f',    ,                                                'pdbkm/psl/pdb_PDB30_cat.txt')                   ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('sdr', 'rm', '-f',    ,                                                'pdbkm/psl/pslmsg.pl')                           ;* D3
            cprTbl['al2'][c = c + 1]  = cpr('sdr', 'rm', '-f',    ,                                                'pdbkm/psl/pslmsg.rc')                           ;* D3

            c = 0
            cprTbl['ali'][c = c + 1]  = cpr('cdr', 'cp', '-vp',   *(cm33PubDir '/ald/src/hlp/alterdb2.chm'),       'common/bin/en_US.iso88591/db22/help')           ;* G
            cprTbl['ali'][c = c + 1]  = cpr('cdr', 'cp', '-vp',   *(cm33PubDir '/hhupd.exe'),                      'common')                                        ;* G
            cprTbl['ali'][c = c + 1]  = cpr('cdr', 'cp', '-vp',   *(pubDir '/aki/src/hlp/*.chm'),                  'common/bin/en_US.iso88591/infmx/help')          ;* BD3
            cprTbl['ali'][c = c + 1]  = cpr('cdr', 'cp', '-vp',   *(cm33PubDir '/aki/src/hlp/ALTERINF.chm'),       'common/bin/en_US.iso88591/infmx/help')          ;* G
            cprTbl['ali'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/alicfa32.dll'),                       'infmx/bin/md')                                  ;* G
            cprTbl['ali'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/alidef32.dll'),                       'infmx/bin/md')                                  ;* G
            cprTbl['ali'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/alied32.dll'),                        'infmx/bin/md')                                  ;* G
            cprTbl['ali'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/aliid32.dll'),                        'infmx/bin/md')                                  ;* G
            cprTbl['ali'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/aliiddl3.dll'),                       'infmx/bin/md')                                  ;* G
            cprTbl['ali'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/aliscr3.dll'),                        'infmx/bin/md')                                  ;* G
            cprTbl['ali'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/alisql73.dll'),                       'infmx/bin/md')                                  ;* G
            cprTbl['ali'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/aliusr32.dll'),                       'infmx/bin/md')                                  ;* G
            cprTbl['ali'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/aliutil3.dll'),                       'infmx/bin/md')                                  ;* G
            cprTbl['ali'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/alivld32.dll'),                       'infmx/bin/md')                                  ;* G
            cprTbl['ali'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/alicfa32.lib'),                       'infmx/bin/md')                                  ;* G
            cprTbl['ali'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/alidef32.lib'),                       'infmx/bin/md')                                  ;* G
            cprTbl['ali'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/alied32.lib'),                        'infmx/bin/md')                                  ;* G
            cprTbl['ali'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/aliid32.lib'),                        'infmx/bin/md')                                  ;* G
            cprTbl['ali'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/aliiddl3.lib'),                       'infmx/bin/md')                                  ;* G
            cprTbl['ali'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/aliscr3.lib'),                        'infmx/bin/md')                                  ;* G
            cprTbl['ali'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/alisql73.lib'),                       'infmx/bin/md')                                  ;* G
            cprTbl['ali'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/alitpl32.dll'),                       'infmx/bin/md')                                  ;* G
            cprTbl['ali'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/aliusr32.lib'),                       'infmx/bin/md')                                  ;* G
            cprTbl['ali'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/aliutil3.lib'),                       'infmx/bin/md')                                  ;* G
            cprTbl['ali'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/alivld32.lib'),                       'infmx/bin/md')                                  ;* G
            cprTbl['ali'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/ali/version'),                        'infmx/bin')                                     ;* G
            cprTbl['ali'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/ali/product'),                        'infmx/bin')                                     ;* G
            cprTbl['ali'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(server '/unix/scripts/shakeout.msl'),          'infmx/bin/md')                                  ;* G
            cprTbl['ali'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/ali/mds/*.mds'),                      'infmx/bin/md')                                  ;* G
            cprTbl['ali'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/ali/scripts/*.bsl'),                  'infmx/bin/md')                                  ;* G
            cprTbl['ali'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/ali/inifiles/aligmkw.ini'),           'infmx/config/md/mdinfmx.ini')                   ;* G
            cprTbl['ali'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/ali/inifiles/ali*.ini'),              'infmx/config/md')                               ;* G
            cprTbl['ali'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/cmxcomp3.dll'),                       'infmx/bin/mm')                                  ;* G
            cprTbl['ali'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/cmxcomp3.lib'),                       'infmx/bin/mm')                                  ;* G
            cprTbl['ali'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/ali/aliiddl/*.pda'),                  'infmx/bin/mm')                                  ;* G
            cprTbl['ali'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/ali/inifiles/aligmkw.ini'),           'infmx/config/mm/mminfmx.ini')                   ;* G
            cprTbl['ali'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(srcDir '/ali/inifiles/*.ini'),                 'config/ssa/infmx')                              ;* G
            cprTbl['ali'][c = c + 1]  = cpr('sdr', 'rm', '-f',    ,                                                'config/ssa/infmx/aclhosts.ini')                 ;* G
            cprTbl['ali'][c = c + 1]  = cpr('sdr', 'rm', '-f',    ,                                                'config/ssa/infmx/aclsprof.ini')                 ;* G
            cprTbl['ali'][c = c + 1]  = cpr('sdr', 'rm', '-f',    ,                                                'config/ssa/infmx/aclgmkw.ini')                  ;* G
            cprTbl['ali'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/alisvi*.dll'),                        'bin/ntsrv/infmx')                               ;* G
            cprTbl['ali'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/aliiddl3.dll'),                       'bin/ntsrv/infmx')                               ;* G
            cprTbl['ali'][c = c + 1]  = cpr('sdr', 'cp', '-vpf',  *(dllDir '/alitpl32.dll'),                       'bin/ntsrv/infmx')                               ;* G
            cprTbl['ali'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(srcDir '/ali/aliiddl/aliiddlp.pda'),           'bin/ntsrv/infmx')                               ;* G
            cprTbl['ali'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/alidef*.dll'),                        'bin/ssa/infmx')                                 ;* G
            cprTbl['ali'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(srcDir '/ali/scripts/infserr.msl'),            'bin/ntsrv/infmx')                               ;* G
            cprTbl['ali'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(srcDir '/ali/scripts/*.bat'),                  'bin/ntsrv/infmx')                               ;* G
            cprTbl['ali'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(srcDir '/ali/scripts/infssuid.msl'),           'bin/ntsrv/infmx')                               ;* G
            cprTbl['ali'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(srcDir '/ali/scripts/infsruid.msl'),           'bin/ntsrv/infmx')                               ;* G
            cprTbl['ali'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(srcDir '/ali/scripts/alipgsiz'),               'bin/ntsrv/infmx')                               ;* G
            cprTbl['ali'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(srcDir '/ali/scripts/inftab'),                 'bin/ntsrv/infmx')                               ;* G
            cprTbl['ali'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/aliid32.dll'),                        'bin/ssa/infmx')                                 ;* G
            cprTbl['ali'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/aliusr32.dll'),                       'bin/ssa/infmx')                                 ;* G
            cprTbl['ali'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/alicfa32.dll'),                       'bin/ssa/infmx')                                 ;* G
            cprTbl['ali'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(srcDir '/ali/scripts/inf*.bsl'),               'bin/ssa/infmx')                                 ;* G
            cprTbl['ali'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(srcDir '/ali/scripts/inm*.bsl'),               'bin/ssa/infmx')                                 ;* G
            cprTbl['ali'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(srcDir '/ali/scripts/inr*.bsl'),               'bin/ssa/infmx')                                 ;* G
            cprTbl['ali'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(srcDir '/ali/scripts/cmi*.bsl'),               'bin/ssa/infmx')                                 ;* G

            c = 0
            cprTbl['alm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/almcm32.dll'),                        'sqlsrv/bin/md')                                 ;* B
            cprTbl['alm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/almdef32.dll'),                       'sqlsrv/bin/md')                                 ;* B
            cprTbl['alm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/almed32.dll'),                        'sqlsrv/bin/md')                                 ;* B
            cprTbl['alm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/almid32.dll'),                        'sqlsrv/bin/md')                                 ;* B
            cprTbl['alm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/almiddl3.dll'),                       'sqlsrv/bin/md')                                 ;* B
            cprTbl['alm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/almsql32.dll'),                       'sqlsrv/bin/md')                                 ;* B
            cprTbl['alm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/almutl32.dll'),                       'sqlsrv/bin/md')                                 ;* B
            cprTbl['alm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/almtpl32.dll'),                       'sqlsrv/bin/md')                                 ;* B
            cprTbl['alm'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/almcm32.lib'),                        'sqlsrv/bin/md')                                 ;* B
            cprTbl['alm'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/almdef32.lib'),                       'sqlsrv/bin/md')                                 ;* B
            cprTbl['alm'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/almed32.lib'),                        'sqlsrv/bin/md')                                 ;* B
            cprTbl['alm'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/almid32.lib'),                        'sqlsrv/bin/md')                                 ;* B
            cprTbl['alm'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/almiddl3.lib'),                       'sqlsrv/bin/md')                                 ;* B
            cprTbl['alm'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/almsql32.lib'),                       'sqlsrv/bin/md')                                 ;* B
            cprTbl['alm'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/almutl32.lib'),                       'sqlsrv/bin/md')                                 ;* B
            cprTbl['alm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(server '/unix/scripts/shakeout.msl'),          'sqlsrv/bin/md')                                 ;* B
            cprTbl['alm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/alm/version'),                        'sqlsrv/bin')                                    ;* B
            cprTbl['alm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/alm/product'),                        'sqlsrv/bin')                                    ;* B
            cprTbl['alm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/alm/mds/*.mds'),                      'sqlsrv/bin/md')                                 ;* B
            cprTbl['alm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/alm/scripts/*.bsl'),                  'sqlsrv/bin/md')                                 ;* B
            cprTbl['alm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/alm/inifiles/aclgmkw.ini'),           'sqlsrv/config/md/mdsqlsrv.ini')                 ;* B
            cprTbl['alm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/alm/inifiles/alm*.ini'),              'sqlsrv/config/md')                              ;* B
            cprTbl['alm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/cmxcomp3.dll'),                       'sqlsrv/bin/mm')                                 ;* B
            cprTbl['alm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/almusr32.dll'),                       'sqlsrv/bin/mm')                                 ;* B
            cprTbl['alm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/almcfa32.dll'),                       'sqlsrv/bin/mm')                                 ;* B
            cprTbl['alm'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/cmxcomp3.lib'),                       'sqlsrv/bin/mm')                                 ;* B
            cprTbl['alm'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/almusr32.lib'),                       'sqlsrv/bin/mm')                                 ;* B
            cprTbl['alm'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/almcfa32.lib'),                       'sqlsrv/bin/mm')                                 ;* B
            cprTbl['alm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/alm/almiddl/*.pda'),                  'sqlsrv/bin/mm')                                 ;* B
            cprTbl['alm'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/alm/inifiles/aclgmkw.ini'),           'sqlsrv/config/mm/mmsqlsrv.ini')                 ;* B
            cprTbl['alm'][c = c + 1]  = cpr('cdr', 'cp', '-vp',   *(almPubDir '/*.chm'),                           'common/bin/en_US.iso88591/sqlsrv/help')         ;* BDM3
            cprTbl['alm'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/alm*.dll'),                           'bin/ntsrv/sqlsrv')                              ;* B
            cprTbl['alm'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(srcDir '/alm/scripts/mssserr.msl'),            'bin/ntsrv/sqlsrv')                              ;* B
            cprTbl['alm'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(srcDir '/alm/scripts/msserr.msl'),             'bin/ntsrv/sqlsrv')                              ;* B
            cprTbl['alm'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(srcDir '/alm/scripts/msssuid.msl'),            'bin/ntsrv/sqlsrv')                              ;* B
            cprTbl['alm'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/almid32.dll'),                        'bin/ssa/sqlsrv')                                ;* B
            cprTbl['alm'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(srcDir '/alm/almiddl/almiddlp.pda'),           'bin/ssa/sqlsrv')                                ;* B
            cprTbl['alm'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(srcDir '/alm/scripts/*.bsl'),                  'bin/ssa/sqlsrv')                                ;* B
            cprTbl['alm'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(srcDir '/alm/inifiles/*.ini'),                 'config/ssa/sqlsrv')                             ;* B
            cprTbl['alm'][c = c + 1]  = cpr('sdr', 'rm', '-f',    ,                                                'config/ssa/sqlsrv/aclhosts.ini')                ;* B
            cprTbl['alm'][c = c + 1]  = cpr('sdr', 'rm', '-f',    ,                                                'config/ssa/sqlsrv/aclsprof.ini')                ;* B
            cprTbl['alm'][c = c + 1]  = cpr('sdr', 'rm', '-f',    ,                                                'config/ssa/sqlsrv/metaman.ini')                 ;* B
            cprTbl['alm'][c = c + 1]  = cpr('sdr', 'rm', '-f',    ,                                                'config/ssa/sqlsrv/aclgmkw.ini')                 ;* B

            c = 0
            cprTbl['alo'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/alodblstNT.exe'),                     'common/bin')                                    ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/ado*.dll'),                           'ora/bin/md')                                    ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/alo*.dll'),                           'ora/bin/md')                                    ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(common '/OEMIntegration/OEM1x/*.exe'),         'ora/oem/1x')                                    ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(common '/OEMIntegration/OEM1x/*.bmp'),         'ora/oem/1x')                                    ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(common '/OEMIntegration/OEM2x/*.exe'),         'ora/oem/2x')                                    ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(common '/OEMIntegration/OEM2x/*.gif'),         'ora/oem/2x')                                    ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(common '/OEMIntegration/OEM2x/*.class'),       'ora/oem/2x')                                    ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(common '/OEMIntegration/OEM2x/bmc.txt'),       'ora/oem/2x')                                    ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/ado*.lib'),                           'ora/bin/md')                                    ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/alo*.lib'),                           'ora/bin/md')                                    ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(server '/unix/scripts/shakeout.msl'),          'ora/bin/md')                                    ;* BDG3
            cprTbl['alo'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/alo/version'),                        'ora/bin')                                       ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/alo/product'),                        'ora/bin')                                       ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(common '/alx/alxcmdwz/*.tpl'),                 'ora/bin/md')                                    ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/alo/mds/*.mds'),                      'ora/bin/md')                                    ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/alo/en_US.iso88591/images/*'),        'common/bin/en_US.iso88591/ora/images')          ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/alo/scripts/*.bsl'),                  'ora/bin/md')                                    ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/alo/scripts/*.mcp'),                  'ora/bin/md')                                    ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/alo/inifiles/alo*.ini'),              'ora/config/md')                                 ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/alo/inifiles/ora*.ini'),              'ora/config/md')                                 ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/alo*.dll'),                           'ora/bin/mm')                                    ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/cmxchin3.dll'),                       'ora/bin/mm')                                    ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/cmxcomp3.dll'),                       'ora/bin/mm')                                    ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/alo*.lib'),                           'ora/bin/mm')                                    ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/cmxchin3.lib'),                       'ora/bin/mm')                                    ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/cmxcomp3.lib'),                       'ora/bin/mm')                                    ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('cdr', 'cp', '-v',    *(pubDir '/alo/src/hlp/*.chm'),                  'common/bin/en_US.iso88591/ora/help')            ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('cdr', 'rm', '-f',    ,                                                'ora/bin/md/alompx32.dll')                       ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('cd',  'rm', '-f',    ,                                                'ora/bin/md/alompx32.lib')                       ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('cdr', 'rm', '-f',    ,                                                'ora/bin/mm/alo73i32.dll')                       ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('cd',  'rm', '-f',    ,                                                'ora/bin/mm/alo73i32.lib')                       ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('cdr', 'rm', '-f',    ,                                                'ora/bin/mm/alo80i32.dll')                       ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('cd',  'rm', '-f',    ,                                                'ora/bin/mm/alo80i32.lib')                       ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('cdr', 'rm', '-f',    ,                                                'ora/bin/mm/alo81i32.dll')                       ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('cd',  'rm', '-f',    ,                                                'ora/bin/mm/alo81i32.lib')                       ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('cdr', 'rm', '-f',    ,                                                'ora/bin/mm/alompx32.dll')                       ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('cd',  'rm', '-f',    ,                                                'ora/bin/mm/alompx32.lib')                       ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('cdr', 'rm', '-f',    ,                                                'common/bin/en_US.iso88591/ora/images/makefile') ;* BDGM3
            cprTbl['alo'][c = c + 1]  = cpr('cdr', 'rm', '-f',    ,                                                'common/bin/en_US.iso88591/ora/images/unixlist') ;* BDGM3
            cprTbl['alo'][c = c + 1]  = cpr('cdr', 'rm', '-f',    ,                                                'ora/bin/md/aloaux32.*')                         ;* D3
            cprTbl['alo'][c = c + 1]  = cpr('cdr', 'rm', '-f',    ,                                                'ora/bin/mm/aloaux32.*')                         ;* D3
            cprTbl['alo'][c = c + 1]  = cpr('cdr', 'rm', '-f',    ,                                                'ora/bin/md/alo*i32.*')                          ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(udoDir '/alold/NT/alold73.exe'),               'bin/ntsrv/ora')                                 ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(udoDir '/alold/NT/alold80.exe'),               'bin/ntsrv/ora')                                 ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(udoDir '/alold/NT/alold81.exe'),               'bin/ntsrv/ora')                                 ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(udoDir '/alounl/NT/alounl73.exe'),             'bin/ntsrv/ora')                                 ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(udoDir '/alounl/NT/alounl80.exe'),             'bin/ntsrv/ora')                                 ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(udoDir '/alounl/NT/alounl81.exe'),             'bin/ntsrv/ora')                                 ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(udoDir '/alounl/NT/aloiod73.exe'),             'bin/ntsrv/ora')                                 ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(udoDir '/alounl/NT/aloiod80.exe'),             'bin/ntsrv/ora')                                 ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(udoDir '/alounl/NT/aloiod81.exe'),             'bin/ntsrv/ora')                                 ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(udoDir '/alounl/NT/*.cat'),                    'bin/ntsrv/ora')                                 ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(udoDir '/alounl/NT/locale/*.nls'),             'bin/ntsrv/ora/udo/locale')                      ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(udoDir '/alounl/admin/alo*'),                  'bin/ntsrv/ora')                                 ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/alo*.dll'),                           'bin/ntsrv/ora')                                 ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/alodblstnt.exe'),                     'bin/ntsrv/ora')                                 ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(srcDir '/alo/scripts/ors*.msl'),               'bin/ntsrv/ora')                                 ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/aloid32.dll'),                        'bin/ssa/ora')                                   ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(srcDir '/alo/scripts/or8*.bsl'),               'bin/ssa/ora')                                   ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(srcDir '/alo/scripts/ora*.bsl'),               'bin/ssa/ora')                                   ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(srcDir '/alo/scripts/orf*.bsl'),               'bin/ssa/ora')                                   ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(srcDir '/alo/scripts/orm*.bsl'),               'bin/ssa/ora')                                   ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(srcDir '/alo/scripts/orn*.bsl'),               'bin/ssa/ora')                                   ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(srcDir '/alo/scripts/orx*.bsl'),               'bin/ssa/ora')                                   ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(srcDir '/alo/scripts/cmo*.bsl'),               'bin/ssa/ora')                                   ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(srcDir '/alo/scripts/cxo*.bsl'),               'bin/ssa/ora')                                   ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(srcDir '/alo/en_US.iso88591/images/*.*'),      'bin/ntsrv/en_US.iso88591/ora/images')           ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(srcDir '/alo/inifiles/*.ini'),                 'config/ssa/ora')                                ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('sdr', 'rm', '-f',    ,                                                'config/ssa/ora/aclhosts.ini')                   ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('sdr', 'rm', '-f',    ,                                                'config/ssa/ora/aclsprof.ini')                   ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('sdr', 'rm', '-f',    ,                                                'config/ssa/ora/metaman.ini')                    ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('sdr', 'rm', '-f',    ,                                                'config/ssa/ora/aclgmkw.ini')                    ;* BD3
            cprTbl['alo'][c = c + 1]  = cpr('sdr', 'rm', '-f',    ,                                                'config/ssa/ora/al8gmkw.ini')                    ;* BD3

            c = 0
            cprTbl['als'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/als/version'),                        'syb/bin')                                       ;* D3
            cprTbl['als'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/als/product'),                        'syb/bin')                                       ;* D3
            cprTbl['als'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(pubDir '/als/src/hlp/altersyb.chm'),           'common/bin/en_US.iso88591/syb/help')            ;* D3
            cprTbl['als'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/als/alsiddl/alsiddlp.pda'),           'syb/bin/mm')                                    ;* D3
            cprTbl['als'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/als/mds/sy4zsess.mds'),               'syb/bin/md')                                    ;* D3
            cprTbl['als'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/als/mds/sybzsess.mds'),               'syb/bin/md')                                    ;* D3
            cprTbl['als'][c = c + 1]  = cpr('cdr', 'cp', '-Rvp',  *(srcDir '/als/scripts/*.bsl'),                  'syb/bin/md')                                    ;* D3
            cprTbl['als'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/als/scripts/sqsfkfix.mcp'),           'syb/bin/md')                                    ;* D3
            cprTbl['als'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(server '/unix/scripts/shakeout.msl'),          'syb/bin/md')                                    ;* D3
            cprTbl['als'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/alstpl32.dll'),                       'syb/bin/mm')                                    ;* D3
            cprTbl['als'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/alscfa32.dll'),                       'syb/bin/mm')                                    ;* D3
            cprTbl['als'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/alsid32.dll'),                        'syb/bin/mm')                                    ;* D3
            cprTbl['als'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/alsiddl3.dll'),                       'syb/bin/mm')                                    ;* D3
            cprTbl['als'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/alsusr32.dll'),                       'syb/bin/mm')                                    ;* D3
            cprTbl['als'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/alscfa32.dll'),                       'syb/bin/mm')                                    ;* D3
            cprTbl['als'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/cmxcomp3.dll'),                       'syb/bin/mm')                                    ;* D3
            cprTbl['als'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/alscm32.dll'),                        'syb/bin/md')                                    ;* D3
            cprTbl['als'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/alsdef32.dll'),                       'syb/bin/md')                                    ;* D3
            cprTbl['als'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/alsed32.dll'),                        'syb/bin/md')                                    ;* D3
            cprTbl['als'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/alsutl32.dll'),                       'syb/bin/md')                                    ;* D3
            cprTbl['als'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/alsysql3.dll'),                       'syb/bin/md')                                    ;* D3
            cprTbl['als'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/alscfa32.lib'),                       'syb/bin/mm')                                    ;* D3
            cprTbl['als'][c = c + 1]  = cpr('cd',  'cp', '-Rvp',  *(dllDir '/alsi*.lib'),                          'syb/bin/mm')                                    ;* D3
            cprTbl['als'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/cmxcomp3.lib'),                       'syb/bin/mm')                                    ;* D3
            cprTbl['als'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/alsusr32.lib'),                       'syb/bin/mm')                                    ;* D3
            cprTbl['als'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/alscm32.lib'),                        'syb/bin/md')                                    ;* D3
            cprTbl['als'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/alsdef32.lib'),                       'syb/bin/md')                                    ;* D3
            cprTbl['als'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/alsed32.lib'),                        'syb/bin/md')                                    ;* D3
            cprTbl['als'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/alsutl32.lib'),                       'syb/bin/md')                                    ;* D3
            cprTbl['als'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/alsysql3.lib'),                       'syb/bin/md')                                    ;* D3
            cprTbl['als'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/als/inifiles/alsimpac.ini'),          'syb/config/md')                                 ;* D3
            cprTbl['als'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/als/inifiles/monitors.ini'),          'syb/config/md')                                 ;* D3
            cprTbl['als'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/als/inifiles/sy4def.ini'),            'syb/config/md')                                 ;* D3
            cprTbl['als'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/als/inifiles/sy4pipe.ini'),           'syb/config/md')                                 ;* D3
            cprTbl['als'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/als/inifiles/sy4util.ini'),           'syb/config/md')                                 ;* D3
            cprTbl['als'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/als/inifiles/sybcfzy.ini'),           'syb/config/md')                                 ;* D3
            cprTbl['als'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/als/inifiles/sybcpwiz.ini'),          'syb/config/md')                                 ;* D3
            cprTbl['als'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/als/inifiles/sybdef.ini'),            'syb/config/md')                                 ;* D3
            cprTbl['als'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/als/inifiles/sybgst.ini'),            'syb/config/md')                                 ;* D3
            cprTbl['als'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/als/inifiles/sybmfzy.ini'),           'syb/config/md')                                 ;* D3
            cprTbl['als'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/als/inifiles/sybmon.ini'),            'syb/config/md')                                 ;* D3
            cprTbl['als'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/als/inifiles/sybpipe.ini'),           'syb/config/md')                                 ;* D3
            cprTbl['als'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/als/inifiles/sybutil.ini'),           'syb/config/md')                                 ;* D3
            cprTbl['als'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/als/inifiles/monitors.ini'),          'syb/config/mm')                                 ;* D3

            cprTbl['als'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/als*.dll'),                           'bin/ntsrv/syb')                                 ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/analyzet.exe'),                       'bin/ntsrv/syb')                                 ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/patrolisql.exe'),                     'bin/ntsrv/syb')                                 ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/sspcvt.exe'),                         'bin/ntsrv/syb')                                 ;* D3
*           cprTbl['als'][c = c + 1]  = cpr('sdr', 'cp', '-vpf',  *(dllDir '/alsid32.dll'),                        'bin/ntsrv/syb')                                 ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'cp', '-vpf',  *(srcDir '/als/server/analyzet/analyzet.txt'),   'bin/ntsrv/syb')                                 ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'cp', '-vpf',  *(srcDir '/als/server/sspcvt/SSPCVT.txt'),       'bin/ntsrv/syb')                                 ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'cp', '-vpf',  *(srcDir '/als/alsiddl/alsiddlp.pda'),           'bin/ntsrv/syb')                                 ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'cp', '-vpf',  *(srcDir '/als/scripts/sqserr.msl'),             'bin/ntsrv/syb')                                 ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'cp', '-vpf',  *(srcDir '/als/scripts/sqsserr.msl'),            'bin/ntsrv/syb')                                 ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'cp', '-vpf',  *(srcDir '/als/scripts/sqssuid.msl'),            'bin/ntsrv/syb')                                 ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(srcDir '/als/scripts/sq*.bsl'),                'bin/ssa/syb')                                   ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(srcDir '/als/scripts/sy*.bsl'),                'bin/ssa/syb')                                   ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(srcDir '/als/scripts/cms*.bsl'),               'bin/ssa/syb')                                   ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(srcDir '/als/scripts/sqr*.bsl'),               'bin/ssa/syb')                                   ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'cp', '-vpf',  *(ThirdParty '/Sybase/bin/libblk.dll'),          'bin/ntsrv/syb/sybase')                          ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'cp', '-vpf',  *(ThirdParty '/Sybase/bin/libcomn.dll'),         'bin/ntsrv/syb/sybase')                          ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'cp', '-vpf',  *(ThirdParty '/Sybase/bin/libcs.dll'),           'bin/ntsrv/syb/sybase')                          ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'cp', '-vpf',  *(ThirdParty '/Sybase/bin/libct.dll'),           'bin/ntsrv/syb/sybase')                          ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'cp', '-vpf',  *(ThirdParty '/Sybase/bin/libddce.dll'),         'bin/ntsrv/syb/sybase')                          ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'cp', '-vpf',  *(ThirdParty '/Sybase/bin/libdreg.dll'),         'bin/ntsrv/syb/sybase')                          ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'cp', '-vpf',  *(ThirdParty '/Sybase/bin/libintl.dll'),         'bin/ntsrv/syb/sybase')                          ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'cp', '-vpf',  *(ThirdParty '/Sybase/bin/libsdce.dll'),         'bin/ntsrv/syb/sybase')                          ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'cp', '-vpf',  *(ThirdParty '/Sybase/bin/libskrb.dll'),         'bin/ntsrv/syb/sybase')                          ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'cp', '-vpf',  *(ThirdParty '/Sybase/bin/libsmssp.dll'),        'bin/ntsrv/syb/sybase')                          ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'cp', '-vpf',  *(ThirdParty '/Sybase/bin/libsrv.dll'),          'bin/ntsrv/syb/sybase')                          ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'cp', '-vpf',  *(ThirdParty '/Sybase/bin/libsybdb.dll'),        'bin/ntsrv/syb/sybase')                          ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'cp', '-vpf',  *(ThirdParty '/Sybase/bin/libtcl.dll'),          'bin/ntsrv/syb/sybase')                          ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'cp', '-vpf',  *(ThirdParty '/Sybase/bin/nldecnet.dll'),        'bin/ntsrv/syb/sybase')                          ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'cp', '-vpf',  *(ThirdParty '/Sybase/bin/nlmsnmp.dll'),         'bin/ntsrv/syb/sybase')                          ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'cp', '-vpf',  *(ThirdParty '/Sybase/bin/nlnwlink.dll'),        'bin/ntsrv/syb/sybase')                          ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'cp', '-vpf',  *(ThirdParty '/Sybase/bin/nlwnsck.dll'),         'bin/ntsrv/syb/sybase')                          ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'cp', '-vpf',  *(ThirdParty '/Sybase/bin/bcp115.exe'),          'bin/ntsrv/syb/sybase')                          ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'cp', '-vpf',  *(srcDir '/als/inifiles/alsimpac.ini'),          'config/ssa/syb')                                ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'cp', '-vpf',  *(srcDir '/als/inifiles/chgmgrs.ini'),           'config/ssa/syb')                                ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'cp', '-vpf',  *(srcDir '/als/inifiles/monitors.ini'),          'config/ssa/syb')                                ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'cp', '-vpf',  *(srcDir '/als/inifiles/sy4def.ini'),            'config/ssa/syb')                                ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'cp', '-vpf',  *(srcDir '/als/inifiles/sy4pipe.ini'),           'config/ssa/syb')                                ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'cp', '-vpf',  *(srcDir '/als/inifiles/sy4util.ini'),           'config/ssa/syb')                                ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'cp', '-vpf',  *(srcDir '/als/inifiles/sybcfzy.ini'),           'config/ssa/syb')                                ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'cp', '-vpf',  *(srcDir '/als/inifiles/sybcpwiz.ini'),          'config/ssa/syb')                                ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'cp', '-vpf',  *(srcDir '/als/inifiles/sybdef.ini'),            'config/ssa/syb')                                ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'cp', '-vpf',  *(srcDir '/als/inifiles/sybgst.ini'),            'config/ssa/syb')                                ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'cp', '-vpf',  *(srcDir '/als/inifiles/sybmfzy.ini'),           'config/ssa/syb')                                ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'cp', '-vpf',  *(srcDir '/als/inifiles/sybmon.ini'),            'config/ssa/syb')                                ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'cp', '-vpf',  *(srcDir '/als/inifiles/sybpipe.ini'),           'config/ssa/syb')                                ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'cp', '-vpf',  *(srcDir '/als/inifiles/sybutil.ini'),           'config/ssa/syb')                                ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'rm', '-f',    ,                                                'bin/ssa/syb/aclhosts.ini')                      ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'rm', '-f',    ,                                                'bin/ssa/syb/aclsprof.ini')                      ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'rm', '-f',    ,                                                'bin/ssa/syb/metaman.ini')                       ;* D3
            cprTbl['als'][c = c + 1]  = cpr('sdr', 'rm', '-f',    ,                                                'bin/ssa/syb/aclgmkw.ini')                       ;* D3

            c = 0
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(common '/lib/*.dll'),                          'common/bin')                                    ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(common '/build/client/bin/*'),                 'common/bin')                                    ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(common '/build/client/tag/*'),                 'common/tag')                                    ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(common '/build/client/util/*'),                'common/util')                                   ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(common '/build/client/windows/common/*'),      'common/windows/system/common')                  ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-Rvpf', *(common '/build/client/windows/nt'),            'common/windows/system')                         ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-Rvpf', *(common '/build/client/windows/win95'),         'common/windows/system')                         ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(common '/build/client/icons/*'),               'common/icons')                                  ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(common '/resources/xfer.avi'),                 'common/bin')                                    ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(common '/inifiles/aclsprof.ini'),              'special')                                       ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(common '/inifiles/aclhosts.ini'),              'special')                                       ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(common '/en_US.iso88591/msgfiles/*.msg'),      'common/bin/en_US.iso88591')                     ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(common '/en_US.iso88591/images/*'),            'common/bin/en_US.iso88591/common/images')       ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(ThirdParty '/mls/iconv/tables/binary/*'),      'common/bin/iconv/tables/binary')                ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(ThirdParty '/mls/iconv/*'),                    'common/bin/iconv')                              ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(ThirdParty '/mls/charmaps/*'),                 'common/bin/charmaps')                           ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-Rvpf', *(ThirdParty '/mls/locale/*'),                   'common/bin/locale')                             ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(ThirdParty '/' mode '/*.dll'),                 'common/bin')                                    ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(ThirdParty '/' mode '/*.lib'),                 'common/bin')                                    ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(system32 '/' mode '/vc60/msvc*.dll'),          'common/bin')                                    ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(system32 '/' mode '/vc60/mfc*.dll'),           'common/bin')                                    ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cr',  'cp', '-vpf',  *(system32 '/' mode '/vc60/msvc*.dll'),          'common/bin')                                    ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cr',  'cp', '-vpf',  *(system32 '/' mode '/vc60/mfc*.dll'),           'common/bin')                                    ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/schtpl32.dll'),                       'common/bin')                                    ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/acl*.dll'),                           'common/bin')                                    ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/th.dll'),                             'common/bin')                                    ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/alx*.dll'),                           'common/bin')                                    ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/cgs*.dll'),                           'common/bin')                                    ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/acm*.dll'),                           'common/bin')                                    ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/alz*.dll'),                           'common/bin')                                    ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/cmxcon*.dll'),                        'common/bin')                                    ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/acmhhgen.exe'),                       'common/bin')                                    ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/AddSvc.exe'),                         'common/bin')                                    ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/alxidtst.exe'),                       'common/bin')                                    ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/patrolcm.exe'),                       'common/bin')                                    ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/patrolco.exe'),                       'common/bin')                                    ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/patrolmsg.exe'),                      'common/bin')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/patroltv.exe'),                       'common/bin')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/pcmexec.exe'),                        'common/windows/system/common')                  ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/acl*.lib'),                           'common/bin')                                    ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/schtpl32.lib'),                       'common/bin')                                    ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/cmxcon*.lib'),                        'common/bin')                                    ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/alx*.lib'),                           'common/bin')                                    ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/cgs*.lib'),                           'common/bin')                                    ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/acm*.lib'),                           'common/bin')                                    ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/alz*.lib'),                           'common/bin')                                    ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/lcns*.lib'),                          'common/bin')                                    ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(common '/scripts/*.*'),                        'common/bin')                                    ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/*.tlb'),                              'common/bin')                                    ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(common '/alx/alxcvt/alxc*.pda'),               'common/bin')                                    ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(common '/cmx/inifiles/aclgmkw.ini'),           'common/config')                                 ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(common '/inifiles/aclgmkw.tag'),               'common/config')                                 ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(common '/inifiles/rdbms.ini'),                 'common/config')                                 ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(common '/inifiles/omserr.ini'),                'common/config')                                 ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(common '/sch/scripts/*.bsl'),                  'common/sch')                                    ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(pdbkm '/knowledge/asoMergeKm.bin'),            'oss/ossinteg')                                  ;* BDM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(pdbkm '/knowledge/asoMergeKm.psl'),            'oss/ossinteg')                                  ;* BDM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(pdbkm '/knowledge/dbstats_integration.txt'),   'oss/ossinteg')                                  ;* BDM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(pdbkm '/knowledge/DBSTATS_ORAOBJECTS_ADD.km'), 'oss/ossinteg')                                  ;* BDM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(pdbkm '/knowledge/getkmstr'),                  'oss/ossinteg')                                  ;* BDM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(pdbkm '/knowledge/kmtext.sh'),                 'oss/ossinteg')                                  ;* BDM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(pdbkm '/knowledge/mergekms'),                  'oss/ossinteg')                                  ;* BDM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(pdbkm '/knowledge/mergekms.bat'),              'oss/ossinteg')                                  ;* BDM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(pdbkm '/knowledge/mlmsgfmt'),                  'oss/ossinteg')                                  ;* BDM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(pdbkm '/knowledge/msgmerge'),                  'oss/ossinteg')                                  ;* BDM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/CM*.DLL'),                            'common/mc/bin')                                 ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cd',  'cp', '-vpf',  *(dllDir '/CM*.LIB'),                            'common/mc/bin')                                 ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpr',  *(mkcdl '/dependencies/*'),                      'common/mc/bin')                                 ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(common '/cmx/cmxicdl/*.pda'),                  'common/mc/bin')                                 ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(mkcdl '/dependencies/aclgmkw.cfg'),            'common/config')                                 ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'rm', '-f',    ,                                                'common/mc/bin/aclgmkw.cfg')                     ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(common '/cmx/scripts/*.bsl'),                  'common/mc/bin')                                 ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(common '/cmx/inifiles/cmx*.ini'),              'common/mc/config')                              ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(common '/cmx/inifiles/aclgmkw.ini'),           'common/mc/config/mcora.ini')                    ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/en_US.iso88591/*.rll'),               'common/bin/en_US.iso88591')                     ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vp',   *(pubDir '/pdb/src/hlp/patroldb/*.chm'),         'common/bin/en_US.iso88591/common/help')         ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vp',   *(pubDir '/pdb/src/hlp/patroldb/*.map'),         'common/bin')                                    ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vp',   *(pubDir '/hhupd.exe'),                          'common')                                        ;* BDM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vp',   *(pubDir '/pdb/src/hlp/his/his.hlp'),            'common/bin/en_US.iso88591/common/help')         ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vp',   *(pubDir '/pdb/src/hlp/his/his.cnt'),            'common/bin/en_US.iso88591/common/help')         ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vp',   *(pubDir '/pdb/src/hlp/license/pdblcns.cnt'),    'common/bin/en_US.iso88591/common/help')         ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vp',   *(pubDir '/pdb/src/hlp/license/pdblcns.hlp'),    'common/bin/en_US.iso88591/common/help')         ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vp',   *(pubDir '/pdb/src/hlp/appmgr/*.chm'),           'common/bin/en_US.iso88591/common/help')         ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vp',   *(pubDir '/pdb/src/hlp/cmdpipe/*.chm'),          'common/bin/en_US.iso88591/common/help')         ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vp',   *(pubDir '/pdb/src/hlp/dataed/*.chm'),           'common/bin/en_US.iso88591/common/help')         ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vp',   *(pubDir '/pdb/src/hlp/ocdled/*.chm'),           'common/bin/en_US.iso88591/common/help')         ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vp',   *(pubDir '/pdb/src/hlp/prived/*.chm'),           'common/bin/en_US.iso88591/common/help')         ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vp',   *(pubDir '/pdb/src/hlp/schedman/*.chm'),         'common/bin/en_US.iso88591/common/help')         ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vp',   *(pubDir '/pdb/src/hlp/scripted/*.chm'),         'common/bin/en_US.iso88591/common/help')         ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'cp', '-vp',   *(pubDir '/pdb/src/hlp/selctwiz/*.chm'),         'common/bin/en_US.iso88591/common/help')         ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'rm', '-f',    ,                                                'common/mc/bin/aclgmkw.cfg')                     ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'rm', '-f',    ,                                                'common/bin/AddSvc.exe')                         ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'rm', '-f',    ,                                                'common/bin/alodblstNT.exe')                     ;* BDM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'rm', '-f',    ,                                                'common/bin/en_US.iso88591/patroldb.rll')        ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'rm', '-f',    ,                                                'common/bin/en_US.iso88591/patrolsd.rll')        ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'rm', '-f',    ,                                                'common/bin/patrolmsg.exe')                      ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'rm', '-f',    ,                                                'common/bin/patroltv.exe')                       ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'rm', '-f',    ,                                                'common/bin/en_US.iso88591/common/images/makefile') ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('cdr', 'rm', '-f',    ,                                                'common/bin/en_US.iso88591/common/images/unixlist') ;* BDGM3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/pcmexec.exe'),                        'bin/winnt')                                     ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(common '/lib/pemapi.dll'),                     'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(common '/lib/acmtcp3d.dll'),                   'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/acmbty.dll'),                         'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/cmxhelpmap.dll'),                     'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/schtpl32.dll'),                       'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/acmcha32.dll'),                       'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/aclmic32.dll'),                       'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/acmbio32.dll'),                       'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/acmcmp32.dll'),                       'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/acmutils.dll'),                       'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/acmxio32.dll'),                       'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/alxcm32.dll'),                        'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/alxeval.dll'),                        'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/alxexpr3.dll'),                       'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/alxexedit.dll'),                      'bin/common')                                    ;* 3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/alxdef32.dll'),                       'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/alxfltr3.dll'),                       'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/alxid32.dll'),                        'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/alxport.dll'),                        'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/alxupf32.dll'),                       'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/alxtpl32.dll'),                       'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/alxvar32.dll'),                       'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/acmmem32.dll'),                       'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/acmoms32.dll'),                       'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/acmrtm32.dll'),                       'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/acmtcp32.dll'),                       'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/acmtr32.dll'),                        'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/acmvts32.dll'),                       'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/acmscr32.dll'),                       'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/acmsys32.dll'),                       'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/acmhh32.dll'),                        'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/acmcfg32.dll'),                       'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/acmpars3.dll'),                       'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/acmtpl32.dll'),                       'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/acmcvio3.dll'),                       'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/acmobj32.dll'),                       'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/acmyy32.dll'),                        'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/aclodx32.dll'),                       'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/cgsgctl3.dll'),                       'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/cgsedit3.dll'),                       'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/cgsmctl3.dll'),                       'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/cgsxctl3.dll'),                       'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/getopt32.dll'),                       'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-vp',   *(server '/jzs/jzsexe/psapi.dll'),               'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sd',  'cp', '-vp',   *(server '/jzs/jzsexe/psapi.lib'),               'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sd',  'cp', '-vp',   *(system32 '/' mode '/vc60/*.dll'),              'bin/ntsrv/mls')                                 ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sr',  'cp', '-vp',   *(system32 '/' mode '/vc60/*.dll'),              'bin/ntsrv/mls')                                 ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sr',  'cp', '-Rvp',  *(ThirdParty '/' mode '/MVC611V6as.dll'),        'bin/ntsrv/mls')                                 ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sd',  'cp', '-Rvp',  *(ThirdParty '/' mode '/MVC611V6asd.dll'),       'bin/ntsrv/mls')                                 ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sr',  'cp', '-Rvp',  *(ThirdParty '/' mode '/MVC611as.dll'),          'bin/ntsrv/mls')                                 ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sd',  'cp', '-Rvp',  *(ThirdParty '/' mode '/MVC611asd.dll'),         'bin/ntsrv/mls')                                 ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sr',  'cp', '-Rvp',  *(ThirdParty '/' mode '/OC1050R.dll'),           'bin/ntsrv/mls')                                 ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sd',  'cp', '-Rvp',  *(ThirdParty '/' mode '/OC1050D.dll'),           'bin/ntsrv/mls')                                 ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sr',  'cp', '-Rvp',  *(ThirdParty '/' mode '/OSC611V6as.dll'),        'bin/ntsrv/mls')                                 ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sd',  'cp', '-Rvp',  *(ThirdParty '/' mode '/OSC611V6asd.dll'),       'bin/ntsrv/mls')                                 ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sr',  'cp', '-Rvp',  *(ThirdParty '/' mode '/OSC611as.dll'),          'bin/ntsrv/mls')                                 ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sd',  'cp', '-Rvp',  *(ThirdParty '/' mode '/OSC611asd.dll'),         'bin/ntsrv/mls')                                 ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sr',  'cp', '-Rvp',  *(ThirdParty '/' mode '/OT603V6as.dll'),         'bin/ntsrv/mls')                                 ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sd',  'cp', '-Rvp',  *(ThirdParty '/' mode '/OT603V6asd.dll'),        'bin/ntsrv/mls')                                 ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sr',  'cp', '-Rvp',  *(ThirdParty '/' mode '/OT603as.dll'),           'bin/ntsrv/mls')                                 ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sd',  'cp', '-Rvp',  *(ThirdParty '/' mode '/OT603asd.dll'),          'bin/ntsrv/mls')                                 ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sr',  'cp', '-Rvp',  *(ThirdParty '/' mode '/OT52as.dll'),            'bin/ntsrv/mls')                                 ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sr',  'cp', '-Rvp',  *(ThirdParty '/' mode '/XMLLIB50.dll'),          'bin/ntsrv/mls')                                 ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sd',  'cp', '-Rvp',  *(ThirdParty '/' mode '/XMLLIB50d.dll'),         'bin/ntsrv/mls')                                 ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sr',  'cp', '-Rvp',  *(ThirdParty '/' mode '/XMLLIB60.dll'),          'bin/ntsrv/mls')                                 ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sd',  'cp', '-Rvp',  *(ThirdParty '/' mode '/XMLLIB60d.dll'),         'bin/ntsrv/mls')                                 ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sr',  'cp', '-Rvp',  *(ThirdParty '/' mode '/og701V6as.dll'),         'bin/ntsrv/mls')                                 ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sd',  'cp', '-Rvp',  *(ThirdParty '/' mode '/og701V6asd.dll'),        'bin/ntsrv/mls')                                 ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sr',  'cp', '-Rvp',  *(ThirdParty '/' mode '/og701as.dll'),           'bin/ntsrv/mls')                                 ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sd',  'cp', '-Rvp',  *(ThirdParty '/' mode '/og701asd.dll'),          'bin/ntsrv/mls')                                 ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sr',  'cp', '-Rvp',  *(ThirdParty '/' mode '/og70as.dll'),            'bin/ntsrv/mls')                                 ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sd',  'cp', '-Rvp',  *(ThirdParty '/' mode '/og70asd.dll'),           'bin/ntsrv/mls')                                 ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sr',  'cp', '-Rvp',  *(ThirdParty '/' mode '/xtl20.dll'),             'bin/ntsrv/mls')                                 ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sd',  'cp', '-Rvp',  *(ThirdParty '/' mode '/xtl20d.dll'),            'bin/ntsrv/mls')                                 ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(ThirdParty '/' mode '/acmmls32.dll'),          'bin/ntsrv/mls')                                 ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(ThirdParty '/' mode '/cygwin.dll'),            'bin/ntsrv/mls')                                 ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(ThirdParty '/' mode '/cygwin.dll'),            'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(ThirdParty '/' mode '/psapi.dll'),             'bin/ntsrv/mls')                                 ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(ThirdParty '/' mode '/psapi.dll'),             'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(ThirdParty '/' mode '/win32gnu.dll'),          'bin/ntsrv/mls')                                 ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(ThirdParty '/' mode '/win32gnu.dll'),          'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(ThirdParty '/' mode '/*.exe'),                 'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(ThirdParty '/' mode '/*.gz'),                  'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(system32 '/release/NT/*.dll'),                 'bin/ntsrv/mls')                                 ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(ThirdParty '/' mode '/acmmls32.dll'),          'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sr',  'cp', '-Rvp',  *(ThirdParty '/release/OT52as.dll'),             'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/acmini32.dll'),                       'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/acmpev32.dll'),                       'bin/common')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(common '/build/nt/version'),                   'bin/ntsrv')                                     ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/addsvc.exe'),                         'bin/ntsrv')                                     ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/jzssvp32*.dll'),                      'bin/ntsrv')                                     ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/jzsapi32.dll'),                       'bin/ntsrv')                                     ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/patroldb.exe'),                       'bin/ntsrv')                                     ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/pdbcat.exe'),                         'bin/ntsrv')                                     ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/patrolex.exe'),                       'bin/ntsrv')                                     ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/patroljd.exe'),                       'bin/ntsrv')                                     ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/patrolsd.exe'),                       'bin/ntsrv')                                     ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/patrolan.exe'),                       'bin/ntsrv')                                     ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/pasetup.exe'),                        'bin/ntsrv')                                     ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/patroltv.exe'),                       'bin/ntsrv')                                     ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/patrolad.exe'),                       'bin/ntsrv')                                     ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/patrolcl.exe'),                       'bin/ntsrv')                                     ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/en_US.iso88591/alxexedit.rll'),       'bin/ntsrv/en_US.iso88591')                      ;* 3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/en_US.iso88591/pasetup.rll'),         'bin/ntsrv/en_US.iso88591')                      ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/en_US.iso88591/patroldb.rll'),        'bin/ntsrv/en_US.iso88591')                      ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/en_US.iso88591/patrolsd.rll'),        'bin/ntsrv/en_US.iso88591')                      ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(common '/en_US.iso88591/msgfiles/*.msg'),      'bin/ntsrv/en_US.iso88591')                      ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvpf', *(common '/en_US.iso88591/images/*.gif'),        'bin/ntsrv/en_US.iso88591/common/images')        ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvpf', *(common '/en_US.iso88591/images/*.jpg'),        'bin/ntsrv/en_US.iso88591/common/images')        ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvpf', *(common '/en_US.iso88591/images/*.css'),        'bin/ntsrv/en_US.iso88591/common/images')        ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/wpasetup.exe'),                       'bin/ntsrv')                                     ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(server '/acmwinnt/patroldb/shakeout.bat'),     'bin/ntsrv')                                     ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(server '/acmwinnt/patroldb/patroldb.ini'),     'config/ntsrv')                                  ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(common '/inifiles/patrolan.ini'),              'config/ntsrv')                                  ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(common '/inifiles/omserr.ini'),                'bin/ntsrv')                                     ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/ACLPCOD3.dll'),                       'bin/ssa')                                       ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/aclcm32.dll'),                        'bin/ssa')                                       ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/ALXIMP32.dll'),                       'bin/ssa')                                       ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/ALXSCH32.dll'),                       'bin/ssa')                                       ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/ALZPMG32.dll'),                       'bin/ssa')                                       ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/alxchg32.dll'),                       'bin/ssa')                                       ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/alxfuz32.dll'),                       'bin/ssa')                                       ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/alximpr3.dll'),                       'bin/ssa')                                       ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/cmxchin3.dll'),                       'bin/ssa')                                       ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/cmxcomp3.dll'),                       'bin/ssa')                                       ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/cmxicdl3.dll'),                       'bin/ssa')                                       ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/cmxrepo.dll'),                        'bin/ssa')                                       ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(dllDir '/patrolan.exe'),                       'bin/ssa')                                       ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(ThirdParty '/mls/*'),                          'bin/ntsrv/mls')                                 ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(common '/scripts/bmc*.bsl'),                   'bin/ssa')                                       ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(common '/cmx/scripts/cmxupld.bsl'),            'bin/ssa')                                       ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(common '/cmx/scripts/cmxsupld.bsl'),           'bin/ssa')                                       ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(common '/jzs/scripts/*.bsl'),                  'bin/ssa')                                       ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(common '/cmx/cmxicdl/cmxicdlp.pda'),           'bin/ssa')                                       ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(common '/inifiles/patrolan.ini'),              'config/ssa')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(common '/inifiles/patrolcl.ini'),              'config/ntsrv')                                  ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(common '/cmx/inifiles/cmx*.ini'),              'config/ssa')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(common '/inifiles/rdbms.ini'),                 'config/ssa')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(common '/inifiles/dbadmin.ini'),               'config/ntsrv')                                  ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(pubDir '/pdb/src/hlp/hisnt/hisnt.hlp'),        'bin/ntsrv/en_US.iso88591')                      ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(pubDir '/pdb/src/hlp/hisnt/hisnt.cnt'),        'bin/ntsrv/en_US.iso88591')                      ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(pubDir '/pdb/src/hlp/acmwinnt/acmwinnt.chm'),  'bin/ntsrv/en_us.iso88591')                      ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(pubDir '/pdb/src/hlp/wpasetup/wpasetup.chm'),  'bin/ntsrv/en_us.iso88591')                      ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(pubDir '/pdb/src/hlp/patroldb/htmlhelp.map'),  'bin/ntsrv')                                     ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(pubDrive '/pda/v3help/winhelp/*.hlp'),         'pdbkm/help')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(pubDrive '/pda/v3help/winhelp/*.cnt'),         'pdbkm/help')                                    ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(pdbkm '/images/*.*'),                          'pdbkm/images')                                  ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(pdbkm '/knowledge/*.*'),                       'pdbkm/km')                                      ;* BDG3
            cprTbl['cmn'][c = c + 1]  = cpr('sdr', 'cp', '-Rvp',  *(pdbkm '/psl/*.*'),                             'pdbkm/psl')                                     ;* BDG3

            c = 0
            cprTbl['pse'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/pse/scripts/*.*'),                    'db2/bin/sqlx')                                  ;* D
            cprTbl['pse'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(dllDir '/pse*.dll'),                           'db2/bin/sqlx')                                  ;* D
            cprTbl['pse'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/pse/inifiles/aclgmkw.ini'),           'db2/config/sqlx/sqlxdb2.ini')                   ;* D
            cprTbl['pse'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/pse/inifiles/psedef.ini'),            'db2/config/sqlx/psedef.ini')                    ;* D
            cprTbl['pse'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/pse/inifiles/db2v31.ini'),            'db2/config/sqlx/db2v31.ini')                    ;* D
            cprTbl['pse'][c = c + 1]  = cpr('cdr', 'cp', '-vpf',  *(srcDir '/pse/inifiles/db2v4.ini'),             'db2/config/sqlx/db2v4.ini')                     ;* D

*----------------------------------------------------------------------------------------------------------
*
*           patrol-db SQL Explorer windows client/ntsrv include path expressions
*
            incSEPaths        =   ARRAY('0:9')
            incSEPaths[1]     =   *(env['MSVCDir'] '/include')
            incSEPaths[2]     =   *(env['MSVCDir'] '/mfc/include')
            incSEPaths[3]     =   *(env['MSVCDir'] '/atl/include')
            incSEPaths[4]     =   *(workDir '/ThirdParty/ochart_include')
            incSEPaths[5]     =   *(workDir '/ThirdParty/ora_include')
            incSEPaths[6]     =   *(workDir '/ThirdParty/Simulus')
            incSEPaths[7]     =   *(workDir '/PQO')
            incSEPaths[8]     =   *(workDir '/COMMON')
            incSEPaths[9]     =   *(oraInclDirNm)
*---------------------------------------------------------------------------------------------------------------
*
*           patrol-db SQL Explorer windows client/ntsrv lib path expressions
*
            libSEPaths        =   ARRAY('0:5')
            libSEPaths[1]     =   *(env['MSVCDir'] '/lib')
            libSEPaths[2]     =   *(env['MSVCDir'] '/mfc/lib')
            libSEPaths[3]     =   *(workDir '/ThirdParty/Simulus')
            libSEPaths[4]     =   *(workDir '/ThirdParty/ora_lib')
            libSEPaths[5]     =   *(workDir '/ThirdParty/ochart_lib')
*----------------------------------------------------------------------------------------------------------
*
*           patrol-db SQL Explorer windows client/ntsrv extraction rules
*
            ssSEXtra          =   TABLE()
            ssSEXtra['sqlx']  =   TABLE()
            ssSEXtra['sqlx']['ActiveX']                        = 'Pr'
            ssSEXtra['sqlx']['ActiveX_Snapin_Shared']          = 'Pr'
            ssSEXtra['sqlx']['Common']                         = 'Pr'
            ssSEXtra['sqlx']['Pqo']                            = 'Pr'
            ssSEXtra['sqlx']['pqodstab']                       = 'Pr'
            ssSEXtra['sqlx']['Snapin']                         = 'Pr'
            ssSEXtra['sqlx']['/../../Doc/5.0/Help/Sqlex.hlp']  = 'Pr'
            ssSEXtra['sqlx']['/../../Doc/5.0/Help/sqlex.cnt']  = 'Pr'
            ssSEXtra['sqlx']['/../../Doc/5.0/Tour/Pqotr.hlp']  = 'Pr'
            ssSEXtra['sqlx']['/../../Doc/5.0/Tour/pqotr.CNT']  = 'Pr'
            ssSEXtra['sqlx']['/../../Doc/5.0/Help/distrib']    = 'Pr'
            ssSEXtra['sqlx']['ThirdParty']                     = 'Pr'
*---------------------------------------------------------------------------------------------------------------
*
*           patrol-db SQL Explorer windows client staging area directory structure
*
            stgClientSEDirs   =    'Staging' nl
+                                  'Staging/bin' nl
*----------------------------------------------------------------------------------------------------------
*
*           patrol-db SQL Explorer windows server staging area directory structure
*
            stgNtsrvSEDirs    =
*----------------------------------------------------------------------------------------------------------
*
*           patrol-db SQL Explorer copy macros referenced by the copy rules
*
            cpmSETbl                  =    TABLE()
            cpmSETbl[.Work]           =    *(bldWorkDir)
            cpmSETbl[.dllDir]         =    *(Work '/../' mode)
            cpmSETbl[.docDir]         =    *(Work '/../Doc' )
            cpmSETbl[.ThirdParty]     =    *(Work '/ThirdParty')
            cpmSETbl[.common]         =    *(Work '/common')
*           cpmSETbl[.pubDir]         =    *(pubDrive '/' bldPubDir)
*----------------------------------------------------------------------------------------------------------
*
*           patrol-db SQL Explorer copy rules (used to copy to the staging area)
*
            cprSETbl          =   TABLE()
            cprTbl            =   cprSETbl
            cprTbl['sqlx']    =   TABLE()

            c = 0
            cprTbl['sqlx'][c = c + 1] = cpr('cdr', 'cp', '-v',    *(dllDir 'SQLExplorer.ocx'),                     '/bin')                                          ;* S
            cprTbl['sqlx'][c = c + 1] = cpr('cdr', 'cp', '-v',    *(dllDir 'pqodstab.exe'),                        '/bin')                                          ;* S
            cprTbl['sqlx'][c = c + 1] = cpr('cdr', 'cp', '-v',    *(dllDir 'SQLExplorerSnapin.dll'),               '/bin')                                          ;* S
            cprTbl['sqlx'][c = c + 1] = cpr('cdr', 'cp', '-v',    *(dllDir 'Pqoschm.exe'),                         '/bin')                                          ;* S
            cprTbl['sqlx'][c = c + 1] = cpr('cdr', 'cp', '-v',    *(dllDir 'Pqocoll.exe'),                         '/bin')                                          ;* S
            cprTbl['sqlx'][c = c + 1] = cpr('cdr', 'cp', '-v',    *(Work '"BMC Software SQL Explorer.msc"'),       '/bin')                                          ;* S
            cprTbl['sqlx'][c = c + 1] = cpr('cdr', 'cp', '-v',    *(Work 'SQL-Explorer.reg'),                      '/bin')                                          ;* S
            cprTbl['sqlx'][c = c + 1] = cpr('cdr', 'cp', '-v',    *(ThirdParty '/ochart_lib/oc602as.dll'),         '/bin')                                          ;* S
            cprTbl['sqlx'][c = c + 1] = cpr('cdr', 'cp', '-v',    *(ThirdParty '/ochart_lib/oc1050D.lib'),         '/bin')                                          ;* S
            cprTbl['sqlx'][c = c + 1] = cpr('cdr', 'cp', '-v',    *(ThirdParty '/Simulus/Streams.lib'),            '/bin')                                          ;* S
            cprTbl['sqlx'][c = c + 1] = cpr('cdr', 'cp', '-v',    *(ThirdParty '/Simulus/Interface.lib'),          '/bin')                                          ;* S
            cprTbl['sqlx'][c = c + 1] = cpr('cdr', 'cp', '-v',    *(ThirdParty '/Simulus/borlndmm.dll'),           '/bin')                                          ;* S
            cprTbl['sqlx'][c = c + 1] = cpr('cdr', 'cp', '-v',    *(ThirdParty '/Simulus/cc3250mt.dll'),           '/bin')                                          ;* S
            cprTbl['sqlx'][c = c + 1] = cpr('cdr', 'cp', '-v',    *(ThirdParty '/Simulus/dbint.dll'),              '/bin')                                          ;* S
            cprTbl['sqlx'][c = c + 1] = cpr('cdr', 'cp', '-v',    *(ThirdParty '/Simulus/morse.dll'),              '/bin')                                          ;* S
            cprTbl['sqlx'][c = c + 1] = cpr('cdr', 'cp', '-v',    *(ThirdParty '/Simulus/oraclemodel.dll'),        '/bin')                                          ;* S
            cprTbl['sqlx'][c = c + 1] = cpr('cdr', 'cp', '-v',    *(ThirdParty '/Simulus/oraclesupport.dll'),      '/bin')                                          ;* S
            cprTbl['sqlx'][c = c + 1] = cpr('cdr', 'cp', '-v',    *(ThirdParty '/Simulus/server.dll'),             '/bin')                                          ;* S
            cprTbl['sqlx'][c = c + 1] = cpr('cdr', 'cp', '-v',    *(ThirdParty '/Simulus/simutilities.dll'),       '/bin')                                          ;* S
            cprTbl['sqlx'][c = c + 1] = cpr('cdr', 'cp', '-v',    *(ThirdParty '/Simulus/Interface.dll'),          '/bin')                                          ;* S
            cprTbl['sqlx'][c = c + 1] = cpr('cdr', 'cp', '-v',    *(ThirdParty '/Simulus/vc150.dll'),              '/bin')                                          ;* S
            cprTbl['sqlx'][c = c + 1] = cpr('cdr', 'cp', '-Rv',   *(dllDir '/En_Us.iso88591/pqosql32.rll'),        '/bin/en_us.iso88591')                           ;* S
            cprTbl['sqlx'][c = c + 1] = cpr('cdr', 'cp', '-Rv',   *(docDir '/Help/sqlex.hlp'),                     '/bin/en_us.iso88591')                           ;* S
            cprTbl['sqlx'][c = c + 1] = cpr('cdr', 'cp', '-Rv',   *(docDir '/Help/sqlex.cnt'),                     '/bin/en_us.iso88591')                           ;* S
            cprTbl['sqlx'][c = c + 1] = cpr('cdr', 'cp', '-Rv',   *(docDir '/Tour/pqotr.hlp'),                     '/bin/en_us.iso88591')                           ;* S
            cprTbl['sqlx'][c = c + 1] = cpr('cdr', 'cp', '-Rv',   *(docDir '/Tour/pqotr.cnt'),                     '/bin/en_us.iso88591')                           ;* S
            cprTbl['sqlx'][c = c + 1] = cpr('cdr', 'cp', '-Rv',   *(docDir '/Help/distrib/axdist.exe'),            '/bin/en_us.iso88591')                           ;* S
            cprTbl['sqlx'][c = c + 1] = cpr('cdr', 'cp', '-Rv',   *(docDir '/Help/distrib/csh.dll'),               '/bin/en_us.iso88591')                           ;* S
            cprTbl['sqlx'][c = c + 1] = cpr('cdr', 'cp', '-Rv',   *(docDir '/Help/distrib/hlp256.dll'),            '/bin/en_us.iso88591')                           ;* S
            cprTbl['sqlx'][c = c + 1] = cpr('cdr', 'cp', '-Rv',   *(docDir '/Help/distrib/hlp25632.dll'),          '/bin/en_us.iso88591')                           ;* S
            cprTbl['sqlx'][c = c + 1] = cpr('cdr', 'cp', '-Rv',   *(docDir '/Help/distrib/inetwh16.dll'),          '/bin/en_us.iso88591')                           ;* S
            cprTbl['sqlx'][c = c + 1] = cpr('cdr', 'cp', '-Rv',   *(docDir '/Help/distrib/inetwh32.dll'),          '/bin/en_us.iso88591')                           ;* S
            cprTbl['sqlx'][c = c + 1] = cpr('cdr', 'cp', '-Rv',   *(docDir '/Help/distrib/rhgbtn16.dll'),          '/bin/en_us.iso88591')                           ;* S
            cprTbl['sqlx'][c = c + 1] = cpr('cdr', 'cp', '-Rv',   *(docDir '/Help/distrib/rhgbtn32.dll'),          '/bin/en_us.iso88591')                           ;* S
            cprTbl['sqlx'][c = c + 1] = cpr('cdr', 'cp', '-Rv',   *(docDir '/Help/distrib/setbrows.exe'),          '/bin/en_us.iso88591')                           ;* S
            cprTbl['sqlx'][c = c + 1] = cpr('cdr', 'cp', '-Rv',   *(docDir '/Help/distrib/smthlp32.ocx'),          '/bin/en_us.iso88591')                           ;* S
            cprTbl['sqlx'][c = c + 1] = cpr('cdr', 'cp', '-Rv',   *(docDir '/Help/distrib/webpphlp.ocx'),          '/bin/en_us.iso88591')                           ;* S

*---------------------------------------------------------------------------------------------------------------
*
*           high speed data collector windows client/server extraction rules
*
            ssHSDCXtra        = TABLE()
            ssHSDCXtra['cmn'] = TABLE()

            ssHSDCXtra['cmn']['HSDC/Include/*']                         = 'F'
            ssHSDCXtra['cmn']['ObjStudio/lib/*']                        = 'F'
            ssHSDCXtra['cmn']['ObjStudio/OT603/include']                = 'Pr'
            ssHSDCXtra['cmn']['ObjStudio/common/common 6.11/include']   = 'Pr'
            ssHSDCXtra['cmn']['ObjStudio/common/MVC 6.11/include']      = 'Pr'
*---------------------------------------------------------------------------------------------------------------
*
*           high speed data collector windows client staging area directory structure
*
            stgClientHSDCDirs =
*----------------------------------------------------------------------------------------------------------
*
*           high speed data collector windows server staging area directory structure
*
            stgServerHSDCDirs =
*----------------------------------------------------------------------------------------------------------
*
*           high speed data collector copy macros referenced by the copy rules
*
            cpmHSDCTbl        =
*----------------------------------------------------------------------------------------------------------
*
*           high speed data collector copy rules (used to copy to the staging area)
*
            cprHSDCTbl        =
*---------------------------------------------------------------------------------------------------------------
*
*           high speed data collector windows client/server include path expressions
*
            incHSDCPaths      =   ARRAY('0:11')
            incHSDCPaths[1]   =   *(env['MSVCDir'] '/include')
            incHSDCPaths[2]   =   *(env['MSVCDir'] '/mfc/include')
            incHSDCPaths[3]   =   *(env['MSVCDir'] '/atl/include')
            incHSDCPaths[4]   =   *(oracleDir '/oo4o/cpp/include')
            incHSDCPaths[5]   =   *(oracleDir '/oo4o/cpp/mfc/include')
            incHSDCPaths[6]   =   *(workDir '/ObjStudio/OT603/include')
            incHSDCPaths[7]   =   *(workDir '/ObjStudio/OT603/include/config')
            incHSDCPaths[8]   =   *(workDir '/ObjStudio/common/common 6.11/include')
            incHSDCPaths[9]   =   *(workDir '/ObjStudio/common/common 6.11/include/config')
            incHSDCPaths[10]  =   *(workDir '/ObjStudio/common/MVC 6.11/include/config')
            incHSDCPaths[11]  =   *(workDir '/HSDC/Include')
*---------------------------------------------------------------------------------------------------------------
*
*           high speed data collector windows client/server lib path expressions
*
            libHSDCPaths      =   ARRAY('0:6')
            libHSDCPaths[1]   =   *(env['MSVCDir'] '/lib')
            libHSDCPaths[2]   =   *(env['MSVCDir'] '/mfc/lib')
            libHSDCPaths[3]   =   *(oracleDir '/oo4o/cpp/lib')
            libHSDCPaths[4]   =   *(oracleDir '/oo4o/cpp/mfc/lib')
            libHSDCPaths[5]   =   *(workDir '/ObjStudio/lib')
            libHSDCPaths[6]   =   *(workDir '/' libMode)
*----------------------------------------------------------------------------------------------------------

