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
	void Turn();
	int GetLetterByPermutation(int input) override;
	int GetPermutationByLetter(int input) override;
	bool IsNextNotchPosition();
	bool Rotated();
	
private:
	RotorDTO* rotorPattern;
	int currentPosition;
	bool* turnoverPositions;
	int amountOfTurnoverPositions;
	int length;
	bool notchSet;
	bool isRotated;

	void populateWithPermutations();
	void populateWithTurnovers();
	int getIndex(int index) const;
	int mathematicalRemainder(int value) const;
	void setInitialPosition();
};

