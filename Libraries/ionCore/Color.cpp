
#include "Color.h"


namespace ion
{
	namespace Color
	{

		color3f const White = color3f(1);
		color3f const Black = color3f(0);

		color3f const Basic::White = color3f(1, 1, 1);
		color3f const Basic::Grey = color3f(0.5f, 0.5f, 0.5f);
		color3f const Basic::Black = color3f(0, 0, 0);
		color3f const Basic::Red = color3f(1, 0, 0);
		color3f const Basic::Orange = color3f(1, 0.5f, 0);
		color3f const Basic::Yellow = color3f(1, 1, 0);
		color3f const Basic::Green = color3f(0, 1, 0);
		color3f const Basic::Cyan = color3f(0, 1, 1);
		color3f const Basic::Blue = color3f(0, 0, 1);
		color3f const Basic::Magenta = color3f(1, 0, 1);

		uint PackBits24(color3i const & Color)
		{
			uint const Red = Color.Red;
			uint const Green = Color.Green;
			uint const Blue = Color.Blue;
			return (Red << 16) | (Green << 8) | (Blue);
		}

		color3i UnpackBits24(uint const Value)
		{
			color3i Color;
			Color.Red = (Value >> 16) & 0xFF;
			Color.Green = (Value >> 8) & 0xFF;
			Color.Blue = Value & 0xFF;
			return Color;
		}

		color3i Hex(uint const Value)
		{
			color3i Color;
			Color.Red = (Value >> 16) & 0xFF;
			Color.Green = (Value >> 8) & 0xFF;
			Color.Blue = Value & 0xFF;
			return Color;
		}

		color3f HSV(float const H, float const S, float const V)
		{
			// Convert hsv floats ([0-1],[0-1],[0-1]) to rgb floats ([0-1],[0-1],[0-1]), from Foley & van Dam p593
			// also http://en.wikipedia.org/wiki/HSL_and_HSV
			// Copied from imgui.cpp

			//
			// The MIT License (MIT)
			// 
			// Original Work Copyright (c) 2014-2015 Omar Cornut and ImGui contributors
			// Modified Work Copyright (c) 2017
			// 
			// Permission is hereby granted, free of charge, to any person obtaining a copy
			// of this software and associated documentation files (the "Software"), to deal
			// in the Software without restriction, including without limitation the rights
			// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
			// copies of the Software, and to permit persons to whom the Software is
			// furnished to do so, subject to the following conditions:
			// 
			// The above copyright notice and this permission notice shall be included in all
			// copies or substantial portions of the Software.
			// 
			// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
			// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
			// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
			// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
			// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
			// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
			// SOFTWARE.
			//

			if (S == 0.0f)
			{
				// gray
				return color3f(V);
			}

			float const Hue = fmodf(H, 1.0f) / (60.0f/360.0f);
			int   i = (int) Hue;
			float f = Hue - (float)i;
			float p = V * (1.0f - S);
			float q = V * (1.0f - S * f);
			float t = V * (1.0f - S * (1.0f - f));

			switch (i)
			{
			case 0:
				return color3f(V, t, p);
			case 1:
				return color3f(q, V, p);
			case 2:
				return color3f(p, V, t);
			case 3:
				return color3f(p, q, V);
			case 4:
				return color3f(t, p, V);
			case 5:
			default:
				return color3f(V, p, q);
			}
		}

		vec3f ToHSV(color3f const & Color)
		{
			// Original Work Copyright (c) 2014, Jan Winkler <winkler@cs.uni-bremen.de>
			// All rights reserved.
			//
			// Redistribution and use in source and binary forms, with or without
			// modification, are permitted provided that the following conditions are met:
			//
			//     * Redistributions of source code must retain the above copyright
			//       notice, this list of conditions and the following disclaimer.
			//     * Redistributions in binary form must reproduce the above copyright
			//       notice, this list of conditions and the following disclaimer in the
			//       documentation and/or other materials provided with the distribution.
			//     * Neither the name of Universität Bremen nor the names of its
			//       contributors may be used to endorse or promote products derived from
			//       this software without specific prior written permission.
			//
			// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
			// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
			// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
			// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
			// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
			// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
			// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
			// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
			// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
			// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
			// POSSIBILITY OF SUCH DAMAGE.

			// Modified Work Copyright (c) 2017, Ian Dunn

			float fCMax = Max(Color.Red, Color.Green, Color.Blue);
			float fCMin = Min(Color.Red, Color.Green, Color.Blue);
			float fDelta = fCMax - fCMin;

			float Hue = 0, Value = 0, Saturation = 0;

			if (fDelta > 0)
			{
				if (fCMax == Color.Red)
				{
					Hue = 60 * (fmodf(((Color.Green - Color.Blue) / fDelta), 6));
				}
				else if (fCMax == Color.Green)
				{
					Hue = 60 * (((Color.Blue - Color.Red) / fDelta) + 2);
				}
				else if (fCMax == Color.Blue)
				{
					Hue = 60 * (((Color.Red - Color.Green) / fDelta) + 4);
				}

				if (fCMax > 0)
				{
					Saturation = fDelta / fCMax;
				}
				else
				{
					Saturation = 0;
				}

				Value = fCMax;
			}
			else
			{
				Hue = 0;
				Saturation = 0;
				Value = fCMax;
			}

			if (Hue < 0)
			{
				Hue = 360 + Hue;
			}

			return vec3f(Hue / 360.f, Saturation, Value);
		}
	}

}
