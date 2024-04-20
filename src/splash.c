
/**
 * Clue Media Experience
 * Splash.c - Splash configuration and workflow implementation
 */

#include <stdio.h>
#include <locale.h>
#include <getopt.h>
#include <stdbool.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <libgen.h>
#include <string.h>

#include "constants.h"
#include "usage.h"
#include "utils.h"
#include "buffer.h"
#include "images.h"
#include "shapes.h"
#include "text.h"

static char FBPATH[256];

void SaveDataInMemory(CmdData data)
{
	int ShmID;
	key_t ShmKEY;
	CmdData *ShmDAP;

	ShmKEY = ftok(".", 'x');
	ShmID = shmget(ShmKEY, sizeof(CmdData), IPC_CREAT | 0666);

	if (ShmID < 0)
	{
		 ERROR("Shared memory can not be reserved for writing");
		 return;
	}

	ShmDAP = (CmdData*) shmat(ShmID, NULL, 0);

	if ((int) ShmDAP == -1)
	{
		 ERROR("Shared memory cannot be attached for writing");
		 return;
	}
	else DEBUG("Attached shared memory for writing");

	//set data
	ShmDAP->id = data.id;
	strcpy(ShmDAP->value, data.value);
	strcpy(ShmDAP->props, data.props);
	ShmDAP->xpoint = data.xpoint;
	ShmDAP->ypoint = data.ypoint;
	DEBUG("Writing command in memory: [%d] = %s", data.id, data.value != NULL ? data.value : "");
	DEBUG("    @point = (%d,%d)", data.xpoint, data.ypoint);
	DEBUG("    >props = %s", data.props);

	shmdt((void *) ShmDAP);
	INFO("Detached shared memory for writing");
}

CmdData GetMemoryData(void)
{
	int ShmID;
	key_t ShmKEY;
	CmdData data;
	CmdData *ShmDAP;

	ShmKEY = ftok(".", 'x');
	ShmID = shmget(ShmKEY, sizeof(CmdData), 0666);

	if (ShmID < 0)
	{
		 ERROR("Shared memory can not be reserved for reading");
		 return data;
	}

	ShmDAP = (CmdData*) shmat(ShmID, NULL, 0);

	if ((int) ShmDAP == -1)
	{
		 ERROR("Shared memory cannot be attached for reading");
		 return data;
	}
	else DEBUG("Attached shared memory for reading");

	//set data
	data.id = ShmDAP->id;
	strcpy(data.value, ShmDAP->value);
	strcpy(data.props, ShmDAP->props);
	data.xpoint = ShmDAP->xpoint;
	data.ypoint = ShmDAP->ypoint;

	DEBUG("Reading command from memory: [%d] = %s", data.id, data.value != NULL ? data.value : "");
	DEBUG("    @point = (%d,%d)", data.xpoint, data.ypoint);
	DEBUG("    >props = %s", data.props);

	shmdt((void *) ShmDAP);
	INFO("Detached shared memory for reading");

	return data;
}

void CleanDataInMemory(void)
{
	int ShmID;
	key_t ShmKEY;

	ShmKEY = ftok(".", 'x');
	ShmID = shmget(ShmKEY, sizeof(CmdData), IPC_RMID | 0666);

	if (ShmID >= 0)
	{
		shmctl(ShmID, IPC_RMID, NULL);
		DEBUG("Released shared memory reference for writing");
	}
}

bool HasDataInMemory(void)
{
	int ShmID;
	key_t ShmKEY;

	ShmKEY = ftok(".", 'x');
	ShmID = shmget(ShmKEY, sizeof(CmdData), 0666);

	if (ShmID < 0) return false;
		else return true;
}

/**
 * Transform input parameters into a specific structure for data processing
 *
 * @param argc list of input arguments
 * @param argv number of arguments in the list
 *
 * @return CmdData structure
 */
CmdData GetInputData(int argc, char **argv)
{
	CmdData data;
	char value[1000];
	int opt;

	//Command line arguments
	static struct option options[] =
	{
		{"dev", required_argument, NULL, 'd'},
		{"reset", no_argument, NULL, 'r'},
		{"keep", no_argument, NULL, 'k'},
		{"wipe", no_argument, NULL, 'w'},
		{"head", no_argument, NULL, 'h'},
		{"console", no_argument, NULL, 'c'},
		{"exit", optional_argument, NULL, 'e'},
		{"quit", optional_argument, NULL, 'q'},
		{"shape", optional_argument, NULL, 's'},
		{"image", optional_argument, NULL, 'i'},
		{"message", optional_argument, NULL, 'm'},
		{"properties", optional_argument, NULL, 'p'},
		{"xpoint", optional_argument, NULL, 'x'},
		{"ypoint", optional_argument, NULL, 'y'},
		{NULL, 0, NULL, 0}
	};

	//initializing command properties
	data.id = 0;
	data.xpoint = 0;
	data.ypoint = 0;
	strcpy(data.value, "");
	strcpy(data.props, "");

	while((opt = getopt_long(argc, argv, "rkwhen::q::x::y::i:m:p:sd:", options, NULL)) != -1)
	{
		if (optarg != NULL)
		{
			if(sizeof (optarg) < 255) strcpy(value, optarg);
				else strncpy(value, optarg, 255);

			strcpy(value, strtrim(value));
		}
		else strcpy(value, "");
		
		switch (opt)
		{
			case 'd':
				if (strlen(value) < 1 )
					ERROR("-d/--dev requires framebuffer device such as /dev/fb0 as argument");
				else if ( strlen(value) > 253 )
					ERROR("framebuffer device passed to -d, had too long path to be acceptable framebuffer device");
				else
					strcpy(FBPATH, value);
				break;
			case 'p':
				if(strlen(data.props) > 0) strcat(data.props, ", ");
				strcat(data.props, value);
				break;

			case 'r':
				if(strlen(data.props) > 0) strcat(data.props, ", ");
				strcat(data.props, "reset=true");
				break;

			case 'k':
				if(strlen(data.props) > 0) strcat(data.props, ", ");
				strcat(data.props, "keep=true");
				break;

			case 'w':
				if(strlen(data.props) > 0) strcat(data.props, ", ");
				strcat(data.props, "wipe=true");
				break;

			case 'h':
				if(strlen(data.props) > 0) strcat(data.props, ", ");
				strcat(data.props, "head=true");
				break;

			case 'c':
				if(strlen(data.props) > 0) strcat(data.props, ", ");
				strcat(data.props, "console=true");
				break;

			case 'x':
				if(strcmp(value, "") > 0) data.xpoint = atoi(value);
					else data.xpoint = 0;
				break;

			case 'y':
				if(strcmp(value, "") > 0) data.ypoint = atoi(value);
					else data.ypoint = 0;
				break;

			case 'e':
			case 'q':
				if (data.id == 0) 
				{
					data.id = opt;
					if(strlen(data.props) > 0) strcat(data.props, ", ");
					if(strcmp(value, "") != 0)
					{
						strcat(data.props, "exitdelay=");
						strcat(data.props, value);
					}
					else strcat(data.props, "exitdelay=0");
				}
				else 
				{
					ERROR("Multiple commands specified, previous was [%s] ", data.id);
					exit(1);
				}
				break;

			case 'm':
			case 'i':
			case 's':
				if (data.id == 0) 
				{
					data.id = opt;
					strcpy(data.value, value);
				}
				else 
				{
					ERROR("Multiple commands specified, previous was [%s] ", data.id);
					exit(1);
				}
				break;
		}
	}
	
	DEBUG("Reading command from input: [%d] = %s", data.id, data.value != NULL ? data.value : "");
	DEBUG("    @point = (%d,%d)", data.xpoint, data.ypoint);
	DEBUG("    >props = %s", data.props);
	
	return data;
}

/**
 * Synchronize input command data with graphical environment
 * 
 * @param data input command data structure
 * @return improved and synched data structure
 */
CmdData GetSyncData(CmdData data)
{
	//update properties based on the command that will be executed
	if (data.id == 'm')
	{
		data = SetTextProps(data);
	}
	else if(data.id == 's') 
	{
		data = SetShapeProps(data);
	}
	else if(data.id == 'i') 
	{
		data = SetImageProps(data);
	}
	
	DEBUG("Synchronizing input command: [%d] = %s", data.id, data.value != NULL ? data.value : "");
	DEBUG("    @point = (%d,%d)", data.xpoint, data.ypoint);
	DEBUG("    >props = %s", data.props);
	
	return data;
}

/**
 *  System function to run the program
 *
 * @param argc number of input arguments
 * @param argv pointer to the list of arguments
 * @return  0 if the execution is correct, otherwise a non 0 value.
 */
int main(int argc, char **argv)
{
	setlocale(LC_ALL, "");
	strcpy(RESPATH, DATADIR);
	strcpy(LOGFILE, LOGFILEPATH);
	strcpy(FBPATH, "");

	if ( parseUsage(argc, argv))
		return 0;

	CmdData data, prevdata;

	//Extract absolute path of executable in order to identify related resources: picture and font files
	//readlink("/proc/self/exe", RESPATH, sizeof (RESPATH));
	//sprintf(RESPATH, "%s%s", dirname(dirname(RESPATH)), "/share/splash");
	INFO("***** Start New Splash Session *****");

	//read input arguments
	DEBUG("Reading input data");
	data = GetInputData(argc, argv);

	// Main Workflow
	if(!HasDataInMemory())
	{
		if(getBoolDataProperty(data, "console"))
		{
			INFO("New process CREATEs console");

			//open graphical console
			OpenGraphicsOnConsole(&console);			
		}
		else
		{
			INFO("New process KEEPs console ");
		}
			
		//initialize the screen
		OpenBuffer(strlen(FBPATH) > 0 ? FBPATH : NULL);

		//reset the screen
		if(getBoolDataProperty(data, "reset") || getBoolDataProperty(data, "console"))
		{
			//set black screen
			ResetScreen();
		}
	}
	else
	{
		INFO("New process OPENs console");

		//initialize the screen
		OpenBuffer(strlen(FBPATH) > 0 ? FBPATH : NULL);

		//reset the screen
		if(getBoolDataProperty(data, "reset"))
		{
			DEBUG("Reset the screen");
			ResetScreen();
			
			//delete reserved memory buffer
			DEBUG("Deleting memory buffer");
			CleanDataInMemory();
		}
		else
		{
			if(!getBoolDataProperty(data, "wipe") && !getBoolDataProperty(data, "head"))
			{
				//read old data from memory and parse it
				DEBUG("Reading memory buffer");
				prevdata = GetMemoryData();

				//evaluate persistency
				if(!getBoolDataProperty(prevdata, "keep"))
				{	
					//remove old message
					if(data.id == 'm' && prevdata.id == 'm')
					{
						DEBUG("Request to overdraw old Message..");
						OverdrawText(prevdata);
					}
					else if(data.id == 's' && prevdata.id == 's' && !(strcmp(data.value, "progressbar") == 0 && getIntDataProperty(data, "percent") < 0))
					{
						DEBUG("Request to overdraw old Shape..");
						OverdrawShape(prevdata);
					}
					else if(data.id == 'i' && prevdata.id == 'i')
					{
						DEBUG("Request to overdraw old Image..");
						OverdrawImage(prevdata);
					}
				}
			}
		}
	}
	
	// synchronize command with graphical environment
	data = GetSyncData(data);

	// run actual command
	if(data.id == 'm')
	{
		if(!getBoolDataProperty(data, "wipe"))
		{
			INFO("Request to draw Message..");
			DrawText(data);
		}
		else
		{
			INFO("Request to wipe Message..");
			OverdrawText(data);
		}
	}
	else if(data.id == 's')
	{
		if(!getBoolDataProperty(data, "wipe"))
		{
			INFO("Request to draw Shape..");
			DrawShape(data);
		}
		else
		{
			INFO("Request to wipe Shape..");
			OverdrawShape(data);
		}
	}
	else if(data.id == 'i')
	{
		if(!getBoolDataProperty(data, "wipe"))
		{
			INFO("Request to draw Image..");
			DrawImage(data);
		}
		else
		{
			INFO("Request to wipe Image..");
			OverdrawImage(data);
		}		
	}

	//process EXIT-REQUEST event
	if(data.id == 'e' || data.id == 'q')
	{
		INFO("Request to Exit..");

		if(getIntDataProperty(data, "exitdelay") > 0)
		{
			int delay = getIntDataProperty(data, "exitdelay");
			DEBUG("Sleeping %d seconds before exit", delay);
			sleep(delay);
		}

		//delete reserved memory buffer
		DEBUG("Deleting memory buffer");
		CleanDataInMemory();

		//clear screen
		DEBUG("Clearing frame buffer and closing graphical console");
		OpenGraphicsOnConsole(&console);
		CloseConsole(&console);

		CloseBuffer();
		INFO("Workflow EXIT.");
	}
	else
	{
		if(!getBoolDataProperty(data, "wipe") && !getBoolDataProperty(data, "head") && !(strcmp(data.value, "progressbar") == 0 && getIntDataProperty(data, "percent") < 0))
		{
			// write the current transaction in memory
			DEBUG("Writing memory buffer");
			SaveDataInMemory(data);
		}

		INFO("Process DONE.");
	}

	exit(0);
}
