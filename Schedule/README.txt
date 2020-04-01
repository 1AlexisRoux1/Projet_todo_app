Projet TODO_APP

Alexis Roux

Commandes disponibles :


=> Pour créer un nouvel évènement avec un certain nombre de paramètres:

./todo_app create --title <entrez un titre au choix>
		  --beginning <entrez une date de création entière sous la forme jjmmaa>
		  --end <entrez une date de fin entière sous la forme jjmmaa>
		  --description <entrez une description au choix (optionnel:"None" par défaut)>
		  --status <entrez un status au choix (optionnel:"open" par défaut)>
		  --advancement <entrez un avancement flottant (optionnel:0.0 par défaut)>
		  --priority <entrez une priorité entière (optionnel: 5 par défaut)>
		  --comment <entrez un commentaire (optionnel:"Event created" par défaut)>
		  --subevent <entrez le nombre n de sous-évènements voulus entier (optionnel: 0 par défaut) <entrez l'id du sous-évènement>*n

ex: ./todo_app create --title "Confinement" --beginning 250320 --end 150420 --advancement 0.5 --priority 8
    ./todo_app create --title "Vacances" --beginning 070420 --end 150420 --comment "Annulées"
    ./todo_app create --title "Second semestre" --beginning 020320 --end 150720 --subevents 1 0


=> Pour supprimer un évènement:

./todo_app delete <entrez l'id de l'évènement à supprimer>

ex : ./todo_app delete 1


=> Pour rechercher la liste de tous les évènement qui remplissent une condition précise:

./todo_app list <entrez le paramètre sur lequel sélectionner les évènements> <entrez la valeur rechechée du paramètre>

Paramètres disponibles : --title / --beginning / --end / --description / --status / --advancement / --priority
ex: ./todo_app list --title "Confinement"
>Events with --title = Confinement are : 
>Confinement --> ID = 0


=> Pour obtenir toutes les informations sur un évènement:

./todo_app search <entrez l'id de l'évènement>

ex: ./todo_app search 1
>Title : Second semestre
>Description : None
>Beginning (jjmmaa) : 20320
>End (jjmmaa) : 150720
>Status : open
>Advancement : 0
<Priority : 5
>Advancement : 0
>Comments :
>  Event created
>Subevents :
>  Confinement --> ID = 0


=> Pour changer la valeur d'un paramètre:

./todo_app change <entrez l'id de l'évènement à modifier> <entre le paramètre à modifier> <entrez la nouvelle valeur du paramètre>

Paramètres disponibles : --title / --beginning / --end / --description / --status / --advancement / --priority / --comment / --subevents

ex: ./todo_app change 1 --title "S2 Cycle ingénieur civil"
    ./todo_app change 0 --end 150620

Remarques : pour change --comment / change --subevents on ne peut que rajouter des commentaires et des sous-évènements

Notes : change --comment et change --subevents on tendance à générer des Segmentation Fault au-delà de un nouveau commentaire et quatre nouveaux sous-évènements
