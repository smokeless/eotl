// stone_altar.c - entry object for Ragnarok
// By Toadwart and Durak
// Modded by Nardo 1/15/95 for new ObjectCode
 
inherit ObjectCode;
 
 
#define ALTAR_KEYWORDS ({"kill","KILL","death","DEATH","destruction","DESTRUCTION","Death","Destruction","Kill"})
 
int flag;
string pnme;
 
extra_create() 
   {
   flag=0;
   pnme="NOONE";
   set("id",({"altar","stone altar"}));
   set("short","A large altar built of stone");
   set("long",
    "This altar was built entirely of native stone.  The construction appears "+
    "ancient beyond belief, it would be a safe bet to assume that this has been "+
    "here since before all of Eternal City.  The altar is covered in moss, though "+
    "looking closely, you can see many bas-reliefs and cryptic runes, carved with "+
    "exquisite care into and around the rim of the altar.  Along with depictions "+
    "of wars, and blood-shed without equal.  Just looking at it makes shivers run "+
    "up and down your spine. There appears to be two small depressions in the altars "+
    "surface about the size of a human hand.  Perhaps if you placed your hands "+
    "there, and said something appropriate to warfare, something might "+
    "happen.  "+
    "");
   set("gettable",0);
   set("droppable",0);
   set("value",100000);
   set("weight",1000000);
   }
extra_init() 
   {
   add_action("say", "say");
   add_action("say");
   add_xverb("'");
   add_action("movement","d");
   add_action("movement","down");
   add_action("movement","n");
   add_action("movement","north");
   add_action("movement","s");
   add_action("movement","south");
   add_action("place", "place");
   add_action("place","put");
   add_action("place","lay");
   add_action("remove","remove");
   add_action("read","read");
   }
int movement() 
   {
   if((string)PNAME==pnme&&flag==1) 
      return(write("You must first remove your hands from the altar.\n"),1);
   return(0);
   }
read(string arg) 
   {
   if((arg=="runes")||(arg=="writing")||(arg=="altar")) 
      {
      write("You decipher the runes to be:\n");
      write("          KILL\n");
      write(" Death and Destruction\n");
      say(PNAME+" reads the runes.\n");
      return(1);
      }
   return(0);
   }
transport(string arg)
   {
   write(
    "With your "+THISP->query_hand_name()+"s on the altar you invoke the the power word "+arg+".\n"+
    "You see an enormous flash.  Suddenly you vaporize!\n"+
    "You find yourself somewhere else!\n\n");
   say(PNAME+" dissolves in a flash of brilliant radiance, as they are \n"+
      "struck by a dazzling bolt of blue-white lightning from nowhere.\n");
   if(load_name(ENV(THISO))==TEMPLE+"entry")
      move_object(THISP,ENTRY+"room057");
   else
      move_object(THISP,TEMPLE+"entry");
   command("glance",THISP);
   say(PNAME+" materializes in a cloud of white smoke, smelling of brimstone and ashes.\n");
   flag=0;
   pnme="NOONE";
   return(1);
   }
place(string arg)
   {
   string hname;
   
   hname=THISP->query_hand_name();
   if((arg==hname+"s on altar")||(arg==hname+" on altar")||(arg==hname)||(arg==hname+"s")) 
      {
      flag=1;
      if(pnme==PNAME) 
         return(write("You already have your "+hname+"s on the altar.\n"),1);
      else 
         if(pnme!="NOONE") 
            return(write("You push "+pnme+" away from the altar.\n"),1);
      pnme=PNAME;
      write("You place your "+hname+"s on the altar.\n");
      say(PNAME+" places "+possessive(THISP)+" "+hname+"s on the altar.\n");
      return(1);
      }
   else 
      return(write("You may only place your "+hname+"s on the altar.\n"),1);
   }
remove(string arg)
   {
   if((arg==THISP->query_hand_name()+"s"||arg==THISP->query_hand_name()+"s from altar")&&(pnme==PNAME)) 
      {
      write("You remove your "+THISP->query_hand_name()+"s from the altar.\n");
      say(PNAME+" removes "+possessive(THISP)+" "+THISP->query_hand_name()+"s from the altar.\n");
      flag=0;
      pnme="NOONE";
      return(1);
      }
   return(0);
   }
say(string arg)
   {
   if((searcha(ALTAR_KEYWORDS,arg)!=-1)&&(flag==1)&&(pnme=PNAME))
      {
      transport(arg);
      return(1);
      }
   return(0);
   }
// stone_altar.c - entry object for Ragnarok
// By Toadwart and Durak
// Modded by Nardo 1/15/95 for new ObjectCode
 
inherit ObjectCode;
 
#include "dir.h"
#define ALTAR_KEYWORDS ({"kill","KILL","death","DEATH","destruction","DESTRUCTION","Death","Destruction","Kill"})
 
int flag;
string pnme;
 
extra_create() 
   {
   flag=0;
   pnme="NOONE";
   set("id",({"altar","stone altar"}));
   set("short","A large altar built of stone");
   set("long",
    "This altar was built entirely of native stone.  The construction appears "+
    "ancient beyond belief, it would be a safe bet to assume that this has been "+
    "here since before all of Eternal City.  The altar is covered in moss, though "+
    "looking closely, you can see many bas-reliefs and cryptic runes, carved with "+
    "exquisite care into and around the rim of the altar.  Along with depictions "+
    "of wars, and blood-shed without equal.  Just looking at it makes shivers run "+
    "up and down your spine. There appears to be two small depressions in the altars "+
    "surface about the size of a human hand.  Perhaps if you placed your hands "+
    "there, and said something appropriate to warfare, something might "+
    "happen.  "+
    "");
   set("gettable",0);
   set("droppable",0);
   set("value",100000);
   set("weight",1000000);
   }
extra_init() 
   {
   add_action("say", "say");
   add_action("say");
   add_xverb("'");
   add_action("movement","d");
   add_action("movement","down");
   add_action("movement","n");
   add_action("movement","north");
   add_action("movement","s");
   add_action("movement","south");
   add_action("place", "place");
   add_action("place","put");
   add_action("place","lay");
   add_action("remove","remove");
   add_action("read","read");
   }
int movement() 
   {
   if((string)PNAME==pnme&&flag==1) 
      return(write("You must first remove your hands from the altar.\n"),1);
   return(0);
   }
read(string arg) 
   {
   if((arg=="runes")||(arg=="writing")||(arg=="altar")) 
      {
      write("You decipher the runes to be:\n");
      write("          KILL\n");
      write(" Death and Destruction\n");
      say(PNAME+" reads the runes.\n");
      return(1);
      }
   return(0);
   }
transport(string arg)
   {
   write(
    "With your "+THISP->query_hand_name()+"s on the altar you invoke the the power word "+arg+".\n"+
    "You see an enormous flash.  Suddenly you vaporize!\n"+
    "You find yourself somewhere else!\n\n");
   say(PNAME+" dissolves in a flash of brilliant radiance, as they are \n"+
      "struck by a dazzling bolt of blue-white lightning from nowhere.\n");
   if(load_name(ENV(THISO))==TEMPLE+"entry")
      move_object(THISP,ENTRY+"room057");
   else
      move_object(THISP,TEMPLE+"entry");
   command("glance",THISP);
   say(PNAME+" materializes in a cloud of white smoke, smelling of brimstone and ashes.\n");
   flag=0;
   pnme="NOONE";
   return(1);
   }
place(string arg)
   {
   string hname;
   
   hname=THISP->query_hand_name();
   if((arg==hname+"s on altar")||(arg==hname+" on altar")||(arg==hname)||(arg==hname+"s")) 
      {
      flag=1;
      if(pnme==PNAME) 
         return(write("You already have your "+hname+"s on the altar.\n"),1);
      else 
         if(pnme!="NOONE") 
            return(write("You push "+pnme+" away from the altar.\n"),1);
      pnme=PNAME;
      write("You place your "+hname+"s on the altar.\n");
      say(PNAME+" places "+possessive(THISP)+" "+hname+"s on the altar.\n");
      return(1);
      }
   else 
      return(write("You may only place your "+hname+"s on the altar.\n"),1);
   }
remove(string arg)
   {
   if((arg==THISP->query_hand_name()+"s"||arg==THISP->query_hand_name()+"s from altar")&&(pnme==PNAME)) 
      {
      write("You remove your "+THISP->query_hand_name()+"s from the altar.\n");
      say(PNAME+" removes "+possessive(THISP)+" "+THISP->query_hand_name()+"s from the altar.\n");
      flag=0;
      pnme="NOONE";
      return(1);
      }
   return(0);
   }
say(string arg)
   {
   if((searcha(ALTAR_KEYWORDS,arg)!=-1)&&(flag==1)&&(pnme=PNAME))
      {
      transport(arg);
      return(1);
      }
   return(0);
   }
