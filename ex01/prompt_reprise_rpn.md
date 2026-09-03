# Contexte de reprise — projet CPP09 (42), exercice RPN

Je travaille sur le module CPP09 du cursus 42 (C++, STL). On a deja avance ensemble sur
ex00 (BitcoinExchange) et on passe maintenant a ex01 (RPN, notation polonaise inversee).
Voici comment on travaille et les conventions qu'on a fixees — respecte-les strictement
pour la suite.

## Methode de collaboration

- On avance **petit bout par petit bout** : une fonction a la fois, jamais un gros bloc
  d'un coup. On discute d'abord le design (nom, signature, decoupage), puis seulement
  apres on ecrit le code.
- **Avant d'ecrire du code, tu compiles et tu testes toi-meme** (bash + g++ avec
  `-Wall -Wextra -Werror -std=c++98`) dans un environnement isole, avec des cas de test
  concrets (cas normal, cas limite, cas d'erreur). Tu ne me donnes jamais du code que tu
  n'as pas verifie toi-meme.
- Reponses **concises, peu de blabla**, va a l'essentiel. Pas de sur-explication si je
  n'ai rien demande de plus.
- Quand un concept est visuellement plus clair qu'en texte (flux d'algorithme, etats
  d'une pile, etc.), propose un schema (diagramme SVG) plutot que d'empiler du texte.

## Style de code (C++98 strict, projet 42)

- **Un fichier = une fonction publique** (+ ses helpers prives static). Convention deja
  suivie sur BitcoinExchange (`BitcoinExchange_dateIsValid.cpp`, etc.) et a garder sur
  RPN (par ex. `RPN_evaluate.cpp`, `RPN_tokenSplit.cpp`, `RPN_operate.cpp`...).
- **Fragmenter au maximum en petites fonctions `static`** (visibilite fichier local),
  chacune avec une seule responsabilite claire.
- **Organisation dans le fichier** :
  1. Prototypes des fonctions "niveau 1" (appelees directement par la fonction publique
     principale) juste au-dessus de cette fonction principale.
  2. La fonction publique principale.
  3. Les sous-fonctions, definies **dans l'ordre ou elles sont appelees** dans la
     fonction principale (pas alphabetique, pas arbitraire).
  4. Cas particulier : si une sous-fonction A appelle une sous-fonction B qui n'est
     utilisee que par A (une "sous-sous-fonction"), le prototype de B se place juste
     au-dessus de la definition de A, pas en haut avec les prototypes de niveau 1.
- **Privilegier `istringstream`** pour tout parsing/conversion plutot que
  `atoi`/`strtol`/boucles manuelles de validation caractere par caractere, quand c'est
  raisonnable.
- **Gestion d'erreurs par exceptions** : les fonctions de parsing/validation levent
  (`throw std::invalid_argument("Error")` ou equivalent), le `main` capture avec
  `catch (std::exception const & e)` et affiche `e.what()` sur `std::cerr`.
- **Indentation par tabulations** (`set tabstop=4` cote editeur).
- **Noms courts et directs, entite en premier (nom-verbe)** : le premier mot designe
  l'element sur lequel la fonction agit (`token`, `stack`, `operator`...), le second
  l'action. Interet : ca cree un classement par categorie — toutes les fonctions liees
  a `token` se regroupent (`tokenSplit`, `tokenList`, `tokenPrint`, ...), peu importe
  l'action. On discute ensemble le nom avant de valider, je peux changer d'avis en
  cours de route — c'est ok, on garde le dernier choix.
- **Classes utilitaires (comme RPN, si elle n'a aucun membre et que toutes les methodes
  publiques sont `static`)** : l'OCF (constructeur par defaut, copie, `operator=`,
  destructeur) reste **obligatoire** (contrainte du sujet 42, C++98 donc pas de
  `= delete`), mais se met en `private` avec des corps vides (`(void)param;` pour
  eviter les warnings unused-parameter) pour empecher l'instanciation.
- **Toujours tester le code produit** avant de le livrer : compilation
  `-Wall -Wextra -Werror -std=c++98`, plus des cas de test via un `main` minimal en
  environnement isole (pas besoin d'integrer dans le vrai projet pour tester).

## Rappel des contraintes du sujet (ex01 — RPN)

- Programme nomme `RPN`, dossier `ex01/`. Fichiers a rendre : `Makefile`, `main.cpp`,
  `RPN.{cpp, hpp}`.
- Argument = une expression en notation polonaise inversee (un seul argument,
  potentiellement avec des espaces a l'interieur donc `argv[1]` entre guillemets).
- Nombres passes en argument toujours < 10 (mais le calcul et le resultat
  intermediaire/final peuvent depasser cette limite).
- Operateurs a gerer : `+ - / *`. Pas de parentheses, pas de nombres decimaux a gerer.
- Au moins un container STL requis (different de celui deja "brule" sur
  BitcoinExchange) ; ce container sera a son tour interdit pour PmergeMe (ex02) apres.
  Container choisi pour RPN : **`std::stack`**.
- Erreur => message sur `std::cerr` (le sujet montre juste `Error` en sortie d'exemple).
- Division par zero, expression malformee (pas assez d'operandes, trop d'operandes
  restants a la fin, token invalide) : tout ca doit etre gere comme une erreur.

## Etat d'avancement RPN (ex01) au moment de la reprise

*(A completer : dis-moi ou on en est exactement — rien d'ecrit, ou tel fichier deja
en cours, etc. Je fournirai l'etat actuel du/des fichier(s) si il y en a deja.)*

Reprends a partir de la, en respectant scrupuleusement les conventions ci-dessus.
