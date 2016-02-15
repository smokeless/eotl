#include <city.h>
inherit MonsterCode;
inherit MonsterNoFlee;
inherit MonsterMove;
inherit SpecialAttackCode;
inherit AnsiTellCode;

void extra_create()
{
    set_name( "a beholder" );
    add_alias( "beholder" );
    set_short( "a beholder" );
    set_long( "This is a beholder. It is essentially a floating head "
      "with one single, cyclops-like eye surrounded by ten smaller eye "
      "stalks. Its massive, gaping maw is set in a permanent grin. "
      "It looks like a sphere covered in eyes, with extra eyes "
      "growing out of it. Little eye sprouts if you will." );
    set_gender( "unknown" );
    set_race( MON "beholder_race" );
    //set_guild()
    //set_specialization
    set_skill( "dodge", 50 );
    set_alignment( -4000 );
    set_stat( "str", random( 5000 ) );
    set_stat( "con", random( 5000 ) );
    set_proficiency( "hands", 50 );
    set_move_rate( 60 );
    set_move_chance( 50 );
    set_aggressive( 3 );
    add_combat_message( "smack", "smacks" );
    add_combat_message( "slup", "slurps" );
    add_combat_message( "grab", "grabs" );
    set_type( "blunt" );
    set_hit_bonus( 2 ); //So many eyes.
    set_heal_rate( 30 );
    set_heal_amount( random( THISO->query_max_hp() ) - random( 300 ) );
    set_natural_ac( 5 );
    set( "loot", 1 );
    add_money( random( 1000 ) );
    add_special_attack( "blastem", THISO, 10 );
}

int blastem( object vic, object att )
{
    if( !vic || !att )
      return 0;
    int dam = random( vic->query_max_hp() ) - vic->query_stat( "int" )/3;
    string *types = ({ "magic", "magic_fire", "electric", "sonic" });
    ansi_tell( vic, "The beholder cackles with glee as it "
      "unleashes a beam of pain in your direction!", RED );
    ansi_tell_room( ENV( THISO ), "The beholder cackles madly and unleashes "
      "a ray of PAIN!!!", RED, ({ vic }) );
    command( "cackle", THISO );
    
    vic->take_damage( dam, 0, types[ random( sizeof( types ) )],
      att );
    return 1;
}

varargs int try_skill( string name, object other, object target )
{
    if( target == THISO && !THISO->query_incap() )
       if( name == "mug" || name == "backstab" || 
          name == "mighty swing" || name == "quivering palm" )
          {
            ansi_tell( other, "The beholder saw you coming a "
              "mile away!", RED );
            other->attack_object( THISO );
            
            return 1;
          }
    return 0;
}
          
    
int DeathSequence( object killer, string cause, int nocorpse )
{
    ansi_tell_room( ENV( THISO ), "The beholder collapses to "
      "the ground dead.\n", RED, ({ }) );
    int level = THISO->query( "loot" );
    object env = ENV( THISO );
    SERV->loot( level, env );
    return( ::DeathSequence( killer, cause ) );
}
