object me;
void sh_init( object arg )
{
    me = arg;
    shadow( me, 1 );
}
status query_no_wear( object armor, object blah )
{

    if( armor->query(RingP) || armor->query(AmuletP) ||
        armor->id("earring") || armor->id("wristwatch") )
        return 0;

    //  no steel, iron, etc.
    if( armor->query( MetalP ) && is_wizard( THISP ) )
    {
      tell_object( THISP, "Mortal guildmembers wouldn't be able to "
        "wear that.\n" );
      return 0;
    }     
    if( armor->query( MetalP ) )    
    {
      tell_object( THISP, "That item is too rigid and heavy to allow "
        "freedom of movement.\n" );
      return 1;
    }
    return 0;
}
