# ⛽ LeetCode 134 — Gas Station

## 1. Problem in One Line

You have a circular sequence of gas stations.

At station `i`:

* You gain `gas[i]` fuel.
* You spend `cost[i]` fuel to travel to the next station.

Find a starting station from which you can travel through **every station exactly once and return to the starting station** without your fuel ever becoming negative.

If impossible → return `-1`.

---

# 2. The Most Important Transformation

Instead of thinking separately about:

```text
gas[i]
cost[i]
```

think about the **net fuel change**:

```text
net[i] = gas[i] - cost[i]
```

This tells us what happens to our fuel after leaving station `i`.

| `net[i]` | Meaning   |
| -------- | --------- |
| `> 0`    | Gain fuel |
| `= 0`    | No change |
| `< 0`    | Lose fuel |

So the problem becomes:

> Find a starting position from which the running sum of `net[i]` never becomes negative while completing the circle.

This transformation is the key to the entire problem.

---

# 3. Think of Fuel as a Running Balance

Imagine:

```text
net = [4, -6, 3, 2, -1]
```

Starting from index `0`:

```text
fuel = 4
fuel = 4 - 6 = -2  ❌
```

We failed.

The important question is not:

> "Which station has the most gas?"

Instead ask:

> "From which position can my cumulative fuel stay ≥ 0?"

This distinction is the heart of the problem.

---

# 4. Why Maximum Gas Is NOT the Strategy

A common first thought is:

> "Start from the station having maximum gas."

This is tempting, but it is not the actual condition.

A station may have a lot of gas but be followed by several stations with very large costs.

Similarly:

> "Start from the station with minimum cost."

also isn't sufficient.

The correct criterion is **cumulative feasibility**, not the value of one individual station.

### Remember:

```text
Individual value ≠ Starting-point quality
```

The starting point depends on the **entire sequence after it**.

---

# 5. The Brute-Force Idea

The most obvious solution is:

```text
Try station 0
    → travel around the circle

Try station 1
    → travel around the circle

Try station 2
    → travel around the circle

...
```

For every starting station, you may need to inspect almost every station.

Therefore:

```text
n starting points × n stations
= O(n²)
```

This works conceptually, but there is a much better observation.

---

# 6. The Greedy Observation 🔥

Suppose we start at station `S`.

While travelling:

```text
fuel += net[i]
```

Eventually we reach station `i` and:

```text
fuel < 0
```

That means:

> Starting from `S`, we cannot even survive until station `i + 1`.

Now comes the important part.

## Why can we skip all stations between `S` and `i`?

Suppose we had:

```text
S → S+1 → S+2 → ... → i
```

and starting from `S` resulted in a negative balance at `i`.

Every possible starting point between `S` and `i` would have to deal with the same problematic portion.

The earlier starting point has already accumulated the net contribution of the previous stations.

If even that accumulated balance is insufficient, choosing a later point cannot magically make the entire failed segment feasible.

Therefore:

```text
S, S+1, S+2, ... , i
```

can all be rejected.

So we jump directly to:

```text
i + 1
```

🔥 **This is the main greedy step.**

---

# 7. The Greedy Pattern

The mental process is:

```text
Choose a candidate start
        ↓
Accumulate balance
        ↓
Balance becomes negative?
        ↓
YES
        ↓
Current start is impossible
        ↓
Everything up to failure point is impossible
        ↓
Jump to next station
```

Instead of repeatedly testing candidates, we **eliminate entire groups of candidates at once**.

That's why we get:

```text
O(n)
```

instead of:

```text
O(n²)
```

---

# 8. The Global Feasibility Condition

There is one separate condition.

Calculate:

```text
total = Σ(gas[i] - cost[i])
```

If:

```text
total < 0
```

then the answer is definitely:

```text
-1
```

Why?

Because after completing the entire circle:

```text
total fuel gained < total fuel required
```

There simply isn't enough fuel in the entire system.

No starting point can fix that.

### Important distinction

There are actually **two balances** to think about:

### Local balance

```text
fuel
```

Used to determine:

> "Can my current starting point survive?"

### Global balance

```text
total
```

Used to determine:

> "Does the entire circle have enough fuel at all?"

---

# 9. The Two-Balance Mental Model

This is a very useful way to remember LC 134:

```text
                 GAS STATION
                      │
          ┌───────────┴───────────┐
          ↓                       ↓
     CURRENT FUEL              TOTAL FUEL
       `fuel`                    `total`
          │                       │
          ↓                       ↓
 Can current start survive?   Is solution possible?
          │                       │
       Negative?              Negative?
          │                       │
          ↓                       ↓
 Change start                  return -1
```

This makes the solution much easier to reconstruct.

---

# 10. Why Do We Reset Fuel?

When:

```text
fuel < 0
```

the current candidate has failed.

We choose a new candidate:

```text
start = i + 1
```

The old accumulated fuel is no longer relevant to the new starting point.

Therefore:

```text
fuel = 0
```

Now we start evaluating the new candidate independently.

---

# 11. Circular Nature of the Problem

The stations are arranged like:

```text
0 → 1 → 2 → 3 → 4
↑               ↓
└───────────────┘
```

So after the last station:

```text
n - 1
```

we go back to:

```text
0
```

The greedy traversal doesn't need to physically create:

```text
[0,1,2,3,4,0,1,2,3,4]
```

The global condition:

```text
total >= 0
```

combined with the greedy candidate selection handles the circular part.

---

# 12. The Deep Intuition

Think of every station as contributing a positive or negative value:

```text
+ = fuel gain
- = fuel loss
```

The problem becomes:

> Find a point in a circular array from which the cumulative sum never goes below zero.

This is closely related to **prefix sums**.

For example:

```text
net = [2, -4, 3, 4, -2]
```

The running balance from some starting point tells us whether that point is viable.

The greedy algorithm essentially finds a position **after a problematic prefix/segment**.

---

# 13. A Useful Mathematical View

Let:

```text
net[i] = gas[i] - cost[i]
```

Then the journey is possible only if:

```text
Σ net[i] >= 0
```

If the total is non-negative, there is at least one valid starting point.

The greedy algorithm finds such a point by repeatedly discarding starting positions that are proven impossible.

So the solution is based on:

```text
Global feasibility
+
Local failure detection
+
Candidate elimination
```

---

# 14. How to Identify This Type of Greedy Problem 🧠

When solving DSA, look for these signals.

## Signal 1 — "Find a starting point"

Words like:

* Find a starting position
* Choose a starting index
* Where should we begin?
* Find a valid starting point

should make you think:

> "Can I eliminate bad starting points instead of testing all of them?"

---

## Signal 2 — Circular Array

If you see:

```text
last → first
```

immediately think about:

* total balance
* prefix sums
* greedy
* modulo/index wrapping
* feasibility conditions

---

## Signal 3 — Net Gain / Net Loss

If the problem contains:

```text
gain
cost
profit
loss
available
required
```

try:

```text
gain - cost
```

This often collapses the problem into a much simpler form.

---

## Signal 4 — Running Balance

If something says:

> You can continue only while your balance doesn't become negative.

Think:

```text
running sum
```

Examples:

```text
fuel
money
energy
health
resources
inventory
```

Often:

```text
balance += gain - loss
```

---

## Signal 5 — A Failure Lets You Eliminate Candidates

This is the **big greedy signal**.

Ask yourself:

> "If candidate X fails here, can I prove that candidates X+1 ... i are also impossible?"

If YES:

🔥 You may have found a greedy solution.

This is much more important than simply noticing that the problem "looks greedy."

---

# 15. Greedy Proof Pattern to Remember

Whenever you think:

> "I'll skip all these candidates."

STOP.

Ask:

### Can I prove they are impossible?

For LC 134:

```text
Current start → ... → failure point
```

If cumulative fuel becomes negative at the failure point, none of the stations inside that failed segment can be a valid starting point.

Therefore skipping them is safe.

That proof is what makes the greedy algorithm correct.

---

# 16. Common Wrong Approaches

### ❌ Start at maximum gas

Not sufficient.

### ❌ Start at minimum cost

Not sufficient.

### ❌ Start at maximum `gas[i] - cost[i]`

Still not generally the correct reasoning.

### ❌ Try every station

Correct but:

```text
O(n²)
```

### ❌ Only check total gas

Not enough.

For example:

```text
gas total >= cost total
```

tells us that a solution exists, but does **not directly tell us which station to start from**.

---

# 17. The Three Questions to Ask in Similar Problems

When you see a problem like this, ask:

### Q1. Can I convert the problem into a net change?

```text
gain - cost
```

### Q2. Can I maintain a running balance?

```text
balance += net
```

### Q3. When a candidate fails, can I eliminate multiple candidates?

```text
failure → discard a whole range
```

If all three answers are YES:

🚨 **Strong greedy candidate.**

---

# 18. Complexity Insight

### Brute force

```text
Try every start
    ↓
Traverse the circle
```

Time:

```text
O(n²)
```

### Greedy

```text
One traversal
+
Candidate elimination
```

Time:

```text
O(n)
```

Extra space:

```text
O(1)
```

You don't even need to construct the `net` array.

---

# 19. Memory Trick 🧠

Remember LC 134 as:

> **"Negative balance kills the current segment, not just the current station."**

And:

> **"Total negative → nobody can win."**

So:

```text
LOCAL NEGATIVE
    ↓
change starting point

GLOBAL NEGATIVE
    ↓
return -1
```

That's basically the entire conceptual skeleton of the problem.

---

# ⚡ DSA Pattern Cheat Sheet

| If you see...                       | Think...                            |
| ----------------------------------- | ----------------------------------- |
| Gain − Cost                         | Net balance                         |
| Running resource                    | Prefix/running sum                  |
| Circular journey                    | Total balance + greedy              |
| Find starting point                 | Candidate elimination               |
| Candidate fails                     | Can later candidates be eliminated? |
| Failure at `i` invalidates a range  | Greedy                              |
| Need to try every start             | Look for an elimination rule        |
| Total resources < total requirement | Impossible globally                 |
| Local balance < 0                   | Current candidate failed            |

---

## Final Mental Model

Don't memorize:

```text
start = i + 1
```

Memorize **why**:

```text
I started here
      ↓
I accumulated fuel
      ↓
fuel became negative
      ↓
this journey cannot survive
      ↓
the entire segment I used to reach this failure
cannot be a valid starting segment
      ↓
jump past it
```

That's the actual LC 134 trick.

**The code is tiny because the observation is the hard part.** 🚀
