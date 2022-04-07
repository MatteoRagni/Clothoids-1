/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @file Clothoids.hh
 * @author Matteo Ragni (info@ragni.me)
 *
 * @copyright Copyright (c) 2022 Matteo Ragni
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Based on the work of:
 * Enrico Bertolazzi http://ebertolazzi.github.io/Clothoids/
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#pragma once

#ifndef CLOTHOIDS_dot_HH
#define CLOTHOIDS_dot_HH

#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cmath>

#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include <iterator>

#include "Clothoids/Types.hxx"
#include "Clothoids/Constants.hxx"
#include "Clothoids/G2lib.hxx"
#include "Clothoids/Triangle2D.hxx"
#include "Clothoids/BaseCurve.hxx"
#include "Clothoids/AABBtree.hxx"
#include "Clothoids/Fresnel.hxx"
#include "Clothoids/Line.hxx"
#include "Clothoids/Circle.hxx"
#include "Clothoids/Biarc.hxx"
#include "Clothoids/Clothoid.hxx"
#include "Clothoids/PolyLine.hxx"
#include "Clothoids/BiarcList.hxx"
#include "Clothoids/ClothoidList.hxx"
#include "Clothoids/ClothoidSpline-Interpolation.hxx"

#endif

///
/// eof: Clothoids.hh
///
