#include "TaskManager.h"

TaskManager::TaskManager(RotorService* rotorService, ReflectorService* reflectorService) : rotorService(rotorService), reflectorService(reflectorService) {	
}

TaskManager::~TaskManager() {
}

void TaskManager::PerformTask() {
	int reflectorAmount = 1;
	int amountOfRotors;
	int amountOfParts;
	int letter;
	
	scanf_s("%i", &amountOfRotors);
	amountOfParts = amountOfRotors + reflectorAmount;

	Enigma enigma(amountOfParts);

	SetRotors(&enigma, amountOfRotors);
	SetReflector(&enigma);

	scanf_s("%i", &letter);
	
	while(letter != 0) {
		EncodeLetter(&enigma, &letter);
	}

	printf_s("\n");
}

void TaskManager::SetRotors(Enigma* enigma, int amountOfRotors) {
	for (int i = 0; i < amountOfRotors; i++) {
		int rotorIndex = 0;
		int rotorPosition = 0;
		scanf_s("%i", &rotorIndex);
		scanf_s("%i", &rotorPosition);

		RotorDTO* rotor = rotorService->GetRotor(rotorIndex);
		rotor->initialTurn = rotorPosition;
		enigma->AddRotor(rotor);
	}
}

void TaskManager::SetReflector(Enigma* enigma) {
	int reflectorIndex;
	
	scanf_s("%i", &reflectorIndex);
	ReflectorDTO* reflector = reflectorService->GetReflector(reflectorIndex);
	enigma->AddReflector(reflector);
}

void TaskManager::EncodeLetter(Enigma* enigma, int* letter) {
	const int encodedLetter = enigma->EncodeLetter(*letter);
	printf_s("%i ", encodedLetter);
	scanf_s("%i", letter);
}

