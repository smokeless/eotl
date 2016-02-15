inherit NewThingCode;

#include <facility.h>
#include <sys/input_to.h>
#include <sys/files.h>

int junk;

void extra_create()
{
    set_ids( ({ "kiosk", "machine", "computer" }) );
    set_short( "an application kiosk" );
    set_ansi_short( sprintf( "%san application kiosk%s", HIC, NORM ) );
    set_long( "Ergonomically shaped plastic gives away to a "
      "cheap keyboard, and a low end nine inch display. The Grey "
      "plastic is dirty and brittle with age, and the letters on "
      "the keys have been worn down to an almost indistinguishable "
      "level. There is a smell of burning plastic coming off of "
      "the whole object. A cord completely bare of any "
      "insulation snakes across the carpet sparking occasionally. " 
      "Even though the machine is too heavy to pick up, it seems "
      "to be set in an unstable manner." );
    
    set_descs( ([ "cord" : "This whole set up looks like a "
      "huge fire hazard, it should be unplugged."
    ]) );
    set( NoStoreP, 1 );
    set_gettable( 0 );
    set_droppable( 0 );
    junk = random( 6 ) + 1;
}

void reset()
{
    junk = random( 6 ) + 1;
}   

void extra_init()
{
    add_action( "apply", "use" );
    add_action( "cord", "unplug" );
    add_action( "smoke", "shake" );
    add_action( "smoke", "push" );
}

int cord( string arg )
{
    
    object idiot = ENV( THISP );
    int dama = THISP->query_stat( "con" );
    int dam = dama + random( ( dama / 2 ) );
    int hp = THISP->query_hp();
    if( !stringp( arg ) || ( member( query_ids(), arg ) == -1 ) )
      {
        return notify_fail( CAP( query_verb() ) + " what?\n" );
      } 
    
    if( dam > hp )
    {
       tell_object( THISP, "You aren't feeling up to it.\n" );
       return 1;
    }
    
    tell_object( THISP, sprintf( "%sYou reach your hand down and "
      "attempt to pull the cord out of the socket.%s\n", RED, NORM )
    );
    tell_object( THISP, sprintf( "%sThe electricity arcs across your "
      "skin, you suddenly feel more alive than you have ever "
      "felt in your life. Right up until your vision goes black.%s\n", 
       HIC, NORM ) );
    tell_room( idiot, sprintf( "%s%s reaches down and attempts to unplug "
      "the machine. You are temporarily blinded by a gigantic flash, "
      "when you can see again, %s is gone.%s\n", HIC, THISP->query_name(), 
      THISP->query_name(), NORM ), ({ THISP }) );
    
    THISP->add_hp( -dam );
    THISP->move_player( "&&", "/zone/null/eternal/common", 1 );
    
    tell_room( ENV( THISP ), sprintf( "%s erupts from the ground, skin "
      "still smoldering.\n", THISP->query_name() ), 
      ({ THISP }) );
    return 1;
}

int smoke( string arg )
{
    object machine = ENV( THISO );
    if( !stringp( arg ) || ( member( query_ids(), arg ) == -1 ) )
      {
        return notify_fail( CAP( query_verb() ) + " what?\n" );
      } 
    tell_object( THISP, "You, push, pull, and violently shake the kiosk.\n" );
    tell_room( machine, sprintf( "The kiosk makes horrible noises and begins to "
      "smoke slightly as %s shakes it.\n", THISP->query_name() ), ({ THISP }) );
    if( !junk )
      {
       tell_object( THISP, "Nothing seems to happen.\n" ); 
       return 1;
      }
    tell_room( machine, "Something shakes loose from the kiosk!\n" );
    move_object( clone_object( FOBJ "kioskjunk" ), machine );
    junk = junk - 1;
    return 1;
}

int apply( string arg )
{    
    string playername = THISP->query_real_name();
    string *people = get_dir( FAPP+"*" );
    object machine = ENV( THISO );
    if( !stringp( arg ) || ( member( query_ids(), arg ) == -1 ) )
      {
        return notify_fail( CAP( query_verb() ) + " what?\n" );
      }
       
    tell_object( THISP, "You push a few buttons on the kiosk, "
      "bringing up the application page.\n" );
    tell_room( machine, sprintf( "%s walks over to the kiosk, "
      "and starts %s application process.\n", THISP->query_name(), 
      possessive( THISP ) ), ({ THISP }) );
    tell_object( THISP, "Welcome to the Facility 31 application process, "
      "this is a two step application process, starting here at the kiosk, "
      "and ending at your interview. We are looking forward to having you "
      "as a new team member. This first stage is designed to test your "
      "personality fit with Facility 31. There will be multiple questions, "
      "please answer \"y\" for yes, and \"n\" for no. You can quit "
      "the process at anytime by, entering anything other than, "
      "\"y\" or \"n\". Should you choose to exit the process your answers "
      "will not be saved. As such we here at Facility 31 recommend you "
      "only begin the application if you have adequate time.\n"
      "From all of us on team 31, good luck!!!\n\n" );
    
//Important to not forget that the first input is here.
    input_to( "ques1", INPUT_PROMPT, "Have you ever been convicted of "
       "a crime? \n" );
    return 1; 
}    

int ques1( string arg )
{
   
   string whoisthis = THISP->query_real_name();
   write_file( FAPP+"/"+whoisthis, sprintf( "%s\n", arg ) );
    
   if( arg == "y" )
    { 
      input_to( "ques2", INPUT_PROMPT, "Do you believe in ghosts? \n" );
      write_file( FAPP+"/"+whoisthis, sprintf( "%s\n", arg ) );
      return 1;
    } 
    if( arg == "n" )
    {
      input_to( "ques2", INPUT_PROMPT, "Do you believe in ghosts? \n" );
      write_file( FAPP+"/"+whoisthis, sprintf( "%s\n", arg ) );
      return 1;
    }
    else 
    tell_object( THISP, "The application process has been "
      "canceled. Feel free to come back when you have more time.\n" );
    rm( FAPP+"/"+whoisthis );
    return 1;
}

int ques2( string arg )
{
   string whoisthis = THISP->query_real_name(); 
   if( arg == "y" )
    { 
      input_to( "ques3", INPUT_PROMPT, "Alien abductions? \n" );
      write_file( FAPP+"/"+whoisthis, sprintf( "%s\n", arg ) );
      return 1;
    } 
    if( arg == "n" )
    {
      input_to( "ques3", INPUT_PROMPT, "Alien abductions? \n" );
      write_file( FAPP+"/"+whoisthis, sprintf( "%s\n", arg ) );
      return 1;
    }
    else 
    tell_object( THISP, "The application process has been "
      "canceled. Feel free to come back when you have more time.\n" );
    rm( FAPP+"/"+whoisthis );
    return 1;
}

int ques3( string arg )
{
 string whoisthis = THISP->query_real_name(); 
   if( arg == "y" )
    { 
      input_to( "ques4", INPUT_PROMPT, "Astral projections? \n" );
      write_file( FAPP+"/"+whoisthis, sprintf( "%s\n", arg ) );
      return 1;
    } 
    if( arg == "n" )
    {
      input_to( "ques4", INPUT_PROMPT, "Astral projections? \n" );
      write_file( FAPP+"/"+whoisthis, sprintf( "%s\n", arg ) );
      return 1;
    }
    else 
    tell_object( THISP, "The application process has been "
      "canceled. Feel free to come back when you have more time.\n" );
    rm( FAPP+"/"+whoisthis );
    return 1;
}
int ques4( string arg )
{
 string whoisthis = THISP->query_real_name(); 
   if( arg == "y" )
    { 
      input_to( "ques5", INPUT_PROMPT, "Have you ever been terminated? \n" );
      write_file( FAPP+"/"+whoisthis, sprintf( "%s\n", arg ) );
      return 1;
    } 
    if( arg == "n" )
    {
      input_to( "ques5", INPUT_PROMPT, "Have you ever been terminated? \n" );
      write_file( FAPP+"/"+whoisthis, sprintf( "%s\n", arg ) );
      return 1;
    }
    else 
    tell_object( THISP, "The application process has been "
      "canceled. Feel free to come back when you have more time.\n" );
    rm( FAPP+"/"+whoisthis );
    return 1;
}  

int ques5( string arg )
{
 string whoisthis = THISP->query_real_name(); 
   if( arg == "y" )
    { 
      input_to( "ques6", INPUT_PROMPT, "Have you ever been killed? \n" );
      write_file( FAPP+"/"+whoisthis, sprintf( "%s\n", arg ) );
      return 1;
    } 
    if( arg == "n" )
    {
      input_to( "ques6", INPUT_PROMPT, "Have you ever been killed? \n" );
      write_file( FAPP+"/"+whoisthis, sprintf( "%s\n", arg ) );
      return 1;
    }
    else 
    tell_object( THISP, "The application process has been "
      "canceled. Feel free to come back when you have more time.\n" );
    rm( FAPP+"/"+whoisthis );
    return 1;
}

int ques6( string arg )
{
    string hero = THISP->query_name();
    object machine = ENV( THISO );
    string whoisthis = THISP->query_real_name();
    string *quickcheck;
    quickcheck = ({ "y", "n" });
    if( ( member( quickcheck, arg ) == -1 ) )
    {
      tell_object( THISP, "The application process has been "
      "canceled. Feel free to come back when you have more time.\n" );
    rm( FAPP+"/"+whoisthis );
    write_file( FAPP+"/"+whoisthis, sprintf( "%s\n", arg ) );
    return 1;
    }
    
    tell_object( THISP, "You have completed your application, "
       "expect to hear from us promptly. Best of luck!\n"
     );
    tell_room( machine, sprintf( "A disk shoots out of the machine "
      "into the hands of %s\n", hero ), ({ THISP }) );
    tell_object( THISP, "A floppy disk flies out of the machine.\n" );
    move_object( clone_object( FOBJ "disk" ), THISP );
    tell_object( THISP, sprintf( "%sYou are grasped by cold hands and pulled "
      "through the ether.\n%s", HIY, NORM ) 
    );
    tell_room( machine, sprintf( "Suddenly a pair of hands reach out "
      "from the ether and pull %s in!\n", hero ) , ( {THISP} )
    );
    THISP->move_player( "&&", FROOM "skeloff", 1 );
    tell_room( ENV( THISP ), sprintf( "%s smashes to the ground.\n",
      hero ), ({ THISP }) );
    tell_object( THISP, sprintf( "%sEverything about you hurts "
      "your skin stings as you take in your new environment.%s\n", 
      HIY, NORM )
    );
    
}
