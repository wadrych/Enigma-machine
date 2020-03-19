#include "Reflector.h"

Reflector::Reflector(ReflectorDTO* reflector)
{
	length = reflector->length;
	signalOutlet = new Circuit[length];

	populateWithPermutations(reflector);
}

void Reflector::populateWithPermutations(ReflectorDTO* reflector)
{
	for (int i = 0; i < length; i++) {
		signalOutlet[i].letter = i;
		signalOutlet[i].permutation = reflector->signalOutlet[i].permutation-1;
	}
}

Reflector::~Reflector() {
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
	return input;
}