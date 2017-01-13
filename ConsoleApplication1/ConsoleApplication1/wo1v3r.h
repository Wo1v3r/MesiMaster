#include "functions.h"

void PrintTasksList(Global* GlobalFile, Project* Project){
	int i, status;
	Task* task;
	char* creator;

	printf("Tasks in project:\n");
	for (i = 0; i < Project->ProjectTasksAmount; i++){
		task = FindTask(GlobalFile->TaskList, Project->TasksIDS[i]);
		status = task->TaskStatus;
		if (status == 5) //Trash and won't show it
			continue;

		printf("---\n");
		printf("%d) ID: %d Creator: %s Status: %d",task->TaskID,task->TaskCreatorName,task->TaskStatus);
		print("Task: %s", task->TaskName);
		/*int TaskID;
		char TaskName[256], TaskCreatorName[31];
		STATUS TaskStatus;
		Task* TaskNext;*/
	}
}