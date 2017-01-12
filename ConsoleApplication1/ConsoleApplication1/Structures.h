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
	char StudentUsername[31], StudentPassword[31], StudentName[21], StudentEmail[50], StudentSurename[21], StudentDepartment[21], StudentYear[1];
	int *ProjectIDS;
	char StudentMessages[31], StudentActivityLog[31];
	Student *StudentNext;
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
//
//	Linked list functions start
//
// Find element by id
Student *FindStudent(Student* head, int StudentID)
{
	Student *current = head;
	while (current)
	{
		if (current->StudentID == StudentID)
			return current;
		current = current->StudentNext;
	}

	return NULL;
}
Admin *FindAdmin(Admin *head, int AdminID)
{
	Admin *current = head;
	while (current)
	{
		if (current->AdminID == AdminID)
			return current;
		current = current->AdminNext;
	}

	return NULL;
}
Watcher *FindWatcher(Watcher* head, int WatcherID)
{
	Watcher *current = head;
	while (current)
	{
		if (current->WatcherID == WatcherID)
			return current;
		current = current->WatcherNext;
	}

	return NULL;
}
Project *FindProject(Project* head, int ProjectID)
{
	Project *current = head;
	while (current)
	{
		if (current->ProjectID == ProjectID)
			return current;
		current = current->ProjectNext;
	}

	return NULL;
}
// search in list end
// Add to lists
Student *AddStudent(Student *studentHead, Student*addStudent)
{
	if (studentHead == NULL)
	{
		studentHead = addStudent;
		studentHead->StudentNext = NULL;
		return studentHead;
	}
	Student *current = studentHead, *Previous = NULL;
	while (current)
	{
		Previous = current;
		current = current->StudentNext;
	}
	Previous->StudentNext = addStudent;
	addStudent->StudentNext = NULL;
	return studentHead;
}
Admin *AddAdmin(Admin *adminHead, Admin*addAdmin)
{
	if (adminHead == NULL)
	{
		adminHead = addAdmin;
		adminHead->AdminNext = NULL;
		return adminHead;
	}
	Admin *current = adminHead, *Previous = NULL;
	while (current)
	{
		Previous = current;
		current = current->AdminNext;
	}
	Previous->AdminNext = addAdmin;
	addAdmin->AdminNext = NULL;
	return adminHead;
}
Watcher *AddWatcher(Watcher *watcherHead, Watcher *addWatcher)
{
	if (watcherHead == NULL)
	{
		watcherHead = addWatcher;
		watcherHead->WatcherNext = NULL;
		return watcherHead;
	}
	Watcher *current = watcherHead, *Previous = NULL;
	while (current)
	{
		Previous = current;
		current = current->WatcherNext;
	}
	Previous->WatcherNext = addWatcher;
	addWatcher->WatcherNext = NULL;
	return watcherHead;
}
Project *AddProject(Project *projectHead, Project *addProject)
{
	if (projectHead == NULL)
	{
		projectHead = addProject;
		projectHead->ProjectNext = NULL;
		return projectHead;
	}
	Project *current = projectHead, *Previous = NULL;
	while (current)
	{
		Previous = current;
		current = current->ProjectNext;
	}
	Previous->ProjectNext = addProject;
	addProject->ProjectNext = NULL;
	return projectHead;
}
Quote *AddQuote(Quote *QuoteHead, Quote *addQuote)
{
	if (QuoteHead == NULL)
	{
		QuoteHead = addQuote;
		QuoteHead->QuoteNext = NULL;
		return QuoteHead;
	}
	Quote *current = QuoteHead, *Previous = NULL;
	while (current)
	{
		Previous = current;
		current = current->QuoteNext;
	}
	Previous->QuoteNext = addQuote;
	addQuote->QuoteNext = NULL;
	return QuoteHead;
}
Task *AddTask(Task *TasksHead, Task *addTask)
{
	if (TasksHead == NULL)
	{
		TasksHead = addTask;
		TasksHead->TaskNext = NULL;
		return TasksHead;
	}
	Task *current = TasksHead, *Previous = NULL;
	while (current)
	{
		Previous = current;
		current = current->TaskNext;
	}
	Previous->TaskNext = addTask;
	addTask->TaskNext = NULL;
	return TasksHead;
}
// 
// Print List's Functions
void PrintStudentList(Student *StudentHead)
{
	Student *s = StudentHead;
	printf("ID  Name\tSurename\tDepartment\tYear\tProjects\tTasks\n");
	while (s)
	{
		// print all student fields
		printf("%d   %s\t%s\t\t%s\t%s\t%d\t\t%d\n", s->StudentID, s->StudentName, s->StudentSurename, s->StudentDepartment, s->StudentYear, s->StudentProjectsAmount, s->StudentTasksAmount);
		s = s->StudentNext;
	}

}
//
//	Linked list functions end
//
