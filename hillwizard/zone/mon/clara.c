// hill wizard skill trainer  -arphen 03182015
// needs special attacks to emulate guild skills

#include <ansi.h>
#include <hillwizard.h>

inherit MonsterCode;
inherit SpecialAttackCode;
inherit AnsiTellCode;

void extra_create()
{
    object ob;

    set_name(  "Clara Duggin" );
    add_alias( "duggin" );
    add_alias( "clara duggin" );
    add_alias( "clara" );
    add_alias( "spellflinger" );
    add_alias( "head spellflinger" );
    set_short( "Clara Duggin, Head Spellflinger" );
    set_long(
      "Little Clara Duggin sure did sprout up like a weed.  She's "
      "only about 17 now, but good golly has she... developed.  "
      "She ain't too bright, but she's likely the brightest here "
      "at Wartzhog.  She's actually become so proficient at spell "
      "flingery, that she's been promoted to Head Flinger!  She'll "
      "be able to train you up somethin' fierce, should you be "
      "willin' to listen!."
    );

    set_race( "human" );
    set_gender( "female" );
    set_alignment( 200 );

    set_stat( "str",  800 );
    set_stat( "int",  250 );
    set_stat( "wil", 1000 );
    set_stat( "con", 1000 );
    set_stat( "dex",  400 );
    set_stat( "chr", 5000 ); // because... dem titties?
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
