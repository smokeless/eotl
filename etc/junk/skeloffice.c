inherit RoomPlusCode;

#include <facility.h>

void extra_create()
{
    set( "short", "Skelaf's Office" ); 
    set( "ansi_short" , sprintf( "%sSkelaf's Office", HIK) );   
    set( "day_long" , "Pieces. That's what it looks like "
      "it looks like someone built this office from "
      "pieces of other offices. Wood paneling clashing "
      "against modern flat black metal. The whole thing "
      "is a mish mash of design. An office for the post "
      "apocolyptic man, or woman. Whoever is in charge "
      "after something like that. The air is filled with "
      "the smell of mildew. As you mill about you notice "
      "that the floor is built out of old soda bottles, "
      "well soda bottles, and various animal parts. "
      "There is an old 3.5 inch drive sitting on the desk."
    );
    set( "day_light", 30 );
    set( InsideP, 1 );
    set( NoTeleportP, 1);
    set( NoTeleportInP, 1 );
    set( NoTeleportOutP, 1 );
    set( "exits", 
      ([
//suckers!       
      ]) );
    set( "descs", 
      ([ "desk" : "It seems to be crafted out of plywood "
                  "and scrap metal.", 
         "drive" : "Seems like you could insert a "
                   "floppy disk into it.",
         "floor" : "Looks like the bottles aren't "
                   "held in place, you could probably "
                   "pull one out."
      ]) );
    set( "reset_data",  
      ([
        "skelaf" : FMONS "skelaf"
      ]) );
}

void extra_init()
{
    add_action( "insert", "insert" );
    add_action( "getmeout", "pull" );
}

int insert( string disk )
{
    object skelaf;
    object *disky = filter_objects( deep_inventory( THISP ),
      "id", "disk" );
    int diskysize = sizeof( disky );
    string hero = THISP->query_real_name();
    int hasdisk = 1;
    if( !stringp( disk ) || disk != "disk" )
    {
      return( notify_fail( "Insert what?\n" ) );
    }
    skelaf = query( "skelaf" );
    if( !skelaf || !present_clone( skelaf ) )
    {
      tell_player( THISP, "Doesn't make sense without someone here." );
      return 1;
    }
    if( hasdisk > diskysize )
    {
       tell_player( THISP, "You left your disk somewhere else!" );
       return 1;
    }
    if( hasdisk < diskysize )
    {
      tell_player( THISP, "Skelaf looks at you fumbling through your "
        "collection of disks. He walks over and grabs them from you "
        "throwing all of them in a drawer, aside from one. He nods at you "
        "to go ahead and insert it in the drive." );
      while( diskysize > 1 ) 
      destruct( disky[0] ); 
      --diskysize; 
      move_object( clone_object( FOBJ "disk" ), THISP );
      return 1;
    }
    tell_player( THISP, "You insert your disk in the floppy drive "
      "it comes to life with some clicking and whirring."
    );
    
    
    return 1;
}
