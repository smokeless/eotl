/*
This thing does different things depending on
the function you call in it. Mainly using it
to add generic population to places. Will continue
working on it as time permits.

get_male() gets a male name
get_female() gets a female name
sex() gets a sex
race() gets a race from /obj/races/
alignment() gives an alignment int
toughness() random toughness
desc() gives a pretty dull description for the monster

Taplash 2014
*/

#include <sys/strings.h>

string sex()
{
    string s;
    if( !random( 2 ) )
      return( "female" );
    else
      return "male";
}

string get_male()
{    
    int n;
    string *names = ({ "Abaet", "Abarden", "Aboloft", "Acamen", 
      "Achard", "Ackmard", "Adeen",  "Aerden", "Afflon", "Aghon",
      "Agnar",  "Ahalfar",  "Ahburn",  "Ahdun",  "Aidan",  "Airen",  
      "Airis",  "Albright",  "Aldaren",  "Alderman",  "Aldren",  "Alkirk",  
      "Allso",  "Amerdan",  "Amitel",  "Anfar",  "Anumi",  "Anumil",  "Asden",  
      "Asdern",  "Asen",  "Aslan",  "Atar",  "Atgur",  "Atlin",  "Auchfor",  
      "Auden",  "Ault",  "Ayrie",  "Aysen",  "Bacohl",  "Badeek",  "Baduk",  
      "Balati",  "Baradeer",  "Barkydle",  "Basden",  "Bayde",  "Beck",  "Bedic",  
      "Beeron",  "Bein",  "Beson",  "Besur",  "Besurlde",  "Bewul",  "Biedgar",  
      "Bildon",  "Biston",  "Bithon",  "Boal",  "Boaldelr",  "Bolrock",  "Brakdern",  
      "Breanon",  "Bredere",  "Bredin",  "Bredock",  "Breen",  "Brighton",  "Bristan",  
      "Buchmeid",  "Bue",  "Busma",  "Buthomar",  "Bydern",  "Caelholdt",  "Cainon",  
      "Calden",  "Camchak",  "Camilde",  "Cardon",  "Casden",  "Cayold",  "Celbahr",  
      "Celorn",  "Celthric",  "Cemark",  "Cerdern",  "Cespar",  "Cether",  "Cevelt",  
      "Chamon",  "Chesmarn",  "Chidak",  "Cibrock",  "Cipyar",  "Ciroc",  "Codern",  
      "Colthan",  "Connell",  "Cordale",  "Cos",  "Cosdeer",  "Cuparun",  "Cusmirk",  
      "Cydare",  "Cylmar",  "Cythnar",  "Cyton",  "Daburn",  "Daermod",  "Dak",  
      "Dakamon",  "Dakkone",  "Dalburn",  "Dalmarn",  "Dapvhir",  "Darkboon",  
      "Darkkon",  "Darko",  "Darkspur",  "Darmor",  "Darpick",  "Dasbeck",  "Dask",  
      "Deathmar",  "Defearon",  "Derik",  "Derrin",  "Desil",  "Dessfar",  "Dinfar",  
      "Dismer",  "Doceon",  "Dochrohan",  "Dokoran",  "Dorn",  "Dosoman",  "Drakoe",  
      "Drakone",  "Drandon",  "Drit",  "Dritz",  "Drophar",  "Dryden",  "Dryn",  "Duba",  
      "Dukran",  "Duran",  "Durmark",  "Dusaro",  "Dyfar",  "Dyten",  "Eard",  "Eckard",  
      "Efamar",  "Efar",  "Egmardern",  "Eiridan",  "Ekgamut",  "Eli",  "Elik",  "Elson",  
      "Elthin",  "Enbane",  "Endor",  "Enidin",  "Enoon",  "Enro",  "Erikarn",  "Erim",  
      "Eritai",  "Escariet",  "Espardo",  "Etar",  "Etburn",  "Etdar",  "Ethen",  "Etmere",  
      "Etran",  "Eythil",  "Faoturk",  "Faowind",  "Fearlock",  "Fenrirr",  "Fetmar",  
      "Feturn",  "Ficadon",  "Fickfylo",  "Fildon",  "Firedorn",  "Firiro",  "Floran",  
      "Folmard",  "Fraderk",  "Fronar",  "Fydar",  "Fyn",  "Gafolern",  "Gai",  
      "Galain",  "Galiron",  "Gametris",  "Gauthus",  "Gemardt",  "Gemedern",  
      "Gemedes",  "Gerirr",  "Geth",  "Gib",  "Gibolock",  "Gibolt",  "Gith",  
      "Gom",  "Gosford",  "Gothar",  "Gothikar",  "Gresforn",  "Grimie",  
      "Gryn",  "Gundir",  "Gustov",  "Guthale",  "Gybol",  "Gybrush",  
      "Gyin",  "Halmar",  "Harrenhal",  "Hasten",  "Hectar",  "Hecton",  
      "Heramon",  "Hermenze",  "Hermuck",  "Hezak",  "Hildale",  "Hildar",  
      "Hileict",  "Hydale",  "Hyten",  "Iarmod",  "Idon",  "Ieli",  "Ieserk",  
      "Ikar",  "Ilgenar",  "Illilorn",  "Illium",  "Ingel",  
      "Ipedorn",  "Irefist",  "Ironmark",  "Isen",  "Isil",  
      "Ithric",  "Jackson",  "Jalil",  "Jamik",  "Janus",  
      "Jayco",  "Jaython",  "Jesco",  "Jespar",  "Jethil",  
      "Jex",  "Jib",  "Jibar",  "Jin",  "Juktar",  "Julthor",  
      "Jun",  "Justal",  "Kafar",  "Kaldar",  "Kellan",  "Keran",  
      "Kesad",  "Kesmon",  "Kethren",  "Kib",  "Kibidon",  "Kiden",  
      "Kilbas",  "Kilburn",  "Kildarien",  "Kimdar",  "Kinorn",  
      "Kip",  "Kirder",  "Kodof",  "Kolmorn",  "Kyrad",  "Lackus",  
      "Lacspor",  "Laderic",  "Lafornon",  "Lahorn",  "Laracal",  
      "Ledale",  "Leit",  "Lephar",  "Lephidiles",  "Lerin",  "Lesphares",  
      "Letor",  "Lidorn",  "Lin",  "Liphanes",  "Loban",  "Lox",  "Ludokrin",  
      "Luphildern",  "Lupin",  "Lurd",  "Macon",  "Madarlon",  "Mafar",  
      "Marderdeen",  "Mardin",  "Markard",  "Markdoon",  "Marklin",  "Mashasen",  
      "Mathar",  "Medarin",  "Medin",  "Mellamo",  "Meowol",  "Merdon",  "Meridan",  
      "Merkesh",  "Mesah",  "Mes'ard",  "Mesophan",  "Mesoton",  "Mezo",  "Michael",  
      "Mick",  "Mickal",  "Migorn",  "Milo",  "Miphates",  "Mi'talrythin",  "Mitar",  
      "Modric",  "Modum",  "Mudon",  "Mufar",  "Mujarin",  "Mylo",  "Mythik",  "Mythil",  
      "Nadeer",  "Nalfar",  "Namorn",  "Naphates",  "Neowyld",  "Nidale",  "Nikpal",  
      "Nikrolin",  "Niktohal",  "Niro",  "Noford",  "Nothar",  "Nuthor",  "Nuwolf",  
      "Nydale",  "Nythil",  "O�tho",  "Ocarin",  "Occelot",  "Occhi",  "Odaren",  
      "Odeir",  "Ohethlic",  "Okar",  "Omaniron",  "Omarn",  "Orin",  "Ospar",  
      "Othelen",  "Oxbaren",  "Padan",  "Palid",  "Papur",  "Peitar",  "Pelphides",  
      "Pender",  "Pendus",  "Perder",  "Perol",  "Phairdon",  "Phemedes",  
      "Phexides",  "Phoenix",  "Picon",  "Pictal",  "Picumar",  
      "Pildoor",  "Pixdale",  "Ponith",  "Poran",  "Poscidion",  
      "Prothalon",  "Puthor",  "Pyder",  "Qeisan",  "Qidan",  
      "Quiad",  "Quid",  "Quiss",  "Qupar",  "Qysan",  "Radag'mal",  
      "Randar",  "Raysdan",  "Rayth",  "Reaper",  "Resboron",  "Reth",  
      "Rethik",  "Rhithik",  "Rhithin",  "Rhysling",  "Riandur",  "Rikar",  
      "Rismak",  "Riss",  "Ritic",  "Rogeir",  "Rogist",  "Rogoth",  
      "Rophan",  "Rulrindale",  "Rydan",  "Ryfar",  "Ryfar",  "Ryodan",  
      "Rysdan",  "Rythen",  "Rythern",  "Sabal",  "Sadareen",  "Safilix",  
      "Samon",  "Samot",  "Sasic",  "Scoth",  "Scythe",  "Secor",  "Sed",  
      "Sedar",  "Senick",  "Senthyril",  "Serin",  "Sermak",  "Seryth",  
      "Sesmidat",  "Seth",  "Setlo",  "Shade",  "Shadowbane",  "Shane",  
      "Shard",  "Shardo",  "Shillen",  "Silco",  "Sildo",  "Sil'forrin",  
      "Silpal",  "Sithik",  "Soderman",  "Sothale",  "Staph",  "Stenwulf",  
      "Steven",  "Suktor",  "Suth",  "Sutlin",  "Syr",  "Syth",  "Sythril",  
      "Talberon",  "Telpur",  "Temil",  "Temilfist",  "Tempist",  "Teslanar",  
      "Tespar",  "Tessino",  "Tethran",  "Thiltran",  "Tholan",  "Tibers",  
      "Tibolt",  "Ticharol",  "Tilner",  "Tithan",  "Tobale",  "Tol�Solie",  
      "Tolle",  "Tolsar",  "Toma",  "Tothale",  "Tousba",  "Towerlock",  
      "Tuk",  "Tuscanar",  "Tusdar",  "Tyden",  "Uerthe",  "Ugmar",  "Uhrd",  
      "Undin",  "Updar",  "Uther",  "Vaccon",  "Vacone",  "Valkeri",  
      "Valynard",  "Vectomon",  "Veldahar",  "Vespar",  "Vethelot",  
      "Victor",  "Vider",  "Vigoth",  "Vilan",  "Vildar",  "Vinald",  
      "Vinkolt",  "Virde",  "Voltain",  "Volux",  "Voudim",  "Vythethi",  
      "Wak�dern",  "Walkar",  "Wanar",  "Wekmar",  "Werymn",  "Weshin",  
      "William",  "Willican",  "Wilte",  "Wiltmar",  "Wishane",  "Witfar",  
      "Wrathran",  "Wraythe",  "Wuthmon",  "Wyder",  "Wyeth",  "Wyvorn",  
      "Xander",  "Xavier",  "Xenil",  "Xex",  "Xithyl",  "Xuio",  "Y�reth",  
      "Yabaro",  "Yepal",  "Yesirn",  "Yssik",  "Yssith",  "Zak",  "Zakarn",  
      "Zecane",  "Zeke",  "Zerin",  "Zessfar",  "Zidar",  "Zigmal",  "Zile",  
      "Zilocke",  "Zio",  "Zoru",  "Zotar",  "Zutar",  "Zyten" });
    
    n = random( sizeof( names ) );
    return names[n];
}

string get_female()
{
    int n;
    string *names = ({ "Acele", "Acholate", "Ada", "Adiannon", 
      "Adorra", "Ahanna", "Akara", "Akassa", "Akia", "Amaerilde", 
      "Amara", "Amarisa", "Amarizi", "Ana", "Andonna", "Ani", 
      "Annalyn", "Archane", "Ariannona", "Arina", "Arryn", 
      "Asada", "Awnia", "Ayne", "Basete", "Bathelie", "Bethe", 
      "Brana", "Brianan", "Bridonna", "Brynhilde", "Calene", 
      "Calina", "Celestine", "Celoa", "Cephenrene", "Chani", 
      "Chivahle", "Chrystyne", "Corda", "Cyelena", "Dalavesta", 
      "Desini", "Dylena", "Ebatryne", "Ecematare", "Efari", 
      "Enaldie", "Enoka", "Enoona", "Errinaya", "Fayne", "Frederika", 
      "Frida", "Gene", "Gessane", "Gronalyn", "Gvene", "Gwethana", 
      "Halete", "Helenia", "Hildandi", "Hyza", "Idona", "Ikini", 
      "Ilene", "Illia", "Iona", "Jessika", "Jezzine", "Justalyne", 
      "Kassina", "Kilayox", "Kilia", "Kilyne", "Kressara", "Laela", 
      "Laenaya", "Lelani", "Lenala", "Linovahle", "Linyah", "Lloyanda", 
      "Lolinda", "Lyna", "Lynessa", "Mehande", "Melisande", "Midiga", 
      "Mirayam", "Mylene", "Nachaloa", "Naria", "Narisa", "Nelenna", 
      "Niraya", "Nymira", "Ochala", "Olivia", "Onathe", "Ondola", 
      "Orwyne", "Parthinia", "Pascheine", "Pela", "Peri�el", 
      "Pharysene", "Philadona", "Prisane", "Prysala", "Pythe", 
      "Q�ara", "Q�pala", "Quasee", "Rhyanon", "Rivatha", "Ryiah", 
      "Sanala", "Sathe", "Senira", "Sennetta", "Sepherene", 
      "Serane", "Sevestra", "Sidara", "Sidathe", "Sina", 
      "Sunete", "Synestra", "Sythini", "Szene", "Tabika", "Tabithi", 
      "Tajule", "Tamare", "Teresse", "Tolida", "Tonica", "Treka", "Tressa", 
      "Trinsa", "Tryane", "Tybressa", "Tycane", "Tysinni", "Undaria", 
      "Uneste", "Urda", "Usara", "Useli", "Ussesa", "Venessa", "Veseere", 
      "Voladea", "Vysarane", "Vythica", "Wanera", "Welisarne", "Wellisa", 
      "Wesolyne", "Wyeta", "Yilvoxe", "Ysane", "Yve", "Yviene", "Yvonnette", 
      "Yysara", "Zana", "Zathe", "Zecele", "Zenobia", "Zephale", "Zephere", 
      "Zerma", "Zestia", "Zilka", "Zoura", "Zrye", "Zyneste", "Zynoa" });
    
    n = random( sizeof( names ) );
    return names[n];
}

string race()
{
    string r, trimmed;
    string *races = get_dir( "/obj/races/*.c" );
    int n;
    n = random( sizeof( races ) );
    r = races[n];
    trimmed = trim( r, 2, ".c" );
    if( trimmed == "lich" )
      return "human";
    else
      return trimmed;
}

int alignment()
{
    if( !random( 2 ) )
      return random( 4000 );
    else
      return -random( 4000 );
}

int toughness()
{
    return random( 300 );
}
    
string desc()
{
    string *eyes = ({ "light blue", "pale blue", "blue", 
      "dark blue", "light silver", "pale silver", "dark silver",
      "light green", "dark green", "pale green", "light brown",
      "pale brown", "dark brown" });
    string *height = ({ "short", "tall", "rather short", "rather tall",
      "average height" });
    string *build = ({ "thick", "thin", "gaunt", "heavy", "muscular", 
      "medium" });
    string *skin = ({ "tan", "pale", "dark" });
    string *hairstyle = ({ "mulleted", "curly", "long", "shoulder length",
      "fine" });
    string *haircolor = ({ "black", "brown", "blonde", "red", "auburn",
      "grey" });
    
    string *face = ({ "oval", "thick", "thin", "rotund", "boney" });
    
    string *job = ({ "They are covered in flour! They must be pretty heavy into "
      "baking.", "They are covered in dirt, and smell moldy.", "Their hands are "
      "extremely calloused. They must use them a lot.", "They smell faintly of "
      "yeast, and their clothes are stained with beer.", "They walk with a bad "
      "limp." });
    
    return sprintf( "This person has %s eyes, %s %s hair, and "
      "a %s face. Their skin is a %s color. They are %s for their "
      "race. They have a %s build. %s", eyes[ random( sizeof( eyes ) ) ], 
      hairstyle[ random( sizeof( hairstyle ) ) ], 
      haircolor[ random( sizeof( haircolor ) ) ], 
      face[ random( sizeof( face ) ) ], skin[ random( sizeof( skin ) ) ], 
      height[ random( sizeof( height ) ) ], build[ random( sizeof( build ) ) ], 
      job[ random( sizeof( job ) ) ] );
} 
