*---------------------------------------------------------------------------------------------------
* Lower case string: string = lwr(string)
               DEFINE('lwr(lwr)')                                                   :(lwr_end)
lwr            lwr            =   REPLACE(lwr, &UCASE, &LCASE)                      :(RETURN)
lwr_end
*---------------------------------------------------------------------------------------------------
* Upper case string: string = upr(string)
               DEFINE('upr(upr)')                                                   :(upr_end)
upr            upr            =   REPLACE(upr, &LCASE, &UCASE)                      :(RETURN)
upr_end
*---------------------------------------------------------------------------------------------------
* Capitalize string: string = cap(string)
               DEFINE('cap(cap)')                                                   :(cap_end)
cap            cap            =   REPLACE(SUBSTR(cap, 1, 1), &LCASE, &UCASE)
+                                 REPLACE(SUBSTR(cap, 2), &UCASE, &LCASE)           :S(RETURN)F(error)
cap_end
*---------------------------------------------------------------------------------------------------
* Create pattern for case insensitive string match:
* pattern = icase(string)
               DEFINE('icase(str)letter,character')                                 :(icase_end)
icase          IDENT(str)                                                           :S(RETURN)
               str            POS(0) ANY(&UCASE &LCASE) . letter =                  :F(icase1)
               icase          =   icase (upr(letter) | lwr(letter))                 :(icase)
icase1         str            POS(0) LEN(1) . character =
               icase          =   icase character                                   :(icase)
icase_end
