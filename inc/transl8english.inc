* Program: English Language Parser
* Author:  Lon Cherryholmes
* First Created: 2002/12/25
* Last Modified: 2003/01/03
* Version: 0.01
* (c) Copyright 2003, Lon Cherryholmes
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
-INCLUDE 'Cide.inc'
-INCLUDE 'WordNet.inc'
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
*  ---- ----------- --- ----------------------------------- ------------
        DEFINE('XT(Q)QA,i,t,q')                             :(XTEnd)
XT      QA          =   DIFFER(Q) SORT(Q, 1)                :F(RETURN)
        i           =   DIFFER(QA) 0                        :F(RETURN)
XT5     i           =   i + 1
        t           =   QA[i, 1]                            :F(RETURN)
        q           =   QA[i, 2]
        OUTPUT      =   LPAD(q, 4) ' ' t                    :(XT5)
XTEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserDefs()')                                                             :(UserDefsEnd)
UserDefs    u                 =     0
            usr               =     ARRAY('1:32')
            doDebugAfter1st   =     TRUE
            doInclWhite       =     TRUE
            doInclNL          =     FALSE
            doReportFileName  =     FALSE
            doRemember        =     FALSE
            fndExt            =     'txt' . extc
            fndCmd            =     'C:/mksnt/find C:/LegalEarth -name "g*.txt" -print'
            fndSpecific       =     'gUSC.txt'
            fndExclude        =
            spcpfx            =     (EQ(doInclWhite, TRUE) "$' ' ", NULL)
            keyint            =     ('?') . tx
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
-INCLUDE 'english.inc'
*---------- ----------------- ----- -------------------------------------------------------- ---------------------------
                                                                                             :(RETURN)
UserDefsEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserRpt()')                                                              :(UserRptEnd)
UserRpt                                                                                      :(RETURN)
UserRptEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserFinal()')                                                            :(UserFinalEnd)
UserFinal   XT(tblpat)                                                                       :(RETURN)
UserFinalEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserTokens()')                                                           :(UserTokensEnd)
UserTokens
            tok[t = t + 1] = token(,, .eFormOfBEVerb)
            tok[t = t + 1] = token( "Dict1"
+                                 , *( (DIFFER(match(dict[eWrd], 'n')) 'N', NULL)
+                                      (DIFFER(match(dict[eWrd], 'a' | 's')) 'A', NULL)
+                                      (DIFFER(match(dict[eWrd], 'r')) 'R', NULL)
+                                      (DIFFER(match(dict[eWrd], 'v')) 'V', NULL)
+                                      '()'
+                                   )
+                                 , eWord $ eWrd $ *match(NULL, *DIFFER(dict[eWrd]))
+                                 )
            tok[t = t + 1] = token( "Dict2"
+                                 , *( (DIFFER(match(dict[lwr(eWrd)], 'n')) 'N', NULL)
+                                      (DIFFER(match(dict[lwr(eWrd)], 'a' | 's')) 'A', NULL)
+                                      (DIFFER(match(dict[lwr(eWrd)], 'r')) 'R', NULL)
+                                      (DIFFER(match(dict[lwr(eWrd)], 'v')) 'V', NULL)
+                                      '()'
+                                   )
+                                 , eWord $ eWrd $ *match(NULL, *DIFFER(dict[lwr(eWrd)]))
+                                 )
            tok[t = t + 1] = token("IsEng"
+                                 , *( (DIFFER(EngIsNoun(eWrd)) 'N', NULL)
+                                      (DIFFER(EngIsAdj(eWrd)) 'A', NULL)
+                                      (DIFFER(EngIsAdv(eWrd)) 'R', NULL)
+                                      (DIFFER(EngIsVerb(eWrd)) 'V', NULL)
+                                      '()'
+                                   )
+                                 , eWord $ eWrd
+                                 $ *match( NULL
+                                         , epsilon $ *EngIsNoun(eWrd)
+                                         | epsilon $ *EngIsAdj(eWrd)
+                                         | epsilon $ *EngIsAdv(eWrd)
+                                         | epsilon $ *EngIsVerb(eWrd)
+                                         )
+                                 )
            tok[t = t + 1] = token(,, .eArticle)
            tok[t = t + 1] = token(,, .eNoun)
            tok[t = t + 1] = token(, *("'" tx "'"), *eKnownWord . tx)

            tok[t = t + 1] = token(,, .eModifiedNoun)
            tok[t = t + 1] = token(,, .ePrepositionalPhrase)

            tok[t = t + 1] = token(,, .eBasicSentence)
            tok[t = t + 1] = token(,, .eCompleteSentence)
*           tok[t = t + 1] = token(,, .ePredicate)
            tok[t = t + 1] = token(,, .eSimpleSentence)
            tok[t = t + 1] = token(,, .eCompoundSentence)
            tok[t = t + 1] = token(,, .eComplexSentence)
            tok[t = t + 1] = token(,, .eCompoundComplexSentence)
            tok[t = t + 1] = token(,, .eIndependentClause)
*           tok[t = t + 1] = token(,, .eCompoundSubject)
*           tok[t = t + 1] = token(,, .eCompoundVerb)


            tok[t = t + 1] = token(,, .eCoordinatingConjunction)
            tok[t = t + 1] = token(,, .eSubordinatingConjunction)
*           tok[t = t + 1] = token(,, .eCorrelativeConjunctions)
            tok[t = t + 1] = token(,, .eConjunctiveAdverb)

            tok[t = t + 1] = token(,, .eDemonstrativeAdjective)
            tok[t = t + 1] = token(,, .eDescriptiveAdjective)
            tok[t = t + 1] = token(,, .eIndefiniteAdjective)
            tok[t = t + 1] = token(,, .eNumericalAdjective)
            tok[t = t + 1] = token(,, .ePossessiveAdjective)
            tok[t = t + 1] = token(,, .eProperAdjective)
            tok[t = t + 1] = token(,, .eAdjective)

            tok[t = t + 1] = token(,, .eMultiplier)
            tok[t = t + 1] = token(,, .eFractionionalExpression)
            tok[t = t + 1] = token(,, .eIntensifier)
            tok[t = t + 1] = token(,, .ePredeterminer)

            tok[t = t + 1] = token(,, .ePreposition)
            tok[t = t + 1] = token(,, .eAdverb)

            tok[t = t + 1] = token(,, .ePersonNoun)
            tok[t = t + 1] = token(,, .ePlaceNoun)
            tok[t = t + 1] = token(,, .eThingNoun)
            tok[t = t + 1] = token(,, .eTimeNoun)
            tok[t = t + 1] = token(,, .eProperNoun)
            tok[t = t + 1] = token(,, .eSubjectPersonalPronoun)
            tok[t = t + 1] = token(,, .ePossessivePersonalPronoun)
            tok[t = t + 1] = token(,, .eObjectPersonalPronoun)
            tok[t = t + 1] = token(,, .ePersonalPronoun)
            tok[t = t + 1] = token(,, .eReflexiveIntensivePronoun)
            tok[t = t + 1] = token(,, .eDemonstrativePronoun)
            tok[t = t + 1] = token(,, .eRelativePronoun)
            tok[t = t + 1] = token(,, .eInterrogativePronoun)
            tok[t = t + 1] = token(,, .eIndefiniteSingularPronoun)
            tok[t = t + 1] = token(,, .eIndefinitePluralPronoun)
            tok[t = t + 1] = token(,, .eIndefiniteEitherPronoun)
            tok[t = t + 1] = token(,, .eIndefinitePronoun)
            tok[t = t + 1] = token(,, .eReciprocalPronoun)
            tok[t = t + 1] = token(,, .ePronoun)

            tok[t = t + 1] = token(,, .eFormOfBEVerb)
            tok[t = t + 1] = token(,, .eLinkingVerb)
            tok[t = t + 1] = token(,, .eHelpingVerb)
            tok[t = t + 1] = token(,, .eAuxiliaryVerb)
            tok[t = t + 1] = token(,, .eModalVerb)
            tok[t = t + 1] = token(,, .eDitransitiveVerb)
            tok[t = t + 1] = token(,, .eDictVerb)
            tok[t = t + 1] = token(,, .eVerb)

            tok[t = t + 1] = token(,, .eNumber)
            tok[t = t + 1] = token(,, .eDQString)
            tok[t = t + 1] = token(,, .eSQString)
*           tok[t = t + 1] = token(, *('$"' tx "'s" '"'), *eKnownWord . tx "'s")
*           tok[t = t + 1] = token(, *("'" tx "'"),  *eKnownWord . tx)
*           tok[t = t + 1] = token(, *('$"' tx "'s" '"'), *eWord . tx "'s")
*           tok[t = t + 1] = token(, *("$'" tx "'"), *eWord . tx)
*           tok[t = t + 1] = token("Noun", *("Noun"), eWord $ eWrd $ *EngIsNoun(eWrd))
*           tok[t = t + 1] = token("Adj",  *("Adj"),  eWord $ eWrd $ *EngIsAdj(eWrd))
*           tok[t = t + 1] = token("Adv",  *("Adv"),  eWord $ eWrd $ *EngIsAdv(eWrd))
*           tok[t = t + 1] = token("Verb", *("Verb"), eWord $ eWrd $ *EngIsVerb(eWrd))
            tok[t = t + 1] = token(, *('"' tx '"'),  *eWord . tx)
            tok[t = t + 1] = token('!')
            tok[t = t + 1] = token('$')
            tok[t = t + 1] = token('(')
            tok[t = t + 1] = token(')')
            tok[t = t + 1] = token('[')
            tok[t = t + 1] = token(']')
            tok[t = t + 1] = token(',')
            tok[t = t + 1] = token('-')
            tok[t = t + 1] = token('--')
            tok[t = t + 1] = token('.')
            tok[t = t + 1] = token('/')
            tok[t = t + 1] = token('*')
            tok[t = t + 1] = token(':')
            tok[t = t + 1] = token(';')
            tok[t = t + 1] = token('?')
            tok[t = t + 1] = token('=')
            tok[t = t + 1] = token('<')
            tok[t = t + 1] = token('>')
            tok[t = t + 1] = token('%')
            tok[t = t + 1] = token("'")
            tok[t = t + 1] = token('`')
            tok[t = t + 1] = token('"')

            dbg[.eActivityVerb] = TRUE
            dbg[.eAdjectivePhrase] = TRUE
            dbg[.eAdjectives] = TRUE
            dbg[.eAdverbPhrase] = TRUE
            dbg[.eAdverb] = TRUE
            dbg[.eAdverbialPhrase] = TRUE
            dbg[.eArticle] = TRUE
            dbg[.eCompletePredicate] = TRUE
            dbg[.eCompleteSubject] = TRUE
            dbg[.eCompoundSubject] = TRUE
            dbg[.eCompoundVerb] = TRUE
            dbg[.eConjunctiveAdverb] = TRUE
            dbg[.eCoordinatingConjunction] = TRUE
            dbg[.eDemonstrativePronoun] = TRUE
            dbg[.eDirectObject] = TRUE
            dbg[.eFractionionalExpression] = TRUE
            dbg[.eHelpingVerb] = TRUE
            dbg[.eIndefinitePronoun] = TRUE
            dbg[.eIndirectObject] = TRUE
            dbg[.eIntensifier] = TRUE
            dbg[.eInterrogativePronoun] = TRUE
            dbg[.eLinkingVerb] = TRUE
            dbg[.eModifiedNounOrPronoun] = TRUE
            dbg[.eModifiedNoun] = TRUE
            dbg[.eModifiedVerb] = TRUE
            dbg[.eMultiplier] = TRUE
            dbg[.eNoun] = TRUE
            dbg[.eNumber] = TRUE
            dbg[.eObjectPersonalPronoun] = TRUE
            dbg[.eObjectiveComplement] = TRUE
            dbg[.ePersonalPronoun] = TRUE
            dbg[.ePossessivePersonalPronoun] = TRUE
            dbg[.ePredeterminer] = TRUE
            dbg[.ePredicate] = TRUE
            dbg[.ePredicateAdjective] = TRUE
            dbg[.ePredicateNominative] = TRUE
            dbg[.ePreposition] = TRUE
            dbg[.ePrepositionalPhrase] = TRUE
            dbg[.ePronoun] = TRUE
            dbg[.eReciprocalPronoun] = TRUE
            dbg[.eReflexiveIntensivePronoun] = TRUE
            dbg[.eRelativePronoun] = TRUE
            dbg[.eSentence] = TRUE
            dbg[.eDQString] = TRUE
            dbg[.eSQString] = TRUE
            dbg[.eSubjectPersonalPronoun] = TRUE
            dbg[.eSubject] = TRUE
            dbg[.eSubordinatingConjunction] = TRUE
            dbg[.eVerb] = TRUE

                                                                                             :(RETURN)
UserTokensEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
