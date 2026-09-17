# LeetCode 1477 — Minimum Two Non-Overlapping Subarrays

## 🎯 Problem Pattern

**Given:**
An array of **positive integers** and a target.

Find **two non-overlapping subarrays** whose sums are equal to `target`, minimizing the sum of their lengths.

---

# 1. First Natural Thought — Find Two Subarrays

The most straightforward thought is:

> "Find one valid subarray, then search for another valid subarray after it."

Conceptually:

```text
First subarray              Second subarray
[---------]                 [---------]
i         j                 j+1       k
```

For every possible first subarray:

1. Find `[i...j]` with sum = target.
2. Start searching from `j+1`.
3. Find another subarray with sum = target.
4. Minimize:

```text
length(first) + length(second)
```

### 🚨 Problem

The second search is repeated again and again.

So we get something like:

```text
First subarray  → search remaining array
First subarray  → search remaining array
First subarray  → search remaining array
...
```

This can become **O(n²)** and may TLE.

---

# 2. Important Question to Ask

Instead of:

> "After finding my current subarray, how do I search for the next one?"

Ask:

> **"Can I remember the best subarray I've already seen?"**

This changes the direction of the solution.

Instead of repeatedly searching the future:

```text
Current → Search future
Current → Search future
Current → Search future
```

we store useful information about the past:

```text
Past information
       ↓
   DP / best array
       ↓
Current subarray
```

This is the key optimization.

---

# 3. The Main Aha! 💡

Suppose we currently find a valid subarray:

```text
[l ................. r]
```

with:

```text
sum = target
```

Its length is:

```text
r - l + 1
```

Now the second subarray does NOT need to be searched.

We only need to know:

> **What is the shortest valid subarray that exists completely before `l`?**

If we already know that, we can immediately combine them.

```text
Previous best          Current
[---------]          [-------------]
           |         |
           l         r
           ↑
       boundary
```

Therefore:

```text
answer candidate =
best previous length + current length
```

This is the crucial transition.

---

# 4. DP / Prefix-Best State

Define:

```text
dp[i] = minimum length of a valid subarray
        completely contained before index i
```

In other words:

```text
dp[i]
```

stores the best valid subarray available in:

```text
[0 ... i-1]
```

This definition is extremely useful because if our current subarray starts at `l`:

```text
[l ... r]
```

then:

```text
dp[l]
```

can only contain a subarray ending before `l`.

Therefore:

```text
dp[l] + (r-l+1)
```

automatically represents **two non-overlapping subarrays**.

### 🔥 No separate overlap checking required.

---

# 5. Why `dp[l]` Instead of `dp[r]`?

This is an important indexing idea.

Current subarray:

```text
        l                 r
        ↓                 ↓
--------[=================]--------
        current subarray
```

We need a previous subarray that ends **before `l`**.

So:

```text
dp[l]
```

is exactly what we want.

If we used:

```text
dp[r]
```

the stored subarray might overlap the current one.

### Rule

When a current interval starts at `l`:

> **Query the best information strictly before `l`.**

---

# 6. How Do We Find Valid Subarrays Efficiently?

The array contains **positive integers**.

That is a huge clue.

For positive numbers, we can use a **sliding window**.

Maintain:

```text
[l ... r]
```

and its sum.

Expand:

```text
r → r + 1
```

If:

```text
sum > target
```

shrink from the left:

```text
l → l + 1
```

until:

```text
sum <= target
```

If:

```text
sum == target
```

we found a valid subarray.

---

# 7. Why Sliding Window Works Here

The positivity of the array is critical.

When we increase `r`:

```text
sum increases
```

When we increase `l`:

```text
sum decreases
```

Therefore, once:

```text
sum > target
```

we know that we must remove elements from the left.

This monotonic behavior allows the two pointers to move only forward.

### Complexity

Although there is a `while` inside the loop:

```text
r moves → at most n times
l moves → at most n times
```

Therefore:

```text
O(n)
```

not:

```text
O(n²)
```

---

# 8. The Complete Transition

Suppose sliding window finds:

```text
[l ... r]
```

and:

```text
sum == target
```

Current length:

```text
len = r-l+1
```

We already know:

```text
dp[l]
```

= shortest valid subarray before `l`.

Therefore:

```text
candidate = dp[l] + len
```

and:

```text
answer = min(answer, candidate)
```

Then the current subarray itself becomes useful information for future subarrays.

So we update the prefix-best state.

Conceptually:

```text
Current valid subarray
        ↓
store its length
        ↓
future subarray can use it
```

---

# 9. Why Carry `dp` Forward?

Suppose no valid subarray ends exactly at the current position.

We still don't want to lose the best subarray found earlier.

Example:

```text
index:  0 1 2 3 4 5
               ↑
             current
```

A valid subarray may have ended at index `2`.

Its information must still be available at index `3`, `4`, `5`...

Therefore:

```text
dp[i] = min(
    best ending here,
    best already seen before
)
```

This is called **carrying the prefix optimum forward**.

---

# 10. The Beautiful Part of the Optimization 🔥

### Initial approach

```text
Find first subarray
        ↓
Search for second subarray
        ↓
Repeat
```

Potentially:

```text
O(n²)
```

### Optimized approach

```text
Scan once
   ↓
Find current valid subarray
   ↓
Ask DP:
"What is the best valid subarray before me?"
   ↓
Combine immediately
```

So:

```text
Sliding Window + Prefix Best
            ↓
           O(n)
```

---

# 11. The Mental Transformation to Remember

This is the most important revision point.

### ❌ Don't think:

> "I found one interval. Now I have to search for another interval."

### ✅ Think:

> **"I have already scanned the past. Can I store the best possible answer from the past so that the current interval can query it in O(1)?"**

That shift is the main trick.

---

# 12. General DP Pattern Behind This Problem

This problem teaches a much broader technique:

## "Best-so-far + current state"

Whenever you have:

```text
Current interval = [l...r]
```

and need another interval before it, ask:

> Can I precompute the best valid interval ending before `l`?

If yes, you can often turn:

```text
search previous interval
```

into:

```text
O(1) lookup
```

This pattern appears in many interval/subarray problems.

---

# 13. How to Recognize This Pattern

Look for these clues:

### Clue 1 — Multiple subarrays / intervals

The problem asks for:

* two subarrays
* multiple segments
* non-overlapping intervals
* minimum/maximum combined length/cost

---

### Clue 2 — Non-overlapping constraint

Something like:

```text
[first interval] [second interval]
```

Immediately think:

> "Can I store the best interval I've seen before the current one?"

---

### Clue 3 — Optimization over previous answers

If the current answer looks like:

```text
current_cost + best_previous_cost
```

there is a strong chance that a prefix DP / prefix-best array can help.

---

### Clue 4 — Positive numbers

If the array contains positive integers and the problem involves:

```text
subarray sum = target
```

immediately consider:

**Sliding Window / Two Pointers**

because the sum changes monotonically as the window moves.

---

# 14. A Useful Question During Optimization

When you have an O(n²) solution, ask:

> **"Why am I repeating the same search?"**

Then ask:

> **"Can I remember the result of that search?"**

For LC 1477:

```text
Repeated search:
"Find the best subarray before me."

Optimization:
Store that answer in dp.
```

This is a very useful way to discover DP optimizations yourself instead of memorizing solutions.

---

# 15. Why the Original O(n²) Idea Was Still Valuable

The TLE approach wasn't useless.

It helped identify the actual relationship:

```text
first subarray
      +
best second subarray after it
```

Then reverse the perspective:

```text
current subarray
      +
best previous subarray
```

The second form is much easier to precompute.

### Important lesson:

> **A TLE solution can reveal the correct DP state.**

Don't immediately throw away a slow solution.

First ask:

```text
What work am I repeating?
```

Then eliminate that repetition.

---

# 16. Indexing Trick to Memorize

A very useful convention:

```text
dp[i] = answer using elements before i
```

Then if current interval starts at:

```text
l
```

query:

```text
dp[l]
```

This makes interval boundaries extremely clean.

Visual:

```text
0 ---------------- l-1 | l ---------------- r
      DP territory     |    current window
                        ↑
                     dp[l]
```

The `|` boundary is doing all the overlap work for you.

---

# 17. Common Mistakes 🚨

### Mistake 1 — Using `dp[r]`

Wrong idea:

```text
dp[r] + current_length
```

The previous interval might overlap the current one.

Use the boundary:

```text
dp[l]
```

---

### Mistake 2 — Searching for the second subarray again

This recreates the O(n²) behavior.

Instead:

```text
precompute best past answer
```

---

### Mistake 3 — Using `if` instead of `while`

For sliding window:

```text
while(sum > target)
```

is required.

One removal may not be enough to bring the sum back under the target.

---

### Mistake 4 — Forgetting positivity

This sliding-window technique relies on:

```text
arr[i] > 0
```

If negative numbers were allowed, the sum would no longer behave monotonically and ordinary sliding window would not work this way.

---

### Mistake 5 — Losing the previous DP answer

Even if there is no valid subarray ending at the current position, the previous best must survive.

Think:

```text
dp[i] = best seen so far
```

not merely:

```text
dp[i] = answer ending exactly at i
```

---

# 18. Complexity

| Component         |            Complexity |
| ----------------- | --------------------: |
| Sliding window    |                  O(n) |
| DP / prefix-best  |                  O(n) |
| Combining answers | O(1) per valid window |
| Total             |              **O(n)** |
| Extra space       |              **O(n)** |

---

# 19. Revision Cheat Sheet 🧠

```text
LC 1477
│
├── Positive integers
│      ↓
│   Sliding Window
│
├── Need TWO non-overlapping subarrays
│      ↓
│   Current interval [l...r]
│
├── Need best interval before l
│      ↓
│   dp[l]
│
├── Current length
│      ↓
│   r-l+1
│
├── Combine
│      ↓
│   dp[l] + (r-l+1)
│
└── Store current answer for future
       ↓
    prefix minimum
```

### One-line memory hook:

> **"Find the current window with sliding window; ask DP for the best window before its left boundary."**

---

# 20. The Bigger DSA Lesson 🚀

The real takeaway from this problem is not:

> "Memorize LC 1477."

It's:

> **When an O(n²) solution repeatedly searches for an optimal previous/future segment, try storing the best result of that search and turning it into an O(1) lookup.**

The progression is:

```text
Brute force
    ↓
Identify repeated work
    ↓
Store useful previous result
    ↓
Prefix DP / prefix minimum
    ↓
Combine with current state
    ↓
Optimize remaining search
    ↓
O(n)
```

That transition — **from repeatedly searching to remembering the best-so-far** — is the real pattern worth carrying to other problems.
