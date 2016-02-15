inherit MonsterCode;
inherit MonsterPickUp;
inherit MonsterMove;
inherit SpecialAttackCode;
inherit MonsterTalk;
inherit AnsiTellCode;

#include <shaftdust.h>

int is_ghoul, dodge, exploding;

void extra_create()
{
   string adj, creature, pre, full, desc;
   object ob;

   switch( random( 25 ) ) 
   {
     case  0 : adj = "abominable";   pre = "an";  break; 
     case  1 : adj = "accursed";     pre = "an";  break; 
     case  2 : adj = "atrocious";    pre = "an";  break;
     case  3 : adj = "appalling";    pre = "an";  break; 
     case  4 : adj = "abhorrent";    pre = "an";  break;
     case  5 : adj = "awful";        pre = "an";  break;
     case  6 : adj = "unspeakable";  pre = "an";  break;
     case  7 : adj = "grim";         pre = "a";   break;
     case  8 : adj = "hideous";      pre = "a";   break;
     case  9 : adj = "horrid";       pre = "a";   break;
     case 10 : adj = "gruesome";     pre = "a";   break;
     case 11 : adj = "horrendous";   pre = "a";   break;
     case 12 : adj = "nauseating";   pre = "a";   break;
     case 13 : adj = "disgusting";   pre = "a";   break;
     case 14 : adj = "despicable";   pre = "a";   break;
     case 15 : adj = "detestable";   pre = "a";   break;
     case 16 : adj = "repulsive";    pre = "a";   break;
     case 17 : adj = "revolting";    pre = "a";   break;
     case 18 : adj = "heinous";      pre = "a";   break; 
     case 19 : adj = "cursed";       pre = "a";   break;
     case 20 : adj = "stinking";     pre = "a";   break; 
     case 21 : adj = "vicious";      pre = "a";   break;
     case 22 : adj = "terrible";     pre = "a";   break;
     case 23 : adj = "rotten";       pre = "a";   break;
     case 24 : adj = "repugnant";    pre = "a";   break;
   }

   is_ghoul = 0;
   dodge = 80;

   switch( random( 4 ) ) {
     case 0 : creature = "ghoul";  
       is_ghoul = 1; // For Corpse Explosion.
       set_race( SHAFT_OBJ "race_ghoul" );
         break;
     case 1 : creature = "wraith";
       add_special_attack( "wraith", THISO, 5 );
       dodge = 150;
       set_race( SHAFT_OBJ "race_wraith" );
         break;
     case 2 : creature = "skeleton";
       add_special_attack( "skeleton", THISO, 3 );
       set_race( SHAFT_OBJ "race_skele" );
         break;
     case 3 : creature = "vampire";
       add_special_attack( "vampire", THISO, 6 );
       set_race( SHAFT_OBJ "race_vamp" );
         break;
   }
   full = pre + " " + adj + " " + creature;

   desc = "This " + creature + " looks absolutely terrifying.  You " +
     "may want to avoid it altogether.  It does not appear to be " +
     "'glowing' in the dark, but there is an extremely faint aura " +
     "all around it.  Creepy!";

   set_name( creature );
   add_alias( creature );
   add_alias( adj + " " + creature );
   add_alias( full );
   add_alias( full );
   add_alias( "undead" );
   set_short( full );
   set_long( desc );

   set_gender( "unknown" );

   set_aggressive( 1 + random( 10 ) );
   set_stat( "str",  700 + random( 20 ) );
   set_stat( "int",  200 );
   set_stat( "wil",  400 );
   set_stat( "con",  600 + random( 20 ) );
   set_stat( "dex",  225 + random( 10 ) );
   set_stat( "chr",   10 );

   set_skill( "dodge", dodge );

   set_percent_bonus_exp( 15 );
   set_proficiency( "hands", 66 );

   set_max_fatigue( 25000 );
   set_natural_ac ( 25 );

   set_pick_up_rate( 20 );
   set_pick_up_chance( 0 );

   set_move_rate( 120 + random( 30 ) );
   set_move_chance( 75 + random( 20 ) );
   set_avoid_props( ({ NoWanderRoomP }) );

   set_chat_chance( 0 );
   set_chat_rate( 20 + random( 30 ) );

   add_phrase( creature + " moans faintly... or was it the wind?" );

   set_alignment( -4000 );
   set( UndeadP, 1 );
   set( NoBreatheP, 1 );
   set( NoStunP, 1 );

   if( random( 5 ) )
   {
      add_money( 100 + random( 75 ) );
   }

   if ( random( 250 ) == 0 )
   {
     clone_object( SHAFT_OBJ + "talisman" );
     move_object( ob, THISO );
   }

   ob = clone_object( SHAFT_ARM + "undead_rag" );
     move_object( ob, THISO );

   call_out( "gear_up", 1 );
}

int gear_up()
{
   command( "equip" );
}

DeathSequence( object killer, string cause, int nocorpse )
{
   int i;
   object *all;
   object soup_part;
   all = all_inventory( ENV( THISO ) );

   if( is_ghoul )
   {
     exploding = 1;

     ansi_tell_room( ENV( THISO ), "The ghoul, sensing his imminent "
       "demise, suddenly EXPLODES into a million "
       "pieces!", HIR, ({ }) );

     for( i = 0; i < sizeof( all ); i++ )
     {
       if( ( living( all[ i ] ) ) && 
           ( !ENV( THISO )->query( NoCombatP ) ) &&
           ( THISO->valid_target(  all[ i ] ) ) )
       {
         all[i]->take_damage( 175 + random ( 50 ), 0, "unholy", THISO );
       }
     }
     return( ::DeathSequence( killer, cause, 1 ) );
   }

   else
   {
     if( random( 30 ) == 1 )
     {
       soup_part = clone_object( SHAFT_OBJ + "femur" );
         move_object( soup_part, THISO );
     }

     return( ::DeathSequence( killer, cause, 0 ) );
   }
}

int wraith( object victim, object attacker )
{
   int dmg    = 60 + random( 50 );
   string vic = victim->query_name();

   ansi_tell( victim, "The Wraith's eyes glow brightly "
     "for a moment.\nYou are suddenly enveloped in a cocoon of "
     "mysterious energy!", YELLOW );
   ansi_tell_room( ENV( THISO ), "The Wraith's eyes glow "
     "brightly for a moment.  Suddenly, a shockwave of energy "
     "envelopes " + vic + "!", YELLOW, ({ victim }) );

   victim->add_combat_delay( 1 );
   victim->take_damage( dmg, 0, "unholy", attacker );
   return 1;
}

int skeleton( object victim, object attacker )
{
   if( !victim->query_weapon() )
     return 1;

   if( victim->test_prop( NoDisarmP ) )
     return 1;

   if( victim->query_weapon()->query( NoDisarmP ) )
     return 1;

   ansi_tell( victim, "The skeleton disarms you!", RED );
   tell_room( ENV( THISO ), "The skeleton reaches out and "
     "disarms " + victim->query_name() + "!\n", ({ victim }) );

   victim->unwield_weapon();
   victim->add_combat_delay( 2 + random( 2 ) );

   return 1;
}

int vampire( object victim, object attacker )
{
   object o;

   if( victim->query( UndeadP ) )
     return 1;

   if( victim->query_resistance( "drain" ) == 100 )
     return 1;

   ansi_tell( victim, "The vampire raises his arms in your "
     "direction.  A mystical funnel begins to form, with energy "
     "flowing from you toward the vampire!", RED );
   ansi_tell_room( ENV( THISO ), "The vampire raises his arms at "
     + victim->query_name() + ".  A mystical funnel begins to form, "
     "and energy begins to flow from " + victim->query_name() + 
     " toward the vampire!\n", RED, ({ victim }) );

   if( !( o = present_clone( SHAFT_OBJ + "drain_obj", victim ) ) )
   {
     o = clone_object( SHAFT_OBJ + "drain_obj" );
     move_object( o, victim );
   }
   o->setup_drain( victim, 10, 30 + random( 10 ) );
   victim->add_fatigue( -50 - random( 50 ) );
   victim->add_mana( -5 - random( 20 ) );
   return 1;
}

add_combat_delay( int x )
{
    if( x > 0 ) x = to_int( x / 3 );
    return ::add_combat_delay( x );
}

varargs int take_damage( int dam, int loc, string type, object attacker,
  object w, int always )
{
  if( exploding )
    return 0;

  return ::take_damage( dam, loc, type, attacker, w, always );
}
