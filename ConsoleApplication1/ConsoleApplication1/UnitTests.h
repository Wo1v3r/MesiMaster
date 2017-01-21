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
	mu_check(check->StudentID == 1);
	mu_check(strcmp(check->StudentUsername, "isabeme") == 0);
	mu_check(strcmp(check->StudentPassword, "A1b") == 0);
	mu_check(strcmp(check->StudentName, "izzie") == 0);
	mu_check(strcmp(check->StudentSurename, "me") == 0);
	mu_check(strcmp(check->StudentEmail, "ii@f") == 0);
	mu_check(strcmp(check->StudentDepartment, "Mechanical") == 0);
	mu_check(check->StudentYear == 'b');
	mu_check(strcmp(check->StudentActivityLog, "1002_SLog.txt") == 0);
	mu_check(check->Group == 1);
	mu_check(check->StudentProjectsAmount == 0);
	mu_check(check->StudentTasksAmount == 0);
	mu_check(strcmp(check->StudentMessages, "1002_SMess.txt") == 0);
	freeStudents(check);
}

MU_TEST(test_init_projects){
	Project *check = initProjects();
	mu_check(check->ProjectID == 6);
	mu_check(strcmp(check->ProjectName, "projectest") == 0);
	mu_check(strcmp(check->ProjectCreatorName, "me") == 0);
	mu_check(strcmp(check->ProjectActivityLogs, "none") == 0);
	mu_check(check->ProjectUsersAmount == 2);
	mu_check(check->StudentsIDS[0] == 3);
	mu_check(check->StudentsIDS[1] == 4);
	mu_check(check->ProjectTasksAmount == 1);
	mu_check(check->TasksIDS[0] == 1);
	mu_check(strcmp(check->ProjectMessages, "6_Pmsg.txt") == 0);
	freeProjects(check);
}

MU_TEST(test_init_watchers){
	Watcher *check = initWatchers();
	mu_check(check->WatcherID == 2001);
	mu_check(strcmp(check->WatcherUsername, "watcher") == 0);
	mu_check(strcmp(check->WatcherPassword, "jipwa#$%sfjip") == 0);
	mu_check(strcmp(check->WatcherName, "DUDU") == 0);
	mu_check(strcmp(check->WatcherSurename, "BEN-HATUL") == 0);
	mu_check(strcmp(check->WatcherEmail, "DUDU@gmail.com") == 0);
	mu_check(check->Group == 3);
	mu_check(check->WatcherReceiveChanges == 0);
	mu_check(check->WatcherProjectsAmount == 1);
	mu_check(check->ProjectIDS[0] == 6);
	freeWatchers(check);
}

MU_TEST(test_init_admins){
	Admin *check = initAdmins();
	mu_check(check->AdminID == 1001);
	mu_check(strcmp(check->AdminUsername, "Dubi") == 0);
	mu_check(strcmp(check->AdminPassword, "purr") == 0);
	mu_check(strcmp(check->AdminName, "Kuki") == 0);
	mu_check(strcmp(check->AdminSurename, "Leon") == 0);
	mu_check(check->Group == 2);
	freeAdmins(check);
}

MU_TEST(test_init_tasks){
	Task *check = initTasks();
	mu_check(check->TaskID == 1);
	mu_check(strcmp(check->TaskName, "Check") == 0);
	mu_check(check->TaskStatus == 1);
	mu_check(strcmp(check->TaskCreatorName, "ME") == 0);
	freeTasks(check);
}

MU_TEST(test_init_quotes){
	Quote *check = initQuotes();
	mu_check(check->QuoteID == 1);
	mu_check(strcmp(check->Quote, "master check quote") == 0);
	mu_check(strcmp(check->QuoteAuthor, "me") == 0);
	freeQuotes(check);
}

MU_TEST(test_init_global){
	Global *check = initGlobal();
	mu_check(check->StudentRunID == 4);
	mu_check(check->AdminRunID == 1003);
	mu_check(check->WatcherRunID == 2003);
	mu_check(check->ProjectRunID == 4000);
	mu_check(check->QuoteRunID == 5000);
	mu_check(check->TaskRunID == 6000);
	mu_check(strcmp(check->GlobalMessages, "globalMsg.txt") == 0);
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
	MU_REPORT_SUITE();
}


//Utilities Suite Tests

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
	char* watcherUN = "liranr"; //Good username - sould provide the right info
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


//Utilities suite

MU_TEST_SUITE(Utilities){
	MU_RUN_TEST(test_find_accessgroup);
	MU_RUN_TEST(test_FindAdminByUN);
	MU_RUN_TEST(test_FindWatcherByUN);
	MU_RUN_TEST(test_FindStudentByUN);

	MU_REPORT_SUITE();
}


//Login suite tests:

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
	char* studentUN = "alex";
	char* watcherUN = "watcher";
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

	MU_REPORT_SUITE();
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
	int id = 1;
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
	id = 3002;//Watcher
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
	AddNewQuote(global);
	mu_check(FindQuote(global->QuotesList, (global->QuoteRunID) - 1) != NULL);
	mu_assert(global->QuoteRunID - current_runID == 1, "Suppose to be 1!(1 new quote added)");
	freeMemory(global);
}

MU_TEST_SUITE(Admin_Suite){
	MU_RUN_TEST(test_delete_user);
	MU_RUN_TEST(test_delete_quote);
	MU_RUN_TEST(test_promote_user);
	MU_RUN_TEST(test_add_new_quote);
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


}
MU_TEST_SUITE(Project_Suite){

	MU_RUN_TEST(test_create_project);
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
	int watcherID = 3002; //Good ID - sould provide the right info
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
	int adminID = 2001; //Good ID - sould provide the right info
	int badID = 9999;//Bad ID - should return NULL
	//Loading file:
	Global* global = InitDataBases();
	mu_check(FindAdmin(global->AdminsList, adminID) != NULL);//Check that the admin was found
	mu_check(FindAdmin(global->AdminsList, adminID)->AdminID == adminID); //Check that the admin is actually the right one
	mu_check(FindAdmin(global->AdminsList, badID) == NULL); //Check that bad username not found
	freeMemory(global);
}

/*
Project *FindProject(Project* head, int ProjectID);
Task *FindTask(Task* head, int TaskID);
Quote *FindQuote(Quote* head, int QuoteID);
*/

MU_TEST(test_FindProject_structures)
{
	//Finds admin by ID
	int adminID = 2001; //Good ID - sould provide the right info
	int badID = 9999;//Bad ID - should return NULL
	//Loading file:
	Global* global = InitDataBases();
	mu_check(FindAdmin(global->AdminsList, adminID) != NULL);//Check that the admin was found
	mu_check(FindAdmin(global->AdminsList, adminID)->AdminID == adminID); //Check that the admin is actually the right one
	mu_check(FindAdmin(global->AdminsList, badID) == NULL); //Check that bad username not found
	freeMemory(global);
}

MU_TEST(test_FindTask_structures)
{
	//Finds admin by ID
	int adminID = 2001; //Good ID - sould provide the right info
	int badID = 9999;//Bad ID - should return NULL
	//Loading file:
	Global* global = InitDataBases();
	mu_check(FindAdmin(global->AdminsList, adminID) != NULL);//Check that the admin was found
	mu_check(FindAdmin(global->AdminsList, adminID)->AdminID == adminID); //Check that the admin is actually the right one
	mu_check(FindAdmin(global->AdminsList, badID) == NULL); //Check that bad username not found
	freeMemory(global);
}

MU_TEST(test_FindQuote_structures)
{
	//Finds admin by ID
	int adminID = 2001; //Good ID - sould provide the right info
	int badID = 9999;//Bad ID - should return NULL
	//Loading file:
	Global* global = InitDataBases();
	mu_check(FindAdmin(global->AdminsList, adminID) != NULL);//Check that the admin was found
	mu_check(FindAdmin(global->AdminsList, adminID)->AdminID == adminID); //Check that the admin is actually the right one
	mu_check(FindAdmin(global->AdminsList, badID) == NULL); //Check that bad username not found
	freeMemory(global);
}


MU_TEST_SUITE(Structures_Suite)
{
	MU_RUN_TEST(test_FindStudent_structures);
	MU_RUN_TEST(test_FindWatcher_structures);
	MU_RUN_TEST(test_FindAdmin_structures);

	MU_REPORT_SUITE();
}