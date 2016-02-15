void extra_init()
{
   add_action("offer_stuff", "place");
   add_action("offer_stuff", "put");
   add_action("call_charon", "blow");
}

void display_msg(object who, int msg)
{
   object ob;
   if(ENV(who) != THISO) {
      LAB_BOAT -> set_status(0);
      return;
   }
   switch(msg) {
     case 1:
         tell_room(THISO, strformat("A thick fog rolls in."));
         call_out("display_msg", 7, who, 2); break;
      case 2:
         tell_room(THISO, strformat("The ocean starts to go "
            "calm as the fog rolls up onto the beach."));
         call_out("display_msg", 5, who, 3); break;
      case 3:
         tell_room(THISO, strformat("You think you see something "
            "approaching the shoreline in the distance."));
         call_out("display_msg", 10, who, 4); break;
      case 4:
         tell_room(THISO, strformat("A decaying boat drifts "
            "on to the beach."));
         ob = clone_object(LAB_OBJ "boat");
         move_object(ob, THISO);
         ob->set_up_move();
        break;
   }
}

int call_charon(string str)
{
   if(str!="horn") return 0;
   if(LAB_BOAT->query_status() || !LAB_BOAT->query_captain() ||
      present_path(OBJECTS "boat")) {
      ansi_tell(YEL, "A magical force holds the horn in "
         "place.", THISP);
      return 1;
   }
  LAB_BOAT->set_status(1);
   LAB_BOAT->set_dock(file_name(THISO));
  ansi_tell(YEL, "You pick up the horn off the stand and "
      "place it to your lips.  Exhaling as hard as you can, "
      "the horn erupts with a deep bellow.", THISP);
   call_out("display_msg", 15, THISP, 1);
   return 1;
}

int offer_stuff(string str)
{
   string what, junk;
   int amount;
   if( ! stringp( str ) ) return( 0 );
   if(sscanf(str, "%d coins %s %s", amount, junk, what) != 3) return 0;
   if(what!= "dish" && what != "plate" && what != "golden dish") return 0;
   if(amount<1) return 0;
   if(amount > THISP->query_money()) {
      ansi_tell(YEL, "You don't have that many coins.", THISP);
      return 1;
   }
   THISP->add_money(-amount);
   ansi_tell(GRN, "You place the coins on the dish and they vanish in "
      "a burst of flames.", THISP);
   if(amount < 1000 + random(500) + random(500)) return 1;
   call_out("get_death", 5, THISP);
   return 1;
}

void get_death(object who)
{
    seteuid( getuid( ) );
   SERVER->load_it_up();
   if(move_object(clone_object(CLIENT), who))
   ansi_tell(YEL, "A cold shiver runs up your spine as you are "
      "connected to the underworld.", who);
}
