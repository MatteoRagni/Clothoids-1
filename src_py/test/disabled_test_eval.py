# PYTHON Wrapper for Clothoids
# 
# License MIT - See LICENSE file
# 
# 2019 Matteo Ragni, Claudio Kerov Ghiglianovich,
#      Enrico Bertolazzi, Marco Frego

import sys
import os

sys.path.insert(0, os.path.normpath(os.path.join(__file__, "../../distrib/G2lib")))

import unittest
import G2lib

class TestEval(unittest.TestCase):

    def test_eval(self):
        xs = [0, 1, 2, 3, 4, 5, 6]
        ys = [0, 0, 0, 0, 0, 0, 0]
        lines = G2lib.PolyLine(xs, ys)
         
        for s, v, z in zip(xs, xs, ys):
            x, y = lines.eval(s)
            self.assertEqual(x, v)
            self.assertEqual(y, z)

    def test_polyline(self):
        xs = [0, 1, 2, 3, 4, 5, 6]
        ys = [0, 0, 0, 0, 0, 0, 0]
        xz = [1, 2, 3, 4, 5, 6, 7]
        yz = [0, 0, 0, 0, 0, 0, 0]
        # polyline = G2lib.PolyLine()
        # for x, y, v, w in zip(xs, ys, xz, yz):
        #     line = G2lib.LineSegment()
        #     line.build_2P(x, y, v, w)
        #     polyline.push_back(line)