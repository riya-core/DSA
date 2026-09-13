# Codeforces:1648A :: 1D Decomposition & Prefix Sums for Pairwise Manhattan Distance

## Overview

A common bottleneck in coordinate geometry problems is computing the sum of pairwise Manhattan distances across a subset of points. When a group contains $K$ points, computing distances pairwise by brute force requires $O(K^2)$ operations. For large inputs ($K \approx 10^5$), this immediately results in a Time Limit Exceeded (TLE).

This technique optimizes pairwise distance summation from **$O(K^2)$ down to $O(K \log K)$** by combining two core ideas:
1. **Dimension Independence (Coordinate Decoupling)**
2. **Sorting + Contribution via Prefix Sums**

---

## 1. Dimension Decoupling

The Manhattan distance between two cells $(r_1, c_1)$ and $(r_2, c_2)$ is defined as:

$$\text{dist} = |r_1 - r_2| + |c_1 - c_2|$$

Notice that the row dimension ($r$) and column dimension ($c$) are completely independent:

$$\sum_{i < j} (|r_i - r_j| + |c_i - c_j|) = \sum_{i < j} |r_i - r_j| + \sum_{i < j} |c_i - c_j|$$

Because the summation splits cleanly, **2D points do not need to stay paired**. We can extract all row indices into one 1D array and all column indices into another 1D array, solving the exact same 1D subproblem twice.

---

## 2. Resolving Absolute Values (1D Subproblem)

Given an array of 1D coordinates $A = [a_0, a_1, \dots, a_{k-1}]$, we want to find:

$$\sum_{i < j} |a_i - a_j|$$

The absolute value $|a_i - a_j|$ creates conditional branching ($a_i - a_j$ vs. $a_j - a_i$). We can eliminate the absolute value entirely by **sorting** the array in non-decreasing order:

$$a_0 \le a_1 \le a_2 \le \dots \le a_{k-1}$$

Once sorted, every element $a_i$ is guaranteed to be greater than or equal to all preceding elements $a_j$ where $j < i$. Therefore, for all $j < i$:

$$|a_i - a_j| = a_i - a_j$$

---

## 3. Contribution Technique & Prefix Sums

Instead of recomputing the difference for each pair $(j, i)$, analyze the aggregate contribution of $a_i$ against all elements before it:

$$\sum_{j=0}^{i-1} (a_i - a_j) = \sum_{j=0}^{i-1} a_i - \sum_{j=0}^{i-1} a_j$$

Breaking this down:
- $\sum_{j=0}^{i-1} a_i$: The term $a_i$ is added once for each of the $i$ elements before it, yielding $i \cdot a_i$.
- $\sum_{j=0}^{i-1} a_j$: This is the sum of all elements strictly before index $i$.

Thus, for any index $i$ (0-indexed):

$$\text{Contribution}(a_i) = (i \cdot a_i) - \text{PrefixSum}_{i-1}$$

By maintaining a running prefix sum as you iterate from left to right, each step takes $O(1)$ time.

---

## Complexity Analysis

For an array of size $K$:
- **Sorting:** $O(K \log K)$
- **Prefix Sum Accumulation:** $O(K)$
- **Total Time:** $O(K \log K)$
- **Space:** $O(K)$ to store the 1D coordinates

If the grid has dimensions $N \times M$, the sum of sizes of all color groups satisfies $\sum K \le N \cdot M$. The total runtime across all groups is bounded by $O(NM \log(NM))$.

---

## Quick Revision Sheet (Cheatsheet)

* **Trigger:** "Find sum of pairwise Manhattan distances between similar elements."
* **Pitfall:** Pairing $(r, c)$ coordinates forces $O(K^2)$ checks.
* **Step 1:** Separate dimensions: $\sum \text{dist} = \sum |r_i - r_j| + \sum |c_i - c_j|$.
* **Step 2:** Sort the 1D coordinate array.
* **Step 3:** Accumulate: $\text{Total} += (i \cdot a_i) - \text{PrefixSum}$.
* **Data Types:** Ensure all totals and prefix sums use 64-bit integers (`long long` in C++) to prevent integer overflow.

---

## Reference Problems

* **Codeforces 1648A - Weird Sum (Rating 1400)**: Pairwise Manhattan distances for matching colors on an $N \times M$ grid.
