#ifndef DEF_TODO
#define DEF_TODO

#include<iostream>

class Event{
public:
    int id;
    std::string title;         /* Titre de l'évènement */
    std::string description;   /* Description facultative de l'évènement */
    int date_of_creation;      /* Format jjmmaa */
    int date_of_end;           /* Format jjmmaa */
    std::string status;        /* Statut de la tâche ex: open, closed, in progress, ... */
    float advancement;         /* Avancement de la tâche en pourcentage de 0% à 100% */
    int priority;              /* Priorités possibles de 0 -> anecdotique à 10 -> très urgent */
    int nb_comments;           /* Nombre de commentaires enregistrés */
    std::string* comments;     /* Commentaires sur l'évènement rajoutés au fur et à mesure */
    int nb_subevents;          /* Nombre de sous-tâches */
    Event** subevents;         /* Sous-tâches nécessaires à la réalisation de la tâche principale */

Event();

Event (std::string t, 
        int doc,
        int dof, 
        std::string descr, 
        std::string s, 
        float adv, 
        int prio,
        std::string com,
        int nb_subevents,
        int* subevents_id); /* Pour créer une tâche avec un seul commentaire */

Event (std::string t, 
        int doc,
        int dof, 
        std::string descr, 
        std::string s, 
        float adv, 
        int prio,
        int nb_comments,
        std::string* com,
        int nb_subevents,
        int* subevents_id); /* Pour charger une tâche possédant déja plusieurs commentaires */

};



class Schedule{
public:
    Event* events;                        /* Liste des évènements enregistrés */
    int nb_events;                        /* Nombre d'évènements enregistrés */

Schedule();
void add(Event e);                         /* Ajoute un évènement à la liste d'events */
void create(int nb_arg, 
            char** args);                  /* Créé un évènement à partir de la commande create */
void del(int id);                          /* Supprime un évènement à partir de la commande delete */
void load ();                              /* Charge les évènements stockés dans un fichier texte */
void save();                               /* Enregistre les évènements dans un fichier texte */
void list(std::string category, 
            std::string clue);             /* Donne les titres des évènements selon un critère choisi */
void search(int id);                       /* Donne la description complète d'un évènement trouvé grâce à son id */
void change(int id,
            std::string category,
            std::string new_item);         /* Remplace un détail d'une tâche/ajoute un commentaire */
};


#endif