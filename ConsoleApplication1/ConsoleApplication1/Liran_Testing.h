//#include "MinUnit.h"
//#include "Register.h"
//
///*
//FOR RUNNING THE TESTS COPY THEM BEFORE THE MAIN FUNCTION.
//ADD include for minunit.h
//#include "MinUnit.h"
//in the main function add
//MU_RUN_SUITE(InitTest);
//
//These tests are built on the given txt files. any change will need to be change in accordance with them!!!
//if you wish to run the programm as usual comment this whole file.
//*/
//
//MU_TEST(test_init_student){
//	Student *check = initStudents();
//	mu_check(check->StudentID == 1);
//	mu_check(strcmp(check->StudentUsername, "isabeme") == 0);
//	mu_check(strcmp(check->StudentPassword, "A1b") == 0);
//	mu_check(strcmp(check->StudentName, "izzie") == 0);
//	mu_check(strcmp(check->StudentSurename, "me") == 0);
//	mu_check(strcmp(check->StudentEmail, "ii@f") == 0);
//	mu_check(strcmp(check->StudentDepartment, "Mechanical") == 0);
//	mu_check(check->StudentYear == 'b');
//	mu_check(strcmp(check->StudentActivityLog, "1002_SLog.txt") == 0);
//	mu_check(check->Group == 1);
//	mu_check(check->StudentProjectsAmount == 0);
//	mu_check(check->StudentTasksAmount == 0);
//	mu_check(strcmp(check->StudentMessages, "1002_SMess.txt") == 0);
//	freeStudents(check);
//}
//
//MU_TEST(test_init_projects){
//	Project *check = initProjects();
//	mu_check(check->ProjectID == 6);
//	mu_check(strcmp(check->ProjectName, "projectest") == 0);
//	mu_check(strcmp(check->ProjectCreatorName, "me") == 0);
//	mu_check(strcmp(check->ProjectActivityLogs, "none") == 0);
//	mu_check(check->ProjectUsersAmount == 2);
//	mu_check(check->StudentsIDS[0] == 3);
//	mu_check(check->StudentsIDS[1] == 4);
//	mu_check(check->ProjectTasksAmount == 1);
//	mu_check(check->TasksIDS[0] == 1);
//	mu_check(strcmp(check->ProjectMessages, "6_Pmsg.txt") == 0);
//	freeProjects(check);
//}
//
//MU_TEST(test_init_watchers){
//	Watcher *check = initWatchers();
//	mu_check(check->WatcherID == 2001);
//	mu_check(strcmp(check->WatcherUsername, "watcher") == 0);
//	mu_check(strcmp(check->WatcherPassword, "jipwa#$%sfjip") == 0);
//	mu_check(strcmp(check->WatcherName, "DUDU") == 0);
//	mu_check(strcmp(check->WatcherSurename, "BEN-HATUL") == 0);
//	mu_check(strcmp(check->WatcherEmail, "DUDU@gmail.com") == 0);
//	mu_check(check->Group == 3);
//	mu_check(check->WatcherReceiveChanges == 0);
//	mu_check(check->WatcherProjectsAmount == 1);
//	mu_check(check->ProjectIDS[0] == 6);
//	freeWatchers(check);
//}
//
//MU_TEST(test_init_admins){
//	Admin *check = initAdmins();
//	mu_check(check->AdminID == 1001);
//	mu_check(strcmp(check->AdminUsername, "Dubi") == 0);
//	mu_check(strcmp(check->AdminPassword, "purr") == 0);
//	mu_check(strcmp(check->AdminName, "Kuki") == 0);
//	mu_check(strcmp(check->AdminSurename, "Leon") == 0);
//	mu_check(check->Group == 2);
//	freeAdmins(check);
//}
//
//MU_TEST(test_init_tasks){
//	Task *check = initTasks();
//	mu_check(check->TaskID == 1);
//	mu_check(strcmp(check->TaskName, "Check") == 0);
//	mu_check(check->TaskStatus == 1);
//	mu_check(strcmp(check->TaskCreatorName, "ME") == 0);
//	freeTasks(check);
//}
//
//MU_TEST(test_init_quotes){
//	Quote *check = initQuotes();
//	mu_check(check->QuoteID == 1);
//	mu_check(strcmp(check->Quote, "master check quote") == 0);
//	mu_check(strcmp(check->QuoteAuthor, "me") == 0);
//	freeQuotes(check);
//}
//
//MU_TEST(test_init_global){
//	Global *check = initGlobal();
//	mu_check(check->StudentRunID == 4);
//	mu_check(check->AdminRunID == 1003);
//	mu_check(check->WatcherRunID == 2003);
//	mu_check(check->ProjectRunID == 4000);
//	mu_check(check->QuoteRunID == 5000);
//	mu_check(check->TaskRunID == 6000);
//	mu_check(strcmp(check->GlobalMessages, "globalMsg.txt") == 0);
//	free(check);
//}
//
//MU_TEST_SUITE(InitTest){
//	MU_RUN_TEST(test_init_student);
//	MU_RUN_TEST(test_init_projects);
//	MU_RUN_TEST(test_init_watchers);
//	MU_RUN_TEST(test_init_admins);
//	MU_RUN_TEST(test_init_tasks);
//	MU_RUN_TEST(test_init_quotes);
//	MU_RUN_TEST(test_init_global);
//	MU_REPORT_SUITE();
//}