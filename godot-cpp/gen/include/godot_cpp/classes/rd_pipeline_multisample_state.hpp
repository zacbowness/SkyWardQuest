/**************************************************************************/
/*  rd_pipeline_multisample_state.hpp                                     */
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

#ifndef GODOT_CPP_RD_PIPELINE_MULTISAMPLE_STATE_HPP
#define GODOT_CPP_RD_PIPELINE_MULTISAMPLE_STATE_HPP

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/ref_counted.hpp>
#include <godot_cpp/classes/rendering_device.hpp>
#include <godot_cpp/variant/typed_array.hpp>

#include <godot_cpp/core/class_db.hpp>

#include <type_traits>

namespace godot {

class RDPipelineMultisampleState : public RefCounted {
	GDEXTENSION_CLASS(RDPipelineMultisampleState, RefCounted)

public:

	void set_sample_count(RenderingDevice::TextureSamples p_member);
	RenderingDevice::TextureSamples get_sample_count() const;
	void set_enable_sample_shading(bool p_member);
	bool get_enable_sample_shading() const;
	void set_min_sample_shading(double p_member);
	double get_min_sample_shading() const;
	void set_enable_alpha_to_coverage(bool p_member);
	bool get_enable_alpha_to_coverage() const;
	void set_enable_alpha_to_one(bool p_member);
	bool get_enable_alpha_to_one() const;
	void set_sample_masks(const TypedArray<int> &masks);
	TypedArray<int> get_sample_masks() const;
protected:
	template <typename T, typename B>
	static void register_virtuals() {
		RefCounted::register_virtuals<T, B>();
	}

public:

};

} // namespace godot

#endif // ! GODOT_CPP_RD_PIPELINE_MULTISAMPLE_STATE_HPP