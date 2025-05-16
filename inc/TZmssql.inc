*-------------------------------------------------------------------------------------------------------------------------
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            u                 =     0
            usr               =     ARRAY('1:32')
            doDebug           =     0
            doDebugAfter1st   =     TRUE
            doInclWhite       =     TRUE
            doInclNL          =     TRUE
            doReportFileName  =     FALSE
            doRemember        =     TRUE
            doParseTree       =     TRUE
            fndExt            =     '' . extc
            fndCmd            =     'C:/mksnt/find C:/Docume~1/lcherryh/MyDocu~1/IMCEDA -name "*.sql" -print'
*           fndCmd            =     'C:/mksnt/find C:/Progra~1/Micros~4/MSSQL/Install -name "*.sql" -print'
*           fndSpecific       =     'C:/Progra~1/Micros~4/MSSQL/Install/instmsdb.sql'
            fndSpecific       =     'C:/Docume~1/lcherryh/MyDocu~1/IMCEDA/MSSQL/test.sql'
*           fndSpecific       =     'C:/Docume~1/lcherryh/MyDocu~1/IMCEDA/MSSQL/ansiview.sql'
*           fndSpecific       =     'C:/Docume~1/lcherryh/MyDocu~1/IMCEDA/MSSQL/instpubs.sql'
*           fndSpecific       =     'C:/Docume~1/lcherryh/MyDocu~1/IMCEDA/MSSQL/MSSQL_msdn.sql'
            fndExclude        =
            keyint            =     ('?') . tx

            blanks            =     SPAN(' ' tab cr ff)
            white             =     SPAN(' ' tab nl cr ff)
            cStyleComment     =     '/*' BREAKX('*') '*/'
            sqlStyleComment   =     '--' BREAK(nl) nl
            space             =     (blanks | cStyleComment | sqlStyleComment) FENCE(*space | epsilon)
            whitespace        =     (white | cStyleComment | sqlStyleComment)  FENCE(*whitespace | epsilon)
            $' '              =     FENCE(whitespace | epsilon)
            $'  '             =     FENCE(space | epsilon)

            keywords          =
+           'ABS ABSOLUTE ACOS ACP ACTION ADDEXTENDEDPROC ADDINSTANCE AFTER ALLOW_DUP_ROW ANSI_DEFAULTS ANSI_NULLS '
+           'ANSI_NULL_DEFAULT ANSI_NULL_DFLT_OFF ANSI_NULL_DFLT_ON '
+           'ANSI_PADDING ANSI_WARNINGS ANY APPEND APP_NAME ARITHABORT '
+           'ARITHIGNORE ASCII ASIN ATAN ATN2 ATTACH AUTO AUTO_CLOSE '
+           'AUTO_CREATE_STATISTICS AUTO_SHRINK AUTO_UPDATE_STATISTICS AVG '
+           'BACKUP_DATABASE BASE64 BATCHSIZE BINARY BINARY_CHECKSUM BLOCKSIZE '
+           'BULK_LOGGED CAST CEILING CHAR CHARACTER CHARINDEX CHECKSUM CHECKSUM_AGG '
+           'CHECK_CONSTRAINTS CODEPAGE COLLATIONPROPERTY COLUMNPROPERTY '
+           'COLUMNS COLUMNS_UPDATED COL_LENGTH COL_NAME COMMITTED CONCAT '
+           'CONCAT_NULL_YIELDS_NULL CONTEXT_INFO COS COT COUNT COUNT_BIG CUBE '
+           'CURSOR_CLOSE_ON_COMMIT CURSOR_DEFAULT CURSOR_STATUS '
+           'DATABASE_DEFAULT DATABASEPROPERTY DATABASEPROPERTYEX DATAFILETYPE DATALENGTH '
+           'DATEADD DATEDIFF DATEFIRST DATEFORMAT DATENAME DATEPART DAY '
+           'DAYOFYEAR DB_ID DB_NAME DEADLOCK_PRIORITY DEGREES DELETEINSTANCE DELAY '
+           'DESCRIPTION DIFFERENCE DIFFERENTIAL DISABLE DISABLE_DEF_CNST_CHK '
+           'DROP_EXISTING DYNAMIC ELEMENTS ENABLE ENCRYPTION EXP EXPAND '
+           'EXPIREDATE EXPLICIT FAST FASTFIRSTROW FAST_FORWARD '
+           'FIELDTERMINATOR FILEGROUP FILEGROUPPROPERTY FILEGROUP_ID '
+           'FILEGROUP_NAME FILEGROWTH FILELISTONLY FILENAME FILEPROPERTY '
+           'FILE_ID FILE_NAME FIPS_FLAGGER FIRE_TRIGGERS FIRST FIRSTROW FLOOR FLUSHPROCINDB '
+           'FMTONLY FN FORCE FORCEPLAN FORMAT FORMATFILE FORMATMESSAGE '
+           'FORWARD_ONLY FULL FULLSCAN FULLTEXTCATALOGPROPERTY '
+           'FULLTEXTSERVICEPROPERTY GETANSINULL GETDATE GETUTCDATE GLOBAL GO '
+           'GROUPING HASH HAS_DBACCESS HEADERONLY HOST_ID HOST_NAME HOUR '
+           'IDENT_CURRENT IDENT_INCR IDENT_SEED IGNORE_DUP_KEY IMMEDIATE '
+           'IMPLICIT_TRANSACTIONS INCREMENTINSTANCE INDEXKEY_PROPERTY INDEXPROPERTY INDEX_COL '
+           'INIT INSTEAD INSENSITIVE INT INTEGER IO ISDATE ISNULL ISNUMERIC ISOLATION IS_MEMBER '
+           'IS_SRVROLEMEMBER KEEP KEEPFIXED KEEPIDENTITY KEEPNULLS '
+           'KEEP_REPLICATION KEYSET KILOBYTES_PER_BATCH LABELONLY LANGUAGE '
+           'LAST LASTROW LEN LEVEL LOADHISTORY LOCAL LOCK_TIMEOUT LOG LOG10 '
+           'LOOP LOW LOWER LTRIM MARK MAX MAXDOP MAXERRORS MAXSIZE '
+           'MEDIADESCRIPTION MEDIANAME MEDIAPASSWORD MERGE MILLISECOND MIN '
+           'MINUTE MODIFY MONTH MOVE MULTI_USER N NAME NCHAR NCHARACTER NEWID NEWNAME '
+           'NEXT NO NOCOUNT NOEXEC NOFORMAT NOINIT NOLOCK NORECOMPUTE '
+           'NORECOVERY NORESET NOREWIND NORMAL NOSKIP NOUNLOAD NOWAIT NO_LOG '
+           'NO_TRUNCATE NO_WAIT NUMERIC_ROUNDABORT OBJECTPROPERTY OBJECT_ID '
+           'OBJECT_NAME OEM OFFLINE ONLINE ONLY OPTIMISTIC OUT OUTPUT OVERRIDE '
+           'PAD_INDEX PAGLOCK PARSENAME PARSEONLY PARTIAL PASSWORD PATINDEX '
+           'PERMISSIONS PI POWER PRIOR PRIVILEGES PROFILE QUARTER '
+           'QUERY_GOVERNOR_COST_LIMIT QUOTED_IDENTIFIER QUOTENAME RADIANS '
+           'RAND RAW READCOMMITTED READPAST READUNCOMMITTED READ_ONLY '
+           'READ_WRITE RECOMPILE RECOVERY RECURSIVE_TRIGGERS RELATIVE '
+           'REMOTE_PROC_TRANSACTIONS REMOVE REPEATABLE REPEATABLEREAD REPLACE '
+           'REPLICATE RESAMPLE RESTART RESTRICTED_USER RETAINDAYS RETURNS '
+           'REVERSE REWIND ROBUST ROLLUP ROUND ROWCOUNT_BIG ROWLOCK ROWS '
+           'ROWS_PER_BATCH ROWTERMINATOR ROWVERSION RTRIM SAMPLE SCHEMABINDING '
+           'SCOPE_IDENTITY SCROLL SCROLL_LOCKS SECOND SECONDS SERIALIZABLE '
+           'SERVERPROPERTY SESSIONPROPERTY SETERROR SETINSTANCE SHOWPLAN_ALL '
+           'SHOWPLAN_TEXT SIGN SIMPLE SIN SINGLE_USER SIZE SKIP '
+           'SORT_IN_TEMPDB SOUNDEX SPACE SQL_VARIANT_PROPERTY SQRT SQUARE '
+           'STANDBY STATIC STATISTICS_NORECOMPUTE STATS STATS_DATE STATUSONLY '
+           'STDEV STDEVP STOPAT STOPATMARK STOPBEFOREMARK STR STUFF SUBSTRING '
+           'SUM SUSER_ID SUSER_NAME SUSER_SID SUSER_SNAME TABLOCK TABLOCKX '
+           'TAN TAPE TEXTIMAGE_ON TEXTPTR TEXTVALID TIES TIME '
+           'TORN_PAGE_DETECTION TRIGGER_NESTLEVEL TRUNCATE_ONLY TYPEPROPERTY '
+           'TYPE_WARNING UNCOMMITTED UNICODE UNLIMITED UNLOAD UOW UPDLOCK '
+           'UPPER USER_ID USER_NAME VAR VARP VERIFYONLY VIEWS VIEW_METADATA '
+           'WEEK WORK XACT_ABORT XML XMLDATA YEAR BIGINT SMALLINT TINYINT '
+           'BIT DEC DECIMAL NUMERIC MONEY SMALLMONEY FLOAT REAL DATETIME '
+           'SMALLDATETIME CHAR VARCHAR TEXT NCHAR NVARCHAR NTEXT BINARY '
+           'VARBINARY IMAGE CURSOR SQL_VARIANT TABLE TIMESTAMP '
+           'UNIQUEIDENTIFIER FN_GET_SQL FN_HELPCOLLATIONS '
+           'FN_SERVERSHAREDDRIVES FN_TRACE_GETEVENTINFO '
+           'FN_TRACE_GETFILTERINFO FN_TRACE_GETINFO FN_TRACE_GETTABLE '
+           'FN_VIRTUALFILESTATS FN_VIRTUALSERVERNODES FN_LISTEXTENDEDPROPERTY '
+           'ALL_CONSTRAINTS ALL_ERRORMSGS ALL_INDEXES ALL_LEVELS '
+           'CHECKALLOC CHECKCATALOG CHECKCONSTRAINTS CHECKDB '
+           'CHECKFILEGROUP CHECKIDENT CHECKTABLE CLEANTABLE '
+           'CONCURRENCYVIOLATION COUNT_ROWS DBREINDEX DBREPAIR '
+           'DENSITY_VECTOR DROPCLEANBUFFERS ESTIMATEONLY FAST '
+           'FREE FREEPROCCACHE HELP INDEXDEFRAG '
+           'INPUTBUFFER LOGSPACE NEWALLOC '
+           'NOINDEX NOTRUNCATE NO_INFOMSGS OPENTRAN '
+           'OUTPUTBUFFER PHYSICAL_ONLY PINTABLE PROCCACHE '
+           'REPAIR_ALLOW_DATA_LOSS REPAIR_FAST REPAIR_REBUILD RESEED '
+           'RESET ROWLOCK SHOWCONTIG SHOW_STATISTICS '
+           'SHRINKDATABASE SHRINKFILE SQLPERF STARTLOG '
+           'STAT_HEADER STOPLOG TABLERESULTS TABLOCK '
+           'TRACEOFF TRACEON TRACESTATUS TRUNCATEONLY '
+           'UNPINTABLE UPDATEUSAGE USEROPTIONS WITH '
+           'DISPLAY EMPTYFILE FAST NORESEED NOTRUNCATE '
+           'ROWGUIDCOL '

            reswords          =
+           'ADD ALL ALTER AND ANY AS ASC AUTHORIZATION BACKUP BEGIN BETWEEN '
+           'BREAK BROWSE BULK BY CASCADE CASE CHECK CHECKPOINT CLOSE '
+           'CLUSTERED COALESCE COLLATE COLUMN COMMIT COMPUTE CONSTRAINT '
+           'CONTAINS CONTAINSTABLE CONTINUE CONVERT CREATE CROSS CURRENT '
+           'CURRENT_DATE CURRENT_TIME CURRENT_TIMESTAMP CURRENT_USER CURSOR '
+           'DATABASE DBCC DEALLOCATE DECLARE DEFAULT DELETE DENY DESC DISK '
+           'DISTINCT DISTRIBUTED DOUBLE DROP DUMMY DUMP ELSE END ERRLVL '
+           'ESCAPE EXCEPT EXEC EXECUTE EXISTS EXIT FETCH FILE FILLFACTOR FOR '
+           'FOREIGN FREETEXT FREETEXTTABLE FROM FULL FUNCTION GO GOTO GRANT '
+           'GROUP HAVING HOLDLOCK IDENTITY IDENTITYCOL IDENTITY_INSERT IF IN '
+           'INDEX INNER INSERT INTERSECT INTO IS JOIN KEY KILL LEFT LIKE '
+           'LINENO LOAD NATIONAL NOCHECK NONCLUSTERED NOT NULL NULLIF OF OFF '
+           'OFFSETS ON OPEN OPENDATASOURCE OPENQUERY OPENROWSET OPENXML '
+           'OPTION OR ORDER OUTER OVER PERCENT PLAN PRECISION PRIMARY PRINT '
+           'PROC PROCEDURE PUBLIC RAISERROR READ READTEXT RECONFIGURE '
+           'REFERENCES REPLICATION RESTORE RESTRICT RETURN REVOKE RIGHT '
+           'ROLLBACK ROWCOUNT RULE SAVE SCHEMA SELECT SESSION_USER '
+           'SET SETUSER SHUTDOWN SOME STATISTICS SYSTEM_USER TABLE TEXTSIZE '
+           'THEN TO TOP TRAN TRANSACTION TRIGGER TRUNCATE TSEQUAL UNION '
+           'UNIQUE UPDATE UPDATETEXT USE USER VALUES VARYING VIEW WAITFOR '
+           'WHEN WHERE WHILE WITH WRITETEXT '
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            special           =     ') ( } { @ @@ : ;'
            operators         =     '! !< != !> % & * *= + , - . / < <= <> = =* > >= ^ | ~ ::'
            $'_IDENT_'        =     ANY('$#_' &UCASE &LCASE) FENCE(SPAN('$#_' &UCASE &LCASE '0123456789') | epsilon)
            $'_AT_IDENT_'     =     '@' SPAN('$#_' &UCASE &LCASE '0123456789')
            ident             =     $'_IDENT_' $ tx $ *notmatch(reswords, (POS(0) | ' ') upr(tx) (' ' | RPOS(0)))
            resword           =     $'_IDENT_' $ tx $ *match(reswords, (POS(0) | ' ') upr(tx) (' ' | RPOS(0)))
            keyword           =     $'_IDENT_' $ tx $ *match(keywords, (POS(0) | ' ') upr(tx) (' ' | RPOS(0)))

            Populate(.TW, $'_IDENT_', keywords, reswords, special, operators)

            $'_BINARY_'       =     ('0x' | '0X') SPAN('0123456789ABCDEFabcdef')
            $'_REAL_'         =     SPAN('0123456789')
+                                   FENCE('.' (SPAN('0123456789') | epsilon) | epsilon)
+                                   FENCE(ANY('Ee') !(ANY('+-')) SPAN('0123456789') | epsilon)
            $'_REAL_1_'       =     FENCE(SPAN('0123456789') | epsilon)
+                                   '.'
+                                   SPAN('0123456789')
+                                   FENCE(ANY('Ee') !(ANY('+-')) SPAN('0123456789') | epsilon)
            $'_INTEGER_'      =     SPAN('0123456789')
            $'_DQ_STRING_'    =     '"' !%NOTANY('"') '"'
            $'_SQ_STRING_'    =     ('N' | epsilon) "'" !%("'" "'" | NOTANY("'")) "'"
            $'_DELIMITED_'    =     '[' BREAK(']') ']'
            $'_MONEY_'        =     '$' SPAN('0123456789') FENCE('.' SPAN('0123456789') | epsilon)

            $'@@CONNECTIONS'     =     $' ' TW(1, '@@' $'_IDENT_', '@@CONNECTIONS')
            $'@@CPU_BUSY'        =     $' ' TW(1, '@@' $'_IDENT_', '@@CPU_BUSY')
            $'@@CURSOR_ROWS'     =     $' ' TW(1, '@@' $'_IDENT_', '@@CURSOR_ROWS')
            $'@@DATEFIRST'       =     $' ' TW(1, '@@' $'_IDENT_', '@@DATEFIRST')
            $'@@DBTS'            =     $' ' TW(1, '@@' $'_IDENT_', '@@DBTS')
            $'@@ERROR'           =     $' ' TW(1, '@@' $'_IDENT_', '@@ERROR')
            $'@@FETCH_STATUS'    =     $' ' TW(1, '@@' $'_IDENT_', '@@FETCH_STATUS')
            $'@@IDENTITY'        =     $' ' TW(1, '@@' $'_IDENT_', '@@IDENTITY')
            $'@@IDLE'            =     $' ' TW(1, '@@' $'_IDENT_', '@@IDLE')
            $'@@IO_BUSY'         =     $' ' TW(1, '@@' $'_IDENT_', '@@IO_BUSY')
            $'@@LANGID'          =     $' ' TW(1, '@@' $'_IDENT_', '@@LANGID')
            $'@@LANGUAGE'        =     $' ' TW(1, '@@' $'_IDENT_', '@@LANGUAGE')
            $'@@LOCK_TIMEOUT'    =     $' ' TW(1, '@@' $'_IDENT_', '@@LOCK_TIMEOUT')
            $'@@MAX_CONNECTIONS' =     $' ' TW(1, '@@' $'_IDENT_', '@@MAX_CONNECTIONS')
            $'@@MAX_PRECISION'   =     $' ' TW(1, '@@' $'_IDENT_', '@@MAX_PRECISION')
            $'@@NESTLEVEL'       =     $' ' TW(1, '@@' $'_IDENT_', '@@NESTLEVEL')
            $'@@OPTIONS'         =     $' ' TW(1, '@@' $'_IDENT_', '@@OPTIONS')
            $'@@PACK_RECEIVED'   =     $' ' TW(1, '@@' $'_IDENT_', '@@PACK_RECEIVED')
            $'@@PACK_SENT'       =     $' ' TW(1, '@@' $'_IDENT_', '@@PACK_SENT')
            $'@@PACKET_ERRORS'   =     $' ' TW(1, '@@' $'_IDENT_', '@@PACKET_ERRORS')
            $'@@PROCID'          =     $' ' TW(1, '@@' $'_IDENT_', '@@PROCID')
            $'@@REMSERVER'       =     $' ' TW(1, '@@' $'_IDENT_', '@@REMSERVER')
            $'@@ROWCOUNT'        =     $' ' TW(1, '@@' $'_IDENT_', '@@ROWCOUNT')
            $'@@SERVERNAME'      =     $' ' TW(1, '@@' $'_IDENT_', '@@SERVERNAME')
            $'@@SERVICENAME'     =     $' ' TW(1, '@@' $'_IDENT_', '@@SERVICENAME')
            $'@@SPID'            =     $' ' TW(1, '@@' $'_IDENT_', '@@SPID')
            $'@@TEXTSIZE'        =     $' ' TW(1, '@@' $'_IDENT_', '@@TEXTSIZE')
            $'@@TIMETICKS'       =     $' ' TW(1, '@@' $'_IDENT_', '@@TIMETICKS')
            $'@@TOTAL_ERRORS'    =     $' ' TW(1, '@@' $'_IDENT_', '@@TOTAL_ERRORS')
            $'@@TOTAL_READ'      =     $' ' TW(1, '@@' $'_IDENT_', '@@TOTAL_READ')
            $'@@TOTAL_WRITE'     =     $' ' TW(1, '@@' $'_IDENT_', '@@TOTAL_WRITE')
            $'@@TRANCOUNT'       =     $' ' TW(1, '@@' $'_IDENT_', '@@TRANCOUNT')
            $'@@VERSION'         =     $' ' TW(1, '@@' $'_IDENT_', '@@VERSION')

            compiland         =     POS(0) *SQL_batches $' ' RPOS(0)

            EQ(doParseTree, TRUE)                                                            :F(mssql10)

            at_at_identifier  =     $' ' ('@@' $'_IDENT_')                  ~ 'identifier'
            at_identifier     =     $' ' $'_AT_IDENT_'                      ~ 'identifier'
            identifier        =     $' '
+                                   (  ident
+                                   |  $'_DQ_STRING_'
+                                   |  $'_DELIMITED_'
+                                   )                                       ~ 'identifier'
            real_literal      =     $' ' ($'_REAL_' | $'_REAL_1_')          ~ 'real'
            integer_literal   =     $' ' $'_INTEGER_'                       ~ 'integer'
            binary_literal    =     $' ' $'_BINARY_'                        ~ 'binary'
            string_literal    =     $' ' ($'_SQ_STRING_' | $'_DQ_STRING_')  ~ 'string'
            money_literal     =     $' ' $'_MONEY_'                         ~ 'money'
            true              =     $' ' TW(1, $'_IDENT_', 'TRUE')          ~ 'identifier'
            false             =     $' ' TW(1, $'_IDENT_', 'FALSE')         ~ 'identifier'   :(mssql20)
mssql10
            at_at_identifier  =     $' ' ('@@' $'_IDENT_')
            at_identifier     =     $' ' $'_AT_IDENT_'
            identifier        =     $' '
+                                   (  ident
+                                   |  $'_DQ_STRING_'
+                                   |  $'_DELIMITED_'
+                                   )
            real_literal      =     $' ' ($'_REAL_' | $'_REAL_1_')
            integer_literal   =     $' ' $'_INTEGER_'
            binary_literal    =     $' ' $'_BINARY_'
            string_literal    =     $' ' ($'_SQ_STRING_' | $'_DQ_STRING_')
            money_literal     =     $' ' $'_MONEY_'
            true              =     $' ' TW(1, $'_IDENT_', 'TRUE')
            false             =     $' ' TW(1, $'_IDENT_', 'FALSE')
mssql20
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
-INCLUDE    'transl8-MSSQL_msdn.inc'
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserRpt()')                                                              :(UserRptEnd)
UserRpt     mssql             =     Pop()                                                    :F(RETURN)
            DIFFER(mssql)                                                                    :F(RETURN)
*           XDump(mssql, 'mssql')
            TDump(mssql)                                                                     :(RETURN)
UserRptEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserFinal()')                                                            :(UserFinalEnd)
UserFinal                                                                                    :(RETURN)
UserFinalEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserTokens()')                                                           :(UserTokensEnd)
UserTokens  tok[t = t + 1] = token(,, .compiland)
            tok[t = t + 1] = token(,  *(spcpfx "*$'_REAL_'"), *$'_REAL_')
            tok[t = t + 1] = token(,  *(spcpfx "*$'_REAL_1_'"), *$'_REAL_1_')
            tok[t = t + 1] = token(,  *(spcpfx "*$'_INTEGER_'"), *$'_INTEGER_')
            tok[t = t + 1] = token(,  *(spcpfx "*$'_DQ_STRING_'"), *$'_DQ_STRING_')
            tok[t = t + 1] = token(,  *(spcpfx "*$'_SQ_STRING_'"), *$'_SQ_STRING_')
            tok[t = t + 1] = token(,  *(tx), *resword . tx)
            tok[t = t + 1] = token(,  *(tx), *keyword . tx)
            tok[t = t + 1] = token(,  *(spcpfx "*$'_IDENT_'"), *$'_IDENT_')
            tok[t = t + 1] = token(,  *("$'" tx "'"), *operator . tx)
            tok[t = t + 1] = token(,  *("$'" tx "'"), ',' . tx)
            tok[t = t + 1] = token(,  *("$'" tx "'"), '(' . tx)
            tok[t = t + 1] = token(,  *("$'" tx "'"), ')' . tx)
            tok[t = t + 1] = token(,  *("$'" tx "'"), '@' . tx)
            tok[t = t + 1] = token(,  *("$'" tx "'"), '@@' . tx)
            tok[t = t + 1] = token(,  *("$'" tx "'"), ';' . tx)

            dbg[.SQL_batches]                             = TRUE
*           dbg[.$'_INTEGER_']                            = TRUE
*           dbg[.$'_IDENT_']                              = TRUE
*           dbg[.$'_REAL_']                               = TRUE
*           dbg[.$'_REAL_1_']                             = TRUE
*           dbg[.$'_DQ_STRING_']                          = TRUE
*           dbg[.$'_SQ_STRING_']                          = TRUE

            dbg[.ALTER_DATABASE_statement]                = TRUE
            dbg[.ALTER_FUNCTION_statement]                = TRUE
            dbg[.ALTER_PROCEDURE_statement]               = TRUE
            dbg[.ALTER_TABLE_statement]                   = TRUE
            dbg[.ALTER_TRIGGER_statement]                 = TRUE
            dbg[.ALTER_VIEW_statement]                    = TRUE
            dbg[.BACKUP_statement]                        = TRUE
            dbg[.BEGIN_DISTRIBUTED_TRANSACTION_statement] = TRUE
            dbg[.BEGIN_END_block]                         = TRUE
            dbg[.BEGIN_TRANSACTION_statement]             = TRUE
            dbg[.BULK_INSERT_statement]                   = TRUE
            dbg[.CASE_statement]                          = TRUE
            dbg[.CHECKPOINT_statement]                    = TRUE
            dbg[.CLOSE_statement]                         = TRUE
            dbg[.COLLATE_clause]                          = TRUE
            dbg[.COMMIT_TRANSACTION_statement]            = TRUE
            dbg[.COMMIT_statement]                        = TRUE
            dbg[.COMPUTE_Clause]                          = TRUE
            dbg[.CONTAINSTABLE_clause]                    = TRUE
            dbg[.CONTAINS_clause]                         = TRUE
            dbg[.CREATE_DATABASE_statement]               = TRUE
            dbg[.CREATE_DEFAULT_statement]                = TRUE
            dbg[.CREATE_FUNCTION_statement]               = TRUE
            dbg[.CREATE_INDEX_statement]                  = TRUE
            dbg[.CREATE_PROCEDURE_statement]              = TRUE
            dbg[.CREATE_RULE_statement]                   = TRUE
            dbg[.CREATE_SCHEMA_statement]                 = TRUE
            dbg[.CREATE_STATISTICS_statement]             = TRUE
            dbg[.CREATE_TABLE_statement]                  = TRUE
            dbg[.CREATE_TRIGGER_statement]                = TRUE
            dbg[.CREATE_VIEW_statement]                   = TRUE
            dbg[.DEALLOCATE_statement]                    = TRUE
            dbg[.DECLARE_CURSOR_statement]                = TRUE
            dbg[.DECLARE_variable_statement]              = TRUE
            dbg[.DELETE_statement]                        = TRUE
            dbg[.DENY_statement]                          = TRUE
            dbg[.DROP_DATABASE_statement]                 = TRUE
            dbg[.DROP_DEFAULT_statement]                  = TRUE
            dbg[.DROP_FUNCTION_statement]                 = TRUE
            dbg[.DROP_INDEX_statement]                    = TRUE
            dbg[.DROP_PROCEDURE_statement]                = TRUE
            dbg[.DROP_RULE_statement]                     = TRUE
            dbg[.DROP_STATISTICS_statement]               = TRUE
            dbg[.DROP_TABLE_statement]                    = TRUE
            dbg[.DROP_TRIGGER_statement]                  = TRUE
            dbg[.DROP_VIEW_statement]                     = TRUE
            dbg[.DUMP_statement]                          = TRUE
            dbg[.EXECUTE_statement]                       = TRUE
            dbg[.FETCH_statement]                         = TRUE
            dbg[.FOR_Clause]                              = TRUE
            dbg[.GRANT_statement]                         = TRUE
            dbg[.GROUPING_clause]                         = TRUE
            dbg[.GROUP_BY_Clause]                         = TRUE
            dbg[.HAVING_Clause]                           = TRUE
            dbg[.IDENTITY_clause]                         = TRUE
            dbg[.IF_ELSE_statement]                       = TRUE
            dbg[.INSERT_statement]                        = TRUE
            dbg[.INTO_Clause]                             = TRUE
            dbg[.IS_clause]                               = TRUE
            dbg[.KILL_statement]                          = TRUE
            dbg[.LIKE_clause]                             = TRUE
            dbg[.LOAD_statement]                          = TRUE
            dbg[.NOT_IN_clause]                           = TRUE
            dbg[.NOT_clause]                              = TRUE
            dbg[.OPENXML_clause]                          = TRUE
            dbg[.OPEN_statement]                          = TRUE
            dbg[.OPTION_Clause]                           = TRUE
            dbg[.ORDER_BY_Clause]                         = TRUE
            dbg[.PRINT_statement]                         = TRUE
            dbg[.RAISERROR_statement]                     = TRUE
            dbg[.READTEXT_statement]                      = TRUE
            dbg[.RECONFIGURE_statement]                   = TRUE
            dbg[.RESTORE_FILELISTONLY_statement]          = TRUE
            dbg[.RESTORE_HEADERONLY_statement]            = TRUE
            dbg[.RESTORE_LABELONLY_statement]             = TRUE
            dbg[.RESTORE_VERIFYONLY_statement]            = TRUE
            dbg[.RESTORE_statement]                       = TRUE
            dbg[.REVOKE_statement]                        = TRUE
            dbg[.ROLLBACK_TRANSACTION_statement]          = TRUE
            dbg[.ROLLBACK_statement]                      = TRUE
            dbg[.SAVE_TRANSACTION_statement]              = TRUE
            dbg[.SELECT_Clause]                           = TRUE
            dbg[.SELECT_statement]                        = TRUE
            dbg[.SELECT_variable_statement]               = TRUE
            dbg[.SETUSER_statement]                       = TRUE
            dbg[.SET_statement]                           = TRUE
            dbg[.SET_variable_statement]                  = TRUE
            dbg[.SHUTDOWN_statement]                      = TRUE
            dbg[.SQL_batch]                               = TRUE
            dbg[.SQL_batches]                             = TRUE
            dbg[.TRUNCATE_TABLE_statement]                = TRUE
            dbg[.Transact_SQL_statement]                  = TRUE
            dbg[.Transact_block]                          = TRUE
            dbg[.UNION_Operator]                          = TRUE
            dbg[.UPDATETEXT_statement]                    = TRUE
            dbg[.UPDATE_STATISTICS_statement]             = TRUE
            dbg[.UPDATE_statement]                        = TRUE
            dbg[.USE_statement]                           = TRUE
            dbg[.WHERE_Clause]                            = TRUE
            dbg[.WHILE_statement]                         = TRUE
            dbg[.WRITETEXT_statement]                     = TRUE
            dbg[.alias]                                   = TRUE
            dbg[.alter_database_filespec]                 = TRUE
            dbg[.alter_table_column_definition]           = TRUE
            dbg[.alter_table_constraint]                  = TRUE
            dbg[.at_at_identifier]                        = TRUE
            dbg[.at_identifier]                           = TRUE
            dbg[.auto_option]                             = TRUE
            dbg[.backup_device]                           = TRUE
            dbg[.backup_set_name]                         = TRUE
            dbg[.backup_set_name_var]                     = TRUE
            dbg[.bitwise_operator]                        = TRUE
            dbg[.blocksize]                               = TRUE
            dbg[.blocksize_variable]                      = TRUE
            dbg[.boolean_expression]                      = TRUE
            dbg[.character_expression]                    = TRUE
            dbg[.collation_name]                          = TRUE
            dbg[.column]                                  = TRUE
            dbg[.column_alias]                            = TRUE
            dbg[.column_bitmask]                          = TRUE
            dbg[.column_constraint]                       = TRUE
            dbg[.column_name]                             = TRUE
            dbg[.comparison_operator]                     = TRUE
            dbg[.computed_column_expression]              = TRUE
            dbg[.constant]                                = TRUE
            dbg[.constant_expression]                     = TRUE
            dbg[.constraint_name]                         = TRUE
            dbg[.control_of_flow_statement]               = TRUE
            dbg[.create_table_column_definition]          = TRUE
            dbg[.create_table_constraint]                 = TRUE
            dbg[.cursor_name]                             = TRUE
            dbg[.cursor_option]                           = TRUE
            dbg[.cursor_variable]                         = TRUE
            dbg[.cursor_variable_name]                    = TRUE
            dbg[.data_type]                               = TRUE
            dbg[.database]                                = TRUE
            dbg[.database_id]                             = TRUE
            dbg[.database_name]                           = TRUE
            dbg[.database_name_var]                       = TRUE
            dbg[.date]                                    = TRUE
            dbg[.date_var]                                = TRUE
            dbg[.datepart]                                = TRUE
            dbg[.datetime]                                = TRUE
            dbg[.days]                                    = TRUE
            dbg[.days_var]                                = TRUE
            dbg[.declared_column_constraint]              = TRUE
            dbg[.declared_column_definition]              = TRUE
            dbg[.declared_table_constraint]               = TRUE
            dbg[.default]                                 = TRUE
            dbg[.delete_query_hint]                       = TRUE
            dbg[.derived_table]                           = TRUE
            dbg[.else_result_expression]                  = TRUE
            dbg[.escape_character]                        = TRUE
            dbg[.expression]                              = TRUE
            dbg[.expression1]                             = TRUE
            dbg[.expression2]                             = TRUE
            dbg[.expression3]                             = TRUE
            dbg[.expression4]                             = TRUE
            dbg[.expression5]                             = TRUE
            dbg[.expression6]                             = TRUE
            dbg[.extended_procedure]                      = TRUE
            dbg[.file_id]                                 = TRUE
            dbg[.file_name]                               = TRUE
            dbg[.file_number]                             = TRUE
            dbg[.file_number_variable]                    = TRUE
            dbg[.file_or_filegroup]                       = TRUE
            dbg[.filegroup]                               = TRUE
            dbg[.filegroup_name]                          = TRUE
            dbg[.filespec]                                = TRUE
            dbg[.fillfactor]                              = TRUE
            dbg[.float_expression]                        = TRUE
            dbg[.freetext_string]                         = TRUE
            dbg[.function_body]                           = TRUE
            dbg[.function_name]                           = TRUE
            dbg[.function_option]                         = TRUE
            dbg[.global_variable]                         = TRUE
            dbg[.group]                                   = TRUE
            dbg[.group_by_expression]                     = TRUE
            dbg[.growth_increment]                        = TRUE
            dbg[.id]                                      = TRUE
            dbg[.identifier]                              = TRUE
            dbg[.increment]                               = TRUE
            dbg[.index]                                   = TRUE
            dbg[.index_id]                                = TRUE
            dbg[.index_option]                            = TRUE
            dbg[.integer_expression]                      = TRUE
            dbg[.joined_table]                            = TRUE
            dbg[.length]                                  = TRUE
            dbg[.local_variable]                          = TRUE
            dbg[.logical_expression]                      = TRUE
            dbg[.logical_file_name]                       = TRUE
            dbg[.login]                                   = TRUE
            dbg[.mark_name]                               = TRUE
            dbg[.max_size]                                = TRUE
            dbg[.media_name]                              = TRUE
            dbg[.media_name_variable]                     = TRUE
            dbg[.mediapassword]                           = TRUE
            dbg[.mediapassword_variable]                  = TRUE
            dbg[.n]                                       = TRUE
            dbg[.new_table]                               = TRUE
            dbg[.number]                                  = TRUE
            dbg[.number_rows]                             = TRUE
            dbg[.number_var]                              = TRUE
            dbg[.numeric_expression]                      = TRUE
            dbg[.nvar]                                    = TRUE
            dbg[.object]                                  = TRUE
            dbg[.object_id]                               = TRUE
            dbg[.old_outer_join]                          = TRUE
            dbg[.operating_system_file_name]              = TRUE
            dbg[.option]                                  = TRUE
            dbg[.optionspec]                              = TRUE
            dbg[.order_by_expression]                     = TRUE
            dbg[.os_file_name]                            = TRUE
            dbg[.owner]                                   = TRUE
            dbg[.owner_name]                              = TRUE
            dbg[.p]                                       = TRUE
            dbg[.parameter]                               = TRUE
            dbg[.parameter_name]                          = TRUE
            dbg[.password]                                = TRUE
            dbg[.password_variable]                       = TRUE
            dbg[.percentage]                              = TRUE
            dbg[.permission]                              = TRUE
            dbg[.predicate]                               = TRUE
            dbg[.procedure_name]                          = TRUE
            dbg[.property]                                = TRUE
            dbg[.provider_name]                           = TRUE
            dbg[.query]                                   = TRUE
            dbg[.query_expression]                        = TRUE
            dbg[.query_specification]                     = TRUE
            dbg[.recovery_option]                         = TRUE
            dbg[.ref_column]                              = TRUE
            dbg[.ref_table]                               = TRUE
            dbg[.result_expression]                       = TRUE
            dbg[.return_variable]                         = TRUE
            dbg[.role]                                    = TRUE
            dbg[.rowset_function_limited]                 = TRUE
            dbg[.rule]                                    = TRUE
            dbg[.s]                                       = TRUE
            dbg[.savepoint_name]                          = TRUE
            dbg[.savepoint_variable]                      = TRUE
            dbg[.scalar_expression]                       = TRUE
            dbg[.scalar_function]                         = TRUE
            dbg[.scalar_parameter_data_type]              = TRUE
            dbg[.scalar_return_data_type]                 = TRUE
            dbg[.schema_element]                          = TRUE
            dbg[.search_condition]                        = TRUE
            dbg[.search_condition1]                       = TRUE
            dbg[.search_condition2]                       = TRUE
            dbg[.search_condition3]                       = TRUE
            dbg[.search_condition4]                       = TRUE
            dbg[.search_condition5]                       = TRUE
            dbg[.search_condition6]                       = TRUE
            dbg[.search_condition7]                       = TRUE
            dbg[.search_condition8]                       = TRUE
            dbg[.search_condition9]                       = TRUE
            dbg[.search_conditions]                       = TRUE
            dbg[.security_account]                        = TRUE
            dbg[.seed]                                    = TRUE
            dbg[.select_list]                             = TRUE
            dbg[.select_query_hint]                       = TRUE
            dbg[.select_statement]                        = TRUE
            dbg[.select_stmt]                             = TRUE
            dbg[.size]                                    = TRUE
            dbg[.sql_option]                              = TRUE
            dbg[.sql_statement]                           = TRUE
            dbg[.start]                                   = TRUE
            dbg[.state_option]                            = TRUE
            dbg[.statement]                               = TRUE
            dbg[.statistics_name]                         = TRUE
            dbg[.stored_procedure]                        = TRUE
            dbg[.string_expression]                       = TRUE
            dbg[.string_factor]                           = TRUE
            dbg[.string_sum]                              = TRUE
            dbg[.subquery]                                = TRUE
            dbg[.table]                                   = TRUE
            dbg[.table_ID]                                = TRUE
            dbg[.table_alias]                             = TRUE
            dbg[.table_hint]                              = TRUE
            dbg[.table_hint_limited]                      = TRUE
            dbg[.table_id]                                = TRUE
            dbg[.table_name]                              = TRUE
            dbg[.table_or_view]                           = TRUE
            dbg[.table_source]                            = TRUE
            dbg[.termination]                             = TRUE
            dbg[.text]                                    = TRUE
            dbg[.text_ptr]                                = TRUE
            dbg[.text_variable]                           = TRUE
            dbg[.time]                                    = TRUE
            dbg[.top_n_by_rank]                           = TRUE
            dbg[.trace_id]                                = TRUE
            dbg[.traceid]                                 = TRUE
            dbg[.tran_name_variable]                      = TRUE
            dbg[.transaction_name]                        = TRUE
            dbg[.trigger_name]                            = TRUE
            dbg[.undo_file_name]                          = TRUE
            dbg[.undo_file_name_var]                      = TRUE
            dbg[.update_query_hint]                       = TRUE
            dbg[.updated_bitmask]                         = TRUE
            dbg[.user_defined_function]                   = TRUE
            dbg[.value]                                   = TRUE
            dbg[.variable]                                = TRUE
            dbg[.view]                                    = TRUE
            dbg[.view_attribute]                          = TRUE
            dbg[.view_name]                               = TRUE

                                                                                             :(RETURN)
UserTokensEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
