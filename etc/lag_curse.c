/* [Xurbax] */

string *victims = ({ "jester" });
int *vtime;

create()
{
int i;
vtime = allocate(sizeof(victims));
for (i = 0; i < sizeof(victims); i++)
	vtime[i] = 0;
call_out("lag", 1);
}

lag() {
object o;
int i, j;
for (j = 0; j < sizeof(victims); j++) {
o = find_player(victims[j]);
if (!o) {
	vtime[j] = 0;
}
else if (o && time() > vtime[j]) {
	i = random(5)*20 + 20;
	vtime[j] = time() + i + 1;
	freeze_interactive(o, i);
}
}
call_out("lag", 2);
}

