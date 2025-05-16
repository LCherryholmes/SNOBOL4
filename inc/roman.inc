*----------------------------------------------------------------------------------------------------
* Roman(n) - Convert integer n to Roman numeral form
*    n must be positive and less than 4000
*    An asterisk appears in the result if n >= 4000
*    The function fails if n is not an integer
*------- ----------- ----- -------------------------------------------- -----------------------------
         DEFINE('Roman(n)units')
         romanXlat   =     '0,1I,2II,3III,4IV,5V,6VI,7VII,8VIII,9IX,'   :(RomanEnd)
Roman    n           RPOS(1) LEN(1) . units =                           :F(RETURN)           ;* Get rightmost digit to units and remove it from n
                                                                                             ;* Return null result if argument is null
         romanXlat   units BREAK(',') . units                           :F(FRETURN)          ;* Search for digit, replace with its Roman form.
                                                                                             ;* Return failing if not a digit.
         Roman       =     REPLACE(Roman(n),'IVXLCDM','XLCDM**') units  :S(RETURN)F(FRETURN) ;* Convert rest of n and multiply by 10.  Propagate a
                                                                                             ;* failure return from recursive call back to caller
RomanEnd
