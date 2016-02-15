// meth cook for hill wizard guild.  clones into the
// methlab in the guild hall.  -arphen 03182015

#include <ansi.h>
#include <hillwizard.h>

inherit MonsterCode;
inherit SpecialAttackCode;
inherit AnsiTellCode;

int exploding;
 
void extra_create()
{
   object ob;

   set_name(  "Paula Spleen" );
   add_alias( "paula" );
   add_alias( "spleen" );
   add_alias( "paula spleen" );
   add_alias( "Paula Spleen" );
   set_short( "Paula Spleen" );
   set_long(
     "This here be Paula.  She is famous round these parts fer "
     "being the best durn cook this side-a the mississipper.  "
     "She sure must love herself some butter, cuz she's five "
     "hunred pounds if shesa ounce yessireeee yeeehawwww."
   );

   set_race( "pig" );
   set_gender( "female" );
   set_alignment( 250 );

   set_stat( "str",  500 );
   set_stat( "int",    1 );
   set_stat( "wil",  800 );
   set_stat( "con",  500 );
   set_stat( "dex",  300 );
   set_stat( "chr", 1500 );

   set_max_fatigue( 25000 );
   set_natural_ac ( 10 );
   set_proficiency( "pig-fu", 6 );
   set_skill( "dodge", 100 );
   set_percent_bonus_exp( -15 );

   add_special_attack( "chuck_butter", THISO, 10 );

   ob = clone_object( ZOBJ "wig" );
     move_object( ob, THISO );
   ob = clone_object( ZOBJ "muumuu" );
     move_object( ob, THISO );
    ob = clone_object( ZOBJ "diabetes" );
      if( !ob ) ob = clone_object( ZOBJ "butter" );
      move_object( ob, THISO );

   call_out( "gear_up", 2 );
}

int gear_up()
{
    command( "equip" );
}

int chuck_butter( object victim, object attacker )
{
    int counter = 10;
    int dmg     = 5 + random( 20 );
    object butter;

    if( counter > 0 )
    {
      ansi_tell( victim, "Paula pulls out a stick of "
        "butter and tosses it at you.", HIY );
      ansi_tell_room( ENV( victim ), sprintf( "Paula pulls out "
        "a stick of butter and tosses it at %s.",
      victim->query_name() ), HIY, ({ victim }) );

      butter = clone_object( ZOBJ "butter" );
        move_object( butter, victim );

      victim->take_damage( dmg, 0, "ego", attacker, butter );
      victim->add_combat_delay( 1 + random( 1 ) );

      counter--;
      return 0;
    }
    return 0;
}

query_resistance()
{
    return 20;
}

DeathSequence( object killer, string cause )
{
    int i;
    object butter;

    exploding = 1;
    int k = 2 + random( 4 );
    object *all = all_inventory( ENV( THISO ) );

    while( k >= 0 )
    {
      butter = clone_object( ZOBJ "butter" );
        move_object( butter, ENV( THISO ) );
      k--;
    }

    tell_room( ENV( THISO ), "Paula's structural integrity "
      "has reached buttery levels!\n", ({ }) );
    ansi_tell_room( ENV( THISO ), ">---BUTTERSPLOSION---<", 
      HIY,  ({ }) );

    for( i = 0; i < sizeof( all ); i++ )
    {
      if( ( living( all[ i ] ) ) && 
          ( !ENV( THISO )->query( NoCombatP ) ) &&
          ( THISO->valid_target(  all[ i ] ) ) )
      {
         all[ i ]->take_damage( 25 + random ( 50 ), 0, "blunt", THISO );
      }
    }

    return ( ::DeathSequence( killer, cause, 1 ) );
}

varargs int take_damage( int dam, int loc, string type, object attacker,
  object w, int always )
{
  if( exploding )
    return 0;

  return ::take_damage( dam, loc, type, attacker, w, always );
}
