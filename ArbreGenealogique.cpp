/**
 * \file ArbreGenealogique.cpp
 * \brief implémentation de la classe arbre genealogique
 * \author mario
 * \version 0.1
 * \date 2015
 */

#include "ArbreGenealogique.h"
#include <iostream>

using namespace std;

//! \brief Constructeur sans paramètre
ArbreGenealogique::ArbreGenealogique()
{
	throw exception("Not yet implemented");
}

//! \brief constructeur à un paramètre
ArbreGenealogique::ArbreGenealogique(pEntree p_personne_it)
{
	throw exception("Not yet implemented");
}

//! \brief constructeur de copie
ArbreGenealogique::ArbreGenealogique(const ArbreGenealogique & p_source)
{
	throw exception("Not yet implemented");
}

//! \brief Destructeur
ArbreGenealogique::~ArbreGenealogique()
{
	throw exception("Not yet implemented");
}

//! \brief surcharge de l'opérateur =
const ArbreGenealogique & ArbreGenealogique::operator=(const ArbreGenealogique & p_source)
{
	throw exception("Not yet implemented");
}

//! \brief retourne le nom de l'arbre généalogique
string ArbreGenealogique::reqNom() const
{
	throw exception("Not yet implemented");
}

//! \brief Ajouter un enfant (ou possiblement son parent) dans un arbre genealogique
//!			Le parent peut appartenir à un arbre généalogique ssi il a le même nom que celui de l'arbre généalogique.
//!			Le nom d'un enfant doit être celui d'un de ses parents (mais il est possiblement différent de celui du parent pour cet appel).
//!			Un enfant se trouvant dans un arbre généalogique d'un nom différent sera donc une feuille: les efants de cet enfant seront dans un autre arbre généalogique.
//!			Toute personne n'est présente qu'une seule fois dans un arbre généalogique.
//!			Si le parent est dans son arbreGene mais pas l'enfant, alors ajouter l'enfant dans cet arbreGene.
//!			Si le parent n'est pas dans l'arbreGene et que son enfant est l'ancêtre ; alors remplacer l'ancêtre (l'ancien ancêtre devient un enfant du nouvel ancêtre)
//!			Si le parent n'est pas dans l'arbreGene et que son enfant n'est pas l'ancêtre, alors ne pas modifier l'arbreGene.
//! \param[in] p_parent le pointeur d'une personne
//! \param[in] p_enfant le pointeur d'une personne
//! \exception logic_error si le parent a un nom différent de l'arbreGene
//! \exception logic_error si le parent n'est pas dans l'arbreGene et que son enfant n'est pas l'ancêtre
void ArbreGenealogique::ajouterEnfant(pEntree p_parent_it, pEntree p_enfant_it)
{
	throw exception("Not yet implemented");
}

//! \brief opérateur surcharge de sortie
//!		affichage des noeuds de l,arbre en pré-ordre
std::ostream & operator <<(std::ostream & p_out,
		const ArbreGenealogique & p_arbreG)
{
	throw exception("Not yet implemented");
}

//! \brief permet de savoir si une personne appartient à l'arbre
//! \param[in] p_personne_it la personne recherchée.
//! \pre non nulle
//! \return vrai si la personne est dans l'arbre, faux sinon.
bool ArbreGenealogique::appartient(pEntree p_personne_it) const
{
	throw exception("Not yet implemented");
}


