#include "RotorService.h"
#include <csignal>

RotorService::RotorService(int alphabetSize) : alphabetSize(alphabetSize) {
	rotorsArray = nullptr;
	length = 0;
}

RotorService::~RotorService() {
	for(int i=0; i<length; i++) {
		delete[] rotorsArray[i]->signalOutlet;
		rotorsArray[i]->signalOutlet = nullptr;
		delete[] rotorsArray[i]->turnoverPositions;
		rotorsArray[i]->turnoverPositions = nullptr;
		delete rotorsArray[i];
		rotorsArray[i] = nullptr;
	}
	delete[] rotorsArray;
	rotorsArray = nullptr;
}

void RotorService::Create() {
	scanf_s("%i", &length);

	rotorsArray = new RotorDTO* [length];

	for (int i = 0; i < length; i++) {
		rotorsArray[i] = createRotor();
	}
}

RotorDTO* RotorService::GetRotor(int index) {
	return rotorsArray[index];
}

RotorDTO* RotorService::createRotor() {
	RotorDTO* newRotor = new RotorDTO();
	newRotor->length = alphabetSize;

	Circuit* signalOutlet = new Circuit[newRotor->length];
	readCircuits(newRotor, signalOutlet);
	newRotor->signalOutlet = signalOutlet;

	scanf_s("%i", &newRotor->amountOfTurnoverPositions);
	int* turnoverPositions = new int[newRotor->amountOfTurnoverPositions];
	readTurnovers(newRotor, turnoverPositions);
	newRotor->turnoverPositions = turnoverPositions;
	newRotor->initialTurn = 0;
	
	return newRotor;
}

void RotorService::readCircuits(RotorDTO* newRotor, Circuit* signalOutlet) {
	for (int i = 0; i < newRotor->length; i++) {
		int permutation;
		scanf_s("%i", &permutation);
		signalOutlet[i].permutation = permutation;
		signalOutlet[i].letter = i;
	}
}

void RotorService::readTurnovers(RotorDTO* newRotor, int* turnoverPositions) {
	for (int i = 0; i < newRotor->amountOfTurnoverPositions; i++) {
		int turnover;
		scanf_s("%i", &turnover);
		turnoverPositions[i] = turnover;
	}
}
