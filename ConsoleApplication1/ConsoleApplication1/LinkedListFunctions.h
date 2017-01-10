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