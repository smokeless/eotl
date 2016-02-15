inherit ObjectCode;
int Ammo;
extra_create() {
    set("id", ({"pistol","gun","automatic"}));
    set("short", "a silenced automatic pistol");
    Ammo = 8;
    set("long","This is a small, compact, 8 shot silenced automatic.");
}
extra_init() {
    add_action("cock","cock");
    add_action("aim","aim");
    add_action("execute","execute");
    add_action("whip","whip");
    add_action("reload", "reload");
}
whip(string str) {
    object wank;
    int dam;
    if(!str) { write("Pistol-whip who?\n"); return 1; }
    if(!objectp(wank = FINDP(str))) { write("Pistol-whip who?\n"); return 1; }
    if(ENV(wank) != ENV(THISP)) { write("They're not here.\n"); return 1; }
    dam = wank->query_max_hp();
    dam += (wank->query_stat("con") - 1);
    dam -= (wank->query_max_hp() - wank->query_hp());
    write("You calmly pistol-whip "+wank->query_name()+".\n");
    tell_room(ENV(THISP), strformat(PNAME+" looks at "+wank->query_name()+
	", then calmly walks over and pistol-whips "+objective(wank)+"."),({THISP,wank}));
    tell_object(wank, strformat(PNAME+" looks at you, then walks out of your "
	"field of vision.  A sudden explosion of pain and light fills your vision."));
    wank->add_hp(-dam);
    return 1;
}
aim(string str) {
    object wank;
    if(!str) { 
	write("You wave your pistol around.\n");
	tell_room(ENV(THISP), strformat(PNAME+" waves "+possessive(THISP)+
	    " pistol around."),({THISP}));
	return 1;
    }
    if(!objectp(wank = FINDP(str))) {
	write("Nobody by that name.\n"); return 1;
    }
    if(ENV(wank) != ENV(THISP)) {
	write("They're not here.\n");
	return 1;
    }
    write("You raise your pistol and take casual aim at "+wank->query_name()+".\n");
    tell_room(ENV(THISP), strformat(PNAME+" raises "+possessive(THISP)+" pistol "
	"and takes casual aim at "+wank->query_name()+"."),({THISP}));
    return 1;
}
cock(string str) {
    if(!str) return 0;
    if(str != "gun" && str != "pistol") { write("Cock what?\n"); return 1; }
    if(Ammo < 1) {
	write("You need to reload the pistol.\n"); return 1; }
    write("You cock the pistol.\n");
    tell_room(ENV(THISP), strformat(PNAME+" cocks "+possessive(THISP)+
	" pistol."),({THISP}));
    return 1;
}
execute(string str) {
    object whack;
    object head;
    if(!IsWizard(THISP)) return 0;
    if(!str) return 0;
    if(!objectp(whack = FINDP(str))) { write("Who?\n"); return 1; }
    if(ENV(whack) != ENV(THISP)) { write("Not here.\n"); return 1; }
    if(whack->query_ghost()) { write("They're dead.\n"); return 1; }
    write("You execute "+whack->query_name()+".\n");
    tell_room(ENV(whack), strformat(PNAME+" places the muzzle of "+possessive(THISP)+
	" pistol against the back of "+whack->query_name()+"'s head, and "
	"fires!\n"+whack->query_name()+" slumps forward."),({THISP,whack}));
    tell_object(whack, "You feel something cold and hard against the back of "
      "your head, then blackness.\n");
    whack->DeathSequence(THISP, "by execution");
    call_out("shell",2,whack,ENV(whack));
    head = clone_object("/usr/reverend/checker/headbits");
    head->set("short", "the remains of "+capitalize(whack->query_real_name())+"'s head");
    head->set("long", "This was once "+capitalize(whack->query_real_name())+"'s head.  It looks surprisingly edible.");
    move_object(head, ENV(whack));
    if(!ENV(whack)->query("spattered")) {
	ENV(whack)->set("spattered", ENV(whack)->query("day_long"));
	ENV(whack)->set("day_long", ENV(whack)->query("day_long")+"There is a spatter of blood and brains on the wall.");
    }
    else { 
	switch(ENV(whack)->query("Spat")) {
	case 0:
	    ENV(whack)->set("day_long", ENV(whack)->query("spattered")+"There is big spatter of blood and brains on the wall.");
	    break;
	case 1:
	    ENV(whack)->set("day_long", ENV(whack)->query("spattered")+"There is a large spatter of blood and brains on the wall.");
	    break;
	case 2..3:
	    ENV(whack)->set("day_long", ENV(whack)->query("spattered")+"There is a very large spatter of blood and brains on the wall.");
	    break;
	case 4..6:
	    ENV(whack)->set("day_long",ENV(whack)->query("spattered")+"There is a huge dripping mess of blood and brains on the wall.");
	    break;
	default:
	    ENV(whack)->set("day_long",ENV(whack)->query("spattered")+"The walls are coated in clotting blood and brains.");
	    break;
	}
	ENV(whack)->set("Spat", ENV(whack)->query("Spat")+1);
    }
    tell_room(ENV(whack), strformat(capitalize(whack->query_real_name())+"'s body flops around for a moment as "+possessive(whack)+
	" nerves fire randomly."),({whack}));
    call_out("twitch", 4, capitalize(whack->query_real_name()), ENV(THISP));
    Ammo --;
    call_out("dest", 3, whack);
    return 1;
}
dest(object whack) {
    if(whack)
	MASTEROBJECT->forced_destruct(whack);
    if(whack)
	destruct(whack);
}

twitch(string name, object room) {
    tell_room(room, strformat(name+"'s body twitches a bit as nerves fire randomly."));
    if(!random(4)) call_out("twitch", 4, name, room);
}
reload(string str) {
    if(!str) return 0;
    if(str != "gun" && str != "pistol") { write("Reload what?\n"); return 1; }
    if(Ammo) { write("The gun is loaded.\n"); return 1; }
    Ammo = 8;
    write("You reload your pistol.\n");
    tell_room(ENV(THISP), strformat(PNAME+" slams a quickloader into "+possessive(THISP)+
	" pistol."),({THISP}));
    return 1;
}

shell(object whack, object room) {
    object shell;
    shell = clone_object("/usr/reverend/etc/shell");
    move_object(shell,room);
    tell_room(room,strformat("A shell casing falls to the ground with a metallic ringing."),({whack}));
}
