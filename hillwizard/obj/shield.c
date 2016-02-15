#include <ansi.h>
#include <hillwizard.h>
inherit ShieldCode;
inherit AnsiTellCode;

void extra_create()
{
    set_ids( ({ "shield", "wizard shield", "hillwizard shield" }) );
    set( "short", "a hillwizard shield" );
    set( "long", "This shield is definitely magical. "
      "Which is odd because hillwizards seem definitely "
      "not in tune with magic enough to conjure something. "
      "But oh well, this is their guild shield. When they came "
      "down from the hills they brought this. Well, this and "
      "banjos." );
    set_weight( 0 );
    set( MagicP, 1 );
    set( NoStoreP, 1 );
    set_droppable( 0 );
    set_block_chance( 10 );
    set_handed( 1 );
    set_value( 0 );
}

void make_better( int x )
{
  return;
}

int try_block( object shield, object target, object weapon )
{
    object *whoshere;
    object wizard = ENV( THISO );
    int cost = random( wizard->query_max_mana() ) -
                       wizard->query_stat( "int" ) + 1;
    int dam, i;
    if( cost > wizard->query_mana() )
    {
      ansi_tell( wizard, "Oh noes! You lost your "
       "hillbilly connection to your shield! It explodes!", RED );
      ansi_tell_room( ENV( wizard ), sprintf( "Oh shit %s "
       "just lost his grasp on shield magic! %s shield "
       "explodes!", wizard->query_name(), possessive( wizard ) ),
       RED, ({ wizard }) );
      wizard->add_mana( -cost );
      dam = wizard->query_skill( "summon shield" ) +
            wizard->query_stat( "str" ) +
            wizard->query_stat( "dex" ) +
            wizard->query_stat( "wil" ) +
            cost;
      dam = random( dam );
      tell_player( wizard, sprintf( "damage was: %i", dam ) );
      whoshere = filter_array( all_inventory( ENV( wizard ) ), #'living );
      i = sizeof( whoshere );
      while( i-- )
      {
        whoshere[ i ]->take_damage( dam, 0, "magic", wizard );
        wizard->attack_object( whoshere[ i ] );
      }
      destruct( THISO );
      return 0;
    }
    wizard->add_mana( -cost );
    shield->try_block( shield, target, weapon );
}
  
void post_block( object vic, object attacker, object weapon )
{        
    object wizard = ENV( THISO );
    wizard->add_freedom_magic( 1 );
    ansi_tell( wizard, "Blocks are freedoms!@$!@!", CYAN );
    vic->post_block( vic, attacker, weapon );
}
