object shaman;

status sh_init(object ob)
{
    shaman = ob;
    shadow( shaman, 1 );    
}

string short( object looker )
{
    string myshort;

    if( !stringp( myshort = shaman->short( looker ) ) )  
      return 0;
    
    if( objectp( looker ) && is_wizard( looker ) )
      return sprintf( "a raccoon, [%s]", myshort );

    return( "a raccoon" );
}

mapping query_skill_map()
{
   return ([ "steal", 2 ]);
}

mixed query_skills()
{
    return ({ "steal" });
}
