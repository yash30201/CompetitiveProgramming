# Competitive Programming

This repository contains all my notes and snippets related to competitive programming.

## [Sparse Table](./CodeSnippets/SparseTable.cpp)

- Allows to calculate range queries which are cumulative on immutable arrays in logarithmic time instead of linear.
- Commonly used in finding Lowest Common Ancestor quries in a binary tree.

## [Binary Search](./CodeSnippets/BinarySearch.cpp)

- In questions where we need to find number of pairs satisfying a particular
  condition, we can fix the left boundary `l` and do lowerBound and upperBound searches
  and add the pairs with `l` and points between `lowerBoundIndex` and `upperBoundIndex`.

## [Bit Manipulation](./CodeSnippets/BitManipulation.cpp)

- Finding AND of window which can decrease / increase is possible in O(1).

## Trees

### [Segment Tree](./CodeSnippets/SegmentTrees/SegmentTree.cpp)

Basic segment tree with range query and point update.

### Bit Trees

These trees use bitwise operations to calculate indices and store things efficiently.

#### [Iterative Segment Tree](./CodeSnippets/SegmentTrees/IterativeSegmentTree.cpp)

- Uses 2N memory
- Actual array is stored from [n, 2n)
- Each index i of tree stores value for i*2 and i*2 + 1
- Hence point updations are easy to think about
- Regarding range queries, see code for more explaination
  - Basically we normalise the ranges (+=n)
  - Then for every l, r, if they are odd, that means, it isn't covered in a whole range
    , hence we just thake it's value and move to a more complete range.

#### [Binary Indexed Tree](./CodeSnippets/SegmentTrees/FenwichTree.cpp)

- Uses N memory
- Each index stores the value of the range some [g(i), i]
  - g(i) is defined as i & (i + 1) =>
    - If i is even, then == i
    - Else remove all set rightmost ones
  - Hence, now we can calculate any range sum [l, r] as sum(r) - sum(l - 1);
  - Point updations means, we recursively update
    - For i, add the update value, then go to next index which also has contribution from value i
      i = i | (i + 1);
  