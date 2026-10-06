# Valid Parenthesis String — From Brute Force to Greedy

## Problem

Given a string containing:

- `(` — opening bracket
- `)` — closing bracket
- `*` — wildcard

The `*` can represent:

- `(`
- `)`
- empty string

Determine whether the string can be made valid by choosing an appropriate meaning for every `*`.

---

# 1. First Understand What Makes Parentheses Valid

For a normal parenthesis string, two conditions are required:

### Condition 1 — Prefix condition

At every point while scanning from left to right:

> Number of `)` cannot exceed number of `(`.

Otherwise, a closing bracket appears before anything can match it.

Example:

```text
)(
```

The first character is already invalid.

---

### Condition 2 — Final balance

At the end:

```text
number of '(' = number of ')'
```

Equivalently:

```text
unmatched '(' = 0
```

---

# 2. What Makes `*` Difficult?

Normally:

```text
( → always opening
) → always closing
```

But:

```text
* → can be (, ), or empty
```

Therefore, one character has multiple possible interpretations.

Example:

```text
(*)
```

The `*` could be:

```text
(
```

or:

```text
)
```

or:

```text
empty
```

The challenge is therefore:

> How do we keep track of these different possibilities without trying every combination?

---

# 3. First Thought — Brute Force

The most direct idea is:

> For every `*`, try all three possibilities.

For example:

```text
* → (
* → )
* → empty
```

If there are `k` stars, there can be roughly:

```text
3^k
```

different interpretations.

Then check whether any interpretation forms a valid parenthesis string.

### Complexity

```text
Time:  O(3^k × n)
Space: O(n) for recursion/state
```

This is exponential.

### Why is this useful?

Even though we won't implement it, brute force gives us an important understanding:

> The problem is about managing many possible interpretations of `*`.

That observation leads to the next question:

> Can we avoid explicitly trying every possibility?

---

# 4. Next Thought — Can a Stack Help?

For normal parentheses, the natural data structure is a stack.

Example:

```text
((()))
```

Whenever we see:

```text
(
```

we push it.

Whenever we see:

```text
)
```

we match it with a previous `(`.

So naturally, for this problem:

```text
( → push
) → match/pop
```

But what should we do with:

```text
*
```

?

It could potentially help us match an opening bracket.

This suggests keeping track of:

- unmatched `(`
- available `*`

---

# 5. First Stack Idea — Track `(` and `*`

We can maintain:

```text
open     → unmatched '('
extra    → available '*'
```

When we see:

```text
(
```

store it.

When we see:

```text
*
```

store it.

When we see:

```text
)
```

prefer:

```text
(
```

because it is an actual opening bracket.

If no `(` exists, use:

```text
*
```

as a substitute for `(`.

This already handles many cases.

---

# 6. Where Does the Simple Count Approach Fail?

The problem is that a `*` is not automatically usable for every `(`.

### Position matters.

Consider:

```text
(*(
```

Indexes:

```text
0 1 2
( * (
```

There is:

```text
1 star
2 opening brackets
```

A simple count says:

```text
1 star available
```

But that's not enough information.

The star is at index `1`.

The second `(` is at index `2`.

Therefore:

```text
star index < open index
```

The star occurs **before** that opening bracket.

It cannot travel backward and become `)` for it.

So the string is invalid.

---

# 7. The Important Discovery — Position Matters

This is the key insight of the problem.

A `*` can only help an opening bracket if:

```text
position of '*' > position of '('
```

because the `*` must occur **after** the `(` if it is going to become `)`.

Therefore:

> Counting stars is insufficient. We need their positions.

This is the point where the original simple `extra` counter breaks.

---

# 8. Transition — Store Indices Instead of Just Counts

Instead of storing:

```text
number of '('
number of '*'
```

store:

```text
positions of '('
positions of '*'
```

Use two stacks conceptually:

```text
Open Stack
    ↓
indices of unmatched '('

Star Stack
    ↓
indices of '*'
```

Now we know not only **how many** are available, but **where they occurred**.

---

# 9. How the Two-Stack Method Works

Scan from left to right.

### When we see `(`

Store its index in the open stack.

### When we see `*`

Store its index in the star stack.

### When we see `)`

First try to match it with an actual:

```text
(
```

If none exists, use a:

```text
*
```

as an opening bracket.

If neither exists:

```text
invalid
```

---

# 10. The Remaining Problem After the First Scan

After processing the entire string, we may still have unmatched:

```text
(
```

Now we need to use remaining:

```text
*
```

to convert them into:

```text
)
```

But again:

> Position matters.

For an opening bracket to be closed by a star:

```text
star position > open position
```

Therefore compare the top indices of the two stacks.

---

# 11. Why Matching from the Right Works

Suppose:

```text
Open:
[0, 2]

Star:
[1]
```

The remaining opening bracket at index `2` cannot use the star at index `1`.

Why?

```text
1 < 2
```

The star came too early.

Therefore invalid.

But if:

```text
Open:
[0, 2]

Star:
[1, 3]
```

we can match:

```text
open 2 ← star 3
open 0 ← star 1
```

Everything works.

This is why the stacks of indices are powerful.

---

# 12. Complexity of the Two-Stack Solution

Every character:

- is processed once
- is pushed at most once
- is popped at most once

Therefore:

```text
Time:  O(n)
Space: O(n)
```

This is already an excellent solution.

But we can do even better in terms of space.

---

# 13. Ask the Next Question

The two-stack solution remembers a lot of information:

```text
exact position of every '('
exact position of every '*'
```

But do we really need all of that?

Ask:

> What information is actually necessary to know whether the string can still become valid?

We don't necessarily care about the exact positions anymore.

What we really care about is:

> How many unmatched `(` could possibly remain?

This leads to the greedy solution.

---

# 14. The Key Greedy Idea

Instead of tracking one exact number of unmatched `(`, track a **range**.

Define:

```text
low
```

as:

> Minimum possible number of unmatched `(` after processing the current prefix.

Define:

```text
high
```

as:

> Maximum possible number of unmatched `(` after processing the current prefix.

So instead of storing every possibility:

```text
0
1
2
3
4
```

we compress them into:

```text
[low, high]
```

For example:

```text
low = 1
high = 4
```

means the current prefix could have:

```text
1, 2, 3, or 4
```

unmatched opening brackets depending on how we interpret the stars.

---

# 15. Why Is This Compression Possible?

The important observation is that the possible values form a continuous range.

For example:

```text
0, 1, 2, 3
```

can be represented simply as:

```text
[0, 3]
```

We don't need to remember every individual possibility.

This is the major conceptual jump:

> Instead of storing all possible states, store the boundaries of the possible states.

This is a common greedy/state-compression technique.

---

# 16. Effect of `(`

An opening bracket definitely increases the number of unmatched opens.

Therefore:

```text
low  increases by 1
high increases by 1
```

Example:

```text
possible unmatched opens:

[1, 4]

after '(':

[2, 5]
```

No uncertainty exists.

---

# 17. Effect of `)`

A closing bracket definitely tries to consume one unmatched opening bracket.

Therefore:

```text
low  decreases by 1
high decreases by 1
```

Example:

```text
[1, 4]

after ')':

[0, 3]
```

---

# 18. Effect of `*`

This is the interesting part.

A `*` has three possibilities:

```text
* → '('
* → ')'
* → empty
```

Therefore it can:

```text
increase unmatched '(' by 1
```

or:

```text
decrease unmatched '(' by 1
```

or:

```text
leave it unchanged
```

So:

```text
low decreases by 1
high increases by 1
```

Conceptually:

```text
[1, 4]

* can reduce:
1 → 0

* can increase:
4 → 5

therefore:

[0, 5]
```

This is why the wildcard expands the possible range.

---

# 19. Why Can `low` Never Be Negative?

Imagine:

```text
low = 0
```

and then a `*` acts as:

```text
)
```

Mathematically:

```text
low = -1
```

But there is no such thing as:

```text
-1 unmatched '('
```

The minimum possible number of unmatched opens is therefore:

```text
0
```

So we clamp:

```text
low = max(low, 0)
```

Important:

> A negative `low` is not an error.

It simply means:

> "The star could potentially close an opening bracket, but there weren't actually any opens to close."

So we reset the minimum possibility to zero.

---

# 20. Why Is `high < 0` an Immediate Failure?

This is much more important.

Remember:

```text
high = maximum possible unmatched '('
```

Suppose:

```text
high < 0
```

That means:

> Even under the most favorable interpretation of every `*`, we still have more closing brackets than available opening brackets.

There is no possible interpretation that can save the prefix.

Therefore:

```text
high < 0
```

means:

```text
INVALID
```

immediately.

---

# 21. Why Does `high` Protect Us From Too Many `)`?

Suppose:

```text
))))
```

There are no stars.

Initially:

```text
low = 0
high = 0
```

First `)`:

```text
low  = -1
high = -1
```

Even the maximum possible number of unmatched opens is negative.

Therefore the string is already impossible.

This is why:

```text
high
```

is effectively answering:

> "Can the maximum number of possible opens still handle all these closing brackets?"

If the answer becomes no:

```text
high < 0
```

we stop.

---

# 22. Why Do We Only Need `low == 0` at the End?

This is the other half of the greedy logic.

At the end, we need:

```text
unmatched '(' = 0
```

We know:

```text
low = minimum possible unmatched '('
```

Therefore:

```text
low == 0
```

means:

> There exists at least one interpretation of the `*` characters that leaves zero unmatched opening brackets.

And that's all we need.

We don't need every interpretation to work.

We only need:

```text
ONE valid interpretation
```

Therefore:

```text
low == 0
```

is enough.

---

# 23. Why Don't We Check `high == 0`?

Suppose at the end:

```text
low = 0
high = 3
```

This is still potentially valid.

Why?

Because the range means:

```text
possible unmatched '(':

0
1
2
3
```

There is a possibility where:

```text
unmatched '(' = 0
```

That's enough.

Therefore:

```text
low == 0
```

is the important final condition.

Not:

```text
high == 0
```

---

# 24. Complete Greedy Mental Model

At every point:

```text
             possible unmatched '('

          low ---------------- high
           ↑                     ↑
        minimum               maximum
        possible              possible
```

### `(`

```text
[low, high]
      ↓
[low + 1, high + 1]
```

### `)`

```text
[low, high]
      ↓
[low - 1, high - 1]
```

### `*`

```text
[low, high]
      ↓
[low - 1, high + 1]
```

Then:

```text
low cannot be below 0
```

and:

```text
high cannot be below 0
```

If `high` becomes negative:

```text
impossible
```

At the end:

```text
low == 0
```

means:

```text
a valid interpretation exists
```

---

# 25. How the Two-Stack Solution Becomes Greedy

This is the most important transition to remember.

### Two-stack approach

Stores detailed information:

```text
where are all unmatched '('?
where are all '*'?
```

This gives exact positional information.

Complexity:

```text
O(n) space
```

---

### Greedy approach

Ask:

> Do I really need the exact positions anymore?

Instead, track:

```text
minimum possible unmatched '('
maximum possible unmatched '('
```

So:

```text
Detailed possibilities
        ↓
compress into a range
        ↓
[low, high]
```

Therefore:

```text
Two stacks → exact state
Greedy     → boundary of possible states
```

This reduces space from:

```text
O(n)
```

to:

```text
O(1)
```

while keeping:

```text
O(n)
```

time.

---

# 26. Why This Is Called Greedy

At every character, we don't decide exactly what every `*` should become.

Instead, we maintain the **best possible boundaries**:

```text
low  → most restrictive/minimum possibility
high → most flexible/maximum possibility
```

We postpone the exact decision about each `*`.

This is powerful because:

> We don't need to decide the meaning of a star immediately.

We only need to know whether some valid interpretation still exists.

---

# 27. The Full Evolution of the Thinking

This is the mental progression you should reproduce in an interview.

```text
Problem
  ↓
'(' and ')' need matching
  ↓
'*' has multiple meanings
  ↓
Brute force:
try every interpretation
  ↓
Too expensive
  ↓
Use stack because parentheses naturally match with stack
  ↓
Track '(' and '*'
  ↓
Simple count isn't enough
  ↓
Why?
  ↓
POSITION of '*' matters
  ↓
Store indices
  ↓
Two stacks:
open positions + star positions
  ↓
O(n) time, O(n) space
  ↓
Ask:
Do I really need exact positions?
  ↓
What actually matters?
  ↓
Number of unmatched '(' that can possibly remain
  ↓
There are multiple possibilities
  ↓
Can those possibilities be represented as a range?
  ↓
YES
  ↓
low = minimum possible unmatched '('
high = maximum possible unmatched '('
  ↓
Greedy O(n) time, O(1) space
```

---

# 28. The Three Most Important Insights

## Insight 1 — Wildcards create possibilities

`*` isn't one fixed character.

It represents three choices:

```text
(
)
empty
```

Therefore the problem is fundamentally about managing possibilities.

---

## Insight 2 — Position matters

A star cannot magically move around the string.

For:

```text
(*(
```

the star cannot close the second `(` because:

```text
star comes before '('
```

This is why a simple star count isn't enough.

---

## Insight 3 — Possibilities can sometimes be compressed

Instead of remembering every possible interpretation:

```text
state 1
state 2
state 3
...
```

we can sometimes maintain:

```text
minimum possible
maximum possible
```

Here:

```text
[low, high]
```

completely captures the information we need.

This is the key greedy/state-compression idea.

---

# 29. Common Mistakes

### Mistake 1 — Treating every `*` as automatically useful

Wrong:

> "There are enough stars, so the string must be valid."

Position can make a star useless.

---

### Mistake 2 — Only counting `(` and `*`

Counts alone lose ordering information.

---

### Mistake 3 — Jumping to DP immediately

Seeing multiple interpretations does not automatically mean DP.

First ask:

> Can I summarize all possibilities?

Here the answer is yes.

---

### Mistake 4 — Thinking `low` and `high` represent actual brackets

They don't.

They represent:

```text
possible NUMBER of unmatched '('
```

---

### Mistake 5 — Thinking negative `low` means invalid

No.

```text
low < 0
```

means the minimum possibility went below zero, so clamp it.

But:

```text
high < 0
```

means even the maximum possibility failed.

That's invalid.

---

### Mistake 6 — Checking `high == 0` at the end

Wrong.

We only need one valid interpretation.

Therefore:

```text
low == 0
```

is sufficient.

---

# 30. Complexity Comparison

| Approach | Time | Space | Main Idea |
|---|---:|---:|---|
| Brute force | Exponential | O(n) | Try every `*` interpretation |
| Simple stack/count attempt | O(n) | O(n) | Track brackets and stars |
| Two stacks | O(n) | O(n) | Track positions |
| Greedy | O(n) | O(1) | Track possible range |

---

# 31. Placement Interview Explanation

If asked to explain the greedy solution, a strong answer is:

> "I maintain the minimum and maximum possible number of unmatched opening brackets while scanning the string. `low` represents the minimum possible unmatched `(` and `high` represents the maximum possible unmatched `(`. An opening bracket increases both, a closing bracket decreases both, and a wildcard decreases `low` and increases `high` because it can act as either a closing or opening bracket. Since we cannot have a negative number of unmatched openings, `low` is clamped to zero. If `high` becomes negative, even the most favorable interpretation cannot make the prefix valid. At the end, `low == 0` means there exists an interpretation of the wildcards that makes the complete string valid."

That is a **proper placement-level explanation**, rather than just memorizing the formula.

---

# 32. Final Revision Sheet

### Brute Force

```text
Every * has 3 choices
→ exponential
```

### Stack

```text
Parentheses → naturally use stack
```

### Problem with simple star count

```text
Position matters
```

### Two stacks

```text
open → indices of '('
star → indices of '*'

Match ')' with '(' first,
otherwise '*'.

Remaining '(' need a '*' occurring AFTER them.
```

### Greedy

```text
low  = minimum possible unmatched '('
high = maximum possible unmatched '('
```

Transitions:

```text
( → low++, high++
) → low--, high--
* → low--, high++
```

Rules:

```text
low = max(low, 0)

high < 0
→ impossible

end:
low == 0
→ valid interpretation exists
```

### Core lesson

> **Don't just ask "How many possibilities are there?" Ask "What information distinguishes those possibilities?" Then ask whether that information can be compressed.**

For this problem:

```text
Exact positions
      ↓
Two stacks
      ↓
Possible unmatched-open counts
      ↓
[minimum, maximum]
      ↓
Greedy
```

**This is the real DSA lesson of the problem — not just the `low/high` formula.**
