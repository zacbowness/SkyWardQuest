#ifndef BeeEye_H
#define BeeEye_H

#include "bee_part.h"

// everything in gdextension is defined in this namespace
namespace godot {
class BeeEye : public BeePart {
    // this macro sets up a few internal things
	GDCLASS(BeeEye, BeePart);

// private:

	
protected:
    // a static function that Godot will call to find out which methods can be called and which properties it exposes
	static void _bind_methods();

public:
	BeeEye();
	~BeeEye();

	void _enter_tree ( ) override;
	void _process(double delta) override;

};

}

#endif