//Jonathan
#include "functions.h"

int main()
{
	Global *GlobalFile = (Global*)malloc(sizeof(Global));
	GlobalFile = InitDataBases();
	//CreateNewProject(NULL, GlobalFile); TODO: WHO ADDED THIS LINE??
	return 1;
}

////// Menus

//Project Menu : Finished ,Ready for testing - Jonathan
int ProjectMenu(Global* GlobalFile , Project* project, int accessGroup, int userID){
	//Showing project menu of projectID project based on the accessgroup of the user:
	Student* student;
	Admin* admin;
	Watcher* watcher;
	int opt = -1;
	char* username;

	//Saving user pointer based on accessgroup:

	switch (accessGroup){
	case STUDENT:
		student = FindStudent(GlobalFile, userID);
		username = student->StudentUsername;
		break;
	case ADMIN:
		admin = FindAdmin(GlobalFile, userID);
		username = admin->AdminUsername;
	case WATCHER:
		watcher = FindWatcher(GlobalFile, userID);
		username = watcher->WatcherUsername;
	default:
		//Error
		printf("ERROR\n\n"); //Should not happen because accessgroup is evaluated in login function
	}

	while (opt == -1){
		//These options are shared among watcher,user and admin:
		printf("0) Exit project menu\n");
		printf("1) Create a new task\n");
		printf("2) Print tasks list\n");
		printf("3) Print activity log\n");
		printf("4) Print project details\n");
		printf("5) Add users to Project\n");
		printf("6) Change task status\n");

		switch (accessGroup){

		case ADMIN://This option is for admin only:
			printf("7) Remove Project\n");
			break;
		case WATCHER: //These options are for watcher only:
			printf("7) Leave a message to a student\n");
			printf("8) Add a project message\n");
			break;
		}
		
		scanf("%d", &opt);

		switch (opt){

		case 0:
			//Exit to upper menu
			return 1;
		case 1:
			CreateNewTask(project, username);
			break;
		case 2:
			PrintTasksList(project);
			break;
		case 3:
			PrintActivityLog(project);
			break;
		case 4:
			PrintProjectDetails(project);
			break;
		case 5:
			AddUsersToProject(GlobalFile, project);
			break;
		case 6:
			ChangeTaskStatus(project);
			break;

		case 7:
			switch (accessGroup){

			case ADMIN:
				RemoveProject(project);
				break;
			case WATCHER:
				LeaveMessageToStudent(project, watcher);
				break;
			}
			break;

		case 8:
			if (accessGroup == WATCHER){ //The last option is only for watcher
				AddProjectMessage(project, watcher);
				break;
			}
		default:
			//Dosomething
		}
		opt = -1; //Reseting option before relaunching project menu
		system("cls");  //Clearing screen before relaunhing project menu
	}
	return 0;
}

//Finished - Ready for testing - Jonathan
int StudentMenu(Global *GlobalFile, int studentID){
	int status = 0, opt = -1, projectID = 0;
	Student* student = FindStudent(GlobalFile->StudentList, studentID);
	Project* project = NULL;
	while (opt == -1){

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

		scanf("%d",&opt);
		switch (opt){

		case 1:
			CreateNewProject(GlobalFile,student); //3
			break;
		case 2:
			PrintProjectsList(student); // 13
			break;

		case 3:
			printf("Enter Project ID:\n");
			scanf("%d\n", &projectID);
			project = FindProject(GlobalFile->ProjectsList, projectID);
			if (project == NULL){
				//Project not found 
				printf("No project of that ID\n");
				break;
			}
			ProjectMenu(GlobalFile,project, STUDENT, studentID);
			break;
		case 4:
			//Might be good to transfer that part into ShowTasksByStatus, leaving it that way for now
			printf("Available Status:\n");
			printf("[0] New , [1] Elicitation, [2] Analysis, [3] VandV, [4] Approved\n ");
			printf("Enter an integer of your choice:\n");
			scanf("%d\n", &status);
			ShowTasksByStatus(studentID, status);
			break;
		case 5:
			UpdateDetails(student); // 19
			break;
		case 6:
			PrintStudentLog(student); // 11
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

int AdminMenu(Global* GlobalFile ,int adminID){
	Admin* admin = FindAdmin(GlobalFile->AdminsList, adminID);
	int opt = -1, projectID;
	Project* project = NULL;
	while (opt == -1){
		printf("0) Exit Admin Menu\n");
		printf("1) Delete User\n");
		printf("2) Add a new User\n");
		printf("3) Print all users information\n");
		printf("4) Promote user to admin\n");
		printf("5) Show user details\n");
		printf("6) Update details\n");
		printf("7) Print Projects List\n");
		printf("8) Enter Project Menu\n");
		printf("9) Add a global message\n");
		printf("10) Add a global random quote\n");
		printf("11) View Quotes\n");
		scanf("%d", &opt);
		switch (opt){
		case 0:
			return 1;
		case 1:
			DeleteUser(GlobalFile);
			break;
		case 2:
			AddNewUser(GlobalFile);
			break;
		case 3:
			PrintAllUsers(GlobalFile);
		case 4: 
			PromoteUserToAdmin(GlobalFile);
			break;
		case 5:
			ShowUserDetails(GlobalFile);
		case 6:
			UpdateDetails(GlobalFile, admin);
		case 7:
			PrintProjectsList(GlobalFile, adminID, ADMIN);
			break;
		case 8:
			printf("Enter Project ID:\n");
			scanf("%d\n", &projectID);
			project = FindProject(GlobalFile->ProjectsList, projectID);
			if (project == NULL){
				//Project not found 
				printf("No project of that ID\n");
				break;
			}
			ProjectMenu(GlobalFile, project, ADMIN, adminID);
			break;
		case 9: 
			AddGlobalMessage(GlobalFile, admin);
			break;
		case 10:
			AddNewQuote(GlobalFile); //An Add quote function exists, need to write one that uses it from the menu 
			break;
		case 11:
			PrintQuotes(GlobalFile);
		default:
			printf("No such option\n");
		}
		system("cls");
		opt = -1;
	}


	return 0;
}

int WatcherMenu(Global* GlobalFile ,int watcherID){
	Watcher* watcher = FindWatcher(GlobalFile->WatchersList, watcherID);

	int opt = -1, projectID;

	while (opt == -1){
		printf("1) Print list of projects you're watching\n");
		printf("2) Print list of all projects\n");
		printf("3) Enter Project menu of a Project you're watching\n");
		printf("4) Update details\n");

		switch (opt){
		}
	}


	return 0;
}


int MainMenu(Global* GlobalFile , int ID){

	//According to the access group, launching relevant menu:
	int accessGroup = 0;
	if (ID > 0 && ID <= 1000) return StudentMenu(GlobalFile, ID);
	else if (ID > 1000 && ID <= 2000) return AdminMenu(GlobalFile,ID);
	else if (ID > 2000 && ID <= 3000) return WatcherMenu(GlobalFile, ID);
	else printf("\n\nError Evaluating Access Group\n\n");
	Exit();

}

void LoginMenu(Global* GlobalFile){

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
		if (MainMenu(GlobalFile,ID)) LoginMenu(GlobalFile);
	}
}
