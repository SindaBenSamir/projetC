# projet-C-e-bus-reserservation
Système de Gestion de Réservations de Voyages en Bus

Ce projet implémente un système simple de gestion de réservations de voyages en bus. Il permet de créer des comptes voyageurs, des réservations de voyages, des comptes de bus, d'afficher les détails des bus, des voyageurs, des réservations, de modifier les dates de réservations, et d'annuler des réservations.

Fonctions

afficherMenu():     
Affiche le menu principal du système.

afficherBuses():               
Affiche la liste des bus disponibles avec leurs détails.

afficherVoyageurs():                   
Affiche la liste des voyageurs enregistrés avec leurs détails.

afficherReservations():                         
Affiche la liste des réservations effectuées avec les détails associés.

ajouterBus(int idBus, int capacite, const char* destination):                   
Ajoute un nouveau bus à la liste des bus disponibles.

ajouterVoyageur(int idVoyageur, const char* nom, const char* prenom):                              
Ajoute un nouveau voyageur à la liste des voyageurs enregistrés.

faireReservation(int idReservation, int idVoyageur, int idBus, const char* date):                             
Permet de faire une nouvelle réservation associée à un voyageur, un bus et une date spécifiés.

modifier_Reservation(int idReservation, const char* newDate):                     
Modifie la date d'une réservation existante.

supprimer_reservation(int idReservation):                              
Supprime une réservation existante.

int placeDisponible(int idBus):                              
Retourne le nombre de place disponible associée à un bus.
