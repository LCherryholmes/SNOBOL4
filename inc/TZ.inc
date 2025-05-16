*-------------------------------------------------------------------------------------------------------------------------
-INCLUDE 'omega.inc'
-INCLUDE 'Populate.inc'
-INCLUDE 'semantic.inc'
-INCLUDE 'opsyn.inc'
-INCLUDE 'trace.inc'
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('T8DbgPos(sOfs)i')                                                        :(T8DbgPosEnd)
T8DbgPos    T8DbgPos          =     .dummy
            txMax             =     GT(sOfs, txMax) sOfs                                     :F(NRETURN)
            OUTPUT            =     DIFFER(notyet) GT(doDebug, 0) T8Pos(sOfs, t8Map)         :(NRETURN)
T8DbgPosEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
*           Function to read and compile SNOBOL4 functions from a disk file.
*           The filename is specified as the argument to function SLOAD.  It is
*           included here for handy access when running this program.
*
*           This version is supplemented by the ability to process INCLUDE
*           control cards. It avoids redundant includes.
*
	         DEFINE('SLoad(filename)lib,code,x,max_sav,trim_sav,position')
	         white_space_	  =	    CHAR(9) ' '
	         sf_pat_		  =	    FENCE ANY('SsFf') (ANY(white_space_) | RPOS(0))
	         Q_	              =	    "'"
	         QQ_	          =	    '"'
	         sload_stmt       =	    ARBNO(Q_ BREAK(Q_) Q_ | QQ_ BREAK(QQ_) QQ_
+			                  |     NOTANY(Q_ QQ_) BREAK(Q_ QQ_ ';')) ';'
	         sload_stmts      =	    FENCE (';' ARBNO(sload_stmt)) . x '*' REM
	         sload_ccpat      =	    FENCE ('*' | '-' | RPOS(0))
	         sload_cnpat      =	    FENCE (';.' | ';+')
	         sload_inpat      =	    FENCE '-' ANY('Ii') ('nclude' | 'NCLUDE')
+			                        BREAK(QQ_ Q_) LEN(1) BREAK(QQ_ Q_) . x
	         sload_tab	      =	    TABLE()
	         sload_prefix	  =	    HOST(4, 'SNOLIB') '/'
                                                                                             :(SLoadEnd)
SLoad	     filename         =     TRIM(filename)
	         sload_tab[filename] =   1
             INPUT(.lib, .lib, filename)			                                         :S(SLoad_0)
	         INPUT(.lib, .lib, sload_prefix filename)	                                     :F(FRETURN)
SLoad_0	     max_sav          =	    &MAXLNGTH
	         trim_sav         =	    &TRIM
	         &MAXLNGTH        =	    524288
	         &TRIM            =	    1
SLoad_1	     x	              =	    lib				                                         :F(SLoad_2)
	         x                sload_ccpat					                                 :S(SLoad_4)
	         x	              =	    ';' x
	         x                sload_cnpat =	' '
	         x                sload_stmts
	         code	          =	    code x				                                     :(SLoad_1)
SLoad_4	     x                sload_inpat					                                 :F(SLoad_1)
*            x                =     REPLACE(x, &UCASE, &LCASE)
	         DIFFER(sload_tab[x])				                                             :S(SLoad_1)
SLoad_44     position         =     SET(.lib, 0, 1)
             ENDFILE(.lib)
             DIFFER(code)                                                                    :F(SLoad_45)
*            OUTPUT           =     SUBSTR('!' code, 1, 80)
	         code	          =     CODE(code '; :(SLoad_45)')	                             :S<code>
	         TERMINAL         =	    'Compilation error, file: ' filename                     :(SLoad_59)
SLoad_45     SLoad(x)					                                                     :F(FRETURN)
	         sload_tab[TRIM(x)] =    1
	         INPUT(.lib, .lib, filename)			                                         :S(SLoad_5)
	         INPUT(.lib, .lib, sload_prefix filename)	                                     :F(FRETURN)
SLoad_5	     code             =
             SET(.lib, position, 0)				                                             :S(SLoad_1)F(FRETURN)
SLoad_2	     ENDFILE(.lib)
*            OUTPUT           =     SUBSTR('!' code, 1, 80)
	         code	          =     CODE(code '; :(SLoad_3)')	                             :S<code>
	         TERMINAL         =	    'Compilation error, file: ' filename
*            Error. Take CODE apart statement by statement to find the problem.
*            Remove initial ';'
SLoad_59     code	          =	    SUBSTR(code, 2)
SLoad_6	     code             FENCE sload_stmt . x =			                             :F(SLoad_7)
	         CODE(x)						                                                 :S(SLoad_6)
	         x                RTAB(1) . TERMINAL
SLoad_7	     &MAXLNGTH        =	    max_sav
	         &TRIM	          =	    trim_sav
	         TERMINAL         =	    &ERRTEXT			                                     :(FRETURN)
SLoad_3	     &MAXLNGTH        =	    max_sav
	         &TRIM	          =	    trim_sav			                                     :(RETURN)
SLoadEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
