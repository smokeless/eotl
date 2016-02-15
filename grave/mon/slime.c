#include <forest.h>

inherit MonsterCode;
inherit MonsterMove;
inherit MonsterTalk;
inherit MonsterPickUp;
inherit AnsiTellCode;
inherit SpecialAttackCode;

string color;
string colorname;

void extra_create() 
{
    switch( random( 3 ) )
    {
      case 0 : colorname = "green"  ; color = GRN; break;
      case 1 : colorname = "blue"   ; color = BLU; break;
      case 2 : colorname = "purple" ; color = MAG; break;
    }
    
    set_name( "a slime" );
    add_alias( "slime" );
    add_alias( sprintf( "%s slime", colorname ) );
    
    set_short( sprintf( "a %s slime", colorname ) );
    set_ansi_short ( sprintf( "%sa %s slime", color, colorname )  );
    
    set_long( sprintf( "This slime oozes sloppily through the room absorbing "
      "bits and pieces off of the mushrooms around it. Inside of its "
      "%s colored body you can see quite a bit of material. "
      "Hopefully it doesn't try to digest you!", colorname ) );
    
    set_race( FRACE "slime" );
    set_alignment( NEUTRAL_AL );
    
    set_stat( "str" , 200 );
    set_stat( "con" , 300 );
    
    
    set_proficiency( "hands", 150 );
    set_skill( "dodge", 65 );
    
    set( NoStealP, 1 );
    set( NoStunP, 1 );
    
    set_natural_ac( 10 );
    
    set_heal_rate( 20 );
    set_heal_amount( 60 );
    
    set_chat_rate( 30 );
    set_chat_chance( 50 );
    
    add_phrase( "#emote squelches along." );
    add_phrase( "#emote jiggles wildly." );

    set_move_rate( 40 );
    set_move_chance( 50 );
    
    set_pick_up_rate( 60 );
    set_pick_up_chance( 0 );
    
    set_heart_beat( 30 );
    
    add_special_attack( "mimic", THISO, 30 );
}

int mimic( object victim, object attacker )
{
    string vil = victim->query_name();
    string att = attacker->query_name();
    int dam = 100 + random( 30 );
    
    ansi_tell_room( ENV( attacker ), sprintf(
      "%s screams as the slime touches %s "
      "skin! The slime burbles and changes form. "
      "It looks almost identical to %s!!!!\n", vil, possessive( vil ),
      vil ), color, ({ victim }) );
    ansi_tell( victim, sprintf(
      "The slime touches you, the pain is incredible. "
      "It begins to change form!!! It has become a copy of you!!!\n" ),
      color );
    
    set_short( sprintf( "%s, covered in slime", CAP( vil ) ) );
    set_ansi_short ( sprintf( "%s%s, covered in slime", color, CAP( vil ) ) );
    
    set_long( " " );
    
    set_name( sprintf( "%s", victim->query_real_name() ) );
    
    add_alias( sprintf( "%s", victim->query_real_name() ) );
   
    set_gender( victim->query_gender() );
    set_race( victim->query_race() );
    
    set_stat( "str" , victim->query_stat( "str" ) + 100 );
    set_stat( "con" , victim->query_stat( "con" ) + 100 );
    
    attacker->full_heal();
    
    set_guild( victim->query_guild() );
    
    set_proficiency( "hands", 150 );
    
    set_skill( "dodge", victim->query_skill( "dodge" ) + 100 );
    
    
    set( NoStealP, 1 );
    set( NoStunP, 1 );
    set_natural_ac( 10 );
    
    victim->take_damage( dam, 0, "acid", THISO );
    
    remove_special_attack( "mimic" );
    return 1;    
}

void heart_beat()
{
    object *inv = all_inventory( THISO );
    int x;
    
    if( sizeof( inv ) == 0 )
      return 0;
    
    for( x = 0; x < sizeof( inv ); x++)
    {
      destruct( inv[x] ); 
    }    
    
    ansi_tell_room( ENV( THISO ), "A slime digests something.\n", RED );
}
