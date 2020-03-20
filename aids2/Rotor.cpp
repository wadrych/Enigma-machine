#include "Rotor.h"
#include <iostream>

Rotor::Rotor(RotorDTO* rotor)
{
	length = rotor->length;
	signalOutlet = new Circuit[length];
	currentPosition = 0;
	notchSet = false;
	turnoverPositions = nullptr;
	amountOfTurnoverPositions = 0;

	populateWithPermutations(rotor);
	populateWithTurnovers(rotor);

	SetInitialPosition(rotor->initialTurn);
}

void Rotor::populateWithPermutations(RotorDTO* rotor)
{	
	for (int i = 0; i < length; i++) {
		const int delta = (rotor->signalOutlet[getIndex(i)].permutation - 1) - i;
		signalOutlet[getIndex(i)].permutation = delta;
		signalOutlet[getIndex(delta +i)].letter = -delta;
	}
}

void Rotor::populateWithTurnovers(RotorDTO* rotor)
{
	amountOfTurnoverPositions = rotor->amountOfTurnoverPositions;
	turnoverPositions = new int[amountOfTurnoverPositions];

	for(int i=0; i<amountOfTurnoverPositions; i++) {
		turnoverPositions[i] = rotor->turnoverPositions[i]-1;
	}
}

Rotor::~Rotor() {
	delete[] turnoverPositions;
}

bool Rotor::IsLocked()
{
	for(int i=0; i<amountOfTurnoverPositions; i++) {
		if(turnoverPositions[i] == currentPosition && notchSet) {
			notchSet = false;
			return true;
		}
	}
	return false;
}

bool Rotor::IsLockedBefore()
{
	for (int i=0; i<amountOfTurnoverPositions; i++) {
		const int realTurnoverPos = mathematicalRemainder(turnoverPositions[i] - 1);
		if (realTurnoverPos == currentPosition && notchSet) {
			notchSet = false;
			return true;
		}
	}
	return false;
}

void Rotor::Turn()
{
	currentPosition++;
	currentPosition = currentPosition % length;

	for (int i=0;i<amountOfTurnoverPositions;i++) {
		const int realTurnoverPos = mathematicalRemainder(turnoverPositions[i] - 1);
		
		if (currentPosition == realTurnoverPos) {
			notchSet = true;
		}
	}
}

void Rotor::SetInitialPosition(int position)
{
	currentPosition = position-1;
	notchSet = false;
}

int Rotor::GetLetterByPermutation(int input)
{
	const int delta = signalOutlet[getIndex(input)].permutation;

	const int result = (input + delta) % length;
	return result >= 0 ? result : result + length;
}

int Rotor::GetPermutationByLetter(int input)
{
	const int delta = signalOutlet[getIndex(input)].letter;

	const int result = (input + delta) % length;
	return result >= 0 ? result : result + length;
}

int Rotor::getIndex(int index) const {
	const int currentIndex = (index + currentPosition) % length;
	
	return currentIndex;
}

int Rotor::mathematicalRemainder(int value) const {
	const int result = value % length;

	if (result >= 0)
		return result;
	else
		return result + length;
}