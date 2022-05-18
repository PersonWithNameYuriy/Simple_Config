#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//----------------------------------------------------------------------------

#define MAXCONFIGLINELEN 151 // max lenght of line
#define TEXTMAXLEN 1001

#define CNFNAMEEND " :: " // delimiter between config name and value

#define TEXTWRITECHANGEFLAG "-change" // with this flag changing value of config
#define TEXTWRITEADDFLAG "-new" // with this flag add new config on line writed next of next symbols

//----------------------------------------------------------------------------

int get_cnf(char * config_name, char * to, char * file_name)
{
	// return line with config number, if line havent found, return -1
	
	FILE * file;
	char line[MAXCONFIGLINELEN];
	int cnei, i, j, k, l, line_num, same, stop;
	
	file = fopen(file_name, "r");
	
	line_num = 0;
	
	while(fgets(line, MAXCONFIGLINELEN, file)!=NULL)
	{
		++line_num; // every read line line_num + 1 to know what line has needed config
		
		// searching CNFNAMEEND in line
		for(i=0, stop=1; (line[i]!='\n') && (line[i]!='\0') && (stop==1); ++i)
		{	for(j=0, k=i, same=0; (CNFNAMEEND[j]!='\n') && (CNFNAMEEND[j]!='\0') && (stop==1); ++j, ++k)
			{
				if(line[k]==CNFNAMEEND[j])
					++same;
				else
					break;
				
				if((strlen(CNFNAMEEND))==same)
					cnei=i, stop=-1;
			}
		}
		
		//if line have needed config name
		if((strncmp(config_name, line, cnei)==0) && (strlen(config_name)==cnei))
		{
			// copy symbols from config value starting with end of CNFNAMEEND to "to" line
			for(i=0, j=cnei+strlen(CNFNAMEEND); (line[j]!='\n') && (line[j]!='\0'); ++i, ++j)
				to[i]=line[j];
			to[i]='\0'; // '\0' in end of line for corect work of functions
			
			fclose(file); // close file
			return line_num+1; // return line with config number
		}
	}
	// if needed config not found
	fclose(file);
	
	strcpy(to, "Config not found");
	return -1;
}

//----------------------------------------------------------------------------

int write_cnf(char * config_name, char * new_value, char * file_name, char * flag)
{
	// return line with config number, if line havent found, return -1
	
	FILE * file, * f2;
	char line[MAXCONFIGLINELEN], text[TEXTMAXLEN][MAXCONFIGLINELEN], intinflag[MAXCONFIGLINELEN];
	int cnei, i, j, k, l, z, same, stop, linewithcnf;
	
	file = fopen(file_name, "r+");
	
	l=0, linewithcnf = -1;
	
	// if need to change
	if(strncmp(flag, TEXTWRITECHANGEFLAG, strlen(TEXTWRITECHANGEFLAG))==0)
	// finding needed config and copy file in "text", if found, 
	{
		while(fgets(line, MAXCONFIGLINELEN, file)!=NULL)
		{
			strcpy(text[l++], line); // copying text in "text" for lines
			
			// searching CNFNAMEEND index in line
			for(i=0, stop=1; (line[i]!='\n') && (line[i]!='\0') && (stop==1) && (linewithcnf==-1); ++i)
			{	for(j=0, k=i, same=0; (CNFNAMEEND[j]!='\n') && (CNFNAMEEND[j]!='\0') && (stop==1); ++j, ++k)
				{
					if(line[k]==CNFNAMEEND[j])
						++same;
					else
						break;
					
					if((strlen(CNFNAMEEND))==same)
						cnei=i, stop=-1;
				}
			}
		
			// if line have needed config name, remember what line need to change
			if((strncmp(config_name, line, cnei)==0) && (strlen(config_name)==cnei) && (linewithcnf==-1))
				linewithcnf = l;
		} 
		strcpy(text[l+1], "end");
	}
	// if need to add or replace
	else if(strncmp(flag, TEXTWRITEADDFLAG, strlen(TEXTWRITEADDFLAG))==0)
	{
		// copy text into "text"
		while(fgets(line, MAXCONFIGLINELEN, file)!=NULL)
		{
			strcpy(text[l++], line); // copying text in "text" for lines
		} 
		strcpy(text[l+1], "end");
		
		// geting line for new config
		// get integer from "flag"
		for(i=strlen(TEXTWRITEADDFLAG)+1, j=0; flag[i]!='\0'; ++i) // +1 to lenght of flag to ignore space
			intinflag[j]=flag[i];
		intinflag[j+1]='\0';	
		linewithcnf = atoi(intinflag);
	}
	
	
	if(linewithcnf>-1) // if line with config was found
	{
		// reopening file fore changing
		fclose(file);
		file = fopen(file_name, "w");
		// rewrite file with changed config
		for(i=0; strcmp(text[i], "end"); ++i)
		{
			if(i==linewithcnf-1) // -1 because of in massive first element is 0, but linewithcnf have correct line of config
			{
				fprintf(file, "%s%s%s\n", config_name, CNFNAMEEND, new_value);
				z=1;
			}
			else
				fprintf(file, text[i]);
		}
		// adding argument in the end of text, if not added before
		if(z!=1)
			fprintf(file, "\n%s%s%s\n", config_name, CNFNAMEEND, new_value);
	}
	
	fclose(file);
	return linewithcnf;
}