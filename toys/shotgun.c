void sh_init()
{
    shadow( THISP, 1 );  
    call_out( "blood", 3);
    call_out( "stumble", 5 );
    call_out( "dest_shad", 60 );
}

void dest_shad()
{  
    tell_player( THISP, "Your wounds stop bleeding.\n" ); 
    remove_shadow( THISO );
    destruct( THISO );
}

void blood()
{
    tell_player( THISP, "Your fresh shotgun wounds bleed." );
    tell_room( ENV( THISP ), sprintf( "%s groans as %s wounds "
      "bleed.\n", THISP->query_name(), possessive( THISP ) ),
      ({ THISP }) );
    call_out( "blood", random( 20 ) );
}

void stumble()
{
    string *places = m_indices( ENV( THISP )->query( "exits" ) );
    string dir = places[ random( sizeof( places ) ) ];
    tell_player( THISP, "You feel dizzy from the blood loss. You "
      "stumble.\n" );
    tell_room( ENV( THISP ), sprintf( "%s stumbles off dazed.\n", 
      THISP->query_name() ), ({ THISP }) );
    command( dir, THISP );
}
