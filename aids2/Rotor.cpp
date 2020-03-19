#include "Rotor.h"
#include <iostream>

Rotor::Rotor(RotorDTO* rotor)
{
	length = rotor->length;
	signalOutlet = new Circuit[length];
	currentPosition = 0;
	notchSet = false;

	populateWithPermutations(rotor);
	populateWithTurnovers(rotor);

	SetPosition(rotor->initialTurn);
}

void Rotor::populateWithPermutations(RotorDTO* rotor)
{	
	for(int i=0; i<length; i++) {
		signalOutlet[i].letter = i;
		signalOutlet[i].permutation = rotor->signalOutlet[i].permutation-1;
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
	for (int i = 0; i < amountOfTurnoverPositions; i++) {
		if (turnoverPositions[i]-1 == currentPosition && notchSet) {
			notchSet = false;
			return true;
		}
	}

	return false;
}


void Rotor::Turn()
{
	const Circuit temp = signalOutlet[0];
	const int lastIndex = length - 1;

	for (int i=0; i<lastIndex; i++) {
		signalOutlet[i] = signalOutlet[i + 1];
	}

	signalOutlet[lastIndex] = temp;

	currentPosition = (++currentPosition) % length;

	for (int i=0;i<amountOfTurnoverPositions;i++) {
		if (currentPosition == turnoverPositions[i]-1) {
			notchSet = true;
		}
	}
}

void Rotor::SetPosition(int position)
{
	while (currentPosition != position-1) {
		Turn();
	}

	notchSet = false;
}

int Rotor::GetLetterByPermutation(int input)
{
	const int permutation = signalOutlet[input].permutation;

	return findPositionOfPermutationInAlphabet(permutation);
}

int Rotor::GetPermutationByLetter(int input)
{
	const int letter = signalOutlet[input].letter;

	return findPositionOfPermutationLetterInPermutations(letter);
}

int Rotor::findPositionOfPermutationLetterInPermutations(int letter) const
{
	for (int i = 0; i < length; i++) {
		if (signalOutlet[i].permutation == letter) return i;
	}

	return 0;
}

int Rotor::findPositionOfPermutationInAlphabet(int permutation) const
{
	for(int i=0; i<length; i++) {
		if (signalOutlet[i].letter == permutation) return i;
	}
	
	return 0;
}