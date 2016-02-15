//Taplash room creator.
//Taplash 2015
/*
To do:
Fix absolute path. That sucks.
*/

inherit NewThingCode;
string includeFile;
int roomNumber = 0;

void extra_create()
{
    set_ids(({"zapper", "room zapper" }));
    set_short( "Taplash's room zapper");
    set_long( "Building large area files by hand is not fun. "
      "Let the zapper handle it. Zap those things to life.\n\n" 
      "Here's how you do it, zap north will add a north exit "
      "to the current room. Then make a room linked to the current "
      "room. Then you FTP in and grab them all, and just edit it based "
      "on plans. Lets you make skeleton areas super fast. "
      "Which is good.\n\n"
      "Hidden features:\n"
      "num $number: set the number of new file.\n"
      "include $file: set your personal include file.\n"
      "showme: Shows you current settings.\n\n"
      "The bad:\n"
      "You can/or will damage your existing areas with this tool. "
      "I'm not responsible for damage to areas. Back up your shit. "
      "You must be in the dir you are creating for. "
      "You're a wizard. You figure it out. "
      "Also unfortunately this uses absolute paths. "
      "So you'll need to search replace all instances of /usr/you/file.c "
      "to ROOM file. Much of this will be fixed if it annoys me enough. "
      "if it annoys you enough, you fix it, let me know and we'll update.\n\n"
      "Version: Alpha 3.");
    set_weight(0);
}

void extra_init()
{
    add_action("zap", "zap");
    add_action("include", "include");
    add_action("num", "num" );
    add_action("showme", "showme" );
}

int showme()
{
    if( !stringp(includeFile))
    {
        tell_player( THISP, sprintf("No include file set.\nNumber: %i",
          roomNumber));
        return 1;
    }
    tell_player( THISP, sprintf("Include file: %s\nNumber: %i",
      includeFile, roomNumber));
    return 1;
}

int num( string arg )
{
    int y = to_int( arg );
    if( !stringp(arg) )
        return notify_fail( "buh.\n");
    if(!is_wizard(THISP))
        return notify_fail("OMG get cycled.\n");
    if(!y)
        return notify_fail("Look at this guy. That's not a number.\n");
    roomNumber = y;
    tell_player( THISP, sprintf("Room number set to %i", roomNumber));
    return 1;
}

int include( string arg )
{
    if(!stringp(arg))
        return notify_fail( "Uh. Wat?\n");
    if(!is_wizard(THISP))
        return notify_fail("OMG get cycled.\n");
    includeFile = arg;
    tell_player( THISP, sprintf("Using %s as include file.",
      includeFile));
    return 1;
}

int zap( string arg )
{
    if(!is_wizard(THISP))
        return notify_fail("Wiz only n000b\n" );
    
    string dir;
    //Log it.
    if( THISP->query_real_name() != "taplash" )
    {
      write_file("/usr/taplash/wiztoy/wiztoy.log",
        sprintf("%s used the zapper on %s.\n",
          THISP->query_real_name(), ctime() ));
    }
    
    mapping exits = ([ "north" : "south",
                    "south" : "north",
                    "east"  : "west",
                    "west"  : "east",
                    "up"    : "down",
                    "down"  : "up", 
                    "northwest" : "southeast",
                    "northeast" : "southwest",
                    "southwest" : "northeast",
                    "southeast" : "northwest"
    ]);
    //Don't create asshat exits.
    if( !member( exits, arg ) )
    {
        tell_player( THISP, "Not a valid exit." );
        return 1;
    }
    //direction
    dir = arg;    
    
    //Didn't set an include file? You suck.
    if(!stringp(includeFile))
        return notify_fail( "Set an include file with include $name.\n");
    
    string baseFile = sprintf(
      "//Created with Taplash's room zapper!@#!\n"
      "#include<%s>\n"
      "inherit RoomPlusCode;\n"
      "void extra_create()\n"
      "{\n"
      "    set(\"short\", \"Room\");\n"
      "    set(\"day_long\", \"skeletonroom!\");\n"
      "    set( \"descs\", ([]));\n"
      "\n    set( \"reset_data\", ([]));\n ", includeFile );
    
    string currentRoomPath = to_string( ENV( THISP ) );
    mapping existExits = ENV( THISP )->query("exits");
    
    
    string newRoom = to_string( roomNumber);
    
    //back up? Do I need this?
    rename( sprintf( "%s.c", currentRoomPath ), sprintf("%s.bak", currentRoomPath ) );
    write_file( sprintf( "%s.c", currentRoomPath ), sprintf( 
      "    %s\n"
      "    set( \"exits\", %O );\n"
      "    add( \"exits\", ([ \"%s\" : \"%s\" ]) );\n"
      "    replace_program(); //makes the driver happy.\n"
      "}", baseFile, existExits, dir, newRoom ) );
    
    write_file( sprintf( "%s.c", newRoom), sprintf("%s\n    add( \"exits\", ([\n "
      "      \"%s\" : \"%s\" ]) );\n"
      "    replace_program(); //makes the driver happy.\n"
      "}", baseFile, exits[arg], currentRoomPath ) );
    roomNumber = roomNumber + 1;
    tell_player( THISP, sprintf("You zap a new room %s.", dir ));
    tell_room( ENV( THISP ), sprintf( "%s zaps a new room %s.", THISP->query_name(),
      dir ), ({ THISP }));
    object *p = all_inventory( ENV(THISP));
    object *people = filter( p, #'living );
    call_out( "move_us", 2, people, currentRoomPath );
    destruct( to_object( currentRoomPath ) ) ;
    load_object( currentRoomPath );
    clone_object( currentRoomPath );
    
    return 1;
}

void move_us( object *people, object place )
{
    object *p = people;
    object currentRoomPath = place;
    foreach( object o : p )
    {  
      move_object( o, to_string( currentRoomPath ) );
      tell_player( o, "You return to your current project.");
    }
    return;
}
