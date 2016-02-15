// meth lab for hill wizard guild.  -arphen 03182015

#include <ansi.h>
#include <hillwizard.h>

inherit RoomPlusCode;

void extra_create()
{
    set( "short", "A Cozy, Well-Kept Meth Lab" );
    set( "ansi_short" , HIB "A Cozy, Well-Kept Meth Lab" NORM );
    set( "day_long" ,
      "This delightful kitchen looks fit for a TV cooking show.  "
      "Every surface of the kitchen is clean and well polished, "
      "and everything seems to be in its right place.  Even the "
      "lighting in here is excellent, despite the fact that there "
      "are no windows.  There are various vats and beakers and "
      "series of tubes and such all over the place."
    );
    set( "day_light" , SUNLIGHT );
    set( "night_light", SUNLIGHT );
    set( InsideP, 1 );
    set( "exits" , 
      ([
        "north" : ZROOM "hallway1" ,
      ])
    );
    set( "reset_data" ,
      ([
        "methsign" : ZOBJ "methsign",
        "paula" : ZMON "paula",
      ])
    );
    set( "descs" ,
      ([
        "floor" : "The floors are some sort of linoleum, "
          "and boy does it shine!",
        "glasswear" : "*beakers",
        "vat" : "*beakers",
        "vats" : "*beakers",
        "beakers" : "Everything looks to be of the absolute "
          "highest quality.",
      ])
    );
}

int query_enter_ok( object item, object mover )
{
    if( is_player( item ) && present_clone( ZMON "paula", THISO ) )
    {
      call_out( "methbaby", 2 );
    }
    return 0;
}

methbaby()
{
    object o = present_clone( ZMON "paula" );

    if( !o )              { return 1; }
    if( o->in_combat() )  { return 1; }

    command( "say HOWDY YA'LL!  Ya here to cook some meth?!", o );
    command( "oink", o );
    return 1;
}
