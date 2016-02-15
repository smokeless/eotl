#include <ansi.h>
object me;

void sh_init( object arg )
{
    me = arg;
    shadow( me, 1 );
}

short()
{
     return( sprintf( "%s ", me->query_name() ) +RED+"( seasoned "
       "to perfection. )"+NORM );
}
