/*
Gargoyle race. 
--Socialism 2012
*/

inherit "/obj/races/bodies/winged_humanoid.c";
inherit "/obj/races/limbs/tail.c";

void setup_race()
{
    set_race_name( "Gargoyle" );
    
    set_help( "Gargoyles were the stony protectors of temples through out the world. " 
      "After many millennia guarding these buildings some of them took on a life of "
      "their own. Casting off the shackles of stone and their own immortality they "
      "now walk among the living. Gargoyles are not widely liked. Their faces "
      "are grotesque caricatures of beasts. Their bodies are lithe and well muscled. "
      "They retain their leathery wings, though they are vestigal at best. " 
      "They have an enormous amount of willpower after breaking free from "
      "their stone constraints. They have also maintained some of the knowledge "
      "from their millennia of guarding temples." );
    
    set_hand_name( "claw" );
    
    set_stat( "str", 13,  90 ); //They're big and heavy.
    set_stat( "con", 10,  100);
    set_stat( "wil", 15,  70 ); //Broke free from stone.
    set_stat( "chr", 4,   130 ); //Ugly as sin.
    set_stat( "dex", 7,   110 );  //Hard to be graceful.
    set_stat( "int", 13,  75 ); //Years listening at temples.
               
   
    add_resistance( "psychic", 25 ); //They're smart.
    add_resistance( "poison",  25 ); //Lots of wil, also used to be stone.
    
    set_max_base_ac( 10 );
    
    set_free_points( 5 );
}

string default_title( object player )
{
    return( "the Newly Free" );
}

void init_race()
{
    THISP->set( NightVisionP, "glowing eyes" );
    
    THISP->add_combat_message( "slash", "slashes" ); 
    THISP->add_combat_message( "rip",   "rips" );
    THISP->add_combat_message( "tear",  "tears" );
    THISP->add_combat_message( "bite",  "bites" );
}
    

int query_skill_bonus( string arg, object gargoyle )
{
    if( arg == "dodge" ) //Not the smoothest creatures.
      return( -15 );
    if( arg == "hide" ) //They're used to going unnoticed.
      return( 10 );
    if( arg == "Silvari" ) //Temples
      return( 5 );
    if( arg== "Grwrl" ) //They're animalistic as hell.
      return( 5 );
    
    return( 0 );
}

int query_digestion_rate( object gargoyle, int resting )
{
    return( 10 );
}
