#include <ansi.h>

inherit NewThingCode;

#define IPFILE "/usr/socialism/pumpkin/ipaddy"
#define REGFILE "/usr/socialism/pumpkin/registered"
#define VOTESFILE "/usr/socialism/pumpkin/votes"
#define VOTEDFILE "/usr/socialism/pumpkin/voted"
void extra_create()
{
    set_ids( ({ "machine", "voting machine" }) );
    set_short( "a voting machine" );
    set_long( "This is an outdated Diebold voting machine. "
      "Someone has painted it orange and re-purposed it "
      "for use with halloween pumpkin voting. The screen is "
      "displaying some options. The options are: help, "
      "register, pumpkinlist, and vote." );
    set_gettable( 0 );
}

void extra_init()
{
    add_action( "reg" , "register" );
    add_action( "help", "help"     );
    add_action( "list", "pumpkinlist" );
    add_action( "vote", "vote"     );
}

int help( string arg )
{
    if( !stringp( arg ) )
    {
      tell_player( THISP, "There is a pumpkin carving contest going on. "
        "The rules are easy:\n\n"
        "Carve a pumpkin.\n"
        "Photograph the pumpkin (including proof of who you are).\n"
        "Upload the image somewhere.\n"
        "Register.\n"
        "Vote.\n"
        "\nYou can vote without registering a pumpkin photo if you want. "
        "It is one vote per player it will be tracked, tabulated, etc. "
        "Also, you can't vote for yourself! Have fun!\n" 
        "\nOther help functions are, help register, help vote, "
        "help pumpkinlist" );
      return 1;
    }
    if( arg == "register" )
    {
      tell_player( THISP, "Registration is easy. Simply type register "
        "followed by the web address of your image!\n" );
      return 1;
    }
    if( arg == "vote" )
    {
      tell_player( THISP, "In order to vote, type vote followed by the "
        "name of the player you are voting for. Don't vote for yourself. "
        "Something nasty will happen to people who vote for themselves.\n" );
      return 1;
    }
    if( arg == "pumpkinlist" )
    {
      tell_player( THISP, "Pumpkinlist will print you a list of registered "
        "entrants and the web address where you can find their "
        "pumpkin!\n" );
      return 1;
    }
}

int reg( string arg )
{
    string *ipaddy = grab_file( IPFILE );
    string *registered = grab_file( REGFILE );
    string ip = query_ip_number( THISP );
    string name = THISP->query_real_name();
    if( !stringp( arg ) )
      return notify_fail( "You need to provide a web address.\n" );
    if( is_wizard( THISP ) )
    {
      write_file( REGFILE, sprintf( "%s has a pumpkin at %s\n",
        CAP( name ), arg ) );
      tell_player( THISP, sprintf( "You registered your pumpkin "
        "picture at %s.\nIf this is incorrect please mail "
        "Socialism.\n", arg ) );
      return 1;
    }      
    
    if( member( ipaddy, ip ) > -1 )
    {  
      return notify_fail( "You have already registered!!! If there "
        "was an error in your registration please mail Socialism.\n" );
    }
    write_file( REGFILE, sprintf( "%s has a pumpkin at %s\n",
      CAP( name ), arg ) );
    write_file( IPFILE, sprintf( "%s\n", ip ) );
    tell_player( THISP, sprintf( "You registered your pumpkin picture "
      "at %s.\nIf this is incorrect please mail Socialism.\n", arg ) );
    return 1;
}

int list( string arg )
{
    
    string *registered = grab_file( REGFILE );
    if( sizeof( registered ) == 0 )
      return notify_fail( "No one has registered!\n" );
    ansi_tell( THISP, "*********************\n", YEL );
    tell_player( THISP, sprintf( "%s\n", 
      ( implode( registered, "\n" ) ) ) );
    ansi_tell( THISP, "*********************\n", YEL );
    return 1;
}

int vote( string arg )
{
    string *voteips = grab_file( VOTEDFILE );
    string ip = query_ip_number( THISP );
    string name = THISP->query_real_name(); 
    if( !stringp( arg ) )
      return notify_fail( "Syntax is vote <who>.\n" );
    
    if( is_wizard( THISP ) )
    {
      tell_player( THISP, sprintf( "You voted for %s! If "
        "you are unhappy with this vote, mail Socialism.\n",
        arg ) );
      write_file( VOTESFILE, sprintf( "%s voted for %s\n",
        THISP->query_real_name(), arg ) ); 
      return 1;
    }
    
    if( member( voteips, ip ) > -1 )
    {   
      tell_player( THISP, "You already voted!!! If you are " 
        "unhappy with this vote, mail Socialism.\n" );
      return 1;
    }
    tell_player( THISP, sprintf( "You voted for %s! If "
        "you are unhappy with this vote, mail Socialism.\n",
        arg ) );
    write_file( VOTESFILE, sprintf( "%s voted for %s, %s\n",
        THISP->query_real_name(), arg, ip ) );
    write_file( VOTEDFILE, sprintf( "%s\n", ip ) );
        
    return 1;
}
