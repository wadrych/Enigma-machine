#include "RotorService.h"
#include <csignal>

RotorService::RotorService(int alphabetSize) : alphabetSize(alphabetSize) {
	rotorsArray = nullptr;
	length = 0;
}

RotorService::~RotorService()
{
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

void RotorService::Create()
{
	scanf_s("%i", &length);

	rotorsArray = new RotorDTO* [length];

	for (int i = 0; i < length; i++) {
		rotorsArray[i] = GetInputFromUser();
	}
}

RotorDTO* RotorService::GetRotor(int index)
{
	return rotorsArray[index];
}

RotorDTO* RotorService::GetInputFromUser()
{
	RotorDTO* newRotor = new RotorDTO();

	newRotor->length = alphabetSize;

	Circuit* signalOutlet = new Circuit[newRotor->length];

	for (int i=0; i<newRotor->length; i++) {
		int permutation;
		scanf_s("%i", &permutation);
		signalOutlet[i].permutation = permutation;
		signalOutlet[i].letter = i;
	}

	newRotor->signalOutlet = signalOutlet;

	scanf_s("%i", &newRotor->amountOfTurnoverPositions);

	int* turnoverPositions = new int[newRotor->amountOfTurnoverPositions];
	
	for(int i=0; i<newRotor->amountOfTurnoverPositions; i++) {
		int turnover;
		scanf_s("%i", &turnover);
		turnoverPositions[i] = turnover;
	}

	newRotor->turnoverPositions = turnoverPositions;
	newRotor->initialTurn = 0;
	
	return newRotor;
}
