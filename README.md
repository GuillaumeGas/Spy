Spy
===

Recuperer le Depot

  git clone https://github.com/GuillaumeGas/Spy.git
  
  
Compiler le Projet

  cd trunk
  
  mkdir .build
  
  cd .build
  
  cmake ..
  
  make (le dossier ~/lib doit être crée pour que la librairie puisse s'y installer)
  
  
Executer le projet

  
  cd .build
  ./master [-f ( file.conf) ] par defaut le fichier lu est le fichier def.conf
  
  ./spy [ -f (file.conf) ]
  
  ./controller [-f (file.conf) ]
  
  ./observer [-f (file.conf) ]
  
  le controller scan le reseau tout le n second avec n la vitesse note dans le dossier def.conf
  il peut donc arriver si vous lancez le controller avant le psy que le controller n'ai pas encore detecté le spy 
  et donc que l'observeur n'observe personne. L'ordre de lancement peut donc être important sauf si vous attendez avant
  de lancer l'observer que le controller ait detecté les spy 

