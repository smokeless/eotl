#include <ansi.h>
inherit NewThingCode;
inherit AnsiTellCode;
int delay;

void extra_create()
{
    set_ids( ({ "fissure", "massive fissure" }) );
    set_short( "a massive fissue" );
    set_ansi_short( YEL "a massive fissure" );
    set_long( "The ground is cracking and "
      "chunking to bits. Cracks spread from "
      "the fissure like veins. The whole room "
      "is shaking!!!!!" );
    set_gettable( 0 );
    set_value( 0 );
}

void set_me_up( int quakestr, int quaketime )
{
    delay = quakestr;
    call_out( "shake", 1 );
    call_out( "go_away", quaketime );
    return;
}

void shake()
{
    object *ob;
    int x;

    ob = filter( all_inventory( ENV( THISO ) ), #'living );
    x = 0;
    
    while( x < sizeof( ob ) )
    {
      if( ob[x]->query_skill( "natural attunement" ) >
        random( 50 ) )
      {
        tell_player( ob[x], "Your natural attunement "
          "keeps you on your feet!" );
        x++;
        break;
      }
      tell_player( ob[ x ], "The ground shakes and you "
        "lose your footing!" );
      ob[ x ]->add_delay( delay );
      x++;
    }

    call_out( "shake", 7 );
}

int destruct_signal( object d, object a )
{
    while( find_call_out( "shake" ) != -1 )
      remove_call_out( "shake" );
    
    return 0;
}

void go_away()
{
    string change = ENV( THISO )->query( "day_long" );
    ansi_tell_room( ENV( THISO ), "The ground stops shaking.", 
      YEL, ({ }) );
    ENV( THISO )->set( "day_long", sprintf( "%s\nThe ground is "
      "cracked to pieces.", change ) );     
    destruct( THISO );
}
