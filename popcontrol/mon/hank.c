#include <popcontrol.h>

inherit MonsterTalk;
inherit MonsterAsk;

void extra_create()
{
    set_name( "Hank" );
    
    add_alias( "hank" );
    add_alias( "gustof" );
    add_alias( "hank gustof" );
    
    set_short( "Hank Gustof" );
    set_ansi_short( YEL "Hank Gustof" );
    set_long( "Hank's skin is tough and leathery. He looks to "
      "be around fifty years old. He is in extremely good shape "
      "for a man his age all things considered. He walks with a "
      "slight limp. His face is permanently plastered in a smile "
      "and his cheeks are rosy. You can smell alcohol on him." );
    
    set_gender( "male" );
    set_race( "dwarf" );
    
    set_guild( "fighter" );
    
    set_alignment( MALICIOUS_AL );
    
    set_stat( "str", 100 + random( 25 ) );
    set_stat( "con", 300 + random( 10 ) );
    set_stat( "wil", 300 );
    set_stat( "dex", 130 );
    
    set_proficiency( "rifle", 50 );
    set_skill( "dodge", 65 );
    
    set( NoStealP, 1 );
    set( NoStunP, 1 );
    
    set_natural_ac( 10 );
    
    set_heal_rate( 30 );
    set_heal_amount( 6 );
    
    set_max_damage( 30 );
    
    set_chat_rate( 20 );
    set_chat_chance( 20 );
    
    add_phrase( "#peer" );
    add_phrase( "#say I love this bar!" );
    add_phrase( "#emote pours himself a shot." );
    add_phrase( "#say Ah, to hunt again... The thrill of the chase, "
      "that's what it was all about." );
    
    ask_me_about( "club", "#say We got the best club in all "
      "the world. Behind that door our members are sitting "
      "in plush chairs sipping on the finest beverages and "
      "recalling their latest hunt. We live for the hunt." );
    ask_me_about( "hunt", "#say All types of people like to hunt and "
      "everyone has varying skill levels. Of course the most revered "
      "hunters hunt the most dangerous game." );
    ask_me_about( "game", "#say What do you think it is? "
      "It's other sentient and capable beings. Once you get tired of "
      "whacking brain dead creatures in the head with a stick you should join "
      "up with us. See if you can cut it as a member." );
    ask_me_about( "join", "@check" ); 
    
    move_object( clone_object( PARM "pants" ),    THISO );
    move_object( clone_object( PARM "shirt" ),    THISO );
    
    add_money( 50 + random( 40 ) );
    
    command( "equip" );
}

int check()
{
    if( THISP->query( "player_kills" ) < 10 )
    {
      command( "laugh", THISO );
      command( "say I'd like to let you in. But you don't " 
        "seem to have a real interest in hunting the most "
        "dangerous game. Maybe if you did a bit more hunting... ",
        THISO );
      command( "emote looks around quickly.", THISO );
      command( "say I'll help you out a bit. I love it when younger "
        "people show an interest in the sport.", THISO );
      command( "emote gives you a rusty old boom stick." );
      
      move_object( clone_object( PWEAP "boomstick" ), THISP );
      
      command( sprintf( "give %s boomstick", THISP->query_real_name() ),
        THISO );
      return 1;
    }
    if( THISP->query( "player_kills" ) > 10 )
    {
      command( "grin", THISO );
      command( "say Well well well. Looks like you have hunted the "
        "deadliest game. Of course it's not all about hunting the deadliest "
        "game. Sometimes we hunt very dangerous beasts too cook them.",
        THISO );
      command( "laugh", THISO );
      command( "say For example, the Rancor. Most people just assume "
        "it's for spacey religions. Like we would ever hunt a "
        "cryptozoological species. I happen to know of a place where "
        "you can find a delicious Rancor. I'll give you a bit of bait "
        "and you bring back some meat. Then you can join the club!", THISO );
      command( "cackle", THISO );
      command( "say That is... If you live, this isn't some weak spacey "
        "fake Rancor. Be careful out there!", THISO );
      return 1;
    }
}    


//These are called by the room common.c when someone
//enters.
void start_greet( object person ) 
{
    call_out( "greet", 3, person );
}

void greet()
{
    command( "say Oh hullo there! It's good to see someone stopping in "
      "and checking out our club. If you are interested in becoming "
      "a member you're in luck! I do all the pre-screening. Go ahead "
      "and ask me about the club I'll try to fill you in as best as "
      "I can.", THISO );
}
