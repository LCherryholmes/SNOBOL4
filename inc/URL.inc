*-------------------------------------------------------------------------------------------------------
* URL.inc
*-------------------------------------------------------------------------------------------------------
            DEFINE('URLEncode(url)asc,ch,xch0,xch1')
            urlHex      =   '0123456789ABCDEF'                                      :(URLEncodeEnd)
URLEncode   url         POS(0) ANY(&UCASE) . ch =                                   :S(URLEncode1)
            url         POS(0) ANY(&LCASE) . ch =                                   :S(URLEncode1)
            url         POS(0) ANY('0123456789') . ch =                             :S(URLEncode1)
            url         POS(0) ANY('.-_') . ch =                                    :S(URLEncode1)
            url         POS(0) ' ' =                                                :S(URLEncode2)
            url         POS(0) ANY('$&+,/:;=?@') . ch =                             :S(URLEncode3)
            url         POS(0) LEN(1) . ch =                                        :S(URLEncode3)F(RETURN)
URLEncode1  URLEncode   =   URLEncode ch                                            :(URLEncode)
URLEncode2  URLEncode   =   URLEncode '+'                                           :(URLEncode)
URLEncode3  &ALPHABET   BREAK(ch) @asc
            urlHex      TAB(asc / 16) LEN(1) . xch1
            urlHex      TAB(REMDR(asc, 16)) LEN(1) . xch0
            URLEncode   =   URLEncode '%' xch1 xch0                                 :(URLEncode)
URLEncodeEnd
*-------------------------------------------------------------------------------------------------------
            DEFINE('URLDecode(url)ch,h0,h1,xch0,xch1')                              :(URLDecodeEnd)
URLDecode   url         POS(0) '%' LEN(1) . xch1 LEN(1) . xch0 =                    :S(URLDecode3)
            url         POS(0) '+' =                                                :S(URLDecode2)
            url         POS(0) LEN(1) . ch =                                        :S(URLDecode1)F(RETURN)
URLDecode1  URLDecode   =   URLDecode ch                                            :(URLDecode)
URLDecode2  URLDecode   =   URLDecode ' '                                           :(URLDecode)
URLDecode3  urlHex      BREAK(upr(xch1)) @h1
            urlHex      BREAK(upr(xch0)) @h0
            URLDecode   =   URLDecode CHAR(h1 * 16 + h0)                            :(URLDecode)
URLDecodeEnd
