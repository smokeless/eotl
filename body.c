inherit "/secure/wizard/body";

#define PDATA "/etc/pdata/"

int set_it_up( string who )
{
   string file;
   
   seteuid( getuid() );
   file = sprintf( "%s%c/%s", PDATA, who[0], who );
   
   if( file_size( file ) )
   {
       return( restore_object( file ) );
   }
   return( 0 );
}

void save_schitt( string where )
{
    seteuid( getuid() );
    save_object( where );
}

void save_me( )
{

}
