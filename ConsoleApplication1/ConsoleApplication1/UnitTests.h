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

//Utilities suite

MU_TEST_SUITE(Utilities){
	MU_RUN_TEST(test_find_accessgroup);

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

MU_TEST_SUITE(Login_Suite){
	MU_RUN_TEST(test_check_password);

	MU_REPORT_SUITE();
}