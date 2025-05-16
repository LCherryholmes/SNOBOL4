*-----------------------------------------------------------------------------------------------------------------------
* XDump(object, nm) - Generic SNOBOL4 object dump routine. This recursive routine is useful
* from within the debugger or as debug code sprinkled throughout the SNOBOL4 application.
* Needs to be enhanced to handle 2+ dimensional arrays.
*-----------------------------------------------------------------------------------------------------------------------
               DEFINE('XDump(object,nm)'
+                 'i,iMax,iMin,objArr,objField,objKey,objKeyNm,objType,objVal'
+              )                                                                    :(XDumpEnd)
XDump          objType        =    DATATYPE(object)
               IDENT(objType, 'CODE')                                               :S(XDump00)
               IDENT(objType, 'EXPRESSION')                                         :S(XDump00)
               IDENT(objType, 'INTEGER')                                            :S(XDump05)
               IDENT(objType, 'NAME')                                               :S(XDump00)
               IDENT(objType, 'PATTERN')                                            :S(XDump00)
               IDENT(objType, 'REAL')                                               :S(XDump05)
               IDENT(objType, 'STRING')                                             :S(XDump10)
               IDENT(objType, 'ARRAY')                                              :S(XDump20)
               IDENT(objType, 'TABLE')                                              :S(XDump30)F(XDump40)
XDump00        OUTPUT         =    nm ' = ' objType                                 :(RETURN)
XDump05        OUTPUT         =    nm ' = ' object                                  :(RETURN)
XDump10        OUTPUT         =    nm ' = ' Qize(object)                            :(RETURN)
XDump20        objProto       =    PROTOTYPE(object)
               objProto       POS(0)
+                             (('+' | '-' | epsilon) SPAN(digits)) . iMin ':'
+                             (('+' | '-' | epsilon) SPAN(digits)) . iMax
+                             RPOS(0)
               OUTPUT         =    nm ' = ' "ARRAY['" objProto "']"
               i              =    iMin - 1
XDump25        i              =    LT(i, iMax) i + 1                                :F(RETURN)
               XDump(object[i], nm '[' i ']')                                       :(XDump25)
XDump30        OUTPUT         =    nm ' = ' 'TABLE'
*              objArr         =    CONVERT(object, 'ARRAY')                         :F(RETURN)
               objArr         =    SORT(object)                                     :F(RETURN)
               i              =    0
XDump35        i              =    i + 1
               objKey         =    objArr[i, 1]                                     :F(RETURN)
               objVal         =    objArr[i, 2]
               objKeyNm       =    IDENT(DATATYPE(objKey), 'INTEGER') objKey        :S(XDump37)
               objKeyNm       =    IDENT(DATATYPE(objKey), 'STRING') Qize(objKey)   :S(XDump37)
               objKeyNm       =    DATATYPE(objKey)
XDump37        XDump(objVal, nm '[' objKeyNm ']')                                   :(XDump35)
XDump40        OUTPUT         =    nm ' = ' objType '()'
               i              =    0
XDump45        i              =    i + 1
               objField       =    FIELD(objType, i)                                :F(RETURN)
               XDump(APPLY(objField, object), objField '(' nm ')')                  :(XDump45)
XDumpEnd
