/**
 * PYTHON Wrapper for Clothoids
 * 
 * License MIT - See LICENSE file
 * 2019 Matteo Ragni, Claudio Kerov Ghiglianovich,
 *      Enrico Bertolazzi, Marco Frego
 */

#include "pybind11/pybind11.h"
#include "python-Interpolation.hh"

namespace py = pybind11;
using namespace G2lib;
using namespace G2lib::python;

PYBIND11_MODULE(_G2lib_Interpolation, m) {
  G2lib::python::wrap_interpolation(m);
}