inherit NewThingCode;
#include <hillwizard.h>

object me;

void extra_create()
{
    int n = random( 7 );
    set_id( "meth_obj" );
    set_gettable( 0 );
    set_droppable( 0 );
    set( NoStoreP, 1 );
    set( NoContainP, 1 );
    set( NoSellP, 1 );
    set( DestOnDeathP, 1 );
    set("value", 0);
    set("weight", 0);
    set( InvisP, 1 );
} 

int set_up( object cook )
{
    object me = cook;
    me->add_bonus_object( THISO );
    tell_player( me, "Smokin' your meth sure is better than " 
      "drinkin' white lightnin'! It's damn fine." );
    call_out( "go_away", me->query_skill( "cook meth" * 20 ) );
}

void go_away()
{
   if( me )
   {
      tell_player( me, "The meth just wore off! You'd "
        "do anything to get some more!" );
      me->remove_bonus_object( THISO );
   }
   if( THISO )
     destruct( THISO );
}


int query_stat_bonus( string arg )
{
    int skill = me->query_skill( "cook meth" );
    if( !me )
    {
      call_out( "go_away", 1 );
      return 0;
    }
    
    if( arg == "str" )
        return(  ( skill / 2 ) + random( skill ) );
    
    if( arg == "dex" )
      return( ( skill / 2 ) + random( skill ) );
    
    return 0;
}
