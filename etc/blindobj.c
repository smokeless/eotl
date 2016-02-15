/*  This object is meant to be used with alumpen.c. The premise is
    that the victim of the weapon special attack gets stabbed in the
    eyes, temporarily preventing sight.
    
    Added:
    - a command filter. it should capture all outputs from the blinded
        player, and finds out if 'look' or 'glance' commands are being
        used, and gives 'ARGHYERBLIND' msg accordingly, and whether the
        blinded player is trying to MOVE/FLEE to an exit, and scrambles
        the exits in that case.
    - a clonep() check, to eliminate call_out errors that happen when
        the blueprint is loaded initially.
        
    To add:
    - a way to have RoomCode handle the actual player movement, using
        use_exit. This will need more experiments, as previous attempts
        seem to show the correct messages/tells, but no actual player
        movement seems to occur.
    2014.02.09 Shibame
*/

inherit NewThingCode;
inherit AnsiTellCode;

#include <ansi.h>

void extra_create()
{
    set_ids( ({ "suckerblind" }) );
    set( InvisP, 1 );
    set_gettable( 0 );
    set_droppable( 0 );
    call_out( "done", 15 );
}

void done()
{
    if( !clonep( THISO ) )
    {
        return 0;
    }
        ansi_tell( ENV( THISO ), "Your vision returns as the pain in "
        "your eyes subsides.\n", HIG );
        destruct( THISO );
}
    
extra_init()
{
    add_action( "command_filter", "", 1 );
}

int command_filter( string stuff )
{
    object oldenv;
    string str, my_dir, blinded, pblinded, *dirs, *looks;
    mapping m;
    
    looks = ({ "look", "peer", "examine", "glance", "alertness",
        "inventory", "see" });

    oldenv = ENV( THISP );
    m = mappingp( oldenv->query( "exits" ) ) ? oldenv->query( "exits" )
        : ([ ]);
    m += oldenv->query( "invis_exits" );
    str = query_verb();
    my_dir = m[ str ];
    dirs = m_indices( m );
    
    blinded = THISP->query_name();

    if( !living( ENV( THISO ) ) )
    {
            destruct ( THISO );
            return 0;
    }
    
    if( member( looks, str ) !=-1 )
    {
        ansi_tell( THISP, "Your eyes BURN with searing pain! You can "
            "not see anything!\n", HIR );
        return 1;
    }
    
    if( member( dirs, str ) !=-1 )
    {
        if( random( 100 ) < 20 )
        {
        ansi_tell( THISP, sprintf( "Disoriented by searing pain in your "
            "eyes, you manage to stumble %s.", str ), HIR );
        ansi_tell_room( oldenv, sprintf( "Disoriented by pain, %s "
            "stumbles %s!", blinded, str ), HIY, ({ THISP }) );
        move_object( THISP, my_dir );
        command( "look", THISP );
        return 1;
        }
        
        my_dir = m[ dirs[ random( sizeof( dirs ) ) ] ];
        ansi_tell( THISP, "Your eyes burning with searing pain, you "
            "stumble around blindly!", HIR );
        ansi_tell_room( oldenv, sprintf( "Disoriented by pain, %s "
            "blindly stumbles out!", blinded ), HIY, ({ THISP }) );
        move_object( THISP, my_dir );
        command( "look", THISP );
        return 1;
    }
    
    return 0;
}
