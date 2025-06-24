`bsearch_enhanced()` searches for an element within a sorted array as an optimal, universal replacement for `bsearch()` in security-compliant C systems.

The license is public domain. Anyone is free to use it for any purpose without restriction. It has no warranty.

On average, it's faster and safer than every other evaluated search algorithm for sorted arrays that don't require a specific distribution of elements, including variations of Binary Search, Exponential Search and Fibonacci Search.

I welcome submissions of algorithms in the same class that challenge the aforementioned claim.

Detailed benchmark results are coming soon.

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
