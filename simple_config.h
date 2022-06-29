#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//----------------------------------------------------------------------------

struct t_t
{
	int i;
};

struct t_t t={10};

#define MAXCONFIGLINELEN 151 // max lenght of line
#define TEXTMAXLEN 1001

// constants below you can change, to use config as you like
#define CNFNAMEEND " :: " // delimiter between config name and value
#define CNFVALUESEPARATOR " ;; " // separator between results where you want get all values with one name

#define NOTFOUNDMASSAGE "config wasnt found"

#define GETCNFFLAGONE "-one" // get one highest configvalue
#define GETCNFFLAGALL "-all" //get all config values withsame names

#define TEXTWRITECHANGEFLAG "-change" // with this flag changing value of config
#define TEXTWRITEADDFLAG "-new" // with this flag add new config on line writed next of next symbols

//----------------------------------------------------------------------------

int get_cnf(char * config_name, char * to, char * file_name, char * flag)
{
	// return line with config number, if line havent found, return -1
	
	FILE * file;
	char line[MAXCONFIGLINELEN], *ind;
	int i, cnei, found;
	
	ind = to; // remember index of first element of "to"
	found = 0;
	
	strcpy(to, NOTFOUNDMASSAGE); // if no one config find, you will get thiss massage in "to"
	
	file = fopen(file_name, "r");
	
	while(fgets(line, MAXCONFIGLINELEN, file)!=NULL)
	{
		// remove \n at the end of line
		if(line[strlen(line)-1] == '\n')
			line[strlen(line)-1] = 0;
		
		// searching CNFNAMEEND in line
		for(cnei=0, i = 0; line[i]!='\0'; ++i)
		{
			if(strncmp((line+i), CNFNAMEEND, strlen(CNFNAMEEND))==0)
			{
				cnei = i;
				break;
			}
		}
		
		//if line have needed config name
		if((strncmp(config_name, line, cnei)==0) && (strlen(config_name)==cnei))
		{
			++found; // mark that needed coinfig founded
			
			// if needed only one result write them into "to" and stop programm
			if(strcmp(flag, GETCNFFLAGONE)==0)
			{
				// copy symbols from config value starting with end of CNFNAMEEND to "to" line
				strcpy(to, (line+cnei+strlen(CNFNAMEEND)));
				line[strlen(line)]='\0';
				//stop program
				fclose(file);
				return found; // return found words
			}
			
			// if needed all values with same config name add that value to "to" and c ontinue
			else if(strcmp(flag, GETCNFFLAGALL)==0)
			{
				// add separator between results
				if(to != ind)
				{
					strcpy(to, CNFVALUESEPARATOR);
					to += strlen(CNFVALUESEPARATOR);
				}
				// copy value
				strcpy(to, (line+cnei+strlen(CNFNAMEEND)));
				to += strlen((line+cnei+strlen(CNFNAMEEND)));
			}
		}
	}
	// end of working
	fclose(file);
	return found;
}

//----------------------------------------------------------------------------

int write_cnf(char * config_name, char * new_value, char * file_name, char * flag)
{
	// return line with config number, if line havent found, return -1
	
	FILE * file, * f2;
	char line[MAXCONFIGLINELEN], text[TEXTMAXLEN][MAXCONFIGLINELEN], *intinflag;
	int cnei, i, l, scw, same, linewithcnf;
	
	l=0, linewithcnf = -1;
	
	file = fopen(file_name, "r+");
	
	// if need to add or fully replace
	if(strncmp(flag, TEXTWRITEADDFLAG, strlen(TEXTWRITEADDFLAG))==0)
	{
		// copy text into "text"
		while(fgets(line, MAXCONFIGLINELEN, file)!=NULL)
			strcpy(text[l++], line); // copying text in "text" for lines
		
		// remove \n at the end of last string
		if(text[l][strlen(text[l])-1]=='\n')
			text[l][strlen(text[l])-1]=0;
		// mark to know where is end of file
		strcpy(text[l+1], "end");
		
		// get integer from "flag"
		intinflag = (flag + strlen(TEXTWRITEADDFLAG) + 1);
		linewithcnf = atoi(intinflag);
	}
	// if need to change
	
	if(strncmp(flag, TEXTWRITECHANGEFLAG, strlen(TEXTWRITECHANGEFLAG))==0)
	// finding needed config and copy all file in "text"
	{
		while(fgets(line, MAXCONFIGLINELEN, file)!=NULL)
		{
			strcpy(text[l++], line); // copying text in "text" for lines, remember line now
			
			// searching CNFNAMEEND in line
			for(cnei=0, i = 0; (line[i]!='\n') && (line[i]!='\0'); ++i)
			{
				if(strncmp((line+i), CNFNAMEEND, strlen(CNFNAMEEND))==0)
				{
					cnei = i;
					break;
				}
			}
		
			// remember what line need to change
			if((strncmp(config_name, line, cnei)==0) && (strlen(config_name)==cnei) && (linewithcnf==-1))
				linewithcnf = l;
		} 
		// remove \n at the end of last string
		if(text[l][strlen(text[l])-1]=='\n')
			text[l][strlen(text[l])-1]=0;
		// mark to know where is end of file
		strcpy(text[l+1], "end");
	}
	
	//write in file new text with changes
	if(linewithcnf>-1) // if line with config was found
	{
		// reopening file for writeing
		fclose(file);
		file = fopen(file_name, "w");
		
		// rewrite file with changed config
		for(i=0; strcmp(text[i], "end"); ++i)
		{
			if(i==linewithcnf-1) // -1 because of in massive first element is 0, but linewithcnf have correct line of config
			{
				fprintf(file, "%s%s%s\n", config_name, CNFNAMEEND, new_value);
				scw=1;
			}
			else
				fprintf(file, text[i]);
		}
		// adding argument in the end of text on new line, if not added before
		if(scw!=1)
			fprintf(file, "\n%s%s%s\n", config_name, CNFNAMEEND, new_value);
	}
	
	fclose(file);
	return linewithcnf;
}