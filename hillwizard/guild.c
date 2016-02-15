#include <hillwizard.h>

inherit SpecGuildCode;

void extra_create()
{
    set( "guild_name", "hillwizard" );
    set( "parent", "fighter" );
    set( "GuildWizards", ({ "arphen", "taplash" }) );
    set( "min_stats", ([ "wil" : 150, "dex" : 150 ]) );
    set( "join_fee", 5000 );

    set( "skills", ([
        "summon shield"        : 1000; 2,
        "blockade"             : 1000; 2,
        "thankin' 'bout stuff" : 1000; 2,
        "cook meth"            : 1000; 2,
        "wizardy smash"        : 1000; 2,
        "sling spell"          : 1000; 2,
        "battle barrier"       : 1000; 2,
        "wind whip"            : 1000; 2,
        "windprisonment"       : 1000; 2,
        "magic twister"        :    1; 1,  // Cost handled elsewhere
    ]) );

    set( "profs", ([
        "light axe"            :  500;  1,
        "light club"           :  500;  1,
        "light sword"          :  500;  1,
        "light flail"          :  500;  1,
        "light polearm"        :  500;  1,
        "hands"                :  500;  1,
        "knife"                :  500;  1,
    ]) );

    set( "titles", ([
         0  :  "the yankee",
        40  :  "is about as useful as tits on a bull",
        80  :  "is off like a herd 'a turtles",
       120  :  "is as smart as a bucket fulla hammers",
       160  :  "finally bought that banjo",
       200  :  "is madder than a wet hen",
       240  :  "'s got more broke cars than fixed teeths",
       280  :  "is happier than a tornado in a trailer park",
       320  :  "the good ol' boy",
       400  :  "the Hill Wizard",
    ]) );
}

int join_signal( object me )
{
    if( present_clone("/zone/guild/mageslayer/obj/shoulder_implant", me ) ||
        present_clone("/zone/guild/mageslayer/obj/tail_implant",     me ) ||
        present_clone("/zone/guild/mageslayer/obj/eye_implant",      me ) )
    {
      tell_player( me, "There ain't no place for them technowhatsits "
        "up round these here parts, ya hear?" );
      return 1;
    }

    if( me->query_skill( "shield" ) < 30 ) 
    {
      tell_player( me, "Ain't gonna be mucha none Hill Wizard widdout "
        "some shield practicin'!" );
      return 1;
    }
    
    if( !present_clone( ZMON "clyde", ENV( me ) ) )
    {
      tell_player( me, "No trainer here." );
      return 1;
    }

    return 0;
}

void join_comm( object me )
{
    object shad = clone_object( GOBJ "shad" );
    shad->sh_init( me );
    tell_object( me, "You suddenly find beauty in the crowing of "
      "the cock, the squealing of the sow, and god damn do you ever "
      "feel the need to buy yourself some lawn cars.\n" ); 
    return( ::join_comm( me ) );
}

void leave_comm( object me )
{
    ::leave_comm( me );
    me->kill_hillwizard_shad();
    destruct( present_clone( GOBJ "shield", me ) );
    tell_object( me, "You surely will miss the lovely sounds of"
      "banjos and squealing pigs.\n" );
}
