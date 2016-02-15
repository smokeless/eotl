#include <facility.h>

inherit ArmorCode;
string *boostem;

void extra_create()
{    
    set_ids( ({ "doll", "porcelain doll", "old doll" }) );
    set_short( "an old doll" );
    set_ansi_short( sprintf( "%san old doll%s", RED, NORM ) );
    set_long( "The porcelain has dulled off the face " 
      "of this well loved toy. Where there was once "
      "red blush, there is simply a bland greyish "
      "surface covered in pock marks and cracking. "
      "The eyes have long since fallen out leaving "
      "deep black holes where they belong. The cheaply "
      "made canvas body is charred and blackened "
      "however still mostly intact. Someone has "
      "threaded a fishing hook with some very fine "
      "filament through the doll. Seems like it would "
      "make a nice necklace."
    );

    set_local_ac( "neck", 2 );
    set_base_ac( 4 );
    set_droppable( 0 ); 
    set( NoStoreP, 1 );
    set_weight( 300 );
    set_value( 480 );
 
    set_material( "organic" );
    
    



}

string post_short( object looker )
{ 
//Thanks Poi, and thanks for the explanation.    
    string lname;
    if( objectp( looker ) )
      lname = CAP( looker->query_real_name() );
    else
      lname = "you";
    return sprintf( " <(consuming %s)> %s", lname, ::post_short( looker ) );
}

int try_wear( object wearer )
{    
  
    if( wearer->query_stat( "wil" ) +
        wearer->query_stat( "str" ) <= 250 )
    return 1;
    
    return 0;
}
    
void post_wear( object wearer )
{
    string playn = wearer->query_real_name();
/*   resists = ([ 
      "asphyxiation" : wearer->query_resistance( "asphyxiation" ),
      "blunt" : wearer->query_resistance( "blunt" ),
      "cold" : wearer->query_resistance( "cold" ),
      "corrosive" : wearer->query_resistance( "corrosive" ),
      "crushing" : wearer->query_resistance( "crushing" ),
      "disease" : wearer->query_resistance( "disease" ),
      "drain" : wearer->query_resistance( "drain" ),
      "edged" : wearer->query_resistance( "edged" ),
      "electric" : wearer->query_resistance( "electric" ),
      "energy" : wearer->query_resistance( "energy" ),
      "fire" : wearer->query_resistance( "fire" ),
      "holy" : wearer->query_resistance( "holy" ),
      "magic" : wearer->query_resistance( "magic" ),
      "magic_cold" : wearer->query_resistance( "magic_cold" ),
      "magic_elec" : wearer->query_resistance( "magic_elec" ),
      "magic_fire" : wearer->query_resistance( "magic_fire" ),
      "piercing" : wearer->query_resistance( "piercing" ),
      "poison" : wearer->query_resistance( "poison" ),
      "psionic" : wearer->query_resistance( "psionic" ),
      "psychic" : wearer->query_resistance( "pyschic" ),
      "sonic" : wearer->query_resistance( "sonic" ),
      "unholy" : wearer->query_resistance( "unholy" ),
    ]);
*/
    int *resists;
    string *resist;
    resists = ({ wearer->query_resistance( "asphyxsiation" ),
      wearer->query_resistance( "blunt" ),
      wearer->query_resistance( "cold" ),
      wearer->query_resistance( "corrosive" ),
      wearer->query_resistance( "crushing" ),
      wearer->query_resistance( "disease" ),
      wearer->query_resistance( "drain" ),
      wearer->query_resistance( "edged" ),
      wearer->query_resistance( "electric" ),
      wearer->query_resistance( "energy" ),
      wearer->query_resistance( "fire" ),
      wearer->query_resistance( "holy" ),
      wearer->query_resistance( "magic" ),
      wearer->query_resistance( "magic_cold" ),
      wearer->query_resistance( "magic_elec" ),
      wearer->query_resistance( "magic_fire" ),
      wearer->query_resistance( "piercing" ),
      wearer->query_resistance( "poison" ),
      wearer->query_resistance( "psionic" ),
      wearer->query_resistance( "psychic" ),
      wearer->query_resistance( "sonic" ),
      wearer->query_resistance( "unholy" ),
    });
    resist = ({ "asphyxsiation", "blunt", "cold", "corrosive",
      "crushing", "disease", "drain", "edged", "electric",
      "energy", "fire", "magic", "holy", "magic_cold", "magic_elec",
      "piercing", "poison", "psionic", "psychic", "sonic", "unholy"
    });
    int saveresist = random( sizeof( resist ) );
    int numberboost = resists[saveresist];
    string nameof = resist[saveresist];
    write_file( FARMOR "thosepast", sprintf("%s\n", playn ) );
    write_file( FARMOR "thosepast", sprintf("%s\n", nameof ) );
    write_file( FARMOR "thosepast", sprintf("%d\n", numberboost ) );
    boostem = grab_file( FARMOR "thepresent" );
    wearer->add_bonus_object( THISO );            
}

int query_resist_bonus( string arg, int much )
{
    much = to_int( boostem[2] );
    if( arg == boostem[1] ) return much;
}
   

void post_remove( object wearer ) 
{
    rename( FARMOR "thosepast", FARMOR "thepresent");
    wearer->remove_bonus_object( THISO );
    
}



