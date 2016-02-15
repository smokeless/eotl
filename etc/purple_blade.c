/*
** This is the purple blade but given 2 magic - only for the knight
*/

#include <ansi.h>

inherit NewWeaponCode;
inherit SpecialAttackCode;

#define MYSHAD "/zone/fantasy/entesia/objects/shadows/purple_glow_sh"
#define INSIDE() ( ENV( ENV( THISO ))->query( InsideP ) ? "floor" : "ground" )

object shad;

void extra_create()
{
    set_ids( ({"purple blade","blade","sword"}) );
    set_short("a purple blade");
    set_ansi_short(MAG "a purple blade" NORM);
    set_long("This sword has a double edged blade that extends about \
3 feet.  In the hands of an experienced swordsman, it can be quite \
a deadly weapon because it's made out of a special purple steel \
which stays extremely sharp.  You note that this blade stands out " +
      "in that it has an internal purple glow to it.  The purple essense " +
      "of the blade seems specifically increased in this blade.\n" );
    set_limit(6); /* This is a test. Fugue 10/10/99 */
                  // A test for what?  And when is the test over? Cambot 6/11/00
    set_proficiency("light sword");
    set_base_damage(25);
    set_damage_step(7.5);
    set_base_speed(20);
    set_speed_step(9);
    set_prof_mod(6.5);
    set_fatigue_cost(1);

    //set("material","purple steel"); isn't steel steel regardless of color?
    set_material("steel");
    set_handed(1);
    set_damage_type("edged");

    add_combat_message( ({"slash","slashes"}) );
    add_special_attack( "purple_mist", THISO, 12 );
}

status purple_mist( object victim, object attacker )
{
    int dmg;
    string Vname, Aname;

    Vname = capitalize( (string)victim->query_name() );
    Aname = capitalize( (string)attacker->query_name() );
    if ( (int)attacker->roll_to_hit( victim, THISO ) > 0 ) {
	dmg = random( (int)attacker->query_stat( "str" ) / 5 ) * 2 + 3;
	tell_object( victim, Aname + "'s blade fills your mind with " +
	  "a purple haze!\nAs you are dazed, you feel a sword " +
	  "painfully slide into your body!\nYou scream in horror!\n" );
	tell_object( attacker, "Your blade develops a purple mist " +
	  "about it, then leaps out of your hand!\nIt sinks " +
	  "into " + Vname + "'s body!\nQuickly it returns to your hand.\n" );

	tell_room( environment( victim ), Aname + "'s blade glows " +
	  "with a purple haze.\nSuddenly the blade plunges itself " +
	  "into " + Vname + "'s body!\n" + Vname + " screams from " +
	  "the intense pain!\n", ({ victim, attacker }) );
	victim->take_damage( dmg, 0, "edged", attacker, THISO );
    }
    return 1;
}

status try_wield( object me )
{
    if ( ::try_wield( me ) )
	return 1;
    if ( (int)me->query_stat( "str" ) < 45 ) {
	write( "You haven't the strength to bind with the purple blade.\n" );
        call_out( #'destruct, 2, THISO );
	write( "The blade has been contaminated with your weakness, " +
	  "and rapidly disintegrates into a fine purple dust.\n " );
	return 1;
    }
    else {
	write( "Your mind is filled with a purple rage!\n" );
        shad = clone_object(MYSHAD);
        shad->sh_init(me);
    }
}

void post_unwield( object me )
{
    write( "The purple rage slips from your body.\n" );
    me->remove_purple_shadow();
}

