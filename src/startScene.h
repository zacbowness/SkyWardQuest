	#ifndef STARTSCENE_H
	#define STARTSCENE_H

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
	#include "2dScene.h"

	namespace godot {
	class startScene : public Scene2D {
		GDCLASS(startScene, Scene2D);

	protected:
		static void _bind_methods();


	private:
		

	public:
		startScene();
		~startScene();
		void _enter_tree() override;
		void _process(double) override;
		void createTitle();
		void createInfo();
		Label* title;
		Label* info;

	};
	}//namespace end

	#endif