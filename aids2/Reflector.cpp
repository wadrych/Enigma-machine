#include "Reflector.h"

Reflector::Reflector(ReflectorDTO* reflector) {
	length = reflector->length;
	signalOutlet = new Circuit[length];

	populateWithPermutations(reflector);
}

void Reflector::populateWithPermutations(ReflectorDTO* reflector) {
	for (int i = 0; i < length; i++) {
		const int delta = (reflector->signalOutlet[i].permutation - 1) - i;
		signalOutlet[i].permutation = delta;
		signalOutlet[delta + i].letter = -delta;
	}
}

Reflector::~Reflector() {
}

int Reflector::GetLetterByPermutation(int input) {
	const int delta = signalOutlet[input].permutation;

	const int result = (input + delta) % length;
	return result >= 0 ? result : result + length;
}

int Reflector::GetPermutationByLetter(int input) {
	return input;
}