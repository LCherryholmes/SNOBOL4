*----------------------------------------------------------------------------------------------------
-INCLUDE 'global.inc'
*------------ --------------------------------------------------------------------- -----------------
              textExtList    =   'aix,att,bas,bat,bnf,c,cpp,d,def,dep,dsp,dsw,dyn,ec,h,hh,history,hp,hpp,'
+                                'inf,ini,ini_bk,inl,ksh,log,lst,mak,map,osf,pl,psl,rc,rc2,sh,sin,sno,'
+                                'sol,sql,spt,t3x,t41,t51,tag,tpl,txt,y'
              binaryExtList  =   'a,acm,avi,ax,b3x,b41,b51,b61,bak,bin,bmk,bmp,bo,bpd,bsc,bsl,'
+                                'cab,cat,cfg,cfg32,chm,class,cm,cnt,com,config,cpi,cpl,cpx,ctg,cur,'
+                                'dat,dba,dbg,dir,dlg,dll,doc,drv,evt,ex_,exe,exp,fin,fnt,'
+                                'gid,gif,grs,hdr,hlp,hm,hsh,htm,idb,ico,icv,idl,ilk,ins,iss,isu,iwf,'
+                                'km,kml,kpp,lib,lid,mcp,mds,mod,msc,msg,msk,msl,msq,nls,nt,'
+                                'obj,ocx,odl,ol_,olb,pc,pch,pda,pdb,pch,pdf,plg,pnf,po,ppd,pro,'
+                                'ram,rat,rch,reg,res,rgs,rll,rom,rsp,'
+                                'sam,sav,sbr,scr,sep,sl,so,sp4,srg,sys,'
+                                'tar,tlb,tmp,trm,trn,tsk,tsp,twd,usr,ver,vwp,vxd,wri,x32,xpm,'
+                                'z,zip'
              extList        =   binaryExtList ',' textExtList
              digits         =   '0123456789'
              slash          =   '/' | bSlash
              integer        =   SPAN(digits)
              int            =   SPAN('0123456789')
              hex            =   '0x' SPAN('0123456789ABCDEFabcdef')

              extInList      =   (POS(0) | ',') *lwr(ext) (',' | RPOS(0))
              textPathExt    =   SPAN(digits &UCASE '_' &LCASE) $ ext $ *match(textExtList, extInList)
              binaryPathExt  =   SPAN(digits &UCASE '_' &LCASE) $ ext $ *match(binaryExtList, extInList)

              pathExt        =   SPAN(digits &UCASE '_' &LCASE) $ ext $ *match(extList, extInList)
+                            |   SPAN(digits)
+                            |   'a.bak'
+                            |   'sl.bak'
+                            |   'so.bak'
+                            |   'so.' SPAN(digits) '.' SPAN(digits)
              pathNode       =   SPAN(digits &UCASE &LCASE '%-_ ')
              pathId         =   *pathNode ('.' 'iso88591' | '~' *integer | epsilon)
              pathLeaf       =   *pathNode ('.' *pathExt | epsilon)
              pathDrive      =   (  ANY(&UCASE &LCASE) ':' slash
+                                |  slash slash BREAK(fSlash bSlash nl) slash BREAK(fSlash bSlash nl) slash
+                                |  slash
+                                |  epsilon
+                                )
              pathDir        =   ('..' | '.' | *pathId) (slash *pathDir | epsilon)
              pathName       =   *pathDrive *pathDir slash *pathLeaf
+                            |   *pathDrive *pathDir slash (slash | epsilon)
+                            |   *pathNode '.' *pathExt
*------------ --------------------------------------------------------------------- -----------------
-INCLUDE 'is.inc'
-INCLUDE 'FENCE.inc'
-INCLUDE 'io.inc'
-INCLUDE 'assign.inc'
-INCLUDE 'match.inc'
-INCLUDE 'slash.inc'
-INCLUDE 'case.inc'
-INCLUDE 'export.inc'
-INCLUDE 'counter.inc'
-INCLUDE 'stack.inc'
-INCLUDE 'tree.inc'
-INCLUDE 'ShiftReduce.inc'
-INCLUDE 'TDump.inc'
-INCLUDE 'Gen.inc'
-INCLUDE 'Qize.inc'
-INCLUDE 'XDump.inc'
-INCLUDE 'ReadWrite.inc'
-INCLUDE 'system.inc'
*------------ --------------------------------------------------------------------- -----------------
              DEFINE('mkdir(dirnm,options)lsResponse')
              mkdirs         =   TABLE()                                            :(mkdir_end)
mkdir         IDENT(mkdirs[dirnm])                                                  :F(RETURN)
*             lsResponse     =   system('@-ls', '-1d "' dirnm '"')
*             IDENT(lsResponse)                                                     :F(mkdir9)
              system('mkdir', options ' "' dirnm '"')
mkdir9        mkdirs[dirnm]  =   1                                                  :(RETURN)
mkdir_end
*------------ --------------------------------------------------------------------- -----------------
* Creates a Date Build Name
*------------ --------------------------------------------------------------------- -----------------
              DEFINE('blddate()dd,mo,year,mm,hh,ss')                                :(blddate_end)
blddate       bddt           =   Datetime()
              bddt           POS(0) int . year '/' int . mo '/' int . dd
+                             ' '    int . hh ':' int . mm
+                             (':' int . ss | epsilon) RPOS(0)
              blddate        =   year mo dd                                         :(RETURN)
blddate_end
*------------ --------------------------------------------------------------------- -----------------
* Creates a Date/Time Build Name
*------------ --------------------------------------------------------------------- -----------------
              DEFINE('blddatetime()dom,mon,hr,min,sec,yr')                          :(blddatetime_end)
blddatetime   bdt            =   Datetime()
              bdt            POS(0) int . yr '/' int . mon '/' int . dom
+                             ' '    int . hr ':' int . min
+                             (':' int . sec | epsilon) RPOS(0)
              blddatetime    =   yr mon dom '-' hr min                              :(RETURN)
blddatetime_end
*------------ --------------------------------------------------------------------- -----------------
              DEFINE('Plural(n,Plural)')                                            :(PluralEnd)
Plural        Plural         =   Plural EQ(n, 0) 's'                                :S(RETURN)
              Plural         =   Plural GT(n ,1) 's'                                :(RETURN)
PluralEnd
*------------ --------------------------------------------------------------------- -----------------
              DEFINE('Vector(t)a,aMax,n,proto')                                     :(VectorEnd)
Vector        IsType(t, 'table')                                                    :F(FRETURN)
              NE(t[0], 0)                                                           :F(FRETURN)
              a              =   SORT(t, 1)                                         :F(error)
              proto          =   PROTOTYPE(a)                                       :F(error)
              proto          POS(0) *integer . aMax ',2' RPOS(0)                    :F(error)
              aMax           =   aMax - 1
              Vector         =   ARRAY(aMax)                                        :F(error)
              n              =   0
Vector5       n              =   LT(n, aMax) n + 1                                  :F(RETURN)
              EQ(n, a[n + 1, 1])                                                    :F(error)
              Vector[n]      =   a[n + 1, 2]                                        :S(Vector5)F(error)
VectorEnd
*------------ --------------------------------------------------------------------- -----------------
-INCLUDE 'datetime.inc'
