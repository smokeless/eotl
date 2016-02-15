inherit "/obj/races/bodies/demon_body";

void setup_race()
{
    set_race_name(  "Angel of Decay" );
    add_resistance( "poison", 100 );  
    add_resistance( "disease", 100 );
    add_resistance( "psychic", 100 );
    add_resistance( "holy", -50 );  
}
