inherit MonsterCode;

void extra_create()
{
    set_name( "Anful" );
    
    add_alias( "anful" );
    add_alias( "featherstalk" );
    add_alias( "gnome" );
    add_alias( "anful featherstalk" );
    
    set_short( "Anful Featherstalk" );
    
    set_long( "temp" );
    
    set_gender( "male" );
    set_race( "gnome" );
    
    set_guild( "forester" );
    set_specialization( "ranger" );
    
    set_alignment( MALICIOUS_AL );
    
    set_stat( "str", 100 + random( 25 ) );
    set_stat( "con", 300 + random( 10 ) );
    set_stat( "wil", 300 );
    set_stat( "dex", 130 );
    
    set_proficiency( "light sword", 50 );
    set_proficiency( "hands", 100 );
    set_skill( "dodge", 65 );
    
    set( NoStealP, 1 );
    set( NoStunP, 1 );
    
    set_natural_ac( 10 );
    
    set_heal_rate( 30 );
    set_heal_amount( 6 );
}

void start_greet( object vag )
{
    call_out( "greet", 2, vag );
}   

void greet()
{  
    command( "say Well hello there! Name is "
      "Anful and cooking is the game! Though I do other "
      "things as well, run a bit of a curio shop. I also "
      "have my ear to all things ranger. So if you have "
      "any questions about rangers feel free to ask me!",
      THISO );
}
