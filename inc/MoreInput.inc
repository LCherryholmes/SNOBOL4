*---------- ----------- --- ----------------------------------------------- ------------------------
            DEFINE('Tack(p,o)')                                             :(Tack_end)
Tack        Tack        =   (DIFFER(p) p '_', NULL) o                       :(RETURN)
Tack_end
*---------- ----------- --- ----------------------------------------------- ------------------------
            DEFINE('SQL_type(SQL_type)')                                    :(SQL_type_end)
SQL_type    SQL_type    =   SQL_type IDENT(SQL_type, 'varchar') "(max)"     :S(RETURN)
            SQL_type    =   SQL_type IDENT(SQL_type, 'nvarchar') "(max)"    :(RETURN)
SQL_type_end
*---------- ----------- --- ----------------------------------------------- ------------------------
            DEFINE('SQL_CREATE_TABLE(nmSQL,o,level)'
+               'SQL,aS,f,has_city,iK,iS,sK,st'
+           ,   .SQL_CT
+           )                                                               :(SQL_CT_End)
SQL_CT      aS          =   (DIFFER(tS[o]) SORT(tS[o]), NULL)
            has_city    =   ( ?(o ? POS(0) 'CityGrid') TRUE
+                           , ?(o ? POS(0) 'Foursquare') TRUE
+                           , ?(o ? POS(0) 'Yelp') TRUE
+                           , ?(o ? POS(0) 'Geo') TRUE
+                           , FALSE
+                           )
            SQL         =   'CREATE TABLE ' o nl
            iK          =   0
SQL_CT1     sK          =   DIFFER(tK[iK = iK + 1]) tK[iK]                  :F(SQL_CT2)
            SQL         =   SQL (EQ(iK, 1) "(", ",") "   "
            SQL         =   SQL sK "_id$ int"
*           SQL         =   SQL (DIFFER(sK, o) sK "_id$", "id$") " int"
            SQL         =   SQL EQ(level, 1) EQ(iK, 1) " IDENTITY(1, 1)"
            SQL         =   SQL " NOT NULL" nl                              :(SQL_CT1)
SQL_CT2     SQL         =   SQL EQ(level, 1) ',   stamp$ timestamp NOT NULL' nl
            SQL         =   SQL EQ(level, 1) ',   topic_id$ int NOT NULL' nl
            SQL         =   SQL EQ(level, 1) EQ(has_city, TRUE) ',   city_id$ int NOT NULL' nl
            iS          =   0
SQL_CT3     f           =   DIFFER(aS) aS[(iS = iS + 1), 1]                 :F(SQL_CT4)
            st          =   aS[iS, 2]
            DIFFER(tTypes[st]) GT(tTypes[st], 0)                            :F(SQL_CT3)
            f           =   IDENT(f, 'primary') '[' f ']'
            f           =   IDENT(f, 'schema') '[' f ']'
            SQL         =   SQL ",   " f " " SQL_type(st) " NULL" nl        :(SQL_CT3)
SQL_CT4     SQL         =   SQL ",   CONSTRAINT PK_" o
            SQL         =   SQL " PRIMARY KEY CLUSTERED "
            iK          =   0
SQL_CT5     sK          =   DIFFER(tK[iK = iK + 1]) tK[iK]                  :F(SQL_CT6)
            SQL         =   SQL (EQ(iK, 1) "(", ", ") sK "_id$"
*           SQL         =   SQL (EQ(iK, 1) "(", ", ") (DIFFER(sK, o) sK "_id$", "id$")
                                                                            :(SQL_CT5)
SQL_CT6     SQL         =   SQL ")" nl
            SQL         =   SQL ")" nl
            TERMINAL    =   SQL ;* 'CREATE TABLE ' o
            $nmSQL      =   $nmSQL SQL                                      :(RETURN)
*           SQL_A_ExecDirect(hStmt, SQL)                                    :F(SQLFail)
*           SQL_EndTranCommit()                                             :S(RETURN)F(SQLFail)
SQL_CT_End
*---------- ----------- --- ----------------------------------------------- ------------------------
            DEFINE('SQL_ALTER_TABLE_ADD_COLUMN(nmSQL,o,f,st)SQL'
+           , .SQL_AT_AddC
+           )                                                               :(SQL_AT_AddC_End)
SQL_AT_AddC SQL         =   "ALTER TABLE " o
+                           " ADD " f " " SQL_type(st) " NULL" nl
            TERMINAL    =   SQL
            $nmSQL      =   $nmSQL SQL                                      :(RETURN)
*           SQL_A_ExecDirect(hStmt, SQL)                                    :F(SQLFail)
*           SQL_EndTranCommit()                                             :S(RETURN)F(SQLFail)
SQL_AT_AddC_End
*---------- ----------- --- ----------------------------------------------- ------------------------
            DEFINE('SQL_ALTER_TABLE_ALTER_COLUMN(nmSQL,o,f,st)SQL'
+           , .SQL_AT_AltC
+           )                                                               :(SQL_AT_AltC_End)
SQL_AT_AltC SQL         =   "ALTER TABLE " o
+                           " ALTER COLUMN " f " " SQL_type(st) " NULL" nl
            TERMINAL    =   SQL
            $nmSQL      =   $nmSQL SQL                                      :(RETURN)
*           SQL_A_ExecDirect(hStmt, SQL)                                    :F(SQLFail)
*           SQL_EndTranCommit()                                             :S(RETURN)F(SQLFail)
SQL_AT_AltC_End
*---------- ----------- --- ----------------------------------------------- ------------------------
            DEFINE('SQL_INSERT(nmSQL,x,o,level)SQL,f,has_city,i,n,st,t,v')  :(SQL_INSERT_End)
SQL_INSERT  IDENT(t(x), '{}')                                               :F(error)
            has_city    =   ( ?(o ? POS(0) 'CityGrid') TRUE
+                           , ?(o ? POS(0) 'Foursquare') TRUE
+                           , ?(o ? POS(0) 'Yelp') TRUE
+                           , ?(o ? POS(0) 'Geo') TRUE
+                           , FALSE
+                           )
*           SQL         =   SQL EQ(level, 1) 'DECLARE @id$ int' nl
            SQL         =   SQL "INSERT INTO " o " ("
            n           =   0
            i           =   0
SQL_INSERT1 i           =   LT(i, tK[0]) i + 1                              :F(SQL_INSERT2)
            n           =   (GT(level, 1) n + 1, GT(i, 1) n + 1)            :F(SQL_INSERT1)
            f           =   tK[i]
            SQL         =   SQL GT(n, 1) ", "
            SQL         =   SQL f "_id$"
*           SQL         =   SQL (DIFFER(f, o) f "_id$", "id$")
                                                                            :(SQL_INSERT1)
SQL_INSERT2 SQL         =   SQL EQ(level, 1) GT(n = n + 1, 1) ", "
            SQL         =   SQL EQ(level, 1) "topic_id$"
            SQL         =   SQL EQ(level, 1) EQ(has_city, TRUE) GT(n = n + 1, 1) ", "
            SQL         =   SQL EQ(level, 1) EQ(has_city, TRUE) "city_id$"
            i           =   0
SQL_INSERT3 i           =   LT(i, n(x)) i + 1                               :F(SQL_INSERT4)
            f           =   v(c(c(x)[i])[1])
            t           =   t(c(c(x)[i])[2])
            st          =   (DIFFER(tS[o][f]) tS[o][f], IDENT(t, 'Null'))   :F(error)
            (DIFFER(st) DIFFER(tTypes[st]))                                 :F(SQL_INSERT3)
            f           =   IDENT(f, 'primary') '[' f ']'
            f           =   IDENT(f, 'schema') '[' f ']'
            SQL         =   SQL ", " f                                      :(SQL_INSERT3)
SQL_INSERT4 SQL         =   SQL ")" nl
*           SQL         =   SQL EQ(level, 1) 'OUTPUT INSERTED.' o '_id$' nl
            SQL         =   SQL "VALUES ("
            n           =   0
            i           =   0
SQL_INSERT5 i           =   LT(i, tK[0]) i + 1                              :F(SQL_INSERT6)
            n           =   (GT(level, 1) n + 1, GT(i, 1) n + 1)            :F(SQL_INSERT5)
            f           =   tK[i]
            v           =   tK['$' f]
            SQL         =   SQL (GT(n, 1) ', ' v, v)                        :(SQL_INSERT5)
SQL_INSERT6 SQL         =   SQL EQ(level, 1) GT(n = n + 1, 1) ", "
            SQL         =   SQL EQ(level, 1) +iTopic
            SQL         =   SQL EQ(level, 1) EQ(has_city, TRUE) GT(n = n + 1, 1) ", "
            SQL         =   SQL EQ(level, 1) EQ(has_city, TRUE) +iCity
            i           =   0
SQL_INSERT7 i           =   LT(i, n(x)) i + 1                               :F(SQL_INSERT8)
            f           =   v(c(c(x)[i])[1])
            t           =   t(c(c(x)[i])[2])
            v           =   v(c(c(x)[i])[2])
            st          =   (DIFFER(tS[o][f]) tS[o][f], IDENT(t, 'Null'))   :F(error)
            (DIFFER(st) DIFFER(tTypes[st]))                                 :F(SQL_INSERT7)
            v           =   (   IDENT(t, 'Null')
+                           ,   IDENT(t, 'Bool') IDENT(v, 'true') TRUE
+                           ,   IDENT(t, 'Bool') IDENT(v, 'false') FALSE
+                           ,   v
+                           )
            SQL         =   SQL ', '
            SQL         =   SQL IDENT(t, 'Null') 'NULL'                     :S(SQL_INSERT7)
            SQL         =   SQL IDENT(st, 'bit') +v                         :S(SQL_INSERT7)
            SQL         =   SQL IDENT(st, 'tinyint') +v                     :S(SQL_INSERT7)
            SQL         =   SQL IDENT(st, 'smallint') +v                    :S(SQL_INSERT7)
            SQL         =   SQL IDENT(st, 'int') +v                         :S(SQL_INSERT7)
            SQL         =   SQL IDENT(st, 'bigint') v                       :S(SQL_INSERT7)
            SQL         =   SQL IDENT(st, 'real') v                         :S(SQL_INSERT7)
            SQL         =   SQL IDENT(st, 'datetime') "'" SqlSQize(v) "'"   :S(SQL_INSERT7)
            SQL         =   SQL IDENT(st, 'varchar') "'" SqlSQize(v) "'"    :S(SQL_INSERT7)
            SQL         =   SQL IDENT(st, 'nvarchar') "N'" SqlSQize(v) "'"  :S(SQL_INSERT7)
            TERMINAL    =   i ' ' f ' ' t ' ' st ' ' n ' "' v '"'           :(error)
SQL_INSERT8 SQL         =   SQL ')' nl
*           TERMINAL    =   SQL
*           hInsert     =   SQL_AllocStmt()                                 :F(SQLFail)
*           SQL_W_ExecDirect(hInsert, utf8_to_wstr(SQL))                    :F(FRETURN)
*           SQL_EndTranCommit()                                             :F(SQLFail)
            SQL         =   SQL EQ(level, 1) "SET @id$ = @@IDENTITY" nl     :F(SQL_INSERT9)
*           SQL_Fetch(hInsert)                                              :F(SQLFail)
*           tK['$' tK[1]] = SQL_GetData(hInsert, 1)                         :F(SQLFail)
SQL_INSERT9
*           SQL_FreeStmt(hInsert)                                           :S(RETURN)F(SQLFail)
            $nmSQL      =   $nmSQL SQL                                      :(RETURN)
SQL_INSERT_End
*---------- ----------- --- ----------------------------------------------- ------------------------
*-------------- ------------------- --- ------------------------------------------------------------
                &ALPHABET           ?   TAB(128) LEN(128) . non_ascii
                tS                  =   TABLE()
                tTypes              =   TABLE()
                tTypes['null']      =   0
                tTypes['bit']       =   1
                tTypes['tinyint']   =   2
                tTypes['smallint']  =   3
                tTypes['int']       =   4
                tTypes['bigint']    =   5
                tTypes['real']      =   6
                tTypes['datetime']  =   7
                tTypes['varchar']   =   8
                tTypes['nvarchar']  =   9
*-------------- ----------- --- ------------------------------------------- ------------------------
                DEFINE('Schema(nmSQL,x,o,p,level,is_first)'
+                   'cx1,cx2,st0,st1,f,i,ist0,ist1,s,svp,t,v'
+               ,   .Sch
+               )                                                           :(SchEnd)
Sch             Schema      =   Tack(p, o)
                x           =   IDENT(DATATYPE(x), 'NAME') $x
                cx1         =   (DIFFER(c(x)) c(x)[1], NULL)
                cx2         =   (DIFFER(c(x)) c(x)[2], NULL)
                v           =   v(x)
                t           =   DIFFER(t(x)) t(x)                           :S($('Sch_' t))F(error)
*               ----------- --- ------------------------------------------- ------------------------
Sch_JSON        Schema(nmSQL, c(x)[1], o, p, level + 1)                     :(RETURN)
*               ----------- --- ------------------------------------------- ------------------------
Sch_{}          is_first    =   (IDENT(tS[o]) TRUE, FALSE)
                tS[o]       =   EQ(is_first, TRUE) TABLE()
                i           =   0
Sch_{}3         i           =   LT(i, n(x)) i + 1                           :F($'Sch_{}5')
                Schema(nmSQL, c(x)[i], o, p, level + 1, is_first)           :($'Sch_{}3')
Sch_{}5         (EQ(is_first, TRUE) SQL_CREATE_TABLE(nmSQL, o, level))      :(RETURN)
*               ----------- --- ------------------------------------------- ------------------------
Sch_[]          i           =   0
Sch_[]3         i           =   LT(i, n(x)) i + 1                           :F(RETURN)
                tK[0]       =   tK[0] + 1
                tK[tK[0]]   =   o
                Schema(nmSQL, c(x)[i], o, p, level + 1)
                tK[tK[0]]   =
                tK[0]       =   tK[0] - 1                                   :($'Sch_[]3')
*               ----------- --- ------------------------------------------- ------------------------
Sch_:           f           =   Schema(nmSQL, cx1,,, level + 1)
                (DIFFER(t(cx2), '{}') DIFFER(t(cx2), '[]'))                 :F($'Sch_:3')
                st0         =   tS[o][f]
                st1         =   Schema(nmSQL, cx2,,, level + 1)
                ist0        =   tTypes[st0]
                ist1        =   tTypes[st1]
                (IDENT(ist1, 0))                                            :S(RETURN)
                (IDENT(st0))                                                :S($'Sch_:1')
                (IDENT(ist0, 0) DIFFER(ist1))                               :S($'Sch_:1')
                (DIFFER(ist0) DIFFER(ist1) GT(ist1, ist0))                  :S($'Sch_:2')
                (DIFFER(ist0) IDENT(ist1))                                  :S(SchError)
                (IDENT(ist0) DIFFER(ist1))                                  :S(SchError)
                (IDENT(ist0) IDENT(ist1) DIFFER(st0, st1))                  :S(SchError)F(RETURN)
Sch_:1          tS[o][f]    =   st1
                EQ(is_first, FALSE)                                         :F(RETURN)
                SQL_ALTER_TABLE_ADD_COLUMN(nmSQL, o, f, st1)                :(RETURN)
Sch_:2          tS[o][f]    =   st1
                EQ(is_first, FALSE)                                         :F(RETURN)
                SQL_ALTER_TABLE_ALTER_COLUMN(nmSQL, o, f, st1)              :(RETURN)
Sch_:3          tS[o][f]    =   Schema(nmSQL, cx2, Tack(o, f), Tack(p, o), level + 1) :(RETURN)
SchError        TERMINAL    =   'st0=' st0 ', st1=' st1
                TERMINAL    =   'ist0=' ist0 ', ist1=' ist1                 :(END)
*               ----------- --- ------------------------------------------- ------------------------
Sch_Bool        Schema      =   'bit'                                       :(RETURN)
Sch_Datetime    Schema      =   'datetime'                                  :(RETURN)
*               ----------- --- ------------------------------------------- ------------------------
Sch_Integer     INTEGER(v)                                                  :F(Sch_Integer64)
                Schema      =   GE(v, 0) LE(v, 1) 'bit'                     :S(RETURN)
                Schema      =   GE(v, 0) LE(v, 256) 'tinyint'               :S(RETURN)
                Schema      =   GE(v, -32768) LE(v, 32767) 'smallint'       :S(RETURN)
                Schema      =   'int'                                       :(RETURN)
Sch_Integer64   s           =   '+'
                v           ?   POS(0) ('+' . s | '-' . s | epsilon) =
                Schema      =   IDENT(s, '-')
+                               LE(SIZE(v), 19)
+                               LLE(LPAD(v, 19, 0), '9223372036854775808')
+                               'bigint'                                    :S(RETURN)
                Schema      =   IDENT(s, '+')
+                               LE(SIZE(v), 19)
+                               LLE(LPAD(v, 19, 0), '9223372036854775807')
+                               'bigint'                                    :S(RETURN)
                Schema      =   'varchar'                                   :(RETURN)
*               ----------- --- ------------------------------------------- ------------------------
Sch_Name        Schema      =   v                                           :(RETURN)
Sch_Null        Schema      =   'null'                                      :(RETURN)
Sch_Real        Schema      =   'real'                                      :(RETURN)
*               ----------- --- ------------------------------------------- ------------------------
Sch_String      Schema      =   ~(v ? ANY(non_ascii)) 'varchar'             :S(RETURN)
                Schema      =   'nvarchar'                                  :(RETURN)
SchEnd
*-------------- ----------- --- ------------------------------------------- ------------------------
                DEFINE('Save(nmSQL,x,o,level)i,t')                          :(SaveEnd)
Save            t           =   DIFFER(t(x)) t(x)                           :S($('Save_' t))F(error)
*               ----------- --- ------------------------------------------- ------------------------
Save_JSON       Save(nmSQL, c(x)[1], o, level + 1)                          :(RETURN)
*               ----------- --- ------------------------------------------- ------------------------
Save_{}         SQL_INSERT(nmSQL,x, o, level)
                i           =   0
Save_{}3        i           =   LT(i, n(x)) i + 1                           :F(RETURN)
                Save(nmSQL, c(x)[i], o, level + 1)                          :($'Save_{}3')
*               ----------- --- ------------------------------------------- ------------------------
Save_[]         tK[0]       =   tK[0] + 1
                tK[tK[0]]   =   o
                i           =   0
Save_[]3        i           =   LT(i, n(x)) i + 1                           :F($'Save_[]5')
                tK['$' o]   =   i
                Save(nmSQL, c(x)[i], o, level + 1)                          :($'Save_[]3')
Save_[]5        tK['$' o]   =
                tK[tK[0]]   =
                tK[0]       =   tK[0] - 1                                   :(RETURN)
*               ----------- --- ------------------------------------------- ------------------------
Save_:          Save(nmSQL, c(x)[2], o '_' v(c(x)[1]), level + 1)           :(RETURN)
*               ----------- --- ------------------------------------------- ------------------------
Save_Bool
Save_Datetime
Save_Integer
Save_Name
Save_Null
Save_Real
Save_String                                                                 :(RETURN)
SaveEnd
*-------------- ----------- --- ------------------------------------------- ------------------------
