#include "functions.h"

void PrintTasksList(Global* GlobalFile, Project* Project){
	int i,j, status, taskID;
	Task* task;
	char* creator;
	char* taskName;

	printf("Tasks in project:\n");
	for (j = 1 ,i = 0; i < Project->ProjectTasksAmount; i++){
		task = FindTask(GlobalFile->TaskList, Project->TasksIDS[i]);
		status = task->TaskStatus;
		if (status == 5) //Trash and won't show it
			continue;
		taskID = task->TaskID;
		creator = task->TaskCreatorName;
		taskName = task->TaskName;
		
		printf("---\n");
		printf("%d) ID: %d Creator: %s Status: %d\n",j,taskID,creator,status);
		print("Task: %s\n\n", taskName);
		j++;
	}
}

void printActivityLog(Global* GlobalFile, Project* project){
	char BUFFER[400], *fileName = project->ProjectActivityLogs;
	FILE* file = fopen(fileName, "r");
	if (!file) return;

	while (fgets(BUFFER, 400, file)) printf("%s\n", BUFFER);
	fclose(file);
}




