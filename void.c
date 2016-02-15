#include <ansi.h>

inherit RoomPlusCode;
inherit DoorCode;

void extra_create()
{
    set( "short", "A horrible void" ); 
//for players with no ansi
    set( "ansi_short" , HIK "A cold empty void" NORM );
//for players with ansi   
    set( "day_long" , "A void. There is nothing here. " 
         "There should never be anything here. "
         "This is the way of the void. The lights of "
         "the Golden Gate are off in the distance."
    );
set( "day_light", DARK );
set( "night_light", DARK );
    set( InsideP, 1 );
add_door( "workroom", "/usr/taplash/workroom", "/usr/taplash/bdoor" );
//set( NoWanderRoomP, 1 ); read later.
    set( "exits" , 
     ([
     ])
    );
    set( "reset_data" ,
     ([ 
       "dummy" : "/usr/poi/stuff/dummy.c",
//to clone dummy grab it here "dummy" : "/usr/skorch/open/dummy",
     ])
    );
    set( "descs" ,
     ([ 
     ])
   );
}
