inherit "/zone/null/stuff/base/trap";

void extra_create()
{
    set( "trap_name", "a nerve gas trap" );
    add( "id", "nerve trap" );
    add( "id", "trap" );
    add( "id", "nerve" );
    set( "spawn_limit", 2 );
    set( "ready", 1 );
    set( "difficulty", 8 );
    set( "time_delay", 0 );
}

void effect( object tripper )
{
    object x = clone_object( "/usr/taplash/stuff/fhealth" );
    object vic = tripper;
    tell_room( ENV( THISO ), sprintf( "You hear a horrible "
      "hissing sound. It's gas escaping from a trap!" ), ({ vic }) );
    tell_player( vic, sprintf( "You just tripped a nerve gas trap!!!" ) );
    x->sh_init( vic );
}
