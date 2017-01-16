// Alexey
#include "DataBase.h"

/////// functions decalrations
void addUserToProject(Global *GlobalFile, Project *newProject);									//42
void CreateNewTask(Global *GlobalFile, Project *project, int UserID, AccessGroup group);		//53
void PrintProjectsList(Global *GlobalFile, int UserID, AccessGroup group);						//44

/////// declarations end

// Functions
// 46 - Create new project by STUDENT or WATCHER only, UNDONE
int CreateNewProject(Global* GlobalFile,int userID, AccessGroup userGroup)
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
		return 1;		// incorrect access group
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
	puts("1 .Return to previous menu");
	puts("2. Exit");
	fflush(stdin);
	choice = getchar();
	if (choice == '1')
		return 1; //returns to menu
	else if (choice == '2')
		Exit(GlobalFile);
	else
		puts("Incorrect input, you will be returned to Menu");
	return 1;

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
	

	///////THERES AN ERROR HERE  //////
	//project->TasksList = AddTask(project->TasksList, newTask);		// add new task to tasks list of choosen project
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


void PrintTasksList(Global* GlobalFile, Project* Project){
	int i, j, status, taskID;
	Task* task;
	char* creator;
	char* taskName;

	printf("Tasks in project:\n");
	for (j = 1, i = 0; i < Project->ProjectTasksAmount; i++){
		task = FindTask(GlobalFile->TaskList, Project->TasksIDS[i]);
		status = task->TaskStatus;
		if (status == 5) //Trash and won't show it
			continue;
		taskID = task->TaskID;
		creator = task->TaskCreatorName;
		taskName = task->TaskName;

		printf("---\n");
		printf("%d) ID: %d Creator: %s Status: %d\n", j, taskID, creator, status);
		printf("Task: %s\n\n", taskName);
		j++;
	}
}

void PrintActivityLog(Global* GlobalFile, Project* project){
	
	char BUFFER[400], *fileName = project->ProjectActivityLogs;
	FILE* file = fopen(fileName, "r");
	if (!file) return;

	while (fgets(BUFFER, 400, file)) printf("%s\n", BUFFER);
	fclose(file);
}




void PrintProjectDetails(Global* GlobalFile, Project* project){
	int projectID = project->ProjectID,
		numOfTasks = project->ProjectTasksAmount,
		numOfUsers = project->ProjectUsersAmount;
	char* creator = project->ProjectCreatorName, *projectName = project->ProjectName;

	printf("Project Details:\n");
	printf("-------------------");
	printf("ID: %d , Number of tasks: %d , Number of users: %d , Creator: %s", projectID, numOfTasks, numOfUsers, creator);

	//Need to print details of student here too.
	printf("Students in project:\n");
	printf("----------------------");
	//Need to add a helper function for that
}

void ChangeTaskStatus(Global* GlobalFile, Project* project, int userID, int accessGroup){
	int taskID, status;
	Task* task;
	//Getting a task from the user:

	printf("Enter Task ID:\n");
	scanf("%d", &taskID);
	//Making sure that task is in the relevant project:
	task = findTaskInProject(GlobalFile, project, taskID);
	if (!task){
		printf("Task does not belong to this project\n");
		return;
	}

	printf("Current status is: %s\n", convertStatusToString(task->TaskStatus));
	printf("Choose status to change into:\n");
	printf("Available Status:\n");
	printf("[0] New , [1] Elicitation, [2] Analysis, [3] VandV ");
	if (accessGroup != 1) printf(" [4] Approved"); //Student can't change to approved
	printf("\n");
	printf("Enter an integer of your choice:\n");
	scanf("%d", &status);
	if (accessGroup == STUDENT && status == APPROVED) {
		printf("Student cannot set status to approved, please contact your watcher or admin\n");
		return;
	}
	task->TaskStatus = (STATUS)status;
}


void RemoveProject(Global* GlobalFile, Project* project, int userID, int accessGroup){
	char choice = 'O';
	printf("Are you sure you want to remove this project and all of its tasks (Y/N)?\n");
	
	while (choice == 'O'){
		choice = getchar();

		switch (choice){
		case 'Y':
		case 'y':
			RemoveProjectFromList(GlobalFile->ProjectsList, project->ProjectID);
			//delete // Need to implement functions that will remove this project id from all the users, from all the lists etc
			break;
		case 'N':
		case 'n':
			break;
		default: printf("No such option!\n");
			choice = 'O';
		}
	}

}

void LeaveMessageToStudent(Global* GlobalFile, Project* project, Watcher* watcher){
	int studentID;
	Student* student;
	char* Message;
	printf("Please choose a studentID of the student you want to leave a message for:\n");
	scanf("%d", &studentID);
	if (isStudentInProject(project, studentID)){
		student = FindStudent(GlobalFile->StudentList, studentID);
		if (!student) return //If for some reason student is not in the global file, exiting function
		printf("Enter the message you want to leave (Between 5 to 30):\n");
		do
			scanf("%s", &Message);
		while (strlen(Message) < 5 || strlen(Message) > 30);
		strcpy(student->StudentMessages, Message);
	}
}

void AddProjectMessage(Global* GlobalFile, Project* project, Watcher* watcher){
	char* Message = "";
	printf("Enter the message you want to leave (Between 5 to 30):\n");
	do
	scanf("%s", &Message);
	while (strlen(Message) < 5 || strlen(Message) > 30);

	strcpy(project->ProjectMessages, Message);
}

void ShowTasksByStatus(Global* GlobalFile, int studentID ){
	int tasksCount = 1 , i,j, status = -1 , projectID, taskID;
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
	for (i = 0; i < student->StudentProjectsAmount; i++){
		projectID = projectIDs[i];
		project = FindProject(GlobalFile->ProjectsList, projectID);
		for (j = 0; j < project->ProjectTasksAmount; j++){
			taskID = project->TasksIDS[j];
			task = findTaskInProject(GlobalFile, project, taskID);
			if (task->TaskStatus == status){
				printf("%d.)ID: %d , Creator: %s , Task: %s \n", tasksCount,task->TaskID, task->TaskCreatorName, task->TaskName);
				tasksCount++;
			}
		}
	}

}

void PrintStudentLog(Student* student){
	char BUFFER[400], *fileName = student->StudentActivityLog;
	FILE* file = fopen(fileName, "r");
	if (!file) return;

	while (fgets(BUFFER, 400, file)) printf("%s\n", BUFFER);
	fclose(file);
}

int FindAccessGroup(int ID){
	//Should be in Functions, I wrote it for the meantime here
	if (ID > 0 && ID <= 1000) return STUDENT;
	else if (ID > 1000 && ID <= 2000) return ADMIN;
	else if (ID > 2000 && ID <= 3000) return WATCHER;
	
	return BAD;
}

void UpdateDetails(Global* GlobalFile, int userID){
	//Finding the user and its' struct:
	Watcher* watcher = NULL;
	Admin* admin = NULL;
	Student* student = NULL;
	char *name, *surname, *username , input;
	int AG = FindAccessGroup(userID);
	
	switch (AG){
	case STUDENT:
		student = FindStudent(GlobalFile->StudentList, userID);
		name = student->StudentName;
		surname = student->StudentSurename;
		username = student->StudentUsername;
		break;

	case ADMIN:
		admin = FindAdmin(GlobalFile->AdminsList, userID);
		name = admin->AdminName;
		surname = admin->AdminSurename;
		username = admin->AdminUsername;
		break;

	case WATCHER:
		watcher = FindWatcher(GlobalFile->WatchersList, userID);
		name = student->StudentName;
		surname = student->StudentSurename;
		username = watcher->WatcherUsername;
		break;
	}

	printf("Do you want to change your first name?(y/n)\n");
	scanf("%c", &input);
	if (input == 'y') {
		printf("Enter new first name:\n");
		scanf("%s", &name);
		input = 'n';
	}

	printf("Do you want to change your last name?(y/n)\n");
	scanf("%c", &input);
	if (input == 'y') {
		printf("Enter new last name:\n");
		scanf("%s", &surname);
		input = 'n';
	}

	printf("Do you want to change your user name?(y/n)\n");
	scanf("%c", &input);
	if (input == 'y') {
		printf("Enter new user name:\n");
		scanf("%s", &username);
		input = 'n';
	}

}

void AddGlobalMessage(Global* GlobalFile){
	char temp[250] = "";
	printf("Enter global message (max length 30):\n");
	do
	scanf("%s", &temp);
	while (strlen(temp) > 30);

	strcpy(GlobalFile->GlobalMessages, temp);
}
// quotes funcs start, done, ready to testing
void AddNewQuote(Global* GlobalFile){
	char tempQuote[300], tempAuthor[100];
	//Creating a new quote and incrementing quoteRunID: Not sure if that's right
	int quoteID = GlobalFile->QuoteRunID++;
	Quote* newQuote = (Quote*) malloc(sizeof(Quote));
	newQuote->QuoteID = quoteID;
	printf("Enter quote (max length 256):\n");
	do
	{
		fflush(stdin);
		scanf("%s", &tempQuote);
	}
	while (strlen(tempQuote) > 255);

	strcpy(newQuote->Quote, tempQuote);

	printf("Enter quote's author (max length 30):\n");
	do
	{
		fflush(stdin);
		scanf("%s", &tempAuthor);
	}
	while (strlen(tempQuote) > 30);

	strcpy(newQuote->QuoteAuthor, tempAuthor);

	//Adding to global quote list:
	AddQuote(GlobalFile->QuotesList, newQuote);
	GlobalFile->QuoteRunID++;

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
}
void DeleteQuote(Global* GlobalFile)
{
	Quote *quote = NULL;
	int ID;
	fflush(stdin);
	printf("Input Quote ID to delete : ");
	scanf("%d", &ID);
	quote = FindQuote(GlobalFile->QuotesList, ID);
	if (quote)
	{
		RemoveQuoteFromList(GlobalFile->QuotesList, ID);
		printf("Quote with id : %d found and deleted.\n", ID);
	}
	else
		puts("ID not found in database");
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
			AddNewQuote(GlobalFile);
		else if (choice == '3')
			DeleteQuote(GlobalFile);
		else if (choice == '4')
			flag=FALSE;
		else
			puts("Incorrect choice");
	}

}
// quotes funcs end
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
	if (ID < 1000 || ID >=4000)
		puts("incorrect ID , correct range 1000-3999");
	else if (ID >= 1000 && ID <= 1999)
	{
		student = FindStudent(GlobalFile->StudentList, ID);
		if (student)
		{
			printf("User data for user with ID %d",ID);
			printf("\nUsername : %s\nPassword :%s\nName : %s\nSurename : %s\nEmail : %s\nDepartment :%s\nYear : %c\nProjects Amount : %d\nTasks Amount : %d\n\n", student->StudentUsername, student->StudentPassword, student->StudentName, student->StudentSurename, student->StudentEmail, student->StudentDepartment, student->StudentYear, student->StudentProjectsAmount, student->StudentTasksAmount);
		}
		else
			puts("Student with this id not found");

	}
	else if (ID >= 2000 && ID <= 2999)
	{
		admin = FindAdmin(GlobalFile->AdminsList, ID);
		if (admin)
		{
			printf("User data for user with ID %d", ID);
			printf("\nUsername : %s\nPassword :%s\nName : %s\n%Surename\n\n", admin->AdminUsername, admin->AdminPassword, admin->AdminName, admin->AdminSurename);
		}
		else
			puts("Admin with this ID not found");

	}
	else if (ID >= 3000 && ID <= 3999)
	{
		watcher = FindWatcher(GlobalFile->WatchersList, ID);
		if (watcher)
		{
			printf("User data for user with ID %d\n", ID);
			printf("Username : %s\nPassword :%s\nName : %s\n%Surename\nEmail : %s\nProjects Amount : %d\n\n", watcher->WatcherUsername, watcher->WatcherPassword, watcher->WatcherName, watcher->WatcherSurename, watcher->WatcherProjectsAmount);
		}
		else
			puts("Watcher with this ID not found");

	}
		printf("Return to previous menu ( Y / N ) :");
		fflush(stdin);
	choice = getchar();
	if (choice == 'Y' || choice == 'y')
		return;
	else if (choice == 'N' || choice == 'n')
		Exit(GlobalFile);
	else
		puts("Incorrect choice, returning to previous menu");
}