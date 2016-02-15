// hill wizard trophy guard  -arphen 03182015
// needs magic guild spell powahs

#include <ansi.h>
#include <hillwizard.h>

inherit MonsterCode;
inherit SpecialAttackCode;
inherit AnsiTellCode;

void extra_create()
{
    set_name(  "Wartz Hog" );
    add_alias( "wartz" );
    add_alias( "hog" );
    add_alias( "wartz the hog" );
    add_alias( "wartz hog" );
    add_alias( "wartz the magic hog" );
    add_alias( "wartz the magic battle hog" );
    add_alias( "wartz the battle hog" );
    add_alias( "wartz the battle-hog" );
    set_short( "Wartz the Magic Battle-Hog" );
    set_long(
      "Oh yes.  OOOOoohhhhhhh yes, the hillbillies named their "
      "acamedy of higher learning after this, their prize winning "
      "hogasaurus-rex, Wartz.  Wartz is one of the biggest, baddest "
      "hogs in all the land, and rumor has it he's even been known "
      "to fling a few spells in his day.  Watch yoself!"
    );

    set_race( "human" );
    set_gender( "male" );
    set_alignment( -50 );

    set_stat( "str", 1000 );
    set_stat( "int",  250 );
    set_stat( "wil", 1000 );
    set_stat( "con", 1500 );
    set_stat( "dex",  600 );
    set_stat( "chr",  250 );
    set_skill( "dodge", 250 );
    set_proficiency( "pig-fu", 50 );

    set_max_fatigue( 25000 );
    set_natural_ac ( 10 );
    set_percent_bonus_exp( -25 );

}

query_resistance()
{
    return 40;
}
