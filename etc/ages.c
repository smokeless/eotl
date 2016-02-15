// Kharas 120425
// I wonder, how old are people in mud years?

void view_age(mixed container)
{
  write("Age of online players in mud years: \n");
  write("=================================== \n");
  foreach(mixed x : container )
  {
    write(x[1]+" -> "+x[0]+"\n");
  }

}

int sort_desc (mixed *a, mixed *b) 
{
   return a[1] < b[1];
}

mixed ages()
{  
  // alias j cc -s "/usr/kharas/etc/item/ages"->ages();
  // *seems some wizzards have a shadow that procs when
  //  their body is referenced. Try not to spam too much.

  string *container = ({});
  int i, sz;
  mixed *players;

  players = users();
  sz = sizeof(players);

  for(i = 0;  i < sz; i++)
  {   
    string name = players[i]->query_name();    
    mixed *year = players[i]->query_birthday();
    year = ClockObject->query_year()-year[0];
    
    container += ({({name, year})});    
  }

  container = sort_array(container, "sort_desc");
  return(view_age(container));
}

int age_individual(string player_name)
{
  // alias age cc return "/usr/kharas/etc/item/ages"->age_individual("$1");

  object playa;
  mixed year;
  
  playa = find_living(player_name);
  year = playa->query_birthday();
  year = year[0];
  return(ClockObject->query_year()-year);

}
/*
alias age cc -s int age = "/usr/kharas/etc/item/ages"->age_individual("$1");int played = find_living("$1")->query_age()/86400;write("years: "+age+" played: ~"+played+"d\n");
*/
