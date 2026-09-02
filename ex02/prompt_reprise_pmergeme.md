# Contexte de reprise — projet CPP09 (42), exercice PmergeMe

Je travaille sur le module CPP09 du cursus 42 (C++, STL). On a deja avance ensemble sur
ex00 (BitcoinExchange) et on est en plein dans ex02 (PmergeMe, tri Ford-Johnson).
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
  d'un iterateur, etc.), propose un schema (diagramme SVG) plutot que d'empiler du texte.

## Style de code (C++98 strict, projet 42)

- **Un fichier = une fonction publique** (+ ses helpers prives static). Convention deja
  suivie sur BitcoinExchange (`BitcoinExchange_dateIsValid.cpp`, etc.) et gardee sur
  PmergeMe (`PmergeMe_parse.cpp`, `PmergeMe_vectorToDeque.cpp`, `PmergeMe_vectorSort.cpp`...).
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
- **Noms courts et directs**, souvent nom-verbe ou verbe-nom selon ce qui se lit le
  mieux (ex: `oddCaseHandle`, `pairsMake`, `toPositiveInt`, `extractInt`). On discute
  ensemble le nom avant de valider, je peux changer d'avis en cours de route — c'est ok,
  on garde le dernier choix.
- **Classes utilitaires (comme PmergeMe)** : si la classe n'a aucun membre et que toutes
  les methodes publiques sont `static`, l'OCF (constructeur par defaut, copie,
  `operator=`, destructeur) reste **obligatoire** (contrainte du sujet 42, C++98 donc pas
  de `= delete`), mais se met en `private` avec des corps vides (`(void)param;` pour
  eviter les warnings unused-parameter) pour empecher l'instanciation.
- **Toujours tester le code produit** avant de le livrer : compilation
  `-Wall -Wextra -Werror -std=c++98`, plus des cas de test via un `main` minimal en
  environnement isole (pas besoin d'integrer dans le vrai projet pour tester).

## Etat d'avancement PmergeMe (ex02) au moment de la reprise

Deja ecrit et teste ensemble (dans notre style, fichiers deja livres) :
- `PmergeMe_parse.cpp` : `inputParse` (public) + `toPositiveInt` + `extractInt`
  (parsing des arguments via istringstream, rejette <=0, overflow, non-numerique).
- `PmergeMe_vectorToDeque.cpp` : `vectorToDeque` (conversion simple via constructeur
  de range).
- `PmergeMe_vectorSort.cpp` : en cours — je fournirai l'etat actuel de ce fichier
  directement dans la nouvelle conversation, ainsi que le sujet complet de l'exercice.

Discute mais pas encore code dans notre style :
- Comment reconnecter chaque grand trie a son petit apres la recursion (recherche par
  valeur + suppression dans `pairs`, technique validee comme correcte meme avec doublons
  — pas besoin de suivi par index, l'invariant `b < a` tient peu importe l'assignation
  entre elements egaux).
- Generation de la suite de Jacobsthal : je veux une fonction qui renvoie un tableau
  `const` de `int` **en dur** (valeurs precalculees), pas une generation dynamique par
  calcul.
- Insertion finale de l'element impair (`oddOne`), sans borne superieure.
- `dequeSort` (meme algorithme, container `std::deque` — a ecrire separement une fois
  `vectorSort` fini, pas de fonction generique commune, conformement au sujet qui
  demande d'implementer l'algo pour chaque conteneur separement).

Reprends a partir de la, en continuant `vectorSort` : je vais te fournir l'etat actuel
du fichier ainsi que le sujet de l'exercice.
