
1. Notation aux échecs

1.1 FEN

Les codes FEN (Notation Forsyth-Edwards) permettent de noter une position
sur un échiquier sous la forme suivante : 

rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1

Ce code permet de noter une position sans les coups précédents ou suivants

1.1.1 Les pièces 

r est root la tour
n est knight le cavalier
b est bishop le fou
k est king le roi
q est queen la reine
p est pawn le pion

Les symboles en majuscule correspondent aux pièces blanche 
Les cases vides sont représentées par un entier  1 une case vide 2 deux etc...

1.1.2 L'échiquier

La représation va des noirs au début au blancs
Le symbole / séparer les rangées il y en a donc 7 pour représenter les 
8 rangées

1.1.3 Les symboles suivant l'échiquer 

w ou b indique si le trait est aux blancs(w) ou aux noirs(b)

KQkq  indiquent respectivement que le roi blanc peut roquer sur l'aile roi
sur l'aile dame que le roi noir peut roquer sur l'aile roi et  dame un tiret indique
qu'aucun roque ne peut être effectué. Si le K est manquant le roi blanc ne peut
pas roquer sir l'aile roi car la tour à déjà bougée.

Le - indique si la dernière pièce jouée était un pion qui a avancé de deux cases
et qu'une prise en passant est possible	on peut donner ici le numéro de la case
concernée par exemple e3 ou b6

Le nombre de demis coups joués qui n'est pas l'avance d'un pion ou d'une prise de pièce
pour savoir si une partie nulle peut être déclenchée 

Nombre de coups noirs joués.

1.2 SAN 

Le SAN pous système algébrique de notation est la notation d'un coup 
soit sous forme case de départ case d'arrivée par exemple e2 e4 
La forme SAN abrégée est e4


