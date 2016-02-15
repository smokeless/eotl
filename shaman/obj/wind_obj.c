/*
This object is given to the player when
the wind attack on imbue shield goes off.
Taplash 2014
*/
#include <ansi.h>
inherit NewThingCode;
inherit AnsiTellCode;

object shaman;
int skill;

void extra_create()
{
    set_id( "wind_obj" );
    set_gettable( 0 );
    set_droppable( 0 );
    set( NoStoreP, 1 );
    set( NoContainP, 1 );
    set( NoSellP, 1 );
    set( DestOnDeathP, 1 );
    set_value( 0 );
    set_weight( 0 );
    set( InvisP, 1 );
} 

int start_bonus( object person, int i )
{
    shaman = person;
    shaman->add_bonus_object( THISO );
    skill = i;
    call_out( "go_away", 3 );    
}

void go_away()
{   
   ansi_tell( shaman, "You slow down.", CYAN );
   shaman->remove_bonus_object( THISO );
   destruct(THISO);
}

int query_stat_bonus( string arg )
{
    if( ENV( THISO ) != shaman )
    {
      call_out( "go_away", 1 );
      return 0;
    }

    if( arg == "dex" )
      return( skill * 2 / 3 );

    return 0;
}

int query_skill_bonus( string arg )
{
    if( ENV( THISO ) != shaman )
    {
        call_out( "go_away", 1 );
        return 0;
    }

    if( arg == "dodge" ) return( skill * 2 + random( skill ) );
    if( arg == "flee" ) return( skill * 2 + random( skill ) );

    return 0;
}
