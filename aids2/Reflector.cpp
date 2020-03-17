#include "Reflector.h"

Reflector::Reflector(int length) : length(length)
{
	signalOutlet = new Circuit[length];

	populateWithPermutations();
}

void Reflector::populateWithPermutations()
{
	int permutation;

	for (int i = 0; i < length; i++) {
		scanf_s("%i", &permutation);
		signalOutlet[i].letter = i;
		signalOutlet[i].permutation = permutation-1;
	}
}

Reflector::~Reflector()
{
}

int Reflector::GetLetterByPermutation(int input)
{
	const int permutation = signalOutlet[input].permutation;

	return findPositionOfPermutationInAlphabet(permutation);
}


int Reflector::findPositionOfPermutationInAlphabet(int permutation) const
{
	for (int i = 0; i < length; i++) {
		if (signalOutlet[i].letter == permutation) return i;
	}

	return 0;
}

int Reflector::GetPermutationByLetter(int input) {
	return 0;
}


Reflector* Reflector::Clone() const
{
	return new Reflector(*this);
}
