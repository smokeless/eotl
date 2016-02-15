inherit RoomPlusCode;

void extra_create()
{
  set("short","Western Forest");
  set("day_long","You are deep in the southwestern forests, the hills "+
   "are becoming very rough and further travel to the south is impossible. "+
   "The sunlight stabs a few weak rays through the canopy, and the forest "+
   "is silent, almost eerily so. You feel a cold shiver run over you and "+
   "you feel as though this area hides something.");
  set("night_long","You are deep in the southwestern forests, the hills "+
   "are becoming very rough and further travel to the south is impossible. "+
   "The moonlight stabs a few weak rays through the canopy, and the forest "+
   "is silent, almost eerily so. You feel a cold shiver run over you and "+
   "you feel as though this area hides something.");
  set("day_light", SHADY);
  set("night_light", DIM);
  set( OutsideP, 1);
  set( ForestP, 1);
  set("descs", (["vines":"The vines are very thick, but a light breeze "+
   "stirs them gently, and you notice a darkness more than shadow behind "+
   "them.  Perhaps a cave you could descend into...?",
  "cave":"The cave appears very dark and forboding, the hanging vines "+
   "obscure almost all light and prevent any sight of what might lie "+
   "within."]));
  add("exits", ([
   "west":"plains72",
   "east":"plains74",
   "north":"plains59",
   ]));
}

extra_init()
{
   add_action("down","descend");
   add_action("down","enter");
}

search()
{
   tell_room(environment(THISP),THISP->query_name()+" looks carefully "+
    "around the area, scrutinizing everything.\n",({THISP}));
   write("You carefully scrutinize the area, looking for interesting "+
    "features.\nPushing aside a wall of hanging vines you notice the "+
    "mouth of a cave\nyou could descend into.\n");
  return 1;
}

int down()
{
   tell_room(environment(THISP),THISP->query_name()+" pushes aside some "+
    "hanging vines, and vanishes behind them.\n",({THISP}));
   write("You push aside the hanging vines and descend carefully into "+
     "the mouth\nof the cave.\n");
    THISP->move_player("down", WARRENS + "tunnel1",1);
    return 1;
}
