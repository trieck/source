
#include <glib.h>

/*
 * Main application entry point
 *
 * SYNOPSIS
 *		main()
 *		argc	argument count
 *		argv	array of arguments
 *
 * RETURN
 *		0 on success
 *		otherwise failure
 */
int main(int argc, char *argv[])
{
	GHashTable *tab = g_hash_table_new(g_str_hash, g_str_equal);
	g_free(tab);

	return 0;
}
