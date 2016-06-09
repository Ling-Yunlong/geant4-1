//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// INCL++ intra-nuclear cascade model
// Pekka Kaitaniemi, CEA and Helsinki Institute of Physics
// Davide Mancusi, CEA
// Alain Boudard, CEA
// Sylvie Leray, CEA
// Joseph Cugnon, University of Liege
//
// INCL++ revision: v5.1.8
//
#define INCLXX_IN_GEANT4_MODE 1

#include "globals.hh"

/** \file G4INCLHashing.hh
 * \brief Functions for hashing a collection of NucleonItems.
 *
 * \date 12th October 2012
 * \author Davide Mancusi
 */

#ifndef G4INCLHASHING_HH_
#define G4INCLHASHING_HH_

#ifdef INCLXX_IN_GEANT4_MODE
#define INCL_CACHING_CLUSTERING_MODEL_INTERCOMPARISON_Set 1
#endif // INCLXX_IN_GEANT4_MODE

#ifdef INCL_CACHING_CLUSTERING_MODEL_INTERCOMPARISON_HashMask

#include <algorithm>
#include <numeric>
#include <climits>
// #include <cassert>

namespace G4INCL {

  namespace Hashing {

    typedef G4int NucleonItem;

    // the C++ standard guarantees that unsigned long is at least 32-bit long
    typedef unsigned long HashType;

    /* Depending on the size of the HashType type, we use 32-bit or 64-bit
     * binary masks. 64-bit masks guarantee lower collision rates (about a
     * factor of 3). Checks are done using compile-time constants defined in
     * the standard <climits> header.
     */

    namespace {
      const G4int maskTableSize = 500;
      HashType mask[maskTableSize] = {
#if ULONG_MAX >= 18446744073709551615UL // 2^64-1
        // unsigned longs have at least 64 bits here
        4702504706864814267UL,
        15867743096752998125UL,
        1925133831785711339UL,
        3063678697824149615UL,
        3234475698548538313UL,
        7917662962824220875UL,
        9924018995951912525UL,
        4682901166658838314UL,
        981361508296534881UL,
        18376824469534567556UL,
        5343971687892173674UL,
        10169451505660710328UL,
        7865786236744900341UL,
        10279352445822536091UL,
        7089630702066408548UL,
        4808534960882600398UL,
        12538238618753707399UL,
        16091508301730012097UL,
        14073498192850855514UL,
        9966250765115558375UL,
        5718582854016674314UL,
        5837057680281951483UL,
        1596870119086046964UL,
        15866877264435719977UL,
        12743659579234384899UL,
        13589152059793213451UL,
        3364441792317801205UL,
        17190534087980602002UL,
        2252844317879582875UL,
        16883577324406774376UL,
        15985239218161130895UL,
        3661288085782215193UL,
        17294313791381397188UL,
        9405115097872546015UL,
        2834208340246893214UL,
        15589349083551097162UL,
        7475687940900359446UL,
        2706367355862311522UL,
        17987211229193808759UL,
        6863833750504706813UL,
        3685392250678121047UL,
        11759380240055300923UL,
        13403449794574083242UL,
        1985973959990096358UL,
        15223952677867744295UL,
        6118509595165778043UL,
        815155895778500187UL,
        18185573450595916074UL,
        5501350898920817482UL,
        382043392356382894UL,
        7212372096396984419UL,
        17216082813533838272UL,
        11664929762302443627UL,
        12742534429666211769UL,
        10885936672907243422UL,
        7408809357861601856UL,
        7235809803254354851UL,
        10923449527984005964UL,
        11846584293234382222UL,
        10656509822128626836UL,
        2129734486054336774UL,
        4595091378435214061UL,
        9874818728883580365UL,
        5946304945334907747UL,
        10039693308935676801UL,
        13281974385330546238UL,
        18100260506304059768UL,
        2874169620796400411UL,
        7108218580097801290UL,
        1609767302727070556UL,
        11296708194993589343UL,
        13937355006285948174UL,
        4714440178991372538UL,
        16551309706022489963UL,
        10000176812340548792UL,
        11878058786115320873UL,
        17227685596830233118UL,
        6913194524255335692UL,
        8581157771211862326UL,
        7692516248830269819UL,
        4834805303668841320UL,
        17683695285788382628UL,
        3163270552620053128UL,
        7501354178009882428UL,
        18032292064795682158UL,
        14903091228667847945UL,
        12658813769564311973UL,
        11071671991853641692UL,
        1898680911275368123UL,
        11850012838739454071UL,
        11605340059702017433UL,
        1993475538032240150UL,
        14225643076178260981UL,
        6073746146812460969UL,
        10427646200541715974UL,
        8534830515125041658UL,
        12137748989343460832UL,
        401619354176178507UL,
        10566842722928406433UL,
        2726007197202736953UL,
        12070986965363522186UL,
        14306741808513945796UL,
        9411600548893210409UL,
        10677814577847517837UL,
        2524629524427176799UL,
        13769537677295179355UL,
        2202164469715649820UL,
        18048299992904550974UL,
        11620367199819191275UL,
        12863789957300408274UL,
        9470331939464407385UL,
        1530202837192022943UL,
        8835064955139736011UL,
        8145200231008682998UL,
        7839809942742909916UL,
        9138434136821323472UL,
        14559393378324131957UL,
        17365140272468484867UL,
        12986052322695094991UL,
        15032117076709947810UL,
        3710476151324188272UL,
        1301282554894996635UL,
        10667152340954078766UL,
        6983777770664759713UL,
        16611664140947488647UL,
        12136122930610106551UL,
        15900825787656229127UL,
        10248132639811024681UL,
        11698219706208598358UL,
        12307261434875431124UL,
        14365082098869236341UL,
        7765033571440697089UL,
        14810290195054154855UL,
        9618298383970391972UL,
        5541541247731255102UL,
        16567733959804019203UL,
        17600930129818672877UL,
        5232016726685772558UL,
        226023602797856284UL,
        3268675878373668427UL,
        15412168229420758040UL,
        9483353024934253554UL,
        12957711733854877641UL,
        13202855362863795860UL,
        14659098127488639325UL,
        5642266569510167780UL,
        8405185641276686415UL,
        12567678120796482638UL,
        5572663458795121052UL,
        11292924459778654315UL,
        12907130784326268258UL,
        2781503111506861655UL,
        14052031913630628463UL,
        7662091316495917798UL,
        12388345726433231307UL,
        2855096782092770172UL,
        143760647337486211UL,
        5268378935483038729UL,
        14347085534022186031UL,
        8226804542313416051UL,
        503042565036387930UL,
        13277939264481364629UL,
        4807934385534294767UL,
        6554792055682376182UL,
        3505789456125861647UL,
        17485983928210687457UL,
        6551825177685364660UL,
        6530399878351375719UL,
        11618616536378075323UL,
        8710939588645435621UL,
        15913776342681996234UL,
        12975832615100357766UL,
        11385194348110364656UL,
        7334273726237402463UL,
        18215307287507846020UL,
        108052987233117093UL,
        14819872198639686030UL,
        7651108032227837181UL,
        7326148382022660565UL,
        15520843621422491193UL,
        14890169031248899249UL,
        3302880341533628710UL,
        17509231796729795392UL,
        6938974810266312299UL,
        9904104728819873047UL,
        10277854813228565819UL,
        8062859346560164933UL,
        11953220042241400520UL,
        8905905195342696566UL,
        8620925171331846539UL,
        15354008279539346333UL,
        16255477929425666651UL,
        15625465014312179739UL,
        6560194503171884780UL,
        458508474659358201UL,
        11178141379033004711UL,
        7025589002713530514UL,
        6196040542056180472UL,
        1771599404396005753UL,
        490848885681539136UL,
        15438702070227423706UL,
        8790555204480314499UL,
        6572556090639551862UL,
        3282457245646221158UL,
        4239195535437592000UL,
        16001734625059485025UL,
        14396081511655033925UL,
        10261432601192522025UL,
        9247260218125952769UL,
        16080570631414044686UL,
        15656989589485934942UL,
        10761254633620277391UL,
        1363122333823743651UL,
        14847079675279608117UL,
        6077849015756077442UL,
        15290828636077500470UL,
        220281240092237795UL,
        15760968530563963031UL,
        1364939791854189821UL,
        5997510653682588941UL,
        2006088633984038082UL,
        1383498232486134285UL,
        17859041093815211104UL,
        15894184107946313879UL,
        18173079296415961736UL,
        3443997055549483358UL,
        5294019672823936930UL,
        1341830676613088487UL,
        581727297735446503UL,
        18219577357392561487UL,
        17639313299012264080UL,
        14222133713791167321UL,
        5879505043799386532UL,
        7557129766625449226UL,
        13360075610958017985UL,
        12724115904336527780UL,
        16753075547920915484UL,
        4116411708112171871UL,
        16025692682808517910UL,
        4003328942103420939UL,
        9811320057930109787UL,
        3576072849789367484UL,
        17075748046009610792UL,
        12833406223291392866UL,
        9648248336540660688UL,
        17476583957989300837UL,
        16827359136787046510UL,
        4345039153564047180UL,
        1224716260729000059UL,
        13959598322342824445UL,
        10743140873520517726UL,
        13340880620026565045UL,
        9192556363923792986UL,
        3841907957831078749UL,
        246438482871824834UL,
        4260787342534664069UL,
        17100720253388227686UL,
        11544966922599678750UL,
        9293075407897592921UL,
        1610905992411273162UL,
        2239787421847352995UL,
        15182496755963432304UL,
        1823665993529743824UL,
        7263153004799849282UL,
        11497980475724160945UL,
        1274355111868335897UL,
        15057972526005432563UL,
        11823052640709049475UL,
        15927429045819933119UL,
        14618154733049321749UL,
        16861991482751749049UL,
        5936874228331837512UL,
        15290754097890487720UL,
        9191375772889979508UL,
        6816129633576113785UL,
        12923817606396645484UL,
        8875993281327238816UL,
        123714282527043508UL,
        7179882084825590703UL,
        3925024599322075567UL,
        2426048646574757412UL,
        10665962527629258587UL,
        12646312850531314143UL,
        528129165734836933UL,
        3701120955488573646UL,
        15861534485058814280UL,
        14022467189115595098UL,
        9502851142036471883UL,
        12432213096681522867UL,
        751500370320404802UL,
        1606345595406828785UL,
        10313713517508959984UL,
        6565609239876268324UL,
        8654149379457545096UL,
        6548830896464452248UL,
        1464368532414012445UL,
        4302937696445584032UL,
        17063664947863781419UL,
        8038577586991861682UL,
        10951259595021013980UL,
        7709630466255725074UL,
        609806407111517279UL,
        13860208046684354033UL,
        15140303568956907423UL,
        4803057729274452412UL,
        4367455766719288283UL,
        320027280359511727UL,
        16020877306388137190UL,
        3764882323315346488UL,
        11972546313392727283UL,
        7977601566213555124UL,
        15148378244947865280UL,
        4483722253329626321UL,
        16560836625841776840UL,
        14666077208671482135UL,
        9298193298119711211UL,
        12015014023744623893UL,
        10191703760489555596UL,
        1316913070589847725UL,
        15881746492947991011UL,
        13665807677473998048UL,
        14390309917106480591UL,
        17231567872468478469UL,
        4562957401728953232UL,
        11501454621029854493UL,
        10252134323451005656UL,
        12021948387925309670UL,
        3525149157835967069UL,
        10292558937206299109UL,
        13725724605985217856UL,
        175033751151696127UL,
        14720951489402332470UL,
        11927624343611332814UL,
        567437266624809204UL,
        14161392585443694227UL,
        8725463779420655722UL,
        12063468735510140344UL,
        12026523736635889408UL,
        16565599419781878456UL,
        7086470817660744490UL,
        14809513609573064984UL,
        10898762682820885052UL,
        13982083571459739493UL,
        15656618354974864372UL,
        4239583100143107224UL,
        4322769551545487304UL,
        13825585217369415084UL,
        5136324433139686016UL,
        8179080547263771206UL,
        8279259187088296150UL,
        6381371846375303738UL,
        3142014871877744388UL,
        3417815453103862427UL,
        5556557018553548625UL,
        7788492627093668219UL,
        2446537327809742760UL,
        7165731799178534002UL,
        10969060298437286606UL,
        16392640790529049402UL,
        4905600830298563047UL,
        12442106640046578583UL,
        7139041375816724964UL,
        18098103947732186633UL,
        2078238351823174321UL,
        9929562085097862277UL,
        14231090695955652612UL,
        16914810114016502414UL,
        9172887937989634160UL,
        10057184693043820912UL,
        8739867056556181319UL,
        1879322488574672564UL,
        6706469496298082633UL,
        17962793280504692541UL,
        2796622365685518391UL,
        14206454203780509608UL,
        11911505185092294091UL,
        13188421404411005493UL,
        1002631262698104372UL,
        16116424222649594941UL,
        731059841323644991UL,
        16630196285890835221UL,
        6275370517569960592UL,
        2762335813606797964UL,
        1550415195017045798UL,
        8084777285994689863UL,
        4858045103923411134UL,
        13517076072140006105UL,
        16656029182431041189UL,
        6076064496187725305UL,
        15281271591975529160UL,
        2275428871306187428UL,
        15396744606475751109UL,
        15460778948302864604UL,
        6107847787338713474UL,
        9357621545767658217UL,
        4805014239018879550UL,
        17869119773972988965UL,
        17868495682315323441UL,
        10660808254721474616UL,
        7308276872489783138UL,
        4234856545479982050UL,
        1223334879029033304UL,
        10995800624761949288UL,
        16283797325974965665UL,
        12410167362078398820UL,
        12918484557456873081UL,
        14423314551522087679UL,
        4967867692111402622UL,
        16197846038770304940UL,
        11809884480603742831UL,
        16802686488973843640UL,
        2354077987008574056UL,
        9978003576519895777UL,
        5506048811554826358UL,
        18433781523380564149UL,
        4302137793340917657UL,
        978195094879846769UL,
        2377823329880292548UL,
        3464291122006072777UL,
        18046845603455616162UL,
        13944776942598500463UL,
        4000590694056817931UL,
        496833875371241644UL,
        16247695245933522501UL,
        1505779951058046438UL,
        11430822963532124358UL,
        4729903064888922231UL,
        8864507718425611027UL,
        14643598183997536338UL,
        4480511581250357378UL,
        11133239898726463704UL,
        17471052555928421508UL,
        15541989708583753235UL,
        7461560065837635158UL,
        13956421526574063689UL,
        3743280538841219763UL,
        12020611143801404565UL,
        6618703997501212010UL,
        3729371474666129836UL,
        17869245751809494685UL,
        1833331385744685838UL,
        1506104207003999508UL,
        8158509169843256229UL,
        10212507222875597491UL,
        7211593336579637715UL,
        14341253648497092530UL,
        4511202703905924031UL,
        8043833010361144102UL,
        2512875450160943286UL,
        18235665817864664213UL,
        8317446467730476132UL,
        11182884000969346056UL,
        548357546399462395UL,
        1960628024952592835UL,
        4650095513901192085UL,
        12679676177772217157UL,
        3487733703240934135UL,
        6446640077094538365UL,
        1114715573562175630UL,
        16622874083185883281UL,
        17081932748524927392UL,
        17192402071367355968UL,
        15013800339030843048UL,
        3718961432784285989UL,
        14953817216655866296UL,
        11410118254031919487UL,
        17718071771819733200UL,
        6970769915355275987UL,
        14244261541942962860UL,
        295778071941084510UL,
        553041658124347434UL,
        571128341496031343UL,
        6867891970504820807UL,
        16515587447694198371UL,
        3932569386063656416UL,
        15542525920467376967UL,
        4513384432419818675UL,
        7336705434792969335UL,
        1342984449178439078UL,
        10672151960711459277UL,
        11668091039787926587UL,
        15308742994910314323UL,
        8337161158579684228UL,
        5390473811288298369UL,
        444117188512458090UL,
        8602531868090961223UL,
        1632809043568697774UL,
        11829254858211213981UL,
        4634227867572760505UL,
        16086237486731074061UL,
        4844172753138751369UL,
        4992022238300904271UL,
        11132360655811360102UL,
        11660714643785469458UL,
        2468480999090126185UL,
        10912054708474512716UL,
        12659667168896228555UL,
        11988368921832936489UL,
        5116996783249524791UL,
        253818271896405507UL
#else // ULONG_MAX >= 18446744073709551615
          // unsigned longs have less than 64 bits here
          4218046471UL,
        1917139952UL,
        2103556369UL,
        1588695878UL,
        4215491346UL,
        216507845UL,
        2296134958UL,
        1868314761UL,
        3228779327UL,
        1785085484UL,
        4228225705UL,
        1165369009UL,
        3142089765UL,
        431503981UL,
        3369606777UL,
        745480828UL,
        2744780773UL,
        689045082UL,
        1900506313UL,
        2497498204UL,
        368683604UL,
        2225005389UL,
        781333974UL,
        4132002528UL,
        2847677322UL,
        343783736UL,
        2901322050UL,
        3337243677UL,
        1665993590UL,
        233599841UL,
        1022462535UL,
        1680112766UL,
        500144658UL,
        3013714463UL,
        1102944137UL,
        424404167UL,
        1616048503UL,
        3058072676UL,
        2626558419UL,
        2270217197UL,
        1042360030UL,
        1406615072UL,
        2817651072UL,
        3066388841UL,
        3595996753UL,
        2530300747UL,
        1068533293UL,
        3850615434UL,
        2000952241UL,
        500251219UL,
        2785863467UL,
        116749905UL,
        2534901578UL,
        2762569636UL,
        441176494UL,
        3611264136UL,
        708254627UL,
        3107133154UL,
        3498823450UL,
        3710248321UL,
        3408201403UL,
        2483680087UL,
        1593406496UL,
        2358632005UL,
        1113775647UL,
        1296788200UL,
        866750108UL,
        1511795181UL,
        2007682240UL,
        1383572622UL,
        2747177348UL,
        751086457UL,
        3862498228UL,
        1330825518UL,
        1893848486UL,
        3716728436UL,
        257714096UL,
        1129572537UL,
        3411765329UL,
        1445308638UL,
        1675128925UL,
        1177771214UL,
        610662193UL,
        308703855UL,
        3766028156UL,
        2406778266UL,
        1614133721UL,
        3094138658UL,
        644181699UL,
        3585820756UL,
        228354647UL,
        3895845225UL,
        837654579UL,
        2423338235UL,
        3626844735UL,
        4004795529UL,
        1966777404UL,
        4099992662UL,
        561993057UL,
        478026097UL,
        2726060916UL,
        160900471UL,
        4067242522UL,
        2107667107UL,
        2291883857UL,
        3366222014UL,
        804030225UL,
        815232690UL,
        4173469665UL,
        3680594736UL,
        1812916838UL,
        953829049UL,
        645064420UL,
        893103776UL,
        1484445384UL,
        1704310224UL,
        3169988691UL,
        994674462UL,
        3348302238UL,
        420911742UL,
        3997852732UL,
        3006569532UL,
        244288857UL,
        3012303255UL,
        3091414730UL,
        3919806716UL,
        815658776UL,
        396540369UL,
        2296675021UL,
        3199014033UL,
        2569108436UL,
        3862344457UL,
        4058338881UL,
        1161706542UL,
        2972997031UL,
        2099532487UL,
        160888949UL,
        427549488UL,
        3061518659UL,
        66373532UL,
        3444886884UL,
        2530414305UL,
        3380064368UL,
        937051782UL,
        1302891919UL,
        2463653477UL,
        3547879633UL,
        2260320717UL,
        832678359UL,
        2453616965UL,
        2193052461UL,
        799622604UL,
        3629014225UL,
        1522933084UL,
        2498150583UL,
        1976833008UL,
        1725662928UL,
        1733324678UL,
        3374380020UL,
        818903650UL,
        718472891UL,
        411252729UL,
        3187730653UL,
        798673927UL,
        1222802842UL,
        1985038219UL,
        1623995355UL,
        2603784033UL,
        4261727525UL,
        3939193905UL,
        2256923068UL,
        507372076UL,
        229897092UL,
        3447212333UL,
        1015331998UL,
        1624914646UL,
        3270616777UL,
        1922996004UL,
        2303929294UL,
        3083527264UL,
        3511924852UL,
        651582997UL,
        2830297570UL,
        2541981492UL,
        3229134142UL,
        535111766UL,
        2531439891UL,
        1176474835UL,
        1746643607UL,
        196953906UL,
        190859135UL,
        1471944757UL,
        3764050027UL,
        2300961517UL,
        1200836119UL,
        1934885757UL,
        1017153529UL,
        864626426UL,
        65215191UL,
        3649915955UL,
        2649000649UL,
        3056185941UL,
        2895789221UL,
        2705123786UL,
        3486894128UL,
        1764275188UL,
        800856520UL,
        1121637219UL,
        3470689154UL,
        2031015368UL,
        1799564405UL,
        412027838UL,
        3505785501UL,
        819633830UL,
        2841515279UL,
        397789381UL,
        3850545068UL,
        4038096561UL,
        702453020UL,
        298184560UL,
        1331143206UL,
        3832472400UL,
        483752162UL,
        3365506546UL,
        2403178818UL,
        2588604760UL,
        3630868707UL,
        2672754775UL,
        3834743541UL,
        625254315UL,
        3404805826UL,
        2758773926UL,
        3539158313UL,
        1304746437UL,
        4228336097UL,
        1790470857UL,
        2017211747UL,
        2823780770UL,
        1361022238UL,
        2442638132UL,
        3465700788UL,
        2602256049UL,
        61072285UL,
        1290754848UL,
        1365538365UL,
        2885926246UL,
        3366937675UL,
        1976271220UL,
        4274857987UL,
        2846551234UL,
        3730952612UL,
        785655762UL,
        2640747064UL,
        2479569674UL,
        2988213501UL,
        238402214UL,
        2736968438UL,
        1273211556UL,
        2993298676UL,
        2076907296UL,
        169664466UL,
        3590743418UL,
        2853715414UL,
        1494116982UL,
        3408636076UL,
        1354085945UL,
        2121174096UL,
        557203192UL,
        2005947221UL,
        2790204730UL,
        3673048078UL,
        2710286579UL,
        2759941695UL,
        2554805430UL,
        1565053908UL,
        1516728908UL,
        457211737UL,
        4053842378UL,
        1926452932UL,
        121166907UL,
        1884552326UL,
        2050083102UL,
        783329973UL,
        1002934724UL,
        2916755028UL,
        1574390275UL,
        4246041184UL,
        112940213UL,
        4213344814UL,
        3831377539UL,
        3593710048UL,
        184196123UL,
        62388243UL,
        1824724968UL,
        1553056630UL,
        2471314862UL,
        1580248726UL,
        1641907471UL,
        4182117804UL,
        244827601UL,
        2673787044UL,
        1245428424UL,
        1254024234UL,
        1944146503UL,
        2068525708UL,
        1452126855UL,
        1368763640UL,
        2063660828UL,
        306042674UL,
        668216774UL,
        2002594576UL,
        3192370193UL,
        4189750176UL,
        1815590529UL,
        2838559664UL,
        3322933511UL,
        708460425UL,
        3093499804UL,
        219970021UL,
        2136064297UL,
        1281979964UL,
        3437613761UL,
        544003806UL,
        2998811936UL,
        1481470929UL,
        2880899873UL,
        3617899122UL,
        2269535287UL,
        2964733041UL,
        1437018425UL,
        4136436935UL,
        2892386937UL,
        2312588208UL,
        3470825412UL,
        3048839250UL,
        3124535567UL,
        74106735UL,
        740534715UL,
        780483498UL,
        1703009387UL,
        3908417545UL,
        2925498568UL,
        570244170UL,
        768611579UL,
        2561901277UL,
        3369289022UL,
        298430172UL,
        3399976658UL,
        2781253163UL,
        2203229433UL,
        4083764265UL,
        1813739940UL,
        2495956219UL,
        1733876904UL,
        2961522297UL,
        2806638528UL,
        210215678UL,
        3179651913UL,
        3488143624UL,
        2162063032UL,
        2230441611UL,
        3104777333UL,
        1901009578UL,
        2357529595UL,
        1661659881UL,
        2275001257UL,
        1089779619UL,
        1019581619UL,
        3676689000UL,
        2363224232UL,
        3087179246UL,
        2521585396UL,
        1172580989UL,
        3363959227UL,
        1379171244UL,
        2568664929UL,
        2716951910UL,
        634711458UL,
        1881366407UL,
        2339310622UL,
        1437137856UL,
        775517573UL,
        2403816337UL,
        3643691625UL,
        2796142813UL,
        2636271743UL,
        3548645335UL,
        2401818065UL,
        1430955355UL,
        1529261488UL,
        2672050975UL,
        1824816344UL,
        437321422UL,
        1010469737UL,
        975873927UL,
        3808619211UL,
        1306922849UL,
        2306306586UL,
        3492263153UL,
        915764428UL,
        4049080639UL,
        2584666827UL,
        2248503228UL,
        1156685342UL,
        3545089377UL,
        2927987815UL,
        1188340469UL,
        1983809416UL,
        2359080396UL,
        3026745995UL,
        1020085481UL,
        2455748822UL,
        2973731428UL,
        1685598150UL,
        2459914554UL,
        222412187UL,
        1550326895UL,
        3808681066UL,
        910364646UL,
        4011483211UL,
        3449464402UL,
        3094973082UL,
        3370230650UL,
        1693151952UL,
        3574854040UL,
        3557103099UL,
        4108399894UL,
        3762036621UL,
        2337346271UL,
        1005455572UL,
        3860207735UL,
        1771002576UL,
        199004943UL,
        1578846676UL,
        2676995104UL,
        4076948954UL,
        830057378UL,
        459065499UL,
        3804368733UL,
        3499868406UL,
        852696530UL,
        514613423UL,
        1584281952UL,
        985799155UL,
        1895009366UL,
        3825253357UL,
        1782693174UL,
        2196979238UL,
        1308429445UL,
        2960767408UL,
        2285337396UL,
        2065293874UL,
        1306724979UL,
        4056398081UL,
        4047112430UL,
        3606840914UL,
        3117829644UL,
        3877872838UL,
        3297977849UL,
        336255855UL,
        3794593369UL,
        2534532716UL,
        3726226824UL,
        2067902083UL,
        1289138711UL,
        615241845UL,
        3711156810UL,
        4069284324UL,
        3829237942UL,
        3615667378UL,
        750506440UL,
        3851304132UL,
        1159089146UL,
        2459260597UL,
        2955574874UL,
        1775846339UL,
        1872505027UL,
        3021810567UL,
        2498812392UL,
        2388439890UL,
        3509540924UL,
        4132084900UL,
        1762358900UL,
        3005639020UL,
        961559514UL,
        5499771UL,
        2114442568UL,
        2725996306UL,
        2213448586UL,
        3041192141UL,
        2318358424UL,
        4199956637UL,
        508024672UL,
        2898231491UL,
        985807031UL,
        3712119117UL,
        487464412UL,
        1443950379UL,
        2897942828UL,
        2942321529UL
#endif
      };

      /// \brief Helper function for hashing
      inline HashType xorrer(HashType const &l, NucleonItem const &r) {
        return l^mask[r];
      }

    }

    /** \brief Compute the hash of a nucleon configuration
     *
     * The hash is computed as
     *
     *   \f[ \mathrm{mask}_{i_1} \oplus \mathrm{mask}_{i_2} \oplus \ldots \oplus \mathrm{mask}_{i_n} \f]
     *
     * where \f$\oplus\f$ represents logical exclusive OR (XOR), \f$i_1,\ldots,
     * i_n\f$ represent the indices of the nucleons in the
     * ClusteringModelIntercomparison::consideredPartners
     * array, and \f$\mathrm{mask}_i\f$ is a static look-up table of 500
     * \f$n\f$-bit integers such that their binary representations have exactly
     * \f$n/2\f$ true bits and \f$n/2\f$ false bits, at random positions. The
     * value of \f$n\f$ is 32 if unsigned longs are less than 64-bit wide, and
     * 64 otherwise.
     *
     * Folding the mask values using XOR has two advantages: first, XOR is a
     * commutative operation, so the result is independent of the order in
     * which the nucleons appear in the configuration (which is what we want).
     * Second, it's very fast. Profiling shows that the time spent hashing
     * configurations is negligible compared to the time spent evaluating
     * phase-space proximity.
     */
    inline HashType hashConfig(NucleonItem *config, G4int n) {
// assert(n<maskTableSize);
      return std::accumulate(config, config+n, ((HashType)0), xorrer);
    }

  }
}

#endif // INCL_CACHING_CLUSTERING_MODEL_INTERCOMPARISON_HashMask

#endif // G4INCLHASHING_HH_