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
	FILE * read = fopen(StudentsFilePath, "r");
	if (read == NULL){
		printf("Error opening the students file.\n");
		return NULL;
	}
	else{
		while (!feof(read)){
			newStud = (Student*)(malloc(sizeof(Student)));
			head = AddStudent(head, newStud);
			fscanf(read, "%d", &newStud->StudentID);
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
		}
	}
	fclose(read);
	return head;
}

Project* initProjects(){
	Project* head = NULL, *newProj;
	FILE * read = fopen(ProjectsFilePath, "r");
	if (read == NULL){
		printf("Error opening the projects file.\n");
		return NULL;
	}
	else{
		while (!feof(read)){
			newProj = (Project*)(malloc(sizeof(Project)));
			head = AddProject(head, newProj);
			fscanf(read, "%d", &newProj->ProjectID);
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
		while (!feof(read)){
			newWatcher = (Watcher*)(malloc(sizeof(Watcher)));
			head = AddWatcher(head, newWatcher);
			fscanf(read, "%d", &newWatcher->WatcherID);
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
		while (!feof(read)){
			newAdmin = (Admin*)(malloc(sizeof(Admin)));
			head = AddAdmin(head, newAdmin);
			fscanf(read, "%d", &newAdmin->AdminID);
			fscanf(read, "%s", &newAdmin->AdminUsername);
			fscanf(read, "%s", &newAdmin->AdminPassword);
			fscanf(read, "%s", &newAdmin->AdminName);
			fscanf(read, "%s", &newAdmin->AdminSurename);
			fscanf(read, "%d", &newAdmin->Group);
		}
	}
	fclose(read);
	return head;
}

Task* initTasks(){
	Task* head = NULL, *newTask;
	FILE * read = fopen(TasksFilePath, "r");
	if (read == NULL){
		printf("Error opening the tasks file.\n");
		return NULL;
	}
	else{
		while (!feof(read)){
			newTask = (Task*)(malloc(sizeof(Task)));
			head = AddTask(head, newTask);
			fscanf(read, "%d", &newTask->TaskID);
			fscanf(read, "%s", &newTask->TaskName);
			fscanf(read, "%d", &newTask->TaskStatus);
			fscanf(read, "%s", &newTask->TaskCreatorName);
		}
	}
	fclose(read);
	return head;
}

Quote* initQuotes(){
	Quote* head = NULL, *newQuote;
	int i;
	FILE * read = fopen(QuotesFilePath, "r");
	if (read == NULL){
		printf("Error opening the quotes file.\n");
		return NULL;
	}
	else{
		while (!feof(read)){
			newQuote = (Quote*)(malloc(sizeof(Quote)));
			head = AddQuote(head, newQuote);
			i = 0;
			fscanf(read, "%d", &newQuote->QuoteID);
			fgetc(read);
			fgets(newQuote->Quote, sizeof(newQuote->Quote), read);
			while (newQuote->Quote[i++] != '\n');
			newQuote->Quote[i - 1] = '\0';
			fscanf(read, "%s", &newQuote->QuoteAuthor);
		}
	}
	fclose(read);
	return head;
}

Global *InitDataBases(){
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
	GlobalDB->TaskList = initTasks();
	GlobalDB->ProjectsList = initProjects();
	fscanf(globalFile, "%d", &GlobalDB->StudentRunID);
	fscanf(globalFile, "%d", &GlobalDB->AdminRunID);
	fscanf(globalFile, "%d", &GlobalDB->WatcherRunID);
	fscanf(globalFile, "%d", &GlobalDB->ProjectRunID);
	fscanf(globalFile, "%d", &GlobalDB->QuoteRunID);
	fscanf(globalFile, "%d", &GlobalDB->TaskRunID);
	fscanf(globalFile, "%s", &GlobalDB->GlobalMessages);
	fclose(globalFile);
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
}

void saveStudents(Student *StudentList){
	FILE *saveFile = fopen(StudentsFilePath, "r");
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
}

void saveWatchers(Watcher *WatchersList){
	FILE *saveFile = fopen(WatchersFilePath, "r");
	if (!saveFile){
		printf("Warning ! File %s can't be opened.\n", StudentsFilePath);
		exit(1);
	}

}

void saveProjects(Project *ProjectsList){

}

void saveQuotes(Quote *QuotesList){

}

void saveTasks(Task *TaskList){

}

void saveGlobal(Global *GlobalDB){

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
}