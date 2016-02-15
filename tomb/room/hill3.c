#include <tomb.h>

inherit RoomPlusCode;
inherit AnsiTellCode;

int searched = 0;
void extra_create()
{
    set( "ansi_short", HIK "On a rocky hill."  );
    set( "short", "On a rocky hill." );
    set( "day_long", "Before you is a low, flat topped hill "
      "ugly weeds, thorns, and briars grow upon the steep "
      "sides and bald lop of the tall mound. There are lots of black "
      "rocks on the top of the hill." );
    set( "day_light", 30 );
    
    set( InsideP, 1 );
    set( NoTeleportP, 1);
    
    set( "exits", ([
      "southwest" : ROOM "hill1",
      "west" : ROOM "hill2" ]) );

    set( "descs", 
    ([ 
      ({ "rocks", "rock", "black rocks" }) : "They appear to form the shape of "
                                             "a grinning skull.",
        
      ({ "weeds", "thorns", "briars" }) : "Looks like there hasn't been a "
                                          "landscaper here in a long time.",
    ]) );
}

int search( string arg )
{
    string name = THISP->query_name();
    if( THISP->query_stat( "int" ) < 100 )
    {
      tell_player( THISP, "You wouldn't know where to start." );
      return 1;
    }
    
    tell_player( THISP, "You search around and discover some shifty "
      "ground. You dig a little bit and find a way down." );
    tell_room( ENV( THISP ), sprintf( "%s searches around and finds "
      "a way down.", name ), ({ THISP }) );
    set( "exits", ([ 
      "down" : ROOM "ent",
      "southwest" : ROOM "hill1",
      "west" : ROOM "hill2" 
    ]) );
    if( searched = 1 )
      call_out( "fix", 60 );
    return 1;
}

void fix()
{
    searched = 0;
    set( "exits", ([
    "southwest" : ROOM "hill1",
    "west" : ROOM "hill2" ]) );
    return;
}
