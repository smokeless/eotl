object me;

sh_init(object who)
{
    me = who;
    shadow(me,1);
}

string short()
{
    return "Chopped liver";

}

void remove_sir_shadow()
{
    remove_shadow(THISO);
    destruct(THISO);
}
string query_name()
{
    return "Chopped liver";
}
int id(string who)
{
    if(who == "liver" || who == "chopped" || who == "chopped liver") return 1;
}
