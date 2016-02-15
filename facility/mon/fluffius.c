#include <facility.h>

inherit MonsterAsk;
inherit SpecialAttackCode;
inherit MonsterTalk;
inherit MonsterNoHunt;
inherit AnsiTellCode;

void extra_create() 
{
    set_name( "Ramsey" );
    add_alias( "ramsey" );
    add_alias( "khan" );
    add_alias( "guard" );
    add_alias( "ramsey khan" );
    
    set_short( "Ramsey Khan, Facility 31 Security" );
    set_ansi_short ( YEL "Ramsey Khan, Facility 31 Security" );
    
    set_long( "Ramsey stares idlely around the "
      "office, taking in every event and detail. "
      "Though he seems to be mainly focused on the "
      "exit to the west. You may not want to push your "
      "luck. His arms are massive and covered in thick fluffy "
      "hair. For some reason he smells like the stuffing " 
      "that is found inside of blankets. There maybe more "
      "to this man than meets the eye." );
    
    set_gender( "male" );
    set_race( "human" );
    
    set_guild( "fighter" );
    set_specialization( "bodyguard" );
    set_skill( "grapple", 20 );
    
    
    set_alignment( MALICIOUS_AL );
    
    set_stat( "str" , 100 );
    set_stat( "con" , 300 );
    set_stat( "wil" , 500 );
    set_stat( "dex" , 200 );
    
    full_heal();
    
    set_proficiency( "hands", 30 );
    set_skill( "dodge", 65 );
    
    set( NoStealP, 1 );
    set( NoStunP, 1 );
    
    set_natural_ac( 10 );
    
    set_heal_rate( 20 );
    set_heal_amount( 60 );
    
    set_chat_rate( 30 );
    set_chat_chance( 50 );
    
    add_phrase( "#spit" );
    add_phrase( "#say This way isn't for you" );
    add_phrase( "#growl" );
    add_phrase( "#emote smiles showing more teeth than necessary." );
    add_phrase( "#grin" );
    add_phrase( "#say Go head, ask me what happened to the last intern." );
    add_phrase( "#say I've killed more people for just looking at " 
      "that stairwell than you've got teeth in your head." );
    
    ask_me_about( "intern", "#say I put him in "
      "his place. Always asking about the stairwell, " 
      "always prying " );
    
    move_object( clone_object( FARMOR "shirt" ), THISO );
    move_object( clone_object( FARMOR "pants" ), THISO );
    move_object( clone_object( FWEAP  "nails" ), THISO );

//This call_out is seperate so that he will equip the nails and
//be at full health when he spawns. Since the nails do
//damage on wield.
    
    call_out( "equip", 1 );
    
    add_special_attack( "go_bear", THISO, 40 );
}

int equip()
{
    full_heal();
    command( "equip" );
    add_hp( THISO->query_max_hp() );
    return 1;
}

int go_bear( object victim, object attacker )
{
    string vil = victim->query_name();
    
    ansi_tell_room( ENV( attacker ), sprintf(
      "Ramsey twitches and shudders, his skin "
      "changing; growing hairier. He begins to "
      "shrink, roaring and growling. Stuffing "
      "explodes out of his wounds! %s takes "
      "a frightened step back.\n",
      CAP ( vil ) ), YEL, ({ victim, attacker }) );
    ansi_tell( victim, sprintf(
      "Ramsey twitches and shudders, his skin "
      "changing; growing hairier. He begins to "
      "shrink, roaring and growling. Stuffing "
      "explodes out of his wounds! You take a frightened " 
      "step back", vil ), YEL );
    
    set_short( "Fluffius Khan, Facility 31 Security" );
    set_ansi_short ( YEL "Fluffius Khan, Facility 31 Security" );
    
    set_long( "This teddy bear is fearsome. He's been well loved to "
      "to say the least. His fluffy fur is worn thread bare. His left "
      "eye just hangs loosely out of it's socket, fluff and lint sticking "
      "out like tinder for a fire." );
    
    set_name( "Fluffius" );
    
    
    add_alias( "fluffius" );
    add_alias( "khan" );
    add_alias( "fluffius khan" );
    
    remove_alias( "ramsey" );
    remove_alias( "ramsey khan" );
    
    set_gender( "male" );
    set_race( "teddybear" );
    
    set_stat( "str" , 200 );
    set_stat( "con" , 300 );
    set_stat( "wil" , 200 );
    set_stat( "dex" , 200 );
    
    set_proficiency( "hands", 40 );
    
    set_skill( "dodge", 65 );
    
    set( NoStealP, 1 );
    set( NoStunP, 1 );
    set_natural_ac( 10 );
    
    set_chat_rate( 30 );
    set_chat_chance( 10 );
    
    THISO->add_hp( THISO->query_max_hp() );
    
    remove_special_attack( "go_bear" );
    add_special_attack( "grapple", THISO, 20 );
    return 1;    
}

int grapple( object victim, object attacker )
{
    string vil = victim->query_name();
    string graptarg = victim->query_real_name();
    
    ansi_tell_room( ENV( attacker ), sprintf( "Fluffius "
      "lowers his center of gravity and prepares to "
      "grapple with %s", vil ), YEL, ({ victim, attacker }) );
    
    ansi_tell( victim, "Fluffius gets down low "
      "and prepares to grapple you!", YEL );
    
    command( sprintf( "grapple %s", graptarg ), THISO );
    command( "say Now you're in trouble!", THISO );
    
    add_special_attack( "stop", THISO, 1 );
    return 1;
}

int stop( object victim, object attacker )
{
    string vic = victim->query_name();
    
    command( "say This is total bullshit.", THISO );
    
    ansi_tell_room( ENV( THISO ), sprintf( "Fluffius deftly, "
      "steps out of the way of %s.", vic ), YEL, ({ victim }) );
    
    ansi_tell( victim, "Fluffius slams your head into the wall, "
      "you don't really feel like fighting anymore.", YEL );
    
    command( "say What is below isn't for you." );
    
    THISO->reset_combat();
    
    remove_special_attack( "stop" );
    
    return 1;
}
