#include "Rotor.h"
#include <iostream>

Rotor::Rotor(RotorDTO* rotor) : rotorPattern(rotor) {
	length = rotorPattern->length;
	signalOutlet = new Circuit[length];
	turnoverPositions = new bool[length];
	currentPosition = 0;
	notchSet = false;
	amountOfTurnoverPositions = 0;
	rotated = false;

	populateWithPermutations();
	populateWithTurnovers();
	setInitialPosition();
}

void Rotor::populateWithPermutations() {	
	for (int i = 0; i < length; i++) {
		const int offset = 1;
		const int indexOfPermutation = getIndex(i);
		const int delta = rotorPattern->signalOutlet[indexOfPermutation].permutation - offset - i;
		const int indexOfAlphabet = getIndex(delta + i);

		signalOutlet[indexOfPermutation].permutation = delta;
		signalOutlet[indexOfAlphabet].letter = -delta;
	}
}

void Rotor::populateWithTurnovers() {
	const int offset = 1;
	
	amountOfTurnoverPositions = rotorPattern->amountOfTurnoverPositions;
	for(int i=0; i<length; i++) {
		turnoverPositions[i] = false;
	}

	for(int i=0; i<amountOfTurnoverPositions; i++) {
		const int indexOfTurnover = rotorPattern->turnoverPositions[i] - offset;
		turnoverPositions[indexOfTurnover] = true;
	}
}

Rotor::~Rotor() {
	delete[] turnoverPositions;
}

bool Rotor::IsLocked() {
	const int indexOfNextElement = mathematicalRemainder(currentPosition + 1);

	if (notchSet) {
		notchSet = false;
		return true;
	}
	else {
		return false;
	}
}
/*
bool Rotor::TryTurn(int rotorIndex, bool shouldTurn, int amountOfRotors) {
	if(rotorIndex<amountOfRotors-1 && rotorIndex<2 && rotated) {
		if(isLocked()) {
			turn();
			return true;
		}
	}

	if(shouldTurn) {
		turn();
	}

	return false;
}
*/
void Rotor::Turn() {
	rotated = true;
	const int indexOfNextElement = mathematicalRemainder(currentPosition + 2);
	notchSet = turnoverPositions[indexOfNextElement];
	
	currentPosition++;
	currentPosition = currentPosition % length;
}

void Rotor::setInitialPosition() {
	const int offset = 1;
	currentPosition = rotorPattern->initialTurn - offset;
}

int Rotor::GetLetterByPermutation(int input) {
	const int delta = signalOutlet[getIndex(input)].permutation;
	const int result = mathematicalRemainder(input + delta);

	return result;
}

int Rotor::GetPermutationByLetter(int input) {
	const int delta = signalOutlet[getIndex(input)].letter;
	const int result = mathematicalRemainder(input + delta);

	return result;
}

int Rotor::getIndex(int index) const {
	const int currentIndex = mathematicalRemainder(index + currentPosition);
	
	return currentIndex;
}

int Rotor::mathematicalRemainder(int value) const {
	const int result = value % length;

	if (result >= 0)
		return result;
	else
		return result + length;
}

bool Rotor::IsRotated() {
	return rotated;
}
