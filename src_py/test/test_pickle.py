# PYTHON Wrapper for Clothoids
#
# License MIT - See LICENSE file
#
# 2022 Matteo Ragni

import math
import pickle
import unittest
import sys
import os
# fmt: off
sys.path.insert(0, os.path.normpath(
    os.path.join(__file__, "../../distrib/G2lib")))
import G2lib
#fmt: on


def pickle_and_compare(origin, method_list):
    data = pickle.dumps(origin)
    destination = pickle.loads(data)

    assert type(origin) == type(destination)
    for method in method_list:
        origin_result = getattr(origin, method)()
        destination_result = getattr(destination, method)()
        if isinstance(origin_result, float):
            assert (
                origin_result - destination_result)**2 <= 1e-24, f"Different result for {method} on type {type(origin).__name__}: {origin_result} != {destination_result}\nORIGIN::\n{origin}\nDESTINATION::\n{destination}"
        else:
            assert origin_result == destination_result, f"Different result for {method} on type {type(origin).__name__}: {origin_result} != {destination_result}\nORIGIN::\n{origin}\nDESTINATION::\n{destination}"


def test_bbox_pickle():
    method_list = ["Xmin", "Ymin", "Xmax", "Ymax", "Id", "Ipos"]
    origin = G2lib.BBox(((0, 0), (1, 1)), 1, 2)
    pickle_and_compare(origin, method_list)


def test_biarc_pickle():
    method_list = ["x_begin", "x_end", "y_begin",
                   "y_end", "theta_begin", "theta_end"]
    origin = G2lib.Biarc(0, 0, 10, 0, math.pi/2, math.pi/2)
    pickle_and_compare(origin, method_list)


def test_biarclist_pickle():
    method_list = ["length", "x_begin", "x_end",
                   "y_begin", "y_end", "theta_begin", "theta_end"]
    origin = G2lib.BiarcList(G2lib.Biarc(0, 0, math.pi/2, 1, 1, math.pi/2))
    origin.push_back_G1(1, 1, math.pi/2, 2, 2, math.pi/2)
    origin.push_back_G1(2, 2, math.pi/2, 3, 3, math.pi/2)
    pickle_and_compare(origin, method_list)


def test_circlearc_pickle():
    method_list = ["length", "x_begin", "x_end",
                   "y_begin", "y_end", "theta_begin", "theta_end"]
    origin = G2lib.CircleArc(1, 2, math.pi, 0.1, 3)
    pickle_and_compare(origin, method_list)


def test_clothoidcurve_pickle():
    method_list = ["length", "x_begin", "x_end",
                   "y_begin", "y_end", "theta_begin", "theta_end"]
    origin = G2lib.ClothoidCurve(1, 2, math.pi, 0.1, 0.01, 3)
    pickle_and_compare(origin, method_list)


def test_clothoidlist_pickle():
    method_list = ["length", "x_begin", "x_end",
                   "y_begin", "y_end", "theta_begin", "theta_end"]
    stats, origin = G2lib.buildP2([0, 1, 2, 3, 4], [1, -1, 1, -1, 1])
    assert stats.ok()
    pickle_and_compare(origin, method_list)


def test_linesegment_pickle():
    method_list = ["length", "x_begin", "x_end",
                   "y_begin", "y_end", "theta_begin", "theta_end"]
    origin = G2lib.LineSegment(1, 2, math.pi/4, 20)
    pickle_and_compare(origin, method_list)


def test_polyline_pickle():
    method_list = ["length", "x_begin", "x_end",
                   "y_begin", "y_end", "theta_begin", "theta_end"]
    origin = G2lib.PolyLine()
    origin.build([0, 1, 2, 3, 4], [1, -1, 1, -1, 1])
    pickle_and_compare(origin, method_list)
