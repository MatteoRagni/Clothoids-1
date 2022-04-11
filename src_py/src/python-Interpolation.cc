/**
 * PYTHON Wrapper for Clothoids
 *
 * License MIT - See LICENSE file
 * 2022 Matteo Ragni
 */

#include "python-Clothoid.hh"
#include "python-Interpolation.hh"
#include "pybind11/stl.h"
#include <stdexcept>

#ifdef _WIN32
#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif
#endif

namespace G2lib {
  namespace python {

    void wrap_interpolation(py::module & m) {
      py::enum_<G2lib::Interpolation::ResultType>(m, "InterpolatorResultType")
          .value("Success", G2lib::Interpolation::ResultType::Success)
          .value("NumericalIssue", G2lib::Interpolation::ResultType::NumericalIssue)
          .value("NoConvergence", G2lib::Interpolation::ResultType::NoConvergence)
          .value("InvalidInput", G2lib::Interpolation::ResultType::InvalidInput)
          .value("InternalError", G2lib::Interpolation::ResultType::InternalError);

      py::class_<G2lib::Interpolation::Result>(m, "InterpolatorResult")
          .def("ok", &G2lib::Interpolation::Result::ok)
          .def("status", &G2lib::Interpolation::Result::status)
          .def("objective_value", &G2lib::Interpolation::Result::objective_value)
          .def("iters", &G2lib::Interpolation::Result::iters);

      m.def(
           "buildP1",
           [](const std::vector<real_type> & xs, const std::vector<real_type> & ys, real_type theta_0,
              real_type theta_1) {
             G2lib::ClothoidList                result;
             G2lib::Interpolation::Interpolator interpolator(xs, ys);
             const auto                         status = interpolator.buildP1(theta_0, theta_1, result);
             return std::make_tuple(status, result);
           },
           py::arg("xs"), py::arg("ys"), py::arg("theta0"), py::arg("theta1"),
           R"S(
        Builds a clothoid list starting from a list of points. Build a 
        clothoids between each point pair.

        Uses target P1. Requires Eigen library during compilation

        :param List[float] xs: **x** coordinates of points
        :param List[float] ys: **y** coordinates of points
        :param float theta0: intial angle
        :param float theta1: final angle 
        :return: a tuple containing the result of the interpolation and the clothoid list
        :rtype: Tuple[InterpolatorResult, ClothodList] 
      )S")
          .def(
              "buildP2",
              [](const std::vector<real_type> & xs, const std::vector<real_type> & ys) {
                G2lib::ClothoidList                result;
                G2lib::Interpolation::Interpolator interpolator(xs, ys);
                const auto                         status = interpolator.buildP2(result);
                return std::make_tuple(status, result);
              },
              py::arg("xs"), py::arg("ys"),
              R"S(
        Builds a clothoid list starting from a list of points. Build a 
        clothoids between each point pair.

        Uses target P2. Requires Eigen library during compilation

        :param List[float] xs: **x** coordinates of points
        :param List[float] ys: **y** coordinates of points
        :return: a tuple containing the result of the interpolation and the clothoid list
        :rtype: Tuple[InterpolatorResult, ClothodList] 
      )S")
          .def(
              "buildP4",
              [](const std::vector<real_type> & xs, const std::vector<real_type> & ys) {
                G2lib::ClothoidList                result;
                G2lib::Interpolation::Interpolator interpolator(xs, ys);
                const auto                         status = interpolator.buildP4(result);
                return std::make_tuple(status, result);
              },
              py::arg("xs"), py::arg("ys"),
              R"S(
        Builds a clothoid list starting from a list of points. Build a 
        clothoids between each point pair.

        Uses target P4. Requires IPOPT library during compilation

        :param List[float] xs: **x** coordinates of points
        :param List[float] ys: **y** coordinates of points
        :return: a tuple containing the result of the interpolation and the clothoid list
        :rtype: Tuple[InterpolatorResult, ClothodList] 
      )S")
          .def(
              "buildP5",
              [](const std::vector<real_type> & xs, const std::vector<real_type> & ys) {
                G2lib::ClothoidList                result;
                G2lib::Interpolation::Interpolator interpolator(xs, ys);
                const auto                         status = interpolator.buildP5(result);
                return std::make_tuple(status, result);
              },
              py::arg("xs"), py::arg("ys"),
              R"S(
        Builds a clothoid list starting from a list of points. Build a 
        clothoids between each point pair.

        Uses target P5. Requires IPOPT library during compilation

        :param List[float] xs: **x** coordinates of points
        :param List[float] ys: **y** coordinates of points
        :return: a tuple containing the result of the interpolation and the clothoid list
        :rtype: Tuple[InterpolatorResult, ClothodList] 
      )S")
          .def(
              "buildP6",
              [](const std::vector<real_type> & xs, const std::vector<real_type> & ys) {
                G2lib::ClothoidList                result;
                G2lib::Interpolation::Interpolator interpolator(xs, ys);
                const auto                         status = interpolator.buildP6(result);
                return std::make_tuple(status, result);
              },
              py::arg("xs"), py::arg("ys"),
              R"S(
        Builds a clothoid list starting from a list of points. Build a 
        clothoids between each point pair.

        Uses target P6. Requires IPOPT library during compilation

        :param List[float] xs: **x** coordinates of points
        :param List[float] ys: **y** coordinates of points
        :return: a tuple containing the result of the interpolation and the clothoid list
        :rtype: Tuple[InterpolatorResult, ClothodList] 
      )S")
          .def(
              "buildP7",
              [](const std::vector<real_type> & xs, const std::vector<real_type> & ys) {
                G2lib::ClothoidList                result;
                G2lib::Interpolation::Interpolator interpolator(xs, ys);
                const auto                         status = interpolator.buildP7(result);
                return std::make_tuple(status, result);
              },
              py::arg("xs"), py::arg("ys"),
              R"S(
        Builds a clothoid list starting from a list of points. Build a 
        clothoids between each point pair.

        Uses target P7. Requires IPOPT library during compilation

        :param List[float] xs: **x** coordinates of points
        :param List[float] ys: **y** coordinates of points
        :return: a tuple containing the result of the interpolation and the clothoid list
        :rtype: Tuple[InterpolatorResult, ClothodList] 
      )S")
          .def(
              "buildP8",
              [](const std::vector<real_type> & xs, const std::vector<real_type> & ys) {
                G2lib::ClothoidList                result;
                G2lib::Interpolation::Interpolator interpolator(xs, ys);
                const auto                         status = interpolator.buildP8(result);
                return std::make_tuple(status, result);
              },
              py::arg("xs"), py::arg("ys"),
              R"S(
        Builds a clothoid list starting from a list of points. Build a 
        clothoids between each point pair.

        Uses target P8. Requires IPOPT library during compilation

        :param List[float] xs: **x** coordinates of points
        :param List[float] ys: **y** coordinates of points
        :return: a tuple containing the result of the interpolation and the clothoid list
        :rtype: Tuple[InterpolatorResult, ClothodList] 
      )S")
          .def(
              "buildP9",
              [](const std::vector<real_type> & xs, const std::vector<real_type> & ys) {
                G2lib::ClothoidList                result;
                G2lib::Interpolation::Interpolator interpolator(xs, ys);
                const auto                         status = interpolator.buildP9(result);
                return std::make_tuple(status, result);
              },
              py::arg("xs"), py::arg("ys"),
              R"S(
        Builds a clothoid list starting from a list of points. Build a 
        clothoids between each point pair.

        Uses target P9. Requires IPOPT library during compilation

        :param List[float] xs: **x** coordinates of points
        :param List[float] ys: **y** coordinates of points
        :return: a tuple containing the result of the interpolation and the clothoid list
        :rtype: Tuple[InterpolatorResult, ClothodList] 
      )S");
    }

  }  // namespace python
}  // namespace G2lib