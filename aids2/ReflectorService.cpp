#include "ReflectorService.h"
#include "Rotor.h"

ReflectorService::ReflectorService(int length) : length(length)
{
}

ReflectorService::~ReflectorService()
{
	delete[] reflectorsArray;
}

void ReflectorService::Create()
{
	int amountOfReflectors;
	scanf_s("%i", &amountOfReflectors);

	reflectorsArray = new Reflector* [amountOfReflectors];

	for (int i = 0; i < amountOfReflectors; i++) {
		Reflector *newReflector = new Reflector(length);
		reflectorsArray[i] = newReflector;
	}
}

Reflector* ReflectorService::GetReflector(int index)
{
	return reflectorsArray[index];
}

