# LeetCode 32 — Longest Valid Parentheses

> **Goal:** Find the length of the longest contiguous substring that forms valid, correctly matched parentheses. Return the length, not the substring itself.

## 1. Core Concepts

### Valid parentheses
- Every opening parenthesis `(` must have a matching closing parenthesis `)`.
- A closing parenthesis must never appear before its matching opening parenthesis.
- The order matters: equal counts alone do not guarantee validity.
- The answer is a **substring**, so the characters must be contiguous. It is not a subsequence.

### Balance / counter
- Treat `(` as **+1** and `)` as **−1**.
- A balance of zero means the number of opening and closing parentheses seen so far is equal.
- A negative balance means a closing parenthesis appeared without a usable opening parenthesis in the current scan segment. The current segment cannot include that closing parenthesis as part of a valid substring.
- A positive balance at the end of a left-to-right scan means some opening parentheses remain unmatched. It does **not** mean that no valid substring occurred inside the segment.

### Boundaries and indices
- Keep track of where a candidate valid segment begins.
- If the balance becomes negative, the next possible segment must begin after the invalid closing parenthesis.
- For a valid segment ending at index `i` and beginning at index `start`, its length is `i - start + 1`.
- Be careful about inclusive indices: the `+1` is necessary when calculating length from a start index.

## 2. Counter-Based Scan: Tips and Tricks

### Left-to-right scan
- Increment the opening count for `(` and the closing count for `)`.
- When the counts are equal, the current segment is valid; its length is twice either count.
- If closing parentheses outnumber opening parentheses, reset both counts. No valid substring can cross that invalid closing parenthesis in this scan direction.
- **Important limitation:** a left-to-right counter scan can miss valid substrings when extra opening parentheses remain unmatched. For example, a segment may begin with an extra `(` but contain a valid pair later.

### Right-to-left scan
- Scan in the opposite direction to handle the unmatched-opening case.
- When opening parentheses outnumber closing parentheses during this reverse scan, reset both counts.
- When the counts are equal, update the maximum length.
- The reverse pass complements the forward pass; it is not redundant.

### Reset rule to remember
- Forward scan: reset when **closing > opening**.
- Reverse scan: reset when **opening > closing**.
- Do not reset just because the balance is positive in the forward scan; a valid substring may still appear later in the same segment.

## 3. Stack-of-Indices Approach: Tips and Tricks

- Store **indices**, not the literal parenthesis characters. Indices let you calculate lengths directly.
- A sentinel index of `-1` represents the boundary immediately before the string begins.
- On `(`, push its index.
- On `)`, pop once to attempt to match the most recent opening parenthesis.
- If the stack becomes empty after popping, the current closing parenthesis is unmatched. Push its index as the new invalid-segment boundary.
- Otherwise, the current valid suffix length is the current index minus the index at the top of the stack.
- The top index can represent either an unmatched opening parenthesis or a boundary. Its meaning follows from the algorithm's push/pop rules.
- Do not clear the entire stack whenever a pair is matched. Remove only the relevant top entry; preserve earlier indices that define the boundary.

## 4. Why a Single Counter Can Fail

- Equal counts are necessary for a valid substring, but not sufficient unless the scan has also respected the correct order and segment boundary.
- A prefix with more closing than opening parentheses is invalid and requires a reset for that scan direction.
- A prefix with more opening than closing parentheses may still contain a valid substring later in the segment.
- Unmatched opening parentheses at the end do not tell you to discard the entire segment. Valid substrings may exist between unmatched openings.
- If you want a one-pass solution, use the stack-of-indices method. If you want a constant-extra-space counter solution, use two directional scans.

## 5. Common Pitfalls

- **Confusing substring and subsequence:** characters cannot be skipped.
- **Returning the count instead of the length:** the answer counts characters, so each matched pair contributes two characters.
- **Forgetting the sentinel:** without a boundary index, calculating a valid length that starts at index `0` becomes awkward.
- **Resetting at the wrong time:** only reset when the current scan direction has too many of its invalidating parenthesis type.
- **Handling only one direction with counters:** this misses cases with unmatched opening parentheses.
- **Using the wrong length formula:** index-based inclusive segments use `end - start + 1`; stack boundaries commonly use `current_index - boundary_index`.
- **Assuming a zero balance proves validity:** the segment must also have remained valid with respect to the scan's boundary rules.
- **Trying to repair everything only at the end:** maintain enough boundary information during the scan to calculate candidate lengths correctly.

## 6. Complexity Cheatsheet

| Approach | Time | Extra space | Main trade-off |
|---|---:|---:|---|
| Two directional counter scans | O(n) | O(1) | Space-efficient, but requires two passes |
| Stack of indices | O(n) | O(n) | One pass; boundary logic is explicit |

Here, `n` is the length of the string.

## 7. Edge Cases to Test

- Empty string: answer is zero.
- One parenthesis only: answer is zero.
- All opening parentheses: answer is zero.
- All closing parentheses: answer is zero.
- A simple matched pair: answer is two.
- A valid substring preceded by an unmatched closing parenthesis.
- A valid substring followed by an unmatched opening parenthesis.
- Extra opening parentheses before a valid pair.
- Nested valid parentheses.
- Several valid groups separated by an invalid parenthesis.
- A valid substring that begins after index zero.
- The entire string is valid.

## 8. Quick Mental Checklist

Before submitting, ask:

1. Am I finding a **contiguous substring**?
2. Do I update the maximum whenever a valid candidate is identified?
3. Does my reset rule match the scan direction?
4. Have I handled both unmatched closing and unmatched opening parentheses?
5. If using a stack, do I preserve the correct boundary index?
6. Are my length calculations consistent with whether the boundary is included or excluded?
7. Have I tested the empty string and strings with unmatched parentheses?

## 9. Interview Takeaway

The central challenge is not counting parentheses; it is tracking **where a valid substring can begin**. Counters summarize balance, while indices preserve boundaries. Choose the counter method for constant auxiliary space and the stack method when you want direct, one-pass boundary tracking.
