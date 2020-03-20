#include "Enigma.h"

Enigma::Enigma(int amountOfParts) : amountOfParts(amountOfParts) {
	indexOfLastAddedRotor = 0;
	parts = new ElectroMechanicalElement * [amountOfParts];
	rotors = new Rotor * [amountOfParts - 1];
}

Enigma::~Enigma() {
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

void Enigma::AddRotor(RotorDTO* rotor) {
	Rotor* newRotor = new Rotor(rotor);
	parts[indexOfLastAddedRotor] = newRotor;
	rotors[indexOfLastAddedRotor] = newRotor;
	indexOfLastAddedRotor++;
}

void Enigma::AddReflector(ReflectorDTO* reflector) {
	const int lastIndex = amountOfParts - 1;
	Reflector* newReflector = new Reflector(reflector);
	parts[lastIndex] = newReflector;
}

int Enigma::EncodeLetter(int letter) {
	setRotators();
	return runLetterThroughParts(letter-1);
}

void Enigma::setRotators() {
	bool shouldNextRotate = changeRotor(0, true, amountOfParts);

	for(int i=1; i<amountOfParts-2; i++) {
		
		shouldNextRotate = changeRotor(i, shouldNextRotate, amountOfParts);
	}

	if (shouldNextRotate && amountOfParts-2 != 0) {
		rotors[amountOfParts - 2]->Turn();
	}
	
	/*rotors[0]->Turn();

	if(amountOfParts == 3) {
		if (rotors[0]->IsLocked()) {
			rotors[1]->Turn();
		}
	}

	if(amountOfParts >= 4) {
		if (rotors[1]->IsLockedBefore()) {
			//rotors[0]->CleanNotch();
			rotors[0]->IsLocked();
			rotors[1]->Turn();
			rotors[2]->Turn();
		}
		else if(rotors[0]->IsLocked()) {
			rotors[1]->Turn();
		}
	}*/
}

bool Enigma::changeRotor(int rotorIndex, bool shouldTurn, int amountOfRotors) {
	if (rotorIndex < 2 && rotors[rotorIndex]->IsRotated() && rotors[rotorIndex]->IsLocked()) {
		rotors[rotorIndex]->Turn();
		return true;
	}

	if (amountOfRotors-1 == rotorIndex - 2) return true;
	
	if (shouldTurn ) {
		rotors[rotorIndex]->Turn();
	}
	return false;
}

int Enigma::runLetterThroughParts(int letter) {
	int output = letter;
	
	for (int k = 0; k < amountOfParts; k++) {
		output = parts[k]->GetLetterByPermutation(output);
	}
	for(int k=amountOfParts-2; k>=0; k--) {
		output = parts[k]->GetPermutationByLetter(output);
	}
	
	return output + 1;
}
