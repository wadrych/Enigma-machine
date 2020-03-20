#include "Rotor.h"
#include <iostream>

Rotor::Rotor(RotorDTO* rotor) : rotorPattern(rotor) {
	length = rotorPattern->length;
	signalOutlet = new Circuit[length];
	currentPosition = 0;
	notchSet = false;
	turnoverPositions = nullptr;
	amountOfTurnoverPositions = 0;

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
	turnoverPositions = new int[amountOfTurnoverPositions];

	for(int i=0; i<amountOfTurnoverPositions; i++) {
		turnoverPositions[i] = rotorPattern->turnoverPositions[i]-offset;
	}
}

Rotor::~Rotor() {
	delete[] turnoverPositions;
}

bool Rotor::IsLocked() {
	for(int i=0; i<amountOfTurnoverPositions; i++) {
		if(turnoverPositions[i] == currentPosition && notchSet) {
			notchSet = false;
			return true;
		}
	}
	return false;
}

bool Rotor::IsLockedBefore() {
	for (int i=0; i<amountOfTurnoverPositions; i++) {
		const int realTurnoverPos = mathematicalRemainder(turnoverPositions[i] - 1);

		if (realTurnoverPos == currentPosition && notchSet) {
			notchSet = false;
			return true;
		}
	}
	return false;
}

void Rotor::Turn() {
	currentPosition++;
	currentPosition = currentPosition % length;

	for (int i=0; i<amountOfTurnoverPositions; i++) {
		const int realTurnoverPos = mathematicalRemainder(turnoverPositions[i] - 1);
		
		if (currentPosition == realTurnoverPos) {
			notchSet = true;
		}
	}
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

void Rotor::CleanNotch() {
	notchSet = false;
}
