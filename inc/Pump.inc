*---------- --------------------------------------------------------------------------------------------
*           SQL Server Data Type defines.
*
            SQLTEXT             =    35   ;* 0x23
            SQLVARBINARY        =    37   ;* 0x25
            SQLINTN             =    38   ;* 0x26
            SQLVARCHAR          =    39   ;* 0x27
            SQLBINARY           =    45   ;* 0x2d
            SQLIMAGE            =    34   ;* 0x22
            SQLCHARACTER        =    47   ;* 0x2f
            SQLINT1             =    48   ;* 0x30
            SQLBIT              =    50   ;* 0x32
            SQLINT2             =    52   ;* 0x34
            SQLINT4             =    56   ;* 0x38
            SQLMONEY            =    60   ;* 0x3c
            SQLDATETIME         =    61   ;* 0x3d
            SQLFLT8             =    62   ;* 0x3e
            SQLFLTN             =   109   ;* 0x6d
            SQLMONEYN           =   110   ;* 0x6e
            SQLDATETIMN         =   111   ;* 0x6f
            SQLFLT4             =    59   ;* 0x3b
            SQLMONEY4           =   122   ;* 0x7a
            SQLDATETIM4         =    58   ;* 0x3a
            SQLDECIMAL          =   106   ;* 0x6a    New types for SQL 6.0 and later servers
            SQLNUMERIC          =   108   ;* 0x6c
            SQLUNIQUEID         =    36   ;* 0x24    New types for SQL 7.0 and later servers
            SQLBIGCHAR          =   175   ;* 0xaf
            SQLBIGVARCHAR       =   167   ;* 0xa7
            SQLBIGBINARY        =   173   ;* 0xad
            SQLBIGVARBINARY     =   165   ;* 0xa5
            SQLBITN             =   104   ;* 0x68
            SQLNCHAR            =   239   ;* 0xef
            SQLNVARCHAR         =   231   ;* 0xe7
            SQLNTEXT            =    99   ;* 0x63
            SQLINT8             =   127   ;* 0x7f    New types for SQL 2000 and later servers
            SQLVARIANT          =    98   ;* 0x62
            SQLUDT              =   240   ;* 0xf0    New types for SQL 2005 and later servers
            SQLXML              =   241   ;* 0xf1
            SQLTABLE            =   243   ;* 0xf3    New types for SQL 2008 and later servers
            SQLDATEN            =    40   ;* 0x28
            SQLTIMEN            =    41   ;* 0x29
            SQLDATETIME2N       =    42   ;* 0x2a
            SQLDATETIMEOFFSETN  =    43   ;* 0x2b
*-----------------------------------------------------------------------------------------------------------------------
            DATA('Fmt(bcpDataType,bcpPrefixLength,bcpDataLength,sqlDataSize,sqlDataLength,sqlDataType,bcpColumnCollation)')
            FmtT                      =   TABLE()
            FmtT['bit']               =   Fmt('SQLCHAR',    1,  3,   2,  1, SQLBITN,           '""')
            FmtT['tinyint']           =   Fmt('SQLCHAR',    1,  5,   4,  1, SQLINT1,           '""')
            FmtT['smallint']          =   Fmt('SQLCHAR',    1,  7,   6,  2, SQLINT2,           '""')
            FmtT['int']               =   Fmt('SQLCHAR',    1, 12,  11,  4, SQLINT4,           '""')
            FmtT['bigint']            =   Fmt('SQLCHAR',    1, 21,  20,  8, SQLINT8,           '""')
            FmtT['decimal']           =   Fmt('SQLCHAR',    1, 41,  40, 19, SQLDECIMAL,        '""')
            FmtT['numeric']           =   Fmt('SQLCHAR',    1, 41,  40, 19, SQLNUMERIC,        '""')
            FmtT['smallmoney']        =   Fmt('SQLCHAR',    1, 30,  12,  4, SQLMONEY4,         '""')
            FmtT['money']             =   Fmt('SQLCHAR',    1, 30,  21,  8, SQLMONEY,          '""')
            FmtT['real']              =   Fmt('SQLCHAR',    1, 30,  30,  4, SQLFLT4,           '""')
            FmtT['float']             =   Fmt('SQLCHAR',    1, 30,  30,  8, SQLFLT8,           '""')
            FmtT['smalldatetime']     =   Fmt('SQLCHAR',    1, 24,  23,  4, SQLDATETIM4,       '""')
            FmtT['datetime']          =   Fmt('SQLCHAR',    1, 24,  23,  8, SQLDATETIME,       '""')
            FmtT['char']              =   Fmt('SQLCHAR',    2,   ,    ,   , SQLBIGCHAR,        'Latin1_General_BIN')
            FmtT['varchar']           =   Fmt('SQLCHAR',    2,   ,    ,   , SQLBIGVARCHAR,     'Latin1_General_BIN')
            FmtT['varcharmax']        =   Fmt('SQLCHAR',     ,  0,  -1,   , SQLBIGVARCHAR,     'Latin1_General_BIN')
            FmtT['text']              =   Fmt('SQLCHAR',     ,  0,   0,   , SQLTEXT,           'Latin1_General_BIN')
            FmtT['nchar']             =   Fmt('SQLNCHAR',   2,   ,    ,   , SQLNCHAR,          'Latin1_General_BIN')
            FmtT['nvarchar']          =   Fmt('SQLNCHAR',   2,   ,    ,   , SQLNVARCHAR,       'Latin1_General_BIN')
            FmtT['nvarcharmax']       =   Fmt('SQLNCHAR',    ,  0,  -1,   , SQLNVARCHAR,       'Latin1_General_BIN')
            FmtT['ntext']             =   Fmt('SQLCHAR',     ,  0,   0,   , SQLNTEXT,          'Latin1_General_BIN')
            FmtT['binary']            =   Fmt('SQLBINARY',  2,   ,    ,   , SQLBIGBINARY,      '""')
            FmtT['varbinary']         =   Fmt('SQLBINARY',  2,   ,    ,   , SQLBIGVARBINARY,   '""')
            FmtT['varbinarymax']      =   Fmt('SQLBINARY',   ,  0,  -1,   , SQLBIGVARBINARY,   '""')
            FmtT['image']             =   Fmt('SQLIMAGE',    ,  0,   0,   , SQLIMAGE,          '""')
            FmtT['sql_variant']       =   Fmt('SQLVARIANT', 4,   ,   1,   , SQLVARIANT,        '""')
            FmtT['timestamp']         =   Fmt('SQLBINARY',  1,  8,   8,   , SQLBINARY,         '""') ;* 189
            FmtT['uniqueidentifier']  =   Fmt('SQLCHAR',    1, 36,  16,   , SQLUNIQUEID,       '""')
            FmtT['xml']               =   Fmt('SQLCHAR',     ,  0,    ,   , SQLXML,            'SQL_Latin1_General_CP1_CI_AS')
*---------- ----------- --- --------------------------------------------------- --------------------------------
            BULK_Pump   =   1  ;* BULK INSERT via format and data file
            SQL_Pump    =   2  ;* SQL INSERT via SQLNCLI ODBC routines
            BCP_Pump    =   3  ;* BCP API via SQLNCLI bcp_* routines
            DynSQL_Pump =   4  ;* Dynamic SQL via SQLNCLI ODBC routines
*---------- ----------- --- --------------------------------------------------- --------------------------------
            DATA('column(colName,colDataType,colExpr)')
*---------- ----------- --- --------------------------------------------------- --------------------------------
            DEFINE('PumpInit(columns,name,ftcol)SQL')                           :(PumpInitEnd)
PumpInit    SQL         =   GenTABLE(columns, name)
            SQL_A_ExecDirect(hstmt, SQL)                                        :F(PumpInitE)
            SQL_EndTranCommit()                                                 :F(PumpInitE)
*           SQL         =   DIFFER(ftcol) GenFTIndex(name, ftcol)               :F(PumpInit0)
*           SQL_A_ExecDirect(hstmt, SQL)                                        :F(PumpInitE)
*           SQL_EndTranCommit()                                                 :F(PumpInitE)
PumpInit0   DIFFER(xPump)                                                       :S($('PumpInit' xPump))F(RETURN)
PumpInit1   BULK_Fmt(columns, name)
            BULK_Cmds(columns, name)                                            :(RETURN)
PumpInit2                                                                       :(RETURN)
PumpInit3   BCP_Init(columns, name)                                             :S(RETURN)F(FRETURN)
PumpInitE   OUTPUT      =   SQL_GetLastError()
            OUTPUT      =   SQL                                                 :(FRETURN)
PumpInitEnd
*---------- ----------- --- --------------------------------------------------- --------------------------------
            DEFINE('PumpOpen(nm,name)')                                         :(PumpOpenEnd)
PumpOpen    DIFFER(xPump)                                                       :S($('PumpOpen' xPump))F(RETURN)
PumpOpen1   OUTPUT(nm, 4, name '.bcp[-r1 -w]')                                  :S(RETURN)F(ioerr)
PumpOpen2   $nm         =                                                       :(RETURN)
PumpOpen3                                                                       :(RETURN)
PumpOpenEnd
*---------- ----------- --- --------------------------------------------------- --------------------------------
            DEFINE('PumpRow(nm,columns)')                                       :(PumpRowEnd)
PumpRow     DIFFER(xPump)                                                       :S($('PumpRow' xPump))F(RETURN)
PumpRow1    BULK_Row(nm, columns)                                               :S(RETURN)F(FRETURN)
PumpRow2    $nm         =   $nm nl (DIFFER($nm) ', ', '  ')
            $nm         =   $nm SQL_Vals(columns)                               :(RETURN)
PumpRow3    BCP_Row(columns)                                                    :S(RETURN)F(FRETURN)
PumpRowEnd
*---------- ----------- --- --------------------------------------------------- --------------------------------
            DEFINE('PumpClose(nm,name,count)SQL')                               :(PumpCloseEnd)
PumpClose   DIFFER(xPump)                                                       :S($('PumpClose' xPump))F(RETURN)
PumpClose1  ENDFILE(4)                                                          :F(ioerr)
            SQL         =   "BULK INSERT " name
+                           " FROM '" xCwd bSlash name ".bcp'"
+                           " WITH (FORMATFILE = '" xCwd bSlash name ".fmt')"   :(PumpClose5)
PumpClose2  SQL         =   "INSERT INTO " name " VALUES " $nm nl ";"           :(PumpClose5)
PumpClose3  BCP_Close()                                                         :S(RETURN)F(FRETURN)
PumpClose5  GT(count)                                                           :F(RETURN)
            SQL_A_ExecDirect(hstmt, SQL)                                        :F(PumpCloseE)
            SQL_EndTranCommit()                                                 :S(RETURN)F(PumpCloseE)
PumpCloseE  OUTPUT      =   SQL_GetLastError()
            OUTPUT      =   SQL                                                 :(FRETURN)
PumpCloseEnd
*---------- ----------- --- --------------------------------------------------- --------------------------------
            DEFINE('PumpFini()')                                                :(PumpFiniEnd)
PumpFini    DIFFER(xPump)                                                       :S($('PumpFini' xPump))F(RETURN)
PumpFini1                                                                       :(RETURN)
PumpFini2                                                                       :(RETURN)
PumpFini3   BCP_Fini()                                                          :S(RETURN)F(FRETURN)
PumpFiniEnd
*---------- ----------- --- --------------------------------------------------- --------------------------------
            DEFINE('BCP_Init(columns,name)'
+               'cbIndicator,cbUserData,colDataType,colName,'
+               'column,eDataType,fmt,iC,p,s'
+           )                                                                   :(BCP_InitEnd)
BCP_Init    bcp_init(name)                                                      :F(FRETURN)
            iC          =   0
BCP_Init3   iC          =   iC + 1
            column      =   columns[iC]                                         :F(BCP_Init7)
            colName     =   DIFFER(colName(column), 'id$') colName(column)      :F(BCP_Init3)
            colDataType =   DIFFER(colDataType(column)) colDataType(column)     :S(BCP_Init4)
            bcp_colfmt(iC, 0, 0, 0, colName)                                    :(BCP_Init3)
BCP_Init4   colDataType =   DTDigest(colDataType, .p, .s)
            fmt         =   FmtT[colDataType]
            eDataType   =   sqlDataType(fmt)
            cbIndicator =   bcpPrefixLength(fmt)
            cbUserData  =   sqlDataSize(fmt)
            cbUserData  =   IDENT(cbUserData) p
            bcp_colfmt(iC, eDataType, cbIndicator, cbUserData, colName)         :S(BCP_Init3)F(FRETURN)
BCP_Init7                                                                       :(RETURN)
BCP_InitEnd
*---------- ----------- --- --------------------------------------------------- --------------------------------
            DEFINE('BCP_Row(columns)'
+               'cbUserData,colDataType,colExpr,colMore,colName,colSize,colVal,'
+               'column,eDataType,fmt,iC,iP,p,s'
+           )                                                                   :(BCP_RowEnd)
BCP_Row     iP          =   0
BCP_Row1    iP          =   LT(iP, 2) iP + 1                                    :F(BCP_Row9)
            iC          =   0
BCP_Row3    iC          =   iC + 1
            column      =   columns[iC]                                         :F(BCP_Row7)
            colName     =   DIFFER(colName(column), 'id$') colName(column)      :F(BCP_Row3)
            colDataType =   DIFFER(colDataType(column)) colDataType(column)     :F(BCP_Row3)
            colDataType =   colDataType(column)
            colDataType =   DTDigest(colDataType, .p, .s)
            fmt         =   FmtT[colDataType]
            eDataType   =   sqlDataType(fmt)
            cbUserData  =   sqlDataSize(fmt)
            cbUserData  =   IDENT(cbUserData) p
            colExpr     =   colExpr(column)
            colVal      =   EVAL(colExpr)
            colVal      =   IDENT(colDataType, 'nchar') (utf8_to_wstr(colVal), NULL)
            colVal      =   IDENT(colDataType, 'nvarchar') (utf8_to_wstr(colVal), NULL)
            colVal      =   IDENT(colDataType, 'nvarcharmax') (utf8_to_wstr(colVal), NULL)
            colSize     =   SIZE(colVal)
            (EQ(iP, 1))                                                         :F(BCP_Row4)
            (IDENT(colVal)  GT(cbUserData) bcp_collen(-1, iC))                  :S(BCP_Row3)
            (IDENT(colVal)  EQ(cbUserData) bcp_collen(-1, iC))                  :S(BCP_Row3)
            (DIFFER(colVal) GT(cbUserData) bcp_colval(colVal, iC))              :S(BCP_Row3)
            (DIFFER(colVal) EQ(cbUserData) bcp_collen(colSize, iC))             :(BCP_Row3)
BCP_Row4    colMore     =   IDENT(colVal)  GT(cbUserData)                       :S(BCP_Row3)
            colMore     =   IDENT(colVal)  LE(cbUserData) -1                    :S(BCP_Row5)
            colMore     =   DIFFER(colVal) LE(cbUserData) colVal                :S(BCP_Row5)F(BCP_Row3)
BCP_Row5    bcp_moretext(colMore)                                               :F(BCP_RowE)
            colMore     =   DIFFER(colVal) LT(cbUserData) 0                     :F(BCP_Row3)
            bcp_moretext(colMore)                                               :S(BCP_Row3)F(BCP_RowE)
BCP_Row7    (EQ(iP, 1))                                                         :F(BCP_Row1)
            bcp_sendrow()                                                       :S(BCP_Row1)F(BCP_RowE)
BCP_Row9                                                                        :(RETURN)
BCP_RowE    OUTPUT      =   SQL_GetLastError()                                  :(FRETURN)
BCP_RowEnd
*---------- ----------- --- --------------------------------------------------- --------------------------------
            DEFINE('BCP_Close()')                                               :(BCP_CloseEnd)
BCP_Close   bcp_batch()                                                         :S(RETURN)
            OUTPUT      =   SQL_GetLastError()                                  :(FRETURN)
BCP_CloseEnd
*---------- ----------- --- --------------------------------------------------- --------------------------------
            DEFINE('BCP_Fini()')                                                :(BCP_FiniEnd)
BCP_Fini    bcp_done()                                                          :S(RETURN)
            OUTPUT      =   SQL_GetLastError()                                  :(FRETURN)
BCP_FiniEnd
*---------- --------------- --- --------------------------------------------------- ----------------------------
            bcpInt          =   SPAN('0123456789')
*---------- --------------- --- --------------------------------------------------- ----------------------------
            DEFINE('DTDigest(DTDigest,nmP,nmS)max')                             :(DTDigestEnd)
DTDigest    $nmP            =
            $nmS            =
            max             =   1073741824
            DTDigest        '(' 'max' . $nmP ')' =                              :S(DTDigest10)
            DTDigest        '(' bcpInt . $nmP ')' =                             :S(DTDigest10)
            DTDigest        '(' bcpInt . $nmP ',' bcpInt . $nmS ')' =           :S(DTDigest10)
DTDigest10  DTDigest        =   LEQ($nmP, 'max') DTDigest 'max'
            $nmP            =   LEQ($nmP, 'max') max                            :S(RETURN)
            $nmP            =   LEQ(DTDigest, 'text') max                       :S(RETURN)
            $nmP            =   LEQ(DTDigest, 'ntext') max                      :S(RETURN)
            $nmP            =   LEQ(DTDigest, 'image') max                      :(RETURN)
DTDigestEnd
*---------- --------------- --- --------------------------------------------------- ----------------------------
            DEFINE('BULK_Pfx(len,datatype)fmt,pfxLen')                          :(BULK_PfxEnd)
BULK_Pfx    fmt             =   FmtT[datatype]
            pfxLen          =   bcpPrefixLength(fmt)
            pfxLen          =   IDENT(pfxLen) 4
            EQ(len, -1)                                                         :F(BULK_Pfx5)
            BULK_Pfx        =   GT(pfxLen, 3) BULK_Pfx CHAR(255)
            BULK_Pfx        =   GT(pfxLen, 2) BULK_Pfx CHAR(255)
            BULK_Pfx        =   GT(pfxLen, 1) BULK_Pfx CHAR(255)
            BULK_Pfx        =   GT(pfxLen, 0) BULK_Pfx CHAR(255)                :(RETURN)
BULK_Pfx5   pfxLen          =   GT(pfxLen, 0) pfxLen - 1                        :F(RETURN)
            BULK_Pfx        =   BULK_Pfx CHAR(REMDR(len, 256))
            len             =   len / 256                                       :(BULK_Pfx5)
BULK_PfxEnd
*---------- --------------- --- --------------------------------------------------- ----------------------------
            DEFINE('BULK_Fmt(columns,name)'
+              'bcpOutput,fmt,column,colName,colDataLen,colDataType,i,j,p,pfxLen,s'
+           )                                                                       :(BULK_FmtEnd)
BULK_Fmt    OUTPUT(.bcpOutput, 4, name '.fmt')
            bcpOutput       =   "8.0"
            bcpOutput       =   c - 1
            i               =   0
            j               =   0
BULK_Fmt1   i               =   i + 1
            column          =   columns[i]                                          :F(BULK_Fmt9)
            colName         =   DIFFER(column) colName(column)                      :F(BULK_Fmt1)
            j               =   DIFFER(colName, 'id$') j + 1                        :F(BULK_Fmt1)
            colDataType     =   colDataType(column)
            colDataType     =   DTDigest(colDataType, .p, .s)
            fmt             =   FmtT[colDataType]
            colDataLen      =   bcpDataLength(fmt)
            colDataLen      =   (DIFFER(colDataLen) colDataLen, p)
            pfxLen          =   bcpPrefixLength(fmt)
            pfxLen          =   IDENT(pfxLen) 4
            bcpOutput       =   RPAD(j, 7)
+                               ' ' RPAD(bcpDataType(fmt), 13)
+                               ' ' RPAD(pfxLen, 7)
+                               ' ' RPAD(colDataLen, 7)
+                               ' ' RPAD('""', 25)
+                               ' ' RPAD(j + 1, 5)
+                               ' ' RPAD(colName, 23)
+                               ' ' bcpColumnCollation(fmt)                         :(BULK_Fmt1)
BULK_Fmt9   ENDFILE(4)                                                              :(RETURN)
BULK_FmtEnd
*---------- --------------- --- ----------------------------------------------- ----------------------------
            DEFINE('GenTABLE(columns,name)i,n')                                 :(GenTABLEEnd)
GenTABLE    GenTABLE        =   "IF (OBJECT_ID('" name "', 'U') IS NULL)" nl
            GenTABLE        =   GenTABLE "    CREATE TABLE " name nl
            i               =   0
GenTABLE1   i               =   i + 1
            column          =   columns[i]                                      :F(GenTABLE9)
            colName         =   colName(column)
            colDataType     =   DIFFER(colDataType(column)) colDataType(column) :F(GenTABLE1)
            n               =   n + 1
            GenTABLE        =   GenTABLE "    " (EQ(n, 1) "(", ",") "   "
            GenTABLE        =   GenTABLE RPAD(colName, 15) ' ' colDataType
            GenTABLE        =   GenTABLE IDENT(colName, 'id$') ' IDENTITY(1, 1)'
            GenTABLE        =   GenTABLE nl                                     :(GenTABLE1)
GenTABLE9   GenTABLE        =   GenTABLE "    , CONSTRAINT PK_" name " PRIMARY KEY CLUSTERED (id$)"
            GenTABLE        =   GenTABLE "    )" nl                             :(RETURN)
GenTABLEEnd
*---------- --------------- --- ----------------------------------------------- ----------------------------
            xFT_Catalog =   '5ivesAlive'
*---------- --------------- --- ----------------------------------------------- ----------------------------
            DEFINE('GenFTCat()')                                                :(GenFTCatEnd)
GenFTCat    GenFTCat        =   "CREATE FULLTEXT"
                                "        CATALOG [" xFT_Catalog "]"
                                "           WITH ACCENT_SENSITIVITY = OFF"
                                "  AUTHORIZATION dbo"                           :(RETURN)
GenFTCatEnd
*---------- --------------- --- ----------------------------------------------- ----------------------------
            DEFINE('GenFTIndex(name,ftcol)')                                    :(GenFTIndexEnd)
GenFTIndex  GenFTIndex      =   "DECLARE @object_id int" nl
+                               "SET @object_id = OBJECT_ID('dbo." name "')" nl
+                               "IF NOT EXISTS(SELECT 1 FROM sys.fulltext_indexes WHERE object_id = @object_id)" nl
+                               "    CREATE FULLTEXT INDEX" nl
+                               "                 ON " name " (" ftcol " LANGUAGE 0)" nl
+                               "          KEY INDEX PK_" name nl
+                               "                 ON [" xFT_Catalog "]" nl
+                               "               WITH CHANGE_TRACKING = MANUAL" nl
+                               "                  , STOPLIST = OFF" nl         :(RETURN)
GenFTIndexEnd
*---------- --------------- --- ----------------------------------------------- ----------------------------
            DEFINE('BULK_Cmds(columns,name)'
+              'sqlOutput,bcpdir,fmt,column,colName,colDataType,i'
+           )                                                                   :(BULK_CmdsEnd)
BULK_Cmds   OUTPUT(.sqlOutput, 4, name '.sql')
            sqlOutput       =   "USE Lon"
            sqlOutput       =
            sqlOutput       =   "DROP TABLE " name
            sqlOutput       =   "CREATE TABLE " name
            i               =   0
BULK_Cmds1  i               =   i + 1
            column          =   columns[i]                                      :F(BULK_Cmds9)
            colName         =   colName(column)
            colDataType     =   colDataType(column)
            sqlOutput       =   (EQ(i, 1) '(', ',')
+                               '   ' RPAD(colName, 15) ' ' colDataType         :(BULK_Cmds1)
BULK_Cmds9  sqlOutput       =   ")"
            sqlOutput       =
            sqlOutput       =   "BULK INSERT " name
            sqlOutput       =   "    FROM '" xCwd bSlash name ".bcp'"
            sqlOutput       =   "    WITH (FORMATFILE = '" xCwd bSlash name ".fmt')"
            sqlOutput       =
            sqlOutput       =   "GO"
            ENDFILE(4)                                                          :(RETURN)
BULK_CmdsEnd
*---------- ----------- --- --------------------------------------------------- --------------------------------
            DEFINE('BULK_Row(nm,columns)'
+              'column,colName,colDataType,colExpr,colVal,colLen,j,p,row,s'
+           )                                                                   :(BULK_RowEnd)
BULK_Row    row         =
            j           =   0
BULK_Row3   j           =   j + 1
            column      =   columns[j]                                          :F(BULK_Row7)
            DIFFER(column)                                                      :F(BULK_Row3)
            colName     =   DIFFER(colName(column), 'id$') colName(column)      :F(BULK_Row3)
            colDataType =   colDataType(column)
            colDataType =   DTDigest(colDataType, .p, .s)
            colExpr     =   colExpr(column)
            colVal      =   EVAL(colExpr)
            colVal      =   IDENT(colDataType, 'nchar') (utf8_to_wstr(colVal), NULL)
            colVal      =   IDENT(colDataType, 'nvarchar') (utf8_to_wstr(colVal), NULL)
            colVal      =   IDENT(colDataType, 'nvarcharmax') (utf8_to_wstr(colVal), NULL)
            colLen      =   (DIFFER(colVal) SIZE(colVal), -1)
            row         =   row BULK_Pfx(colLen, colDataType) colVal            :(BULK_Row3)
BULK_Row7   $nm         =   row                                                 :(RETURN)
BULK_RowEnd
*---------- ----------- --- --------------------------------------------------- --------------------------------
            DEFINE('SQL_Vals(columns)'
+              'column,colName,colDataType,colExpr,colVal,colLen,i,j,p,row,s'
+           )                                                                   :(SQL_ValsEnd)
SQL_Vals    row         =   "("
            i           =   0
            j           =   0
SQL_Vals3   j           =   j + 1
            column      =   columns[j]                                          :F(SQL_Vals7)
            colName     =   DIFFER(column) colName(column)                      :F(SQL_Vals3)
            i           =   DIFFER(colName, 'id$') i + 1                        :F(SQL_Vals3)
            row         =   GT(i, 1) row ', '
            colDataType =   colDataType(column)
            colDataType =   DTDigest(colDataType, .p, .s)
            colExpr     =   colExpr(column)
            colVal      =   EVAL(colExpr)
            colVal      =   IDENT(colVal) 'NULL'                                :S(SQL_Vals5)
            colVal      =   IDENT(colDataType, 'char')        "'" SqlSQize(colVal) "'"
            colVal      =   IDENT(colDataType, 'varchar')     "'" SqlSQize(colVal) "'"
            colVal      =   IDENT(colDataType, 'varcharmax')  "'" SqlSQize(colVal) "'"
            colVal      =   IDENT(colDataType, 'nchar')       "N'" SqlSQize(colVal) "'"
            colVal      =   IDENT(colDataType, 'nvarchar')    "N'" SqlSQize(colVal) "'"
            colVal      =   IDENT(colDataType, 'nvarcharmax') "N'" SqlSQize(colVal) "'"
            colVal      =   IDENT(colDataType, 'datetime')    "'" SqlSQize(colVal) "'"
*           colVal      =   IDENT(colDataType, 'decimal')     "'" SqlSQize(colVal) "'"
*           colVal      =   IDENT(colDataType, 'numeric')     "'" SqlSQize(colVal) "'"
            colVal      =   IDENT(colDataType, 'bigint') colVal
            colVal      =   IDENT(colDataType, 'int') +colVal
            colVal      =   IDENT(colDataType, 'smallint') +colVal
            colVal      =   IDENT(colDataType, 'tinyint') +colVal
            colVal      =   IDENT(colDataType, 'bit') +colVal
            colVal      =   IDENT(colDataType, 'timestamp') 'DEFAULT'
SQL_Vals5   row         =   row colVal                                          :(SQL_Vals3)
SQL_Vals7   row         =   row ')'
            SQL_Vals    =   row                                                 :(RETURN)
SQL_ValsEnd
*---------- ----------- --- ---------------------------------------------------
            DEFINE('MinId(id1,id2)cmp,dflt,idx1,idx2,ret')
            DEFINE('MaxId(id1,id2)cmp,dflt,idx1,idx2,ret')                      :(IdEnd)
MinId       ret         =   .MinId
            dflt        =   '9223372036854775808'
            cmp         =   *LLT(idx2, idx1)                                    :(Id)
MaxId       ret         =   .MaxId
            dflt        =   '0'
            cmp         =   *LGT(idx2, idx1)                                    :(Id)
Id          idx1        =   (DIFFER(id1) id1, dflt)
            idx2        =   (DIFFER(id2) id2, dflt)
            idx1        =   LPAD(idx1, 19, '0')
            idx2        =   LPAD(idx2, 19, '0')
            $ret        =   id1
            $ret        =   EVAL(cmp) id2                                       :(RETURN)
IdEnd
*---------- ----------- --- ---------------------------------------------------
            DEFINE('MinDate(d1,d2)cmp,dflt,dx1,dx2,ret')
            DEFINE('MaxDate(d1,d2)cmp,dflt,dx1,dx2,ret')                        :(DateEnd)
MinDate     ret         =   .MinDate
            dflt        =   '9999-99-99 99:99:99'
            cmp         =   *LLT(dx2, dx1)                                      :(Date)
MaxDate     ret         =   .MaxDate
            dflt        =   '0000-00-00 00:00:00'
            cmp         =   *LGT(dx2, dx1)                                      :(Date)
Date        dx1         =   (DIFFER(d1) d1, dflt)
            dx2         =   (DIFFER(d2) d2, dflt)
            $ret        =   d1
            $ret        =   EVAL(cmp) d2                                        :(RETURN)
DateEnd
*---------- ----------- --- ---------------------------------------------------
            DEFINE('ReadConfig(name,incl_domains,modulo,number)'
+               'eDomain,eId,eName,eQuery,hQuery,sQuery'
+           )                                                                   :(ReadConfigEnd)
ReadConfig  xIT         =   IDENT(xIT) IniRead(name '.ini')
            EQ(xOffline, TRUE)                                                  :F(ReadConfig1)
            DIFFER(xIT)                                                         :F(FRETURN)
            xIT[0]      =   IDENT(xIT[0]) TABLE(17)
            eId         =   0
ReadConfig0 eId         =   LT(eId, 1000) eId + 1                               :F(RETURN)
            xMaxEntity  =   DIFFER(xIT[eId]) eId                                :(ReadConfig0)
ReadConfig1 xIT         =   IDENT(xIT) TABLE(17)
            xIT[0]      =   IDENT(xIT[0]) TABLE(17)
            hQuery      =   SQL_AllocStmt()                                     :F(SQLFail)
            sQuery      =   "SELECT id$, name, query, domain"
+                           " FROM Topics"
+                           " WHERE active_ind = 1"
+                           ( DIFFER(modulo)
+                             DIFFER(number)
+                           " AND " number " = id$ % " modulo
+                           , ""
+                           )
            SQL_A_ExecDirect(hQuery, sQuery)                                    :F(ReadConfigE)
ReadConfig2 SQL_Fetch(hQuery)                                                   :F(ReadConfig3)
            eId         =   SQL_GetData(hQuery, 1)                              :F(ReadConfigE)
            eName       =   SQL_GetData(hQuery, 2)                              :F(ReadConfigE)
            eQuery      =   SQL_GetData(hQuery, 3)                              :F(ReadConfigE)
            eDomain     =   SQL_GetData(hQuery, 4)                              :F(ReadConfigE)
            eId         =   +eId
            (EQ(incl_domains, FALSE) IDENT(eDomain), EQ(incl_domains, TRUE))    :F(ReadConfig2)
            xMaxEntity  =   GT(eId, xMaxEntity) eId
            xIT[eId]    =   IDENT(xIT[eId]) TABLE(7)                            ;* :F(ReadConfig2)
            xIT[eId]['Name'] = eName
            xIT[eId]['Query'] = eQuery
            xIT[eId]['Domain'] = eDomain                                        :(ReadConfig2)
ReadConfig3 SQL_FreeStmt(hQuery)                                                :F(SQLFail)
            IniWrite(name '.ini', xIT)                                          :(RETURN)
ReadConfigE OUTPUT      =   'SQL Failure: ' SQL_GetLastError()                  :(FRETURN)
ReadConfigEnd
*---------- ----------- --- ---------------------------------------------------
            DEFINE('ReadCities()'
+               'cId,cCity,cState,cLatDeg,cLatMin,cLonDeg,cLonMin,hQuery'
+           )
            DATA('City(name,latitude,longitude)')                               :(ReadCitiesEnd)
ReadCities  xCT         =   IDENT(xCT) TABLE(275)
            hQuery      =   SQL_AllocStmt()                                     :F(SQLFail)
            SQL_A_ExecDirect(hQuery, "SELECT * FROM Cities")                    :F(ReadCitiesE)
ReadCities1 SQL_Fetch(hQuery)                                                   :F(ReadCities2)
            cId         =   SQL_GetData(hQuery, 1)                              :F(ReadCitiesE)
            cCity       =   SQL_GetData(hQuery, 2)                              :F(ReadCitiesE)
            cState      =   SQL_GetData(hQuery, 3)                              :F(ReadCitiesE)
            cLatDeg     =   SQL_GetData(hQuery, 4)                              :F(ReadCitiesE)
            cLatMin     =   SQL_GetData(hQuery, 5)                              :F(ReadCitiesE)
            cLonDeg     =   SQL_GetData(hQuery, 6)                              :F(ReadCitiesE)
            cLonMin     =   SQL_GetData(hQuery, 7)                              :F(ReadCitiesE)
            cLat        =   GE(cLatDeg) cLatDeg + cLatDeg / 60.0
            cLat        =   LT(cLatDeg) cLatDeg - cLatMin / 60.0
            cLon        =   GE(cLonDeg) cLonDeg + cLonDeg / 60.0
            cLon        =   LT(cLonDeg) cLonDeg - cLonMin / 60.0
            cId         =   +cId
            xMaxCities  =   GT(cId, xMaxCities) cId
            xCT[cId]    =   City(cCity ', ' cState, cLat, cLon)                 :(ReadCities1)
ReadCities2 SQL_FreeStmt(hQuery)                                                :S(RETURN)F(SQLFail)
ReadCitiesE OUTPUT      =   'SQL Failure: ' SQL_GetLastError()                  :(FRETURN)
ReadCitiesEnd
*---------- ----------- --- ---------------------------------------------------
            DEFINE('ReadSchema(p)SQL,aS,f,hQuery,iS,o,st')                      :(ReadSchemaEnd)
ReadSchema  tS          =   TABLE()
            hQuery      =   SQL_AllocStmt()                                     :F(SQLFail)
            SQL         =   "SELECT name" nl
+                           "  FROM sys.objects" nl
+                           " WHERE type = 'U'" nl
+                           "   AND name LIKE '" p "%'" nl
            SQL_A_ExecDirect(hQuery, SQL)                                       :F(ReadSchemaE)
ReadSchema1 SQL_Fetch(hQuery)                                                   :F(ReadSchema2)
            o           =   SQL_GetData(hQuery, 1)                              :F(ReadSchemaE)
            tS[o]       =   TABLE()                                             :(ReadSchema1)
ReadSchema2 SQL_FreeStmt(hQuery)
            aS          =   CONVERT(tS, 'ARRAY')                                :F(RETURN)
            iS          =   0
ReadSchema3 iS          =   iS + 1
            o           =   aS[iS, 1]                                           :F(RETURN)
            hQuery      =   SQL_AllocStmt()                                     :F(SQLFail)
            SQL         =   "SELECT C, dbo.DataType('" o "', C) AS data_type" nl
+                           "  FROM dbo.Columns('" o "')" nl
+                           " WHERE C NOT LIKE '%$'" nl
            SQL_A_ExecDirect(hQuery, SQL)                                       :F(ReadSchemaE)
ReadSchema4 SQL_Fetch(hQuery)                                                   :F(ReadSchema5)
            f           =   SQL_GetData(hQuery, 1)                              :F(ReadSchemaE)
            st          =   SQL_GetData(hQuery, 2)                              :F(ReadSchemaE)
            st          POS(0) ('varchar' | 'nvarchar') . st '(max)' RPOS(0)
            tS[o][f]    =   st                                                  :(ReadSchema4)
ReadSchema5 SQL_FreeStmt(hQuery)                                                :S(ReadSchema3)F(SQLFail)
ReadSchemaE OUTPUT      =   'SQL Failure: ' SQL_GetLastError()                  :(FRETURN)
ReadSchemaEnd
*---------- ----------- --- ---------------------------------------------------
            DEFINE('SetupCancel()eventName')                                    :(SetupCancelEnd)
            hCancel     =   -1
ErrExit     OUTPUT      =   DIFFER(&ERRTYPE, 320) &ERRTEXT                      :S(ABORT)
            &ERRLIMIT   =   1
            OUTPUT      =   'Cancelling ...'
            isCancelled =   TRUE                                                :(SCONTINUE)
SetupCancel isCancelled =   FALSE
*           SETEXIT(.ErrExit)
*           &ERRLIMIT   =   1
            eventName   =   '5ivesAlive_' xListener xNumber '_' getpid()
            hCancel     =   CreateEvent(TRUE, FALSE, eventName)
            OUTPUT      =   DIFFER(hCancel, -1) 'Event "' eventName '"'
+                           ' created (' hCancel ').'                           :S(RETURN)
            OUTPUT      =   'Error: Cannot create cancel event "' eventName '"' :(FRETURN)
SetupCancelEnd
*---------- ----------- --- ---------------------------------------------------
            DEFINE('IsCancelled()iRv')                                          :(IsCancelledEnd)
IsCancelled IsCancelled =   EQ(isCancelled, TRUE) TRUE                          :S(RETURN)
            iRv         =   WaitForSingleObject(hCancel, 0)
            EQ(iRv, -1)                                                         :S(error)
            EQ(iRv, 128)                                                        :S(error)
            IsCancelled =   EQ(iRv, 258) FALSE                                  :S(RETURN)
            isCancelled =   EQ(iRv, 0) TRUE                                     :F(error)
            IsCancelled =   isCancelled                                         :(RETURN)
IsCancelledEnd
*---------- ----------- --- ---------------------------------------------------
            DEFINE('SetupWait()')
            hTimer      =   -1                                                  :(SetupWaitEnd)
SetupWait   hTimer      =   CreateWaitableTimer(TRUE)
            OUTPUT      =   DIFFER(hTimer, -1) 'Timer created (' hTimer ').'    :S(RETURN)
            OUTPUT      =   'Error: Cannot create waitable timer'               :(FRETURN)
SetupWaitEnd
*---------- ----------- --- ---------------------------------------------------
            DEFINE('Wait(iMilliSecs)iObject')                                   :(WaitEnd)
Wait        SetWaitableTimer(hTimer, iMilliSecs)                                :F(error)
            iObject     =   WaitForDoubleObjects(hCancel, hTimer, FALSE, -1)    :F(error)
            isCancelled =   EQ(iObject, 0) TRUE
            OUTPUT      =   EQ(isCancelled, TRUE) 'Wait Interrupted ...'        :(RETURN)
WaitEnd
*---------- ----------- --- ---------------------------------------------------
            DEFINE('Args(name)iArg,sArg,sOpt')                                  :(ArgsEnd)
Args        xDebug      =   FALSE
            xOffline    =   FALSE
            xReset      =   FALSE
            xFailOver   =
            xPassword   =
            xServer     =
            xUser       =
            xModulo     =
            xNumber     =
            xPump       =   BCP_Pump
            xTrace      =   0
            xVerbose    =   1
            iArg        =   HOST(3) - 1
Args1       sArg        =   HOST(2, iArg = iArg + 1)                            :F(Args9)
            sArg        FENCE '-' 'd' . *assign(.xDebug, TRUE) RPOS(0)          :S(Args1)
            sArg        FENCE '-' 'o' . *assign(.xOffline, TRUE) RPOS(0)        :S(Args1)
            sArg        FENCE '-' 'r' . *assign(.xReset, TRUE) RPOS(0)          :S(Args1)
            sArg        FENCE '-' 'D' . *assign(.sOpt, 'xDatabase') RPOS(0)     :S(Args2)
            sArg        FENCE '-' 'F' . *assign(.sOpt, 'xFailOver') RPOS(0)     :S(Args2)
            sArg        FENCE '-' 'P' . *assign(.sOpt, 'xPassword') RPOS(0)     :S(Args2)
            sArg        FENCE '-' 'S' . *assign(.sOpt, 'xServer') RPOS(0)       :S(Args2)
            sArg        FENCE '-' 'U' . *assign(.sOpt, 'xUser') RPOS(0)         :S(Args2)
            sArg        FENCE '-' 'm' . *assign(.sOpt, 'xModulo') RPOS(0)       :S(Args2)
            sArg        FENCE '-' 'n' . *assign(.sOpt, 'xNumber') RPOS(0)       :S(Args2)
            sArg        FENCE '-' 'p' . *assign(.sOpt, 'xPump') RPOS(0)         :S(Args2)
            sArg        FENCE '-' 't' . *assign(.sOpt, 'xTrace') RPOS(0)        :S(Args2)
            sArg        FENCE '-' 'v' . *assign(.sOpt, 'xVerbose') RPOS(0)      :S(Args2)
            sArg        FENCE '-' 'w' . *assign(.sOpt, 'periodSecs') RPOS(0)    :S(Args2)F(ArgsE)
Args2       sArg        =   HOST(2, iArg = iArg + 1)                            :F(ArgsE)
            sArg        FENCE '-'                                               :S(ArgsE)
            sArg        FENCE RPOS(0)                                           :S(ArgsE)
            sArg        FENCE REM . $sOpt RPOS(0)
            xPump       =   IDENT(sOpt, 'xPump') upr(xPump)                     :F(Args1)
            xPump       =   IDENT(xPump, 'BULK') BULK_Pump                      :S(Args1)
            xPump       =   IDENT(xPump, 'SQL') SQL_Pump                        :S(Args1)
            xPump       =   IDENT(xPump, 'BCP') BCP_Pump                        :S(Args1)F(ArgsE)
Args9       DIFFER(xServer)                                                     :F(ArgsE)
            DIFFER(xDatabase)                                                   :S(RETURN)F(ArgsE)
ArgsE       OUTPUT      =   'Usage: ' name
            OUTPUT      =   '    -S <server>                ; SQL Server instance name, required'
            OUTPUT      =   '    -F <failover>              ; SQL Server instance name (failover partner)'
            OUTPUT      =   '    -D <database>              ; SQL Server database name, required'
            OUTPUT      =   '    -U <login>                 ; SQL Server authentication - login name'
            OUTPUT      =   '    -P <password>              ; SQL Server authentication - password'
            OUTPUT      =   '    -d                         ; run program in debugger'
            OUTPUT      =   '    -r                         ; reset configuration info'
            OUTPUT      =   '    -t                         ; trace parsing'
            OUTPUT      =   '    -v <level>                 ; verbosity level (0 - 5), default is 1'
            OUTPUT      =   '    -p "bulk" | "sql" | "bcp"  ; BULK insert, SQL insert, or BCP API'
            OUTPUT      =                                                       :(FRETURN)
ArgsEnd
*---------- ----------- --- --------------------------------------------------- --------------------------------
