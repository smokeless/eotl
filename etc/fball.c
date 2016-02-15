inherit ThingCode;

void extra_create()
{
    add("id","leather football");
    add("id","football");
    add("id","ball");
    set("short","an official EotL Leather Football");
    set("long",
"This is The Official Football of the EotL Football Team.  It is made of \
genuine leather.  As you examine the football further, you can see there \
is a label on it.  It reads 'You can send an item from your inventory to \
anyone else on the mud.  Try 'pass [item] to [receiver]'");

    set("weight",0);
    set("droppable",1);
    set("gettable",1);
    set("value",500);
    set( NoStoreP, 1 );
}
void extra_init()
{
    add_action("passing","pass");
}
/*****************************************************************************/
int passing(string arg)
{
    object recob, itemob;
    string sender, item, receiver;

   if ((sscanf(arg, "%s to %s", item, receiver)) != 2)
     {
       notify_fail("Read the instructions!  It's not pass "+arg+".\n");
       return 0;
     } 
   else
   if (!present(item,THISP))
     {
       write("You don't have anything like that!\n");
       return 0;
     }
   else
   if(!find_player(receiver) || FINDP(receiver)->query_stealthy() )
     {
       write("That person isn't logged on!\n");
       return 1;
     }
   else
   if (present(item,THISP)->query_wielded())
     {
       write("That weapon is wielded.\n");
       return 0;
     }
   else
   if (present(item,THISP)->query("worn"))
     {
       write("You are wearing that!\n");
       return 0;
     }
   else
   if ( !(present(item,THISP)->query("droppable") ) )
     {
      write("That item can't be dropped.  Wah.\n");
      return 0;
       }
   else
   if (item == "football" || item == "leather football")
     {
       sender = THISP->query_name();
       itemob = present(item, THISP);
       recob = find_player(receiver);

       if (ENV(recob)->test_prop(NoTeleportP))
         { write("Gimp, that's a NoTeleport zone!\n");
           return 1;
         }
       else
       if (random(10)<1)
         {
          write("Your leather football runs out of air and turns to dust.\n");
          destruct(THISO);
          return 1;
         }
       write("You sent your magic football [tm] to "+
             recob->query_name()+".\n"); 
       tell_object(recob, sender+" just sent you a magic football [tm].\n");
       move_object(THISO, recob); 
       return 1;
     }
      else
     {
        string junk;
        int amt;
        object itemob2,coinsob;
       sender = THISP->query_name();
       itemob = present(item, THISP);
       recob = find_player(receiver);

       if (ENV(recob)->test_prop(NoTeleportP))
         { write("Gimp, that's a NoTeleport zone!\n");
           return 1;
         }
       else
       if (random(10)<1)
         {
          write("You leather football runs out of air and turns to dust.\n");
          destruct(THISO);
          return 1;
         }
       write("You sent "+item+" to "+
             recob->query_name()+".\n"); 
       tell_object(recob, sender+" just sent you "+item+".\n");
       if( sscanf(file_name(itemob),"/obj/money/money%s", junk) )
       {
            sscanf(item, "%d %s", amt, junk);
            if(amt)
            {
                coinsob=clone_object("/obj/money/money.c");
                coinsob->add("money", amt);
                itemob->add("money", -amt);
                move_object(coinsob, ENV(recob));
                move_object(THISO, recob); 
                command("get "+item,recob);
            }
       }
       else
       {     
           move_object(THISO, recob); 
           move_object(itemob, ENV(recob));
           command("get "+item,recob);
       }
       return 1;
     }
}
/*****************************************************************************/
