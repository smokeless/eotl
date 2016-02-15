#include <ansi.h>

inherit ObjectCode;

extra_create()
{
   set( "id", ({ "a small sign", "small sign",
     "sign", "meth sign", "meth room sign",  }) );
   set( "short", "a small sign" );
   set( "ansi_short", CYAN "a small sign" NORM );
   set( "long",
     "This sign will explain how to cook meth."
   );
   set( "gettable", 0 );
   set( "droppable", 1 );
   set( "weight", 5000000000 );
   set( "value", 0 );
}
