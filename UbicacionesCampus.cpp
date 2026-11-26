// Catalogo obtenido de https://maps.upsa.edu.bo/ (23-11-2026).
#include "UbicacionesCampus.h"
#include "MapaVisual.h"
#include <ostream>
#include <iomanip>
namespace {
const UbicacionCampus lugares[] = {
    {1,"Pascana","Bloque Central","1ra. Planta",-6036690.745850077,2475336.723987148,true,false},
    {2,"Informaciones","Bloque Central","1ra. Planta",-7680392.602094507,2064411.2599260407,true,false},
    {3,"Admisiones y Registro","Bloque Central","1ra. Planta",-8548812.417563505,1182051.6375932507,true,false},
    {4,"Dirección Académica","Bloque Central","1ra. Planta",-10967796.314583367,-205462.73203055374,true,false},
    {5,"Secretaría General","Bloque Central","1ra. Planta",-11574400.571054526,185894.85278954916,true,false},
    {6,"Programación Académica","Bloque Central","1ra. Planta",-9226255.062133912,127191.21506653354,true,false},
    {7,"Departamento de Comunicación e Imagen","Bloque Central","1ra. Planta",-10224216.903425172,-577252.4376096502,true,false},
    {8,"Vicerrectorado","Bloque Central","1ra. Planta",-11280882.38243945,29351.81886150688,true,false},
    {9,"Rectorado","Bloque Central","1ra. Planta",-11985326.035115633,420709.4036816098,true,false},
    {10,"Salón Auditorio","Bloque Central","1ra. Planta",-12842000.830198789,1365776.8729128037,true,false},
    {11,"Directorio","Bloque Central","1ra. Planta",-12220140.586007696,1477374.8826958863,true,false},
    {12,"Cabaña Jatata","","",-8313997.866671446,4440103.531220608,true,false},
    {13,"Cabañas Modulares","","",-4185175.3468193654,5897910.534675489,true,false},
    {14,"Informaciones a Estudiantes Nuevos","Bloque A","1ra. Planta",-7015084.707900332,1966571.863721015,true,false},
    {15,"Agencia de Banco","Bloque A","1ra. Planta",-5821444.074199021,1966571.863721015,true,false},
    {16,"Extensión Cultural","Bloque A","1ra. Planta",-6592024.493462993,1504921.6450698338,true,false},
    {17,"Dirección de Admisiones","Bloque A","1ra. Planta",-10701279.13407407,47114.641614953056,true,false},
    {18,"A-108 Aula","Bloque A","1ra. Planta",-3236421.0320395213,2755693.073192481,true,true},
    {19,"A-110 Aula","Bloque A","1ra. Planta",-3236421.0320395213,2755693.073192481,true,true},
    {20,"A-112 Aula","Bloque A","1ra. Planta",-3236421.0320395213,2755693.073192481,true,true},
    {21,"A-114 Aula","Bloque A","1ra. Planta",-3236421.0320395213,2755693.073192481,true,true},
    {22,"A-116 Aula","Bloque A","1ra. Planta",-3236421.0320395213,2755693.073192481,true,true},
    {23,"Aula Magna","Bloque A","1ra. Planta",-342730.2020767485,612413.5221341066,true,false},
    {24,"Aula Magna - Sala VIP","Bloque A","1ra. Planta",248910.38203363493,827660.1937851626,true,false},
    {25,"Fotocopiadora","Bloque B","1ra. Planta",-8392269.383635465,2815969.5542171784,true,false},
    {26,"B-101 Sala de Estudio de Matemática","Bloque B","1ra. Planta",-10711350.902103476,5074486.76325159,true,true},
    {27,"Enfermería","Bloque B","1ra. Planta",-9284958.699856926,3297187.652109363,true,false},
    {28,"Sala de Estudio","Bloque B","1ra. Planta",-9950266.5940511,3668977.3576884605,true,false},
    {29,"Ventanilla Única","Bloque B","1ra. Planta",-10583871.858628038,3549765.025754869,true,false},
    {30,"B-107 Taller de Moda","Bloque B","1ra. Planta",-10711350.902103476,5074486.76325159,true,true},
    {31,"TI - Departamento de Tecnología de las Informaciones","Bloque B","1ra. Planta",-11554832.691813523,5077864.663040828,true,false},
    {32,"Mantenimiento y Seguridad","Bloque B","1ra. Planta",-12044029.67283865,5801876.194958018,true,false},
    {33,"B-109 Aula de CENACE","Bloque B","1ra. Planta",-10711350.902103476,5074486.76325159,true,true},
    {34,"B-111 Aula de CENACE","Bloque B","1ra. Planta",-10711350.902103476,5074486.76325159,true,true},
    {35,"B-113 Aula de CENACE","Bloque B","1ra. Planta",-10711350.902103476,5074486.76325159,true,true},
    {36,"Secretaría de Atención al Docente","Bloque B","1ra. Planta",-8639218.68490376,2436200.965505136,true,false},
    {37,"Sala de Docentes","Bloque B","1ra. Planta",-9304526.579097934,2729719.1541202143,true,false},
    {38,"B-108 Sala de Auditores Externos","Bloque B","1ra. Planta",-10711350.902103476,5074486.76325159,true,false},
    {39,"B-110 Aula","Bloque B","1ra. Planta",-10711350.902103476,5074486.76325159,true,true},
    {40,"B-112 Aula","Bloque B","1ra. Planta",-10711350.902103476,5074486.76325159,true,true},
    {41,"B-114 Aula de CENACE","Bloque B","1ra. Planta",-10711350.902103476,5074486.76325159,true,true},
    {42,"CENACE - Unidad de Educación Continua","Bloque B","1ra. Planta",-11523536.430753596,3910954.420524694,true,false},
    {43,"B-118 Aula de CENACE","Bloque B","1ra. Planta",-10711350.902103476,5074486.76325159,true,true},
    {44,"B-120 Aula de CENACE","Bloque B","1ra. Planta",-10711350.902103476,5074486.76325159,true,true},
    {45,"B-122 Aula de CENACE","Bloque B","1ra. Planta",-10711350.902103476,5074486.76325159,true,true},
    {46,"Centro de Convenciones","","",5336558.984694965,1620159.3030458707,true,false},
    {47,"Centro de Convenciones - Sala VIP","","",6686742.652324317,710252.9183391333,true,false},
    {48,"Plaza de Banderas","","",5884459.603443107,-786689.8435977586,true,false},
    {49,"Coliseo Polideportivo","","",9054456.040485937,2980126.9102957277,true,false},
    {50,"Coordinación de Deportes","","",10040672.861391356,3129055.622073262,true,false},
    {51,"Cancha de Fútbol","","",7023003.113389423,4940405.278645178,true,false},
    {52,"Archivo Central","Bloque C","1ra. Planta",11758429.889712663,1594297.9284333028,true,false},
    {53,"C-103 Sala de Ensayos","Bloque C","1ra. Planta",11308551.190083962,2770711.4412758723,true,true},
    {54,"C-105 Laboratorio de Procesos Industriales (Planta de Vapor)","Bloque C","1ra. Planta",11308551.190083962,2770711.4412758723,true,true},
    {55,"Atención al Docente","Bloque D","1ra. Planta",14038853.395715516,1496740.789983754,true,false},
    {56,"D-103 Laboratorio de Hormigón","Bloque D","1ra. Planta",13206635.476461457,3915432.3768746722,true,true},
    {57,"D-105 Laboratorio de Materiales de Construcción","Bloque D","1ra. Planta",13206635.476461457,3915432.3768746722,true,true},
    {58,"D-107 Laboratorio de Mecánica de Suelos","Bloque D","1ra. Planta",13206635.476461457,3915432.3768746722,true,true},
    {59,"D-100 Exposición Materiales de Construcción","Bloque D","1ra. Planta",13206635.476461457,3915432.3768746722,true,true},
    {60,"D-102 Laboratorio de Resistencia de Materiales","Bloque D","1ra. Planta",13206635.476461457,3915432.3768746722,true,true},
    {61,"D-104 Laboratorio de Hidráulica y Mecánica de Fluidos","Bloque D","1ra. Planta",13206635.476461457,3915432.3768746722,true,true},
    {62,"D-106 Laboratorio de Asfalto","Bloque D","1ra. Planta",13206635.476461457,3915432.3768746722,true,true},
    {63,"E-101 Laboratorio de Química Orgánica","Bloque E","1ra. Planta",14322004.59319875,5627621.810462621,true,true},
    {64,"E-105 Laboratorio de Secado","Bloque E","1ra. Planta",14322004.59319875,5627621.810462621,true,true},
    {65,"E-107 Laboratorio de Química General","Bloque E","1ra. Planta",14322004.59319875,5627621.810462621,true,true},
    {66,"E-109 Laboratorio de Investigaciones Químicas","Bloque E","1ra. Planta",14322004.59319875,5627621.810462621,true,true},
    {67,"E-111 Laboratorio de Electrónica / Laboratorio de Potencia y Energía","Bloque E","1ra. Planta",14322004.59319875,5627621.810462621,true,true},
    {68,"E-113 Laboratorio de Método y Manufactura Esbelta","Bloque E","1ra. Planta",14322004.59319875,5627621.810462621,true,true},
    {69,"E-115 Laboratorio de Robótica / Laboratorio de Instrumentación","Bloque E","1ra. Planta",14322004.59319875,5627621.810462621,true,true},
    {70,"E-117 Laboratorio de Máquinas y Herramientas / Laboratorio de Automatización Industrial (Neumática)","Bloque E","1ra. Planta",14322004.59319875,5627621.810462621,true,true},
    {71,"E-119 Taller de Soldadura","Bloque E","1ra. Planta",14322004.59319875,5627621.810462621,true,true},
    {72,"E-100 Laboratorio de Física","Bloque E","1ra. Planta",14322004.59319875,5627621.810462621,true,true},
    {73,"E-102 Laboratorio de Física 2","Bloque E","1ra. Planta",14322004.59319875,5627621.810462621,true,true},
    {74,"E-104 Laboratorio de Producción de Hidrocarburos","Bloque E","1ra. Planta",14322004.59319875,5627621.810462621,true,true},
    {75,"E-106 Laboratorio de Presión Volumen Temperatura - PVT","Bloque E","1ra. Planta",14322004.59319875,5627621.810462621,true,true},
    {76,"E-108 Sala de Telecomunicaciones","Bloque E","1ra. Planta",14322004.59319875,5627621.810462621,true,true},
    {77,"E-110 Laboratorio de Cableado Estructurado y Telecomunicaciones","Bloque E","1ra. Planta",14322004.59319875,5627621.810462621,true,true},
    {78,"E-112 Sala de Computación","Bloque E","1ra. Planta",14322004.59319875,5627621.810462621,true,true},
    {79,"E-114 Laboratorio de Modelación Industrial - Fab Lab","Bloque E","1ra. Planta",14322004.59319875,5627621.810462621,true,true},
    {80,"E-116 Laboratorio de Ingeniería Civil (Servicio Externo)","Bloque E","1ra. Planta",14322004.59319875,5627621.810462621,true,true},
    {81,"Centro de Cómputo","Bloque Central","2da. Planta",-8196121.669252034,2200902.1849044617,true,false},
    {82,"Departamento de Personal","Bloque Central","2da. Planta",-8685318.650277162,2181334.3056634553,true,false},
    {83,"Contabilidad","Bloque Central","2da. Planta",-9057108.355856258,2063927.030217426,true,false},
    {84,"Gerencia General","Bloque Central","2da. Planta",-8704886.529518168,1516026.4114692826,true,false},
    {85,"Créditos y Recuperaciones","Bloque Central","2da. Planta",-9154947.752061285,1007261.5512031484,true,false},
    {86,"Jefatura de Retención","Bloque Central","2da. Planta",-9957230.800942495,400657.2947319895,true,false},
    {87,"Dirección de Mejoramiento Institucional","Bloque Central","2da. Planta",-10602970.815895664,557200.3286600318,true,false},
    {88,"Trámites y Títulos","Bloque Central","2da. Planta",-10505049.606981415,-220686.28457863815,true,false},
    {89,"Facultad de Ciencias Empresariales","Bloque Central","2da. Planta",-11586334.787238898,1918861.8993173046,true,false},
    {90,"Facultad de Ciencias Jurídicas y Sociales","Bloque Central","2da. Planta",-11347870.76236587,1808806.4852208155,true,false},
    {91,"Facultad de Humanidades, Comunicación y Artes","Bloque Central","2da. Planta",-11150949.47412653,1708507.1974764988,true,false},
    {92,"DABE - Departamento de Asesoría y Bienestar Estudiantil","","2da. Planta",-1777775.4654931314,5816004.4612714425,true,false},
    {93,"Internacionalización","Bloque A","2da. Planta",-6978099.225982193,3026893.061339219,true,false},
    {94,"Alumni","Bloque A","2da. Planta",-6547605.882680077,2870350.027411178,true,false},
    {95,"A-209 Aula","Bloque A","2da. Planta",-3236421.0320395213,2755693.073192481,true,true},
    {96,"A-211 Aula","Bloque A","2da. Planta",-3236421.0320395213,2755693.073192481,true,true},
    {97,"A-213 Aula","Bloque A","2da. Planta",-3236421.0320395213,2755693.073192481,true,true},
    {98,"CVI - Centro de Visualización de Imagen","Bloque A","2da. Planta",-6943777.397827706,2259605.8226274773,true,false},
    {99,"Data Center","Bloque A","2da. Planta",-6611123.45073062,1985655.5132534057,true,false},
    {100,"Asuntos Estudiantiles","Bloque A","2da. Planta",-6337091.328647324,1462151.3301478047,true,false},
    {101,"A-204 Aula","Bloque A","2da. Planta",-3236421.0320395213,2755693.073192481,true,true},
    {102,"A-206 Aula","Bloque A","2da. Planta",-3236421.0320395213,2755693.073192481,true,true},
    {103,"A-208 Aula","Bloque A","2da. Planta",-3236421.0320395213,2755693.073192481,true,true},
    {104,"A-210 Aula","Bloque A","2da. Planta",-3236421.0320395213,2755693.073192481,true,true},
    {105,"A-212 Aula","Bloque A","2da. Planta",-3236421.0320395213,2755693.073192481,true,true},
    {106,"A-214 Aula","Bloque A","2da. Planta",-3236421.0320395213,2755693.073192481,true,true},
    {107,"A-216 Aula","Bloque A","2da. Planta",-3236421.0320395213,2755693.073192481,true,true},
    {108,"A-218 Aula","Bloque A","2da. Planta",-3236421.0320395213,2755693.073192481,true,true},
    {109,"A-220 Aula","Bloque A","2da. Planta",-3236421.0320395213,2755693.073192481,true,true},
    {110,"IncubaUPSA - Incubadora de Empresas","Bloque B","2da. Planta",-6748176.644900381,2941283.589659822,true,false},
    {111,"B-205 Aula","Bloque B","2da. Planta",-10711350.902103476,5074486.76325159,true,true},
    {112,"B-209 Sala de Audiencias / Defensas de Tesis","Bloque B","2da. Planta",-10711350.902103476,5074486.76325159,true,true},
    {113,"B-211 Aula","Bloque B","2da. Planta",-10711350.902103476,5074486.76325159,true,true},
    {114,"B-213 Taller de Moda","Bloque B","2da. Planta",-10711350.902103476,5074486.76325159,true,true},
    {115,"B-215 Aula","Bloque B","2da. Planta",-10711350.902103476,5074486.76325159,true,true},
    {116,"DIP - Dirección de Postgrado","Bloque B","2da. Planta",-13503408.398919405,4278637.619212157,true,false},
    {117,"B-219 Aula de Postgrado","Bloque B","2da. Planta",-10711350.902103476,5074486.76325159,true,true},
    {118,"B-202 Aula","Bloque B","2da. Planta",-10711350.902103476,5074486.76325159,true,true},
    {119,"B-204 Aula","Bloque B","2da. Planta",-10711350.902103476,5074486.76325159,true,true},
    {120,"B-206 Aula","Bloque B","2da. Planta",-10711350.902103476,5074486.76325159,true,true},
    {121,"B-208 Aula","Bloque B","2da. Planta",-10711350.902103476,5074486.76325159,true,true},
    {122,"B-210 Aula","Bloque B","2da. Planta",-10711350.902103476,5074486.76325159,true,true},
    {123,"B-214 Aula de Postgrado","Bloque B","2da. Planta",-10711350.902103476,5074486.76325159,true,true},
    {124,"B-218 Aula de Postgrado","Bloque B","2da. Planta",-10711350.902103476,5074486.76325159,true,true},
    {125,"B-220 Aula de Postgrado","Bloque B","2da. Planta",-10711350.902103476,5074486.76325159,true,true},
    {126,"B-222 Aula de Postgrado","Bloque B","2da. Planta",-10711350.902103476,5074486.76325159,true,true},
    {127,"C-201 Aula","Bloque C","2da. Planta",11308551.190083962,2770711.4412758723,true,true},
    {128,"C-203 Taller de Maquetería","Bloque C","2da. Planta",11308551.190083962,2770711.4412758723,true,true},
    {129,"C-205 Taller de Instalaciones Eléctricas","Bloque C","2da. Planta",11308551.190083962,2770711.4412758723,true,true},
    {130,"D-201 Sala de Computación","Bloque D","2da. Planta",13206635.476461457,3915432.3768746722,true,true},
    {131,"D-203 Laboratorio de Redes","Bloque D","2da. Planta",13206635.476461457,3915432.3768746722,true,true},
    {132,"Sala de Reuniones","Bloque D","2da. Planta",13054595.186479531,1946519.7547713947,true,false},
    {133,"Facultad de Ingeniería","Bloque D","2da. Planta",12512558.814917114,2749085.061408081,true,false},
    {134,"A-305 Aula","Bloque A","3ra. Planta",-3236421.0320395213,2755693.073192481,true,true},
    {135,"A-307 Aula","Bloque A","3ra. Planta",-3236421.0320395213,2755693.073192481,true,true},
    {136,"A-309 Aula","Bloque A","3ra. Planta",-3236421.0320395213,2755693.073192481,true,true},
    {137,"A-302 Aula","Bloque A","3ra. Planta",-3236421.0320395213,2755693.073192481,true,true},
    {138,"A-304 Aula","Bloque A","3ra. Planta",-3236421.0320395213,2755693.073192481,true,true},
    {139,"A-306 Aula","Bloque A","3ra. Planta",-3236421.0320395213,2755693.073192481,true,true},
    {140,"A-308 Aula","Bloque A","3ra. Planta",-3236421.0320395213,2755693.073192481,true,true},
    {141,"A-310 Aula","Bloque A","3ra. Planta",-3236421.0320395213,2755693.073192481,true,true},
    {142,"A-312 Aula","Bloque A","3ra. Planta",-3236421.0320395213,2755693.073192481,true,true},
    {143,"A-314 Aula","Bloque A","3ra. Planta",-3236421.0320395213,2755693.073192481,true,true},
    {144,"A-316 Aula","Bloque A","3ra. Planta",-3236421.0320395213,2755693.073192481,true,true},
    {145,"A-318 Aula","Bloque A","3ra. Planta",-3236421.0320395213,2755693.073192481,true,true},
    {146,"A-320 Aula","Bloque A","3ra. Planta",-3236421.0320395213,2755693.073192481,true,true},
    {147,"A-322 Aula","Bloque A","3ra. Planta",-3236421.0320395213,2755693.073192481,true,true},
    {148,"A-324 Aula","Bloque A","3ra. Planta",-3236421.0320395213,2755693.073192481,true,true},
    {149,"B-301 Aula","Bloque B","3ra. Planta",-10711350.902103476,5074486.76325159,true,true},
    {150,"B-303 Aula","Bloque B","3ra. Planta",-10711350.902103476,5074486.76325159,true,true},
    {151,"B-307 Taller de Diseño","Bloque B","3ra. Planta",-10711350.902103476,5074486.76325159,true,true},
    {152,"Facultad de Arquitectura, Diseño y Urbanismo","Bloque B","3ra. Planta",-11621299.83083604,4939492.884935168,true,false},
    {153,"CIAP - Centro de Investigación y Asesoramiento Psicológico","Bloque B","3ra. Planta",-10711350.902103476,5074486.76325159,true,true},
    {154,"B-317 Aula de Postgrado / Defensas de Tesis","Bloque B","3ra. Planta",-10711350.902103476,5074486.76325159,true,true},
    {155,"B-319 Aula de Postgrado / Defensas de Tesis","Bloque B","3ra. Planta",-10711350.902103476,5074486.76325159,true,true},
    {156,"B-302 Taller de Diseño","Bloque B","3ra. Planta",-10711350.902103476,5074486.76325159,true,true},
    {157,"B-304 Taller de Diseño","Bloque B","3ra. Planta",-10711350.902103476,5074486.76325159,true,true},
    {158,"B-306 Taller de Diseño","Bloque B","3ra. Planta",-10711350.902103476,5074486.76325159,true,true},
    {159,"B-308 Taller de Diseño","Bloque B","3ra. Planta",-10711350.902103476,5074486.76325159,true,true},
    {160,"B-310 Taller de Diseño","Bloque B","3ra. Planta",-10711350.902103476,5074486.76325159,true,true},
    {161,"B-312 Taller de Diseño","Bloque B","3ra. Planta",-10711350.902103476,5074486.76325159,true,true},
    {162,"Sala de Estudio - Arquitectura","Bloque B","3ra. Planta",-11793090.42579719,4429135.252050759,true,false},
    {163,"B-316 Aula de Postgrado","Bloque B","3ra. Planta",-10711350.902103476,5074486.76325159,true,true},
    {164,"B-318 Aula de CENACE","Bloque B","3ra. Planta",-10711350.902103476,5074486.76325159,true,true},
    {165,"B-320 Aula de Postgrado","Bloque B","3ra. Planta",-10711350.902103476,5074486.76325159,true,true},
    {166,"B-322 Aula de Postgrado / Taller de Diseño","Bloque B","3ra. Planta",-10711350.902103476,5074486.76325159,true,true},
    {167,"B-324 Aula de Postgrado / Defensas de Tesis","Bloque B","3ra. Planta",-10711350.902103476,5074486.76325159,true,true},
    {168,"D-301 Aula","Bloque D","3ra. Planta",13206635.476461457,3915432.3768746722,true,true},
    {169,"D-303 Aula","Bloque D","3ra. Planta",13206635.476461457,3915432.3768746722,true,true},
    {170,"D-305 Aula","Bloque D","3ra. Planta",13206635.476461457,3915432.3768746722,true,true},
    {171,"D-302 Sala de Computación","Bloque D","3ra. Planta",13206635.476461457,3915432.3768746722,true,true},
    {172,"D-304 Sala de Computación","Bloque D","3ra. Planta",13206635.476461457,3915432.3768746722,true,true},
    {173,"Biblioteca","Bloque A","4ta. Planta",179012.45860738494,2851470.7562591694,true,false},
    {174,"B-401 Aula de CENACE","Bloque B","4ta. Planta",-10711350.902103476,5074486.76325159,true,true},
    {175,"B-403 Aula de CENACE","Bloque B","4ta. Planta",-10711350.902103476,5074486.76325159,true,true},
    {176,"B-402 Taller de Diseño","Bloque B","4ta. Planta",-10711350.902103476,5074486.76325159,true,true},
    {177,"B-404 Aula","Bloque B","4ta. Planta",-10711350.902103476,5074486.76325159,true,true},
    {178,"B-406 Aula","Bloque B","4ta. Planta",-10711350.902103476,5074486.76325159,true,true},
    {179,"B-408 Aula","Bloque B","4ta. Planta",-10711350.902103476,5074486.76325159,true,true},
    {180,"Administración Laboratorios de Computación","Bloque D","4ta. Planta",12954020.13551527,2469090.882668134,true,false},
    {181,"D-401 Sala de Computación","Bloque D","4ta. Planta",13206635.476461457,3915432.3768746722,true,true},
    {182,"D-403 Sala de Computación","Bloque D","4ta. Planta",13206635.476461457,3915432.3768746722,true,true},
    {183,"D-402 Sala de Computación","Bloque D","4ta. Planta",13206635.476461457,3915432.3768746722,true,true},
    {184,"D-404 Sala de Computación","Bloque D","4ta. Planta",13206635.476461457,3915432.3768746722,true,true},
    {185,"Ingreso Peatonal","","",-10378736.563976273,-1958897.7108234884,true,false},
    {186,"Parqueo Administrativos","","",-15799039.1137347,4136496.672749607,true,false},
    {187,"Parqueo Docentes","","",-3862632.7767215744,-1684947.4014494177,true,false},
    {188,"Parqueo Edificio Central","","",-6939519.387001565,6662862.881562244,true,false},
    {189,"Parqueo Edificio Central","","",675091.8338146759,4808806.323477009,true,false},
    {190,"Parqueo Externo","","",-8676331.070008844,-7154169.649310343,true,false},
    {191,"Parqueo Polideportivo","","",13152388.066752838,-285844.03571755346,true,false},
    {192,"Parqueo Ingeniería","","",13132820.187511832,6983623.102315849,true,false},
    {193,"Parqueo Bicicletas","","",-9291969.42268004,-2457878.631469122,true,false},
    {194,"Parqueo Motos","","",-10652637.688611863,6181334.767944848,true,false},
    {195,"Parqueo Motos","","",-14996706.880114999,6386797.499975402,true,false},
    {196,"Agencia BNB","","",-17354358.07601581,829829.8112551626,true,false},
    {197,"Cajero Automático Banco Fassil","","",-11916754.379802238,-2403311.0483421423,true,false},
    {198,"Snack","","",-12481956.145005533,5242386.580101818,true,false},
    {199,"Patio de Comida","","",-1269561.3399096075,5213034.761240304,true,false},
    {200,"Snack / Librería","","",16006609.29711207,3564892.1201644186,true,false},
    {201,"Pórtico","","",-7413875.42158521,1191835.5772137549,true,false},
    {202,"Punto de Encuentro","","",0.0,0.0,false,false},
    {203,"Patio Central","","",-9742453.051264819,2238717.116607529,true,false},
    {204,"Baños","","",0.0,0.0,false,false},
    {205,"Escalera / Rampa","","",-4987458.395700574,3383438.052206328,true,false},
};
}
const UbicacionCampus* buscarUbicacionCampus(int id) {
    for (const auto& lugar : lugares) if (lugar.id == id) return &lugar;
    return nullptr;
}
std::string normalizarBloqueCampus(const std::string& bloque) {
    const auto inicio=bloque.find_first_not_of(" \t\r\n");
    if (inicio==std::string::npos) return {};
    std::string b=bloque.substr(inicio,bloque.find_last_not_of(" \t\r\n")-inicio+1);
    for (char& c:b) if (c>='a'&&c<='z') c=static_cast<char>(c-'a'+'A');
    if (b.starts_with("BLOQUE ")) {
        b.erase(0,7);
        const auto contenido=b.find_first_not_of(' ');
        b=contenido==std::string::npos?std::string{}:b.substr(contenido);
    }
    return b;
}
const UbicacionCampus* buscarAulaCampus(const std::string& bloque,const std::string& aula) {
    const std::string b=normalizarBloqueCampus(bloque);
    const auto inicio=aula.find_first_not_of(" \t\r\n");
    if (b.size()!=1 || inicio==std::string::npos) return nullptr;
    std::string a=aula.substr(inicio,aula.find_last_not_of(" \t\r\n")-inicio+1);
    for (char& c:a) if (c>='a'&&c<='z') c=static_cast<char>(c-'a'+'A');
    const std::string prefijo=b+"-";
    if (a.starts_with(prefijo)) a.erase(0,prefijo.size());
    if (a.size()!=3 || a.find_first_not_of("0123456789")!=std::string::npos) return nullptr;
    const std::string codigo=prefijo+a;
    for (const auto& p:lugares) {
        if (!p.docente || normalizarBloqueCampus(p.bloque)!=b) continue;
        const std::string nombre=p.nombre;
        if (nombre.starts_with(codigo) && (nombre.size()==codigo.size() || nombre[codigo.size()]==' '))
            return &p;
    }
    return nullptr;
}

const char* nombreReferenciaPlano(int numero) {
    static const char* const nombres[] = {
        "Parqueo Administrativo", "DIP - Direccion de Postgrado", "Salon Auditorio",
        "CIAP - Asesoramiento Psicologico", "Facultad de Arquitectura, Diseno y Urbanismo",
        "CENACE - Educacion Continua", "Facultades del Edificio Central", "Ventanilla Unica",
        "Patio Central", "Tramites y Titulos", "Ingreso Peatonal", "Parqueo Edificio Central",
        "Cabana Jatata", "Escalera Central", "Internacionalizacion", "Admisiones y Registro / Contabilidad",
        "Portico", "Alumni / Asuntos Estudiantiles / Admisiones", "Rampa", "Cabanas Modulares",
        "DABE - Bienestar Estudiantil", "Extension Cultural / IncubaUPSA", "Parqueo Docente",
        "Parqueo Externo", "Parqueo Edificio Central", "Biblioteca (P4)", "Aula Magna",
        "Parqueo CC UPSA", "Centro de Convenciones", "Plaza de Banderas", "Polideportivo",
        "Coordinacion de Deportes", "Parqueo Polideportivo", "Parqueo Ingenieria",
        "Facultad de Ingenieria (P2)", "Laboratorios de Ingenieria"
    };
    return numero >= 1 && numero <= 36 ? nombres[numero-1] : nullptr;
}
void listarReferenciasPlano(std::ostream& out) {
    for (int numero=1; numero<=36; ++numero)
        out << numero << ": " << nombreReferenciaPlano(numero) << '\n';
}
void listarUbicacionesCampus(std::ostream& out) {
    for (const auto& p : lugares) {
        out << p.id << ": " << p.nombre << " | " << p.bloque << " | " << p.planta;
        if (!p.tienePosicion) out << " [sin posicion]";
        out << '\n';
    }
}
void escribirUbicacionesCampusJSON(std::ostream& out) {
    const auto precision = out.precision();
    out << std::setprecision(15) << '[';
    bool primero = true;
    for (const auto& p : lugares) {
        if (!primero) out << ',';
        primero = false;
        out << "{\"id\":" << p.id << ",\"nombre\":"; escribirCadenaJSON(out,p.nombre);
        out << ",\"bloque\":"; escribirCadenaJSON(out,p.bloque);
        out << ",\"planta\":"; escribirCadenaJSON(out,p.planta);
        out << ",\"x\":" << p.x << ",\"y\":" << p.y << ",\"posicion\":" << (p.tienePosicion ? "true" : "false") << ",\"docente\":" << (p.docente ? "true" : "false") << '}';
    }
    out << ']';
    out.precision(precision);
}
