<div align="center">
  <picture>
    <img src="https://github.com/ayogun/42-project-badges/blob/main/badges/philosophersm.png" alt="42 The Philosophers school project badge">
  </picture>

  <p><a href="https://www.hive.fi/en/curriculum">Hive (42 School Network)</a> core curriculum project</p>
  <h1>Philosophers</h1>
</div>

**Philosophers** is a concurrency-oriented C project inspired by the classic “Dining Philosophers” problem. The focus lies on using **threads** and **mutex locks** to manage resource sharing and avoid concurrency hazards like race conditions and deadlocks.

---

##  Highlights: Threads & Mutex

- **Multithreading with `pthread`**: Each philosopher is implemented as a separate thread, enabling parallel execution.
- **Mutex synchronization**: Each fork (shared resource) is protected by a `pthread_mutex_t`. Mutex locks prevent multiple philosophers from picking the same fork simultaneously, thereby avoiding race conditions.
- **Deadlock prevention**:
  - Enforce a consistent fork-acquisition order (e.g., odd vs even philosophers pick forks in different sequences).
  - Optionally implement a central arbitrator (“waiter”) or resource hierarchy to break circular waiting.
- **Lifecycle monitoring**: Regular status checks (e.g., death detection, completion of required eating cycles) ensure graceful termination and cleanup.

---

##  Project Structure

```
philosophers/
├── include/
│   └── philosophers.h     # Shared data structures & definitions
├── src/
│   ├── main.c             # Argument parsing & program startup
│   ├── init.c             # Setup threads & mutexes
│   ├── actions.c          # Philosopher routines: thinking, eating, sleeping
│   ├── monitor.c          # Monitor thread: check for death or end conditions
│   └── cleanup.c          # Thread joining and resource cleanup
├── Makefile               # Build instructions
└── README.md              # Project documentation
```

---

##  How to Use

### 1. Clone the repository
```bash
git clone https://github.com/Lin-0096/42-rank3-philosophers.git
cd 42-rank3-philosophers
```

### 2. Build the project
```bash
make
```

### 3. Run the simulation
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_must_eat]
```

**Example:**
```bash
./philo 5 800 200 200
# 5 philosophers, time_to_die=800ms, time_to_eat=200ms, time_to_sleep=200ms
```

---

##  Learning Outcomes

- Mastered **pthread** usage: thread creation (`pthread_create`), synchronization (`pthread_mutex_*`), and cleanup (`pthread_join`, `pthread_mutex_destroy`).
- Tackled **race conditions** and ensured safe resource access via **mutexes**.
- Implemented strategies to prevent **deadlocks** and ensure fairness.
- Developed insight into **timing constraints**, **monitoring**, and **graceful shutdown** in concurrent systems.
