inherit BonusObject;

object me;
int lose_str, lose_con, time;
void extra_create()
{
    set( PoisonP, 1 );
}
void do_bonus( object who, int time )
{
    me = who;
    
    lose_str = random( 20 );
    lose_con = random( 20 );
    if( me->query_resistance( "disease" ) > random( 30 ) + 5 )
    {
      destruct( THISO );
    }
    tell_object( me, "You feel horribly diseased.\n");
    THISO->set_stat_bonus( "str", -lose_str );
    THISO->set_stat_bonus( "con", -lose_con );
    THISO->set( "destruct_time", time );
    THISO->activate( me );
}


void destruct_me()
{
    tell_object( me, "You feel better as the "
      "disease leaves your body.\n" );
   
    destruct(THISO);
}
