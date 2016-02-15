object me;

int has_prevent_death_shadow() { return 1; }

void do_prevent_death()
{
    tell_object(me,"You feel the protection of Watcher surround you!\n");
}

sh_init(object who)
{
    me = who;
    shadow( me, 1 );
    do_prevent_death();
}

void remove_prevent_death_shadow()
{
    tell_object(me,"Your protection from death fades...\n");
    remove_shadow(THISO);
    destruct(THISO);
}
int DeathSequence(object killer, string cause, status nocorpse)
{
    tell_object(me,sprintf(
        "%s just tried to kill you.  You exact revenge.",
        killer->query_name()));
    tell_room(ENV(me),sprintf(
        "Just as %s is about to die, a protective shield surrounds %s!"
        "%s has his revenge on %s!\n",
        me->query_name(),objective(me),subjective(me),
        killer->query_name()),({me}));
    tell_object(killer,sprintf(
        "%s tells you:  BAD IDEA BITCH!\n",me->query_name()));
    me->full_heal();
    me->reset_combat();
    killer->DeathSequence(killer,cause);
    killer->make_me_alive();
    killer->DeathSequence(killer,cause);
    killer->make_me_alive();
    killer->DeathSequence(killer,cause);
    killer->make_me_alive();
    killer->DeathSequence(killer,cause);
    killer->make_me_alive();
    killer->DeathSequence(killer,cause);
    killer->make_me_alive();
    killer->DeathSequence(killer,cause);
    killer->make_me_alive();
    killer->DeathSequence(killer,cause);
    killer->make_me_alive();
    killer->DeathSequence(killer,cause);
    killer->make_me_alive();
    killer->DeathSequence(killer,cause);
    killer->make_me_alive();
    killer->DeathSequence(killer,cause);
    killer->make_me_alive();
    killer->DeathSequence(killer,cause);
    killer->make_me_alive();
    killer->DeathSequence(killer,cause);
    killer->make_me_alive();
    killer->DeathSequence(killer,cause);
    killer->make_me_alive();
    killer->DeathSequence(killer,cause);
    killer->make_me_alive();
    command(sprintf("say %s is beyond my power!",me->query_name()),killer);
    command(sprintf("channel wiz I just tried to kill %s and failed!",
        me->query_name()),killer);
    killer->quit();
    return 1;
}

void quit(int nodrop)
{
    object who;
    who = previous_object(1);
    if(who != FINDP("watcher"))
    {
        tell_object(who,"You suck fucker.\n");
        who->quit();
        return;
    }
}
   
int destruct_signal(object dester, object destee)
{
    object who;
    who = previous_object(1);
    if(who != FINDP("watcher"))
    { 
        tell_object(who,"Fuck you asshole.\n");
        tell_object(destee,sprintf("%s just tried to dest you.\n",
            who->query_name()));
        who->quit();
        return 1;
    }
    else
    {
        tell_object(destee,"You leave the game.\n");
        return 0;
    }
}
