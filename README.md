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

- [Sparse Table](./CodeSnippets/SparseTable.cpp)
  - Allows to calculate range queries which are cumulative on immutable arrays in logarithmic time instead of linear.
  - Commonly used in finding Lowest Common Ancestor quries in a binary tree.
- [Binary Search](./CodeSnippets/BinarySearch.cpp)
  - In questions where we need to find number of pairs satisfying a particular condition, we can fix the left boundary `l` and do lowerBound and upperBound searches
    and add the pairs with `l` and points between `lowerBoundIndex` and `upperBoundIndex`.
- [Bit Manipulation](./CodeSnippets/BitManipulation.cpp)
  - Finding AND of window which can decrease / increase is possible in O(1).
- [Trees]
  - [Segment Tree 1](./CodeSnippets/SegmentTrees/SegmentTree.cpp)
    - Basic segment tree with range query and point update.
  - **Bit Trees**
    - These trees use bitwise operations to calculate indices and store things efficiently.
    - [Iterative Segment Tree](./CodeSnippets/SegmentTrees/IterativeSegmentTree.cpp)
      - Uses 2N memory
      - Actual array is stored from [n, 2n)
      - Each index i of tree stores value for i*2 and i*2 + 1
      - Hence point updations are easy to think about
      - Regarding range queries, see code for more explaination
        - Basically we normalise the ranges (+=n)
        - Then for every l, r, if they are odd, that means, it isn't covered in a whole range
          , hence we just thake it's value and move to a more complete range.
    - [Binary Indexed Tree](./CodeSnippets/SegmentTrees/FenwickTree.cpp)
      - Uses N memory
      - Each index stores the value of the range some [g(i), i]. For a zero indexed tree
        - g(i) is defined as removing the rightmost set bits starting from the right most index.
          If there are no set bits from the right, then do nothing.
        - Let's say i is of the form some binary number "X" + "0000" + "1" * y times
        - Then all the j's where g(j) <= i <= j, can only have the middle zeros sset to 1 from the
          right. Because suppose we have a j of the form "X" + "0100" + "1" * y times, then g(j)
          would be equal to "X" + "0100" + "0" * y times, which is greater than i! Hence not possible.
        - Bit manipulation wise, if we wish to achive the functionality of h(i) => next j and g(i),
          it can we done as `h(i) = i | (i + 1)`, and `g(i) = i & (i + 1)`.
        - Sum of prefix i can be calulated recursively adding `[g[i], i]` and doing `i = g(i) - 1`.
        - In point updations, we need to update all the `j > i` which has `i` between `[g[j], j]`.
      - For a 1 index based tree, we allocate tree size to be `n + 1` and transformations are:-
        - Here the ranges are half open to left => `(g[i], i]`
        - Hence the equalities in context are:
          - `g[i] < i`
          - `g[j] < i < j`
        - For g(i), we extract the last set bit.
        - For h(i), let's think of i as "X" + "001100"
          - If we set any bit to the right of last set bit, let's say j = "X" + "001110"
            then g(j) becomes "X" + "001100" which is not < i.
          - If we think of j = "X" + "001111", then g(j) becomes "X" + "001110" which is greater
            than i.
          - If we think of j = "X" + "011111", then g(j) becomes "X" + "011100" > i
        - Hence we can only set a bit to left of right most ones and remove all the rightmost ones
          i.e., j = "X" + "010000", then j > i and g(j) = "X" + "0" * 6 < i;
        - Moving onto the bit manipulations, last set bit is fetched through `i & (-i)`.
        - Hence `g[i] = i - (i & (-i))` and `h[i] = i + (i & (-i))`.
