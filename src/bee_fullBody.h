#ifndef BEEBODY_H
#define BEEBODY_H

#include "bee_part.h"
#include "bee_yellowBody.h"
#include "bee_blackBody.h"
#include "bee.h"

// everything in gdextension is defined in this namespace
namespace godot {
class BeeBody : public BeePart {
    // this macro sets up a few internal things
	GDCLASS(BeeBody, BeePart);

private:
	BeeYBody* yellowBody1;
	BeeYBody* yellowBody2;
	BeeBBody* blackBody1;
	

protected:
    // a static function that Godot will call to find out which methods can be called and which properties it exposes
	static void _bind_methods();

public:
	BeeBody();
	~BeeBody();

	void _enter_tree ( ) override;
	void _process(double delta) override;

	Vector3 newPos;

template <class T>
// returns true if pointer is brand-new; false if retrieved from SceneTree
bool create_and_add_as_child(T* &pointer, String name, bool search){
	// this is the default behaviour
	// added the search parameter so that we can skip the slow "find_child" call during runtime (not applicable to this demo, you should always use search = true until next assignment)
	if(search == false){
		pointer = memnew(T);
		pointer->set_name(name);
		add_child(pointer);
		pointer->set_owner(get_tree()->get_edited_scene_root());
		return true;
	}

	// always only have to search once if we save it here
	Node* child = find_child(name);
	
	if(child == nullptr){
		pointer = memnew(T);
		pointer->set_name(name);
		add_child(pointer);
		pointer->set_owner(get_tree()->get_edited_scene_root());
		return true;
	}
	else{
		pointer = dynamic_cast<T*>(child);
		return false;
	}
}

};

}

#endif