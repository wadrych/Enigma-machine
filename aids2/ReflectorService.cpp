#include "ReflectorService.h"

ReflectorService::ReflectorService(int alphabetSize) : alphabetSize(alphabetSize) {
	reflectorsArray = nullptr;
	length = 0;
}

ReflectorService::~ReflectorService() {
	for(int i=0;i<length;i++) {
		delete[] reflectorsArray[i]->signalOutlet;
		reflectorsArray[i]->signalOutlet = nullptr;
		delete reflectorsArray[i];
		reflectorsArray[i] = nullptr;
	}
	delete[] reflectorsArray;
	reflectorsArray = nullptr;
}

void ReflectorService::Create() {
	scanf_s("%i", &length);

	reflectorsArray = new ReflectorDTO* [length];

	for (int i = 0; i < length; i++) {
		reflectorsArray[i] = createReflector();
	}
}

ReflectorDTO* ReflectorService::createReflector() {
	ReflectorDTO* newReflector = new ReflectorDTO();

	newReflector->length = alphabetSize;

	Circuit* signalOutlet = new Circuit[newReflector->length];

	for (int i = 0; i < newReflector->length; i++) {
		int permutation;
		scanf_s("%i", &permutation);
		signalOutlet[i].permutation = permutation;
		signalOutlet[i].letter = i;
	}

	newReflector->signalOutlet = signalOutlet;

	return newReflector;
}


ReflectorDTO* ReflectorService::GetReflector(int index) {
	return reflectorsArray[index];
}

