#include "MinUnit.h"
#include "functions.h"
/*
FOR RUNNING THE TESTS COPY THEM BEFORE THE MAIN FUNCTION.
ADD include for minunit.h
#include "MinUnit.h"
in the main function add
MU_RUN_SUITE(InitTest);

These tests are built on the given txt files. any change will need to be change in accordance with them!!!
if you wish to run the programm as usual comment this whole file.
*/

//Init Suite tests:
MU_TEST(test_init_student){
	Student *check = initStudents();
	mu_check(check->StudentID == 1000);
	mu_check(strcmp(check->StudentUsername, "isabeme") == 0);
	mu_check(strcmp(check->StudentPassword, "AAbb12") == 0);
	mu_check(strcmp(check->StudentName, "Isabelle") == 0);
	mu_check(strcmp(check->StudentSurename, "Meif") == 0);
	mu_check(strcmp(check->StudentEmail, "isabeme@sce.ac.il") == 0);
	mu_check(strcmp(check->StudentDepartment, "Chemistry") == 0);
	mu_check(check->StudentYear == 'b');
	mu_check(strcmp(check->StudentActivityLog, "1000_SLog.txt") == 0);
	mu_check(check->Group == 1);
	mu_check(check->StudentProjectsAmount == 1);
	mu_check(check->ProjectIDS[0] == 4000);
	mu_check(check->StudentTasksAmount == 3);
	mu_check(strcmp(check->StudentMessages, "1000_SMess.txt") == 0);
	freeStudents(check);
}

MU_TEST(test_init_projects){
	Project *check = initProjects();
	mu_check(check->ProjectID == 4000);
	mu_check(strcmp(check->ProjectName, "meistertask") == 0);
	mu_check(strcmp(check->ProjectCreatorName, "Isabelle") == 0);
	mu_check(strcmp(check->ProjectActivityLogs, "4000_ProjectActivityLog.txt") == 0);
	mu_check(check->ProjectUsersAmount == 3);
	mu_check(check->StudentsIDS[0] == 1000);
	mu_check(check->StudentsIDS[1] == 1001);
	mu_check(check->StudentsIDS[2] == 3000);
	mu_check(check->ProjectTasksAmount == 3);
	mu_check(check->TasksIDS[0] == 6000);
	mu_check(check->TasksIDS[1] == 6001);
	mu_check(check->TasksIDS[2] == 6002);
	mu_check(strcmp(check->ProjectMessages, "4000_ProjectMessages.txt") == 0);
	freeProjects(check);
}

MU_TEST(test_init_watchers){
	Watcher *check = initWatchers();
	mu_check(check->WatcherID == 3000);
	mu_check(strcmp(check->WatcherUsername, "hHasidim") == 0);
	mu_check(strcmp(check->WatcherPassword, "pasS987") == 0);
	mu_check(strcmp(check->WatcherName, "Hadas") == 0);
	mu_check(strcmp(check->WatcherSurename, "Hasidim") == 0);
	mu_check(strcmp(check->WatcherEmail, "hadas@sce.ac.il") == 0);
	mu_check(check->Group == 3);
	mu_check(check->WatcherReceiveChanges == 0);
	mu_check(check->WatcherProjectsAmount == 2);
	mu_check(check->ProjectIDS[0] == 4001);
	mu_check(check->ProjectIDS[1] == 4000);
	freeWatchers(check);
}

MU_TEST(test_init_admins){
	Admin *check = initAdmins();
	mu_check(check->AdminID == 2000);
	mu_check(strcmp(check->AdminUsername, "Dubi") == 0);
	mu_check(strcmp(check->AdminPassword, "purr") == 0);
	mu_check(strcmp(check->AdminName, "Kuki") == 0);
	mu_check(strcmp(check->AdminSurename, "Leon") == 0);
	mu_check(check->Group == 2);
	freeAdmins(check);
}

MU_TEST(test_init_tasks){
	Task *check = initTasks();
	mu_check(check->TaskID == 6000);
	mu_check(strcmp(check->TaskName, "do something please #1") == 0);
	mu_check(check->TaskStatus == 0);
	mu_check(strcmp(check->TaskCreatorName, "Isabelle") == 0);
	freeTasks(check);
}

MU_TEST(test_init_quotes){
	Quote *check = initQuotes();
	mu_check(check->QuoteID == 5000);
	mu_check(strcmp(check->Quote, "You have to think anyway, so why not think big? ") == 0);
	mu_check(strcmp(check->QuoteAuthor, "D.Trump") == 0);
	freeQuotes(check);
}

MU_TEST(test_init_global){
	Global *check = initGlobal();
	mu_check(check->StudentRunID == 1004);
	mu_check(check->AdminRunID == 2003);
	mu_check(check->WatcherRunID == 3002);
	mu_check(check->ProjectRunID == 4002);
	mu_check(check->QuoteRunID == 5025);
	mu_check(check->TaskRunID == 6006);
	mu_check(strcmp(check->GlobalMessages, "Good Luck on the exams everyone!") == 0);
	free(check);
}

//Init Suite
MU_TEST_SUITE(InitTest){
	MU_RUN_TEST(test_init_student);
	MU_RUN_TEST(test_init_projects);
	MU_RUN_TEST(test_init_watchers);
	MU_RUN_TEST(test_init_admins);
	MU_RUN_TEST(test_init_tasks);
	MU_RUN_TEST(test_init_quotes);
	MU_RUN_TEST(test_init_global);
}


//Utilities Suite Tests
MU_TEST(test_update_details){
	Global* g = InitDataBases();
	//Trying to update details of Watcher,Student and Admin:, these all exist:
	Student* student = FindStudentByUN(g, "isabeme");
	Admin* admin = FindAdminByUN(g, "Dubi");
	Watcher* watcher = FindWatcherByUN(g, "davidBI");
	char tempPass[31], tempName[31], tempSurname[31];

	//First trying to update a student with a bad password, password won't change:
	strcpy(tempPass, student->StudentPassword);
	strcpy(tempName, student->StudentName);
	strcpy(tempSurname, student->StudentSurename);

	UpdateDetails(g, student->StudentID, "abc", NULL, NULL, 1, 1, 1);

	mu_check(strcmp(student->StudentPassword, tempPass) == 0); //Same pass as before updatedetails

	//Trying to update a watcher, updating only name and surname:
	strcpy(tempName, watcher->WatcherName);
	strcpy(tempSurname, watcher->WatcherSurename);
	UpdateDetails(g, watcher->WatcherID, "adb", "Mike", "Like", 1, 1, 1); //By providing a bad pass

	mu_check(strcmp(watcher->WatcherName, "Mike") == 0);
	mu_check(strcmp(watcher->WatcherSurename, "Like") == 0);

	//Trying to update an admin, changing all fields:
	strcpy(tempPass, admin->AdminPassword);
	strcpy(tempName, admin->AdminName);
	strcpy(tempSurname, admin->AdminSurename);
	UpdateDetails(g, admin->AdminID, "R1s", "Robert", "Stir", 1, 1, 1); //Pass is valid 

	mu_check(strcmp(admin->AdminPassword, "R1s") == 0);
	mu_check(strcmp(admin->AdminName, "Robert") == 0);
	mu_check(strcmp(admin->AdminSurename, "Stir") == 0);

	freeMemory(g);

}
MU_TEST(test_find_accessgroup){
	int studentID = 1000, adminID = 2000, watcherID = 3000, badID1 = 999, badID2 = 4000;
	mu_check(FindAccessGroup(studentID) == 1);
	mu_check(FindAccessGroup(adminID) == 2);
	mu_check(FindAccessGroup(watcherID) == 3);
	mu_check(FindAccessGroup(badID1) == 0);
	mu_check(FindAccessGroup(badID2) == 0);
}

MU_TEST(test_FindAdminByUN){
	//Finds admin by username
	char* adminUN = "Dubi"; //Good username - sould provide the right info
	char* badUN = "Wo1v3r";//Bad username - should return NULL
	//Loading file:
	Global* global = InitDataBases();
	mu_check(FindAdminByUN(global, adminUN) != NULL); //Check that the admin was found
	mu_check(strcmp(FindAdminByUN(global, adminUN)->AdminUsername, adminUN) == 0); //Check that the admin is actually the right one
	mu_check(FindAdminByUN(global, badUN) == NULL); //Check that bad username not found
	freeMemory(global);
}

MU_TEST(test_FindWatcherByUN){
	//Finds watcher by username
	char* watcherUN = "davidBI"; //Good username - sould provide the right info
	char* badUN = "Wo1v3r";//Bad username - should return NULL
	//Loading file:
	Global* global = InitDataBases();
	mu_check(FindWatcherByUN(global, watcherUN) != NULL); //Check that the admin was found
	mu_check(strcmp(FindWatcherByUN(global, watcherUN)->WatcherUsername, watcherUN) == 0); //Check that the admin is actually the right one
	mu_check(FindWatcherByUN(global, badUN) == NULL); //Check that bad username not found
	freeMemory(global);
}

MU_TEST(test_FindStudentByUN){
	//Finds student by username
	char* studentUN = "isabeme"; //Good username - sould provide the right info
	char* badUN = "Wo1v3r";//Bad username - should return NULL
	//Loading file:
	Global* global = InitDataBases();
	mu_check(FindStudentByUN(global, studentUN) != NULL); //Check that the admin was found
	mu_check(strcmp(FindStudentByUN(global, studentUN)->StudentUsername, studentUN) == 0); //Check that the admin is actually the right one
	mu_check(FindStudentByUN(global, badUN) == NULL); //Check that bad username not found
	freeMemory(global);
}

MU_TEST(test_watcher_to_admin){
	Global* global = InitDataBases();
	int oldRunID = global->AdminRunID;
	int oldUsersnum = FindProject(global->ProjectsList, 4000)->ProjectUsersAmount;
	Admin* newAd = WatcherToAdmin(global, FindWatcher(global->WatchersList, 3000));
	mu_check(newAd != NULL);
	mu_check(global->AdminRunID - 1 == oldRunID);
	mu_check(FindWatcher(global->WatchersList, 3000) == NULL);
	mu_check(newAd->AdminID == oldRunID);
	mu_check(strcmp(newAd->AdminName, "Hadas") == 0);
	mu_check(strcmp(newAd->AdminSurename, "Hasidim") == 0);
	mu_check(strcmp(newAd->AdminUsername, "hHasidim") == 0);
	mu_check(strcmp(newAd->AdminPassword, "pasS987") == 0);
	mu_check(newAd->Group == ADMIN);
	mu_check(oldUsersnum - FindProject(global->ProjectsList, 4000)->ProjectUsersAmount == 1);
	freeMemory(global);
}

MU_TEST(test_student_to_admin){
	Global* global = InitDataBases();
	int oldRunID = global->AdminRunID;
	int oldUsersnum = FindProject(global->ProjectsList, 4000)->ProjectUsersAmount;
	Admin* newAd = StudentToAdmin(global, FindStudent(global->StudentList, 1000));
	mu_check(newAd != NULL);
	mu_check(global->AdminRunID - 1 == oldRunID);
	mu_check(FindStudent(global->StudentList, 1000) == NULL);
	mu_check(newAd->AdminID == oldRunID);
	mu_check(strcmp(newAd->AdminName, "Isabelle") == 0);
	mu_check(strcmp(newAd->AdminSurename, "Meif") == 0);
	mu_check(strcmp(newAd->AdminUsername, "isabeme") == 0);
	mu_check(strcmp(newAd->AdminPassword, "AAbb12") == 0);
	mu_check(newAd->Group == ADMIN);
	mu_check(oldUsersnum - FindProject(global->ProjectsList, 4000)->ProjectUsersAmount == 1);
	freeMemory(global);
}

MU_TEST(test_Add_Task_ID_To_Project){
	Global* global = InitDataBases();
	Project *project = FindProject(global->ProjectsList, 4000);
	int oldTasknum = project->ProjectTasksAmount;
	mu_check(findTaskInProject(global, project, 6003) == NULL);
	AddTaskIDToProject(project, 6003);
	mu_check(findTaskInProject(global, project, 6003) != NULL);
	mu_check(project->ProjectTasksAmount == oldTasknum + 1);
	freeMemory(global);
}

MU_TEST(test_Add_project_ID_To_watcher){
	Global* global = InitDataBases();
	Watcher *watcher = FindWatcher(global->WatchersList, 3001);
	int oldProjnum = watcher->WatcherProjectsAmount;
	int i;
	for (i = 0; i < watcher->WatcherProjectsAmount; i++)
		if (watcher->ProjectIDS[i] == 4000)
			mu_fail("Shouldn't get here, project already in!");
	AddProjectIDToWatcher(watcher, 4000);
	mu_check(watcher->WatcherProjectsAmount == oldProjnum + 1);
	for (i = 0; i < watcher->WatcherProjectsAmount; i++)
		if (watcher->ProjectIDS[i] == 4000)
			mu_check(watcher->ProjectIDS[i] == 4000);
	freeMemory(global);
}

MU_TEST(test_Add_project_ID_To_student){
	Global* global = InitDataBases();
	Student *student = FindStudent(global->StudentList, 1000);
	int oldProjnum = student->StudentProjectsAmount;
	int i;
	for (i = 0; i < student->StudentProjectsAmount; i++)
		if (student->ProjectIDS[i] == 4001)
			mu_fail("Shouldn't get here, project already in!");
	AddProjectIDToStudent(student, 4001);
	mu_check(student->StudentProjectsAmount == oldProjnum + 1);
	for (i = 0; i < student->StudentProjectsAmount; i++)
		if (student->ProjectIDS[i] == 4001)
			mu_check(student->ProjectIDS[i] == 4001);
	freeMemory(global);
}

MU_TEST(test_RemoveProjectIDFromArray)
{
	//checks that the function actually removes a value from an array
	int *projIDs = (int*)malloc(4 * sizeof(int)), i, flag = 0;
	projIDs[0] = 4000;
	projIDs[1] = 4001;
	projIDs[2] = 4002;
	projIDs[3] = 4003;
	projIDs = RemoveProjectIDFromArray(projIDs, 4001, 4);
	for (i = 0; i < 3; i++)
		if (projIDs[i] == 4001)
			flag = 1;
	mu_check(flag == 0);
	free(projIDs);
}

MU_TEST(test_RemoveProjectFromUsers)
{
	//improve
	Global* global = InitDataBases();
	int projDel = RemoveProjectFromUsers(global, 4000);
	mu_check(projDel == 3);
	freeMemory(global);
}





MU_TEST(test_RemoveUserIDFromProject)
{
	//checks that the function actually removes a value from an array
	Project *mock = (Project*)malloc(sizeof(Project));
	int i, flag = 0;
	mock->ProjectUsersAmount = 4;
	mock->StudentsIDS = (int*)malloc(4 * sizeof(int));
	mock->StudentsIDS[0] = 1000;
	mock->StudentsIDS[1] = 1001;
	mock->StudentsIDS[2] = 1002;
	mock->StudentsIDS[3] = 1003;
	mock->StudentsIDS = RemoveUserIDFromProject(mock, 1002);
	for (i = 0; i < 3; i++)
		if (mock->StudentsIDS[i] == 1002)
			flag = 1;
	mu_check(flag == 0);
	free(mock->StudentsIDS);
	free(mock);
}

MU_TEST(test_RemoveUserFromProjects)
{
	Global* global = InitDataBases();
	Project *current = global->ProjectsList;
	int i, flag = 0;
	RemoveUserFromProjects(global, 1000);
	while (current)
	{
		for (i = 0; i < current->ProjectUsersAmount; i++)
		{
			if (current->StudentsIDS[i] == 1000)
			{
				flag = 1;
			}
		}
		current = current->ProjectNext;
	}
	mu_check(flag == 0);
	freeMemory(global);
}


//Utilities suite

MU_TEST_SUITE(Utilities){
	MU_RUN_TEST(test_find_accessgroup);
	MU_RUN_TEST(test_FindAdminByUN);
	MU_RUN_TEST(test_FindWatcherByUN);
	MU_RUN_TEST(test_FindStudentByUN);
	MU_RUN_TEST(test_watcher_to_admin);
	MU_RUN_TEST(test_student_to_admin);
	MU_RUN_TEST(test_update_details);
	MU_RUN_TEST(test_Add_Task_ID_To_Project);
	MU_RUN_TEST(test_Add_project_ID_To_watcher);
	MU_RUN_TEST(test_Add_project_ID_To_student);
	MU_RUN_TEST(test_RemoveProjectIDFromArray);
	MU_RUN_TEST(test_RemoveProjectFromUsers);
	MU_RUN_TEST(test_RemoveUserIDFromProject);
	MU_RUN_TEST(test_RemoveUserFromProjects);
}

//Register suite tests:

MU_TEST(test_student_register){
	//int StudentRegister(Global *g, char* nameTest, char* unTest, char* passTest, char* emailTest, char* departmentTest, char yearTest)
	Global* global = InitDataBases();

	//Trying to register a student with a bad password:
	mu_check(StudentRegister(global, "Jonathan", "Leon", "Johnleon24", "aab", "johnleon24@gmail.com", "Software", '2') == 0);

	//Trying to register a student with a taken username:
	mu_check(StudentRegister(global, "Jonathan", "Leon", "johnnyL", "A1b", "johnleon24@gmail.com", "Software", '2') == 0);

	//Trying to register a student with valid input:
	mu_check(StudentRegister(global, "Jonathan", "Leon", "Johnleon24", "A1b", "johnleon24@gmail.com", "Software", '2') != 0);

	//Checking if that user exists:
	mu_check(FindStudentByUN(global, "Johnleon24") != NULL);

	freeMemory(global);
}

MU_TEST(test_admin_register){

	Global* global = InitDataBases();
	//Trying to register an admin with a bad password:
	mu_check(AdminRegister(global, "Meister", "Master", "Meister123", "aab") == 0);

	//Trying to register an admin with a taken username:
	mu_check(AdminRegister(global, "Meister", "Master", "Dubi", "Aa1") == 0);

	//Trying to register an admin with valid input:
	mu_check(AdminRegister(global, "Meister", "Master", "Meister123", "Aa1") != 0);

	//Checking if that user exists:
	mu_check(FindAdminByUN(global, "Meister123") != NULL);




	freeMemory(global);
}

MU_TEST(test_watcher_register){
	Global* global = InitDataBases();
	//Trying to register a watcher with a bad password:
	mu_check(WatcherRegister(global, "Peter", "Parker", "Spiderman", "aab", "spiderman@marvel.com") == 0);

	//Trying to register a watcher with a taken username:
	mu_check(WatcherRegister(global, "Peter", "Parker", "davidBI", "Aa1", "spiderman@marvel.com") == 0);

	//Trying to register a watcher with valid input:
	mu_check(WatcherRegister(global, "Peter", "Parker", "Spiderman", "Aa1", "spiderman@marvel.com") != 0);

	//Checking if that user exists:
	mu_check(FindWatcherByUN(global, "Spiderman") != NULL);
}

MU_TEST_SUITE(Register_Suite){
	MU_RUN_TEST(test_student_register);
	MU_RUN_TEST(test_admin_register);
	MU_RUN_TEST(test_watcher_register);
}
//Login suite tests:
MU_TEST(test_login){
	Global* global = InitDataBases();
	//admin check
	mu_check(Login(global, "Dubi", "purr") == 2000);
	//watcher check
	mu_check(Login(global, "davidBI", "EErrDD1") == 3001);
	//student check
	mu_check(Login(global, "johnnyL", "eLr45e") == 1002);
	//bad check username
	mu_check(Login(global, "asdbfdgsdfg", "asd") == -1);
	//bad check password
	mu_check(Login(global, "Dubi", "asd") == 0);
	freeMemory(global);
}


MU_TEST_SUITE(Login_func_Suite){
	MU_RUN_TEST(test_login);
}


MU_TEST(test_check_password){
	//A valid password is one that contains: at least 1 digit, 1 uppercase letter, 1 lowercase letter.
	char* validPass1 = "Aa12Bb"; //A Good password
	char* validPass2 = "Bb8"; //Good password with minimal chars
	char* invalidPass1 = "BB8"; //Bad password with no lowercase
	char* invalidPass2 = "bb8"; //Bad password with no uppercase
	char* invalidPass3 = "bBeight"; //Bad password with no digits
	char* invalidPass4 = "'#$%";//Bad password with none of the requirements


	mu_check(CheckPassword(validPass1) == 1);
	mu_check(CheckPassword(validPass2) == 1);
	mu_check(CheckPassword(invalidPass1) == 0);
	mu_check(CheckPassword(invalidPass2) == 0);
	mu_check(CheckPassword(invalidPass3) == 0);
	mu_check(CheckPassword(invalidPass4) == 0);
}

MU_TEST(test_check_if_user_exists){
	//Checks if user exists by username, we will provide with both options:
	char* adminUN = "Dubi";
	char* studentUN = "johnnyL";
	char* watcherUN = "davidBI";
	char* badUN = "Wo1v3r";
	//Loading file:
	Global* global = InitDataBases();

	mu_check(CheckIfUserExists(global, adminUN) == 1);
	mu_check(CheckIfUserExists(global, studentUN) == 1);
	mu_check(CheckIfUserExists(global, watcherUN) == 1);
	mu_check(CheckIfUserExists(global, badUN) == 0);
	freeMemory(global);

}
MU_TEST_SUITE(Login_Suite){
	MU_RUN_TEST(test_check_password);
	MU_RUN_TEST(test_check_if_user_exists);
}


MU_TEST(test_delete_user){
	Global* global = InitDataBases();
	int id = 1001;
	mu_check(FindStudent(global->StudentList, id) != NULL);
	DeleteUser(global, id);
	mu_check(FindStudent(global->StudentList, id) == NULL);
	freeMemory(global);
}

MU_TEST(test_delete_quote){
	Global* global = InitDataBases();
	int id = 5000;
	mu_check(FindQuote(global->QuotesList, id) != NULL);
	DeleteQuote(global, id);
	mu_check(FindQuote(global->QuotesList, id) == NULL);
	freeMemory(global);
}

MU_TEST(test_promote_user){
	Global* global = InitDataBases();
	int id = 1001;//student
	int current_runID = global->AdminRunID;
	mu_check(FindAccessGroup(id) == 1);
	PromoteUserToAdmin(global, id);
	mu_check(FindAccessGroup((global->AdminRunID) - 1) == 2);
	id = 2000;//Admin
	mu_check(FindAccessGroup(id) == 2);
	PromoteUserToAdmin(global, id);
	mu_check(FindAccessGroup((global->AdminRunID) - 1) == 2);
	id = 3001;//Watcher
	mu_check(FindAccessGroup(id) == 3);
	PromoteUserToAdmin(global, id);
	mu_check(FindAccessGroup((global->AdminRunID) - 1) == 2);
	id = 9999;//Bad id
	mu_check(FindAccessGroup(id) == 0);
	PromoteUserToAdmin(global, id);
	mu_check(FindAccessGroup(id) == 0);
	mu_assert(global->AdminRunID - current_runID == 2, "Suppose to be 2!(2 promoted)");
	freeMemory(global);
}

MU_TEST(test_add_new_quote){
	Global* global = InitDataBases();
	int current_runID = global->QuoteRunID;
	AddNewQuote(global, "something", "something");
	mu_check(FindQuote(global->QuotesList, (global->QuoteRunID) - 1) != NULL);
	mu_assert(global->QuoteRunID - current_runID == 1, "Suppose to be 1!(1 new quote added)");
	freeMemory(global);
}

MU_TEST(test_global_message){
	Global* global = InitDataBases();
	AddGlobalMessage(global, "This Message entered");
	mu_check(strcmp(global->GlobalMessages, "This Message entered") == 0);
	freeMemory(global);
}

MU_TEST(test_remove_project){
	Global* global = InitDataBases();
	RemoveProject(global, global->ProjectsList, 'y');
	mu_check(FindProject(global->ProjectsList, 4000) == NULL);
	mu_check(FindStudent(global->StudentList, 1000)->StudentProjectsAmount == 0);
	mu_check(FindStudent(global->StudentList, 1000)->ProjectIDS == NULL);
	mu_check(FindStudent(global->StudentList, 1000)->StudentTasksAmount == 0);
	mu_check(FindStudent(global->StudentList, 1001)->StudentProjectsAmount == 0);
	mu_check(FindStudent(global->StudentList, 1001)->ProjectIDS == NULL);
	mu_check(FindStudent(global->StudentList, 1001)->StudentTasksAmount == 0);
	mu_check(FindWatcher(global->WatchersList, 3000)->WatcherProjectsAmount == 1);
	mu_check(FindWatcher(global->WatchersList, 3000)->ProjectIDS[0] == 4001);
	mu_check(FindTask(global->TaskList, 6000) == NULL);
	mu_check(FindTask(global->TaskList, 6001) == NULL);
	mu_check(FindTask(global->TaskList, 6002) == NULL);
	freeMemory(global);
}

MU_TEST_SUITE(Admin_Suite){
	MU_RUN_TEST(test_delete_user);
	MU_RUN_TEST(test_delete_quote);
	MU_RUN_TEST(test_promote_user);
	MU_RUN_TEST(test_add_new_quote);
	MU_RUN_TEST(test_global_message);
	MU_RUN_TEST(test_remove_project);
}

MU_TEST(test_leave_message_to_students){
	Global* global = InitDataBases();
	AddGlobalMessage(global, "This Message entered");
	mu_check(strcmp(global->GlobalMessages, "This Message entered") == 0);
	freeMemory(global);
}

MU_TEST(test_show_notifications){
	Global* global = InitDataBases();
	ShowNotifications(global, global->WatchersList, 'y');
	mu_check(global->WatchersList->WatcherReceiveChanges == TRUE);
	ShowNotifications(global, global->WatchersList, 'n');
	mu_check(global->WatchersList->WatcherReceiveChanges == FALSE);
	freeMemory(global);
}

MU_TEST_SUITE(Watcher_Suite){
	MU_RUN_TEST(test_leave_message_to_students);
	MU_RUN_TEST(test_show_notifications);
}


//Project Menu tests:

MU_TEST(test_create_project){
	char* projectName = "MyNewProject";
	Global* global = InitDataBases();
	int noSuchUserID = 1058, studentID = 1001;
	int projectFound = 0;
	Project* project;
	//Trying to create a new project using a user id that doesnt exist:
	mu_check(CreateNewProject(global, noSuchUserID, STUDENT, projectName) == 0); //Should not create the project
	//Trying to create a new project using an invalid access group:
	mu_check(CreateNewProject(global, studentID, BAD, projectName) == 0);
	//Trying to create a new project using normal paramaters:
	mu_check(CreateNewProject(global, studentID, STUDENT, projectName) == 1);
	//Check if that project exists:
	project = global->ProjectsList;
	while (project) {
		if (strcmp(project->ProjectName, projectName) == 0) projectFound = 1;
		project = project->ProjectNext;
	}
	mu_check(projectFound);

	freeMemory(global);
}
MU_TEST(test_create_task){
	char* taskName = "My Task";
	Global* global = InitDataBases();
	int noSuchUserID = 1058, studentID = 1001;
	int taskID = 0;

	Project *project = FindProject(global->ProjectsList, 4001); //Existing project - checked before this function
	mu_check((taskID = CreateNewTask(global, project, noSuchUserID, STUDENT, taskName)) == 0); //No such user
	mu_check((taskID = CreateNewTask(global, project, studentID, BAD, taskName)) == 0); //No such user acces group
	mu_check((taskID = CreateNewTask(global, project, studentID, STUDENT, taskName)) != 0); // Should pass and create new task

	//Checking if that task was created successfuly:
	mu_check(findTaskInProject(global, project, taskID) != NULL); //That task should exist

	freeMemory(global);
}

MU_TEST(test_add_user_to_project){
	int addStudent = 1, addWatcher = 2, Exit = 3, studentID = 1003, watcherID = 3000, doesNotExist = 1535;
	Global* global = InitDataBases();
	Project* project = FindProject(global->ProjectsList, 4000); //That project exists
	//Trying to exit, should return 1:
	mu_check(addUserToProject(global, project, studentID, Exit) == 1);
	//Trying to add a user that does not exist:
	mu_check(addUserToProject(global, project, doesNotExist, addStudent) == 0);
	//Trying to check if that user is in the project:
	mu_check(isStudentInProject(project, doesNotExist) == 0);
	//Trying to add a student:
	mu_check(addUserToProject(global, project, studentID, addStudent) == 1);
	//Checking if that student is in the project:
	mu_check(isStudentInProject(project, studentID) != 0);

}

MU_TEST(test_change_task_status){
	//int ChangeTaskStatus(Global* GlobalFile, Project* project, int userID, int accessGroup, int tasktest, int statustest); //Test written - Jonathan
	Global* global = InitDataBases();
	Project* project = FindProject(global->ProjectsList, 4000); //That projects exists for testing
	int studentID = 1000, watcherID = 3000, badID = 1956, taskID = 6000;
	Task* task = findTaskInProject(global, project, taskID);

	//Trying to change status to Approved by student : should not work:
	mu_check(ChangeTaskStatus(global, project, studentID, STUDENT, APPROVED, taskID) == 0);

	//Trying to change status to Approved by watcher : should work:
	mu_check(ChangeTaskStatus(global, project, watcherID, WATCHER, APPROVED, taskID) == 1);
	mu_check(task->TaskStatus == APPROVED);

	//Trying to change status to NEW:
	mu_check(ChangeTaskStatus(global, project, studentID, STUDENT, NEW, taskID) == 1);
	mu_check(task->TaskStatus == NEW);

	//Trying to change status to ELICITATION:
	mu_check(ChangeTaskStatus(global, project, studentID, STUDENT, ELICITATION, taskID) == 1);
	mu_check(task->TaskStatus == ELICITATION);

	//Trying to change status to ANALYSIS:
	mu_check(ChangeTaskStatus(global, project, studentID, STUDENT, ANALYSIS, taskID) == 1);
	mu_check(task->TaskStatus == ANALYSIS);

	//Trying to change status to VANDV:
	mu_check(ChangeTaskStatus(global, project, watcherID, WATCHER, VandV, taskID) == 1);
	mu_check(task->TaskStatus == VandV);


}
MU_TEST_SUITE(Project_Suite){

	MU_RUN_TEST(test_create_project);
	MU_RUN_TEST(test_create_task);
	MU_RUN_TEST(test_add_user_to_project);
	MU_RUN_TEST(test_change_task_status);
}

//Structures suite tests

MU_TEST(test_FindStudent_structures)
{
	//Finds student by ID
	int studentID = 1001; //Good ID - sould provide the right info
	int badID = 9999;//Bad ID - should return NULL
	//Loading file:
	Global* global = InitDataBases();
	mu_check(FindStudent(global->StudentList, studentID) != NULL);//Check that the student was found
	mu_check(FindStudent(global->StudentList, studentID)->StudentID == studentID); //Check that the student is actually the right one
	mu_check(FindStudent(global->StudentList, badID) == NULL); //Check that bad username not found
	freeMemory(global);
}

MU_TEST(test_FindWatcher_structures)
{
	//Finds wathcer by ID
	int watcherID = 3000; //Good ID - sould provide the right info
	int badID = 9999;//Bad ID - should return NULL
	//Loading file:
	Global* global = InitDataBases();
	mu_check(FindWatcher(global->WatchersList, watcherID) != NULL);//Check that the watcher was found
	mu_check(FindWatcher(global->WatchersList, watcherID)->WatcherID == watcherID); //Check that the watcher is actually the right one
	mu_check(FindWatcher(global->WatchersList, badID) == NULL); //Check that bad username not found
	freeMemory(global);
}

MU_TEST(test_FindAdmin_structures)
{
	//Finds admin by ID
	int adminID = 2000; //Good ID - sould provide the right info
	int badID = 9999;//Bad ID - should return NULL
	//Loading file:
	Global* global = InitDataBases();
	mu_check(FindAdmin(global->AdminsList, adminID) != NULL);//Check that the admin was found
	mu_check(FindAdmin(global->AdminsList, adminID)->AdminID == adminID); //Check that the admin is actually the right one
	mu_check(FindAdmin(global->AdminsList, badID) == NULL); //Check that bad username not found
	freeMemory(global);
}

MU_TEST(test_FindProject_structures)
{
	//Finds project by ID
	int projID = 4001; //Good ID - sould provide the right info
	int badID = 9999;//Bad ID - should return NULL
	//Loading file:
	Global* global = InitDataBases();
	mu_check(FindProject(global->ProjectsList, projID) != NULL);//Check that the proj. was found
	mu_check(FindProject(global->ProjectsList, projID)->ProjectID == projID); //Check that the porj. is actually the right one
	mu_check(FindProject(global->ProjectsList, badID) == NULL); //Check that bad id not found
	freeMemory(global);
}

MU_TEST(test_FindTask_structures)
{
	//Finds task by ID
	int taskID = 6000; //Good ID - sould provide the right info
	int badID = 9999;//Bad ID - should return NULL
	//Loading file:
	Global* global = InitDataBases();
	mu_check(FindTask(global->TaskList, taskID) != NULL);//Check that the task was found
	mu_check(FindTask(global->TaskList, taskID)->TaskID == taskID); //Check that the task is actually the right one
	mu_check(FindTask(global->TaskList, badID) == NULL); //Check that bad id not found
	freeMemory(global);
}

MU_TEST(test_FindQuote_structures)
{
	//Finds quote by ID
	int quoteID = 5020; //Good ID - sould provide the right info
	int badID = 9999;//Bad ID - should return NULL
	//Loading file:
	Global* global = InitDataBases();
	mu_check(FindQuote(global->QuotesList, quoteID) != NULL);//Check that the admin was found
	mu_check(FindQuote(global->QuotesList, quoteID)->QuoteID == quoteID); //Check that the admin is actually the right one
	mu_check(FindQuote(global->QuotesList, badID) == NULL); //Check that bad username not found
	freeMemory(global);
}

/* מה עם סטודנט בלי פרוייקטים ? */
MU_TEST(test_AddStudent)
{
	//Receives a student object and inserts it to the end of the linked list
	//Loading file:
	Global* global = InitDataBases();
	Student * test_student = (Student*)malloc(sizeof(Student));
	test_student->Group = 1;
	test_student->ProjectIDS = NULL;
	test_student->StudentID = 1999;
	strcpy(test_student->StudentActivityLog, "1999_SLog.txt");
	strcpy(test_student->StudentDepartment, "SoftwareEng.");
	strcpy(test_student->StudentEmail, "email@gmail");
	strcpy(test_student->StudentMessages, "1999_SMess.txt");
	strcpy(test_student->StudentName, "hadas");
	test_student->StudentNext = NULL;
	strcpy(test_student->StudentPassword, "AAaa11");
	test_student->StudentProjectsAmount = 0;
	strcpy(test_student->StudentSurename, "hasidim");
	test_student->StudentTasksAmount = 0;
	strcpy(test_student->StudentUsername, "hHasidim");
	test_student->StudentYear = 'a';

	AddStudent(global->StudentList, test_student);
	mu_check(FindStudent(global->StudentList, test_student->StudentID) != NULL); //check if the student is found by ID 
	mu_check(FindStudentByUN(global, test_student->StudentUsername) != NULL); //check if the student is found by UN

	freeMemory(global);
}



MU_TEST(test_AddAdmin)
{
	//Receives an admin object and inserts it to the end of the linked list
	//Loading file:
	Global* global = InitDataBases();
	Admin * test_admin = (Admin*)malloc(sizeof(Admin));
	test_admin->AdminID = 2999;
	strcpy(test_admin->AdminName, "mr.admin");
	strcpy(test_admin->AdminPassword, "BBcc22");
	test_admin->AdminNext = NULL;
	strcpy(test_admin->AdminSurename, "adminovich");
	strcpy(test_admin->AdminUsername, "adminadmin");
	test_admin->Group = 2;

	AddAdmin(global->AdminsList, test_admin);
	mu_check(FindAdmin(global->AdminsList, test_admin->AdminID) != NULL); //check if the admin is found by ID 
	mu_check(FindAdminByUN(global, test_admin->AdminUsername) != NULL); //check is the admin is found by UN

	freeMemory(global);
}

MU_TEST(test_AddWatcher)
{
	//Receives a watcher object and inserts it to the end of the linked list
	//Loading file:
	Global* global = InitDataBases();
	Watcher * test_watch = (Watcher*)malloc(sizeof(Watcher));
	test_watch->Group = 3;
	test_watch->ProjectIDS = NULL;
	strcpy(test_watch->WatcherEmail, "gmail@email");
	test_watch->WatcherID = 3999;
	strcpy(test_watch->WatcherName, "svetlana");
	strcpy(test_watch->WatcherPassword, "CCdd33");
	test_watch->WatcherNext = NULL;
	test_watch->WatcherProjectsAmount = 0;
	test_watch->WatcherReceiveChanges = 0;
	strcpy(test_watch->WatcherSurename, "rusin");
	strcpy(test_watch->WatcherUsername, "svetar");

	AddWatcher(global->WatchersList, test_watch);
	mu_check(FindWatcher(global->WatchersList, test_watch->WatcherID) != NULL); //check if the watcher is found by ID 

	freeMemory(global);
}

MU_TEST(test_AddProject)
{
	//Receives a project object and inserts it to the end of the linked list
	//Loading file:
	Global* global = InitDataBases();
	Project * test_proj = (Project*)malloc(sizeof(Project));
	test_proj->ProgramChanges = 0;
	test_proj->ProjectID = 4999;
	strcpy(test_proj->ProjectActivityLogs, "4999_ProjectActivityLog.txt");
	strcpy(test_proj->ProjectCreatorName, "izzie");
	strcpy(test_proj->ProjectMessages, "4999_PMess.txt");
	strcpy(test_proj->ProjectName, "Mesimaster");
	test_proj->ProjectNext = NULL;
	test_proj->ProjectTasksAmount = 0;
	test_proj->ProjectUsersAmount = 0;
	test_proj->StudentsIDS = NULL;
	test_proj->TasksIDS = NULL;

	AddProject(global->ProjectsList, test_proj);
	mu_check(FindProject(global->ProjectsList, test_proj->ProjectID) != NULL); //check if the project is found by ID 

	freeMemory(global);
}

MU_TEST(test_AddTask)
{
	//Receives a task object and inserts it to the end of the linked list
	//Loading file:
	Global* global = InitDataBases();
	Task * test_task = (Task*)malloc(sizeof(Task));
	strcpy(test_task->TaskCreatorName, "isabelle");
	test_task->TaskID = 5999;
	strcpy(test_task->TaskName, "doSomething");
	test_task->TaskNext = NULL;
	test_task->TaskStatus = NEW;

	AddTask(global->TaskList, test_task);
	mu_check(FindTask(global->TaskList, test_task->TaskID) != NULL); //check if the task is found by ID 

	freeMemory(global);
}

MU_TEST(test_AddQuote)
{
	//Receives a quote object and inserts it to the end of the linked list
	//Loading file:
	Global* global = InitDataBases();
	Quote * test_quote = (Quote*)malloc(sizeof(Quote));
	strcpy(test_quote->Quote, "If not me, Who?");
	strcpy(test_quote->QuoteAuthor, "Anonymous dude");
	test_quote->QuoteID = 6999;

	AddQuote(global->QuotesList, test_quote);
	mu_check(FindQuote(global->QuotesList, test_quote->QuoteID) != NULL); //check if the quote is found by ID 

	freeMemory(global);
}

MU_TEST(test_RemoveProjectFromList)
{
	//Receives a project id and removes it from the linked list
	//Loading file:
	Global* global = InitDataBases();
	Project * emptyList = NULL; //should do nothing but dont crash
	int testID = 4000; //Should delete
	int badId = 9999; //Should do nothing (non existing item) , should not crash

	global->ProjectsList = RemoveProjectFromList(global->ProjectsList, testID);
	mu_check(FindProject(global->ProjectsList, testID) == NULL); //check that realy removed - item is really not in the list
	global->ProjectsList = RemoveProjectFromList(global->ProjectsList, badId); //check deleting non exosting item
	global->ProjectsList = RemoveProjectFromList(emptyList, testID); //check deleting from empty list
	freeMemory(global);
}

MU_TEST(test_RemoveStudentFromList)
{
	//Receives a student id and removes it from the linked list
	//Loading file:
	Global* global = InitDataBases();
	Student * emptyList = NULL;
	int testID = 1001; //Should delete
	int badID = 9999;

	global->StudentList = RemoveStudentFromList(global->StudentList, testID);
	mu_check(FindStudent(global->StudentList, testID) == NULL); //check that realy removed - item is really not in the list
	global->StudentList = RemoveStudentFromList(global->StudentList, badID); //check deleting non exosting item
	global->StudentList = RemoveStudentFromList(emptyList, testID); //check deleting from empty list

	freeMemory(global);
}

MU_TEST(test_RemoveWatcherFromList)
{
	//Receives a watcher id and removes it from the linked list
	//Loading file:
	Global* global = InitDataBases();
	Watcher * emptyList = NULL;
	int badID = 9999;
	int testID = 1001; //Should delete

	global->WatchersList = RemoveWatcherFromList(global->WatchersList, testID);
	mu_check(FindWatcher(global->WatchersList, testID) == NULL); //check that realy removed - item is really not in the list
	global->WatchersList = RemoveWatcherFromList(global->WatchersList, badID); //check deleting from empty list
	global->WatchersList = RemoveWatcherFromList(emptyList, testID); //check deleting from empty list

	freeMemory(global);
}

MU_TEST(test_RemoveAdminFromList)
{
	//Receives a admin id and removes it from the linked list
	//Loading file:
	Global* global = InitDataBases();
	Admin * emptyList = NULL;
	int badID = 9999;
	int testID = 2001; //Should delete

	global->AdminsList = RemoveAdminFromList(global->AdminsList, testID);
	mu_check(FindAdmin(global->AdminsList, testID) == NULL); //check that realy removed - item is really not in the list
	global->AdminsList = RemoveAdminFromList(global->AdminsList, badID);  //check deleting from empty list
	global->AdminsList = RemoveAdminFromList(emptyList, testID);//check deleting from empty list

	freeMemory(global);
}

MU_TEST(test_RemoveQuoteFromList)
{
	//Receives a quote id and removes it from the linked list
	//Loading file:
	Global* global = InitDataBases();
	Quote * emptyList = NULL;
	int badID = 9999;
	int testID = 1; //Should delete

	global->QuotesList = RemoveQuoteFromList(global->QuotesList, testID);
	mu_check(FindQuote(global->QuotesList, testID) == NULL); //check that realy removed - item is really not in the list
	global->QuotesList = RemoveQuoteFromList(global->QuotesList, badID);  //check deleting from empty list
	global->QuotesList = RemoveQuoteFromList(emptyList, testID);//check deleting from empty list

	freeMemory(global);
}

MU_TEST(test_RemoveTaskFromList)
{
	//Receives a task id and removes it from the linked list
	//Loading file:
	Global* global = InitDataBases();
	Task * emptyList = NULL;
	int badID = 9999;
	int testID = 5000; //Should delete

	global->TaskList = RemoveTaskFromList(global->TaskList, testID);
	mu_check(FindTask(global->TaskList, testID) == NULL); //check that realy removed - item is really not in the list
	global->TaskList = RemoveTaskFromList(global->TaskList, badID);//check deleting from empty list
	global->TaskList = RemoveTaskFromList(emptyList, testID);//check deleting from empty list

	freeMemory(global);
}

//int isStudentInProject(Project* project, int studentID);
MU_TEST(test_findTaskInProject)
{
	Global* global = InitDataBases();
	mu_check(findTaskInProject(global, FindProject(global->ProjectsList, 4000), 6001) != NULL); //check that returns smthn
	mu_check(findTaskInProject(global, FindProject(global->ProjectsList, 4000), 6001)->TaskID == 6001); //check that returns the right thing
	mu_check(findTaskInProject(global, FindProject(global->ProjectsList, 4000), 5007) == NULL); // check that returns null if bad id
	freeMemory(global);
}

MU_TEST(test_convertStatusToString)
{
	mu_check(strcmp(convertStatusToString(NEW), "New") == 0);
	mu_check(strcmp(convertStatusToString(APPROVED), "Approved") == 0);
	mu_check(convertStatusToString(10) == NULL);
}

MU_TEST(test_isStudentInProject)
{
	Global* global = InitDataBases();
	mu_check(isStudentInProject(FindProject(global->ProjectsList, 4000), 1001) == 1); //right student and project
	mu_check(isStudentInProject(FindProject(global->ProjectsList, 4001), 9999) == 0); // right project wrong student
	freeMemory(global);
}

MU_TEST_SUITE(Structures_Suite)
{
	MU_RUN_TEST(test_FindStudent_structures);
	MU_RUN_TEST(test_FindWatcher_structures);
	MU_RUN_TEST(test_FindAdmin_structures);
	MU_RUN_TEST(test_FindProject_structures);
	MU_RUN_TEST(test_FindTask_structures);
	MU_RUN_TEST(test_FindQuote_structures);
	MU_RUN_TEST(test_AddStudent);
	MU_RUN_TEST(test_AddAdmin);
	MU_RUN_TEST(test_AddWatcher);
	MU_RUN_TEST(test_AddProject);
	MU_RUN_TEST(test_AddTask);
	MU_RUN_TEST(test_AddQuote);
	MU_RUN_TEST(test_RemoveProjectFromList);
	MU_RUN_TEST(test_findTaskInProject);
	MU_RUN_TEST(test_RemoveStudentFromList);
	MU_RUN_TEST(test_RemoveWatcherFromList);
	MU_RUN_TEST(test_RemoveAdminFromList);
	MU_RUN_TEST(test_RemoveQuoteFromList);
	MU_RUN_TEST(test_RemoveTaskFromList);
	MU_RUN_TEST(test_convertStatusToString);
	MU_RUN_TEST(test_isStudentInProject);
}