# Competitive Programming

This repository contains all my notes and snippets related to competitive programming.

- [Sparse Table](./CodeSnippets/SparseTable.cpp)
  - Allows to calculate range queries which are cumulative on immutable arrays in logarithmic time instead of linear.
  - Commonly used in finding Lowest Common Ancestor quries in a binary tree.
- [Binary Search](./CodeSnippets/BinarySearch.cpp)
  - In questions where we need to find number of pairs satisfying a particular condition, we can fix the left boundary `l` and do lowerBound and upperBound searches
    and add the pairs with `l` and points between `lowerBoundIndex` and `upperBoundIndex`.
- [Bit Manipulation](./CodeSnippets/BitManipulation.cpp)
  - Finding AND of window which can decrease / increase is possible in O(1).
