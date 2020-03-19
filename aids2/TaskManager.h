#pragma once
#include <stdio.h>
#include "Enigma.h"
#include "ReflectorService.h"
#include "RotorService.h"

class TaskManager
{
public:
	TaskManager(RotorService* rotorService, ReflectorService* reflectorService);
	~TaskManager();

	void PerformTask();
	
private:
	RotorService* rotorService;
	ReflectorService* reflectorService;

	void SetRotors(Enigma* enigma, int amountOfRotors);
	void SetReflector(Enigma* enigma);
	static void EncodeLetter(Enigma* enigma, int* letter);
};

