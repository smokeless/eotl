object me;
short()
{
    return( "Upload" );
}
void sh_init( object arg )
{
    me = arg;
    shadow( me, 1 );
}
string long()
{
    return( "an awesome party dude." );
}
