//Jonathan

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define BACK = 1;

typedef enum Access{ BAD = 0, STUDENT, ADMIN, WATCHER };

int ProjectMenu(int projectID, int accessGroup, int userID){

	return 0;
}

int StudentMenu(int studentID){
	int opt = -1, projectID = 0;

	while (opt != -1){

		printf("Welcome Student:\n");
		printf("##########################\n");
		printf("Choose an option: (Int)\n\n");
		printf("1) Create new project\n");
		printf("2) Print existing projects\n");
		printf("3) Enter Project menu\n");
		printf("4) Update details\n");
		printf("5) Print last actions\n");
		printf("6) Exit Mesimaster\n");


		opt = getchar();
		switch (opt){

		case 1:
			CreateNewProject(studentID); //3
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
			UpdateDetails(studentID); // 19
			break;

		case 5:
			PrintStudentLog(studentID); // 11
			break;
		case 6:
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

void AdminMenu(int ID){


}

void WatcherMenu(int ID){


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
		MainMenu(ID);
	}
}