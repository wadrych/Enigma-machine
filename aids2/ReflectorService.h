#pragma once
#include "Reflector.h"
class ReflectorService
{
public:
	ReflectorService(int length);
	~ReflectorService();
	void Create();
	Reflector* GetReflector(int index);
	
private:
	Reflector** reflectorsArray;
	int length;
	
};

