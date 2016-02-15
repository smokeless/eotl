
//  Surgically removes body parts, which can be replaced
//  by socketed artificial appendages.

inherit ObjectCode;
inherit AnsiTellCode;
#include <ansi.h>

void extra_create()
{
    set( "id", ({ "monster", "surgeon", "cyborg", "cyrus",
                  "cyborg surgeon" }) );
    set( "short", "Cyrus, the cyborg surgeon" );
    set( "long",
         "The metallic figure stands perfectly motionless, waiting for "
         "further commands.  In place of hands, it has a fearsome "
         "array of needles, surgical blades, and clamp-like "
         "manipulators.  It also has what looks like a band-aid "
         "dispensor in the center of its chest.  The precision "
         "stainless steel body is covered by a slightly rumpled "
         "white lab coat.  A crooked sign hangs from a chain "
         "around its 'neck', which reads:\n"
         "\n"
         "            SURGICAL OPTIONS\n"
         "            ----------------\n"
         "You may request any of the following voluntary\n"
         "       out-patient surgical procedures:\n"
         "\n"
 "  SURGERY TYPE      DAMAGE   PERMANENT CONSEQUENCE\n"
 "  tail implant       50+     -25 max mana, Loss of tail (if applicable)\n"
 "  wrist implant     100+     -50 max mana, loss of right hand\n"
 "  eye implant       300+     -200 max mana\n"
 "  shoulder implant  400+     -100 max mana, loss of entire left arm\n"
         "\n"
         "*** All surgeries are considered elective, and are performed "
         "only at the patient's discretion.  Removal of body parts is "
         "permanent, until such time as bodily death and "
         "regeneration occurs.  The surgeon will not be held liable "
         "for injuries sustained due to complications, which could "
         "be as much as 50% higher than anticipated." );
    set( "gettable", 0 );
    set( "value", 0 );
    set( "weight", 10000 );
}

void extra_init()
{
   add_action("do_chop", "request" );
}

do_chop( string str )
{
    int x;
    object shunt, equip;
    string *locs, loc;
    mixed *allarm;

    if( THISP->query_ghost() )
    {
        ansi_notify_fail( "You need a solid body to do that.", BOLD_WHITE );
        return 0;
    }

    if( THISP->query_guild() != "mageslayer" && !IsWizard( THISP ) )
    {
        ansi_notify_fail( "The computer beeps.  A message scrolls "
            "across the screen:  'OPERATIONS ARE CURRENTLY AVAILABLE "
            "ONLY TO MEMBERS OF THE MAGESLAYER GUILD'", BOLD_WHITE );
        return 0;
    }

    if( str == "tail implant" && THISP->query_race() == "Merfolk" && 
        !IsWizard( THISP ) )
    {
        ansi_notify_fail( "The computer beeps.  A message scrolls "
            "across the screen:  'AN OPERATION OF THAT MAGNITUDE "
            "WOULD RESULT IN DEATH'", BOLD_WHITE );
        return 0;
    }

    if( str == "tail implant" )
        shunt = clone_object( "/zone/guild/mageslayer/obj/tail_implant" );
    else if( str == "eye implant" )
        shunt = clone_object( "/zone/guild/mageslayer/obj/eye_implant" );
    else if( str == "wrist implant" )
        shunt = clone_object( "/zone/guild/mageslayer/obj/wrist_implant" );
    else if( str == "shoulder implant" )
        shunt = clone_object( "/zone/guild/mageslayer/obj/shoulder_implant" );
    else
    {
        ansi_notify_fail( "Request <which> implant?", BOLD_WHITE );
        return 0;
    }

    if( present_clone( shunt, THISP ) )
    {
        ansi_tell( THISP, "The computer beeps.  A message scrolls "
            "across the screen:  'YOU ALREADY HAVE AN IMPLANT OF THAT "
            "TYPE'", BOLD_WHITE );
        destruct( shunt );
        return 1;
    }

    locs = shunt->query( "shunt" );
    if( sizeof( THISP->query_armor_worn() +
        ({ THISP->query_weapon() }) - ({ 0 }) ) )
    {
            ansi_tell( THISP, "The computer beeps.  A message scrolls "
                "across the screen:  'YOU MUST FIRST REMOVE ALL "
                "EQUIPMENT'", BOLD_WHITE );
            destruct( shunt );
            return 1;
    }

    ansi_tell( THISP, "The computer beeps.  A message scrolls "
        "across the screen:  'THIS MIGHT HURT'", BOLD_WHITE );
    ansi_tell( THISP, "You feel the sting of an injector needle "
        "moments before you pass out.  The operation is quickly "
        "performed while you sleep, but you wake to excruciating "
        "pain....", LOW_RED );
    ansi_tell_room( ENV( THISP ), sprintf( "With amazing speed, "
        "Cyrus grabs %s, injecting %s with a powerful sedative.  "
        "You cannot bear to watch as Cyrus begins to cut away part "
        "of %s body!", PNAME, objective( THISP ), possessive( THISP ) ),
        LOW_RED, ({ THISP }) );

    foreach( loc : locs )
    {
        THISP->remove_hit_location( loc );
        allarm = THISP->query_armor();
        for( x=0; x<sizeof(allarm); x+=3 )
             if( allarm[x] == loc )
                 allarm = allarm[0..x-1] + allarm[x+3..];
        THISP->set_armor( allarm );
    }
        
    move_object( shunt, THISP );
    THISP->add_bonus_object( shunt );

    THISP->take_damage( shunt->query( "dam" ), 0, "piercing", 0, 0, 1 );

    if( THISP->query_ghost() )
        ansi_tell_room( ENV( THISP ), "The computer beeps.  A message "
            "scrolls across the screen:  'SURGERY FAILED.  NO BAND-AID "
            "REQUIRED'", BOLD_RED );
    else
        ansi_tell_room( ENV( THISP ), "The computer beeps.  A message "
            "scrolls across the screen:  'SURGERY SUCCESSFUL'\n"
            "Cyrus applies a band-aid to the affected area.", BOLD_WHITE );

    return 1;
}


//You can check for slayer sockets, should be able to
//check slayer implants as well so they don't get dested
//by specials or traps or whatever.
//Taplash 2015
int slayer_implant()
{
    return 1;
}
