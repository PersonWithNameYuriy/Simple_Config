#include <stdio.h>
#include "simple_config.h"

#define MAXLEN 64
#define READFLAG "-read"
#define CHANGEFLAG "-change"
#define NEWFLAG "-new"

// exemple of usage "simple_config.h" library
int main(int argc, char *argv[]) 
{
	char result[MAXLEN];
	int res;
	
	if(argc<3)
	{
		printf("Type:\nsimple_config_exemple %s $config_name\n\tor\nsimple_config_exemple %s $config_name $new_value\n\tor\nsimple_config_exemple %s_$str_num $config_name $new_value", READFLAG, CHANGEFLAG, NEWFLAG);
		return 1;
	}
	
	//reading config
	if(strcmp(argv[1], READFLAG)==0)
	{
		res = get_cnf(argv[2], result, "config.cnf"); // read config named as second argument in result, res = -1 if failed to read, or config line number
		if(res>-1)
			printf("config value: %s\nconfig line number is %d", result, res);
		else
			printf("%s", result);
	}
	// changing config 
	else if(strcmp(argv[1], CHANGEFLAG)==0)
	{
		res = write_cnf(argv[2], argv[3], "config.cnf", "-change"); // change config named as second argument to third argument, res = -1 if failed to read, or config line number
		if(res>-1)
			printf("config changed succesful!\nconfig line number is %d", res);
		else
			printf("config not found");
	}
	// adding config
	else if(strncmp(argv[1], NEWFLAG, strlen(NEWFLAG))==0)
	{
		res = write_cnf(argv[2], argv[3], "config.cnf", argv[1]); // change config named as second argument to third argument, res = -1 if failed to read, or config line number
		if(res>-1)
			printf("config changed succesful!\nconfig line number is %d", res);
		else
			printf("config not found");
	}
	
	else
	{
		printf("incorrect argument, please type:\nsimple_config_exemple %s $config_name\n\tor\nsimple_config_exemple %s $config_name $new_value\n\tor\nsimple_config_exemple %s_$str_num $config_name $new_value", READFLAG, CHANGEFLAG, NEWFLAG);
		return 1;
	}
	
	// remark 1: functions can work with config names writed with space
	// remark 2: all text, why isnt config programm will ignore
	// remark 3: flag for create new config: "-new $anysymbol $linenumber" without spaces 
	
	return 0;
}