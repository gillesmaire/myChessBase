#! /usr/bin/python3

import sys

avec_vide = True
count=1   
trouve=False
indexsearched=2812802
counttrouve=0
#with open("caissa.pgn", 'r') as fichier:
with open("result", 'r') as fichier:
	for ligne in fichier:       
		if ligne.strip() == '' :
			avec_vide = True
		else: 
			if count == indexsearched:
				print (ligne, end='')
				counttrouve+=1
				if counttrouve == 60 :
					sys.exit()
			else:
				if avec_vide and not ligne.startswith("1") and not ligne.startswith("0"):
					count=count+1
			avec_vide=False				
		
		
