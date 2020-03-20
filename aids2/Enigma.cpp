#include "Enigma.h"

Enigma::Enigma(int amountOfParts) : amountOfParts(amountOfParts)
{
	indexOfLastAddedRotor = 0;
	parts = new ElectroMechanicalElement * [amountOfParts];
	rotors = new Rotor * [amountOfParts - 1];
}

Enigma::~Enigma()
{
	for(int i=0;i<amountOfParts-1;i++) {
		delete rotors[i];
		rotors[i] = nullptr;
	}
	for (int i=0; i<amountOfParts-1; i++) {
		parts[i] = nullptr;
	}
	delete parts[amountOfParts - 1];
	parts[amountOfParts-1] = nullptr;
	
	delete[] parts;
	parts = nullptr;
	delete[] rotors;
	rotors = nullptr;
}

void Enigma::AddRotor(RotorDTO* rotor)
{
	Rotor* newRotor = new Rotor(rotor);
	parts[indexOfLastAddedRotor] = newRotor;
	rotors[indexOfLastAddedRotor] = newRotor;
	indexOfLastAddedRotor++;
}

void Enigma::AddReflector(ReflectorDTO* reflector)
{
	Reflector* newReflector = new Reflector(reflector);
	parts[amountOfParts-1] = newReflector;
}

int Enigma::EncodeLetter(int letter)
{
	setRotators();
	return RunLetterThroughParts(letter-1);
}

void Enigma::setRotators()
{
	rotors[0]->Turn();

	if(amountOfParts == 3) {
		if (rotors[0]->IsLocked()) {
			rotors[1]->Turn();
		}
	}

	if(amountOfParts >= 4) {
		if (rotors[1]->IsLockedBefore()) {
			rotors[1]->Turn();
			rotors[2]->Turn();
		}
		else if(rotors[0]->IsLocked()) {
			rotors[1]->Turn();
		}
	}
}

int Enigma::runLetterThroughParts(int letter)
{
	int output = letter;
	
	for (int k = 0; k < amountOfParts; k++) {
		output = parts[k]->GetLetterByPermutation(output);
	}
	for(int k=amountOfParts-2; k>=0; k--) {
		output = parts[k]->GetPermutationByLetter(output);
	}
	
	return output + 1;
}
