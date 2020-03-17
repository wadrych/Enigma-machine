#include "Rotor.h"
#include <iostream>

Rotor::Rotor(int length) :  length(length)
{
	signalOutlet = new Circuit[length];
	currentPosition = 0;

	populateWithPermutations();
	pupulateWithTurnovers();
}

void Rotor::populateWithPermutations()
{
	int permutation;
	
	for(int i=0; i<length; i++) {
		scanf_s("%i", &permutation);
		signalOutlet[i].letter = i;
		signalOutlet[i].permutation = permutation-1;
	}
}

void Rotor::pupulateWithTurnovers()
{
	int turnover;
	
	scanf_s("%i", &amountOfTurnoverPositions);

	turnoverPositions = new int[amountOfTurnoverPositions];

	for(int i=0; i<amountOfTurnoverPositions; i++) {
		scanf_s("%i", &turnover);
		turnoverPositions[i] = turnover-1;
	}
}

Rotor::~Rotor()
{
}

bool Rotor::IsLocked() const
{
	for(int i=0; i<amountOfTurnoverPositions; i++) {
		if(turnoverPositions[i]-1 == currentPosition) {
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
}

void Rotor::SetPosition(int position)
{
	while (currentPosition != position-1) {
		Turn();
	}
	Print();
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

Rotor* Rotor::Clone() const
{
	return new Rotor(*this); 
}

void Rotor::Print()
{
	for(int i=0;i<length;i++)
	{
		printf("%i ", signalOutlet[i].letter+1);
	}
	printf("\n");
	for (int i = 0; i < length; i++)
	{
		printf("%i ", signalOutlet[i].permutation+1);
	}
	printf("\n");
}
