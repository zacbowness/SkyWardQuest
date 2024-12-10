#ifndef BeeBlackBody_H
#define BeeBlackBody_H

#include "bee_part.h"

// everything in gdextension is defined in this namespace
namespace godot {
class BeeBBody : public BeePart {
    // this macro sets up a few internal things
	GDCLASS(BeeBBody, BeePart);

// private:

	
protected:
    // a static function that Godot will call to find out which methods can be called and which properties it exposes
	static void _bind_methods();

public:
	BeeBBody();
	~BeeBBody();

	void _enter_tree ( ) override;
	void _process(double delta) override;

};

}

#endif