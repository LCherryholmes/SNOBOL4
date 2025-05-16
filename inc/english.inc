*---------- ----------------- ----- -------------------------------------------------------- ---------------------------
            DEFINE('Lexicon(wordpat,lexemes)lexeme,lexPart,lexRest')                         :(LexiconEnd)
Lexicon     lexemes           POS(0) RPOS(0)                                                 :S(RETURN)
            lexemes           POS(0) (BREAK('/') . lexeme '/' | RTAB(0) . lexeme) =          :F(RETURN)
            IDENT(lexeme)                                                                    :S(Lexicon)
            DIFFER(dict[lexeme])                                                             :F(Lexicon5)
*           OUTPUT            =     'Removing: '  lexeme '(' dict[lexeme] ')'
            dict[lexeme]      =
Lexicon5    $lexeme           =
            lexRest           =     lexeme
Lexicon10   lexRest           POS(0) RPOS(0)                                                 :S(Lexicon)
            lexRest           POS(0) ' ' =                                                   :S(Lexicon20)
            lexRest           POS(0) '-' =                                                   :S(Lexicon30)
            lexRest           POS(0) '.' =                                                   :S(Lexicon40)
            lexRest           POS(0) "'" =                                                   :S(Lexicon50)
            lexRest           POS(0) BREAK(' -.' "'") . lexPart =                            :S(Lexicon60)
            lexRest           POS(0) RTAB(0) . lexPart =                                     :S(Lexicon60)
Lexicon20   $lexeme           =     $lexeme $' '                                             :(Lexicon10)
Lexicon30   $lexeme           =     $lexeme '-'                                              :(Lexicon10)
Lexicon40   $lexeme           =     $lexeme '.'                                              :(Lexicon10)
Lexicon50   $lexeme           =     $lexeme "'"                                              :(Lexicon10)
Lexicon60   $lexeme           =     DIFFER($lexeme) $lexeme lexPart                          :S(Lexicon10)
            $lexeme           =     IDENT($lexeme) $' ' TU(2, wordpat, lexPart)              :(Lexicon10)
LexiconEnd
*---------- ----------------- ----- -------------------------------------------------------- ---------------------------
            space             =     SPAN(' ')
            white             =     SPAN(' ')
            whitespace        =     SPAN(' ')
            $'  '             =     FENCE(space | epsilon)
            $' '              =     FENCE(white | epsilon)
            eWordSegment      =     SPAN(&UCASE &LCASE)
            eWordSegments     =     *eWordSegment FENCE('-' *eWordSegments | epsilon)
            eWord             =     *eWordSegment FENCE('-' *eWordSegments | epsilon)
            eUnknownWord      =     eWord $ tx $ *notmatch(eWords, '/' (tx | lwr(tx)) '/')
            eKnownWord        =     eWord $ tx $ *match(eWords,    '/' (tx | lwr(tx)) '/')
            eDQString         =     '"' BREAK('"') '"'
            eSQString         =     "`" BREAK("'") "'" | "'" BREAK("'") "'"
            eNumber           =     SPAN('0123456789')

            eWords            =     '/'
+           "I/Shakespear/William/Winifred/children's/"
+           'a/about/above/accordingly/across/after/again/against/all/along/also/although/am being/am/among/an/and/'
+           'another/any/anybody/anyone/anything/appear/are being/are/as/at/be/because/become/before/beneath/beside/'
+           'besides/beyond/both/but also/but/by/can be/can/cause/consequently/could be/could have been/could/'
+           'did/do/does/double/down/each other/each/either/enough/even/every/everybody/everyone/everything/except/feel/'
+           'few/finally/five/for/four/fourth/from/furthermore/give/grow/had been/had/half/has been/has/have been/have/'
+           'he/her/hers/herself/him/himself/his/however/hundred/if/in/indeed/inside/into/is being/is/it/its/itself/'
+           'less/little/long/look/many/may be/may have been/may/me/might be/might have been/might/mine/more/'
+           'moreover/most/much/must be/must have been/must/my/myself/near/neither/nevertheless/next to/no one/nobody/'
+           'none/nor/not only/not/nothing/now/of/on/once/one another/one/one-third/oneself/only/or/order/other/others/'
+           'otherwise/our/ours/ourselves/out/over/quite/rather/remain/result/seem/several/shall be/shall have been/'
+           'shall/she/should be/should have been/should/since/smell/so/some/somebody/someone/something/'
+           'soon/sound/stay/such/taste/ten/than/that/the/their/theirs/them/themselves/then/there/therefore/these/they/this/'
+           'those/though/thousand/three/three-quarters/through/thus/till/times/to/toward/turn/twice/two/'
+           'under/unless/until/upon/us/was being/was/we/were being/were/what/when/whenever/where/whereas/wherever/whether/'
+           'which/while/who/whom/whose/why/will be/will have been/will/with/without/would be/would have been/would/'
+           'yet/you/your/yours/yourself/yourselves/zero/'

            $'!'              =     $' ' '!'
            $'$'              =     $' ' '$'
            $'('              =     $' ' '('
            $')'              =     $' ' ')'
            $','              =     $' ' ','
            $'-'              =     $' ' '-'
            $'--'             =     $' ' '--'
            $'.'              =     $' ' '.'
            $'/'              =     $' ' '/'
            $':'              =     $' ' ':'
            $';'              =     $' ' ';'
            $'?'              =     $' ' '?'

            Dict()
            CideText()
            dict['A'] =
            dict['As'] =
            dict['In'] =
            dict['les'] =
            dict['unde'] =
            dict['i'] =
            Lexicon(eWord, eWords)
*===================================================================================================
*
*     NOUNS
*
*     A noun is the name of a person, place, or thing. Some of the things nouns name can be seen or
*     touched; some cannot. A compound noun is a noun that is made up of more than one word either
*     separated, hyphenated, or combined.
*
      eNoun                         =  *ePersonNoun
+                                   |  *ePlaceNoun
+                                   |  *eThingNoun
+                                   |  *eTimeNoun
+                                   |  *eProperNoun
+                                   |  *eDictNoun

      eDictNoun                     =  $' ' *eWord $ eW1 $' ' *eWord $ eW2 $' ' *eWord $ eW3 $ *EngIsNoun(eW1 ' ' eW2 ' ' eW3)
+                                   |  $' ' *eWord $ eW1 $' ' *eWord $ eW2 $ *EngIsNoun(eW1 ' ' eW2)
+                                   |  $' ' *eWord $ eWrd $ *EngIsNoun(eWrd)

      ePersonNoun                   =  $'Shakespear'
+                                   |  $'William'
+                                   |  $'Winifred'

      ePlaceNoun                    =  $' ' 'Alaska'
+                                   |  $' ' 'Arizona'
+                                   |  $' ' 'Colorado'
+                                   |  $' ' 'Delaware'
+                                   |  $' ' 'Honolulu'
+                                   |  $' ' 'Nebraska'
+                                   |  $' ' 'New Jersey'
+                                   |  $' ' 'New Mexico'
+                                   |  $' ' 'Connecticut'
+                                   |  $' ' 'Puerto Rico'
+                                   |  $' ' 'North Dakota'
+                                   |  $' ' 'Rhode Island'
+                                   |  $' ' 'Massachusetts'
+                                   |  $' ' 'New Hampshire'
+                                   |  $' ' 'Maine'
+                                   |  $' ' 'Kansas'
+                                   |  $' ' 'Nevada'
+                                   |  $' ' 'Oregon'
+                                   |  $' ' 'Vermont'
+                                   |  $' ' 'Nebraska'
+                                   |  $' ' 'United States'
+                                   |  $' ' 'Washington'
+                                   |  $' ' 'Wilmington'
+                                   |  $' ' 'Bangor'
+                                   |  $' ' 'Portland'
+                                   |  $' ' 'Tucson' $',' 'Arizona'

      eParens                       =  $'(' BREAK('()') $')'
      eThingNoun                    =  $' ' 'Advisory Council on Historic Preservation'
+                                   |  $' ' 'Appalachian Housing Fund'
+                                   |  $' ' 'Capitol Building'
+                                   |  $' ' 'Capitol police'
+                                   |  $' ' 'Coast Guard Reserve'
+                                   |  $' ' 'Cochairman'
+                                   |  $' ' 'Cochairmen'
+                                   |  $' ' 'Coordinating Board'
+                                   |  $' ' 'Data Bank'
+                                   |  $' ' 'Department of Homeland Security'
+                                   |  $' ' 'Department of the Air Force'
+                                   |  $' ' 'Federal Advisory Committee Act'
+                                   |  $' ' 'Flag Day'
+                                   |  $' ' 'Fort Jefferson National Monument'
+                                   |  $' ' 'Government Accountability Office'
+                                   |  $' ' 'Government Publishing Office'
+                                   |  $' ' 'Immigration and Customs Enforcement'
+                                   |  $' ' 'Inspector General Act'
+                                   |  $' ' 'Joint Intelligence Community Council'
+                                   |  $' ' 'Kerr Memorial Arboretum and Nature Center'
+                                   |  $' ' 'Loyalty Day'
+                                   |  $' ' 'Metropolitan Medical Response Program'
+                                   |  $' ' 'National Intelligence Council'
+                                   |  $' ' 'National Portrait Gallery Commission'
+                                   |  $' ' 'National Reconnaissance Office'
+                                   |  $' ' 'Public Health Service Act'
+                                   |  $' ' 'Russell National School Lunch Act'
+                                   |  $' ' 'Smithsonian Institution'
+                                   |  $' ' 'Social Security Act'
+                                   |  $' ' 'Steelmark Month'
+                                   |  $' ' 'Under Secretary'
+                                   |  $' ' 'Wright Brothers Day'
+                                   |  $' ' 'Referenda'
+                                   |  $' ' 'FINRA'
+                                   |  $' ' 'SIPC'
+                                   |  $' ' 'campus director'
+                                   |  $' ' 'committee proceeding'
+                                   |  $' ' 'community residence'
+                                   |  $' ' 'conversion rate'
+                                   |  $' ' 'market rents'
+                                   |  $' ' 'risk assessment'
+                                   |  $' ' 'staffing agency'
+                                   |  $' ' *eNumber
+                                   |  $' ' '$' *eNumber ARBNO(',' *eNumber)
+                                   |  $' ' ('Title' | 'title') ' ' *eNumber
+                                   |  $' ' ('Paragraph' | 'paragraph') ' ' *eParens
+                                   |  $' ' ('Paragraphs' | 'paragraphs') ' ' ARBNO(*eParens)
+                                           ('and' | 'or') ARBNO(*eParens)
+                                   |  $' ' ('Section' | 'section') ' ' *eNumber ARBNO(*eParens)
+                                   |  $' ' ('Subsection' | 'subsection') ' ' ARBNO(*eParens)
+                                   |  $' ' ('Subchapter' | 'subchapter')
+                                   |  $' ' ('Subclause' | 'subclause')
+                                   |  $' ' ('Subparagraph' | 'subparagraph') ' ' ARBNO(*eParens)
+                                   |  $' ' ('Subparagraph' | 'subparagraph')
+                                   |  $' ' ('Subparagraphs' | 'subparagraphs')
+                                   |  $'order'
+                                   |  $'through' $' ' 'route'

      eDayOfWeek                    =  'Monday'
+                                   |  'Tuesday'
+                                   |  'Wednesday'
+                                   |  'Thursday'
+                                   |  'Friday'
+                                   |  'Saturday'
+                                   |  'Sunday'

      eMonth                        =  'January'
+                                   |  'February'
+                                   |  'March'
+                                   |  'April'
+                                   |  'May'
+                                   |  'June'
+                                   |  'July'
+                                   |  'August'
+                                   |  'September'
+                                   |  'October'
+                                   |  'November'
+                                   |  'December'

      eTimeNoun                     =  $' ' *eWordSegment $ tx $ *match(tx, POS(0) eMonth RPOS(0)) ' ' *eNumber ', ' *eNumber
+                                   |  $' ' *eWordSegment $ tx $ *match(tx, POS(0) eMonth RPOS(0)) (' ' *eNumber | epsilon)
+                                   |  $' ' *eWordSegment $ tx $ *match(tx, POS(0) eDayOfWeek RPOS(0))
+                                   |  $' ' 'year ' *eNumber

      eSeparatedNoun                =
      eHyphenatedNoun               =
      eCombinedNoun                 =
*
*     A common noun names any one of a class of people, places, or things. A proper noun names a
*     specific person, place, or thing. Proper nouns take capitals.
*
      eCommonNoun                   =
      eProperNoun                   =
+                                      $' ' 'co-chairs'
+                                   |  $' ' 'demonstration program'

      eCountNouns                   =  *eSingularCountNoun | *ePluralCountNoun
      eSingularCountNoun            =
      ePluralCountNoun              =
      eMassNouns                    =

      eCollectiveNoun               =
*===================================================================================================
*
*     PRONOUNS
*
*     A pronoun is a word used to take the place of a noun. The noun a pronoun substitutes for is
*     called an antecedent. Personal pronouns refer to (1) the person speaking, (2) the person
*     spoken to, or (3) the person, place, or thing spoken about.
*
      ePronoun                      =  *ePersonalPronoun
+                                   |  *eReflexiveIntensivePronoun
+                                   |  *eDemonstrativePronoun
+                                   |  *eRelativePronoun
+                                   |  *eInterrogativePronoun
+                                   |  *eIndefinitePronoun
+                                   |  *eReciprocalPronoun

      ePersonalPronoun              =  *eSubjectPersonalPronoun
+                                   |  *ePossessivePersonalPronoun
+                                   |  *eObjectPersonalPronoun
      eSubjectPersonalPronoun       =  $'I' | $'you' | $'he' | $'she' | $'it' | $'we' | $'they'
      ePossessivePersonalPronoun    =  $'mine'
+                                   |  $'yours'
+                                   |  $'his'
+                                   |  $'hers'
+                                   |  $'its'
+                                   |  $'ours'
+                                   |  $'theirs'
      eObjectPersonalPronoun        =  $'me' | $'you' | $'him' | $'her' | $'it' | $'us' | $'them'
*
*     A reflexive pronoun ends in "-self" or "-selves" and adds information to a sentence by
*     pointing back to a noun or pronoun that appears earlier in the sentence. An intensive pronoun
*     has the same ending as a reflexive pronoun but simply adds emphasis to a noun or pronoun in
*     the same sentence.
*
      eReflexiveIntensivePronoun    =  $'myself'
+                                   |  $'yourself'
+                                   |  $'himself'
+                                   |  $'herself'
+                                   |  $'itself'
+                                   |  $'oneself'
+                                   |  $'ourselves'
+                                   |  $'yourselves'
+                                   |  $'themselves'
*
*     A demonstrative pronoun directs attention to a specific person, place, or thing. A relative
*     pronoun begins a subordinate clause and connects it to another idea in the sentence. An
*     interrogative pronoun is used to begin a question.
*
      eDemonstrativePronoun         =  $'this' | $'that' | $'these' | $'those'
      eRelativePronoun              =  $'that' | $'which' | $'who' | $'whom' | $'whose' ;* when, where, why
      eInterrogativePronoun         =  $'who' | $'whom' | $'why' | $'what'
*
*     Indefinite pronouns refer to people, places, or things, often without specifying which ones.
*     Some indefinite pronouns may have an antecedent, but many do not have a specific antecedent.
*
      eIndefinitePronoun            =  *eIndefiniteSingularPronoun
+                                   |  *eIndefinitePluralPronoun
+                                   |  *eIndefiniteEitherPronoun
      eIndefiniteSingularPronoun    =  $'another'
+                                   |  $'anybody'
+                                   |  $'anyone'
+                                   |  $'anything'
+                                   |  $'each'
+                                   |  $'either'
+                                   |  $'everybody'
+                                   |  $'everyone'
+                                   |  $'everything'
+                                   |  $'little'
+                                   |  $'much'
+                                   |  $'neither'
+                                   |  $'nobody'
+                                   |  $'no one'
+                                   |  $'nothing'
+                                   |  $'one'
+                                   |  $'other'
+                                   |  $'somebody'
+                                   |  $'someone'
+                                   |  $'something'
      eIndefinitePluralPronoun      =  $'both'
+                                   |  $'few'
+                                   |  $'many'
+                                   |  $'others'
+                                   |  $'several'
      eIndefiniteEitherPronoun      =  $'all'
+                                   |  $'any'
+                                   |  $'less'
+                                   |  $'more'
+                                   |  $'most'
+                                   |  $'none'
+                                   |  $'some'

      eReciprocalPronoun            =  $'each other' | $'one another'
*===================================================================================================
*
*     VERBS
*
*     A verb is a word that expresses time while showing an action, a condition, or the fact that
*     something exists. An action verb is a verb that tells what action someone or something is
*     performing. An action verb may show mental action as well as visible action. An action verb
*     is transitive if it directs action toward someone or something. An action verb is intransitive
*     if it does not direct action toward someone or something.
*
*     1. simple present,             simple past,             simple future
*     2. present continuous,         past continuous,         future continuous
*     3. present perfect,            past perfect,            future perfect
*     4. present perfect continuous, past perfect continuous, future perfect continuous

      eVerb                         =  *eModalVerb
+                                   |  *eModalVerb *eDictVerb
+                                   |  *eLinkingVerb
+                                   |  *eFormOfBEVerb
+                                   |  *eFormOfBEVerb *eDictVerb
+                                   |  *eHelpingVerb *eDictVerb
*+                                  |  $'made' *eDictAdjective

      eDictVerb                     =  $' ' *eWord $ eW1 $' ' *eWord $ eW2 $' ' *eWord $ eW3 $ *EngIsVerb(eW1 ' ' eW2 ' ' eW3)
+                                   |  $' ' *eWord $ eW1 $' ' *eWord $ eW2 $ *EngIsVerb(eW1 ' ' eW2)
+                                   |  $' ' *eWord $ eWrd $ *EngIsVerb(eWrd)
+                                   |  $' ' 'reappointed'
+                                   |  $' ' 'redelegated'

*     eMainVerb                     =  *eTransitiveVerb | *eIntransitiveVerb
*     eTransitiveVerb               =
*     eIntransitiveVerb             =

      eModalVerb                    =  $'can'         | $'can' $'not'
+                                   |  $'could'       | $'could' $'not'
+                                   |  $'may'         | $'may' $'not'
+                                   |  $'might'       | $'might' $'not'
+                                   |  $'shall'       | $'shall' $'not'
+                                   |  $'should'      | $'should' $'not'
+                                   |  $'will'        | $'will' $'not'
+                                   |  $'would'       | $'would' $'not'

*     A linking verb is a verb that connects a word at or near the beginning of a sentence with a
*     word at or near the end. In English, the most common linking verb is some form of "be".
*     Other verbs may be used in the same was as "be" to link two parts of a sentence.

      eLinkingVerb                  =  $'appear'
+                                   |  $'become'
+                                   |  $'feel'
+                                   |  $'grow'
+                                   |  $'look'
+                                   |  $'remain'
+                                   |  $'seem'
+                                   |  $'smell'
+                                   |  $'sound'
+                                   |  $'stay'
+                                   |  $'taste'
+                                   |  $'turn'

*     Helping verbs are verbs that can be added to another verb to make a single verb phrase. Any of
*     the many forms of "be" as well as some other common verbs can be used as helping verbs.
      eHelpingVerb                  = $'do'     $'not' | $'do'
+                                   | $'does'   $'not' | $'does'
+                                   | $'did'    $'not' | $'did'
+                                   | $'have'   $'not' | $'have'
+                                   | $'has'    $'not' | $'has'
+                                   | $'had'    $'not' | $'had'
+                                   | $'shall'  $'not' | $'shall'
+                                   | $'should' $'not' | $'should'
+                                   | $'will'   $'not' | $'will'
+                                   | $'would'  $'not' | $'would'
+                                   | $'can'    $'not' | $'can'
+                                   | $'could'  $'not' | $'could'
+                                   | $'may'    $'not' | $'may'
+                                   | $'might'  $'not' | $'might'
+                                   | $'must'   $'not' | $'must'

      eFormOfBEVerb                 =  $'am'     $'not'                 | $'am'
+                                   |  $'are'    $'not'                 | $'are'
+                                   |  $'is'     $'not'                 | $'is'
+                                   |  $'was'    $'not'                 | $'was'
+                                   |  $'were'   $'not'                 | $'were'
+                                   |  $'am'     $'not' $'being'        | $'am being'
+                                   |  $'are'    $'not' $'being'        | $'are being'
+                                   |  $'is'     $'not' $'being'        | $'is being'
+                                   |  $'was'    $'not' $'being'        | $'was being'
+                                   |  $'were'   $'not' $'being'        | $'were being'
+                                   |  $'can'    $'not' $'be'           | $'can be'
+                                   |  $'could'  $'not' $'be'           | $'could be'
+                                   |  $'may'    $'not' $'be'           | $'may be'
+                                   |  $'might'  $'not' $'be'           | $'might be'
+                                   |  $'must'   $'not' $'be'           | $'must be'
+                                   |  $'shall'  $'not' $'be'           | $'shall be'
+                                   |  $'should' $'not' $'be'           | $'should be'
+                                   |  $'will'   $'not' $'be'           | $'will be'
+                                   |  $'would'  $'not' $'be'           | $'would be'
+                                   |  $'have'   $'not' $'been'         | $'have been'
+                                   |  $'has'    $'not' $'been'         | $'has been'
+                                   |  $'had'    $'not' $'been'         | $'had been'
+                                   |  $'could'  $'not' $'have' $'been' | $'could have been'
+                                   |  $'may'    $'not' $'have' $'been' | $'may have been'
+                                   |  $'might'  $'not' $'have' $'been' | $'might have been'
+                                   |  $'must'   $'not' $'have' $'been' | $'must have been'
+                                   |  $'shall'  $'not' $'have' $'been' | $'shall have been'
+                                   |  $'should' $'not' $'have' $'been' | $'should have been'
+                                   |  $'will'   $'not' $'have' $'been' | $'will have been'
+                                   |  $'would'  $'not' $'have' $'been' | $'would have been'

      eAuxiliaryVerb                =  $'be' | $'do' | $'have'

      eDitransitiveVerb             =  $'cause' | $'give'
      eFiniteVerb                   =
      eNonFiniteVerb                =
      eDynamicVerb                  =  *eActivityVerb
+                                   |  *eProcessVerb
+                                   |  *eBodilySensationVerb
+                                   |  *eTransitionalEventVerb
+                                   |  *eMomentaryVerb
      eStativeVerb                  =  *eCognitionVerb
+                                   |  *eRelationalVerb
      eActivityVerb                 =
      eProcessVerb                  =
      eBodilySensationVerb          =
      eTransitionalEventVerb        =
      eMomentaryVerb                =
      eCognitionVerb                =
      eRelationalVerb               =
*===================================================================================================
*
*     ADJECTIVES
*
      eAdjectives                   =  *eAdjective (*eAdjectives | epsilon)
      eAdjective                    =  *eArticle
+                                   |  *eIntensifier
+                                   |  *ePredeterminer
+                                   |  *eDemonstrativeAdjective
+                                   |  *eDescriptiveAdjective
+                                   |  *eIndefiniteAdjective
+                                   |  *eNumericalAdjective
+                                   |  *ePossessiveAdjective
+                                   |  *eProperAdjective
+                                   |  *eDictAdjective

      eDictAdjective                =  $' ' *eWord $ eW1 $' ' *eWord $ eW2 $' ' *eWord $ eW3 $ *EngIsAdj(eW1 ' ' eW2 ' ' eW3)
+                                   |  $' ' *eWord $ eW1 $' ' *eWord $ eW2 $ *EngIsAdj(eW1 ' ' eW2)
+                                   |  $' ' *eWord $ eWrd $ *EngIsAdj(eWrd)

      eArticle                      =  $'a' | $'an' | $'the'
      eIntensifier                  =  $'quite' | $'rather' | $'such'
      ePredeterminer                =  *eMultiplier | *eFractionionalExpression | $'both' | $'half' | $'all'
      eMultiplier                   =  $'double' | $'twice' | $'four' $'times' | $'five' $'times'
      eFractionionalExpression      =  $'one-third' | $'three-quarters'
*
*     A noun used as an adjective answers the question "What kind?" or "Which one?" about a noun
*     that follows it. A proper adjective is a proper noun used as an adjective or an adjective
*     formed from a proper noun. A compound adjective is an adjective made up of more than one word.
*
      eNounAdjective                =
      eProperAdjective              =  '?'
      eCompoundAdjective            =
*
*     A pronoun is used as an adjective if it modifies a noun. A personal pronoun used as a
*     possesssive adjective answers the question "Which one?" about a noun that follows it.
*
      ePossessiveAdjective          =  $'my'
+                                   |  $'your'
+                                   |  $'his'
+                                   |  $'her'
+                                   |  $'its'
+                                   |  $'our'
+                                   |  $'their'
+                                   |  $"children's"
*
*     A demonstrative, interrogative, or indefinite pronoun used as an adjective anwers the question
*     "Which one?", "How many?", or "How much?" about the noun that follows it.
*
      eDemonstrativeAdjective       =  $'this' | $'that' | $'these' | $'those'
      eInterrogativeAdjective       =  $'what' | $'which' | $'whose'
      eIndefiniteAdjective          =  $'all'
+                                   |  $'another'
+                                   |  $'any'
+                                   |  $'both'
+                                   |  $'each'
+                                   |  $'either'
+                                   |  $'enough'
+                                   |  $'every'
+                                   |  $'few'
+                                   |  $'less'
+                                   |  $'many'
+                                   |  $'more'
+                                   |  $'most'
+                                   |  $'much'
+                                   |  $'neither'
+                                   |  $'other'
+                                   |  $'several'
+                                   |  $'some'
+                                   |  $'what'
+                                   |  $'which'

      eDescriptiveAdjective         =  $' ' 'agency-specific'
+                                   |  $' ' 'below-market'
+                                   |  $' ' 'asbestos-containing'
+                                   |  $' ' 'career-conditional'
+                                   |  $' ' 'crosscutting'
+                                   |  $' ' 'employer-sponsored'
+                                   |  $' ' 'medium-sized'
+                                   |  $' ' 'merit-based'
+                                   |  $' ' 'merit-reviewed'
+                                   |  $' ' 'multiyear'
+                                   |  $' ' 'non-criminal'
+                                   |  $' ' 'non-federal'
+                                   |  $' ' 'out-of-area'
+                                   |  $' ' 'public-private'
+                                   |  $' ' 'refundable'
+                                   |  $' ' 'security-based'
+                                   |  $' ' 'self-closing'
+                                   |  $' ' 'self-latching'
+                                   |  $' ' 'sixteen-year-old'
+                                   |  $' ' 'three-year'
+                                   |  $' ' *eNumber '-year'

      eNumericalAdjective           =  $'four'
+                                   |  $'five'
+                                   |  $'five' $'hundred'
+                                   |  $'fourth'
+                                   |  $'one'
+                                   |  $'ten'
+                                   |  $'three'
+                                   |  $'two'
+                                   |  $'zero'
+                                   |  $'thousand'
+                                   |  $' ' *eNumber
*===================================================================================================
*
*     ADVERBS
*
*     An adverb is a word that modifies a verb, an adjective, or another adverb. An adverb
*     modifying a verb answers the question "Where?", "When?", "In what manner?", or
*     "To what extent?". An adverb modifying an adjective answers only one question:
*     "To what extent?". An adverb modifying another adverb also answers just one question:
*     "To what extent?".
*
      eAdverbs                      =  *eAdverb (*eAdverbs | epsilon)
      eAdverb                       =  $' ' *eWord $ eW1 $' ' *eWord $ eW2 $' ' *eWord $ eW3 $ *EngIsAdv(eW1 ' ' eW2 ' ' eW3)
+                                   |  $' ' *eWord $ eW1 $' ' *eWord $ eW2 $ *EngIsAdv(eW1 ' ' eW2)
+                                   |  $' ' *eWord $ eWrd $ *EngIsAdv(eWrd)
*===================================================================================================
*
*     PREPOSITIONS
*
*     A preposition is a word that relates a noun or pronoun that appears with it to another word in
*     the sentence. The choice of preposition affects the way the other words in a sentence relate
*     to each other.
*
      ePreposition                  =  $'about'
+                                   |  $'against'
+                                   |  $'above'
+                                   |  $'across'
+                                   |  $'after'
+                                   |  $'among'
+                                   |  $'beneath'
+                                   |  $'beside'
+                                   |  $'beyond'
+                                   |  $'by'
+                                   |  $'down'
+                                   |  $'except'
+                                   |  $'for'
+                                   |  $'from'
+                                   |  $'in'
+                                   |  $'inside'
+                                   |  $'into'
+                                   |  $'near'
+                                   |  $'next to'
+                                   |  $'of'
+                                   |  $'on'
+                                   |  $'out'
+                                   |  $'over'
+                                   |  $'since'
+                                   |  $'to'
+                                   |  $'toward'
+                                   |  $'under'
+                                   |  $'upon'
+                                   |  $'until'
+                                   |  $'with'
+                                   |  $'without'
+                                   |  $'along'
+                                   |  $'through'
+                                   |  $'at'
*===================================================================================================
*
*     CONJUNCTIONS
*
      eConjunction                  =  *eCoordinatingConjunction
+                                   |  *eSubordinatingConjunction

      eCoordinatingConjunction      =  $'and'
+                                   |  $'or'
+                                   |  $'for'
+                                   |  $'nor'
+                                   |  $'so'
+                                   |  $'but'
+                                   |  $'yet'
      eSubordinatingConjunction     =  $'after'
+                                   |  $'although'
+                                   |  $'as' $'if'
+                                   |  $'as' $'long' $'as'
+                                   |  $'as' $'soon' $'as'
+                                   |  $'as' $'though'
+                                   |  $'as'
+                                   |  $'because'
+                                   |  $'before'
+                                   |  $'even' $'if'
+                                   |  $'even' $'though'
+                                   |  $'if' $'only'
+                                   |  $'if'
+                                   |  $'in' $'order' $'that'
+                                   |  $'now' $'that'
+                                   |  $'once'
+                                   |  $'rather' $'than'
+                                   |  $'since'
+                                   |  $'so' $'that'
+                                   |  $'than'
+                                   |  $'that'
+                                   |  $'though'
+                                   |  $'till'
+                                   |  $'unless'
+                                   |  $'until'
+                                   |  $'when'
+                                   |  $'whenever'
+                                   |  $'where'
+                                   |  $'whereas'
+                                   |  $'wherever'
+                                   |  $'whether'
+                                   |  $'while'
      eCorrelativeConjunctions      =  $'both' $'and'
+                                   |  $'not only' $'but also'
+                                   |  $'not' $'but'
+                                   |  $'either' $'or'
+                                   |  $'neither' $'nor'
+                                   |  $'whether' $'or'
+                                   |  $'as' $'as'
*===================================================================================================
*
*     INTERJECTIONS
*
      eConjunctiveAdverb            =  $'however'
+                                   |  $'moreover'
+                                   |  $'nevertheless'
+                                   |  $'consequently'
+                                   |  $'as' $'a' $'result'
+                                   |  $'accordingly'
+                                   |  $'again'
+                                   |  $'also'
+                                   |  $'besides'
+                                   |  $'consequently'
+                                   |  $'finally'
+                                   |  $'furthermore'
+                                   |  $'however'
+                                   |  $'indeed'
+                                   |  $'moreover'
+                                   |  $'nevertheless'
+                                   |  $'otherwise'
+                                   |  $'then'
+                                   |  $'therefore'
+                                   |  $'thus'

      eInterjection                 =
*===================================================================================================
*
*     SENTENCE
*
*     The two fundamental parts of every English sentence are the complete subject and the
*     predicate.  The complete subject is normally the topic of the sentence, and the predicate is
*     what is asserted of that topic.

      eCompleteSentence = *eCompleteSubject *eCompletePredicate $'.'

*     The complete subject is the entire noun phrase, including the head noun and any modifiers
*     (e.g., "the" and "few") of that noun, that occurs in subject position in a sentence.
*     The simple subject is the essential noun, pronoun, or group of words acting as a noun that
*     cannot be left out of the complete subject. The simple predicate is the essential verb or verb
*     phrase that cannot be left out of the complete predicate.

      eCompleteSubject              =  *eCompoundSubject ;* *eSubject ;*
      eCompletePredicate            =  *ePredicate

      eSubject                      =  *eModifiedNounOrPronoun
      ePredicate                    =  *eModifiedVerb
+                                      (  *eDirectObject (*eObjectiveComplement | epsilon)
+                                      |  *eIndirectObject *eDirectObject
+                                      |  epsilon
+                                      )
+                                   |  (*eLinkingVerb | *eFormOfBEVerb)
+                                      (*eAdverbs | epsilon)
+                                      (  *ePredicateNominative
+                                      |  *ePredicateAdjective
+                                      )

      eModifiedVerb                 =  *eAdverbs *eDictVerb
+                                   |  *eDictVerb (*eAdverbialPhrase | $'only' | epsilon)
      eAdverbialPhrase              =  *eAdverb | *ePrepositionalPhrase
      eIndirectObject               =  *eModifiedNounOrPronoun
      eDirectObject                 =  *eModifiedNounOrPronoun

*     A predicate nominative is a noun or pronoun that follows a linking verb and renames,
*     identifies, or explains the subject of a sentence. A predicate adjective is an adjective that
*     follows a linking verb and describes the subject of the sentence.
      ePredicateNominative          =  *eModifiedNoun | *eModifiedPronoun
      ePredicateAdjective           =  *eAdjective | *eAdjectivalPhrase
      eAdjectivalPhrase             =  *eAdjectives | *ePrepositionalPhrase | *eParticipialPhrase

*     An objective complement is an adjective, noun, or group of words acting as a noun that follows
*     a direct object and describes or renames it.
      eObjectiveComplement          =  *eAdjective | *eModifiedNoun
      eObjectiveComplement          =  *eNoun | *eAdjective

*     A compound subject is two or more subjects that have the same verb and are joined by a
*     conjunction such as "and" or "or".
      eCompoundSubject              =  *eCompoundOrSubject | *eCompoundAndSubject
      eCompoundOrSubject            =  *eSubject (($',' !$'or' | $'or') *eCompoundOrSubject | epsilon)
      eCompoundAndSubject           =  *eSubject (($',' !$'and' | $'and') *eCompoundAndSubject | epsilon)

*     A compound verb is two or more verbs that have the same subject and are joined by a
*     conjunction such as "and" or "or".
      eCompoundVerb                 =  *eAdverbs
+                                      (*eCompoundOrVerb | *eCompoundAndVerb)
+                                   |  (*eCompoundOrVerb | *eCompoundAndVerb)
+                                      (*eAdverbialPhrase | epsilon)
      eCompoundOrVerb               =  *eDictVerb (($',' !$'or' | $'or') *eCompoundOrVerb | epsilon)
      eCompoundAndVerb              =  *eDictVerb (($',' !$'and' | $'and') *eCompoundAndVerb | epsilon)

*     Sentences can be:
*
*     Simple: One independent clause (subject or verb or both may be compound)
*     Compound: Two or more independent clauses
*     Complex: One independent clause and one or more subordinate clauses
*     Compound-Complex: Two or more independent clauses and one or more subordinate clauses.
*
      eIndependentClause            =  *eCompoundSubject *eCompoundVerb
      eSimpleSentence               =  *eIndependentClause
      eCompoundSentence             =  *eIndependentClause
+                                      (  !$',' $'and' *eCompoundAndClauses
+                                      |  !$',' $'or'  *eCompoundOrClauses
+                                      )
      eCompoundAndClauses           =  *eIndependentClause (!$',' $'and' *eCompoundAndClauses | epsilon)
      eCompoundOrClauses            =  *eIndependentClause (!$',' $'or' *eCompoundOrClauses | epsilon)
      eComplexSentence              =  *eIndependentClause *eSubordinateClauses
      eCompoundComplexSentence      =  *eComplexSentence
+                                      (  !$',' $'and' *eCompoundAndSentences
+                                      |  !$',' $'or' *eCompoundOrSentences
+                                      )
      eCompoundAndSentences         =  *eComplexSentence (!$',' $'and' *eCompoundAndSentences | epsilon)
      eCompoundOrSentences          =  *eComplexSentence (!$',' $'or' *eCompoundOrSentences | epsilon)
      eSubordinateClauses           =  *eSubordinateClause (!$',' *eSubordinateClauses | epsilon)
      eSubordinateClause            =  *eRelativePronoun
+                                      (  *eFormOfBEVerb *eModifiedNoun
+                                      |  *eDictVerb *eModifiedNoun
+                                      )
+                                   |  *eSubordinatingConjunction
+                                      (  *eAdjective
+                                      |  *eDictVerb *eModifiedNoun
+                                      )

*     There are six basic sentence patterns in English. The patterns differ on the basis of what
*     type of complement structure they have within the predicate.
*     The first pattern is the simplest -- one without a verb complement, as verb complements are defined in traditional grammar.
*     The second pattern has as its defining characteristic the presence of a direct object.
*         Direct objects are noun phrases that come after the verb.
*     The third pattern has as its defining characteristic the presence of both indirect and direct objects.
*         Indirect objects do always come immediately after the verb.
*     The fourth pattern has as its defining characteristic the presence of a predicate nominative verb complement.
*         The predicate nominative is a noun or a pronoun that redefines, renames, or classifies the subject of the sentence.
*         The verb in a predicate nominative construction is always a linking verb, such as be, seem, or become.
*     The fifth pattern has as its defining characteristic the presence of a predicate adjective verb complement.
*         The predicate adjective is an adjective that characterizes the subject of the sentence.
*         The verb in a predicate adjective construction, like the verb in a predicate nominative construction,
*         is always a linking verb, such as be, seem, smell, look, taste, or become.
*     The sixth pattern has as its defining characteristic the presence as verb complements of both a direct object
*         and an objective complement.
*         We met the direct object earlier.
*         An objective complement is a noun or an adjective that occurs after the direct object and that describes the direct object.

      eBasicSentence =
+     ( *eSubject *eVerb
+     | *eSubject *eVerb *eDirectObject
+     | *eSubject *eVerb *eIndirectObject *eDirectObject
+     | *eSubject *eLinkingVerb *ePredicateNominative
+     | *eSubject *eLinkingVerb *ePredicateAdjective
+     | *eSubject *eVerb *eDirectObject *eObjectiveComplement
+     )

*     Sentences can also be classified by their function.
*
*     Declarative: States and idea. Ends in a period.
*     Interrogative: Asks a question. Ends in a question mark.
*     Imperative: Gives an order or a direction. Ends in a period or an exclamation mark.
*     Exclamatory: Conveys strong emotion.  Ends in an exclamation mark.

      ePlaySentence =
+     (  *eCompleteSubject $'has' *eModifiedNoun
+     |  *eCompleteSubject *eModalVerb *eDictVerb
+     |  *eCompleteSubject *eModalVerb *eDictVerb *eModifiedNoun
+     |  *eCompleteSubject *eModalVerb *eDictVerb *ePreposition *eNoun
+     |  *eCompleteSubject *eDictVerb *eModifiedNoun
+     |  *eCompleteSubject *eDictVerb *ePrepositionalPhrase
+     |  *eCompleteSubject *eFormOfBEVerb *eModifiedNoun
+     |  *eCompleteSubject *eFormOfBEVerb *eModifiedNoun *eModifiedNoun
+     |  *eCompleteSubject *eFormOfBEVerb *eModifiedVerb
+     |  *eCompleteSubject *eFormOfBEVerb *eAdjective
+     |  *eCompleteSubject *eFormOfBEVerb *ePrepositionalPhrase
+     |  *eCompleteSubject *eFormOfBEVerb *eDictVerb $'as' *DictVerb
+     |  *eCompleteSubject *eFormOfBEVerb *eDictVerb $'to' $'be' *eAdjective
+     |  *eCompleteSubject *eFormOfBEVerb *eDictVerb *eAdverb $'to' *eDictVerb *eModifiedNoun
+     |  *eCompleteSubject *ePrepositionalPhrase *eFormOfBEVerb *eModifiedNoun
+     |  *eCompleteSubject ($'shall' | $'must' | $'does') ($'not' | epsilon) $'have'    *eModifiedNoun
+     |  *eCompleteSubject ($'shall' | $'must' | $'does') ($'not' | epsilon) *eDictVerb *eModifiedNoun
+     |  *eCompleteSubject ($'shall' | $'must' | $'does') ($'not' | epsilon) *eDictVerb *ePrepositionalPhrase
+     |  $'there' *eFormOfBEVerb *eModifiedNoun
+     )
+     $'.'

*     A direct object is a noun, pronoun, or group of words acting as a noun that receives the
*     action of a transitive verb. A compound direct object is more that one direct object that
*     receives the action of the same transitive verb. A direct object is never the noun or pronoun
*     at the end of a prepositional phrase.
      eCompoundDirectObject         =  *eCompoundOrDirectObject | *eCompoundAndDirectObject
      eCompoundOrDirectObject       =  *eDirectObject (!$',' $'or' *eCompoundOrDirectObject | epsilon)
      eCompoundAndDirectObject      =  *eDirectObject (!$',' $'and' *eCompoundAndDirectObject | epsilon)

*     An indirect object is a noun or pronoun that appears with a direct object and names the person
*     or thing that something is given to or done for. A compound indirect object is two or more
*     nouns or pronouns that appear with a direct object and name the people or things that
*     something is given to or done for. An indirect object never follows the word "to" or "for".
      eCompoundIndirectObject       =  *eCompoundOrIndirectObject | *eCompoundAndIndirectObject
      eCompoundOrIndirectObject     =  *eIndirectObject (!$',' $'or' *eCompoundOrIndirectObject | epsilon)
      eCompoundAndIndirectObject    =  *eIndirectObject (!$',' $'and' *eCompoundAndIndirectObject | epsilon)

*     A compound predicate nominative is two or more nouns or pronouns that follow a linking verb
*     and rename the subject of the sentence. A compound predicate adjective is two or more
*     adjectives that follow a linking verb and describe the subject of the sentence.
      eCompoundPredicateNominative    = *eCompoundOrPredicateNominative | *eCompoundAndPredicateNominative
      eCompoundOrPredicateNominative  = *ePredicateNominative (!$',' $'or' *eCompoundOrPredicateNominative | epsilon)
      eCompoundAndPredicateNominative = *ePredicateNominative (!$',' $'and' *eCompoundAndPredicateNominative | epsilon)

      eCompoundPredicateAdjective    = *eCompoundOrPredicateAdjective | *eCompoundAndPredicateAdjective
      eCompoundOrPredicateAdjective  = *ePredicateAdjective (!$',' $'or' *eCompoundOrPredicateAdjective | epsilon)
      eCompoundAndPredicateAdjective = *ePredicateAdjective (!$',' $'and' *eCompoundAndPredicateAdjective | epsilon)

*===================================================================================================
*
*     PHRASES
*
*     A phrase is a group of words, without a subject and verb, that acts as one part of speech.
*
*     eModifiedNoun                 =  *eAdjectivalPhrase *eNoun | *eGerundivePhrase
      eModifiedNoun                 =  (*eAdjectives | epsilon)
+                                      (*eNoun (*eNoun (*eNoun | epsilon) | epsilon) | epsilon)
+                                      *eNoun
+                                      (*eAdjectivePhrase | epsilon)
      eModifiedPronoun              =  (*eAdjectives | epsilon) *ePronoun (*eAdjectivePhrase | epsilon)
      eModifiedNounOrPronoun        =  (*eModifiedNoun | *eModifiedPronoun)

      eNounModifier                 =  *eAdjectives
+                                   |  *eNoun
*+                                  |  *eParticipialPhrase
*+                                  |  *eInfinitivePhrase
*+                                  |  *eModifyingClause
*+                                  |  *ePrepositionalPhrase
      eModifyingClause              =  '?'

      eVerbPhrase                   =  *eAdverbialPhrase *eDictVerb
*
*     An adjective phrase is a prepositional phrase that modifies a noun or pronoun by telling what
*     kind or which one.
      eAdjectivePhrase              =  *ePrepositionalPhrase
*
*     An adverb phrase is a prepositional phrase that modifies a verb, adjective, or adverb by
*     pointing out where, when, in what manner, or to what extent.
      eAdverbPhrase                 =  *ePrepositionalPhrase
*
*     An appositive is a noun or pronoun placed next to another noun or pronoun to identify, rename,
*     or explain it.  An appositive phrase is an appositive with modifiers.
      eAppositive                   =  *eNoun | *ePronoun
      eAppositivePhrase             =  *eModifiedNoun
*
*     A compound appositive is two or more appositives or appositive phrases connected by a
*     conjunction and used to identify the same noun or pronoun.
      eCompoundAppositive           =  *eCompoundOrAppositive | *eCompoundAndAppositive
      eCompoundOrAppositive         =  (*eAppositive | *eAppositivePhrase) (!$',' $'or' *eCompoundOrAppositive | epsilon)
      eCompoundAndAppositive        =  (*eAppositive | *eAppositivePhrase) (!$',' $'and' *eCompoundAndAppositive | epsilon)

*     A participle is a form of a verb that acts as an adjective and modifies a noun or pronoun. A
*     verb phrase always begins with a helping verb, but a participle acting as an adjective stands
*     by itself.
      eParticiple                   =  *eDictVerb

*     A participial phrase is a participle modified by an adverb or adverb phrase or accompanied by
*     a complement. The entire phrase acts as an adjective.
      eParticipialPhrase            =  *eParticiple (*eAdverb | *eAdverbPhrase)
*
*     A gerund is a form of a verb that acts like a noun. Words ending in "-ing" that act as nouns
*     are gerunds. They do not have helping verbs, nor do they act as adjectives.
      eGerund                       =  *ePresentParticipleVerb
*
*     A gerund phrase is a gerund with modifiers or a complement, all acting together as a noun. The
*     possessive form of a noun or pronoun is used before a gerund.
      eGerundPhrase                 =  *eGerund (*eModifiers | *eComplements)

*     An infinitive is a form of a verb that comes after the word "to" and acts as a noun,
*     adjective, or adverb. A prepositional phrase always ends with a noun or pronoun. An infinitive
*     always ends with a verb.
      eInfinitive                   =

*     An infinitive phrase is an infinitive with modifiers, complements, or a subject, all acting
*     together as a single part of speech. When an infinitive or infinitive phrase is used as the
*     direct object of certain verbs, "to" is often omitted.
      eInfinitivePhrase             =  *eInfinitive *eRootVerb $'to' (*eModifiers | *eComplements | epsilon)

*     A prepositional phrase is a group of words that includes a preposition and a noun or pronoun
*     called the object of the preposition.
      ePrepositionalPhrase          =  $'in' $' ' 'rem'
+                                   |  ( $'of' $'less' $'than'
+                                      | $'of' $'more' $'than'
+                                      | *ePreposition
+                                      ) *eModifiedNounOrPronoun

      eAbsolutePhrase               =
      eAppositivePhrase             =  $',' (*eModifiedNoun | *eGerundPhrase | *eInfinitivePhrase) $','
      eAbsolutePhrase               =  (*eNoun | *ePronoun) *eModifiers *eParticiple
      eParticipialPhrase            =  (*ePresentParticipleVerb | *ePastParticipleVerb) (*eModifiers | *eComplements)

*     eSentence = *eNoun $'is' $' ' *eAdjectiveParticiple('committed') *eComplement
*     eComplement = $'to' $' ' 'providing' *eAdjective *eNoun
*     $'to' *eGerund | $'to' *eAdjective
*     $'I' $'am' $'not' *collocation($' ' 'used' $'to') $'being' $' ' 'interviewed'
*     $'in' $'some' $' ' 'cultures' $',' $' ' 'people' $'are' *collocation($' ' 'accustomed' $'to') $' ' 'taking' 'their' 'shoes' 'off' 'inside' 'the' 'home'
*     $'the' 'neighbourhood' 'was' 'divided' 'into' 'warring' 'factions'
*     'interested' 'in' 'doing'
*     'concerned' 'about' 'giving'
*     $'I' 'need' 'to' 'do'
*     ePreposition = 'under' | 'below' | 'beneath' | 'underneath'
*     eTransition = 'thereby' | 'thereof' | 'thereafter' | 'therein' | 'therefore'
*+                | 'wherein' | 'whereby' | 'hereby' ;* big mama
*
*     ePhrasalVerb = *eVerb *ePreposition
*+                 | 'break' | 'breakout' | 'break-in' | 'break-up' | 'breakthrough' | 'breakdown' | 'breakaway' | 'breakeven'
*+                 | 'come'
*+                   ( 'up' 'with' | 'up' 'against' | 'across' | 'around' | 'out' 'with' | 'apart'
*+                   | 'on' | 'into' | 'over' | 'in'
*+                   )
*+                 | 'kick' ('in' | 'back' | 'out' | 'off' | 'about' | 'around' | 'up' | 'over')
*+                 | 'step' ('down' | 'up' | 'in' | 'inside' | 'around' | 'out' | 'on' | 'back' | 'aside' | 'forward')
*+                 | 'bring' ('up' | 'about' | 'around' | 'back' | 'down' | 'in' | 'on' | 'off' | 'to')

*     eED_Adjective = 'bored' | 'interested' | 'excited' | 'worried' | 'confused' ;* people, animals (are the feeling)
*     eING_Adjective = 'boring' | 'interesting' | 'exciting' | 'worrying' | 'confusing' ;* people, animals, things, situations, places, ideas (cause the feeling)
*         $'I' 'am' 'bored' 'with' *eNoun 'because' *eNoun 'is' 'boring'
*         $'I' 'am' *eED_Adjective 'with' *eNoun 'because' *eNoun 'is' *eING_Adjective
*     eParticiple = eActiveParticiple | ePassiveParticiple ;* ePresentParticiple | ePastParticiple
*     eING_words used in 1. eGerund (used as eNoun) | 2. 'be' continuousVerb | 3. *eAdjective | 4. *Adverb
*         1. Wearing loose pants while riding a bicycle is dangerous. ('wearing' is noun)
*         2. The man is riding a bike. (beVerb continuousVerb, 'riding')
*         3. Wearing a blue backless dress, the actress created quite a stir at the party. ('wearing', adjective participle, subjects are same)
*         4. Not wanting to miss our flight, we arrived at the airport 3 hours early. ('wanting', adverb participle)

*     eAdjectiveParticiple is reduced eAdjectiveClause, i.e. minus eSubject and eVerb, modifies noun
*        The jazz musician, who was known for his tendency to daydream, got into a zone and played for an hour straight.
*        The jazz musician,         known for his tendency to daydream, got into a zone and played for an hour straight.
*        The woman who is talking to Jeff is his sister.
*        The woman        talking to Jeff is his sister.
*        The station chief was fired, which means there is an open position.
*        The station chief was fired, meaning     there is an open position.
*        The        window that was broken was fixed.
*        The broken window                 was fixed.
*     eAdverbParticiple is reduced eAdverbClause shows relationship between itself and independentClause
*                                    Most people, who are given the choice, would probably choose good health over good fortune.
*                                    Most people,         given the choice, would probably choose good health over good fortune.
*                  Given the choice, most people                            would probably choose good health over good fortune.
*     If they were given the choice, most people                            would probably choose good health over good fortune.
*
*             Realizing    that the police were on to him, Bernie quickly moved his millions off shore.
*     Bernie, who realized that the police were on to him,        quickly moved his millions off shore.
*     Because he  realized that the police were on to him, Bernie quickly moved his millions off shore.
*
*           Delivering his speech to the council, Frank had a heart attack.
*     While delivering his speech to the council, Frank had a heart attack.
*
*     She refused to cooperate while targeted by the media.
*     She refused to cooperate       targeted by the media. (Wrong)
*
*     eAdverbClause is eDependentClause (eSubordinateClause)
*         1. Reason. (because, since)
*         2. Contrast. (although, though, whereas)
*         3. Condition. (if, as long as)
*         4. Time. (when, while)
*         5. Purpose. (so that)
*         6. Comparison. (as, x-er than)

*===================================================================================================
*
*     CLAUSES
*
*     A clause is a group of words containing its own subject and verb. A clause that can stand by
*     itself as a sentence is an independent clause. A clause that can only be part of a sentence is
*     a subordinate clause.
*
*     THE essential difference between a clause and a phrase is that a clause has a tensed verb and
*     a subject and a phrase is lacking the tensed verb and/or the subject. A clause may be
*     independent or dependent. If independent, a clause may occur by itself or cojoined (by means
*     of a coordinating conjunction) with other independent clauses. If dependent, a clause must
*     occur attached to an independent clause (by means of a subordinating conjunction).
*
*     A clause has a subject and a tensed verb, whether that clause is independent or subordinate.
*     The most frequent difference between an independent clause and a subordinate clause is that a
*     subordinate clause has a subordinator while an independent clause has no subordinator. There
*     are three types of subordinate clauses in English: adverbial clauses, relative clauses,
*     nominal clauses. Adverbial clauses, like all clauses, have both a subject and a tensed verb.
*     They are different from other clauses in being subordinated by an adverbial subordinator.
*     Adverbial clauses serve to modify the entire independent clause or another subordinate clause
*     to which they might be attached. Relative clauses modify nouns most frequently and indefinite
*     pronouns occasionally. Nominal clauses function as nouns and are subordinated by one of the
*     following subordinating conjunctions: "how", "that", "what", "when", "where", "whether",
*     "which", "who", "why". Some nominal clauses--those that follow noun phrases--look very much
*     like relative clauses. However, they are different in structure. The difference is this: the
*     referent for the noun that is modified by a nominal clause has no grammatical role in the
*     nominal clause; the referent for the noun that is modified by a relative clause necessarily
*     has a grammatical role in the relative clause. Restrictive relative clauses and restrictive
*     nominal clauses restrict the reference of a noun phrase by identifying an individual or a
*     subset of some larger set named by the noun phrase that is modified.  Restrictive relative and
*     nominal clauses are not surrounded by commas.
*
*     eSubordinateClause            =  *eAdverbialClause | *eRelativeClause | *eNominalClause
*     eAdverbialClause              =  *adverbialSubordinator *subject *tensedVerb
*     eAdverbialClause (eIndependentClause | eSubordinateClause)
*     eRelativeClause (eNoun | eIndefinitePronoun)
*     eNominalClause                =  ( $'how' | $'that' | $'what' | $'when'
*                                      | $'where' | $'whether' | $'which' | $'who' | $'why') ...
*     eClause                       =  *eIndepedentClause *eCoordinatingConjunction $',' *eClause
*
*     An adjective clause is a subordinate clause that modifies a noun or pronoun, telling what kind
*     or which one. Adjective clauses usually begin with a relative pronoun -- that, which, who,
*     whom, or whose. Relative pronouns connect adjective clauses to the words the clauses modify.
*     Relative pronouns act as subjects, direct objects, adjectives, or objects of prepositions
*     within the clause. Putting the clause in normal word order can help you see how the word acts
*     within the clause. Adjective clauses are sometimes introduced by a relative adverb such as
*     where, when, why, before, or since. The relative adverb connects the clause to the word the
*     clause modifies and acts as an adverb within the clause.
*
*     eRelativeClause = *eAdjectiveClause
*     eAdjectiveClause = *eDefiningAdjectiveClause
*+                     | *eModifyingAdjectiveClause

*     'that', 'which', and 'who' can be subject and conjunction, 'that' sometimes removed
*     'whom', 'whose', 'when', 'where', and 'why' not subject only conjunction
*     *eModifiedNoun ($'that' | $'which' | $'who') *eVerb *eModifiedNoun *eFormOfBEVerb *eModifiedNoun $'.'
*     *eProperNoun $',' $'who' *eVerb *eModifiedNoun $',' *eFormOfBEVerb *eModifiedNoun $'.'
*     *eProperNoun *eVerb $'to' *eModifiedNoun $'where' *eProperNoun *eVerb *ePersonalPronoun *eModifiedNoun $'.'
*     The only effort that matters is that that leads to a win.
*     The only effort that matters is that which leads to a win.
*     Larry failed his test, which means he will have to go to summer school.
*     Larry failed his test, which means that he will have to go to summer school.
*     The eccentric billionaire, about whom the public knows little, donated millions to charity.

*     eAdjectiveClause              =  *eRelativePronoun

*     An adverb clause is a subordinate clause that modifies a verb, adjective, adverb, or verbal.
*     An adverb clause always begins with a subordinating conjunction. Adverb clauses tell when,
*     where, how, or why.
*     eAdverbClause                 =

*     An elliptical adverb clause is one in which the verb or the subject and verb are understood
*     but not actually stated.
*     eEllipticalAdverbClause       =

*     A noun clause is a subordinate clause that acts as a noun. It can be used in any of the
*     functions common to single-word nouns.
*     eNounClause                   =     *eIntroductoryWord

*     Some of the words that introduce noun clauses function as the subject, direct object, or some
*     other important part of their clause. Other introductory words have no function in the clause.
*     eIntroductoryWord             =  'who' | 'where' | 'which' | 'what' | 'whether'
*     eIndepedentClause             =
*     eIntroductoryModifier         =
*     eParentheticalElement         =
*---------------------------------------------------------------------------------------------------
*     functions: subject, predicate, complement, adverbial
*     complements: direct object, indirect object, subject predicate, object predicate
*     verbs:
*         0. intransitive,
*         1. (mono) transitive,
*         2. ditransitive,
*         3. copula verbs (linking verbs),
*         4. complex transitive
*         5. prepositional verbs (abide by, refer to, glance at, lean against, account for, reply to, absolve from, long for, yearn for, argue about, defer to)
*         6. phrasal verbs (call up, bring up, cover up)
*         7. phrasal prepositional verbs (put up with, came up with)
*     Lexical versus auxiliary (grammatical) verbs
*     Special Modals, semi-modals, dare to, need to , have to, ought to
*     Regular versus irregular verbs
*     Auxiliary verbs:
*         1. modal, (must, may, etc)
*         2. perfect, (have), -ed/-en
*         3. progressive, (be), -ing
*         4. passive, (be), -ed/-en
*     Subjects have nominative case.
*     Direct and indirect objects have accusative or objective case.
*     Prepositions also give accusative or objective case.
*     Possessive nouns have genitive case.
*     Clauses in sentences function as subject, direct object, subject predicate, or adverbial
*     Clauses can not function as indirect object, object of phrasal verbs, or prepositional objects, nor object predicate.
*     Clause in NP or AdjP function as modifier (relative clause) or complement (noun complement)
*     Sentence = main clause = independent clause = superordinate clause = S
*     Clause = embedded clause = embedded sentence = dependent clause = subordinate clause
*     Complementizer = Subordinating conjunction = C
*     Coordinator = Coordinating conjunction
*     Main clause is always finite, but embedded clause can be finite or non-finite.
*     eNP = *eNounPhrase
*     eVP = *eVerbPhrase
*     eAdjP = *eAdjectivePhrase
*     eAdvP = *eAdverbPhrase
*     ePP = *ePrepositionalPhrase

        eN      =   $' ' (*eNoun | *ePronoun) ~ 'N'
        eV      =   $' ' (*eVerb | *eDictVerb) ~ 'V'
        eAdj    =   $' ' *eAdjective ~ 'Adj'
        eAdv    =   $' ' *eAdverb ~ 'Adv'
        eP      =   $' ' *ePreposition ~ 'P'
        ePreD   =   $' ' ('all' | 'both' | 'half')
        eD      =   $' ' *eArticle ~ 'D'
        eNP     =   nPush()
+                   (*eD nInc() | epsilon)
+                   (*eAdjP nInc() | epsilon)
+                   *eN
+                   (*ePP nInc() | epsilon)
+                   ("'NP'" & 'nTop() + 1')
+                   nPop()
*       eNP     =   eNP | *eNP $'and' *eNP
        eVP     =   *eV *eNP ("'VP'" & 2) ;* direct object
        eVP     =   eVP | *eV *eNP *eNP ("'VP'" & 3) ;* indirect and direct objects
        eVP     =   eVP | *eV *eNP *eAdvP  ("'VP'" & 3) ;* direct object and adverbial
*       eVP     =   eVP | *eV *eNP *eSbar ;* direct object and adverbial clause
        eVP     =   eVP | *eV *eNP (*eAdjP | *eNP | *ePP) ("'VP'" & 3) ;* direct object and object predicate
        eVP     =   eVP | $'is' ~ 'V' (*eAdjP | *eNP | *ePP) ("'VP'" & 2) ;* subject predicate
*       eVP     =   eVP | *ePhrasalVerb *eNP
*       eVP     =   eVP | *ePrepositionalVerb *eNP
*       eVP     =   eVP | *ePhrasalPrepositionalVerb *eNP
        eVP     =   eVP | *eV *ePP ("'VP'" & 2)
        eVP     =   eVP | *eV *eAdjP ("'VP'" & 2)
*       eVP     =   eVP | *eV *eSbar
*       eVP     =   eVP | *eVP *ePP
*       eVP     =   eVP | *eVGP *eNP
        ePP     =   *eP *eNP ("'PP'" & 2)
        eAdjP   =   nPush()
+                   (*eAdvP nInc() | epsilon)
+                   *eAdj nInc()
+                   ARBNO(*eAdj nInc())
+                   ("'AdjP'" & '*(GT(nTop(), 1) nTop())')
+                   nPop()
        eAdvP   =   nPush()
+                   *eAdv nInc()
+                   ARBNO(*eAdv nInc())
+                   ("'AdvP'" & '*(GT(nTop(), 1) nTop())')
+                   nPop()
*       eVGP    =
*       eAdvl   =   *eAdvP | *eNP | *ePP | *eAdvC
        eS      =   *eNP *eVP ("'S'" & 2) ;* subject predicate
*       eS      =   eS | *eAdvP !$',' *eNP *eVP ;* sentence initial adverbial
*       eS      =   eS | *eNP *eVP !$',' *eAdvP ;* sentence final adverbial
*       eS      =   eS | *eSbar *eVP
*       eS      =   eS | *eSbar *eS
*       eS      =   eS | *eS 'and' *eS
*       eSbar   =   *eComplementizer *eS
