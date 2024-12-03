#ifndef QUATCAMERA_H
#define QUATCAMERA_H

// parent class
#include <godot_cpp/classes/camera3d.hpp>
#include <godot_cpp/classes/node3d.hpp>

#include <godot_cpp/classes/input.hpp>

#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/vector3.hpp>
#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/variant/packed_vector3_array.hpp>
#include <godot_cpp/variant/quaternion.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/viewport.hpp>

#include "defs.h"


// everything in gdextension is defined in this namespace
namespace godot {
class QuatCamera : public Camera3D {
    // this macro sets up a few internal things
	GDCLASS(QuatCamera, Camera3D);

private:

	// this one is the one we will use to transform our side, up and forward vectors for the GetX functions. 
	// why would it be a bad idea to transform by the built-in quaternion?
	Quaternion our_quaternion;
	
	Vector3 forward_;
	Vector3 side_;

	Vector3 GetForward() const;
	Vector3 GetUp() const;
	Vector3 GetSide() const;
	float angle_diff(Vector3 vec1, Vector3 vec2);

	void Pitch(float angle);
	void Roll(float angle);
	

	float throttle;// float value between 0 and 1, to scale speed for both forward and backwards movement
	float top_speed;// maximum speed of the rocket
	float accel_factor;// how fast the rocket can accelerate forwards

	bool GameOver;//OLD - DELETE THIS

	Vector2 last_mouse_position;
	

protected:
    // a static function that Godot will call to find out which methods can be called and which properties it exposes
	static void _bind_methods();

public:
	QuatCamera();
	~QuatCamera();

	void _enter_tree() override;
	void _ready() override;
	void _process(double delta) override;

	void pitch_camera(float dist, double delta);
	void Yaw(float angle);
};

}

#endif