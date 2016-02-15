#include <ansi.h>

inherit ArmorCode;

void extra_create()
{
    set_ids( ({ "necklace", "green necklace", "a green necklace",
        "Shibame necklace", "green Shibame necklace" }) );
    set_short( "a green necklace" );
    set_ansi_short( GRN "a green necklace" );
    set_long( "This looks to be a very simple necklace made of "
        "braided green leather. The leather is very soft, and the "
        "lacing is tight. Someone has spent considerable time "
        "making this necklace. There is a little tag dangling " 
        "near the rear knot of the necklace. It reads 'Shibame.' " );
    set_base_ac( 1 );
    set_weight( 10 );
    set_value( 100 );
    set_material( "leather" );
    set_areas( ({ "neck" }) );
}

int try_wear( object wearer )
{
    string *allowed = ({ "shibame, zzshibame", "taplash" });
    if( !member( allowed, THISP->query_real_name() ) )
    {
      tell_player( THISP, "This is not for you.\n" );
      return 1;
    }
    tell_player ( THISP , "A-Ok. Here's your necklace.\n" );
    return 0;
}
