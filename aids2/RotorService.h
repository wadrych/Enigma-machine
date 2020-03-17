#pragma once
#include "Rotor.h"

class RotorService
{
public:
	RotorService(int length);
	~RotorService();
	void Create();
	Rotor* GetRotor(int index);
	
private:
	Rotor** rotorsArray;
	int length;
};

