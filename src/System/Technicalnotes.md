# Goal of document

The document explains some technical choice or point to understand
the project

Several independant TabWidgets  offers disctinct functions. They are
independant but communicate with the main window with a signal slot
mecanism : 

These differents sub projects are 
	- PGN Editor
	- Configuration 
	- Data Base management
	- Analyse

# PGNEditor

The PGNEditor is based on several concepts :

 - a Board organized around chess.hpp library
 - a navigation panel to go end, start and navigate on the game
 - an TextEdit editor to display moves.


## The editor

- The editor shows the moves 
- It displays the current move my an hilighting mechanism
- QCursor is used because it allow to manipulate text inside the Editor

### Particularism 

- The QCursor uses - (in 0-0 and  0-0-0) + in check as delimitor.
They are replacd by UTF8 symbols in the editor to allow to don't
separate the words
- The  Paste PGN copy a ASCII game in Editor in PGN in Editor and after the caracters 
are replaced.



