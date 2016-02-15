#include <ansi.h>
inherit NewThingCode;
inherit AnsiTellCode;
int power;

void extra_create()
{
    set_ids( ({ "cloud", "a rain cloud", "rain cloud", "rain" 
      "cluster", "torrential cloud", "torrential rain cloud",
      "a cluster of torrential rain clouds", "clouds",
      "rain clouds", "torrential clouds", "torrential rain "
      "clouds" }) );
    set_short( "a cluster of torrential rain clouds" );
    set_ansi_short( CYAN "a torrential rain cloud" );
    set_long( "This cloud is pouring down soothing rain. "
      "The warm rain soaks the ground, pooling up in "
      "cracks and crevices. The air smells of wet "
      "earth. Over all it feels great." );
    
    set_gettable( 0 );
    set_value( 0 );
}

void set_me_up( int dur, int attune, int hrain, int str )
{
    power = attune + hrain + ( str / 10 ) + random( 10 );
    call_out( "heal_people", 1 );
    call_out( "go_away", dur );
    return;
}

void heal_people()
{
    object *ob;
    int x;

    ob = filter( all_inventory( ENV( THISO ) ), #'living );
    x = 0;
    
    while( x < sizeof( ob ) )
    {
      ob[ x ]->add_hp( random( power ) );
      ob[ x ]->add_mana( random( power ) );
      ob[ x ]->add_fatigue( random( power ) );
      x++;
    }
    ansi_tell_room( ENV( THISO ), "The rain soaks into your "
      "body refreshing you!", CYAN, ({ }) );

    call_out( "heal_people", 12 );
}

int destruct_signal( object d, object a )
{
    while( find_call_out( "heal_people" ) != -1 )
      remove_call_out( "heal_people" );
    
    return 0;
}

void go_away()
{
    ansi_tell_room( ENV( THISO ), "The clouds clear up and the sky "
      "returns to its normal color.", CYAN, ({ }) ); 
    destruct( THISO );
}
