#include <forest.h>

inherit NewThingCode;
inherit AnsiTellCode;

void extra_create()
{
    set_ids( ({ "egg", "black egg", "pulsating", "pulsating egg", 
      "pulsating black egg" }) );
    
    set_short( "a pulsating black egg" );
    set_ansi_short( HIK "a pulsating black egg" );
    
    set_long( "The egg pulsates as you look at it. "
      "The shell appears to be a thick skin like "
      "membrane. Thick veins run up and down the "
      "shell, carrying nutrition to whatever is "
      "inside. The air around the egg is very warm. "
      "A scientist would probably examine this specimen." );      
   
    set_gettable( 0 );
}

void extra_init()
{
    add_action( "examine", "examine" );
}

int examine( string arg )
{
    if( !stringp( arg ) || arg != "egg" )
      return notify_fail( "What are you trying to examine?\n" );
    int x = random( 300 );
    if( x > 200 )
    {
      ansi_tell( THISP, "The egg pulsates and becomes more active "
        "as you get closer to it. You can see some sort of squid "
        "like creatures inside.\n", BLU  );
      ansi_tell_room( ENV( THISP ), sprintf( "%s examines an egg.\n",
        THISP->query_name() ), BLU, ({ THISP }) );
      return 1;
    }
    
    ansi_tell( THISP, "The egg pulsates and becomes more active "
        "as you get closer to it. Suddenly it bursts! You are covered "
        "in fluid. You can feel tiny slimy creatures crawling all over "
        "you. They burrow under your skin.\n", 
        BLU  );
    ansi_tell_room( ENV( THISP ), sprintf( "%s examines an egg. It "
      "bursts, %s is showered with disgusting fluid. You notice small "
      "squid like creatures burrowing into %s skin.\n", 
      THISP->query_name(), subjective( THISP ), possessive( THISP ) ), 
      BLU, ({ THISP }) );
    
    object shad;
    
    shad = clone_object( FSHAD "eggshad" );
    shad->sh_init( THISP );
    
    THISP->take_damage( random( 40 ), 0, "piercing", THISO );
    destruct( THISO );
    return 1;
}    
