#define SYNTAX "crypt <-d -r> <file(s)> <encryption password>"
#define HELP "Encrypts or Decrypts files.  Default is to encrypt.\
\n-d = decrypt.  -r = read encrypted files."
#include "/usr/zippo/bw/cmd.h"
 
mixed cmd_crypt(object me, string arg)
{ string pwd, key, whassup, hellstring;
  string *files, *lines;
  int a, i, j, k, sz, dick, linesz;
 
  Init;
  
  hellstring = "";
  
  seteuid(geteuid());
  if( explode(geteuid(me),":")[0] != geteuid()) Exit("inherit _crypt");
  if( ! arg ) Exit(SYNTAX);
  
  whassup = "e";
  if( sscanf( arg, "-d %s", arg ) )  whassup = "d";
  if( sscanf( arg, "-r %s", arg ) )  whassup = "r";
  if( whassup != "e" && whassup != "d" && whassup != "r" )
  Exit("Encrypt, Decrypt or Read?");
  if( sscanf( arg, "%s %s", arg, pwd ) != 2 )
  Exit(SYNTAX);
  if( ! (i = sizeof( files = me->ExpandFiles(({ arg })))))
  Exit("No files.");
  if( strlen(pwd) < 8 ) Exit("You password is less than 8 chars long.");
//============={ THIS IS THE ENCRYPTION PART }=======================
  if( whassup == "e" )
  while( i-- )
  { //======={ initialize some schitt }============================
    lines = grab_file( files[i] );
    linesz = sizeof( lines );
    a = 0;  key = "";  j = 10;  dick = 0;
    //======={ make an encryption key that's longer than the file length}== 
    for( k = 0; k < linesz; k++ )
    { a += strlen( lines[k] );
    }
    while( strlen( key ) < a )
    { key += crypt( pwd, to_string( j ) );
      j++;
    }
    //=============================================================
    for( k = 0; k < linesz; k++)  
    {
     sz = strlen( lines[k] );
     for( j = 0; j < sz; j++ )
     { lines[ k ][ j ] =   lines[ k ][ j ] + key[ dick ]%32;
       dick ++;
     }
     hellstring += lines[k] + "\n";
    }
    pwd = crypt( pwd, "99");           
    hellstring += pwd + "\n" + to_string( a ) + "\n";
    rm( files[i] );
    write_file( files[i], hellstring );
  }
 
//==========={ DECRYPTION, YOU MOTHER FOOKER }==========================
  if( whassup == "d" || whassup == "r" )
  while( i-- )
  { //========{ initialize some schitt }===============
    lines = grab_file( files[i] );
    linesz = sizeof( lines );
    a = to_int(lines[linesz-1]);
    j = 10;
    dick = 0;
    key = "";
    //========{ make a fugging decryption key }=========
    while( strlen( key ) < a )
    { key += crypt( pwd , to_string(j) );
      j ++;
    }
    //========{ actual decryption }=====================
    if( crypt( pwd, "99") == lines[linesz-2] ) //pwd ok
    for( k = 0; k < linesz-2; k++)  
    {
     sz = strlen( lines[k] );
     for( j = 0; j < sz; j++ )
     { lines[k][j] = lines[k][j] - key[dick]%32;
       dick ++;
     }
     hellstring += lines[k] + "\n";
    }
    else
    Exit("Heh, your password didn't work, buttmunch.");
    
    if( whassup == "d" )
    {
    rm( files[i] );
    write_file( files[i], hellstring );
    }
    
    if( whassup == "r" )
    me->more_string(hellstring);
  }
  Exit("SuckaAss, Baby!");
}
