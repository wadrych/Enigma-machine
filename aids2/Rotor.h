#pragma once

#include  "ElectroMechanicalElement.h"

typedef struct RotorDTO {
	Circuit* signalOutlet;
	int length;
	int* turnoverPositions;
	int amountOfTurnoverPositions;
	int currentPosition;
	int initialTurn;
} rotor;

class Rotor :
	public ElectroMechanicalElement
{
public:
	Rotor(RotorDTO* rotor);
	~Rotor() override;
	void SetInitialPosition(int position);
	bool IsLocked();
	void Turn();
	int GetLetterByPermutation(int input) override;
	int GetPermutationByLetter(int input) override;
	bool IsLockedBefore();
	
private:
	int currentPosition;
	int* turnoverPositions;
	int amountOfTurnoverPositions;
	int length;
	bool notchSet;

	void populateWithPermutations(RotorDTO* rotor);
	void populateWithTurnovers(RotorDTO* rotor);
	int getIndex(int index) const;
};

