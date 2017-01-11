/*LIRAN*/
#define _CRT_SECURE_NO_WARNINGS
#include "LinkedListFunctions.c"
/// Define path's
#define StudentsFilePath "/Databases/students.txt"
#define AdminsFilePath "/Databases/admins.txt"
#define WatchersFilePath "/Databases/watchers.txt"
#define GlobalFilePath "/Databases/global.txt"
#define QuotesFilePath "/Databases/quotes.txt"
#define ProjectsFilePath "/Databases/projects.txt"
/// end defines & includes 


Student* initStudents(){
	Student* head = NULL, *newStud;
	FILE * read = fopen(StudentsFilePath, "r");
	if (read == NULL){
		printf("Error opening the students file.\n");
		return NULL;
	}
	else{
		int num = 0;
		while (!feof(read)){
			if (num == 0)
			{
				newStud = (Student*)(malloc(sizeof(Student)));
				head = newStud;
			}
			else{
				newStud = (Student*)(malloc(sizeof(Student)));
				head = AddStudent(head, newStud);					// use linked list func's to add new element to end of linked list
			}
			fscanf(read, "%d", &newStud->StudentID);
			fscanf(read, "%s", &newStud->StudentUsername);
			fscanf(read, "%s", &newStud->StudentPassword);
			fscanf(read, "%s", &newStud->StudentName);
			fscanf(read, "%s", &newStud->StudentSurename);
			fscanf(read, "%s", &newStud->StudentEmail);
			fscanf(read, "%s", &newStud->StudentDepartment);
			fscanf(read, "%c", &newStud->StudentYear);
			fscanf(read, "%s", &newStud->StudentActivityLog);
			fscanf(read, "%d", &newStud->Group);
			fscanf(read, "%d", &newStud->StudentProjectsAmount);
			int i;
			newStud->ProjectIDS = (int*)(malloc(newStud->StudentProjectsAmount * sizeof(int)));
			for (i = 0; i < newStud->StudentProjectsAmount; i++){
				fscanf(read, "%d", &newStud->ProjectIDS[i]);
			}
			fscanf(read, "%d", &newStud->StudentTasksAmount);
			fscanf(read, "%s", &newStud->StudentMessages);
			num++;
		}

	}
	fclose(read);
	return head;
}

Project* initProjects(Student* studhead, Task* taskhead){
	Project* head = NULL, *newProj;
	FILE * read = fopen(ProjectsFilePath, "r");
	if (read == NULL){
		printf("Error opening the projects file.\n");
		return NULL;
	}
	else{
		int num = 0;
		while (!feof(read)){
			if (num == 0){
				newProj = (Project*)(malloc(sizeof(Project)));
				head = newProj;
			}
			else{
				newProj = (Project*)(malloc(sizeof(Project)));
				head = AddProject(head, newProj);
			}
			fscanf(read, "%d", &newProj->ProjectID);
			fscanf(read, "%s", &newProj->ProjectName);
			fscanf(read, "%s", &newProj->ProjectCreatorName);
			fscanf(read, "%s", &newProj->ProjectActivityLogs);
			fscanf(read, "%d", &newProj->ProjectUsersAmount);
			int i;
			for (i = 0; i < newProj->ProjectUsersAmount; i++)
			{
				
			}
			fscanf(read, "%d", &newProj->ProjectTasksAmount);
			for (i = 0; i < newProj->ProjectUsersAmount; i++)
			{

			}
			fscanf(read, "%s", &newProj->ProjectMessages);
			num++;
		}
	}
	fclose(read);
	return head;
}

Watcher* initWatchers(){
	Watcher* head = NULL, *newWatcher;
	FILE * read = fopen(WatchersFilePath, "r");
	if (read == NULL){
		printf("Error opening the admins file.\n");
		return NULL;
	}
	else{
		int num = 0;
		while (!feof(read)){
			if (num == 0){
				newWatcher = (Watcher*)(malloc(sizeof(Watcher)));
				head = newWatcher;
			}
			else{
				newWatcher = (Watcher*)(malloc(sizeof(Watcher)));
				head = AddWatcher(head,newWatcher);

			}
			fscanf(read, "%d", &newWatcher->WatcherID);
			fscanf(read, "%s", &newWatcher->WatcherUsername);
			fscanf(read, "%s", &newWatcher->WatcherPassword);
			fscanf(read, "%s", &newWatcher->WatcherName);
			fscanf(read, "%s", &newWatcher->WatcherSurename);
			fscanf(read, "%s", &newWatcher->WatcherEmail);
			fscanf(read, "%s", &newWatcher->Group);
			fscanf(read, "%d", &newWatcher->WatcherReceiveChanges);
			fscanf(read, "%s", &newWatcher->WatcherProjectsAmount);

			num++;
		}
	}
	fclose(read);
	return head;
}

Admin* initAdmins(){
	Admin* head = NULL, *newAdmin;
	FILE * read = fopen(AdminsFilePath, "r");
	if (read == NULL){
		printf("Error opening the admins file.\n");
		return NULL;
	}
	else{
		int num = 0;
		while (!feof(read)){
			if (num == 0){
				newAdmin = (Admin*)(malloc(sizeof(Admin)));
				head = newAdmin;
			}
			else{
				newAdmin = (Admin*)(malloc(sizeof(Admin)));
				head = AddAdmin(head, newAdmin);
			}
			fscanf(read, "%d", &newAdmin->AdminID);
			fscanf(read, "%s", &newAdmin->AdminUsername);
			fscanf(read, "%s", &newAdmin->AdminPassword);
			fscanf(read, "%s", &newAdmin->AdminName);
			fscanf(read, "%s", &newAdmin->AdminSurename);
			fscanf(read, "%d", &newAdmin->Group);
			num++;
		}
	}
	fclose(read);
	return head;
}

Task* initTasks(){
	Task* head = NULL, *newTask;
	FILE * read = fopen("tasks.txt", "r");
	if (read == NULL){
		printf("Error opening the tasks file.\n");
		return NULL;
	}
	else{
		int num = 0;
		while (!feof(read)){
			if (num == 0){
				newTask = (Task*)(malloc(sizeof(Task)));
				head = newTask;
			}
			else{
				newTask = (Task*)(malloc(sizeof(Task)));
				head = AddTask(head, newTask);
			}
			fscanf(read, "%d", &newTask->TaskID);
			fscanf(read, "%s", &newTask->TaskName);
			fscanf(read, "%d", &newTask->TaskStatus);
			fscanf(read, "%s", &newTask->TaskCreatorName);
			num++;
		}
	}
	fclose(read);
	return head;
}

Quote* initQuotes(){
	Quote* head = NULL, *newQuote;
	FILE * read = fopen(QuotesFilePath, "r");
	if (read == NULL){
		printf("Error opening the quotes file.\n");
		return NULL;
	}
	else{
		int num = 0;
		while (!feof(read)){
			if (num == 0){
				newQuote = (Quote*)(malloc(sizeof(Quote)));
				head = newQuote;
			}
			else{
				newQuote = (Quote*)(malloc(sizeof(Quote)));
				head = AddQuote(head, newQuote);
			}
			fscanf(read, "%d", &newQuote->QuoteID);
			fscanf(read, "%s", &newQuote->Quote);
			fscanf(read, "%d", &newQuote->QuoteAuthor);
			num++;
		}
	}
	fclose(read);
	return head;
}
Global *InitDataBases()
{
	FILE *globalFile = fopen(GlobalFilePath, "r");
	if (!globalFile){
		printf("Warning ! File %s can't be opened.\n", GlobalFilePath);
		exit(1);
	}
	Global *GlobalDB = (Global*)malloc(sizeof(Global));
	GlobalDB->AdminsList = initAdmins();
	GlobalDB->StudentList = initStudents();
	GlobalDB->WatchersList = initWatchers();
	GlobalDB->QuotesList = initQuotes();

	return GlobalDB;
}