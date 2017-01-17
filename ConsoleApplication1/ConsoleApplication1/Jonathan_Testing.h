#include "MinUnit.h"
#include "Register.h"

/*
FOR RUNNING THE TESTS COPY THEM BEFORE THE MAIN FUNCTION.
ADD include for minunit.h
#include "MinUnit.h"
in the main function add
MU_RUN_SUITE(InitTest);

These tests are built on the given txt files. any change will need to be change in accordance with them!!!
if you wish to run the programm as usual comment this whole file.
*/

MU_TEST(test_init_student){
	Student *check = initStudents();
	mu_check(check->StudentID == 1);
}

//
//MU_TEST_SUITE(InitTest){
//	MU_RUN_TEST(test_init_student);
//
//	MU_REPORT_SUITE();
//}