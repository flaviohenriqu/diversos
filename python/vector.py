from math import hypot


class Vector:

    def __init__(self, *args):
        self.x, self.y = args

    def __repr__(self):
        # return ''.join([self.__class__.__name__, '(', str(self.x), ', ', str(self.y), ')'])
        return '%s(%d, %d)' % (self.__class__.__name__, self.x, self.y)

    def __str__(self):
        # return ''.join(['(', str(self.x), ', ', str(self.y), ')'])
        return '(%d, %d)' % (self.x, self.y)

    def __eq__(self, other):
        return self.x == other.x and self.y == other.y

    def __add__(self, other):
        return Vector(self.x + other.x, self.y + other.y)

    def __mul__(self, other):
        return Vector(self.x * other, self.y * other)

    __rmul__ = __mul__

    def __abs__(self):
        return hypot(self.x, self.y)

    def __nonzero__(self):
        return self.x or self.y

    def dot(self, other):
        return (self.x * other.x) + (self.y * other.y)

def main():
    assert Vector(2, 4)
    assert (Vector(2, 4).x, Vector(2, 4).y) == (2, 4)
    assert repr(Vector(2, 4)) == 'Vector(2, 4)'
    assert str(Vector(2, 4)) == '(2, 4)'
    assert Vector(2, 4) == Vector(2, 4)
    assert Vector(2, 4) + Vector(1, 2) == Vector(3, 6)
    assert Vector(2, 4) * 2 == Vector(4, 8)
    assert 2 * Vector(2, 4) == Vector(4, 8)
    assert abs(Vector(3, 4)) == 5.0
    assert bool(Vector(0, 0)) == False
    assert bool(Vector(0, 1)) == bool(Vector(1, 0)) == bool(Vector(1, 1))
    assert Vector(2, 2).dot(Vector(3, 4)) == 14


if __name__ == '__main__':
    main()