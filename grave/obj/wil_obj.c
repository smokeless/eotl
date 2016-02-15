inherit BonusObject;

object me, bonus;

void do_bonus( object who, int time)
{
    me = who;
    THISO->set_stat_bonus( "wil", -5 );
    THISO->set( "destruct_time", time );
    THISO->activate( me );
}

void destruct_me()
{
    destruct(THISO);
}
