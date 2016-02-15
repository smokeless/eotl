#include<ansi.h>
inherit AnsiTellCode;

object poisoner;
object what;

sh_init( object food, int person )
{
    poisoner = person;
    what = food;
    shadow( what, 1 ); 
}

int poisoned_item()
{
    return 1;
}

string short( object looker )
{
    int chance = random( 50 ) + 1;
    object doof = looker;
    string desc = what->query( "short" );
    
    if( IsWizard( doof ) )
        return( sprintf( "%s [poisoned]", desc ) );
    
    if( is_player( doof ) && 
        doof->query_alert() == 1 ) 
          return( sprintf("%s [poisoned]", desc ) );
    
    if( is_player( doof ) && 
        present( "site_obj", doof ) != 0 )
          return( sprintf( "%s [poisoned]", desc ) );
    
    if( is_player( doof ) && 
        doof->query_stat( "int" ) / 10 >= chance )
        return( sprintf( "%s [poisoned]", desc ) );
    
    else
        return( sprintf( "%s", desc ) );
}

status heal_signal( object healed )
{
    object player = healed;
    ansi_tell( player, sprintf( "You feel a horrible burning "
      "sensation in your throat. Something may have been off about "
      "%s.", what->query( "short") ), RED );
    ansi_tell_room( ENV( player ), sprintf( "%s grabs %s stomach after "
      "consuming %s.\n", player->query_name(), possessive( player ),
      what->query( "short" ) ), RED, ({ player }) );
    
    int dam = player->query_max_hp() * 2;
    int time = player->query_eval();
    
    object thePain = clone_object( "/lib/items/poison" );
    thePain->set_poison( dam, time, poisoner );
    move_object( thePain, player );
    remove_shadow( THISO );
    destruct( what );
    destruct( THISO );
    return 1;
}
