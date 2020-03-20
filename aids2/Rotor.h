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
	public ElectroMechanicalElement {
public:
	Rotor(RotorDTO* rotor);
	~Rotor() override;
	bool IsLocked();
	void Turn();
	int GetLetterByPermutation(int input) override;
	int GetPermutationByLetter(int input) override;
	bool IsLockedBefore();
	void CleanNotch();
	
private:
	RotorDTO* rotorPattern;
	int currentPosition;
	int* turnoverPositions;
	int amountOfTurnoverPositions;
	int length;
	bool notchSet;

	void populateWithPermutations();
	void populateWithTurnovers();
	int getIndex(int index) const;
	int mathematicalRemainder(int value) const;
	void setInitialPosition();
};

