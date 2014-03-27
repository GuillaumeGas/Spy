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


Principe du programme

  le controlleur est un client UDP qui envoi des messages sur le reseau.
  
  Des qu'un client UDP d'un spy recoit le message il repond au controlleur pour lui dire qu'il est présent sur le réseau
  
  Un master recoit les noms est les ip:port des spy reconnus par le controlleur
  
  L'observer demande la liste des spy présent sur le reseau au master et tente de se connecter à chacun d'eux.
  La connexion de l'observeur se fait par un protocol RSA de cette manière seul ce programme pourra executer des 
  commandes sur les spy. Si cette sécurité n'était pas présente un simple netcat pourrait supprimer tout les fichiers     d'une session.
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  

