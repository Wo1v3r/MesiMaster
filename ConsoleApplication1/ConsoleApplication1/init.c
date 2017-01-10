#define _CRT_SECURE_NO_WARNINGS_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"

Student* initStudents(){
	Student* head = NULL, *newStud;
	FILE * read = fopen("students.txt", "r");
	if (read == NULL){
		printf("Error opening the students file.\n");
		return NULL;
	}
	else{
		int num = 0;
		while (!feof(read)){
			if (num == 0){
				newStud = (Student*)(malloc(sizeof(Student)));
				head = newStud;
			}
			else{
				newStud = newStud->StudentNext;
				newStud = (Student*)(malloc(sizeof(Student)));
			}
			fscanf(read, "%d", &newStud->StudentID);
			fscanf(read, "%s", &newStud->StudentUsername);
			fscanf(read, "%s", &newStud->StudentPassword);
			fscanf(read, "%s", &newStud->StudentName);
			fscanf(read, "%s", &newStud->StudentSurename);
			fscanf(read, "%s", &newStud->StudentEmail);
			fscanf(read, "%s", &newStud->StudentDepartment);
			fscanf(read, "%c", &newStud->StudentYear);
			fscanf(read, "%s", &newStud->StudentActivityLog);
			fscanf(read, "%d", &newStud->Group);
			fscanf(read, "%d", &newStud->StudentProjectsAmount);
			int i;
			for (i = 0; i < newStud->StudentProjectsAmount; i++){

			}
			fscanf(read, "%d", &newStud->StudentTasksAmount);
			fscanf(read, "%s", &newStud->StudentMessages);
			num++;
		}
		newStud->StudentNext = NULL;
	}
	fclose(read);
	return head;
}

Project* initProjects(Student* studhead, Task* taskhead){
	Project* head = NULL, *newProj;
	FILE * read = fopen("projects.txt", "r");
	if (read == NULL){
		printf("Error opening the projects file.\n");
		return NULL;
	}
	else{
		int num = 0;
		while (!feof(read)){
			if (num == 0){
				newProj = (Project*)(malloc(sizeof(Project)));
				head = newProj;
			}
			else{
				newProj = newProj->ProjectNext;
				newProj = (Project*)(malloc(sizeof(Project)));
			}
			fscanf(read, "%d", &newProj->ProjectID);
			fscanf(read, "%s", &newProj->ProjectName);
			fscanf(read, "%s", &newProj->ProjectCreatorName);
			fscanf(read, "%s", &newProj->ProjectActivityLogs);
			fscanf(read, "%d", &newProj->ProjectUsersAmount);
			int i;
			for (i = 0; i < newProj->ProjectUsersAmount; i++){
				
			}
			fscanf(read, "%d", &newProj->ProjectTasksAmount);
			for (i = 0; i < newProj->ProjectUsersAmount; i++){

			}
			fscanf(read, "%s", &newProj->ProjectMessages);
			num++;
		}
		newProj->ProjectNext = NULL;
	}
	fclose(read);
	return head;
}

Admin* initAdmins(){
	Admin* head = NULL, *newAdmin;
	FILE * read = fopen("admins.txt", "r");
	if (read == NULL){
		printf("Error opening the admins file.\n");
		return NULL;
	}
	else{
		int num = 0;
		while (!feof(read)){
			if (num == 0){
				newAdmin = (Admin*)(malloc(sizeof(Admin)));
				head = newAdmin;
			}
			else{
				newAdmin = newAdmin->AdminNext;
				newAdmin = (Admin*)(malloc(sizeof(Admin)));
			}
			fscanf(read, "%d", &newAdmin->AdminID);
			fscanf(read, "%s", &newAdmin->AdminUsername);
			fscanf(read, "%s", &newAdmin->AdminPassword);
			fscanf(read, "%s", &newAdmin->AdminName);
			fscanf(read, "%s", &newAdmin->AdminSurename);
			fscanf(read, "%d", &newAdmin->Group);
			num++;
		}
		newAdmin->AdminNext = NULL;
	}
	fclose(read);
	return head;
}

Task* initTasks(){
	Task* head = NULL, *newTask;
	FILE * read = fopen("tasks.txt", "r");
	if (read == NULL){
		printf("Error opening the tasks file.\n");
		return NULL;
	}
	else{
		int num = 0;
		while (!feof(read)){
			if (num == 0){
				newTask = (Task*)(malloc(sizeof(Task)));
				head = newTask;
			}
			else{
				newTask = newTask->TaskNext;
				newTask = (Task*)(malloc(sizeof(Task)));
			}
			fscanf(read, "%d", &newTask->TaskID);
			fscanf(read, "%s", &newTask->TaskName);
			fscanf(read, "%d", &newTask->);
			fscanf(read, "%s", &newTask->TaskCreatorName);
			num++;
		}
		newTask->TaskNext = NULL;
	}
	fclose(read);
	return head;
}

Quote* initQuotes(){
	Quote* head = NULL, *newQuote;
	FILE * read = fopen("quotes.txt", "r");
	if (read == NULL){
		printf("Error opening the quotes file.\n");
		return NULL;
	}
	else{
		int num = 0;
		while (!feof(read)){
			if (num == 0){
				newQuote = (Quote*)(malloc(sizeof(Quote)));
				head = newQuote;
			}
			else{
				newQuote = newQuote->QuoteNext;
				newQuote = (Quote*)(malloc(sizeof(Quote)));
			}
			fscanf(read, "%d", &newQuote->QuoteID);
			fscanf(read, "%s", &newQuote->Quote);
			fscanf(read, "%d", &newQuote->QuoteAuthor);
			num++;
		}
		newQuote->QuoteNext = NULL;
	}
	fclose(read);
	return head;
}