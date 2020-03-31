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
    Event* events;
    int nb_events;

Schedule();
void add(Event e);
void create(int nb_arg, char** args);
void del(int id);
void load ();
void save();

};


#endif