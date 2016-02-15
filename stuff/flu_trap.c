// A trap that gives players the flu!
// Taplash 2015

#include<ansi.h>
inherit "/zone/null/stuff/base/trap";
inherit AnsiTellCode;
#define FLU "/zone/null/stuff/support/flu_obj"

void extra_create()
{
    set( "trap_name", "a flu trap");
    add( "id", "trap");
    add("id", "flu");
    add("id", "flu trap");
    set( "spawn_limit", 3 );
    set( "difficulty", 8 );
    set( "ready", 1 );
    set( "hidden", 0 );
}

void effect( object tripper )
{
    object vic = tripper;
    if( !vic->is_player() )
        return;
    ansi_tell( vic, "You just stepped on a flu trap! It hoses "
      "you down with a solution of disgusting flu germs.", RED );
    ansi_tell_room( ENV( THISO ), sprintf( "%s just stepped on "
      "a flu trap! It sprays %s down with a solution of "
      "disgusting flu germs.", vic->query_name(), objective( vic ) ),
      RED, ({vic}) );
    if( vic->query_resistance( "disease" ) > random(60) )
    {
        ansi_tell( vic, "You resist the flu.", RED );
        return;
    }
    object sick = clone_object( FLU );
    move_object( sick, vic );
    sick->set_me_up( random( 300 ), vic );
    return;
}
