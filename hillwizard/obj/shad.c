// Guild Shadow for Hill Wizard guild.  Taplash 03172015

#include <ansi.h>

inherit AnsiTellCode;

object me;
string form;

int query_max_freedom_magic();
int query_freedom_magic();
int add_freedom_magic( int add );

sh_init( object user )
{
    me = user;
    shadow( me, 1 );
    set_heart_beat( 1 );
    add_freedom_magic( 0 );  // resets 'guild_score' info
}

kill_hillwizard_shad()
{
   remove_shadow( THISO );
   set_heart_beat( 0 );
   me->remove_prop( "guild_score" );
   destruct( THISO );
}

status print_hp()
{
    int x, y;
    string line = "";
    x = query_freedom_magic();
    y = query_max_freedom_magic();

    if( y ) line += sprintf( "%sFM:%d %s",
            me->query_ansi() ? me->hpcol( x, y ) : "", 
            x, NORM );
    tell_object( me, line );
    return me->print_hp();;
}

int query_max_freedom_magic()
{
    int max;
    max = 5;
    return 5;
}

int query_freedom_magic()
{
    return( intp( me->query( "freedom_magic" ) ) ? 
        me->query( "freedom_magic" ) : 0 );
}

int add_freedom_magic( int add )
{
    int x, max;
    max = query_max_freedom_magic(); 
    x = MIN( MAX( query_freedom_magic() + add, 0 ), max );
    me->set( "freedom_magic", x );
    me->set( "guild_score", sprintf( "Freedom Magic:  %d/%d\n", 
      x, max ) );
    return x;
}

void heart_beat()
{
    
    int losepoint = random( 100 ) + 1;
    int think = me->query_skill( "thankin bout stuff" );
    int gainpoint = random( 50 ) + 1;
    string t;
    
    switch( random( 100 ) )
    {
      case 0..10  : t = "A boner is like a thumbs "
                        "up from from your balls "
                        "to whatever you're thinking "
                        "about.";                         break;
      case 11..20 : t = "Grass is like the fur of "
                        "the earth.";                     break;
      case 21..30 : t = "Kangaroos are just t-rex "
                        "deers.";                         break;
      case 31..40 : t = "Rocks are probably really "
                        "soft, they just tense up "
                        "when you touch them.";           break;
      case 41..50 : t = "Seals are just dog mermaids.";   break;
      case 51..60 : t = "Soup is just good flavored "
                        "tea.";                           break;
      case 61..70 : t = "To travel forward in time "
                        "all I have to do is wait.";      break;
      case 71..80 : t = "Picnic baskets are just "
                        "food briefcases.";               break;
      case 81..90 : t = "Hips are like, butt shoulders."; break;
      case 91..99 : t = "There is no way to know how "
                        "many chameleons are in this "
                        "room right now."               ; break;
    }                        
    
    if( me->in_combat() )
      return;
    
    if( me->query_resting() && think > 25 && think > gainpoint )
    {
      me->add_mana( random( me->query( "str" ) ) + 
      me->query( "wil" ) + ( think * 2 ) );
      add_freedom_magic( 1 );
      tell_player( me, sprintf( "You think really hard and realize: %s ",
        t ) );
      return;
    }
      
    if( me->query_resting() && think > 0 )
    {
      me->add_mana( random( me->query( "str" ) ) + 
      me->query( "wil" ) + ( think * 2 ) );
      return;
    }
          
    if( losepoint < 30 )
    {
      add_freedom_magic( -1 );
      return;
    }
    return;
}
