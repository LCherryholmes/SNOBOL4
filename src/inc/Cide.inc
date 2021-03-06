*---------- --------------- --- ------------------------------------------- ------------
            DEFINE('CideOpen(letter)dictDir,dictFile')                      :(CideOpenEnd)
CideOpen    dictDir         =   "C:/LegalEarth/English/dict/gcide-0.52"
            dictFile        =   dictDir '/CIDE.' letter
            dictLineNo      =   0
            INPUT(.dictInput, 3, dictFile '[-m10 -l65536]')                 :S(RETURN)F(FRETURN)
CideOpenEnd
*---------- --------------- --- ------------------------------------------- ------------
            DEFINE('CideLine()')                                            :(CideLineEnd)
CideLine    CideLine        =   dictInput                                   :F(FRETURN)
            CideLine        ?   cr RPOS(0) =
            dictLineNo      =   dictLineNo + 1                              :(RETURN)
CideLineEnd
*---------- --------------- --- ------------------------------------------- ------------
            DEFINE('CideClose()')                                           :(CideCloseEnd)
CideClose   ENDFILE(3)                                                      :S(RETURN)F(FRETURN)
CideCloseEnd
*---------- --------------- --- ------------------------------------------- ------------
            DEFINE('ReadCide()Blank,Comment,PStart,PFinish,dictEntry,dictLine,letters,letter') :(ReadCideEnd)
ReadCide    OUTPUT          =   "Read CIDE Processing ..."
            cide            =   TABLE(132000)
            Blank           =   (SPAN(' ' tab) | epsilon)
            Comment         =   '<--' BREAK('-') '-->'
            PStart          =   (Comment | epsilon) '<p>'
            PFinish         =   '</p>'
            letters         =   &UCASE
ReadCide10  letters         ?   POS(0) LEN(1) . letter =                    :F(ReadCide90)
*           OUTPUT          =   'Reading ' letter ' ...'
            CideOpen(letter)                                                :F(Yikes)
            dictLine        =   CideLine()                                  :F(ReadCide80)
            dictLine        ?   POS(0) '<--'                                :F(ReadCideErr)
ReadCide20  dictLine        =   CideLine()                                  :F(Yikes)
            dictLine        ?   POS(0) '-->'                                :F(ReadCide20)
ReadCide30  dictLine        =   CideLine()                                  :F(ReadCide80)
            dictLine        ?   POS(0) Blank RPOS(0)                        :S(ReadCide30)
            dictLine        ?   POS(0) Comment RPOS(0)                      :S(ReadCide30)
            dictLine        ?   POS(0) PStart                               :F(Err10)
            dictEntry       =   dictLine nl
ReadCide40  dictLine        ?   RPOS(4) PFinish                             :S(ReadCide50)
            dictLine        =   CideLine()                                  :F(Yikes)
            dictEntry       =   dictEntry dictLine nl                       :(ReadCide40)
ReadCide50  dictEntry       ?   '<ent>' BREAK('<') . w '</ent>'
            cide[w]         =   DIFFER(w) cide[w] nl dictEntry              :(ReadCide30)
ReadCide80  CideClose()                                                     :(ReadCide10)
ReadCide90  OUTPUT          =   'Read CIDE Finished!'                       :(RETURN)
ReadCideErr OUTPUT          =   dictLineNo ': "' dictLine '"'
            OUTPUT          =   dictEntry                                   :(END)
ReadCideEnd
*---------- --------------- --- ------------------------------------------- ------------
            DEFINE('Cide()A,body,conjf,dictType,ent,ety,i,part_of_speech,pos,posPatrn,vmorph,w')
            $'&'            =   ARBNO(' ') '&' ARBNO(' ')
            sgmlENT         =   '<ent>' BREAK('<') . ent '</ent>'
            sgmlPOS         =   '<pos>' BREAK('<') . pos '</pos>'
            sgmlCONJF       =   '<conjf>' BREAK('<') . conjf '</conjf>'
            sgmlVMORPH      =   '<vmorph>' BREAKX('<') . vmorph '</vmorph>'
            sgmlETY         =   '<ety>' BREAKX('<') . ety '</ety>'
                                                                            :(CideEnd)
Cide        posPatrn        =   epsilon $ part_of_speech
+           ( 'Adj.'            . *assign(.dictType, 'a')  . *assign(.part_of_speech, 'adjective')
+           | 'adj.'            . *assign(.dictType, 'a')  . *assign(.part_of_speech, 'adjective')
+           | 'adj. & adv.'     . *assign(.dictType, 'ar') . *assign(.part_of_speech, 'adjective, adverb')
+           | 'adj. prenom.'    . *assign(.dictType, 'a')  . *assign(.part_of_speech, 'adjective prenominal')
+           | 'a. & adv.'       . *assign(.dictType, 'ar') . *assign(.part_of_speech, 'adjective, adverb')
+           | 'a. & n.'         . *assign(.dictType, 'an') . *assign(.part_of_speech, 'adjective, noun')
+           | 'a. & v. t.'      . *assign(.dictType, 'av') . *assign(.part_of_speech, 'adjective, verb transitive')
+           | 'a. & vb. n.'     . *assign(.dictType, 'an') . *assign(.part_of_speech, 'adjective, verbal noun')
+           | 'a.'              . *assign(.dictType, 'a')  . *assign(.part_of_speech, 'adjective')
+           | 'adv.'            . *assign(.dictType, 'r')  . *assign(.part_of_speech, 'adverb')
+           | 'adv. & a.'       . *assign(.dictType, 'ar') . *assign(.part_of_speech, 'adverb, adjective')
+           | 'Compar.'         . *assign(.dictType, 'a')  . *assign(.part_of_speech, 'comparative')
+           | 'compar.'         . *assign(.dictType, 'a')  . *assign(.part_of_speech, 'comparative')
+           | 'interj.'         . *assign(.dictType)       . *assign(.part_of_speech, 'interjection')
+           | 'imp.'            . *assign(.dictType, 'v')  . *assign(.part_of_speech, 'imperfect')
+           | 'imp. & p. p.'    . *assign(.dictType, 'v')  . *assign(.part_of_speech, 'imperfect, participle past')
+           | 'n. sing.'        . *assign(.dictType, 'n')  . *assign(.part_of_speech, 'noun singular')
+           | 'n. pl.'          . *assign(.dictType, 'n')  . *assign(.part_of_speech, 'noun plural')
+           | 'n.'              . *assign(.dictType, 'n')  . *assign(.part_of_speech, 'noun')
+           | 'p. pr.'          . *assign(.dictType, 'v')  . *assign(.part_of_speech, 'participle present')
+           | 'p. pr. & vb. n.' . *assign(.dictType, 'vn') . *assign(.part_of_speech, 'participle present, verbal noun')
+           | 'p. p.'           . *assign(.dictType, 'v')  . *assign(.part_of_speech, 'participle past')
+           | 'p. a.'           . *assign(.dictType, 'a')  . *assign(.part_of_speech, 'participial adjective')
+           | 'p.'              . *assign(.dictType, 'v')  . *assign(.part_of_speech, 'participle')
+           | 'prep.'           . *assign(.dictType)       . *assign(.part_of_speech, 'preposition')
+           | 'prop. adj.'      . *assign(.dictType, 'a')  . *assign(.part_of_speech, 'proper adjective')
+           | 'prop. a.'        . *assign(.dictType, 'a')  . *assign(.part_of_speech, 'proper adjective')
+           | 'prop. n. pl.'    . *assign(.dictType, 'n')  . *assign(.part_of_speech, 'proper noun plural')
+           | 'prop. n.'        . *assign(.dictType, 'n')  . *assign(.part_of_speech, 'proper noun')
+           | 'pl.'             . *assign(.dictType, 'n')  . *assign(.part_of_speech, 'plural')
+           | 'sing.'           . *assign(.dictType, 'n')  . *assign(.part_of_speech, 'singular')
+           | 'vb. n.'          . *assign(.dictType, 'n')  . *assign(.part_of_speech, 'verbal noun')
+           | 'v. i. & t.'      . *assign(.dictType, 'v')  . *assign(.part_of_speech, 'verb')
+           | 'v. t. & i.'      . *assign(.dictType, 'v')  . *assign(.part_of_speech, 'verb')
+           | 'v. i.'           . *assign(.dictType, 'v')  . *assign(.part_of_speech, 'verb intransitive')
+           | 'v. t.'           . *assign(.dictType, 'v')  . *assign(.part_of_speech, 'verb transitive')
+           | 'v.'              . *assign(.dictType, 'v')  . *assign(.part_of_speech, 'verb')
+           )
            A               =   SORT(cide)                                  :F(FRETURN)
            dict            =   TABLE(131072)
Cide1       i               =   i + 1
            w               =   A[i, 1]                                     :F(Cide9)
            body            =   A[i, 2]
            body            ?   sgmlENT =                                   :F(Yikes)
Cide2       body            ?   sgmlETY =                                   :S(Cide2)
            body            ?   sgmlVMORPH =
Cide3       body            ?   sgmlPOS =                                   :F(Cide5)
            pos             =   TRIM(pos)
            pos             ?   POS(0) posPatrn RPOS(0)                     :F(Cide3)
*           OUTPUT          =   DIFFER(dictType) w '(' dictType ')'
            dict[w]         =   DIFFER(dictType) dictType                   :(Cide3)
Cide5       vmorph          ?   sgmlPOS ARBNO(' ') sgmlCONJF =              :F(Cide1)
            pos             =   TRIM(pos)
            pos             ?   POS(0) posPatrn RPOS(0)                     :F(Cide5)
*           OUTPUT          =   DIFFER(dictType) conjf '(' dictType ')'
            dict[conjf]     =   DIFFER(dictType) dictType                   :(Cide5)
Cide9       cide            =   NULL                                        :(RETURN)
CideEnd
*---------- --------------- --- ------------------------------------------- ------------
            DEFINE('CideText()cideCount,cideLine,cideText,type,types,w')    :(CideTextEnd)
CideText    INPUT(.cideText, 3, 'C:/LegalEarth/cide.txt')                   :F(Yikes)
CideText1   cideLine        =   cideText                                    :F(CideText9)
            cideLine        ?   POS(0)
+                               BREAK('(') . w
+                               '(' BREAK(')') . types ')'
+                               RPOS(0)                                     :F(CideTextE)
*           OUTPUT          =   cideLine
            cideCount       =   cideCount + 1
CideText3   types           ?   POS(0) RPOS(0)                              :S(CideText1)
            types           ?   POS(0) ANY('arvn') . type =                 :F(Yikes)
            dict[lwr(w)]    ?   type                                        :S(CideText3)
            dict[lwr(w)]    =   dict[lwr(w)] type                           :(CideText3)
CideText9   ENDFILE(3)
*           OUTPUT          =   'cide ' cideCount
                                                                            :(RETURN)
CideTextE   OUTPUT          =   'cide error: ' cideLine                     :(END)
CideTextEnd
*---------- --------------- --- ------------------------------------------- ------------
