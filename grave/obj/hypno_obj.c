inherit NewThingCode;

short()
{
    return 0;
}

void extra_init() 
{
    add_action( "do_nothing", "unequip"   );
    add_action( "do_nothing", "unwield"   );
    add_action( "do_nothing", "mswing"    );
    add_action( "do_nothing", "drink"     );
    add_action( "do_nothing", "drain"     );
    add_action( "do_nothing", "quaff"     );
    add_action( "do_nothing", "rest"      );
//    add_action( "do_nothing", "quit"   );
    add_action( "do_nothing", "read"      ); 
    add_action( "do_nothing", "sit"       );
    add_action( "do_nothing", "eat"       );
    add_action( "do_nothing", "look"      );
    add_action( "do_nothing", "west"      );
    add_action( "do_nothing", "east"      );
    add_action( "do_nothing", "north"     );
    add_action( "do_nothing", "south"     );
    add_action( "do_nothing", "southwest" );
    add_action( "do_nothing", "northwest" );
    add_action( "do_nothing", "southeast" );
    add_action( "do_nothing", "southwest" );
    add_action( "do_nothing", "kill"      );
}

int do_nothing( string arg )
{
    tell_player( THISP, sprintf( "You are entranced by the ramblings "
      "of the ghost!\n" ) );
    return 1;
}

void setup( int time )
{
    int death = random( 100 ) + 100 - time;
    call_out( "die", death );
}

void die()
{
   destruct( THISO );
}
