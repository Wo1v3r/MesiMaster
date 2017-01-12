// Alexey
#include "DataBase.h"

/////// functions decalrations
void addUserToProject(Global *GlobalFile, Project *newProject);									//42
void CreateNewTask(Global *GlobalFile, Project *project, int UserID, AccessGroup group);		//53
void PrintProjectsList(Global *GlobalFile, int UserID, AccessGroup group);						//44

/////// declarations end

// Functions
// 46 - Create new project by STUDENT or WATCHER only , done, ready for testing
void CreateNewProject(Global* GlobalFile,int userID, AccessGroup userGroup)
{
	Student *Student;
	Watcher *Watcher;
	puts("Input Name of your project (maximum 127 characters) : ");
	char buffer[128];		// get name
	gets(buffer);
	
	// check if student or watcher and get pointer to him
	if (userGroup == STUDENT)
		Student = FindStudent(GlobalFile->StudentList, userID);

	else if (userGroup == WATCHER)
		Watcher = FindWatcher(GlobalFile->WatchersList, userID);
	else
	{
		puts("Incorrect acess group received.");
		return;		// incorrect access group
	}

	// allocate memory
	Project *newProject = (Project*)malloc(sizeof(Project));

	newProject->ProjectID = GlobalFile->ProjectRunID;		// set runID
	GlobalFile->ProjectRunID++;								// increase runID

	strcpy(newProject->ProjectName, buffer);	// copy name

	if (userGroup == STUDENT)
		strcpy(newProject->ProjectCreatorName, Student->StudentName);	// set student name
	else if (userGroup == WATCHER)
		strcpy(newProject->ProjectCreatorName, Watcher->WatcherName);	// set watcher name

	// fill basic fields
	newProject->ProjectUsersAmount = 1;		// 1 for creator
	// add creator ID to project array
	newProject->StudentsIDS = (int*)malloc(newProject->ProjectUsersAmount*sizeof(int));
	if (userGroup == STUDENT);
	newProject->StudentsIDS[0] = userID;

	newProject->ProjectTasksAmount = 0;
	newProject->TasksList = NULL;
	newProject->TasksIDS = NULL;
	newProject->ProgramChanges = FALSE;
	newProject->ProjectNext = NULL;

	// create file name ID_ProjectActivityLog.txt and put name to ProjectActivityLog field
	char ActivityFileName[50];		
	sprintf(ActivityFileName, "%d_ProjectActivityLog.txt", newProject->ProjectID);
	FILE *ProjActivityLog = fopen(ActivityFileName, "w");
	fclose(ProjActivityLog);
	strcpy(newProject->ProjectActivityLogs, ActivityFileName);

	// create file name ID_ProjectMessages.txt and put name to ProjectMessages field
	char MessagesFileName[50];		
	sprintf(MessagesFileName, "%d_Project.Messages.txt", newProject->ProjectID);
	FILE *ProjMsgs = fopen(MessagesFileName, "w");
	fclose(ProjMsgs);
	strcpy(newProject->ProjectMessages, MessagesFileName);

	// add new project to list of projects Global
	AddProject(GlobalFile->ProjectsList, newProject); 

	//add id of new project to creator
	int ProjectIDSNewSize,index;
	int* newArrayIDs;	//create new increased array

	if (userGroup == STUDENT)			// add project ID to student 
	{
		ProjectIDSNewSize = Student->StudentProjectsAmount + 1;
		newArrayIDs = (int*)malloc(ProjectIDSNewSize * sizeof(int));

		for (index = 0; index < ProjectIDSNewSize - 1; index++)
			newArrayIDs[index] = Student->ProjectIDS[index];			// copy old values
		newArrayIDs[index] = newProject->ProjectID;					// add new project id to last index of nea array

		free(Student->ProjectIDS);											// free old array memory
		Student->ProjectIDS = newArrayIDs;									// set new array pointer to student
		Student->StudentProjectsAmount ++;									// update size of projects amount to student

	}

	else if (userGroup == WATCHER)			// add project ID to Watcher's array
	{
		ProjectIDSNewSize = Watcher->WatcherProjectsAmount + 1;
		newArrayIDs = (int*)malloc(ProjectIDSNewSize * sizeof(int));

		for (index = 0; index < ProjectIDSNewSize - 1; index++)
			newArrayIDs[index] = Watcher->ProjectIDS[index];			// copy old values
		newArrayIDs[index] = newProject->ProjectID;					// add new project id to last index of nea array

		free(Watcher->ProjectIDS);											// free old array memory
		Student->ProjectIDS = newArrayIDs;									// set new array pointer to student
		Watcher->WatcherProjectsAmount++;								// update size of projects amount to watcher
	}


	char choice;
	printf("Project \"%s\" created!\nWant to add collaborators to this project? (y / n) :", newProject->ProjectName);
	fflush(stdin);
	choice = getchar();
	switch (choice)
	{
	case 'y':
		addUserToProject(GlobalFile, newProject);
		break;
	case 'n':
		puts("Ok!");
		break;
	default:
		puts("Incorrect Symbol inputed");
		break;
	}
	puts("1 .Return to previous StudentMenu");
	puts("2. Exit");
	fflush(stdin);
	choice = getchar();
	if (choice == '1')
		puts("Returning to main menu...");
	else if (choice == '2')
		Exit();
	else
		puts("Incorrect input, you will be returned to Menu");

}

// 42 - Add user to project  , done, ready for testing
void addUserToProject(Global *GlobalFile, Project *newProject)
{
	BOOL flag = TRUE;
	Student *student=NULL;
	Watcher *watcher= NULL;
	char choice;
	int StudentProjectsIDSNewSize, WatcherProjectsIDSNewSize, i, ProjectUsersIDNewSize, ID;
	int* ProjectsIDs,*UsersID;	//create new increased array


	while (flag)
	{
		puts("1. Add Student ID");
		puts("2. Add Watcher ID");
		puts("3. Return to main menu");
		fflush(stdin);
		choice = getchar();
		switch (choice)
		{
		case '1':
			fflush(stdin);
			printf("\nStudent ID :");
			scanf("%d", &ID);
			student = FindStudent(GlobalFile->StudentList, ID);
			if (student)	// student found
			{
				/// add project to student 
				StudentProjectsIDSNewSize = student->StudentProjectsAmount + 1;
				ProjectsIDs = (int*)malloc(StudentProjectsIDSNewSize * sizeof(int));

				for (i = 0; i < StudentProjectsIDSNewSize - 1; i++)
					ProjectsIDs[i] = student->ProjectIDS[i];			// copy old values
				ProjectsIDs[i] = newProject->ProjectID;					// add new project id to last index of nea array

				free(student->ProjectIDS);											// free old array memory
				student->ProjectIDS = ProjectsIDs;									// set new array pointer to student

				printf("\nStudent with ID : %d was added to project!\n", ID);
				
				// add student to project
				ProjectUsersIDNewSize = newProject->ProjectUsersAmount + 1;
				UsersID = (int*)malloc(ProjectUsersIDNewSize*sizeof(int));
				for (i = 0; i < ProjectUsersIDNewSize - 1; i++)
					UsersID[i] = newProject->StudentsIDS[i];
				UsersID[i] = ID;

				newProject->StudentsIDS = UsersID;
			}
			else
				puts("Student ID not found. Try again.");
			break;

		case '2':
			fflush(stdin);
			printf("\nWatcher ID :");
			scanf("%d", &ID);
			watcher = FindWatcher(GlobalFile->WatchersList, ID);
			if (watcher)	// student found
			{
				/// add project to student 
				WatcherProjectsIDSNewSize = watcher->WatcherProjectsAmount + 1;
				ProjectsIDs = (int*)malloc(WatcherProjectsIDSNewSize * sizeof(int));

				for (i = 0; i < WatcherProjectsIDSNewSize - 1; i++)
					ProjectsIDs[i] = watcher->ProjectIDS[i];			// copy old values
				ProjectsIDs[i] = newProject->ProjectID;					// add new project id to last index of nea array

				free(watcher->ProjectIDS);											// free old array memory
				watcher->ProjectIDS = ProjectsIDs;									// set new array pointer to student

				printf("Watcher with ID : %d was added to project!\n", ID);

				// add student to project
				ProjectUsersIDNewSize = newProject->ProjectUsersAmount + 1;
				UsersID = (int*)malloc(ProjectUsersIDNewSize*sizeof(int));
				for (i = 0; i < ProjectUsersIDNewSize - 1; i++)
					UsersID[i] = newProject->StudentsIDS[i];
				UsersID[i] = ID;

				newProject->StudentsIDS = UsersID;
			}
			else
				puts("Watcher ID not found. Try again.");
			break;
		case '3':
			puts("Choosen to return back");
			flag = FALSE;
			break;
		default:
			puts("Incorrect choice. Try again.");
			break;
		}

	}
}

// 53 - create new task from project menu, done, ready for testing
void CreateNewTask(Global *GlobalFile, Project *project,int UserID,AccessGroup group)
{
	Student *student = NULL;
	Watcher *watcher = NULL;

	Task *newTask = (Task*)malloc(sizeof(Task));	//new task pointer

	newTask->TaskID = GlobalFile->TaskRunID;		// set Task Run ID

	GlobalFile->TaskRunID++;						// increase run id by 1
	fflush(stdin);
	puts("Enter your task (up to 255 chars) :");
	gets(newTask->TaskName);
	if (group == STUDENT)
		student = FindStudent(GlobalFile->StudentList, UserID);
	else if (group == WATCHER)
		watcher = FindWatcher(GlobalFile->WatchersList, UserID);
	else
	{
		puts("Incorrect access group");
		return;
	}

	if (group == STUDENT)
	{
		strcpy(newTask->TaskCreatorName, student->StudentName);			// copy creator name to task
		student->StudentTasksAmount++;
	}
	else if (group == WATCHER)
		strcpy(newTask->TaskCreatorName, watcher->WatcherName);			// copy creator name to task

	newTask->TaskStatus = NEW;								// initialize status

	project->TasksList = AddTask(project->TasksList, newTask);		// add new task to tasks list of choosen project
	printf("New Task \"%s\" was created in project \"%s\"\n",newTask->TaskName,project->ProjectName);


	/// to complete saving ID to TASKSID array

}


void PrintProjectsList(Global *GlobalFile, int UserID, AccessGroup group)
{
	int i;
	Student* student=NULL;
	Watcher *watcher = NULL;
	Project *current = NULL;
	int *ProjectsIDS;

	// find user
	if (group == STUDENT)
	{
		student = FindStudent(GlobalFile->StudentList, UserID);
		ProjectsIDS = student->ProjectIDS;

		int arraySize = sizeof(ProjectsIDS) / sizeof(int);
		puts("List of your projects :");
		printf("ID\tName\tUsers\tTasks");
		for (i = 0; i < arraySize; i++)
		{
			current = FindProject(GlobalFile->ProjectsList, student->ProjectIDS[i]);
			if (current)
			{
				printf("%d\t%s\t%d\t%d",current->ProjectID,current->ProjectName,current->ProjectUsersAmount,current->ProjectTasksAmount);
			}

		}
	}// in case of watcher
	else if (group == WATCHER)
	{
		watcher = FindWatcher(GlobalFile->WatchersList, UserID);
		ProjectsIDS = watcher->ProjectIDS;

		int arraySize = sizeof(ProjectsIDS) / sizeof(int);
		puts("List of your projects :");
		printf("ID\tName\tUsers\tTasks");
		for (i = 0; i < arraySize; i++)
		{
			current = FindProject(GlobalFile->ProjectsList, watcher->ProjectIDS[i]);
			if (current)
			{
				printf("%d\t%s\t%d\t%d", current->ProjectID, current->ProjectName, current->ProjectUsersAmount, current->ProjectTasksAmount);
			}

		}
	}
	else
	{
		puts("Incorrect access group");
		return;
	}
	
}