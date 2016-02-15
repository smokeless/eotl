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
      case 0 : rankfirst = sprintf( "%s is middle aged. %s black hair " 
        "shines in the light. ", name, CAP( possessive( THISO ) ) ); break;
      case 1 : rankfirst = sprintf( "%s is very confident. %s shirt is pressed and " 
        "there is not a single wrinkle in %s pants. ", name, CAP( possessive( THISO ) ), 
        possessive( THISO ) );                                       break;
      case 2 : rankfirst = sprintf( "%s's face is covered in tattoos, " 
        "all of them are science related. %s must take science very seriously. ", 
        name, CAP( subjective( THISO ) ) );                          break;
      case 3 : rankfirst = sprintf( "%s looks a little under the weather. "
        "%s skin is wrinkly and dry looking. ", name, CAP( possessive( THISO ) ) );
                                                                     break;
    }
      
    switch( random( 4 ) )
    {
      case 0 : ranksecond = sprintf( "%s plods slowly "
        "forwards. Each step looks harder than the last. ", 
        CAP( subjective( THISO ) ) ); break;
      case 1 : ranksecond = sprintf( "%s is starting to slow down a bit. It is "
      "apparent that years of working in an office have taken both a physical and "
      "emotional toll. ", CAP( subjective( THISO ) ) );    break;
      case 2 : ranksecond = sprintf( "%s looks concerned and a very "
        "over worked. %s sighs quietly to %sself as you pass. ", 
        CAP( subjective( THISO ) ), CAP( subjective( THISO ) ),
        objective( THISO ) );                              break;
      case 3 : ranksecond = sprintf( "%s is in no hurry. The way %s moves "
        "indicates someone who is just waiting for the clock to run out. ",
        CAP( subjective( THISO ) ), subjective( THISO ) ); break;
    }
    
    switch( random( 4 ) )
    {
      case 0 : rankthird = sprintf( "%s eyes are dull and tired. ", 
        CAP( possessive( THISO ) ) );                             break;
      case 1 : rankthird = sprintf( "%s eyes seem cold, calculating. "
        "%s will be moving up the ladder soon.", 
        CAP( possessive( THISO ) ), CAP( subjective( THISO ) ) ); break;
      case 2 : rankthird = sprintf( "%s eyes are lifeless and dopey. "
        "You can tell %s won't be promoted anytime soon.",
        CAP( possessive( THISO ) ), subjective( THISO ) );        break;
      case 3 : rankthird = sprintf( "%s eyes glance around wildly and "
        "%s looks frightened. ", 
        CAP( possessive( THISO ) ), subjective( THISO ) );        break;
    }
    
    switch( random( 4 ) )
    {
      case 0 : rankfourth = sprintf( "%s yawns at you. ",
        CAP( subjective( THISO ) ) ); break;
      case 1 : rankfourth = sprintf( "%s frowns slightly.", 
        CAP( subjective( THISO ) ) );                      break;
      case 2 : rankfourth = sprintf( "%s cracks %s knuckles.",
        CAP( subjective( THISO ) ), possessive( THISO ) ); break;
      case 3 : rankfourth = sprintf( "%s is a million miles away "
      "in thought.", CAP( subjective( THISO ) ) );         break;
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
    
    set_short( sprintf( "%s %s, a mid level researcher", 
    name, lastname ) );
    
    set_long( sprintf( "%s %s %s %s", rankfirst, ranksecond, rankthird,
      rankfourth ) );
    
    set_race( race );
    
    set_alignment( NEUTRAL_AL );
    
    set_stat( "str", 120 + random( 10 ) );
    set_stat( "con", 100 + random( 10 ) );
    set_stat( "wil", 100 + random( 10 ) );
    set_stat( "int", 100 + random( 10 ) );
    set_stat( "dex", 100 + random( 10 ) );
    
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
    
    add_phrase( sprintf( "%s frowns at you.", name ) );
    add_phrase( sprintf( "%s refuses to make eye contact with you.", name ) );
    add_phrase( "#say I hope I can get some vacation." );
    add_phrase( "#say I wish they'd just promote me already." );
    add_phrase( "#say Ugh. More visitors." );
    
    ask_me_about( "promotion", "I've been here long enough. "
      "The least they could do is acknowledge that." );
    ask_me_about( "vacation", "I really would like to sneak into "
      "Eternal city. Some day. Some day." );	  
    
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
