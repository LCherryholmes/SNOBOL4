*-------------------------------------------------------------------------------------------------------
* SQL Native Client. Interface to SQLNCLI10.dll
*-------------------------------------------------------------------------------------------------------
* Load functions using their external names.
*
            LOAD('EXT_COINITIALIZE_()',                   xInstall 'snolibc.dll')  :F(error)
            LOAD('EXT_SQL_CONNECT_(STRING,STRING,STRING,STRING,STRING,STRING)', xInstall 'snolibc.dll')  :F(error)
            LOAD('EXT_SQL_ALLOCSTMT_()',                  xInstall 'snolibc.dll')  :F(error)
            LOAD('EXT_SQL_A_EXECDIRECT_(INTEGER,STRING)', xInstall 'snolibc.dll')  :F(error)
            LOAD('EXT_SQL_W_EXECDIRECT_(INTEGER,STRING)', xInstall 'snolibc.dll')  :F(error)
            LOAD('EXT_SQL_FETCH_(INTEGER)',               xInstall 'snolibc.dll')  :F(error)
            LOAD('EXT_SQL_GETDATA_(INTEGER,INTEGER)',     xInstall 'snolibc.dll')  :F(error)
            LOAD('EXT_SQL_FREESTMT_(INTEGER)',            xInstall 'snolibc.dll')  :F(error)
            LOAD('EXT_SQL_DISCONNECT_()',                 xInstall 'snolibc.dll')  :F(error)
            LOAD('EXT_SQL_GETLASTERROR_()',               xInstall 'snolibc.dll')  :F(error)
            LOAD('EXT_SQL_SET_AUTOCOMMIT_OFF()',          xInstall 'snolibc.dll')  :F(error)
            LOAD('EXT_SQL_ENDTRAN_COMMIT()',              xInstall 'snolibc.dll')  :F(error)
            LOAD('EXT_SQL_ENDTRAN_ROLLBACK()',            xInstall 'snolibc.dll')  :F(error)

            LOAD('EXT_BCP_INIT(STRING)',                  xInstall 'snolibc.dll')  :F(error)
            LOAD('EXT_BCP_COLFMT(INTEGER,INTEGER,INTEGER,INTEGER,STRING)', xInstall 'snolibc.dll')  :F(error)
            LOAD('EXT_BCP_COLLEN(INTEGER,INTEGER)',       xInstall 'snolibc.dll')  :F(error)
            LOAD('EXT_BCP_COLVAL(STRING,INTEGER)',        xInstall 'snolibc.dll')  :F(error)
            LOAD('EXT_BCP_SENDROW()',                     xInstall 'snolibc.dll')  :F(error)
            LOAD('EXT_BCP_MORETEXT(EXTERNAL)',            xInstall 'snolibc.dll')  :F(error)
            LOAD('EXT_BCP_BATCH()',                       xInstall 'snolibc.dll')  :F(error)
            LOAD('EXT_BCP_DONE()',                        xInstall 'snolibc.dll')  :F(error)
*-------------------------------------------------------------------------------------------------------
* Make functions available with nicer names.
*
            OPSYN("CoInitialize",         "EXT_COINITIALIZE_")              :F(error)
            OPSYN("SQL_Connect",          "EXT_SQL_CONNECT_")               :F(error)
            OPSYN("SQL_AllocStmt",        "EXT_SQL_ALLOCSTMT_")             :F(error)
            OPSYN("SQL_A_ExecDirect",     "EXT_SQL_A_EXECDIRECT_")          :F(error)
            OPSYN("SQL_W_ExecDirect",     "EXT_SQL_W_EXECDIRECT_")          :F(error)
            OPSYN("SQL_Fetch",            "EXT_SQL_FETCH_")                 :F(error)
            OPSYN("SQL_GetData",          "EXT_SQL_GETDATA_")               :F(error)
            OPSYN("SQL_FreeStmt",         "EXT_SQL_FREESTMT_")              :F(error)
            OPSYN("SQL_Disconnect",       "EXT_SQL_DISCONNECT_")            :F(error)
            OPSYN("SQL_GetLastError",     "EXT_SQL_GETLASTERROR_")          :F(error)
            OPSYN("SQL_SetAutoCommitOff", "EXT_SQL_SET_AUTOCOMMIT_OFF")     :F(error)
            OPSYN("SQL_EndTranCommit",    "EXT_SQL_ENDTRAN_COMMIT")         :F(error)
            OPSYN("SQL_EndTranRollback",  "EXT_SQL_ENDTRAN_ROLLBACK")       :F(error)

            OPSYN("bcp_init",             "EXT_BCP_INIT")                   :F(error)
            OPSYN("bcp_colfmt",           "EXT_BCP_COLFMT")                 :F(error)
            OPSYN("bcp_collen",           "EXT_BCP_COLLEN")                 :F(error)
            OPSYN("bcp_colval",           "EXT_BCP_COLVAL")                 :F(error)
            OPSYN("bcp_sendrow",          "EXT_BCP_SENDROW")                :F(error)
            OPSYN("bcp_moretext",         "EXT_BCP_MORETEXT")               :F(error)
            OPSYN("bcp_batch",            "EXT_BCP_BATCH")                  :F(error)
            OPSYN("bcp_done",             "EXT_BCP_DONE")                   :F(error)
*-------------------------------------------------------------------------------------------------------
            SQL_SUCCESS             =   0
            SQL_SUCCESS_WITH_INFO   =   1
            SQL_NO_DATA             =   100
            SQL_ERROR               =   -1
            SQL_INVALID_HANDLE      =   -2
            SQL_STILL_EXECUTING     =   2
            SQL_NEED_DATA           =   99
*-------------------------------------------------------------------------------------------------------
