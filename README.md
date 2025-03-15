# Simulation des Algorithmes d'Ordonnancement avec Interface Qt

## Description

Ce projet implémente plusieurs algorithmes d'ordonnancement des processus pour la gestion du CPU dans un système d'exploitation, avec une interface graphique réalisée en **Qt**. Le projet vise à simuler et visualiser les comportements de différents algorithmes d'ordonnancement en temps réel, permettant une meilleure compréhension de leur fonctionnement.

Les algorithmes d'ordonnancement simulés sont :
- **PCTE (Priorité en Temps Critique et Exécution)** : L'ordonnancement des processus est basé sur leur priorité et leur durée d'exécution.
- **TOURNIQUE (Round-Robin)** : Chaque processus reçoit un quantum de temps fixe avant de passer au suivant.
- **FIFO (First In, First Out)** : Les processus sont exécutés dans l'ordre d'arrivée sans interruption.
- **PCTER (Priorité en Temps Critique et Exécution avec Rappel)** : Variante de PCTE avec gestion dynamique des priorités.
- **PRIORITÉ** : Les processus sont exécutés en fonction de leur priorité, du plus élevé au plus bas.
- **PRIORITÉ AVEC PRÉEMPTION** : L'algorithme PRIORITÉ mais avec préemption possible si un processus plus prioritaire arrive.

## Fonctionnalités

- Interface graphique avec **Qt** pour l'entrée et la visualisation des résultats.
- Simulation des algorithmes d'ordonnancement avec calcul automatique des temps d'attente, de réponse et de retour.
- Affichage graphique des processus en cours d'exécution et de l'état du CPU.
- Interaction facile avec les utilisateurs via des formulaires pour saisir les processus et leurs caractéristiques.
- Affichage des résultats sous forme de tableaux dans l'interface.

## Prérequis

- **Qt 5.15** ou version supérieure.
- Un compilateur C++ compatible (par exemple, **g++**, **clang++** ou **MSVC** pour Windows).
- **CMake** pour la gestion du projet (optionnel, selon votre configuration).

## Installation

### 1. Clonez ce repository :

```bash
git clone https://github.com/your-username/algorithmes-ordonnancement-qt.git
