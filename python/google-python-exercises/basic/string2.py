#!/usr/bin/python2.4 -tt
# Copyright 2010 Google Inc.
# Licensed under the Apache License, Version 2.0
# http://www.apache.org/licenses/LICENSE-2.0

# Google's Python Class
# http://code.google.com/edu/languages/google-python-class/

# Additional basic string exercises

# D. verbing
# Given a string, if its length is at least 3,
# add 'ing' to its end.
# Unless it already ends in 'ing', in which case
# add 'ly' instead.
# If the string length is less than 3, leave it unchanged.
# Return the resulting string.
from math import ceil

def verbing(s):
    suffix = 'ing'
    if len(s) < 3:
        suffix = ''
    elif s.endswith('ing'):
        suffix = 'ly'

    return '%s%s' % (s, suffix)


# E. not_bad
# Given a string, find the first appearance of the
# substring 'not' and 'bad'. If the 'bad' follows
# the 'not', replace the whole 'not'...'bad' substring
# with 'good'.
# Return the resulting string.
# So 'This dinner is not that bad!' yields:
# This dinner is good!
def not_bad(s):
    msg = s
    if 'not' in s and 'bad' in s:
        idx_not = s.index('not')
        idx_bad = s.index('bad')
        if idx_not < idx_bad:
            msg = s.replace(s[idx_not: idx_bad+3], 'good')

    return msg


# F. front_back
# Consider dividing a string into two halves.
# If the length is even, the front and back halves are the same length.
# If the length is odd, we'll say that the extra char goes in the front half.
# e.g. 'abcde', the front half is 'abc', the back half 'de'.
# Given 2 strings, a and b, return a string of the form
#  a-front + b-front + a-back + b-back
def front_back(a, b):
    half_a = int(ceil(len(a)/2.))
    half_b = int(ceil(len(b)/2.))
    return '%s%s%s%s' % (a[:half_a], b[:half_b], a[half_a:], b[half_b:])


def front_back(a, b):
    half_a = len(a)/2 + len(a) % 2
    half_b = len(b)/2 + len(b) % 2
    return '%s%s%s%s' % (a[:half_a], b[:half_b], a[half_a:], b[half_b:])


def front_back(a, b):
    mid = lambda s: int(ceil(len(s)/2.))
    front = lambda s: s[:mid(s)]
    back = lambda s: s[mid(s):]

    return ''.join([front(a), front(b), back(a), back(b)])

# Simple provided test() function used in main() to print
# what each function returns vs. what it's supposed to return.


def test(got, expected):
    if got == expected:
        prefix = ' OK '
    else:
        prefix = '  X '
    print '%s got: %s expected: %s' % (prefix, repr(got), repr(expected))


# main() calls the above functions with interesting inputs,
# using the above test() to check if the result is correct or not.
def main():
    print 'verbing'
    test(verbing('hail'), 'hailing')
    test(verbing('swiming'), 'swimingly')
    test(verbing('do'), 'do')

    print
    print 'not_bad'
    test(not_bad('This movie is not so bad'), 'This movie is good')
    test(not_bad('This dinner is not that bad!'), 'This dinner is good!')
    test(not_bad('This tea is not hot'), 'This tea is not hot')
    test(not_bad("It's bad yet not"), "It's bad yet not")
    test(not_bad("It's bad yet"), "It's bad yet")

    print
    print 'front_back'
    test(front_back('abcd', 'xy'), 'abxcdy')
    test(front_back('abcde', 'xyz'), 'abcxydez')
    test(front_back('Kitten', 'Donut'), 'KitDontenut')

if __name__ == '__main__':
    main()
