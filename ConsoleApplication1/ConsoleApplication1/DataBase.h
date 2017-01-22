#ifndef _STRUCTURES_
#define _STRUCTURES
//Liran
#include "Structures.h"

/// Define path's
#define StudentsFilePath "./Databases/students.txt"
#define AdminsFilePath "./Databases/admins.txt"
#define WatchersFilePath "./Databases/watchers.txt"
#define GlobalFilePath "./Databases/global.txt"
#define QuotesFilePath "./Databases/quotes.txt"
#define ProjectsFilePath "./Databases/projects.txt"
#define TasksFilePath "./Databases/tasks.txt"
/// end defines & includes 

// initializations from files
Student* initStudents(){
	Student* head = NULL, *newStud;
	int emptyline;
	FILE * read = fopen(StudentsFilePath, "r");
	if (read == NULL){
		printf("Error opening the students file.\n");
		return NULL;
	}
	else{
		while (!feof(read)){
			newStud = (Student*)(malloc(sizeof(Student)));
			emptyline = fscanf(read, "%d", &newStud->StudentID);
			if (emptyline < 1){
				free(newStud);
				break;
			}
			fscanf(read, "%s", &newStud->StudentUsername);
			fscanf(read, "%s", &newStud->StudentPassword);
			fscanf(read, "%s", &newStud->StudentName);
			fscanf(read, "%s", &newStud->StudentSurename);
			fscanf(read, "%s", &newStud->StudentEmail);
			fscanf(read, "%s", &newStud->StudentDepartment);
			fscanf(read, " %c", &newStud->StudentYear);
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
			head = AddStudent(head, newStud);
		}
	}
	fclose(read);
	return head;
}

Project* initProjects(){
	Project* head = NULL, *newProj;
	int emptyline;
	FILE * read = fopen(ProjectsFilePath, "r");
	if (read == NULL){
		printf("Error opening the projects file.\n");
		return NULL;
	}
	else{
		while (!feof(read)){
			newProj = (Project*)(malloc(sizeof(Project)));
			emptyline = fscanf(read, "%d", &newProj->ProjectID);
			if (emptyline < 1){
				free(newProj);
				break;
			}
			fscanf(read, "%s", &newProj->ProjectName);
			fscanf(read, "%s", &newProj->ProjectCreatorName);
			fscanf(read, "%s", &newProj->ProjectActivityLogs);
			fscanf(read, "%d", &newProj->ProjectUsersAmount);
			int i;
			newProj->StudentsIDS = (int*)(malloc(newProj->ProjectUsersAmount * sizeof(int)));
			for (i = 0; i < newProj->ProjectUsersAmount; i++){
				fscanf(read, "%d", &newProj->StudentsIDS[i]);
			}
			fscanf(read, "%d", &newProj->ProjectTasksAmount);
			newProj->TasksIDS = (int*)(malloc(newProj->ProjectTasksAmount * sizeof(int)));
			for (i = 0; i < newProj->ProjectTasksAmount; i++){
				fscanf(read, "%d", &newProj->TasksIDS[i]);
			}
			fscanf(read, "%s", &newProj->ProjectMessages);
			head = AddProject(head, newProj);
		}
	}
	fclose(read);
	return head;
}

Watcher* initWatchers(){
	Watcher* head = NULL, *newWatcher;
	int emptyline;
	FILE * read = fopen(WatchersFilePath, "r");
	if (read == NULL){
		printf("Error opening the admins file.\n");
		return NULL;
	}
	else{
		while (!feof(read)){
			newWatcher = (Watcher*)(malloc(sizeof(Watcher)));
			emptyline = fscanf(read, "%d", &newWatcher->WatcherID);
			if (emptyline < 1){
				free(newWatcher);
				break;
			}
			fscanf(read, "%s", &newWatcher->WatcherUsername);
			fscanf(read, "%s", &newWatcher->WatcherPassword);
			fscanf(read, "%s", &newWatcher->WatcherName);
			fscanf(read, "%s", &newWatcher->WatcherSurename);
			fscanf(read, "%s", &newWatcher->WatcherEmail);
			fscanf(read, "%d", &newWatcher->Group);
			fscanf(read, "%d", &newWatcher->WatcherReceiveChanges);
			fscanf(read, "%d", &newWatcher->WatcherProjectsAmount);
			int i;
			newWatcher->ProjectIDS = (int*)malloc(newWatcher->WatcherProjectsAmount * sizeof(int));
			for (i = 0; i < newWatcher->WatcherProjectsAmount; i++){
				fscanf(read, "%d", &newWatcher->ProjectIDS[i]);
			}
			head = AddWatcher(head, newWatcher);
		}
	}
	fclose(read);
	return head;
}

Admin* initAdmins(){
	Admin* head = NULL, *newAdmin;
	FILE * read = fopen(AdminsFilePath, "r");
	int emptyline;
	if (read == NULL){
		printf("Error opening the admins file.\n");
		return NULL;
	}
	else{
		while (!feof(read)){
			newAdmin = (Admin*)(malloc(sizeof(Admin)));
			emptyline = fscanf(read, "%d", &newAdmin->AdminID);
			if (emptyline < 1){
				free(newAdmin);
				break;
			}
			fscanf(read, "%s", &newAdmin->AdminUsername);
			fscanf(read, "%s", &newAdmin->AdminPassword);
			fscanf(read, "%s", &newAdmin->AdminName);
			fscanf(read, "%s", &newAdmin->AdminSurename);
			fscanf(read, "%d", &newAdmin->Group);
			head = AddAdmin(head, newAdmin);
		}
	}
	fclose(read);
	return head;
}

Task* initTasks(){
	Task* head = NULL, *newTask;
	int emptyline;
	FILE * read = fopen(TasksFilePath, "r");
	if (read == NULL){
		printf("Error opening the tasks file.\n");
		return NULL;
	}
	else{
		while (!feof(read)){
			newTask = (Task*)(malloc(sizeof(Task)));
			emptyline = fscanf(read, "%d", &newTask->TaskID);
			if (emptyline < 1){
				free(newTask);
				break;
			}
			fscanf(read, "%s", &newTask->TaskName);
			fscanf(read, "%d", &newTask->TaskStatus);
			fscanf(read, "%s", &newTask->TaskCreatorName);
			head = AddTask(head, newTask);
		}
	}
	fclose(read);
	return head;
}

Quote* initQuotes(){
	Quote* head = NULL, *newQuote;
	int i, emptyline;
	FILE * read = fopen(QuotesFilePath, "r");
	if (read == NULL){
		printf("Error opening the quotes file.\n");
		return NULL;
	}
	else{
		while (!feof(read)){
			newQuote = (Quote*)(malloc(sizeof(Quote)));
			i = 0;
			emptyline = fscanf(read, "%d", &newQuote->QuoteID);
			if (emptyline < 1){
				free(newQuote);
				break;
			}
			fgetc(read);
			fgets(newQuote->Quote, sizeof(newQuote->Quote), read);
			while (newQuote->Quote[i++] != '\n');
			newQuote->Quote[i - 1] = '\0';
			fscanf(read, "%s", &newQuote->QuoteAuthor);
			head = AddQuote(head, newQuote);
		}
	}
	fclose(read);
	return head;
}

Global *initGlobal(){
	FILE *globalFile = fopen(GlobalFilePath, "r");
	if (!globalFile){
		printf("Warning ! File %s can't be opened.\n", GlobalFilePath);
		exit(1);
	}
	Global *GlobalDB = (Global*)malloc(sizeof(Global));
	fscanf(globalFile, "%d", &GlobalDB->StudentRunID);
	fscanf(globalFile, "%d", &GlobalDB->AdminRunID);
	fscanf(globalFile, "%d", &GlobalDB->WatcherRunID);
	fscanf(globalFile, "%d", &GlobalDB->ProjectRunID);
	fscanf(globalFile, "%d", &GlobalDB->QuoteRunID);
	fscanf(globalFile, "%d", &GlobalDB->TaskRunID);
	fgetc(globalFile);
	int i = 0;
	fgets(GlobalDB->GlobalMessages, sizeof(GlobalDB->GlobalMessages), globalFile);
	while (GlobalDB->GlobalMessages[i++] != '\n' && GlobalDB->GlobalMessages[i++] != '\0');
	GlobalDB->GlobalMessages[i - 1] = '\0';
	fclose(globalFile);
	return GlobalDB;
}

Global *InitDataBases(){
	Global *GlobalDB = initGlobal();
	GlobalDB->AdminsList = initAdmins();
	GlobalDB->StudentList = initStudents();
	GlobalDB->WatchersList = initWatchers();
	GlobalDB->QuotesList = initQuotes();
	GlobalDB->TaskList = initTasks();
	GlobalDB->ProjectsList = initProjects();
	return GlobalDB;
}

//save to file functions
void saveAdmins(Admin *AdminList){
	FILE *saveFile = fopen(AdminsFilePath, "w");
	if (!saveFile){
		printf("Warning ! File %s can't be opened.\n", AdminsFilePath);
		exit(1);
	}
	while (AdminList){
		fprintf(saveFile, "%d %s %s %s %s %d\n", AdminList->AdminID, AdminList->AdminUsername,
			AdminList->AdminPassword, AdminList->AdminName, AdminList->AdminSurename, AdminList->Group);
		AdminList = AdminList->AdminNext;
	}
	fclose(saveFile);
}

void saveStudents(Student *StudentList){
	FILE *saveFile = fopen(StudentsFilePath, "w");
	if (!saveFile){
		printf("Warning ! File %s can't be opened.\n", StudentsFilePath);
		exit(1);
	}
	while (StudentList){
		fprintf(saveFile, "%d %s %s %s %s %s %s %c %s %d %d ", StudentList->StudentID, StudentList->StudentUsername,
			StudentList->StudentPassword, StudentList->StudentName, StudentList->StudentSurename,
			StudentList->StudentEmail, StudentList->StudentDepartment, StudentList->StudentYear,
			StudentList->StudentActivityLog, StudentList->Group, StudentList->StudentProjectsAmount);
		int i;
		for (i = 0; i < StudentList->StudentProjectsAmount; i++){
			fprintf(saveFile, "%d ", StudentList->ProjectIDS[i]);
		}
		fprintf(saveFile, "%d %s\n", StudentList->StudentTasksAmount, StudentList->StudentMessages);
		StudentList = StudentList->StudentNext;
	}
	fclose(saveFile);
}

void saveWatchers(Watcher *WatchersList){
	FILE *saveFile = fopen(WatchersFilePath, "w");
	if (!saveFile){
		printf("Warning ! File %s can't be opened.\n", WatchersFilePath);
		exit(1);
	}
	while (WatchersList){
		fprintf(saveFile, "%d %s %s %s %s %s %d %d %d ", WatchersList->WatcherID, WatchersList->WatcherUsername, WatchersList->WatcherPassword,
			WatchersList->WatcherName, WatchersList->WatcherSurename, WatchersList->WatcherEmail, WatchersList->Group,
			WatchersList->WatcherReceiveChanges, WatchersList->WatcherProjectsAmount);
		int i;
		for (i = 0; i < WatchersList->WatcherProjectsAmount; i++){
			if (i == WatchersList->WatcherProjectsAmount - 1)
				fprintf(saveFile, "%d\n", WatchersList->ProjectIDS[i]);
			else
				fprintf(saveFile, "%d ", WatchersList->ProjectIDS[i]);
		}
		if (WatchersList->WatcherProjectsAmount == 0)
			fprintf(saveFile, "\n");
		WatchersList = WatchersList->WatcherNext;
	}
	fclose(saveFile);
}

void saveProjects(Project *ProjectsList){
	FILE *saveFile = fopen(ProjectsFilePath, "w");
	if (!saveFile){
		printf("Warning ! File %s can't be opened.\n", ProjectsFilePath);
		exit(1);
	}
	while (ProjectsList){
		fprintf(saveFile, "%d %s %s %s %d ", ProjectsList->ProjectID, ProjectsList->ProjectName, ProjectsList->ProjectCreatorName,
			ProjectsList->ProjectActivityLogs, ProjectsList->ProjectUsersAmount);
		int i;
		for (i = 0; i < ProjectsList->ProjectUsersAmount; i++){
			fprintf(saveFile, "%d ", ProjectsList->StudentsIDS[i]);
		}
		fprintf(saveFile, "%d ", ProjectsList->ProjectTasksAmount);
		for (i = 0; i < ProjectsList->ProjectTasksAmount; i++){
			fprintf(saveFile, "%d ", ProjectsList->TasksIDS[i]);
		}
		fprintf(saveFile, "%s\n", ProjectsList->ProjectMessages);
		ProjectsList = ProjectsList->ProjectNext;
	}
	fclose(saveFile);
}

void saveQuotes(Quote *QuotesList){
	FILE *saveFile = fopen(QuotesFilePath, "w");
	if (!saveFile){
		printf("Warning ! File %s can't be opened.\n", QuotesFilePath);
		exit(1);
	}
	while (QuotesList){
		fprintf(saveFile, "%d\n%s\n%s\n", QuotesList->QuoteID, QuotesList->Quote, QuotesList->QuoteAuthor);
		QuotesList = QuotesList->QuoteNext;
	}
	fclose(saveFile);
}

void saveTasks(Task *TaskList){
	FILE *saveFile = fopen(TasksFilePath, "w");
	if (!saveFile){
		printf("Warning ! File %s can't be opened.\n", TasksFilePath);
		exit(1);
	}
	while (TaskList){
		fprintf(saveFile, "%d %s %d %s\n", TaskList->TaskID, TaskList->TaskName,
			TaskList->TaskStatus, TaskList->TaskCreatorName);
		TaskList = TaskList->TaskNext;
	}
	fclose(saveFile);
}

void saveGlobal(Global *GlobalDB){
	FILE *saveFile = fopen(GlobalFilePath, "w");
	if (!saveFile){
		printf("Warning ! File %s can't be opened.\n", GlobalFilePath);
		exit(1);
	}
	fprintf(saveFile, "%d\n", GlobalDB->StudentRunID);
	fprintf(saveFile, "%d\n", GlobalDB->AdminRunID);
	fprintf(saveFile, "%d\n", GlobalDB->WatcherRunID);
	fprintf(saveFile, "%d\n", GlobalDB->ProjectRunID);
	fprintf(saveFile, "%d\n", GlobalDB->QuoteRunID);
	fprintf(saveFile, "%d\n", GlobalDB->TaskRunID);
	fprintf(saveFile, "%s", GlobalDB->GlobalMessages);
	fclose(saveFile);
}

//free all allocated memory of the lists and global itself
void freeAdmins(Admin *AdminsList){
	Admin *pointer = AdminsList;
	while (AdminsList != 0){
		AdminsList = AdminsList->AdminNext;
		free(pointer);
		pointer = AdminsList;
	}
}

void freeStudents(Student *StudentsList){
	Student *pointer = StudentsList;
	while (StudentsList != 0){
		free(StudentsList->ProjectIDS);
		StudentsList = StudentsList->StudentNext;
		free(pointer);
		pointer = StudentsList;
	}
}

void freeWatchers(Watcher *WatchersList){
	Watcher *pointer = WatchersList;
	while (WatchersList != 0){
		free(WatchersList->ProjectIDS);
		WatchersList = WatchersList->WatcherNext;
		free(pointer);
		pointer = WatchersList;
	}
}

void freeProjects(Project *ProjectsList){
	Project *pointer = ProjectsList;
	while (ProjectsList != 0){
		free(ProjectsList->StudentsIDS);
		free(ProjectsList->TasksIDS);
		ProjectsList = ProjectsList->ProjectNext;
		free(pointer);
		pointer = ProjectsList;
	}
}

void freeQuotes(Quote *QuotesList){
	Quote *pointer = QuotesList;
	while (QuotesList != 0){
		QuotesList = QuotesList->QuoteNext;
		free(pointer);
		pointer = QuotesList;
	}
}

void freeTasks(Task *TasksList){
	Task *pointer = TasksList;
	while (TasksList != 0){
		TasksList = TasksList->TaskNext;
		free(pointer);
		pointer = TasksList;
	}
}

void freeMemory(Global *GlobalDB){
	freeAdmins(GlobalDB->AdminsList);
	freeStudents(GlobalDB->StudentList);
	freeWatchers(GlobalDB->WatchersList);
	freeProjects(GlobalDB->ProjectsList);
	freeQuotes(GlobalDB->QuotesList);
	freeTasks(GlobalDB->TaskList);
	free(GlobalDB);
}

// this functions will save all databases to files, deallocate memory and close program
void Exit(Global *GlobalDB){
	saveAdmins(GlobalDB->AdminsList);
	saveStudents(GlobalDB->StudentList);
	saveWatchers(GlobalDB->WatchersList);
	saveProjects(GlobalDB->ProjectsList);
	saveQuotes(GlobalDB->QuotesList);
	saveTasks(GlobalDB->TaskList);
	saveGlobal(GlobalDB);
	freeMemory(GlobalDB);
}

#endif