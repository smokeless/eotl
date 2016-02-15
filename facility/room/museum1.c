#include <facility.h>

inherit RoomPlusCode;

void extra_create()
{
    set( "short", "The Facility 31 Museum" ); 
    set( "ansi_short", YEL "The Facility 31 Museum" );   
    
    set( "day_long", "This room used to contain many classified artifacts and "
      "a display of historical items. Now it contains a pile of trash. "
      "Blood soaked magazine shreds and glass have been tracked in and out of this room. "
      "There is no longer any sort of barrier preventing the viewing "
      "of artifacts. There are also no artifacts to see, just empty "
      "shelves. There is a fire burning in the center of the room. "
      "To west you can see the lobby. To the east the mirror "
      "has been broken, which explains all the glass." );
 
    
    set( "day_light", PART_LIT );
    set( InsideP, 1 );
    set( NoTeleportP, 1 );
    
     set( "descs",
    ([ 
      ({ "mirror", "glass" })                 : 
        "The glass on the ground is definitely from the mirror. "
        "Bits of the mirror remain intact and you can see another "
        "room behind them. You could probably climb through the mirror.",
      ({ "trash", "pile" })                   :
        "On closer inspection this isn't just a normal trash pile. "
        "It only contains flammable items. Junk food wrappers, dry "
        "magazines, and Facility 31 flyers.",
      ({ "shreds", "magazine", "magazines" }) :
        "These were also in the lobby. Someone has tracked them "
        "into this room. Probably while they were clearing out "
        "the artifacts.",
      ({ "shelf", "shelves" })                :
        "From the lack of dust on these shelves you can tell that they "
        "were once full. Someone or something took all of the artifacts."
    ]) );
    
    set( "reset_data" , 
    ([ 
      "fire"       : FOBJ "fire"
    ]) );
    
    set( "exits", 
    ([
      "west" : FROOM "lobby1"        
    ]) );
    
}

void extra_init()
{
    add_action( "climb", "climb" );
}

int climb( string arg )
{
    string hero = THISP->query_name();
    
    if( !stringp( arg ) || arg != "through mirror" )
      return notify_fail( CAP( query_verb() ) + " through what?\n" );
      
    tell_room( THISO, sprintf( "%s climbs through the broken mirror.\n", hero ),
      ({ THISP }) );
    
    tell_player( THISP, "You climb through the mirror." );
    
    THISP->move_player( "&&", FROOM "hidden", 1 );
    return 1;
}
