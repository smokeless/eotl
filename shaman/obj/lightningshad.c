#include <sguild.h>
#include <ansi.h>

inherit AnsiTellCode;

int charges;
object shaman;

int sh_init( object me )
{
    shaman = me;
    shadow( shaman, 1 );
    
    charges = shaman->query_stat( "wil" ) / 15; 
    charges += shaman->query_stat( "int" ) / 15;
    charges += shaman->query_skill( "lightning shield" ) / 5; 
    charges += shaman->query_skill( "natural attunement" ) / 10; 
    
    if( charges < 3 )
      charges = 3;
}

string short( object looker ) 
{
    string myshort;

    if( !stringp( myshort = shaman->short( looker ) ) )  
      return 0;

    if( objectp(looker) && !looker->query_ansi() )
        return sprintf( "%s [Crackling with Lightning]",
          myshort );

    return sprintf( "%s%s [Crackling with Lightning]%s%s",
      myshort, HIB, NOR, NOR2 );
}

int lightning_charges()
{
    return charges;
}


void kill_lightning_shad()
{
    ansi_tell( shaman, "The last of the lightning dissipates.", HIB );
    tell_room( ENV( shaman ), sprintf( "The last of the "
      "lightning surrounding %s dissipates", shaman->query_name() ),
      ({ shaman }) );
    remove_shadow( THISO );
    destruct( THISO );
}

take_damage( int dam, int loc, string type, object att, object w, int a )
{
   int resist;
   int lshield = shaman->query_skill( "lightning shield" );
   int shield_dam = random( shaman->query_skill( "lightning shield" ) ) * 3;
    if( !random( 5 ) )
    {
      if( charges <= 0 )
      {
        kill_lightning_shad();
        return shaman->take_damage( dam, loc, type, att, w, a );
      }
      resist = random( dam ) + random( lshield );
      charges --;
      shaman->take_damage( dam - resist, loc, type, att, w, a );
      
      ansi_tell( shaman, sprintf( "Your lightning shield blasts %s.",
        att->query_name() ), HIB );
      ansi_tell_room( ENV( shaman ), sprintf( "Lightning "
        "arcs from the body of %s into %s.",
        shaman->query_name(), att->query_name() ), HIB,
        ({ shaman, att }) );
      ansi_tell( att, sprintf( "A bolt of lightning leaps from "
        "the body of %s, striking you.", shaman->query_name() ),
        HIB );
      
      att->take_damage( shield_dam, 0, "electric", shaman, 0 );
      tell_player( shaman, sprintf( "You did %i damage. You "
        "blocked %i damage.", shield_dam, dam - resist ) ); 
    }
    else shaman->take_damage( dam, loc, type, att, w, a );
}

int lightning_shielded()
{
    return 1;
}
