/*
Salt grinder.
Taplash 2015
*/
inherit NewThingCode;

void extra_create()
{
    set_ids( ({ "salter", "salt grinder", "grinder" }) );
    set_short( "a salt grinder" );
    set_long( "This is an old beat up salt grinder. "
      "it doesn't seem to have any salt in it. There "
      "is some magical writing on the side. \"This will "
      "take a password and salt it. Example grind password seed\" "
      "It was probably made by some mad hat wizard in an evil "
      "lab." );
    set_value( 0 );
    set_weight( 0 );
}

void extra_init()
{
    add_action( "grind", "grind" );
}

int grind( string arg )
{
    string mod;
    if( !arg )
    {
      tell_player( THISP, "Looks like you didn't provide the proper "
        "argument. Go to the abuse room down the hall." );
    return 1;
    }
    mod = to_string( md5( arg ) );
    
    tell_player( THISP, "Grinding!" );
    tell_room( ENV( THISP ), sprintf( "%s grinds some salt.", THISP->query_name() ),
      ({ THISP }) );
    tell_player( sprintf( "Old Pass = %s\nNew Pass = %s", arg, mod ) );
    return 1;
}
