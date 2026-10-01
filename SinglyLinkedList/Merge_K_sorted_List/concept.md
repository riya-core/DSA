# LeetCode 23 — Merge K Sorted Lists

## 1. Core idea

We are given `k` individually sorted linked lists. The goal is to combine them into one sorted linked list.

Because every input list is already sorted, the next node in the final answer must be the smallest node among the **current, unprocessed heads** of all lists.

A min-priority queue helps us repeatedly find that smallest current node efficiently.

## 2. The priority queue's job

Think of the priority queue as a waiting room containing one candidate node from each non-empty list.

- Initially, put the head node of every non-empty list into the queue.
- The smallest value is at the top.
- Take that node for the answer.
- If that node has a successor, add the successor to the queue.
- Repeat until the queue is empty.

### Why only one node per list?

Each list is already sorted. If a list's current node is the smallest candidate, its successor cannot be smaller than it. Therefore, we only need to reveal the successor after taking the current node.

This keeps the queue focused on the next possible answer from each list rather than storing every node at once.

## 3. What is stored in the queue?

Each queue entry contains two pieces of information:

- **Value:** used to order the candidates by their node values.
- **Node pointer:** the address of the actual linked-list node.

The value helps the priority queue decide which entry comes first. The pointer lets us reach the real node and its successor.

The pointer is not the node itself, and removing a pointer from the queue does not delete the node it points to.

## 4. Min-heap and ordering

A C++ `priority_queue` is a max-heap by default: the largest element is at the top.

For this problem, we need a min-heap so that the smallest value is at the top. A comparator such as `greater` can provide min-heap ordering for suitable comparable types.

When entries are pairs, the default pair comparison is lexicographical:

1. Compare the first fields.
2. If those are equal, compare the second fields.

So a pair containing a value and a node pointer uses the value first. If two values tie, the pointer fields may be compared as a tie-breaker. The pointer tie-breaker is not needed for the algorithm's logic; the important requirement is that the smallest node value is available at the top.

## 5. Pointer, reference, and queue entry — the crucial distinction

These are three different ideas:

- **Queue entry:** the pair currently stored inside the priority queue.
- **Pointer:** the address of a linked-list node, stored inside that pair.
- **Reference:** another name for an existing object, such as the pair returned by the queue's `top` operation.

The queue's `top` operation gives access to its top entry by reference. If a reference is bound to a field inside that entry, it is tied to the queue's storage—not to the lifetime of the linked-list node.

### What happens when an entry is popped?

Popping removes the top queue entry. It does **not** delete the linked-list node addressed by the pointer.

However, references to the removed queue entry become invalid. Using such a reference after popping is undefined behavior.

### What about pushing before popping?

A push can rearrange or reallocate the priority queue's underlying storage. Consequently, references to its elements should not be relied on across a push.

**Safe rule:** copy the top pair into local variables before modifying the queue. The copied node pointer remains usable as long as the linked-list node itself is still alive. Then pop the queue entry and use the copied pointer to inspect or enqueue the successor.

This is a general C++ lifetime and reference-validity rule, not a special property of linked lists.

## 6. Why the order of operations matters

Conceptually, one iteration does the following:

1. Read and **copy** the smallest queue entry.
2. Remove that entry from the queue.
3. Attach its node to the answer list.
4. If that node has a successor, insert the successor as a new candidate.
5. Continue with the new smallest candidate.

The key is to preserve the node pointer independently before removing or rearranging queue entries.

The exact order of linking and queue operations can vary, but never use a reference to a queue entry after an operation that may invalidate it.

## 7. Building the answer list

Maintain two pointers:

- **Head of the answer:** remembers the first node in the merged list.
- **Tail of the answer:** remembers the last node, so the next selected node can be attached efficiently.

When the first node is selected, initialize both pointers to it. For later nodes, connect the current tail to the selected node and move the tail forward.

It is good practice to ensure the tail's `next` pointer is null after attaching a node. This avoids accidentally retaining an old link, particularly when the input nodes are reused rather than copied.

## 8. Why the algorithm works

At every stage, the queue contains the smallest unprocessed candidate from each non-empty list.

Because each input list is sorted, every unprocessed node in a list is at least as large as that list's current candidate. Therefore, the smallest candidate across all lists is also the smallest unprocessed node overall.

Taking that candidate next is correct. Adding its successor maintains the same property for the next iteration.

When the queue becomes empty, all nodes have been processed.

## 9. Complexity

Let:

- `N` be the total number of nodes across all lists.
- `k` be the number of input lists.

Each node is inserted into and removed from the priority queue at most once. The queue holds at most `k` candidates at a time.

- **Time:** `O(N log k)`
- **Auxiliary queue space:** `O(k)`
- **Extra linked-list node allocation:** none is required if the original nodes are relinked.

The answer list reuses the input nodes, so the queue is the main extra data structure.

## 10. Tips and common pitfalls

- **Skip empty lists.** Never insert a null node as if it were a valid candidate.
- **Use a min-heap.** A default max-heap would process the largest candidate first.
- **Copy before modifying the queue.** Avoid holding references to `top()` across a `pop()` or `push()`.
- **A pointer is not ownership.** Popping a pointer from the queue does not free the node.
- **Enqueue only the successor of the node just selected.** Do not add every node from that list in advance.
- **Be careful with equal values.** Duplicate values are valid; they do not mean a node should be skipped.
- **Preserve the answer head.** Moving the tail must not lose the pointer to the beginning of the merged list.
- **Avoid stale links.** When relinking existing nodes, ensure the final tail does not retain a link to an already-connected portion of an input list.
- **Do not confuse the queue's order with list order.** The queue orders the current candidates; each linked list retains its own successor links.
- **Trace pointers, not just values.** When debugging, track which list each candidate came from and which node its pointer addresses.

## 11. Mental model to remember

Imagine `k` sorted queues of people, with each queue showing only its first person. Choose the person with the smallest number, move them into the final line, and then reveal the next person from that same queue.

The priority queue chooses the next candidate. The linked-list pointers connect the actual nodes. Keeping those responsibilities separate makes the algorithm—and its C++ reference rules—much easier to reason about.
"""
