#include "DataBase.h"

BOOL ChaeckIfExists(Global, char*);
BOOL CheckPassword(char*);
int Register(Global);
int StudentRegister(Global);
int WatcherRegister(Global);

//HELP FUNCTION for Register(Global)
BOOL CheckIfUserExists(Global *g, char *username)
{
	//The function receives a username and a global pointer, and checks if the given username 
	//already exists in the system's databases.
	Student *tempStud = g->StudentList;
	Watcher *tempWatch = g->WatchersList;
	Admin *tempAdm = g->AdminsList;

	while (tempStud != NULL)																		//Checking if the username exists in the student list																																
	{
		if (strcmp(tempStud->StudentUsername, username))
		{
			return TRUE;
		}
	}

	while (tempWatch != NULL)														                //Checking if the username exists in the watcher list
	{
		if (strcmp(tempWatch->WatcherUsername, username))
		{
			return TRUE;
		}
	}

	while (tempAdm != NULL)														                    //Checking if the username exists in the admins list
	{
		if (strcmp(tempAdm->AdminUsername, username))
		{
			return TRUE;
		}
	}

	return FALSE;
}

BOOL CheckPassword(char* pass)
{
	//A valid password must contain at least: a digit, an upper case letter, a lower case letter.
	BOOL lowerFlag = FALSE, upperFlag = FALSE, digitFlag = FALSE;
	int i;
	for (i = 0; i < strlen(pass); i++)
	{
		if (pass[i] >= 'A' && pass[i] <= 'Z')
		{
			upperFlag = TRUE;
		}
		if (pass[i] >= 'a' && pass[i] <= 'z')
		{
			lowerFlag = TRUE;
		}
		if (pass[i] >= '0' && pass[i] <= '9')
		{
			digitFlag = TRUE;
		}
	}
	if (upperFlag == TRUE && lowerFlag == TRUE && digitFlag == TRUE)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

int Register(Global *g)
{
	int choice;                                                                                     //Action menu - choosing user type or action (student, watcher, back)
	do{
		printf("Choose a user type:\n\t[1] Student\n\t[2]Watcher\n\t[3]Back to last menu\n");
		scanf("%d", &choice);
	} while (choice != 1 && choice != 2 && choice != 3);

	if (choice == 1)                                                                                //Executing student registration
	{
		return StudentRegister(g);
	}
	else if (choice == 2)																			//Executing watcher registration
	{
		return WatcherRegister(g);
	}
	else
	{																								//Back to last menu
		return 0;
	}
}

int StudentRegister(Global *g)
{
	char stringID[31];
	int choice = 0;
	Student* newStudent = NULL;																		//Allocating memory for the new student
	newStudent = (Student*)malloc(sizeof(Student));

	if (newStudent == NULL)                                                                         //Allocation check
	{
		printf("Error allocating memory for the new student.\n");
		return 0;
	}

	newStudent->StudentID = g->StudentRunID;														//ID allocation
	(g->StudentRunID)++;

	//Initializing username
	do{																								//CS - Initializing attributes that require user input
		_flushall();
		printf("Enter your desired username: (Has to be less then 30 characters!)\n");
		scanf("%s", newStudent->StudentUsername);

		if (CheckIfUserExists(g, newStudent->StudentUsername) == TRUE)
		{
			printf("This username already exists in the system. \n Press 1 to try again, press 2 to go back to the next menu.\n");
			scanf("%d", &choice);
		}
	} while (CheckIfUserExists(g, newStudent->StudentUsername) == TRUE && choice == 1);

	if (choice != 1)
	{
		printf("You did not press 1 to continue. Going back to last menu.\n");
		return 0;
	}
	 //Initializing password
	do{
		_flushall();
		printf("Enter your desired password: (Has to be less then 30 characters, and contain\n");
		printf("at least one digit, one upper case letter, one lower case letter)\n");
		scanf("%s", newStudent->StudentPassword);
		if (CheckPassword(newStudent->StudentPassword) == FALSE)
		{
			printf("This password is invalid.\n You need to try again.\n");
		}
	} while (CheckPassword(newStudent->StudentPassword) == FALSE);

	printf("Enter your email address: (Has to be less then 50 characters!)\n");
	scanf("%s", newStudent->StudentEmail);
	printf("Enter your first name: (Has to be less then 20 characters!)\n");
	scanf("%s", newStudent->StudentName);
	printf("Enter your last name: (Has to be less then 20 chatacters!)\n");
	scanf("%s", newStudent->StudentSurename);
	printf("Enter you department: (Has to be less then 20 characters!)\n");
	scanf("%s", newStudent->StudentDepartment);
	_flushall();
	printf("Enter your year in the academic facility: (Has to be 1 character!)\n");
	scanf("%c", &(newStudent->StudentYear));
	//Default initializations 
	newStudent->Group = STUDENT;
	newStudent->StudentProjectsAmount = 0;
	newStudent->ProjectIDS= NULL;
	newStudent->StudentTasksAmount = 0;

	sprintf(stringID, "%d", newStudent->StudentID); //convert id num to string
	strcpy(newStudent->StudentActivityLog, stringID); //insert this num to student log string
	strcat(newStudent->StudentActivityLog, "_SLog.txt"); //cat the rest of the file name

	strcpy(newStudent->StudentMessages, stringID); //insert id string to messages string
	strcat(newStudent->StudentMessages, "_SMess.txt"); // cat the rest of the file name

	newStudent->StudentNext = g->StudentList;
	return newStudent->StudentID;
}

int WatcherRegister(Global *g)
{
	Watcher* newWatcher = NULL;
	int choice;
	newWatcher = (Watcher*)malloc(sizeof(Watcher));													//Allcating memory for the new watcher

	if (newWatcher == NULL)                                                                         //Allocation check
	{
		printf("Error allocating memory for the new watcher.\n");
		return 0;
	}
	newWatcher->WatcherID = g->WatcherRunID;														//Id allocation
	(g->WatcherRunID)++;

	do{																								//CS - Initializing attributes that require user input
		_flushall();
		printf("Enter your desired username: (Has to be less then 30 characters!)\n");
		scanf("%s", newWatcher->WatcherUsername);

		if (CheckIfUserExists(g, newWatcher->WatcherUsername) == TRUE)
		{
			printf("This username already exists in the system. \n Press 1 to try again, press 2 to go back to the next menu.\n");
			scanf("%d", &choice);
		}
	} while (CheckIfUserExists(g, newWatcher->WatcherUsername) == TRUE && choice == 1);

	if (choice != 1)
	{
		printf("You did not press 1 to continue. Going back to last menu.\n");
		return 0;
	}
	//Initializing password
	do{
		_flushall();
		printf("Enter your desired password: (Has to be less then 30 characters, and contain\n");
		printf("at least one digit, one upper case letter, one lower case letter)\n");
		scanf("%s", newWatcher->WatcherPassword);
		if (CheckPassword(newWatcher->WatcherPassword) == FALSE)
		{
			printf("This password is invalid.\n You need to try again.\n");
		}
	} while (CheckPassword(newWatcher->WatcherPassword) == FALSE);

	printf("Enter your email address: (Has to be less then 50 characters!)\n");
	scanf("%s", newWatcher->WatcherEmail);
	printf("Enter your first name: (Has to be less then 20 characters!)\n");
	scanf("%s", newWatcher->WatcherName);
	printf("Enter your last name: (Has to be less then 20 chatacters!)\n");
	scanf("%s", newWatcher->WatcherSurename);

	newWatcher->Group = WATCHER;																	//Default initializations
	newWatcher->ProjectIDS = NULL;
	newWatcher->WatcherProjectsAmount = 0;
	newWatcher->WatcherReceiveChanges = FALSE;

	newWatcher->WatcherNext = g->WatchersList;
	return newWatcher->WatcherID;
}