/*
spell sling, it's a hillwizard thang! taplash 2015
*/

inherit AttackCommand;
inherit AnsiTellCode;
#include <ansi.h>

void extra_create()
{
    set( "name", "sling spell" );
    set( "guild", "hillwizard" );
    set( "class", "combat" );
    set( "help",
      "Skill : Sling Spell\n"
      "Usage : sling <target>\n"
      "Cost  : 3-5 Freedom Magic, 40 Fatigue\n"
      "    Sling Spell was first discovered during a party at "
      " a monster truck rally. There was a lot of meth, a lot of "
      " drinking, and a lot of dancing.\n\n"
      "This spell allows the hillwizard to attack with Freedom Magic!"
      "The hillwizard has no control over type, or whether or not it "
      "overloads. Hillwizards just know the right moves and grooves.\n" );
    set( "function", "do_sling" );
    set( "action", "sling" );
    set( "usage", "sling [target optional]" );
    set( "private", 1 );
    set( "no_rest", 1 );
    set( "no_combat", 0 );
    set( "cost", ([ "fatigue" : 40 ]) );
    set( "success", ([ "skills" : ({ "sling spell", 1, 1 }) ])  );
    set( "offchance", 4 );
    set( "delay", 1 );
} 

status okattempt( object victim )
{
    if( !::okattempt( victim ) ) return 0;

    if( THISP->query_freedom_magic() < 3 )
        return( write( "You don't have enough Freedom Magic.\n" ), 0 );

    if( ENV( THISP )->query( NoMagicP ) )
        return( write( "Magic isn't working here!!?!!@#\n" ), 0 );

    if( THISP->test_prop( CastingP ) )
        return( write( "You're doing something else.\n" ), 0 );

    if( THISP->query_delay() )
        return( write( "You are not able to do that right now.\n" ), 0 );
        
    return 1;
}

void do_sling( object victim )
{
    string vname, myname, hname, damstring, damtype,
      color;
    object weap = THISP->query_weapon();
    int dam, cost, delay, weapondam;
    vname = victim->query_name();
    myname = THISP->query_name();
    hname = THISP->query_hand_name();
    
    if( !THISP->query_weapon() )
      weapondam = THISP->query_max_damage();
    else
      weapondam = weap->query_max_damage();
      
    if( success_roll() < 0 )
    {
      delay = 2;
      ansi_tell( THISP, "You try to do some magic, "
        "but it's not right.", BLUE );
      ansi_tell( victim, sprintf( "%s just tried to magic you!!!",
        myname ), BLUE );
      tell_room( ENV( THISP ), sprintf( "%s just tried to magic %s!!!",
        myname, vname ), ({ THISP, victim }) );
      THISP->add_combat_delay( delay );
      if( victim )
        victim->attack_object( THISP );
      return;
    }
    
    switch( random( 100 ) + 1 )
    {
      case 0..75   : cost = 3; break;
      case 76..90  : cost = 4; break;
      case 91..100 : cost = 5; break;
    }
    
    switch( random( 100 ) + 1 )
    {
      case 1..25   : damstring = "arcane magic";
                     damtype   = "magic";
                     color     = CYAN;         break;
      case 26..50  : damstring = "frost";
                     damtype   = "magic_cold"; 
                     color     = BLUE;         break;
      case 51..75  : damstring = "electricity";
                     damtype   = "magic_elec"; 
                     color     = YELLOW;       break;
      case 76..100 : damstring = "fire";
                     damtype   = "magic_fire";
                     color     = RED;          break;
    }
    
    if( cost > THISP->query_freedom_magic() )
      cost = 3;
    
    dam = ( cost * weapondam ) +
      ( THISP->query_skill( "sling spell" ) * 2 );
    
    THISP->add_freedom_magic( -cost );
    subtract_cost(); // fatigue
    combat_delay();  
    
    ansi_tell( THISP, sprintf( "You smash %s into %s!",
      damstring, vname ), color );
    ansi_tell( victim, sprintf( "%s smashes you with %s!",
      myname, damstring ), color );
    tell_room( ENV( THISP ), sprintf( "%s smashes %s with %s!",
      myname, vname, damstring ), ({ victim, THISP }) );

    victim->take_damage( dam, 0, damtype, THISP, weap );

    if( victim )  
      THISP->attack_object( victim );
   
    return; 
}
