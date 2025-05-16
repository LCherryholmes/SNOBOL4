*-----------------------------------------------------------------------------------------------------------------------
* tree: a general purpose tree datatype
*    t: type of tree (unique identification)
*    v: value of tree (for leaf node)
*    n: number of children (for internal node)
*    c: array of children trees
* Append(x,y)       -- insert y tree as the rightmost child of x tree
* Prepend(x,y)      -- insert y tree as the leftmost child of x tree
* Insert(x,y,place) -- insert y tree as child of x tree at the designated place
* Remove(x,place)   -- remove the child tree at the designated place
*-----------------------------------------------------------------------------------------------------------------------
               DATA('tree(t,v,n,c)')
               DEFINE('Append(x,y)')
               DEFINE('Prepend(x,y)')
               DEFINE('Insert(x,y,place)c,i')
               DEFINE('Remove(x,place)c,i')                                         :(TreeEnd)
Append         Append         =    Insert(x, y, n(x) + 1)                           :(RETURN)
Prepend        Prepend        =    Insert(x, y, 1)                                  :(RETURN)
Insert         Insert         =    x
               c              =    ARRAY('1:' n(x) + 1)
               i              =    0
Insert1        i              =    LT(i, place - 1) i + 1                           :F(Insert2)
               c[i]           =    c(x)[i]                                          :(Insert1)
Insert2        c[i + 1]       =    y
Insert3        i              =    LT(i, n(x)) i + 1                                :F(Insert4)
               c[i + 1]       =    c(x)[i]                                          :(Insert3)
Insert4        n(x)           =    n(x) + 1
               c(x)           =    c                                                :(RETURN)
Remove         Remove         =    x
               c              =    GT(n(x) - 1, 0) ARRAY('1:' n(x) - 1)
               i              =    0
Remove1        i              =    LT(i, place - 1) i + 1                           :F(Remove2)
               c[i]           =    c(x)[i]                                          :(Remove1)
Remove2        i              =    i + 1
Remove3        i              =    LT(i, n(x)) i + 1                                :F(Remove4)
               c[i - 1]       =    c(x)[i]                                          :(Remove3)
Remove4        n(x)           =    n(x) - 1
               c(x)           =    c                                                :(RETURN)
TreeEnd
*------------- -------------------------------------------------------------------- -----------------
               DEFINE('Tree(t,v,n,c1,c2,c3,c4,c5,c6,c7,c8)i,nc')                    :(Tree_End)
Tree           nc             =    8
Tree1          nc             =    GT(nc, 0) IDENT($('c' nc)) nc - 1                :S(Tree1)
               Tree           =    tree(t, v,
+                                      (GT(nc, 0) nc, NULL)
+                                  ,   (GT(nc, 0) ARRAY('1:' nc), NULL)
+                                  )
               i              =    0
Tree3          i              =    LT(i, nc) i + 1                                  :F(RETURN)
               c(Tree)[i]     =    $('c' i)                                         :(Tree3)
Tree_End
*------------- -------------------------------------------------------------------- -----------------
               DEFINE('Equal(x,y)i')                                                :(EqualEnd)
Equal          epsilon        *IDENT(x) *IDENT(y)                                   :S(RETURN)
               epsilon        *IDENT(x) | *IDENT(y)                                 :F(FRETURN)
               IDENT(t(x), t(y))                                                    :F(FRETURN)
               IDENT(v(x), v(y))                                                    :F(FRETURN)
               IDENT(n(x), n(y))                                                    :F(FRETURN)
               i              =    0
Equal5         i              =    LT(i, n(x)) i + 1                                :F(RETURN)
               Equal(c(x)[i], c(y)[i])                                              :S(Equal5)F(FRETURN)
EqualEnd
*------------- -------------------------------------------------------------------- -----------------
               DEFINE('Equiv(x,y)i')                                                :(EquivEnd)
Equiv          t(x)           POS(0) t(y) RPOS(0)                                   :F(FRETURN)
               v(x)           POS(0) v(y) RPOS(0)                                   :F(FRETURN)
               n(x)           POS(0) n(y) RPOS(0)                                   :F(FRETURN)
               i              =    0
Equiv5         i              =    i + 1
               (DIFFER(c(y)) c(y)[i])                                               :F(RETURN)
               Equiv(c(x)[i], c(y)[i])                                              :S(Equiv5)F(FRETURN)
EquivEnd
*------------- -------------------------------------------------------------------- -----------------
               DEFINE('Find(xn,y,f)i')                                              :(FindEnd)
Find           DIFFER($xn)                                                          :F(RETURN)
               (Equiv($xn, y) APPLY(f, xn))                                         :S(RETURN)
               i              =    0
Find5          i              =    LT(i, n($xn)) i + 1                              :F(RETURN)
               Find(.c($xn)[i], y, f)                                               :(Find5)
FindEnd
*------------- -------------------------------------------------------------------- ---------------------
*              Perform a pre-order traversal of tree x, and apply the function fnc at each node
               DEFINE('Visit(x,fnc)i')                                              :(VisitEnd)
Visit          APPLY(fnc, x)                                                        :F(RETURN)
               i              =  0
Visit_1        i              =  LT(i, n(x)) i + 1                                  :F(RETURN)
               Visit(c(x)[i], fnc)                                                  :(Visit_1)
VisitEnd
