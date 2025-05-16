*---------- ----------------- ----- -------------------------------------------------------- ---------------------------
            DEFINE('Words()wordsInput,wordsFile,wordsI,word,wordCount,wordTotal,hypenTotal') :(WordsEnd)
Words       words             =     TABLE(524288)
            wordsI            =     0
Words1      wordsI            =     LT(wordsI, 3) wordsI + 1                                 :F(Words4)
            wordsFile         =     'C:/LegalEarth/English/words-' wordsI '.txt'
            wordCount         =     0
            INPUT(.wordsInput, 21, wordsFile)                                                :F(WordsE)
Words2      word              =     lwr(wordsInput)                                          :F(Words3)
            wordCount         =     wordCount + 1
            wordTotal         =     IDENT(words[word]) wordTotal + 1
            hypenTotal        =     match(word, '-') hypenTotal + 1
            words[word]       =     words[word] + 1                                          :(Words2)
Words3      OUTPUT            =     'Total words(' wordsI ') ' wordCount
            ENDFILE(21)                                                                      :(Words1)
Words4      OUTPUT            =     'Total words ' wordTotal
            OUTPUT            =     'Total hypenated words ' hypenTotal                      :(RETURN)
WordsE      OUTPUT            =     'Error: ' wordsFile                                      :(END)
WordsEnd
*---------- ----------------- ----- -------------------------------------------------------- ---------------------------
            DEFINE('Dict()'
+              'datCount,datFileName,datFileNames,datLine,datPathName,dictType,dictWord'
+           )
            hex2Dec           =     TABLE()
            hex2Dec['0']      =     0
            hex2Dec['1']      =     1
            hex2Dec['2']      =     2
            hex2Dec['3']      =     3
            hex2Dec['4']      =     4
            hex2Dec['5']      =     5
            hex2Dec['6']      =     6
            hex2Dec['7']      =     7
            hex2Dec['8']      =     8
            hex2Dec['9']      =     9
            hex2Dec['a']      =     10
            hex2Dec['b']      =     11
            hex2Dec['c']      =     12
            hex2Dec['d']      =     13
            hex2Dec['e']      =     14
            hex2Dec['f']      =     15                                                       :(DictEnd)
Dict        dict              =     IDENT(dict) TABLE(16384)
            datDirPath        =     'C:/WordNet 3.0/dict' ;* WordNet 2.1/dict
            datFileNames      =     'adj/adv/noun/verb/'
Dict0       datFileNames      ?     POS(0) BREAK('/') . datFileName '/' =                    :F(DictRet)
            datPathName       =     'data.' datFileName
            datCount          =     0
            INPUT(.datFile, 21, datDirPath '/' datPathName '[-m10 -l4096]')                  :F(error)
Dict1       datLine           =     datFile                                                  :F(Dict6)
            datCount          =     datCount + 1
            datLine           ?     POS(0) '  ' SPAN(digits) ' '                             :S(Dict1)
            datLine           ?     POS(0) SPAN('0123456789')
+                                   ' ' SPAN('0123456789')
+                                   ' ' ANY('asrnv') . dictType
+                                   ' ' SPAN('0123456789abcdef') . dictHexEntries
+                                   ' ' =                                                    :F(DictErr)
            dictHexEntries    ?     POS(0) LEN(1) . dictH1 LEN(1) . dictH2 RPOS(0)           :F(error)
            dictNumEntries    =     hex2Dec[dictH1] * 16 + hex2Dec[dictH2]
            dictN             =     0
Dict2       dictN             =     LT(dictN, dictNumEntries) dictN + 1                      :F(Dict1)
            datLine           ?     POS(0) BREAK(' (') . dictWord '(' BREAK(')') ') ' =      :S(Dict3)
            datLine           ?     POS(0) BREAK(' (') . dictWord ' ' =                      :F(error)
            dictWord          =     REPLACE(dictWord, '_', ' ')
*           OUTPUT            =     dictWord
            dict[dictWord]    ?     dictType                                                 :S(Dict3)
            dict[dictWord]    =     dict[dictWord] dictType
Dict3       datLine           ?     POS(0) SPAN('0123456789abcdef') ' ' =                    :S(Dict2)F(DictErr)
Dict5       datLine           ?     POS(0) ARB ' | ' RTAB(0) . datLine
            OUTPUT            =     datLine                                                  :(Dict1)
            datLine           ?     '"' BREAK('"') . dictExample '"' =                       :F(Dict1)
            OUTPUT            =     dictExample                                              :(Dict5)
Dict6       ENDFILE(21)
*           OUTPUT            =     datFileName ' ' datCount
            datPathName       =     datFileName '.exc'
            INPUT(.datFile, 21, datDirPath '/' datPathName '[-l4096]')                       :F(Dict0)  ;* :F(error)
Dict7       datLine           =     datFile                                                  :F(Dict9)
            datLine           ?     POS(0) BREAK(' ') . dict1st ' ' RTAB(0) . dict2nd        :F(DictErr)
            dict1st           =     REPLACE(dict1st, '_', ' ')
*           OUTPUT            =     dict1st
            dict[dict1st]     ?     dictType                                                 :S(Dict8)
            dict[dict1st]     =     dict[dict1st] dictType
Dict8       dict2nd           =     REPLACE(dict2nd, '_', ' ')
*           OUTPUT            =     dict2nd
            dict[dict2nd]     ?     dictType                                                 :S(Dict7)
            dict[dict2nd]     =     dict[dict2nd] dictType                                   :(Dict7)
Dict9       ENDFILE(21)                                                                      :(Dict0)

DictErr     OUTPUT            =     'Error:' datLine                                         :(END)
DictRet     dictN             =     0                                                        :(RETURN)
            dictA             =     CONVERT(dict, 'ARRAY')
DictRet1    dictN             =     LT(dictN, 1024) dictN + 1                                :F(RETURN)
            dictWord          =     dictA[dictN, 1]                                          :F(RETURN)
            dictTypes         =     dictA[dictN, 2]
            OUTPUT            =     dictWord ' = ' dictTypes                                 :(DictRet1)
DictEnd
*---------- ----------------- ----- -------------------------------------------------------- ---------------------------
            EngIs_level       =     0
            DEFINE('EngIsNoun(wrd)lemma')
            DEFINE('EngIsAdj(wrd)lemma')
            DEFINE('EngIsAdv(wrd)lemma')
            DEFINE('EngIsVerb(wrd)lemma')
            DEFINE('EngIsING(wrd)lemma')                                                     :(EngIsEnd)
EngIsNoun   EngIsNoun         =     .dummy
            wrd               =     lwr(wrd)
            dict[wrd]         ?     'n'                                                      :S(EngIsNoun9)
            lemma             =     wrd
            lemma             ?     POS(0) 'is' RPOS(0)                                      :S(FRETURN)
            lemma             ?     RPOS(4) 'ches' = 'ch'                                    :S(EngIsNoun0)
            lemma             ?     RPOS(4) 'shes' = 'sh'                                    :S(EngIsNoun0)
            lemma             ?     RPOS(3) 'ies'  = 'y'                                     :S(EngIsNoun0)
            lemma             ?     RPOS(3) 'ses'  = 's'                                     :S(EngIsNoun0)
            lemma             ?     RPOS(3) 'xes'  = 'x'                                     :S(EngIsNoun0)
            lemma             ?     RPOS(3) 'zes'  = 'z'                                     :S(EngIsNoun0)
            lemma             ?     RPOS(3) 'men'  = 'man'                                   :S(EngIsNoun0)
            lemma             ?     RPOS(1) 's'    =                                         :S(EngIsNoun0)
            lemma             ?     RPOS(3) 'ing'  =                                         :S(EngIsNoun1)F(FRETURN)
EngIsNoun0  dict[lemma]       ?     'n'                                                      :S(EngIsNoun9)F(FRETURN)
EngIsNoun1  dict[lemma]       ?     'v'                                                      :S(EngIsNoun9)
            lemma             =     lemma 'e'
            dict[lemma]       ?     'v'                                                      :S(EngIsNoun9)F(FRETURN)
EngIsNoun9  OUTPUT            =     GT(doDebug, EngIs_level)
+                                   IDENT(ldict[wrd])
+                                   'Noun = ' wrd ' (' lemma ')'
            ldict[wrd]        =     IDENT(ldict[wrd]) dict[lemma]                            :(NRETURN)
*---------- ----------------- ----- -------------------------------------------------------- ---------------------------
EngIsAdj    EngIsAdj          =     .dummy
            wrd               =     lwr(wrd)
            dict[wrd]         ?     ('a' | 's')                                              :S(EngIsAdj9)
            lemma             =     wrd
            lemma             ?     RPOS(3) 'est' =                                          :S(EngIsAdj0)
            lemma             ?     RPOS(2) 'er' =                                           :S(EngIsAdj0)F(FRETURN)
EngIsAdj0   dict[lemma]       ?     ('a' | 's')                                              :S(EngIsAdj9)
            lemma             =     lemma 'e'
            dict[lemma]       ?     ('a' | 's')                                              :S(EngIsAdj9)F(FRETURN)
EngIsAdj9   OUTPUT            =     GT(doDebug, EngIs_level)
+                                   IDENT(ldict[wrd])
+                                   'Adj =  ' wrd  ' (' lemma ')'
            ldict[wrd]        =     IDENT(ldict[wrd]) dict[lemma]                            :(NRETURN)
*---------- ----------------- ----- -------------------------------------------------------- ---------------------------
EngIsAdv    EngIsAdv          =     .dummy
            dict[lwr(wrd)]    ?     'r'                                                      :F(FRETURN)
            OUTPUT            =     GT(doDebug, EngIs_level)
+                                   IDENT(ldict[wrd])
+                                   'Adv =  ' wrd
            ldict[wrd]        =     IDENT(ldict[wrd]) dict[lwr(wrd)]                         :(NRETURN)
*---------- ----------------- ----- -------------------------------------------------------- ---------------------------
EngIsVerb   EngIsVerb         =     .dummy
            wrd               =     lwr(wrd)
            dict[wrd]         ?     'v'                                                      :S(EngIsVerb9)
            lemma             =     wrd
            lemma             ?     RPOS(3) 'ied' = 'y'                                      :S(EngIsVerb0)
            lemma             ?     RPOS(3) 'ies' = 'y'                                      :S(EngIsVerb0)
            lemma             ?     RPOS(2) 'es'  =                                          :S(EngIsVerb1)
            lemma             ?     RPOS(2) 'ed'  =                                          :S(EngIsVerb1)
*           lemma             ?     RPOS(3) 'ing' =                                          :S(EngIsVerb1)
            lemma             ?     RPOS(1) 's'   =                                          :S(EngIsVerb0)F(FRETURN)
EngIsVerb0  dict[lemma]       ?     'v'                                                      :S(EngIsVerb9)F(FRETURN)
EngIsVerb1  dict[lemma]       ?     'v'                                                      :S(EngIsVerb9)
            lemma             =     lemma 'e'
            dict[lemma]       ?     'v'                                                      :S(EngIsVerb9)F(FRETURN)
EngIsVerb9  OUTPUT            =     GT(doDebug, EngIs_level)
+                                   IDENT(ldict[wrd])
+                                   'Verb = ' wrd  ' (' lemma ')'
            ldict[wrd]        =     IDENT(ldict[wrd]) dict[lemma]                            :(NRETURN)
*---------- ----------------- ----- -------------------------------------------------------- ---------------------------
EngIsING    EngIsING          =     .dummy
            wrd               =     lwr(wrd)
            lemma             =     wrd
            lemma             ?     RPOS(3) 'ing' =                                          :F(FRETURN)
            dict[lemma]       ?     'v'                                                      :S(NRETURN)
            lemma             =     lemma 'e'
            dict[lemma]       ?     'v'                                                      :S(NRETURN)F(FRETURN)
EngIsEnd
*---------- ----------------- ----- -------------------------------------------------------- ---------------------------
