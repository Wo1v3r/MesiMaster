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

//UNFINISHED
void printProjectDetails(Global* GlobalFile, Project* project){
	int projectID = project->ProjectID,
		numOfTasks = project->ProjectTasksAmount,
		numOfUsers = project->ProjectUsersAmount;
	char* creator = project->ProjectCreatorName, projectName = project->ProjectName;

	printf("Project Details:\n");
	printf("-------------------");
	printf("ID: %d , Number of tasks: %d , Number of users: %d , Creator: %s", projectID, numOfTasks, numOfUsers, creator);

	//Need to print details of student here too.
	
}

void ChangeTaskStatus(Global* GlobalFile, Project* project, int userID, int accessGroup){
	int taskID, i,status;
	Task* task;
	//Getting a task from the user:

	printf("Enter Task ID:\n");
	scanf("%d", &taskID);
	//Making sure that task is in the relevant project:
	task = findTaskInProject(GlobalFile, project, taskID);
	if (!task){
		printf("Task does not belong to this project\n");
		return;
	}

	printf("Current status is: %s\n", convertStatusToString(task->TaskStatus));
	printf("Choose status to change into:\n");
	printf("Available Status:\n");
	printf("[0] New , [1] Elicitation, [2] Analysis, [3] VandV ");
	if (accessGroup != 1) printf(" [4] Approved"); //Student can't change to approved
	printf("\n");
	printf("Enter an integer of your choice:\n");
	scanf("%d", &status);
}


