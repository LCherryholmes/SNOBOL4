*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            doDebug           =     0
            doParseTree       =     FALSE

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

            EQ(doParseTree, TRUE)                                                            :F(tsql10)

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
            false             =     $' ' TW(1, $'_IDENT_', 'FALSE')         ~ 'identifier'   :(tsql20)
tsql10
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
tsql20
