*---------------------------------------------------------------------------------------------------
               DEFINE('export_table(tbl,keyname,name,expression)i,tblArr')          :(export_table_end)
export_table   tblArr         =    SORT(tbl, 1)                                     :F(FRETURN)
export_table1  i              =    i + 1
               $keyname       =    tblArr[i, 1]                                     :F(RETURN)
               $name          =    tblArr[i, 2]
               export_table   =    export_table EVAL(expression)                    :(export_table1)
export_table_end
*---------------------------------------------------------------------------------------------------
               DEFINE('export_list(lst,name,expression)')                           :(export_list_end)
export_list    lst            POS(0) *ident . $name (',' | RPOS(0)) =               :F(RETURN)
               export_list    =    export_list EVAL(expression)                     :(export_list)
export_list_end
