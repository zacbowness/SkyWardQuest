	#ifndef TWODSCENE_H
	#define TWODSCENE_H

	#include <godot_cpp/classes/node3d.hpp>
	#include <godot_cpp/variant/utility_functions.hpp>
	#include <godot_cpp/classes/mesh_instance3d.hpp>
	#include <godot_cpp/godot.hpp>
	#include <godot_cpp/core/class_db.hpp>
	#include <godot_cpp/classes/engine.hpp>
	#include <godot_cpp/classes/scene_tree.hpp>
	#include <godot_cpp/classes/label.hpp>
	#include <godot_cpp/classes/node2d.hpp>
	#include <godot_cpp/variant/color.hpp>


	#include "defs.h"

	namespace godot {
	class Scene2D : public  Node2D{
		GDCLASS(Scene2D, Node2D);

	protected:
		static void _bind_methods();


	private:
		

	public:
		Scene2D();
		~Scene2D();
		void _enter_tree() override;
		void _process(double) override;
		void swapScene();
		void setFont(Label*, int);
		void setColour(Label*, const Color&);
		void createTitle();
		void createInfo();
		void swapScene(String);
		Label* title;
		Label* info;
		

		template <class T>
		// returns true if pointer is brand-new; false if retrieved from SceneTree
		bool create_and_add_as_child(T* &pointer, String name){

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
	}//namespace end

	#endif