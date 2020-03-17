#include "Enigma.h"

Enigma::Enigma(int amountOfParts) : amountOfParts(amountOfParts)
{
	indexOfLastAddedRotor = 0;
	parts = new ElectroMechanicalElement * [amountOfParts];
	rotors = new Rotor * [amountOfParts - 1];
}

Enigma::~Enigma()
{
	delete[] parts;
	delete[] rotors;
}

void Enigma::AddRotor(Rotor* rotor)
{
	Rotor* newRotor = rotor->Clone();
	parts[indexOfLastAddedRotor] = newRotor;
	rotors[indexOfLastAddedRotor] = newRotor;
	indexOfLastAddedRotor++;

}

void Enigma::AddReflector(Reflector* reflector)
{
	Reflector* newReflector = reflector->Clone();
	parts[amountOfParts-1] = newReflector;
}

int Enigma::EncodeLetter(int letter)
{
	setRotators();
	return runLetterThroughParts(letter-1);
}

void Enigma::setRotators()
{
	rotors[0]->Turn();

	if(rotors[0]->IsLocked()) {
		rotors[1]->Turn();
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
