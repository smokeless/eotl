/*
    Trance shadow. Helps shaman heal.
    They are stuck sitting while this happens.
    In the meantime they gain hp, mana, and ftg.
    In accordance with their skill.
      Socialism 2012
*/

inherit AnsiTellCode;
#include <ansi.h>
#define TRANCEOBJ "/usr/socialism/shaman/obj/trance_obj"

object tranceob;
object shaman;
int skill;
int time;

sh_init( object sh, int sk )
{
    shaman = sh;
    skill = sk;
    time = 15;
    tranceob = clone_object( TRANCEOBJ );
    move_object( tranceob, shaman );
    shadow( shaman, 1 );
    call_out( "start", 1 );
}

string post_short()
{
    return( " (in a trance)" );
}

string title()
{
    return( shaman->query_title() + " (in a trance)" );
}

void start()
{
    ansi_tell( shaman, "Many colors float past your vision. "
      "The silence is beautiful.\n", CYAN );
    THISP->add_mana( skill + random( skill ) );
    THISP->add_hp( skill + random( skill ) );
    THISP->add_fatigue( skill + random( skill ) );
    call_out( "mid", time );
}

void mid()
{
    ansi_tell( shaman, "You can hear the voices of your "
      "ancestors. They are whispering and laughing.\n", CYAN );
    THISP->add_mana( skill + random( skill ) );
    THISP->add_hp( skill + random( skill ) );
    THISP->add_fatigue( skill + random( skill ) );
    call_out( "end", skill );      
}

void end()
{
    ansi_tell( shaman, "You feel something pulling you out of your "
      "trance! The voices are getting farther away! You are ripped "
      "back to the harshness of reality.\n", CYAN );
    ansi_tell_room( ENV( shaman ), sprintf( "%s lets out a pitiful "
      "whine as %s returns back to reality.\n", shaman->query_name(),
      subjective( shaman ) ), CYAN, ({ shaman }) );
    THISP->add_mana( skill + random( skill ) );
    THISP->add_hp( skill + random( skill ) );
    THISP->add_fatigue( skill + random( skill ) );
    call_out( "kill_shad", 1 );
}    

void kill_shad() 
{ 
    destruct( transob );
    remove_shadow( THISO );
    destruct( THISO );
}
