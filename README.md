# Philosophers

A multithreaded simulation of the classic dining philosophers concurrency problem.

## Overview

This project simulates philosophers seated at a round table sharing forks while cycling through eating, sleeping, and thinking states. Each philosopher needs two forks to eat and must avoid starvation within a time limit. The simulation ends either when a philosopher dies or when all philosophers reach their meal quota.

## Problem Description

- Philosophers share a table with one fork between each plate
- Each philosopher needs two forks to eat
- Philosophers alternate between thinking, eating, and sleeping
- Philosophers must eat within a time limit to avoid death
- Philosophers can only use forks adjacent to their plate
- Forks cannot be duplicated

## Usage

First, make the program.
```bash
make all
```
Then, run the program with plugged in parameters: (number of philosophers, time to die, time to eat, time to sleep, and OPTIONAL meals required)
```bash
./philo [philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [meals_to_eat]
```

Parameters:
- `philosophers`: Number of philosophers (max 200)
- `time_to_die`: Milliseconds until starvation
- `time_to_eat`: Milliseconds to complete a meal
- `time_to_sleep`: Milliseconds spent sleeping
- `meals_to_eat`: (Optional) Number of meals required for simulation success

### Examples
```bash
./philo 10 300 70 70 5    # Peaceful end - all philosophers eat 5 meals
./philo 10 200 150 150    # Death scenario - insufficient time for fork rotation
```

## Output Format
```
[timestamp_in_ms] X is eating
[timestamp_in_ms] X is sleeping
[timestamp_in_ms] X is thinking
[timestamp_in_ms] X died
```

## Key Concepts
- Multithreading
- Mutex synchronization
- Race condition prevention
- Resource sharing algorithms
