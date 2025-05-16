            expr                                =  *expr1 
+           expr1                               =  *expr2 nPush() ARBNO(($'+' *expr2 ('&' & 2) | $'-' *expr2 ('&' & 2)) nInc()) ('*' & 'nTop()') nPop() ('&' & 2) 
+           expr2                               =  *expr3 nPush() ARBNO(($'*' *expr3 ('&' & 2) | $'/' *expr3 ('&' & 2)) nInc()) ('*' & 'nTop()') nPop() ('&' & 2) 
+           expr3                               =  $'+' *expr3 ('&' & 2) | $'-' *expr3 ('&' & 2) | *expr4 
+           expr4                               =  *integer_literal | *real_literal | $'(' *expr1 $')' ('&' & 3) 
