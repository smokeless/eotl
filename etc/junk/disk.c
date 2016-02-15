inherit NewThingCode;

#include <facility.h>

void extra_create()
{
    set_ids( ({ "disk", "floppy", "floppy disk" }) );
    set_short( "a floppy disk" );
    set_ansi_short( sprintf( "%sa floppy disk", YEL ) );
    set_long( "This disk is a dark yellow color, it "
      "is chipped here and there. It looks like it has "
      "been recycled many times. Where there should be "
      "a label, there is simply a coffee stain." );
    set_value( 3 );
    set_weight( 2 );
}
     
