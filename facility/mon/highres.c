#include <facility.h>

inherit MonsterAsk;
inherit MonsterMove;
inherit MonsterTalk;
inherit AnsiTellCode;
inherit SpecialAttackCode;

void extra_create()
{
    string race, name, lastname, rankfirst, 
      ranksecond, rankthird, rankfourth, attk;
        
    int sex = random( 2 );
    
    if( sex == 1 )
    {
      set_gender( "male" );
      switch( random( 15 ) )
      {
        case 0  : name = "Gary";     break;
        case 1  : name = "Larry";    break;
        case 2  : name = "Sigmund";  break;
        case 3  : name = "Alfred";   break;
        case 4  : name = "Gregory";  break;
        case 5  : name = "Lester";   break;
        case 6  : name = "Arnold";   break;
        case 7  : name = "Homer";    break;
        case 8  : name = "James";    break;
        case 9  : name = "Atherton"; break;
        case 10 : name = "Eric";     break;
        case 11 : name = "Robert";   break;
        case 12 : name = "Mike";     break;
        case 13 : name = "Gabe";     break;
        case 14 : name = "Malcom";   break;
      }  
    } 
    if( sex == 0 )
    {
      set_gender( "female" );
      
      switch( random( 15 ) )
      {
        case 0  : name = "Gale";       break;
        case 1  : name = "Edith";      break;
        case 2  : name = "Marilyn";    break;
        case 3  : name = "Margo";      break;
        case 4  : name = "Agnes";      break;
        case 5  : name = "Nelly";      break;
        case 6  : name = "Mildred";    break;
        case 7  : name = "Charlotte";  break;
        case 8  : name = "Eva";        break;
        case 9  : name = "Victoria";   break;
        case 10 : name = "Stella";     break;
        case 11 : name = "Vivian";     break;
        case 12 : name = "Ruth";       break;
        case 13 : name = "Sophronia";  break;
        case 14 : name = "Virginia";   break;
      }
    }
    
    switch( random( 15 ) )
    {
      case 0  : lastname = "Masterson"; break;
      case 1  : lastname = "Laymon";    break;
      case 2  : lastname = "Wilson";    break;
      case 3  : lastname = "McCammon";  break;
      case 4  : lastname = "Bierce";    break;
      case 5  : lastname = "Blackwood"; break;
      case 6  : lastname = "Lovecraft"; break;
      case 7  : lastname = "Saul";      break;
      case 8  : lastname = "Poe";       break;
      case 9  : lastname = "Ketchum";   break;
      case 10 : lastname = "Koontz";    break;
      case 11 : lastname = "Lumley";    break;
      case 12 : lastname = "Lansdale";  break;
      case 13 : lastname = "Barker";    break;
      case 14 : lastname = "Bloch";     break;
    }
    
    switch( random( 4 ) )
    {
      case 0 : race = "drow_elf"; break;
      case 1 : race = "dwarf";    break;
      case 2 : race = "human";    break;
      case 3 : race = "gnome";    break;
    }
    
    switch( random( 4 ) )
    {
      case 0 : rankfirst = sprintf( "%s is tall and middle aged. %s "
        "shirt is wrinkled and %s looks dazed. ", name, 
        CAP( possessive( THISO ) ), subjective( THISO ) );      break;
      case 1 : rankfirst = sprintf( "%s is a bit overweight. %s presence "
        "is chilling. There is something dark about %s. ", 
        name, CAP( possessive( THISO ) ), objective( THISO ) ); break;
      case 2 : rankfirst = sprintf( "There is a silky shine to %s hair. %s "
        "looks clean and well groomed. Almost too well groomed. Like %s is "
        "hiding something. ", possessive( THISO ), CAP( subjective( THISO ) ), 
        subjective( THISO ) );                                  break;
      case 3 : rankfirst = sprintf( "%s has taut skin and well toned muscles. %s "
        "looks to only be around thirty, though you know %s is much older. ", name,
        CAP( subjective( THISO ) ), subjective( THISO ) );      break;
    }
    
    switch( random( 4 ) )
    {
      case 0 : ranksecond = sprintf( "%s dutifully concentrates on "
        "whatever %s task maybe. %s concentration is unwavering and intense. ", 
        CAP( subjective( THISO ) ), possessive( THISO ), 
        CAP( possessive( THISO ) ) );                                break;
      case 1 : ranksecond = sprintf( "%s moves with great agility. %s speed "
        "and grace is almost supernatural. As if %s wasn't fully of this world. ", 
        CAP( subjective( THISO ) ), CAP( possessive( THISO ) ), 
        subjective( THISO ) );                                       break;
      case 2 : ranksecond = sprintf( "%s refuses to pause for a moment. %s "
        "rushes forward lost in thought. ", CAP( subjective( THISO ) ), 
        CAP( subjective( THISO ) ) );                                break;
      case 3 : ranksecond = sprintf( "%s shoes are scuffed and the soles are almost "
        "worn through. %s proceeds relentlessly forwards driven by an unknown goal. ",
        CAP( possessive( THISO ) ), CAP( subjective( THISO ) ) );    break;
    }
      
    switch( random( 4 ) )
    {
      case 0 : rankthird = sprintf( "%s eyes are crisp and calculating. ", 
        CAP( possessive( THISO ) ) );                            break;
      case 1 : rankthird = sprintf( "%s eyes seem cold, yet relentless. ",
        CAP( possessive( THISO ) ) );                            break;
      case 2 : rankthird = sprintf( "%s eyes are tireless and unyielding. ",
        CAP( possessive( THISO ) ) );                            break;
      case 3 : rankthird = sprintf( "%s eyes intake the whole of the room, "
        "%s is searching for something. ", 
        CAP( possessive( THISO ) ), subjective( THISO ) );       break;
    }
    
    switch( random( 4 ) )
    {
      case 0 : rankfourth = sprintf( "%s only cares for work.",
        CAP( subjective( THISO ) ) );                      break;
      case 1 : rankfourth = sprintf( "%s licks %s lips at the sight of you.", 
        CAP( subjective( THISO ) ), possessive( THISO ) ); break;
      case 2 : rankfourth = sprintf( "%s is a tireless asset to this company.",
        CAP( subjective( THISO ) ) );                      break;
      case 3 : rankfourth = sprintf( "%s has no fear. No worry.",
        CAP( subjective( THISO ) ) );                      break;
    }
    
    switch( random( 100 ) )
    {
       case 0..20  : attk = "sympathy"; break;
       case 21..70 : attk = "shove";    break;
       case 71..76 : attk = "panic";    break;
       case 77..99 : attk = "eyeclaw";  break;
    }
    
    set_name( sprintf( "%s %s", name, lastname ) );
    
    add_alias( "researcher" );
    add_alias( "res" );
    add_alias( "doctor" );
    add_alias( lower_case( name ) );
    add_alias( lower_case( lastname ) );
    add_alias( sprintf( "%s %s", lower_case( name ), 
      lower_case( lastname ) ) );
    
    set_short( sprintf( "%s %s, a high level researcher", 
    name, lastname ) );
    
    set_long( sprintf( "%s %s %s %s", rankfirst, ranksecond, rankthird,
      rankfourth ) );
    
    set_race( race );
    
    set_alignment( NEUTRAL_AL );
    
    set_stat( "str", 120 + random( 30 ) );
    set_stat( "con", 100 + random( 30 ) );
    set_stat( "wil", 100 + random( 30 ) );
    set_stat( "int", 100 + random( 30 ) );
    set_stat( "dex", 100 + random( 30 ) );
    
    set_avoid_props( ({ NoWanderRoomP }) );
   
    set_proficiency( "hands", 75 );
    set_skill( "dodge", 50 );
    
    set_natural_ac( 5 );
    set_heal_rate( 30 );
    set_heal_amount( 10 );
    
    set( NoStealP, 1 );
    set( NoStunP, 1 );
    
    set_move_rate( 20 );
    set_move_chance( 20 + random( 20 ) );
    
    set_chat_chance( 10 );
    set_chat_rate( 10 + random( 30 ) );
    
    add_phrase( "#say This work must never end." );
    add_phrase( "#say If you carry the 2..." );
    add_phrase( "#say I feel something... Something near." );
    
    ask_me_about( "work", "I have no need to tell you anything." );
    ask_me_about( "something", "I have no need to tell you anything." );
    ask_me_about( "math", "I have no need to tell you anything." );	 
    
    add_money( random( 100 ) );
    
    move_object( clone_object( FARMOR "pants" ), THISO );
    move_object( clone_object( FARMOR "shirt" ), THISO );
    
    command( "equip" );
    add_special_attack( attk, THISO, 5 );
}

int sympathy( object vic, object att )
{
    int which = random( 2 );
    string says;
    
    string victim = vic->query_name();
    string attacker = att->query_name();
    
    switch( random ( 6 ) )
    {
      case 0 : says = "say After all I've seen? This...";              break;
      case 1 : says = "say There is something truely miserable here."; break;
      case 2 : says = "say I feel everything.";                        break;
      case 3 : says = "say My soul isn't ready to be free!";           break;
      case 4 : says = "say I have seen the dark, so calm.";            break;
      case 5 : says = "say In death I will find no rest.";             break;
    }
    
    command( says );
    
    ansi_tell_room( ENV( att ), sprintf( "%s begins to speak, "
      "%s stays %s hand for a moment.\n", attacker, victim, 
      possessive( vic ) ), BLU, ({ att, vic }) );
    
    
    ansi_tell( vic, sprintf( "%s looks pitiful and sad, "
      "mournful even, you feel a surge of empathy for %s.", 
      attacker, objective( att ) ), BLU );
    
    if( which == 1 )
    {
      vic->add_combat_delay( 4 );
      return 1;
    }
    
    if( which == 0 ) 
    {
      vic->remove_target( THISO );
      return 1;
    }
    
    return 1;
}

int shove( object vic, object att )
{
    int dam = 15 + random( 50 );
    string victim = vic->query_name();
    string attacker = att->query_name();
    string says;
    
    switch( random( 8 ) )
    {
      case 0 : says = "say You aren't my supervisor!";             break;
      case 1 : says = "say Get off my back!";                      break;
      case 2 : says = "say I'm working as hard as I can!";         break;
      case 3 : says = "say I feel no pain, there is only work.";   break;
      case 4 : says = "say Why?";                                  break;
      case 5 : says = "say I've seen tougher specimens.";          break;
      case 6 : says = "say I finished the rest, I'll finish you."; break;
      case 7 : says = "say More for him.";                         break;
    }
    
    command( says );
    
    ansi_tell_room( ENV( att ), 
      sprintf( "A mighty shove sends %s toppling "
      "to the ground\n", victim ), YEL, ({ att, vic }) );
    
    ansi_tell( vic, sprintf( "A mighty shove from %s " 
      "sends you toppling.", attacker ), YEL );
    
    vic->add_combat_delay( 4 );
    vic->take_damage( dam, 0, "blunt", att );
    
    return 1;
}

int panic( object vic, object att )
{
    string victim = vic->query_name();
    string attacker = att->query_name();
    string *dirs = m_indices( ENV( THISO )->query( "exits" ) );
    int exitsnumber = sizeof( dirs );
    int exitto = random( exitsnumber );
    string direction = dirs[exitto];
    
    ansi_tell_room( ENV( att ), sprintf( "%s gets a "
      "mad look in %s eyes, %s begins to scream in "
      "terror. %s says: I just want out!!!\n", attacker,
      possessive( att ), attacker, attacker ), 
      YEL, ({ att }) );
    
    command( direction );
    
    return 1;
}
int eyeclaw( object vic, object att )
{
    string victim = vic->query_name();
    string attacker = att->query_name();
    
    ansi_tell_room( ENV( att ), sprintf( "%s reaches out at " 
      "%s, viciously grabbing %s eyes.\n", 
      attacker, victim, possessive( vic ) ), RED, 
      ({ vic, att }) );
    ansi_tell( vic, sprintf( "%s shoves %s thumbs " 
      "deep into your eye sockets.", 
      attacker, possessive( att ) ), RED );
    
    vic->take_damage( 30 + random( 5 ), 0, "piercing", att );
    
    return 1;
}   
