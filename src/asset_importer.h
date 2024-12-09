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
	Ref<ImageTexture> import_img_tex(String filepath){
		Ref<Image> image = ResourceLoader::get_singleton()->load(filepath, "Image");
		
		if(image.is_null()){
			ERR_PRINT("Image Could Not Be Imported From: "+filepath);
			return nullptr;
		}

		Ref<ImageTexture> texture = ImageTexture::create_from_image(image);
		//UtilityFunctions::print("Image Converted To Texture :)");

		if(texture.is_null()){
			ERR_PRINT("Image Could Not Be Converted To Texture");
			return nullptr;
		} else return texture;
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
	Ref<ArrayMesh> import_mesh(String mesh_filepath, Vector<String> texture_filepath){
		//if(DEBUG)UtilityFunctions::print("Importing File: "+mesh_filepath);
		//Load Model from GLTF file
		Ref<ArrayMesh> mesh_import = ResourceLoader::get_singleton()->load(mesh_filepath);
		
		//If not loaded propperly, print error msg and return nullptr
		if(mesh_import.is_null()){
			ERR_PRINT("Failed to load res file at provided filepath: "+mesh_filepath);
			return nullptr;
		}

		for(int i=0;i<mesh_import->get_surface_count();i++){
			StandardMaterial3D* material = memnew(StandardMaterial3D);
			Ref<ImageTexture> img_tex = import_img_tex(texture_filepath[i]);

			//UtilityFunctions::print(texture_filepath[i]);
			if(!img_tex.is_null()) material->set_texture(StandardMaterial3D::TEXTURE_ALBEDO, img_tex);
			else return nullptr;
			if(i<mesh_import->get_surface_count()) mesh_import->surface_set_material(i, material);
			else ERR_PRINT("Not All Textures Applied, Surface Count < Provided Textures");
		}

		return mesh_import;
	}

	Ref<ConcavePolygonShape3D> shape_from_Arraymesh(Ref<ArrayMesh> mesh){
		Ref<ConcavePolygonShape3D> collision_shape_mesh;
		collision_shape_mesh = mesh->create_trimesh_shape();
		return collision_shape_mesh;
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