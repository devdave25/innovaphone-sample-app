/*---------------------------------------------------------------------------*/
/* timezone.h                                                                */
/* copyright (c) innovaphone 2017                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/

#if 1 // This helps to close the following, long list in some IDEs

// Version of tz database used to create that files: 2017b
// Latest version can be downloaded at https://www.iana.org/time-zones

// This list of the tz database IDs had been created using the zone1970.tab file of the tzdata2017b.zip
// (except the ones in section "others" and below).  Be aware that some IDs had been mapped to others
// (see  http://en.wikipedia.org/wiki/List_of_tz_database_time_zones), becuase of that, they are not
// listed here.
// Some additional informations and tools can be found here: https://www.iana.org/time-zones/repository/tz-link.html
//

#define TZ_AFRICA_ABIDJAN                   "Africa/Abidjan"
#define TZ_AFRICA_ACCRA                     "Africa/Accra"
#define TZ_AFRICA_ALGIERS                   "Africa/Algiers"
#define TZ_AFRICA_BISSAU                    "Africa/Bissau"
#define TZ_AFRICA_CAIRO                     "Africa/Cairo"
#define TZ_AFRICA_CASABLANCA                "Africa/Casablanca"
#define TZ_AFRICA_CEUTA                     "Africa/Ceuta"                      // Ceuta, Melilla
#define TZ_AFRICA_EL_AAIUN                  "Africa/El_Aaiun"	
#define TZ_AFRICA_JOHANNESBURG              "Africa/Johannesburg"
#define TZ_AFRICA_JUBA                      "Africa/Juba"
#define TZ_AFRICA_KHARTOUM                  "Africa/Khartoum"
#define TZ_AFRICA_LAGOS                     "Africa/Lagos"                      // West Africa Time
#define TZ_AFRICA_MAPUTO                    "Africa/Maputo"                     // Central Africa Time
#define TZ_AFRICA_MONROVIA                  "Africa/Monrovia"
#define TZ_AFRICA_NAIROBI                   "Africa/Nairobi"
#define TZ_AFRICA_NDJAMENA                  "Africa/Ndjamena"
#define TZ_AFRICA_TRIPOLI                   "Africa/Tripoli"
#define TZ_AFRICA_TUNIS                     "Africa/Tunis"
#define TZ_AFRICA_WINDHOEK                  "Africa/Windhoek"

#define TZ_AMERICA_ADAK                     "America/Adak"                      // Aleutian Islands
#define TZ_AMERICA_ANCHORAGE                "America/Anchorage"                 // Alaska (most areas)
#define TZ_AMERICA_ARAGUAINA                "America/Araguaina"                 // Tocantins
#define TZ_AMERICA_ARGENTINA_BUENOS_AIRES   "America/Argentina/Buenos_Aires"    // Buenos Aires (BA, CF)
#define TZ_AMERICA_ARGENTINA_CATAMARCA      "America/Argentina/Catamarca"       // Catamarca (CT); Chubut (CH)
#define TZ_AMERICA_ARGENTINA_CORDOBA        "America/Argentina/Cordoba"         // Argentina (most areas: CB, CC, CN, ER, FM, MN, SE, SF)
#define TZ_AMERICA_ARGENTINA_JUJUY          "America/Argentina/Jujuy"           // Jujuy (JY)
#define TZ_AMERICA_ARGENTINA_LA_RIOJA       "America/Argentina/La_Rioja"        // La Rioja (LR)
#define TZ_AMERICA_ARGENTINA_MENDOZA        "America/Argentina/Mendoza"         // Mendoza (MZ)
#define TZ_AMERICA_ARGENTINA_RIO_GALLEGOS   "America/Argentina/Rio_Gallegos"    // Santa Cruz (SC)
#define TZ_AMERICA_ARGENTINA_SALTA          "America/Argentina/Salta"           // Salta (SA, LP, NQ, RN)
#define TZ_AMERICA_ARGENTINA_SAN_JUAN       "America/Argentina/San_Juan"        // San Juan (SJ)
#define TZ_AMERICA_ARGENTINA_SAN_LUIS       "America/Argentina/San_Luis"        // San Luis (SL)
#define TZ_AMERICA_ARGENTINA_TUCUMAN        "America/Argentina/Tucuman"         // Tucumán (TM)
#define TZ_AMERICA_ARGENTINA_USHUAIA        "America/Argentina/Ushuaia"         // Tierra del Fuego (TF)
#define TZ_AMERICA_ASUNCION                 "America/Asuncion"
#define TZ_AMERICA_ATIKOKAN                 "America/Atikokan"                  // EST - ON (Atikokan); NU (Coral H)
#define TZ_AMERICA_BAHIA                    "America/Bahia"                     // Bahía
#define TZ_AMERICA_BAHIA_BANDERAS           "America/Bahia_Banderas"            // Central Time - Bahí­a de Banderas
#define TZ_AMERICA_BARBADOS                 "America/Barbados"
#define TZ_AMERICA_BELEM                    "America/Belem"                     // Pará (east); Amapá
#define TZ_AMERICA_BELIZE                   "America/Belize"
#define TZ_AMERICA_BLANC_SABLON             "America/Blanc-Sablon"              // AST - QC (Lower North Shore)
#define TZ_AMERICA_BOA_VISTA                "America/Boa_Vista"                 // Roraima
#define TZ_AMERICA_BOGOTA                   "America/Bogota"
#define TZ_AMERICA_BOISE                    "America/Boise"                     // Mountain - ID (south); OR (east)
#define TZ_AMERICA_CAMBRIDGE_BAY            "America/Cambridge_Bay"             // Mountain - NU (west)
#define TZ_AMERICA_CAMPO_GRANDE             "America/Campo_Grande"              // Mato Grosso do Sul
#define TZ_AMERICA_CANCUN                   "America/Cancun"                    // Eastern Standard Time - Quintana Roo
#define TZ_AMERICA_CARACAS                  "America/Caracas"
#define TZ_AMERICA_CAYENNE                  "America/Cayenne"
#define TZ_AMERICA_CHICAGO                  "America/Chicago"                   // Central (most areas)
#define TZ_AMERICA_CHIHUAHUA                "America/Chihuahua"                 // Mountain Time - Chihuahua (most areas)
#define TZ_AMERICA_COSTA_RICA               "America/Costa_Rica"
#define TZ_AMERICA_CRESTON                  "America/Creston"                   // MST - BC (Creston)
#define TZ_AMERICA_CUIABA                   "America/Cuiaba"                    // Mato Grosso
#define TZ_AMERICA_CURACAO                  "America/Curacao"
#define TZ_AMERICA_DANMARKSHAVN             "America/Danmarkshavn"              // National Park (east coast)
#define TZ_AMERICA_DAWSON                   "America/Dawson"                    // Pacific - Yukon (north)
#define TZ_AMERICA_DAWSON_CREEK             "America/Dawson_Creek"              // MST - BC (Dawson Cr, Ft St John)
#define TZ_AMERICA_DENVER                   "America/Denver"                    // Mountain (most areas)
#define TZ_AMERICA_DETROIT                  "America/Detroit"                   // Eastern - MI (most areas)
#define TZ_AMERICA_EDMONTON                 "America/Edmonton"                  // Mountain - AB; BC (E); SK (W)
#define TZ_AMERICA_EIRUNEPE                 "America/Eirunepe"                  // Amazonas (west)
#define TZ_AMERICA_EL_SALVADOR              "America/El_Salvador"
#define TZ_AMERICA_FORT_NELSON              "America/Fort_Nelson"               // MST - BC (Ft Nelson)
#define TZ_AMERICA_FORTALEZA                "America/Fortaleza"                 // Brazil (northeast: MA, PI, CE, RN, PB)
#define TZ_AMERICA_GLACE_BAY                "America/Glace_Bay"                 // Atlantic - NS (Cape Breton)
#define TZ_AMERICA_GODTHAB                  "America/Godthab"                   // Greenland (most areas)
#define TZ_AMERICA_GOOSE_BAY                "America/Goose_Bay"                 // Atlantic - Labrador (most areas)
#define TZ_AMERICA_GRAND_TURK               "America/Grand_Turk"
#define TZ_AMERICA_GUATEMALA                "America/Guatemala"
#define TZ_AMERICA_GUAYAQUIL                "America/Guayaquil"                 // Ecuador (mainland)
#define TZ_AMERICA_GUYANA                   "America/Guyana"
#define TZ_AMERICA_HALIFAX                  "America/Halifax"                   // Atlantic - NS (most areas); PE
#define TZ_AMERICA_HAVANA                   "America/Havana"
#define TZ_AMERICA_HERMOSILLO               "America/Hermosillo"                // Mountain Standard Time - Sonora
#define TZ_AMERICA_INDIANA_INDIANAPOLIS     "America/Indiana/Indianapolis"      // Eastern - IN (most areas)
#define TZ_AMERICA_INDIANA_KNOX             "America/Indiana/Knox"              // Central - IN (Starke)
#define TZ_AMERICA_INDIANA_MARENGO          "America/Indiana/Marengo"           // Eastern - IN (Crawford)
#define TZ_AMERICA_INDIANA_PETERSBURG       "America/Indiana/Petersburg"        // Eastern - IN (Pike)
#define TZ_AMERICA_INDIANA_TELL_CITY        "America/Indiana/Tell_City"         // Central - IN (Perry)
#define TZ_AMERICA_INDIANA_VEVAY            "America/Indiana/Vevay"             // Eastern - IN (Switzerland)
#define TZ_AMERICA_INDIANA_VINCENNES        "America/Indiana/Vincennes"         // Eastern - IN (Da, Du, K, Mn)
#define TZ_AMERICA_INDIANA_WINAMAC          "America/Indiana/Winamac"           // Eastern - IN (Pulaski)
#define TZ_AMERICA_INUVIK                   "America/Inuvik"                    // Mountain - NT (west)
#define TZ_AMERICA_IQALUIT                  "America/Iqaluit"                   // Eastern - NU (most east areas)
#define TZ_AMERICA_JAMAICA                  "America/Jamaica"
#define TZ_AMERICA_JUNEAU                   "America/Juneau"                    // Alaska - Juneau area
#define TZ_AMERICA_KENTUCKY_LOUISVILLE      "America/Kentucky/Louisville"       // Eastern - KY (Louisville area)
#define TZ_AMERICA_KENTUCKY_MONTICELLO      "America/Kentucky/Monticello"       // Eastern - KY (Wayne)
#define TZ_AMERICA_LA_PAZ                   "America/La_Paz"
#define TZ_AMERICA_LIMA                     "America/Lima"
#define TZ_AMERICA_LOS_ANGELES              "America/Los_Angeles"               // Pacific
#define TZ_AMERICA_MACEIO                   "America/Maceio"                    // Alagoas, Sergipe
#define TZ_AMERICA_MANAGUA                  "America/Managua"
#define TZ_AMERICA_MANAUS                   "America/Manaus"                    // Amazonas (east)
#define TZ_AMERICA_MARTINIQUE               "America/Martinique"
#define TZ_AMERICA_MATAMOROS                "America/Matamoros"                 // Central Time US - Coahuila, Nuevo León, Tamaulipas (US border)
#define TZ_AMERICA_MAZATLAN                 "America/Mazatlan"                  // Mountain Time - Baja California Sur, Nayarit, Sinaloa
#define TZ_AMERICA_MENOMINEE                "America/Menominee"                 // Central - MI (Wisconsin border)
#define TZ_AMERICA_MERIDA                   "America/Merida"                    // Central Time - Campeche, Yucatán
#define TZ_AMERICA_METLAKATLA               "America/Metlakatla"                // Alaska - Annette Island
#define TZ_AMERICA_MEXICO_CITY              "America/Mexico_City"               // Central Time
#define TZ_AMERICA_MIQUELON                 "America/Miquelon"
#define TZ_AMERICA_MONCTON                  "America/Moncton"                   // Atlantic - New Brunswick
#define TZ_AMERICA_MONTERREY                "America/Monterrey"                 // Central Time - Durango; Coahuila, Nuevo León, Tamaulipas (most areas)
#define TZ_AMERICA_MONTEVIDEO               "America/Montevideo"
#define TZ_AMERICA_NASSAU                   "America/Nassau"
#define TZ_AMERICA_NEW_YORK                 "America/New_York"                  // Eastern (most areas)
#define TZ_AMERICA_NIPIGON                  "America/Nipigon"                   // Eastern - ON, QC (no DST 1967-73)
#define TZ_AMERICA_NOME                     "America/Nome"                      // Alaska (west)
#define TZ_AMERICA_NORONHA                  "America/Noronha"                   // Atlantic islands
#define TZ_AMERICA_NORTH_DAKOTA_BEULAH      "America/North_Dakota/Beulah"       // Central - ND (Mercer)
#define TZ_AMERICA_NORTH_DAKOTA_CENTER      "America/North_Dakota/Center"       // Central - ND (Oliver)
#define TZ_AMERICA_NORTH_DAKOTA_NEW_SALEM   "America/North_Dakota/New_Salem"    // Central - ND (Morton rural)
#define TZ_AMERICA_OJINAGA                  "America/Ojinaga"                   // Mountain Time US - Chihuahua (US border)
#define TZ_AMERICA_PANAMA                   "America/Panama"
#define TZ_AMERICA_PANGNIRTUNG              "America/Pangnirtung"               // Eastern - NU (Pangnirtung)
#define TZ_AMERICA_PARAMARIBO               "America/Paramaribo"
#define TZ_AMERICA_PHOENIX                  "America/Phoenix"                   // MST - Arizona (except Navajo)
#define TZ_AMERICA_PORT_OF_SPAIN            "America/Port_of_Spain"
#define TZ_AMERICA_PORT_AU_PRINCE           "America/Port-au-Prince"
#define TZ_AMERICA_PORTO_VELHO              "America/Porto_Velho"               // Rondônia
#define TZ_AMERICA_PUERTO_RICO              "America/Puerto_Rico"
#define TZ_AMERICA_PUNTA_ARENAS             "America/Punta_Arenas"              // Region of Magallanes
#define TZ_AMERICA_RAINY_RIVER              "America/Rainy_River"               // Central - ON (Rainy R, Ft Frances)
#define TZ_AMERICA_RANKIN_INLET             "America/Rankin_Inlet"              // Central - NU (central)
#define TZ_AMERICA_RECIFE                   "America/Recife"                    // Pernambuco
#define TZ_AMERICA_REGINA                   "America/Regina"                    // CST - SK (most areas)
#define TZ_AMERICA_RESOLUTE                 "America/Resolute"                  // Central - NU (Resolute)
#define TZ_AMERICA_RIO_BRANCO               "America/Rio_Branco"                // Acre
#define TZ_AMERICA_SANTAREM                 "America/Santarem"                  // Pará (west)
#define TZ_AMERICA_SANTIAGO                 "America/Santiago"                  // Chile (most areas)
#define TZ_AMERICA_SANTO_DOMINGO            "America/Santo_Domingo"
#define TZ_AMERICA_SAO_PAULO                "America/Sao_Paulo"                 // Brazil (southeast: GO, DF, MG, ES, RJ, SP, PR, SC, RS)
#define TZ_AMERICA_SCORESBYSUND             "America/Scoresbysund"              // Scoresbysund/Ittoqqortoormiit
#define TZ_AMERICA_SITKA                    "America/Sitka"                     // Alaska - Sitka area
#define TZ_AMERICA_ST_JOHNS                 "America/St_Johns"                  // Newfoundland; Labrador (southeast)
#define TZ_AMERICA_SWIFT_CURRENT            "America/Swift_Current"             // CST - SK (midwest)
#define TZ_AMERICA_TEGUCIGALPA              "America/Tegucigalpa"
#define TZ_AMERICA_THULE                    "America/Thule"                     // Thule/Pituffik
#define TZ_AMERICA_THUNDER_BAY              "America/Thunder_Bay"               // Eastern - ON (Thunder Bay)
#define TZ_AMERICA_TIJUANA                  "America/Tijuana"                   // Pacific Time US - Baja California
#define TZ_AMERICA_TORONTO                  "America/Toronto"                   // Eastern - ON, QC (most areas)
#define TZ_AMERICA_VANCOUVER                "America/Vancouver"                 // Pacific - BC (most areas)
#define TZ_AMERICA_WHITEHORSE               "America/Whitehorse"                // Pacific - Yukon (south)
#define TZ_AMERICA_WINNIPEG                 "America/Winnipeg"                  // Central - ON (west); Manitoba
#define TZ_AMERICA_YAKUTAT                  "America/Yakutat"                   // Alaska - Yakutat
#define TZ_AMERICA_YELLOWKNIFE              "America/Yellowknife"               // Mountain - NT (central)

#define TZ_ANTARCTICA_CASEY                 "Antarctica/Casey"                  // Casey
#define TZ_ANTARCTICA_DAVIS                 "Antarctica/Davis"                  // Davis
#define TZ_ANTARCTICA_DUMONTDURVILLE        "Antarctica/DumontDUrville"         // Dumont-d'Urville
#define TZ_ANTARCTICA_MACQUARIE             "Antarctica/Macquarie"              // Macquarie Island
#define TZ_ANTARCTICA_MAWSON                "Antarctica/Mawson"                 // Mawson
#define TZ_ANTARCTICA_PALMER                "Antarctica/Palmer"                 // Palmer
#define TZ_ANTARCTICA_ROTHERA               "Antarctica/Rothera"                // Rothera
#define TZ_ANTARCTICA_SYOWA                 "Antarctica/Syowa"                  // Syowa
#define TZ_ANTARCTICA_TROLL                 "Antarctica/Troll"                  // Troll
#define TZ_ANTARCTICA_VOSTOK                "Antarctica/Vostok"                 // Vostok

#define TZ_ASIA_ALMATY                      "Asia/Almaty"                       // Kazakhstan (most areas)
#define TZ_ASIA_AMMAN                       "Asia/Amman"
#define TZ_ASIA_ANADYR                      "Asia/Anadyr"                       // MSK+09 - Bering Sea
#define TZ_ASIA_AQTAU                       "Asia/Aqtau"                        // Mangghystaū/Mankistau
#define TZ_ASIA_AQTOBE                      "Asia/Aqtobe"                       // Aqtöbe/Aktobe
#define TZ_ASIA_ASHGABAT                    "Asia/Ashgabat"
#define TZ_ASIA_ATYRAU                      "Asia/Atyrau"                       // Atyraū/Atirau/Gur'yev
#define TZ_ASIA_BAGHDAD                     "Asia/Baghdad"
#define TZ_ASIA_BAKU                        "Asia/Baku"
#define TZ_ASIA_BANGKOK                     "Asia/Bangkok"                      // Indochina (most areas)
#define TZ_ASIA_BARNAUL                     "Asia/Barnaul"                      // MSK+04 - Altai
#define TZ_ASIA_BEIRUT                      "Asia/Beirut"
#define TZ_ASIA_BISHKEK                     "Asia/Bishkek"
#define TZ_ASIA_BRUNEI                      "Asia/Brunei"
#define TZ_ASIA_CHITA                       "Asia/Chita"                        // MSK+06 - Zabaykalsky
#define TZ_ASIA_CHOIBALSAN                  "Asia/Choibalsan"                   // Dornod, Sükhbaatar
#define TZ_ASIA_COLOMBO                     "Asia/Colombo"
#define TZ_ASIA_DAMASCUS                    "Asia/Damascus"
#define TZ_ASIA_DHAKA                       "Asia/Dhaka"
#define TZ_ASIA_DILI                        "Asia/Dili"
#define TZ_ASIA_DUBAI                       "Asia/Dubai"
#define TZ_ASIA_DUSHANBE                    "Asia/Dushanbe"
#define TZ_ASIA_FAMAGUSTA                   "Asia/Famagusta"                    // Northern Cyprus
#define TZ_ASIA_GAZA                        "Asia/Gaza"                         // Gaza Strip
#define TZ_ASIA_HEBRON                      "Asia/Hebron"                       // West Bank
#define TZ_ASIA_HO_CHI_MINH                 "Asia/Ho_Chi_Minh"                  // Vietnam (south)
#define TZ_ASIA_HONG_KONG                   "Asia/Hong_Kong"
#define TZ_ASIA_HOVD                        "Asia/Hovd"                         // Bayan-Ölgii, Govi-Altai, Hovd, Uvs, Zavkhan
#define TZ_ASIA_IRKUTSK                     "Asia/Irkutsk"                      // MSK+05 - Irkutsk, Buryatia
#define TZ_ASIA_JAKARTA                     "Asia/Jakarta"                      // Java, Sumatra
#define TZ_ASIA_JAYAPURA                    "Asia/Jayapura"                     // New Guinea (West Papua / Irian Jaya); Malukus/Moluccas
#define TZ_ASIA_JERUSALEM                   "Asia/Jerusalem"
#define TZ_ASIA_KABUL                       "Asia/Kabul"
#define TZ_ASIA_KAMCHATKA                   "Asia/Kamchatka"                    // MSK+09 - Kamchatka
#define TZ_ASIA_KARACHI                     "Asia/Karachi"
#define TZ_ASIA_KATHMANDU                   "Asia/Kathmandu"
#define TZ_ASIA_KHANDYGA                    "Asia/Khandyga"                     // MSK+06 - Tomponsky, Ust-Maysky
#define TZ_ASIA_KOLKATA                     "Asia/Kolkata"
#define TZ_ASIA_KRASNOYARSK                 "Asia/Krasnoyarsk"                  // MSK+04 - Krasnoyarsk area
#define TZ_ASIA_KUALA_LUMPUR                "Asia/Kuala_Lumpur"                 // Malaysia (peninsula)
#define TZ_ASIA_KUCHING                     "Asia/Kuching"                      // Sabah, Sarawak
#define TZ_ASIA_MACAU                       "Asia/Macau"
#define TZ_ASIA_MAGADAN                     "Asia/Magadan"                      // MSK+08 - Magadan
#define TZ_ASIA_MAKASSAR                    "Asia/Makassar"                     // Borneo (east, south); Sulawesi/Celebes, Bali, Nusa Tengarra; Timor (west)
#define TZ_ASIA_MANILA                      "Asia/Manila"
#define TZ_ASIA_NICOSIA                     "Asia/Nicosia"                      // Cyprus (most areas)
#define TZ_ASIA_NOVOKUZNETSK                "Asia/Novokuznetsk"                 // MSK+04 - Kemerovo
#define TZ_ASIA_NOVOSIBIRSK                 "Asia/Novosibirsk"                  // MSK+04 - Novosibirsk
#define TZ_ASIA_OMSK                        "Asia/Omsk"                         // MSK+03 - Omsk
#define TZ_ASIA_ORAL                        "Asia/Oral"                         // West Kazakhstan
#define TZ_ASIA_PONTIANAK                   "Asia/Pontianak"                    // Borneo (west, central)
#define TZ_ASIA_PYONGYANG                   "Asia/Pyongyang"
#define TZ_ASIA_QATAR                       "Asia/Qatar"
#define TZ_ASIA_QYZYLORDA                   "Asia/Qyzylorda"                    // Qyzylorda/Kyzylorda/Kzyl-Orda
#define TZ_ASIA_RIYADH                      "Asia/Riyadh"
#define TZ_ASIA_SAKHALIN                    "Asia/Sakhalin"                     // MSK+08 - Sakhalin Island
#define TZ_ASIA_SAMARKAND                   "Asia/Samarkand"                    // Uzbekistan (west)
#define TZ_ASIA_SEOUL                       "Asia/Seoul"
#define TZ_ASIA_SHANGHAI                    "Asia/Shanghai"                     // Beijing Time
#define TZ_ASIA_SINGAPORE                   "Asia/Singapore"
#define TZ_ASIA_SREDNEKOLYMSK               "Asia/Srednekolymsk"                // MSK+08 - Sakha (E); North Kuril Is
#define TZ_ASIA_TAIPEI                      "Asia/Taipei"
#define TZ_ASIA_TASHKENT                    "Asia/Tashkent"                     // Uzbekistan (east)
#define TZ_ASIA_TBILISI                     "Asia/Tbilisi"
#define TZ_ASIA_TEHRAN                      "Asia/Tehran"
#define TZ_ASIA_THIMPHU                     "Asia/Thimphu"
#define TZ_ASIA_TOKYO                       "Asia/Tokyo"
#define TZ_ASIA_TOMSK                       "Asia/Tomsk"                        // MSK+04 - Tomsk
#define TZ_ASIA_ULAANBAATAR                 "Asia/Ulaanbaatar"                  // Mongolia (most areas)
#define TZ_ASIA_URUMQI                      "Asia/Urumqi"                       // Xinjiang Time
#define TZ_ASIA_UST_NERA                    "Asia/Ust-Nera"                     // MSK+07 - Oymyakonsky
#define TZ_ASIA_VLADIVOSTOK                 "Asia/Vladivostok"                  // MSK+07 - Amur River
#define TZ_ASIA_YAKUTSK                     "Asia/Yakutsk"                      // MSK+06 - Lena River
#define TZ_ASIA_YANGON                      "Asia/Yangon"
#define TZ_ASIA_YEKATERINBURG               "Asia/Yekaterinburg"                // MSK+02 - Urals
#define TZ_ASIA_YEREVAN                     "Asia/Yerevan"

#define TZ_ATLANTIC_AZORES                  "Atlantic/Azores"                   // Azores
#define TZ_ATLANTIC_BERMUDA                 "Atlantic/Bermuda"
#define TZ_ATLANTIC_CANARY                  "Atlantic/Canary"                   // Canary Islands
#define TZ_ATLANTIC_CAPE_VERDE              "Atlantic/Cape_Verde"
#define TZ_ATLANTIC_FAROE                   "Atlantic/Faroe"
#define TZ_ATLANTIC_MADEIRA                 "Atlantic/Madeira"                  // Madeira Islands
#define TZ_ATLANTIC_REYKJAVIK               "Atlantic/Reykjavik"
#define TZ_ATLANTIC_SOUTH_GEORGIA           "Atlantic/South_Georgia"
#define TZ_ATLANTIC_STANLEY                 "Atlantic/Stanley"

#define TZ_AUSTRALIA_ADELAIDE               "Australia/Adelaide"                // South Australia
#define TZ_AUSTRALIA_BRISBANE               "Australia/Brisbane"                // Queensland (most areas)
#define TZ_AUSTRALIA_BROKEN_HILL            "Australia/Broken_Hill"             // New South Wales (Yancowinna)
#define TZ_AUSTRALIA_CURRIE                 "Australia/Currie"                  // Tasmania (King Island)
#define TZ_AUSTRALIA_DARWIN                 "Australia/Darwin"                  // Northern Territory
#define TZ_AUSTRALIA_EUCLA                  "Australia/Eucla"                   // Western Australia (Eucla)
#define TZ_AUSTRALIA_HOBART                 "Australia/Hobart"                  // Tasmania (most areas)
#define TZ_AUSTRALIA_LINDEMAN               "Australia/Lindeman"                // Queensland (Whitsunday Islands)
#define TZ_AUSTRALIA_LORD_HOWE              "Australia/Lord_Howe"               // Lord Howe Island
#define TZ_AUSTRALIA_MELBOURNE              "Australia/Melbourne"               // Victoria
#define TZ_AUSTRALIA_PERTH                  "Australia/Perth"                   // Western Australia (most areas)
#define TZ_AUSTRALIA_SYDNEY                 "Australia/Sydney"                  // New South Wales (most areas)

#define TZ_EUROPE_AMSTERDAM                 "Europe/Amsterdam"
#define TZ_EUROPE_ANDORRA                   "Europe/Andorra"
#define TZ_EUROPE_ASTRAKHAN                 "Europe/Astrakhan"                  // MSK+01 - Astrakhan
#define TZ_EUROPE_ATHENS                    "Europe/Athens"
#define TZ_EUROPE_BELGRADE                  "Europe/Belgrade"
#define TZ_EUROPE_BERLIN                    "Europe/Berlin"                     // Germany (most areas)
#define TZ_EUROPE_BRUSSELS                  "Europe/Brussels"
#define TZ_EUROPE_BUCHAREST                 "Europe/Bucharest"
#define TZ_EUROPE_BUDAPEST                  "Europe/Budapest"
#define TZ_EUROPE_CHISINAU                  "Europe/Chisinau"
#define TZ_EUROPE_COPENHAGEN                "Europe/Copenhagen"
#define TZ_EUROPE_DUBLIN                    "Europe/Dublin"
#define TZ_EUROPE_GIBRALTAR                 "Europe/Gibraltar"
#define TZ_EUROPE_HELSINKI                  "Europe/Helsinki"
#define TZ_EUROPE_ISTANBUL                  "Europe/Istanbul"
#define TZ_EUROPE_KALININGRAD               "Europe/Kaliningrad"                // MSK-01 - Kaliningrad
#define TZ_EUROPE_KIEV                      "Europe/Kiev"                       // Ukraine (most areas)
#define TZ_EUROPE_KIROV                     "Europe/Kirov"                      // MSK+00 - Kirov
#define TZ_EUROPE_LISBON                    "Europe/Lisbon"                     // Portugal (mainland)
#define TZ_EUROPE_LONDON                    "Europe/London"
#define TZ_EUROPE_LUXEMBOURG                "Europe/Luxembourg"
#define TZ_EUROPE_MADRID                    "Europe/Madrid"                     // Spain (mainland)
#define TZ_EUROPE_MALTA                     "Europe/Malta"
#define TZ_EUROPE_MINSK                     "Europe/Minsk"
#define TZ_EUROPE_MONACO                    "Europe/Monaco"
#define TZ_EUROPE_MOSCOW                    "Europe/Moscow"                     // MSK+00 - Moscow area
#define TZ_EUROPE_OSLO                      "Europe/Oslo"
#define TZ_EUROPE_PARIS                     "Europe/Paris"
#define TZ_EUROPE_PRAGUE                    "Europe/Prague"
#define TZ_EUROPE_RIGA                      "Europe/Riga"
#define TZ_EUROPE_ROME                      "Europe/Rome"
#define TZ_EUROPE_SAMARA                    "Europe/Samara"                     // MSK+01 - Samara, Udmurtia
#define TZ_EUROPE_SARATOV                   "Europe/Saratov"                    // MSK+01 - Saratov
#define TZ_EUROPE_SIMFEROPOL                "Europe/Simferopol"                 // MSK+00 - Crimea
#define TZ_EUROPE_SOFIA                     "Europe/Sofia"
#define TZ_EUROPE_STOCKHOLM                 "Europe/Stockholm"
#define TZ_EUROPE_TALLINN                   "Europe/Tallinn"
#define TZ_EUROPE_TIRANE                    "Europe/Tirane"
#define TZ_EUROPE_ULYANOVSK                 "Europe/Ulyanovsk"                  // MSK+01 - Ulyanovsk
#define TZ_EUROPE_UZHGOROD                  "Europe/Uzhgorod"                   // Ruthenia
#define TZ_EUROPE_VIENNA                    "Europe/Vienna"
#define TZ_EUROPE_VILNIUS                   "Europe/Vilnius"
#define TZ_EUROPE_VOLGOGRAD                 "Europe/Volgograd"                  // MSK+00 - Volgograd
#define TZ_EUROPE_WARSAW                    "Europe/Warsaw"
#define TZ_EUROPE_ZAPOROZHYE                "Europe/Zaporozhye"                 // Zaporozh'ye/Zaporizhia; Lugansk/Luhansk (east)
#define TZ_EUROPE_ZURICH                    "Europe/Zurich"                     // Swiss time

#define TZ_INDIAN_CHAGOS                    "Indian/Chagos"
#define TZ_INDIAN_CHRISTMAS                 "Indian/Christmas"
#define TZ_INDIAN_COCOS                     "Indian/Cocos"
#define TZ_INDIAN_KERGUELEN                 "Indian/Kerguelen"                  // Kerguelen, St Paul Island, Amsterdam Island
#define TZ_INDIAN_MAHE                      "Indian/Mahe"
#define TZ_INDIAN_MALDIVES                  "Indian/Maldives"
#define TZ_INDIAN_MAURITIUS                 "Indian/Mauritius"
#define TZ_INDIAN_REUNION                   "Indian/Reunion"                    // Réunion, Crozet, Scattered Islands

#define TZ_PACIFIC_APIA                     "Pacific/Apia"
#define TZ_PACIFIC_AUCKLAND                 "Pacific/Auckland"                  // New Zealand time
#define TZ_PACIFIC_BOUGAINVILLE             "Pacific/Bougainville"              // Bougainville
#define TZ_PACIFIC_CHATHAM                  "Pacific/Chatham"                   // Chatham Islands
#define TZ_PACIFIC_CHUUK                    "Pacific/Chuuk"                     // Chuuk/Truk, Yap
#define TZ_PACIFIC_EASTER                   "Pacific/Easter"                    // Easter Island
#define TZ_PACIFIC_EFATE                    "Pacific/Efate"
#define TZ_PACIFIC_ENDERBURY                "Pacific/Enderbury"                 // Phoenix Islands
#define TZ_PACIFIC_FAKAOFO                  "Pacific/Fakaofo"
#define TZ_PACIFIC_FIJI                     "Pacific/Fiji"
#define TZ_PACIFIC_FUNAFUTI                 "Pacific/Funafuti"
#define TZ_PACIFIC_GALAPAGOS                "Pacific/Galapagos"                 // Galápagos Islands
#define TZ_PACIFIC_GAMBIER                  "Pacific/Gambier"                   // Gambier Islands
#define TZ_PACIFIC_GUADALCANAL              "Pacific/Guadalcanal"
#define TZ_PACIFIC_GUAM                     "Pacific/Guam"
#define TZ_PACIFIC_HONOLULU                 "Pacific/Honolulu"                  // Hawaii
#define TZ_PACIFIC_KIRITIMATI               "Pacific/Kiritimati"                // Line Islands
#define TZ_PACIFIC_KOSRAE                   "Pacific/Kosrae"                    // Kosrae
#define TZ_PACIFIC_KWAJALEIN                "Pacific/Kwajalein"                 // Kwajalein
#define TZ_PACIFIC_MAJURO                   "Pacific/Majuro"                    // Marshall Islands (most areas)
#define TZ_PACIFIC_MARQUESAS                "Pacific/Marquesas"                 // Marquesas Islands
#define TZ_PACIFIC_NAURU                    "Pacific/Nauru"
#define TZ_PACIFIC_NIUE                     "Pacific/Niue"
#define TZ_PACIFIC_NORFOLK                  "Pacific/Norfolk"
#define TZ_PACIFIC_NOUMEA                   "Pacific/Noumea"
#define TZ_PACIFIC_PAGO_PAGO                "Pacific/Pago_Pago"                 // Samoa, Midway
#define TZ_PACIFIC_PALAU                    "Pacific/Palau"
#define TZ_PACIFIC_PITCAIRN                 "Pacific/Pitcairn"
#define TZ_PACIFIC_POHNPEI                  "Pacific/Pohnpei"                   // Pohnpei/Ponape
#define TZ_PACIFIC_PORT_MORESBY             "Pacific/Port_Moresby"              // Papua New Guinea (most areas)
#define TZ_PACIFIC_RAROTONGA                "Pacific/Rarotonga"
#define TZ_PACIFIC_TAHITI                   "Pacific/Tahiti"                    // Society Islands
#define TZ_PACIFIC_TARAWA                   "Pacific/Tarawa"                    // Gilbert Islands
#define TZ_PACIFIC_TONGATAPU                "Pacific/Tongatapu"
#define TZ_PACIFIC_WAKE                     "Pacific/Wake"                      // Wake Island
#define TZ_PACIFIC_WALLIS                   "Pacific/Wallis"

// Others - added from the list in wikipedia. Only that IDs that not had been mapped to others or that are a good
// general base had been added.
#define TZ_GMT                              "Etc/GMT"
#define TZ_GMT0                             TZ_GMT
#define TZ_UTC                              "Etc/UTC"

#define TZ_WET                              "WET"                               // Western European Time
#define TZ_MET                              "MET"                               // Central European Time
#define TZ_EET                              "EET"                               // Eastern European Time

#define TZ_EST                              "EST"                               // Eastern Standard Time (North America)
#define TZ_MST                              "MST"                               // Mountain Standard Time
#define TZ_HST                              "HST"                               // Hawaiian Standard Time

#define TZ_GREENWICH                        TZ_GMT
#define TZ_UNIVERSAL                        TZ_UTC
#define TZ_ZULU                             TZ_UTC

#define TZ_CST6CDT                          "CST6CDT"
#define TZ_EST5EDT                          "EST5EDT"
#define TZ_MST7MDT                          "MST7MDT"
#define TZ_PST8PDT                          "PST8PDT"


// These defines are an other way of handling the timezones. The zones here are grouped by - what a
// coincidence - the system / groups used by Microsoft (Windows / Exchange). The defines are sorted
// by their UTC value. Because + and - are not valid for define names, + had been replaced by a P
// and - by a M. (So UTC+01:00 becomes UTC_P0100).
//
// The mapping had been done with the informations found at the homepage of the unicode group
// (http://unicode.org/repos/cldr/trunk/common/supplemental/windowsZones.xml - legal informations
// can be found at http://www.unicode.org/copyright.html). For the mapping itself, all entries with
// territory="001" had been used, except if that value was an GMT+* value and the group had an other
// option for a city / country. Also tz ids that are linked to others had been updated by using the
// list at wikipedia (https://en.wikipedia.org/wiki/List_of_tz_database_time_zones)
//
// Note that are some exception (e. G. Mid-Atlantic Standard Time). More informations about that exceptions
// (as well as for exceptions of tz database items that can not be mapped to windows timeszone) can be
// found here: http://cldr.unicode.org/development/development-process/design-proposals/extended-windows-olson-zid-mapping
//

#define TZ_UTC_M1200_INTERNATIONAL_DATE_LINE_WEST                   TZ_GMT"+12"                         // (UTC-12:00) International Date Line West
#define TZ_UTC_M1100_COORDINATED_UNIVERSAL_TIME_11                  TZ_PACIFIC_PAGO_PAGO                // (UTC-11:00) Coordinated Universal Time-11
#define TZ_UTC_M1000_ALEUTIAN_ISLANDS                               TZ_AMERICA_ADAK                     // (UTC-10:00) Aleutian Islands
#define TZ_UTC_M1000_HAWAII                                         TZ_PACIFIC_HONOLULU                 // (UTC-10:00) Hawaii
#define TZ_UTC_M0930_MARQUESAS_ISLANDS                              TZ_PACIFIC_MARQUESAS                // (UTC-09:30) Marquesas Islands
#define TZ_UTC_M0900_ALASKA                                         TZ_AMERICA_ANCHORAGE                // (UTC-09:00) Alaska
#define TZ_UTC_M0900_COORDINATED_UNIVERSAL_TIME_09                  TZ_PACIFIC_GAMBIER                  // (UTC-09:00) Coordinated Universal Time-09
#define TZ_UTC_M0800_BAJA_CALIFORNIA                                TZ_AMERICA_TIJUANA                  // (UTC-08:00) Baja California
#define TZ_UTC_M0800_COORDINATED_UNIVERSAL_TIME_08                  TZ_PACIFIC_PITCAIRN                 // (UTC-08:00) Coordinated Universal Time-08
#define TZ_UTC_M0800_PACIFIC_TIME_US_CANADA                         TZ_AMERICA_LOS_ANGELES              // (UTC-08:00) Pacific Time (US & Canada)
#define TZ_UTC_M0700_ARIZONA                                        TZ_AMERICA_PHOENIX                  // (UTC-07:00) Arizona
#define TZ_UTC_M0700_CHIHUAHUA_LA_PAZ_MAZATLAN                      TZ_AMERICA_CHIHUAHUA                // (UTC-07:00) Chihuahua, La Paz, Mazatlan
#define TZ_UTC_M0700_MOUNTAIN_TIME_US_CANADA                        TZ_AMERICA_DENVER                   // (UTC-07:00) Mountain Time (US & Canada)
#define TZ_UTC_M0600_CENTRAL_AMERICA                                TZ_AMERICA_GUATEMALA                // (UTC-06:00) Central America
#define TZ_UTC_M0600_CENTRAL_TIME_US_CANADA                         TZ_AMERICA_CHICAGO                  // (UTC-06:00) Central Time (US & Canada)
#define TZ_UTC_M0600_EASTER_ISLAND                                  TZ_PACIFIC_EASTER                   // (UTC-06:00) Easter Island
#define TZ_UTC_M0600_GUADALAJARA_MEXICO_CITY_MONTERREY	            TZ_AMERICA_MEXICO_CITY              // (UTC-06:00) Guadalajara, Mexico City, Monterrey
#define TZ_UTC_M0600_SASKATCHEWAN                                   TZ_AMERICA_REGINA                   // (UTC-06:00) Saskatchewan
#define TZ_UTC_M0500_BOGOTA_LIMA_QUITO_RIO_BRANCO                   TZ_AMERICA_BOGOTA                   // (UTC-05:00) Bogota, Lima, Quito, Rio Branco
#define TZ_UTC_M0500_CHETUMAL                                       TZ_AMERICA_CANCUN                   // (UTC-05:00) Chetumal
#define TZ_UTC_M0500_EASTERN_TIME_US_CANADA                         TZ_AMERICA_NEW_YORK                 // (UTC-05:00) Eastern Time (US & Canada)
#define TZ_UTC_M0500_HAITI                                          TZ_AMERICA_PORT_AU_PRINCE           // (UTC-05:00) Haiti
#define TZ_UTC_M0500_HAVANA                                         TZ_AMERICA_HAVANA                   // (UTC-05:00) Havana
#define TZ_UTC_M0500_INDIANA_EAST                                   TZ_AMERICA_INDIANA_INDIANAPOLIS     // (UTC-05:00) Indiana (East)
#define TZ_UTC_M0400_ASUNCION                                       TZ_AMERICA_ASUNCION                 // (UTC-04:00) Asuncion
#define TZ_UTC_M0400_ATLANTIC_TIME_CANADA                           TZ_AMERICA_HALIFAX                  // (UTC-04:00) Atlantic Time (Canada)
#define TZ_UTC_M0400_CARACAS                                        TZ_AMERICA_CARACAS                  // (UTC-04:00) Caracas
#define TZ_UTC_M0400_CUIABA                                         TZ_AMERICA_CUIABA                   // (UTC-04:00) Cuiaba
#define TZ_UTC_M0400_GEORGETOWN_LA_PAZ_MANAUS_SAN_JUAN              TZ_AMERICA_LA_PAZ                   // (UTC-04:00) Georgetown, La Paz, Manaus, San Juan
#define TZ_UTC_M0400_SANTIAGO                                       TZ_AMERICA_SANTIAGO                 // (UTC-04:00) Santiago
#define TZ_UTC_M0400_TURKS_AND_CAICOS                               TZ_AMERICA_GRAND_TURK               // (UTC-04:00) Turks and Caicos
#define TZ_UTC_M0330_NEWFOUNDLAND                                   TZ_AMERICA_ST_JOHNS                 // (UTC-03:30) Newfoundland
#define TZ_UTC_M0300_ARAGUAINA                                      TZ_AMERICA_ARAGUAINA                // (UTC-03:00) Araguaina
#define TZ_UTC_M0300_BRASILIA                                       TZ_AMERICA_SAO_PAULO                // (UTC-03:00) Brasilia
#define TZ_UTC_M0300_CAYENNE_FORTALEZA                              TZ_AMERICA_CAYENNE                  // (UTC-03:00) Cayenne, Fortaleza
#define TZ_UTC_M0300_CITY_OF_BUENOS_AIRES                           TZ_AMERICA_ARGENTINA_BUENOS_AIRES   // (UTC-03:00) City of Buenos Aires
#define TZ_UTC_M0300_GREENLAND                                      TZ_AMERICA_GODTHAB                  // (UTC-03:00) Greenland
#define TZ_UTC_M0300_MONTEVIDEO                                     TZ_AMERICA_MONTEVIDEO               // (UTC-03:00) Montevideo
#define TZ_UTC_M0300_PUNTA_ARENAS                                   TZ_AMERICA_PUNTA_ARENAS             // (UTC-03:00) Punta Arenas 
#define TZ_UTC_M0300_SAINT_PIERRE_AND_MIQUELON                      TZ_AMERICA_MIQUELON                 // (UTC-03:00) Saint Pierre and Miquelon
#define TZ_UTC_M0300_SALVADOR                                       TZ_AMERICA_BAHIA                    // (UTC-03:00) Salvador
#define TZ_UTC_M0200_COORDINATED_UNIVERSAL_TIME_02                  TZ_AMERICA_NORONHA                  // (UTC-02:00) Coordinated Universal Time-02
#define TZ_UTC_M0100_AZORES                                         TZ_ATLANTIC_AZORES                  // (UTC-01:00) Azores
#define TZ_UTC_M0100_CABO_VERDE_IS                                  TZ_ATLANTIC_CAPE_VERDE              // (UTC-01:00) Cabo Verde Is.
#define TZ_UTC_COORDINATED_UNIVERSAL_TIME                           TZ_AMERICA_DANMARKSHAVN             // (UTC) Coordinated Universal Time
#define TZ_UTC_P0000_CASABLANCA                                     TZ_AFRICA_CASABLANCA                // (UTC+00:00) Casablanca
#define TZ_UTC_P0000_DUBLIN_EDINBURGH_LISBON_LONDON                 TZ_EUROPE_LONDON                    // (UTC+00:00) Dublin, Edinburgh, Lisbon, London
#define TZ_UTC_P0000_MONROVIA_REYKJAVIK                             TZ_ATLANTIC_REYKJAVIK               // (UTC+00:00) Monrovia, Reykjavik
#define TZ_UTC_P0100_AMSTERDAM_BERLIN_BERN_ROME_STOCKHOLM_VIENNA    TZ_EUROPE_BERLIN                    // (UTC+01:00) Amsterdam, Berlin, Bern, Rome, Stockholm, Vienna
#define TZ_UTC_P0100_BELGRADE_BRATISLAVA_BUDAPEST_LJUBLJANA_PRAGUE	TZ_EUROPE_BUDAPEST                  // (UTC+01:00) Belgrade, Bratislava, Budapest, Ljubljana, Prague
#define TZ_UTC_P0100_BRUSSELS_COPENHAGEN_MADRID_PARIS               TZ_EUROPE_PARIS                     // (UTC+01:00) Brussels, Copenhagen, Madrid, Paris
#define TZ_UTC_P0100_SARAJEVO_SKOPJE_WARSAW_ZAGREB                  TZ_EUROPE_WARSAW                    // (UTC+01:00) Sarajevo, Skopje, Warsaw, Zagreb
#define TZ_UTC_P0100_WEST_CENTRAL_AFRICA                            TZ_AFRICA_LAGOS                     // (UTC+01:00) West Central Africa
#define TZ_UTC_P0100_WINDHOEK                                       TZ_AFRICA_WINDHOEK                  // (UTC+01:00) Windhoek
#define TZ_UTC_P0200_AMMAN                                          TZ_ASIA_AMMAN                       // (UTC+02:00) Amman
#define TZ_UTC_P0200_ATHENS_BUCHAREST                               TZ_EUROPE_BUCHAREST                 // (UTC+02:00) Athens, Bucharest
#define TZ_UTC_P0200_BEIRUT                                         TZ_ASIA_BEIRUT                      // (UTC+02:00) Beirut
#define TZ_UTC_P0200_CAIRO                                          TZ_AFRICA_CAIRO                     // (UTC+02:00) Cairo
#define TZ_UTC_P0200_CHISINAU                                       TZ_EUROPE_CHISINAU                  // (UTC+02:00) Chisinau
#define TZ_UTC_P0200_DAMASCUS                                       TZ_ASIA_DAMASCUS                    // (UTC+02:00) Damascus
#define TZ_UTC_P0200_GAZA_HEBRON                                    TZ_ASIA_HEBRON                      // (UTC+02:00) Gaza, Hebron
#define TZ_UTC_P0200_HARARE_PRETORIA                                TZ_AFRICA_JOHANNESBURG              // (UTC+02:00) Harare, Pretoria
#define TZ_UTC_P0200_HELSINKI_KYIV_RIGA_SOFIA_TALLINN_VILNIUS       TZ_EUROPE_KIEV                      // (UTC+02:00) Helsinki, Kyiv, Riga, Sofia, Tallinn, Vilnius
#define TZ_UTC_P0200_JERUSALEM                                      TZ_ASIA_JERUSALEM                   // (UTC+02:00) Jerusalem
#define TZ_UTC_P0200_KALININGRAD                                    TZ_EUROPE_KALININGRAD               // (UTC+02:00) Kaliningrad
#define TZ_UTC_P0200_TRIPOLI                                        TZ_AFRICA_TRIPOLI                   // (UTC+02:00) Tripoli
#define TZ_UTC_P0200_SUDAN                                          TZ_AFRICA_JUBA                      // (UTC+02:00) Sudan Standard Time
#define TZ_UTC_P0300_BAGHDAD                                        TZ_ASIA_BAGHDAD                     // (UTC+03:00) Baghdad
#define TZ_UTC_P0300_ISTANBUL                                       TZ_EUROPE_ISTANBUL                  // (UTC+03:00) Istanbul
#define TZ_UTC_P0300_KUWAIT_RIYADH                                  TZ_ASIA_RIYADH                      // (UTC+03:00) Kuwait, Riyadh
#define TZ_UTC_P0300_MINSK                                          TZ_EUROPE_MINSK                     // (UTC+03:00) Minsk
#define TZ_UTC_P0300_MOSCOW_ST_PETERSBURG_VOLGOGRAD                 TZ_EUROPE_MOSCOW                    // (UTC+03:00) Moscow, St. Petersburg, Volgograd
#define TZ_UTC_P0300_NAIROBI                                        TZ_AFRICA_NAIROBI                   // (UTC+03:00) Nairobi
#define TZ_UTC_P0330_TEHRAN                                         TZ_ASIA_TEHRAN                      // (UTC+03:30) Tehran
#define TZ_UTC_P0400_ABU_DHABI_MUSCAT                               TZ_ASIA_DUBAI                       // (UTC+04:00) Abu Dhabi, Muscat
#define TZ_UTC_P0400_ASTRAKHAN_ULYANOVSK                            TZ_EUROPE_ASTRAKHAN                 // (UTC+04:00) Astrakhan, Ulyanovsk
#define TZ_UTC_P0400_BAKU                                           TZ_ASIA_BAKU                        // (UTC+04:00) Baku
#define TZ_UTC_P0400_IZHEVSK_SAMARA                                 TZ_EUROPE_SAMARA                    // (UTC+04:00) Izhevsk, Samara
#define TZ_UTC_P0400_PORT_LOUIS                                     TZ_INDIAN_MAURITIUS                 // (UTC+04:00) Port Louis
#define TZ_UTC_P0400_SARATOV                                        TZ_EUROPE_SARATOV                   // (UTC+04:00) Saratov 
#define TZ_UTC_P0400_TBILISI                                        TZ_ASIA_TBILISI                     // (UTC+04:00) Tbilisi
#define TZ_UTC_P0400_YEREVAN                                        TZ_ASIA_YEREVAN                     // (UTC+04:00) Yerevan
#define TZ_UTC_P0430_KABUL                                          TZ_ASIA_KABUL                       // (UTC+04:30) Kabul
#define TZ_UTC_P0500_ASHGABAT_TASHKENT                              TZ_ASIA_TASHKENT                    // (UTC+05:00) Ashgabat, Tashkent
#define TZ_UTC_P0500_EKATERINBURG                                   TZ_ASIA_YEKATERINBURG               // (UTC+05:00) Ekaterinburg
#define TZ_UTC_P0500_ISLAMABAD_KARACHI                              TZ_ASIA_KARACHI                     // (UTC+05:00) Islamabad, Karachi
#define TZ_UTC_P0530_CHENNAI_KOLKATA_MUMBAI_NEW_DELHI               TZ_ASIA_KOLKATA                     // (UTC+05:30) Chennai, Kolkata, Mumbai, New Delhi
#define TZ_UTC_P0530_SRI_JAYAWARDENEPURA                            TZ_ASIA_COLOMBO                     // (UTC+05:30) Sri Jayawardenepura
#define TZ_UTC_P0545_KATHMANDU                                      TZ_ASIA_KATHMANDU                   // (UTC+05:45) Kathmandu
#define TZ_UTC_P0600_ASTANA                                         TZ_ASIA_ALMATY                      // (UTC+06:00) Astana
#define TZ_UTC_P0600_DHAKA                                          TZ_ASIA_DHAKA                       // (UTC+06:00) Dhaka
#define TZ_UTC_P0600_OMSK                                           TZ_ASIA_OMSK                        // (UTC+06:00) Omsk
#define TZ_UTC_P0630_YANGON_RANGOON                                 TZ_ASIA_YANGON                      // (UTC+06:30) Yangon (Rangoon)
#define TZ_UTC_P0700_BANGKOK_HANOI_JAKARTA                          TZ_ASIA_BANGKOK                     // (UTC+07:00) Bangkok, Hanoi, Jakarta
#define TZ_UTC_P0700_BARNAUL_GORNO_ALTAYSK                          TZ_ASIA_BARNAUL                     // (UTC+07:00) Barnaul, Gorno-Altaysk
#define TZ_UTC_P0700_HOVD                                           TZ_ASIA_HOVD                        // (UTC+07:00) Hovd
#define TZ_UTC_P0700_KRASNOYARSK                                    TZ_ASIA_KRASNOYARSK                 // (UTC+07:00) Krasnoyarsk
#define TZ_UTC_P0700_NOVOSIBIRSK                                    TZ_ASIA_NOVOSIBIRSK                 // (UTC+07:00) Novosibirsk
#define TZ_UTC_P0700_TOMSK                                          TZ_ASIA_TOMSK                       // (UTC+07:00) Tomsk
#define TZ_UTC_P0800_BEIJING_CHONGQING_HONG_KONG_URUMQI             TZ_ASIA_SHANGHAI                    // (UTC+08:00) Beijing, Chongqing, Hong Kong, Urumqi
#define TZ_UTC_P0800_IRKUTSK                                        TZ_ASIA_IRKUTSK                     // (UTC+08:00) Irkutsk
#define TZ_UTC_P0800_KUALA_LUMPUR_SINGAPORE                         TZ_ASIA_SINGAPORE                   // (UTC+08:00) Kuala Lumpur, Singapore
#define TZ_UTC_P0800_PERTH                                          TZ_AUSTRALIA_PERTH                  // (UTC+08:00) Perth
#define TZ_UTC_P0800_TAIPEI                                         TZ_ASIA_TAIPEI                      // (UTC+08:00) Taipei
#define TZ_UTC_P0800_ULAANBAATAR                                    TZ_ASIA_ULAANBAATAR                 // (UTC+08:00) Ulaanbaatar
#define TZ_UTC_P0830_PYONGYANG                                      TZ_ASIA_PYONGYANG                   // (UTC+08:30) Pyongyang
#define TZ_UTC_P0845_EUCLA                                          TZ_AUSTRALIA_EUCLA                  // (UTC+08:45) Eucla
#define TZ_UTC_P0900_CHITA                                          TZ_ASIA_CHITA                       // (UTC+09:00) Chita
#define TZ_UTC_P0900_OSAKA_SAPPORO_TOKYO                            TZ_ASIA_TOKYO                       // (UTC+09:00) Osaka, Sapporo, Tokyo
#define TZ_UTC_P0900_SEOUL                                          TZ_ASIA_SEOUL                       // (UTC+09:00) Seoul
#define TZ_UTC_P0900_YAKUTSK                                        TZ_ASIA_YAKUTSK                     // (UTC+09:00) Yakutsk
#define TZ_UTC_P0930_ADELAIDE                                       TZ_AUSTRALIA_ADELAIDE               // (UTC+09:30) Adelaide
#define TZ_UTC_P0930_DARWIN                                         TZ_AUSTRALIA_DARWIN                 // (UTC+09:30) Darwin
#define TZ_UTC_P1000_BRISBANE                                       TZ_AUSTRALIA_BRISBANE               // (UTC+10:00) Brisbane
#define TZ_UTC_P1000_CANBERRA_MELBOURNE_SYDNEY                      TZ_AUSTRALIA_SYDNEY                 // (UTC+10:00) Canberra, Melbourne, Sydney
#define TZ_UTC_P1000_GUAM_PORT_MORESBY                              TZ_PACIFIC_PORT_MORESBY             // (UTC+10:00) Guam, Port Moresby
#define TZ_UTC_P1000_HOBART                                         TZ_AUSTRALIA_HOBART                 // (UTC+10:00) Hobart
#define TZ_UTC_P1000_VLADIVOSTOK                                    TZ_ASIA_VLADIVOSTOK                 // (UTC+10:00) Vladivostok
#define TZ_UTC_P1030_LORD_HOWE_ISLAND                               TZ_AUSTRALIA_LORD_HOWE              // (UTC+10:30) Lord Howe Island
#define TZ_UTC_P1100_BOUGAINVILLE_ISLAND                            TZ_PACIFIC_BOUGAINVILLE             // (UTC+11:00) Bougainville Island
#define TZ_UTC_P1100_CHOKURDAKH                                     TZ_ASIA_SREDNEKOLYMSK               // (UTC+11:00) Chokurdakh
#define TZ_UTC_P1100_MAGADAN                                        TZ_ASIA_MAGADAN                     // (UTC+11:00) Magadan
#define TZ_UTC_P1100_NORFOLK_ISLAND                                 TZ_PACIFIC_NORFOLK                  // (UTC+11:00) Norfolk Island
#define TZ_UTC_P1100_SAKHALIN                                       TZ_ASIA_SAKHALIN                    // (UTC+11:00) Sakhalin
#define TZ_UTC_P1100_SOLOMON_IS_NEW_CALEDONIA                       TZ_PACIFIC_GUADALCANAL              // (UTC+11:00) Solomon Is., New Caledonia
#define TZ_UTC_P1200_ANADYR_PETROPAVLOVSK_KAMCHATSKY                TZ_ASIA_KAMCHATKA                   // (UTC+12:00) Anadyr, Petropavlovsk-Kamchatsky
#define TZ_UTC_P1200_AUCKLAND_WELLINGTON                            TZ_PACIFIC_AUCKLAND                 // (UTC+12:00) Auckland, Wellington
#define TZ_UTC_P1200_COORDINATED_UNIVERSAL_TIME_12                  TZ_PACIFIC_TARAWA                   // (UTC+12:00) Coordinated Universal Time+12
#define TZ_UTC_P1200_FIJI                                           TZ_PACIFIC_FIJI                     // (UTC+12:00) Fiji
#define TZ_UTC_P1245_CHATHAM_ISLANDS                                TZ_PACIFIC_CHATHAM                  // (UTC+12:45) Chatham Islands
#define TZ_UTC_P1300_COORDINATED_UNIVERSAL_TIME_13                  TZ_PACIFIC_ENDERBURY                // (UTC+13:00) Coordinated Universal Time+13 
#define TZ_UTC_P1300_NUKU_ALOFA                                     TZ_PACIFIC_TONGATAPU                // (UTC+13:00) Nuku'alofa
#define TZ_UTC_P1300_SAMOA                                          TZ_PACIFIC_APIA                     // (UTC+13:00) Samoa
#define TZ_UTC_P1400_KIRITIMATI_ISLAND                              TZ_PACIFIC_KIRITIMATI               // (UTC+14:00) Kiritimati Island

#endif


class ITimeZoneDSTRange {
public:
    ITimeZoneDSTRange() {};
    virtual ~ITimeZoneDSTRange() {};

    virtual class ITimeZone * TimeZone() = 0;
    virtual long64 RangeStart() = 0;
    virtual long64 RangeEnd() = 0;
};


class ITimeZone {
protected:
    virtual ~ITimeZone() {}
public:
    virtual const char * TimeZoneName() = 0;
    virtual const char * UTCName() = 0;
    virtual long64 UTCDiff() = 0;
    virtual long64 DSTDiff() = 0;
    virtual long64 ToLocalTime(long64 utcTime) = 0;
    virtual long64 ToUTCTime(long64 localTime) = 0;
    virtual long64 RemoveDST(long64 timeStamp) = 0;
    virtual long64 AddDST(long64 timeStamp) = 0;
    virtual bool IsDST(long64 timeStamp, bool isLocalTime = false) = 0;
    virtual bool IsDST(ITimeZoneDSTRange * dstRange, long64 timeStamp, bool isLocalTime = false) = 0;
    virtual ITimeZoneDSTRange * GetDSTRange(long64 rangeStartDate, long64 rangeEndDate) = 0;
};


class ITimeZoneProvider {
public:
    static ITimeZone * GetTimeZone(const char * tzid, class IInstanceLog * const log);
};
