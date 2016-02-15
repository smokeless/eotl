#include <facility.h>;

inherit NewThingCode;

void extra_create()
{
    set_ids( ({ "flier", "pamphlet" }) );
    
    set_short( "a pamphlet on psychic research" );
    set_ansi_short( BLU "a pamphlet on psychic research" );
    
    set_long( "There is a happy looking family romping "
      "in a field of flowers on the cover. It is titled "
      "\"Psychic Research: A better tomorrow\". Perhaps "
      "you should read it." );
}

void extra_init()
{
    add_action( "pamph", "read" );
}

int pamph( string arg )
{
    if( !stringp( arg ) || ( member( query_ids(), arg ) == -1 ) )
      return notify_fail( CAP( query_verb() ) + " what?\n" );
    
    
    tell_player( THISP, "Facility 31 is dedicated to the exploration "
      "of the possible continuation after death of personality and "
      "consciousness. Facility 31 research and educational activities "
      "include studies of expanded states of consciousness, out-of-body "
      "experiences, mediumship, meditation, near death experiences, " 
      "and violent or non violent haunting disturbances.\n" );
    
    return 1;
}

