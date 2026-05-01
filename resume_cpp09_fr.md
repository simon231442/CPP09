# C++ Module 09 - Fiche claire en français

Ce document reformule le sujet du module 09 pour aller droit à l’essentiel. L’objectif est de comprendre rapidement ce qu’il faut faire, sans relire tout l’énoncé à chaque fois.

## Rappels généraux du module

- Compilation avec `c++` et les flags `-Wall -Wextra -Werror`.
- Le code doit rester compatible avec `-std=c++98`.
- Le module 09 autorise l’utilisation de la STL.
- Chaque exercice doit utiliser au moins un conteneur, sauf l’exercice 02 qui en exige deux différents.
- Les conteneurs utilisés pour valider un exercice ne peuvent plus être réutilisés dans le reste du module.
- Les programmes doivent gérer les erreurs proprement avec des messages explicites.

## Exercice 00 - Bitcoin Exchange

### Ce qu’il faut faire

Créer un programme nommé `btc` qui lit un fichier fourni en argument.

Chaque ligne du fichier d’entrée doit avoir la forme suivante :

```text
date | value
```

Le programme doit :

- lire une base de données CSV contenant l’évolution du prix du bitcoin dans le temps ;
- récupérer pour chaque date la valeur correspondante dans la base ;
- multiplier la valeur donnée en entrée par le taux de change du jour ;
- afficher le résultat sur la sortie standard ;
- si la date n’existe pas exactement dans la base, utiliser la date la plus proche antérieure ;
- refuser les dates invalides et les valeurs hors limites.

### Contraintes importantes

- La date doit être au format `YYYY-MM-DD`.
- La valeur doit être un entier positif ou un flottant positif.
- La valeur doit rester comprise entre `0` et `1000`.
- Si le fichier ne peut pas être ouvert, il faut afficher une erreur.
- Si une ligne est invalide, il faut afficher un message adapté.

### Idée théorique utile

Le point clé de cet exercice est le repérage rapide d’une date dans une base triée.

- Un conteneur associatif comme `std::map` est très adapté.
- Comme le format de date est ISO (`YYYY-MM-DD`), la comparaison lexicographique fonctionne correctement.
- Pour trouver la date immédiatement inférieure, `lower_bound` ou une recherche équivalente est utile.
- Il faut aussi bien séparer le parsing, la validation et le calcul.

## Exercice 01 - Reverse Polish Notation

### Ce qu’il faut faire

Créer un programme nommé `RPN` qui prend en argument une expression écrite en notation polonaise inverse.

Le programme doit calculer l’expression et afficher le résultat sur la sortie standard.

Les opérateurs autorisés sont :

- `+`
- `-`
- `*`
- `/`

### Contraintes importantes

- Les opérandes reçus en entrée sont des chiffres strictement inférieurs à `10`.
- Les parenthèses ne sont pas à gérer.
- Les nombres décimaux ne sont pas à gérer.
- En cas d’erreur, il faut afficher `Error` sur la sortie d’erreur.
- Le programme doit rejeter les expressions mal formées.

### Idée théorique utile

La notation polonaise inverse se traite naturellement avec une pile.

- On lit l’expression de gauche à droite.
- Quand on voit un nombre, on l’empile.
- Quand on voit un opérateur, on dépile deux valeurs, on applique l’opération, puis on réempile le résultat.
- Une `std::stack` est le conteneur classique pour ce genre de traitement.
- Il faut vérifier les cas d’erreur : pile insuffisante, division par zéro, données résiduelles à la fin.

## Exercice 02 - PmergeMe

### Ce qu’il faut faire

Créer un programme nommé `PmergeMe` qui trie une suite d’entiers positifs reçue en argument.

Le tri imposé est le merge-insert sort, aussi connu comme l’algorithme de Ford-Johnson.

Le programme doit afficher :

- la suite d’entrée non triée ;
- la suite triée ;
- le temps de tri mesuré avec le premier conteneur ;
- le temps de tri mesuré avec le second conteneur.

### Contraintes importantes

- Les nombres fournis doivent être des entiers positifs.
- Le programme doit gérer au moins 3000 entiers différents.
- En cas d’erreur, il faut afficher un message sur la sortie d’erreur.
- Deux conteneurs différents doivent être utilisés.

### Idée théorique utile

Le merge-insert sort combine une logique de paires et d’insertion optimisée.

- On regroupe souvent les éléments par paires.
- On trie ensuite certains éléments de référence.
- Les autres éléments sont insérés dans la séquence triée à l’aide d’une recherche efficace, souvent binaire.
- L’objectif est de réduire le nombre de comparaisons par rapport à un tri classique.
- Il est conseillé d’implémenter l’algorithme séparément pour chaque conteneur, plutôt que d’essayer de tout généraliser.

## Résumé rapide

- `ex00` : convertir une date en valeur bitcoin grâce à une base historique.
- `ex01` : évaluer une expression en notation polonaise inverse avec une pile.
- `ex02` : trier efficacement une suite d’entiers avec Ford-Johnson et comparer deux conteneurs.
