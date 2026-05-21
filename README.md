*This project has been created as part of the 42 curriculum by kesaitou.*

# Philosophers

## Description

`Philosophers` is a 42 concurrency project based on the classic dining
philosophers problem. The goal is to learn the basics of threading a process
by creating threads and using mutexes (mandatory part), and by using processes
and semaphores (bonus part), while building a race-free simulation in C.

In the simulation, one or more philosophers sit at a round table and
alternate between **eating**, **thinking**, and **sleeping**. There are as
many forks as philosophers, and a philosopher must hold both their left and
right fork to eat. The simulation ends when a philosopher dies of starvation,
or, if specified, when every philosopher has eaten a given number of times.

## Instructions

### Requirements

- A C compiler (`cc`) with POSIX thread support
- GNU `make`
- A Unix-like environment

### Compilation

Mandatory part:

```bash
cd philo
make
```

The `Makefile` provides the rules `all`, `clean`, `fclean`, and `re`.
The program is compiled with `-Wall -Wextra -Werror`.

### Execution

```text
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

| Argument                                    | Unit | Valid range            | Description                                                                                          |
| ------------------------------------------- | ---- | ---------------------- | ---------------------------------------------------------------------------------------------------- |
| `number_of_philosophers`                    | —    | `1` … `INT_MAX`        | Number of philosophers and forks                                                                     |
| `time_to_die`                               | ms   | `1` … `LONG_MAX`       | A philosopher dies if they have not started eating within this time since the start of their last meal |
| `time_to_eat`                               | ms   | `1` … `LONG_MAX`       | Time it takes for a philosopher to eat (holding two forks)                                           |
| `time_to_sleep`                             | ms   | `1` … `LONG_MAX`       | Time a philosopher spends sleeping                                                                   |
| `number_of_times_each_philosopher_must_eat` | —    | `1` … `LONG_MAX` (opt) | (Optional) Stop the simulation once every philosopher has eaten this many times                      |
|                                             |      |                        |                                                                                                      |

#### Behavior when boundaries are exceeded

Every argument is validated before the simulation starts. If any of the
following conditions is met, the program prints `Error` to standard error,
exits with status `1`, and **never spawns a thread**:

- The number of arguments is not 5 or 6.
- An argument contains non-digit characters (a leading `+` is accepted, `-` is not — negative values are rejected as non-numeric).
- An argument is empty or its numeric value overflows `LONG_MAX`.
- `number_of_philosophers` is `0` or greater than `INT_MAX`.
- `time_to_die`, `time_to_eat`, or `time_to_sleep` is `0` or negative.
- `number_of_times_each_philosopher_must_eat`, when supplied, is `0` or negative.

Notes on edge cases inside the valid range:

- `number_of_philosophers = 1`: only one fork is reachable, so the lone philosopher cannot eat and dies after `time_to_die` ms (this is the expected behavior, not an error).
- Very small `time_to_die` (e.g. `1`): the philosopher dies almost immediately. The subject still requires the death message to be printed within 10 ms of the actual death.
- Very large values (close to `LONG_MAX`): accepted by the parser, but the simulation runs in real time, so the program will simply run for an unreasonably long duration.

Examples:

```bash
./philo 5 800 200 200
./philo 5 800 200 200 7
./philo 1 800 200 200
./philo 4 310 200 100
```

The program prints each state change as `timestamp_in_ms X <state>`, where
`X` is the philosopher number. The simulation stops on the first death or
once the optional meal target has been reached.

## Resources

Classic references related to the topic:

- Dijkstra, *Cooperating Sequential Processes* (1965) — original dining philosophers problem.
- [Wikipedia — Dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- POSIX threads — [`pthread_create(3)`](https://man7.org/linux/man-pages/man3/pthread_create.3.html), [`pthread_mutex_lock(3p)`](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html)
- POSIX semaphores — [`sem_open(3)`](https://man7.org/linux/man-pages/man3/sem_open.3.html), [`sem_wait(3)`](https://man7.org/linux/man-pages/man3/sem_wait.3.html)

### AI usage

AI assistance was used for the following tasks only:

- Drafting and proofreading the wording of this `README.md`.