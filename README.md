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

### [Segment Tree](./CodeSnippets/Trees/SegmentTree.cpp)

Basic segment tree with range query and point update.

- Segment Trees can be used in descending the tree mode!
  - See [code](./CodeForces/1520.cpp)
  - Another example would be to get the index whose predix sum is greater than equal to k
    - Obviously the array can have updations otherwise we can just create a prefix array with
      binary search.
- Ranged Maximum subarray sum queries [code](./SPOJ/GSS3.cpp)
- **We can store the whole subtree in nodes**
  - This will result in a memory of **O(NlogN), not O(N^2)**
  - We can store the node data in special data structures like multiset to achive more functionality.
    - This is called **merge sort tree**.
  - Example Q: Find the smallest number greater or equal to a specified number with modification queries

### [Segment Tree](./CodeSnippets/Trees/SegmentTreeLazyPush.cpp): Lazy Propagation

This segment tree allows range updates and range queries both in log(n) time. You probably need
to **use lazy propagation whenever you require range updates**!

The crux behind the DS is in the following two points:

- If in a particular range update query, we are at a range `[l, r)` which is completely
  inside the update query range, then we will just update the lazy array index for this
  range and return.
- Now whenever you are descending into the tree, for each node in your path, just **push** the current
  lazy operation present in the lazy array down for both of it's children. This would be a `O(1)`
  operation assuming applying changes take `O(1)`.
- Example usage: [code](./CodeForces/1114F.cpp)

### Persistent Segment Trees

Firstly, think of a normal segment tree implementation with nodes as pointer to some node structure.
Now, in this tree, whenever we update some node, instead of updating the node, we create a new node with
the updated value and pass it on above. The above node again creates a new version of current node
and passes and it goes on. At the end, you get a new node for every update. Atmax there can be `O(height) == O(logN)`
new node creations per update query.

- => Still all operation works in `O(logN)`
- => You can store each new root node to get the updated version of the tree.
- => For any range query [l, r], let's we are in some point at the query step and say we want to calculate
  do some calulation based on the current node's value, then to get that, we can effectively do
  latest_version->value - previous_version->value.
  - This approach is useful in calculating numbers greater than k in [l, r] range.
  - Example [code](./SPOJ/KQUERY.cpp)
- Similary, a Persistent Segment Tree for range sum and range update (by some constant value) operations
  is implemented [here](./CodeSnippets/Trees/PersistentSegmentTree.cpp).

### Bit Trees

These trees use bitwise operations to calculate indices and store things efficiently.

#### [Iterative Segment Tree](./CodeSnippets/Trees/IterativeSegmentTree.cpp)

- Uses 2N memory
- Actual array is stored from [n, 2n)
- Each index i of tree stores value for i*2 and i*2 + 1
- Hence point updations are easy to think about
- Regarding range queries, see code for more explaination
  - Basically we normalise the ranges (+=n)
  - Then for every l, r, if they are odd, that means, it isn't covered in a whole range
    , hence we just thake it's value and move to a more complete range.

#### [Binary Indexed Tree](./CodeSnippets/Trees/FenwickTree.cpp)

- Uses N memory
- Used to store modifications, it's best get the result value by summing array value and
  modification value.
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

#### [Binary Indexed Tree](./CodeSnippets/Trees/FenwickRangeUpdatePointQuery.cpp) Range Update Point Query

- We can do this via hacks
- For update to range [l, r] by x each, we do `add(l, x)` and `add(r + 1, -x)`
- For getting the point value of a[i], the answer would be `prefix_sum(i)`

#### [Binary Indexed Tree](./CodeSnippets/Trees/FenwickTreeRangeUpdateRangeQuery.cpp): Range Update Range Query

- Let's think about the scenario, where we update a range `[l, r]` by x, then sum of a
  prefix i can be described as follows: <br/>
 ![alt text](Assets/image.png)
- We can write the sum as follows then: <br/>
 ![alt text](Assets/image1.png)
- Now we can write the prefix sum as sum of two BIT tree B1 and B2 as
  - `sum[0, i] = sum(B1, i) * i - sum(B2, i)`, where
  - B1 contains updates in the form of `x`
  - B2 contains updates in the form of `x * (i - 1)`

#### [Binary Indexed Tree](./CodeSnippets/Trees/FenwickTree2D.cpp): 2 Dimensions

This is relatively simpler to implement compared to segment trees for 2 dimensions.

## Dynamic Programming

Nothing for notes as such,just remember

- When calculating some `ith` state, if you need to find the max of all smaller / greater element than i'th, then use
  binary search or set or segment tree.
- Some nice questions to know advance patterns:
  - [CSES: Elevator](https://cses.fi/problemset/task/1653)

## Array

This section mostly contains algorithms related to arrays

### Longest Increasing Subsequence

Apart from DP, we have a smart `O(nlogn)` solution.

```cpp
vi lis;
FORE(i, a) {
    auto it = lower_bound(all(lis), i);
    if (it == lis.end())
        lis.pub(i);
    else
        *it = i;
}
op(lis.size());
```
