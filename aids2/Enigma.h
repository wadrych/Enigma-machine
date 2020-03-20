#pragma once
#include "ElectroMechanicalElement.h"
#include "Rotor.h"
#include "Reflector.h"

class Enigma {
public:
	Enigma(int amountOfParts);
	~Enigma();
	void AddRotor(RotorDTO* rotor);
	void AddReflector(ReflectorDTO* reflector);
	int EncodeLetter(int letter);
	
private:
	ElectroMechanicalElement** parts;
	Rotor** rotors;
	int amountOfParts;
	int indexOfLastAddedRotor;

	void setRotators();
	int runLetterThroughParts(int letter);
	bool changeRotor(int rotorIndex, bool shouldTurn, int amountOfRotors);

};

