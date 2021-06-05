# Isolation

Practice for a better understanding of the isolation levels mentioned in SQL.

Degree 0 - (skip)

Degree 1 - read uncommitted (done)

Degree 2 - read committed (skip, it is just the same with 2 version MVCC)

Degree 2.5 - snapshot isolation (done, using MVCC)
- MVCC implementation
- the lost update detection by MVCC (By serialization and no-wait policy)

Degree 3 - serializable (done, using 2PL)

the Phantom is not considered, since only the item read is considered.

# Reference Paper

《An Empirical Evaluation of In-Memory Multi-Version Concurrency Control》

《A Critique of ANSI SQL Isolation Levels》
