
---

# Philosophers

![Statut du projet](https://img.shields.io/badge/statut-compl%C3%A9t%C3%A9-4caf50)
![Notions](https://img.shields.io/badge/notions-threads%2C%20mutex%2C%20synchronisation-007ec6)

## Description (FR)

**Manger, Dormir, Spaghetti, Répéter**  
Ce projet consiste à gérer les comportements de philosophes autour d’une table en utilisant des "threads". 
Parmi un groupe de philosophes, l'objectif est de déterminer précisément quand chaque philosophe doit prendre des fourchettes pour manger des spaghettis, sans que l'un d'eux ne meure de faim.
Pour ce projet, nous devons apprendre la programmation concurrente, nous devons résoudre le problème en utilisant uniquement des threads et des mutex.

### Le sujet décrit le problème comme suit :

- Un ou plusieurs philosophes sont assis autour d’une table ronde.
- Un grand bol de spaghetti est placé au centre de la table.
- Les spaghettis ne peuvent être mangés qu’avec deux fourchettes.
- Il y a autant de fourchettes que de philosophes.
- Chaque philosophe mange, dort, et pense successivement.
- Si un philosophe ne mange pas dans un certain délai, il mourra de faim.
- Les philosophes ne peuvent pas communiquer entre eux.

## Objectifs

- Comprendre les bases des threads et des mutex.
- Apprendre à synchroniser des threads pour éviter les "data races".
- Créer une simulation en C en respectant les normes de 42.

## Compilation

Pour compiler le projet, utilisez la commande suivante dans le répertoire `philo` :

```bash
$ make
```

## Exécution

Le programme prend les arguments suivants :

```bash
$ ./philo <nombre_de_philosophes> <temps_avant_mort> <temps_pour_manger> <temps_pour_dormir> [nombre_de_repas]
```

- **nombre_de_philosophes** : Nombre de philosophes autour de la table.
- **temps_avant_mort** : Temps (en millisecondes) avant qu'un philosophe ne meure de faim s’il ne mange pas.
- **temps_pour_manger** : Temps que prend un philosophe pour manger.
- **temps_pour_dormir** : Temps que prend un philosophe pour dormir.
- **nombre_de_repas** *(optionnel)* : Nombre de fois que chaque philosophe doit manger. La simulation se termine si tous les philosophes atteignent ce nombre.

---


# Philosophers

![Statut du projet](https://img.shields.io/badge/statut-compl%C3%A9t%C3%A9-4caf50)
![Notions](https://img.shields.io/badge/notions-threads%2C%20mutex%2C%20synchronisation-007ec6)

## Description (EN)

**Eat, Sleep, Spaghetti, Repeat**  
This project involves managing the behaviors of philosophers sitting at a round table using threads. Among a group of philosophers, the goal is to determine precisely when each philosopher should pick up forks to eat spaghetti, ensuring none starve.

### The subject describes the problem as follows:

- One or more philosophers sit at a round table.
- There is a large bowl of spaghetti in the middle of the table.
- The spaghetti can only be eaten with two forks.
- There are only as many forks as there are philosophers.
- Each philosopher successively eats, sleeps, and thinks.
- If a philosopher hasn't eaten in a certain timeframe, he will die of starvation.
- Philosophers cannot communicate with each other.

## Goals

- Learn the basics of threads and mutexes.
- Understand thread synchronization to avoid data races.
- Create a simulation in C following the 42 Norm.

## Compilation

To compile the project, use the following command in the `philo` directory:

```bash
$ make
```

## Execution

The program takes the following arguments:

```bash
$ ./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_meals]
```

- **number_of_philosophers**: Number of philosophers around the table.
- **time_to_die**: Time (in milliseconds) a philosopher can survive without eating.
- **time_to_eat**: Time it takes for a philosopher to eat.
- **time_to_sleep**: Time a philosopher spends sleeping.
- **number_of_meals** *(optional)*: Number of times each philosopher must eat. The simulation ends if all philosophers have eaten this number.

---
