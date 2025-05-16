*---------------------------------------------------------------------------------------------------
* IsSpitbol() succeeds if the runtime environment is SPITBOL. It fails otherwise.
* IsSnobol4() succeeds if the runtime environment is SNOBOL4. It fails otherwise.
*---------------------------------------------------------------------------------------------------
               DEFINE('IsSpitbol()')                                                :(IsSpitbolEnd)
IsSpitbol      DIFFER(.NAME, 'NAME')                                                :S(RETURN)F(FRETURN)
IsSpitbolEnd
*---------------------------------------------------------------------------------------------------
               DEFINE('IsSnobol4()')                                                :(IsSnobol4End)
IsSnobol4      IDENT(.NAME, 'NAME')                                                 :S(RETURN)F(FRETURN)
IsSnobol4End
*---------------------------------------------------------------------------------------------------
               DEFINE('IsType(it,types)type')                                       :(IsTypeEnd)
IsType         types          POS(0) SPAN(&UCASE &LCASE) . type (',' | RPOS(0)) =   :F(FRETURN)
               (IDENT(upr(type), 'NULL') IDENT(it))                                 :S(RETURN)
               IDENT(DATATYPE(it), upr(type))                                       :S(RETURN)F(IsType)
IsTypeEnd
