inherit NewThingCode;

void extra_create()
{
    set_ids( ({ "suckerblind" }) );
    set( InvisP, 1 );
    set_gettable( 0 );
    set_droppable( 0 );
    call_out( "done", 400 );
}

void done()
{
    tell_player( THISP, "The world comes back into focus! "
      "You can see! It's a miracle!!!\n" );
    destruct( THISO );
}
    
extra_init()
{
    add_action( "do_look", "peer"      );
    add_action( "do_look", "look"      );
    add_action( "do_look", "glance"    );
    add_action( "do_look", "alertness" );
    add_action( "do_look", "inventory" );
}

int do_look( string arg )
{
    if( !living( ENV( THISO ) ) )
    {
      destruct( THISO );
      return 0;
    }
    tell_object( THISP, "You cannot see! You are completely blind!\n" );
    return 1;
}
