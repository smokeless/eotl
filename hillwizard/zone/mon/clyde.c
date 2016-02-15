// hill wizard front gate guard  -arphen 03182015

#include <ansi.h>
#include <hillwizard.h>

inherit MonsterCode;
inherit SpecialAttackCode;
inherit AnsiTellCode;

void extra_create()
{
    object ob;

    set_name(  "Clyde Stillwater" );
    add_alias( "clyde" );
    add_alias( "stillwater" );
    add_alias( "clyde stillwater" );
    add_alias( "Clyde Stillwater" );
    set_short( "Clyde Stillwater" );
    set_long(
      "Clyde is definitely a good ol' boy.  And boy is he old.  "
      "He ain't no spring chicken, but what he has is old man "
      "strength.  He sure ain't much to look at, but people have "
      "been underestimating him for years, and hes still here, even "
      "if he ain't got no teeth left.  Rumor has it that Clyde is "
      "never goes anywhere without his close buddy Roscoe, but "
      "Roscoe ain't nowhere to be seen right meow."
    );

    set_race( "human" );
    set_gender( "male" );
    set_alignment( -50 );

    set_stat( "str",  800 );
    set_stat( "int",  250 );
    set_stat( "wil", 1000 );
    set_stat( "con", 3000 );
    set_stat( "dex",  400 );
    set_stat( "chr",  250 );
    set_skill( "dodge", 100 );
    set_proficiency( "hands", 50 );

    set_max_fatigue( 25000 );
    set_natural_ac ( 10 );
    set_percent_bonus_exp( -40 );

   add_special_attack( "call_sniper", THISO, 15 );

    ob = clone_object( "/zone/present/hillbilly/obj/armor/overalls.c" );
      move_object( ob, THISO );

    call_out( "gear_up", 1 );
}

int gear_up()
{
    command( "equip" );
}

int call_sniper( object victim, object attacker )
{
    int dmg = to_int( attacker->query_max_hp() / 4 );

    command( "say ROSCOE! TAKE THE SHOT!!!", attacker );
    command( "say TAKE IT NOOOOOOOOOOOW!!!", attacker );

    ansi_tell( victim, "You hear a BOOMING gunshot.\nA bullet "
      "hammers its way into your body! OOOOOOOOOWWWWWWWW!", HIR );

    ansi_tell_room( ENV( attacker ), sprintf( "Your hear a BOOMING "
      "gunshot.\n%s just got shot! You don't see the shooter.",
      victim->query_name() ), HIR, ({ victim }) );

     victim->take_damage( dmg, 0, "piercing", attacker );
}

query_resistance()
{
    return 25;
}
