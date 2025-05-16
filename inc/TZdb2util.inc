*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserDefs()')                                                             :(UserDefsEnd)
UserDefs    u                 =     0
            usr               =     ARRAY('1:32')
            doDebug           =     0
            doDebugAfter1st   =     FALSE
            doInclWhite       =     TRUE
            doInclNL          =     TRUE
            doReportFileName  =     FALSE
            doRemember        =     TRUE
            fndExt            =     '' . extc
            fndCmd            =     'd:/mksnt/find d:/db2util -name "@*" -print'
*           fndSpecific       =     '@SGI600' ANY('123456')
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

            DEFINE('Parenthesis(pattern)')
            OPSYN('=', 'Parenthesis', 1)                                                     :s(ParenthesisEnd)f(error)
Parenthesis Parenthesis       =     pattern | $'(' pattern $')'                              :(RETURN)
ParenthesisEnd

*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            integer           =     SPAN('0123456789')
            hex               =     ('X' | 'x') "'" SPAN('0123456789ABCDEFabcdef') "'"
            ghex              =     ('G' | 'g') "'" BREAK("'") "'"
            nhex              =     ('N' | 'n') "'" BREAK("'") "'"
            string            =     "'" BREAK("'") "'"
            keywords          =
+           'ABEND ABORT ACCESS ACCESSPATH ACCTG ACTION ACTIVE ADVISORY AFTER AGE AL ALL ALLDUMPS ALT ALTER AND '
+           'ARC ARCHIVE ARCHLOG AREST ASCII AUDIT AUTHID AUTOREC AUXERROR AUXONLY BETWEEN BLOB BMCSTATS BPOOL BSDS '
+           'BUFFERPOOL BUFSIZE CAN CANCEL CASTOUT CASTOWNR CATALOG CATMAINT CCSID CHANGE CHANGELIMIT CHAR '
+           'CHECK CHECK2 CICS CLAIMERS CLASS CLASST CLOB CO COLUMN COMMENT COMMIT CONCURRENT CONNLIST '
+           'CONSTRAINTS CONTINUE CONTINUEIF COPY COPY2 COPYDDN CORRELATION COUNT CPU CURRENT DATA DATABASE '
+           'DATASPACE DATE DAY DAYS DB DB2 DBCLOB DBD DBDB DBET DBID DBM1 DBNAME DDF DEADLINE DEC DECIMAL '
+           'DEFAULT DEFAULTIF DEFER DELAY DELETE DEST DETAIL DEVTYPE DIAGNOSE DIS DISCARDDN DISCARD DISCARDS '
+           'DISPLAY DIST DISTRIBUTED DOUBLE DRAIN DROP DS DSNUM DSNZPARM DUMP DWQT EBCDIC END ENFORCE '
+           'ERRDDN ERROR ESCAPE EXCEPTION EXCEPTIONS EXTERNAL FIELDNM FIELDNM2 FIFO FILTERDD FILTERDDN FLOAT FOR '
+           'FORCE FORMAT FREQVAL FROM FULL FUNC FUNCTION GBCACHE GBPCHKPT GBPOOL GBPOOLT GCONN GDETAIL GENERIC '
+           'GENERICLU GPBDEP GRAPHIC GROUP GROUPBUFFERPOOL GTF HOUR HOURS HPSEQT HPSIZE ID IEEE IFCID IMS '
+           'IN INACTIVE IND INDDN INDEX INDEXES INDEXSPACE INDOUBT INDREFLIMIT INSTANCE INT INTEGER INTERVAL '
+           'INVALIDATE IPADDR IS KEEPDICTIONARY KEY KEYCARD LEAFDISTLIMIT LENGTH LEVELID LIKE LIMIT LIST LOAD LOAD2 '
+           'LOB LOC LOCALSITE LOCATE LOCATION LOCKS LOG LOGONLY LONGLOG LPL LRU LSTATS LU LULA LUNAME LUWID '
+           'MAINT MAP MAPDDN MAPPINGTABLE MAXRO MCONN MDETAIL MEMBER MEPL MERGECOPY MESSAGE MICROSECOND MICROSECONDS '
+           'MINUTE MINUTES MIXED MOD MODE MODIFY MONITOR MONTH MONTHS MSTR MYCOPY NET1 NEWCOPY NID NO '
+           'NOAUXCHKP NOAUXWARN NOCACHE NOCHECKPEND NOCOPYPEND NODUMP NODUMPS NOLIMIT NONE NOPAD NORBDPEND '
+           'NORCVRPEND NOSUBS NOSYSREC NOT NULL NULLIF NUMCOLS OBD OBJECT OFFLOAD OFFPOSLIMIT OFFSET ONLY OP1 OP2 OP3 OR OUTDDN '
+           'PACKED PAGE PAGES PARALLEL PARM PART PAUSE PENDING PERFM PGSTEAL PLAN POSITION POST POSTPONED PRECISION '
+           'PREFORMAT PRIMARY PROC PROCEDURE PUNCHDDN QUEUE QUIESCE RANGE RATIO REAL REBUILD REC RECOVE RECOVER '
+           'RECOVERY RECOVERYDDN RECOVERYSITE REFERENCE REFONLY REJECT REOR REORG REPAIR REPLACE REPORT '
+           'REPORTONLY RESET RESTRICT RESUME REUSE RID RLIM RLIMIT ROWID RUNSTATS S390 SAMPLE SCOPE SECOND '
+           'SECONDS SET SHRLEVEL SMALLINT SMF SORT SORTDATA SORTDEVT SORTKEYS SORTNUM SORTOUT SOUROUT SPACE SPACENAM '
+           'SPEC SPECIFIC SQL SRV STA START STAT STATISTICS STO STOGROUP STOP STOSPACE SUMMARY SYSCOPY SYSDISC SYSERR '
+           'SYSMAP SYSPUNCH SYSREC SYSUT1 SYSUTIL T TABLE TABLES TABLESPACESET TDATA TER TERM TEST THD THREAD TIME '
+           'TIMEOUT TIMESTAMP TNO TOCOPY TOLOGPOINT TORBA TOSEQNO TOVOLUME TRA TRACE TRACEID TYPE UNLDDN UNLOAD UPDATE '
+           'USE UTIL UTILID UTILITY VARCHAR VARGRAPHIC VDWQT VERIFY VERSION VPPSEQT VPSEQT VPSIZE VPXPSEQT '
+           'VTYPE WAIT WEPR WHEN WIERD WILDSTFF WORKDDN WRITE WRITERS YEAR YEARS YES ZONED'
            reswords          =     'INTO TABLESPACE'
            special           =     '} { ) ('
            operators         =     '¬> ¬= ¬< || >= > = <> <= < ; : / . - , + * # !='
            ident             =     ANY(&UCASE '_' &LCASE) FENCE(SPAN('#' &UCASE '_' &LCASE '0123456789') | epsilon)
            identifier        =     ident $ tx $ *notmatch(reswords, (POS(0) | ' ') tx (' ' | RPOS(0)))
            resword           =     ident $ tx $ *match(reswords, (POS(0) | ' ') tx (' ' | RPOS(0)))
            keyword           =     ident $ tx $ *match(keywords, (POS(0) | ' ') tx (' ' | RPOS(0)))
            Populate(.TX, ident, keywords, reswords, special, operators)
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            utlTokens         =     (*utlToken | $',' | $'(' *utlTokens $')') FENCE(*utlTokens | epsilon)
            utlToken          =     $' '
+                                   (  *integer
+                                   |  *hex
+                                   |  *ghex
+                                   |  *nhex
+                                   |  *string
+                                   |  *identifier
+                                   |  *resword
+                                   |  *operator
+                                   )

            page_number       =     $' ' (*integer | *hex) ~ 'page_number'
            num_objects       =     $' ' *integer ~ 'num_objects'
            percent_value     =     $' ' *integer ~ 'percent_value'
            ddname            =     $' ' *identifier ~ 'ddname'
            creator_id        =     $' ' *identifier ~ 'creator_id'
            column_name       =     $' ' *identifier ~ 'column_name'
            database_name     =     $' ' *identifier ~ 'database_name'
            device_type       =     $' ' *identifier ~ 'device_type'
            index_name        =     $' ' *identifier ~ 'index_name'
            index_space_name  =     $' ' *identifier ~ 'index_space_name'
            message_id        =     $' ' *identifier ~ 'message_id'
            stogroup_name     =     $' ' *identifier ~ 'stogroup_name'
            table_space_name  =     $' ' *identifier ~ 'table_space_name'
            table_name        =     $' ' *identifier ~ 'table_name'
            vol_ser           =     $' ' *identifier ~ 'vol_ser'
            data_set_name     =     $' ' *identifier ~ 'identifier'
+                                   $'.' $' ' *identifier ~ 'identifier'
+                                   $'.' $' ' *identifier ~ 'identifier' ('data_set_name' & 3)

            index             =     !(*database_name $'.') *index_name        ('index' & 2)
            index_space       =     !(*creator_id $'.')    *index_space_name  ('index_space' & 2)
            table             =     !(*database_name $'.') *table_name        ('table' & 2)
            table_space       =     !(*database_name $'.') *table_space_name  ('table_space' & 2)

            integerList       =     nPush() ($' ' *integer ~ 'integer' nInc()) % $','  ('integerList' & 'nTop()') nPop()
            hexList           =     nPush() ($' ' *hex ~ 'hex' nInc()) % $','          ('hexList' & 'nTop()')     nPop()

            empty             =     epsilon ~ ''
            filterDDName      =     *ddname
            dsnumValue        =     ALL ~ 'ALL' | $' ' *integer ~ 'integer'
            copyDDNames       =     (*ddname !($',' *ddname) | *empty $',' *ddname)
            recoverDDNames    =     (*ddname !($',' *ddname))
            yes_or_no         =     (YES | NO) ~ 'yes_or_no'
            partNumber        =     $' ' *integer ~ 'partNumber'
            sortNumber        =     $' ' *integer ~ 'sortNumber'
            exceptionsNumber  =     $' ' *integer ~ 'exceptionsNumber'
            instanceNumber    =     $' ' *integer ~ 'instanceNumber'
            traceidNumber     =     $' ' (*hex | *integer) ~ 'traceidNumber'

            index_spec        =     INDEX =*index ('INDEX' & 1)
+                             |     INDEXSPACE =*index_space ('INDEXSPACE' & 1)
            table_space_spec  =     TABLESPACE
+                                   (  *table_space ('TABLESPACE' & 1)
+                                   |  $'(' *table_space !(PART $' ' *integer ~ 'integer') ('PART' & 1) $')' ('TABLESPACE' & 2)
+                                   )

*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            catMaintUpdate    =     CATMAINT UPDATE

            checkData         =     CHECK DATA                                                                    nPush()
+                                  !%( *table_space_spec                                                          nInc()
+                                   |  PART =*partNumber                               ('PART' & 1)               nInc()
+                                   |  FOR EXCEPTION                                   ('FOR_EXCEPTION' & 0)      nInc()
+                                   |  IN *table USE *table                            ('IN_USE' & 2)             nInc()
+                                   |  SCOPE
+                                      =((PENDING | AUXONLY | ALL | REFONLY) ~ '')     ('SCOPE' & 1)              nInc()
+                                   |  AUXERROR =((REPORT | INVALIDATE) ~ '')          ('AUXERROR' & 1)           nInc()
+                                   |  DELETE =*yes_or_no                              ('DELETE' & 1)             nInc()
+                                   |  LOG =*yes_or_no                                 ('LOG' & 1)                nInc()
+                                   |  EXCEPTIONS =*exceptionsNumber                   ('EXCEPTIONS' & 1)         nInc()
+                                   |  ERRDDN =*ddname                                 ('ERRDDN' & 1)             nInc()
+                                   |  WORKDDN =(*ddname !($',' *ddname))              ('WORKDDN' & 2)            nInc()
+                                   |  SORTDEVT =*device_type                          ('SORTDEVT' & 1)           nInc()
+                                   |  SORTNUM =*sortNumber                            ('SORTNUM' & 1)            nInc()
+                                   )                                                  ('CHECK_DATA' & 'nTop()')  nPop()

            checkIndex        =     CHECK INDEX                                                                   nPush()
+                                  !(  =(ALL ~ '')                                     ('INDEX' & 1)
+                                   |  $'('                                                                       nPush()
+                                      (  *index
+                                         !(PART =*partNumber ('PART' & 1))            ('INDEX' & 2)              nInc()
+                                      ) % $','
+                                      $')'                                            ('INDEXES' & 'nTop()')     nPop()
+                                   )                                                                             nInc()
+                                  !%( *table_space_spec                                                          nInc()
+                                   |  PART =*partNumber                               ('PART' & 1)               nInc()
+                                   |  WORKDDN =(*ddname !($',' *ddname))              ('WORKDDN' & 2)            nInc()
+                                   |  SORTDEVT =*device_type                          ('SORTDEVT' & 1)           nInc()
+                                   |  SORTNUM =sortNumber                             ('SORTNUM' & 1)            nInc()
+                                   )  ('CHECK_INDEX' & '(LT(nTop(), 2) 2, nTop())')                              nPop()

            checkLob          =     CHECK LOB                                                                     nPush()
+                                  !%( *table_space_spec                                                          nInc()
+                                   |  EXCEPTIONS =*exceptionsNumber                   ('EXCEPTIONS' & 1)         nInc()
+                                   |  WORKDDN =(*ddname !($',' *ddname))              ('WORKDDN' & 2)            nInc()
+                                   |  SORTDEVT =*device_type                          ('SORTDEVT' & 1)           nInc()
+                                   |  SORTNUM =*sortNumber                            ('SORTNUM' & 1)            nInc()
+                                   )                                                  ('CHECK_LOB' & 'nTop()')   nPop()

            copyCommand       =     COPY                                                                          nPush()
+                                  %(  *table_space_spec                                                          nInc()
+                                   |  *index_spec                                                                nInc()
+                                   |  FULL =*yes_or_no                                ('FULL' & 1)               nInc()
+                                   |  CHANGELIMIT
+                                     !=( *percent_value
+                                         !($',' *percent_value)                       ('percent_values' & 2)
+                                      )                                               ('CHANGELIMIT' & 1)        nInc()
+                                   |  DSNUM =*dsnumValue                              ('DSNUM' & 1)              nInc()
+                                   |  PARALLEL !=*num_objects                         ('PARALLEL' & 1)           nInc()
+                                   |  FILTERDDN =*filterDDName                        ('FILTERDDN' & 1)          nInc()
+                                   |  COPYDDN =*copyDDNames                           ('COPYDDN' & 2)            nInc()
+                                   |  RECOVERYDDN =*recoverDDNames                    ('RECOVERYDDN' & 2)        nInc()
+                                   |  CONCURRENT                                      ('CONCURRENT' & 0)         nInc()
+                                   |  REPORTONLY                                      ('REPORTONLY' & 0)         nInc()
+                                   |  SHRLEVEL =((REFERENCE | CHANGE) ~ '')           ('SHRLEVEL' & 1)           nInc()
+                                   )                                                  ('COPY' & 'nTop()')        nPop()

            diagnoseCommand   =     DIAGNOSE                                                                      nPush()
+                                   (  END                                             ('END' & 0)                nInc()
+                                   | %(  TYPE
+                                         (  $' ' *integer ~ 'integer'
+                                         |  $'(' *integerList $')'
+                                         )                                            ('TYPE' & 1)               nInc()
+                                      |  ALLDUMPS !($'(' *hexList $')')               ('ALLDUMPS' & 1)           nInc()
+                                      |  NODUMPS !($'(' *hexList $')')                ('NODUMPS' & 1)            nInc()
+                                      |  *display_statement                                                      nInc()
+                                      |  *wait_statement                                                         nInc()
+                                      |  *abend_statement                                                        nInc()
+                                      )
+                                   )                                                  ('DIAGNOSE' & 'nTop()')    nPop()

            display_statement =     DISPLAY
+                                   (  OBD *table_space
+                                      !((ALL | TABLES | INDEXES) ~ '')                ('OBD' & 2)
+                                   |  SYSUTIL                                         ('SYSUTIL' & 0)
+                                   |  MEPL                                            ('MEPL' & 0)
+                                   |  DBET
+                                      (  DATABASE *database_name                      ('DATABASE' & 1)
+                                      |  TABLESPACE *table_space                      ('TABLESPACE' & 1)
+                                      |  INDEX *index                                 ('INDEX' & 1)
+                                      )                                               ('DBET' & 1)
+                                   )                                                  ('DISPLAY' & 1)

            wait_statement    =     WAIT                                                                          nPush()
+                                  %(  MESSAGE =*message_id                            ('MESSAGE' & 1)            nInc()
+                                      !(INSTANCE =*instanceNumber)                    ('INSTANCE' & 1)           nInc()
+                                   |  TRACEID =*traceidNumber                         ('TRACEID' & 1)            nInc()
+                                      !(INSTANCE =*instanceNumber)                    ('INSTANCE' & 1)           nInc()
+                                   )                                                  ('WAIT' & 'nTop()')        nPop()

            abend_statement   =     ABEND                                                                         nPush()
+                                  %(  MESSAGE =*message_id                            ('MESSAGE' & 1)            nInc()
+                                      !(INSTANCE =*instanceNumber)                    ('INSTANCE' & 1)           nInc()
+                                   |  TRACEID =*traceidNumber                         ('TRACEID' & 1)            nInc()
+                                      !(INSTANCE =*instanceNumber)                    ('INSTANCE' & 1)           nInc()
+                                   )
+                                   !(NODUMP ('NODUMP' & 0))                           ('ABEND' & 'nTop() + 1')   nPop()

            loadCommand       =     LOAD !DATA
+                                  %(  INDDN =(SYSREC | *ddname)
+                                   |  PREFORMAT
+                                   |  RESUME =(YES | NO)
+                                   |  REPLACE
+                                   |  COPYDDN =((SYSCOPY | *ddname) !($',' *ddname) | $',' *ddname)
+                                   |  RECOVERYDDN =(*ddname !($',' *ddname))
+                                   |  *statistics_spec
+                                   |  KEEPDICTIONARY
+                                   |  REUSE
+                                   |  LOG =(YES | NO)
+                                   |  NOCOPYPEND
+                                   |  WORKDDN =((SYSUT1 | *ddname) !($',' (SORTOUT | *ddname)))
+                                   |  SORTKEYS =($' ' *integer)
+                                   |  FORMAT =(UNLOAD | $' ' 'SQL/DS')
+                                   |  FLOAT $'(' (S390 | IEEE) $')'
+                                   |  EBCDIC
+                                   |  ASCII
+                                   |  CCSID ($' ' *integer | $'(' !%$',' *integerList $')')
+                                   |  NOSUBS
+                                   |  ENFORCE =(CONSTRAINTS | NO)
+                                   |  ERRDDN =(SYSERR | *ddname)
+                                   |  MAPDDN =(SYSMAP | *ddname)
+                                   |  DISCARDDN =(SYSDISC | *ddname)
+                                   |  DISCARDS =($' ' *integer)
+                                   |  SORTDEVT =*device_type
+                                   |  SORTNUM =($' ' *integer)
+                                   |  CONTINUEIF =($' ' *integer !($':' $' ' *integer)) $'=' $' ' (*hex | *string)
+                                   |  *into_table_spec
+                                   )

            into_table_spec   =     INTO TABLE =*table
+                                   !(PART =($' ' *integer))
+                                  !(  WHEN
+                                      (  =($' ' ('SQL/DS' | *identifier | *integer !($':' $' ' *integer)))
+                                         $'=' $' ' (*hex | *ghex | *nhex | *string)
+                                      )
+                                   |  $'(' (*column_name !*column_datatype) % $',' $')'
+                                   )

            column_datatype   =     (  BLOB
+                                   |  CHAR !(MIXED !($'(' $' ' *integer $')'))
+                                   |  CLOB
+                                   |  DATE EXTERNAL $'(' $' ' *integer $')'
+                                   |  DBCLOB
+                                   |  DEC EXTERNAL !($'(' $' ' *integer !($',' $' ' *integer) $')')
+                                   |  DEC !(PACKED | ZONED)
+                                   |  DECIMAL
+                                   |  DEFAULTIF
+                                      =($' ' *identifier | $' ' *integer !($':' $' ' *integer)) $'=' $' ' (*hex | *string)
+                                   |  DOUBLE PRECISION
+                                   |  FLOAT EXTERNAL
+                                   |  GRAPHIC EXTERNAL $'(' $' ' *integer $')'
+                                   |  INT EXTERNAL $'(' $' ' *integer $')'
+                                   |  INTEGER
+                                   |  NULLIF
+                                      =($' ' *identifier | $' ' *integer !($':' $' ' *integer)) $'=' $' ' (*hex | *string)
+                                   |  POSITION $'(' $' ' *integer !($':' $' ' *integer) $')'
+                                   |  REAL $'(' $' ' *integer $')'
+                                   |  ROWID
+                                   |  SMALLINT
+                                   |  TIME EXTERNAL $'(' $' ' *integer $')'
+                                   |  TIMESTAMP EXTERNAL $'(' $' ' *integer $')'
+                                   |  VARCHAR MIXED
+                                   |  VARGRAPHIC
+                                   )

            statistics_spec   =     STATISTICS
+                                  !%( TABLE =ALL
+                                   |  TABLE !($'(' *table $')')
+                                   |  SAMPLE =($' ' *integer)
+                                   |  COLUMN !(ALL | $'(' (ALL | *column_name % $',') $')')
+                                   |  INDEX !=((ALL !*correlation_stats_spec | *index_correlations))
+                                   |  REPORT =(NO | YES)
+                                   |  UPDATE =(ALL | ACCESSPATH | SPACE | NONE)
+                                   )

            index_correlations =    *index !*correlation_stats_spec FENCE($',' *index_correlations | epsilon)
            correlation_stats_spec = KEYCARD !%(FREQVAL NUMCOLS =($' ' *integer) COUNT =($' ' *integer))
+                                  | %(FREQVAL NUMCOLS =($' ' *integer) COUNT =($' ' *integer))


            mergecopy         =     MERGECOPY
+                                  !%( TABLESPACE =*table_space
+                                   |  WORKDDN =(SYSUT1 | *ddname)
+                                   |  DSNUM =(ALL | $' ' *integer)
+                                   |  NEWCOPY
+                                     !=( YES !*copyddn_spec !*recoveryddn_spec
+                                      |  NO !(*copyddn_spec | *recoveryddn_spec)
+                                      |  (*copyddn_spec | *recoveryddn_spec)
+                                      )
+                                   )

            copyddn_spec      =     COPYDDN =((SYSCOPY | *ddname) !($',' *ddname) | $',' *ddname)
            recoveryddn_spec  =     RECOVERYDDN =(*ddname !($',' *ddname))

            modifyRecovery    =     MODIFY RECOVERY
+                                  !%( TABLESPACE =*table_space
+                                   |  DSNUM =(ALL | $' ' *integer)
+                                   |  DELETE (AGE =($'*' | $' ' *integer) | DATE =($'*' | $' ' *integer))
+                                   )

            quiesce           =     QUIESCE
+                                  %(  (  TABLESPACE =*table_space !(PART =($' ' *integer))
+                                      |  TABLESPACESET !TABLESPACE =*table_space
+                                      )
+                                      !(WRITE =(YES | NO))
+                                   )

            rebuildIndex      =     REBUILD INDEX
+                                   (  =ALL TABLESPACE =*table_space !(PART =($' ' *integer))
+                                   |  $'(' (*index !(PART =($' ' *integer))) % $',' $')'
+                                   )
+                                  !%( REUSE
+                                   |  WORKDDN =(SYSUT1 | *ddname)
+                                   |  SORTDEVT =*device_type
+                                   |  SORTNUM =($' ' *integer)
+                                   |  SORTKEYS
+                                   |  STATISTICS
+                                     !%( REPORT =(NO | YES)
+                                      |  UPDATE =(ALL | ACCESSPATH | SPACE | NONE)
+                                      |  *correlation_stats_spec
+                                      )
+                                   )

            recoverCommand    =     RECOVER
+                                   (  *object !(DSNUM =(ALL | $' ' *integer)) *recover_options_spec
+                                   |  *object PAGE =*page_number !CONTINUE
+                                   |  %(*object !(DSNUM =(ALL | $' ' *integer)))
+                                      !(TORBA =($' ' *hex) | TOLOGPOINT =($' ' *hex))
+                                      !(REUSE !*parallel_spec | *parallel_spec | LOGONLY)
+                                   )
+                                   !(LOCALSITE | RECOVERYSITE)

            object            =     (  INDEX =*index
+                                   |  INDEXSPACE =*index_space
+                                   |  TABLESPACE =*table_space
+                                   )

            parallel_spec     =     PARALLEL !=*num_objects
            recover_options_spec =  (  TOCOPY =*data_set_name
+                                      !(TOVOLUME =(CATALOG | *vol_ser))
+                                      !(TOSEQNO =($' ' *integer))
+                                      !REUSE
+                                   |  ERROR RANGE
+                                   )

            reorgIndex        =     REORG INDEX =*index
+                                  !%( REUSE
+                                   |  PART =($' ' *integer)
+                                   |  SHRLEVEL =NONE
+                                   |  SHRLEVEL (=REFERENCE !*deadline_spec | =CHANGE !*deadline_spec !*change_spec)
+                                   |  LEAFDISTLIMIT =($' ' *integer)
+                                   |  REPORTONLY
+                                   |  UNLOAD
+                                      (  =(CONTINUE | PAUSE)
+                                        !(  STATISTICS
+                                           !%( REPORT =(NO | YES)
+                                            |  UPDATE =(ALL | ACCESSPATH | SPACE | NONE)
+                                            |  *correlation_stats_spec
+                                            )
+                                         )
+                                      | =ONLY
+                                      )
+                                   |  WORKDDN =(SYSUT1 | *ddname)
+                                   |  PREFORMAT
+                                   )

            deadline_spec     =     DEADLINE (=NONE | *labeled_duration_expression)
            change_spec       =    %(  MAXRO =($' ' *integer | DEFER)
+                                   |  DRAIN =(WRITERS | ALL)
+                                   |  LONGLOG =(CONTINUE | TERM | DRAIN)
+                                   |  DELAY =($' ' *integer)
+                                   |  TIMEOUT =(ABEND | TERM)
+                                   )
            constant          =     $' ' (*integer | *string | *hex | *ghex)
            labeled_duration_expression =
+                                   (CURRENT DATE | CURRENT TIMESTAMP)
+                                   ($'+' | $'-')
+                                   (  *constant
+                                      (  YEAR
+                                      |  YEARS
+                                      |  MONTH
+                                      |  MONTHS
+                                      |  DAY
+                                      |  DAYS
+                                      |  HOUR
+                                      |  HOURS
+                                      |  MINUTE
+                                      |  MINUTES
+                                      |  SECOND
+                                      |  SECONDS
+                                      |  MICROSECOND
+                                      |  MICROSECONDS
+                                      )
+                                   ) % ($'+' | $'-')

            reorgTablespace   =     REORG TABLESPACE =*table_space
+                                  !%( REUSE
+                                   |  PART =($' ' *integer !($':' $' ' *integer))
+                                   |  LOG =(YES | NO)
+                                   |  SORTDATA
+                                   |  NOSYSREC
+                                   |  SORTKEYS
+                                   |  SORTDEVT =*device_type
+                                   |  SORTNUM =($' ' *integer)
+                                   |  COPYDDN =((SYSCOPY | *ddname) !($',' *ddname) | $',' *ddname)
+                                   |  RECOVERYDDN =(*ddname !($',' *ddname))
+                                   |  WORKDDN =((SYSUT1 | *ddname) !($',' (SORTOUT | *ddname)))
+                                   |  PREFORMAT
+                                   |  SHRLEVEL =NONE
+                                   |  SHRLEVEL
+                                      (  =REFERENCE !*deadline_spec
+                                      |  =CHANGE !*deadline_spec
+                                        !%( MAPPINGTABLE *table
+                                         |  MAXRO =($' ' *integer | DEFER)
+                                         |  DRAIN =(WRITERS | ALL)
+                                         |  LONGLOG =(CONTINUE | TERM | DRAIN)
+                                         |  DELAY =($' ' *integer)
+                                         |  TIMEOUT =(ABEND | TERM)
+                                         )
+                                      )
+                                   |  OFFPOSLIMIT =($' ' *integer) INDREFLIMIT =($' ' *integer) !REPORTONLY
+                                   |  (  UNLOAD =(CONTINUE | PAUSE) !KEEPDICTIONARY !*statistics_spec
+                                      |  UNLOAD =ONLY
+                                      |  UNLOAD =EXTERNAL !NOPAD
+                                         !%(FROM TABLE =*table !(WHEN $'(' *selection_condition $')'))
+                                      )
+                                   |  UNLDDN =*ddname
+                                   |  PUNCHDDN =(SYSPUNCH | *ddname)
+                                   |  DISCARDDN =(SYSDISC | *ddname)
+                                   |  DISCARD !NOPAD
+                                      !%(FROM TABLE =*table !(WHEN $'(' *selection_condition $')'))
+                                   |  FROM TABLE =*table !(WHEN $'(' *selection_condition $')')
+                                   )

            selection_condition =   (*predicate | $'(' *selection_condition $')') % (AND | OR)
            predicate         =     (  *column_name
+                                      ($'=' | $'<>' | $'>' | $'<' | $'>=' | $'<=' | $'¬=' | $'¬>' | $'¬<')
+                                      (*constant | *labeled_duration_expression)
+                                   |  *column_name !NOT
+                                      BETWEEN (*constant | *labeled_duration_expression)
+                                      (AND | OR) (*constant | *labeled_duration_expression)
+                                   |  *column_name !NOT IN $'(' *constant % $',' $')'
+                                   |  *column_name !NOT LIKE $' ' *string !(ESCAPE $' ' *string)
+                                   |  *column_name IS !NOT NULL
+                                   )

            repairCommand     =     REPAIR
+                                   (  LEVELID (TABLESPACE *table_space | INDEX *index) !(PART =($' ' *integer))
+                                   |  !OBJECT
+                                      !(LOG =(YES | NO))
+                                      (%(*set_tablespace_statement | *locate_block) | *dbd_statement)
+                                   )

            set_tablespace_statement =
+                                   SET
+                                  %(  INDEX $'(' (ALL | *index !(PART $' ' *integer)) $')'
+                                   |  TABLESPACE *table_space
+                                   |  PART $' ' *integer
+                                   |  NOCHECKPEND
+                                   |  NORBDPEND
+                                   |  NOCOPYPEND
+                                   |  NORCVRPEND
+                                   |  NOAUXWARN
+                                   |  NOAUXCHKP
+                                   )

            locate_block      =     LOCATE (TABLESPACE *table_space | INDEX *index) !(PART $' ' *integer)
+                                   (  PAGE $' ' (*hex | *integer)
+                                   |  ROWID $' ' *hex
+                                   |  RID $' ' *hex
+                                   |  KEY $' ' *hex INDEX *index
+                                   )
+                                  !%( DUMP DATA $' ' (*hex | *integer | *string)
+                                   |  DUMP MAP  $' ' *integer
+                                   |  DUMP
+                                      !(OFFSET $' ' (*hex | *integer) LENGTH $' ' (*hex | *integer))
+                                      PAGES $' ' (*hex | *integer | $'*')
+                                   |  DUMP
+                                   |  DELETE
+                                   |  REPLACE OFFSET $' ' (*hex | *integer) DATA $' ' (*hex | *integer | *string)
+                                   |  REPLACE RESET
+                                   |  VERIFY !(OFFSET $' ' (*hex | *integer)) DATA $' ' (*hex | *integer | *string)
+                                   |  VERSION $' ' *hex
+                                   )

            dbd_statement     =     DBD (REBUILD | DIAGNOSE | TEST | DROP)
+                                  %(  DATABASE CHECK
+                                   |  OUTDDN *ddname
+                                   |  DBID $' ' *hex
+                                   )

            reportCommand     =     REPORT
+                                   (  RECOVERY
+                                      (  TABLESPACE =*table_space !(INDEX =(NONE | ALL))
+                                      |  INDEXSPACE =*index_space
+                                      |  INDEX =*index
+                                      )
+                                     !%( DSNUM =(ALL | $' ' *integer)
+                                      |  CURRENT
+                                      |  SUMMARY
+                                      |  LOCALSITE
+                                      |  RECOVERYSITE
+                                      |  ARCHLOG =(ALL | $' ' *integer)
+                                      )
+                                   |  TABLESPACESET !TABLESPACE =*table_space
+                                   )

            runstatsTablespace =    RUNSTATS
+                                   (  TABLESPACE =*table_space !(PART =($' ' *integer))
+                                     !(  TABLE =(ALL) !(SAMPLE =($' ' *integer))
+                                      | %(  TABLE =*table !(SAMPLE =($' ' *integer))
+                                            COLUMN (=ALL | $'(' *column_name % $',' $')')
+                                         )
+                                      )
+                                     !%( INDEX
+                                        !(  =ALL !*correlation_stats_spec
+                                         |  $'(' (*index !(PART =($' ' *integer)) !*correlation_stats_spec) % $',' $')'
+                                         )
+                                      |  SHRLEVEL =(REFERENCE | CHANGE)
+                                      |  REPORT =(NO | YES)
+                                      |  UPDATE =(ALL | ACCESSPATH | SPACE | NONE)
+                                      )
+                                   |  INDEX
+                                      (  =ALL TABLESPACE =*table_space !*correlation_stats_spec
+                                      |  $'(' (*index !(PART =($' ' *integer)) !*correlation_stats_spec) % $',' $')'
+                                      )
+                                     !%( SHRLEVEL =(REFERENCE | CHANGE)
+                                      |  REPORT =(NO | YES)
+                                      |  UPDATE =(ALL | ACCESSPATH | SPACE | NONE)
+                                      )
+                                   )

            stospaceStogroup  =     STOSPACE STOGROUP $'(' ($'*' | *stogroup_name % $',') $')'

            dashNameList      =     *dashName (($',' | $':') *dashNameList | epsilon)
            dashName          =     (  $'*'
+                                   |  $'*' $'.' $'*'
+                                   |  !$'*' $' ' *identifier !($'*' $' ' *identifier) !$'*'
+                                      !($'.' !$'*' $' ' *identifier !$'*')
+                                   )

            dashAlterBpool    =     $'-' (ALT | ALTER) (BPOOL | BUFFERPOOL) $'(' $' ' *identifier $')'
+                                   VPSIZE $'(' $' ' *integer $')'
+                                   VTYPE (DATASPACE | PRIMARY)
+                                   HPSIZE $'(' $' ' *integer $')'
+                                   VPSEQT $'(' $' ' *integer $')'
+                                   VPPSEQT $'(' $' ' *integer $')'
+                                   VPXPSEQT $'(' $' ' *integer $')'
+                                   HPSEQT $'(' $' ' *integer $')'
+                                   DWQT $'(' $' ' *integer $')'
+                                   VDWQT $'(' $' ' *integer $',' $' ' *integer $')'
+                                   CASTOUT $'(' (YES | NO) $')'
+                                   PGSTEAL (FIFO | LRU)

            dashAlterGbpool   =     $'-' (ALT | ALTER) (GBPOOL | GROUPBUFFERPOOL) $'(' $' ' *identifier $')'
+                                   GBCACHE $'(' YES $')'
+                                   AUTOREC $'(' YES $')'
+                                   RATIO $'(' $' ' *integer $'.' $' ' *integer $')'
+                                   CLASST $'(' $' ' *integer $')'
+                                   GBPOOLT $'(' $' ' *integer $')'
+                                   GBPCHKPT $'(' $' ' *integer $')'

            dashAlterUtility  =     $'-' (ALT | ALTER) UTILITY $'(' $' ' *identifier $')'
+                                   REORG
+                                   DEADLINE $'(' NONE $')'
+                                   MAXRO $'(' DEFER $')'
+                                   LONGLOG $'(' CONTINUE $')'
+                                   DELAY $'(' $' ' *integer $')'

            dashArchive       =     $'-' (ARC | ARCHIVE) LOG
+                                   (  CANCEL OFFLOAD
+                                   |  MODE $'(' QUIESCE $')'
+                                      TIME $'(' $' ' *integer $')'
+                                      WAIT $'(' YES $')'
+                                   |  SCOPE $'(' (DBDB | GROUP) $')'
+                                   )
            dashCancel        =     $'-' (CAN | CANCEL)
+                                   !DDF
+                                   (THD | THREAD) $'(' ($' ' *integer | $' ' *identifier $'.' $' ' *identifier) $')'
+                                   !DUMP

            dashDisArc        =     $'-' (DIS | DISPLAY) (ARC | ARCHIVE)
            dashDisBpool      =     $'-' (DIS | DISPLAY) (BPOOL | BUFFERPOOL)
+                                   $'(' ($'*' | ACTIVE | $' ' *identifier $',' $' ' *identifier) $')'
+                                   (  DBNAME $'(' *dashNameList $')'
+                                      !(GPBDEP $'(' (YES | NO) $')')
+                                   |  DETAIL $'(' ($'*' | ACTIVE) $')'
+                                      LIST $'(' ($'*' | ACTIVE) $')' !($'(' $'*' $')')
+                                      !(LSTATS $'(' ACTIVE $')')
+                                   |  SPACENAM $'(' ($'*' | COPY $'*' | COPY ($',' | $':') UNLOAD) $')'
+                                      !(CASTOWNR $'(' (YES | NO) $')')
+                                   )

            dashDisDb         =     $'-' (DIS | DISPLAY) (DB | DATABASE)
+                                   $'(' *dashNameList $')'
+                                   !(CLAIMERS | LOCKS | LPL | USE | WEPR)
+                                   SPACENAM
+                                   $'(' *dashNameList $')'
+                                   !(CLAIMERS | LOCKS | LPL | USE | WEPR)
+                                   (  PART $'(' $' ' *integer !(($',' | $':') $' ' *integer) $')'
+                                      LIMIT $'(' ($'*' | $' ' *integer) $')'
+                                   |  ONLY
+                                   |  epsilon
+                                   )
+                                   AFTER ACTIVE RESTRICT ADVISORY AREST

            dashDisFunc       =     $'-' (DIS | DISPLAY) (FUNC | FUNCTION) (SPEC | SPECIFIC)
+                                   $'(' *dashNameList $')'

            dashDisGbpool     =     $'-' (DIS | DISPLAY) (GBPOOL | GROUPBUFFERPOOL)
+                                   $'(' *dashNameList $')'
+                                  %(  CONNLIST $'(' (YES | NO) $')'
+                                   |  MDETAIL !($'(' ($'*' | INTERVAL) $')')
+                                   |  GDETAIL !($'(' ($'*' | INTERVAL) $')')
+                                   |  TYPE $'(' (GCONN | MCONN | NOCACHE) $')'
+                                   )

            dashDisGroup      =     $'-' (DIS | DISPLAY) GROUP !DETAIL
            dashDisLoc        =     $'-' (DIS | DISPLAY) (LOC | LOCATION)
+                                   (  $'(' $' ' *integer $'.' $' ' *integer $'.' $' ' *integer $'.' $' ' *integer $')'
+                                   |  $'(' $'*' $')' DETAIL
+                                   |  $'(' $'<' LU $'*' $')'
+                                   |  $'(' $'<' LULA $'>' $')'
+                                   )

            dashDisProc       =     $'-' (DIS | DISPLAY) (PROC | PROCEDURE)
+                                   $'(' *dashNameList $')'

            dashDisRlim       =     $'-' (DIS | DISPLAY) (RLIM | RLIMIT)
            dashDisThd        =     $'-' (DIS | DISPLAY) (THD | THREAD)
+                                   $'(' *dashNameList $')'
+                                  !%( T $'(' ($'*' | INACTIVE | INDOUBT | POSTPONED) $')'
+                                   |  LUWID $'(' $'*' $')'
+                                   |  LUWID $'(' NET1 $'.' $'*' $')'
+                                   |  LOCATION $'(' $'*' $')'
+                                   |  LOCATION $'(' $'<' LULA $'>' $')'
+                                   |  LOCATION $'(' $'<' LU $'*' $')'
+                                   |  LOCATION $'(' $' ' *integer $'.' $' ' *integer $'.' $' ' *integer $'.' $' ' *integer $')'
+                                   |  TYPE $'(' ACTIVE $')'
+                                   |  DETAIL
+                                   )

            dashTraName       =     ACCTG | AUDIT | MONITOR | PERFM | STAT
            dashDisTra        =     $'-' (DIS | DISPLAY) (TRA | TRACE)
+                                   !( $'(' ($'*' | *dashTraName) $')'
+                                   |  DEST $'(' GTF $',' SMF $',' SRV $',' OP1 $')'
+                                   |  DETAIL $'(' $' ' *integer $')'
+                                      COMMENT $'(' $' ' *string $')'
+                                   |  PLAN $'(' REORG $',' COPY $')'
+                                      AUTHID $'(' CHECK $',' LOAD $')'
+                                      !( CLASS $'(' $' ' *integer $',' $' ' *integer $')'
+                                         TNO $'(' $' ' *integer $',' $' ' *integer $')'
+                                      )
+                                      LOCATION
+                                      $'('
+                                      (  $' ' *integer $'.' $' ' *integer $'.' $' ' *integer $'.' $' ' *integer
+                                      |  $'<' LULA $'>'
+                                      )
+                                      $')'
+                                   )

            dashDisUtil       =     $'-' (DIS | DISPLAY) (UTIL | UTILITY)
+                                   $'(' *dashNameList $')'
+                                   MEMBER $'(' *dashNameList $')'

            dashModify        =     $'-' (MOD | MODIFY) (TRA | TRACE)
+                                   $'(' *dashTraName $')'
+                                   CLASS $'(' ($'*' | $' ' *integer) $')'
+                                   TNO $'(' $' ' *integer $')'
+                                   IFCID $'(' ($'*' | $' ' *integer !($',' $' ' *integer)) $')'
+                                   !(COMMENT $'(' $' ' *string $')')

            dashRecover       =     $'-' (REC | RECOVER)
+                                   (  BSDS
+                                   |  POST
+                                   |  POSTPONED
+                                   |  (IND | INDOUBT)
+                                      !($'(' *dashName $')')
+                                      ACTION $'(' (ABORT | COMMIT) $')'
+                                      (  ID $'(' ($'*' | *dashNameList) $')'
+                                      |  LUWID $'(' $' ' (*integer | *identifier) $')'
+                                      |  NID
+                                         $'('
+                                         $' ' *identifier $'.' $' ' *integer
+                                         !($',' $' ' *identifier $'.' $' ' *integer)
+                                         $')'
+                                      )
+                                   )

            dashResetGeneric  =     $'-' RESET (GENERIC | GENERICLU) $'(' *dashNameList $')'

            dashResetInd      =     $'-' RESET (IND | INDOUBT)
+                                  !%( IPADDR $'(' $' ' *integer $'.' $' ' *integer $'.' $' ' *integer $'.' $' ' *integer $')'
+                                   |  IPADDR $'(' $'*' $')'
+                                   |  LOCATION $'(' CHECK $',' LOAD $',' REPORT $')'
+                                   |  LOCATION $'(' REPORT $')'
+                                   |  LUNAME $'(' $'*' $')'
+                                   |  LUNAME $'(' $' ' *identifier $')'
+                                   |  LUWID $'(' $' ' *integer $')'
+                                   |  LUWID $'(' CHECK $')'
+                                   |  FORCE
+                                   )

            dashSet           =     $'-' SET (ARC | ARCHIVE)
+                                   (  COUNT $'(' $' ' *integer $')'
+                                      TIME
+                                      $'('
+                                      (  $' ' *integer
+                                      |  $' ' *integer $',' $' ' *integer
+                                      |  $',' $' ' *integer
+                                      |  NOLIMIT
+                                      )
+                                      $')'
+                                   |  DEFAULT
+                                   )

            dashStartDb       =     $'-' (STA | START) (DB | DATABASE) $'(' *dashNameList $')'
+                                  !%( SPACENAM $'(' *dashNameList $')'
+                                   |  PART $'(' $' ' *integer $')'
+                                   |  PART $'(' $' ' *integer $':' $' ' *integer $')'
+                                   |  PART $'(' $' ' *integer $',' $' ' *integer $')'
+                                   )

            dashStartDb2Parm  =     $'-' (STA | START) DB2 PARM $'(' (DSNZPARM | REPORT) $')'
+                                  !%( ACCESS $'(' $'*' $')'
+                                   |  ACCESS $'(' MAINT $')'
+                                   |  DBM1 $'(' $' ' *string $')'
+                                   |  DIST $'(' $' ' *string $')'
+                                   |  MSTR $'(' $' ' *string $')'
+                                   )

            dashStartDdf      =     $'-' (STA | START) DDF
            dashStartFunc     =     $'-' (STA | START) (FUNC | FUNCTION) (SPEC | SPECIFIC) $'(' *dashNameList $')'
            dashStartProc     =     $'-' (STA | START) (PROC | PROCEDURE) $'(' *dashNameList $')'
            dashStartRlim     =     $'-' (STA | START) (RLIM | RLIMIT) !(ID $'=' $' ' *identifier)

            dashStartTra      =     $'-' (STA | START) (TRA | TRACE) $'(' ($'*' | *dashTraName) $')'
+                                  !%( DEST $'(' GTF $',' SMF $',' SRV $',' OP2 $',' OP3 $')'
+                                   |  LOCATION $'(' $'*' $')'
+                                   |  COMMENT $'(' $' ' *string $')'
+                                   |  PLAN $'(' $'*' $')'
+                                   |  PLAN $'(' LOAD $',' REORG $')'
+                                   |  AUTHID $'(' $'*' $')'
+                                   |  AUTHID $'(' COPY $',' REPORT $')'
+                                   |  CLASS $'(' $'*' $')'
+                                   |  IFCID $'(' $'*' $')'
+                                   |  BUFSIZE $'(' $'*' $')'
+                                   |  TDATA $'(' CORRELATION $',' (TRA | TRACE) $',' CPU $',' DISTRIBUTED $')'
+                                   )

            dashStopDb        =     $'-' (STO | STOP) (DB | DATABASE) $'(' *dashNameList $')'
+                                  !%( SPACENAM $'(' *dashNameList $')'
+                                   |  PART $'(' $' ' *integer $')'
+                                   |  PART $'(' $' ' *integer $':' $' ' *integer $')'
+                                   |  PART $'(' $' ' *integer $',' $' ' *integer $')'
+                                   )

            dashStopDb2       =     $'-' (STO | STOP) DB2 !(MODE $'(' (FORCE | QUIESCE) $')')
            dashStopDdf       =     $'-' (STO | STOP) DDF !(MODE $'(' (FORCE | QUIESCE) $')')

            dashStopFunc      =     $'-' (STO | STOP) (FUNC | FUNCTION) (SPEC | SPECIFIC)
+                                   $'(' *dashNameList $')'
+                                   !(ACTION $'(' (QUEUE | REJECT) $')')

            dashStopProc      =     $'-' (STO | STOP) (PROC | PROCEDURE)
+                                   $'(' *dashNameList $')'
+                                   ACTION $'(' (QUEUE | REJECT) $')'

            dashStopRlim      =     $'-' (STO | STOP) (RLIM | RLIMIT) !(ID $'=' $' ' *identifier)

            dashStopTra       =     $'-' (STO | STOP) (TRA | TRACE) $'(' ($'*' | *dashTraName) $')'
+                                  !%( DEST $'(' GTF $',' SMF $',' SRV $',' OP2 $')'
+                                   |  PLAN $'(' $'*' $')'
+                                   |  PLAN $'(' LOAD $',' REORG $')'
+                                   |  AUTHID $'(' $'*' $')'
+                                   |  AUTHID $'(' COPY $',' REPORT $')'
+                                   |  CLASS $'(' $' ' *integer $',' $' ' *integer $')'
+                                   |  TNO $'(' $' ' *integer $',' $' ' *integer $')'
+                                   |  LOCATION $'(' REORG $')'
+                                   )

            dashTerm          =     $'-' (TER | TERM) (UTIL | UTILITY) $'(' ($'*' | REORG | REPORT !$'*') $')'

            utlCommand        =     (  *catMaintUpdate
+                                   |  *checkData           nInc()
+                                   |  *checkIndex          nInc()
+                                   |  *checkLob            nInc()
+                                   |  *copyCommand         nInc()
+                                   |  *dashAlterBpool
+                                   |  *dashAlterGbpool
+                                   |  *dashAlterUtility
+                                   |  *dashArchive
+                                   |  *dashCancel
+                                   |  *dashDisArc
+                                   |  *dashDisBpool
+                                   |  *dashDisDb
+                                   |  *dashDisFunc
+                                   |  *dashDisGbpool
+                                   |  *dashDisGroup
+                                   |  *dashDisLoc
+                                   |  *dashDisProc
+                                   |  *dashDisRlim
+                                   |  *dashDisThd
+                                   |  *dashDisTra
+                                   |  *dashDisUtil
+                                   |  *dashModify
+                                   |  *dashRecover
+                                   |  *dashResetGeneric
+                                   |  *dashResetInd
+                                   |  *dashSet
+                                   |  *dashStartDb
+                                   |  *dashStartDb2Parm
+                                   |  *dashStartDdf
+                                   |  *dashStartFunc
+                                   |  *dashStartProc
+                                   |  *dashStartRlim
+                                   |  *dashStartTra
+                                   |  *dashStopDb
+                                   |  *dashStopDb2
+                                   |  *dashStopDdf
+                                   |  *dashStopFunc
+                                   |  *dashStopProc
+                                   |  *dashStopRlim
+                                   |  *dashStopTra
+                                   |  *dashTerm
+                                   |  *diagnoseCommand     nInc()
+                                   |  *loadCommand
+                                   |  *mergecopy
+                                   |  *recoverCommand
+                                   |  *reorgIndex
+                                   |  *reorgTablespace
+                                   |  *reportCommand
+                                   |  *runstatsTablespace
+                                   |  *stospaceStogroup
+                                   |  *modifyRecovery
+                                   |  *quiesce
+                                   |  *rebuildIndex
+                                   |  *repairCommand
+                                   ) . utlVerb
+                                   ARBNO(*utlToken)
*                                   . utlText . *Remember(utlVerb '~' utlText)

            utlRecognizer     =     nPush() ARBNO(*utlCommand) $' ' RPOS(0) reduce('commands', 'nTop()') nPop()

*---------- ----------------- ----- -------------------------------------------------------- -----------------------------

                                                                                             :(RETURN)
UserDefsEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserRpt()')                                                              :(UserRptEnd)
UserRpt     utl               =     Pop()                                                    :f(RETURN)
            DIFFER(utl)                                                                      :f(RETURN)
*           XDump('utl', utl)
            TDump(utl)                                                                       :(RETURN)
UserRptEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserTokens()')                                                           :(UserTokensEnd)
UserTokens  tok[t = t + 1] = token(,, .utlRecognizer)
            tok[t = t + 1] = token(,  *(spcpfx '*integer'), *integer)
            tok[t = t + 1] = token(,  *(spcpfx '*hex'), *hex)
            tok[t = t + 1] = token(,  *(spcpfx '*ghex'), *ghex)
            tok[t = t + 1] = token(,  *(spcpfx '*nhex'), *nhex)
            tok[t = t + 1] = token(,  *(spcpfx '*string'), *string)
            tok[t = t + 1] = token(,  *(tx), *resword . tx)
            tok[t = t + 1] = token(,  *(tx), *keyword . tx)
            tok[t = t + 1] = token(,  *("'" tx "'"), *identifier . tx)
*           tok[t = t + 1] = token(,  *(spcpfx "$'(' *dashNameList $')'"), $'(' *dashNameList $')')
            tok[t = t + 1] = token(,  *("$'" tx "'"), *operator . tx)
            tok[t = t + 1] = token(,  *("$'" tx "'"), ',' . tx)
            tok[t = t + 1] = token(,  *("$'" tx "'"), '(' . tx)
            tok[t = t + 1] = token(,  *("$'" tx "'"), ')' . tx)

            dbg[.utlToken]                   = TRUE
            dbg[.utlCommand]                 = TRUE
            dbg[.predicate]                  = TRUE
            dbg[.selection_condition]        = TRUE
            dbg[.reorgTablespace]            = TRUE
            dbg[.identifier]                 = TRUE
            dbg[.hex]                        = TRUE
            dbg[.integer]                    = TRUE
            dbg[.string]                     = TRUE
            dbg[.set_tablespace_statement]   = TRUE
            dbg[.repairCommand]              = TRUE
            dbg[.locate_block]               = TRUE
            dbg[.dbd_statement]              = TRUE
            dbg[.column_datatype]            = TRUE
            dbg[.table_space_spec]           = TRUE
            dbg[.table_space]                = TRUE

                                                                                             :(RETURN)
UserTokensEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
