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
	this->m_nom = p_nom;
	this->m_prenom = p_prenom;
	this->m_dateNaissance = p_date;
}

Personne::Personne(const Personne & p_personne)
{
	this->m_nom = p_personne.reqNom();
	this->m_prenom = p_personne.reqPrenom();
	this->m_dateNaissance = p_personne.reqDateNaissance();
}

//! \brief surcharge de l'opérateur <
bool Personne::operator <(const Personne & p_personne) const
{
	throw exception("Not yet implemented");
}

//! \brief surcharge de l'opérateur << d'écriture dans une ostream
//! \param[in] p_os un ostream vide dans laquelle on va écrire
//! \param[in] p_personne qui est une personne
//! \return le ostream dans laquelle on a écrit les information sur la personne
ostream& operator<<(ostream& p_os, const Personne& p_personne)
{
	p_os << p_personne.reqNom() << ", "
		 << p_personne.reqPrenom() << ", "
		 << p_personne.reqDateNaissance();
	return p_os;

}

//! \brief obtient la date de naissance
//! \return la date de naissance
int Personne::reqDateNaissance() const
{
	return this->m_dateNaissance;
}

//! \brief obtient le nom (de famille) de la personne
//! \return le nom de la personne
std::string Personne::reqNom() const
{
	return this->m_nom;
}
//! \brief obtient le prénom de la personne
//! \return le prénom de la personne
std::string Personne::reqPrenom() const
{
	return this->m_prenom;
}

