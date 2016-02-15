#include <facility.h>

inherit NewThingCode;

void extra_create()
{
    set_ids( ({ "fire", "smoldering fire" }) );
    
    set_short( "a smoldering fire" );
    set_ansi_short( YEL "a smoldering fire" );
    
    set_long( "Even though the flame is not roaring this fire is "
      "still burning very hot. There is burnt paper at the bottom "
      "of it. Burning on top of the flame is charred skin, bones, "
      "and bits of living things that you've never seen before. Someone "
      "was burning the remains of the things that now roam this facility." );
    
    set_descs(
    ([ 
      ({ "flame", "flames" }) : 
        "It is not a raging flame. But it is still hot as hell.",
      ({ "paper", "papers" }) :
        "The way it burns it seems to be magazine paper. It gives off "
        "a touch of black smoke from the plastic coating.",
      ({ "skin", "bones", "things" }) :
        "The stink from these things burning is even worse than their looks."
    ]) );
    
    set_gettable( 0 );
}
