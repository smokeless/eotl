inherit "/obj/races/bodies/amorphous_body";

void setup_race()
{
    set_race_name( "gum beast" );
    set_help( strformat( "A horrible thing " 
      "created in a lab." ) );
    add_resistance("poison", 100);  
    add_resistance("cold", -35);   
    add_resistance("disease", -100);  
}
