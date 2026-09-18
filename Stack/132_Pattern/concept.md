# LeetCode 456 — 132 Pattern

## 🧠 Problem Concept

We need to determine whether an array contains three elements satisfying:

* `i < j < k`
* `nums[i] < nums[k] < nums[j]`

The three values form:

```text
1 < 2 < 3
```

but their positions are:

```text
1 → 3 → 2
```

Hence the name **132 Pattern**.

### Example

```text
[3, 5, 4]

3 < 4 < 5
1   2   3

Positions:

3 → 5 → 4
1 → 3 → 2
```

---

# 1. First Think: What Are We Actually Searching For?

The natural thought is:

> Find a small `1`, then a larger `3`, and finally a value `2` that lies between them.

So conceptually:

```text
        3
       / \
      1   2

Need:

1 < 2 < 3
```

while maintaining:

```text
index(1) < index(3) < index(2)
```

---

# 2. Initial Approach

A straightforward approach is:

1. Pick a possible `1`.
2. Search to its right for a possible `3`.
3. Search further right for a possible `2`.
4. Check whether:

```text
1 < 2 < 3
```

This directly follows the definition of the problem.

### Problem

Repeatedly searching for the third element can make the solution expensive.

The deeper question becomes:

> Can we maintain enough information while scanning instead of repeatedly searching?

This is the key optimization step.

---

# 3. Why Simply Keeping Minimum + Maximum Isn't Enough

A natural optimization is:

```text
minimum seen so far
        +
large value after it
        ↓
look for a middle value
```

This is a reasonable first attempt.

However, there can be **multiple useful candidates for `3` and `2`**.

A single `minimum` or `maximum` may not preserve the relationships we need.

The important information isn't simply:

```text
smallest value
largest value
```

It is:

```text
Which values can form a valid 2 with which larger 3?
```

This relationship is what the optimized solution preserves.

---

# 4. 🔄 The Key Insight: Scan From Right to Left

Instead of searching:

```text
1 → 3 → 2
```

scan the array in reverse:

```text
2 ← 3 ← 1
```

Now when we are looking at a possible `1`, the elements that could become `2` and `3` have already been processed.

This reverses the problem into something easier to maintain.

### Forward view

```text
Find:

1 → 3 → 2
```

### Reverse view

```text
Already processed:

2 ← 3

Current element:
1 ?
```

So the question becomes:

> "Do I already have a valid `2` associated with some larger `3`?"

If yes, checking a new `1` becomes extremely cheap.

---

# 5. What Does `second` Represent?

The optimized approach maintains a value representing a candidate for **2**.

Think:

```text
second = possible "2"
```

with some larger value already available as the corresponding **3**.

Therefore, if the current value satisfies:

```text
current < second
```

we immediately have:

```text
current < second < 3
   1        2       3
```

So the 132 pattern exists.

### Important

`second` is **not simply the second-smallest value**.

It means:

> A value that can serve as the `2` in a valid `2 → 3` relationship already found while scanning from the right.

This distinction is extremely important.

---

# 6. Why a Monotonic Stack?

While scanning from right to left, we need to maintain possible `3` values.

A stack helps us efficiently handle values that become candidates for `2`.

Suppose we have:

```text
2 < 5
```

and we encounter `5` while scanning backwards.

Then:

```text
2 → candidate for "2"
5 → candidate for "3"
```

So the smaller value can be promoted into our `second` candidate.

The stack allows us to repeatedly perform this promotion while maintaining useful ordering.

---

# 7. The Core Stack Idea

When the current element is **larger than the top of the stack**, the stack-top value can become a candidate for `2`.

Conceptually:

```text
stack top < current
    2          3
```

Therefore:

```text
stack top
    ↓
candidate for 2
```

The value is removed from the stack because its role has changed.

This process can happen repeatedly.

Example:

```text
Stack:

[2, 4, 6]

Current = 8
```

Since:

```text
2 < 8
4 < 8
6 < 8
```

values can be exposed as candidates for the middle `2`.

The stack efficiently handles this without rescanning the array.

---

# 8. The Three Mental Steps

For every element while scanning right → left:

### Step 1 — Can this be `1`?

Check whether:

```text
current < second
```

If yes:

```text
1 < 2 < 3
```

Pattern found.

---

### Step 2 — Can existing stack values become `2`?

If:

```text
current > stack top
```

then the stack-top value has found a larger `3`.

Therefore it can become a `2`.

Keep updating the useful `second` candidate.

---

### Step 3 — Treat current as a possible `3`

After handling smaller stack values, the current value can be stored as a future candidate for the larger `3`.

---

# 9. 🔥 Why the Reverse Direction Is So Powerful

Forward traversal forces you to remember:

```text
Have I seen a suitable 1?
Have I seen a suitable 3?
Can I now find a 2?
```

Reverse traversal changes this into:

```text
Have I already constructed a 2 < 3 relationship?
```

Then the current element only needs to answer:

```text
Is current < 2?
```

That is much easier.

This is a common algorithmic trick:

> **If a pattern contains elements that are easier to validate from the opposite direction, try reversing the traversal.**

---

# 10. Monotonic Stack Intuition

A monotonic stack is useful when:

* We need previous/next greater or smaller elements.
* Elements become irrelevant after encountering a stronger candidate.
* We want to process each element only a small number of times.
* We need to maintain ordered candidates dynamically.

For LC 456, the stack isn't being used merely to find "next greater."

It is being used to maintain **candidate relationships** between `2` and `3`.

That is the more important insight.

---

# 11. Why Each Element Is Efficiently Processed

Every value:

1. Gets pushed onto the stack.
2. Can be popped at most once.

Therefore, although there is a loop that may remove multiple elements at one point, the total number of removals across the entire algorithm is still limited.

This gives:

```text
Time:  O(n)
Space: O(n)
```

### Important complexity trick

Don't automatically assume:

```text
while loop inside for loop = O(n²)
```

If every element can enter and leave the stack only once, the total work can still be:

```text
O(n)
```

This is called **amortized analysis**.

---

# 12. 🧩 Connection to Your Original Approach

Your initial thought was:

```text
minimum
   ↓
find large
   ↓
find middle
```

That is actually a good starting point.

The optimization journey is:

```text
Brute force
   ↓
Try maintaining minimum
   ↓
Try maintaining large
   ↓
Realize multiple 2/3 relationships matter
   ↓
Reverse the traversal
   ↓
Maintain valid 2 → 3 relationships
   ↓
Use monotonic stack
   ↓
O(n)
```

So the important lesson isn't just the final stack technique.

It's understanding **why your original state wasn't enough**.

---

# 13. 🚨 Common Mistakes

### Mistake 1 — Forgetting the index order

It's not enough to find:

```text
1 < 2 < 3
```

The positions must correspond to:

```text
1 → 3 → 2
```

The ordering of indices is part of the problem.

---

### Mistake 2 — Thinking `second` means second-smallest

It doesn't.

It represents:

```text
a valid candidate for "2"
```

that already has a compatible larger `3`.

---

### Mistake 3 — Using only the global minimum

The smallest value isn't automatically useful.

What matters is whether it participates in:

```text
1 < 2 < 3
```

with the correct index ordering.

---

### Mistake 4 — Using only the maximum

Similarly, the largest value isn't necessarily enough.

The relationship between candidates matters more than isolated extrema.

---

### Mistake 5 — Traversing left → right by default

Whenever a pattern involves:

```text
i < j < k
```

ask yourself:

> Would reversing the traversal make one of the relationships easier to maintain?

For 132, the answer is yes.

---

# 14. 🧠 Pattern Recognition Cheat Sheet

When you see a problem asking for:

```text
a < b < c
```

but the array positions are rearranged, immediately ask:

### Question 1

What is the numerical relationship?

```text
1 < 2 < 3
```

### Question 2

What is the positional relationship?

```text
1 → 3 → 2
```

### Question 3

Can I scan from the opposite direction?

```text
2 ← 3 ← 1
```

### Question 4

Can I maintain a useful candidate instead of searching repeatedly?

### Question 5

Do candidates become irrelevant in an ordered way?

If yes:

```text
🔥 Monotonic stack candidate
```

---

# 15. 💡 General Monotonic Stack Lesson

Don't think:

> "This is a stack problem."

Think:

> "I need to maintain a set of candidates where some candidates become useless once a stronger relationship appears."

Then ask:

```text
Can I remove those useless candidates permanently?
```

If yes, a monotonic stack may give you an `O(n)` solution.

---

# 16. Quick Revision

### Pattern

```text
1 < 2 < 3
```

### Index order

```text
1 → 3 → 2
```

### Direction

```text
Right → Left
```

### Stack

Maintains candidate `3`s.

### `second`

Maintains a useful candidate for `2`.

### Detection

If current value can become the `1`:

```text
current < second
```

then:

```text
1 < 2 < 3
```

exists.

### Complexity

```text
Time  → O(n)
Space → O(n)
```

---

# 🚀 Final Takeaway

The biggest lesson from LC 456 is **not the code**.

It's this transformation:

```text
"Find 1, then 3, then 2"
             ↓
"Can I build the 2–3 relationship first?"
             ↓
"Scan from right to left"
             ↓
"Maintain candidates with a monotonic stack"
             ↓
"When I see a smaller value, check whether
it can become 1"
```

Once this mental transformation becomes familiar, a lot of seemingly weird monotonic-stack problems become much less scary.

**Remember:**

> Don't store everything. Store the information that makes the next decision O(1).
