#pragma once

#include  "ElectroMechanicalElement.h"

class Rotor :
	public ElectroMechanicalElement
{
public:
	Rotor(int length);
	~Rotor() override;
	Rotor* Clone() const;
	void SetPosition(int position);
	bool IsLocked() const;
	void Turn();
	int GetLetterByPermutation(int input) override;
	int GetPermutationByLetter(int input) override;
	void Print();
	
private:
	int currentPosition;
	int* turnoverPositions;
	int amountOfTurnoverPositions;
	int length;

	int findPositionOfPermutationInAlphabet(int permutation) const;
	int findPositionOfPermutationLetterInPermutations(int letter) const;
	void populateWithPermutations();
	void pupulateWithTurnovers();
};

