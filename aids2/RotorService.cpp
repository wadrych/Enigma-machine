#include "RotorService.h"

RotorService::RotorService(int length) : length(length)
{
}

RotorService::~RotorService()
{
	for(int i=0; i<length; i++) {
		delete rotorsArray[i];
	}
	delete[] rotorsArray;
}

void RotorService::Create()
{
	int amountOfRotors;
	scanf_s("%i", &amountOfRotors);

	rotorsArray = new Rotor * [amountOfRotors];

	for (int i = 0; i < amountOfRotors; i++) {
		Rotor* newRotor= new Rotor(length);
		rotorsArray[i] = newRotor;
	}
}

Rotor* RotorService::GetRotor(int index)
{
	return new Rotor(*(rotorsArray[index]));
}
