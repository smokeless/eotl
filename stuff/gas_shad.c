//Illy shad modified for stuff trap
//taplash 2015
#include <ansi.h>
inherit AnsiTellCode;

object vic;
int damage;

int sh_init( object victim )
{
    int x;
    vic = victim;
    damage = 0;

    shadow( vic, 1 );

    ansi_tell( vic, "Gas encases you. You feel your nerves "
      "deadening. It's hard to tell what's going on.", BOLD_GREEN );
    x = 500;
    x = 500 - random( vic->query_stat( "int" ) * 2 );
    call_out( "end_health", x );
}

report_fhealth_damage() { return damage; }

take_damage( int dam, int loc, string type, object att, object w )
{
    int incoming = dam;
    if( ENV( vic )->query( ArenaP ) )
        vic->take_damage( 0, loc, type, att, w );
    else {
       damage += incoming;

        if( damage >= vic->query_hp() )
            if( find_call_out( "surprise" ) < 0 )
                call_out( "surprise", 2 );

        return vic->take_damage( 0, loc, type, att, w );
    }
}

end_health()
{
    if( !damage || !objectp( vic ) ) {
        ansi_tell( vic, "The gas has worn off.", BOLD_GREEN );
        remove_shadow( THISO );
        destruct( THISO );
        return;
    }
    ansi_tell( vic, sprintf( "You feel different." ),BOLD_GREEN );

    if( ( find_call_out( "surprise" ) < 0 ) &&
             ( find_call_out( "oops" ) < 0 ) )
        call_out( "oops", 3 );
}

rem_enchantments()
{
    end_health();
}

void
oops()
{
    if( !objectp( vic ) ) {
        remove_shadow( THISO );
        destruct( THISO );
        return;
    }
    ansi_tell( vic, "You do not feel very good.\n",BOLD_GREEN );
    ansi_tell_room( ENV( vic ), vic->query_name() + " looks "
    "suddenly ill.\n",BOLD_GREEN,({vic}) );
    if( find_call_out( "surprise" ) < 0 )
        call_out( "surprise", 2 );
}

void
surprise()
{
    int resist, dam_aft_res;

    if( !objectp( vic ) ) {
        remove_shadow( THISO );
        destruct( THISO );
        return;
    }

    resist = vic->query_resistance( "poison" );

    dam_aft_res = ( resist >= 0 ) ?
      ( damage * resist ) / 100 : damage + ( damage * -resist ) / 100;

    ansi_tell( vic, "You look at your self and see battle wounds "
    "which were not there before. You begin to remember the battles, "
    "and how odd it was that you had felt no pain.\nIt seems "
    "you did after all.",BOLD_GREEN);

    ansi_tell_room( ENV( vic ), vic->query_name() + "'s body is "
    "suddenly rent by wounds better left forgotten.\n",BOLD_GREEN,({ vic }));
    if( damage >= vic->query_hp() )
    {
      ansi_tell( vic, "Your mind clears as the nerve gas wears "
        "off. You notice that you are injured to the point of death!",BOLD_GREEN );
      vic->DeathSequence( vic, "Didn't pay attention to traps." );
    }

    vic->take_damage( damage, 0, "poison", vic );

    if( objectp( vic ) ) {
        remove_shadow( THISO );
        destruct( THISO );
    }
}

has_false_health_shad() { return 1; }
