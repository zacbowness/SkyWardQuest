/**************************************************************************/
/*  a_star2d.hpp                                                          */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

// THIS FILE IS GENERATED. EDITS WILL BE LOST.

#ifndef GODOT_CPP_A_STAR2D_HPP
#define GODOT_CPP_A_STAR2D_HPP

#include <godot_cpp/variant/packed_int64_array.hpp>
#include <godot_cpp/variant/packed_vector2_array.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/variant/vector2.hpp>

#include <godot_cpp/core/class_db.hpp>

#include <type_traits>

namespace godot {

class AStar2D : public RefCounted {
	GDEXTENSION_CLASS(AStar2D, RefCounted)

public:

	int64_t get_available_point_id() const;
	void add_point(int64_t id, const Vector2 &position, double weight_scale = 1.0);
	Vector2 get_point_position(int64_t id) const;
	void set_point_position(int64_t id, const Vector2 &position);
	double get_point_weight_scale(int64_t id) const;
	void set_point_weight_scale(int64_t id, double weight_scale);
	void remove_point(int64_t id);
	bool has_point(int64_t id) const;
	PackedInt64Array get_point_connections(int64_t id);
	PackedInt64Array get_point_ids();
	void set_point_disabled(int64_t id, bool disabled = true);
	bool is_point_disabled(int64_t id) const;
	void connect_points(int64_t id, int64_t to_id, bool bidirectional = true);
	void disconnect_points(int64_t id, int64_t to_id, bool bidirectional = true);
	bool are_points_connected(int64_t id, int64_t to_id, bool bidirectional = true) const;
	int64_t get_point_count() const;
	int64_t get_point_capacity() const;
	void reserve_space(int64_t num_nodes);
	void clear();
	int64_t get_closest_point(const Vector2 &to_position, bool include_disabled = false) const;
	Vector2 get_closest_position_in_segment(const Vector2 &to_position) const;
	PackedVector2Array get_point_path(int64_t from_id, int64_t to_id);
	PackedInt64Array get_id_path(int64_t from_id, int64_t to_id);
	virtual double _estimate_cost(int64_t from_id, int64_t to_id) const;
	virtual double _compute_cost(int64_t from_id, int64_t to_id) const;
protected:
	template <typename T, typename B>
	static void register_virtuals() {
		RefCounted::register_virtuals<T, B>();
		if constexpr (!std::is_same_v<decltype(&B::_estimate_cost),decltype(&T::_estimate_cost)>) {
			BIND_VIRTUAL_METHOD(T, _estimate_cost);
		}
		if constexpr (!std::is_same_v<decltype(&B::_compute_cost),decltype(&T::_compute_cost)>) {
			BIND_VIRTUAL_METHOD(T, _compute_cost);
		}
	}

public:

};

} // namespace godot

#endif // ! GODOT_CPP_A_STAR2D_HPP