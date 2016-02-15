#include <facility.h>
inherit NewThingCode;
inherit AnsiTellCode;


void extra_create() 
{
    int monstertime = random( 300 )+45;
    add_id( "177ob" );
    set( InvisP, 1 );
    call_out( "makeone", monstertime );
    set_gettable( 0 );
}

void makeone()
{
    object socialism = find_player( "socialism" );
    
    string *locations = get_dir( FROOM "*1.c" );
    object monster;
    object room = load_object( locations[ random( sizeof(
      locations) )] );
      
    tell_player( socialism, "Loaded random room." );
    
    int gotime = random( 300 ) + 4;
    if( monster = present_clone( FMONS "tent2.c", room ) )
    {
      tell_object( room, "The tendrils recede into the ground." );
      destruct( monster );
      call_out( "makeone", gotime );
      tell_player( socialism, "Tent already in this room.\n" );
      return;
    }
    move_object( clone_object( FMONS "tent2" ), room );
    tell_object( room, "Tendrils erupt from the ground!\n" );
    call_out( "makeone", gotime );
    tell_player( socialism, "Cloned a monster in a room." );
    return;
}
    
    
