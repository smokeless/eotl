#include <forest.h>

inherit MonsterCode;
inherit AnsiTellCode;
inherit SpecialAttackCode;

object owner, stopper;
string ownername;

void extra_create()
{
    switch( random( 3 ) )
    {
      case 0 : 
      set_name( "A brown bear" );
      add_alias( "bear" );
      add_alias( "brown bear" );
      set_short( "a brown bear" );
      set_long( "Can brown bears climb trees? Or are they the " 
      "ones to run from?" ); break;
      case 1 :
      set_name( "A giant alligator" );
      add_alias( "giant alligator" );
      add_alias( "alligator" );
      set_short( "a giant alligator" );
      set_long( "So people really do flush alligators into the sewers." ); break;
      case 2:
      set_name( "An elephant" );
      add_alias( "elephant" );
      set_short( "an elephant" );
      set_long( "Seeing elephants might indicate too much drinking." ); break;
    }
}

void set_up( object o, string n )
{
    owner = o;
    ownername = n;
    
    tell_player( owner, "To get help on your exciting new pet type: "
      "pethelp\n" );
    /*
    stopper = clone_object( FOBJ "pet_obj" );
    move_object( stopper, owner );
    */
}

void heart_beat()
{
    if( ENV( THISP ) != ENV( owner ) )
    {
      move_object( THISP, ENV( owner ) );
    }
}
