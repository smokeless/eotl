//  Updated by Ladylunar@Eotl  Oct '96
 
inherit ContainerCode;
inherit ObjectCode;
inherit ArmorCode;
 
object *suck_stuff(object room);
 
void extra_create()
{
    set("id", ({"vacuum cleaner","vacuum"}));
    set("short","a vacuum cleaner");
    set("long",
      "This is just an ordinary, run of the mill, vacuum cleaner.  It " +
      "looks like it could vacuum the chrome off a trailer hitch, must " +
      "be one of those extra strength, new fangled jobs.  Maybe if you " +
      "<clean the room>, you'll see if it's got any power.");
    set("weight", 50);
    set("max_weight", 500);
    set_ac(0);
    set("value", 0);
    set( AutoLoadP, 1 );
    set("droppable", 0);
}
 
init()
{
    add_action("do_clean","clean");;
}
 
int do_clean(string str)
{
    if(!str) return 0;
    if(str == "room" || str == "the room")
    {
        write("You hear a 'whoosh' as the vacuum sucks everything up!\n");
        say(PNAME + "'s vacuum cleans up the room!\n");
        write(sizeof(suck_stuff(ENV(THISP)))+" objects vacuumed.\n");
    }
    return 1;
}
 
object *suck_stuff(object room)
{
    object *inv, *gotten;
    int i;
 
    gotten=({});
    inv=inventorya(room);
    for(i=0;i<sizeof(inv);i++)
    {
        if(inv[i]->query("gettable"))
        {
            move_object(inv[i],THISO);
            gotten=gotten + ({inv[i]});
        }
    }
    return gotten;
}
