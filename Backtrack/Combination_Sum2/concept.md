# LeetCode 40 — Combination Sum II

## 1. Problem Summary

Given an array of candidate numbers and a target, return all **unique combinations** whose sum equals the target.

Rules:
- Each array element can be used **at most once**.
- The input may contain duplicate values.
- The output must not contain duplicate combinations.
- The order of combinations in the answer does not matter.

The important distinction: a value may appear multiple times in one combination **if it occurs multiple times in the input**. We cannot reuse the same array index.

---

## 2. Core Idea: Backtracking

Backtracking explores possible choices one by one.

At each recursive step:
1. Choose a candidate.
2. Reduce the remaining target by that candidate.
3. Continue searching from the next index.
4. Undo the choice before trying another candidate.

A path represents the current combination. When its sum reaches the target, record it and stop exploring that path.

### Base cases

- **Remaining target equals zero:** a valid combination has been found. Save it and return.
- **Candidate is greater than the remaining target:** because the candidates are sorted, this candidate and every later candidate are too large. Stop the loop.
- **No candidates remain:** the current path cannot be extended.

A negative remaining target can also be rejected, but sorted input allows the loop to stop before selecting an oversized candidate.

---

## 3. Why Sort the Input?

Sorting helps with two things:

- **Duplicate detection:** equal values become adjacent.
- **Pruning:** once a candidate exceeds the remaining target, all later candidates will also exceed it.

Sorting does not change which combinations are possible; it only makes them easier to find efficiently.

---

## 4. Why Use `index + 1` in Recursion?

Each element can be used only once.

After choosing the candidate at index `i`, the next recursive call starts at `i + 1`. This prevents the same **array position** from being selected again.

For example, if the input contains three occurrences of `1`, a valid combination may contain three `1`s—but each must come from a different index.

### Contrast with Combination Sum I

| Feature | Combination Sum (LC 39) | Combination Sum II (LC 40) |
|---|---|---|
| Reuse an array element? | Yes, unlimited reuse | No, each index at most once |
| Recursive starting index | Usually `i` | `i + 1` |
| Duplicate values in input | Usually distinct candidates | May contain duplicates |
| Duplicate-result handling | Usually not needed for distinct candidates | Skip duplicate choices at the same depth |

---

## 5. The Most Important Trick: Skip Duplicates at the Same Depth

After sorting, equal values are adjacent. During the loop, skip a value when:

- It is equal to the previous value, **and**
- It is not the first choice at the current recursion depth.

Conceptually, the condition is:

`i > index && candidates[i] == candidates[i - 1]`

### Why does `i > index` matter?

It ensures we skip only equivalent choices made at the **same depth**.

Suppose the candidates are `[1, 1, 2]` and the target is `3`.

- Choosing the first `1` can lead to a branch that later chooses the second `1`.
- At the starting level, choosing the second `1` instead of the first would repeat equivalent work, so that branch is skipped.
- Inside the first branch, the second `1` is still available because it is at a deeper recursion level.

This allows combinations such as `[1, 1, 1]` when the input contains at least three separate `1` elements.

**Remember:** Skip duplicate *choices at the same level*, not duplicate values everywhere.

---

## 6. Why a `set<vector<int>>` Is Usually Unnecessary

A set can remove duplicate combinations after they have been generated. This can produce correct unique output, but it has drawbacks:

- Duplicate branches are still explored.
- Every combination is inserted into an ordered set, adding overhead.
- The final result must be copied from the set into a vector.

Skipping duplicate choices during backtracking prevents much of this repeated work before it happens. A normal result vector is sufficient.

---

## 7. Why a `used` Array Is Unnecessary

A boolean `used` array is often useful in permutation problems, where the recursion may consider elements from many positions.

Here, the recursion always moves forward using `i + 1`. Earlier indices are never revisited, so the recursion index itself already prevents reuse.

**Rule of thumb:** If the recursion only moves forward through a sorted array, check whether the starting index already handles element usage before adding a separate `used` array.

---

## 8. Why a Global “Found One” Flag Is Wrong

Finding one valid combination does **not** mean the whole search is complete.

The goal is to find **all** unique combinations. When the remaining target reaches zero:

1. Save the current combination.
2. Return from that recursive call only.
3. Allow other branches to continue.

A global stop flag can discard valid answers. In backtracking, distinguish carefully between:

- **Returning from one path:** normal and necessary.
- **Stopping the entire search:** appropriate only when the problem asks for one answer or a specific stopping condition has been satisfied.

---

## 9. Pruning Tips

### Candidate exceeds the remaining target

Because the array is sorted and candidates are positive, once the current candidate is larger than the remaining target, break out of the loop. Later candidates cannot work either.

### Remaining target becomes zero

Record the current combination immediately. Adding more positive candidates would make the sum too large.

### Duplicate candidate at the same depth

Skip it to avoid exploring a branch equivalent to one already considered.

These optimizations preserve correctness while reducing unnecessary recursive calls.

---

## 10. Complexity Analysis

Let `n` be the number of candidates.

### Time complexity: `O(n × 2^n)` worst case

There can be up to `2^n` subsets of `n` elements. Constructing or copying a combination can take up to `O(n)` time, giving a commonly stated worst-case upper bound of `O(n × 2^n)`. Sorting costs `O(n log n)` and is dominated by this bound.

Duplicate skipping and pruning often reduce practical work, but they do not improve the worst-case exponential nature of the problem.

### Auxiliary space: `O(n)`

Excluding the returned answers:
- Recursion depth is at most `O(n)`.
- The current combination stores at most `n` elements.
- Sorting may use additional implementation-dependent stack space.

### Output space: up to `O(n × 2^n)`

There can be exponentially many valid combinations, and each stored combination may contain up to `n` elements. Output space is usually discussed separately from auxiliary space.

---

## 11. Common Mistakes Checklist

- [ ] Using `i` instead of `i + 1`, accidentally allowing reuse of an element.
- [ ] Skipping every repeated value globally, preventing valid combinations with repeated values.
- [ ] Forgetting the `i > index` part of duplicate skipping.
- [ ] Using a `set` to deduplicate results instead of avoiding duplicate branches.
- [ ] Returning from the entire search after finding the first valid combination.
- [ ] Forgetting to undo the last choice after recursion (backtracking cleanup).
- [ ] Forgetting to sort before duplicate checks or sorted-array pruning.
- [ ] Continuing the loop after a candidate exceeds the remaining target.
- [ ] Confusing a duplicate **value** with the same **array index**.

---

## 12. A Reliable Mental Model

For every recursive call, ask:

1. **What is my remaining target?**
2. **Which indices am I allowed to choose from?**
3. **Am I starting a duplicate branch at this depth?**
4. **Can sorted order prove that later choices are too large?**
5. **After recursion, have I undone my choice?**

If you can answer these five questions, you understand the core of this solution.

---

## 13. Interview-Ready Summary

Combination Sum II is a backtracking problem. Sort the candidates to make duplicate detection and pruning possible. At each step, select a candidate, subtract it from the remaining target, and recurse from the next index so that each array element is used at most once. Skip equal candidates when they occur at the same recursion depth to avoid duplicate combinations. Stop a branch when the target is reached, and use sorted order to stop exploring candidates that are too large.

**Key pattern:** Sort → Backtrack → Recurse with `i + 1` → Skip same-depth duplicates → Undo choice.
"""
