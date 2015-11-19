#Spécifications fonctionnelles de UnamedRoguelike


**NOTE**: Ces spécifications sont encore en cours de rédaction. 
Vous pouvez proposer vos idées en créant un ticket d'issue.


## 1.Objectif global

UnamedRoguelike vise à produire un jeu dans lequel l'aléatoire occupe une place importante. 
Néanmoins, comme le nom l'indique, le jeu se destinait à la base a être un énieme roguelike ce qui n'est absolument pas original, ou tout du moins, nous pouvons souligner le fait que l'usage de l'aléatoire est sur-représenté dans le genre. 

Partant de ce constat, nous considérons que l'objectif principal de ce jeu est d'apporter au moins quelque chose de nouveau.

De fait, soyez original dans les fonctionnalités, tout en gardant en tête que le jeu doit conserver un rapport étroit avec l'aléatoire. 

## 2.Définition 

UnamedRoguelike est donc un jeu de gestion dans un monde généré de manière aléatoire. 
L'objectif du joueur étant de guider un ensemble de personnages stupides afin de permettre à ces derniers de survivre dans un mmonde qui leur est fortement hostile. 
Ce jeu doit permettre l'usage du multijjoueur, il est donc prioritaire de définir des mécaniques de gameplay en multijoueur en rapport avec le postulat précedemmment exposé.

## 3. Lexique

* Joueur 1: joueur principal/ joueur du mode solo. En multijoueur, il fait tourner le serveur sur sa machine.
* Joueur 2: joueur secondaire. Il n'est présent qu'en multi et se connecte au serveur du joueur 1, il est donc client de ce dernier.
* Créature: Nom donné aux entités que le joueur 1 doit faire survivre dans le donjon.
* Donjon: Environnement hostile, généré de manière aléatoire dans lequel éveoluent les créatures gérées par le joueur 1.

## 4.Gameplay

### 4.1 Objectif principal des joueurs

#### 4.1.1 Objectif principal du joueur 1

Le joueur doit permettre à ces créatures  de survivre en les guidant de la manière la plus intelligente qui soit.
Pour cela, le joueur peut selectionner une ou plusieurs créature et lui dire d'agir sur tel ou tel élement de l'univers. Chaque élement ne devant avoir qu'une et une seule possibilité d'interraction (du moins par type de créature) afin de permettre une meilleure compatibilité avec les systèmes tactiles.

#### 4.1.2 Objectif principal du joueur 2

Le joueur 2 devra rendre impossible la vie au joueur 1 en disposant des pièges et autres obstacles dans le donjon à interval prédéfinis par le jeu. 

Il devra profiter de l'aspect du donjon pour optimiser ses actions et tuer toutes les créatures du joueur 1.

