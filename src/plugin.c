#include <mysql/plugin.h>

#ifndef MARIADB_BASE_VERSION
#include <mysql/udf_registration_types.h>
#endif



char lupa_similarity_init(UDF_INIT *initid, UDF_ARGS *args, char *message);
double lupa_similarity(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error);
char lupa_clear_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

char *lupa_clear(UDF_INIT *initid, UDF_ARGS *args, char *result,
		unsigned long *length, char *is_null, char *error);

char lupa_phoneticBr_init(UDF_INIT *initid, UDF_ARGS *args, char *message);
char *lupa_phoneticBr(UDF_INIT *initid, UDF_ARGS *args, char *result,
		unsigned long *length, char *is_null, char *error);


static int lupa_plugin_init(void *arg __attribute__((unused))) { 

#ifdef MARIADB_BASE_VERSION 
	return 0;
#else

	if (mysql_udf_register("lupa_similarity", REAL_RESULT,
				(Udf_func_any) lupa_similarity,
				lupa_similarity_init, NULL)) return 1;

	if (mysql_udf_register("lupa_clear", STRING_RESULT,
				(Udf_func_any) lupa_clear,
				lupa_clear_init, NULL)) return 1;

	if (mysql_udf_register("lupa_phoneticBr", STRING_RESULT,
				(Udf_func_any) lupa_phoneticBr,
				lupa_phoneticBr_init, NULL)) return 1;

	return 0; 
#endif
}

static int lupa_plugin_deinit(void *arg __attribute__((unused))) { 

#ifdef MARIADB_BASE_VERSION 
	return 0;
#else

	mysql_udf_unregister("lupa_similarity", REAL_RESULT);
	mysql_udf_unregister("lupa_clear", STRING_RESULT);
	mysql_udf_unregister("lupa_phonetic", STRING_RESULT);


	return 0; 
#endif
}

static struct st_mysql_daemon lupa_descriptor = {
	MYSQL_DAEMON_INTERFACE_VERSION 
};

maria_declare_plugin(lupa)
{
    MYSQL_DAEMON_PLUGIN,
    &lupa_descriptor,
    "lupa",
    "Ovídio José Francisco",
    "Text preprocessing: similarity, clear, phoneticBr",
    PLUGIN_LICENSE_GPL,
    lupa_plugin_init,
    lupa_plugin_deinit,
    0x0100,
    NULL,
    NULL,
    NULL,
    MariaDB_PLUGIN_MATURITY_STABLE
}
maria_declare_plugin_end;


