What is "simple_config.h"
========================

Its small and fast modul writed in c, what allows you to create, read and chang config for your programm.

How to use it?
----------------
"simple_config.h" have two functions: 

get_cnf (config_name, to, file_name) - read config named "config_name" from file "file_name", and write value of them into "to" variable. Program automatically open file.

write_cnf (config_name, new_value, file_name, flag) - now have two flags: 

write_cnf flags: "-change" and "-new"
with -change changing config value with name "config_name" to "new_value";
-new_%intager% - write config "config_name" :: "new_value" on writed in flag instead %integer% number line in file "file_name"

get_cnf flags: "-one" and "-all"
"-one" to get only first value
"-all" to get all values with same config names. between values program placing separators, on default " ;; "

How to create config file?
--------------------------
Config must be as:
%config_name% :: %config_value%

programm ignoring all lines, why havent config or have wrong syntaxis

Remark
------
Its first version of module, becouse of that can have bugs, and now haventmany functions. 
You can make bug report in "Issues" or send mail to my gmail "Yurii.github@gmail.com"