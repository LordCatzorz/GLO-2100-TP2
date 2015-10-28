/**
 * \file Personne.cpp
 * \brief implémentation de l'interface de la classe Personne
 * \author Mario à partir de Thierry
 * \version 0.1
 * \date 2015
 */

#include "Personne.h"
using namespace std;

Personne::Personne(const std::string& p_nom, const std::string& p_prenom,
		int p_date)
{

}

Personne::Personne(const Personne & p_personne)
{

}

//! \brief surcharge de l'opérateur <
bool Personne::operator <(const Personne & p_personne) const
{

}

//! \brief surcharge de l'opérateur << d'écriture dans une ostream
//! \param[in] p_os un ostream vide dans laquelle on va écrire
//! \param[in] p_personne qui est une personne
//! \return le ostream dans laquelle on a écrit les information sur la personne
ostream& operator<<(ostream& p_os, const Personne& p_personne)
{

}

//! \brief obtient la date de naissance
//! \return la date de naissance
int Personne::reqDateNaissance() const
{

}

//! \brief obtient le nom (de famille) de la personne
//! \return le nom de la personne
std::string Personne::reqNom() const
{

}
//! \brief obtient le prénom de la personne
//! \return le prénom de la personne
std::string Personne::reqPrenom() const
{

}

