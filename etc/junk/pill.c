#include <facility.h>

inherit NewThingCode;

void extra_create(){
    set_ansi_short( sprintf( "%sa pill", BOLD_GREEN ) );
    set_short( "a pill" );
    set_long(
      "This pill is neon green and, "
      "seems to call out to be taken. "
      "You can feel energy radiating "
      "out from it. As you roll it "
      "around in your palm you wonder "
      "where it might have come from. "
    );
    set_ids( ({ "a pill", "pill", "green pill" }) );
    set( NoStoreP, 1 ); 
    set_weight( 1 );
    set_value( 20 );
}

void extra_init(){
    add_action( "drugged", "take" );
    add_action( "drugged", "ingest" );
    add_action( "drugged", "eat" );
}

int drugged(string strarg){
    
    object hero = ENV( THISP );

    if( ENV(THISO) != THISP )
      {
        return 0;
      }
    if ( !stringp( strarg ) || ( member( query_ids(), strarg ) == -1 ))
      {
        return notify_fail( CAP( query_verb() ) + " what?\n" );
      } 
    tell_object( THISP, "You throw the pill into your mouth, "
      "before you can begin to chew it "
      "slides down your throat.\n You "
      "feel a bit tired." );

    
    tell_room( hero, sprintf( "%s's eyes widen, as if in a trance.\n", 
      THISP->query_name() ), ({THISP}) 
    );
    if( ENV ( THISP )->query( NoTeleportP) ||
        ENV ( THISP )->query( NoTeleportOutP ) )
      {
        tell_object( THISP, "These surroundings are "
           "too distracting for you to become "
           "fully entranced."
        );
        destruct(THISO);
        return 1;
      }
    else
      {
        tell_object( THISP, "You are grasped by cold hands and pulled "
          "through the ether." );
        tell_room( hero, sprintf( "Suddenly a pair of hands reach out "
          "from the ether and pull %s in!\n",
          objective(THISP) ), ({THISP})
        );
        
        THISP->move_player( "&&", FROOM "pit", 1 );
        tell_room( ENV( THISP ), sprintf( "%s smashes to the ground.\n",
          THISP->query_name() ), ({THISP}) );
        tell_object( THISP, "Everything about you hurts "
          "your skin stings as you take in your new "
          "environment.");

        destruct(THISO);
      }

   return 1;
}
 
 

    

