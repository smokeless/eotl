//Insy @ EoTL
//Tracker 
//  Added NoScryP check 8-2010   Dorf
#define MAXRADIUS 8
inherit ObjectCode;
object hunteddude, hunterdude;
mixed *level, *master_rooms;
int radius, was_in = 0, auto_attack = 0, c_radius = 50;
string obname, obtwoname;

//Mapper 
mixed c_specials( mixed theroom );
#define NoMapCabal ({\
	"baronar_member", "yxuxacta_member", \
})
#define NoMapPath ({\
	"/zone/fantasy/africa/rooms/celtic/",\
})
#define Radius 8
#define X_MAX (Radius*8+2)
#define Y_MAX (Radius*4+2)
#define MAX_LENGTH 24
#define WIDTH 100
mapping ring;
//key=room (must exist)
//0 = X_Coordinate
//1 = Y_Coordinate
//2 = fCheck
//3 = picture
mapping legend;
mixed *sring, pic_counter, pic_counter_temp;
int fCheck_exists, fverbose, fmonster, map_counter, x, y, test, imod;
string *coordinates,str;


extra_create()
{
   add("id", ({ "tracker", "radar", "sensor" }) );
   set("long",strformat(
      "This is a tracker.  The auto-attack option has been "+option()+
      ".  Type 'thelp' for more information.") );
   set("short","a tracker");
set( "value", 1200 );
    set(NoStoreP, 1);
set_limit(1);
   set( "weight",20 );
   //mapper settings
	fmonster=0;	//default settings
	fverbose=1;	//default settings

   //tracker settings
   radius = MAXRADIUS;
}

extra_init()
{
   add_action("prep_func","track");
   add_action("stoppage","stop" );
   add_action("set_auto_attack","set");
   add_action("thelp","thelp");
   add_action("mappage","map");
}

disp_help()
{
	write("Usage: map [-b -v -m -h -?]\n");
	write("-h or ?: Help Screen.\n-b: brief mode.\n-v: verbose mode (includes a legend).\n-m: display monsters.\n");
	write("Example: map -vm is a verbose mode map displaying monsters.\n");
	write( strformat( "\nNote: This will map only logical exits well.    Up and down directions aren't included in the display.\n" ) );
}

thelp()
{
   write("Commands:\n"+
      "track <living object's name>   : Initiates tracking sequence.\n"+
      "track monster                  : Tracks monster(s) currently in your room.\n"+
      "stop tracking                  : Stops tracking current victim.\n"+
      "set auto-attack on             : Enables auto-attack option.\n"+
      "set auto-attack off            : Disables auto-attack option.\n"+
      "                                 Auto-attack parameter is currently "+option()+".\n"+
      "map [-b -v -m -h -?]           : -b map surrounding area in brief mode.\n"+
      "                               : -v map surrounding area in verbose mode.\n"+
      "                               : -m display monsters in map mode.\n"+
      "                               : -h or -? display mapping help.\n"+
"\nPlease mail all comments, suggestions, bugs, etc... to Malice. Thank you.\n"+
      endl);
   return 1;
}
string option()
{
   if( auto_attack ) return( "enabled" );
   return( "disabled" );
}

set_auto_attack( string arg )
{
   if( !arg ) return;
   if( arg == "auto-attack on" ){
      if( hunteddude ){
         tell_object( hunteddude,"You cringe in terror as you realize "+
          "your foe wants you dead!\n" );
      }
      write("Auto-attack option activated.\n");
      auto_attack = 1;
      return 1;
   }
   if( arg == "auto-attack off" ){
      write("Auto-attack option deactivated.\n");
      auto_attack = 0;
      return 1;
   }
   if( explode( arg, " " )[0] == "auto-attack" ){
      auto_attack++;
      auto_attack %= 2;
      if( auto_attack ){
         if( hunteddude ){
            tell_object( hunteddude,"You cringe in terror as you realize "+
             "your foe wants you dead!\n" );
         }
         return( write("Auto-attack option activated.\n") , 1 );
      }else
         return( write("Auto-attack option deactivated.\n"), 1 );
      return 1;
   }
}

thwack()
{
  if( !hunteddude )
    return 0;

   tell_object( hunterdude, "You are in the same room as "+
      capitalize( hunteddude->query_real_name() )+"!\n");

   if( present( hunteddude, ENV( THISP ) ) && auto_attack && !( hunterdude->query_npc() ) ){
      tell_object( hunterdude, "You feel an explosive force from the tracker as you are hurled towards "+
         capitalize( hunteddude->query_real_name() )+".\n");
      command( "kill " + hunteddude -> query_real_name(), hunterdude );
   }

}

get_monster(string monster)
{
   object *monsters;

   monsters = clones( monster[1..] );
   if( sizeof( monsters ) >= 1 )
      hunteddude = monsters[0];
}

stoppage(string arg)
{
   if( !arg ) return;
   if( arg == "tracking" )
      shadowstuff( 0, 0, 0, "stop" );
   return 1;
}

clean_array()
{
   int i;

   master_rooms = ({});
   level = allocate( radius+2 );
   for( i = ( radius+2 ) ; i-- ; )
       level[i] = ({});
}

prep_func( string arg )
{
   string hunterroom, huntedroom;
   object ob, obtwo;

   radius = MAXRADIUS;
   clean_array();
   shadowstuff( 0, 0, 0, "stop" );

   if( !arg )
      return( write( "Usage: track <the person's name>.\n" ), 1 );
   if( arg == PRNAME )
      return( write("You can't track yourself you stupid gimp.\n"), 1 );
   if( IsWizard( hunteddude = FINDL( arg  ) ) )
      return( write( "Don't even think about tracking "+capitalize( arg )+  ".\n" ), 1 );
   if( ( THISP -> query_player_kills() >= 50 ) &&
     ( GetOrdLevel( FINDL( arg ) ) == OrdLevel( Mortal ) ) )
write( "An experienced pkiller like yourself doesn't need the help of this tracker.  But, hell, who am I to stop you!\n");
   if( ( hunteddude = FINDL( arg ) ) && ( hunteddude -> query_npc() ) ) get_monster( to_string( hunteddude ) );
   if( ( hunteddude ) && !ENV( hunteddude ) )
      return( write( capitalize( arg ) + " is lost.\n" ), 1 );
   if( ( explode( arg, " " )[0] == "monster" ) && ( present( arg, ENV( THISP ) ) ) )
      hunteddude = present( arg, ENV( THISP ) );
   else
   if( !FINDL( arg ) )
      return( write( capitalize( arg )+" isn't on the mud.\n"), 1 );
   if( hunteddude && hunteddude->query( NoScryP ) )
      return( write( CAP( arg ) + " doesn't show up on radar.\n" ), 1 );

   hunterdude = THISP;
   hunterroom = explode( to_string( ENV( hunterdude ) ), "." )[0];
   huntedroom = explode( to_string( ENV( hunteddude ) ), "." )[0];

   level[0] += ({ hunterroom });


   array_check( 0, huntedroom );

   ob = clone_object( MISC + "hunted" );
   obname = to_string( ob );
   ob -> sh_init( hunteddude );
   ob -> tracker( THISP, hunteddude, THISO );
   obtwo = clone_object( MISC + "hunter" );
   obtwoname = to_string( obtwo );
   obtwo->sh_init( THISP );
   obtwo -> tracker( THISP, hunteddude, THISO );
   return 1;
}

array_check( int current_level, string huntedroom )
{
   mixed *mini_ring;
   int i, position;

   if( !sizeof( level[current_level] ) ) return;
   for( position = sizeof( level[current_level] ) ; position-- ; ) {
      mini_ring = m_values( level[current_level][position] -> query( "exits" ) );
      for( i = sizeof( mini_ring ) ; i --; ){
         if( ( member_array( mini_ring[i], master_rooms ) == -1) && ( objectp( find_object( mini_ring[i] ) ) ) ){
            master_rooms += ({ mini_ring[i] });
            level[current_level +1] += ({ mini_ring[i] });
         }
      }
      if( level[current_level][position] == huntedroom ) {
         radius = MAXRADIUS;
         was_in = 1;
         if( !current_level ){
            return ( call_out( "thwack", 1) );
         }else{
            return( backtrack( huntedroom, current_level, ({}) ) );
         }
      }
   }
   if( current_level >= radius ){
//radius = MAXRADIUS%2 ? MAXRADIUS/2 +1: MAXRADIUS/2;
      long_range( huntedroom );
      return;
   }
   array_check( ++current_level, huntedroom);
}

backtrack( string theroom, int current_level, string *directions)
{
   int i, z;

   if(!to_int( current_level ) ){
      return( display( directions ) );
   }
   current_level--;
   for( i=sizeof( level[current_level] ) ; i-- ; ){
      if( ( z=member_array( theroom, m_values( level[current_level][i] -> query( "exits" ) ) ) ) != -1 ){
         directions += ({ m_indices( level[current_level][i] -> query( "exits" ) )[z] });
         theroom = level[current_level][i];
         i=0;
      }
   }
   backtrack(theroom, current_level, directions);
}

medium_range()
{
   tell_object( hunterdude, "|Medium Range| "+capitalize(hunteddude->query_real_name())+
   " --> " + ENV( hunteddude ) -> short()+".\n");
}

display( string *directions )
{
   int i;

   tell_object( hunterdude, "|Short Range| "+capitalize(hunteddude->query_real_name())+" --> { " );
   for( i=sizeof( directions ); --i ; ){
      tell_object( hunterdude, directions[i] +", " );
   }
   tell_object( hunterdude, directions[0]+" }\n" );

   c_radius = sizeof( directions );
   if( auto_attack ) {
      if( c_radius == MAXRADIUS )
         tell_object( hunteddude, "You hear several faint high-pitched beeps in the distance.\n" );
      if( c_radius == MAXRADIUS/2 )
         tell_object( hunteddude, "You hear several high-pitched beeps a short distance away.\n" );
      if( c_radius == 1 )
         tell_object( hunteddude, "You hear a screaming high-pitched noise all around you.\n" );
   }

   hunterdude -> add_fatigue( -c_radius );
   if( hunterdude -> query_fatigue() == 0) {
      tell_object( hunterdude, "You are much too tired to continue tracking " +
        capitalize( hunteddude -> query_real_name() ) + ".\n" );
      shadowstuff( 0, 0, 0, "stop" );
   }
}

long_range( string huntedroom )
{
   string *hunter, *hunted;

   hunter = allocate( 4 ); hunted = allocate( 4 );

   if( sscanf( to_string( level[0][0] ), "/%s/%s/%s/", hunter[0], hunter[1], hunter[2] ) != 3 )
      return;
   if( sscanf( huntedroom, "/%s/%s/%s/", hunted[0], hunted[1], hunted[2] ) != 3)
      return;

   if( hunter[2] == hunted[2] ){
      if( was_in == 0 ){
         tell_object( hunterdude, "|Long Range|  You are now within striking range of " +
           capitalize( hunteddude -> query_real_name() ) + ".\n" );
         was_in = 1;
      }
      medium_range();
      return;
   }
   if( ( hunter[2] != hunted[2] ) && ( was_in == 1 ) ){
      tell_object( hunterdude, "|Long Range|  You are no longer in the same dimension as " +
        capitalize( hunteddude -> query_real_name() ) + ".\n" );
      was_in = 0;
      return;
   }
}

shadowstuff( string dest, object hunter, object hunted, string flag )
{
   object ob, obtwo;

   dest = to_string( dest );
   clean_array();
   hunterdude = hunter;
   hunterdude = hunter;
   hunteddude = hunted;
   if( flag == "hunter" ){
      level[0] += ({ dest });
      array_check( 0, to_string( ENV( hunteddude ) ) );
   }
   if( flag == "hunted" ){
      level[0] += ({ to_string( ENV( hunterdude ) ) });
      array_check( 0,  dest );
   }
   if( flag == "stop" ){
      if( objectp( ob = find_object( to_string( obname ) ) ) ){ ob -> destme();}
      if( objectp( obtwo = find_object( to_string( obtwoname ) ) ) ){ obtwo -> destme(); }
   }
}

//mapper code begins here
/* function mappage: initializes parameters */
mappage(string arg)
{
	int i,xx,yy;
	string *param, pathtest;
	//Initializations
	param = ({});
	legend = ([]);
	ring = ([]);
	sring = ({});
	map_counter=0;
	pic_counter=0;
	imod=0;
	x=( X_MAX/2 );
	y=( Y_MAX/2 );

	if( !ENV( THISP ) )
		return( write("Get an environment.\n"), 1 );
	if( member( NoMapCabal, getuid( ENV( THISP ) ) ) != -1 )
		return( write("Cartography isn't permitted in this area.\n"), 1 );
	for( i=sizeof( NoMapPath ); i--; )
		if( sscanf( to_string( ENV( THISP ) ), NoMapPath[i]+"%s", pathtest ) )
			return( write("Cartography isn't permitted in this area.\n"), 1 );
	if( THISP -> query_stat("int") < 20 ) 
		return( write("Cartography requires _some_ intelligence.\n"), 1 );
	if( THISP -> query_mana() < 25 )
		return( write("You are too mentally exhausted to survey your area.\n") , 1 );
	else
		THISP -> add_mana( -5 );

	str="A flare shoots suddenly in the air.\nAs your eyes adjust to the glare, an image of your surroundings appear.\n";
	str+="=========================================================================\n";
	coordinates=allocate( Y_MAX );
	for( i=0;i<Y_MAX; i++ )
		coordinates[i]=allocate( X_MAX );

	if( arg ){
		for( i=0;i< strlen(arg); i++ )
			param += ({ arg[i..i] });
		if( member( param, "v" ) != -1 )
			fverbose = 1;
		if( member( param, "m" ) != -1 )
			fmonster = 1;
		else 
			fmonster = 0;
		if( member( param, "b" ) != -1 )
			fverbose = 0;
		if( ( member( param, "h" ) != -1 ) || ( member( param, "?" ) != -1 ) ){
			disp_help();
			return 1;
		}
	}

	for( yy=0; yy<Y_MAX; yy++ )
		for( xx=0; xx<X_MAX; xx++ ) 	
			coordinates[yy][xx] = " ";

	legend = allocate_mapping( 2, WIDTH );
        ring += ([ to_string( ENV(THISP) ): x; y; 1; "@" ]);

	if( fverbose )
		add_pic( to_string( ENV( THISP ) ), add_legend( ENV( THISP ) ), /*vy1=*/0 , /*vx1=*/-1 , /*vx2=*/0 , /*vx3=*/1 );

	map_it();
	return 1;
}

/*function disp_all: Exists only for debugging purposes only.
Displays all members of mapping ring. */
disp_all()
{

	write("Pay attention here---------------------------------------"+endl);
	walk_mapping( ring, "disp" );
}

/* Function map_it: is a recursive function that maps rooms */
map_it()
{
	int i;
	mixed nextroom;
	
	
	if( ++map_counter >= Radius )
		return( call_out( "Showmap",1 ) );
	fCheck_exists=0;
	sring = ({});
	walk_mapping( ring, "search_fCheck" );
	if( !fCheck_exists )
		return( call_out( "Showmap",1 ) );

	for( i=sizeof( sring ); i-- ; )
		if( catch( add_surrounding( i ) ) )
			return( call_out( "Showmap",1 ) );

	map_it();

}

/* Function add_surrounding: adds surrounding rooms to the map */
add_surrounding( int i )
{
	int z;
	object theroom;
	mapping srooms;

	srooms=([]);

	if( !objectp( theroom=find_object( to_string( sring[i] ) ) ) )
		return;
	else{
		x=ring[ sring[i] , 0 ];
		y=ring[ sring[i] , 1 ];
	}
	srooms += mkmapping( m_values( theroom->query( "exits" ) ), m_indices( theroom->query( "exits" ) ) );
	walk_mapping( srooms, "add_to_ring" );
}

/*function add_to_ring: adds the picture of the next room to the map
as well as the directions towards the next room. */
add_to_ring( mixed room, mixed direction )
{
	mixed pic;
	pic=0;

	switch( direction ){
		case "north":
			if( member( m_indices( ring ), room ) == -1 )
				pic=add_legend( room );
			if( !fverbose ){
				pic="*";
				pic=c_specials( room );

				ring+=([ room: x; y-2; 1; pic ]);
				coordinates[y-1][x]="|";
			}else{
				coordinates[y-1][x]="|";
				add_pic( room, pic, /*vy1=*/-2 , /*vx1=*/-1 , /*vx2=*/0 , /*vx3=*/1 );
			}
			break;
		case "northeast":
			if( member( m_indices( ring ), room ) == -1 )
				pic=add_legend( room );
			if( !fverbose ){
				pic="*";
				pic=c_specials( room );
				ring+=([ room: x+2; y-2; 1; pic ]);
				if( coordinates[y-1][x+1]=="\\" 
					|| coordinates[y-1][x+1]=="X" )
					coordinates[y-1][x+1]="X";
				else
					coordinates[y-1][x+1]="/";
			}else{
				if( coordinates[y-1][x+2]=="\\" 
					|| coordinates[y-1][x+2]=="X" )
					coordinates[y-1][x+2]="X";
				else
					coordinates[y-1][x+2]="/";

				add_pic( room, pic, /*vy1=*/-2 , /*vx1=*/3 , /*vx2=*/4 , /*vx3=*/5 );
			}
			break;
		case "east":
			if( member( m_indices( ring ), room ) == -1 )
				pic=add_legend( room );
			if( !fverbose ){
				pic="*";
				pic=c_specials( room );
				ring+=([ room: x+2; y; 1; pic ]);
				coordinates[y][x+1]="-";
			}else{
				coordinates[y][x+2]="-";

				add_pic( room, pic, /*vy1=*/0 , /*vx1=*/3 , /*vx2=*/4 , /*vx3=*/5 );
			}
			break;
		case "southeast":
			if( member( m_indices( ring ), room ) == -1 )
				pic=add_legend( room );
			if( !fverbose ){
				pic="*";
				pic=c_specials( room );
				ring+=([ room: x+2; y+2; 1; pic ]);
				if( coordinates[ y+1 ][x+1] == "/" 
					|| coordinates[ y+1 ][x+1] == "X" )
					coordinates[ y+1 ][x+1]="X";
				else
					coordinates[y+1][x+1]="\\";
			}else{
				if( coordinates[ y+1 ][x+2] == "/" 
					|| coordinates[ y+1 ][x+2] == "X" )
					coordinates[ y+1 ][x+2]="X";
				else
					coordinates[y+1][x+2]="\\";

				add_pic( room, pic, /*vy1=*/2 , /*vx1=*/3 , /*vx2=*/4 , /*vx3=*/5 );
			}
			break;
		case "south":
			if( member( m_indices( ring ), room ) == -1 )
				pic=add_legend( room );
			if( !fverbose ){
				pic="*";
				pic=c_specials( room );
				ring+=([ room: x; y+2; 1; pic ]);
				coordinates[y+1][x]="|";
			}else{
				coordinates[y+1][x]="|";

				add_pic( room, pic, /*vy1=*/2 , /*vx1=*/-1 , /*vx2=*/0 , /*vx3=*/1 );
			}
			break;
		case "southwest":
			if( member( m_indices( ring ), room ) == -1 )
				pic=add_legend( room );
			if( !fverbose ){
				pic="*";
				pic=c_specials( room );
				ring+=([ room: x-2; y+2; 1; pic ]);
				if( coordinates[y+1][x-1] == "\\"
					|| coordinates[y+1][x-1] == "X" )
					coordinates[y+1][x-1] = "X";
				else
					coordinates[y+1][x-1] = "/";
			}else{
				if( coordinates[y+1][x-2] == "\\"
					|| coordinates[y+1][x-2] == "X" )
					coordinates[y+1][x-2] = "X";
				else
					coordinates[y+1][x-2] = "/";

				add_pic( room, pic, /*vy1=*/2 , /*vx1=*/-5 , /*vx2=*/-4 , /*vx3=*/-3 );
			}
			break;
		case "west":
			if( member( m_indices( ring ), room ) == -1 )
				pic=add_legend( room );
			if( !fverbose ){
				pic="*";
				pic=c_specials( room );
				ring+=([ room: x-2; y; 1; pic ]);
				coordinates[y][x-1]="-";
			}else{
				coordinates[y][x-2]="-";

				add_pic( room, pic, /*vy1=*/0 , /*vx1=*/-5 , /*vx2=*/-4 , /*vx3=*/-3 );
			}
			break;
		case "northwest":
			if( member( m_indices( ring ), room ) == -1 )
				pic=add_legend( room );
			if( !fverbose ){
				pic="*";
				pic=c_specials( room );
				ring+=([ room: x-2; y-2; 1; pic ]);
				if( coordinates[y-1][x-1] == "/"
					|| coordinates[y-1][x-1] == "X")
					coordinates[y-1][x-1] = "X";
				else
					coordinates[y-1][x-1] = "\\";
			}else{
				if( coordinates[y-1][x-2] == "/"
					|| coordinates[y-1][x-2] == "X")
					coordinates[y-1][x-2] = "X";
				else
					coordinates[y-1][x-2] = "\\";

				add_pic( room, pic, /*vy1=*/-2 , /*vx1=*/-5 , /*vx2=*/-4 , /*vx3=*/-3 );
			}
			break;
	}

}

/* Function add_pic: adds the picture to the verbose map. */
add_pic( mixed room, mixed pic, int vy1 , int vx1 , int vx2 , int vx3 )
{
	if( ! ( intp( pic ) ) ){
		coordinates[y+vy1][x+vx1]=pic[0..2];
		coordinates[y+vy1][x+vx2]="";
		coordinates[y+vy1][x+vx3]="";
		ring+=([ room: x+vx2; y+vy1; 1; "" ]);
	}else		
	if( pic && pic != 999 ){
		if( pic < 10 ){
			coordinates[y+vy1][x+vx1]=0;
			coordinates[y+vy1][x+vx2]=0;
			coordinates[y+vy1][x+vx3]=pic;
			ring+=([ room: x+vx2; y+vy1; 1; 0 ]);
		}else
		if( pic < 100 ){
			coordinates[y+vy1][x+vx1]=0;
			coordinates[y+vy1][x+vx2]=pic;
			coordinates[y+vy1][x+vx3]="";
			ring+=([ room: x+vx2; y+vy1; 1; pic ]);
		}else
		if( pic < 1000 ){
			coordinates[y+vy1][x+vx1]=pic;
			coordinates[y+vy1][x+vx2]="";
			coordinates[y+vy1][x+vx3]="";
			ring+=([ room: x+vx2; y+vy1; 1; "" ]);
		}			
	}
}

/* function add_legend: determines what the picture will be
as well as adding it to the legend for the verbose map. */
mixed add_legend( mixed room )
{
	object theroom;
	mixed value0, value1, value2, value3, num;
	mixed temp;

	if( !objectp( theroom = find_object( to_string( room ) ) ) )
		return 999;

	if( ( test=member( m_indices( legend ) , ( theroom->short()[0..MAX_LENGTH] ) ) ) != -1 ){

		pic_counter_temp = ++pic_counter;
		num=(int) legend[ theroom->short()[0..MAX_LENGTH], 0 ];
		value1=legend[ theroom->short()[0..MAX_LENGTH], 1 ];
		value2=legend[ theroom->short()[0..MAX_LENGTH], 2 ];
		value3=legend[ theroom->short()[0..MAX_LENGTH], 3 ];
		
		if( value1 && intp( value1 ) ) pic_counter_temp=value1;
		if( value2 && intp( value2 ) ) pic_counter_temp=value2;
		if( value3 && intp( value3 ) ) pic_counter_temp=value3;

		pic_counter_temp=c_specials( theroom );

		if( member( ({ value1, value2, value3 }), pic_counter_temp ) == -1 ){
			legend[ theroom->short()[0..MAX_LENGTH], 0 ] = ++num;
			legend[ theroom->short()[0..MAX_LENGTH], num ] = pic_counter_temp;
		}					

		return( pic_counter_temp );

	}else{

		pic_counter_temp=0;
		pic_counter_temp=c_specials( theroom );

		if( intp( pic_counter_temp ) ){
			legend[ theroom->short()[0..MAX_LENGTH], 0 ] = 1;
			legend[ theroom->short()[0..MAX_LENGTH], 1 ] = ++pic_counter;
			pic_counter_temp = pic_counter;
			return( pic_counter_temp );
		}

		legend[ theroom->short()[0..MAX_LENGTH], 0 ] = 1;
		legend[ theroom->short()[0..MAX_LENGTH], 1 ] = pic_counter_temp;
		return( pic_counter_temp );

	}
}	
/* Function c_specials: Checks rooms for special qualities and returns a description
of the picture to be added to the map.  If you are going to add special qualities
please make sure you add another value0...n to function add_legend as well
as checking if it exists.  Also make sure that the formatting in function
disp_legend will adequately accomodate the change.
*/ 
mixed c_specials( mixed theroom )
{
	if( !fverbose && !objectp( theroom = find_object( to_string( theroom ) ) ) )
		return("*");
	
	if( theroom == ENV(THISP) ){
		if( fverbose )
			return("YOU");
		else
			return("@");	
	}
	else 
	if( fmonster && present( "monster", theroom ) ){
		if( fverbose )
			return("MON");
		else
			return("M");
	}
	if( fverbose )
		return( pic_counter_temp );
	else
		return("*");
}

/* function disp: Exists only for debugging purposes */
disp(mixed room, mixed X_Coordinate, mixed Y_Coordinate, mixed fCheck, mixed picture )
{
	write("disp: room="+to_string( room )+";X_Coordinate="+to_string(X_Coordinate)+
		";Y_Coordinate="+to_string(Y_Coordinate)+";fCheck="+to_string(fCheck)+
		";picture="+to_string(picture)+endl);
}

/* function search_fCheck: Checks mapping ring for rooms to be
added to the map.
*/
search_fCheck( mixed room, mixed X_Coordinate, mixed Y_Coordinate, mixed fCheck, mixed picture )
{
	if( fCheck ){
		fCheck = 0;
		fCheck_exists = 1;
		sring += ({ room });
	}
}

/* function Showmap: Displays the map */
Showmap()
{
	int xx,yy,i,printflag;
	string str2;

	//makes sure "YOU" appear.
	x=(X_MAX/2);
	y=(Y_MAX/2);
	if( fverbose )
		add_pic( to_string( ENV( THISP ) ), add_legend( ENV( THISP ) ), /*vy1=*/0 , /*vx1=*/-1 , /*vx2=*/0 , /*vx3=*/1 );
	if( !fverbose )
                ring += ([ to_string( ENV(THISP) ): x; y; 0; "@" ]);

	walk_mapping(ring,"get_coord");
	for( yy=0; yy<Y_MAX; yy++ ){
		for( xx=0; xx<X_MAX; xx++ ) 	
			str+=to_string( coordinates[yy][xx] ) ;
		str+="\n";
	}
	str+="=========================================================================\n";

	if( fverbose ){
		str+="YOU = Yourself";
		if(fmonster) 
			str+="; MON = Monster(s) ";
	}else{
		str+="@ = Yourself; * = A Room";
		if(fmonster)
			str+="; M = Monster(s)";
		str+=".\n\n\n";
	}
	
	str+="\n";
	str2="\n";
	for( i=0;i<strlen(str);i++)
		if(str[i..i]=="\n"){
			if( printflag )
				write( str2 );
			str2=str[i..i];
			printflag=0;
		}else{
			if( str[i..i] != " " )
				printflag=1;
			str2+=str[i..i];
		}
	if( fverbose ){
		write("\nPress enter to continue...");
		input_to("legend");
	}else
		write("\n");
	
}	

/* function legend: Displays the legend only if in verbose mode */
legend(string arg)
{

	if( fverbose ){
		write("Legend:\n");
		walk_mapping( legend, "remove_non_int" );
		disp_legend();
		write("\n");
	}else
		write("\n");
}

remove_non_int( mixed desc, mixed number, mixed r1, mixed r2, mixed r3, mixed r4, mixed r5, mixed r6, mixed r7, mixed r8, mixed r9, mixed r10 )
{
	int i, fnot_intp;

	fnot_intp=0;

	for( i=1; i <= number; i++ )
		if( !intp( legend[desc, i] ) )
			fnot_intp=1;
	
	if( fnot_intp ){
		write( desc );
		for( i=0; i<= ( MAX_LENGTH-strlen(to_string(desc) ) ); i++ )
			write(" ");
		write(": ");
		for( i=1; i <= number; i++ )
			if( intp( legend[desc, i] ) )
				printf( "%03d ", (int)legend[desc, i] );
			else
				printf( to_string( legend[desc,i]+" " ) );

		if( number == 1 )
			write("        ");
		if( number == 2 )
			write("    ");

		if( imod++ )
			write("\n");
		imod %= 2;
		
		m_delete( legend, desc );
	}
}		

switch_elem0_elem1( mixed desc, mixed r0, mixed r1, mixed r2, mixed r3, mixed r4, mixed r5, mixed r6, mixed r7, mixed r8, mixed r9, mixed r10 )
{
	r0=r1;
}

/* function disp_legend: Displays each member of mapping legend in increasing order */
disp_legend()
{
	int i,ii;
	mixed *order;

	walk_mapping( legend, "switch_elem0_elem1" );

	//puts it in ascending order.
	order = sort_array( m_values( legend ), #'> );
	
	legend = mkmapping( m_values( legend ), m_indices( legend ) );

	for( i=0; i<sizeof(order); i++ ){
		write( to_string( legend[order[i],0] ) );
		//pads description with spaces
		for( ii=0; ii <= ( MAX_LENGTH-strlen( to_string( legend[order[i],0] ) ) ); ii++ )
			write(" ");
		write(": ");
		printf( "%03d ", order[i] );
		write("        ");
		if( imod++ )
			write("\n");

		imod %= 2;
	}
	
}

/*function get_coord: Puts each member of the room to be mapped in
a two dimensional array called coordinates */
get_coord(mixed room, mixed X_Coordinate, mixed Y_Coordinate, mixed fCheck, mixed picture )
{
	if( coordinates[ (int) Y_Coordinate ][ (int) X_Coordinate ] == " " )	
		coordinates[ (int) Y_Coordinate ][ (int) X_Coordinate ] = to_string( picture );	

}
