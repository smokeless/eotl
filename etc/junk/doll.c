#include <facility.h>

inherit NewThingCode;

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
      "threaded a fishing hook through the back of "
      "it. It seems like you could attach the doll "
      "to your armor." );
    set_descs( ([
      "eyes" :
      "The empty sockets seem to be watching you.\n"
    ]) );
//would put more here but arrays don't work in set_descs
    set_droppable( 0 ); 
    set( NoStoreP, 1 );
    set_weight( 300 );
    set_value( 40 );
    set_material( "organic" );
    
    
}
