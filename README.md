# **philosopher**
School project 9

## **Description**
This project aims to teach about: multithreading, data race, synchronization, and deadlock.
Here are the rules:

- One or more philosophers sit at a round table.
There is a large bowl of spaghetti in the middle of the table.
- The philosophers alternatively eat, think, or sleep.
While they are eating, they are not thinking nor sleeping;
while thinking, they are not eating nor sleeping;
and, of course, while sleeping, they are not eating nor thinking.
- There are also forks on the table. There are as many forks as philosophers.
- Because serving and eating spaghetti with only one fork is very inconvenient, a
philosopher takes their right and their left forks to eat, one in each hand.
- When a philosopher has finished eating, they put their forks back on the table and
start sleeping. Once awake, they start thinking again. The simulation stops when
a philosopher dies of starvation.
- Every philosopher needs to eat and should never starve.
- Philosophers don’t speak with each other.
- Philosophers don’t know if another philosopher is about to die.
- No need to say that philosophers should avoid dying

## **How to run**
clone this repository in your computer and open it
```
git clone https://github.com/greedymelon/philosophers.git; cd philosophers
```
then ```make`` the program
run
```./philo``` with 4 or 5 parameters in this order:

1. number_of_philosophers: The number of philosophers (max 200)
2. time_to_die (in milliseconds): If a philosopher didn’t start eating time_to_die
milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
3. time_to_eat (in milliseconds): The time it takes for a philosopher to eat.
4. time_to_sleep (in milliseconds): The time a philosopher will spend sleeping.
5. number_of_times_each_philosopher_must_eat (optional argument): If all
philosophers have eaten at least number_of_times_each_philosopher_must_eat
times, the simulation stops. If not specified, the simulation stops when a
philosopher dies.

example
```./philo 50 410 200 200```
no philosophers should die;

# **Challenges**
**Data races:** writing on a shared variable. In my case: the variable that keeps track of if a philosopher died, and the variable that keeps track of eating times.<br>
**Deadlock:** two threads waiting for the same resource, that it's never released. In my case: none.
**Synchronization:** threads not synchronized well. In my case uneven N of philosophers, the last one was not able to eat in time.
