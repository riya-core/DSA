# Codeforces 1513B - AND Sequences

A conceptual breakdown, intuition guide, and problem-solving playbook for **Codeforces 1513B (AND Sequences)**.

---

## 1. Problem Overview

* **Platform:** Codeforces
* **Problem Code:** 1513B
* **Topic:** Bitwise Operations, Combinatorics, Prefix/Suffix Invariants
* **Rating:** ~1300–1400

### What the Problem Asks
You are given an array of `n` non-negative integers. An arrangement (permutation) of these elements `a[1], a[2], ..., a[n]` is called **good** if for **every single split point** `i` from `1` to `n - 1`, the bitwise AND of the prefix equals the bitwise AND of the suffix:

```text
(a[1] & a[2] & ... & a[i]) == (a[i+1] & a[i+2] & ... & a[n])   for all 1 <= i <= n - 1
```

You must count how many distinct permutations of the given array satisfy this condition simultaneously for **all** split points, modulo `10^9 + 7`.

---

## 2. The Core Mathematical Intuition

### Step 1: What Happens at the Extreme Boundaries?
Instead of checking all middle split points, inspect the two extreme boundaries:

1. **At the very first split (i = 1):**
   `a[1] == (a[2] & a[3] & ... & a[n])`

   Bitwise AND-ing both sides with `a[1]` gives:
   `a[1] & a[1] == a[1] & (a[2] & a[3] & ... & a[n])`
   `a[1] == (total AND of the entire array)`

2. **At the very last split (i = n - 1):**
   `(a[1] & a[2] & ... & a[n-1]) == a[n]`

   Similarly, AND-ing both sides with `a[n]` yields:
   `a[n] == (total AND of the entire array)`

> **Fundamental Deduction:** Let `T = a[1] & a[2] & ... & a[n]`. In any valid arrangement, both the first element and the last element **must strictly equal `T`**.

---

### Step 2: Why Must the Endpoints Be Exactly Equal to T?
Bitwise AND is a monotonically non-increasing operation on set bits. When you include more numbers into a bitwise AND:
* A bit that is `0` can **never** turn back into `1`.
* Therefore, for any prefix or suffix:
  `Prefix AND >= T` and `Suffix AND >= T`
* Furthermore, by definition, the overall array AND is `T`.

If the problem requires `Prefix AND == Suffix AND` at every split point:
* The prefix and suffix together span the entire array.
* The only value both halves can share simultaneously is the overall bitwise AND: **`T`**.

Thus, at **every** split step `i`:
* `prefix_and(i) == T`
* `suffix_and(i+1) == T`

For the very first prefix (`a[1]`) to already equal `T`, the element `a[1]` itself must satisfy `a[1] == T`.  
For the very last suffix (`a[n]`) to already equal `T`, the element `a[n]` itself must satisfy `a[n] == T`.

---

### Step 3: Why Does Fixing Just the Two Ends Guarantee the Entire Middle?
Once you fix `a[1] = T` and `a[n] = T`:

1. **Every prefix starts with a[1] = T:**
   `prefix_and(i) = a[1] & a[2] & ... & a[i] = T & (a[2] & ... & a[i])`

   Because `T` already has `0` wherever any number in the array has `0`, AND-ing `T` with any other elements from the array **cannot change `T`**:
   `T & x == T` for every element `x` in the array.
   Therefore, **every prefix AND is guaranteed to evaluate to `T`**.

2. **Every suffix ends with a[n] = T:**
   `suffix_and(i+1) = (a[i+1] & ... & a[n-1]) & a[n] = (a[i+1] & ... & a[n-1]) & T == T`
   Therefore, **every suffix AND is also guaranteed to evaluate to `T`**.

### Conclusion
As long as the two boundary positions (`a[1]` and `a[n]`) are assigned elements strictly equal to `T`:
* **All (n - 2) elements in the middle can be placed in ANY arbitrary order.**
* Every single split point will automatically satisfy `Prefix AND == Suffix AND == T`.

---

## 3. The Combinatorial Counting Formula

Let `cnt` be the number of elements in the given array that are strictly equal to `T`:

1. **If cnt < 2:**
   You do not have enough elements equal to `T` to place at both ends (`a[1]` and `a[n]`).
   * **Answer = 0**

2. **If cnt >= 2:**
   * Ways to choose and place the first element `a[1]`: `cnt` choices.
   * Ways to choose and place the last element `a[n]`: `(cnt - 1)` choices.
   * Total ways for the boundaries: `cnt * (cnt - 1)`.
   * Ways to arrange the remaining `(n - 2)` middle elements: `(n - 2)!`.

```text
Total Ways = (cnt * (cnt - 1) * (n - 2)!) % (10^9 + 7)
```

---

## 4. Tips & Mental Models for Bitwise & Permutation Problems

### Tip 1: "For All Split Points" -> Check the Extremes First
When a problem says a condition must hold for **every** split point `1 <= i <= n - 1`, test the boundary conditions:
* `i = 1` (first element isolated on the left)
* `i = n - 1` (last element isolated on the right)

These boundary constraints almost always force an invariant that dictates the entire sequence.

### Tip 2: The "Monotonic Filter" Nature of Bitwise AND
* Bitwise AND only eliminates `1`s; it can never restore them.
* If the entire set ANDs to `T`, then `T` is a submask of every single element (`x & T == T`).
* Once an accumulator reaches `T`, no remaining element from the array can change it. It stays `T` indefinitely.

### Tip 3: Distinguish "Arrangement Search" vs "Permutation Counting"
* If a problem asks "is there an arrangement?", you only need to construct one.
* If a problem asks "how many permutations?", look for **degrees of freedom**:
  * Which positions are strictly constrained? (Here: only index `1` and index `n`).
  * Which positions are completely unconstrained? (Here: all `n - 2` middle positions).
* Once the hard constraints are pinned down, the unconstrained elements contribute simple factorial permutations `k!`.

### Tip 4: Watch for Edge Cases
* When calculating `(n - 2)!`, note that `0! = 1` (for `n = 2`).
* Apply the modulo `10^9 + 7` at every single multiplication step to avoid 64-bit integer overflow.
