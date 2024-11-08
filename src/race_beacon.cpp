#include "race_beacon.h"
#include <godot_cpp/classes/resource_loader.hpp>


using namespace godot;

void RaceBeacon::_bind_methods() {}

RaceBeacon::RaceBeacon() {
	isNextBeacon = false;//default to false
}

RaceBeacon::~RaceBeacon() {}
