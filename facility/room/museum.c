#include <facility.h>

inherit RoomPlusCode;

void extra_create()
{
    int board = random( 10 );
    set( "short", "The Facility 31 Museum" ); 
    set( "ansi_short", YEL "The Facility 31 Museum" );   
    
    set( "day_long", sprintf( "Contained within this room are "
      "artifacts from the past. All of them related in someway "
      "to magic or psychic phenomenon. Most of the artifacts "
      "are covered in an opaque barrier. Dust and grime has "
      "piled up over the years. Judging from the amount "
      "this place hasn't been cleaned in a long time. In the "
      "center of the room is the featured display. Near the display, " 
      "an illuminated button flickers. There is a mirror on "
      "the east wall. To the west you can see the lobby." ) );
    
    set( "day_light", PART_LIT );
    set( InsideP, 1 );
    set( NoTeleportP, 1 );
    
    set( "exits", 
    ([
      "west" : FROOM "lobby"        
    ]) );
    
    set( "descs",
    ([ 
    ({ "artifacts", "artifact", "barrier",  }) : 
      "There are shelves and shelves of items "
      "covered by a black barrier. It seems there "
      "are very few items classified for viewing. ",
 
    ({ "mirror", "wall" }) :
      "Looking in the mirror you discover that "
      "you are one sexy beast.",
    
    ({ "dust", "grime" }) :
      "Horrible filth. Someone should clean this place!",
    
    ({ "button" }) : 
      "A small taped on note underneath the "
      "button says, \"press to change display.\""
    ]) );
    set( "reset_data" , 
    
    ([ 
      "display"     : FOBJ  "display",
      "researcher"  : FMONS "midres",
      "researcher1" : FMONS "midres",
      "researcher2" : FMONS "midres",
      "researcher3" : FMONS "midres",
    ]) );

    if( board < 3 )
    {
      move_object( clone_object( FOBJ "board.c" ), THISO );
    }
}

void extra_init()
{
    add_action( "cleanup", "clean" );
    add_action( "cleanup", "tidy" );
    if( THISP && ( ENV( THISP ) == THISO ) )
      call_out( "dust", 1, THISP );
}

int cleanup( string arg )
{
    string hero = THISP->query_name();
    
    if( !stringp( arg ) || arg != "museum" )
      return notify_fail( CAP( query_verb() ) + " what?\n" );
    
    if( present_clone( FOBJ "keycardf", THISP ) )
    {
      tell_player( THISP, "You begin cleaning the museum. "
        "There is an awful lot of dirt and you make very "
        "little progress.");
      tell_room( THISO, sprintf( "%s begins to clean the "
        "museum up.\n", hero ), ({ THISP }) );
      return 1;
    }
    
    tell_room( THISO, sprintf( "%s begins to clean the museum up.\n", hero ),
      ({ THISP }) );
    tell_player( THISP, "You start to tidy up as best as you can, brushing "
      "dust off the opaque surfaces. You stoop low and notice a drawer out "
      "of place. It contains a stack of key cards. You quietly "
      "pocket one." );
    move_object( clone_object( FOBJ "keycardf" ), THISP );     
    return 1;
}

void dust( object player )
{
    int dust = random( 100 );
    if( dust < 20 )
    {
      command( "cough", player );
      tell_room( ENV( player ), "Must be the dust in the air. Someone "
        "should clean this place.\n" );
    }
}
