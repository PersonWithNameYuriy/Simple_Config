What is "simple_config.h"
========================

Its small and fast modul writed in c, what allows you to create, read and chang config for your programm.

How to use it?
----------------
"simple_config.h" have two functions: 

get_cnf (config_name, to, file_name) - read config named "config_name" from file "file_name", and write value of them into "to" variable. Program automatically open file.

write_cnf (config_name, new_value, file_name, flag) - now have two flags: 

-change and -new, with -change changing config value with name "config_name" to "new_value";
-new_$intager - write config "config_name" :: "new_value" on writed in flag instead $integer number line in file "file_name"

How to create config file?
--------------------------
Config must be as:
$config_name :: $config_value

programm ignoring all lines, why havent config or have wrong syntaxis

Other
-----
You can also open "exemples" directory run "simple_config_exemple.exe" or compile "simple_config_exemple.c" if you arent using windows. You can also see and change "config.cnf" file, which used by "simple_config_exemple.c". this programm have exemple of reading and writing configuration files. 
Or you can open main module "simple_config" and try to understand what i writed in.

Remark
------
Its first version of module, becouse of that can have bugs, and now haventmany functions. 
You can make bug report in "Issues" or send mail to my gmail "Yurii.github@gmail.com"