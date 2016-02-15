/*
Spirit walk shadow, makes sure that the player
comes around.
*/

inherit AnsiTellCode;
#include <ansi.h>

object shaman;
int skill;

sh_init( object sh, int sk )
{
    shaman = sh;
    skill = sk;
    shadow( shaman, 1 );
    call_out( "kill_shad", skill * 10 );
}

void kill_shad() 
{ 
    if( shaman->query_ghost() == 0 )
    {
      int hplost = THISP->query_hp() - 1 ;
      ansi_tell( shaman, "It appears that the magic used to "
      "regenerate you has disagreed with your body! "
      "You feel an immense amount of pain as your body rebels "
      "against your spirit.\n", BOLD_RED );
      command( "scream", shaman );
      ansi_tell_room( ENV( shaman ), sprintf( "%s shakes violently. "
      "Wounds appear all over %s flesh.\n", shaman->query_name(),
      possessive( shaman ) ), BOLD_RED, ({ THISP }) );      
    
      THISP->add_hp( -hplost );
      THISP->add_fatigue( - THISP->query_fatigue() );
      THISP->add_mana( - THISP->query_mana() ); 
      
      remove_shadow( THISO );
      destruct( THISO );
      return;
    }
    
    ansi_tell( shaman, "You feel your will to continue as a "
      "spirit sapping. You can no longer hold out and are "
      "returned to mortal form.\n", CYAN );
    ansi_tell_room( ENV( shaman), sprintf( "%s "
      "blinks in and out of existence. %s face is twisted in "
      "agony.\n", shaman->query_name(), CAP( possessive( shaman ) ) ),
      CYAN, ({ THISP }) );

    THISP->make_me_alive();
    THISP->add_fatigue( - THISP->query_max_fatigue() );
    THISP->add_mana( - THISP->query_max_mana() );
    THISP->add_hp( ( -THISP->query_max_hp() / 2 ) );
    remove_shadow( THISO );
    destruct( THISO );
}
