/**
 * PYTHON Wrapper for Clothoids
 *
 * License MIT - See LICENSE file
 * 2022 Matteo Ragni
 */
#pragma once

#include "pybind11/pybind11.h"

namespace py = pybind11;

namespace G2lib {
namespace python {

  void wrap_interpolation(py::module & m);

}  
}