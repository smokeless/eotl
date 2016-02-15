/*
Shaman guild. Shaman is a primarily defensive guild.
Taplash 2014
*/

inherit GuildCode;

#define GuildShadow "/usr/taplash/shaman/obj/shaman_shad"
#define LOG_FILE    "/usr/taplash/log/reincarnation"

/* Reincarnation cost defines */
#define R_EVAL_MIN       50        // minimum eval used for calculating costs
#define R_XP_COST_MULT   1000000   // xp cost multiplier
#define R_COIN_COST_MULT 1000      // coin cost multiplier
#define R_XP_MIN_COST    FOF_EVAL_MIN * FOF_XP_COST_MULT   // minimum xp cost
#define R_COIN_MIN_COST  FOF_EVAL_MIN * FOF_COIN_COST_MULT // minimum coin cost


void extra_create()
{
    set( "guild_name", "DeathSequence" );
    set( "GuildWizards", ({ "taplash" }) );
    set( "join_fee", 500 );
    set( "min_stats", ([ "str" : 20, "int" : 45, "wil" : 20 ])  );
    set( "cant", 1 );
    set( "skills", ([
         "natural attunement"  : 1000; 2,
         "lightning shield"    : 1000; 2, 
         "healing rain"        : 1000; 2, 
         "earthquake"          : 1400; 6, 
         "shapeshift"          : 2000; 4,
         "reincarnation"       : 1   ; 1, //Cost is handled elsewhere.
         "scorching flame"     : 1500; 3,
         "imbue shield"        : 1000; 2,
         "shield"              : 800 ; 2,
         "dodge"               : 1000; 1,
         "evade"               : 1000; 1,
         "flee"                : 1000; 1 ]) );
    
    //Shaman prefer 1 handed weapons as it allows them
    //to use shields. Shaman are not big on edged weapons
    //but they remember their more primitive days with
    //spears and such.
    set( "profs", ([
         "light club"    : 700;  2,
         "heavy club"    : 1000; 5,
         "light axe"     : 700;  2,
         "heavy axe"     : 1000; 5,
         "hands"         : 700;  2,
         "light flail"   : 700;  2,
         "heavy flail"   : 1000; 5,
         "light polearm" : 1000; 4,
         "heavy polearm" : 1000; 4 ]) );
    set( "titles", ([
           0 : "the student of nature",
          40 : "the naturalist",
          60 : "the keeper of nature",
          80 : "the keeper of elements",
          90 : "the shaman",
         100 : "the elemental shaman",
         125 : "the aged shaman"  ]) );
}

void logon_signal( object me )
{
   object shad;

   shad = clone_object( GuildShadow );
   shad->sh_init( me );
   ::logon_signal( me );
}


status join_signal( object me )
{
    object armor, *arm;
    int x = 0;
    
    if( me->query_race_ob() == "/obj/races/android" )
      return( write( "Androids cannot properly "
        "connect to nature.\n" ), 1 );
    
    if( me->query_race_ob() == "/obj/races/teddybear" )
      return( write( "You are all stuff and fluff. You are not "
        "connected to nature..\n" ), 1 );
    
    if( me->query_eval() > 50 )
      return( write( "You have been away from nature too long.\n" ), 1 );
    
    
    if( present_clone( "/zone/guild/mageslayer/obj/shoulder_implant", me ) ||
        present_clone( "/zone/guild/mageslayer/obj/tail_implant",     me ) ||
        present_clone( "/zone/guild/mageslayer/obj/eye_implant",      me ) )
    {
      tell_object( me, "You have been implanted with foul technology. "
        "A true shaman needs only nature.\n" );
      return 1;
    }
        
    
    arm = me->query_armor_worn();
    if( sizeof( arm ) )
      foreach( armor : arm )
    if( armor->query( MetalP ) )
    {
      if( !armor->query( RingP ) && !armor->query( AmuletP ) &&
          !armor->id( "earring" ) && !armor->id( "wristwatch" ) )
        {
          x += 1;
          break;
        }
    }

    if( x )
    {
      tell_player( me, "You sense that your armor will not " 
        "allow you to commune properly with nature." );
      return 1;
    }
    
    return 0;
}

int wear_signal( object armor, object me )
{

    if( armor->query( RingP ) || armor->query( AmuletP ) ||
        armor->id( "earring" ) || armor->id( "wristwatch" ) ||
        armor->query( ShieldP ) )
        return 0;

    //No metals.
    if( armor->query( MetalP ) )
    {
      if( me->query_wizard() )
      {
        tell_object( me, "Mortal guildmembers wouldn't be able to "
          "wear that.\n" );
        return 0;
       }

      tell_object( me, "That item would restrict your ability to "
        "commune with nature.\n" );
        return 1;
    }
    return 0;
}      

void join_comm( object me )
{
   object shad;
   
   ::join_comm( me );

   shad = clone_object( GuildShadow );
   shad->sh_init( me );
}

void leave_comm( object me )
{
   ::leave_comm( me );
   me->kill_shaman_shad();
}
