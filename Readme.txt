Readme

Configuration sur Visual Studio 2019

CONFIGURATION
-Dans le devoir a remettre sur le moodle, il y a un un dossier lib, Copier-Coller ce fichier dans MoteurDeJeu/Libraries
-Ouvrir le projet à l'aide du fichier MoteurDeJeu.sln situé à la racine du projet.
-Une fois le projet ouvert, cliquer sur projet->propriétés de MoteurJV.
	-Dérouler le menu propriétés de configuration et cliquer sur "Répertoire VC++"
	-Dans l'onglet "Général", sur la ligne "Répertoire Include", cliquer sur la flèche a droite et cliquer sur modifier
séléctionner maintenant dans le 1er tableau une ligne et cliquer sur les ... puis séléctionner le dossier include situé 
dans le dossier libraries du projet cliquer sur OK
	-Dans ce même onglet, répéter l'opération pour la ligne "Répertoires de bibliothèques" mais en séléctionnant 
cette fois-ci le dossier lib situés dans libraries et cliquer sur OK
-Cliquer sur "Editeur de liens" puis sur "entrée"
	-Sur la ligne "Dépendances supplémentaires", cliquer sur "additionnal Dependencies" puis sur modifier
	-Dans le 1er tableau en 1ere ligne indiquer "glfw.lib" et seconde ligne "opengl32.lib"
	-Vérifier que la case "Hériter des paramètres par défaut" est bien cochée
	-Cliquer sur Ok
-Cliquer sur "C/C++" puis sur Général
	-Sur la ligne "Autre répertoire Include", cliquer sur AddtionalIncludeDirectories puis sur modifier 
	-Dans le 1er tableau, indiquer en 1ere ligne "imgui"
	-Vérifier que la case "Hériter des paramètres par défaut" est bien cochée
	-Cliquer sur OK

LANCEMENT DU PROJET 
-Se placer dans le main
-Exécuter le programme

EXECUTION DU CODE 
Suivre les instructions sur menu qui apparaît dans la console 
