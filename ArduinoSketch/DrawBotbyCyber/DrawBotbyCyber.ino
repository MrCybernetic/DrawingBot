#include <Servo.h>

// setup servo
int servoPin = A0;
int PEN_DOWN = 0; // angle of servo when pen is down
int PEN_UP = 80;   // angle of servo when pen is up
Servo penServo;

float wheel_dia=55.48;//59.45
float wheel_base=110.095; //      distance between the 2 wheels//103
int steps_rev=128; //           number of steps per revolution (16x gearbox)
int delay_time=5; //           time between steps in ms//5//8


// Stepper sequence org->pink->blue->yel
int L_stepper_pins[] = {6, 7, 8, 9};
int R_stepper_pins[] = {2, 3, 4, 5};

int fwd_mask[][4] =  {{0, 0, 0, 1},
                      {0, 0, 1, 1},
                      {0, 0, 1, 0},
                      {0, 1, 1, 0},
                      {0, 1, 0, 0},
                      {1, 1, 0, 0},
                      {1, 0, 0, 0},
                      {1, 0, 0, 1}};

int rev_mask[][4] =  {{1, 0, 0, 0},
                      {1, 1, 0, 0},
                      {0, 1, 0, 0},
                      {0, 1, 1, 0},
                      {0, 0, 1, 0},
                      {0, 0, 1, 1},
                      {0, 0, 0, 1},
                      {1, 0, 0, 1}};


void setup() {
  for(int pin=0; pin<4; pin++){
    pinMode(L_stepper_pins[pin], OUTPUT);
    digitalWrite(L_stepper_pins[pin], LOW);
    pinMode(R_stepper_pins[pin], OUTPUT);
    digitalWrite(R_stepper_pins[pin], LOW);
  }
  penServo.attach(servoPin);
  Serial.begin(9600);
  Serial.println("setup");
  penup();
  delay(1000);
}


void loop(){ 

    for(int i=0; i<16; i++){
    right(90);
    
  }


/*left(90.98675);
forward(58.648697);
pendown();
left(133.36694);
forward(10.656777);
left(13.456606);
forward(2.965888);
left(1.1022149);
forward(0.7940405);
right(137.46747);
forward(1.6630704);
right(15.288612);
forward(3.878723);
right(8.085749);
forward(0.7256711);
left(114.97929);
forward(1.5500321);
left(13.116284);
forward(3.855075);
left(17.664602);
forward(2.4258814);
left(35.669746);
forward(2.6341033);
right(28.368505);
forward(0.8605223);
right(125.660805);
forward(1.162109);
right(5.8515525);
forward(0.5984148);
left(133.57828);
forward(1.6860001);
left(17.656523);
forward(2.8051574);
right(2.6558506);
forward(0.53851604);
right(141.49947);
forward(0.9396292);
right(11.171532);
forward(0.31144586);
left(133.29675);
forward(5.1946607);
left(7.3212657);
forward(10.64474);
left(20.127153);
forward(2.6970346);
left(21.339088);
forward(2.1892924);
right(136.83244);
forward(1.7554768);
right(22.882225);
forward(0.38470796);
left(131.24864);
forward(0.2247205);
left(13.588627);
forward(2.5303164);
left(14.741842);
forward(3.8426678);
left(0.28868476);
forward(0.8881451);
right(127.66404);
forward(0.46141294);
right(23.081188);
forward(1.5280036);
left(2.785788);
forward(0.3905119);
left(119.9314);
forward(2.9740543);
left(9.042289);
forward(5.0362687);
left(4.7151866);
forward(1.1473874);
right(64.69458);
forward(0.49648908);
left(13.993541);
forward(1.7724855);
left(29.236732);
forward(3.283533);
left(5.506573);
forward(1.125389);
left(11.353747);
forward(2.802517);
left(8.042923);
forward(1.121606);
left(5.503254);
forward(0.9408508);
left(4.2732873);
forward(0.17117256);
right(141.70981);
forward(0.3111277);
right(12.094816);
forward(0.20248495);
left(83.659676);
forward(0.91678756);
left(31.900301);
forward(1.0324713);
left(4.1961126);
forward(4.638028);
left(15.80227);
forward(6.95041);
left(21.420374);
forward(5.3595524);
left(34.0647);
forward(3.0835042);
left(34.060375);
forward(2.3104134);
left(22.49114);
forward(2.3595123);
left(5.4449863);
forward(0.65521073);
right(101.39153);
forward(1.1335785);
left(2.3608205);
forward(5.0668516);
left(16.341131);
forward(3.951014);
left(25.729752);
forward(3.459047);
left(20.083246);
forward(2.3233166);
left(11.277483);
forward(1.9678655);
left(0.42397544);
forward(0.81049466);
right(113.43113);
forward(0.46324888);
left(5.0275517);
forward(1.9188812);
left(28.054693);
forward(4.0801125);
left(19.546095);
forward(9.341546);
left(12.782582);
forward(11.664143);
left(8.977907);
forward(14.122731);
left(24.856718);
forward(6.592942);
left(23.415396);
forward(6.45);
left(23.415394);
forward(6.5929427);
left(24.887012);
forward(14.116077);
left(8.906321);
forward(11.669556);
left(12.823877);
forward(9.341546);
left(19.546095);
forward(4.0801125);
left(28.318598);
forward(1.9235398);
left(4.763647);
forward(0.46324888);
right(113.54315);
forward(0.820367);
left(0.5360008);
forward(1.9678655);
left(11.365942);
forward(2.3139791);
left(24.333931);
forward(4.5821404);
left(30.473093);
forward(6.085235);
left(11.908373);
forward(1.7713842);
right(2.792304);
forward(1.1344162);
right(100.88814);
forward(0.65521073);
left(5.400538);
forward(2.3496785);
left(22.484293);
forward(2.3201942);
left(34.245735);
forward(3.0765736);
left(33.82534);
forward(5.361278);
left(19.519552);
forward(5.5566897);
left(16.802935);
forward(6.6277595);
left(33.747757);
forward(1.2229892);
right(7.955845);
forward(0.22803552);
right(48.786537);
forward(1.2020397);
left(7.404676);
forward(4.559923);
left(10.050937);
forward(0.8450441);
left(10.608513);
forward(2.0151672);
left(22.330101);
forward(2.282126);
left(17.832394);
forward(0.50596786);
right(65.059586);
forward(1.1473874);
left(4.7151866);
forward(5.0362687);
left(9.042289);
forward(2.9740543);
left(119.9314);
forward(0.3905119);
left(3.0863163);
forward(1.5220046);
right(23.381594);
forward(0.46141127);
right(127.66429);
forward(0.8881453);
left(0.2888077);
forward(3.8426678);
left(14.741842);
forward(2.5303164);
left(15.93328);
forward(0.2284724);
left(130.23624);
forward(0.38013172);
right(24.214481);
forward(1.7554768);
right(136.57288);
forward(2.1879902);
left(21.07952);
forward(2.6970346);
left(20.127153);
forward(10.64474);
left(7.3212657);
forward(5.1946607);
left(135.13297);
forward(0.3106421);
right(13.590006);
forward(0.9425514);
right(141.91185);
forward(0.53488266);
right(1.6612043);
forward(2.8051574);
left(17.656523);
forward(1.6860001);
left(133.57828);
forward(0.5984148);
right(5.8515525);
forward(1.162109);
right(125.660805);
forward(0.8605223);
right(20.63363);
forward(3.6113436);
left(44.9975);
forward(6.3057513);
left(20.285252);
forward(0.44283128);
left(107.63768);
forward(0.72367036);
right(7.311157);
forward(3.878723);
right(14.950519);
forward(1.661115);
right(137.1916);
forward(0.79924995);
left(0.3244886);
forward(2.9605727);
left(15.140616);
forward(11.222737);
left(60.07498);
forward(0.60728914);
left(162.75851);
forward(0.0);
penup();
right(121.26667);
forward(17.841248);
pendown();
left(114.83796);
forward(3.5724645);
left(2.1621556);
forward(6.3175073);
left(8.526372);
forward(6.32748);
left(0.6891951);
forward(7.186794);
right(18.859682);
forward(5.5322514);
right(21.627016);
forward(3.4409297);
right(21.550766);
forward(4.490713);
right(21.841343);
forward(5.6246586);
right(11.951608);
forward(5.200614);
right(14.170873);
forward(13.130519);
right(20.381031);
forward(2.552802);
right(28.464935);
forward(3.318433);
right(11.3647375);
forward(8.923554);
left(0.9052732);
forward(0.5192303);
left(151.00899);
forward(0.60638285);
right(3.820869);
forward(3.150397);
right(1.905539);
forward(1.1321659);
right(10.122302);
forward(0.38948676);
right(13.276463);
forward(0.9626007);
right(10.939326);
forward(3.2380397);
right(13.388249);
forward(0.38078853);
right(23.509926);
forward(1.8400271);
right(23.53351);
forward(1.978914);
right(16.031921);
forward(1.0294172);
right(15.223753);
forward(3.5480978);
right(25.943352);
forward(5.3957853);
right(19.740366);
forward(2.565307);
right(31.100636);
forward(2.0819702);
right(7.5137815);
forward(0.27658632);
left(146.5922);
forward(1.0381714);
right(5.9999795);
forward(0.48010418);
right(81.18543);
forward(0.17262676);
right(10.799376);
forward(3.6203454);
right(54.38419);
forward(0.56035703);
right(42.564827);
forward(1.039471);
left(145.60274);
forward(0.28319612);
right(5.7930655);
forward(2.074536);
right(31.209824);
forward(2.4946744);
right(21.606018);
forward(6.381927);
right(30.91715);
forward(3.159051);
right(5.567519);
forward(0.5448852);
right(19.019316);
forward(1.9119103);
right(23.441462);
forward(1.8600267);
right(23.296947);
forward(0.35846952);
left(0.46838704);
forward(0.8876933);
right(23.442345);
forward(3.3663037);
right(23.37423);
forward(4.3925624);
right(7.241069);
forward(0.90471);
left(150.38895);
forward(0.3228007);
left(0.1733092);
forward(11.163302);
right(30.148918);
forward(3.8262377);
right(28.825043);
forward(13.127925);
right(12.111537);
forward(2.373035);
right(7.6022186);
forward(6.341356);
right(18.252956);
forward(4.973934);
right(22.427984);
forward(3.1608367);
right(14.60865);
forward(3.7992234);
right(23.388826);
forward(3.6442838);
right(9.848953);
forward(3.725922);
left(3.2309964);
forward(0.0);
penup();
right(135.74728);
forward(3.2529683);
pendown();
right(31.307714);
forward(4.3300447);
left(31.649633);
forward(5.996418);
left(36.779823);
forward(8.668036);
left(13.389192);
forward(7.104541);
left(21.68533);
forward(6.6232476);
left(47.567158);
forward(6.137272);
left(16.22185);
forward(9.630083);
left(0.4014506);
forward(4.480279);
right(2.01813);
forward(8.312407);
left(5.5606093);
forward(4.662413);
left(14.06701);
forward(3.8959465);
left(27.232525);
forward(1.6829736);
left(16.965714);
forward(0.7782681);
left(12.563702);
forward(8.312846);
left(15.9311285);
forward(6.6909027);
left(16.213215);
forward(7.221282);
left(30.307625);
forward(2.6328688);
left(21.012789);
forward(4.2246184);
left(20.639942);
forward(5.830694);
left(6.6103935);
forward(3.7085037);
right(4.988606);
forward(7.7706437);
right(5.8546467);
forward(6.05413);
left(3.0595832);
forward(1.6710776);
left(5.457512);
forward(1.0117809);
left(176.6002);
forward(0.0);
penup();
right(7.9988084);
forward(10.492079);
pendown();
right(1.3902986);
forward(1.2872449);
left(10.809315);
forward(1.2103719);
right(1.0339655);
forward(4.450101);
right(0.8043817);
forward(1.3700368);
left(2.8040876);
forward(2.161874);
right(41.582344);
forward(2.1677864);
right(50.803604);
forward(1.6399994);
right(61.189156);
forward(0.22825521);
right(21.216219);
forward(1.0592914);
right(0.15083788);
forward(2.0069134);
right(7.4437857);
forward(1.1500001);
left(4.7637563);
forward(0.2408317);
left(12.761839);
forward(0.597746);
right(14.2506695);
forward(3.6760032);
right(2.2040746);
forward(1.0701869);
right(56.85515);
forward(0.30232432);
left(9.615157);
forward(0.34655446);
left(93.55509);
forward(0.33970574);
left(8.398346);
forward(0.30232432);
right(56.85515);
forward(1.0701869);
right(2.1951954);
forward(3.6859872);
right(14.2595625);
forward(0.59774554);
left(12.555745);
forward(0.23086798);
left(4.969864);
forward(1.1500001);
right(7.406957);
forward(2.01683);
right(0.1876526);
forward(1.0592914);
right(22.474026);
forward(0.21954575);
right(59.581985);
forward(1.6400299);
right(51.31941);
forward(2.1755457);
right(41.4159);
forward(2.161874);
left(2.807162);
forward(1.3600368);
left(2.142582);
forward(3.3533564);
right(2.563796);
forward(0.0);
penup();
right(177.63979);
forward(10.198651);
pendown();
left(120.751015);
forward(0.82377374);
right(61.600536);
forward(2.2641757);
right(1.7671064);
forward(3.0563405);
left(2.2940829);
forward(0.9170585);
right(129.27902);
forward(2.2230825);
right(17.504824);
forward(2.621012);
right(42.384796);
forward(1.7560166);
right(45.65896);
forward(1.6732306);
right(15.340122);
forward(0.98994994);
penup();
left(8.108404);
forward(26.460001);
pendown();
right(49.206554);
forward(1.8222244);
right(45.44728);
forward(2.6989799);
right(18.083143);
forward(2.2230825);
right(129.27902);
forward(0.9170585);
left(2.4557397);
forward(3.0613916);
right(2.1516461);
forward(2.2594228);
right(71.77852);
forward(1.0893123);
right(49.363365);
forward(2.1927614);
penup();
right(158.9838);
forward(14.164028);
pendown();
left(147.65372);
forward(5.745694);
right(16.508402);
forward(4.32695);
right(39.655388);
forward(1.6668847);
right(56.305004);
forward(3.51602);
right(43.769135);
forward(4.99938);
right(17.77349);
forward(2.7987318);
right(36.19242);
forward(1.3718607);
left(44.409367);
forward(0.16999999);
left(44.409367);
forward(1.3718607);
right(36.19242);
forward(2.7987318);
right(17.77349);
forward(4.99938);
right(43.769135);
forward(3.51602);
right(56.305004);
forward(1.6668847);
right(46.45643);
forward(8.215168);
right(19.560186);
forward(3.8210208);
right(4.3527164);
forward(0.0);
penup();
right(147.83862);
forward(19.857014);
pendown();
left(81.379524);
forward(5.9338436);
left(11.417088);
forward(1.3787669);
right(55.45533);
forward(2.2846448);
right(57.31404);
forward(1.2788274);
right(21.318794);
forward(2.2687438);
right(38.485558);
forward(1.3944534);
right(46.68107);
forward(5.6057563);
right(23.657478);
forward(3.13589);
right(138.88815);
forward(0.7907596);
penup();
left(76.08651);
forward(32.592834);
pendown();
right(80.74459);
forward(7.23951);
right(50.88374);
forward(1.3944534);
right(38.525463);
forward(2.2786179);
right(21.3742);
forward(1.2690544);
right(57.21872);
forward(2.2846448);
right(55.45533);
forward(1.3787669);
left(11.339708);
forward(5.9155135);
left(12.867358);
forward(0.80411524);
right(133.93788);
forward(1.4705445);
left(54.68882);
forward(0.0);
penup();
right(171.35335);
forward(27.138445);
pendown();
left(165.53154);
forward(2.5632205);
right(11.443968);
forward(1.5498384);
right(47.533127);
forward(0.18788297);
left(112.08951);
forward(0.35383648);
right(24.910545);
forward(0.5515427);
right(24.766003);
forward(2.1618743);
left(0.6274271);
forward(2.2810745);
right(29.848957);
forward(0.61057335);
right(21.52269);
forward(0.35000056);
left(104.97301);
forward(0.3560904);
right(20.235363);
forward(0.61057335);
right(29.841215);
forward(2.271079);
left(0.60870236);
forward(2.171866);
right(24.755022);
forward(0.5515427);
right(24.910545);
forward(0.35383648);
left(112.08951);
forward(0.18788297);
right(47.533127);
forward(1.5498384);
right(11.359626);
forward(2.6239285);
left(0.43406746);
forward(1.8110763);
right(6.340218);
forward(0.25);
right(91.145676);
forward(0.50009996);
right(9.793411);
forward(2.4240472);
right(42.771107);
forward(2.568132);
right(41.91572);
forward(3.3662138);
left(15.829919);
forward(0.5080355);
left(4.2542105);
forward(2.9638658);
right(25.077858);
forward(2.441823);
right(16.41121);
forward(0.55009085);
left(54.542854);
forward(0.54120237);
right(16.892342);
forward(2.441823);
right(25.077858);
forward(2.9638658);
left(4.4502096);
forward(0.5178801);
left(15.650667);
forward(3.3562634);
right(41.93247);
forward(2.5681312);
right(44.01657);
forward(2.850701);
right(86.818596);
forward(0.3590259);
right(19.960157);
forward(1.7836202);
left(7.0851483);
forward(0.0);
penup();
right(53.331104);
forward(25.084152);
pendown();
right(6.062496);
forward(1.6498482);
left(31.56319);
forward(2.227667);
left(45.6426);
forward(2.9094667);
left(16.207127);
forward(0.48259768);
left(142.80083);
forward(0.72111046);
right(9.263498);
forward(4.3624763);
right(10.670873);
forward(0.8915718);
left(32.57653);
forward(0.1824827);
left(170.53766);
forward(0.0);
penup();
right(178.94666);
forward(9.791656);
pendown();
left(22.649317);
forward(0.89554423);
right(11.387632);
forward(4.360333);
right(8.342529);
forward(0.7217343);
left(142.00818);
forward(0.48259768);
left(16.267172);
forward(2.9189892);
left(45.80953);
forward(2.2323532);
left(34.623722);
forward(1.6995586);
left(142.09402);
forward(0.14317831);
penup();
right(48.49434);
forward(33.237656);
pendown();
left(135.01653);
forward(0.6332456);
left(1.4776225);
forward(1.4207745);
left(1.1270767);
forward(0.96254855);
left(0.7216914);
forward(0.26400763);
right(58.076912);
forward(0.6711927);
right(33.764423);
forward(1.0846194);
right(5.8548517);
forward(1.2020831);
left(12.240081);
forward(0.98488635);
right(0.42759714);
forward(0.35355127);
right(108.73117);
forward(0.17262729);
right(17.603638);
forward(0.45398283);
right(6.293213);
forward(1.8748065);
right(17.425505);
forward(2.8091984);
right(39.88654);
forward(0.49648908);
penup();
right(19.097418);
forward(71.260956);
pendown();
right(63.85813);
forward(3.5556288);
right(12.849621);
forward(0.6670832);
left(0.5756278);
forward(0.29832858);
right(99.75633);
forward(0.45099965);
right(19.275257);
forward(0.9752933);
right(0.03365917);
forward(1.0480957);
right(7.4938645);
forward(1.0754045);
right(33.55807);
forward(0.6711927);
right(58.07616);
forward(0.26400602);
left(0.72072834);
forward(0.9625501);
left(1.253169);
forward(1.5061536);
right(58.604816);
forward(0.92070603);
right(8.746126);
forward(0.0);
penup();
right(176.17046);
forward(69.02411);
pendown();
left(73.27904);
forward(5.8268685);
right(8.359345);
forward(0.5793973);
right(42.587654);
forward(0.63505876);
left(6.345942);
forward(1.2095045);
right(0.31164786);
forward(0.6381198);
right(95.75752);
forward(2.0214112);
right(15.741858);
forward(2.747744);
right(5.9325447);
forward(0.60207987);
right(50.887257);
forward(0.72138786);
right(15.793085);
forward(3.0376475);
right(28.083584);
forward(0.5);
left(38.41797);
forward(0.7402716);
right(39.11668);
forward(0.8200607);
left(0.6987106);
forward(0.0);
penup();
left(0.017213676);
forward(66.57001);
pendown();
right(38.558372);
forward(0.7543209);
left(38.54116);
forward(0.5099983);
right(26.281412);
forward(2.7101479);
right(15.215031);
forward(0.69426256);
right(35.05486);
forward(0.9459386);
right(22.36361);
forward(2.0649457);
left(18.697178);
forward(0.29427862);
right(20.736227);
forward(0.6315059);
right(20.732395);
forward(0.9518929);
right(5.1836624);
forward(0.7000012);
right(6.5818706);
forward(0.26172525);
right(84.63697);
forward(0.47010553);
left(5.6441813);
forward(1.6589468);
right(20.149944);
forward(0.8560377);
right(24.609854);
forward(5.824645);
right(25.702984);
forward(0.4924435);
right(110.782684);
forward(0.8292759);
left(33.690147);
forward(0.0);
penup();
right(14.413599);
forward(4.4190936);
pendown();
right(95.81117);
forward(0.20248452);
right(109.58027);
forward(0.07810368);
right(66.89458);
forward(0.20880635);
right(113.901764);
forward(0.092195176);
penup();
right(137.08095);
forward(77.89372);
pendown();
left(101.13816);
forward(1.6760069);
left(1.1185049);
forward(0.5166239);
left(10.88896);
forward(2.0933456);
left(5.966409);
forward(0.21095058);
left(3.162695);
forward(0.7045574);
right(3.6288621);
forward(0.6997126);
right(39.378212);
forward(1.7083911);
left(20.17269);
forward(2.2573662);
left(20.28437);
forward(1.6398168);
left(7.051733);
forward(0.20615584);
left(9.621171);
forward(1.0912374);
left(79.94466);
forward(0.512248);
left(0.709158);
forward(0.5044825);
right(85.11335);
forward(0.54451615);
right(56.199783);
forward(1.063014);
right(36.373787);
forward(1.9548936);
left(55.624027);
forward(0.3931928);
right(20.698702);
forward(1.079351);
right(10.768544);
forward(1.1727338);
right(45.20667);
forward(2.6392775);
right(38.55513);
forward(3.1845431);
right(56.386086);
forward(5.87909);
right(30.427467);
forward(8.137678);
right(17.341425);
forward(3.3517153);
right(125.755684);
forward(0.2915478);
left(67.833534);
forward(0.0);
penup();
right(0.37740892);
forward(80.46175);
pendown();
right(62.137737);
forward(3.900205);
right(14.98426);
forward(6.6066184);
right(28.191639);
forward(5.87909);
right(56.386055);
forward(3.1845396);
right(38.55513);
forward(2.639281);
right(44.762733);
forward(1.17686);
right(11.212506);
forward(1.079351);
right(20.698149);
forward(0.3931923);
left(55.427773);
forward(1.9474349);
right(36.396957);
forward(1.0825896);
right(66.6515);
forward(0.5742831);
right(77.347176);
forward(0.14866108);
right(1.7213442);
forward(0.4031137);
left(29.672062);
forward(0.48507476);
left(56.431473);
forward(0.70092815);
left(32.756283);
forward(5.438649);
left(28.527807);
forward(0.43174127);
right(52.428226);
forward(0.47633973);
left(15.236119);
forward(4.63406);
left(6.517892);
forward(0.9425492);
right(123.77275);
forward(0.9386161);
penup();
right(129.67384);
forward(18.101461);
pendown();
left(155.85387);
forward(3.6374297);
right(23.31101);
forward(4.1996317);
right(22.320322);
forward(9.918599);
right(10.601976);
forward(1.4878846);
right(10.475658);
forward(3.9815192);
right(20.573826);
forward(4.1893682);
right(24.675894);
forward(3.5373423);
right(30.249334);
forward(2.236605);
right(26.072607);
forward(2.6803362);
right(10.377611);
forward(0.67623883);
left(99.4961);
forward(0.4123103);
right(15.433604);
forward(3.618135);
right(29.738083);
forward(4.004511);
right(27.062574);
forward(6.303347);
right(27.980305);
forward(5.6484423);
right(9.685645);
forward(2.5793803);
left(11.189994);
forward(3.8277018);
left(36.200794);
forward(2.1489766);
left(19.464712);
forward(4.1217957);
right(12.344938);
forward(7.455521);
right(28.487652);
forward(4.866343);
right(24.374525);
forward(4.0810423);
right(29.42299);
forward(3.270612);
right(12.827504);
forward(0.48764706);
left(97.28967);
forward(0.67230856);
right(7.8045287);
forward(2.4426425);
right(31.37581);
forward(3.252813);
right(34.37563);
forward(3.8451655);
right(20.33751);
forward(3.0010831);
right(17.301743);
forward(4.0514936);
right(10.5082655);
forward(1.4780054);
right(12.107684);
forward(10.908656);
right(24.401909);
forward(3.5073636);
right(28.301304);
forward(4.8640003);
right(29.780924);
forward(3.6721244);
right(30.462212);
forward(1.2234795);
right(64.28634);
forward(1.2744024);
left(33.715054);
forward(1.5041614);
right(7.990877);
forward(0.4638965);
right(83.395096);
forward(0.2473861);
right(17.38089);
forward(1.5426285);
left(17.117737);
forward(3.696282);
left(46.077984);
forward(4.2210064);
left(36.17053);
forward(2.3831496);
right(34.44286);
forward(0.9664884);
right(33.313072);
forward(3.3153133);
left(53.82729);
forward(0.36345518);
left(73.02669);
forward(3.0423677);
left(24.88036);
forward(4.91);
left(19.7176);
forward(10.877798);
right(0.66469175);
forward(2.0524375);
right(24.679674);
forward(2.0398283);
right(49.403435);
forward(2.1111605);
right(73.57453);
forward(8.125725);
right(21.370705);
forward(1.778679);
right(4.0996294);
forward(0.8005627);
left(152.02962);
forward(0.56035745);
left(16.26795);
forward(2.238616);
left(27.738651);
forward(6.5357857);
left(1.9155469);
forward(1.0820813);
right(31.416655);
forward(3.6151485);
right(36.507187);
forward(2.748545);
right(31.107105);
forward(0.9626007);
left(13.760273);
forward(5.958565);
left(25.701145);
forward(2.1813073);
left(15.692835);
forward(0.7199993);
left(152.73051);
forward(1.0912831);
right(9.850375);
forward(4.1260405);
right(14.722909);
forward(4.095033);
right(19.940136);
forward(1.66337);
right(63.839836);
forward(2.6023068);
right(47.23969);
forward(1.401749);
right(16.546524);
forward(2.046289);
right(1.9361553);
forward(9.09379);
left(18.894573);
forward(7.0164146);
left(27.796703);
forward(2.5228562);
left(25.560003);
forward(0.4123112);
left(86.0688);
forward(0.61554915);
left(16.204937);
forward(3.0142481);
left(9.933321);
forward(0.5852363);
right(86.9284);
forward(0.628172);
left(12.614539);
forward(3.3407335);
left(33.805214);
forward(2.6352992);
left(26.54882);
forward(2.5158894);
left(30.265905);
forward(2.960153);
right(35.34784);
forward(0.8521147);
right(69.595604);
forward(1.4945235);
left(34.099888);
forward(1.2870512);
right(62.615593);
forward(1.265899);
right(34.191875);
forward(4.167601);
right(16.79737);
forward(1.2548306);
left(5.0290794);
forward(0.0);
penup();
right(166.31966);
forward(36.7012);
pendown();
left(148.29988);
forward(2.6184344);
right(142.007);
forward(4.9475846);
right(2.6634185);
forward(3.865049);
right(123.12899);
forward(1.2472368);
right(37.677094);
forward(4.0680833);
right(35.7364);
forward(2.2402005);
penup();
right(1.120369);
forward(29.210554);
pendown();
right(44.646935);
forward(4.1577873);
right(47.86228);
forward(0.60074985);
right(106.02871);
forward(8.740813);
right(130.33495);
forward(1.0358567);
right(22.501787);
forward(2.849649);
right(16.20782);
forward(1.6659538);
penup();
left(168.35373);
forward(16.58947);
right(160.41818);
forward(0.0);
*/

penup();
  done();      // releases stepper motor
  while(1);    // wait for reset
}


// ----- HELPER FUNCTIONS -----------
int step(float distance){
  int steps = round(distance * steps_rev / (wheel_dia * PI));
  return steps;  
}

void left_rotationNTimes(int rotationNumber){
  int steps = rotationNumber * steps_rev;
  for(int step=0; step<steps; step++){
    for(int mask=0; mask<8; mask++){
      for(int pin=0; pin<4; pin++){
        digitalWrite(L_stepper_pins[pin], fwd_mask[mask][pin]);
      }
      delay(delay_time);
    } 
  }
}

void right_rotationNTimes(int rotationNumber){
  int steps = rotationNumber * steps_rev;
  for(int step=0; step<steps; step++){
    for(int mask=0; mask<8; mask++){
      for(int pin=0; pin<4; pin++){
        digitalWrite(R_stepper_pins[pin], fwd_mask[mask][pin]);
      }
      delay(delay_time);
    } 
  }
}

void forward(float distance){
  int steps = step(distance);
  for(int step=0; step<steps; step++){
    for(int mask=0; mask<8; mask++){
      for(int pin=0; pin<4; pin++){
          digitalWrite(L_stepper_pins[pin], rev_mask[mask][pin]);
          digitalWrite(R_stepper_pins[pin], fwd_mask[mask][pin]);
      }
      delay(delay_time);
    } 
  }   
}

void backward(float distance){
  int steps = step(distance);
  for(int step=0; step<steps; step++){
    for(int mask=0; mask<8; mask++){
      for(int pin=0; pin<4; pin++){
        digitalWrite(L_stepper_pins[pin], fwd_mask[mask][pin]);
        digitalWrite(R_stepper_pins[pin], rev_mask[mask][pin]);
      }
      delay(delay_time);
    } 
  }   
}


void right(float degrees){
  float rotation = degrees / 360.0;
  float distance = wheel_base * PI * rotation;
  int steps = step(distance);
  for(int step=0; step<steps; step++){
    for(int mask=0; mask<8; mask++){
      for(int pin=0; pin<4; pin++){
        digitalWrite(L_stepper_pins[pin], rev_mask[mask][pin]);
        digitalWrite(R_stepper_pins[pin], rev_mask[mask][pin]);
      }
      delay(delay_time);
    } 
  }   
  delay(10);
}


void left(float degrees){
  float rotation = degrees / 360.0;
  float distance = wheel_base * PI * rotation;
  int steps = step(distance);
  for(int step=0; step<steps; step++){
    for(int mask=0; mask<8; mask++){
      for(int pin=0; pin<4; pin++){
        digitalWrite(L_stepper_pins[pin], fwd_mask[mask][pin]);
        digitalWrite(R_stepper_pins[pin], fwd_mask[mask][pin]);
      }
      delay(delay_time);
    } 
  }   
  delay(10);
}

void moveWheelsRL(float Rdist, float Ldist) {
  bool RDirection = Rdist>=0;
  bool LDirection = Ldist>=0;
  int stepsR = step(abs(Rdist));
  int stepsL = step(abs(Ldist));
  Serial.println("Rdist "+String(Rdist));
  Serial.println("Ldist "+String(Ldist));
  Serial.println("stepsR "+String(stepsR));
  Serial.println("stepsL "+String(stepsL));
  int stepsMax = max(stepsR,stepsL);
  int stepsMin = min(stepsR,stepsL);
  int ratio = round(float(stepsMax)/float(stepsMin));
  Serial.println("L dir "+String(LDirection));
  Serial.println("R dir "+String(RDirection));
  for(int step=0; step<stepsMax; step++){
    for(int mask=0; mask<8; mask++){
      for(int pin=0; pin<4; pin++){
        if (stepsMax==stepsR) {
          if (RDirection) {
            digitalWrite(R_stepper_pins[pin], fwd_mask[mask][pin]);
          } else {
            digitalWrite(R_stepper_pins[pin], rev_mask[mask][pin]);
          }
          if (step%ratio==0 && step<stepsMin) {
            if (LDirection) {
              digitalWrite(L_stepper_pins[pin], rev_mask[mask][pin]);
            } else {
              digitalWrite(L_stepper_pins[pin], fwd_mask[mask][pin]);
            }
          }
        }
        if (stepsMax==stepsL) {
          if (LDirection) {
            digitalWrite(L_stepper_pins[pin], rev_mask[mask][pin]);
          } else {
            digitalWrite(L_stepper_pins[pin], fwd_mask[mask][pin]);
          }
          if (step%ratio==0 && step<stepsMin) {
            if (RDirection) {
              digitalWrite(R_stepper_pins[pin], fwd_mask[mask][pin]);
            } else {
              digitalWrite(R_stepper_pins[pin], rev_mask[mask][pin]);
            }
          }
        }
      }
      delay(delay_time);
    } 
  }   
  delay(10);
}


void done(){ // unlock stepper to save battery
  for(int mask=0; mask<8; mask++){
    for(int pin=0; pin<4; pin++){
      digitalWrite(R_stepper_pins[pin], LOW);
      digitalWrite(L_stepper_pins[pin], LOW);
    }
    delay(delay_time);
  }
}


void penup(){
  delay(250);
  Serial.println("PEN_UP()");
  penServo.write(PEN_UP);
  delay(250);
}


void pendown(){
  delay(250);  
  Serial.println("PEN_DOWN()");
  penServo.write(PEN_DOWN);
  delay(250);
}
