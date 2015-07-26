#!/usr/bin/python
"""
Challenge SkyHub  --  Hell Triangle
@author: Flavio Santos
@date: 07/24/2015

Requirements:
    Python 2.7

Run Tests:
    python hell_triangle.py

Expected results:

test001 (__main__.TestHellTriangle)
Test 001 | Assert True Sum Max equals 26 ... __main__.TestHellTriangle.test001: 0.000027
ok
test002 (__main__.TestHellTriangle)
Test 002 | Assert True Sum Max equals 321 ... __main__.TestHellTriangle.test002: 0.000018
ok
test003 (__main__.TestHellTriangle)
Test 003 | Assert True Sum Max equals 1320 ... __main__.TestHellTriangle.test003: 0.000127
ok
test004 (__main__.TestHellTriangle)
Test 004 | Assert True Sum Max equals 23 ... __main__.TestHellTriangle.test004: 0.000016
ok
test005 (__main__.TestHellTriangle)
Test 005 | Assert Equal Max 35 ... __main__.TestHellTriangle.test005: 0.000020
ok
test006 (__main__.TestHellTriangle)
Test 006 | Sum Max 1074 ... __main__.TestHellTriangle.test006: 0.000098
ok

----------------------------------------------------------------------
Ran 6 tests in 0.001s

OK

"""
import time
import unittest


def solution(tri):
    while len(tri) > 1:
        t0 = tri.pop()
        t1 = tri.pop()
        tri.append([max(t0[i], t0[i+1]) + t for i, t in enumerate(t1)])
    return tri[0][0]


class TestHellTriangle(unittest.TestCase):
    """
        Class Test Case
    """
    def setUp(self):
        self.startTime = time.time()

    def tearDown(self):
        t = time.time() - self.startTime
        print "%s: %.6f" % (self.id(), t)

    def test001(self):
        """ Test 001 | Assert True Sum Max equals 26 """
        data = [[6],
                [3, 5],
                [9, 7, 1],
                [4, 6, 8, 4]]

        result = solution([map(int, row) for row in data])

        self.assertEqual(result, 26)

    def test002(self):
        """ Test 002 | Assert True Sum Max equals 321 """
        data = [[55],
                [94, 48],
                [95, 30, 96],
                [77, 71, 26, 67]]

        result = solution([map(int, row) for row in data])

        self.assertEqual(result, 321)

    def test003(self):
        """ Test 003 | Assert True Sum Max equals 1320 """
        data = [[55],
                [94, 48],
                [95, 30, 96],
                [77, 71, 26, 67],
                [97, 13, 76, 38, 45],
                [07, 36, 79, 16, 37, 68],
                [48, 07, 9, 18, 70, 26, 06],
                [18, 72, 79, 46, 59, 79, 29, 90],
                [20, 76, 87, 11, 32, 07, 07, 49, 18],
                [27, 83, 58, 35, 71, 11, 25, 57, 29, 85],
                [14, 64, 36, 96, 27, 11, 58, 56, 92, 18, 55],
                [02, 90, 03, 60, 48, 49, 41, 46, 33, 36, 47, 23],
                [92, 50, 48, 02, 36, 59, 42, 79, 72, 20, 82, 77, 42],
                [56, 78, 38, 80, 39, 75, 02, 71, 66, 66, 01, 03, 55, 72],
                [44, 25, 67, 84, 71, 67, 11, 61, 40, 57, 58, 89, 40, 56, 36],
                [85, 32, 25, 85, 57, 48, 84, 35, 47, 62, 17, 01, 01, 99, 89, 52],
                [06, 71, 28, 75, 94, 48, 37, 10, 23, 51, 06, 48, 53, 18, 74, 98, 15],
                [27, 02, 92, 23, 8, 71, 76, 84, 15, 52, 92, 63, 81, 10, 44, 10, 69, 93]]

        result = solution([map(int, row) for row in data])

        self.assertEqual(result, 1320)

    def test004(self):
        """ Test 004 | Assert True Sum Max equals 23 """
        data = [[3],
                [7, 4],
                [2, 4, 6],
                [8, 5, 9, 3]]

        result = solution([map(int, row) for row in data])

        self.assertEqual(result, 23)

    def test005(self):
        """ Test 005 | Assert Equal Max 35"""
        data = [[3],
                [7, 4],
                [2, 4, 6],
                [8, 5, 9, 3],
                [15, 10, 2, 7, 8]]

        result = solution([map(int, row) for row in data])

        self.assertEqual(result, 35)

    def test006(self):
        """ Test 006 | Sum Max 1074"""
        data = [[75],
                [95, 64],
                [17, 47, 82],
                [18, 35, 87, 10],
                [20, 04, 82, 47, 65],
                [19, 01, 23, 75, 03, 34],
                [88, 02, 77, 73, 07, 63, 67],
                [99, 65, 04, 28, 06, 16, 70, 92],
                [41, 41, 26, 56, 83, 40, 80, 70, 33],
                [41, 48, 72, 33, 47, 32, 37, 16, 94, 29],
                [53, 71, 44, 65, 25, 43, 91, 52, 97, 51, 14],
                [70, 11, 33, 28, 77, 73, 17, 78, 39, 68, 17, 57],
                [91, 71, 52, 38, 17, 14, 91, 43, 58, 50, 27, 29, 48],
                [63, 66, 04, 68, 89, 53, 67, 30, 73, 16, 69, 87, 40, 31],
                [04, 62, 98, 27, 23, 9, 70, 98, 73, 93, 38, 53, 60, 04, 23]]

        result = solution([map(int, row) for row in data])

        self.assertEqual(result, 1074)

if __name__ == '__main__':
    suite = unittest.TestLoader().loadTestsFromTestCase(TestHellTriangle)
    unittest.TextTestRunner(verbosity=2).run(suite)
