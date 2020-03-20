#include "ElectroMechanicalElement.h"

ElectroMechanicalElement::~ElectroMechanicalElement() {
	delete[] signalOutlet;
}
