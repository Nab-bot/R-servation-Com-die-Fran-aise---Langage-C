#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h> // Pour les accents
#include <ctype.h> //pour les toupper

// page 40/477 du polycopié du cours C //
// gestion des accents --> page 208 poly

/* Déclaration des variables pour les tailles de champs nom, prenom et autres et autres éléménets comme les booléens qui doivent être utilisés de façon globale (pour sauvegarder par exemple si un changement à été fait ?) */

#define MAX_ID 20
// ID pour identifiant, donc le login

#define MAX_MDP 30
// PW pour PassWord

// pour les infos du client
#define TAILLE_NOM 50
#define TAILLE_PRENOM 50

// pour les infos de l'admin
#define TAILLE_LOGADMIN 50
// pour le mot de passe on reprend le PW

#define TAILLE_ID 20

#define TAILLE_MAIL 100

#define TAILLE_ADRESSE 100

#define DATE 11

#define TYPE_ABO 11

#define NOM_SALLE 50

#define NOM_COMPLET 101
// concerne les auteurs et metteurs en scèbne --> on regroupe en 1 car juste de l'affichage, on ira pas rechercher pas ça ni fouiller dans le fichier avec ces noms

#define TITRE 100
// pour les titres des représentations

#define MAX_REPRES 100
// TAILLE MAX DU TABLEAU QUI VA CONTENIR LES REPRESENTATIONS (d'ailleurs j'aurais pu en mettre moins, 25 ou 50 auraient largement suffit je pense--> check site comédie Française pour les représentations de la saison

/* Déclaration des structs */

/* Visiteurs (abonnés ou pas) */

/* Capacité des salles (nombre de places max PAE SALLE, chacune ne a un nombre différent)  */
#define MAXRICH 879 // la salle Richelieu compte 879 places, donc 879 places dipsonlbes max !
#define SOULIER 839 // idem pour Soulier de Satin (autre disposotion de richelieu)

#define VXCOLOMBIER 300 // idem salle Vieux Colombier
#define BIFRONTAL 276   // idem bifrontal (autre disposition de vieux colombier)

#define STUDIO 136 // idem studio

#define NUM_RES 10 // numéro de réservation

struct admin
{
    // Optionnel : Il faut prévoir la présence d'accents et de caractères spéciaux dans le mot de passe ( pour créer des mots de passe sécure //

    char identifiant[TAILLE_ID];
    char mdp[MAX_MDP];
};

struct visitor
{
    // Il faut prévoir comment on va gérer les accents de nos visiteurs //
    char nom[TAILLE_NOM];
    char prenom[TAILLE_PRENOM];
    char mail[TAILLE_MAIL];
    // c'est une des deux infos à saisir à chaque connexion --> devra être dans le fichier

    int dateNaiss;
    // on le traite comme une chaine de caractères je pense 27/03/2000

    char mdp[MAX_MDP];
    // définir une taille max pour ce champ ?

    char numTel[11];
    // définir taille max num tel ? --> on connait la taille donc oui je pense--> donc on limite à 10--> mais pas besoin de le mettre dans les déclarations de variables globales je pense

    // pas de #define ici car a priori on n eva pas le remanipuler ailleurs

    char adresse[TAILLE_ADRESSE];
    // faire plusieurs champs au sein de l'adresse ? Donc mettre le numéro de voie, puis un autre élément qui donc le nom de la ville, un autre pour le nom du pays ?

    int abo;
    // en faire un booléen pour dire si abonné ou pas --> si vrai --> affichera "abonné" dans le champ, si faux --> affichera soit un champ vide, soit des xxxxx, soit "non abonné", ask avis Dany
    // on met différents types d'avonnement ou c'est un seul abonnement ? Je crois bien qu'il y en a plusieurs--> dans ce cas-là, il faudra peut-être en faire un char, ou utiiser autre chose qu'un bool
    // ou alors, le booléen ici permet de savoir si abo ou pas --> de là, si true --> donc abonné --> on mettra un switch pour les différents types d'abonnement
    // si true --> pas de frais web pdt réservation en ligne, sinon on a es frais web

    char typeAbo[TYPE_ABO];
    // si pas abo --> vide ou des xxxxx, si abo --> on mettra le type d'abonnement
    // on a 3 types d'abos (Carte adulte, jeune et famille)
    // selon le type d'abonnement --> le tarif est pas le même

    // on ne sait pas si on met en #define ou pas, dans le doute on met que oui

    char dateDebutAbo[DATE];
    // si on a un abonnement --> on récupère la date où ça a été fait et celle-ci devra rester telle qu'elle est, sauf si on résilie un abonnement, alors cette date sera mise par défaut à une valeur aberrante, comme 31/12/9999 par exemple, et si le booléen revient à true, alors on récupère la date au moment où le booléne devient true

    //char dateCreaCompte[DATE];
    //

    int numAbo;
    // le numéro d'abonné démarre à 1 et sera incrémenté de 1 à chaque abonnement, on arrivera à 6400 abos pour toutes les cartes comédie fr, mais une fois que qqun va se désabo puis un autre ira s'abonner --> on aura la reprise à 6401, puis on continue, mais n ne revient pas en arrière

    int numVisitor;
    // ce champ sera rempli pour tous les users, abonnés ou pas, il permezttra tjrs d'identifier un visiteur ayant un compte (et sans compte, pas de réservation donc le sujet est réglé)
};

/* Représentation */

// créer un tableau de complétion taillSalle[] que je démarre plein avec autant de cases que le nombre de places par salles (on sait déjà combien de places, puis on remplira chaque case avec un booléen, ou alors un tableau de struct pour les places aussi ?)

struct repre
{

    char nomSalle[NOM_SALLE];
    // on aura plusieurs valeurs possibles, (5 il me semble car on aura les 3 salles et les 2 configurations possibles pour 2 des salles) --> il suffira de mettre le taille de ce champ à autant de caractères que le nom le plus long, ça doit être Salle Soulier de satin je pense, mais vérifier

    char saison[10];
    // ex : Saison 2024-2025 --> ça donne 9 caractères pour les dates, ça suffira je pense--> ce sera fixe d'une année à l'autre
    // on devrait la fixer cette donnée,on sait déjà qu'on est sur une saison précise, mais comment faire pour que le porgramme s'adpte à chaque fois quand je changerai de saison? un fichier de dates et il comporterai un champ indiquant la saison ?

    char titreRepresentation[TITRE];
    // les noms sont plus ou moins longs, prendre large piur être safe, c'est le titre de la représentation

    char nomAuteur[NOM_COMPLET];
    // nom de l'auteur de la représentation qui a lieu
    // ex : pour Macbeth, l'auteur est william shakespeare

    char nomMES[NOM_COMPLET];
    // MES pour Metteur en scène de la représentation

    int dateDebut;
    // 1ère date d'une représentation
    // int car on va les utiliser pour calculer plage de date

    int dateFin; // on laisse la date de fin ? oui car utilse pour connaitre la plage de dates durant lesquelles la représentation sera jouée
    // dernière date d'une représentation
    // idem, on calcule plage de date avec ça
    int plageDate;
    // sera calculé en se basant sur les deux champs précédents

    char idRepre[TAILLE_ID];
    // identifiant de la représentation (
    // comment décider de sa forme ?
    // voir si'il existe déjà des règles de nommage sur ça
    // ex : 01H

    // char plageDate [];
    // indique les dates de 1ère et dernière représentation (donc toute la période durant laquelle elle sera jouée)

    bool placementLibre;
    // si vrai, alors on passe directement au choix du type de tarif (plein tarif, -26 ans, etc...)
    // si faux --> on a alors le choix des placements, et ensuite on passera au choix des tarifs, ce choix de tarifs sera influencé par le choix de la place choisie

    // ex : dans le choix de  if (repre.placementLibre == 0) va affecter reserv.prix, donc un élément d'un struct peut affecter un élément d'un autre struct, en le comparant
    /*      {
                printf("Choix place)
                printf("Avant-scène")
                printf("Avant-scène Corbeille")
                printf("")
            }
            --> ensuite, si je choisi une catéogrie--> on affiche toutes les palces répodnant à ces conditons et on choisit laquelle on veut --> confirmer et passer au paiemeent
    */
};


struct reserv
{
    char numRes[NUM_RES];    // Numéro de réservation
    char idRepre[TAILLE_ID]; // Identifiant de la représentation
    int date;                // Date de la séance (format AAAAMMJJ)
    char numPlace[5];        // Numéro de la place (ex: A15)
    char categorie[10];      // Catégorie de la place (ex: A, B, C)
    char zone[50];           // Zone dans la salle
    int prix;                // Prix de la place
    char tarif[20];          // Type de tarif appliqué (plein, carte jeune, etc.)
    int numVisitor;          // Numéro du visiteur ayant réservé
};

// chaque place est caractérisée par ces éléments
struct place
{

    char salle[NOM_SALLE]; // Salle (ex : Richelieu, Studio, Vieux-Colombier)
    char numero[5];        // Numéro de la place (ex : "001", "B02", etc.)
    char categorie[10];    // Catégorie : "A", "B", "C", "Unique"
    char zone[50];         // Zone (par proximité à la scène)
    int prix;              // Prix en euros (€)
    char tarif[20];        // Tarif : "Plein", "-28 ans", "Famille", "Carte jeune", etc.
    int accesHandicap;    // Accessible handicapé (1 : oui, 0 : non)
    int estLibre;         // Disponibilité (1 : disponible, 0 : réservée)
};//on va utilsier le sintt pourt booléens

/*---Déclaration des variables globales----*/

struct repre tabRepre[MAX_REPRES];
int nbRepre = 0;
int mode = -1; // C'est le mode de connexion : -1 par défaut, 0 = admin, 1 = client

int numVisitorConnecte = -1; // numéro du visiteur connecté

// compteurs du nombre de représentations par salle
int compteurRICH = 1;
int compteurVXCLB = 1;
int compteurSTUDIO = 1;
int compteurSOULIER = 1;    // c'est uen autre disposition de richelieu mais compte comme une autre salle
int compteurBIFRONTALE = 1; // idem, autre dispo de vx colombier

/* --- Déclarations préliminaires --- */
void Admin(); // Cette fonction permet d'accéder au menu de l'administrateur, au sein duquel celui-ci pourra réaliser plusieurs tâches 
void AfficherAdmins(); // Permet d'afficher l'ensemble des comptes administrateurs
void AjouterAdmin(); // Permet de créer un compte administrateur depuis l'espace d'administration
void SupprimerAdmin(); // Permet de supprimer un compte administrateur
void ModifierAdmin(); // Permet de modifier l'identifiant ou le mot de passe d'un administrateur spécifique 
void Client(); // Cette fonction permet d'accéder au menu du client, il pourra réaliser plusieurs actions à partir de là

void AjoutUtilisateur(); // Cette fonction permet d'ajouter un utilisateur depuis l'administration
void ModifUtilisateur();// Cette fonction permet de modifier les champs d'un compte utilisateur spécifique 
void DelUtilisateurs(); // Permet de supprimer un compte utilisateur
void AfficheUtilisateurs(); //Permet d'afficher l'ensemble des utilisateurs présents au sein du fichier utilisateur.txt
void GestionAbo(); //Permet d'ajouter ou de supprimer un abonnement à un compte utilisateur

// fonctions liées aux représentations

void AjoutRepre();
// void AfficherRepre(struct repre tab[], int nbRepre);
void AfficheRepre(); //(affichera la liste des repésentation, on devra pouvoir la trier selon différents critères je pense, comme la date)
void DelRepre(); // Permet de supprimer des représentations 
void ModifRepre(); // Permet de modifier des aspects spécifiques des représentations 

void ToUpper(char *str);

// fonctions liées aux séances (donc une représentation à une date et à une heure donnée)
void AjouterSeance(const char *fichierDates, struct repre tab[], int nbRepre);

void AfficherListeRepreEtChoix(); // permet d'afficher la liste des représentations avec un numéro à coté pour choisir celle qu'on veut plutot que de retaper le nom complet et toutes les erreurs de saisie s'en suivant
void SeanceParRepresentation();

// fonction liées aux places

void AfficherPlace();

int AfficherPlacesDispoFiltrée(const char *fichierPlaces, const char *nomSalle, char *numeroChoisie);

bool EstPlacementLibre(const char *nomSalle); // permet de savoir si une salle est en placement libre ou non

// void AfficherPlaceDispo();//il faudra peut-être préciser les arguments de la fonction(struct place tabPlaces[], int nbPlaces)

void VerifierOuGenererFichierPlaces(); //(const char *nomSalle, const char *fichierPlaces);
// permet de voir is le fichier des places pour une séance donnée à une représentation existe déjà ou pas

// Fonctions liées aux réservations

int GenererNumeroReservation(); // créer un numéro de réservation global à chaque réservation effectuée (donc le numéro de réservation est un numéro global, pas géré par salle)

void AfficherReservations();

void ParcoursReservationComplet(struct repre tab[], int nbRepre);

// ce void fait la parcours complet, donc choix de la représentation--> de la séance (date et heure) --> afficher places dispo avec filtres --> et ENFIN il appel le void suivant, donc ReserverPlace, en fin de void

void ReserverPlace(const char *fichierPlaces, const char *numeroPlace, const char *idRepre, int date);

void AnnulerReservation();

// FONCTIONS DE CHARGEMENT DES FICHIERS AU DÉBUT DU PROGRAMME
void ChargerRepresentations(); // charge automatiquement le contenu de representations.txt dans tabRepre[]

void quitter();

// Menu principal
int main()
{
    setlocale(LC_ALL, "");
    // Chargement des représentations
    ChargerRepresentations(); // à appeler avant d'afficher les représentations

    // Initialisation du fichier numReservations.txt si nécessaire
    FILE *check = fopen("numReservations.txt", "r");
    if (check == NULL)
    {
        check = fopen("numReservations.txt", "w");
        if (check != NULL)
        {
            fprintf(check, "0\n");
            fclose(check);
            printf("Fichier numReservations.txt créé et initialisé à 0.\n");
        }
    }
    else
    {
        fclose(check);
    }

    int choix = -1;
    int saisieValide;

    while (choix != 0)
    {
        printf("     Vous êtes :    \n");
        printf("-1-  Administrateur \n");
        printf("-2-  Client         \n");
        printf("-0-  Quitter        \n");

        saisieValide = 0;
        while (!saisieValide)
        {
            printf("Choix : ");
            if (scanf("%d", &choix) != 1)
            {
                printf("Erreur : veuillez saisir un nombre entier.\n");
                while (getchar() != '\n')
                    ; // vider le buffer
            }
            else if (choix != 1 && choix != 2 && choix != 0)
            {
                printf("Choix erroné. Recommencez.\n");
            }
            else
            {
                saisieValide = 1;
            }
        }

        switch (choix)
        {
        case 1:
            mode = 0;                // mode admin
            numVisitorConnecte = -1; // reset du visiteur connecté
            Admin();
            break;

        case 2:
            mode = 1; // mode client
            Client();
            break;

        case 0:
            quitter();
            break;
        }
    }
    return 0;
}

int verifierConnexionAdmin()
{
    FILE *fic;
    struct admin a;
    char saisieId[TAILLE_ID];
    char saisieMdp[MAX_MDP];
    int trouve = 0;

    printf("Connexion administrateur requise.\n");

    while (trouve == 0)
    {
        printf("Identifiant : ");
        scanf("%s", saisieId);
        printf("Mot de passe : ");
        scanf("%s", saisieMdp);

        fic = fopen("administrateur.txt", "r");
        if (fic == NULL)
        {
            printf("Erreur lors de l'ouverture du fichier administrateurs.txt\n");
            return 0;
        }

        while (fscanf(fic, "%s %s", a.identifiant, a.mdp) != EOF)
        {
            if ((strcmp(saisieId, a.identifiant) == 0) &&
                (strcmp(saisieMdp, a.mdp) == 0))
            {
                trouve = 1;
                break;
            }
        }

        fclose(fic);

        if (!trouve)
        {
            printf("Identifiants incorrects. Réessayez.\n");
        }
    }

    return 1;
}

// Espace administrateur // Modifié par Dany pour qu'on n'ai pas à se reconnecter à chaque fois après avoir effectué une action
void Admin()
{
    int choix = -1;

    if (!verifierConnexionAdmin())
    {
        printf("Échec de la connexion administrateur.\n");
        return;
    }

    do
    {
        printf("+----------------------------------------------+\n");
        printf("|    Espace Administrateur                     |\n");
        printf("+----------------------------------------------+\n");
        printf("|   Gestion des utilisateurs                   |\n");
        printf("+----------------------------------------------+\n");
        printf("|-1- Ajouter un utilisateur                    |\n");
        printf("|-2- Modifier un utilisateur                   |\n");
        printf("|-3- Supprimer un utilisateur                  |\n");
        printf("|-4- Afficher les utilisateurs                 |\n");
        printf("|-5- Gestion des abonnements                   |\n");
        printf("+----------------------------------------------+\n");
        printf("|  Gestion des administrateurs                 |\n");
        printf("+----------------------------------------------+\n");
        printf("|-6- Ajouter un administrateur                 |\n");
        printf("|-7- Afficher la liste des administrateurs     |\n");
        printf("|-8- Supprimer un administrateur               |\n");
        printf("|-9- Modifier  un administrateur               |\n");
        printf("+----------------------------------------------+\n");
        printf("|  Gestion des représentations                 |\n");
        printf("+----------------------------------------------+\n");
        printf("|-10- Ajouter une représentation               |\n");
        printf("|-11- Afficher une représentation              |\n");
        printf("|-12- Modifier une représentation              |\n");
        printf("|-13- Supprimer une représentation             |\n");
        printf("+----------------------------------------------+\n");
        printf("|  Gestion des réservations                    |\n");
        printf("+----------------------------------------------+\n");
        printf("|-14- Ajouter une séance (date+heure)          |\n");
        printf("|-15- Afficher les séances d’une représentation|\n");
        printf("|-16- Afficher les réservations existantes     |\n");
        printf("|-17 - Faire une réservation (parcours complet)|\n");
        printf("|-18- Annuler une réservation existante        |\n");
        printf("+----------------------------------------------+\n");
        printf("|-0- Déconnexion de l'espace administrateur    |\n");
        printf("+----------------------------------------------+\n");
        printf("Choix : ");
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
            AjoutUtilisateur();
            break;
        case 2:
            ModifUtilisateur();
            break;
        case 3:
            DelUtilisateurs();
            break;
        case 4:
            AfficheUtilisateurs();
            break;
        case 5:
            GestionAbo();
            break;
        case 6:
            AjouterAdmin("administrateur.txt");
            break;
        case 7:
            AfficherAdmins("administrateur.txt");
            break;
        case 8:
            SupprimerAdmin("administrateur.txt");
            break;
        case 9:
            ModifierAdmin("administrateur.txt");
            break;
        case 10:
            AjoutRepre();
            break;
        case 11:
            AfficheRepre();
            break;
        case 12:
            ModifRepre();
            break;
        case 13:
            DelRepre();
            break;
        case 14:
            AjouterSeance("dates.txt", tabRepre, nbRepre);
            break;
        case 15:
        {
            int index;
            AfficherListeRepreEtChoix(tabRepre, nbRepre, &index);
            if (index >= 0 && index < nbRepre)
            {
                SeanceParRepresentation("dates.txt", tabRepre[index].idRepre);
            }
            else
            {
                printf("Numéro invalide.\n");
            }
            break;
        }
        case 16:
            AfficherReservations();
            break;
        case 17:
            ParcoursReservationComplet(tabRepre, nbRepre);
            break;
        case 18:
            AnnulerReservation(0);
            break;

        case 0:
            printf("Déconnexion de l'espace administrateur.\n");
            break;
        default:
            printf("Choix erroné\n");
            break;
        }
    } while (choix != 0);
}

// Vérification de la non présence d'un identifiant saisie dans le fichier administrateur.txt
int identifiantExiste(char *identifiant)
{
    FILE *fic = fopen("administrateur.txt", "r");
    struct admin a;

    if (fic == NULL)
    {
        // Si le fichier n'existe pas encore, aucun identifiant n'existe
        return 0;
    }

    while (fscanf(fic, "%s %s", a.identifiant, a.mdp) != EOF)
    {
        if (strcmp(a.identifiant, identifiant) == 0)
        {
            fclose(fic);
            return 1; // Identifiant trouvé
        }
    }

    fclose(fic);
    return 0; // Identifiant non trouvé
}

void AjouterAdmin()
{
    FILE *fic;
    struct admin nouveau;
    int identifiantValide = 0;

    printf("\n--- Ajout d'un nouvel administrateur ---\n");

    // Boucle pour vérifier que l’identifiant est unique
    while (!identifiantValide)
    {
        printf("Identifiant du nouvel administrateur : ");
        scanf("%s", nouveau.identifiant);
        while (getchar() != '\n');

        if (identifiantExiste(nouveau.identifiant))
        {
            printf("Cet identifiant est déjà utilisé. Veuillez en choisir un autre.\n");
        }
        else
        {
            identifiantValide = 1;
        }
    }

    printf("Mot de passe : ");
    scanf("%s", nouveau.mdp);
    while (getchar() != '\n');

    fic = fopen("administrateur.txt", "a");
    if (fic == NULL)
    {
        printf("Erreur ouverture du fichier administrateur.txt\n");
        return;
    }

    fprintf(fic, "\n%s %s", nouveau.identifiant, nouveau.mdp);
    fclose(fic);

    printf("Administrateur ajouté avec succès.\n");
}

void AfficherAdmins()
{
    FILE *fic = fopen("administrateur.txt", "r");
    struct admin a;
    int compteur = 0;

    if (fic == NULL)
    {
        printf("Erreur : impossible d'ouvrir le fichier administrateur.txt\n");
        return;
    }

    printf("\n--- Liste des administrateurs ---\n");
    while (fscanf(fic, "%s %s", a.identifiant, a.mdp) != EOF)
    {
        printf("identifiant - %s / mdp - %s\n", a.identifiant, a.mdp);
        compteur++;
    }

    if (compteur == 0)
    {
        printf("Aucun administrateur enregistré pour le moment.\n");
    }

    fclose(fic);
}

void SupprimerAdmin()
{
    FILE *fic = fopen("administrateur.txt", "r");
    FILE *temp = fopen("temp_admin.txt", "w");
    struct admin a;
    char idASupprimer[TAILLE_ID];
    int trouve = 0;

    if (fic == NULL || temp == NULL)
    {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        return;
    }

    printf("Entrez l'identifiant de l'administrateur à supprimer : ");
    scanf("%s", idASupprimer);

    while (fscanf(fic, "%s %s", a.identifiant, a.mdp) != EOF)
    {
        if (strcmp(a.identifiant, idASupprimer) == 0)
        {
            trouve = 1; // On ne réécrit pas cet admin
        }
        else
        {
            fprintf(temp, "%s %s\n", a.identifiant, a.mdp);
        }
    }

    fclose(fic);
    fclose(temp);

    if (trouve)
    {
        printf("\n Administrateur supprimé.\n");
        printf("ℹ️  Remplace manuellement le fichier 'administrateur.txt' par 'temp_admin.txt'.\n");
    }
    else
    {
        printf("Aucun administrateur trouvé avec cet identifiant.\n");
    }
}

void ModifierAdmin()
{
    FILE *fic = fopen("administrateur.txt", "r");
    FILE *temp = fopen("temp_admin.txt", "w");
    struct admin a;
    char idSaisi[TAILLE_ID];
    char mdpSaisi[MAX_MDP];
    char nouveauId[TAILLE_ID];
    char nouveauMdp[MAX_MDP];
    int choix = -1;
    int trouve = 0;

    if (fic == NULL || temp == NULL)
    {
        printf("Erreur ouverture des fichiers.\n");
        return;
    }

    // Authentification
    printf("Identifiant : ");
    scanf("%s", idSaisi);
    printf("Mot de passe : ");
    scanf("%s", mdpSaisi);

    // Lecture et traitement
    while (fscanf(fic, "%s %s", a.identifiant, a.mdp) != EOF)
    {
        if (strcmp(idSaisi, a.identifiant) == 0 && strcmp(mdpSaisi, a.mdp) == 0)
        {
            trouve = 1;

            while (choix != 1 && choix != 2)
            {
                printf("Que souhaitez-vous modifier ?\n");
                printf("1 - Identifiant\n");
                printf("2 - Mot de passe\n");
                printf("Votre choix : ");
                scanf("%d", &choix);
            }

            if (choix == 1)
            {
                printf("Nouveau identifiant : ");
                scanf("%s", nouveauId);
                fprintf(temp, "%s %s\n", nouveauId, a.mdp);
            }
            else
            {
                printf("Nouveau mot de passe : ");
                scanf("%s", nouveauMdp);
                fprintf(temp, "%s %s\n", a.identifiant, nouveauMdp);
            }
        }
        else
        {
            fprintf(temp, "%s %s\n", a.identifiant, a.mdp);
        }
    }

    fclose(fic);
    fclose(temp);

    if (trouve)
    {
        printf("Modification effectuée.\n");
        printf("Remplace manuellement 'administrateur.txt' par 'temp_admin.txt' pour que les changements prennent effet.\n");
    }
    else
    {
        printf("Identifiants incorrects. Aucune modification effectuée.\n");
    }
}

int genererNumeroUtilisateur()
{
    FILE *f;
    // On défini num qui est égal à 0 et qui va s'incrémenter au fur et à mesure, et temp qui servira à effectuer les comparaison
    int num = 0, tmp;

    f = fopen("numUtilisateurs.txt", "r");
    if (f != NULL)
    {
        // Parcourir chaque ligne pour trouver le dernier numéro
        while (fscanf(f, "%d", &tmp) == 1)
        {
            if (tmp > num)
                num = tmp;
        }
        fclose(f);
    }
    // Lorsqu'on a trouvé le dernier numéro utilisateur, on l'incrémente de 1

    num++; // Création du nouveau numéro

    // Ajouter le nouveau numéro à la fin du fichier
    f = fopen("numUtilisateurs.txt", "a");
    if (f != NULL)
    {
        fprintf(f, "%d\n", num);
        fclose(f);
    }

    return num;
}

int genererNumeroAbonne()
{
    FILE *f;
    int num = 0, tmp;

    f = fopen("numAbonnes.txt", "r");
    if (f != NULL)
    {
        while (fscanf(f, "%d", &tmp) == 1)
        {
            if (tmp > num)
                num = tmp;
        }
        fclose(f);
    }

    num++; // incrémentation pour le nouveau numéro

    f = fopen("numAbonnes.txt", "a");
    if (f != NULL)
    {
        fprintf(f, "%d\n", num);
        fclose(f);
    }

    return num;
}

void AjoutUtilisateur()
{
    FILE *fic;
    struct visitor user;
    int annee, mois, jour;
    int dateNaiss;

    fic = fopen("utilisateurs.txt", "a");
    if (fic == NULL)
    {
        printf("Erreur ouverture fichier utilisateurs.txt\n");
        return;
    }

    printf("Prénom : ");
    scanf(" %[^\n]", user.prenom);
    getchar();
    ToUpper(user.prenom); // ← force la casse

    printf("Nom : ");
    scanf(" %[^\n]", user.nom);
    getchar();
    ToUpper(user.nom); // ← force la casse

    printf("Adresse mail : ");
    scanf("%[^\n]", user.mail);
    getchar();

    // JOUR
    printf("Jour de naissance (1 à 31) : ");
    scanf("%d", &jour);
    while (jour < 1 || jour > 31)
    {
        printf("Jour invalide. Recommencez : ");
        scanf("%d", &jour);
    }

    // MOIS
    printf("Mois de naissance (1 à 12) : ");
    scanf("%d", &mois);
    while (mois < 1 || mois > 12)
    {
        printf("Mois invalide. Recommencez : ");
        scanf("%d", &mois);
    }

    // ANNÉE
    printf("Année de naissance (>= 1900) : ");
    scanf("%d", &annee);
    while (annee < 1900)
    {
        printf("Année invalide. Recommencez : ");
        scanf("%d", &annee);
    }

    dateNaiss = annee * 10000 + mois * 100 + jour;
    if (dateNaiss > 20240504)
    {
        printf("La date doit être au maximum le 04/05/2024.\n");
    }
    user.dateNaiss = dateNaiss;
    printf("La date de naissance a été enregistrée.\n");

    printf("Mot de passe : ");
    scanf(" %[^\n]", user.mdp);
    getchar();

    printf("Numéro de téléphone : ");
    scanf(" %[^\n]", user.numTel);
    getchar();

    printf("Adresse : ");
    scanf(" %[^\n]", user.adresse);
    getchar();

    int tmpAbo;
    printf("L’utilisateur est-il abonné ? (1=oui / 0=non) : ");
    scanf("%d", &tmpAbo);
    while (tmpAbo != 0 && tmpAbo != 1)
    {
        printf("Saisie invalide. Tapez 1 pour oui, 0 pour non : ");
        scanf("%d", &tmpAbo);
    }
    user.abo = tmpAbo;

    if (user.abo == 1)
    {
        printf("Type d’abonnement (A=Adulte, J=Jeune, F=Famille) : ");
        scanf("%s", user.typeAbo);
        while (strcmp(user.typeAbo, "A") != 0 &&
               strcmp(user.typeAbo, "J") != 0 &&
               strcmp(user.typeAbo, "F") != 0)
        {
            printf("Erreur : A, J ou F uniquement : ");
            scanf("%s", user.typeAbo);
        }

        printf("Année de début de l’abonnement : ");
        scanf("%d", &annee);
        while (annee < 1900)
        {
            printf("Année invalide. Recommencez : ");
            scanf("%d", &annee);
        }

        printf("Mois de début (1 à 12) : ");
        scanf("%d", &mois);
        while (mois < 1 || mois > 12)
        {
            printf("Mois invalide. Recommencez : ");
            scanf("%d", &mois);
        }

        printf("Jour de début (1 à 31) : ");
        scanf("%d", &jour);
        while (jour < 1 || jour > 31)
        {
            printf("Jour invalide. Recommencez : ");
            scanf("%d", &jour);
        }

        sprintf(user.dateDebutAbo, "%02d/%02d/%04d", jour, mois, annee);
        user.numAbo = genererNumeroAbonne();
        printf("Votre numéro d'abonné : %d\n", user.numAbo);
    }
    else
    {
        strcpy(user.typeAbo, "NonAbo");
        strcpy(user.dateDebutAbo, "00/00/0000");
        user.numAbo = 0;
    }

    user.numVisitor = genererNumeroUtilisateur();
    printf("Numéro d’utilisateur : %d\n", user.numVisitor);

    fprintf(fic, "%s|%s|%s|%d|%s|%s|%s|%d|%s|%s|%d|%d\n",
            user.nom, user.prenom, user.mail, user.dateNaiss,
            user.mdp, user.numTel, user.adresse,
            user.abo, user.typeAbo, user.dateDebutAbo,
            user.numAbo, user.numVisitor);

    fclose(fic);
    printf("Utilisateur ajouté avec succès !\n");
}

int verifierConnexion()
{
    FILE *fichier;
    struct visitor user;
    char mailSaisi[100], mdpSaisi[100];
    int trouve = 0;
    char ligne[600];

    do
    {
        printf("Entrez votre email : ");
        scanf("%s", mailSaisi);
        printf("Entrez votre mot de passe : ");
        scanf("%s", mdpSaisi);

        fichier = fopen("utilisateurs.txt", "r");
        if (fichier == NULL)
        {
            printf("Erreur d'ouverture du fichier.\n");
            return 0;
        }

        trouve = 0;
        while (fgets(ligne, sizeof(ligne), fichier) != NULL)
        {
            sscanf(ligne, "%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%d|%d",
                   user.nom,
                   user.prenom,
                   user.mail,
                   &user.dateNaiss,
                   user.mdp,
                   user.numTel,
                   user.adresse,
                   (int *)&user.abo,
                   user.typeAbo,
                   user.dateDebutAbo,
                   &user.numAbo,
                   &user.numVisitor);
            if ((strcmp(mailSaisi, user.mail) == 0) && (strcmp(mdpSaisi, user.mdp) == 0))
            {
                trouve = 1;
                break;
            }
        }

        fclose(fichier);

        if (!trouve)
        {
            printf("Erreur : Email ou mot de passe incorrect. Veuillez réessayer.\n");
        }

    } while (!trouve);

    printf("Connexion réussie !\n");
    return 1;
}

void Client()
{
    int choix = -1;

    while (choix != 0)
    {
        printf("\n--- Espace Client ---\n");
        printf("1 - Se connecter\n");
        printf("2 - Créer un compte\n");
        printf("0 - Retour au menu principal\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
            if (verifierConnexion())
            {
                int choix_client = -1;
                while (choix_client != 0)
                {
                    printf("\n--- Menu Client Connecté ---\n");
                    printf("1 - Voir les représentations\n");
                    printf("0 - Déconnexion\n");
                    printf("Votre choix : ");
                    scanf("%d", &choix_client);

                    switch (choix_client)
                    {
                    case 1:
                        AfficheRepre();
                        break;
                    case 0:
                        printf("Déconnexion...\n");
                        break;
                    default:
                        printf("Choix invalide.\n");
                        break;
                    }
                }
            }
            break;
        case 2:
            AjoutUtilisateur();
            break;
        case 0:
            printf("Retour au menu principal.\n");
            break;

        default:
            printf("Choix invalide.\n");
            break;
        }
    }
}

// sachant que le nombre de représentation max est connu à l'avance, pas besoin de réallouer continuellement l'espace, ce tableau ne sera donc pas dynamique mais statique !
// ON PEUT FAIRE DYNAMIQUE MAIS ÇA COMPLIQUERAIT LES CHOSES
// on va faire une suppression logique

// Création de la fonction basique d'affichage des utilisateurs, cette première fonction va d'abord afficher tous les utilisateurs, mais par la suite on va pouvoir filtrer les informations affichées

void AfficheUtilisateurs()
{
    FILE *fic = fopen("utilisateurs.txt", "r");
    if (fic == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier\n");
        return;
    }

    struct visitor user;
    char ligne[600];
    printf("Liste des utilisateurs présents :\n");
    while (fgets(ligne, sizeof(ligne), fic) != NULL)
    {
        ligne[strcspn(ligne, "\n")] = 0;
        int nbChamps = sscanf(ligne, "%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%d|%d",
                              user.nom,
                              user.prenom,
                              user.mail,
                              &user.dateNaiss,
                              user.mdp,
                              user.numTel,
                              user.adresse,
                              (int *)&user.abo,
                              user.typeAbo,
                              user.dateDebutAbo,
                              &user.numAbo,
                              &user.numVisitor);

        if (nbChamps != 12)
            printf("Erreur de format dans la ligne : %s\n", ligne);
        else
        {
                printf("%-20s | %-20s | %-30s | %-10d | %-20s | %-15s | %-30s | %-5s | %-20s | %-15s | %-10d | %-10d\n",
                    user.nom, 
                    user.prenom,
                    user.mail, 
                    user.dateNaiss, 
                    user.mdp,
                    user.numTel, 
                    user.adresse, 
                    user.abo ? "Oui" : "Non",
                    user.typeAbo, 
                    user.dateDebutAbo, 
                    user.numAbo, 
                    user.numVisitor);
        }
    }

    fclose(fic);
}

bool RechercheAbonnee(struct visitor user, char *nom, char *prenom, int dateNaiss, int numUtilisateur)
{
    return strcmp(user.nom, nom) == 0 &&
           strcmp(user.prenom, prenom) == 0 &&
           user.dateNaiss == dateNaiss &&
           user.numVisitor == numUtilisateur;
}

void DelUtilisateurs()
{
    FILE *fic = fopen("utilisateurs.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    struct visitor user;
    char ligne[600];
    char nom[TAILLE_NOM], prenom[TAILLE_PRENOM];
    int numUtilisateur = -1;
    int trouve = 0;
    int dateNaiss;

    if (fic == NULL || temp == NULL)
    {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        return;
    }

    printf("Suppression par :\n");
    printf("1. Nom, prénom et date de naissance\n");
    printf("2. Numéro d'utilisateur\n");
    int choix;
    scanf("%d", &choix);
    getchar(); // Pour consommer le retour à la ligne

    if (choix == 1)
    {
        printf("Nom : ");
        fgets(nom, TAILLE_NOM, stdin);
        nom[strcspn(nom, "\n")] = 0;

        printf("Prénom : ");
        fgets(prenom, TAILLE_PRENOM, stdin);
        prenom[strcspn(prenom, "\n")] = 0;

        printf("Date de naissance (AAAAMMJJ) : ");
        scanf("%d", &dateNaiss);
    }
    else if (choix == 2)
    {
        printf("Numéro d'utilisateur : ");
        scanf("%d", &numUtilisateur);
    }
    else
    {
        printf("Choix invalide.\n");
        fclose(fic);
        fclose(temp);
        return;
    }

    // Parcourir chaque ligne du fichier utilisateurs.txt
    while (fgets(ligne, sizeof(ligne), fic) != NULL)
    {
        sscanf(ligne, "%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%d|%d",
               user.nom, user.prenom, user.mail, &user.dateNaiss, user.mdp,
               user.numTel, user.adresse, (int *)&user.abo, user.typeAbo,
               user.dateDebutAbo, &user.numAbo, &user.numVisitor);

        if ((choix == 1 && RechercheAbonnee(user, nom, prenom, dateNaiss, user.numVisitor)) ||
            (choix == 2 && user.numVisitor == numUtilisateur))
        {
            printf("Utilisateur trouvé et supprimé : %s %s %d\n", user.prenom, user.nom, user.numVisitor);
            trouve = 1;
        }
        else
        {
            fprintf(temp, "%s", ligne);
        }
    }

    fclose(fic);
    fclose(temp);

    if (trouve)
    {
        remove("utilisateurs.txt");             // Suppression de l'ancien fichier
        rename("temp.txt", "utilisateurs.txt"); // Renommage du fichier temporaire en fichier final
    }
    else
    {
        remove("temp.txt");
        printf("Utilisateur non trouvé.\n");
    }
}

void AjoutAbo()
{
    struct visitor user;
    char nom[TAILLE_NOM], prenom[TAILLE_PRENOM];
    int numUtilisateur,dateNaiss,jour,mois,annee;
    int trouve = 0;

    printf("Saisissez les informations de l'utilisateur à abonner :\n");
    printf("Nom : ");
    scanf(" %[^\n]", nom);
    printf("Prénom : ");
    scanf(" %[^\n]", prenom);
    printf("Jour de naissance  : ");
    scanf("%d", &jour);
    printf("Mois de naissance  : ");
    scanf("%d", &mois);
    printf("Année de naissance : ");
    scanf("%d", &annee);
    dateNaiss = annee * 10000 + mois * 100 + jour;
    printf("Numéro d'utilisateur : ");
    scanf("%d", &numUtilisateur);

    FILE *fic = fopen("utilisateurs.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    char ligne[600];

    if (fic == NULL || temp == NULL)
    {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        return;
    }

    while (fgets(ligne, sizeof(ligne), fic) != NULL)
    {
        sscanf(ligne, "%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%d|%d",
               user.nom, user.prenom, user.mail, &user.dateNaiss, user.mdp,
               user.numTel, user.adresse, (int *)&user.abo, user.typeAbo,
               user.dateDebutAbo, &user.numAbo, &user.numVisitor);

        if (!trouve && RechercheAbonnee(user, nom, prenom, dateNaiss, numUtilisateur))
        {
            user.abo = true;
            printf("Utilisateur %s %s abonné avec succès.\n", user.prenom, user.nom);
            printf("Type d’abonnement (A=Adulte, J=Jeune, F=Famille) : ");
            scanf("%s", user.typeAbo);
            while (strcmp(user.typeAbo, "A") != 0 &&
                strcmp(user.typeAbo, "J") != 0 &&
                strcmp(user.typeAbo, "F") != 0)
            {
                printf("Erreur : A, J ou F uniquement : ");
                scanf("%s", user.typeAbo);
            }
            trouve = 1;
        }

        // Réécriture de la ligne (modifiée ou non)
        fprintf(temp, "%s|%s|%s|%d|%s|%s|%s|%d|%s|%s|%d|%d\n",
                user.nom, user.prenom, user.mail, user.dateNaiss, user.mdp,
                user.numTel, user.adresse, user.abo, user.typeAbo,
                user.dateDebutAbo, user.numAbo, user.numVisitor);
    }

    fclose(fic);
    fclose(temp);

    if (trouve)
    {
        remove("utilisateurs.txt");
        rename("temp.txt", "utilisateurs.txt");
    }
    else
    {
        remove("temp.txt");
        printf("Utilisateur non trouvé.\n");
    }
}

void DelAbo()
{
    struct visitor user;
    char nom[TAILLE_NOM], prenom[TAILLE_PRENOM];
    int numUtilisateur, dateNaiss,jour,mois,annee;
    int trouve = 0;

    printf("Saisissez les informations de l'utilisateur à désabonner :\n");
    printf("Nom : ");
    scanf(" %[^\n]", nom);
    printf("Prénom : ");
    scanf(" %[^\n]", prenom);
    printf("Jour de naissance  : ");
    scanf("%d", &jour);
    printf("Mois de naissance  : ");
    scanf("%d", &mois);
    printf("Année de naissance : ");
    scanf("%d", &annee);
    dateNaiss = annee * 10000 + mois * 100 + jour;
    printf("Numéro d'utilisateur : ");
    scanf("%d", &numUtilisateur);

    FILE *fic = fopen("utilisateurs.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    char ligne[600];

    if (fic == NULL || temp == NULL)
    {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        return;
    }

    while (fgets(ligne, sizeof(ligne), fic) != NULL)
    {
        sscanf(ligne, "%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%d|%d",
               user.nom, user.prenom, user.mail, &user.dateNaiss, user.mdp,
               user.numTel, user.adresse, (int *)&user.abo, user.typeAbo,
               user.dateDebutAbo, &user.numAbo, &user.numVisitor);

        if (!trouve && RechercheAbonnee(user, nom, prenom, dateNaiss, numUtilisateur))
        {
            user.abo = false;
            strcpy(user.typeAbo, "NonAbo");
            printf("Utilisateur %s %s désabonné avec succès.\n", user.prenom, user.nom);
            trouve = 1;
        }

        // Réécriture de la ligne (modifiée ou non)
        fprintf(temp, "%s|%s|%s|%d|%s|%s|%s|%d|%s|%s|%d|%d\n",
                user.nom, user.prenom, user.mail, user.dateNaiss, user.mdp,
                user.numTel, user.adresse, user.abo, user.typeAbo,
                user.dateDebutAbo, user.numAbo, user.numVisitor);
    }

    fclose(fic);
    fclose(temp);

    if (trouve)
    {
        remove("utilisateurs.txt");
        rename("temp.txt", "utilisateurs.txt");
    }
    else
    {
        remove("temp.txt");
        printf("Utilisateur non trouvé.\n");
    }
}

void GestionAbo()
{
    int choix;
    printf(" Espace de gestion des abonnées\n");
    printf(" -1- Ajouter un abonnement à un utilisateur\n");
    printf(" -2- Supprimer un abonnement à un utilisateur\n");
    scanf("%d", &choix);
    switch (choix)
    {
    case 1:
        AjoutAbo();
        break;
    case 2:
        DelAbo();
        break;
    default:
        printf("Choix erroné\n");
        break;
    }
}

void ModifUtilisateur()
{
    FILE *fic = fopen("utilisateurs.txt", "r");
    FILE *temp = fopen("temp.txt", "w");
    struct visitor user;
    char ligne[600];
    int numUtilisateur, trouve = 0;
    int choix;

    if (fic == NULL || temp == NULL)
    {
        printf("Erreur lors de l'ouverture des fichiers.\n");
        return;
    }

    // Demande du numéro d'utilisateur à modifier
    printf("Entrez le numéro d'utilisateur du visiteur à modifier : ");
    scanf("%d", &numUtilisateur);
    getchar(); // Pour consommer le retour à la ligne

    // Parcours du fichier utilisateurs.txt pour trouver l'utilisateur
    while (fgets(ligne, sizeof(ligne), fic) != NULL)
    {
        sscanf(ligne, "%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%d|%d",
               user.nom, user.prenom, user.mail, &user.dateNaiss,
               user.mdp, user.numTel, user.adresse, (int *)&user.abo,
               user.typeAbo, user.dateDebutAbo, &user.numAbo, &user.numVisitor);

        // Vérifie si le numéro d'utilisateur correspond
        if (user.numVisitor == numUtilisateur)
        {
            printf("Visiteur trouvé : %s %s\n", user.prenom, user.nom);
            printf("Choisissez le champ à modifier :\n");
            printf("1. Nom\n");
            printf("2. Prénom\n");
            printf("3. Date de naissance\n");
            printf("4. Adresse\n");
            printf("5. Numéro de téléphone\n");
            printf("6. Email\n");
            printf("7. Type d'abonnement\n");
            printf("8. Date de début d'abonnement\n");
            printf("9. Statut d'abonnement\n");
            printf("Votre choix : ");
            scanf("%d", &choix);
            getchar(); // Pour consommer le retour à la ligne

            // Modification en fonction du choix de l'utilisateur
            switch (choix)
            {
            case 1:
                printf("Nouveau nom : ");
                fgets(user.nom, sizeof(user.nom), stdin);
                user.nom[strcspn(user.nom, "\n")] = 0;
                break;
            case 2:
                printf("Nouveau prénom : ");
                fgets(user.prenom, sizeof(user.prenom), stdin);
                user.prenom[strcspn(user.prenom, "\n")] = 0;
                break;
            case 3:
                printf("Nouvelle date de naissance (JJMMAAAA) : ");
                scanf("%d", &user.dateNaiss);
                break;
            case 4:
                printf("Nouvelle adresse : ");
                fgets(user.adresse, sizeof(user.adresse), stdin);
                user.adresse[strcspn(user.adresse, "\n")] = 0;
                break;
            case 5:
                printf("Nouveau numéro de téléphone : ");
                fgets(user.numTel, sizeof(user.numTel), stdin);
                user.numTel[strcspn(user.numTel, "\n")] = 0;
                break;
            case 6:
                printf("Nouvel email : ");
                fgets(user.mail, sizeof(user.mail), stdin);
                user.mail[strcspn(user.mail, "\n")] = 0;
                break;
            case 7:
                printf("Nouveau type d'abonnement : ");
                fgets(user.typeAbo, sizeof(user.typeAbo), stdin);
                user.typeAbo[strcspn(user.typeAbo, "\n")] = 0;
                break;
            case 8:
                printf("Nouvelle date de début d'abonnement (JJ/MM/AAAA) : ");
                fgets(user.dateDebutAbo, sizeof(user.dateDebutAbo), stdin);
                user.dateDebutAbo[strcspn(user.dateDebutAbo, "\n")] = 0;
                break;
            case 9:
                printf("Statut d'abonnement (1 pour abonné, 0 pour non abonné) : ");
                int statut;
                scanf("%d", &statut);
                user.abo = statut;
                break;
            default:
                printf("Choix invalide.\n");
                fclose(fic);
                fclose(temp);
                return;
            }

            // Réécriture de l'utilisateur modifié dans le fichier temporaire
            fprintf(temp, "%s|%s|%s|%d|%s|%s|%s|%d|%s|%s|%d|%d\n",
                    user.nom,
                    user.prenom,
                    user.mail,
                    user.dateNaiss,
                    user.mdp,
                    user.numTel,
                    user.adresse,
                    (int)user.abo,
                    user.typeAbo,
                    user.dateDebutAbo,
                    user.numAbo,
                    user.numVisitor);
            trouve = 1;
        }
        else
        {
            // Si l'utilisateur n'est pas celui à modifier, on le laisse dans le fichier temporaire
            fprintf(temp, "%s", ligne);
        }
    }

    fclose(fic);
    fclose(temp);

    // Si l'utilisateur a été trouvé et modifié, on remplace le fichier original
    if (trouve)
    {
        remove("utilisateurs.txt");
        rename("temp.txt", "utilisateurs.txt");
        printf("Modification effectuée avec succès.\n");
    }
    else
    {
        remove("temp.txt");
        printf("Visiteur non trouvé.\n");
    }
}

// la logique ic est que comme le tableau est statique, on ne réalloue pas la mémoire et on ne fait qu'afficher ou pas avec pour critère la date de début, si le champ reçoit 0, alors on considère que cette représentation est comme supprimée, elle ne s'affichera pas ici, cepednant

//---------------------------Afficher représentations--------------------

void AfficheRepre()
{
    FILE *f = fopen("representations.txt", "r");
    if (f == NULL)
    {
        printf("Erreur : impossible d’ouvrir le fichier representations.txt\n");
        return;
    }

    char ligne[512];
    struct repre r;
    int tmpPlacementLibre;

    printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| %-15s | %-25s | %-25s | %-26s | %-12s | %-12s | %-10s | %-14s | %-10s |\n",
           "Salle", "Titre", "Auteur", "Metteur en scène", "Début", "Fin", "Plage", "Saison", "ID");
    printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    while (fgets(ligne, sizeof(ligne), f) != NULL)
    {
        if (sscanf(ligne, "%[^|]|%[^|]|%[^|]|%[^|]|%d|%d|%d|%[^|]|%d|%s",
                   r.nomSalle,
                   r.titreRepresentation,
                   r.nomAuteur,
                   r.nomMES,
                   &r.dateDebut,
                   &r.dateFin,
                   &r.plageDate,
                   r.saison,
                   &tmpPlacementLibre,
                   r.idRepre) == 10)
        {

            r.placementLibre = tmpPlacementLibre;

            if (r.dateDebut != 0)
            {
                // Conversion format AAAAMMJJ → JJ/MM/AAAA
                int jjDebut = r.dateDebut % 100;
                int mmDebut = (r.dateDebut / 100) % 100;
                int aaaaDebut = r.dateDebut / 10000;

                int jjFin = r.dateFin % 100;
                int mmFin = (r.dateFin / 100) % 100;
                int aaaaFin = r.dateFin / 10000;

                printf("| %-15s | %-25s | %-25s | %-25s | %02d/%02d/%04d | %02d/%02d/%04d | %-10d | %-15s | %-10s |\n",
                       r.nomSalle,
                       r.titreRepresentation,
                       r.nomAuteur,
                       r.nomMES,
                       jjDebut, mmDebut, aaaaDebut,
                       jjFin, mmFin, aaaaFin,
                       r.plageDate,
                       r.saison,
                       r.idRepre);
            }
        }
    }

    printf("---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    fclose(f);
}

// sachant que le nombre de représentation max est connu à l'avance, pas besoin de réallouer continuellement l'espace, ce tableau ne sera donc pas dynamique mais statique !
// ON PEUT FAIRE DYNAMIQUE MAIS ÇA COMPLIQUERAIT LES CHOSES
// on va faire une suppression logique
void AjoutRepre()
{
    if (nbRepre >= MAX_REPRES)
    {
        printf("Nombre maximum de représentations atteint.\n");
        return;
    }

    struct repre r;
    int tmpPlacementLibre;
    int jour, mois, annee;
    int choix;

    // Lecture du titre de la représentation
    printf("Titre de la représentation : ");
    getchar(); // Consommer le retour à la ligne précédent
    scanf("%[^\n]", r.titreRepresentation);

    // Lecture du nom de la salle
    printf("Sélectionnez la salle de la représentation : ");
    printf("-------------------");
    printf("- 1- RICHELIEU      \n");
    printf("- 2- SOULIER DE SATIN\n");
    printf("- 3- VIEUX COLOMBIER  \n");
    printf("- 4- STUDIO\n");
    printf("- 5- BIFRONTAL\n");
    scanf("%d", &choix);
    switch (choix)
    {
    case 1:
        strcpy(r.nomSalle, "RICHELIEU");
        break;
    case 2:
        strcpy(r.nomSalle, "SOULIER DE SATIN");
        break;
    case 3:
        strcpy(r.nomSalle, "VIEUX COLOMBIER");
        break;
    case 4:
        strcpy(r.nomSalle, "STUDIO");
        break;
    case 5:
        strcpy(r.nomSalle, "BI-FRONTAL");
        break;
    }

    // Lecture de la saison
    printf("Saison (ex : 2024-2025) : ");
    getchar(); // Consommer le retour à la ligne précédent
    scanf("%[^\n]", r.saison);

    // Lecture du nom de l’auteur
    printf("Nom de l’auteur : ");
    getchar(); // Consommer le retour à la ligne précédent
    scanf("%[^\n]", r.nomAuteur);

    // Lecture du nom du metteur en scène
    printf("Nom du metteur en scène : ");
    getchar(); // Consommer le retour à la ligne précédent
    scanf("%[^\n]", r.nomMES);

    // Date de début (jour, mois, année)
    printf("Date de début :\n");

    // Jour de début
    printf("Jour de début de la représentation (1 à 31) : ");
    scanf("%d", &jour);
    while (jour < 1 || jour > 31)
    {
        printf("Jour invalide. Recommencez : ");
        scanf("%d", &jour);
    }

    // Mois de début
    printf("Mois de début de la représentation (1 à 12) : ");
    scanf("%d", &mois);
    while (mois < 1 || mois > 12)
    {
        printf("Mois invalide. Recommencez : ");
        scanf("%d", &mois);
    }

    // Année de début
    printf("Année de début de la représentation : ");
    scanf("%d", &annee);
    while (annee < 2024)
    {
        printf("Année invalide. Recommencez : ");
        scanf("%d", &annee);
    }
    int dateDebut = annee * 10000 + mois * 100 + jour;
    r.dateDebut = dateDebut;
    printf("La date de début de la représentation est enregistrée.\n");

    // Date de fin (jour, mois, année)
    printf("Date de fin :\n");

    // Jour de fin
    printf("Jour de fin de la représentation (1 à 31) : ");
    scanf("%d", &jour);
    while (jour < 1 || jour > 31)
    {
        printf("Jour invalide. Recommencez : ");
        scanf("%d", &jour);
    }

    // Mois de fin
    printf("Mois de fin de la représentation (1 à 12) : ");
    scanf("%d", &mois);
    while (mois < 1 || mois > 12)
    {
        printf("Mois invalide. Recommencez : ");
        scanf("%d", &mois);
    }

    // Année de fin
    printf("Année de fin de la représentation : ");
    scanf("%d", &annee);
    while (annee < 2024)
    {
        printf("Année invalide. Recommencez : ");
        scanf("%d", &annee);
    }
    int dateFin = annee * 10000 + mois * 100 + jour;
    r.dateFin = dateFin;
    printf("La date de fin de la représentation est enregistrée.\n");

    // Vérification de la validité des dates
    if (r.dateFin < r.dateDebut)
    {
        printf("La date de fin doit être après la date de début.\n");
        return;
    }

    // Calcul de la plage de dates
    r.plageDate = r.dateFin - r.dateDebut;

    // Lecture du placement libre
    printf("Placement libre ? (1 = Oui, 0 = Non) : ");
    scanf("%d", &tmpPlacementLibre);
    r.placementLibre = tmpPlacementLibre;

    // Génération de l'ID de la représentation
    if (strcmp(r.nomSalle, "RICHELIEU") == 0)
    {
        sprintf(r.idRepre, "RICH%03d", compteurRICH++);
    }
    else if (strcmp(r.nomSalle, "VIEUX-COLOMBIER") == 0 || strcmp(r.nomSalle, "VX-COLOMBIER") == 0)
    {
        sprintf(r.idRepre, "VXCLB%03d", compteurVXCLB++);
    }
    else if (strcmp(r.nomSalle, "STUDIO-THEATRE") == 0 || strcmp(r.nomSalle, "STUDIO") == 0)
    {
        sprintf(r.idRepre, "STUDIO%03d", compteurSTUDIO++);
    }
    else if (strcmp(r.nomSalle, "SOULIER DE SATIN") == 0)
    {
        sprintf(r.idRepre, "SOULIER%03d", compteurSOULIER++);
    }
    else if (strcmp(r.nomSalle, "BIFRONTALE") == 0)
    {
        sprintf(r.idRepre, "BIFRONTALE%03d", compteurBIFRONTALE++);
    }
    else
    {
        sprintf(r.idRepre, "GEN%03d", nbRepre + 1);
    }

    // Ajout de la représentation dans le tableau
    if (nbRepre >= MAX_REPRES)
    {
        printf("Le nombre maximum de représentations est atteint.\n");
        return;
    }
    tabRepre[nbRepre++] = r;

    // Ouverture du fichier en mode ajout
    FILE *f = fopen("representations.txt", "a");
    if (f == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier representations.txt\n");
        return;
    }

    // Écriture de la représentation dans le fichier
    fprintf(f, "%s|%s|%s|%s|%d|%d|%d|%s|%d|%s\n",
            r.nomSalle,
            r.titreRepresentation,
            r.nomAuteur,
            r.nomMES,
            r.dateDebut,
            r.dateFin,
            r.plageDate,
            r.saison,
            r.placementLibre,
            r.idRepre);
    fclose(f);

    // Confirmation de l'ajout
    printf("Représentation ajoutée avec succès.\n");
}

void DelRepre()
{
    FILE *f = fopen("representations.txt", "r"); // Ouverture du fichier en lecture
    if (f == NULL)
    {
        printf("Erreur : impossible d'ouvrir le fichier representations.txt\n");
        return;
    }

    FILE *fTemp = fopen("temp_representations.txt", "w");
    if (fTemp == NULL)
    {
        printf("Erreur : impossible de créer le fichier temporaire\n");
        fclose(f);
        return;
    }

    char ligne[512];
    struct repre r;
    int tmpPlacementLibre;
    char idRepreSuppr[TAILLE_ID];
    int trouve = 0;

    printf("Entrez l'ID de la représentation à supprimer : ");
    scanf("%s", idRepreSuppr);

    while (fgets(ligne, sizeof(ligne), f) != NULL)
    {
        if (sscanf(ligne, "%[^|]|%[^|]|%[^|]|%[^|]|%d|%d|%d|%[^|]|%d|%s",
                   r.nomSalle,
                   r.titreRepresentation,
                   r.nomAuteur,
                   r.nomMES,
                   &r.dateDebut,
                   &r.dateFin,
                   &r.plageDate,
                   r.saison,
                   &tmpPlacementLibre,
                   r.idRepre) == 10)
        {

            r.placementLibre = tmpPlacementLibre;

            if (strcmp(r.idRepre, idRepreSuppr) == 0)
            {
                printf("Représentation avec ID %s supprimée.\n", r.idRepre);
                trouve = 1;
            }
            else
            {
                fprintf(fTemp, "%s|%s|%s|%s|%d|%d|%d|%s|%d|%s\n",
                        r.nomSalle,
                        r.titreRepresentation,
                        r.nomAuteur,
                        r.nomMES,
                        r.dateDebut,
                        r.dateFin,
                        r.plageDate,
                        r.saison,
                        r.placementLibre,
                        r.idRepre);
            }
        }
    }

    fclose(f);
    fclose(fTemp);

    if (trouve)
    {
        remove("representations.txt");
        rename("temp_representations.txt", "representations.txt");
        printf("Modification effectuée avec succès !\n");
    }
    else
    {
        remove("temp_representations.txt");
        printf("Aucune représentation trouvée avec l'ID %s.\n", idRepreSuppr);
    }
}

// v4 modif rep:

void ModifRepre()
{
    FILE *f = fopen("representations.txt", "r+"); // Ouverture en mode lecture/écriture
    if (f == NULL)
    {
        printf("Erreur : impossible d’ouvrir le fichier representations.txt\n");
        return;
    }

    char ligne[512]; // Buffer pour lire chaque ligne du fichier
    struct repre r;
    int tmpPlacementLibre;

    // Affichage des représentations disponibles
    printf("Liste des représentations disponibles :\n");
    while (fgets(ligne, sizeof(ligne), f) != NULL)
    {
        if (sscanf(ligne, "%[^|]|%[^|]|%[^|]|%[^|]|%d|%d|%d|%[^|]|%d|%s",
                   r.nomSalle,
                   r.titreRepresentation,
                   r.nomAuteur,
                   r.nomMES,
                   &r.dateDebut,
                   &r.dateFin,
                   &r.plageDate,
                   r.saison,
                   &tmpPlacementLibre,
                   r.idRepre) == 10)
        {

            r.placementLibre = tmpPlacementLibre; // Conversion en booléen
            if (r.dateDebut != 0)
            {
                // Affichage de la représentation actuelle
                printf("ID : %s, Titre : %s, Salle : %s, Date Début : %d, Date Fin : %d\n",
                       r.idRepre,
                       r.titreRepresentation,
                       r.nomSalle,
                       r.dateDebut,
                       r.dateFin);
            }
        }
    }

    // Demander à l'utilisateur quel ID de représentation il veut modifier
    char idRepreModif[TAILLE_ID];
    printf("\nEntrez l'ID de la représentation à modifier : ");
    scanf("%s", idRepreModif);

    // Réouvrir le fichier en mode lecture/écriture pour modification
    FILE *f2 = fopen("representations.txt", "r+");
    if (f2 == NULL)
    {
        printf("Erreur : impossible de réouvrir le fichier representations.txt pour modification\n");
        fclose(f);
        return;
    }

    // Créer un nouveau fichier pour stocker les données modifiées
    FILE *fTemp = fopen("temp_representations.txt", "w");
    if (fTemp == NULL)
    {
        printf("Erreur : impossible de créer le fichier temporaire\n");
        fclose(f2);
        fclose(f);
        return;
    }

    int modifie = 0; // Flag pour savoir si on a modifié la représentation
    // Relire chaque ligne et remplacer la ligne si nécessaire
    while (fgets(ligne, sizeof(ligne), f2) != NULL)
    {
        if (sscanf(ligne, "%[^|]|%[^|]|%[^|]|%[^|]|%d|%d|%d|%[^|]|%d|%s",
                   r.nomSalle,
                   r.titreRepresentation,
                   r.nomAuteur,
                   r.nomMES,
                   &r.dateDebut,
                   &r.dateFin,
                   &r.plageDate,
                   r.saison,
                   &tmpPlacementLibre,
                   r.idRepre) == 10)
        {

            r.placementLibre = tmpPlacementLibre;

            // Si on trouve la représentation à modifier
            if (strcmp(r.idRepre, idRepreModif) == 0)
            {
                printf("Représentation trouvée, vous pouvez la modifier :\n");

                // Demander à l'utilisateur quel champ il veut modifier
                int choix;
                printf("Que voulez-vous modifier ?\n");
                printf("1. Titre\n");
                printf("2. Salle\n");
                printf("3. Metteur en scène\n");
                printf("4. Date Début\n");
                printf("5. Date Fin\n");
                printf("6. Plage de dates\n");
                printf("7. Saison\n");
                printf("8. Placement libre\n");
                printf("9. Annuler\n");
                printf("Choix : ");
                scanf("%d", &choix);

                // Modifier les champs selon le choix de l'utilisateur
                switch (choix)
                {
                case 1:
                    printf("Entrez le nouveau titre : ");
                    scanf(" %[^\n]", r.titreRepresentation);
                    break;
                case 2:
                    printf("Entrez la nouvelle salle : ");
                    scanf(" %[^\n]", r.nomSalle);
                    break;
                case 3:
                    printf("Entrez le nouveau metteur en scène : ");
                    scanf(" %[^\n]", r.nomMES);
                    break;
                case 4:
                    printf("Entrez la nouvelle date de début (format AAAAMMJJ) : ");
                    scanf("%d", &r.dateDebut);
                    break;
                case 5:
                    printf("Entrez la nouvelle date de fin (format AAAAMMJJ) : ");
                    scanf("%d", &r.dateFin);
                    break;
                case 6:
                    printf("Entrez la nouvelle plage de dates : ");
                    scanf("%d", &r.plageDate);
                    break;
                case 7:
                    printf("Entrez la nouvelle saison : ");
                    scanf(" %[^\n]", r.saison);
                    break;
                case 8:
                    printf("Entrez le nouveau statut de placement libre (1 pour oui, 0 pour non) : ");
                    scanf("%d", &tmpPlacementLibre);
                    r.placementLibre = tmpPlacementLibre;
                    break;
                case 9:
                    printf("Annulation de la modification.\n");
                    fclose(fTemp);
                    fclose(f2);
                    fclose(f);
                    return;
                default:
                    printf("Choix invalide.\n");
                    fclose(fTemp);
                    fclose(f2);
                    fclose(f);
                    return;
                }

                // Écrire la ligne modifiée dans le fichier temporaire
                fprintf(fTemp, "%s|%s|%s|%s|%d|%d|%d|%s|%d|%s\n",
                        r.nomSalle,
                        r.titreRepresentation,
                        r.nomAuteur,
                        r.nomMES,
                        r.dateDebut,
                        r.dateFin,
                        r.plageDate,
                        r.saison,
                        r.placementLibre,
                        r.idRepre);
                modifie = 1;
            }
            else
            {
                // Si ce n'est pas la ligne à modifier, on l'écrit telle quelle dans le fichier temporaire
                fprintf(fTemp, "%s", ligne);
            }
        }
    }

    if (!modifie)
    {
        printf("Aucune représentation trouvée avec l'ID spécifié.\n");
    }
    else
    {
        printf("Représentation modifiée avec succès !\n");
    }

    // Fermer les fichiers
    fclose(fTemp);
    fclose(f2);
    fclose(f);

    // Remplacer le fichier original par le fichier temporaire
    remove("representations.txt");
    rename("temp_representations.txt", "representations.txt");
}

void AfficherPlace(struct place tab[], int nbPlaces)
{
    int i;
    printf("---------------------------------------------------------------------------------------------------------------\n");
    printf("| %-10s | %-5s | %-10s | %-30s | %-5s | %-10s | %-10s | %-10s |\n",
           "Salle", "N°", "Catégorie", "Zone", "Prix", "Tarif", "Handicapé", "Libre");
    printf("---------------------------------------------------------------------------------------------------------------\n");

    for (i = 0; i < nbPlaces; i++)
    {
        printf("| %-10s | %-5s | %-10s | %-30s | %-5d | %-10s | %-10s | %-10s |\n",
               tab[i].salle,
               tab[i].numero,
               tab[i].categorie,
               tab[i].zone,
               tab[i].prix,
               tab[i].tarif,
               tab[i].accesHandicap ? "Oui" : "Non",
               tab[i].estLibre ? "Oui" : "Réservée");
    }

    printf("---------------------------------------------------------------------------------------------------------------\n");
}

// Ajoute une séance (date+heure) à une représentation existante
void AjouterSeance(const char *fichierDates, struct repre tab[], int nbRepre)
{
    int index = -1;
    AfficherListeRepreEtChoix(tabRepre, nbRepre, &index);

    if (index < 0 || index >= nbRepre)
    {
        printf(" Index invalide.\n");
        return;
    }

    struct repre r = tabRepre[index];

    // Saisie des informations de séance
    int saisie, jj, mm, aaaa, date, heure,minute;

    printf("Année de la séance : ");
    scanf("%d",&aaaa);
    while(aaaa<2024){
        printf("L'année saisie est non valide, recommencez : ");
        scanf("%d",&aaaa);
    }
    printf("Mois de la séance (1 à 12) : ");
    scanf("%d",&mm);
    while(mm > 31 || mm<1){
        printf("Le mois saisi est non valide, recommencez : ");
        scanf("%d",&mm);
    }
    printf("Jour de la séance : ");
    scanf("%d",&jj);
    while(jj<1 || jj>31){
        printf("Le jour saisi est non valide, recommencez : ");
        scanf("%d",&jj);
    }
    date = aaaa * 10000 + mm * 100 + jj; // conversion → AAAAMMJJ

    printf("Heure de la séance : ");
    scanf("%d", &heure);
    while(heure>24 || heure <0 ){
        printf("L'heure saisie non valide, recommencez : ");
        scanf("%d",&heure); 
    }
    printf("Minute de la séance : ");
    scanf("%d",&minute);
    while(minute>60 || minute<0){
        printf("La minute saisie non valide, recommencez : ");
        scanf("%d",&minute); 
    }
    heure = heure*100+minute;

    // Vérification que la date est bien dans la plage autorisée
    if (date < r.dateDebut || date > r.dateFin)
    {
        printf(" Date de la séance saisie dépasse la plage de représentation de la pièce : (%d → %d).\n", r.dateDebut, r.dateFin);
        return;
    }

    // Génération du nom de fichier de places
    char fichierPlaces[100];
    sprintf(fichierPlaces, "places_%s_%d.txt", r.idRepre, date);

    // Ajout de la séance dans le fichier dates.txt
    FILE *f = fopen(fichierDates, "a");
    if (f == NULL)
    {
        printf("Erreur : impossible d’ouvrir %s\n", fichierDates);
        return;
    }

    fprintf(f, "%s %d %d %s\n", r.idRepre, date, heure, fichierPlaces);
    fclose(f);

    // Création automatique du fichier de places si besoin
    VerifierOuGenererFichierPlaces(r.nomSalle, fichierPlaces);

    printf(" Séance ajoutée : %s — %d à %d. Fichier : %s\n", r.idRepre, date, heure, fichierPlaces);
}

//-----------------Afficher les représentations--------------------

void AfficherListeRepreEtChoix(struct repre tab[], int nbRepre, int *indexChoisi)
{
    printf("Liste des représentations disponibles :\n");

    for (int i = 0; i < nbRepre; i++)
    {
        if (tab[i].dateDebut != 0)
        {
            int totalPlacesLibres = 0;
            FILE *f = fopen("dates.txt", "r");
            if (f != NULL)
            {
                char id[TAILLE_ID], fichierPlaces[100];
                int date, heure;
                while (fscanf(f, "%s %d %d %s", id, &date, &heure, fichierPlaces) != EOF)
                {
                    if (strcmp(id, tab[i].idRepre) == 0)
                    {
                        FILE *fp = fopen(fichierPlaces, "r");
                        struct place p;
                        while (fp && fscanf(fp, "%s %s %s %s %d %s %d %d",
                                            p.salle, p.numero, p.categorie, p.zone,
                                            &p.prix, p.tarif, (int *)&p.accesHandicap, (int *)&p.estLibre) != EOF)
                        {
                            if (p.estLibre)
                                totalPlacesLibres++;
                        }
                        if (fp)
                            fclose(fp);
                    }
                }
                fclose(f);
            }

            printf("%d. %s — Salle : %s — ID : %s — %s\n",
                   i + 1,
                   tab[i].titreRepresentation,
                   tab[i].nomSalle,
                   tab[i].idRepre,
                   (totalPlacesLibres == 0) ? "COMPLET" : totalPlacesLibres == 1 ? "1 place dispo"
                                                                                 : (sprintf((char[50]){0}, "%d places dispo", totalPlacesLibres), (char[50]){0}));
        }
    }

    printf("Entrez le numéro de la représentation à consulter : ");
    scanf("%d", indexChoisi);
    *indexChoisi -= 1;
}

//----------------------Séances par représentation---------------------------

void SeanceParRepresentation(const char *fichierDates, const char *idRepreCible)
{
    FILE *f = fopen(fichierDates, "r");
    if (f == NULL)
    {
        printf("Erreur : fichier %s introuvable\n", fichierDates);
        return;
    }

    char idRepre[TAILLE_ID], fichierPlaces[100];
    int date, heure;
    int compteur = 1;

    printf("\nSéances pour la représentation %s :\n", idRepreCible);
    while (fscanf(f, "%s %d %d %s", idRepre, &date, &heure, fichierPlaces) != EOF)
    {
        if (strcmp(idRepre, idRepreCible) == 0)
        {
            // Formater la date
            int annee = date / 10000;
            int mois = (date / 100) % 100;
            int jour = date % 100;

            // Compter les places disponibles dans le fichier correspondant
            FILE *fp = fopen(fichierPlaces, "r");
            int libres = 0;
            struct place p;
            while (fp && fscanf(fp, "%s %s %s %s %d %s %d %d",
                                p.salle, p.numero, p.categorie, p.zone,
                                &p.prix, p.tarif,
                                (int *)&p.accesHandicap, (int *)&p.estLibre) != EOF)
            {
                if (p.estLibre)
                    libres++;
            }
            if (fp)
                fclose(fp);

            printf("%d. Date : %04d/%02d/%02d — Heure : %02d:%02d — %s\n",
                   compteur, annee, mois, jour, heure / 100, heure % 100,
                   (libres == 0) ? "COMPLET" : "Places disponibles :");

            if (libres > 0)
            {
                printf(" (%d places libres)\n", libres);
            }
            else
            {
                printf("\n");
            }

            compteur++;
        }
    }

    if (compteur == 1)
    {
        printf("Aucune séance trouvée pour cette représentation.\n");
    }

    fclose(f);
}

//-----------------Générer numéro de réservation-------------------------

int GenererNumeroReservation()
{
    FILE *f = fopen("numReservations.txt", "r");
    int num = 0;

    if (f != NULL)
    {
        fscanf(f, "%d", &num);
        fclose(f);
    }

    num++;

    f = fopen("numReservations.txt", "w");
    if (f != NULL)
    {
        fprintf(f, "%d\n", num);
        fclose(f);
    }

    return num;
}

//---------------------Affichage des réservations-----------------

void AfficherReservations()
{
    FILE *f = fopen("reservations.txt", "r");
    if (f == NULL)
    {
        printf("Aucune réservation enregistrée (fichier introuvable).\n");
        return;
    }

    char numRes[10], idRepre[TAILLE_ID], numPlace[5], categorie[10], zone[50], tarif[20];
    int date, prix, numVisitor;

    printf("---------------------------------------------------------\n");
    printf("| %-8s | %-8s | %-8s | %-5s | %-10s | %-10s | %-4s | %-6s | %-8s |\n",
           "NumRes", "IDRepre", "Date", "Place", "Catégorie", "Zone", "Prix", "Tarif", "Visiteur");
    printf("---------------------------------------------------------\n");

    while (fscanf(f, "%s %s %d %s %s %s %d %s %d",
                  numRes, idRepre, &date, numPlace,
                  categorie, zone, &prix, tarif, &numVisitor) == 9)
    {

        printf("| %-8s | %-8s | %-8d | %-5s | %-10s | %-10s | %-4d€ | %-6s | %-8d |\n",
               numRes, idRepre, date, numPlace, categorie, zone, prix, tarif, numVisitor);
    }

    printf("---------------------------------------------------------\n");

    fclose(f);
}

//-----------------Affichage des places dispo filtrée----------------

// Nouvelle version — renvoie 1 si une place a été choisie, 0 sinon


// Nouvelle version — renvoie 1 si une place a été choisie, 0 sinon
int AfficherPlacesDispoFiltrée(const char *fichierPlaces, const char *nomSalle, char *numeroChoisie)
{
    FILE *f = fopen(fichierPlaces, "r");
    if (f == NULL)
    {
        // Utiliser fprintf(stderr, ...) pour les erreurs est préférable
        printf("Erreur : impossible d’ouvrir %s\n", fichierPlaces);
        return 0;
    }

    struct place tab[1000]; // Attention taille fixe
    int nb = 0;
    // Lire le fichier - Attention à la robustesse de fscanf
    // Utiliser %d pour lire directement les entiers
    while (nb < 1000 && fscanf(f, "%s %s %s %s %d %s %d %d",
                  tab[nb].salle, tab[nb].numero, tab[nb].categorie, tab[nb].zone,
                  &tab[nb].prix, tab[nb].tarif,
                  &tab[nb].accesHandicap, &tab[nb].estLibre) == 8) // Vérifier que 8 champs sont lus
    {
        // Filtrer ici si le fichier contient plusieurs salles
        // if (strcmp(tab[nb].salle, nomSalle) == 0) {
        //    nb++;
        // }
        // Sinon, si le fichier ne contient que la salle 'nomSalle', on incrémente directement
        nb++;
    }
    fclose(f);

    if (nb == 0) {
        printf("Aucune place trouvée dans le fichier pour cette salle.\n");
        return 0;
    }

    // Cas placement totalement libre (Logique originale conservée)
    if (EstPlacementLibre(nomSalle))
    {
        printf("\n--- Placement Libre ---\n");
        for (int i = 0; i < nb; i++)
        {
            if (tab[i].estLibre)
            {
                printf("Réservation de la première place libre disponible (placement libre).\n");
                tab[i].estLibre = 0;
                strcpy(numeroChoisie, tab[i].numero); // Même si générique, on copie

                // Réécriture Fichier
                FILE *fw = fopen(fichierPlaces, "w");
                 if (fw == NULL) {
                     fprintf(stderr, "Erreur CRITIQUE : Impossible de réouvrir %s pour écriture après réservation placement libre.\n", fichierPlaces);
                     // La place est marquée réservée en mémoire mais pas sauvée !
                     return 0; // Échec
                 }
                for (int j = 0; j < nb; j++)
                {
                    fprintf(fw, "%s %s %s %s %d %s %d %d\n",
                            tab[j].salle, tab[j].numero, tab[j].categorie, tab[j].zone,
                            tab[j].prix, tab[j].tarif, tab[j].accesHandicap, tab[j].estLibre);
                }
                fclose(fw);
                return 1; // Succès
            }
        }
        printf(" Aucune place disponible dans cette salle (placement libre).\n");
        return 0; // Échec
    }

    // --- Demande Handicap ---
    int isHandi;
    printf("Êtes-vous en situation de handicap ? (1 = oui, 0 = non) : ");
    // Boucle pour s'assurer d'une entrée valide
    while (scanf("%d", &isHandi) != 1 || (isHandi != 0 && isHandi != 1)) {
        printf("Entrée invalide. Veuillez saisir 1 pour oui ou 0 pour non : ");
        // Vider le buffer d'entrée en cas de saisie incorrecte (ex: lettres)
        while (getchar() != '\n');
    }

    int indexSelectionne = -1; // Indice de la place choisie dans le tableau 'tab'

    if (isHandi == 1)
    {
        int index = 1; // Index pour l'affichage (commence à 1)
        int dispo[1000]; // Stocke les indices REELS (de tab) des places affichées
        int nbPlacesAffichees = 0;

        printf("\n--- Places accessibles disponibles ---\n");
        for (int i = 0; i < nb; i++)
        {
            // Cherche places libres ET accessibles
            if (tab[i].estLibre && tab[i].accesHandicap)
            {
                printf("%d. Place : %-5s | Zone : %-20s | Catégorie : %-8s | Prix : %d€ | Tarif : %s\n",
                       index, tab[i].numero, tab[i].zone, tab[i].categorie, tab[i].prix, tab[i].tarif);
                dispo[index - 1] = i; // Stocke l'indice réel de tab (base 0)
                index++;
                nbPlacesAffichees++;
            }
        }

        if (nbPlacesAffichees == 0) // Vérifier s'il y avait des places à afficher
        {
            printf("Aucune place accessible disponible.\n");
            return 0; // Aucune place choisie
        }

        int choix;
        printf("Numéro de la place à réserver (1-%d) : ", nbPlacesAffichees);
        // Boucle de validation pour le choix
        while (scanf("%d", &choix) != 1 || choix <= 0 || choix > nbPlacesAffichees) {
            printf("Choix invalide. Entrez un numéro entre 1 et %d : ", nbPlacesAffichees);
            while (getchar() != '\n'); // Vider buffer
        }

        indexSelectionne = dispo[choix - 1]; // Récupère l'indice réel dans tab
        strcpy(numeroChoisie, tab[indexSelectionne].numero);
        // La modification de tab[indexSelectionne].estLibre se fera à la fin
    }
    else // Cas non-handicap : sélection par zone puis catégorie
    {
        // 1. Trouver les zones uniques disponibles (non-handi)
        char zones[50][50]; // Utilisation du nom de variable original
        int nbZones = 0;    // Utilisation du nom de variable original
        for (int i = 0; i < nb; i++) {
            // Considérer seulement places libres et non-handi
            if (tab[i].estLibre && !tab[i].accesHandicap) {
                int zExiste = 0;
                for (int j = 0; j < nbZones; j++) {
                    if (strcmp(zones[j], tab[i].zone) == 0) {
                        zExiste = 1;
                        break;
                    }
                }
                if (!zExiste && nbZones < 50) { // Ajouter si nouvelle et espace dispo
                    strcpy(zones[nbZones], tab[i].zone);
                    nbZones++;
                }
            }
        }

        if (nbZones == 0) {
            printf("Aucune zone avec des places standard libres disponible.\n");
            return 0;
        }

        // 2. Afficher les zones et demander le choix de la zone
        printf("\nZones disponibles :\n");
        for (int i = 0; i < nbZones; i++) {
            printf("%d. %s\n", i + 1, zones[i]);
        }

        int zChoix; // Utilisation du nom de variable original
        printf("Choisissez une zone (1-%d) : ", nbZones);
        while (scanf("%d", &zChoix) != 1 || zChoix <= 0 || zChoix > nbZones) {
             printf("Choix invalide. Entrez un numéro entre 1 et %d : ", nbZones);
             while (getchar() != '\n'); // Vider buffer
        }
        // zChoix est 1-based, l'indice est zChoix - 1
        char zoneChoisieStr[50];
        strcpy(zoneChoisieStr, zones[zChoix - 1]);

        // 3. Trouver les catégories uniques DANS la zone choisie
        char categories[10][10]; // Utilisation du nom de variable original
        int nbCat = 0;           // Utilisation du nom de variable original
        for (int i = 0; i < nb; i++) {
            // Chercher places libres, non-handi, DANS la zone choisie
            if (tab[i].estLibre && !tab[i].accesHandicap && strcmp(tab[i].zone, zoneChoisieStr) == 0) {
                int cExiste = 0;
                for (int j = 0; j < nbCat; j++) {
                    if (strcmp(categories[j], tab[i].categorie) == 0) {
                        cExiste = 1;
                        break;
                    }
                }
                if (!cExiste && nbCat < 10) { // Ajouter si nouvelle et espace dispo
                    strcpy(categories[nbCat], tab[i].categorie);
                    nbCat++;
                }
            }
        }

        if (nbCat == 0) {
             printf("Aucune catégorie avec des places libres trouvée dans la zone '%s'.\n", zoneChoisieStr);
             return 0; // Pas de catégorie, donc pas de place
        }

        // 4. Afficher les catégories et demander le choix de la catégorie
        printf("\nCatégories disponibles dans la zone '%s':\n", zoneChoisieStr);
        for (int i = 0; i < nbCat; i++) {
            printf("%d. %s\n", i + 1, categories[i]);
        }
        int cChoix; // Utilisation du nom de variable original
        printf("Choisissez une catégorie (1-%d) : ", nbCat);
         while (scanf("%d", &cChoix) != 1 || cChoix <= 0 || cChoix > nbCat) {
             printf("Choix invalide. Entrez un numéro entre 1 et %d : ", nbCat);
             while (getchar() != '\n'); // Vider buffer
        }
        // cChoix est 1-based, l'indice est cChoix - 1
        char categorieChoisieStr[10];
        strcpy(categorieChoisieStr, categories[cChoix - 1]);

        // 5. Afficher les places correspondantes au filtre final
        int index = 1; // Index pour l'affichage (commence à 1)
        int dispo[1000]; // Stocke les indices REELS (de tab) des places affichées
        int nbPlacesAffichees = 0;

        printf("\n--- Places disponibles (Zone: %s, Catégorie: %s) ---\n", zoneChoisieStr, categorieChoisieStr);
        for (int i = 0; i < nb; i++)
        {
            // Filtre final: libre, non-handi, bonne zone, bonne catégorie
            if (tab[i].estLibre && !tab[i].accesHandicap &&
                strcmp(tab[i].zone, zoneChoisieStr) == 0 &&
                strcmp(tab[i].categorie, categorieChoisieStr) == 0)
            {
                printf("%d. Place : %-5s \n",
                       index, tab[i].numero);
                dispo[index - 1] = i; // Stocke l'indice réel de tab
                index++;
                nbPlacesAffichees++;
            }
        }

        if (nbPlacesAffichees == 0) // Double-vérification, ne devrait pas arriver si nbCat > 0
        {
            printf("Aucune place disponible pour cette zone/catégorie (inattendu).\n");
            return 0;
        }

        // 6. Demander le choix final de la place
        int choix; // Utilisation du nom de variable original
        printf("Numéro de la place à réserver (1-%d) : ", nbPlacesAffichees);
        while (scanf("%d", &choix) != 1 || choix <= 0 || choix > nbPlacesAffichees) {
            printf("Choix invalide. Entrez un numéro entre 1 et %d : ", nbPlacesAffichees);
            while (getchar() != '\n'); // Vider buffer
        }

        indexSelectionne = dispo[choix - 1]; // Récupère l'indice réel dans tab
        strcpy(numeroChoisie, tab[indexSelectionne].numero);
         // La modification de tab[indexSelectionne].estLibre se fera juste après
    }

    // --- Actions communes après sélection (Handicap ou Standard) ---
    if (indexSelectionne != -1) { // Vérifie qu'une place a bien été sélectionnée
        // Marquer la place comme non libre
        tab[indexSelectionne].estLibre = 0;
        printf("Place %s marquée comme réservée.\n", numeroChoisie);

        // Mise à jour du fichier de places
        FILE *fw = fopen(fichierPlaces, "w");
        if (fw == NULL) {
            fprintf(stderr, "Erreur CRITIQUE : Impossible de sauvegarder les modifications dans %s !\n", fichierPlaces);
            // La réservation est perdue au prochain lancement !
            // Vous pourriez vouloir annuler l'opération ou logger l'erreur sérieusement ici.
            return 0; // Indiquer un échec même si la place a été choisie en mémoire.
        }
        for (int i = 0; i < nb; i++)
        {
            fprintf(fw, "%s %s %s %s %d %s %d %d\n",
                    tab[i].salle, tab[i].numero, tab[i].categorie, tab[i].zone,
                    tab[i].prix, tab[i].tarif,
                    tab[i].accesHandicap, tab[i].estLibre);
        }
        fclose(fw);

        return 1; // Succès : une place a été choisie et le fichier (normalement) mis à jour
    } else {
        // Ce cas ne devrait pas être atteint si les retours 0 précédents fonctionnent,
        // mais c'est une sécurité.
        printf("Aucune place n'a finalement été sélectionnée.\n");
        return 0;
    }
}

/*
int AfficherPlacesDispoFiltrée(const char *fichierPlaces, const char *nomSalle, char *numeroChoisie)
{
    FILE *f = fopen(fichierPlaces, "r");
    if (f == NULL)
    {
        printf("Erreur : impossible d’ouvrir %s\n", fichierPlaces);
        return 0;
    }

    struct place tab[1000];
    int nb = 0;
    while (fscanf(f, "%s %s %s %s %d %s %d %d",
                  tab[nb].salle, tab[nb].numero, tab[nb].categorie, tab[nb].zone,
                  &tab[nb].prix, tab[nb].tarif,
                  (int *)&tab[nb].accesHandicap, (int *)&tab[nb].estLibre) != EOF)
    {
        nb++;
    }
    fclose(f);

    // Cas placement totalement libre
    if (EstPlacementLibre(nomSalle))
    {
        for (int i = 0; i < nb; i++)
        {
            if (tab[i].estLibre)
            {
                tab[i].estLibre = 0;
                strcpy(numeroChoisie, tab[i].numero);

                FILE *fw = fopen(fichierPlaces, "w");
                for (int j = 0; j < nb; j++)
                {
                    fprintf(fw, "%s %s %s %s %d %s %d %d\n",
                            tab[j].salle, tab[j].numero, tab[j].categorie, tab[j].zone,
                            tab[j].prix, tab[j].tarif, tab[j].accesHandicap, tab[j].estLibre);
                }
                fclose(fw);
                return 1;
            }
        }
        printf(" Aucune place disponible dans cette salle.\n");
        return 0;
    }

    int isHandi;
    printf("Êtes-vous en situation de handicap ? (1 = oui, 0 = non) : ");
    scanf("%d", &isHandi);

    if (isHandi == 1)
    {
        int index = 1;
        int dispo[1000];
        printf("\n--- Places accessibles disponibles ---\n");
        for (int i = 0; i < nb; i++)
        {
            if (tab[i].estLibre && tab[i].accesHandicap)
            {
                printf("%d. Place : %-5s | Zone : %-20s | Catégorie : %-8s | Prix : %d€ | Tarif : %s\n",
                       index, tab[i].numero, tab[i].zone, tab[i].categorie, tab[i].prix, tab[i].tarif);
                dispo[index++] = i;
            }
        }
        if (index == 1)
        {
            printf("Aucune place accessible disponible.\n");
            return 0;
        }

        int choix;
        printf("Numéro de la place à réserver : ");
        scanf("%d", &choix);
        if (choix <= 0 || choix >= index)
        {
            printf("Choix invalide.\n");
            return 0;
        }

        strcpy(numeroChoisie, tab[dispo[choix]].numero);
        tab[dispo[choix]].estLibre = 0;
    }
    else
    {
        // Zones et catégories disponibles
        char zones[50][50], categories[10][10];
        int nbZones = 0, nbCat = 0;
int j = 0;
        for (int i = 0; i < nb; i++)
        {//cas si la zone est Orchestre, on garde les catégories A et B
            if (strcmp(zones[j],"Orchestre")==0){
            //a, b , c
              int zExiste = 0, cExiste = 0;
              for (j = 0; j <= 2; j++)//2 car on s'arrête 
                  if (strcmp(zones[j], tab[i].zone) == 0)
                      zExiste = 1;
              for ( j = 0; j < nbCat; j++)
                  if (strcmp(categories[j], tab[i].categorie) == 0)
                      cExiste = 1;
              if (!zExiste)
                  strcpy(zones[nbZones++], tab[i].zone);
              if (!cExiste)
                  strcpy(categories[nbCat++], tab[i].categorie);
                  
                  nbZones = 2; // nombre de zone à afficher
               
        }//cas si la zone est Corbeille, on garde les catégories A, B et C
            
            else if (strcmp(zones[j],"Corbeille")==0){
            
              int zExiste = 0, cExiste = 0;
              for (int j = 0; j <= 2; j++) //on prend les 3 types de catégories
                  if (strcmp(zones[j], tab[i].zone) == 0)
                      zExiste = 1;
              for (int j = 0; j < nbCat; j++)
                  if (strcmp(categories[j], tab[i].categorie) == 0)
                      cExiste = 1;
              if (!zExiste)
                  strcpy(zones[nbZones++], tab[i].zone);
              if (!cExiste)
                  strcpy(categories[nbCat++], tab[i].categorie);
                  
                  nbZones = 3; // nombre de zone à afficher
           }
           //
           
            else if (strcmp(zones[j],"1erBalcon")==0){
            
              int zExiste = 0, cExiste = 0;
               for (int j = 0; j <= 2; j++) //on prend les 3 types de catégories
                  if (strcmp(zones[j], tab[i].zone) == 0)
                      zExiste = 1;
              for (int j = 0; j < nbCat; j++)
                  if (strcmp(categories[j], tab[i].categorie) == 0)
                      cExiste = 1;
              if (!zExiste)
                  strcpy(zones[nbZones++], tab[i].zone);
              if (!cExiste)
                  strcpy(categories[nbCat++], tab[i].categorie);
           
           nbZones = 3; // nombre de zone à afficher
        }
        else if (strcmp(zones[j],"2eBalcon")==0){//uniquement catégories B et C
            
              int zExiste = 0, cExiste = 0;
              for (int j = 1; j <= 2; j++)// on prend les catégories B et C ici, donc B et C
                  if (strcmp(zones[j], tab[i].zone) == 0)
                      zExiste = 1;
              for (int j = 0; j < nbCat; j++)
                  if (strcmp(categories[j], tab[i].categorie) == 0)
                      cExiste = 1;
              if (!zExiste)
                  strcpy(zones[nbZones++], tab[i].zone);
              if (!cExiste)
                  strcpy(categories[nbCat++], tab[i].categorie);
               nbZones = 2; // nombre de zone à afficher
        }
        else if (strcmp(zones[j],"Galerie")==0){//uniquement catégorie C
            
              int zExiste = 0, cExiste = 0;
              for (int j = 2; j = 2; j++)// on prend uniquement catégorie C ici
                  if (strcmp(zones[j], tab[i].zone) == 0)
                      zExiste = 1;
              for (int j = 0; j < nbCat; j++)
                  if (strcmp(categories[j], tab[i].categorie) == 0)
                      cExiste = 1;
              if (!zExiste)
                  strcpy(zones[nbZones++], tab[i].zone);
              if (!cExiste)
                  strcpy(categories[nbCat++], tab[i].categorie);
               nbZones = 2; // nombre de zone à afficher
        }

        printf("\nZones disponibles :\n");
        for (int i = 0; i < nbZones; i++)
            printf("%d. %s\n", i + 1, zones[i]);
        int zChoix;
        printf("Choisissez une zone : ");
        scanf("%d", &zChoix);
        zChoix--;

        printf("\nCatégories disponibles :\n");
        for (int i = 0; i < nbCat; i++)
            printf("%d. %s\n", i + 1, categories[i]);
        int cChoix;
        printf("Choisissez une catégorie : ");
        scanf("%d", &cChoix);
        cChoix--;

        int index = 1;
        int dispo[1000];
        printf("\n--- Places disponibles ---\n");
        for (int i = 0; i < nb; i++)
        {
            if (tab[i].estLibre &&
                strcmp(tab[i].zone, zones[zChoix]) == 0 &&
                strcmp(tab[i].categorie, categories[cChoix]) == 0)
            {
                printf("%d. Place : %-5s | Prix : %d€ | Tarif : %s\n",
                       index, tab[i].numero, tab[i].prix, tab[i].tarif);
                dispo[index++] = i;
            }
        }

        if (index == 1)
        {
            printf("Aucune place disponible pour cette zone/catégorie.\n");
            return 0;
        }

        int choix;
        printf("Numéro de la place à réserver : ");
        scanf("%d", &choix);
        if (choix <= 0 || choix >= index)
        {
            printf("Choix invalide.\n");
            return 0;
        }

        strcpy(numeroChoisie, tab[dispo[choix]].numero);
        tab[dispo[choix]].estLibre = 0;
    }

    // Mise à jour du fichier de places
    FILE *fw = fopen(fichierPlaces, "w");
    for (int i = 0; i < nb; i++)
    {
        fprintf(fw, "%s %s %s %s %d %s %d %d\n",
                tab[i].salle, tab[i].numero, tab[i].categorie, tab[i].zone,
                tab[i].prix, tab[i].tarif,
                tab[i].accesHandicap, tab[i].estLibre);
    }
    fclose(fw);

    return 1;
}
}
*/
//----------------------Vérification de l'existence du fichier des places d'une séance-----------------------------
void VerifierOuGenererFichierPlaces(const char *nomSalle, const char *fichierPlaces)
{
    FILE *test = fopen(fichierPlaces, "r");
    if (test != NULL)
    {
        fclose(test);
        return; // Le fichier existe déjà → rien à faire
    }

    // Déterminer le fichier modèle à copier
    char fichierModele[100];

    if (strcmp(nomSalle, "RICHELIEU") == 0)
        strcpy(fichierModele, "places_richelieu.txt");
    else if (strcmp(nomSalle, "SOULIER DE SATIN") == 0)
        strcpy(fichierModele, "places_soulier_satin.txt");
    else if (strcmp(nomSalle, "STUDIO") == 0)
        strcpy(fichierModele, "places_studio.txt");
    else if (strcmp(nomSalle, "VIEUX-COLOMBIER") == 0)
        strcpy(fichierModele, "places_vieux_colombier.txt");
    else if (strcmp(nomSalle, "BIFRONTALE") == 0)
        strcpy(fichierModele, "places_bifrontal.txt");
    else
    {
        printf("Salle inconnue : %s\n", nomSalle);
        return;
    }

    FILE *src = fopen(fichierModele, "r");
    if (src == NULL)
    {
        printf("Erreur : modèle introuvable (%s)\n", fichierModele);
        return;
    }

    FILE *dest = fopen(fichierPlaces, "w");
    if (dest == NULL)
    {
        fclose(src);
        printf("Erreur : impossible de créer %s\n", fichierPlaces);
        return;
    }

    char ligne[200];
    while (fgets(ligne, sizeof(ligne), src))
    {
        fputs(ligne, dest);
    }

    fclose(src);
    fclose(dest);
    printf("Fichier %s généré avec succès à partir de %s.\n", fichierPlaces, fichierModele);
}

//-----------Réservation --------------------------

//-----------Réservation --------------------------

void ReserverPlace(const char *fichierPlaces, const char *numeroPlace, const char *idRepre, int date)
{
    int visiteurFinal = numVisitorConnecte ;

    // Si mode admin : demande du numéro de visiteur
    if (mode == 0)
    {
        int trouve = 0;
        struct visitor v;

        printf("Numéro du visiteur : ");
        scanf("%d", &visiteurFinal);
        
printf("DEBUG : Visiteur lu = %d\n", v.numVisitor);
            printf("DEBUG : Visiteur saisi = %d\n", visiteurFinal);
        

        FILE *fic = fopen("utilisateurs.txt", "r");
        if (fic != NULL)
        {
            while (fscanf(fic, "%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%[^|]|%d|%[^|]|%[^|]|%d|%d\n",
                          v.nom, v.prenom, v.mail, &v.dateNaiss,
                          v.mdp, v.numTel, v.adresse, &v.abo,
                          v.typeAbo, v.dateDebutAbo, &v.numAbo, &v.numVisitor) == 12)
            {
            
            printf("DEBUG : Visiteur lu = %d\n", v.numVisitor);
            printf("DEBUG : Visiteur lu = %d\n", visiteurFinal);
                if (v.numVisitor == visiteurFinal)
                {
                    trouve = 1;
                    break;
                }
            }
            fclose(fic);
        }

        if (!trouve)
        {
            printf(" Visiteur introuvable.\n");
            return;
        }
    }

    // ... (le reste ne change pas)


    // Chargement des places
    FILE *f = fopen(fichierPlaces, "r");
    if (f == NULL)
    {
        printf("Erreur ouverture fichier %s\n", fichierPlaces);
        return;
    }

    struct place tab[1000];
    int nb = 0, trouve = 0;

    while (fscanf(f, "%s %s %s %s %d %s %d %d",
                  tab[nb].salle, tab[nb].numero, tab[nb].categorie, tab[nb].zone,
                  &tab[nb].prix, tab[nb].tarif,
                  (int *)&tab[nb].accesHandicap, (int *)&tab[nb].estLibre) != EOF)
    {

        if (strcmp(tab[nb].numero, numeroPlace) == 0)
        {
            trouve = 1;
            // On ne remet pas à 0 ici, car ça a déjà été fait si besoin
        }

        nb++;
    }
    fclose(f);

    if (!trouve)
    {
        printf(" Place introuvable ou déjà réservée.\n");
        return;
    }

    // Réécriture du fichier places
    f = fopen(fichierPlaces, "w");
    if (f == NULL)
    {
        printf("Erreur enregistrement fichier %s\n", fichierPlaces);
        return;
    }

    for (int i = 0; i < nb; i++)
    {
        fprintf(f, "%s %s %s %s %d %s %d %d\n",
                tab[i].salle, tab[i].numero, tab[i].categorie, tab[i].zone,
                tab[i].prix, tab[i].tarif,
                tab[i].accesHandicap, tab[i].estLibre);
    }
    fclose(f);

    // Enregistrement dans reservations.txt
    FILE *res = fopen("reservations.txt", "a");
    if (res == NULL)
    {
        printf("Erreur ouverture reservations.txt\n");
        return;
    }

    int numReservation = GenererNumeroReservation();

    for (int i = 0; i < nb; i++)
    {
        if (strcmp(tab[i].numero, numeroPlace) == 0)
        {
            fprintf(res, "R%06d %s %d %s %s %s %d %s %d\n",
                    numReservation,
                    idRepre,
                    date,
                    tab[i].numero,
                    tab[i].categorie,
                    tab[i].zone,
                    tab[i].prix,
                    tab[i].tarif,
                    visiteurFinal);
            break;
        }
    }
    fclose(res);

    // Vérifier si placement libre pour message final
    if (EstPlacementLibre(tab[0].salle))
    {
        printf("Réservation R%06d confirmée (placement libre). Vous choisirez votre siège à votre arrivée.\n", numReservation);
    }
    else
    {
        printf(" Réservation R%06d confirmée pour la place %s (Visiteur %d).\n", numReservation, numeroPlace, visiteurFinal);
    }
}

//-----------cHARGEMENT FICHIER REPRÉSENTATION (PAS SÉANCE, JE DIS BIEN REPRÉSENTARTION), JE LE METS ICI MAIS ON AURA UNE FONCTION AU DÉBUT QUI CHARGE TOUS LES FICHIERS !--------------

void ChargerRepresentations()
{
    FILE *f = fopen("representations.txt", "r");
    if (f == NULL)
    {
        printf("⚠️ Fichier representations.txt introuvable. Aucune représentation chargée.\n");
        return;
    }

    char ligne[512];
    struct repre r;
    int tmpPlacementLibre;

    nbRepre = 0; // remet à zéro avant de recharger
    while (fgets(ligne, sizeof(ligne), f))
    {
        if (sscanf(ligne, "%[^|]|%[^|]|%[^|]|%[^|]|%d|%d|%d|%[^|]|%d|%s",
                   r.nomSalle,
                   r.titreRepresentation,
                   r.nomAuteur,
                   r.nomMES,
                   &r.dateDebut,
                   &r.dateFin,
                   &r.plageDate,
                   r.saison,
                   &tmpPlacementLibre,
                   r.idRepre) == 10)
        {
            r.placementLibre = tmpPlacementLibre;
            tabRepre[nbRepre++] = r;
        }
    }

    fclose(f);
    printf(" %d représentations chargées depuis representations.txt\n", nbRepre);
}

//----------------mise en majuscule-----------------------

void ToUpper(char *str)
{
    for (int i = 0; str[i]; i++)
    {
        str[i] = toupper(str[i]);
    }
}

//----------------Parcours complet réservation------------------

void ParcoursReservationComplet(struct repre tab[], int nbRepre)
{
    int indexRepre = -1;
    AfficherListeRepreEtChoix(tab, nbRepre, &indexRepre);

    if (indexRepre < 0 || indexRepre >= nbRepre)
    {
        printf(" Index de représentation invalide.\n");
        return;
    }

    char idRepreChoisie[TAILLE_ID];
    strcpy(idRepreChoisie, tab[indexRepre].idRepre);
    char nomSalle[NOM_SALLE];
    strcpy(nomSalle, tab[indexRepre].nomSalle);
    ToUpper(nomSalle); // pour la gestion cohérente dans VerifierOuGenererFichierPlaces

    // Liste des séances associées
    FILE *f = fopen("dates.txt", "r");
    if (!f)
    {
        printf("Erreur ouverture fichier dates.txt\n");
        return;
    }

    int dates[100], heures[100];
    char fichiersPlaces[100][100];
    int nbSeances = 0;
    char idTemp[TAILLE_ID];
    int date, heure;
    char fichierTemp[100];

    while (fscanf(f, "%s %d %d %s", idTemp, &date, &heure, fichierTemp) == 4)
    {
        if (strcmp(idTemp, idRepreChoisie) == 0)
        {
            dates[nbSeances] = date;
            heures[nbSeances] = heure;
            strcpy(fichiersPlaces[nbSeances], fichierTemp);
            nbSeances++;
        }
    }
    fclose(f);

    if (nbSeances == 0)
    {
        printf(" Aucune séance disponible pour cette représentation.\n");
        return;
    }

    // Affichage des séances
    printf("\nSéances disponibles :\n");
    for (int i = 0; i < nbSeances; i++)
    {
        int annee = dates[i] / 10000;
        int mois = (dates[i] / 100) % 100;
        int jour = dates[i] % 100;
        printf("%d. Date : %04d/%02d/%02d — Heure : %02d:%02d\n",
               i + 1, annee, mois, jour, heures[i] / 100, heures[i] % 100);
    }

    int choixSeance;
    printf("Choisissez une date de séance (saisir un numéro) : ");
    scanf("%d", &choixSeance);
    choixSeance--;

    if (choixSeance < 0 || choixSeance >= nbSeances)
    {
        printf(" Numéro de séance invalide.\n");
        return;
    }

    // Générer le fichier de places si nécessaire
    VerifierOuGenererFichierPlaces(nomSalle, fichiersPlaces[choixSeance]);

    // Choix de la place
    char numeroChoisie[5];
    if (AfficherPlacesDispoFiltrée(fichiersPlaces[choixSeance], nomSalle, numeroChoisie))
    {
        ReserverPlace(fichiersPlaces[choixSeance], numeroChoisie, idRepreChoisie, dates[choixSeance]);
    }
    else
    {
        printf(" Aucune place sélectionnée. Réservation annulée.\n");
    }
}

//-------------------Verifier si une salle en placement libre-----------------

// comment le déclarer en haut ?
bool EstPlacementLibre(const char *nomSalle)
{
    return (strcmp(nomSalle, "STUDIO") == 0 ||
            strcmp(nomSalle, "VIEUX-COLOMBIER") == 0 ||
            strcmp(nomSalle, "BIFRONTALE") == 0);
}

//---------------Annuler une Réservation-----------------------

void AnnulerReservation()
{
    struct reserv tab[1000];
    int nb = 0;
    FILE *f = fopen("reservations.txt", "r");
    if (!f)
    {
        printf("Aucune réservation trouvée.\n");
        return;
    }

    while (fscanf(f, "%s %s %d %s %s %s %d %s %d",
                  tab[nb].numRes,
                  tab[nb].idRepre,
                  &tab[nb].date,
                  tab[nb].numPlace,
                  tab[nb].categorie,
                  tab[nb].zone,
                  &tab[nb].prix,
                  tab[nb].tarif,
                  &tab[nb].numVisitor) == 9)
    {
        nb++;
    }
    fclose(f);

    int numVisiteurRecherche = -1;

    // --- MODE ADMIN : rechercher utilisateur ---
    if (mode == 0)
    {
        char nom[TAILLE_NOM], prenom[TAILLE_PRENOM];
        int dateNaiss;

        printf("Nom : ");
        scanf("%s", nom);
        ToUpper(nom);
        printf("Prénom : ");
        scanf("%s", prenom);
        ToUpper(prenom);
        printf("Date de naissance (JJMMAAAA) : ");
        scanf("%d", &dateNaiss);

        struct visitor v;
        FILE *fic = fopen("utilisateurs.txt", "r");
        if (!fic)
        {
            printf("Erreur ouverture utilisateurs.txt\n");
            return;
        }

        while (fscanf(fic, "%s %s %s %d %s %s %s %d %s %s %d %d",
                      v.nom, v.prenom, v.mail, &v.dateNaiss, v.mdp, v.numTel,
                      v.adresse, (int *)&v.abo, v.typeAbo, v.dateDebutAbo,
                      &v.numAbo, &v.numVisitor) == 12)
        {
            char n1[TAILLE_NOM], p1[TAILLE_PRENOM];
            strcpy(n1, v.nom);
            strcpy(p1, v.prenom);
            ToUpper(n1);
            ToUpper(p1);
            
            
            ToUpper(nom);
            ToUpper(prenom);
            if (strcmp(n1, nom) == 0 && strcmp(p1, prenom) == 0 && v.dateNaiss == dateNaiss)
            {
                numVisiteurRecherche = v.numVisitor;
                break;
            }
        }
        fclose(fic);
    }
    else
    {
        // --- MODE CLIENT CONNECTÉ ---
        numVisiteurRecherche = numVisitorConnecte;
    }

    if (numVisiteurRecherche == -1)
    {
        printf(" Visiteur introuvable.\n");
        return;
    }

    // --- AFFICHAGE DES RESERVATIONS POUR CE VISITEUR ---
    int indexRes[100];
    int nbRes = 0;
    for (int i = 0; i < nb; i++)
    {
        if (tab[i].numVisitor == numVisiteurRecherche)
        {
            printf("%d. Réservation %s | Représentation : %s | Date : %d | Place : %s (%s/%s) | %d€ | Tarif : %s\n",
                   nbRes + 1, tab[i].numRes, tab[i].idRepre, tab[i].date,
                   tab[i].numPlace, tab[i].zone, tab[i].categorie,
                   tab[i].prix, tab[i].tarif);
            indexRes[nbRes++] = i;
        }
    }

    if (nbRes == 0)
    {
        printf("Aucune réservation trouvée pour ce visiteur.\n");
        return;
    }

    int choix;
    printf("Quel numéro souhaitez-vous annuler ? ");
    scanf("%d", &choix);
    if (choix < 1 || choix > nbRes)
    {
        printf(" Choix invalide.\n");
        return;
    }

    int indexSuppr = indexRes[choix - 1];

    // --- Confirmation ---
    printf("Êtes-vous sûr de vouloir annuler la réservation %s ? (1 = oui / 0 = non) : ", tab[indexSuppr].numRes);
    int confirm;
    scanf("%d", &confirm);
    if (confirm != 1)
    {
        printf("Annulation interrompue.\n");
        return;
    }

    // --- Réécriture des réservations sauf celle à supprimer ---
    f = fopen("reservations.txt", "w");
    for (int i = 0; i < nb; i++)
    {
        if (i != indexSuppr)
        {
            fprintf(f, "%s %s %d %s %s %s %d %s %d\n",
                    tab[i].numRes,
                    tab[i].idRepre,
                    tab[i].date,
                    tab[i].numPlace,
                    tab[i].categorie,
                    tab[i].zone,
                    tab[i].prix,
                    tab[i].tarif,
                    tab[i].numVisitor);
        }
    }
    fclose(f);

    // --- Libération de la place dans le fichier places_X_Y.txt ---
    char fichierPlaces[100];
    sprintf(fichierPlaces, "places_%s_%d.txt", tab[indexSuppr].idRepre, tab[indexSuppr].date);
    FILE *pf = fopen(fichierPlaces, "r");
    struct place places[1000];
    int n = 0;

    if (pf)
    {
        while (fscanf(pf, "%s %s %s %s %d %s %d %d",
                      places[n].salle, places[n].numero,
                      places[n].categorie, places[n].zone,
                      &places[n].prix, places[n].tarif,
                      (int *)&places[n].accesHandicap,
                      (int *)&places[n].estLibre) != EOF)
        {
            n++;
        }
        fclose(pf);
    }

    for (int i = 0; i < n; i++)
    {
        if (strcmp(places[i].numero, tab[indexSuppr].numPlace) == 0)
        {
            places[i].estLibre = 1;
            break;
        }
    }

    pf = fopen(fichierPlaces, "w");
    for (int i = 0; i < n; i++)
    {
        fprintf(pf, "%s %s %s %s %d %s %d %d\n",
                places[i].salle, places[i].numero, places[i].categorie,
                places[i].zone, places[i].prix, places[i].tarif,
                places[i].accesHandicap, places[i].estLibre);
    }
    fclose(pf);

    printf(" Réservation %s annulée et place libérée.\n", tab[indexSuppr].numRes);
}

//---------------QUITTER-------------------------

void quitter()
{
    printf("Au revoir!\n");
}
