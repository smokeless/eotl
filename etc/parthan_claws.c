//  Verminard@Eotl July 1997
//  Nargolia Cabal
//  11/1/2001 Updated to NewWeaponCode
//  and cleaned up code -- Crisis
// Made both special attacks return 0 - Crisis 11/21/03

inherit NewWeaponCode;
inherit SpecialAttackCode;
inherit AnsiTellCode;

#include <ansi.h>

// #include "/zone/fantasy/nargolia/logs/log.h"
string *ok_hands;

void extra_create()
{
  ok_hands = ({"paw", "hand"});

  set_ids( ({"glistening claws", "parthan claws", "claws"}) );
  set_short("a set of glistening claws");
  set_long(
    "Razor sharp elven-steel knives shine radiantly, protruding from "
    "a tightly bound leather wrist guard.  Each knife is positioned "
    "evenly apart in the hard leather wrist guard.  The knives resemble "
    "a more deadly form of the claws of their creator.");
  set_material("elven steel");
  set_proficiency( "hands");
  set_handed(2);
  set_damage_type("edged");
set_base_damage(18);
  set_damage_step(6);
  set_base_speed(15);
  set_speed_step(5.7);
  set_prof_damage_mod(6.5);
  set_prof_speed_mod(3.75); // was 3.25
  set(BlessedP,  1);
  set(NoDisarmP, 1);
  set(NoStoreP,  1);
  set(NoEnhanceP, 1);
  set(SharpenedP, 1);
  set(NoEnchantP, 1);
  set_limit(1);
  set_weight(150);
  set_combat_messages( ({"dice", "dices", "slice", "slices", "maul", "mauls", 
    "rip", "rips", "shred", "shreds", "cut", "cuts", "rend", "rends" }) );
  add_special_attack("rage", THISO, 3 + random(2));
  add_special_attack("clumsy", THISO, 6);
}

try_wield(object wielder)
{
  string pname, hand_name, player_fail_msg;
  int eval;

  pname = wielder->query_name();
  hand_name = wielder->query_hand_name();
  eval = to_int(wielder->query_eval());

  if (member(ok_hands, hand_name) == -1)
  {
    player_fail_msg = strformat("You look at your " + 
      hand_name + "s and realize that any attempt would be futile.");
  }
  else if (wielder->query_guild() == "Crusader")
  {
    player_fail_msg = "The claws sense Adon's presence and reject you.";
  }
  else if (eval < 25 && !wielder->query_npc())
  {
    player_fail_msg = "You are not skilled enough to wield this weapon.";
  }
  else
  {
    tell_player(wielder, "The leather guards wrap lovingly around your " + 
      hand_name + "s.  A rush of confidence overwhelms you.");
    if (objectp(ENV(wielder)))
      tell_room(ENV(wielder), strformat(pname+"'s eyes glaze over in ecstacy."), ({wielder}) );
    return 0;
  }

  tell_player(wielder, player_fail_msg);
  if (objectp(ENV(wielder)))
    tell_room(ENV(wielder), pname+" fumbles with a set of knives.", ({wielder}));
  return 1;
}

int clumsy( object victim, object attacker )
{
  int ability, hit_loc, dex, str, prof, race, damage;
  string hit_loc_name, aname;

  aname = attacker->query_name();
  hit_loc = attacker->get_hit_location(attacker);
  hit_loc_name = attacker->query_hit_info( "name", hit_loc);
  str = attacker->query_stat("str");
  dex = attacker->query_stat("dex");
  prof = attacker->query_proficiency("hands");
  race = (attacker->query_race() == "Parthan") ? 14 : 7;
  ability = (dex/8) + race + (prof/3);

  if((attacker->query_real_name() == "merthran") && (attacker->query_npc()))
    ability += 50;
  switch(random(ability))
  {
    case  0..1  :  // LARGE MISTAKE
      tell_player(attacker, sprintf(
        "The claws twist wildly out of your control!\nYou jab yourself "
        "hard in the %s!", hit_loc_name));
      tell_room(ENV(attacker), strformat( sprintf(
        "%s loses control of Merthran's claws and jabs %sself hard in "
        "the %s!", aname, objective( attacker ), hit_loc_name)), ({ attacker }) );
      damage = random(max((str/3) - race - (prof/2), 30));
      attacker->take_damage(damage, 0, "piercing", attacker);
      break;
    case  2     :  // COMBAT DELAY
      tell_player(attacker,
        "The claws contort awkwardly, briefly fusing the knife-like "
        "fingers together.");
      tell_room(ENV(attacker), strformat( sprintf(
        "%s fumbles with Merthran's claws.", aname)), ({attacker}) );
        attacker->add_combat_delay(random(3) + 1);
      break;
    case  3..6  :  // SMALL MISTAKE$
      tell_player(attacker, sprintf(
        "You lose your concentration and nick yourself on the %s.", hit_loc_name));
      tell_room(ENV(attacker), strformat( sprintf(
        "%s slips and nicks %sself on the %s.", aname,
        objective(attacker), hit_loc_name)), ({attacker}) );
      damage = random(max((str/6) - race - (prof/2), 15));
      attacker->take_damage(damage, 0, "edged", attacker);
      break;
    case  7..9  :  // NEAR MISTAKE
      tell_player(attacker, sprintf(
        "You nearly scrape your %s but deftly gain control of Merthran's "
        "claws.", hit_loc_name));
      break;
    case 10..14 :  // LOSE BALANCE
      tell_player(attacker, sprintf(
        "Your frantic movement throws you slightly off balance."));
      tell_room(ENV(attacker), strformat( sprintf(
        "%s momentarily loses %s balance.", aname, possessive(attacker) )),
        ({attacker}) );
      attacker->add_combat_delay(1);
      break;
    default     :  // PAT ON THE BACK
// 20031129 - Verminard
//   No need for a reward here since this weapon is already powerful enough
/*
      tell_player(attacker, 
        "You cackle gleefully as the claws move with perfect precision!");
      tell_room(ENV(attacker), strformat( sprintf(
        "%s cackles gleefully!", aname)), ({attacker}) );
      victim->take_damage(damage, 0, "slashing", attacker);
*/
      break;
  }
  return 0;
}

int enraged = 0;
int rage( object victim, object attacker )
{
  int counter, success, vic_eval, att_eval;
  string aname, vname, hand_name;

  if (enraged)
    return 0;
  enraged = 1;
  aname = attacker->query_name();
  vname = victim->query_name();
  hand_name = attacker->query_hand_name();

  ansi_tell(attacker, sprintf(
   "Your %ss move at a lightning pace as you lash out at %s!",
    hand_name, vname), HIR);
  ansi_tell(victim, sprintf(
    "%s's %ss move at a lightning pace as %s lashes out at you!",
    aname, hand_name, subjective(attacker)), HIR );
  ansi_tell_room(ENV(attacker), sprintf(
    "%s's %ss move at a lightning as %s lashes out at %s!",
    aname, hand_name, subjective(attacker), vname), HIR,
    ({attacker, victim}) );

  // end rage sequence in min of 3 rounds
  enraged = random(to_int(attacker->query_eval() / 30) + 3) + 4;
  return 0;
}

void end_rage()
{
  enraged = 0;
  // todo: determine if/when to notify player and/or room, for now just end silently
}

varargs
int query_speed(object who)
{
  if (enraged)
  {
    enraged--;
    if (!enraged) end_rage();
  }
  float speed = to_float(::query_speed(who));
   return to_int(enraged ? speed * 1.75 : speed);
}

varargs
int query_max_damage(object attacker, object victim)
{
  float damage = to_float(::query_max_damage(attacker, victim));
  return to_int(enraged ? damage * 0.8 : damage);
}

int query_fatigue_cost()
{
  return ::query_fatigue_cost() + (enraged ? random(2) : 0);
}
