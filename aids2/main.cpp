
#define _CRT_SECURE_NO_WARNINGS
#include "Enigma.h"
#include "RotorService.h"
#include "ReflectorService.h"

#include <iostream>
#include "TaskManager.h"

int main ()
{
	int alphabetSize = 0;
	int amountOfTasks = 0;

	scanf("%i", &alphabetSize);
	
	RotorService rotorService(alphabetSize);
	ReflectorService reflectorService(alphabetSize);

	rotorService.Create();
	reflectorService.Create();
	
	TaskManager taskManager(&rotorService, &reflectorService);
	
	scanf("%i", &amountOfTasks);

	for(int i=0; i<amountOfTasks; i++) {
		taskManager.PerformTask();
	}

	return 0;
}
