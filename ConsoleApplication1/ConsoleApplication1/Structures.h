// Alexey
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// enum declarations
typedef enum { BAD, STUDENT, ADMIN, WATCHER }AccessGroup;
typedef enum { NEW, ELICITATION, ANALYSIS, VandV, APPROVED, TRASH }STATUS;
typedef enum { FALSE, TRUE }BOOL;
typedef enum { FILE_READ_ERROR, FILE_WRITE_ERROR } ERRORS;
//structures declarations
typedef struct Project Project;
typedef struct Student Student;
typedef struct Watcher Watcher;
typedef struct Admin Admin;
typedef struct Watcher Watcher;
typedef struct Task Task;
typedef struct Quote Quote;
typedef struct Global Global;
// structures
typedef struct Student{
	AccessGroup Group;
	int StudentID, StudentProjectsAmount, StudentTasksAmount;
	char StudentUsername[31], StudentPassword[31], StudentName[21], StudentEmail[50], StudentSurename[21], StudentDepartment[21], StudentYear;
	int *ProjectIDS;
	char StudentMessages[31], StudentActivityLog[31];
	struct Student *StudentNext;
}Student;


typedef struct Quote{
	int QuoteID;
	char Quote [256], QuoteAuthor[31];
	struct Quote *QuoteNext;
}Quote;


typedef struct Project{
	int ProjectID, ProjectUsersAmount, ProjectTasksAmount;
	char ProjectName[128], ProjectCreatorName[31];
	int *StudentsIDS;
	int *TasksIDS;
	char ProjectMessages[31], ProjectActivityLogs[31];
	BOOL ProgramChanges;
	struct Project *ProjectNext;
}Project;


typedef struct Admin{
	int AdminID;
	char AdminUsername[31], AdminPassword[31], AdminName[21], AdminSurename[21];
	AccessGroup Group;
	struct Admin *AdminNext;
}Admin;


typedef struct Watcher{
	AccessGroup Group;
	int WatcherID, WatcherProjectsAmount;
	char WatcherUsername[31], WatcherPassword[31], WatcherName[21], WatcherSurename[21], WatcherEmail[50];
	int *ProjectIDS;
	BOOL WatcherReceiveChanges;
	struct Watcher *WatcherNext;
}Watcher;


typedef struct Task{
	int TaskID;
	char TaskName[256], TaskCreatorName[31];
	STATUS TaskStatus;
	Task* TaskNext;
}Task;


typedef struct Global{
	int QuoteRunID, StudentRunID, WatcherRunID, AdminRunID,ProjectRunID,TaskRunID;
	Student *StudentList;
	Watcher *WatchersList;
	Admin *AdminsList;
	Project *ProjectsList;
	Quote *QuotesList;
	Task *TaskList;
	char GlobalMessages[31];
}Global;


//
//	Linked list functions start
//
// Find element by id
Student *FindStudent(Student* head, int StudentID){

	Student *current = head;
	while (current){
		if ((current)->StudentID == StudentID)
			return current;
		current = (current)->StudentNext;
	}
	return NULL;
}


Admin *FindAdmin(Admin *head, int AdminID){

	Admin *current = head;
	while (current){
		if ((current)->AdminID == AdminID)
			return current;
		current = (current)->AdminNext;
	}
	return NULL;
}


Watcher *FindWatcher(Watcher* head, int WatcherID){

	Watcher *current = head;
	while (current){
		if ((current)->WatcherID == WatcherID)
			return current;
		current = (current)->WatcherNext;
	}
	return NULL;
}


Project *FindProject(Project* head, int ProjectID){

	Project *current = head;
	while (current){
		if ((current)->ProjectID == ProjectID)
			return current;
		current = (current)->ProjectNext;
	}
	return NULL;
}


Task *FindTask(Task* head, int TaskID){

	Task *current = head;
	while (current){
		if ((current)->TaskID == TaskID)
			return current;
		current = (current)->TaskNext;
	}
	return NULL;
}

Quote *FindQuote(Quote* head, int QuoteID){

	Quote *current = head;
	while (current){
		if ((current)->QuoteID == QuoteID)
			return current;
		current = (current)->QuoteNext;
	}
	return NULL;
}

// search in list end
// Add to lists
Student* AddStudent(Student *studentHead, Student *addStudent){
	if (studentHead == NULL)
	{
		studentHead = addStudent;
		addStudent->StudentNext = NULL;
	}
	else {

		Student *current = studentHead;
		while (current->StudentNext != NULL)		// go to the last node
			current = current->StudentNext;

		addStudent->StudentNext = NULL;
		current->StudentNext = addStudent;
	}
	return studentHead;
}


Admin* AddAdmin(Admin *adminHead, Admin *addAdmin){

	Admin *current = adminHead;
	if (adminHead == NULL)
	{
		adminHead = addAdmin;
		addAdmin->AdminNext = NULL;
	}
	else {
		while (current->AdminNext != NULL)		// go to the last node
			current = current->AdminNext;

		addAdmin->AdminNext = NULL;
		current->AdminNext = addAdmin;
	}
	return adminHead;

}


Watcher* AddWatcher(Watcher *watcherHead, Watcher *addWatcher){
	if (watcherHead == NULL)
	{
		watcherHead = addWatcher;
		addWatcher->WatcherNext = NULL;
	}
	else {
	Watcher *current = watcherHead;

	while (current->WatcherNext != NULL)		// go to the last node
		current = current->WatcherNext;

	addWatcher->WatcherNext = NULL;
	current->WatcherNext = addWatcher;
	}
	return watcherHead;
}


Project* AddProject(Project *projectHead, Project *addProject){
	Project *current = projectHead;
	if (projectHead == NULL)
	{
		projectHead = addProject;
		addProject->ProjectNext = NULL;
	}
	else {
	while (current->ProjectNext != NULL)		// go to the last node
		current = current->ProjectNext;

	addProject->ProjectNext = NULL;
	current->ProjectNext = addProject;
	}
	return projectHead;
}


Quote* AddQuote(Quote *QuoteHead, Quote *addQuote){
	Quote *current = QuoteHead;
	if (QuoteHead == NULL)
	{
		QuoteHead = addQuote;
		addQuote->QuoteNext = NULL;
	}
	else {
	while (current->QuoteNext != NULL)		// go to the last node
		current = current->QuoteNext;

	addQuote->QuoteNext = NULL;
	current->QuoteNext = addQuote;
	}
	return QuoteHead;
}


Task *AddTask(Task *TasksHead, Task *addTask){

	Task *current = TasksHead;
	if (TasksHead == NULL)
	{
		TasksHead = addTask;
		addTask->TaskNext = NULL;
	}
	else {
	while (current->TaskNext != NULL)		// go to the last node
		current = current->TaskNext;

	addTask->TaskNext = NULL;
	current->TaskNext = addTask;
	}
	return TasksHead;
}
//delete elements from linked list

Project *RemoveProjectFromList(Project *head, int deleteID)
{
	Project *current = head, *previous = NULL;
	if (!head) return NULL;

	while (current->ProjectID != deleteID && current->ProjectNext != NULL)
	{
		previous = current;
		current = current->ProjectNext;
	}

	if (current->ProjectID == deleteID)
	{
		if (previous)
			previous->ProjectNext = current->ProjectNext;
		else
			head = current->ProjectNext;

		free(current);
	}
	return head;
}

Student *RemoveStudentFromList(Student *head, int deleteID)
{
	Student *current = head, *previous = NULL;
	if (!head) return NULL;

	while (current->StudentID != deleteID && current->StudentNext != NULL)
	{
		previous = current;
		current = current->StudentNext;
	}

	if (current->StudentID == deleteID)
	{
		if (previous)
			previous->StudentNext = current->StudentNext;
		else
			head = current->StudentNext;

		free(current);
	}
	return head;
}

Watcher *RemoveWatcherFromList(Watcher *head, int deleteID)
{
	Watcher *current = head, *previous = NULL;

	if (!head) return NULL;

	while (current->WatcherID != deleteID && current->WatcherNext != NULL)
	{
		previous = current;
		current = current->WatcherNext;
	}

	if (current->WatcherID == deleteID)
	{
		if (previous)
			previous->WatcherNext = current->WatcherNext;
		else
			head = current->WatcherNext;

		free(current);
	}
	return head;
}

Admin *RemoveAdminFromList(Admin *head, int deleteID)
{
	Admin *current = head, *previous = NULL;
	if (!head) return NULL;

	while (current->AdminID != deleteID && current->AdminNext != NULL)
	{
		previous = current;
		current = current->AdminNext;
	}

	if (current->AdminID == deleteID)
	{
		if (previous)
			previous->AdminNext = current->AdminNext;
		else
			head = current->AdminNext;

		free(current);
	}
	return head;
}

Quote *RemoveQuoteFromList(Quote *head, int deleteID)
{
	Quote *current = head, *previous = NULL;
	if (!head) return NULL;

	while (current->QuoteID != deleteID && current->QuoteNext != NULL)
	{
		previous = current;
		current = current->QuoteNext;
	}

	if (current->QuoteID == deleteID)
	{
		if (previous)
			previous->QuoteNext = current->QuoteNext;
		else
			head = current->QuoteNext;

		free(current);
	}
	return head;
}
/// end remove functions


// Print List's Functions start
void PrintStudentList(Student *StudentHead){

	Student *student = StudentHead;
	if (student == NULL)
		puts("No students in system");

	printf("ID\tName\tSurename\tDepartment\tYear\tProjects\tTasks\n");
	while (student){

		// print all student fields
		printf("%d\t%s\t%s\t\t%s\t%c\t%d\t\t%d\n", student->StudentID, student->StudentName, student->StudentSurename, student->StudentDepartment, student->StudentYear, student->StudentProjectsAmount, student->StudentTasksAmount);
		student = student->StudentNext;
	}
}
void PrintAdminsList(Admin *head)
{
	
	Admin *admin = head;
	if (admin == NULL)
		puts("No admins in system");

	printf("ID\tName\tSurename\n");
	while (admin){
		// print all admin fields
		printf("%d\t%s\t%s\n",admin->AdminID, admin->AdminName, admin->AdminSurename);
		admin = admin->AdminNext;
	}
}

void PrintWatcherList(Watcher *head)
{

	Watcher *watcher = head;
	if (head == NULL)
		puts("No watchers in system");

	printf("ID\tName\tSurename\tProjects\n");
	while (watcher){
		// print all watcher fields
		printf("%d\t%s\t%s\t%d\n", watcher->WatcherID, watcher->WatcherName, watcher->WatcherSurename,watcher->WatcherProjectsAmount);
		watcher = watcher->WatcherNext;
	}
}


// print List's funcs end


//Utilities:

char* convertStatusToString(STATUS status){
	switch (status){
	case 0 :
		return "New";
	case 1:
		return "Elicitation";
	case 2:
		return "Analysis";
	case 3:
		return "VandV";
	case 4:
		return "Approved";
	case 5:
		return "Trash";

	default:
		return NULL;
	}
}

Task* findTaskInProject(Global* globalFile , Project* project, int taskID){
	int i;
	for (i = 0; i < project->ProjectTasksAmount && taskID != project->TasksIDS[i]; i++);

	if (i == project->ProjectTasksAmount) return NULL;

	return FindTask(globalFile->TaskList, taskID);
}

int isStudentInProject(Project* project, int studentID){
	int i;
	for (i = 0; i < project->ProjectUsersAmount; i++) if ((project->StudentsIDS)[i] == studentID) return 1;

	return 0;
}
