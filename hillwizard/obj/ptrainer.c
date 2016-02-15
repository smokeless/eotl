inherit SpecGuildCode;
#include <hillwizard.h>

extra_create()
{
    set( "guild_name", "hillwizard");
    set( "GuildWizards", ({ "taplash", "arphen" }) );
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

// init() overlaid to disable join and leave commands
void init()
{
     add_action( "list_skills", "skills" );
     add_action( "skill_info",  "info"   );
     add_action( "skill_cost",  "cost"   );
     add_action( "train_skill", "train"  );
}  

// train_ok overlaid to check for trainer
status train_ok( object me, string skill, int old, int gain, int prof )
{
   if( present_clone( ZMON "chester", ENV( THISO ) ) )
       return ::train_ok( me, skill, old, gain, prof);
   return( write( "No one here.\n" ), 0 );
}   
