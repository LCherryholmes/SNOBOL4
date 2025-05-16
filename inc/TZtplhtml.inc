   DEFINE('UserDefs()') :(UserDefsEnd)

UserDefs

   u   = 0
   usr = ARRAY('1:32')
   u = u + 1; usr[u] = token(, *('*insertBreak'), *insertBreak, *('InsertBreak();'))
   u = u + 1; usr[u] = token(, *('*refCountInc'), *refCountInc, *('IncRefCount(' aaa ', ' bbb ', ' ccc ', "' ddd '");'))
   u = u + 1; usr[u] = token(, *('*depCountInc'), *depCountInc, *('IncDepCount(' aaa ', ' bbb ', ' ccc ', "' ddd '");'))
   u = u + 1; usr[u] = token(, *('*Function1'),   *function1,   *('Function1(' aaa ', ' bbb ', ' ccc ');'))
   u = u + 1; usr[u] = token(, *('*Function2'),   *function2,   *('Function2();'))
   u = u + 1; usr[u] = token(, *('*Function3'),   *function3,   *('Function3("' aaa '", "' bbb '");'))
   u = u + 1; usr[u] = token(, *('*Function4'),   *function4,   *('Function4(' aaa ', ' bbb ', ' ccc ', ' ddd ', ' eee ');'))
   u = u + 1; usr[u] = token(, *('*Function5'),   *function5,   *('Function5(' aaa ', ' bbb ', ' ccc ', ' ddd ');'))
   u = u + 1; usr[u] = token(, *('*Function6'),   *function6,   *('Function6();'))
   u = u + 1; usr[u] = token(, *('*Function7'),   *function7,   *('Function7(' aaa ', ' bbb ', ' ccc ', ' ddd ', ' eee ');'))
   u = u + 1; usr[u] = token(, *('*Function8'),   *function8,   *('Function8(' ');'))
   u = u + 1; usr[u] = token(, *('*Function9'),   *function9,   *('Function9(' ');'))
   u = u + 1; usr[u] = token(, *('*Function10'),  *function10,  *('Function10(' ');'))
   u = u + 1; usr[u] = token(, *('*Function11'),  *function11,  *('Function11(' ');'))
   u = u + 1; usr[u] = token(, *('*Function12'),  *function12,  *('Function12("' aaa '");'))
   u = u + 1; usr[u] = token(, *('*Function13'),  *function13,  *('Function13(' ');'))
   u = u + 1; usr[u] = token(, *('*Function14'),  *function14,  *('Function14(' ');'))

   keyint         =   ('0' | '1' | '5') . tx
   keyword        =
+                 (   'break'
+                 |   'depCount'
+                 |   'dummy'
+                 |   'dumpAttr'
+                 |   'else'
+                 |   'for'
+                 |   'getAttr'
+                 |   'getNewAttr'
+                 |   'getObjName'
+                 |   'getOldAttr'
+                 |   'if'
+                 |   'isImpact'
+                 |   'nextObj'
+                 |   'objExternalType'
+                 |   'objState'
+                 |   'output'
+                 |   'refCount'
+                 |   'rowCount'
+                 |   'setObj'
+                 |   's'
+                 |   'tplCnt'
+                 |   'Var'
+                 |   'IncRefCount'
+                 |   'IncDepCount'
+                 |   'InsertBreak'
+                 |   'include'
+                 |   'return'
+                 |   'Function' *intx
+                 ) . tx

   extra          =   *relship                  epsilon . *assign(.tx, '*relship')
+                 |   *objintname               epsilon . *assign(.tx, '*objintname')
+                 |   '"<!-- ' *objextname ' "' epsilon . *assign(.tx, "'"  '"'  "<!-- ' *objextname ' "  '"' "'")

*---------------------------------------------------------------------------------------
   relship        =   ('"Owns"' | '"owns"' | '"ReferedToBy"' | '"ReferedToBY"' | '"HasComponent"' | '"Contains"' | '"contains"')
   objintname     =   '"-' *idx '"'
   objextname     =   ('-' | epsilon) *idx (ANY(' -') *idx (' ' *idx | '') | '') (' time' | epsilon)

*---------------------------------------------------------------------------------------
    declVar       =   $' ' 'Var' *id $';'
    declVars      =   *declVar (*declVars | epsilon)

    refCountInit  =        'refCount' $'=' *int $';'
    refCountInc   =        'dummy' $'=' $' ' 'setObj' $'(' $')' $';'
+                     $' ' 'tplCnt' $'=' $' '
+                          'setObj' $'(' $' ' *relship . aaa $',' $' ' *objintname . bbb ($',' *dqc . ccc | epsilon . *assign(.ccc, '""')) $')' $';'
+                     $' ' 'refCount' $'=' $' ' 'tplCnt' $'+' $' ' 'refCount' $';'
+                     $' ' 'output' $'(' $' ' '"<!-- ' *objextname . ddd ' "' $'|' $' ' 'tplCnt' $'|' $' ' '" -->"' $')' $';'
    refCountIncs  =   $' ' *refCountInc (*refCountIncs | epsilon)

    depCountInit  =        'depCount' $'=' *int $';'
    depCountInc   =        'dummy' $'=' $' ' 'setObj' $'(' $')' $';'
+                     $' ' 'tplCnt' $'=' $' '
+                          'setObj' $'(' $' ' *relship . aaa $',' $' ' *objintname . bbb ($',' *dqc . ccc | epsilon . *assign(.ccc, '""')) $')' $';'
+                     $' ' 'depCount' $'=' $' ' 'tplCnt' $'+' $' ' 'depCount' $';'
+                     $' ' 'output' $'(' $' ' '"<!-- ' *objextname . ddd ' "' $'|' $' ' 'tplCnt' $'|' $' ' '" -->"' $')' $';'
    depCountIncs  =   $' ' *depCountInc (*depCountIncs | epsilon)

    insertBreak =
+        'if' $'(' $' ' 'rowCount' $'==' *int $')'
+   $'{'
+   $' ' 'rowCount' $'=' *int $';'
+   $' ' 'output' $'(' $' ' '"<!-- Insert a break after every fifth entry -->"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<TR>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<TD VALIGN=TOP COLSPAN=2>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<IMG SRC=\"../images/dot_cler.gif\" WIDTH=1 HEIGHT=5 BORDER=0>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"</TD>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"</TR>"' $')' $';'
+   $'}'

    function1 =
+        'output' $'(' $' ' '"<!-- "' $'|' $' ' 's' $'(' *id . aaa $',' *id . bbb $')' $'|' $' ' '" -->"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<TD VALIGN=TOP ALIGN=CENTER>' ('0' . ccc | '"' $'|' $' ' *id . ccc $'|' $' ' '"') ' </TD>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<TD WIDTH=\"70%\" VALIGN=TOP>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<P>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<TABLE CELLPADDING=10 CELLSPACING=0 WIDTH=\"100%\" BORDER=1 BGCOLOR=\"#FFFFFF\">"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<TR>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '<TD VALIGN=\"TOP\">"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<!-- Table framing ref objects -->"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<TABLE BORDER=0 WIDTH=\"360\" CELLSPACING=\"3\">"' $')' $';'

    function2 =
+        'output' $'(' $' ' '"<TR>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '<TD><IMG SRC=\"../images/dot_cler.gif\" WIDTH=1 HEIGHT=5 BORDER=0>' $'  ' '</TD>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"</TR>"' $')' $';'

    function3 =
+        'output' $'(' $' ' '"<!-- "' $'|' $' ' 'objExternalType' $'(' $')' $'|' $' ' '" -->"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<TR>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '<TD WIDTH=\"7%\"' $'  ' 'VALIGN=\"TOP\">'
+        (  '<A HREF=\"' *id . aaa '."' $'|' $' ' 'getObjName' $'(' $' ' '"N"' $')' $'|' $' ' '"a.htm\">'
+           '<IMG SRC=\"../images/"' $'|' *id $'|' $' ' '"  "' $'|' $' ' 'getObjName' $'(' $' ' '"N"' $')' $'|' $' ' '"\">'
+           '</A>'
+        |  '<IMG SRC=\"../images/"' $'|' *id $'|' $' ' '"  "' $'|' $' ' 'getObjName' $'(' $' ' '"N"' $')' $'|' $' ' '"\">'
+        ) $'  ' '</TD>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '<TD VALIGN=\"TOP\">'
+        (  '<A HREF=\"' *id . bbb '."'
+           $'|' $' ' 'getObjName' $'(' $' ' '"N"' $')' $'|' $' ' '"a.htm\">"' $'|' $' ' 'getObjName' $'(' $' ' '"N"' $')' $'|' $' ' '"'
+           '</A>'
+        |  '"' $'|' $' ' 'getObjName' $'(' $' ' '"N"' $')' $'|' $' ' '"'
+        ) $'  ' '</TD>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"</TR>"' $')' $';'

    function4 =
+        'dummy' $'=' $' ' 'setObj' $'(' $')' $';'
+   $' ' 'tplCnt' $'=' $' ' 'setObj' $'(' $' ' *relship . aaa $',' $' ' *objintname . bbb ($',' *dqc . ccc | epsilon . *assign(.ccc, '""')) $')' $';'
+   $' ' 'if' $'(' $' ' 'tplCnt' $'>' *int . ddd $')'
+   $'{'
+   $' ' 'for' $'(' $';' $';' $')'
+   $'{'
+   $' ' 'if' $'(' $'!' $'(' $' ' 'objState' $'(' $')' $'==' $' ' '"DELETED"' $'||' $' ' 'isImpact' $'(' $' ' '"Dead"' $')' $')' $')'
+   $'{'
+   $' ' 'rowCount' $'=' $' ' 'rowCount' $'+' *int . eee $';'
+   $' ' 'Function3' $'(' *dqc $',' *dqc $')' $';'
+   $' ' 'InsertBreak' $'(' $')' $';'
+   $'}'
+   $' ' 'if' $'(' $'!' $' ' 'nextObj' $'(' $')' $')'
+   $'{'
+   $' ' 'break' $';'
+   $'}'
+   $'}'
+   $'}'

    function5 =
+        'if' $'(' $' ' 'tplCnt' $'>' *int . ccc $')'
+   $'{'
+   $' ' 'for' $'(' $';' $';' $')'
+   $'{'
+   $' ' 'if' $'(' $'!' $'(' $' ' 'objState' $'(' $')' $'==' $' ' '"DELETED"' $'||' $' ' 'isImpact' $'(' $' ' '"Dead"' $')' $')' $')'
+   $'{'
+   $' ' 'rowCount' $'=' $' ' 'rowCount' $'+' *int . ddd $';'
+   $' ' 'Function3' $'(' *dqc $',' *dqc $')' $';'
+   $' ' 'InsertBreak' $'(' $')' $';'
+   $'}'
+   $' ' 'if' $'(' $'!' $' ' 'nextObj' $'(' $')' $')'
+   $'{'
+   $' ' 'break' $';'
+   $'}'
+   $'}'
+   $'}'

    function6 =
+        'output' $'(' $' ' '"</TABLE>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<!-- End table framing ref objects -->"' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '</TD>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"</TR>"' $')' $';'

    function7 =
+        'output' $'(' $' ' '"</TABLE>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '</TD>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<TR>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<TD' $'  ' 'VALIGN=TOP ALIGN=CENTER>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<FONT SIZE=\"-1\" FACE=\"ARIAL, HELVETICA, TIMES ROMAN\"><B>"' $'|' $' ' 's' $'(' *id . aaa $',' *id . bbb $')' $'|' $' ' '"</B></FONT>' $'  ' '</TD>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<TD' $'  ' 'VALIGN=\"TOP\">"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<TABLE BORDER=0>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<TR>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '<TD' $'  ' 'VALIGN=\"TOP\"><IMG SRC=\"../images/' ('tbl.gif\" WIDTH=16 HEIGHT=13 BORDER=0>' | '"' $'|' *id . ccc $'|' $' ' '"' $'  ' '"' $'|' $' ' 'getObjName' $'(' $' ' '"N"' $')' $'|' $' ' '"\">') $'  ' '</TD>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '<TD' $'  ' 'VALIGN=\"TOP\"><FONT SIZE=\"-1\" FACE=\"ARIAL, HELVETICA, TIMES ROMAN\"><B>"' $'|' $' ' 'getObjName' $'(' $' ' '"N"' $')' $'|' $' ' '"' $'  ' '"' $'|' $' ' 's' $'(' *id . ddd $',' *id . eee $')' $'|' $' ' '"&#58;</B></FONT>' $'  ' '</TD>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"</TR>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"</TABLE>' $'  ' '"' $')' $';'
+   $' ' 'output' $'(' $' ' '"</TD>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"</TR>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<TR>"' $')' $';'

    function8 =
+        'if' $'(' *id $'==' $' ' 1 $')'
+   $'{'
+   $' ' 'output' $'(' $' ' '"<!--*begin file:dbobject\\' *id '.htm -->"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<!-- Header: this page serves as an check object browser launch pad. -->"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 3.2//EN\">"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<HTML>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<HEAD>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '<TITLE>"' $'|' $' ' 's' $'(' *id $',' *id $')' $'|' $' ' '"</TITLE>"' $')' $';'
+   ($' ' 'output' $'(' $' ' '"' $'  ' '"' $')' $';' | epsilon)
+   $' ' 'output' $'(' $' ' '"<LINK REL=\"stylesheet\" HREF=\"../common/reports.css\" TYPE=\"text/css\">"' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '"' $')' $';'
+   $' ' 'output' $'(' $' ' '"</HEAD>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<BODY BGCOLOR=\"#006699\" LINK=\"#005580\" VLINK=\"#003964\" ALINK=\"#188080\">"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<A NAME=\"top\"></A>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<TABLE BORDER=\"0\" CELLPADDING=\"0\" CELLSPACING=\"0\">"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<TR>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<TD VALIGN=\"TOP\" NOWRAP>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '<SPAN CLASS=\"head\">"' $'|' $' ' 's' $'(' *id $',' *id $')' $'|' $' ' '"</SPAN> <IMG SRC=\"../images/dot_cler.gif\" WIDTH=\"40\" HEIGHT=\"1\">"' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '<A CLASS=\"menu\" HREF=\"indexdb.htm\" TARGET=\"_top\">"' $'|' $' ' 's' $'(' *id $',' *id $')' $'|' $' ' '"</A>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '<BR>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '<IMG SRC=\"../images/2_h_red.gif\" WIDTH=25 HEIGHT=50 BORDER=0>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '<IMG SRC=\"../images/dot_cler.gif\" WIDTH=\"90\" HEIGHT=\"1\" BORDER=0>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '"' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '<A CLASS=\"menu\" HREF=\"indexdb.htm\" TARGET=\"_top\">"' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '<IMG SRC=\"../images/2_h_objc.gif\" WIDTH=\"65\" HEIGHT=\"50\" BORDER=\"0\" ALT=\""' $'|' $' ' 's' $'(' *id $',' *id $')' $'|' $' ' '"\"></A>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '</TD>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '"' $')' $';'
+   $' ' 'output' $'(' $' ' '"</TR>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<TR>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<TD VALIGN=\"TOP\">"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<B><FONT COLOR=\"#FFFFFF\" FACE=\"ARIAL, HELVETICA, TIMES ROMAN\" SIZE=\"-1\">"' $'|' $' ' 's' $'(' *id $',' *id $')' $'|' $' ' '"</FONT></B>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<TABLE BORDER=1 CELLPADDING=0 CELLSPACING=0  BGCOLOR=\"#FFFFFF\">"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<TR>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<TD VALIGN=TOP>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<TABLE BORDER=0 CELLPADDING=5>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<!--*end file:dbobject\\' *id '.htm -->"' $')' $';'
+   $'}'

    function9 =
+        'output' $'(' $' ' '"<!--*begin file:dbobject\\' *id '.htm -->"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<!-- Appended list item -->"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<TR>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<!-- Object State -->"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<TD NOWRAP>"' $')' $';'
+   $' ' 'if' $'(' $' ' 'objState' $'(' $')' $'==' $' ' '"ADDED"' $')'
+   $'{'
+  ($' ' 'output' $'(' $' ' '"' $'  ' '"' $')' $';' | epsilon)
+   $' ' 'output' $'(' $' ' '"' $'  ' '<IMG SRC=\"../images/"' $'|' *id $'|' $' ' '"\"> <FONT SIZE=\"-1\" FACE=\"ARIAL, HELVETICA, TIMES ROMAN\"><B>"' $'|' $' ' 's' $'(' *id $',' *id $')' $'|' $' ' '"</B></FONT>"' $')' $';'
+  ($' ' 'output' $'(' $' ' '"' $'  ' '"' $')' $';' | epsilon)
+   $'}'
+   $' ' 'else' $' ' 'if' $'(' $' ' 'objState' $'(' $')' $'==' $' ' '"DELETED"' $')'
+   $'{'
+  ($' ' 'output' $'(' $' ' '"' $'  ' '"' $')' $';' | epsilon)
+   $' ' 'output' $'(' $' ' '"' $'  ' '<IMG SRC=\"../images/"' $'|' *id $'|' $' ' '"\"> <FONT SIZE=\"-1\" FACE=\"ARIAL, HELVETICA, TIMES ROMAN\"><B>v(idstDrop)</B></FONT>"' $')' $';'
+  ($' ' 'output' $'(' $' ' '"' $'  ' '"' $')' $';' | epsilon)
+   $'}'
+   $' ' 'else' $' ' 'if' $'(' $' ' 'objState' $'(' $')' $'==' $' ' '"MODIFIED"' $')'
+   $'{'
+  ($' ' 'output' $'(' $' ' '"' $'  ' '"' $')' $';' | epsilon)
+   $' ' 'output' $'(' $' ' '"' $'  ' '<IMG SRC=\"../images/"' $'|' *id $'|' $' ' '"\"> <FONT SIZE=\"-1\" FACE=\"ARIAL, HELVETICA, TIMES ROMAN\"><B>"' $'|' $' ' 's' $'(' *id $',' *id $')' $'|' $' ' '"</B></FONT>"' $')' $';'
+  ($' ' 'output' $'(' $' ' '"' $'  ' '"' $')' $';' | epsilon)
+   $'}'
+   $' ' 'else' $' ' 'if' $'(' $' ' 'objState' $'(' $')' $'==' $' ' '"MOVED"' $')'
+   $'{'
+  ($' ' 'output' $'(' $' ' '"' $'  ' '"' $')' $';' | epsilon)
+   $' ' 'output' $'(' $' ' '"' $'  ' '<IMG SRC=\"../images/"' $'|' *id $'|' $' ' '"\"> <FONT SIZE=\"-1\" FACE=\"ARIAL, HELVETICA, TIMES ROMAN\"><B>"' $'|' $' ' 's' $'(' *id $',' *id $')' $'|' $' ' '"</B></FONT>"' $')' $';'
+  ($' ' 'output' $'(' $' ' '"' $'  ' '"' $')' $';' | epsilon)
+   $'}'
+   $' ' 'else' $' ' 'if' $'(' $' ' 'objState' $'(' $')' $'==' $' ' '"REBUILT"' $')'
+   $'{'
+  ($' ' 'output' $'(' $' ' '"' $'  ' '"' $')' $';' | epsilon)
+   $' ' 'output' $'(' $' ' '"' $'  ' '<IMG SRC=\"../images/"' $'|' *id $'|' $' ' '"\"> <FONT SIZE=\"-1\" FACE=\"ARIAL, HELVETICA, TIMES ROMAN\"><B>"' $'|' $' ' 's' $'(' *id $',' *id $')' $'|' $' ' '"</B></FONT>"' $')' $';'
+  ($' ' 'output' $'(' $' ' '"' $'  ' '"' $')' $';' | epsilon)
+   $'}'
+   $' ' 'else' $' ' 'if' $'(' $' ' 'objState' $'(' $')' $'==' $' ' '"RECOMPILED"' $')'
+   $'{'
+  ($' ' 'output' $'(' $' ' '"' $'  ' '"' $')' $';' | epsilon)
+   $' ' 'output' $'(' $' ' '"' $'  ' '<IMG SRC=\"../images/"' $'|' *id $'|' $' ' '"\"> <FONT SIZE=\"-1\" FACE=\"ARIAL, HELVETICA, TIMES ROMAN\"><B>"' $'|' $' ' 's' $'(' *id $',' *id $')' $'|' $' ' '"</B></FONT>"' $')' $';'
+  ($' ' 'output' $'(' $' ' '"' $'  ' '"' $')' $';' | epsilon)
+   $'}'
+   $' ' 'else'
+   $'{'
+   $' ' 'output' $'(' $' ' '"' $'  ' '<IMG SRC=\"../images/dot_cler.gif\" WIDTH=1 HEIGHT=5 BORDER=0>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '"' $')' $';'
+   $'}'
+   $' ' 'output' $'(' $' ' '"</TD>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<TD>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '<A HREF=\"' *id '."' $'|' $' ' 'getObjName' $'(' $' ' '"N"' $')' $'|' $' ' '"a.htm\" TARGET=\"dataview\"><IMG SRC=\"../images/"' $'|' *id $'|' $' ' '"  "' $'|' $' ' 'getObjName' $'(' $' ' '"N"' $')' $'|' $' ' '"\"></A>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"</TD>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<TD VALIGN=TOP>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '<A HREF=\"' *id '."' $'|' $' ' 'getObjName' $'(' $' ' '"N"' $')' $'|' $' ' '"a.htm\" TARGET=\"dataview\"><FONT FACE=\"ARIAL, HELVETICA, TIMES ROMAN\" SIZE=\"-1\">"' $'|' $' ' 'getObjName' $'(' $' ' '"N"' $')' $'|' $' ' '"</FONT></A>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"</TD>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"</TR>"' $')' $';'
+   $' ' 'if' $'(' *id $'==' $' ' 5 $')'
+   $'{'
+   *id $'=' $' ' 0 $';'
+   $' ' 'output' $'(' $' ' '"<!-- Insert a break after every fifth entry -->"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<TR>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<TD VALIGN=TOP COLSPAN=3>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<IMG SRC=\"../images/dot_cler.gif\" WIDTH=1 HEIGHT=5 BORDER=0>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"</TD>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"</TR>"' $')' $';'
+   $'}'
+   $' ' 'output' $'(' $' ' '"<!--*end file:dbobject\\' *id '.htm -->"' $')' $';'

    function10 =
+        'output' $'(' $' ' '"<!-- begin file:dbobject\\chk."' $'|' $' ' 'getObjName' $'(' $' ' '"N"' $')' $'|' $' ' '"a.htm -->"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<!-- This page is for data browsing. -->"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<!-- Template: Oracle check, structure. -->"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 3.2//EN\">"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<HTML>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<HEAD>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '<TITLE><H4>"' $'|' $' ' 's' $'(' *id $',' *id $')' $'|' $' ' '" - "' $'|' *id $'|' $' ' '" - "' $'|' $' ' 'getObjName' $'(' $' ' '"N"' $')' $'|' $' ' '"</H4></TITLE>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"</HEAD>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<BODY BGCOLOR=\"#FFFFFF\">"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<!-- Object heading includes type, database name, and object name. -->"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<CENTER>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<FONT FACE=\"ARIAL, HELVETICA, TIMES ROMAN\"><H4>"' $'|' $' ' 's' $'(' *id $',' *id $')' $'|' $' ' '" - "' $'|' *id $'|' $' ' '" - "' $'|' $' ' 'getObjName' $'(' $' ' '"N"' $')' $'|' $' ' '"</H4></FONT>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<FORM METHOD=\"POST\">"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<TABLE WIDTH=\"100%\" BORDER=0 CELLPADDING=\"5\" CELLSPACING=\"0\" BGCOLOR=\"#CCCCCC\">"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<!-- Begin tab buttons -->"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<TR>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '<TD ALIGN=\"CENTER\" BGCOLOR=\"#CCCCCC\"><FONT FACE=\"ARIAL, HELVETICA, TIMES ROMAN\"><B>"' $'|' $' ' 's' $'(' *id $',' *id $')' $'|' $' ' '"</B></FONT> </TD>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '<TD ALIGN=\"CENTER\" BGCOLOR=\"#FFFFFF\">"' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '<INPUT TYPE=\"button\" NAME=\"dependencies\" VALUE=\""' $'|' $' ' 's' $'(' *id $',' *id $')' $'|' $' ' '"\" ONCLICK=\"window.open(' "'" 'chk."' $'|' $' ' 'getObjName' $'(' $' ' '"N"' $')' $'|' $' ' '"b.htm' "'" ',' "'" '_self' "'" ',' "'" 'toolbar=1,location=1,status=1,menubar=1,scrollbars=1,resizable=1,personal=1' "'" ');\"> </TD>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"</TR>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<TR>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<!-- End tab buttons -->"' $')' $';'

    function11 =
+        'output' $'(' $' ' '"<!-- Add new information before this line. Data browser footer starts here. -->"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<!-- End data formatting table -->"' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '</TD>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"</TR>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"</TABLE>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<!-- End thin border line -->"' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '</TD>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"</TR>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"</TABLE>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<!-- End gray page area -->"' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '</TD>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"</TR>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"</TABLE>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<!-- Logos and Footer -->"' $')' $';'
+   $' ' 'output' $'(' $' ' '"</FORM>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"</CENTER>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<P>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<TABLE ALIGN=\"LEFT\" BORDER=0 CELLSPACING=0 CELLPADDING=0 WIDTH=\"425\">"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<TR>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '<TD VALIGN=\"TOP\" ROWSPAN=\"5\"><IMG SRC=\"../images/dot_cler.gif\" WIDTH=15 HEIGHT=1 BORDER=0> </TD>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '<TD ALIGN=\"CENTER\" VALIGN=\"top\"  WIDTH=400 HEIGHT=\"10\"><P><FONT SIZE=1 FACE=\"ARIAL, HELVETICA, TIMES ROMAN\"><A HREF=\"indexdb.htm\" TARGET=\"_top\">"' $'|' $' ' 's' $'(' *id $',' *id $')' $'|' $' ' '"</A> | "' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '<A HREF=\"../index.htm\" TARGET=\"_top\">"' $'|' $' ' 's' $'(' *id $',' *id $')' $'|' $' ' '"</A> | "' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '<A HREF=\"#\" ONCLICK=\"window.open(' "'" '../images/indexhlp.htm' "'" ',' "'" 'AboutWin' "'" ',' "'" 'toolbar,location,scrollbars,resizable,height=400,width=640' "'" ');\">"' $'|' $' ' 's' $'(' *id $',' *id $')' $'|' $' ' '"</A>  "' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '</FONT> </TD>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"</TR>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<TR>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '<TD ALIGN=\"CENTER\" VALIGN=\"top\"  WIDTH=425><FONT SIZE=1 FACE=\"ARIAL, HELVETICA, TIMES ROMAN\">"' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '<A HREF=\"#\" ONCLICK=\"window.open(' "'" 'http://www.bmc.com/'         "'" ',' "'" 'AboutWin' "'" ',' "'" 'toolbar,location,scrollbars,resizable,height=400,width=640' "'" ');\">"' $'|' $' ' 's' $'(' *id $',' *id $')' $'|' $' ' '"</A> | "' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '<A HREF=\"#\" ONCLICK=\"window.open(' "'" 'http://www.bmc.com/support/' "'" ',' "'" 'AboutWin' "'" ',' "'" 'toolbar,location,scrollbars,resizable,height=400,width=640' "'" ');\">"' $'|' $' ' 's' $'(' *id $',' *id $')' $'|' $' ' '"</A> | "' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '<A HREF=\"#\" ONCLICK=\"window.open(' "'" 'http://www.bmc.com/'         "'" ',' "'" 'AboutWin' "'" ',' "'" 'toolbar,location,scrollbars,resizable,height=400,width=640' "'" ');\">"' $'|' $' ' 's' $'(' *id $',' *id $')' $'|' $' ' '"</A></FONT> </TD>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"</TR>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<TR>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '<TD ALIGN=\"left\" VALIGN=\"top\">"' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '<BR>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '<FONT SIZE=1 FACE=\"ARIAL, HELVETICA, TIMES ROMAN\">"' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '"' $'|' $' ' 's' $'(' *id $',' *id $')' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '</FONT> </TD>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"</TR>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<TR>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '<TD ALIGN=\"left\" VALIGN=\"top\">"' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '<FONT SIZE=1 FACE=\"ARIAL, HELVETICA, TIMES ROMAN\">"' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '"' $'|' $' ' 's' $'(' *id $',' *id $')' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '</FONT></TD>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"</TR>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<TR>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '<TD ALIGN=\"left\" VALIGN=\"top\">"' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '<FONT SIZE=2 FACE=\"ARIAL, HELVETICA, TIMES ROMAN\"><B>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '"' $'|' $' ' 's' $'(' *id $',' *id $')' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '</B></FONT></TD>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"</TR>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"</TABLE>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"</BODY>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"</HTML>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<!-- end file:dbobject\\chk."' $'|' $' ' 'getObjName' $'(' $' ' '"N"' $')' $'|' $' ' '"a.htm -->"' $')' $';'

    function12 =
+        'output' $'(' $' ' '"<!-- ' *id . aaa ' -->"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<TD' (' WIDTH=\"50%\"' | ' NOWRAP' | ' COLSPAN=' *intx | epsilon) ' VALIGN=\"TOP\"><FONT SIZE=\"-1\" FACE=\"ARIAL, HELVETICA, TIMES ROMAN\"><B>"' $'|' $' ' 's' $'(' *id $',' *id $')' $')' $';'
+   $' ' 'if' $'(' $' ' 'getOldAttr' $'(' $' ' '"' *id '"' $')' $'!' $'=' $' ' 'getNewAttr' $'(' $' ' '"' *id '"' $')' $')'
+   $'{'
+   $' ' 'output' $'(' $' ' '"<FONT COLOR=\"#006699\">*</FONT>"' $')' $';'
+   $'}'
+   $' ' 'output' $'(' $' ' '"</B></FONT><BR>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<INPUT TYPE=\"hidden\" NAME=\"' *id '\" SIZE=\"' *intx '\" VALUE=\"' *id '\">"' $'|' $' ' 'getNewAttr' $'(' $' ' '"' *id '"' $')' $')' $';'
+   $' ' 'if' $'(' $' ' 'getOldAttr' $'(' $' ' '"' *id '"' $')' $'!' $'=' $' ' 'getNewAttr' $'(' $' ' '"' *id '"' $')' $')'
+   $'{'
+   $' ' 'output' $'(' $' ' '"<I><FONT COLOR=\"#006699\">("' $'|' $' ' 'getOldAttr' $'(' $' ' '"' *id '"' $')' $'|' $' ' '")</FONT></I>"' $')' $';'
+   $'}'
+   $' ' 'output' $'(' $' ' '"' $'  ' '</TD>"' $')' $';'

    function13 =
+        'output' $'(' $' ' '"<!-- ' *id . aaa ' -->"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<TD VALIGN=\"TOP\">"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<FONT SIZE=\"-1\" FACE=\"ARIAL, HELVETICA, TIMES ROMAN\"><B>"' $'|' $' ' 's' $'(' *id $',' *id $')' $')' $';'
+   $' ' 'if' $'(' $' ' 'getOldAttr' $'(' $' ' '"' *id '"' $')' $'!' $'=' $' ' 'getNewAttr' $'(' $' ' '"' *id '"' $')' $')'
+   $'{'
+   $' ' 'output' $'(' $' ' '"<FONT COLOR=\"#006699\">*</FONT>"' $')' $';'
+   $'}'
+   $' ' 'output' $'(' $' ' '"</B></FONT><BR>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<INPUT TYPE=\"hidden\" NAME=\"' *id '\" SIZE=\"35\" VALUE=\"' *id '\">"' $'|' $' ' 'getNewAttr' $'(' $' ' '"' *id '"' $')' $')' $';'
+   $' ' 'if' $'(' $' ' 'getOldAttr' $'(' $' ' '"' *id '"' $')' $'!' $'=' $' ' 'getNewAttr' $'(' $' ' '"' *id '"' $')' $')'
+   $'{'
+   $' ' 'output' $'(' $' ' '"<I><FONT COLOR=\"#006699\">("' $'|' $' ' 'getOldAttr' $'(' $' ' '"' *id '"' $')' $'|' $' ' '")</FONT></I>"' $')' $';'
+   $'}'
+   $' ' 'output' $'(' $' ' '"<BR>"' $')' $';'
+   $' ' 'if' $'(' $' ' 'getNewAttr' $'(' $' ' '"STATUS"' $')' $'==' $' ' '"DISABLED"' $')'
+   $'{'
+   $' ' 'output' $'(' $' ' '"<INPUT TYPE=\"CHECKBOX\" NAME=\"STATUS\" VALUE=\"STATUS\">"' $')' $';'
+   $'}'
+   $' ' 'else'
+   $'{'
+   $' ' 'output' $'(' $' ' '"<INPUT TYPE=\"CHECKBOX\" CHECKED NAME=\"STATUS\" VALUE=\"STATUS\"> "' $')' $';'
+   $'}'
+   $' ' 'output' $'(' $' ' '"<FONT SIZE=\"-1\" FACE=\"ARIAL, HELVETICA, TIMES ROMAN\"><B>"' $'|' $' ' 's' $'(' *id $',' *id $')' $')' $';'
+   $' ' 'if' $'(' $' ' 'getOldAttr' $'(' $' ' '"STATUS"' $')' $'!' $'=' $' ' 'getNewAttr' $'(' $' ' '"STATUS"' $')' $')'
+   $'{'
+   $' ' 'output' $'(' $' ' '"<FONT COLOR=\"#006699\">*</FONT>"' $')' $';'
+   $'}'
+   $' ' 'output' $'(' $' ' '"</B></FONT>"' $')' $';'
+   $' ' 'output' $'(' $' ' '"' $'  ' '</TD>"' $')' $';'

    function14 =
+   $' ' 'output' $'(' $' ' '"<!-- ' *id ' -->"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<TD VALIGN=\"TOP\">"' $')' $';'
+   $' ' 'if' $'(' $' ' 'getNewAttr' $'(' $' ' '"' *id '"' $')' $'==' $' ' '"VALID"' $')'
+   $'{'
+   $' ' 'output' $'(' $' ' '"<!-- ' *id ' -->"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<INPUT TYPE=\"checkbox\" CHECKED NAME=\"' *id '\" VALUE=\"' *id '\"> "' $')' $';'
+   $'}'
+   $' ' 'else'
+   $'{'
+   $' ' 'output' $'(' $' ' '"<!-- ' *id ' -->"' $')' $';'
+   $' ' 'output' $'(' $' ' '"<INPUT TYPE=\"checkbox\" NAME=\"' *id '\" VALUE=\"' *id '\"> "' $')' $';'
+   $'}'
+   $' ' 'output' $'(' $' ' '"<B>"' $'|' $' ' 's' $'(' *id $',' *id $')' $')' $';'
+   $' ' 'if' $'(' $' ' 'getOldAttr' $'(' $' ' '"' *id '"' $')' $'!' $'=' $' ' 'getNewAttr' $'(' $' ' '"' *id '"' $')' $')'
+   $'{'
+   $' ' 'output' $'(' $' ' '"<FONT COLOR=\"#006699\">*</FONT>"' $')' $';'
+   $'}'
+   $' ' 'output' $'(' $' ' '"</B></FONT>"' $')' $';'
+   $' ' 'output' $'(' $' ' '" </TD>"' $')' $';'

    :(RETURN)

UserDefsEnd
