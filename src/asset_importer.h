#ifndef ASSET_IMPORTER_H
#define ASSET_IMPORTER_H

#include <godot_cpp/classes/node.hpp>

//Misc
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/core/class_db.hpp>

//Datatypes & Transforms
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/variant/color.hpp>
#include <godot_cpp/variant/transform3d.hpp>
#include <godot_cpp/templates/vector.hpp> // GODOT EQUIVALENT TO std::vector !!!! 

//Meshes, Textures, and Shapes
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/standard_material3d.hpp>
#include <godot_cpp/classes/collision_shape3d.hpp>

//Resource Related
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/image.hpp>
#include <godot_cpp/classes/image_texture.hpp>

//File Inclusions
#include "defs.h"

//Definitions



// everything in gdextension is defined in this namespace
namespace godot {
class AssetImporter : public Node {
    // this macro sets up a few internal things
	GDCLASS(AssetImporter, Node);

private:
	void apply_textures_to_mesh(MeshInstance3D* mesh_instance, const Ref<ImageTexture> &texture){
		if(mesh_instance){
			for(int i=0;i<mesh_instance->get_surface_override_material_count();i++){
				Ref<StandardMaterial3D> material = memnew(StandardMaterial3D());
				material->set_texture(StandardMaterial3D::TEXTURE_ALBEDO, texture);
				mesh_instance->set_surface_override_material(i, material);
			}
		} else {
			ERR_PRINT("Error: Unable Tpo Apply Texture To Mesh (MeshInstance == nullptr)");
		}
	}


protected:
    // a static function that Godot will call to find out which methods can be called and which properties it exposes
	static void _bind_methods(){}


public:
	AssetImporter(){}
	~AssetImporter(){}

	void _process(double delta) override {}
	void _enter_tree () override {}
	void _ready() override {}


	//Import a mesh from given filepath
	MeshInstance3D* import_mesh_gltf(const String &model_filepath, const String &texture_filepath){
		//Load Model from GLTF file
		Ref<PackedScene> gltf_scene = ResourceLoader::get_singleton()->load(model_filepath);
		
		//If not loaded propperly, print error msg and return nullptr
		if(gltf_scene.is_null()){
			ERR_PRINT("Failed to load GLTF file at provided filepath: "+model_filepath);
			return nullptr;
		}

		//Create an instance of the scene
		if(!gltf_scene->can_instantiate())ERR_PRINT("No Nodes In Scene To Instantiate");

		Node* root = gltf_scene->instantiate();
		//Another error output
		if(root == nullptr){
			ERR_PRINT("Failed to instantiate scene for gltf model.");
			return nullptr;
		}

		//Load Texture from filepath
		Ref<Image> image = ResourceLoader::get_singleton()->load(texture_filepath, "Image");
		//Another Error Msg
		if (image.is_null()) {
            ERR_PRINT("Failed to load texture at provided filepath: "+texture_filepath);
            return nullptr;
        }

		//Create a texture from the png
		Ref<ImageTexture> texture = ImageTexture::create_from_image(image);

		auto mesh_instance = Object::cast_to<MeshInstance3D>(root);
		if (mesh_instance) {
            apply_textures_to_mesh(mesh_instance, texture);
            return mesh_instance;
        }

        // If not, search for a MeshInstance3D in its children
        if(mesh_instance == nullptr)ERR_PRINT("Mesh is nullptr");
        return nullptr;
	}




	//Use this if you want a node to be added underneath the given parent node in the scene tree
	template <class T>
	bool create_or_add_child(T* &pointer, String name, Node3D* parent){
		
		Node* child = find_child(name);//find node with the given name (NAME MUST BE UNIQUE)
		if(child == nullptr){//if child node was not found, create it
			pointer = memnew(T);
			pointer->set_name(name);
			parent->add_child(pointer);//Add node as child of given node
			pointer->set_owner(get_tree()->get_edited_scene_root());
			return true;
		} else {
			pointer = dynamic_cast<T*>(child);//if node with name already exists, assign it to pointer
			return false;
		}
	}

};

}

#endif