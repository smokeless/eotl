/* Basic Shadow */
object wearer;

status
sh_init( object who ) {
	wearer = who;
        catch( shadow(wearer, 1) );
        return objectp( query_shadowing(THISO) );
}
