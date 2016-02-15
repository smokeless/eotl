inherit "/secure/player/body.c";

#define OK ({ \
             "/adm/bin/passtool", \
           })
#define FAIL(q) return( printf("TempBody: %s\n",q), 0 );

string *Ok;

static
status
check_secure( string s )
{
  if( member(Ok, s) == -1 ||
     remote_command() )
    {
      return 0;
    }
    return 1;
}

status 
restore_pdata( string name ) 
{
  int tmp;
  string err;

  if( !check_secure( load_name( previous_object() ) ) )
    {
      FAIL("No permission to read\n")
    }
  if( err=catch( 
       tmp = restore_object( sprintf( "/etc/pdata/%c/%s", name[0], name ) ) )
       || !tmp )
    {
      FAIL("pdata read error: "+err)
    }
  set_living_name( name );
  set_heart_beat( 1 );
  ::move_player_to_start();
  return 1;
}
 
status
save_pdata( string file ) 
{
  string err;
  if( !check_secure( load_name( previous_object() ) ) )
    {
      FAIL("No permission to read\n")
    }
  
  if( err=catch( save_object( file ) ) )
    {
      FAIL("pdata write error: "+err)
    }
  return 1;
}
 
create() 
{
  seteuid(getuid());
  ::create(); 
  Ok=OK;
}
