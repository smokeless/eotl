object me;

sh_init(object who)
{
    me = who;
    shadow(who, 1);
}

void go_byebye() { destruct(THISO); }

string query_race() 
{
  return( "Beer Elf" );
}

string query_real_race()
{ 
return( "Beer Elf" ); 
}
