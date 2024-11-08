/**************************************************************************/
/*  canvas_texture.hpp                                                    */
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

#ifndef GODOT_CPP_CANVAS_TEXTURE_HPP
#define GODOT_CPP_CANVAS_TEXTURE_HPP

#include <godot_cpp/classes/canvas_item.hpp>
#include <godot_cpp/variant/color.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/texture2d.hpp>

#include <godot_cpp/core/class_db.hpp>

#include <type_traits>

namespace godot {

class CanvasTexture : public Texture2D {
	GDEXTENSION_CLASS(CanvasTexture, Texture2D)

public:

	void set_diffuse_texture(const Ref<Texture2D> &texture);
	Ref<Texture2D> get_diffuse_texture() const;
	void set_normal_texture(const Ref<Texture2D> &texture);
	Ref<Texture2D> get_normal_texture() const;
	void set_specular_texture(const Ref<Texture2D> &texture);
	Ref<Texture2D> get_specular_texture() const;
	void set_specular_color(const Color &color);
	Color get_specular_color() const;
	void set_specular_shininess(double shininess);
	double get_specular_shininess() const;
	void set_texture_filter(CanvasItem::TextureFilter filter);
	CanvasItem::TextureFilter get_texture_filter() const;
	void set_texture_repeat(CanvasItem::TextureRepeat repeat);
	CanvasItem::TextureRepeat get_texture_repeat() const;
protected:
	template <typename T, typename B>
	static void register_virtuals() {
		Texture2D::register_virtuals<T, B>();
	}

public:

};

} // namespace godot

#endif // ! GODOT_CPP_CANVAS_TEXTURE_HPP