#include <tomb.h>
inherit NewThingCode;

object me;
int countdown = 4;

void extra_create()
{
    set_ids( ({ "trap", "wall", "stone wall", "moving", 
      "section", "moving wall", "section of wall", "stone", 
      "piece", "piece of stone" }) );
    set_short( "a gigantic piece of moving wall" );
    set_long( "This huge piece of stone is rumbling across "
      "the room. It looks large enough that it could crush "
      "anyone in its path. It also looks like once it "
      "completes its journey across the floor this "
      "entrance will be sealed." );
    set_gettable( 0 );
    set_droppable( 0 );
    set_value( 0 );
}

void start( object guy )
{
    me = guy;
    tell_room( ENV( THISO ), "A giant piece of stone "
      "lurches out of the wall and begins sealing the "
      "room" );
    call_out( "c1", 1, me );
    return;
}
void c1( object who )
{
    me = who;
    tell_room( ENV( THISO ), "The stone grinds the floor "
      "as it fills the room.\n" );
    if( countdown > 0 )
    {
      call_out( "c1", 3 );
      --countdown;
      return;
    }
      call_out( "death", 1, me );
    return;
}

void death( object who )
{
    object room1 = to_object( ROOM "traphall4" );
    object room  = to_object ( ROOM "traphall2" );
    me = who;
    
    tell_room( ENV( THISO ), "The stone crushes you as it seals "
      "the hall!\n" );
    object *inv = filter_array( all_inventory( ENV( THISO ) ), #'living );
    int i = sizeof( inv );
    while( i-- )
    {
      inv[ i ]->DeathSequence( THISO, "crushed to death!" );
    }
    room->clear_exits();
    room1->clear_exits();
    call_out( "dest", 20 ); //86400 = 2 days.
    return;
}

void dest()
{
   object room1 = to_object( ROOM "traphall4" );
   object room  = to_object ( ROOM "traphall2" );
   room->fix();
   room1->fix();
   destruct( THISO );
}
