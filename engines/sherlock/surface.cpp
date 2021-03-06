/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#include "sherlock/surface.h"
#include "sherlock/fonts.h"

namespace Sherlock {

Surface::Surface() : Graphics::ManagedSurface(), Fonts() {
}

Surface::Surface(int width, int height) : Graphics::ManagedSurface(width, height),
		Fonts() {
	create(width, height);
}

void Surface::writeString(const Common::String &str, const Common::Point &pt, uint overrideColor) {
	Fonts::writeString(this, str, pt, overrideColor);
}

void Surface::writeFancyString(const Common::String &str, const Common::Point &pt, uint overrideColor1, uint overrideColor2) {
	writeString(str, Common::Point(pt.x, pt.y), overrideColor1);
	writeString(str, Common::Point(pt.x + 1, pt.y), overrideColor1);
	writeString(str, Common::Point(pt.x + 2, pt.y), overrideColor1);
	writeString(str, Common::Point(pt.x, pt.y + 1), overrideColor1);
	writeString(str, Common::Point(pt.x + 2, pt.y + 1), overrideColor1);
	writeString(str, Common::Point(pt.x, pt.y + 2), overrideColor1);
	writeString(str, Common::Point(pt.x + 1, pt.y + 2), overrideColor1);
	writeString(str, Common::Point(pt.x + 2, pt.y + 2), overrideColor1);
	writeString(str, Common::Point(pt.x + 1, pt.y + 1), overrideColor2);
}

void Surface::SHtransBlitFrom(const ImageFrame &src, const Common::Point &pt,
		bool flipped, int overrideColor, int scaleVal) {
	Common::Point drawPt(pt.x + src.sDrawXOffset(scaleVal), pt.y + src.sDrawYOffset(scaleVal));
	SHtransBlitFrom(src._frame, drawPt, flipped, overrideColor, scaleVal);
}

void Surface::SHtransBlitFrom(const Graphics::Surface &src, const Common::Point &pt,
		bool flipped, int overrideColor, int scaleVal) {
	Common::Rect srcRect(0, 0, src.w, src.h);
	Common::Rect destRect(pt.x, pt.y, pt.x + src.w * SCALE_THRESHOLD / scaleVal,
		pt.y + src.h * SCALE_THRESHOLD / scaleVal);
	
	Graphics::ManagedSurface::transBlitFrom(src, srcRect, destRect, TRANSPARENCY,
		flipped, overrideColor);
}


} // End of namespace Sherlock
