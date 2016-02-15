#include <facility.h>

inherit NewThingCode;
inherit AnsiTellCode;

void extra_create()
{
    set_ids( ({ "board", "ouija", "spirit board", "ouija board", 
      "spirit board" }) );
    
    set_short( "a spirit board" );
    set_ansi_short( HIP "a spirit board" );
    
    set_long( "There are a couple phrases and the entire "
      "alphabet burned onto this old oak board. The wood is dried "
      "and cracking, but it appears to still be useable. "
      "It might be possible for you to divine something "
      "with it. Then again it might not. You could just "
      "write something out with it for fun." );
    
    set( NoStoreP, 1);
    
    set_weight( 300 );
    
    set_value( 40 );
}

void extra_init()
{
    add_action( "divine",  "use" );
    add_action( "divine",  "divine" );
    add_action( "makemsg", "write" );
}

int divine( string strarg )
{
    string *responses = grab_file( FOBJ "letters" );
    string *words = grab_file( FOBJ "boarddict" );
    
    int power = THISP->query_stat( "wil" ) + 
      THISP->query_stat( "int" );
    int resnum = random( sizeof( responses ) );
    int wordnum = random( sizeof( words ) );
    
    object hero = ENV( THISP );
    
    if( ENV( THISO ) != THISP )
    {    
      return 0;
    }

    if( !stringp( strarg ) || ( member( query_ids(), 
      strarg ) == -1 ) )
    {
      return notify_fail( query_verb()  + " what?\n" );
    } 

    if( power <= 50 )
    {
      ansi_tell( THISP, "You look at the board trying "
        "to discern what you could possibly use it for. \n"
        "It seems very confusing. \n", HIP );
      
      tell_room( hero, sprintf( "%s stares at the letters on a spirit board, "
        "totally baffled.\n", THISP->query_name() ), ({ THISP }) );
      
      return 1;    
    }
    
    if( power >= 50 && power <= 125 && THISP->query_mana() > power )
    {
      ansi_tell( THISP, sprintf( "The board tugs and pulls at you, "
        "stopping on %s.\n", responses[resnum] ), HIP );
      
      tell_room( hero, sprintf( "%s gleans information from beyond.\n",
        THISP->query_name() ), ({ THISP }) );

      THISP->add_mana( -power );      
    
      return 1;
    }
    
    else if( power >= 126 && THISP->query_mana() > power )
    {
      ansi_tell( THISP, sprintf( "Your mind hones into the "
        "board, it spells out %s.\n", words[wordnum] ), HIP );

      tell_room( hero, sprintf( "%s gleans information from beyond.\n",
        THISP->query_name() ), ({ THISP }) );
     
      THISP->add_mana( -power );
      
      return 1;
    }


    else
    {  
      ansi_tell( THISP, "You do not have the power to " 
        "do that.\n", HIP );
      
      return 1;
    } 
 
    return 1;
} 

int makemsg( string strarg )
{
    int ppower = THISP->query_stat( "int" ) +
      THISP->query_stat( "wil" );
    
    int chrp = THISP->query_stat( "chr" );
    
    if( ENV( THISO ) != THISP )
    {    
      return 0;
    }

    if( !stringp( strarg ) || strarg != "on board" )
    {
      return notify_fail( CAP( query_verb() ) + " on what?\n" );
    }
    if( ppower >= 176 && THISP->query_mana() > 
      ppower && chrp > 50 )
    {
      input_to( "makesomething", 4, "Begin your message: \n" ); 
      return 1;
    }
    else
    {  
    ansi_tell( THISP, "You do not have the power "
      "to do that.\n", HIP );
    
    return 1;
    }
}
void makesomething(string strinput)
{ 
    string *ethers = grab_file( FOBJ "ether" );
    
    int ppower = THISP->query_stat( "int" ) +
      THISP->query_stat( "wil" ); 
    int ethersnum = random( sizeof( ethers ) );
    
    write_file( FOBJ "ether", sprintf("%s left: %s in the ether. \n", 
        THISP->query_name(), strinput ) );
    
    ansi_tell( THISP, "You scrawl a message into "
         "the ether.\n", HIP );
    ansi_tell( THISP, sprintf( "Something comes through the "
      "ether, %s\n", ethers[ ethersnum ] ), HIP );
    
    ansi_tell_room( ENV( THISP ), sprintf( "%s records to the ether.\n",
      THISP->query_name() ), HIP, ({ THISP }) );
    
    THISP->add_mana( -ppower + random( 3 ) );
}
