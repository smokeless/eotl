inherit ObjectCode;

int do_raise( string s );
int do_lower( string s );

void
setup()
{
    ::setup();
    if( !clonep() ) return;
    set( "id", ({ "turret","artillery" }));
    set( "short","a cannon" );
    set( "long",
    "This is a tank turret.  It is large and steel."
    );
    set( "ammo", "cannon ball" );
    set( "shellname", "shell" );
    set( "proficiency", "artillery" );
    set( "gunname", "cannon" );
    set( "turret_level", 1 );
    set( "gettable", 0 );
    set( "power", 20 );
    set( "aimdir", "north" );
    set( BigP, 1 );
}

post_long()
{
    return( strformat( "This "+query("gunname")+" uses "+query("ammo")+
    ".  It is pointed "+query("turret_level")+" clicks over the "+
    "horizon.  It is pointed "+query("aimdir")+" and is "+
    (query("loaded")?"loaded":"not loaded")+".\nProficiency class: "+
    "Artillery" ) );
}

void
init()
{
    ::init();
    add_action( "do_load","load" );
    add_action( "do_load","reload" );
    add_action( "do_aim","aim" );
    add_action( "do_fire","fire" );
    add_action( "do_raise","raise" );
    add_action( "do_lower","lower" );
}

rightammo( object thing )
{
    if( thing->query( "ammotype" ) == query( "ammo" ) )
        return 1;

    return 0;
}

do_load( string s )
{
    object obj;
    object *stuff;

    if( s ) THISO->extra_load( s );

    if( query( "loaded" ) ) 
        return( notify_fail( "That is already loaded!\n" ), 0 );

    stuff = all_inventory( THISP );
    stuff = filter_array( stuff, #'rightammo );
    if( sizeof(stuff) )
        obj = stuff[0];
    else {
        stuff = all_inventory( ENV( THISP ) );
        stuff = filter_array( stuff, #'rightammo );
        if( sizeof( stuff ) )
            obj = stuff[0];
        else return( notify_fail(
             "You don't have the right ammo.\n" ), 0 );
    }
    if( obj == THISO ) return( notify_fail(
        "You don't have the right ammo.\n" ), 0 );

    move_object( obj, THISO );
    set( "loaded", obj );
    tell_object( THISP, "You slide "+obj->short()+
    " into the "+query("gunname")+".\n" );
    tell_room( ENV( THISP ), PNAME+
    " slides "+obj->short()+" into the "+
    query("gunname")+".\n",
    ({ THISP }));

    return 1;
}

int
do_aim( string s )
{
    if( !s ) return 0;
    if( s == "up" ) return do_raise( query("id")[0] );
    if( s == "down" ) return do_lower( query("id")[0] );

    set( "aimdir", s );
    tell_object( THISP, "You aim the "+query("gunname")+" "+s+".\n" );
    tell_room( ENV( THISP ), PNAME+" aims the "+query("gunname")+
    " "+s+".\n",({ THISP }));
    if( ENV( ENV( THISO ) ) )
        tell_room( ENV( ENV( THISO ) ), "The "+query("gunname")+
        " swings, aiming to the "+s+" now.\n" );

    return 1;
}

do_raise( string s )
{
    if( !s || ( s != query("gunname") ) ) return 0;
    if( query( "turret_level" ) >= ( query( "power" ) * 2 ) )
        return( notify_fail( "That is already pointed straight "
        "up!\n" ), 0 );

    set( "turret_level", query( "turret_level" ) + 1 );

    tell_object( THISP, "You raise the "+query("gunname")+
    ".\nIt is now aiming "+
    query( "turret_level" )+" points over the horizon.\n" );
    tell_room( THISP, PNAME+" raises the turret to "+
    query( "turret_level" )+" points over the horizon.\n",
    ({ THISP }));
    if( ENV( ENV( THISO ) ) )
        tell_room( ENV( ENV( THISO ) ), "The "+
        ENV(THISO)->query("id")[0]+" raises its "+
        query("gunname")+".\n" );

    return 1;
}

do_lower( string s )
{
    if( !s || s != query("gunname") ) return 0;

    if( query( "turret_level" ) <= 0 )
        return( notify_fail( "That cannot be lowered anymore.\n" ), 0 );

    set( "turret_level", query( "turret_level" ) - 1 );

    tell_object( THISP, "You lower the "+query("gunname")+
    ".\nIt is now aiming "+query( "turret_level" )+
    " points over the horizon.\n" );
    tell_room( THISO, PNAME+" lowers the "+query("gunname")+" to "+
    query( "turret_level" )+" points over the horizon.\n",
    ({ THISP }));
    if( ENV( ENV( THISO ) ) )
        tell_room( ENV( ENV( THISO ) ), "The "+
        ENV(THISO)->query("id")[0]+" lowers its "+query("gunname")+".\n" );

    return 1;
}

do_fire( string s )
{
    object targ, room, *peps;
    string thingie;
    string dest;
    int how_far;
    int x, y;

    x = 0;
    thingie = "nothing";

    if( ENV( ENV( THISO ) ) )
        room = ENV( ENV( THISO ) );
    else
        room = ENV( THISO );

    how_far = query( "turret_level" );
    if( how_far > query("power") ) 
        how_far = query( "power" ) - ( how_far - query( "power" ) );

    if( !query( "loaded" ) )
        return( notify_fail( "The "+query("gunname")+
        " is not loaded.\n" ), 0 );

    tell_object( THISP, "You fire the "+query("gunname")+
    " "+query("aimdir")+".\n" );
    tell_room( ENV( THISP ), PNAME+" fires the "+query("gunname")+
    " "+query("aimdir")+".\n",({ THISP }) );

    while( x < how_far ) {
        if( room && room->query("exits")[query("aimdir")] ) {
            tell_room( room, capitalize( query("loaded")->short())+
            " flies "+query("aimdir")+"!\n" );
            dest = room;
            room = room->query("exits")[query("aimdir")];
            x++;
        } else {
            if( room->query(ForestP) ) thingie = "tree";
            else if( room->query( OceanP ) ) thingie = "large wave";
            else thingie = "wall";
            tell_room( room, capitalize( query("loaded")->short() )+
            " hits a "+
            thingie+"!\n" );
            break;
        }
        dest->do_load_me_up();
        if( !objectp( room ) && strstr( (string)room, "@" ) >= 0 ) {
            room = call_other( dest,
                (string)room[1..strlen((string)room)] );
            if( stringp( room ) ) room = FINDO(room);
        }
        if( room )
            tell_room( room, capitalize( query("loaded")->short() )+
           " flies into the room!\n" );
    }

    peps = filter_array( all_inventory( objectp(room)?room:
           FINDO(room)), "check_goodstuff", THISO );

    if( s && sizeof( peps ) ) {
        if( random( THISP->query_proficiency(
                    "artillery" ) ) - random( x ) < 0 ) {
             for( y = 0; y < sizeof( peps ); y++ ) {
                 if( peps[y]->id(s) ) {
                     if( peps[y] == THISO ) continue;
                     targ = peps[y];
                     break;
                 }
             }
        } else {
            if( objectp( room ) )
                if( !( targ = present( s, room ) ) )
                   targ = 0;
        }
    }
    if( !targ && sizeof( peps ) ) {
        if( random( 2 ) && thingie == "nothing" )
            targ = peps[random(sizeof(peps))];
    }

    if( !query("loaded")->blow_check( THISP, room, targ,
             THISO, thingie ) )
        query( "loaded" )->do_blow( THISP, room, targ, THISO, thingie );

    if( query( "loaded" ) )
        destruct( query( "loaded" ) );
    set( "loaded", 0 );

    return 1;
}

check_goodstuff( object thing )
{
    if( living( thing ) || thing->query_vehicle() ) return 1;
    return 0;
}
