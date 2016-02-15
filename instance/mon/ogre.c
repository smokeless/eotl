inherit "/obj/races/bodies/humanoid";

void setup_race()
{
    set_race_name( "Ogre" );
    set_help( strformat(
        "Though the toughest of the civilized races, dwarves are short "
        "and stocky with a ruddy complexion and much hair.  Because of "
        "their great constitution and willpower, dwarves are resistant "
        "to both magic and poison." ) );
    set_hand_name( "hand" );
    set_stat( "str", 11, 90 );
    set_stat( "int", 9,  105 );
    set_stat( "wil", 12, 80 );
    set_stat( "con", 13, 85 );
    set_stat( "dex", 8,  110 );
    set_stat( "chr", 8,  110 );
    set_max_base_ac( 8 );
    add_resistance( "poison", 25 );
    add_resistance( "disease", 25 );
    add_resistance( "magic", 25 );
    //Whatever your resistance to magic is, that's what it is.     
    add_resistance( "magic_fire", 25 );      
    add_resistance( "magic_elec", 25 );       
    add_resistance( "magic_cold", 25);
    set_free_points( 6 );
}
 
int query_skill_bonus( string arg, object stumpy )
{
    if( arg == "drinkin" )
        return( 5 );
    if( arg == "belch" )
        return( 5 );
    if( arg == "endurance" )
        return( 10 );
    if( arg == "detect traps" )
        return( 10 );
    if( arg == "hide" )
        return( -10 );
    if( arg == "stealth" )
        return( -10 );
 
    return( 0 );

}

//Shamelessly borrowed from goblins, the natural counter to dwarves.
//the denominator is lower to reflect the use of base_stat rather than 
//adjusted stat since +stat items are given out like fucking candy.
int query_proficiency_bonus( string arg, object stumpy )
{
    return( 1 + stumpy->query_base_stat( "dex" ) / 80 );
}  

//Changed to base_stat for max hp and intox; see above
int query_max_hp( object stumpy )
{
    return( ::query_max_hp( stumpy ) + stumpy->query_base_stat( "con" ) / 2 );
}

int query_max_intox( object stumpy )
{
    return( ::query_max_intox( stumpy ) + stumpy->query_base_stat( "con" ) );
}

int query_digestion_rate( object stumpy, int resting )
{
    return( 9 );
}

