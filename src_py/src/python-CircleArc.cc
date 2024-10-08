/**
 * PYTHON Wrapper for Clothoids
 * 
 * License MIT - See LICENSE file
 * 2019 Matteo Ragni, Claudio Kerov Ghiglianovich,
 *      Enrico Bertolazzi, Marco Frego
 */

#include "python-CircleArc.hh"
#include "pybind11/stl.h"

using namespace pybind11::literals;

namespace G2lib {
  namespace python {
    py::dict circlearc_to_dict(const CircleArc & self) {
      return py::dict(
        "x0"_a = self.x_begin(),
        "y0"_a = self.y_begin(),
        "theta0"_a = self.theta_begin(),
        "k"_a = self.kappa_begin(),
        "l"_a = self.length()
      );
    }

    CircleArc circlearc_from_dict(const py::dict & state) {
      const std::vector<std::string> keys({"x0", "y0", "theta0", "k", "l"});
      for (const auto & key: keys) {
        if (!state.contains(key)) { 
          char error[128];
          std::snprintf(error, 128, "Missing `%s` in state for CircleArc", key.c_str());
          throw std::runtime_error(error); 
        }

        if (state[py::cast(key)].is_none()) {
          char error[128];
          std::snprintf(error, 128, "Missing `%s` in state for CircleArc (is None)", key.c_str());
          throw std::runtime_error(error); 
        }
      }
      real_type x0 = py::cast<real_type>(state["x0"]);
      real_type y0 = py::cast<real_type>(state["y0"]);
      real_type theta0 = py::cast<real_type>(state["theta0"]);
      real_type k = py::cast<real_type>(state["k"]);
      int_type l = py::cast<real_type>(state["l"]);
      return CircleArc(x0, y0, theta0, k, l);
    }

    void wrap_CircleArc(py::module & m) {
      py::class_<CircleArc, BaseCurve>(m, "CircleArc",
      R"S(
        Class that menages a circle arc. There are several possible
        constructor for this class

         * constructor from a Base Curve
         * constructor from a Line Segment
         * constructor from a Circle Arc
         * constructor from raw data

        for this last constructor:

        :param float x0: starting position **x** coordinate
        :param float y0: starting position **y** coordinate
        :param float theta0: initial angle
        :param k: curvature
        :param l: length
      )S")

      .def(py::init<>())
      .def(py::init<BaseCurve const &>(), py::arg("c"))
      .def(py::init<LineSegment const &>(), py::arg("c"))
      .def(py::init<CircleArc const &>(), py::arg("c"))
      .def(py::init<real_type, real_type, real_type, real_type, real_type>(),
        py::arg("x0"), py::arg("y0"), py::arg("theta0"), py::arg("k"), py::arg("l"))
      
      .def(py::pickle(&circlearc_to_dict, &circlearc_from_dict))

      .def("to_dict", &circlearc_to_dict)

      .def_static("from_dict", &circlearc_from_dict)

      .def("copy", [](const CircleArc & self) {
        CircleArc other;
        other.copy(self);
        return other;
      },
      R"S(
        Create a copy of the current circle arc curve

        :return: a new copy of the current circle arc
        :rtype: CircleArc
      )S")

      .def("build", &CircleArc::build, 
        py::arg("x0"), py::arg("y0"), py::arg("theta0"), py::arg("k"), py::arg("l"),
      R"S(
        Builds a circle arc with the standard parameters

        :param float x0: starting position **x** coordinate
        :param float y0: starting position **y** coordinate
        :param float theta0: initial angle
        :param float k: curvature
        :param float l: length
        :return: nothing, works in place
        :rtype: NoneType
      )S")

      .def("build_G1", &CircleArc::build_G1, 
        py::arg("x0"), py::arg("y0"), py::arg("theta0"), py::arg("x1"), py::arg("y1"),
      R"S(
        Builds a circle arc with the standard parameters

        :param float x0: starting position **x** coordinate
        :param float y0: starting position **y** coordinate
        :param float theta0: initial angle
        :param float x1: final position **x** coordinate
        :param float l: final position **y** coordinate
        :return: true if build succeeds
        :rtype: bool
      )S")

      .def("build_3P", &CircleArc::build_3P,
        py::arg("x0"), py::arg("y0"), py::arg("x1"), py::arg("y1"), py::arg("x2"), py::arg("y2"),
      R"S(
        Builds a circle arc with the standard parameters

        :param float x0: first point **x** coordinate
        :param float y0: first point **y** coordinate
        :param float x1: second point **x** coordinate
        :param float y1: second point **y** coordinate
        :param float x2: third point **x** coordinate
        :param float y2: third point **y** coordinate
        :return: true if build succeeds
        :rtype: bool
      )S")

      .def("sinTheta0", &CircleArc::sinTheta0,
      R"S(
        Returns the :math:`\sin(\theta_0)` (sine of initial angle)

        :return: sine of initial angle
        :rtype: float
      )S")

      .def("cosTheta0", &CircleArc::cosTheta0,
      R"S(
        Returns the :math:`\cos(\theta_0)` (cosine of initial angle)

        :return: cosine of initial angle
        :rtype: float
      )S")

      .def("curvature", &CircleArc::curvature,
      R"S(
        Curvature of the circle arc

        :return: curvature of the circle arc
        :rtype: float
      )S")

      .def("lenTolerance", &CircleArc::lenTolerance, py::arg("tol"),
      R"S(
        Return the arc length to evaluate length with the requested
        tolerance

        :param float tol: tolerance
        :return: arc length
        :rtype: float
      )S")

      .def("delta_theta", &CircleArc::delta_theta, 
      R"S(
        Return the tangent angle variation in the circle arc

        :return: tangent angle variation
        :rtype: float
      )S")

      .def("thetaTotalVariation", &CircleArc::theta_total_variation,
      R"S(
        Return the absolute value of the tangent angle variation in the circle arc.

        :return: absolute value of the tangent angle variation
        :rtype: float
      )S")

      .def("thetaMinMax", [](const CircleArc & self) {
        real_type th_min, th_max;
        self.theta_min_max(th_min, th_max);
        return std::make_tuple(th_min, th_max);
      }, 
      R"S(
        Minimum and maximum tangent angle

        :return: the minimum and maximum tangent angle
        :rtype: Tuple[float, float]
      )S")
      
      .def("change_curvilinear_origin", &CircleArc::change_curvilinear_origin,
        py::arg("s0"), py::arg("newL"),
      R"S(
        Change the origin of the curvilinear abscissa of the circle arc
        and the length of the arc

        :param float s0: new curvilinear abscissa origin
        :param float newL: new length of the curve
        :return: nothing, works in place
        :rtype: NoneType
      )S")

      .def("changeCurvilinearOrigin", &CircleArc::change_curvilinear_origin,
        py::arg("s0"), py::arg("newL"),
      R"S(
        Change the origin of the curvilinear abscissa of the circle arc
        and the length of the arc

        .. warning:: Deprecated for ``change_curvilinear_origin``

        :param float s0: new curvilinear abscissa origin
        :param float newL: new length of the curve
        :return: nothing, works in place
        :rtype: NoneType
      )S")

      .def("center", [](const CircleArc & self) {
        real_type x, y;
        self.center(x, y);
        return std::make_tuple(x, y);
      },
      R"S(
        Get the center of the arc

        :return: center of the arc
        :rtype: Tuple[float, float]
      )S")

      .def("radius", &CircleArc::ray,
      R"S(
        Returns the radius of the circle arc

        :return: radius of the circle
        :rtype: float
      )S")

#ifndef __APPLE__
      .def("toNURBS", [](const CircleArc & self){
        using Point = real_type[3];
        using TPoint = std::tuple<float, float, float>;

        int_type n_pnts, n_knots;
        self.paramNURBS(n_knots, n_pnts);
        
        std::vector<real_type> knots(n_knots);
        std::vector<Point> poly(n_pnts);
        std::vector<TPoint> tpoly;
        tpoly.reserve(n_pnts);

        self.toNURBS(knots.data(), poly.data());
        std::for_each(poly.cbegin(), poly.cend(), [&](const Point & p) {
          tpoly.push_back(std::make_tuple(p[0], p[1], p[2]));
        });
        
        return std::make_tuple(knots, tpoly);
      },
      R"S(
        Returns the nurbs parameters of the circle arc, as a tuple with
        knots and point list (as a tuple of 3 value)

        :return: nurbs parameters
        :rtype: Tuple[List[float], List[Tuple[float, float, float]]]
      )S")
#endif

      .def("paramNURBS", [](const CircleArc & self) {
        int_type n_pnts, n_knots;
        self.paramNURBS(n_knots, n_pnts);
        return std::make_tuple(n_knots, n_pnts);
      },
      R"S(
        Return the number of knots and points for the nurbs of the circle

        :return: knots count and point count
        :rtype: Tuple[int, int]
      )S");
    }
  }
}