#include "todo_app.h"
#include<iostream>
#include<fstream>
#include<sstream>

using namespace std;

Schedule eventlist;
int id_giver;


Event::Event (){this->id = -1;};     /* Pour pouvoir initialiser un évènement vide */

Event::Event (string t, 
            int doc,
            int dof, 
            string descr = "None", 
            string s = "open", 
            float adv = 0.0, 
            int prio = 5,
            string com = "Event created",
            int nb_sub = 0,
            int* subevents_id = {} ):
            title{t},
            description{descr},
            date_of_creation{doc},
            date_of_end{dof},
            status{s},
            advancement{adv},
            priority{prio},
            nb_comments{1},
            nb_subevents{nb_sub}
    {id = id_giver;
    id_giver++;
    comments = new string {};
    comments[0] = com;
    Event _ = Event();
    subevents = new Event* {&_};
    for (int i = 0; i<nb_subevents; i++){
        subevents[i] = &eventlist.events[subevents_id[i]];
    }
};

Event::Event (string t,
            int doc,
            int dof, 
            string descr, 
            string s, 
            float adv, 
            int prio,
            int nb_com,
            string* com,
            int nb_sub,
            int* subevents_id):    // Ce cas sert pour charger des évènements enregistrés, il n'y a donc pas de valeurs par défaut
            title{t},
            description{descr},
            date_of_creation{doc},
            date_of_end{dof},
            status{s},
            advancement{adv},
            priority{prio},
            nb_comments{nb_com},
            comments{com},
            nb_subevents{nb_sub}
    {id = id_giver;
    id_giver++;
    Event _ = Event();
    subevents = new Event* {&_};
    for (int i = 0; i<nb_subevents; i++){
        subevents[i] = &eventlist.events[subevents_id[i]];
    }
};

Schedule::Schedule(){
        events = new Event[100];  // On limite la mémoire à 100 évènements maximum
        nb_events = 0;
};

void Schedule::add (Event e){
        this->events[nb_events] = e;
        nb_events ++;
};

void Schedule::del(int id){
    this->events[id] = Event();
}

void Schedule::create (int nb_arg, char** args){
    string strargs[nb_arg];
    for (int k = 0; k < nb_arg; k++){
        strargs[k] = args[k];
    }                                  // On convertit les args en string pour des raisons pratiques
    string t;     
    string descr;
    int doc;
    int dof;
    string s;
    float adv;
    int prio;
    string com;
    int nb_subevents;
    int* subevents_id;
    int i = 2;                           // On entre le titre avec args[3] = --title et args[4] le titre
    bool is_complete = true;
    if (nb_arg > 3 && (strargs[i] == "--title")){
        t = args[i+1];
    }
    else{
        is_complete = false;
        cout<<"Creation failed : First input title with --title \n";
    }
    i = i+2;                              // On entre la date de création avec args[5] = --beginning et args[6] la date de création
    if (nb_arg > 5 && (strargs[i] == "--beginning")){
        doc = atoi(args[i+1]);
    }
    else{
        is_complete = false;
        cout<<"Creation failed : Input date of creation with --beginning just after title \n";
    }
    i = i+2;                              // On entre la date de fin avec args[7] = --end et args[6] la date de fin
    if (nb_arg > 7 && (strargs[i] == "--end")){
        dof = atoi(args[i+1]);
    }
    else{
        is_complete = false;
        cout<<"Creation failed : Input date of end with --end just after beginning \n";
    }
    i = i+2;                             // On teste la présence d'une description, "" par défaut
    if (i<nb_arg && (strargs[i] == "--description")){
        descr = args[i+1];
        i = i +2;
    }
    else{
        descr = "";
    }                                   // On teste la présence d'un état, "open" par défaut
    if (i<nb_arg && (strargs[i] == "--status")){
        s = args[i+1];
        i = i +2;
    }
    else{
        s = "open";
    }                                   // On teste la présence d'un avancement, 0.0 par défaut
    if (i<nb_arg && (strargs[i] == "--advancement")){
        adv = atof(args[i+1]);
        i = i +2;
    }
    else{
        adv = 0.0;
    }                                   // On teste la présence d'une priorité, 5 par défaut
    if (i<nb_arg && (strargs[i] == "--priority")){
        prio = atoi(args[i+1]);
        i = i +2;
    }
    else{
        prio = 5;
    }                                   // On teste la présence d'un commentaire, "Event created" par défaut
    if (i<nb_arg && (strargs[i] == "--comment")){
        com = args[i+1];
        i = i +2;
    }
    else{  
        com = "Event created";
    }                                   // On teste la présence de sous-évènements, le premier entier est le nombre de sous-évènements, 0 par défaut
    if (i<nb_arg && (strargs[i] == "--subevents")){
        nb_subevents = atoi(args[i+1]);
        i = i + 2;
        if (nb_subevents){              // On récupère la liste de sous-évènements sous-forme d'entiers séparés par des espaces
            subevents_id = new int {};
            for (int j = 0; j<nb_arg-i;j++){
                subevents_id[j] = atoi(args[j+i]);
            }
        }
    }
    else{
        nb_subevents = 0;
        subevents_id = {}; 
    }
    if (is_complete){
        Event e = Event(t, 
                        doc,
                        dof, 
                        descr, 
                        s, 
                        adv, 
                        prio,           // On autorise un seul commentaire à la création manuelle d'une tâche 
                        com,
                        nb_subevents,
                        subevents_id);
        this->add(e);
    }
};

void Schedule::load(){
    ifstream data{"Schedule.txt"};
    string nb_lignes;                 // Le premier caractère contient le nombre de tâches stockées dans le fichier texte
    getline(data,nb_lignes,'\n');
    id_giver = stoi(nb_lignes);
    for(int i = 0; i <stoi(nb_lignes); i++){
        string t;     
        string descr;
        int doc;
        int dof;
        string s;
        float adv;
        int prio;
        int nb_com;
        string* com;
        int nb_subevents;
        int* subevents_id;
        string full_event;     
        getline(data,full_event,'\n');   // Une ligne correspond à un évènement
        stringstream stream_event(full_event);
        getline(stream_event,t,'|');     // On récupère le titre
        string item;
        getline(stream_event,item,'|');  // On récupère la date de création
        doc = stoi(item);
        getline(stream_event,item,'|');  // On récupère la date de fin
        dof = stoi(item);
        getline(stream_event,descr,'|'); // On récupère la description
        getline(stream_event,s,'|');     // On récupère le statut
        getline(stream_event,item,'|');  // On récupère l'avancement
        adv = stof(item);
        getline(stream_event,item,'|');  // On récupère la priorité
        prio = stoi(item);
        getline(stream_event,item,'|');  // On récupère les commentaires
        stringstream stream_item(item);
        string strnb_com;
        getline(stream_item,strnb_com,'$');
        nb_com = stoi(strnb_com);        // On récupere le nombre de commentaires
        com = new string[nb_com];
        for (int j = 0; j<nb_com; j++){  // On récupère les commentaires un par un
            getline(stream_item,com[j],'$');
        }
        getline(stream_event,item,'|');  // On récupère les indices des sous-évènements
        stringstream stream_item2(item);
        string strnb_sub;
        getline(stream_item2,strnb_sub,'$');
        nb_subevents = stoi(strnb_sub);        // On récupere le nombre de sous-évènements
        subevents_id = new int[nb_subevents];
        for (int j = 0; j<nb_subevents; j++){  // On récupère les sous-évènements un par un
            string sub_id;
            getline(stream_item2,sub_id,'$');
            subevents_id[j] = stoi(sub_id);
        }
        Event e = Event (t,
                        doc,
                        dof, 
                        descr, 
                        s, 
                        adv, 
                        prio,
                        nb_com,
                        com,
                        nb_subevents,
                        subevents_id);         // On crée la tâche
        this->add(e);   
    }
}

void Schedule::save(){
    ofstream data("Schedule.txt");
    for (int i = 0; i < this->nb_events; i++){
        Event e = this->events[i];
        if(e.id != -1){         // Permet de ne pas sauvegarder les tâches vides
        cout<<e.title<<"|";
        cout<<e.date_of_creation<<"|";
        cout<<e.date_of_end<<"|";
        cout<<e.description<<"|";
        cout<<e.status<<"|";
        cout<<e.advancement<<"|";
        cout<<e.priority<<"|";
        cout<<e.nb_comments<<"$";
        for (int j = 0; j < e.nb_comments; j++){
            cout<<e.comments[j]<<"$";
        }
        cout<<"|";
        cout<<e.nb_subevents<<"$";
        for (int j = 0; j < e.nb_subevents; j++){
            cout<<e.subevents[j]->id<<"$";
        }
        cout<<"|";
        cout<<"\n";
        }
    }
}

// MAIN

int main(int argc, char** argv){
    string command;
    //eventlist = Schedule();
    eventlist.load();
    if (argc<2){
        cout<<"No input found\n";
    }
    else{
        command = argv[1];
    }
    if (command == "create"){
        eventlist.create(argc,argv);
    }
    else if (command == "delete"){
        eventlist.del(stoi(argv[2]));
    }
    else {
        cout<<"Invalid command"<<endl;
    }
    for (int k = 0; k<eventlist.nb_events; k++){
        cout<<eventlist.events[k].title<<endl;
    }
    eventlist.save();
    return 0;
}
// TEST 4
/*
int main(){
    eventlist = Schedule();
    //eventlist.load();
    cout<<id_giver<<endl;
    Event e = Event();
    eventlist.add(e);
    eventlist.save();
    return 0;
}


 // TEST 3
/*
int main(){
    id_giver = 0;
    eventlist = Schedule();
    Event e = Event("Wouhouhou ça marche !!!",666,999);
    eventlist.add(e);
    eventlist.load();
    cout<<eventlist.events[1].comments[1]<<"\n";
    return 0;
}


// TEST 2
/*
int main(int argc, char** argv){
    int id_giver = 0;
    string command;
    eventlist = Schedule();
    Event e = Event("Wouhouhou ça marche !!!",666,999);
    eventlist.add(e);
    if (argc<2){
        cout<<"No input found\n";
    }
    else{
        command = argv[1];
    }
    if (command == "create"){
        eventlist.create(argc,argv);
    }
    cout<<eventlist.events[1].subevents[0]->title<<"\n";
    return 0;
}


// TEST 1
/*
int main(){
    int id_giver = 0;
    eventlist = Schedule ();
    Event e = Event("Wouhouhou ça marche !!!",666,999);
    eventlist.add(e);
    cout<<eventlist.events[0].comments[0]<<"\n";
    Event f = Event("OMG this is the future !!!",
                    290320,
                    31032021,
                    "Ceci n'est pas une description du tout",
                    "more open",
                    0.5,
                    11,
                    "Event recreated",
                    1,
                    new int {0});
    eventlist.add(f);
    cout<<eventlist.events[1].subevents[0]->comments[0]<<"\n";
    return 0;
}
*/
