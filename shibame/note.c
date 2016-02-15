#include <facility.h>;

inherit NewThingCode;

void extra_create()
{
    set_ids( ({ "note", "postit", "post it" }) );
    set_short( "a Post-It note" );
    set_ansi_short( HIY "a Post-It note" );
    set_long( "There is some hastily scrawled "
      "writing on this note. Perhaps you should "
      "read it." );
    set_weight( 25 );
}

void extra_init()
{
    add_action( "read", "read" );
}

int read( string arg )
{
    if( !stringp( arg ) || arg != "note" )
      return notify_fail( CAP( query_verb() ) + " what?\n" );
    
    if( THISP->query_skill( "read languages" ) < 1 )
    {
      tell_player( THISP, "Whoever wrote this note was in a hurry, "
        "so it is very difficult to make out what it says. The gist of "
        "it seems to be that interns have been leaving early and "
        "it is hard to get ahold of them.\n" );
      
      return 1;
    }
    
    tell_player( THISP, "I don't know what is going on, " 
      "everyone is so friendly here, but there's something "
      "strange behind it. I don't know what happened to the "
      "people who started working with me. When I "
      "started there were fifteen other interns. Now "
      "there are just four. I know they didn't quit "
      "or return to the city. No one they know seems "
      "to have heard from them. I suspect something "
      "is happening in the restricted area. Hopefully "
      "nothing happens to me. But in case something "
      "does, maybe this note will shed some light onto "
      "what it may have been.\n"
      "-M\n" );
    
    return 1;
}
