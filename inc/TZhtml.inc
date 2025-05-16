*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('Quotize(pattern)')
            OPSYN('=', 'Quotize', 1)                                                         :S(QuotizeEnd)F(error)
Quotize     Quotize           =     pattern | '"' pattern '"'                                :(RETURN)
QuotizeEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserDefs()')                                                             :(UserDefsEnd)
UserDefs    u                 =     0
            usr               =     ARRAY('1:32')
            xTrace            =     5
            doDebugAfter1st   =     FALSE
            doInclWhite       =     TRUE
            doInclNL          =     TRUE
            doParseTree       =     FALSE
            doRemember        =     FALSE
            doReportFileName  =     TRUE
            fndExt            =     ('html' | 'htm') . extc
            fndCmd            =     'C:/mksnt/find C:/SNOBOL4 -name "*.html" -print'
            fndSpecific       =
            fndExclude        =
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
-INCLUDE 'HTML.inc'
*---------- --------------------- ----- ----------------------------------------------------------------------------------
                                                                                             :(RETURN)
UserDefsEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserRpt()')                                                              :(UserRptEnd)
UserRpt     html              =     Pop()                                                    :F(RETURN)
            DIFFER(html)                                                                     :F(RETURN)
*           XDump('html', html)
            TDump(html)                                                                      :(RETURN)
UserRptEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserTokens()')                                                           :(UserTokensEnd)
UserTokens  tok[t = t + 1] = token(,, .htmRecognizer)
            tok[t = t + 1] = token(,, .htmDOCTYPE)
            tok[t = t + 1] = token(,, .htmHTML)
            tok[t = t + 1] = token(,, .htmHEAD)
            tok[t = t + 1] = token(,, .htmBODY)
            tok[t = t + 1] = token(,  *(spcpfx "NUMBER"), NUMBER)
            tok[t = t + 1] = token(,  *(spcpfx "SIZE_VALUE"), SIZE_VALUE)
            tok[t = t + 1] = token(,  *(spcpfx "PERCENT"), PERCENT)
            tok[t = t + 1] = token(,  *(spcpfx "RGB"), RGB)
            tok[t = t + 1] = token(,  *(spcpfx "STRING"), STRING)
            tok[t = t + 1] = token(,  *(spcpfx "*identifier"), *identifier)
            tok[t = t + 1] = token(,  *(spcpfx "$'<" upr(tx) "'"), *htmTagBegin . tx)
            tok[t = t + 1] = token(,  *(spcpfx "$'</" upr(tx) "'"), *htmTagEnd . tx)
            tok[t = t + 1] = token(,  *(spcpfx "'" upr(tx) "'"), *htmTag . tx)
            tok[t = t + 1] = token(,  *(spcpfx "'" upr(tx) "'"), *htmAttr . tx)
            tok[t = t + 1] = token(,  *(spcpfx "'" upr(tx) "'"), *htmVal . tx)
            tok[t = t + 1] = token(,  *("$'" tx "'"), '<!--' . tx)
            tok[t = t + 1] = token(,  *("$'" tx "'"), '<!' . tx)
            tok[t = t + 1] = token(,  *("$'" tx "'"), '</' . tx)
            tok[t = t + 1] = token(,  *("$'" tx "'"), '<' . tx)
            tok[t = t + 1] = token(,  *("$'" tx "'"), '>' . tx)
            tok[t = t + 1] = token(,  *("$'" tx "'"), '=' . tx)
            tok[t = t + 1] = token(,  *("$'" tx "'"), '&' . tx)
            tok[t = t + 1] = token(,  *("$'" tx "'"), ';' . tx)
            tok[t = t + 1] = token(,  *("$'" tx "'"), '-->' . tx)

            dbg[.htmRecognizer] = TRUE
            dbg[.htmDOCTYPE]    = TRUE
            dbg[.htmHTML]       = TRUE
            dbg[.htmHEAD]       = TRUE
            dbg[.htmTITLE]      = TRUE
            dbg[.htmISINDEX]    = TRUE
            dbg[.htmBASE]       = TRUE
            dbg[.htmSCRIPT]     = TRUE
            dbg[.htmSTYLE]      = TRUE
            dbg[.htmMETA]       = TRUE
            dbg[.htmLINK]       = TRUE
            dbg[.htmBODY]       = TRUE
            dbg[.htmH]          = TRUE
            dbg[.htmTT]         = TRUE
            dbg[.htmI]          = TRUE
            dbg[.htmB]          = TRUE
            dbg[.htmU]          = TRUE
            dbg[.htmSTRIKE]     = TRUE
            dbg[.htmBIG]        = TRUE
            dbg[.htmSMALL]      = TRUE
            dbg[.htmSUB]        = TRUE
            dbg[.htmSUP]        = TRUE
            dbg[.htmEM]         = TRUE
            dbg[.htmSTRONG]     = TRUE
            dbg[.htmDFN]        = TRUE
            dbg[.htmCODE]       = TRUE
            dbg[.htmSAMP]       = TRUE
            dbg[.htmKBD]        = TRUE
            dbg[.htmVAR]        = TRUE
            dbg[.htmCITE]       = TRUE
            dbg[.htmA]          = TRUE
            dbg[.htmIMG]        = TRUE
            dbg[.htmAPPLET]     = TRUE
            dbg[.htmPARAM]      = TRUE
            dbg[.htmFONT]       = TRUE
            dbg[.htmBASEFONT]   = TRUE
            dbg[.htmAREA]       = TRUE
            dbg[.htmINPUT]      = TRUE
            dbg[.htmSELECT]     = TRUE
            dbg[.htmOPTION]     = TRUE
            dbg[.htmTEXTAREA]   = TRUE
            dbg[.htmP]          = TRUE
            dbg[.htmUL]         = TRUE
            dbg[.htmUL_LI]      = TRUE
            dbg[.htmOL]         = TRUE
            dbg[.htmOL_LI]      = TRUE
            dbg[.htmDIR]        = TRUE
            dbg[.htmMENU]       = TRUE
            dbg[.htmPRE]        = TRUE
            dbg[.htmDL]         = TRUE
            dbg[.htmDT]         = TRUE
            dbg[.htmFORM]       = TRUE
            dbg[.htmHR]         = TRUE
            dbg[.htmTABLE]      = TRUE
            dbg[.htmCAPTION]    = TRUE
            dbg[.htmTR]         = TRUE
            dbg[.htmTH]         = TRUE
            dbg[.htmTD]         = TRUE
            dbg[.htmADDRESS]    = TRUE

                                                                                             :(RETURN)
UserTokensEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
