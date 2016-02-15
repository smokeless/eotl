// Flu object for the flu trap.
// -1/3 infected base stats. For
// a max of 5 minutes.
// Taplash 2015

#include<ansi.h>
inherit NewThingCode;
inherit AnsiTellCode;
int time;
object guy;

#define FLU "/usr/taplash/stuff/flu_obj"

void extra_create()
{
    set_id( "taplash flu object");
    set_droppable( 0 );
    set_weight( 0 );
    set( InvisP, 1 );
    set( DiseaseP, 1 ); //let clerics cure it.
}

void set_me_up( int dur, object sicky )
{
    time = dur;
    guy = sicky;
    guy->add_bonus_object( THISO );
    call_out( "do_flu", 10 );
}

int do_flu()
{
    string message, emote;
    object *potentialVictims = filter_array( 
      all_inventory( ENV( guy ) ), #'is_player );
    
    int timeTilSick = random( 20 );
    int luckyWinner;
    object infect;
    
    if( time < 0 )
    {
        call_out( "go_away", 1);
        return 1;
    }
    
    
    time = time - timeTilSick;
    
    switch( random( 6 )+1 )
    {
        case 1 : message = "Ugh. You feel horrible."; break;
        case 2 : message = "This flu really has you "
                           "down.";                   break;
        case 3 : message = "You crave chicken soup. "
                           "Maybe kill a chicken?";   break;
        case 4 : message = "Man you're just soooo "
                           "sick.";                   break;
        case 5 : message = "Starve a cold feed a "
                           "fever? Wait, or was it "
                           "the other way around?";   break;
        case 6 : message = "Hopefully you can make "
                           "it through your day. "
                           "Should probably just "
                           "call in sick though.";    break;                           
                        
    }
    
    switch( random(3)+1 )
    {
        case 1 : emote = "shiver"; break;
        case 2 : emote = "cough";  break;
        case 3 : emote = "sick";   break;
    }
    
    if( !ENV( THISO )->is_player() )
        destruct( THISO );
    
    //no check for net-dead. Want to spread
    //the flu when people net. If they have it.
    
    ansi_tell( guy, message, RED );
    
    command( emote, guy );
    
    ansi_tell_room( ENV( ENV( THISO ) ), sprintf( "Whoa %s looks really "
      "sick. It might be best to stay away from %s.", 
      guy->query_name(), objective( guy ) ), RED, 
      ({ guy }));
    
    if( sizeof( potentialVictims ) == 1 )
    {
        call_out( "do_flu", timeTilSick );
        return 1;
    }    
    
    luckyWinner = random( sizeof( potentialVictims ));
    infect = potentialVictims[luckyWinner];
    
    if( infect == guy )
    {
        call_out( "do_flu", timeTilSick );
        return 1;
    }
    
    ansi_tell( guy, sprintf( "You sneeze and cough all over "
      "%s.", infect->query_name() ), RED );
    ansi_tell( infect, sprintf( "Oh god %s just coughed and sneezed all "
      "over you.", guy->query_name() ), RED );
    ansi_tell_room( ENV( guy ), sprintf( "%s coughs and sneezes "
      "all over %s.", guy->query_name(), infect->query_name() ), 
      RED, ({ guy, infect }));
    
    if( present_clone( FLU, infect ) )
    {
        ansi_tell( infect, "It's a good thing you're already sick.", RED );
        call_out( "do_flu", timeTilSick );
        return 1;
    }
    if( infect->query_resistance( "disease" ) > random( 60 ) )
    {    
      call_out( "do_flu", timeTilSick );
      return 1;
    }
    
    object get_em = clone_object( FLU );
    move_object( get_em, infect );
    get_em->set_me_up( random( 300 ), infect ); //max of five minutes.
    call_out( "do_flu", timeTilSick );
    return 1;
}

void go_away()
{
    ansi_tell( guy, "You feel better.", BLU );
    guy->remove_bonus_object( THISO );
    destruct( THISO );
}

int query_time_left()
{
    return time;
}

int query_stat_bonus( string arg )
{
    int dex = guy->query_base_stat( "dex")/3;
    int str = guy->query_base_stat( "str")/3;
    int wil = guy->query_base_stat( "wil")/3;
    if( arg == "dex")
        return -dex;
    if( arg == "str" )
        return -str;
    if( arg == "wil")
        return -wil;
}
