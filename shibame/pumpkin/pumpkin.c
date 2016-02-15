#include <ansi.h>
inherit MonsterCode;
inherit MonsterMove;
inherit MonsterTalk;
inherit MonsterNoHunt;
inherit AnsiTellCode;
inherit SpecialAttackCode;

#define RACE "/usr/socialism/pumpkin/pumpkinrace"
#define BELLY "/usr/socialism/pumpkin/belly"
#define KILLEDFILE "/usr/socialism/pumpkin/killers"

void extra_create()
{
    set_name( "The Great Pumpkin" );
    
    add_alias( "pumpkin" );
    add_alias( "great" );
    add_alias( "great pumpkin" );
    add_alias( "the great pumpkin" );
    add_alias( "great pumpkin" );
    
    set_short( "The Great Pumpkin" ); 
    set_ansi_short( YEL "The Great Pumpkin" );
    
    set_long( "Great might be an understatement. This "
      "pumpkin is gargantuan. Its face is comprised of "
      "two oddly spaced eyes and a row of very sharp teeth. "
      "Its legs are a mass of green tendrils. Amongst the tendrils "
      "you can make out a mess of wires. Someone has rebuilt this "
      "creature. They had the technology. They had the capability "
      "to build the world's first bionic pumpkin. Better than it "
      "was before. Better, stronger, faster." );  
    
    set_gender( "unknown" );
    set_race( RACE );
    
    set_alignment( NEUTRAL_AL );
    
    set_percent_bonus_exp( -50 ); //12mil xp was pretty excessive.
    
    set_stat( "str", 5000 );
    set_stat( "con", 5000 );
    
    set_proficiency( "hands", 150 );
    set_skill( "dodge", 200 );
    
    set( NoStealP, 1 );
    set( NoStunP, 1 );
    
    set_natural_ac( 10 );
    
    set_heal_rate( 30 );
    set_heal_amount( 1000 );
    
    set_move_rate( 60 );
    set_move_chance( 50 );
    set_wander_dir( ({ "/zone/null/eternal/", 
      "/zone/guild/" }) );
    
    set_chat_rate( 20 );
    set_chat_chance( 80 );
    
    add_phrase( "#peer" );
    add_phrase( "#say I hear people are carving up my kind! "
      "I won't stand for that!!!" );
    add_phrase( "#say Voting on pumpkin mutilation is "
      "disgusting." );
    add_phrase( "#say I will rip your soul out through your "
      "throat!" );
    add_phrase( "#say When there’s no more room in Hell, "
      "carved pumpkins will walk the Earth." );
    add_phrase( "#say To die. To be really dead, that must be glorious!" );
    add_phrase( "#say Well, now, let me put it this way. If all the " 
      "pumpkins buried around here were to stand up all at once, we'd " 
      "have one hell of a population problem." );
    add_phrase( "@children" );
    add_phrase( "#say I heard, as it were the noise of thunder, "
      "one of the four beasts saying, Come and see." );
      
    add_special_attack( "glomp", THISO, 30 );
}

int children()
{
    tell_room( ENV( THISO ), "You can hear howling in the "
      "distance.\n" );
    command( "say Listen to them. The children of the night. "
      "What sweet music they make.", THISO );
    return 1;    
}

int glomp( object victim, object attacker )
{
    reset_combat();
    command( "say YOU DARE TO ATTACK ME!!!", attacker );
    ansi_tell_room( ENV( attacker ), sprintf( "The Great "
      "Pumpkin skitters forwards on its tendrils and devours "
      "%s in one bite.\n", victim->query_name() ), RED,
      ({ victim }) );
    ansi_tell( victim, "The Great Pumpkin skitters forwards "
      "on its tendrils. It gums you with its disgusting "
      "pumpkin teeth, then swallows you.\n", RED );
    
    victim->move_player( "&&", BELLY, 1 );
    
    command( "belch", THISO );
    
    ansi_tell( victim, "You find yourself inside "
      "a very orange stomach.\n", RED );
    
    return 1;
}

//when people in the pumpkin room rip flesh.
int heartburn( string arg )
{
    command( "groan", THISO );
    command( sprintf( "say Ugh. My stomach is upset. I shouldn't "
      "have eaten %s.\n", arg ), THISO );
    command( "emote takes a huge Tums tablet.", THISO );
    return 1;
}
        


//So that the pumpkin projectile vomits its inventory.
int DeathSequence( object killer, string cause, int nocorpse )
{
    string who = killer->query_real_name();
    write_file( KILLEDFILE, sprintf( "%s killed the great "
      "pumpkin! %s\n", who, ctime() ) );
    BELLY->sick();   
    return( ::DeathSequence( killer, cause, 1 ) );
}
