#include <ansi.h>
inherit SpecialAttackCode;
inherit AnsiTellCode;

object vampire;
int fed;

status sh_init( object ob )
{
    vampire = ob;
    shadow( vampire, 1 );
    fed = 0;
    add_special_attack( "gorge", vampire, 3 );    
}

void extra_init()
{
    add_action( "vampscore", "vampscore" );
}

int vampscore( string arg )
{
    if( !stringp( arg ) )
      return notify_fail( "Huh?\n" );
    
    tell_player( vampire, sprintf( "You have %s liters of blood inside you.\n",
      vampire->blood_points() ) );
}

int gorge( object victim, object attacker)
{
    int dam = ( attacker->query_stat( "str" ) / 2 ) + 
     ( attacker->query_stat( "dex" ) / 5 ) + random( attacker->query_stat( "chr" ) );
    
    if( fed > vampire->query_stat( "wil" ) + vampire->query_stat( "str" ) )
      return 0;
    
    string vic = victim->query_name();
    string att = attacker->query_name();
    
    ansi_tell( attacker, sprintf( "You lunge forward and bite into %s, feeding "
      "on %s delicious blood.\n", vic, possessive( victim ) ), CYAN );
    
    command( "roar", attacker );
    
    ansi_tell( victim, sprintf( "%s lunges forward and bites you! Blood flows from "
      "your wounds into %s mouth!\n", att, possessive( attacker ) ), CYAN );
      
    ansi_tell_room( ENV( attacker ), sprintf( "%s lunges forwards and bites %s. "
      "Yikes.\n", att, vic ), CYAN, ({ victim, attacker }) );
    
    victim->take_damage( dam, 0, "piercing", attacker, attacker );
    
    fed = fed + 1;
    return 1;
}

int is_vampire()
{
    return 1;
}

void kill_vampire_shad()
{
    remove_shadow( THISO );
    destruct( THISO );
}

int blood_points()
{
    return fed;
}
