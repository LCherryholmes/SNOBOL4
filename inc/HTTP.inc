*-------------------------------------------------------------------------------------------------------
            xUserAgent   =   'Blogzilla/1.0 (compatible; MSIE 6.0; Windows NT 5.1; .NET CLR 1.1.4322)'
*---------- ----------- --- --------------------------------------------------- ------------------------
            DEFINE('Pause(secs)')                                               :(PauseEnd)
Pause       EQ(doHTTP, TRUE)                                                    :F(RETURN)
            sleep(RANDOM(secs * 1000))                                          :(RETURN)
PauseEnd
*---------- ----------- --- ----------------------------------------------------------------------------
            DEFINE('HTTP_Init(name)cookies')                                    :(HTTP_InitEnd)
HTTP_Init   EQ(doHTTP, TRUE)                                                    :F(RETURN)
            cookies     =   name 'Cookies.txt'
            curl        =   curl_easy_init()                                    :F(FRETURN)
*           EQ(cc = curl_easy_setopt(curl, CURLOPT_VERBOSE, TRUE))              :F(FRETURN)
            EQ(cc = curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, FALSE))      :F(FRETURN)
            EQ(cc = curl_easy_setopt(curl, CURLOPT_USERAGENT, xUserAgent))      :F(FRETURN)
            EQ(cc = curl_easy_setopt(curl, CURLOPT_COOKIEFILE, cookies))        :F(FRETURN)
            EQ(cc = curl_easy_setopt(curl, CURLOPT_COOKIEJAR, cookies))         :S(RETURN)F(FRETURN)
HTTP_InitEnd
*---------- ----------- --- --------------------------------------------------- ------------------------
            DEFINE('HTTP_Get(name,url,flds)slist')                              :(HTTP_GetEnd)
HTTP_Get    xHTTP_Count = xHTTP_Count + 1
            url         =   DIFFER(flds) url '?' flds
            TERMINAL    =   'GET  ' url
            EQ(doHTTP, TRUE)                                                    :F(HTTP_Get3)
            EQ(cc = curl_easy_setopt(curl, CURLOPT_HTTPGET, TRUE))              :F(FRETURN)
            EQ(cc = curl_easy_setopt(curl, CURLOPT_REFERER, xxUrl))             :F(FRETURN)
            EQ(cc = curl_easy_setopt(curl, CURLOPT_URL, url))                   :F(FRETURN)
            url         ?   POS(0) 'http://api.gowalla.com/'                    :F(HTTP_Get1)
            EQ(cc = curl_easy_setopt(curl, CURLOPT_USERPWD, 'LonJonesCherryholmes:Blogzilla99#')) :F(FRETURN)
            slist =
            slist = curl_slist_append(slist, 'X-Gowalla-API-Key: ' gwAppID)     :F(FRETURN)
            slist = curl_slist_append(slist, 'Accept: application/json')        :F(FRETURN)
            slist = curl_slist_append(slist, 'Content-Type: application/json')  :F(FRETURN)
            EQ(cc = curl_easy_setopt_int(curl, CURLOPT_HTTPHEADER, slist))      :F(FRETURN)
HTTP_Get1   EQ(cc = curl_easy_perform(curl))                                    :F(FRETURN)
            url         ?   POS(0) 'http://api.gowalla.com/'                    :F(HTTP_Get2)
            EQ(cc = curl_easy_setopt_int(curl, CURLOPT_HTTPHEADER, 0))          :F(FRETURN)
            slist = curl_slist_free_all(slist)                                  :F(FRETURN)
HTTP_Get2   HTTP_Get    =   curl_easy_getdata()                                 :F(FRETURN)
            LineMap(HTTP_Get, .t8Map)
            Write(name '-' xHTTP_Count '.txt', HTTP_Get)                        :(HTTP_Get9)
HTTP_Get3   HTTP_Get    =   Read(name '-' xHTTP_Count '.txt', .t8Map)           :S(HTTP_Get9)F(error)
HTTP_Get9   xxUrl       =   url                                                 :(RETURN)
HTTP_GetEnd
*---------- ----------- --- --------------------------------------------------- ------------------------
            DEFINE('HTTP_Post(name,url,flds,xtra)')                             :(HTTP_PostEnd)
HTTP_Post   xHTTP_Count =   xHTTP_Count + 1
            url         =   DIFFER(xtra) url '?' xtra
            TERMINAL    =   'POST ' url
            EQ(doHTTP, TRUE)                                                    :F(HTTP_Post3)
            EQ(cc = curl_easy_setopt(curl, CURLOPT_POST, TRUE))                 :F(FRETURN)
            EQ(cc = curl_easy_setopt(curl, CURLOPT_POSTFIELDS, flds))           :F(FRETURN)
            EQ(cc = curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, TRUE))       :F(FRETURN)
            EQ(cc = curl_easy_setopt(curl, CURLOPT_REFERER, xxUrl))             :F(FRETURN)
            EQ(cc = curl_easy_setopt(curl, CURLOPT_URL, url))                   :F(FRETURN)
            EQ(cc = curl_easy_perform(curl))                                    :F(FRETURN)
            HTTP_Post   =   curl_easy_getdata()                                 :F(FRETURN)
            LineMap(HTTP_Post, .t8Map)
            Write(name '-' xHTTP_Count '.txt', HTTP_Post)                       :(HTTP_Post9)
HTTP_Post3  HTTP_Post   =   Read(name '-' xHTTP_Count '.txt', .t8Map)           :S(HTTP_Post9)F(error)
HTTP_Post9  xxUrl       =   url                                                 :(RETURN)
HTTP_PostEnd
*---------- ----------- --- --------------------------------------------------- ------------------------
