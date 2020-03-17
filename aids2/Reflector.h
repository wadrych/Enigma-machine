#pragma once
#include "ElectroMechanicalElement.h"
class Reflector :
	public ElectroMechanicalElement
{
public:
	Reflector(int length);
	~Reflector() override;
	Reflector* Clone() const;
	int GetLetterByPermutation(int input) override;
	int GetPermutationByLetter(int input) override;
	
private:
	int length;

	int findPositionOfPermutationInAlphabet(int permutation) const;
	void populateWithPermutations() ;
};

