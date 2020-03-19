#pragma once
#include "ElectroMechanicalElement.h"

typedef struct ReflectorDTO {
	Circuit* signalOutlet;
	int length;
} reflectorDTO;

class Reflector :
	public ElectroMechanicalElement
{
public:
	Reflector(ReflectorDTO* reflector);
	~Reflector() override;
	int GetLetterByPermutation(int input) override;
	int GetPermutationByLetter(int input) override;
	
private:
	int length;

	int findPositionOfPermutationInAlphabet(int permutation) const;
	void populateWithPermutations(ReflectorDTO* reflector);
};

