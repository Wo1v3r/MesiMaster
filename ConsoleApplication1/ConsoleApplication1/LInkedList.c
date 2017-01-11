#include "Structures.h"
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
// add functions end

// Print List Functions
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