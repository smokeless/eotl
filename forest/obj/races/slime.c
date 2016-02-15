inherit "/obj/races/bodies/amorphous_body";

void setup_race()
{
    set_race_name( "slime" );
    add_resistance( "poison", 100 );  
    add_resistance( "electric", -30 ); //slimes hate electricity.     
}
