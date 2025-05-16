-NOLIST
*
*             DEBUG.SNO
*
*             Program to allow symbolic debugging of SPITBOL programs.
*
*             V1.3    11/27/95        M.B. Emmer
*                     Restored prompt output.
*                     Added warning about &STLIMIT = -1 statement in user
*                     program.
*
*             V1.2    07/07/87        M.B. Emmer
*                     Converted for use with SPITBOL instead of SNOBOL4+
*                     Remove "?" prompt for Unix.
*                     No BREAK processing either.
*
*             V1.1    05/02/87        M.B. Emmer
*                     Added P command for statement tracing without tracing
*                     subroutines and functions.
*                     Added =expression as synonym for E expression.
*                     Added !command to execute a DOS command.
*                     Added Q command to Quit.
*                     Added "?" prompt to user.
*
*             Source statements can be made available by creating an environment
*             variable named DEBUGLIST equated to the name of a listing file:
*
*                     DEBUGLIST=test.lst
*                     export DEBUGLIST        (need on Unix systems only)
*                     spitbol -lo test.lst test.sno
*
*             DEBUG.SNO must be included after the last line in your program.
*
*             START must be the label of the first statement of your program,
*
*             -------------------------
*             |START    . . .         |
*             |       <user program>  |
*             |         . . .         |
*             |-INCLUDE "debug.sno"   |
*             -------------------------
*
*             If there is a block of statements that are to be excluded from
*             tracing (such as initializations), bracket then with
*                     &TRACE = 0    .....   &TRACE = 50000
*             For example:
*
*             -------------------------
*             |START  &TRACE = 0      |
*             |       <initialization>|
*             |       &TRACE = 50000  |
*             |       <user program>  |
*             |         . . .         |
*             |-INCLUDE "debug.sno"   |
*             -------------------------
*
*             If your program includes the statement &STLIMIT = -1 to turn
*             off statement limit checking, you must remove it.  The debug
*             program cannot perform statement tracing when statement limit
*             checking is disabled.
*

                                                                                   :(END)
-EJECT
debuggo       TERMINAL         =    "Debugger Initializing"

*             Global variables used throughout the debugger package:
*
*             Table to map labels to statement numbers:
              dbg_lbls         =    TABLE(50, 50)
*             First and last statements most recently listed:
              dbg_list_f       =
              dbg_list_l       =
*             Last statement number in listing file.  Null if no listing:
              dbg_final_stmt   =
*             Statement number of user statement last executed:
              dbg_curr_stmt    =
*             Table of statement numbers of breakpoints set.
              dbg_break_tab    =    TABLE()
*             Step count.  Non-zero when we are stepping through a program on
*             a statement by statement basis:
              dbg_step_count   =    1
              dbg_fnclevel     =    50000
*             White space - tab or blank:
              dbg_white        =    CHAR(9) ' '

-EJECT
*             Function definitions

              DEFINE('dbg_case(dbg_case)')

              DEFINE('dbg_cmd()dbg_a,dbg_b,dbg_c,dbg_in')
              dbg_g_pat        =    FENCE
+                                   '='
+                                   (BREAK(dbg_white ',') | REM) . dbg_cmd
+                                   (SPAN(dbg_white ',') | RPOS(0))
              dbg_charu        =    CHAR(9) ' BE=GHKLPQRT+-?!'
              dbg_charl        =    CHAR(9) ' be=ghklpqrt+-?!'
              dbg_charr        =    'c' 'cbeeghklpqrt+-hx'
              dbg_chars        =    FENCE ANY(dbg_charu dbg_charl) . dbg_c (SPAN(dbg_white) | '')

              DEFINE('dbg_fnc()')

              DEFINE('dbg_label(stno)plus,offset')
              dl_pat           =    FENCE
+                                   LEN(8)
+                                   (NOTANY(dbg_white) (BREAK(dbg_white CHAR(10)) | REM)) . dbg_label

              DEFINE('dbg_get_stmt(s)label,sign,offset')
              dbg_get_pat1     =    FENCE
+                                   SPAN('0123456789') . dbg_get_stmt
+                                   (SPAN(dbg_white ',') | RPOS(0))
              dbg_get_pat2     =    FENCE (BREAK(',') | REM) . label (SPAN(dbg_white ',') | RPOS(0))
              dbg_get_pat3     =    FENCE
+                                   BREAK('+-' dbg_white) . label
+                                   BREAK('+-')
+                                   LEN(1) . sign
+                                   BREAK('0123456789')
+                                   SPAN('0123456789') . offset
+                                   (SPAN(dbg_white ',') | RPOS(0))

              DEFINE('errlist()')

              DEFINE('readlist(unit,labtab,last)' 'stno,incl,stmt,listfile,line,label,tab,lf,pat1,pat2')

-EJECT
*             ******************************************************************************
*
*             START OF DEBUGGER PROPER
*
*             ******************************************************************************

*             Read list file.  Ignore failure return, presuming lack of a listing file
*             was an intentional omission to speed up loading the debugger.
*
*             Default table to map statement numbers if no list file
              dbg_stmts        =    TABLE()
              dbg_stmts        =    readlist(15, dbg_lbls, .dbg_final_stmt)

*             Open binary unbuffered output to screen for prompt
              OUTPUT(.dbg_scn, .dbg_scn, '[-f2 -r1 -w]')                           :F(error)

*             Transfer to first statement of user's program (label START), and begin
*             tracing to return control to the debugger.
*
              SETEXIT("errlist")
              &TRACE           =    2097152
              TRACE('STCOUNT', 'KEYWORD', , 'dbg_fnc')                             :(START)
-EJECT
*             ******************************************************************************
*
*             START OF FUNCTIONS
*
*             ******************************************************************************


*             ******************************************************************************
*
*             dbg_case        function to convert argument to upper-case if
*                             &CASE keyword is non-zero.
*
*             dbg_case(dbg_case)
dbg_case
              dbg_case         =    NE(&CASE, 0) REPLACE(dbg_case, &LCASE, &UCASE) :(RETURN)


-EJECT
*             ******************************************************************************
*
*             dbg_cmd - Function to read and process a debug command.
*
*                         Returns failing when caller should return to the
*                         interrupted user program (the 'normal' exit).
*
*                         Returns success to jump indirect to a user label (but down
*                         one function level).  The function value is the label name.
*
*                         If EOF is read from keyboard, debugger shuts itself off.
*
*             dbg_cmd()

dbg_cmd       SETEXIT("errlist")
              dbg_scn          =    '?'
              dbg_in           =    TRIM(TERMINAL)                                 :F(dbg_off)
              IDENT(dbg_in)                                                        :S(dbg_cmd)
*             Test for valid command and branch to appropriate processor (dbg_?).
*             Lower-case commands are equivalent to upper-case, and blank and
*             tab are converted to the command 'C'.
              dbg_in           dbg_chars =                                         :F(dbg_cmd_err)
              dbg_step_count   =    0                                              :S($('dbg_' REPLACE(dbg_c, dbg_charl, dbg_charr)))

dbg_cmd_err   TERMINAL         =    " ?"                                           :(dbg_cmd)

*             ** Blank or tab - Immediate execution of an unlabeled code statement.
*                Append our own GOTOs to regain control after execution.
dbg_c         SETEXIT()
              dbg_c            =    CODE(' ' dbg_in ' :S(dbg_ss)F(dbg_ff)')        :S(dbg_c1)
              TERMINAL         =    'Compilation error: ' &ERRTEXT                 :(dbg_cmd)
dbg_c1        SETEXIT("errlist")                                                   :<dbg_c>

*             Here to report the success or failure of the immediate execution.
dbg_ss        TERMINAL         =    'Success'                                      :(dbg_cmd)
dbg_ff        TERMINAL         =    'Failure'                                      :(dbg_cmd)


*             ** B - Set Breakpoint(s)
dbg_b         IDENT(dbg_in)                                                        :S(dbg_cmd)
              dbg_break_tab[+dbg_get_stmt(.dbg_in)] = 1                            :S(dbg_b)F(dbg_cmd)


*             ** E - Examine variable or Evaluate expression.
dbg_e         SETEXIT()
              TERMINAL         =    EVAL(dbg_in)                                   :S(dbg_cmd)
              TERMINAL         =    'Evaluation error: ' &ERRTEXT                  :(dbg_cmd)


*             ** G - Go <=optional direct transfer label> <optional breakpoint(s)>
*
*             First test for simple G by itself:
dbg_g         IDENT(dbg_in)                                                        :S(FRETURN)
*
*             Check for =label, assign label to dbg_cmd:
              dbg_in           dbg_g_pat =                                         :F(dbg_g1)
              dbg_cmd          =    dbg_case(dbg_cmd)
*             Error if label unknown.
              TERMINAL         =    IDENT(dbg_lbls[dbg_cmd])
+                                   'Unknown label: ='
+                                   dbg_cmd                                        :S(dbg_cmd)

*             Process any breakpoints:
dbg_g1        DIFFER(dbg_in)                                                       :F(dbg_g2)
              dbg_break_tab[+dbg_get_stmt(.dbg_in)] = 1                            :S(dbg_g1)F(dbg_cmd)
*             Choose FRETURN to resume execution where interrupted, RETURN to
*             transfer to the label in dbg_cmd.
dbg_g2        DIFFER(dbg_cmd)                                                      :S(RETURN)F(FRETURN)

*             ** H or ? - Abbreviated Help
dbg_h         TERMINAL         =    'stno - statement numbers specified as integers, or LABEL +- N'
              TERMINAL         =    '          Bracketed items are optional'
              TERMINAL         =    'tab statement           Immediate execution of "statement"'
              TERMINAL         =    'B stno [,stno,...]      set Breakpoint(s)'
              TERMINAL         =    'E expression (or =exp)  evaluate Expression'
              TERMINAL         =    'G [=label,][stno1,...]  Go [at specified label],'
              TERMINAL         =    '                         set specified breakpoint(s)'
              TERMINAL         =    'K bkpt [,bkpt,...]      Kill breakpoint(s)'
              TERMINAL         =    'L                       List current statement'
              TERMINAL         =    'L stno1 [,stno2]        List statement or range'
              TERMINAL         =    '+ [n]                   List next n statements'
              TERMINAL         =    '- [n]                   List previous n statements'
              TERMINAL         =    '++ or --                List 12 statements forward or back'
              TERMINAL         =    'P [n]                   Trace n statements, (no procedures)'
              TERMINAL         =    'Q                       Quit'
              TERMINAL         =    'R                       Report breakpoints set'
              TERMINAL         =    'T [n]                   Trace n statements (into procedures)'
              TERMINAL         =    '!command                Execute shell command'
              TERMINAL         =    '^Z (DOS) or ^D (Unix)   EOF - Resume program, stop debugging'
                                                                                   :(dbg_cmd)
*             ** K - Kill Breakpoint(s)
dbg_k         IDENT(dbg_in)                                                        :S(dbg_cmd)
              dbg_break_tab[+dbg_get_stmt(.dbg_in)] =                              :S(dbg_k)F(dbg_cmd)


*            ** L - List Statement(s).
*
*             L by itself lists the statement about to be executed.
*             L stmt lists the specified statement.
*             L stmt1,stmt2 lists all statements in the specified range.
*             see also + and - commands, below.
*
*             dbg_a is the first statement to print, dbg_c is the last.
*             dbg_list_f and dbg_list_l are reference numbers for subsequent + & -'s
*
dbg_l
*             Dispatch if L by itself:
              dbg_a            =    IDENT(dbg_in) dbg_curr_stmt                    :S(dbg_l5)

*             Get first line number:
              dbg_a            =    +dbg_get_stmt(.dbg_in)                         :F(dbg_cmd)
*             If just one, display it by itself.
              IDENT(dbg_in)                                                        :S(dbg_l5)
*             If another, get it as the ending line number
              dbg_c            =    +dbg_get_stmt(.dbg_in)                         :S(dbg_l1)F(dbg_cmd)

*             Display one line at dbg_a
dbg_l5        dbg_c            =    dbg_a

*             Use dbg_c as the reference for subsequent display.
dbg_l1        dbg_b            =    .dbg_c

*             Check range of values specified
dbg_l2        IDENT(dbg_final_stmt)                                                :S(dbg_cmd)
              dbg_a            =    LT(dbg_a, 1) 1
              dbg_a            =    GT(dbg_a, dbg_final_stmt) dbg_final_stmt
              dbg_c            =    LT(dbg_c, dbg_a) dbg_a
              dbg_c            =    GT(dbg_c, dbg_final_stmt) dbg_final_stmt
              dbg_list_f       =    dbg_a
              dbg_list_l       =    dbg_c

*             Display loop.
dbg_l3        TERMINAL         =    dbg_stmts[dbg_a]
              dbg_a            =    LT(dbg_a, dbg_c) dbg_a + 1                     :S(dbg_l3)F(dbg_cmd)


*             ** +<n>   List next statement(s).  ++ lists the next 12 lines.
dbg_+         dbg_a            =    dbg_list_l + 1
              dbg_c            =    IDENT(dbg_in, dbg_c) 11                        :S(dbg_l6)
              dbg_c            =    INTEGER(dbg_in) +dbg_in                        :F(dbg_cmd_err)
              dbg_c            =    LE(dbg_c, 0) 1
dbg_l6        dbg_c            =    dbg_a + dbg_c - 1                              :(dbg_l2)

*             ** -<n>   List previous statement(s).  -- lists the previous 12 lines.
dbg_-         dbg_b            =    dbg_list_f - 1
              dbg_c            =    IDENT(dbg_in, dbg_c) 11                        :S(dbg_l7)
              dbg_c            =    INTEGER(dbg_in) +dbg_in                        :F(dbg_cmd_err)
              dbg_c            =    LE(dbg_c, 0) 1
dbg_l7        dbg_a            =    dbg_b - dbg_c + 1
              dbg_c            =    dbg_b                                          :(dbg_l2)


*             ** P - Step n statements, treat procedures as intact entities
dbg_p         dbg_step_count   =    INTEGER(dbg_in) +dbg_in                        :F(dbg_cmd_err)
              dbg_fnclevel     =    &FNCLEVEL - 1
              dbg_step_count   =    LE(dbg_step_count, 0) 1                        :(FRETURN)

*             ** Q = Quit
dbg_q                                                                              :(END)

*             ** R - Report Breakpoints
dbg_r         dbg_a            =    SORT(dbg_break_tab)                            :F(dbg_r2)
              dbg_c            =    0

dbg_r1        dbg_c            =    dbg_c + 1
              TERMINAL         =    dbg_a[dbg_c, 1] ' ' dbg_label(dbg_a[dbg_c, 1]) :S(dbg_r1)F(dbg_cmd)

dbg_r2        TERMINAL         =    "None"                                         :(dbg_cmd)

*             ** T - Step n statements, descending into procedures
dbg_t         dbg_step_count   =    INTEGER(dbg_in) +dbg_in                        :F(dbg_cmd_err)
              dbg_fnclevel     =    50000
              dbg_step_count   =    LE(dbg_step_count, 0) 1                        :(FRETURN)

*             ** X - Execute Shell command
dbg_x         HOST(1, dbg_in)
              TERMINAL         =                                                   :(dbg_cmd)

*             ** Turn off debugger:
*
dbg_off       STOPTR('STCOUNT', 'KEYWORD')                                         :(FRETURN)


-EJECT
*             ******************************************************************************
*
*             dbg_fnc - Function to process trace interrupts on each statement.
*
*
*             dbg_fnc()

dbg_fnc       dbg_curr_stmt    =    &LASTNO

*             If not single-stepping and did not hit a breakpoint, just return.
              LE(dbg_step_count, 0) IDENT(dbg_break_tab[dbg_curr_stmt])            :S(RETURN)

*             If it was a breakpoint, turn off any single-stepping.
              dbg_step_count   =    DIFFER(dbg_break_tab[dbg_curr_stmt])           :S(dbg_display)

*             If doing a P trace, don't stop if down in a function.
              GT(&FNCLEVEL, dbg_fnclevel)                                          :S(RETURN)

*             Must have been single-stepping.  Decrement count.
              dbg_step_count   =    dbg_step_count - 1

*             Display current statement.
dbg_display   dbg_fnc          =    dbg_label(dbg_curr_stmt)
              TERMINAL         =    DIFFER(dbg_fnc) dbg_fnc
              TERMINAL         =    DIFFER(dbg_final_stmt) dbg_stmts[dbg_curr_stmt]
              TERMINAL         =    IDENT(dbg_final_stmt) dbg_curr_stmt
              dbg_list_f       =    dbg_curr_stmt
              dbg_list_l       =    dbg_curr_stmt

*             If more single-stepping to do, just exit:
              GT(dbg_step_count, 0)                                                :S(RETURN)

*             Here is where we read commands from the user.  Control stays within
*             dbg_cmd until it is time to return to the user program.  A failure
*             return means resume where interrupted.  A success return requests
*             a direct jump to a user label.  This direct jump is kludgy because
*             we are 'down one level' in function call depth -- too many of these
*             and the stack will overflow.  Too bad you can't manipulate RETURN.

              dbg_curr_stmt    =    dbg_cmd()                                      :F(RETURN)
*             Jump to user's label without clearing interrupt:
              &TRACE           =    2097152                                        :($dbg_curr_stmt)

-EJECT
*             ******************************************************************************
*
*             dbg_get_stmt - Get optional statement number
*
*             Input:  Name of variable containing string with statement number
*                     or label.  Label may be followed by ' +-N'
*
*             Output: Statement number or null if none provided.
*                     Fails and displays error if bad syntax or illegal label.
*                     Statement number or label removed from argument string.
*
*             dbg_get_stmt(s)

dbg_get_stmt  IDENT($s)                                                            :S(RETURN)
*             Check for simple number:
              $s               dbg_get_pat1 =                                      :S(RETURN)

*             Check for text label:
              $s               dbg_get_pat2 =                                      :F(dbg_get1)
*             Check for optional +N or -N after label:
              label            dbg_get_pat3
              offset           =    IDENT(sign, '-') -offset
*             Map case-converted label to statement number:
              dbg_get_stmt     =    dbg_lbls[dbg_case(label)]
*             Check if label unknown to us, and add offset.
              dbg_get_stmt     =    DIFFER(dbg_get_stmt) dbg_get_stmt + offset     :S(RETURN)

dbg_get1      TERMINAL         =    "Bad label or statement number"                :(FRETURN)


-EJECT
*             ******************************************************************************
*
*             dbg_label - Function to return '(' and statement label and offset ')'
*                           given a statement number.
*                           If dbg_final_stmt is null, there is no listing
*                           available, and we just return a null string.
*
*             dbg_label(stno)

dbg_label     IDENT(dbg_final_stmt)                                                :S(RETURN)

dbg_lab2      dbg_stmts[stno]  dl_pat                                              :S(dbg_lab1)
              stno             =    GT(stno, 1) stno - 1                           :F(ERROR)
              plus             =    ' + '
              offset           =    offset + 1                                     :(dbg_lab2)

dbg_lab1      dbg_label        =    '(' dbg_label plus offset ')'                  :(RETURN)


-EJECT
*             ******************************************************************************
*
*             errlist - Function to produce error message to screen upon error.
*
*             errlist()

errlist       dbg_curr_stmt    =    &LASTNO
              TERMINAL         =    'Execution error #' &ERRTYPE ', ' &ERRTEXT
              TERMINAL         =    'In statement #' dbg_curr_stmt dbg_label(dbug_curr_stmt)
              SETEXIT("errlist")                                                   :(RETURN)


-EJECT
*             *******************************************************************************
*
*             readlist - Function to read a SPITBOL listing file.
*                        Only numbered program statements are retained.
*
*             Input:  Arg 1 : Unit number of program list file (unit)  The unit
*                             should either be already open or pre-associated with
*                             a file on the SNOBOL4 command line.
*                     Arg 2 : Table name to get label entries (labtab).
*                     Arg 3 : Name of variable to receive last statement number.
*
*             Output: Function value : Table where Table<N> is text for statement N.
*                     Input Arg 2 (labtab) : setup so labtab<label> returns statement
*                                            number for a given label.
*
*                     Fails if file not formatted as a list file or cannot attach
*                     file.
*
*                     Continued statements will appear as one long string
*                     with embedded carriage returns.
*
*                     The function is independent of all keyword modes.
*
*             readlist(unit,labtab,last)

readlist
              tab              =    CHAR(9)
              lf               =    CHAR(10)
              ff               =    CHAR(12)
              cr               =    CHAR(13)

*             SPITBOL listing format is 4 columns of statement number,
*             four blank columns, then the user's statement.
*
              pat1             =    FENCE (LEN(4) | SPAN("0123456789")) . stno (LEN(4) | "") REM . stmt
              pat2             =    FENCE (NOTANY('-+.* ' tab) BREAK(tab ' ')) . label
              pat3             =    FENCE NOTANY("123456789 ")

              listfilename     =    HOST(4, "DEBUGLIST")
              INPUT(.listfile, unit, listfilename '[-l65536]')                     :S(readls_)
              TERMINAL         =    'No listing file provided'                     :(FRETURN)

readls_       readlist         =    TABLE(151)
readnx_       line             =    TRIM(listfile)                                 :F(readok_)
              IDENT(line)                                                          :S(readnx_)
              line             pat1                                                :F(readnx_)
*             Ignore page throw, error message, form feed, and titles in listing file.
              stno             pat3                                                :S(readnx_)
              INTEGER(TRIM(stno))                                                  :F(reader_)
*             Adjust $last if new statement number
              $last            =    DIFFER(TRIM(stno)) +TRIM(stno)                 :S(readsv_)
*             Append CR/LF to existing text if continued statement:
              readlist[$last]  =    DIFFER(readlist[$last]) readlist[$last] lf
*             Place statement in table:
readsv_       readlist[$last]  =    readlist[$last] line
              (stmt ' ')       pat2                                                :F(readnx_)
*             Record case-converted label to statement number mapping:
              ITEM(labtab, dbg_case(label)) = $last                                :(readnx_)

reader_       TERMINAL         =    "Incorrect program list file, line in error:"
              TERMINAL         =    line
              ENDFILE(unit)                                                        :(FRETURN)

readok_       ENDFILE(unit)                                                        :(RETURN)

-EJECT
*             ******************************************************************************
*
*             After compilation, transfer to the top of this package to initialize.
END           debuggo
