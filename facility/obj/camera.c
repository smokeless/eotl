#include <facility.h>

inherit NewThingCode;
inherit PropertyCode;

void extra_create()
{
    set_ids( ({ "camera", "security camera", "nano security camera"}) );
    
    set_short( "a nano security camera [running]" );
    set_ansi_short( GRN "a nano security camera [running]" );
    
    set_long( "This tiny little ball is a security camera. A red LED "
      "blinks on top of it. Clearly it is currently recording. You "
      "wonder how long the battery life is." );      
    set_weight( 1 );
    set( "alive", 1 );
    call_out( "change", 500 );
}

int change()
{
    set_short( "a nano security camera [barely running]" );
    set_ansi_short( YEL "a nano security camera [barely running]" );
    set_long( "This tiny little ball is a security camera. A yellow LED "
      "blinks on top of it. Clearly it is currently recording. You "
      "wonder how long the battery life is." );
    call_out( "die", 200 );
    return 1;
}

int die()
{
    tell_room( ENV( THISO ), "The LED on the security camera dies.\n" );
    set_short( "a dead nano security camera" );
    set_ansi_short( RED "a dead nano security camera" );
    set_long( "This tiny little ball is a security camera. There is a dead LED on top "
      "of it. It has completely ceased functioning." );
    set( "alive", 0 );
    return 1;
} 
