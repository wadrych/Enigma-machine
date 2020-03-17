#pragma once

#include <stdio.h>

typedef struct Circuit {
	int letter;
	int permutation;
} circuit;

class ElectroMechanicalElement {
public:
	virtual int GetLetterByPermutation(int input) = 0;
	virtual int GetPermutationByLetter(int input) = 0;
	virtual ~ElectroMechanicalElement();
	
protected:
	Circuit* signalOutlet;
};

