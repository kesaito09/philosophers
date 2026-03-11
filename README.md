*This project has been created as part of the 42 curriculum by kesaitou.*

# Philosophers

## **Description**

`Philosophers` is the 42 concurrency project based on the dining philosophers problem.
The goal is to build a correct, race-free simulation in C while learning how to manage
threads, processes, mutexes, timing, and termination conditions.
It also provides a practical way to study deadlocks, starvation, and the trade-offs
required to coordinate concurrent workers safely.

This repository contains two implementations:

- `philo/`: mandatory part using POSIX threads and mutexes.
- `philo_bonus/`: bonus part using processes and semaphores.

Both programs receive the same rule set:

```text
number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

The simulation stops when a philosopher dies or, if the optional argument is provided,
when every philosopher has eaten enough times.

## **Instructions**

### Requirements

- A C compiler such as `cc`
- POSIX thread support
- A Unix-like environment

### Build

Build the mandatory program:

```bash
cd philo
make
```

Build the bonus program:

```bash
cd philo_bonus
make
```

Available Makefile targets in both directories:

```bash
make
make clean
make fclean
make re
```

### Run

Mandatory version:

```bash
./philo 5 800 200 200
./philo 5 800 200 200 7
```

Bonus version:

```bash
./philo_bonus 5 800 200 200
./philo_bonus 5 800 200 200 7
```

Argument meaning:

- `number_of_philosophers`: number of philosophers and forks
- `time_to_die`: maximum time in milliseconds a philosopher can stay without eating
- `time_to_eat`: eating duration in milliseconds
- `time_to_sleep`: sleeping duration in milliseconds
- `number_of_times_each_philosopher_must_eat`: optional stop condition

If the input is invalid, the program prints `Error` to standard error and exits.

## Architecture

From an architectural point of view, both parts solve the same domain problem: the
rules of the philosophers, eating, sleeping, thinking, death detection, and completion
conditions do not change between mandatory and bonus. Based on that observation, this
repository adopts an onion architecture approach. The domain layer is isolated around
the core simulation rules, while the outer layers change only the infrastructure and
coordination tools used to execute them. In practice, the main difference between the
two targets is how concurrency primitives are applied, not what the domain logic means.

The code is organized by responsibility in both `philo/` and `philo_bonus/`:

- `presentation/`: entry point, argument parsing, setup, cleanup
- `application/`: simulation flow, monitoring, orchestration
- `domain/`: philosopher behavior rules
- `infrastructure/`: time, logging, synchronization, low-level operations
- `include/`: public headers shared by the target

## **Resources**

Classic references related to the topic:

- POSIX threads manual pages: [`pthread_create(3)`](https://man7.org/linux/man-pages/man3/pthread_create.3.html), [`pthread_mutex_lock(3p)`](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3p.html)
- POSIX semaphores manual pages: [`sem_open(3)`](https://man7.org/linux/man-pages/man3/sem_open.3.html), [`sem_wait(3)`](https://man7.org/linux/man-pages/man3/sem_wait.3.html)
- Dining philosophers background: [Wikipedia - Dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
- Timing and process control references: [`gettimeofday(2)`](https://man7.org/linux/man-pages/man2/gettimeofday.2.html), [`fork(2)`](https://man7.org/linux/man-pages/man2/fork.2.html), [`waitpid(2)`](https://man7.org/linux/man-pages/man2/waitpid.2.html)

AI usage for this repository documentation:

- AI was mainly used to support code refactoring and to suggest a directory structure
  suitable for learning and applying the architecture used in this repository.
- AI was also used for README wording and organization so that this documentation
  matches the 42 `Readme Requirements`.
