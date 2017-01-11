
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef enum { BAD, STUDENT, ADMIN, WATCHER }AccessGroup;
typedef enum { NEW, ELICITATION, ANALYSIS, VandV, APPROVED, TRASH }STATUS;
typedef enum { FALSE, TRUE }BOOL;
typedef enum { FILE_READ_ERROR, FILE_WRITE_ERROR } ERRORS;

typedef struct Project Project;
typedef struct Student Student;
typedef struct Watcher Watcher;
typedef struct Admin Admin;
typedef struct Watcher Watcher;
typedef struct Task Task;
typedef struct Quote Quote;
typedef struct Global Global;

typedef struct Student{
	AccessGroup Group;
	int StudentID, StudentProjectsAmount, StudentTasksAmount;
	char StudentUsername[31], StudentPassword[31], StudentName[21], StudentEmail[50], StudentSurename[21], StudentDepartment[21], StudentYear[1];
	int *ProjectIDS;
	char StudentMessages[31], StudentActivityLog[31];
	Student *StudentNext;
}Student;
typedef struct Quote{
	int QuoteID;
	char Quote[256], QuoteAuthor[31];
	Quote *QuoteNext;
}Quote;
typedef struct Project{
	int ProjectID, ProjectUsersAmount, ProjectTasksAmount;
	char ProjectName[128], ProjectCreatorName[31];
	int *StudentsIDS;
	int *TasksIDS;
	char ProjectMessages[31], ProjectActivityLogs[31];
	BOOL ProgramChanges;
	struct Project *ProjectNext;
	struct Task *TasksList;
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
	Watcher *WatcherNext;
}Watcher;
typedef struct Task{
	int TaskID;
	char TaskName[256], TaskCreatorName[31];
	STATUS TaskStatus;
	Task* TaskNext;
}Task;
typedef struct Global{
	int QuoteRunID, StudentRunID, WatcherRunID, AdminRunID,ProjectRunID;
	Student *StudentList;
	Watcher *WatchersList;
	Admin *AdminsList;
	Project *ProjectsList;
	Quote *QuotesList;
	char GlobalMessages[31];
}Global;