object me;
string prefix;

sh_init( object user )
{
    me = user;
    shadow( me, 1 );
    string *names = ({ "Wild", "Doc", "Loner", "Loco",
     "Lucky", "Bandit", "Bullet", "Rawhide", "Gravedigger",
     "Pecos" });
    int x = random( sizeof( names ) );
    prefix = names[x];
}

string query_name() 
{ 
    if( me->query_ghost() )
      return( sprintf( "The ghost of %s %s", prefix, 
      CAP( me->query_real_name() ) ) );
    else
        return( sprintf( "%s %s", prefix, CAP( me->query_real_name() ) ) ); 
} 

kill_signal( object victim, string cause )
{
    string *sayings = ({  
      "You see, in this world, there's two kinds "
      "of people, those with loaded guns, and those who die. You die.",
      "I'm your huckleberry.",
      "Dyin' ain't much of a living.",
      "I've killed women. I've killed children. "
      "I've killed just about everything that walked " 
      "or crawled at one point. Now I've killed you.",
      "We've all got it comin' Kid.",
      "A person's only as big as the distance from their holster to their heart.",
      "Funny thing killin' someone. You take away everything they got and "
      "everything their gonna have.", 
      "What an unpleasant surprise.",
      "I've killed more than the drought.",
      "I won't deny my killing done. I won't deny my name.",
      "When I get to dislikin' someone they ain't around long.",
      "Buzzards gotta eat. Same as worms.",
      "Don't piss down my back and tell me it's raining.",
      "They say you can't get 'em all. I reckon I can't. But I got "
      "nothin' better to do.",
      "Hell is comin' to breakfast." });
      
    string death = sayings[ random( sizeof( sayings ) ) ];  
    
    "/secure/player/commands/say.c"->do_command( me, death );

    return me->kill_signal( victim, cause );
}

kill_outlaw_shad()
{
   remove_shadow( THISO );
   destruct( THISO );
}
