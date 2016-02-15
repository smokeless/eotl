// hill wizard prof trainer  -arphen 03182015
// needs special attacks to emulate guild skills

#include <ansi.h>
#include <hillwizard.h>

inherit MonsterCode;
inherit SpecialAttackCode;
inherit AnsiTellCode;

void extra_create()
{
    object ob;

    set_name(  "Chester" );
    add_alias( "chester" );
    add_alias( "uncle chester" );
    add_alias( "uncle" );
    add_alias( "master of arms" );
    add_alias( "hill wizard master of arms" );
    set_short( "Uncle Chester, Hill Wizard Master of Arms" );
    set_long(
      "Remember that jovial old man who helps teach young boys "
      "how to properly use and care for their weapons on every "
      "TV show ever?  Well, that's Uncle Chester.  He's a kind "
      "middle aged man with time to spare.  He also happens to "
      "know a whole lot about weaponry!  And by that, I mean "
      "even moreso than your average hillbilly."
    );

    set_race( "human" );
    set_gender( "male" );
    set_alignment( 500 );

    set_stat( "str",  800 );
    set_stat( "int",  250 );
    set_stat( "wil", 1000 );
    set_stat( "con", 1000 );
    set_stat( "dex",  400 );
    set_stat( "chr",  250 );
    set_skill( "dodge", 100 );
    set_proficiency( "hands", 50 );

    set_max_fatigue( 25000 );
    set_natural_ac ( 10 );
    set_percent_bonus_exp( -25 );

    ob = clone_object( "/zone/present/hillbilly/obj/armor/overalls.c" );
      move_object( ob, THISO );

    call_out( "gear_up", 1 );
}

int gear_up()
{
    command( "equip" );
}

query_resistance()
{
    return 25;
}
