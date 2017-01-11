
#include "DataBase.h"

int main()
{
	Global *GlobalFile = (Global*)malloc(sizeof(Global));
	GlobalFile = InitDataBases();
	CreateNewProject(NULL, GlobalFile);
	return 1;
}

////// Menus
int ProjectMenu(int projectID, int accessGroup, int userID){
	//Showing project menu of projectID project based on the accessgroup of the user:
	int opt = -1;

	switch (accessGroup){
		printf("0) Exit project menu\n");
		printf("1) Create a new task\n");
		printf("2) Print tasks list\n");
		printf("3) Print activity log\n");
		printf("4) Print project tasks\n");
		printf("5) Print project details\n");
		printf("6) Add users to Project\n");

	case STUDENT:
		printf("7) Change task status\n");
		printf("8) Show tasks by status\n");
		break;

		while (opt != -1){
			switch (opt){
			case 0:
				//Exit to upper menu
				return 1;
			case 1:

				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
			default:
				//Dosomething
				opt = -1;
			}
		}
	case ADMIN:

		printf("7) Remove Project\n");
		while (opt != -1){
			switch (opt){
			case 0:
				//Exit to upper menu
				return 1;
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
			case 7:
				break;
			case 8:
				break;
			default:
				//Dosomething
				opt = -1;
			}
			break;

	case WATCHER:
		printf("7) Change Task Status\n");
		printf("8) Leave a message to a student\n");

		while (opt != -1){
			switch (opt){
			case 0:
				//Exit to upper menu
				return 1;
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
			case 7:
				break;
			case 8:
				break;
			default:
				//Dosomething
				opt = -1;
			}
			break;
		}
		return 0;
		}
	}
}

int StudentMenu(Global *GlobalFile, Student *studentID){
	int status = 0, opt = -1, projectID = 0;

	while (opt != -1){

		printf("Welcome Student:\n");
		printf("##########################\n");
		printf("Choose an option: (Int)\n\n");
		printf("1) Create new project\n");
		printf("2) Print existing projects\n");
		printf("3) Enter Project menu\n");
		printf("4) Show tasks by status\n");
		printf("5) Update details\n");
		printf("6) Print last actions\n");
		printf("7) Exit Mesimaster\n");


		opt = getchar();
		switch (opt){

		case 1:
			CreateNewProject(GlobalFile,studentID); //3 - edited by alexey
			break;
		case 2:
			PrintProjectsList(studentID); // 13
			break;

		case 3:
			printf("Enter Project ID:\n");
			scanf("%d\n", &projectID);
			ProjectMenu(projectID, STUDENT, studentID);
			break;
		case 4:
			printf("Available Status:\n");
			printf("[0] New , [1] Elicitation, [2] Analysis, [3] VandV, [4] Approved\n ");
			printf("Enter an integer of your choice:\n");
			scanf("%d\n", &status);
			ShowTasksByStatus(studentID, status);
			break;
		case 5:
			UpdateDetails(studentID); // 19
			break;
		case 6:
			PrintStudentLog(studentID); // 11
			break;
		case 7:
			return 1;
		default:
			//Dosomething
			system("cls");
			opt = -1;
		}
		system("cls");
	}

	return 0;

}

int AdminMenu(int ID){

	printf("X) Delete User\n");
	printf("X) Add a new User\n");
	printf("X) Promote user to admin\n");
	printf("X) Show user details\n");
	printf("X) Update details\n");

	return 0;
}

int WatcherMenu(int ID){

	printf("X) Update details\n");

	return 0;
}


int MainMenu(int ID){

	//According to the access group, launching relevant menu:
	int accessGroup = 0;
	if (ID > 0 && ID <= 1000) return StudentMenu(ID);
	else if (ID > 1000 && ID <= 2000) return AdminMenu(ID);
	else if (ID > 2000 && ID <= 3000) return WatcherMenu(ID);
	else printf("\n\nError Evaluating Access Group\n\n");
	//Save();
	//Exit();

}

int Login(){

	return 1;
}
void LoginMenu(){

	int ID = 0, opt = -1;

	while (opt != -1){

		printf("Welcome to the MesiMaster:\n");
		printf("##########################\n");
		printf("Choose an option: (Int)\n\n");
		printf("1) Login with an existing user\n");
		printf("2) Register a new user\n");

		opt = getchar();
		switch (opt){

		case 1:
			printf("Executing Login function");
			ID = Login();
			break;
		case 2:
			printf("Exexcuting Register function");
			ID = Register();
			break;
		default:
			//Dosomething
			system("cls");
			opt = -1;
		}
		system("cls");
		if (MainMenu(ID)) LoginMenu();
	}
}
