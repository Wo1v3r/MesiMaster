#ifndef _FUNCTIONS_
#define _FUNCTIONS_
#include "DataBase.h"
#include "time.h"

///Functions Declarations///
// 1) Please add function number if possible when re-doing the DFD
// 2) Please add a test to the tests file for each functions, mark "Test Written" as needed

//Project Functions
int CreateNewProject(Global* GlobalFile, int userID, AccessGroup userGroup , char* projectName); //Test written - Jonathan
int CreateNewTask(Global *GlobalFile, Project *project, int UserID, AccessGroup group,char* taskName);//Test written - Jonathan		
int addUserToProject(Global *GlobalFile, Project *newProject,int UserID,int watcherOrStudent);//Test written - Jonathan
int ChangeTaskStatus(Global* GlobalFile, Project* project, int userID, int accessGroup, int tasktest, int statustest); //Test written - Jonathan
void PrintProjectDetails(Global* GlobalFile, Project* project); //No test needed
void PrintProjectMessages(Project *project); //No test needed

//Utilities
void printRandQuote(Global* GlobalFile); //No test needed
void ShowUserDetails(Global *GlobalFile); //No test needed
void PrintUsersLists(Global* GlobalFile);//No test needed
void PrintUsersByID(Global *GlobalFile, Project *project);//No test needed
int PrintTasksList(Global* GlobalFile, Project* Project);//No test needed
void PrintTasksByID(Task *head, int indexes[], int size, char *creator);//No test needed
void PrintProjectsList(Global *GlobalFile, int UserID, AccessGroup group);//No test needed
void PrintProjectsByID(Global *GlobalFile, int indexes[], int size, char *creator);//No test needed
int* RemoveProjectIDFromArray(int Array[], int ProjectID, int  size);//Test written - Isabelle
int RemoveProjectFromUsers(Global* GlobalFile, int ProjectID);//Test written - Isabelle
void RemoveUserFromProjects(Global *GlobalFile, int UserID);//Test written - Isabelle
int *RemoveUserIDFromProject(Project* project, int ID);//Test written - Isabelle
void AddProjectIDToStudent(Student * Student, int ProjectID); //Test written
void AddProjectIDToWatcher(Watcher * Watcher, int ProjectID); //Test written
void AddTaskIDToProject(Project* project, int TaskID); //Test written
int FindAccessGroup(int ID);  //Test Written - Jonathan
Admin* FindAdminByUN(Global *g, char *username); //Test written - Isabelle
Student* FindStudentByUN(Global *g, char *username); //Test written - Isabelle
Watcher* FindWatcherByUN(Global *g, char *username); //Test written - Isabelle
Admin *StudentToAdmin(Global *GlobalFile, Student *student); //Test written
void UpdateDetails(Global* GlobalFile, int userID, char* testpass, char* testname, char* testlastname
									 , int testchangepass, int testchangename, int testchangelastname); //Test written
Admin * WatcherToAdmin(Global *GlobalFile, Watcher *watcher); //Test written
void Output(char* message); // No test needed , prints and prompts for enter

//Log functions
void PrintStudentLog(Student* student);//No test needed
void printLogToFile(char file[], char msg[500]);//No test needed
void PrintProjectChanges(Global *GlobalFile, Project* project, Watcher *watcher);//No test needed
void PrintGlobalMessages(Global *GlobalFile);//No test needed
void PrintActivityLog(char* filePath);//No test needed
void PrintQuotes(Global* GlobalFile);//No test needed

//Student Functions
void ShowMessagesToStudent(Global * Global, Student *student); //No test needed
void ShowTasksByStatus(Global* GlobalFile, int studentID); //No test needed


//Watcher Functions
void LeaveMessageToStudent(Global* GlobalFile, Project* project, Watcher* watcher); //No test needed(writing to file)
void AddProjectMessage(Global* GlobalFile, Project* project, Watcher* watcher); //No test needed(writing to file)
void PrintStudentActivityWatcher(Global *GlobalFile, Project *project); //No test needed(writing to console from file)
BOOL ShowNotifications(Global *GlobalFile, Watcher *watcher, char choice); // Test written
void ShowTasksByWatcher(Global* GlobalFile, int WatcherID); //No test needed(printing to stdout)

//Admin Functions
int RemoveProject(Global* GlobalFile, Project* project, char choice); //Test written
void AddGlobalMessage(Global* GlobalFile, char* msg); //Test written
void AddNewQuote(Global* GlobalFile, char* quote, char* creator); //Test written
void ManageQuotes(Global *GlobalFile); //No test needed(switch case function)
int AddNewUser(Global* GlobalFile); //No test needed(switch case function)
void DeleteQuote(Global* GlobalFile, int ID); //Test written
int DeleteUser(Global *GlobalFile, int ID); //Test written(with blood)
void PromoteUserToAdmin(Global *GlobalFile, int ID); //Test written

//Login/Register Functions
int Register(Global *g); //No test needewd , Admin\Watcher\Student Register takes care of that
int AdminRegister(Global *GlobalFile, char* nameTest, char* surnameTest, char* unTest, char* passTest);//Test written
int WatcherRegister(Global *g,char* nameTest, char* surnameTest, char* unTest, char* passTest, char* emailTest);//Test written
int StudentRegister(Global *g, char* nameTest, char* surnameTest ,char* unTest, char* passTest, char* emailTest, char* departmentTest, char yearTest);//Test written
int Login(Global *g, char* UN, char* PW); //Test written
BOOL CheckPassword(char* pass); //Test written -Jonathan
BOOL CheckIfUserExists(Global *g, char *username); //Test written -Jonathan

//
// change status of choosen task, done, ready for testing
int ChangeTaskStatus(Global* GlobalFile, Project* project, int userID, int accessGroup,int statustest, int taskidtest){
	int taskID, status;
	Task* task;
	Student * student = FindStudent(GlobalFile->StudentList, userID);
	//Getting a task from the user:
	if (!taskidtest){
		printf("Enter Task ID:\n");
		scanf("%d", &taskID);
	}
	else taskID = taskidtest;

	//Making sure that task is in the relevant project:
	if (project->ProjectTasksAmount == 0) {
		if (!taskidtest) Output("Project has no tasks");
		return 0;
	}
	task = findTaskInProject(GlobalFile, project, taskID);
	if (!task){
		if (!taskidtest) Output("Task does not belong to this project");
		return 0;
	}
	if (!taskidtest){
		printf("Current status is: %s\n", convertStatusToString(task->TaskStatus));
		printf("Choose status to change into:\n");
		printf("Available Status:\n");
		printf("[0] New , [1] Elicitation, [2] Analysis, [3] VandV ");
		if (accessGroup != STUDENT) printf(" [4] Approved"); //Student can't change to approved
		printf("\n");
		printf("Enter an integer of your choice:\n");
		scanf("%d", &status);
	}
	else status = statustest;
	
	if (accessGroup == STUDENT && status == APPROVED) {
		if (!taskidtest) Output("Student cannot set status to approved, please contact your watcher or admin");
		return 0;
	}
	if (status == NEW || status == ELICITATION || status == ANALYSIS || status == VandV || status == APPROVED)
	{
		task->TaskStatus = (STATUS)status;
		if (student)
		{
			char log[256];
			sprintf(log, "%s changed status for task ID : to new status : %s", student->StudentUsername, convertStatusToString(task->TaskStatus));
				printLogToFile(project->ProjectActivityLogs,log);
		}

	}
	else
	{
		if (!taskidtest) Output("Incorrect status identificator, status not been changed.");
		return 0;
	}
	if (!taskidtest)Output("");
	return 1;
}


//remove project id from received array, and return new array 
int* RemoveProjectIDFromArray(int Array[], int ProjectID, int size)
{
	if (size - 1 == 0)
		return NULL;
	int *ProjectsIDs = (int*)malloc((size - 1) * sizeof(int)), i, newindex = 0;
	for (i = 0; i < size; i++, newindex++)
	{
		if (Array[i] != ProjectID)
			ProjectsIDs[newindex] = Array[i];
		else
			newindex--;
	}
	return ProjectsIDs;
}

// run over all watcher and student list, if found project ID in him array, delete it
int RemoveProjectFromUsers(Global* GlobalFile, int ProjectID)
{
	int *CheckArray = NULL,i;
	int DeletedFromArrays = 0;	// counter return amount of arrays, where ID been found and deleted from
	Watcher *watcher = GlobalFile->WatchersList;
	Student *student = GlobalFile->StudentList;

	while (watcher)
	{
		for (i = 0; i < watcher->WatcherProjectsAmount; i++)
		{
			if (watcher->ProjectIDS[i] == ProjectID)
			{
				watcher->ProjectIDS = RemoveProjectIDFromArray(watcher->ProjectIDS, ProjectID, watcher->WatcherProjectsAmount);
				watcher->WatcherProjectsAmount--;
				DeletedFromArrays++;
				break;
			}
		}
		watcher = watcher->WatcherNext;
	}
	while (student)
	{
		for (i = 0; i < student->StudentProjectsAmount; i++)
		{
			if (student->ProjectIDS[i] == ProjectID)
			{
				student->ProjectIDS = RemoveProjectIDFromArray(student->ProjectIDS, ProjectID, student->StudentProjectsAmount);
				student->StudentTasksAmount -= FindProject(GlobalFile->ProjectsList, ProjectID)->ProjectTasksAmount;
				student->StudentProjectsAmount--;
				DeletedFromArrays++;
				break;
			}
		}
		student = student->StudentNext;
	}
	return DeletedFromArrays;
}

// done by Alexey, ready for testing
int RemoveProject(Global* GlobalFile, Project* project, char choice){
	int i;
	if (choice == 0){
		choice = 0;
		printf("Are you sure you want to remove this project and all of its tasks (Y/N)?\n");
		while (choice == 0){
			fflush(stdin);
			choice = getchar();
			switch (choice){
			case 'Y':
			case 'y':
				// remove Project ID from all users's arrays of ProjectsID
				RemoveProjectFromUsers(GlobalFile, project->ProjectID);
				free(project->StudentsIDS);
				// remove tasks belongs to project from Global task list
				for (i = 0; i < project->ProjectTasksAmount; i++)
					GlobalFile->TaskList = RemoveTaskFromList(GlobalFile->TaskList, project->TasksIDS[i]);
				free(project->TasksIDS);
				// remove project from GLobal list
				GlobalFile->ProjectsList = RemoveProjectFromList(GlobalFile->ProjectsList, project->ProjectID);
				//delete // Need to implement functions that will remove this project id from all the users, from all the lists etc
				Output("Project removed!!");
				return 1;
				break;
			case 'N':
			case 'n':
				return 0;
				break;
			default: 
				Output("No such option!");
				return 0;
			}
		}
	}
	else{
		RemoveProjectFromUsers(GlobalFile, project->ProjectID);
		free(project->StudentsIDS);
		for (i = 0; i < project->ProjectTasksAmount; i++)
			GlobalFile->TaskList = RemoveTaskFromList(GlobalFile->TaskList, project->TasksIDS[i]);
		free(project->TasksIDS);
		GlobalFile->ProjectsList = RemoveProjectFromList(GlobalFile->ProjectsList, project->ProjectID);
	}
}

// choose student id in project and send message to him, done, ready for testing
void LeaveMessageToStudent(Global* GlobalFile, Project* project, Watcher* watcher){
	int studentID;
	Student* student;
	char* Message;
	printf("Please choose a studentID of the student you want to leave a message for (message will be shown once)\n");
	scanf("%d", &studentID);
	if (isStudentInProject(project, studentID)){
		student = FindStudent(GlobalFile->StudentList, studentID);
		if (!student) return; //If for some reason student is not in the global file, exiting function
			printf("Enter the message you want to leave (Between 5 to 30):\n");
		do
		scanf("%s", &Message);
		while (strlen(Message) < 5 || strlen(Message) > 30);
		strcpy(student->StudentMessages, Message);

		// add message to student message file 
		FILE *file = fopen(student->StudentMessages, "a");
		fprintf(file, "%s %s\n", watcher->WatcherUsername, Message);
		fclose(file);
	}

	system("pause");
}

// added option to delete all messages from message.txt of project
void AddProjectMessage(Global* GlobalFile, Project* project, Watcher* watcher){
	char* Message = "",choice;
	printf("Enter the message you want to leave (Between 5 to 30):\n");
	do
	scanf("%s", &Message);
	while (strlen(Message) < 5 || strlen(Message) > 30);

	strcpy(project->ProjectMessages, Message);

	// add message to project activity and Messages logs
	char log[120];
	sprintf(log,"%s added message : %s", watcher->WatcherUsername, Message);
	printLogToFile(project->ProjectMessages,log);
	printLogToFile(project->ProjectActivityLogs, log);

	puts("If you want to delete all messages from this project, press Y now :");
	choice = getchar();
	// create new empty file
	if (choice == 'y' || choice == 'Y')
	{
		FILE *file = fopen(project->ProjectMessages, "w");
		fclose(file);
	}
	system("pause");
}

//Allow to student print tasks in him project by status,  done by Johnatan, ready for testing ( added checking if project !=NULL)
void ShowTasksByStatus(Global* GlobalFile, int studentID){
	int tasksCount = 0, i, j, status = -1, projectID, taskID;
	Student* student = FindStudent(GlobalFile->StudentList, studentID);
	Project* project;
	Task* task;
	int* projectIDs = student->ProjectIDS;

	printf("Available Status:\n");
	printf("[0] New , [1] Elicitation, [2] Analysis, [3] VandV, [4] Approved\n ");
	printf("Enter an integer of your choice:\n");
	do
	scanf("%d", &status);
	while (status < 0 || status > 4);

	//Finding all the projects this student belongs to and printing the tasks:
	for (i = 0; i < student->StudentProjectsAmount; i++)
	{
		projectID = projectIDs[i];
		project = FindProject(GlobalFile->ProjectsList, projectID);
		if (project)
		{
			for (j = 0; j < project->ProjectTasksAmount; j++)
			{
				taskID = project->TasksIDS[j];
				task = findTaskInProject(GlobalFile, project, taskID);
				if (task->TaskStatus == status)
				{
					printf("%d.)ID: %d , Creator: %s , Task: %s \n", tasksCount + 1, task->TaskID, task->TaskCreatorName, task->TaskName);
					tasksCount++;
				}
			}
		}
	}
	if (tasksCount == 0)
		puts("Not found tasks in your projects with this status");

	system("pause");
}

int PrintTasksList(Global* GlobalFile, Project* Project){
	int i, j, status, taskID;
	Task* task;
	char* creator;
	char* taskName;

	printf("Tasks in project:\n");
	if (Project->ProjectTasksAmount == 0)
	{
		Output("No Tasks created in this project");
		return 0; //Fail
	}

	for (j = 1, i = 0; i < Project->ProjectTasksAmount; i++){
		task = FindTask(GlobalFile->TaskList, Project->TasksIDS[i]);
		status = task->TaskStatus;
		if (status == 5) //Trash and won't show it
			continue;
		taskID = task->TaskID;
		creator = task->TaskCreatorName;
		taskName = task->TaskName;

		printf("---\n");
		printf("%d) ID: %d Creator: %s Status: %s\n", j, taskID, creator, convertStatusToString(status));
		printf("Task: %s\n\n", taskName);
		j++;
	}

	Output("");
	return 1;	//Success
}

// signature was changed to print all types of logs
void PrintActivityLog(char* filePath){

	char BUFFER[400];
	FILE* file = fopen(filePath, "r");
	if (!file) return;

	while (fgets(BUFFER, 400, file)) printf("%s\n", BUFFER);
	fclose(file);

	Output("");
}

void PrintProjectDetails(Global* GlobalFile, Project* project){
	int projectID = project->ProjectID,
		numOfTasks = project->ProjectTasksAmount,
		numOfUsers = project->ProjectUsersAmount;
	char* creator = project->ProjectCreatorName, *projectName = project->ProjectName;

	printf("Project Details:\n");
	printf("-------------------\n");
	printf("ID: %d , Number of tasks: %d , Number of users: %d , Creator: %s\n\n", projectID, numOfTasks, numOfUsers, creator);

	//Need to print details of student here too.
	PrintUsersByID(GlobalFile, project);
	//Need to add a helper function for that

	system("pause");
}

// receive ID and return user group, done, ready for testing
int FindAccessGroup(int ID){
	//Should be in Functions, I wrote it for the meantime here
	if (ID >= 1000 && ID <= 1999) return STUDENT;
	else if (ID >= 2000 && ID <= 2999) return ADMIN;
	else if (ID >= 3000 && ID <= 3999) return WATCHER;

	return BAD;
}

// Update few field of user, done, ready for testing
void UpdateDetails(Global* GlobalFile, int userID,char* testpass, char* testname, char* testlastname
	,int testchangepass, int testchangename, int testchangelastname){
	//Finding the user and its' struct:
	Watcher* watcher = NULL;
	Admin* admin = NULL;
	Student* student = NULL;
	BOOL passCorrectness;
	char *name, *surname, input, *password, tempPass[31], tempname[31], tempsurname[31];
	int AG = FindAccessGroup(userID);

	switch (AG){
	case STUDENT:
		student = FindStudent(GlobalFile->StudentList, userID);
		name = student->StudentName;
		surname = student->StudentSurename;
		password = student->StudentPassword;
		break;

	case ADMIN:
		admin = FindAdmin(GlobalFile->AdminsList, userID);
		name = admin->AdminName;
		surname = admin->AdminSurename;
		password = admin->AdminPassword;
		break;

	case WATCHER:
		watcher = FindWatcher(GlobalFile->WatchersList, userID);
		name = watcher->WatcherName;
		surname = watcher->WatcherSurename;
		password = watcher->WatcherPassword;
		break;
	}
	if (!testchangename){
		fflush(stdin);
		printf("\nDo you want to change your first name?(y/n)\n");
		input = getchar();
		if (input == 'y') {
			printf("Enter new first name:\n");
			scanf("%s", &tempname);
			strcpy(name, tempname);
			input = 'n';
		}
	}
	else if (testname) strcpy(name, testname);

	if (!testchangelastname){
		fflush(stdin);
		printf("Do you want to change your last name?(y/n)\n");
		input = getchar();
		if (input == 'y') {
			printf("Enter new last name:\n");
			scanf("%s", &tempsurname);
			strcpy(surname, tempsurname);
			input = 'n';
		}
	}
	else if (testlastname) strcpy(surname, testlastname);

	if (!testchangepass){
		fflush(stdin);
		printf("Do you want to change your password?(y/n)\n");
		input = getchar();
		if (input == 'y') {
			printf("Enter new password:\n");
			scanf("%s", &tempPass);
			passCorrectness = CheckPassword(tempPass);
			if (passCorrectness)
				strcpy(password, tempPass);
			else Output("Password is invalid, Keeping old password");
			input = 'n';
		}
	}
	else if (testpass){
		passCorrectness = CheckPassword(testpass);
		if (passCorrectness)
			strcpy(password, testpass);
	}


	if (!testname && !testpass && !testlastname) Output("Done!\n");
}


//////////////////////////////////// Johnatan func's end


// add message to file
void printLogToFile(char file[], char msg[500])
{
	FILE *fp = fopen(file, "a");
	if (fp!=NULL)
	{
		fprintf(fp, "%s\n", msg);
		fclose(fp);
	}
}
////////////		Project create functions
// add new project to student's array of Project ID's, done, ready for testing
void AddProjectIDToStudent(Student * Student, int ProjectID)
{
	int ProjectIDSNewSize,index;
	int* newArrayIDs;	//create new increased array

	ProjectIDSNewSize = Student->StudentProjectsAmount + 1;
	newArrayIDs = (int*)malloc(ProjectIDSNewSize * sizeof(int));

	for (index = 0; index < ProjectIDSNewSize - 1; index++)
		newArrayIDs[index] = Student->ProjectIDS[index];			// copy old values
	newArrayIDs[index] = ProjectID;					// add new project id to last index of nea array

	free(Student->ProjectIDS);											// free old array memory
	Student->ProjectIDS = newArrayIDs;									// set new array pointer to student
	Student->StudentProjectsAmount++;								// update size of projects amount to watcher
}
// add new project to watcher's array of Project ID's, done, ready for testing
void AddProjectIDToWatcher(Watcher * Watcher, int ProjectID)
{
	int ProjectIDSNewSize, index;
	int* newArrayIDs;	//create new increased array

	ProjectIDSNewSize = Watcher->WatcherProjectsAmount + 1;
	newArrayIDs = (int*)malloc(ProjectIDSNewSize * sizeof(int));

	for (index = 0; index < ProjectIDSNewSize - 1; index++)
		newArrayIDs[index] = Watcher->ProjectIDS[index];			// copy old values
	newArrayIDs[index] = ProjectID;					// add new project id to last index of nea array

	free(Watcher->ProjectIDS);											// free old array memory
	Watcher->ProjectIDS = newArrayIDs;									// set new array pointer to student
	Watcher->WatcherProjectsAmount++;								// update size of projects amount to watcher
}
// 46 - Create new project by STUDENT or WATCHER only, UNDONE, should to split
int CreateNewProject(Global* GlobalFile,int userID, AccessGroup userGroup,char* projectName)
{
	Student *Student=NULL;
	Watcher *Watcher=NULL;
	FILE *file = NULL;
	char buffer[128];
	char logText[500];
	if (projectName) strcpy(buffer, projectName); //For tests
	else{
		puts("Input Name of your project (maximum 127 characters) : ");
		fflush(stdin);
		gets(buffer);
	}

	// check if student or watcher and get pointer to him
	if (userGroup == STUDENT){	
		Student = FindStudent(GlobalFile->StudentList, userID);
		if (!Student) return 0;
	}

	else if (userGroup == WATCHER){
		Watcher = FindWatcher(GlobalFile->WatchersList, userID);
		if (!Watcher) return 0;
	}
	else
	{
		if (!projectName) puts("Incorrect access group received.");
		return 0;		// incorrect access group
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
	sprintf(MessagesFileName, "%d_ProjectMessages.txt", newProject->ProjectID);
	FILE *ProjMsgs = fopen(MessagesFileName, "w");
	fclose(ProjMsgs);
	strcpy(newProject->ProjectMessages, MessagesFileName);

	// add new project to list of projects Global
	GlobalFile->ProjectsList = AddProject(GlobalFile->ProjectsList, newProject); 

	//add id of new project to creator
	if (userGroup == STUDENT)			// add project ID to student 
		AddProjectIDToStudent(Student, newProject->ProjectID);

	else if (userGroup == WATCHER)			// add project ID to Watcher's array
		AddProjectIDToWatcher(Watcher, newProject->ProjectID);


	// print log to project activity file

	sprintf(logText, "%s created this project with id [%d]\n", newProject->ProjectCreatorName,newProject->ProjectID);
	printLogToFile(newProject->ProjectActivityLogs, logText);

	//---------------------

	// print log to student activity file
	if (Student)
	{
		sprintf(logText, "Created project \" %s \" with id [%d]\n", newProject->ProjectName, newProject->ProjectID);
		printLogToFile(Student->StudentActivityLog, logText);

	}
	//---------------------
	if (projectName) return 1; //For Tests
	char choice;
	printf("Project \"%s\" created!\nWant to add collaborators to this project? (y / n) :", newProject->ProjectName);
	fflush(stdin);
	choice = getchar();
	switch (choice)
	{
	case 'y':
		addUserToProject(GlobalFile, newProject,0,0);
		break;
	case 'n':
		puts("Ok!");
		break;
	default:
		puts("Incorrect Symbol inputed");
		break;
	}
	puts("1 .Return to previous menu");
	puts("2. Exit Mesimaster");
	fflush(stdin);
	choice = getchar();
	if (choice == '1')
		return 0; //returns to menu
	else if (choice == '2')
		Exit(GlobalFile);			// check correct choice
	else
		puts("Incorrect input, you will be returned to Menu");

	system("pause");
	return newProject->ProjectID;

}
//////////			Project create funcs end

// 42 - Add user to project  , done, ready for testing
int addUserToProject(Global *GlobalFile, Project *newProject , int userID , int watcherOrStudent)
{	
	BOOL flag = TRUE;
	FILE *file = NULL;
	Student *student=NULL;
	Watcher *watcher= NULL;
	char choice;
	int   i, ProjectUsersIDNewSize, ID;
	int *UsersID;	//create new increased array

	//First making sure user is not already in project:

	while (flag)
	{
		if (!userID){
			puts("1. Add Student ID");
			puts("2. Add Watcher ID");
			puts("3. Return to main menu");
			fflush(stdin);
			choice = getchar();
		}
		else { 
			choice = watcherOrStudent + '0';
			ID = userID;
		}

		switch (choice)
		{
		case '1':
			if (!userID){
				fflush(stdin);
				printf("\nStudent ID :");
				scanf("%d", &ID);
			}
			for (i = 0; i < newProject->ProjectUsersAmount; i++) if (newProject->StudentsIDS[i] == ID){

				//fclose(file);
				if(!userID) Output("User already in project");
				return 0;
			}
			student = FindStudent(GlobalFile->StudentList, ID);
			if (student)	// student found
			{
				/// add project to student 
				AddProjectIDToStudent(student, newProject->ProjectID);
				if (!userID) printf("\nStudent with ID : %d was added to project!\n", ID);
				file = fopen(newProject->ProjectActivityLogs, "a");
				fprintf(file,"Student with ID : %d was added to project!\n", ID);
				fclose(file);
				
				// add student to project
				ProjectUsersIDNewSize = newProject->ProjectUsersAmount + 1;
				UsersID = (int*)malloc(ProjectUsersIDNewSize*sizeof(int));
				for (i = 0; i < ProjectUsersIDNewSize - 1; i++)
					UsersID[i] = newProject->StudentsIDS[i];
				UsersID[i] = ID;
				student->StudentTasksAmount += newProject->ProjectTasksAmount;
				newProject->StudentsIDS = UsersID;
				newProject->ProjectUsersAmount++;
				return 1;
			}
			else{
				if (!userID) Output("Student ID not found.");
				return 0;
			}
			break;

		case '2':
			if (!userID){
				fflush(stdin);
				printf("\nWatcher ID :");
				scanf("%d", &ID);
			}
			for (i = 0; i < newProject->ProjectUsersAmount; i++) if (newProject->StudentsIDS[i] == ID){

				//fclose(file);
				if(!userID)Output("User already in project");
				return 0;
			}
			watcher = FindWatcher(GlobalFile->WatchersList, ID);
			if (watcher)	// watcher found
			{
				/// add project to watcher 
				AddProjectIDToWatcher(watcher, newProject->ProjectID);

				if (!userID) printf("\nWatcher with ID : %d was added to project!\n", ID);
				file = fopen(newProject->ProjectActivityLogs, "a");
				fprintf(file,"Watcher with ID : %d was added to project!\n", ID);
				fclose(file);
				// add watcher to project
				ProjectUsersIDNewSize = newProject->ProjectUsersAmount + 1;
				UsersID = (int*)malloc(ProjectUsersIDNewSize*sizeof(int));
				for (i = 0; i < ProjectUsersIDNewSize - 1; i++)
					UsersID[i] = newProject->StudentsIDS[i];
				UsersID[i] = ID;
				newProject->ProjectUsersAmount++;
				newProject->StudentsIDS = UsersID;
				return 1;
			}
			else{
				if (!userID) puts("Watcher ID not found. Try again.");
				return 0;
			}
			break;
		case '3':
			if (!userID )Output("Choosen to return back");
			flag = FALSE;
			break;
		default:
			if (!userID) puts("Incorrect choice. Try again.");
			break;
		}

	}

	return 1;
}

// Add id of new task to array in project
void AddTaskIDToProject(Project* project, int TaskID)
{
	int TaskIDSNewSize, index;
	int* newArrayIDs;	//create new increased array

	TaskIDSNewSize = project->ProjectTasksAmount + 1;
	newArrayIDs = (int*)malloc(TaskIDSNewSize * sizeof(int));

	for (index = 0; index < TaskIDSNewSize - 1; index++)
		newArrayIDs[index] = project->TasksIDS[index];			// copy old values
	newArrayIDs[index] = TaskID;					// add new project id to last index of nea array

	free(project->TasksIDS);											// free old array memory
	project->TasksIDS = newArrayIDs;									// set new array pointer to student
	project->ProjectTasksAmount = TaskIDSNewSize;
}

// 53 - create new task from project menu, done, ready for testing
int CreateNewTask(Global *GlobalFile, Project *project,int UserID,AccessGroup group,char* taskName)
{
	Student *student = NULL;
	Watcher *watcher = NULL;
	char log[300];
	Task *newTask = (Task*)malloc(sizeof(Task));	//new task pointer

	newTask->TaskID = GlobalFile->TaskRunID;		// set Task Run ID
	if (taskName) strcpy(newTask->TaskName, taskName);
	else{
		fflush(stdin);
		puts("Enter your task (up to 255 chars) :");
		gets(newTask->TaskName);
	}

	if (group == STUDENT){
		student = FindStudent(GlobalFile->StudentList, UserID);
		if (!student) return 0;
	}
	
	else if (group == WATCHER){
		watcher = FindWatcher(GlobalFile->WatchersList, UserID);
		if (!watcher) return 0;
	}

	else
	{
		puts("Incorrect access group");
		return 0;
	}

	if (group == STUDENT && student)
	{
		strcpy(newTask->TaskCreatorName, student->StudentName);			// copy creator name to task
		// add log to student
		sprintf(log, "%s created task : %s\n", student->StudentUsername, newTask->TaskName);
		printLogToFile(student->StudentActivityLog, log);
	}
	else if (group == WATCHER && watcher)
		strcpy(newTask->TaskCreatorName, watcher->WatcherName);			// copy creator name to task
	newTask->TaskStatus = NEW;								// initialize status
	int i;
	for (i = 0; i < project->ProjectUsersAmount; i++)
		if (FindAccessGroup(project->StudentsIDS[i]) == STUDENT)
			if (FindStudent(GlobalFile->StudentList, project->StudentsIDS[i]) != NULL)
				FindStudent(GlobalFile->StudentList, project->StudentsIDS[i])->StudentTasksAmount++;
	// add ID of new task to array TasksIDs in project
	AddTaskIDToProject(project, newTask->TaskID);
	GlobalFile->TaskRunID++;						// increase run id by 1
	// add new task to global list of Tasks
	GlobalFile->TaskList = AddTask(GlobalFile->TaskList, newTask);
	printf("%s created task \"%s\"\n",newTask->TaskCreatorName, newTask->TaskName);

	// add creation of task to project log
	printLogToFile(project->ProjectActivityLogs, log);
	if (!taskName){
	// switch flag for watcher subscribes
	if (project->ProgramChanges == FALSE)
		project->ProgramChanges = TRUE;
	system("pause");
	}

	project->ProjectTasksAmount++;
	return newTask->TaskID;
}

// print list of projects with details in which user is collaborator - for students, done, ready for testing
void PrintProjectsList(Global *GlobalFile, int UserID, AccessGroup group)
{
	int i;
	Student* student=NULL;
	Watcher *watcher = NULL;
	Admin *admin = NULL;
	Project *current = NULL;
	int* projectIDs = NULL;
	int amount = 0;
	int adminFlag = 0;
	//int *ProjectsIDS;

	if (GlobalFile->ProjectsList == NULL)
	{
		Output("No Projects in database");
		return;
	}

	switch (group){
	case STUDENT:
		student = FindStudent(GlobalFile->StudentList, UserID);
		if (!student) return ;
		if (!(amount = student->StudentProjectsAmount)) { 
			Output("Student has no projects");
			return;
		}
		projectIDs = student->ProjectIDS;
		break;

	case ADMIN:
		admin = FindAdmin(GlobalFile->AdminsList, UserID);
		if (!admin) return ;
		adminFlag = 1;
		current = GlobalFile->ProjectsList;
		break;

	case WATCHER:
		watcher = FindWatcher(GlobalFile->WatchersList, UserID);
		if (!(amount = watcher->WatcherProjectsAmount)) {
			Output("Watcher has no projects");
			return;
		}
		projectIDs = watcher->ProjectIDS;
		if (!watcher) return ;

	default:
		//Not a valid accessgroup:
		Output("Incorrect Access Group");
		return;
	}

	puts("List of your projects:");
	printf("%-10s%-25s%-10s%-10s\n","ID","Name","Users","Tasks");
	if (adminFlag){
		while (current != NULL){
			printf("%-10d%-25s%-10d%-10d\n",
				current->ProjectID,
				current->ProjectName,
				current->ProjectUsersAmount,
				current->ProjectTasksAmount);
			current = current->ProjectNext;
			printf("\n");
		}
	}
	else{
		for (i = 0; i < amount; i++){
			current = FindProject(GlobalFile->ProjectsList, projectIDs[i]);
			printf("%-10d%-25s%-10d%-10d\n",
				current->ProjectID,
				current->ProjectName,
				current->ProjectUsersAmount,
				current->ProjectTasksAmount);
			printf("\n");

		}
	}
	Output("");
	return;
}

// print users list by ID array in project, done,ready fro testing
void PrintUsersByID(Global *GlobalFile, Project *project)
{
	int i;
	Student *student = NULL;
	puts("Collaborators in project:");
	printf("-------------------\n");
	if (project->ProjectUsersAmount == 0)
		puts("No users added.");
	printf("%-20s%-20s%-20s%-20s%-25s\n","Username","Name","Surename","Department","Email");
	for (i = 0; i < project->ProjectUsersAmount; i++)
	{
		student = FindStudent(GlobalFile->StudentList, project->StudentsIDS[i]);
		if (student)
			printf("%-20s%-20s%-20s%-20s%-25s\n", student->StudentUsername, student->StudentName, student->StudentSurename, student->StudentDepartment, student->StudentEmail);
	}
}

// print list of projects with details in which watcher is watching, done, ready for testing
void PrintProjectsListWatcher(Global *GlobalFile, int UserID, AccessGroup group)
{
	int i;
	Student* student = NULL;
	Watcher *watcher = NULL;
	Project *current = NULL;
	int *ProjectsIDS;

	if (GlobalFile->ProjectsList == NULL)
	{
		Output("No Projects in database");
		return;
	}

	// in case of watcher
	if (group == WATCHER)
	{
		watcher = FindWatcher(GlobalFile->WatchersList, UserID);
		ProjectsIDS = watcher->ProjectIDS;
		if (watcher->WatcherProjectsAmount == 0)
		{
			Output("Watcher not in any project");
			return;
		}

		int arraySize = watcher->WatcherProjectsAmount;
		puts("List of your projects :");
		printf("%-10s%-20s%-10s%-10s\n","ID","Name","Users","Tasks");
		for (i = 0; i < arraySize; i++) 
		{
			current = FindProject(GlobalFile->ProjectsList, watcher->ProjectIDS[i]);
			if (current)
			{
				printf("%-10d%-20s%-10d%-10d\n", current->ProjectID, current->ProjectName, current->ProjectUsersAmount, current->ProjectTasksAmount);
				PrintUsersByID(GlobalFile, current);				
			}
		}
	}
	else
	{
		Output("Incorrect access group");
		return;
	}

	Output("\n");
}

// print activity log of student in project, receive student, done, ready for testing
void PrintStudentLog(Student* student){
	char BUFFER[400], *fileName = student->StudentActivityLog;
	FILE* file = fopen(fileName, "r");
	if (!file)
		printf("%s Log file not found or you have not create any log yet", student->StudentActivityLog);

	else
	{
		while (fgets(BUFFER, 400, file)) 
			printf("%s\n", BUFFER);
		fclose(file);
	}
	system("pause");
}

// allow watcher to choose student id in project, and print all his activity in it
void PrintStudentActivityWatcher(Global *GlobalFile, Project *project)
{
	int selectID;
	char buffer[400];
	puts("Students in this project:");
	PrintUsersByID(GlobalFile, project);

	printf("Input student ID to print log :");
	fflush(stdin);
	scanf("%d", &selectID);
	Student *student = FindStudent(GlobalFile->StudentList, selectID);
	
	// find student, scan project log file, compara student username with string, if student make this log line, print log line
	if (student)
	{
		FILE *file = fopen(project->ProjectActivityLogs, "r");
		if (file)
		{
			while (!feof(file))
			{
				fgets(buffer, 400, file);
				if (strstr(buffer, student->StudentUsername))		// find username in line of log
					puts(buffer);
			}
		}
		else
			puts("Log file not found (No actions been performed in it)");
	}
	else
		puts("Student with ID not found!");

	system("pause");
}

// print global message from admin, done, ready for testing
void PrintGlobalMessages(Global *GlobalFile)
{
	if (strcmp(GlobalFile->GlobalMessages, "EMPTY") != 0)
	{
		puts("\n*** System message ***");
		puts(GlobalFile->GlobalMessages);
		puts("\n**********************");
	}
	
}

// add message by admin, done, ready for etsting
void AddGlobalMessage(Global* GlobalFile, char* msg){
	char temp[250];
	if (strcmp(msg, "") == 0){
		printf("Enter global message (max length 255):\n");
		fflush(stdin);
		do{
			gets(temp);
		} while (strlen(temp) > 255);
		strcpy(GlobalFile->GlobalMessages, temp);
	}
	else{
		strcpy(GlobalFile->GlobalMessages, msg);
		return;
	}
	printf("Global message added!\n");
	system("pause");
}

// Quotes funcs start, done, ready to testing
void AddNewQuote(Global* GlobalFile, char* quote, char* creator){
	char tempQuote[300], tempAuthor[100];
	//Creating a new quote and incrementing quoteRunID: Not sure if that's right
	int quoteID = GlobalFile->QuoteRunID++;
	Quote* newQuote = (Quote*) malloc(sizeof(Quote));
	newQuote->QuoteID = quoteID;
	if (strcmp(quote, "") == 0){
		printf("Enter quote (max length 256):\n");
		do
		{
			fflush(stdin);
			scanf("%s", &tempQuote);
		} while (strlen(tempQuote) > 255);

		strcpy(newQuote->Quote, tempQuote);

		printf("Enter quote's author (max length 30):\n");
		do
		{
			fflush(stdin);
			scanf("%s", &tempAuthor);
		} while (strlen(tempQuote) > 30);

		strcpy(newQuote->QuoteAuthor, tempAuthor);
	}
	else{
		strcpy(newQuote->Quote, quote);
		strcpy(newQuote->QuoteAuthor, creator);
	}
	//Adding to global quote list:
	AddQuote(GlobalFile->QuotesList, newQuote);
}
void PrintQuotes(Global* GlobalFile){
	Quote* quote = GlobalFile->QuotesList;
	int i = 1;
	puts("Quotes in Database:");
	while (quote != NULL){

		printf("%d) \"%s\"\t,Author: %s\n", i, quote->Quote, quote->QuoteAuthor);
		quote = quote->QuoteNext;
		i++;
	}
	puts("");

	system("pause");
}
void DeleteQuote(Global* GlobalFile, int ID)
{
	Quote *quote = NULL;
	BOOL flag = TRUE;
	if (!ID){
		fflush(stdin);
		printf("Input Quote ID to delete : ");
		scanf("%d", &ID);
	}
	else
		flag = FALSE;
	quote = FindQuote(GlobalFile->QuotesList, ID);
	if (quote)
	{
		GlobalFile->QuotesList = RemoveQuoteFromList(GlobalFile->QuotesList, ID);
		printf("Quote with id : %d found and deleted.\n", ID);
	}
	else
		puts("ID not found in database");
	if (flag == FALSE)
		return;
	system("pause");
}
void ManageQuotes(Global *GlobalFile)
{
	char choice;

	BOOL flag = TRUE;
	
	while (flag)
	{
		puts("1. Print all Quotes in database");
		puts("2. Add new Quote");
		puts("3. Remove quote by ID");
		puts("4. Back to previous menu");
		fflush(stdin);
		printf("Choice : ");
		choice = getchar();
		if (choice == '1')
			PrintQuotes(GlobalFile);
		else if (choice == '2')
			AddNewQuote(GlobalFile, "", "");
		else if (choice == '3')
			DeleteQuote(GlobalFile, 0);
		else if (choice == '4')
			flag=FALSE;
		else
			puts("Incorrect choice");
	}
	system("pause");
}
// quotes funcs end


// prints all users in system, for admin, done, ready for testing
void PrintUsersLists(Global* GlobalFile)
{
	puts("Admins :");
	PrintAdminsList(GlobalFile->AdminsList);
	puts("");
	puts("Students :");
	PrintStudentList(GlobalFile->StudentList);
	puts("");
	puts("Watchers :");
	PrintWatcherList(GlobalFile->WatchersList);
	puts("");
}

// print all tasks with ID's from received array, done, ready for testing
void PrintTasksByID(Task *head, int indexes[], int size, char *creator)
{
	Task *current = NULL;
	int i,CreatedTasks=0;
	if (size == 0)
	{
		puts("No Tasks in this project");
		return;
	}
	printf("ID\tStatus\t\tTask\n");
	for (i = 0; i < size; i++)
	{
		current = FindTask(head, indexes[i]);
		if (current && strcmp(current->TaskCreatorName, creator) == 0)
		{
				char *status = convertStatusToString(current->TaskStatus);
				printf("%d\t%s\t%s\n", current->TaskID, status, current->TaskName);
				CreatedTasks++;
		}	
	}
	if (CreatedTasks == 0)
		puts("User not created any task in this project");
}

// print projects by ID's array, done, ready for testing
void PrintProjectsByID(Global *GlobalFile, int indexes[],int size,char *creator)
{
	Project *head = GlobalFile->ProjectsList;
	Project *current = NULL;
	int i;
	if (size == 0)
	{
		puts("No Projects");
		return;
	}
	for (i = 0; i < size; i++)
	{
		current = FindProject(head, indexes[i]);
		if (current)
		{
			printf("ID: %d, Name: %s, Tasks : %d\n\nTasks in this Project :\n", current->ProjectID, current->ProjectName, current->ProjectTasksAmount);
			PrintTasksByID(GlobalFile->TaskList, current->TasksIDS, current->ProjectTasksAmount,creator);
		}
	}
}

// print all users in system, gives option to chooce user for more information, done, ready for testing
void ShowUserDetails(Global *GlobalFile)
{
	Student * student = NULL;
	Watcher *watcher = NULL;
	Admin *admin = NULL;
	PrintUsersLists(GlobalFile);
	
	char choice;
	int ID;
	printf("Input ID to see full details of user : ");
	fflush(stdin);
	scanf("%d",&ID);
	if (ID < 1000 || ID >= 4000){
		Output("incorrect ID , correct range 1000-3999");
		return;
	}
	else if (ID >= 1000 && ID <= 1999)
	{
		student = FindStudent(GlobalFile->StudentList, ID);
		if (student)
		{
			printf("User data for user with ID %d",ID);
			printf("\nUsername : %s\nName : %s\nSurename : %s\nEmail : %s\nDepartment :%s\n", student->StudentUsername, student->StudentName, student->StudentSurename, student->StudentEmail, student->StudentDepartment);
			puts("--------------\nCollaborator at Projects:");
			PrintProjectsByID(GlobalFile, student->ProjectIDS,student->StudentProjectsAmount,student->StudentName);
			
		}
		else{
			Output("Student with this id not found");
			return;
		}

	}
	else if (ID >= 2000 && ID <= 2999)
	{
		admin = FindAdmin(GlobalFile->AdminsList, ID);
		if (admin)
		{
			printf("User data for user with ID %d", ID);
			printf("\nUsername : %s\nPassword :%s\nName : %s\n%Surename\n\n", admin->AdminUsername, admin->AdminPassword, admin->AdminName, admin->AdminSurename);
		}
		else{
			Output("Admin with this ID not found");
			return;
		}

	}
	else if (ID >= 3000 && ID <= 3999)
	{
		watcher = FindWatcher(GlobalFile->WatchersList, ID);
		if (watcher)
		{
			printf("User data for user with ID %d\n", ID);
			printf("Username : %s\nPassword :%s\nName : %s\n%Surename\nEmail : %s\nProjects Amount : %d\n\n", watcher->WatcherUsername, watcher->WatcherPassword, watcher->WatcherName, watcher->WatcherSurename, watcher->WatcherProjectsAmount);
		}
		else{
			Output("Watcher with this ID not found");
			return;
		}
	}
	Output("");
	//THIS INDUCES BUGS, REMOVING IT FOR NOW.. JONATHAN
	//printf("Return to previous menu ( Y / N for Exit ) :");
	//fflush(stdin);
	//scanf("%c", &choice);
	//if (choice == 'Y' || choice == 'y')
	//	return;
	//else if (choice == 'N' || choice == 'n')
	//	Exit(GlobalFile);											//////// check correct option for this
	//else
	//	puts("Incorrect choice, returning to previous menu");
}



//receive id and project, remove user ID from array of USersIDs and update array, done, ready for testing
int *RemoveUserIDFromProject(Project* project, int ID)
{
	int *UsersIDs = (int*)malloc((project->ProjectUsersAmount - 1) * sizeof(int)),i,newindex=0;
	
	for (i = 0; i < project->ProjectUsersAmount; i++,newindex++)
	{
		if (project->StudentsIDS[i] != ID)
			UsersIDs[newindex] = project->StudentsIDS[i];
		else
			newindex--;
	}

	return UsersIDs;
}

// receive user id, run over all projects, if user in project, remove it from array, and decrease amount of users in project, done, ready for testing
void RemoveUserFromProjects(Global *GlobalFile, int UserID)
{
	Project *current = GlobalFile->ProjectsList;
	int i;
	while (current)
	{
		for (i = 0; i < current->ProjectUsersAmount; i++)
		{
			if (current->StudentsIDS[i] == UserID)
			{
				current->StudentsIDS = RemoveUserIDFromProject(current, UserID);
				current->ProjectUsersAmount--;
			}
		}
		current = current->ProjectNext;
	}

}

// print all users in database for admin, admin chooce user id for delete, done, ready for testing
int DeleteUser(Global *GlobalFile, int id)
{
	int ID;
	AccessGroup group;
	Student *student = NULL;
	Watcher *watcher = NULL;
	Admin *admin = NULL;
	BOOL flag = TRUE;
	char choice;
	if (!id){
		puts("List of all users in system :\n-----------------------");
		PrintUsersLists(GlobalFile);
	}
	while (flag)
	{
		if (!id){
			printf("Enter ID of user you want to remove: ");
			fflush(stdin);
			scanf("%d", &ID);
		}
		else
		{
			ID = id;
			flag = FALSE;
		}
		group = FindAccessGroup(ID);
		switch (group)
		{
		case WATCHER:
			watcher = FindWatcher(GlobalFile->WatchersList, ID);
			if (watcher)
			{
				GlobalFile->WatchersList = RemoveWatcherFromList(GlobalFile->WatchersList, ID);
				RemoveUserFromProjects(GlobalFile, ID);
			}
			else{
				if (flag) {
					Output("Watcher not found in database");
				}
				return 0;

			}
			break;
		case STUDENT:
			student = FindStudent(GlobalFile->StudentList, ID);
			if (student)
			{
				GlobalFile->StudentList = RemoveStudentFromList(GlobalFile->StudentList, ID);
				RemoveUserFromProjects(GlobalFile, ID);
			}
			else{
				if (flag) {
					Output("Student not found in database");
				}
				return 0;
			}
			break;
		case ADMIN:
			Output("Admin cannot be deleted");
			return 0;
		/*	admin = FindAdmin(GlobalFile->AdminsList, ID);
			if (admin)
				GlobalFile->AdminsList = RemoveAdminFromList(GlobalFile->AdminsList, ID);
			else{
				if (flag) {
					Output("Admin not found in database"); 
				}
				return 0;
			}
			break;*/

		default:
			if (flag){
				Output("Error : No such user group");
			}
			return 0;
		}
		if (flag == FALSE)
			return 0 ;
		printf("Want to delete another user? ( Y/ N ) :");
		_flushall();
		choice = getchar();
		if (choice != 'y' && choice != 'Y')
			flag = FALSE;
	}


	Output("User(s) successfuly deleted");
	return 1;
}

// promote Student to be Admin
Admin *StudentToAdmin(Global *GlobalFile, Student *student)
{
	Admin *newAdmin = (Admin*)malloc(sizeof(Admin));
	// copy fields from user to new admin
	newAdmin->AdminID = GlobalFile->AdminRunID++;
	strcpy(newAdmin ->AdminName, student->StudentName );
	strcpy(newAdmin ->AdminSurename,student->StudentSurename );
	strcpy(newAdmin ->AdminUsername,student->StudentUsername );
	strcpy(newAdmin ->AdminPassword, student->StudentPassword );
	newAdmin->AdminNext = NULL;
	newAdmin->Group = ADMIN;
	
	// delete old fields of student
	RemoveUserFromProjects(GlobalFile, student->StudentID);
	free(student->ProjectIDS);		// free array
	GlobalFile->StudentList = RemoveStudentFromList(GlobalFile->StudentList, student->StudentID);		// remove student from list 

	return newAdmin;
}
// promote Watcher to be Admin
Admin * WatcherToAdmin(Global *GlobalFile, Watcher *watcher)
{
	Admin *newAdmin = (Admin*)malloc(sizeof(Admin));
	// copy fields from user to new admin
	newAdmin->AdminID = GlobalFile->AdminRunID++;
	strcpy(newAdmin->AdminName, watcher->WatcherName);
	strcpy(newAdmin->AdminSurename, watcher->WatcherSurename);
	strcpy(newAdmin->AdminUsername, watcher->WatcherUsername);
	strcpy(newAdmin->AdminPassword, watcher->WatcherPassword);
	newAdmin->AdminNext = NULL;
	newAdmin->Group = ADMIN;

	// delete old fields of student
	RemoveUserFromProjects(GlobalFile, watcher->WatcherID);
	free(watcher->ProjectIDS);		// free array
	GlobalFile->WatchersList = RemoveWatcherFromList(GlobalFile->WatchersList, watcher->WatcherID);		// remove student from list 

	return newAdmin;
}

// promote user to Admin
void PromoteUserToAdmin(Global *GlobalFile, int ID)
{
	if (!ID){
		puts("List of all users in system :\n-----------------------");
		PrintUsersLists(GlobalFile);
	}
	char choice;
	BOOL flag = TRUE;
	Admin *admin = NULL;
	Student *student = NULL;
	Watcher *watcher = NULL;
	AccessGroup group = BAD;
	while (flag)
	{
		if (!ID){
			printf("Input ID of user, you want to promote to ADMIN group : ");
			fflush(stdin);
			scanf("%d", &ID);
		}
		else
			flag = FALSE;
		group = FindAccessGroup(ID);
		switch (group)
		{
		case BAD:
			puts("Incorrect range of ID ( 1000 - 3999 )");
			break;
		case STUDENT:
			student = FindStudent(GlobalFile->StudentList, ID);
			if (student)
			{
				AddAdmin(GlobalFile->AdminsList, StudentToAdmin(GlobalFile, student));
				puts("User been promoted to Admin");
			}
			else
				puts("Student with this id not found");
			break;
		case WATCHER:
			watcher = FindWatcher(GlobalFile->WatchersList, ID);
			if (watcher)
			{
				AddAdmin(GlobalFile->AdminsList, WatcherToAdmin(GlobalFile, watcher));
				puts("User been promoted to Admin");
			}
			else
				puts("Watcher with this id not found");
			break;
		case ADMIN:
			admin = FindAdmin(GlobalFile->AdminsList, ID);
			if (admin)
				puts("User with this ID is admin already");
			else
				puts("The ID entered isn't exist!");		
		}
		if (flag == FALSE)
			return;
		printf("Want to promote another user? ( Y/ N ) :");
		fflush(stdin);
		choice = getchar();
		if (choice == 'n' || choice == 'N')
			flag = FALSE;
		ID = 0;
	}
	system("pause");
}

//// watcher notifications
// Turns on / off watcher notifications, return true if status changed, false if not changed
BOOL ShowNotifications(Global *GlobalFile, Watcher *watcher, char choice)
{
	if (choice == 0){
		printf("\nCurrent status of Subscription : ");
		if (watcher->WatcherReceiveChanges == FALSE)
			puts("OFF");
		if (watcher->WatcherReceiveChanges == TRUE)
			puts("ON");
		printf("\nChange status? ( Y/N ) : ");
		fflush(stdin);
		choice = getchar();
		if (choice == 'y' || choice == 'Y')
		{
			watcher->WatcherReceiveChanges = TRUE;
			Output("New status : ON");
			return TRUE;
		}
		else if (choice == 'n' || choice == 'N')
		{
			watcher->WatcherReceiveChanges = FALSE;
			Output("New status : OFF");
			return TRUE;
		}
		Output("Incorrect choice, status not been changed");
		return FALSE;
	}
	else{
		if (choice == 'y' || choice == 'Y'){
			watcher->WatcherReceiveChanges = TRUE;
			return TRUE;
		}
		else if (choice == 'n' || choice == 'N'){
			watcher->WatcherReceiveChanges = FALSE;
			return FALSE;
		}
	}
	return FALSE;
}

// print changes in project to watcher, done,ready for testing
void PrintProjectChanges(Global *GlobalFile, Project* project, Watcher *watcher){
	if (!watcher) return;
	if (watcher->WatcherReceiveChanges == TRUE)
	{
		puts("Last changes in this project : ");
		PrintActivityLog(project->ProjectActivityLogs);
	}
}
//// watcher notifications end

// show messages from watcher to student, done, ready for testing
void ShowMessagesToStudent(Global * Global, Student *student)
{

	FILE *file = fopen(student->StudentMessages, "r");
	char username[31], message[31];
	if (file)
	{
		puts("You have one or more messages from watchers");
		while (!feof(file))
		{
			fscanf(file,"%s %s", &username, &message);
			printf("User : %s, Message :%s", &username, &message);
		}
		fclose(file);
	}
	else
	{
		puts("Your Messages file cannot be opened or you have not new messages");
	}

	// once messages been printed to student, delete old file by creating new empty one
	remove(student->StudentMessages);

	Output("");
}


// function to print project messages to team,
void PrintProjectMessages(Project *project)
{
	puts("-------------------\nWatcher message/s for project team :");
	PrintActivityLog(project->ProjectMessages);
	puts("\n-------------------");
}

// print all tasks in watchers projects
void ShowTasksByWatcher(Global* GlobalFile, int WatcherID){
	int tasksCount = 0, i, j, status = -1, projectID, taskID;
	Watcher* watcher = FindWatcher(GlobalFile->WatchersList, WatcherID);
	Project* project=NULL;
	Task* task=NULL;
	int* projectIDs = watcher->ProjectIDS;

	printf("All tasks in projects you are watching on:\n");

	//Finding all the projects this student belongs to and printing the tasks:
	for (i = 0; i < watcher->WatcherProjectsAmount; i++)
	{
		projectID = projectIDs[i];
		project = FindProject(GlobalFile->ProjectsList, projectID);
		if (project)
		{
			for (j = 0; j < project->ProjectTasksAmount; j++)
			{
				taskID = project->TasksIDS[j];
				task = findTaskInProject(GlobalFile, project, taskID);
				if (task && task->TaskStatus != TRASH)
				{
					printf("ID: %d , Creator: %s , Task: %s, Status : %s\n", task->TaskID, task->TaskCreatorName, task->TaskName,
						convertStatusToString(task->TaskStatus));
					tasksCount++;
				}
			}
		}
	}
	if (tasksCount == 0)
		puts("Not found tasks in your projects");

	system("pause");

}

// register new admin in system
int AdminRegister(Global *GlobalFile,char* nameTest, char* surnameTest , char* unTest, char* passTest)
{
	Admin* newAdmin = NULL;
	int choice = 0;
	newAdmin = (Admin*)malloc(sizeof(Admin));													//Allocating memory for the new watcher

	if (newAdmin == NULL)                                                                         //Allocation check
	{
		if (!nameTest) printf("Error allocating memory for the new Admin.\n");
		return 0;
	}
	newAdmin->AdminID = GlobalFile->AdminRunID;														//Id allocation

	do{			
		//Initializing username
		if (!nameTest){
			_flushall();
			printf("Enter your desired username: (Has to be less then 30 characters!)\n");
			scanf("%s", newAdmin->AdminUsername);
			getchar();
		}
		else strcpy(newAdmin->AdminUsername, unTest); //For tests

		if (CheckIfUserExists(GlobalFile, newAdmin->AdminUsername) == TRUE)
		{
			if (!nameTest) {
				printf("This username already exists in the system. \n Press 1 to try again, press 2 to go back to the next menu.\n");
				scanf("%d", &choice);
			}
			else return 0;//For tests
		}
	} while (CheckIfUserExists(GlobalFile, newAdmin->AdminUsername) == TRUE && choice == 1);

	if (choice != 1 && choice != 0)
	{
		if (!nameTest)printf("You did not press 1 to continue. Going back to last menu.\n");
		free(newAdmin);
		return 0;
	}
	//Initializing password
	do{
		if (!nameTest){
			_flushall();
			printf("Enter your desired password: (Has to be less then 30 characters, and contain\n");
			printf("at least one digit, one upper case letter, one lower case letter)\n");
			scanf("%s", newAdmin->AdminPassword);
		}
		else strcpy(newAdmin->AdminPassword, passTest);//For tests

		if (CheckPassword(newAdmin->AdminPassword) == FALSE)
		{
			if (!nameTest)printf("This password is invalid.\n You need to try again.\n");
			else return 0;
		}
	} while (CheckPassword(newAdmin->AdminPassword) == FALSE);
	//Initializing other attributes that require user input
	if (!nameTest) {
		printf("Enter your first name: (Has to be less then 20 characters!)\n");
		scanf("%s", newAdmin->AdminName);
		printf("Enter your last name: (Has to be less then 20 chatacters!)\n");
		scanf("%s", newAdmin->AdminSurename);
	}
	else{
		//For tests:
		strcpy(newAdmin->AdminName, nameTest);
		strcpy(newAdmin->AdminSurename, surnameTest);
	}
	newAdmin->Group = ADMIN;

	GlobalFile->AdminsList = AddAdmin(GlobalFile->AdminsList, newAdmin);	// add to AdminsList
	(GlobalFile->AdminRunID)++;

	if (!nameTest)system("pause");
	return newAdmin->AdminID;
}

// Allow Admin to add new user, done,ready for testing
int AddNewUser(Global *GlobalFile)
{
	int choice;
	puts("You choosed to register new user :");
	//Action menu - choosing user type or action (student, watcher, back)
	do{
		printf("Choose a user type:\n\t[1] Student\n\t[2] Watcher\n\t[3] Admin\n\t[4] Back to last menu\n");
		scanf("%d", &choice);
	} while (choice != 1 && choice != 2 && choice != 3 && choice != 4);

	if (choice == 1)                                                                                //Executing student registration
	{
		return StudentRegister(GlobalFile,NULL,NULL,NULL,NULL,NULL,NULL,'0');
	}
	else if (choice == 2)																			//Executing watcher registration
	{
		return WatcherRegister(GlobalFile,NULL,NULL,NULL,NULL,NULL);
	}
	else if (choice == 3)
	{
		return AdminRegister(GlobalFile,NULL,NULL,NULL,NULL);
	}
	else
	{	//Back to last menu
		return 0;
	}


}


// HELP FUNCTIONS

//The function verifies whether the given password is valid.
//A valid password is one that contains: at least 1 digit, 1 uppercase letter, 1 lowercase letter.
BOOL CheckPassword(char* pass)
{
	BOOL lowerFlag = FALSE, upperFlag = FALSE, digitFlag = FALSE;
	int i, size = strlen(pass);
	for (i = 0; i < size; i++)
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
// help functions, check if user exists in system by username
BOOL CheckIfUserExists(Global *g, char *username)
{
	Student *tempStud = g->StudentList;
	Watcher *tempWatch = g->WatchersList;
	Admin *tempAdm = g->AdminsList;
	while (tempStud != NULL)																		//Checking if the username exists in the student list																																
	{
		if (strcmp(tempStud->StudentUsername, username) == 0)
		{
			return TRUE;
		}
		tempStud = tempStud->StudentNext;
	}
	while (tempWatch != NULL)														                //Checking if the username exists in the watcher list
	{
		if (strcmp(tempWatch->WatcherUsername, username) == 0)
		{
			return TRUE;
		}
		tempWatch = tempWatch->WatcherNext;
	}
	while (tempAdm != NULL)														                    //Checking if the username exists in the admins list
	{
		if (strcmp(tempAdm->AdminUsername, username) == 0)
		{
			return TRUE;
		}
		tempAdm = tempAdm->AdminNext;
	}
	return FALSE;
}

//Isabelles functions


int Register(Global *g)
{
	int choice;                                                                                     //Action menu - choosing user type or action (student, watcher, back)
	do{
		printf("Choose a user type:\n\t[1] Student\n\t[2]Watcher\n\t[3]Back to last menu\n");
		scanf("%d", &choice);
	} while (choice != 1 && choice != 2 && choice != 3);

	if (choice == 1)                                                                                //Executing student registration
	{
		return StudentRegister(g,NULL,NULL,NULL,NULL,NULL,NULL,'0');
	}
	else if (choice == 2)																			//Executing watcher registration
	{
		return WatcherRegister(g,NULL,NULL,NULL,NULL,NULL);
	}
	else
	{																								//Back to last menu
		return -1;
	}
}

int StudentRegister(Global *g,char* nameTest,char* surnameTest, char* unTest, char* passTest , char* emailTest, char* departmentTest, char yearTest)
{
	char stringID[31];
	int choice = 0;
	Student* newStudent = NULL;																		//Allocating memory for the new student
	newStudent = (Student*)malloc(sizeof(Student));

	if (newStudent == NULL)                                                                         //Allocation check
	{
		if(!nameTest)printf("Error allocating memory for the new student.\n");
		return 0;
	}

	newStudent->StudentID = g->StudentRunID;														//ID allocation

	//Initializing username
	do{
		_flushall();
		if (!nameTest){
			printf("Enter your desired username: (Has to be less then 30 characters!)\n");
			scanf("%s", newStudent->StudentUsername);
			getchar();
		}
		else strcpy(newStudent->StudentUsername, unTest);
		if (CheckIfUserExists(g, newStudent->StudentUsername) == TRUE)
		{
			if (!nameTest){
				printf("This username already exists in the system. \n Press 1 to try again, press 2 to go back to the next menu.\n");
				scanf("%d", &choice);
			}
			else return 0;
		}
	} while (CheckIfUserExists(g, newStudent->StudentUsername) == TRUE && choice == 1);

	if (choice != 1 && choice != 0)
	{
		if (!nameTest) printf("You did not press 1 to continue. Going back to last menu.\n");
		return 0;
	}
	//Initializing password
	do{
		if (!nameTest){
			_flushall();
			printf("Enter your desired password: (Has to be less then 30 characters, and contain\n");
			printf("at least one digit, one upper case letter, one lower case letter)\n");
			scanf("%s", newStudent->StudentPassword);
		} else strcpy(newStudent->StudentPassword, passTest);
		if (CheckPassword(newStudent->StudentPassword) == FALSE)
		{
			if (!nameTest)printf("This password is invalid.\n You need to try again.\n");
			else return 0;
		}
	} while (CheckPassword(newStudent->StudentPassword) == FALSE);
	//Initializing other attributes that require user input
	if (!nameTest){
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
	}
	else{
		strcpy(newStudent->StudentEmail, emailTest);
		strcpy(newStudent->StudentName, nameTest);
		strcpy(newStudent->StudentSurename, surnameTest);
		strcpy(newStudent->StudentDepartment, departmentTest);
		newStudent->StudentYear = yearTest;
	}
	//Default initializations 
	newStudent->Group = STUDENT;
	newStudent->StudentProjectsAmount = 0;
	newStudent->ProjectIDS = NULL;
	newStudent->StudentTasksAmount = 0;

	sprintf(stringID, "%d", newStudent->StudentID); //convert id num to string
	strcpy(newStudent->StudentActivityLog, stringID); //insert this num to student log string
	strcat(newStudent->StudentActivityLog, "_SLog.txt"); //cat the rest of the file name

	strcpy(newStudent->StudentMessages, stringID); //insert id string to messages string
	strcat(newStudent->StudentMessages, "_SMess.txt"); // cat the rest of the file name

	g->StudentList = AddStudent(g->StudentList, newStudent);
	(g->StudentRunID)++;
	return newStudent->StudentID;
}

int WatcherRegister(Global *g,char* nameTest, char* surnameTest, char* unTest, char* passTest, char* emailTest)
{
	Watcher* newWatcher = NULL;
	int choice = 0;
	newWatcher = (Watcher*)malloc(sizeof(Watcher));													//Allocating memory for the new watcher

	if (newWatcher == NULL)                                                                         //Allocation check
	{
		if (!nameTest) printf("Error allocating memory for the new watcher.\n");
		return 0;
	}
	newWatcher->WatcherID = g->WatcherRunID;														//Id allocation

	do{		
		//Initializing username
		if (!nameTest) {
			_flushall();
			printf("Enter your desired username: (Has to be less then 30 characters!)\n");
			scanf("%s", newWatcher->WatcherUsername);
			getchar();
		}
		else strcpy(newWatcher->WatcherUsername, unTest);
		
		if (CheckIfUserExists(g, newWatcher->WatcherUsername) == TRUE)
		{
			if (nameTest) return 0;
			printf("This username already exists in the system. \n Press 1 to try again, press 2 to go back to the last menu.\n");
			scanf("%d", &choice);
		}
	} while (CheckIfUserExists(g, newWatcher->WatcherUsername) == TRUE && choice == 1);

	if (choice != 1 && choice != 0)
	{

		if (!nameTest) printf("You did not press 1 to continue. Going back to last menu.\n");
		return 0;
	}
	//Initializing password
	do{

		if (!nameTest){
			_flushall();
			printf("Enter your desired password: (Has to be less then 30 characters, and contain\n");
			printf("at least one digit, one upper case letter, one lower case letter)\n");
			scanf("%s", newWatcher->WatcherPassword);
		}
		else strcpy(newWatcher->WatcherPassword, passTest);
		if (CheckPassword(newWatcher->WatcherPassword) == FALSE)
		{
			if (nameTest) return 0;
			printf("This password is invalid.\n You need to try again.\n");
		}
	} while (CheckPassword(newWatcher->WatcherPassword) == FALSE);
	//Initializing other attributes that require user input
	if (!nameTest){
		printf("Enter your email address: (Has to be less then 50 characters!)\n");
		scanf("%s", newWatcher->WatcherEmail);
		printf("Enter your first name: (Has to be less then 20 characters!)\n");
		scanf("%s", newWatcher->WatcherName);
		printf("Enter your last name: (Has to be less then 20 chatacters!)\n");
		scanf("%s", newWatcher->WatcherSurename);
	}
	else{
		strcpy(newWatcher->WatcherEmail, emailTest);
		strcpy(newWatcher->WatcherName, nameTest);
		strcpy(newWatcher->WatcherSurename, surnameTest);
	}



	newWatcher->Group = WATCHER;																	//Default initializations
	newWatcher->ProjectIDS = NULL;
	newWatcher->WatcherProjectsAmount = 0;
	newWatcher->WatcherReceiveChanges = FALSE;

	g->WatchersList = AddWatcher(g->WatchersList, newWatcher);
	(g->WatcherRunID)++;
	return newWatcher->WatcherID;
}

//HELP FUNCTION for Login(Global)
//Receives a username and returns a pointer to the student with that username.
Student* FindStudentByUN(Global *g, char *username)
{
	Student *tempStud = g->StudentList;
	while (tempStud != NULL)																		//Checking if the username exists in the student list																																
	{
		if (strcmp(tempStud->StudentUsername, username) == 0)
		{
			return tempStud;
		}
		tempStud = tempStud->StudentNext;
	}
	return NULL;
}

//HELP FUNCTION for Login(Global)
//Receives a username and returns a pointer to the watcher with that username.
Watcher* FindWatcherByUN(Global *g, char *username)
{
	Watcher *tempW = g->WatchersList;
	while (tempW != NULL)																		//Checking if the username exists in the student list																																
	{
		if (strcmp(tempW->WatcherUsername, username) == 0)
		{
			return tempW;
		}
		tempW = tempW->WatcherNext;
	}
	return NULL;
}

//HELP FUNCTION for Login(Global)
//Receives a username and returns a pointer to the admin with that username.
Admin* FindAdminByUN(Global *g, char *username)
{
	Admin *tempA = g->AdminsList;
	while (tempA != NULL)																		//Checking if the username exists in the student list																																
	{
		if (strcmp(tempA->AdminUsername, username) == 0)
		{
			return tempA;
		}
		tempA = tempA->AdminNext;
	}
	return NULL;
}

int Login(Global *g, char* UN, char* PW)
{
	char username[81], pass[81];
	BOOL flag = TRUE;
	if (UN != NULL && PW != NULL){
		strcpy(username, UN);
		strcpy(pass, PW);
		flag = FALSE;
	}	
	int i;
	Student *studLogin = NULL;
	Watcher *watchLogin = NULL;
	Admin *admLogin = NULL;
	if (flag == TRUE){
		printf("Please enter your username.\n");														//Entering username.
		scanf("%s", username);
	}
	//Finding this username in one of the databases.
	studLogin = FindStudentByUN(g, username);
	watchLogin = FindWatcherByUN(g, username);
	admLogin = FindAdminByUN(g, username);

	if (studLogin == NULL && watchLogin == NULL && admLogin == NULL)								//If not fount in any database - return 0.
	{
		if (flag == TRUE)
			Output("No such user in our system.\n");
		return -1;
	}

	if (studLogin)																					//User inputs a password up to 3 times.
	{																								//If the password is correct - ID returned.
		for (i = 0; i < 3; i++)																		//If none of the attempts were successful - 0 returned.
		{
			if (flag == TRUE){
				_flushall();
				printf("Please enter you password.\n");
				scanf("%s", pass);
			}
			if (strcmp(studLogin->StudentPassword, pass) == 0)
				return studLogin->StudentID;
		}
	}
	else if (watchLogin)
	{
		for (i = 0; i < 3; i++)
		{
			if (flag == TRUE){
				_flushall();
				printf("Please enter you password.\n");
				scanf("%s", pass);
			}
			if (strcmp(watchLogin->WatcherPassword, pass) == 0)
				return watchLogin->WatcherID;
		}
	}
	else if (admLogin)
	{
		for (i = 0; i < 3; i++)
		{
			if (flag == TRUE){
				_flushall();
				printf("Please enter you password.\n");
				scanf("%s", pass);
			}
			if (strcmp(admLogin->AdminPassword, pass) == 0)
				return admLogin->AdminID;
		}
	}
	if (flag == TRUE){
		printf("You have failed to enter you password correctly 3 times. Login failed.\n");
	}
	return 0;

		
}


void Output(char* message){
	//Prints , prompts for enter, clears screen and buffer:
	char junk[50];
	if (message!= "") 
		puts(message);
	puts("Press ENTER to continue");
	fflush(stdin);
	gets(junk);
	system("cls");
}


void printRandQuote(Global* GlobalFile){
	//Calculating quotes amount:
	int amount = 0, r;
	Quote* current = GlobalFile->QuotesList;
	srand(time(NULL));

	while (current != NULL){
		current = current->QuoteNext;
		amount++;
	}
	r = rand() % amount;

	current = GlobalFile->QuotesList;
	amount = 0;
	while (amount < r){
		current = current->QuoteNext;
		amount++;
	}

	printf("%s -%s\n", current->Quote, current->QuoteAuthor);
}
#endif