#!/usr/bin/python -tt
# Copyright 2010 Google Inc.
# Licensed under the Apache License, Version 2.0
# http://www.apache.org/licenses/LICENSE-2.0

# Google's Python Class
# http://code.google.com/edu/languages/google-python-class/

"""Wordcount exercise
Google's Python class

The main() below is already defined and complete. It calls print_words()
and print_top() functions which you write.

1. For the --count flag, implement a print_words(filename) function that counts
how often each word appears in the text and prints:
word1 count1
word2 count2
...

Print the above list in order sorted by word (python will sort punctuation to
come before letters -- that's fine). Store all the words as lowercase,
so 'The' and 'the' count as the same word.

2. For the --topcount flag, implement a print_top(filename) which is similar
to print_words() but which prints just the top 20 most common words sorted
so the most common word is first, then the next most common, and so on.

Use str.split() (no arguments) to split on all whitespace.

Workflow: don't build the whole program at once. Get it to an intermediate
milestone and print your data structure and sys.exit(0).
When that's working, try for the next milestone.

Optional: define a helper function to avoid code duplication inside
print_words() and print_top().

"""
import argparse
from collections import Counter
import re
import sys
import tkinter as tk

# +++your code here+++
# Define print_words(filename) and print_top(filename) functions.
# You could write a helper utility function that reads a file
# and builds and returns a word/count dict for it.
# Then print_words() and print_top() can just call the utility function.

###

# This basic command line argument parsing code is provided and
# calls the print_words() and print_top() functions which you must define.


def __load_words(filename):
    words = re.findall(r"\w+", filename.read().lower())
    filename.close()
    return Counter(words)


def count_words(filename):
    dict_words = __load_words(filename)
    return sorted(dict_words.items())


def top_words(filename):
    dict_words = __load_words(filename)
    return dict_words.most_common(20)


def main():
    parser = argparse.ArgumentParser(description='Count words')
    parser.add_argument('--count', action='store_true', help='Count all words')
    parser.add_argument('--topcount', action='store_true', help='Count 20 most common')
    parser.add_argument('textfile', type=argparse.FileType(), help='Text file to count.')

    options = parser.parse_args()

    if options.count:
        for key, val in count_words(options.textfile):
            print('%s: %s' % (key, val))

    elif options.topcount:
        for key, val in top_words(options.textfile):
            print('%s: %s' % (key, val))

    else:
        print('unknown option: ' + options)
        sys.exit(1)

if __name__ == '__main__':
    main()
