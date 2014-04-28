#include "GMM.h"
float const MeanFeat[13]={-50.4204379325795f, 20.8255100525249f, -2.01727894954906f, 9.63808584506113f, -3.63820077204282f, 5.35244247510115f, 0.674841851913823f, 0.120956497974079f, 1.87590483374293f, 0.119536448547541f, -0.679119789324378f, 1.57839819676811f, -1.30574273444048f
};
float const VarFeat[13]={76.6337497829081f, 15.5845771322990f, 16.8373756963654f, 11.6121085185689f, 21.6216167699983f, 13.0392642649480f, 23.5452990323528f, 17.0738138330820f, 22.9775289980119f, 22.3779443488194f, 17.2702163333020f, 17.1345980524426f, 18.9827222181358f
};
float const Mu[6][13]={
{-0.0315427788982370f,-0.277506530246352f,-0.0231054881208602f,0.162716970792611f,-0.104975989501853f,-0.00987248584552205f,-0.0238964263012325f,-0.0403083888508078f,-0.0708079010715095f,-0.0489181571221248f,-0.0239959704063341f,0.0203678630140305f,0.00963149353131219f},
{-0.210167335594763f,-0.301501947415205f,0.174410194523826f,-0.104719050579273f,0.0898274079487800f,-0.207488286222245f,0.0622122708947199f,0.111712031359015f,0.0628796721185000f,0.0174375442797222f,-0.0220077135649062f,-0.0196728083438556f,-0.00697878966704360f},
{0.0860168665101015f,-0.0284131034388283f,-0.223847541951832f,-0.152540411404648f,-0.104632659798910f,-0.0599982927989022f,-0.183930191413353f,-0.154364206519930f,-0.148326459604386f,-0.140284762113236f,-0.0645857081761300f,-0.0290468073394400f,-0.0532656540437632f},
{0.102021311903329f,-0.105422201500655f,-0.281512301783264f,-0.152669263039450f,-0.127796984694083f,-0.0666630563164969f,-0.190544512909271f,-0.191573966240869f,-0.161674312116517f,-0.102917927788485f,-0.134278064136275f,-0.0262705175011425f,-0.0347292732086924f},
{0.0569549616937138f,0.201586773780516f,0.146116979958085f,0.107887274264464f,-0.0625135353968440f,0.128384291650797f,0.120634155215194f,0.152687626523526f,0.0978050578006168f,0.0865078281321318f,0.0341355580976793f,-0.0452783902048195f,-0.0318484620098552f},
{-0.0551802616024539f,0.203796098144783f,0.165405793732730f,0.133616102224919f,0.219123107644050f,0.112019449369523f,0.165303407594536f,0.0830864502153059f,0.162873306125367f,0.150411889565998f,0.112022118286456f,0.0748581819184513f,0.108649984705676f}
};
float const inv_sigma[6][13][13]={
		{//j=1 k=1  1:13 row 1:13 colunm
		/* 1,1,1,:*/
		{2037.17099467641f,30.0358426766683f,-18.7565858819227f,-66.2646709209331f,187.113679421484f,-96.2808194484734f,185.983818209485f,-102.560421951825f,116.861913865180f,-78.1656070344280f,43.5267309059203f,-21.7027397319130f,18.3153781239938f},
		/* 1,1,2,:*/
		{30.0358426766683f,137.474570003529f,-52.4319174411346f,11.2986361912885f,-17.9732241255046f,24.9824106702676f,-45.4250203031550f,24.5510371716663f,-17.2622792505068f,7.73440512419966f,0.151430362592401f,-0.0131130207589070f,0.826684151740932f},
		{-18.7565858819227f,-52.4319174411346f,170.295165918708f,-34.4724727149444f,5.82243869855134f,-19.5376738358863f,33.1230608580212f,-16.9408414001950f,11.8909477093256f,-3.78020028431954f,-0.541103528364438f,0.411249774694142f,-0.629535389588856f},
		{-66.2646709209331f,11.2986361912885f,-34.4724727149444f,35.0162728684404f,-14.9885355970234f,15.2525644336805f,-23.9804748572562f,3.34907188501546f,3.19835291282695f,2.41725214953660f,-3.09737305838638f,1.73925802863295f,1.09491826697636f},
		{187.113679421484f,-17.9732241255046f,5.82243869855134f,-14.9885355970234f,93.5534739720142f,-46.6666717625517f,58.1233642788305f,-5.45438588185760f,-4.93218949239320f,-4.47857258024547f,12.4577865604720f,-5.61288581739031f,2.60373050612292f},
		{-96.2808194484734f,24.9824106702676f,-19.5376738358863f,15.2525644336805f,-46.6666717625517f,49.9500498966408f,-53.5988287202299f,14.7684623842781f,-7.12870167377742f,4.99004051543242f,-4.70063131177211f,4.82581120945492f,-2.47903940888791f},
		{185.983818209485f,-45.4250203031550f,33.1230608580212f,-23.9804748572562f,58.1233642788305f,-53.5988287202299f,147.805297087097f,-56.6453639180332f,36.9374656234800f,-11.9046157737872f,1.71002115834576f,-2.44570909289738f,4.32569660866172f},
		{-102.560421951825f,24.5510371716663f,-16.9408414001950f,3.34907188501546f,-5.45438588185760f,14.7684623842781f,-56.6453639180332f,70.9922590941039f,-54.1548431234637f,21.4062582374800f,-6.20127489941648f,4.60405100326652f,-2.66947851469649f},
		{116.861913865180f,-17.2622792505068f,11.8909477093256f,3.19835291282695f,-4.93218949239320f,-7.12870167377742f,36.9374656234800f,-54.1548431234637f,116.090616880777f,-66.8020171567190f,23.1068546445084f,-8.55487924303725f,7.91510629913811f},
		{-78.1656070344280f,7.73440512419966f,-3.78020028431954f,2.41725214953660f,-4.47857258024547f,4.99004051543242f,-11.9046157737872f,21.4062582374800f,-66.8020171567190f,101.255156412071f,-41.4932421284749f,15.7349410028893f,-7.28468149741549f},
		{43.5267309059203f,0.151430362592401f,-0.541103528364438f,-3.09737305838638f,12.4577865604720f,-4.70063131177211f,1.71002115834576f,-6.20127489941648f,23.1068546445084f,-41.4932421284749f,51.9456621398708f,-27.0123285226593f,13.6368623054684f},
		{-21.7027397319130f,-0.0131130207589070f,0.411249774694142f,1.73925802863295f,-5.61288581739031f,4.82581120945492f,-2.44570909289738f,4.60405100326652f,-8.55487924303725f,15.7349410028893f,-27.0123285226593f,44.1480956267039f,-22.7540434940684f},
		{18.3153781239938f,0.826684151740932f,-0.629535389588856f,1.09491826697636f,2.60373050612292f,-2.47903940888791f,4.32569660866172f,-2.66947851469649f,7.91510629913811f,-7.28468149741549f,13.6368623054684f,-22.7540434940684f,38.6154502129101f},
		},
		{//j=1 k=2  1:13 row 1:13 colunm
		{5467.63112916904f,-1570.95520106254f,1174.57660679124f,-561.114684168869f,739.922473519788f,-275.893155434676f,255.417377655449f,-121.182964785121f,101.304108685640f,-9.87334511534320f,-24.3985623603786f,47.6275619733588f,-8.66623253208391f},
		{-1570.95520106254f,623.348608572050f,-345.584293011153f,139.313350098345f,-157.255306173830f,71.9068290350935f,-86.9987653382590f,38.5640003333687f,-28.4665401201868f,7.68023925469332f,-0.577301230116645f,-5.18682859676964f,-1.45984015533761f},
		{1174.57660679124f,-345.584293011153f,321.682969868143f,-120.843999069571f,108.907086670092f,-43.7934133944127f,59.6721763155121f,-27.1570455139068f,18.8694200665562f,-8.67435715949231f,6.49261049360207f,-1.70333111399475f,4.18153426343448f},
		{-561.114684168869f,139.313350098345f,-120.843999069571f,91.7039711448492f,-88.9267681010661f,25.4280458560564f,-28.0384667408908f,13.3972690330682f,-9.85709735916471f,8.52541321078088f,-4.99799119102818f,0.591391289311327f,-1.53576285961606f},
		{739.922473519788f,-157.255306173830f,108.907086670092f,-88.9267681010661f,214.956774072715f,-72.7739159408477f,59.4291539544120f,-20.4965358176325f,17.5459310781283f,-14.0061163972442f,9.72231207163977f,-3.77535488989163f,1.74558984819895f},
		{-275.893155434676f,71.9068290350935f,-43.7934133944127f,25.4280458560564f,-72.7739159408477f,64.9605989016786f,-61.7144686303006f,18.2927223454286f,-10.8876864415352f,6.50268498625636f,-3.54116624911741f,2.76474233903717f,-2.03313341992272f},
		{255.417377655449f,-86.9987653382590f,59.6721763155121f,-28.0384667408908f,59.4291539544120f,-61.7144686303006f,164.141905867599f,-64.0795086929587f,35.3794445278665f,-16.4157401989200f,10.3879855129389f,-7.86894177333188f,3.41033360055978f},
		{-121.182964785121f,38.5640003333687f,-27.1570455139068f,13.3972690330682f,-20.4965358176325f,18.2927223454286f,-64.0795086929587f,74.9743662923128f,-58.1554465095244f,23.8370658585531f,-9.64935530529206f,5.83755999082690f,-3.84368834299140f},
		{101.304108685640f,-28.4665401201868f,18.8694200665562f,-9.85709735916471f,17.5459310781283f,-10.8876864415352f,35.3794445278665f,-58.1554465095244f,127.355457417507f,-72.6713978363198f,24.8707253873977f,-10.8668065429571f,6.31268517793136f},
		{-9.87334511534320f,7.68023925469332f,-8.67435715949231f,8.52541321078088f,-14.0061163972442f,6.50268498625636f,-16.4157401989200f,23.8370658585531f,-72.6713978363198f,107.576772264427f,-48.8913641591955f,22.5824648512159f,-8.69674857520315f},
		{-24.3985623603786f,-0.577301230116645f,6.49261049360207f,-4.99799119102818f,9.72231207163977f,-3.54116624911741f,10.3879855129389f,-9.64935530529206f,24.8707253873977f,-48.8913641591955f,58.6539774723484f,-34.2570190164297f,12.9263732205415f},
		{47.6275619733588f,-5.18682859676964f,-1.70333111399475f,0.591391289311327f,-3.77535488989163f,2.76474233903717f,-7.86894177333188f,5.83755999082690f,-10.8668065429571f,22.5824648512159f,-34.2570190164297f,53.2209045627440f,-26.2603766986658f},
		{-8.66623253208391f,-1.45984015533761f,4.18153426343448f,-1.53576285961606f,1.74558984819895f,-2.03313341992272f,3.41033360055978f,-3.84368834299140f,6.31268517793136f,-8.69674857520315f,12.9263732205415f,-26.2603766986658f,38.4479771569450f},
		},
		{//j=2 k=1  1:13 row 1:13 colunm
		{688.057697765491f,-36.8400299828084f,78.7800004926810f,-65.2083224055119f,129.290787875010f,-59.0396555382293f,108.918356111885f,-50.5251977008418f,38.7300733525405f,-24.1664951690120f,9.32035029189562f,-11.2247322159394f,5.22829054658069f},
		{-36.8400299828084f,54.9989894054666f,-10.9611505906841f,21.2715340056334f,-34.8208067320791f,20.9409819742295f,-20.8325245134130f,10.2834690546003f,-8.29353101185355f,11.0578053693728f,-0.454235460256921f,0.662871060352887f,2.57719979784759f},
		{78.7800004926810f,-10.9611505906841f,70.4832814732680f,-29.4729185724776f,42.5688114718086f,-15.3579165820681f,19.3009126107054f,-8.47815062044864f,9.82602763584067f,-11.2681827752976f,6.96165356810205f,-3.64171595825713f,0.655444139796240f},
		{-65.2083224055119f,21.2715340056334f,-29.4729185724776f,32.9045420575049f,-34.0334662403317f,11.0831145907022f,-13.6873809933965f,6.18034759780753f,-4.60303160307434f,4.55015854973935f,-0.942455558237363f,1.70112303981358f,-0.415478669765726f},
		{129.290787875010f,-34.8208067320791f,42.5688114718086f,-34.0334662403317f,94.7884023975893f,-35.0398586505934f,41.5126931930674f,-12.5337205648794f,9.91023797554312f,-4.06357704329655f,3.60231014609598f,-0.527079988559307f,-0.263129049563365f},
		{-59.0396555382293f,20.9409819742295f,-15.3579165820681f,11.0831145907022f,-35.0398586505934f,32.6209559159219f,-36.3689393179996f,14.6436928156827f,-5.78079330117793f,3.98828595734193f,-0.762987425329343f,0.211841046959325f,1.63541315918994f},
		{108.918356111885f,-20.8325245134130f,19.3009126107054f,-13.6873809933965f,41.5126931930674f,-36.3689393179996f,98.7670019951709f,-40.6097671114011f,27.6480098823026f,-15.5871857070061f,3.93698904196896f,-1.19664597372188f,-1.17821858000303f},
		{-50.5251977008418f,10.2834690546003f,-8.47815062044864f,6.18034759780753f,-12.5337205648794f,14.6436928156827f,-40.6097671114011f,47.9192204549053f,-35.9273787211927f,20.8287368742054f,-5.43811944476577f,3.89440969407573f,-0.234879378991819f},
		{38.7300733525405f,-8.29353101185355f,9.82602763584067f,-4.60303160307434f,9.91023797554312f,-5.78079330117793f,27.6480098823026f,-35.9273787211927f,77.1278812651963f,-44.7536859623987f,17.6803661940492f,-7.72365682247269f,2.44147752734430f},
		{-24.1664951690120f,11.0578053693728f,-11.2681827752976f,4.55015854973935f,-4.06357704329655f,3.98828595734193f,-15.5871857070061f,20.8287368742054f,-44.7536859623987f,65.8492318561488f,-29.7343781236779f,16.9638993991177f,-6.58753628482484f},
		{9.32035029189562f,-0.454235460256921f,6.96165356810205f,-0.942455558237363f,3.60231014609598f,-0.762987425329343f,3.93698904196896f,-5.43811944476577f,17.6803661940492f,-29.7343781236779f,37.1530056289107f,-21.7828899477185f,11.3490532780185f},
		{-11.2247322159394f,0.662871060352887f,-3.64171595825713f,1.70112303981358f,-0.527079988559307f,0.211841046959325f,-1.19664597372188f,3.89440969407573f,-7.72365682247269f,16.9638993991177f,-21.7828899477185f,33.2109384063962f,-15.8302370410830f},
		{5.22829054658069f,2.57719979784759f,0.655444139796240f,-0.415478669765726f,-0.263129049563365f,1.63541315918994f,-1.17821858000303f,-0.234879378991819f,2.44147752734430f,-6.58753628482484f,11.3490532780185f,-15.8302370410830f,25.8203318175449f},
		},
		{//j=2 k=2  1:13 row 1:13 colunm
		{415.752713283101f,37.6909981056882f,27.8999761285336f,4.38657121445218f,16.4097709922365f,6.98026227545404f,24.0178942297282f,-10.9154300035514f,22.2412168022490f,-5.78184370110420f,10.5441687936411f,1.54593205271346f,10.9880994260548f},
		{37.6909981056882f,38.0242920170395f,9.23231021289285f,6.34276085887710f,-5.19430654508419f,4.80481599355934f,-1.14771305180275f,5.59551705883467f,-4.50799377391513f,4.79346365929441f,2.06697277939047f,1.02721663359416f,1.19427796898615f},
		{27.8999761285336f,9.23231021289285f,27.7773283681400f,1.22902278073313f,1.28874919171440f,0.193812299031776f,6.23287641840787f,-4.18404502173425f,4.89521855938604f,-1.36954442632459f,2.53774349468672f,-0.710461990214089f,4.05817839356689f},
		{4.38657121445218f,6.34276085887710f,1.22902278073313f,10.9894747002033f,-2.89006870937348f,2.05680120751966f,-5.85037843276183f,3.07099379518290f,-2.12023027699995f,2.75616294979654f,-1.32022706680194f,1.91870552523968f,-0.579551194761926f},
		{16.4097709922365f,-5.19430654508419f,1.28874919171440f,-2.89006870937348f,36.1496862814575f,-9.60580676454982f,6.67269478609776f,-1.13564613240198f,3.59979843545248f,-2.36829658754758f,3.25111929791192f,-1.78589119061703f,2.41634802337169f},
		{6.98026227545404f,4.80481599355934f,0.193812299031776f,2.05680120751966f,-9.60580676454982f,12.4690661345282f,-6.06839284250281f,2.80791067861619f,-0.448779147567079f,0.372895820313747f,-0.365829978318601f,1.81990668783414f,-1.09828141613435f},
		{24.0178942297282f,-1.14771305180275f,6.23287641840787f,-5.85037843276183f,6.67269478609776f,-6.06839284250281f,39.5653892301644f,-10.3879167194484f,4.59347911225834f,-6.47282754062159f,2.38826069917216f,-2.92361642617863f,1.81574202979676f},
		{-10.9154300035514f,5.59551705883467f,-4.18404502173425f,3.07099379518290f,-1.13564613240198f,2.80791067861619f,-10.3879167194484f,20.2693247257037f,-10.4839908898639f,6.53305786659077f,-1.26691482140469f,0.894731355391850f,1.25740503626066f},
		{22.2412168022490f,-4.50799377391513f,4.89521855938604f,-2.12023027699995f,3.59979843545248f,-0.448779147567079f,4.59347911225834f,-10.4839908898639f,40.4570651238124f,-16.3104392233484f,5.12336756123864f,0.149941012300177f,1.06917178843292f},
		{-5.78184370110420f,4.79346365929441f,-1.36954442632459f,2.75616294979654f,-2.36829658754758f,0.372895820313747f,-6.47282754062159f,6.53305786659077f,-16.3104392233484f,35.5437390175463f,-11.2683275257486f,4.94516472240508f,-1.93989893063420f},
		{10.5441687936411f,2.06697277939047f,2.53774349468672f,-1.32022706680194f,3.25111929791192f,-0.365829978318601f,2.38826069917216f,-1.26691482140469f,5.12336756123864f,-11.2683275257486f,22.8262346218162f,-8.29836563617721f,4.23625948160879f},
		{1.54593205271346f,1.02721663359416f,-0.710461990214089f,1.91870552523968f,-1.78589119061703f,1.81990668783414f,-2.92361642617863f,0.894731355391850f,0.149941012300177f,4.94516472240508f,-8.29836563617721f,18.9125361448178f,-6.17339526060359f},
		{10.9880994260548f,1.19427796898615f,4.05817839356689f,-0.579551194761926f,2.41634802337169f,-1.09828141613435f,1.81574202979676f,1.25740503626066f,1.06917178843292f,-1.93989893063420f,4.23625948160879f,-6.17339526060359f,17.0112821544380f},
		},
		{//j=3 k=1  1:13 row 1:13 colunm
		{446.061558699309f,-31.3423218490575f,84.4702521644347f,-43.7208060962096f,113.226058110682f,-55.4931384245338f,89.9915879947605f,-45.5536964369246f,43.7256810818356f,-51.7817010810435f,32.3778775600233f,-20.1790149354077f,10.6578482016850f},
		{-31.3423218490575f,51.4412112091991f,-7.44389092506097f,7.43149725145566f,-2.14044733373695f,5.69316647739244f,-20.7974877090376f,17.7314657512466f,-24.7203078860194f,19.7115288131343f,-11.7184688905796f,6.29191956172489f,-2.36393079098275f},
		{84.4702521644347f,-7.44389092506097f,54.7923961243676f,-14.2430194552699f,5.21938959342607f,0.588098698044448f,4.01395794171526f,-10.2056216467872f,16.7303026571496f,-14.5755211618917f,8.58803949178088f,-1.86517737591430f,2.73237605506497f},
		{-43.7208060962096f,7.43149725145566f,-14.2430194552699f,21.5873279548672f,-17.0687526812282f,-1.29610074744096f,1.31264315918036f,2.98490625371207f,-4.60093210147855f,8.42868787373058f,-6.37848152664181f,3.35576319571252f,-2.29269231528591f},
		{113.226058110682f,-2.14044733373695f,5.21938959342607f,-17.0687526812282f,87.8459799537587f,-23.6708041279801f,10.5288863523550f,-3.34911820956210f,7.37581947288391f,-11.0420198639803f,11.8290479060026f,-9.21882441477182f,2.85542922633421f},
		{-55.4931384245338f,5.69316647739244f,0.588098698044448f,-1.29610074744096f,-23.6708041279801f,33.2170584054234f,-29.5412694456580f,7.09150837713943f,-0.915605445878169f,5.45601773589915f,-5.30196098295181f,2.87436009206746f,-1.62245595889926f},
		{89.9915879947605f,-20.7974877090376f,4.01395794171526f,1.31264315918036f,10.5288863523550f,-29.5412694456580f,106.717483202509f,-39.1196089837403f,16.7323736281573f,-7.01180596026015f,5.39135397441239f,-1.84876318988179f,0.752850438515033f},
		{-45.5536964369246f,17.7314657512466f,-10.2056216467872f,2.98490625371207f,-3.34911820956210f,7.09150837713943f,-39.1196089837403f,49.9636380847938f,-32.4280470058408f,13.5089725166469f,-6.24054070653869f,2.80155715259026f,-1.45040317601892f},
		{43.7256810818356f,-24.7203078860194f,16.7303026571496f,-4.60093210147855f,7.37581947288391f,-0.915605445878169f,16.7323736281573f,-32.4280470058408f,80.0943270364437f,-46.4995852923698f,15.8319418296498f,-7.18576853451571f,2.92625844269559f},
		{-51.7817010810435f,19.7115288131343f,-14.5755211618917f,8.42868787373058f,-11.0420198639803f,5.45601773589915f,-7.01180596026015f,13.5089725166469f,-46.4995852923698f,77.5691255467120f,-31.3479657223675f,9.05656642441574f,-2.46718152385250f},
		{32.3778775600233f,-11.7184688905796f,8.58803949178088f,-6.37848152664181f,11.8290479060026f,-5.30196098295181f,5.39135397441239f,-6.24054070653869f,15.8319418296498f,-31.3479657223675f,39.7326053177012f,-18.9079040837298f,5.86814304184348f},
		{-20.1790149354077f,6.29191956172489f,-1.86517737591430f,3.35576319571252f,-9.21882441477182f,2.87436009206746f,-1.84876318988179f,2.80155715259026f,-7.18576853451571f,9.05656642441574f,-18.9079040837298f,33.6672602955556f,-15.3515334790882f},
		{10.6578482016850f,-2.36393079098275f,2.73237605506497f,-2.29269231528591f,2.85542922633421f,-1.62245595889926f,0.752850438515033f,-1.45040317601892f,2.92625844269559f,-2.46718152385250f,5.86814304184348f,-15.3515334790882f,29.8661614936425f},
		},
		{//j=3 k=2  1:13 row 1:13 colunm
		{5105.18857713470f,-1316.07786684289f,737.752411997684f,-431.822799316616f,735.157049508468f,-332.497118323775f,374.690531235928f,-171.951627383949f,134.757900417582f,-22.0963313212890f,12.4489152227328f,28.8761635872563f,-3.77196903697561f},
		{-1316.07786684289f,402.342967340244f,-244.350070257766f,137.375077598155f,-209.501797309579f,88.5120198639879f,-94.8241508937368f,41.3317881386334f,-35.3243690075349f,2.24649119267927f,-0.583516890290103f,-3.90405953985197f,0.985516902284729f},
		{737.752411997684f,-244.350070257766f,275.053249184696f,-117.823536560182f,147.592436968402f,-47.1745952474621f,45.5289021581204f,-25.8678622021298f,25.7802831786759f,-8.70646618646257f,4.33501961649229f,-1.78784923887912f,2.63106690655180f},
		{-431.822799316616f,137.375077598155f,-117.823536560182f,83.1919330261076f,-89.6441769408633f,21.3703123002035f,-26.7232418914347f,10.8772373497674f,-9.33339069786314f,7.17707277727416f,-4.68629724355754f,0.957247988787698f,0.330867521555996f},
		{735.157049508468f,-209.501797309579f,147.592436968402f,-89.6441769408633f,179.414561331445f,-68.5340876815083f,70.9665557666473f,-25.0555702436757f,22.7752478428015f,-19.8982683370303f,7.88126683867505f,-6.26142816527366f,-8.09769196620420f},
		{-332.497118323775f,88.5120198639879f,-47.1745952474621f,21.3703123002035f,-68.5340876815083f,61.3425692249783f,-64.5776254708859f,20.8773518981977f,-14.4300107651409f,10.0339783232780f,-5.73884438338284f,3.22989328076700f,-0.600695748403032f},
		{374.690531235928f,-94.8241508937368f,45.5289021581204f,-26.7232418914347f,70.9665557666473f,-64.5776254708859f,162.928080438882f,-73.0371439285939f,47.6897814520751f,-22.9930001178424f,13.7465219871211f,-8.91666973961179f,7.62212580858504f},
		{-171.951627383949f,41.3317881386334f,-25.8678622021298f,10.8772373497674f,-25.0555702436757f,20.8773518981977f,-73.0371439285939f,77.9975467921391f,-63.6165926918003f,29.0007882857924f,-13.2634072655709f,7.36262099352630f,-4.53077437547510f},
		{134.757900417582f,-35.3243690075349f,25.7802831786759f,-9.33339069786314f,22.7752478428015f,-14.4300107651409f,47.6897814520751f,-63.6165926918003f,129.298445406201f,-75.4843751472989f,28.4352017669575f,-11.2881378082005f,6.42994766167424f},
		{-22.0963313212890f,2.24649119267927f,-8.70646618646257f,7.17707277727416f,-19.8982683370303f,10.0339783232780f,-22.9930001178424f,29.0007882857924f,-75.4843751472989f,107.458295380517f,-50.9813683185927f,21.0875826285775f,-9.61777656420102f},
		{12.4489152227328f,-0.583516890290103f,4.33501961649229f,-4.68629724355754f,7.88126683867505f,-5.73884438338284f,13.7465219871211f,-13.2634072655709f,28.4352017669575f,-50.9813683185927f,61.1899046206628f,-33.0120833141645f,13.5329957467920f},
		{28.8761635872563f,-3.90405953985197f,-1.78784923887912f,0.957247988787698f,-6.26142816527366f,3.22989328076700f,-8.91666973961179f,7.36262099352630f,-11.2881378082005f,21.0875826285775f,-33.0120833141645f,48.3481190648494f,-24.9334563267868f},
		{-3.77196903697561f,0.985516902284729f,2.63106690655180f,0.330867521555996f,-8.09769196620420f,-0.600695748403032f,7.62212580858504f,-4.53077437547510f,6.42994766167424f,-9.61777656420102f,13.5329957467920f,-24.9334563267868f,37.7075678265701f},
		}
};
float const det_sigma[6]={5010175.12450977f,9898478.68564487f,154489.585578178f,9149.21739335637f,182042.839723080f,4889265.23851760f}; //here  det_sigma =1/sqrt((2*pi)^nbVar * (abs(det(Sigma))+realmin));
float const Priors[6]={0.478909279795927,	0.521090720204073,	0.773483303641223,	0.226516696358777,	0.439566287548368,	0.560433712451633};

int GMM(Variables* P){
int i,j,k,l,m;

float MelBuffer[13];
float GMMBuffer[13];
float GMMResult[13];
float Prob[6]={0,0,0,0,0,0};
for(i=0;i<13;i++){
	MelBuffer[i] = (P->mfcc[i] - MeanFeat[i])/VarFeat[i];
}


for(j=0;j<3;j++){
	for(k=0;k<2;k++){
		int ID=2*j+k;
		for(i=0;i<13;i++){
			GMMBuffer[i] = MelBuffer[i] - Mu[ID][i];
		}
		// GMMBuffer_matrix*sigma_matrix .*GMMBuffer_matrix
		for(l=0;l<13;l++){
			float temp=0;
			for(m=0;m<13;m++){
				temp+=GMMBuffer[m]*inv_sigma[ID][l][m];
			}
			Prob[ID]+=temp*GMMBuffer[l];
		}
		Prob[ID]= (float)(exp(-0.5*Prob[ID])*det_sigma[ID]);
	}
}

float P1=Prob[0]*Priors[0]+Prob[1]*Priors[1];
float P2=Prob[2]*Priors[2]+Prob[3]*Priors[3];
float P3=Prob[4]*Priors[4]+Prob[5]*Priors[5];

if(P1>P2 && P1>P3)
	return 1;
else if(P2>P1 && P2>P3)
	return 2;
else
	return 3;


}