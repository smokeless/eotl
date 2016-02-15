#include <ansi.h>

inherit ObjectCode;

extra_create()
{
   set( "id", ({ "sign", "spraypainted sign", "plywood sign",
     "the sign", "no tresspassing sign", "spraypaint sign",
     "a 'no tresspassing' sign spraypainted on plywood",
     "a no tresspassing sign spraypainted on plywood", 
     "ner traaspasng sign" "traaspasng sign",  }) );
   set( "short", "a 'ner traaspasng' sign spraypainted on plywood" );
   set( "ansi_short", HIR "a 'ner traaspasng' sign spraypainted "
     "on plywood" NORM );
   set( "long",
     "This fine sign was hand crafted by... just kidding.  It's just "
     "a cheap, splintering, thin piece of plywood.  And the elegant "
     "caligra..... nah just kidding, its just red spraypaint.  Its "
     "message is pretty clear, however.  'NER TRAASPASNG!$!@# "
     "HILLFOLK ONLY!$!@#!$@#!!!'"
   );
   set( "gettable", 0 );
   set( "droppable", 1 );
   set( "weight", 5000000000 );
   set( "value", 0 );
}
