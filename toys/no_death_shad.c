// No Death Shadow
// Watcher

// A single use shadow that will protect from a single death.  Upon
// death a player's combat will be reset and they will be transported
// to safety

inherit AnsiTellCode;
#include <ansi.h>
#define DEST "/zone/null/eternal/lounge/lounge"
object me;

int has_prevent_death_shadow() { return 1; }

void do_prevent_death(int time)
{
    tell_object(me,"You feel the protection of Karana surround you!\n");
    call_out("remove_prevent_death_shadow",time);
}
    
short()
{
    return me->short()+BLUE" [protected from death]"NORM;
}
sh_init(object who,int time)
{
    me = who;
    shadow( me, 1 );
    do_prevent_death(time);
}

void remove_prevent_death_shadow()
{
    ansi_tell(me,"Your protection from death fades.",BOLD_BLUE);
    remove_shadow(THISO);
    destruct(THISO);
}
int DeathSequence(object killer, string cause, status nocorpse)
{ 
    tell_object(me,sprintf(
        "The final blow lands but you do not die.  Instead you find "
        "yourself very much alive and in a safer place.\n"));
    tell_room(ENV(me),sprintf(
        "Just as %s is about to die, a mist surrounds %s and %s is "
        "gone!\n",me->query_name(),objective(me),subjective(me)),({me}));
    tell_room(DEST,sprintf(
        "%s arrives from a swirling mist!\n",me->query_name()),({me}));
    me->full_heal();
    me->reset_combat();
    move_object(me,DEST);
    remove_prevent_death_shadow();
    return 0;
}
