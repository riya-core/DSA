# LeetCode 856 — Score of Parentheses

## 🧠 Core Idea

The problem assigns a score to a balanced parentheses string using three rules:

- `()` → **1**
- `(A)` → **2 × score(A)**
- `AB` → **score(A) + score(B)**

The main challenge is handling **nested parentheses** and **multiple groups at the same level**.

---

## 🔑 The Most Important Insight

Think of every pair of parentheses as a **level**.

Whenever `(` appears:

> Start a new level where we will collect the score of everything inside it.

Whenever `)` appears:

> Finish the current level, calculate its score, and add that score to its parent level.

So the stack is not simply storing parentheses.

### The stack stores:

> **The accumulated score at each nesting level.**

---

# 📦 Stack Concept

Start with one extra level representing the outside of the entire string.

```text
[0]
```

When `(` appears:

```text
Create a new score bucket
```

Conceptually:

```text
[0, 0]
```

Another `(`:

```text
[0, 0, 0]
```

Each `0` represents a new nesting level whose score has not been calculated yet.

---

# 🔄 What Happens When `)` Appears?

There are two cases.

## Case 1: The inside score is `0`

This means the pair was:

```text
()
```

Therefore:

```text
score = 1
```

### Important

Never represent `()` using `0`.

`0` is being used to represent an **empty/new level**.

If you also use `0` as the score of `()`, you lose the ability to distinguish:

```text
Boundary / new level
```

from:

```text
Actual score
```

This was the key issue in the original approach.

---

# Case 2: The inside score is non-zero

Suppose:

```text
(A)
```

and the score of `A` is `x`.

According to the rule:

```text
(A) = 2 × x
```

So:

```text
inside score = x
        ↓
multiply by 2
        ↓
parent level
```

---

# ➕ Why Do We Add to the Parent?

Consider:

```text
()()
```

This consists of two independent groups:

```text
() + ()
```

Each has score `1`.

Therefore:

```text
1 + 1 = 2
```

The stack handles this naturally.

After the first group:

```text
parent score = 1
```

After the second group:

```text
parent score = 1 + 1 = 2
```

### Key rule

> Every completed group contributes its score to the level outside it.

---

# 🔥 Example: `(()(()))`

Break the structure:

```text
(()(()))
```

Conceptually:

```text
(
    ()
    (())
)
```

Calculate the inner groups:

```text
() → 1
```

and:

```text
(()) → 2 × 1 = 2
```

Since they are next to each other:

```text
1 + 2 = 3
```

Now they are wrapped by another pair:

```text
(3)
```

Therefore:

```text
2 × 3 = 6
```

Final answer:

```text
6
```

---

# 📊 Stack Thinking

For:

```text
(()(()))
```

The important stack states are:

```text
[0]
      ↓
[0,0]
      ↓
[0,1]       // ()
      ↓
[0,1,0]
      ↓
[0,1,0,0]
      ↓
[0,1,1]     // inner ()
      ↓
[0,3]       // (()) = 2, added to previous 1
      ↓
[6]         // outer parentheses
```

The critical transition is:

```text
[0,1,1]
```

The top `1` belongs to `(())`.

It gets converted:

```text
1 → 2 × 1 → 2
```

Then that `2` is added to the previous `1`:

```text
1 + 2 = 3
```

giving:

```text
[0,3]
```

Then:

```text
3 → 2 × 3 → 6
```

---

# 🧩 Mental Model

Think of the stack as **score buckets**.

```text
Outer level
    ↓
[ 0 ]

Nested level
    ↓
[ 0, 0 ]

Another nested level
    ↓
[ 0, 0, 0 ]
```

When a level closes:

1. Take its accumulated score.
2. Remove that level.
3. Convert the score according to the parentheses rule.
4. Add the resulting score to the parent level.

---

# ⚡ The Three Rules to Memorize

Everything comes from these:

### 1. Empty pair

```text
() → 1
```

### 2. Nested pair

```text
(A) → 2 × A
```

### 3. Adjacent groups

```text
AB → A + B
```

If you understand these three rules, the entire problem becomes straightforward.

---

# 🚨 Common Mistakes

## 1. Using `0` as the score of `()`

Wrong concept:

```text
() → 0
```

Correct:

```text
() → 1
```

`0` is useful as a **new level marker**, not as the score of an empty pair.

---

## 2. Forgetting to add to the parent

After calculating a nested group's score, don't treat it as completely separate.

For:

```text
()()
```

you need:

```text
1 + 1
```

not just the second `1`.

---

## 3. Multiplying every group by 2

Only **nesting** causes multiplication.

```text
() → 1
```

but:

```text
(()) → 2
```

and:

```text
((())) → 4
```

Each additional enclosing level doubles the score.

---

## 4. Confusing concatenation with nesting

These are different:

```text
()()
```

means:

```text
1 + 1 = 2
```

while:

```text
(())
```

means:

```text
2 × 1 = 2
```

Same answer here, but for larger expressions the distinction becomes crucial.

---

# 💡 Useful Shortcut

A primitive pair:

```text
()
```

at nesting depth `d` contributes:

```text
2^(d-1)
```

For example:

```text
()       → 1
(())     → 2
((()))   → 4
(((()))) → 8
```

This gives another way to understand why nesting causes powers of two.

---

# 🧠 Interview/Contest Trick

When you see a problem involving:

- Nested structures
- Matching opening/closing symbols
- Results that depend on nesting depth
- Independent groups that need combining

Immediately consider:

> **Stack + one value per nesting level**

Instead of storing only the brackets, ask:

> **"What information should each level remember?"**

For this problem, the answer is:

> **The accumulated score of that level.**

That's the key abstraction.

---

# ⏱️ Complexity

### Time

**O(n)**

Every parenthesis is processed once.

### Space

**O(n)** worst case.

This happens when the parentheses are completely nested, such as:

```text
((((((...))))))
```

---

# 🎯 Final Takeaway

Don't think:

> "I need to find matching brackets."

Think:

> **"Every pair creates a score, and nesting transforms that score while concatenation adds scores."**

The stack simply keeps track of the score belonging to each nesting level.

### One-line memory trick

> **`()` gives 1, wrapping doubles, neighboring groups add.**
