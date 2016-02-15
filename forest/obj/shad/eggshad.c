#include <forest.h>

inherit AnsiTellCode;

object victim;

status sh_init( object ob )
{
    victim = ob;
    shadow( victim, 1 );
    call_out( "noise", random( 100 ) );
    call_out( "vomit", 300 );
}

void noise()
{
    int dam = random( 60 );
    ansi_tell_room( ENV( victim ), sprintf( "%s squirms uncomfortably, "
      "you think you can see something moving under %s skin.\n",
      victim->query_name(), possessive( victim ) ), RED, ({ victim }) );
    
    ansi_tell( victim, "You can feel something moving around "
      "under your skin, picking at your insides.\n", RED );
    
    victim->take_damage( dam, 0, "piercing", THISP );
}

void vomit()
{
    int dam = victim->query_hp() - 10;
    ansi_tell_room( ENV( victim ), sprintf( "%s looks extremly sick. "
      "%s face turns extremely pale. %s stomach rips open and spills out "
      "a disgusting black egg.\n", victim->query_name(),
      CAP( possessive( victim ) ), CAP( possessive( victim ) ) ),
      RED, ({ victim }) );
    
    ansi_tell( victim, "You feel horribly sick. There is a sharp "
      "pain as your stomach opens up and spills out a disgusting "
      "black egg.\n", RED );
    
    victim->take_damage( dam, 0, "piercing", victim );
    
    move_object( clone_object( FOBJ "egg" ), ENV( victim ) );
    
    call_out( "kill_shad", 1 );
}

void kill_shad()
{
    remove_shadow( THISO );
    destruct( THISO );
}
