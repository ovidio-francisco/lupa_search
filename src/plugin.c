#include <mysql/plugin.h>
#include <mysql/udf_registration_types.h>



char lupa_similarity_init(UDF_INIT *initid, UDF_ARGS *args, char *message);
double lupa_similarity(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error);
char lupa_clear_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

char *lupa_clear(UDF_INIT *initid, UDF_ARGS *args, char *result,
		unsigned long *length, char *is_null, char *error);

char lupa_phoneticBr_init(UDF_INIT *initid, UDF_ARGS *args, char *message);
char *lupa_phoneticBr(UDF_INIT *initid, UDF_ARGS *args, char *result,
		unsigned long *length, char *is_null, char *error);


static int lupa_plugin_init(void *arg __attribute__((unused))) { 

	if (mysql_udf_register("lupa_limilarity", REAL_RESULT,
				(Udf_func_any) lupa_similarity,
				lupa_similarity_init, NULL)) return 1;

	if (mysql_udf_register("lupa_clear", STRING_RESULT,
				(Udf_func_any) lupa_clear,
				lupa_clear_init, NULL)) return 1;

	if (mysql_udf_register("lupa_phoneticBr", STRING_RESULT,
				(Udf_func_any) lupa_phoneticBr,
				lupa_phoneticBr_init, NULL)) return 1;

	return 0; 
}

static int lupa_plugin_deinit(void *arg __attribute__((unused))) { 

	mysql_udf_unregister("lupa_similarity", REAL_RESULT);
	mysql_udf_unregister("lupa_clear", STRING_RESULT);
	mysql_udf_unregister("lupa_phonetic", STRING_RESULT);


	return 0; 
}

static struct st_mysql_daemon lupa_descriptor = {
	MYSQL_DAEMON_INTERFACE_VERSION 
};

mysql_declare_plugin(lupa)
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
	0
}
mysql_declare_plugin_end;


