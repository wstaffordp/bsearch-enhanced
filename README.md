`bsearch_enhanced()` searches for an element within a sorted array as an optimal, universal replacement for `bsearch()` in security-compliant C systems.

The license is public domain. Anyone is free to use it for any purpose without restriction. It has no warranty.

On average, it's faster and safer than every other evaluated search algorithm for sorted arrays that don't require a specific distribution of elements, including variations of Binary Search, Exponential Search and Fibonacci Search.

I welcome submissions of algorithms in the same class that challenge the aforementioned claim.

`bsearch_enhanced()` is the search function that searches for an element in an array of sorted elements.

It accepts the following 5 arguments in left-to-right order.

1. `low` is the `size_t` lowest index bound to search in `haystack`.
2. `high` is the `size_t` highest index bound to search in `haystack` and must be greater than or equal to `low`.
3. `haystack` is the `int` array of elements to search. The elements must be sorted in ascending order as the `bsearch()` comparison function [requires ascending sort order](https://www.ibm.com/docs/en/zos/3.1.0?topic=functions-bsearch-search-arrays) as well.
4. `needle` is the `int` element to search for in `haystack`. The data type of `needle` must match the data type of `haystack`.
5. `position` is the `size_t` pointer that contains the index of the found element.

The return value data type is `char`.

When the return value is `1`, `position` contains the index of the found `needle`.

When the return value is `0`, the element isn't found and `position` has no context to the search operation.

`bsearch()` doesn't guarantee a worst O(log n) time complexity, doesn't return a specific index position when an element is found and doesn't support searching within restricted bounds.

By default, `bsearch_enhanced()` omits the comparison function from `bsearch()` as many `bsearch()` implementations are unnecessary in place of Binary Search.

When an advanced comparison function is required, the additional logic can be inserted before all instances of `*position = low` and `*position = high`. Code examples with advanced comparisons are coming soon.

In addition to the preliminary conditional statements in `bsearch_enhanced()` creating the fastest instance whenever `needle` isn’t within bounds, they set up a fast and safe range to iterate through without requiring additional comparisons.

Instead of initializing with a median pivot value before determining a search direction, the `high` bound is halved, meaning the first Binary Search operation always uses subtraction repeatedly before proceeding in the opposite direction.

The alternation prevents excessive array accesses and equality operations after each modification of the `high` bound to increase speed without either exceeding bounds or skipping elements.
It repeats until either `gap` is `2` or the `high` bound is greater than or equal to `needle`. Then, to avoid infinite loops, it processes a final one-way Binary Search operation as if `gap` is `1`.

The following benchmarks measure the [benchmark example](https://github.com/wstaffordp/bsearch-enhanced/blob/master/examples/benchmark.c) speed from the Unix `time` command with various compilers and settings.

```
gcc -O3

1st   bsearch_enhanced()          0.219s
2nd   bsearch()                   0.258s
3rd   binary_search()             0.264s
4th   monobound_binary_search()   0.319s
5th   interpolation_search()      0.389s
```

```
gcc -O2

1st   bsearch_enhanced()          0.244s
2nd   binary_search()             0.285s
3rd   bsearch()                   0.293s
4th   monobound_binary_search()   0.341s
5th   interpolation_search()      0.421s
```

```
gcc -O1

1st   bsearch_enhanced()          0.227s
2nd   binary_search()             0.278s
3rd   monobound_binary_search()   0.308s
4th   bsearch()                   0.334s
5th   interpolation_search()      0.422s
```

```
gcc -O0

1st   bsearch_enhanced()          0.514s
2nd   bsearch()                   0.637s
3rd   monobound_binary_search()   0.659s
4th   binary_search()             0.675s
5th   interpolation_search()      0.863s
```

```
clang -O3

1st   bsearch_enhanced()          0.213s
2nd   bsearch()                   0.251s
3rd   monobound_binary_search()   0.261s
4th   binary_search()             0.264s
5th   interpolation_search()      0.435s
```

```
clang -O2

1st   bsearch_enhanced()          0.219s
2nd   bsearch()                   0.272s
3rd   monobound_binary_search()   0.280s
4th   binary_search()             0.281s
5th   interpolation_search()      0.475s
```

```
clang -O1

1st   bsearch_enhanced()          0.219s
2nd   bsearch()                   0.265s
3rd   monobound_binary_search()   0.274s
4th   binary_search()             0.280s
5th   interpolation_search()      0.477s
```

```
clang -O0

1st   bsearch_enhanced()          0.552s
2nd   bsearch()                   0.646s
3rd   binary_search()             0.694s
4th   monobound_binary_search()   0.703s
5th   interpolation_search()      0.809s
```
