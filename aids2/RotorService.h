#pragma once
#include "Rotor.h"

class RotorService {
public:
	RotorService(int alphabetSize);
	~RotorService();
	void Create();
	RotorDTO* GetRotor(int index);
	
private:
	RotorDTO** rotorsArray;
	int alphabetSize;
	int length;

	RotorDTO* createRotor();
	static void readCircuits(RotorDTO* newRotor, Circuit* signalOutlet);
	static void readTurnovers(RotorDTO* newRotor,  int* turnoverPositions);
};

