-INCLUDE 'case.inc'
-INCLUDE 'match.inc'
-INCLUDE 'WordNet.inc'
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('Quotize(pattern)')
            OPSYN('=', 'Quotize', 1)                                                         :S(QuotizeEnd)F(error)
Quotize     Quotize           =     pattern | '"' pattern '"'                                :(RETURN)
QuotizeEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserDefs()')                                                             :(UserDefsEnd)
UserDefs    u                 =     0
            usr               =     ARRAY('1:32')
            doDebug           =     0
            doDebugAfter1st   =     TRUE
            doCatchAll        =     FALSE
            doInclWhite       =     TRUE
            doInclNL          =     TRUE
            doParseTree       =     FALSE
            doRemember        =     FALSE
            doReportFileName  =     FALSE
            fndExt            =     'txt' . extc
            fndCmd            =     'C:/mksnt/find C:/SNOBOL4/Development/English -name "*.txt" -print'
            fndSpecific       =     'Tweetish.txt'
            fndExclude        =
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            space             =     SPAN(' ' tab ff vt)
            whitespace        =     SPAN(' ' tab lf cr ff vt)
            $'  '             =     space
            $' '              =     FENCE(space | epsilon)
*---------- --------------------------------------------------------------------------------------------------------------
            twEntities        =     "applebee's neighborhood grill/applebee's grill/applebee's/applebees/applebee/"
+                                   "bahama breeze/"
+                                   "benihana's/benihana/"
+                                   "bennigan's/bennigans/"
+                                   "bob evan's/bob evans/"
+                                   "carino's/"
+                                   "cheesecake factory/"
+                                   "chili's/chilis/"
+                                   "chipotle mexican grill/chipotle's/"
+                                   "cracker barrel/"
+                                   "denny's/dennys/"
+                                   "fuddrucker's/fuddruckers/"
+                                   "hard rock cafe/"
+                                   "hooters/"
+                                   "houlihan's/houlihans/"
+                                   "ihop/international house of pancakes/"
+                                   "marie callender's/marie callender/"
+                                   "mimi's cafe/mimi's/"
+                                   "o'charley's/"
+                                   "olive garden/"
+                                   "roadhouse grill/"
+                                   "outback steakhouse/"
+                                   "p.f. chang's/p.f. changs/pf chang's/pf changs/"
+                                   "panera bread/"
+                                   "ponderosa steakhouse/ponderosa/"
+                                   "red lobster/"
+                                   "red robin/"
+                                   "romano's/macaroni grill/"
+                                   "ruby tuesday/"
+                                   "shoney's/"
+                                   "t.g.i. friday's/tgif/t.g.i.'s/t.g.i's/tgi's/friday's/"
+                                   "texas roadhouse/"
+                                   "tony roma's/"
+                                   "the cheesecake factory/"
+                                   "uno chicago grill/uno grill/uno's/"

            twIngEndings      =     "ballin' chillin' crankin' doin' drinkin' eatin' exaggeratin' fartin' feelin' fuckin' "
+                                   "geekin' grabbin' grubbin' hittin' killin' lookin' mornin' nothin' partyin' puddin' "
+                                   "roastin' runnin' startin' tryin' wantin' workin'"

            twContractions    =     "'bout "
+                                   "abc's ain't aren't "
+                                   "b'fast bf's bff's blow'd bro's "
+                                   "can't cludder'd com'on could've couldn't "
+                                   "da'king didn't dj'n doesn't don't "
+                                   "er'thang everything's "
+                                   "g'mon g'morning g'mornings goodmorn'n "
+                                   "hadn't hasn't haven't he'd he'll he's here's how's "
+                                   "i'd i'm i'ma i'll i've int'l isn't it'd it'll it's "
+                                   "juke'n "
+                                   "let's lil' "
+                                   "ma'am mf'er "
+                                   "n' "
+                                   "o'clock ol' "
+                                   "ppl's "
+                                   ""
+                                   "s'up she'll she's should've shouldn't set'n "
+                                   "that'll that's they'll they're they've there's "
+                                   "wasn't we'd we'll we're we've weren't what's where'd where's who's whoever's won't wouldn't "
+                                   "y'all y'know ya'll yo'self you'll you're you've"
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            keywords          =
+           'the of and a to in is that it was he for as on with his be at you i are this by from had have they not or one '
+           'am an because been came could did do every got has her him how if its me my our myself she should than them their these those towards shall us we were went what when where which who would your '
+           'also consequently finally furthermore hence however incidentally indeed instead likewise meanwhile nevertheless next nonetheless otherwise still then therefore thus '
+           'about above across after against along among around at before behind below beneath beside between beyond but '
+           'by despite down during except for from in inside into like near of off on onto out outside over past since '
+           'through throughout till to toward under underneath until up upon with within without '
*---------- --------------------------------------------------------------------------------------------------------------
            twMSWordList      =
+           'aka al although amen anything anytime assed aw awoken ay aye '
+           'badass bah barcode barstool basmati bb became began belcher bf bi biggie bio blanche bled blvd bogging '
+           'boogieman boppers bossier brie bro bros brought brownies btw '
+           'ca cabbie caffeinated calories calzone camelback cannot capita carpooled carryout celeb celebs chez chg '
+           'children cir ck classier co coffeemaker coldwater com comida congrats cont cornrow couponing coworker '
+           'coworkers cp craftiest craziest cri crispers ct cuties cyber '
+           'dang dc de def del delish dept des dev dipping dolling doo drank drew dropped du duh '
+           'eco eggrolls eh entre et etc eureka exurb exurban '
+           'fajita fajitas fanciest fattest feistiest fest ff firewomen fl fm folic fu funfest funniest fwd '
+           'geeky geo getters girlies goalies goodnight gosh gotcha grabbed grabbing grubbing gumball '
+           'ha hah haute heck hers hopping hottest hp ht http https huh hung hungrier hurray huzzah hw hwy '
+           'ifs inc itty '
+           'jai jess jonnie jus '
+           'kiddo kiddos kidnapped knives '
+           'le led legendarily legit les lf lib loaves loc lone los luckiest '
+           'mc meds mega merlot mf midtown mish misshaped mobbing movies mucho multigrain munchies '
+           'nah nana ne nightline nom nope '
+           'officemates ole oops op org others overheard '
+           'parkers parmesan per petro pg pgs ph pho pies pkwy pl playas pm pooh popped postgame postseason potatoes '
+           'pp pr pre prepping presale promo provolone pt pts '
+           'qua quitting quizzes '
+           'rainiest ramen rancho rapped rd realtors refranchise remix remixes repo roscoe roses '
+           'sagged sat sc se ser shitfaced shittier skipped slammed slamming slapped slapping snuggly something '
+           'sox sp speedier sq starring stepdad strategizing stretchered submitted supermall '
+           'tae tem thingy thru thx tiffany tilapia tm told tomatoes took tripped trippy twitting txt '
+           'ugh ugliest uh um umm unless '
+           'veggies vg voc von '
+           'webcast weenies weightwatchers whew whoa whoever wildwood wk wks wm woke woken wt www '
+           'xo '
+           'yep yikes yippee yuck yuk yum yup '
+           'zombies zzzz '
*---------- --------------------------------------------------------------------------------------------------------------
            twMSCapsList      =
+           'Aaron Abby Abercrombie Abuja Acworth Adam Adams Adrianna Africa Aggies Ahs Ainslie Aki Akron Albuquerque '
+           'Alex Alexandria Alfredo Ali Allen Allison Alpharetta Altamonte Alvarado Amanda Amarillo American '
+           'Americanized Americans Anaheim Anderson Andes Andorra Andrea Andrew Andrews Andy Angeles Angelina Angelo '
+           'Anthony Antoine App Appleton Apps Appt April Arden Arizona Arlington Armand Ashburn Ashford Ashley Asian '
+           'Asians Astoria Auckland Audrey Audubon Aug Austell Av Avalon Ave Aviles Avon Ayo '
+           'Bahamas Baja Banat Bangor Baptists Barnhart Barron Barry Baskin Bautista Baylor Beaumont Bella Belleville '
+           'Bellevue Belmont Belvidere Benson Bergen Berman Bernardino Bernardo Bernie Bethpage Bexar Bingham '
+           'Binghamton Biscayne Blackstone Blair Blondie Bloomfield Bloomington Bo Boca Boeing Boise Bothell Boyle Bp '
+           'Br Bradenton Bradley Brady Braintree Brandi Brandon Braxton Brea Brendan Brett Brian Brianna Bridgewater '
+           'Brighton Brinker Britney Brittany Bronx Brooke Brookfield Brookings Brooklyn Brookshire Bruce Bryan Bryans '
+           'Bryant Bryce Bt Buckland Buena Buenos Buick Burberry Burmese Burnaby Burnett Butterfield Cabot Cade Caesar '
+           'Caitlin Caitlyn Cajon Caleb Calgary Cali Calvin Cambridge Cameron Camino Campbell Canandaigua Cardiff Carle '
+           'Carlos Carole Carrollton Carson Casey Cass Cassandra Catasauqua Centerville Cerritos Cesar Ch Chandra '
+           'Channing Chantilly Charlene Charles Chatsworth Chavez Chelsea Cherie Chicago Chinese Chloe Chris Christina '
+           'Christmas Christy Chu Chula Cincinnati Cindy Claire Clark Clarkson Clarksville Clayton Cle Clearwater '
+           'Cleveland Cobb Cockrell Cody Coeur Coldplay Colfax Colinas Columbia Columbus Como Connecticut Connor Conway '
+           'Conyers Cooley Coolidge Coors Corbin Corey Cornell Cory Courtney Covington Crabtree Craig Crenshaw Creve '
+           'Crocker Cucamonga Culebra Culpepper Cumberland Cumming Cuyahoga '
+           'Dade Dakota Dallas Dalton Daniela Danielle Daniels Danny Dante Danvers Darren Dave David Davis Decatur '
+           'Dedham Dee Delhi Dem Denali Denny Denver Derek Desiree Detroit Deus Devin Dewitt Diana Diane Dias Dimas '
+           'Dior Disney Dix Dodson Dominican Donahue Donald Donnell Donny Doral Dorchester Doritos Douglasville Dover '
+           'Downingtown Dr Dubai Duluth Dundee Dunkin Dunwoody Dutton Dylan '
+           'Easley Easton Ecuador Ed Eddie Eden Edinburg Edison Edmonton Edwards Eileen Elda Elisa Elise Elkhart Elle '
+           'Ellie Elliot Elliott Elmhurst Elmira Elyria Emily Emory Encino Enfamil Enfield England Englewood English '
+           'Erik Erin Este Estrada Eva Evan Evanston Everett Exton '
+           'Fairfield Fairmont Fargo Fayetteville Fe Felipe Fernandez Fiji Fila Finley Finns Fletcher Flo Florida Floyd '
+           'Forestville Forsyth Fr Fraley France Frances Francis Francisco Frankfort Freddie Fredericksburg French '
+           'Fresno Fri Friday Fridays Frisco Fulton '
+           'Gainesville Galveston Gardena Garfield Garvey Gaston Gaylord George Georgetown Gilmore Ginny Giselle Gladys '
+           'Glendale Glenwood Gomez Goodyear Gov Gower Grandview Gratiot Grayson Greek Greenfield Greensboro Greenville '
+           'Greer Grubb Guam Gulfport Gustavo '
+           'Habra Hagerstown Halloween Halsted Hamm Hampton Hancock Hanes Hannah Hansen Hardees Harlem Harrell Harris '
+           'Harrisburg Harrison Hartman Hass Hawaii Heathrow Henderson Hendersonville Hennepin Herndon Hershey Hess '
+           'Hialeah Hillsborough Hirsh Hodges Holcomb Holland Hollywood Honda Honolulu Hooper Houston Howe Hun Hungary '
+           'Huntington Hurst Hyde '
+           'Ian Imo Ina Indianapolis Indy Infiniti Intl Irving Islip Italian Italy Ives '
+           'Jackie Jackson Jacksonville Jae Jakarta Jamal Jameson Jamie Jan Janeiro Janesville Janet Jas Jason Jayden '
+           'Jeff Jefferson Jen Jenks Jenna Jensen Jeremy Jerri Jett Jillian Jody Joes Johnson Johnsons Johnstown Jon '
+           'Jones Jonestown Joppa Jorge Jose Josef Juan Julia Julie Justin '
+           'Kai Kaitlin Kansas Kant Kari Karla Katarina Katella Kathryn Kathy Katie Katrina Katy Kayla Kelley Kelli '
+           'Kelly Kelsey Kendall Kendra Kenmore Kennedy Kennesaw Kenny Kensington Kent Keppel Keswick Kevin Keyport '
+           'Kiki Kimberly Kingsport Kingston Kingsville Kinney Kinston Kirby Kirin Kmart Knightdale Kobe Kokomo Koo '
+           'Kristen Kristi Kristin Kristina Kristine Kurt Kyle '
+           'Lakeview Lakewood Landon Lankford Lansing Laredo Lasik Lauderdale Lauren Lawrenceville Lawton Layne Leandro '
+           'Leavenworth Lebanon Ledbetter Leesburg Lehigh Leigh Lennox Lenny Lenox Leon Leslie Levi Levine Lewisville '
+           'Lexington Libertyville Libras Lil Lincolnshire Linda Lindbergh Lindsay Lisa Lithonia Livingston Livy Liz '
+           'Lockheed Logan London Lopez Lori Lorrie Louis Louisville Lowell Loyola Luda Luis Luvs Lyndon Lynne '
+           'Macarthur Macau Macdonald Macleod Madison Madre Madrid Maggie Maguire Maitland Makati Maki Makin Malibu '
+           'Mallory Mandy Mangum Mann Mansfield Manteca Marco Marcus Marianas Marie Marietta Mario Marissa Marley Marr '
+           'Marriott Marvin Marysville Matthews Mattie Mau Mauricio Maury Mayfield Mayra Mclean Meagan Meaghan '
+           'Mechanicsburg Mechanicsville Medlock Megan Meghan Meijer Mel Melinda Memphis Metcalf Methuen Mexicali '
+           'Mexican Mexicans Mexico Mia Miami Miamisburg Micah Michael Michelle Mickey Middlesex Midori Milford '
+           'Millbury Milliken Millsap Milton Milwaukee Mindy Minneapolis Minnelli Minnesota Miramar Mississauga '
+           'Mitchell Mk Moe Moffitt Moines Monday Mondays Monica Monique Monroeville Monrovia Monsanto Montebello '
+           'Montgomery Monticello Moreau Moreland Mt Mumford Myers Mylanta '
+           'Na Nadia Nashville Nate Nathan Nathaniel Nathans Nazareth Nene Netflix Neuse Neva Nevada Newport Newtown '
+           'Nguyen Niceville Nicky Nicole Nicollet Niger Nigeria Nigerian Nike Nikki Nina Nissan Noelle Norfolk '
+           'Northampton Northglenn Northlake Northridge Nov Num Nyack '
+           'Oakland Oakwood Oates Obispo Ocala Oceanside Oct October Odessa Ogden Oglesby Ohio Oklahoma Oktoberfest '
+           'Olathe Olga Om Omar Ontario Orlando Orleans Otis Oxnard '
+           'Pablo Paige Palin Palo Pam Panini Paola Parton Pasadena Paso Patna Paul Peachtree Pearland Pedi Pedro Pei '
+           'Pelham Penn Perez Perkins Petersburg Peterson Pf Phil Philadelphia Phillies Phillips Philly Pickerington '
+           'Pickwick Pilates Pinocchio Pittsburgh Plainfield Pleasanton Porsche Portland Porto Portobello Posner '
+           'Pottstown Prego Presley Princeton Provo Prussia '
+           'Qualcomm Quebec Quincy Quinn Quinta '
+           'Ra Rachel Racine Rae Raleigh Ramon Rashid Rasta Raton Ravenna Raymond Rayne Reagan Redlands Redondo Reece '
+           'Reina Reiss Renee Revy Rey Reyes Rhett Rhode Riana Rica Richardson Ricky Rico Rivera Riverdale Riverview '
+           'Riviera Robbie Robbins Robert Roberto Roberts Robinson Rochester Rockefeller Rockville Rogers Rohr Rollin '
+           'Ron Ronda Rooty Rosedale Rosemead Rosenberg Roseville Ross Rosslyn Roswell Roxanne Roy Rubenstein Rudy Russ '
+           'Russell Ruston Ruthie Ryan Ryder '
+           'Sa Sade Safeway Saginaw Salazar Salem Samantha Sandler Sandoval Sanford Santa Santana Santiago Sarah '
+           'Saturday Saturdays Saugus Schaumburg Scotland Scott Scotts Scottsdale Scotty Sean Seattle Sebring Secaucus '
+           'Seguin Selena Selwyn Setauket Sevierville Shabbat Shania Sharon Shauna Sheldon Sheppard Sherman Sherwin '
+           'Shoppes Shorty Shreveport Silber Siler Simpson Sinatra Skokie Snellville Snyder Sophie Southaven Southgate '
+           'Southside Spain Spanish Spartanburg Springfield St Stacy Staley Stallone Stanger Starbucks Staten Steelers '
+           'Stefan Steinway Stephanie Stetson Steve Stevens Stockdale Strongsville Succasunna Sullivan Suma Summerville '
+           'Sunday Supt Sur Sweden Swedesboro Sweetwater '
+           'Tallahassee Tampa Tampico Tanta Tara Tasha Tata Tb Temecula Tennessee Terre Terrence Tex Texarkana Texas '
+           'Thai Thee Theo Thompson Thurs Thursday Thursdays Tiffani Tina Togo Tokyo Tonya Topeka Toronto Torres Totowa '
+           'Towne Towson Tracy Tran Tremont Tricia Tripp Tucson Tue Tues Tuesdays Tulsa Tustin Tuttle Ty Tyler Tyson '
+           'Uniontown Uno Ur '
+           'Val Valdosta Vancouver Vegas Ventura Verde Verizon Vernon Vic Viejo Ville Vito Voorhees '
+           'Wadesboro Wadsworth Waldorf Walters Wanamaker Warrington Washtenaw Watauga Watson Wawa Wayne Webster '
+           'Wednesday Wendy Wes Wesley Westbury Westfall Westfield Westlake Westminster Westwood Wheaton Whitehall '
+           'Whitehaven Whitesville Whitney Whyte Wichita Willa Willard Williamsburg Williamsville Willoughby Wilma '
+           'Wilmington Wilson Winston Wisconsin Witt Woodbridge Woodbury Woodward Worcester Wynnewood Wytheville '
+           'Yankees Yee York Yorkers Yu Yung Yvonne '
+           'Zach Zack '
            twMSCapsList      =     lwr(twMSCapsList)
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            twWord            =     SPAN(&LCASE &UCASE)
            twWordAbbrev      =     SPAN(&UCASE '.' "'" &LCASE)
            twWordContraction =     FENCE(twWord "'" twWord "'" twWord | twWord "'" twWord | "'" twWord | twWord "'")
            twWordLookup      =     (POS(0) | ' ') *lwr(tx) (' ' | RPOS(0))
            twIngEnding       =     twWordContraction $ tx $ *match(twIngEndings, twWordLookup)
            twContraction     =     twWordContraction $ tx $ *match(twContractions, twWordLookup)
            twMSWordOkay      =     twWord $ tx $ *match(twMSWordList, twWordLookup)
            twMSCapsOkay      =     twWord $ tx $ *match(twMSCapsList, twWordLookup)
            keyword           =     twWord $ tx $ *match(keywords, twWordLookup)
            specials          =     '@ $ ^ _ / - = & ( ) < > # , : ; . ? ! " ' "'"
            Populate(.TW, twWord, keywords,, specials)
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            twEntity          =
            twWordsList       =     twEntities
UserDefs10  twWordsList       ?     POS(0) FENCE (BREAK('/') . twWords '/') =                       :F(UserDefs50)
            twWordsPat        =
            twI               =     0
UserDefs20  twI               =     twI + 1
            twWords           ?     POS(0) FENCE BREAK(' ') . twW ' ' =                             :S(UserDefs30)
            twWords           ?     POS(0) FENCE (LEN(1) RTAB(0)) . twW '' =                        :S(UserDefs30)F(UserDefs40)
UserDefs30  twW               ?     '.'                                                             :S(UserDefs33)
            twW               ?     "'"                                                             :S(UserDefs35)
            twWordPat         =     "twWord $ tx *LEQ('" lwr(twW) "', lwr(tx))"                     :(UserDefs37)
UserDefs33  twWordPat         =     'twWordAbbrev $ tx *LEQ("' lwr(twW) '", lwr(tx))'               :(UserDefs37)
UserDefs35  twWordPat         =     'twWordContraction $ tx *LEQ("' lwr(twW) '", lwr(tx))'          :(UserDefs37)
UserDefs37  twWordPat         =     EVAL(twWordPat)
*           twWordPat         =     TY(2, twW, twWordPat)
            twWordsPat        =     twWordsPat (EQ(twI, 1), $'  ') twWordPat                        :(UserDefs20)
UserDefs40  twEntity          =     (IDENT(twEntity) twWordsPat, twEntity | twWordsPat)             :(UserDefs10)
UserDefs50
*           twEntity          =     TZ(2, 'twEntity', twEntity)
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            twAtId            =     '@' SPAN(&UCASE '_' &LCASE '0123456789')
            twHashId          =     '#' SPAN(&UCASE '_' &LCASE '0123456789')
            twNumber          =     SPAN('0123456789')
            twHttpUrl         =     'http://' FENCE(BREAK(' ') | RTAB(0))
            twDollars         =     '$' twNumber FENCE('.' twNumber | epsilon)
            twBeta            =     CHAR(225)
            twTheta           =     CHAR(233)
            twPhi             =     CHAR(237)
            twHalf            =     CHAR(171)
            twDblLeft         =     CHAR(174)
            twAUmlat          =     CHAR(160)
            twLessOrEqual     =     CHAR(243)
            twPlusOrMinus     =     CHAR(241)
            twBackApos        =     CHAR(96)

            twNoun            =     twWord $ tx $ *EngIsNoun(tx)
            twVerb            =     twWord $ tx $ *EngIsVerb(tx)
            twAdverb          =     twWord $ tx $ *EngIsAdv(tx)
            twAdjective       =     twWord $ tx $ *EngIsAdj(tx)
            twKnownWord       =     twWord $ tx *DIFFER(words[tx])
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            Words()
            Dict()
                                                                                             :(RETURN)
UserDefsEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserRpt()')                                                              :(UserRptEnd)
UserRpt     tw                =     Pop()                                                    :F(RETURN)
            DIFFER(tw)                                                                       :F(RETURN)
*           XDump('tw', tw)
            TDump(tw)                                                                        :(RETURN)
UserRptEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
            DEFINE('UserTokens()')                                                           :(UserTokensEnd)
UserTokens  tok[t = t + 1] = token(, "*twAtId", twAtId)
            tok[t = t + 1] = token(, "*twHashId", twHashId)
            tok[t = t + 1] = token(, "*twEntity", twEntity)
            tok[t = t + 1] = token('twIngEnding', *(REPLACE(upr(tx), "'", '~')), twIngEnding . tx)
            tok[t = t + 1] = token('twContraction', *(REPLACE(upr(tx), "'", '~')), twContraction . tx)
            tok[t = t + 1] = token('twWordContraction', *('<"' lwr(tx) '">'), twWordContraction . tx)
            tok[t = t + 1] = token(,, .twHttpUrl)
            tok[t = t + 1] = token("KEYWORD", *(upr(tx)), *keyword . tx)
            tok[t = t + 1] = token('twNoun', *lwr(tx), twNoun . tx)
            tok[t = t + 1] = token('twVerb', *lwr(tx), twVerb . tx)
            tok[t = t + 1] = token('twAdverb', *lwr(tx), twAdverb . tx)
            tok[t = t + 1] = token('twAdjective', *lwr(tx), twAdjective . tx)
            tok[t = t + 1] = token('twKnownWord', *lwr(tx), twKnownWord . tx)
            tok[t = t + 1] = token('twMSWordOkay', *lwr(tx), twMSWordOkay . tx)
            tok[t = t + 1] = token('twMSCapsOkay', *cap(tx), twMSCapsOkay . tx)
            tok[t = t + 1] = token('twWord', *("'" tx "'"), *EQ(doCatchAll, TRUE) twWord . tx . OUTPUT)
            tok[t = t + 1] = token(, *('"' "'s" '"'), "'s")
            tok[t = t + 1] = token(,, .twNumber)
            tok[t = t + 1] = token(,, .twDollars)
            tok[t = t + 1] = token(,, .twPhi)
            tok[t = t + 1] = token(,, .twHalf)
            tok[t = t + 1] = token(,, .twDblLeft)
            tok[t = t + 1] = token(,, .twPlusOrMinus)
            tok[t = t + 1] = token(,, .twLessOrEqual)
            tok[t = t + 1] = token(,, .twAUmlat)
            tok[t = t + 1] = token(,, .twBackApos)
            tok[t = t + 1] = token(,, .twBeta)
            tok[t = t + 1] = token(,, .twTheta)
            tok[t = t + 1] = token(, 'CHAR(161)', CHAR(161))
            tok[t = t + 1] = token(, 'CHAR(162)', CHAR(162))
            tok[t = t + 1] = token(, 'CHAR(180)', CHAR(180))
            tok[t = t + 1] = token(, 'CHAR(183)', CHAR(183))
            tok[t = t + 1] = token(, 'CHAR(186)', CHAR(186))
            tok[t = t + 1] = token(, 'CHAR(187)', CHAR(187))
            tok[t = t + 1] = token(, 'CHAR(193)', CHAR(193))
            tok[t = t + 1] = token(, 'CHAR(200)', CHAR(200))
            tok[t = t + 1] = token(, 'CHAR(201)', CHAR(201))
            tok[t = t + 1] = token(, 'CHAR(226)', CHAR(226))
            tok[t = t + 1] = token(, 'CHAR(227)', CHAR(227))
            tok[t = t + 1] = token(, 'CHAR(231)', CHAR(231))
            tok[t = t + 1] = token(, '*twSigma', CHAR(228))
            tok[t = t + 1] = token(, '*twOmega', CHAR(234))
            tok[t = t + 1] = token(, 'CHAR(236)', CHAR(236))
            tok[t = t + 1] = token(, 'CHAR(233)', CHAR(244))
            tok[t = t + 1] = token(, '*twDividedBy', CHAR(246))
            tok[t = t + 1] = token(, '*twDegrees', CHAR(248))
            tok[t = t + 1] = token(, 'bSlash', bSlash)
            tok[t = t + 1] = token(, *("$'" tx "'"), '@' . tx)
            tok[t = t + 1] = token(, *("$'" tx "'"), '+' . tx)
            tok[t = t + 1] = token(, *("$'" tx "'"), '|' . tx)
            tok[t = t + 1] = token(, *("$'" tx "'"), '%' . tx)
            tok[t = t + 1] = token(, *("$'" tx "'"), '~' . tx)
            tok[t = t + 1] = token(, *("$'" tx "'"), '$' . tx)
            tok[t = t + 1] = token(, *("$'" tx "'"), '*' . tx)
            tok[t = t + 1] = token(, *("$'" tx "'"), '^' . tx)
            tok[t = t + 1] = token(, *("$'" tx "'"), '_' . tx)
            tok[t = t + 1] = token(, *("$'" tx "'"), '/' . tx)
            tok[t = t + 1] = token(, *("$'" tx "'"), '-' . tx)
            tok[t = t + 1] = token(, *("$'" tx "'"), '=' . tx)
            tok[t = t + 1] = token(, *("$'" tx "'"), '&' . tx)
            tok[t = t + 1] = token(, *("$'" tx "'"), '(' . tx)
            tok[t = t + 1] = token(, *("$'" tx "'"), ')' . tx)
            tok[t = t + 1] = token(, *("$'" tx "'"), '[' . tx)
            tok[t = t + 1] = token(, *("$'" tx "'"), ']' . tx)
            tok[t = t + 1] = token(, *("$'" tx "'"), '<' . tx)
            tok[t = t + 1] = token(, *("$'" tx "'"), '>' . tx)
            tok[t = t + 1] = token(, *("$'" tx "'"), '#' . tx)
            tok[t = t + 1] = token(, *("$'" tx "'"), ',' . tx)
            tok[t = t + 1] = token(, *("$'" tx "'"), ':' . tx)
            tok[t = t + 1] = token(, *("$'" tx "'"), ';' . tx)
            tok[t = t + 1] = token(, *("$'" tx "'"), '.' . tx)
            tok[t = t + 1] = token(, *("$'" tx "'"), '?' . tx)
            tok[t = t + 1] = token(, *("$'" tx "'"), '!' . tx)
            tok[t = t + 1] = token(, *("'" '"' "'"), '"')
            tok[t = t + 1] = token(, *('"' "'" '"'), "'")

*           dbg[.htmRecognizer] = TRUE

                                                                                             :(RETURN)
UserTokensEnd
*---------- ----------------- ----- -------------------------------------------------------- -----------------------------
