object person;

void sh_init( object m )
{
    person = m;
    shadow( m, 1 );  
    call_out( "blood", 3);
    call_out( "stumble", 5 );
    call_out( "dest_shad", 60 );
}

void dest_shad()
{  
    tell_player( person, "Your wounds stop bleeding.\n" ); 
    remove_shadow( person );
    destruct( THISO );
}

void blood()
{
    tell_player( person, "Your fresh shotgun wounds bleed." );
    tell_room( ENV( person ), sprintf( "%s groans as %s wounds "
      "bleed.\n", person->query_name(), possessive( person ) ),
      ({ person }) );
    call_out( "blood", random( 20 ) );
}

void stumble()
{
    if( THISP->query_resting() == 1 )
    {
      command( "stand", THISP );
    }
    string *places = m_indices( ENV( person )->query( "exits" ) );
    string dir = places[ random( sizeof( places ) ) ];
    tell_player( person, "You feel dizzy from the blood loss. You "
      "stumble.\n" );
    tell_room( ENV( person ), sprintf( "%s stumbles off dazed.\n", 
      person->query_name() ), ({ person }) );
    command( dir, person );
    call_out( "stumble", random( 10 ) );
}
