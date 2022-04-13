#!/usr/bin/env python3
# Copyright (c) 2022 Matteo Ragni
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

import sys
from os import path

__g2lib_bin_path__ = path.normpath(path.abspath(path.dirname(__file__)))
sys.path.insert(0, __g2lib_bin_path__)

from _G2lib import *

try:
    from _G2lib_Interpolation import *
except ImportError:
    def buildP1(*args, **kwargs): 
        raise RuntimeError("Interpolation library cannot be loaded: " 
                           "builder functions not available")
    
    def buildP2(*args, **kwargs): 
        raise RuntimeError("Interpolation library cannot be loaded: " 
                           "builder functions not available")
    
    def buildP4(*args, **kwargs): 
        raise RuntimeError("Interpolation library cannot be loaded: " 
                           "builder functions not available")
    
    def buildP5(*args, **kwargs): 
        raise RuntimeError("Interpolation library cannot be loaded: " 
                           "builder functions not available")
    
    def buildP6(*args, **kwargs): 
        raise RuntimeError("Interpolation library cannot be loaded: " 
                           "builder functions not available")
    
    def buildP7(*args, **kwargs): 
        raise RuntimeError("Interpolation library cannot be loaded: " 
                           "builder functions not available")
    
    def buildP8(*args, **kwargs): 
        raise RuntimeError("Interpolation library cannot be loaded: " 
                           "builder functions not available")
    
    def buildP9(*args, **kwargs): 
        raise RuntimeError("Interpolation library cannot be loaded: " 
                           "builder functions not available")
    
