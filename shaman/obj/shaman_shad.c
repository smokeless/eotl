/*
Shaman guild shadow. 
Taplash 2014
*/
#include <ansi.h>
inherit AnsiTellCode;
inherit SpecialAttackCode;
#define WINDOBJ "/usr/taplash/shaman/obj/wind_obj"
object shaman;
string imbue;

status sh_init(object ob)
{
    shaman = ob;
    shadow( shaman, 1 );
    shaman->set( "guild_score", sprintf( "Shield Imbue:  %s",
      CAP( query_imbue() ) ) );
    
    add_special_attack( "imbued_attack", shaman, 100 ); 
    //The attack always goes off but the testing is handled
    //within the special attack and not here.    
}

int is_shaman()
{
    return 1;
}
void imbue( string arg )
{
    imbue = arg;
}

string query_imbue()
{
    return imbue || "none";
}

void kill_shaman_shad()
{
    shaman->remove_prop( "guild_score" );
    shaman->remove_special_attack( "imbued_attack" );
    remove_shadow( THISO );
    destruct( THISO );
    
}

int imbued_attack( object vic, object att )
{
    object bonus_obj;
    string *shields = att->query_shields();
    int num_shields = sizeof( shields );
    int dam;
    if( num_shields == 0 )
      return 0;
    
    string which_shield = shields[ random( sizeof( shields ) ) ]->query_short();
    
    if( shaman->query_skill( "imbue shield" ) <= 0 )
      return 0;
    
    int shaman_chance = shaman->query_skill( "imbue shield" ) / 2;
    
    if( !vic || !att )
      return 0;
    
    if( shaman_chance < random( 100 ) )
      return 0;
    
    if( shaman->query_imbue() == "none" )
      return 0;
    
    if( shaman->query_imbue() == "fire" )
    {
      ansi_tell( att, sprintf( "%s bursts with flames burning "
        "%s to a crisp!!!", CAP( which_shield ), vic->query_name() ),
        RED );
      ansi_tell( vic, sprintf( "%s throws up %s it ignites charring "
        "you with fiery power!", shaman->query_name(), which_shield ),
        RED );
      ansi_tell_room( ENV( shaman ), sprintf( "%s throws up %s "
        "it blasts %s with fiery power.", shaman->query_name(),
        which_shield, vic->query_name() ), RED, ({ att, vic }) );
      
      dam = shaman->query_skill( "natural attunment" ) +
        shaman->random( shaman->query_skill( "natural attunement" ) ) +
        random( shaman->query( "dex" ) );
      
      vic->take_damage( dam, 0, "fire", shaman );
      return 1;
    }
    
    if( shaman->query_imbue() == "air" &&  
      !present_clone( WINDOBJ, shaman ) )
    {
      ansi_tell( att, sprintf( "A rushing wind pours from "
        "%s. You suddenly feel much faster!", which_shield ),
        CYAN );
      ansi_tell( vic, sprintf( "A rushing wind pours from "
        "%s. %s speeds up!", which_shield, att->query_name() ),
        CYAN );
      ansi_tell_room( ENV( shaman ), sprintf( "A rushing wind pours from "
        "%s. %s speeds up.", which_shield, att->query_name() ),
        CYAN, ({ att, vic }) );
      bonus_obj = clone_object( WINDOBJ );
      move_object( bonus_obj, shaman );
      bonus_obj->start_bonus( shaman,
        shaman->query_skill( "natural attunement" ) );
      return 1;
    }
    else
      return 0;
    
    if( shaman->query_imbue() == "water" )
    {
      ansi_tell( att, sprintf( "Water pours from %s, refreshing "
        "you.", which_shield ), BLUE );
      ansi_tell( vic, sprintf( "Water pours from %s, refreshing "
        "%s.", which_shield, att->query_name() ), BLUE );
      ansi_tell_room( ENV( att ), sprintf( "Water pours from %s, "
        "refreshing %s.", which_shield, att->query_name() ), BLUE,
        ({ vic, att }) );
      shaman->add_hp( random( shaman->query_skill( "natural attunement" ) )+
        random( shaman->query_skill( "imbue shield" ) ) );
      return 0;
    }
    
    if( shaman->query_imbue() == "earth" )
    {
      ansi_tell( att, sprintf( "%s quivers and shakes slamming into "
        "%s!", which_shield, vic->query_name() ), YELLOW );
      ansi_tell( vic, sprintf( "%s quivers and shakes slamming into "
        "you!!!", which_shield ), YELLOW );
      ansi_tell_room( ENV( att ), sprintf( "%s quivers and shakes "
        "slamming into %s", which_shield, vic->query_name() ), YELLOW,
        ({ vic, att }) );
      vic->add_delay( random( shaman->query_skill( "natural attunment" ) )/10
      return 0;
    }
}
