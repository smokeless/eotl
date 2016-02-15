// hill wizard shopkeep  -arphen 03182015

#include <ansi.h>
#include <hillwizard.h>

inherit MonsterCode;
inherit MonsterTalk;
inherit SpecialAttackCode;
inherit AnsiTellCode;

void extra_create()
{
    object ob;

    set_name(  "Junkbob" );
    add_alias( "junkbob" );
    add_alias( "johnson" );
    add_alias( "junkbob johnson" );
    add_alias( "Junkbob Johnson" );
    add_alias( "Honest Junkbob Johnson" );
    add_alias( "honest junkbob johnson" );
    add_alias( "honest junkbob" );
    add_alias( "honest johnson" );
    set_short( "'Honest' Junkbob Johnson... totally doesn't "
      "have meth supplies." );
    set_long(
      "Junkbob Johnson was born 'Cletus Montana,' but over the "
      "years people just sort of forgot his name.  Or perhaps they "
      "just forgot to care.  Either way, Junkbob's the man around "
      "these parts if you're looking for any sorta junk.  Good junk, "
      "bad junk, any kinda junk!  He's about six feet tall, skinny as "
      "a lamppost, and well, he's got about as many teeth as a lamppost, "
      "too.  What he lacks in teeth, he makes up for in mullet.  Junkbob "
      "himself isn't a Hill Wizard, but he's still a nice enough guy."
    );

    set_race( "human" );
    set_gender( "male" );
    set_alignment( 50 );

    set_stat( "str",  400 );
    set_stat( "int",   10 );
    set_stat( "wil",  400 );
    set_stat( "con",  400 );
    set_stat( "dex",  500 );
    set_stat( "chr",  100 );
    set_proficiency( "light flail", 80 );

    set_max_fatigue( 25000 );
    set_natural_ac ( 10 );
    set_skill( "dodge", 100 );
    set_percent_bonus_exp( -15 );

    add_special_attack( "mullet_twirl", THISO, 12 );

    set_chat_chance( 0 );
    set_chat_rate( 30 + random( 30 ) );

    add_phrase( "Junkbob coughs." );
    add_phrase( "Junkbob adjusts his mullet." );
    add_phrase( "Junkbob stares into space." );
    add_phrase( "Junkbob mutters something about Obamacare." );

    ob = clone_object( "/zone/present/hillbilly/obj/armor/overalls.c" );
      move_object( ob, THISO );
    ob = clone_object( ZOBJ "raccoon" );
      move_object( ob, THISO );

    call_out( "gear_up", 1 );
}

int gear_up()
{
    command( "equip" );
}

int mullet_twirl( object victim, object attacker )
{
    ansi_tell( victim, "Junkbob twirls around real fastlike, smackin' "
      "you right in the mouth with his long, wispy mullet.\nYou're not "
      "really sure why he would do that.  It seems to have done absolutely "
      "nothing of note.  Huh.", HIY );

    ansi_tell_room( ENV( attacker ), sprintf( "Junkbob twirls around real "
      "fastlike, smackin' %s right in the mouth with his long, wispy mullet.\n"
      "It seems to have done nothing, but boy was it glorious to witness!",
      victim->query_name() ), HIY );

    return 1;
}

query_resistance()
{
    return 40;
}
