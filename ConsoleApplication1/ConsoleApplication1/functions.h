// Alexey
#include "DataBase.h"

// Functions
void CreateNewProject(Global* GlobalFile,int StudentID)
{
	puts("Input Name of your project (maximum 127 characters) : ");
	char buffer[128];		// get name
	gets(buffer);

	Student *sender = FindStudent(GlobalFile->StudentList, StudentID);

	Project *newProject = (Project*)malloc(sizeof(Project));
	newProject->ProjectID = GlobalFile->ProjectRunID;		// set runID
	GlobalFile->ProjectRunID++;								// increase runID

	strcpy(newProject->ProjectName, buffer);	// copy name
	strcpy(newProject->ProjectCreatorName, sender->StudentName);	// set creator
	newProject->ProjectUsersAmount = 0;
	newProject->ProjectTasksAmount = 0;
	newProject->TasksList = NULL;
	newProject->StudentsIDS = NULL;
	newProject->TasksIDS = NULL;
	newProject->ProgramChanges = FALSE;
	newProject->ProjectNext = NULL;

	char ActivityFileName[50];		// create file name ID_ProjectActivityLog.txt and put name to ProjectActivityLog field
	sprintf(ActivityFileName, "%d_ProjectActivityLog.txt", newProject->ProjectID);
	FILE *ProjActivityLog = fopen(ActivityFileName, "w");
	fclose(ProjActivityLog);
	strcpy(newProject->ProjectActivityLogs, ActivityFileName);

	char MessagesFileName[50];		// create file name ID_ProjectMessages.txt and put name to ProjectMessages field
	sprintf(MessagesFileName, "%d_Project.Messages.txt", newProject->ProjectID);
	FILE *ProjMsgs = fopen(MessagesFileName, "w");
	fclose(ProjMsgs);
	strcpy(newProject->ProjectMessages, MessagesFileName);

	AddProject(GlobalFile->ProjectsList, newProject);

	char choice;
	printf("Project %s created! Want to add collaborators to this project? (y / n) :", newProject->ProjectName);
	choice = getchar();
	switch (choice)
	{
	case 'y':
		//addUserToProject(newProject);
		break;
	case 'n':
		puts("Ok!");
		break;
	default:
		puts("Incorrect Symbol inputed");
		break;
	}
	puts("1 . Return to previous StudentMenu");
	puts("2. Exit");
	choice = getchar();
	if (choice == '1')
		puts("Returning to main menu...");
	else if (choice == '2')
		Exit();
	else
		puts("Incorrect input, you will be returned to Menu");

}
