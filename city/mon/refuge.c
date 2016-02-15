inherit MonsterCode;
void extra_create()
{
    set_name( "Esmeralda, THE WERECROC" );
    add_alias( "esmeralda" );
    add_alias( "werecroc" );
    add_alias( "croc" );
    set_short( "Esmeralda, THE WERECROC" );
    set_long( "This croc apparently used to be a person. Either that or it " 
      "has taken to wearing tattered labcoats for fun. It's huge a huge purple "
      "and pink beast with a massive jaw. It looks to be about fifty feet long "
      "from snout to tail. Looking at her teeth you realize if she gets a bite of "
      "you, you're probably done for!" );
    set_gender( "female" );
    set_race( "beast" );
    set_alignment( 0 );
    set_stat( "str", 500 + random( 50  ) );
    set_stat( "con", 500 + random( 70  ) );
    set_stat( "wil", 500 + random( 90  ) );
    set_stat( "dex", 300 + random( 100 ) );
    set_type( "piercing" );
    set_max_hp( 800000 );
}
