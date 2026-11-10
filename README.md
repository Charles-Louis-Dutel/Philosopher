# Philosophers — École 42

Projet développé en **C** dans le cadre du cursus de l'école 42.

L'objectif est de résoudre le problème classique du **dîner des philosophes**, utilisé pour illustrer les difficultés de synchronisation entre plusieurs processus d'exécution concurrents.

Ce projet permet d'approfondir la programmation multithread, la gestion des ressources partagées et les mécanismes de synchronisation.

## Fonctionnalités

- Simulation de plusieurs philosophes exécutés dans des threads distincts.
- Gestion du cycle de vie des philosophes : manger, dormir et réfléchir.
- Utilisation de mutex pour synchroniser l'accès aux fourchettes.
- Gestion des ressources partagées et prévention des accès concurrents non synchronisés.
- Surveillance du temps écoulé depuis le dernier repas de chaque philosophe.
- Détection de la mort d'un philosophe et arrêt de la simulation.
- Gestion des paramètres de simulation : nombre de philosophes, temps de survie, durée des repas et du sommeil.

## Compétences mises en œuvre

- Programmation en C
- Programmation multithread avec POSIX Threads (`pthread`)
- Synchronisation avec les mutex
- Gestion des ressources partagées
- Problèmes de concurrence et d'interblocage (*deadlock*)
- Gestion du temps et des événements
- Gestion de la mémoire et des ressources système

## Auteur

Charles-Louis Dutel — [GitHub](https://github.com/Charles-Louis-Dutel)
