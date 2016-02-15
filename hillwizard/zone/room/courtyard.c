#include <ansi.h>
#include <hillwizard.h>

inherit RoomPlusCode;

void extra_create()
{
    set( "short", "A courtyard full of broken down cars" );
    set( "ansi_short" , HIB "A courtyard full of broken down cars" NORM );
    set( "day_long" ,
      "Most people would plant a nice lawn and some shade trees, along "
      "with nice flowers and maybe even a bench, but not hillbilles.  "
      "This giant courtyard is being used primarily as a parking lot "
      "for cars that will likely never run again.  Just inside the gate "
      "to your south, the courtyard lies before The Wartzhog Institute "
      "of Spellflingery.  From here you can truly admire the craftsmanship "
      "of the academy.  And that is to say, it is a wonder that the building "
      "is even capable of standing.  It is leaning slightly to the left.  "
      "Architecturally, the building is even more astonishing... as it is "
      "clearly a cement foundation and lumber supports and sheetrock and "
      "plaster and all the rest, but for some reason it looks exactly like "
      "a gigantic trailer."
    );
    set( "day_light" , 100 );
    set( "night_light", 50 );
    set( OutsideP, 1 );
    set( "exits" , 
      ([
        "north" : ZROOM "foyer", //needs a door
        "south" : "@go_south", 
//needs a function for gate opening automatically as you leave
      ])
    );
    set( "reset_data" ,
      ([
      ])
    );
    set( "descs" ,
      ([
        "gate" : "The wrought iron gate is nothing particularly special, but it "
          "does look sturdy.",
        "cars" : "Fords, GMs, Mopars... nothing but a bunch of american steel and "
          "rust.  There is no way any of these cars will ever run again, but they "
          "sure do make nice lawn ornaments?  I guess?",
        "wartzhog" : "*building",
        "building" : "Before you lies The Wartzhog Institute of Spellflingery.  "
          "You cannot imagine why it was designed to resemble a trailer...",
      ])
    );
}

mixed go_south()
{
    tell_player( THISP, "The compound's gate opens automatically "
      "as you approach it." );
    return ZROOM "frontgate";
}
