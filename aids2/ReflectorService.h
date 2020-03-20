#pragma once
#include "Reflector.h"

class ReflectorService {
public:
	ReflectorService(int alphabetSize);
	~ReflectorService();
	void Create();
	ReflectorDTO* GetReflector(int index);
	
private:
	ReflectorDTO** reflectorsArray;
	int alphabetSize;
	int length;

	ReflectorDTO* createReflector();
};

