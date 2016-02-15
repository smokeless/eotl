/*This is the wiztoy-pet
 *With luck it'll be running by the end of the month
 *
 *7/13/96 Muffins
 */
inherit MonsterCode;
inherit MonsterNoHunt;

#include <ansi.h>;
int i, sel;
object ob, who, target, pud;
string str, where, choice,tname;

void extra_create()
{
    set_name("glitch");
    set_race("/usr/muffins/proj/toy/wiztoy");
    add_alias("orb");
    set_short("Glitch the wiztoy");
    set_long("This is a small glowing orb, about the size of a baseball. It"+
      " seems to be made of solid ruby, and is perfetly smooth. It pulsates with a"+
      " red light and you get the feeling like it might be alive. You decide it may"+
      " be best to leave it alone.\n");
    set_natural_ac(50);
    set_type("psionic");
    set_alignment(-2000);
    set_gender("other");
    set_offensive_level(800);
    set_defensive_level(800);
    set_toughness(500);
    set_max_hp(5000);
    set_max_fatigue(5000);
    set_max_mana(5000);
    set_damage_bonus(3);


}


heart_beat()
{
    if(!present("muffins",ENV(THISO)))
    {
	if(find_player("muffins"))
	{
	    tell_room(ENV(THISO),"The orb suddenly winks out of existence.\n");
	    move_object(THISO,ENV(find_player("muffins")));
	    tell_room(ENV(THISO),"The orb winks into existence.\n");
	    return 1;

	}
	destruct(THISO);
	return 1;
    }
    return 0;
}



status extra_init()
{
    if(PRNAME!="muffins")
    {
	return 1;
    }
    add_action("go_rogues","rogue");
    add_action("range_talk","rtalk");
    add_action("possess_targ","possess");
    add_action("room_tell","rtell");
    add_action("to_me","summon");
    add_action("hid_who","hidwho");
    add_action("send_to","send");
    add_action("orb_comm","comm");
    add_action("mangle_target","mangle");
    add_action("puddle_target","puddle");
    add_action("generate_stuff","generate");

}

status go_rogues()
{
    tell_room(ENV(THISP),CPRNAME+" fades back into the shadows and disappears.\n",
      ({THISP}));
    move_object(THISP,"/zone/null/guild/rogue/rogue1");
    tell_room(ENV(THISP),CPRNAME+" steps out of the shadows.\n",({THISP}));
    command("glance",THISP);
    return 1;
}

status to_me(string str)
{
    who=find_living(str);
    if(!who)
    {
	write("Glitch can't find "+CAP(str)+".\n");
	tell_room(ENV(THISO),"Glitch says: Error, file not found.\n");
	return 1;
    }
    tell_room(ENV(who),CAP(who->query_real_name())+" is bathed in a"
      " red glow for an instant, then fades from view.\n",({who}));
    move_object(who,ENV(THISO));
    tell_room(ENV(THISO),"Glitch pulsates a florecent red.\n"+
      "In a sudden burst of red light "+CAP(str)+" arrives.\n",
      ({who}));
    tell_object(who,"Glitch appears before you. You are bathed in a red"+
      " glow as your\n surroundings distort into a new shape.\n");
    command("glance",who);
    return 1;
}

orb_comm(string str)
{
    if(!str)
    {
	tell_room(ENV(THISO),"Glitch says, 'Insufficient data, please clarify.'\n");
	return 1;
    }
    command(str,THISO);
    return 1;
}


send_to(string str)
{
    object who, obj;
    string name, thing, message, sender;
    if(sscanf(str,"%s %s",name,thing)!=2)
    {
	tell_room(ENV(THISO),"Glitch says, 'Insufficient data, clarify.'\n");
	return 1;
    }
    who=find_player(name);
    if(!who) who=find_living(name);
    if(!who) who=find_object(name);
    if(!who)
    {
	tell_room(ENV(THISO),"Glitch says, '"+CAP(name)+" is not in this dimension.\n");
	return 1;
    }
    obj=clone_object(thing);
    if(!obj)
    {
	tell_room(ENV(THISO),"Glitch says, 'Cannot access molecular base.'\n");
	return 1;
    }
    move_object(obj,who);
    if(obj->short())
	tell_object(who,"Glitch appears briefly and leaves "+obj->short()+" for you.\n");
    if(obj->short())
	tell_room(ENV(THISO),"Glitch shimmers briefly as he drops something to "+
	  CAP(name)+".\n");
    else
	tell_object(THISP,"Glitch whispers to you, '"+obj->short()+" sent to "+CAP(name)+".\n");
    return 1;
}
status mangle_target(string str)
{
    string rlong;
    object target, pulp;
    if(!find_living(str))
    {
	return 0;
    }
    target=find_living(str);
    tname=target->query_real_name();
    if(!present(target))
    {
	return 0;
    }
    pulp=clone_object("/usr/muffins/stuff/pulp");
    pulp->set("short","the bloody remains of "+CAP(tname));
    move_object(pulp,ENV(target));
    rlong=ENV(target)->query("day_long");
    ENV(target)->set("day_color",RED);
    ENV(target)->set("day_long",rlong+"\n"+
      "Bits of mashed "+CAP(tname)+" are all over the place.\n");
    tell_object(target,"Glitch glows a deep blue and you feel"+
      " yourself being torn apart.\n");
    tell_object(THISP,CAP(tname)+" is twisted apart by Glitch.\n");
    tell_room(ENV(target),"Glitch glows a deep blue as "+CAP(tname)+
      " is twisted apart by Glitch's TK.\n"+
      "Blood spatters everywhere.\n",({THISP,target}));
    target->make_me_ghost();
    return 1;
}
puddle_target(string str)
{
    string pudname;
    object pudbait, pud;
    if(!find_living(str))
    {
	tell_room(ENV(THISO),"Glitch says, 'No such target present.'\n");
	return 1;
    }
    pudbait=find_living(str);
    pudname=pudbait->query_name();
    if(!present(pudbait))

    {
	tell_room(ENV(THISO),"Glitch says, 'Target "+CAP(pudname)+
	  " not aquired.\n");
	return 1;
    }
    tell_room(ENV(pudbait),"Glitch glows bright crimson.\n"
      "The light falls upon "+CAP(pudname)+" who melts into a"+
      " large red puddle on the floor.\n");
    pudbait->DeathSequence("by: melting");
    pud=clone_object("/usr/muffins/stuff/puddle");
    move_object(pud,ENV(THISO));
    return 1;
}

status possess_targ(string str)
{
    string targname, com;
    object targ;
    if(!str)
    {
	tell_room(ENV(THISO),"Glitch says, 'Insufficient data.'\n");
	return 1;
    }
    sscanf(str,"%s %s",targname,com);
    if(!FINDP(targname))
    {
	tell_room(ENV(THISO),"Glitch says, 'Target not aquired.'\n");
	return 1;
    }
    if(!com)
    {
	tell_room(ENV(THISO),"Glitch says, 'Insufficient data.'\n");
	return 1;
    }
    targ=FINDP(targname);

    write(CAP(targname)+" possesed.\n");
    tell_room(ENV(THISO),"Glitch glows slightly green.\n");
    command(com,targ);
    return 1;
}

status room_tell(string str)
{
    string whoname, what;
    if(!str)
    {
	tell_room(ENV(THISO),"Glitch says 'Invalid parameters.'\n");
	return 1;
    }
    sscanf(str,"%s %s",whoname,what);
    if(!FINDP(whoname))
    {
	tell_room(ENV(THISO),"Glitch says 'No target defined.'\n");
	return 1;
    }
    if(!what)
    {
	tell_room(ENV(THISO),"Glitch says 'Insufficient data.'\n");
	return 1;
    }
    who=FINDP(whoname);
    tell_room(ENV(who),CPRNAME+" says: "+what+"\n");
    write("Message, "+what+"\n"+
      "Conveyed to "+CAP(whoname)+"'s location.\n");
    return 1;
}
status generate_stuff(string obj,int numb,string str,string tname)
{
    object target, cobj;
    sscanf(str,"%d %s",numb,obj);
    if(!obj)
    {
	tell_room(ENV(THISO),"Glitch says, 'No matrix defined.'\n");
	return 1;
    }
    if(!numb)
    {
	cobj=clone_object(obj);
	move_object(cobj,ENV(THISO));
	tell_room(ENV(THISO),"Glitch says, 'One matrix generated.'\n");
    }
    if(!tname)
    {
	{
	    for(i=0;i<=numb;i++)
	    {
		cobj=clone_object(obj);
		move_object(cobj,ENV(THISO));
	    }
	    return 1;
	}
	tell_room(ENV(THISO),"Glitch says, 'Generated "+numb+" matrixes.'\n");
	return 1;
    }
}
status range_talk(string tname)
{
    object drone, target;
    if(!tname)
    {
	tell_room(ENV(THISO),"Glitch says, 'No destination selected.'\n");
	return 1;
    }
    target=find_living(tname);
    if(target)
    {
	tell_room(ENV(THISO),"Glitch says, 'Drone destination not valid.'\n");
	return 1;
    }
    drone=clone_object("/usr/muffins/things/talk.c");
    move_object(drone,ENV(target));
    tell_room(ENV(THISP),"Glitch says,'Drone dispatched.'\n");
    tell_room(ENV(target),"A Glitch Drone appears.\n");
    return 1;
}
