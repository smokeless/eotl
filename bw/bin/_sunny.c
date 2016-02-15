#define SYNTAX "sunny [-nl] [/i] <string>"
#define HELP   "This searches the password file for all users that match " +\
               "the login site by site name or site number or by wizard " +\
               "level.  If the first option is omitted, it will search " +\
               "for any user who has logged in from a site name with the " +\
               "specified string in it.  If you use the '-n' option, it " +\
               "will search for any user who has logged in from a site " +\
               "where the string matches the first part of the IP " +\
               "number.  If you use the '-l' option, this will provide a " +\
               "list of all users of the level specified in string.  " +\
               "Valid level strings are:  guest, frob, wizard, elder, " +\
               "arch, god, other.  Other provides a list of users that " +\
               "have a player type different than 'player' or 'wizard'. " +\
               "The '/i' option will provide a list with more infomation " +\
               "about each user."
 
#define NOTIFY(x)       sprintf("%sBW%% %s%s\n",HIG,norm,x)
#define OPT1 ({ "n", "l" })
#define OPT2 ({ "i" })
#define LEVELS ({ "guest", "frob", "wizard", "elder", "arch", "god", \
                  "other" })
 
#include "/usr/moejoe/bw2/cmd.h"
 
string *search_by_number( string arg, string opt );
string *search_by_level( string arg, string opt );
string *search_by_name( string arg, string opt );
status name_sort( string one, string two );
 
status cmd_sunny( object me, string arg )
{
  int i;
  string *names, report, opt1, opt2;
 
  Init;
  if( !arg || arg == "" )
    Exit( SYNTAX );
  opt1 = 0;
  opt2 = 0;
  sscanf( arg, "-%s %s", opt1, arg );
  sscanf( arg, "/%s %s", opt2, arg );
  if( !arg || arg == "" )
    Exit( SYNTAX );
  if( opt1 && index( OPT1, opt1 ) == -1 )
    Exit( sprintf( "Invalid option: %s", opt1 ) );
  if( opt2 && index( OPT2, opt2 ) == -1 )
    Exit( sprintf( "Invalid option: %s", opt2 ) );
  if( opt1 == "l" && index( LEVELS, arg ) == -1 )
    Exit( sprintf( "Invalid level: %s", arg ) );
 
  switch( opt1 )
  {
    case "n" :
      names = search_by_number( arg, opt2 );
      break;
    case "l" :
      names = search_by_level( arg, opt2 );
      break;
    default :
      names = search_by_name( arg, opt2 );
  }
  report = "";
  names = sort_array( names, #'name_sort, THISO );
  for( i=0; i<sizeof(names); i++ )
  {
    report += names[i] + "\n";
  }
  if( !opt2 )
    report = sprintf( "%-#78s\n", report );
  report += NOTIFY( sprintf( "%d users", sizeof(names) ) );
  me->more_string( report );
  return( 1 );
}
 
string *search_by_number( string arg, string opt )
{
  int i;
  mixed record;
  string *names, junk;
 
  names = ({ });
  i = 0;
  while( record = PASSWDKEEPER->userNumber(i) )
  {
    if( sscanf( record[4], arg+"%s", junk ) == 1 )
    {
      if( opt == "i" )
      {
        names += ({ sprintf( "%-12s %-6s %-6s %-15s %-24s", record[0],
         record[2], record[3], record[4], ctime( record[5] ) ) });
      }
      else
      {
        names += ({ record[0] });
      }
    }
    i++;
  }
  return( names );
}
 
string *search_by_level( string arg, string opt )
{
  int i;
  mixed record;
  string *names, junk;
 
  names = ({ });
  i = 0;
  if( arg == "other" )
  {
    while( record = PASSWDKEEPER->userNumber(i) )
    {
      if( record[3] != "player" && record[3] != "wizard" )
      {
        if( opt == "i" )
        {
          names += ({ sprintf( "%-12s %-24s %-26s", record[0], 
	  string_time( time() - atoi( record[5] )), record[6] ) });
        }
        else
        {
          names += ({ record[0] });
        }
      }
      i++;
    }
  }
  else
  {
    while( record = PASSWDKEEPER->userNumber(i) )
    {
      if( record[2] == arg )
      {
        if( opt == "i" )
        {
          names += ({ sprintf( "%-12s %-24s %-26s", record[0], 
	  string_time( time() - atoi( record[5] )), record[6] ) });
        }
        else
        {
          names += ({ record[0] });
        }
      }
      i++;
    }
  }
  return( names );
}
 
string *search_by_name( string arg, string opt )
{
  int i;
  mixed record;
  string *names, junk;
 
  names = ({ });
  i = 0;
  while( record = PASSWDKEEPER->userNumber(i) )
  {
    if( sscanf( record[6], "%s"+arg+"%s", junk, junk ) == 2 )
    {
      if( opt == "i" )
      {
        names += ({ sprintf( "%-12s %-6s %-6s %-24s %-26s", record[0],
         record[2], record[3], ctime( record[5] ), record[6] ) });
      }
      else
      {
        names += ({ record[0] });
      }
    }
    i++;
  }
  return( names );
}
 
status name_sort( string one, string two )
{
  return( strcmp( one, two ) );
}
