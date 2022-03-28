/** * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * @file BaseCurve_using.hxx
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

/**
 * @note This is a special file that is included inside the BaseCurve child
 *       classes in order to fastly redefine part of their interface. This
 *       file is not intended for direct inclusion. This is why there is no header
 *       guard for this file (and shall not be included)
 */

using BaseCurve::theta_begin;
using BaseCurve::theta_end;

using BaseCurve::x_begin;
using BaseCurve::x_end;
using BaseCurve::y_begin;
using BaseCurve::y_end;

using BaseCurve::x_begin_ISO;
using BaseCurve::x_end_ISO;
using BaseCurve::y_begin_ISO;
using BaseCurve::y_end_ISO;

using BaseCurve::x_begin_SAE;
using BaseCurve::x_end_SAE;
using BaseCurve::y_begin_SAE;
using BaseCurve::y_end_SAE;

using BaseCurve::tx_Begin;
using BaseCurve::tx_End;
using BaseCurve::ty_Begin;
using BaseCurve::ty_End;

using BaseCurve::nx_Begin_ISO;
using BaseCurve::nx_End_ISO;
using BaseCurve::ny_Begin_ISO;
using BaseCurve::ny_End_ISO;

using BaseCurve::nx_Begin_SAE;
using BaseCurve::nx_End_SAE;
using BaseCurve::ny_Begin_SAE;
using BaseCurve::ny_End_SAE;

using BaseCurve::X;
using BaseCurve::X_D;
using BaseCurve::X_DD;
using BaseCurve::X_DDD;

using BaseCurve::Y;
using BaseCurve::Y_D;
using BaseCurve::Y_DD;
using BaseCurve::Y_DDD;

using BaseCurve::X_SAE;
using BaseCurve::X_SAE_D;
using BaseCurve::X_SAE_DD;
using BaseCurve::X_SAE_DDD;

using BaseCurve::Y_SAE;
using BaseCurve::Y_SAE_D;
using BaseCurve::Y_SAE_DD;
using BaseCurve::Y_SAE_DDD;

using BaseCurve::X_ISO;
using BaseCurve::X_ISO_D;
using BaseCurve::X_ISO_DD;
using BaseCurve::X_ISO_DDD;

using BaseCurve::Y_ISO;
using BaseCurve::Y_ISO_D;
using BaseCurve::Y_ISO_DD;
using BaseCurve::Y_ISO_DDD;

using BaseCurve::evaluate_ISO;
using BaseCurve::evaluate_SAE;

using BaseCurve::eval;
using BaseCurve::eval_D;
using BaseCurve::eval_DD;
using BaseCurve::eval_DDD;

using BaseCurve::eval_ISO;
using BaseCurve::eval_ISO_D;
using BaseCurve::eval_ISO_DD;
using BaseCurve::eval_ISO_DDD;

using BaseCurve::eval_SAE;
using BaseCurve::eval_SAE_D;
using BaseCurve::eval_SAE_DD;
using BaseCurve::eval_SAE_DDD;

using BaseCurve::closest_point_ISO;
using BaseCurve::closest_point_SAE;
using BaseCurve::distance_ISO;
using BaseCurve::distance_SAE;

///
/// eof: BaseCurve_using.hxx
///
