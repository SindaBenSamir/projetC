#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Définir la structure Date
struct Date {
    int annee;
    int mois;
    int jour;
};

typedef struct Liste_bus Liste_bus;
struct Liste_bus {
    int idBus;
    int capacite;
    char destination[100];
    struct Liste_bus* suiv;
};
typedef struct Liste_bus* Bus;

typedef struct Liste_Voyageur Liste_Voyageur;
struct Liste_Voyageur {
    int idVoyageur;
    char nom[50];
    char prenom[50];
    struct Liste_Voyageur* suiv;
};
typedef struct Liste_Voyageur* Voyageur;

typedef struct Liste_Reservation Liste_Reservation;
struct Liste_Reservation {
    int idReservation;
    Voyageur voyageur;
    Bus bus;
    struct Date date; // Utiliser la nouvelle structure Date
    struct Liste_Reservation* suiv;
};
typedef struct Liste_Reservation* Reservation;

Bus listeBuses = NULL;
Voyageur listeVoyageurs = NULL;
Reservation listeReservations = NULL;

void afficherMenu();
void afficherBuses();
void afficherVoyageurs();
void afficherReservations();
void afficherUneReservation();
void ajouterBus(int idBus, int capacite, const char* destination);
void ajouterVoyageur(int idVoyageur, const char* nom, const char* prenom);
void faireReservation(int idReservation, int idVoyageur, int idBus, struct Date date);
void modifier_Reservation(int idReservation, struct Date newDate);
void supprimer_reservation(int idReservation);
int placeDisponible(int idBus);

int main() {
    int choix;

    do {
        afficherMenu();
        printf("Choisissez une option : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                {
                    int idVoyageur;
                    char nom[50];
                    char prenom[50];

                    printf("Entrez l'ID du voyageur : ");
                    scanf("%d", &idVoyageur);

                    printf("Entrez le nom du voyageur : ");
                    scanf("%s", nom);

                    printf("Entrez le prénom du voyageur : ");
                    scanf("%s", prenom);

                    ajouterVoyageur(idVoyageur, nom, prenom);
                    printf("Compte voyageur créé avec succès.\n");
                }
                break;
            case 2:
                {
                    int idReservation, idVoyageur, idBus;
                    struct Date date;

                    printf("Entrez l'ID de la réservation : ");
                    scanf("%d", &idReservation);

                    printf("Entrez l'ID du voyageur : ");
                    scanf("%d", &idVoyageur);

                    printf("Entrez l'ID du bus : ");
                    scanf("%d", &idBus);

                    printf("Entrez la date de la réservation (format YYYY MM DD) : ");
                    scanf("%d %d %d", &date.annee, &date.mois, &date.jour);

                    faireReservation(idReservation, idVoyageur, idBus, date);

                }
                break;
            case 3:
                {
                    int idBus, capacite;
                    char destination[100];

                    printf("Entrez l'ID du bus : ");
                    scanf("%d", &idBus);

                    printf("Entrez la capacité du bus : ");
                    scanf("%d", &capacite);

                    printf("Entrez la destination du bus : ");
                    scanf("%s", destination);

                    ajouterBus(idBus, capacite, destination);
                    printf("Compte bus créé avec succès.\n");
                }
                break;
            case 4:
                afficherBuses();
                break;
            case 5:
                afficherVoyageurs();
                break;
            case 6:
                {
                    int idReservation;
                    struct Date newDate;

                    printf("Entrez l'ID de la réservation à modifier : ");
                    scanf("%d", &idReservation);

                    printf("Entrez la nouvelle date de la réservation (format YYYY MM DD) : ");
                    scanf("%d %d %d", &newDate.annee, &newDate.mois, &newDate.jour);

                    modifier_Reservation(idReservation, newDate);
                }
                break;
            case 7:
                {
                    int idReservation;

                    printf("Entrez l'ID de la réservation à annuler : ");
                    scanf("%d", &idReservation);

                    supprimer_reservation(idReservation);
                }
                break;
            case 8:
                afficherUneReservation();
                break;
            case 0:
                printf("Programme terminé.\n");
                break;
            default:
                printf("Option invalide. Veuillez saisir une option valide.\n");
        }

    } while (choix != 0);

    return 0;
}

void afficherMenu() {
    printf("\n ----- Menu -----\n");
    printf("1. Créer un nouveau compte voyageur\n");
    printf("2. Créer une nouvelle réservation\n");
    printf("3. Créer un nouveau compte bus\n");
    printf("4. Afficher les détails des bus\n");
    printf("5. Afficher les détails des voyageurs\n");
    printf("6. Afficher et modifier les détails d'une réservation\n");
    printf("7. Supprimer une réservation déjà créée\n");
    printf("8. Afficher une seule réservation\n");
    printf("0. Quitter\n");
}

void afficherBuses() {
    printf("\n -----Liste des bus : -----\n");
    Liste_bus* bus = listeBuses;
    while (bus != NULL) {
        printf("ID Bus : %d, Capacité : %d, Destination : %s\n", bus->idBus, bus->capacite, bus->destination);
        bus = bus->suiv;
    }
}

void afficherVoyageurs() {
    printf("\n -----Liste des voyageurs : -----\n");
    Liste_Voyageur* voyageur = listeVoyageurs;
    while (voyageur != NULL) {
        printf("ID Voyageur : %d, Nom : %s, Prénom : %s\n", voyageur->idVoyageur, voyageur->nom, voyageur->prenom);
        voyageur = voyageur->suiv;
    }
}

void afficherReservations() {
    printf("\n -----Liste des réservations : -----\n");
    Liste_Reservation* reservation = listeReservations;
    while (reservation != NULL) {
        printf("ID Reservation : %d, Voyageur : %s %s, Bus : %d, Date : %04d-%02d-%02d\n",
               reservation->idReservation, reservation->voyageur->nom, reservation->voyageur->prenom,
               reservation->bus->idBus, reservation->date.annee,
               reservation->date.mois, reservation->date.jour);
        reservation = reservation->suiv;
    }
}

void afficherUneReservation() {
    int idReservation;
    printf("Entrez l'ID de la réservation à afficher : ");
    scanf("%d", &idReservation);

    Liste_Reservation* reservation = listeReservations;
    while (reservation != NULL && reservation->idReservation != idReservation) {
        reservation = reservation->suiv;
    }

    if (reservation == NULL) {
        printf("Réservation introuvable\n");
        return;
    }

    printf("\n ----- Détails de la réservation -----\n");
    printf("ID Reservation : %d\n", reservation->idReservation);
    printf("Voyageur : %s %s\n", reservation->voyageur->nom, reservation->voyageur->prenom);
    printf("Bus : %d\n", reservation->bus->idBus);
    printf("Date : %04d-%02d-%02d\n", reservation->date.annee, reservation->date.mois, reservation->date.jour);
}

void ajouterBus(int idBus, int capacite, const char* destination) {
    Liste_bus* nouveauBus = (Liste_bus*)malloc(sizeof(Liste_bus));
    if (nouveauBus == NULL) {
        printf("Erreur d'allocation de mémoire\n");
        return;
    }

    nouveauBus->idBus = idBus;
    nouveauBus->capacite = capacite;
    strncpy(nouveauBus->destination, destination, sizeof(nouveauBus->destination) - 1);
    nouveauBus->suiv = listeBuses;

    listeBuses = nouveauBus;
}

void ajouterVoyageur(int idVoyageur, const char* nom, const char* prenom) {
    Liste_Voyageur* nouveauVoyageur = (Liste_Voyageur*)malloc(sizeof(Liste_Voyageur));
    if (nouveauVoyageur == NULL) {
        printf("Erreur d'allocation de mémoire\n");
        return;
    }

    nouveauVoyageur->idVoyageur = idVoyageur;
    strncpy(nouveauVoyageur->nom, nom, sizeof(nouveauVoyageur->nom) - 1);
    strncpy(nouveauVoyageur->prenom, prenom, sizeof(nouveauVoyageur->prenom) - 1);
    nouveauVoyageur->suiv = listeVoyageurs;

    listeVoyageurs = nouveauVoyageur;
}

int placeDisponible(int idBus) {
    Liste_bus* bus = listeBuses;

    while (bus != NULL && bus->idBus != idBus) {
        bus = bus->suiv;
    }

    if (bus == NULL) {
        printf("Bus introuvable\n");
        return 0;
    }

    return bus->capacite > 0;
}

void faireReservation(int idReservation, int idVoyageur, int idBus, struct Date date) {
    if (!placeDisponible(idBus)) {
        printf("Aucune place disponible dans le bus sélectionné\n");
        return;
    }

    Liste_Reservation* nouvelleReservation = (Liste_Reservation*)malloc(sizeof(Liste_Reservation));
    if (nouvelleReservation == NULL) {
        printf("Erreur d'allocation de mémoire\n");
        return;
    }

    Voyageur voyageur = listeVoyageurs;
    while (voyageur != NULL && voyageur->idVoyageur != idVoyageur) {
        voyageur = voyageur->suiv;
    }

    Liste_bus* bus = listeBuses;
    while (bus != NULL && bus->idBus != idBus) {
        bus = bus->suiv;
    }

    if (voyageur == NULL || bus == NULL) {
        printf("Voyageur ou bus introuvable\n");
        free(nouvelleReservation);
        return;
    }

    bus->capacite--;

    nouvelleReservation->idReservation = idReservation;
    nouvelleReservation->voyageur = voyageur;
    nouvelleReservation->bus = bus;
    nouvelleReservation->date = date;
    nouvelleReservation->suiv = listeReservations;

    listeReservations = nouvelleReservation;

    printf("Réservation effectuée avec succès\n");
}

void modifier_Reservation(int idReservation, struct Date newDate) {
    Liste_Reservation* reservation = listeReservations;

    while (reservation != NULL && reservation->idReservation != idReservation) {
        reservation = reservation->suiv;
    }

    if (reservation == NULL) {
        printf("Réservation introuvable\n");
        return;
    }

    reservation->date = newDate;
    printf("Date de la réservation modifiée avec succès\n");
}

void supprimer_reservation(int idReservation) {
    Liste_Reservation* current = listeReservations;
    Liste_Reservation* prev = NULL;

    while (current != NULL && current->idReservation != idReservation) {
        prev = current;
        current = current->suiv;
    }

    if (current == NULL) {
        printf("Réservation introuvable\n");
        return;
    }

    if (prev == NULL) {
        listeReservations = current->suiv;
    } else {
        prev->suiv = current->suiv;
    }

    free(current);

    printf("Réservation annulée avec succès\n");
}
