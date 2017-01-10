#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

typedef enum { STUDENT = 1, ADMIN, WATCHER }AccessGroup;
typedef enum { FALSE, TRUE }BOOL;

typedef struct Project Project;
typedef struct Student Student;
typedef struct Student{
	AccessGroup Group;
	int StudentID, StudentProjectsAmount, StudentTasksAmount;
	char StudentUsername[31], StudentPassword[31], StudentName[21], StudentEmail[50], StudentSurename[21], StudentDepartment[21], StudentYear[1];
	int *ProjectIDS;
	Project *ProjectList;
	char StudentMessages[31], StudentActivityLog[31];
	Student *StudentNext;
}Student;

typedef struct Watcher Watcher;
typedef struct Admin Admin;
typedef struct Global{
	int QuoteRunID, StudentRunID, WatcherRunID, AdminRunID;
	Student *StudentList;
	Watcher *WatchersList;
	Admin *AdminsList;
	char GlobalMessages[31];
}Global;

typedef struct Quote{
	int QuoteID;
	char Quote[256], QuoteAuthor[31];
	struct Quote *QuoteNext;
}Quote;

typedef struct Watcher Watcher;
typedef struct Task Task;
typedef struct Project{
	int ProjectID, ProjectUsersAmount, ProjectTasksAmount;
	char ProjectName[128], ProjectCreatorName[31];
	Watcher *WatchersList;
	Student *StudentsList;
	Task *TaskList;
	char ProjectMessages[31], ProjectActivityLogs[31];
	BOOL ProgramChanges;
	Project *ProjectNext;
}Project;

typedef struct Admin{
	int AdminID;
	char AdminUsername[31], AdminPassword[31], AdminName[21], AdminSurename[21];
	AccessGroup Group;
	Admin *AdminNext;
}Admin;

typedef struct Watcher{
	AccessGroup Group;
	int WatcherID, WatcherProjectsAmount;
	char WatcherUsername[31], WatcherPassword[31], WatcherName[21], WatcherSurename[21], WatcherEmail[50];
	Project *ProjectsList;
	BOOL WatcherReceiveChanges;
	Watcher *WatcherNext;
}Watcher;

typedef struct Task{
	int TaskID;
	char TaskName[256], TaskCreatorName[31];
	AccessGroup Group;
	Task* TaskNext;
}Task;