#include <facility.h>

inherit RoomPlusCode;

void extra_create()
{
    int time = random( 400 ) + 1;
    
    set( "short", "The Facility 31 Intern Room" );
    set( "ansi_short", YEL "The Facility 31 Intern Room" NORM );
      
    set( "day_long", "This room is very different from the rest of the "
      "facility. The environment feels very friendly and relaxed. "
      "Motivational posters line the walls and the lights are "
      "brighter. Speakers in the corner of the room play upbeat pop music. "
      "The scent of incense hangs lightly in the air. Pushed up against "
      "the walls there are cots for the interns to nap on. You can see "
      "office space to the south." );
    
    set( "day_light", PART_LIT );
    
    set( InsideP, 1 );
    set( NoTeleportP, 1 );
    
    set( "exits", 
    ([
      "south" : FROOM "office"
    ]) );
    
    set( "descs", 
    ([
      ({ "poster", "posters" }) :   "They seem to all share the "
                                    "same theme, simple phrases "
                                    "to uplift simple people. You "
                                    "could read one.",
      ({ "speaker", "speakers" }) : "Bose, looks like someone "
                                    "has contacts in Eternal. ",
      ({ "cot", "cots" }) : "They look very comfortable, and inviting. "
                            "A short nap couldn't hurt anyone or anything, "
                            "could it?",
    ]) );
    
    set( "reset_data",  
    ([
      "intern" : FMONS "intern",
      "intern1" : FMONS "intern",
      "intern2" : FMONS "intern",
      "intern3" : FMONS "intern"                 
    ]) );
    call_out( "below", time );
}

void extra_init()
{
    add_action( "sleepingidiot", "nap" );
    add_action( "sleepingidiot", "sleep" );
    add_action( "posters", "read" );
}

int posters( string arg )
{
    if( arg != "poster" && arg != "posters" )
      return 0;
    string which;
    switch( random( 3 ) )
    {
      case 0 : which = "Nothing is predestined: The obstacles of your past " 
                       "can become the gateways that lead to new beginnings."; break;
      case 1 : which = "If we all did the things we are capable of doing, "
                       "we would literally astound ourselves.";                break;
      case 2 : which = "Nothing worthwhile comes easily. Work, continuous "
                       "work and hard work, is the only way to accomplish "
                       "results that last.";                                   break;
    }
    tell_player( THISP, sprintf( "You read one of the posters. It says: %s", which ) );
    return 1;
}


int sleepingidiot( string arg )
{
    string hero = THISP->query_name();
    
    if( !stringp( arg ) || arg != "on cot" )
      return notify_fail( CAP( query_verb() ) + " on what?\n" );
      
    tell_room( THISO, sprintf( "%s lays down on the cot for a nice nap. "
      "Inky black tendrils reach up from under the blankets covering %s "
      "body. There is a slurping sound and %s is gone.\n", hero, 
      possessive( THISP ), hero ), ({ THISP }) );
    
    tell_player( THISP, "You decide it's time to rest your tired bones. " 
    "You've earned it!" );
    
    THISP->move_player( "&&", FROOM "dream", 1 );
    load_object( FROOM "dream" )->start( THISP );
    
    return 1;
}

void below()
{
    int time = random( 500 + 1 );
    
    tell_room( THISO, "A voice booms over the speakers: \"Calling any "
      "available intern to come down below. I could use some help "
      "with something.\"\n" );
    
    call_out( "below", time );
}
