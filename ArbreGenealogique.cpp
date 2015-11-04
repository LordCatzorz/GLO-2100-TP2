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
	this->m_racine = NULL;
	this->m_nom = "";
}

//! \brief constructeur à un paramètre
ArbreGenealogique::ArbreGenealogique(pEntree p_personne_it)
{
	this->m_racine = new Noeud(p_personne_it);
	this->m_nom = p_personne_it->first.reqNom();
}

//! \brief constructeur de copie
ArbreGenealogique::ArbreGenealogique(const ArbreGenealogique & p_source)
{
	this->m_nom = p_source.reqNom();
	this->m_racine = this->copierPronfondementNoeud(p_source.m_racine);

}

ArbreGenealogique::~ArbreGenealogique()
{
	this->supprimerNoeudEtSousNoeud(this->m_racine);
}

//! \brief surcharge de l'opérateur =
const ArbreGenealogique & ArbreGenealogique::operator=(const ArbreGenealogique & p_source)
{
	return ArbreGenealogique(p_source);
}

//! \brief retourne le nom de l'arbre généalogique
string ArbreGenealogique::reqNom() const
{
	return this->m_nom;
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
	if (p_parent_it->first.reqNom() != this->m_nom)
	{
		throw logic_error("Le nom du parent doit être le même que le nom de l'arbre");
	}
	if (p_parent_it->first.reqDateNaissance() > p_enfant_it->first.reqDateNaissance())
	{
		throw logic_error("Le parent ne peut pas être né après l'enfant");
	}
	if(this->appartient(p_parent_it)) // Le parent est dans l'arbre
	{
		if (!this->appartient(p_enfant_it)) // Si l'enfant n'existe pas.
		{
			Noeud* noeudParent = this->trouverPositionEntree(this->m_racine, p_parent_it);
			Noeud* noeudEnfant = new Noeud(p_enfant_it);
			noeudParent->m_enfants.push_back(noeudEnfant);
		}
		else
		{
			cout << "L'enfant " << p_enfant_it << " se trouve déjà dans cet arbre généalogique, ajout refusé" << std::endl;
		}
	}
	else
	{
		if (this->m_racine->m_personne_it == p_enfant_it) // L'enfant est à la racine.
		{
			Noeud* noeudParent = new Noeud(p_parent_it);
			noeudParent->m_enfants.push_back(this->m_racine);
			this->m_racine = noeudParent;
		}
		else
		{
			throw logic_error("Le parent n'existe pas et l'enfant n'est pas la racine.");
		}
	}

}

//! \brief opérateur surcharge de sortie
//!		affichage des noeuds de l,arbre en pré-ordre
std::ostream & operator <<(std::ostream & p_out, const ArbreGenealogique & p_arbreG)
{
	p_out << "Arbre " << p_arbreG.reqNom() << " affiché en pré-ordre:";
	p_out << p_arbreG.m_racine;
	return p_out;
}

//! \brief permet de savoir si une personne appartient à l'arbre
//! \param[in] p_personne_it la personne recherchée.
//! \pre non nulle
//! \return vrai si la personne est dans l'arbre, faux sinon.
bool ArbreGenealogique::appartient(pEntree p_personne_it) const
{
	if(p_personne_it._Ptr == NULL)
	{
		throw new invalid_argument("p_personne_it est NULL");
	}

	return this->appartient(this->m_racine, p_personne_it);
}

//! \brief opérateur surcharge de sortie d'un noeud en pré-ordre
//!		affiche le nom du noeud suivi de ses enfants en pré-ordre s'il y en a.
std::ostream& operator <<(std::ostream& p_out, const ArbreGenealogique::Noeud* p_noeud)
{
	p_out << std::endl << p_noeud->m_personne_it->first;
	for(std::list<ArbreGenealogique::Noeud *>::const_iterator iter = p_noeud->m_enfants.begin(); iter != p_noeud->m_enfants.end(); iter++)
	{
		p_out << *iter;
	}
	return p_out;
}

//! \brief permet de savoir si une personne à un noueud ou un enfant d'un noeud
//! \param[in] p_noeud le noeud a chercher
//! \param[in] p_personne_it la personne recherchée.
//! \pre p_noeud non nulle
//! \pre p_personne_it non nulle
//! \return vrai si la personne est dans l'arbre, faux sinon.
const bool ArbreGenealogique::appartient(const ArbreGenealogique::Noeud * p_noeud, const ArbreGenealogique::pEntree& p_personne_it) const
{
	if (p_noeud == NULL)
	{
		throw new invalid_argument("p_noeud est NULL");
	}
	if (p_personne_it._Ptr == NULL)
	{
		throw new invalid_argument("p_personne_it est NULL");
	}

	bool retour = false;

	if (p_noeud->m_personne_it == p_personne_it)
	{
		retour = true;
	}
	else
	{
		for(std::list<ArbreGenealogique::Noeud *>::const_iterator iter = p_noeud->m_enfants.begin(); iter != p_noeud->m_enfants.end() && retour == false; iter++)
		{
			retour = this->appartient(*iter, p_personne_it);
		}
	}
	return retour;
}

//! \brief permet de savoir si une personne à un noueud ou un enfant d'un noeud
//! \param[in] p_noeud le noeud a chercher
//! \param[in] p_personne_it la personne recherchée.
//! \param[in] recursif indique s'il faut poursuivre la recherche dans les noeuds enfants des enfants.
//! \pre p_noeud non nulle
//! \pre p_personne_it non nulle
//! \return vrai si la personne est dans l'arbre, faux sinon.
const bool ArbreGenealogique::appartient(const ArbreGenealogique::Noeud * p_noeud, const ArbreGenealogique::pEntree& p_personne_it, bool p_recursif) const
{
	if (p_noeud == NULL)
	{
		throw new invalid_argument("p_noeud est NULL");
	}
	if (p_personne_it._Ptr == NULL)
	{
		throw new invalid_argument("p_personne_it est NULL");
	}

	bool retour = false;

	if (p_recursif)
	{
		retour = this->appartient(p_noeud, p_personne_it);
	}
	for(std::list<ArbreGenealogique::Noeud *>::const_iterator iter = p_noeud->m_enfants.begin(); iter != p_noeud->m_enfants.end() && retour == false; iter++)
	{
		if (p_personne_it ==  (*iter)->m_personne_it)
		{
			retour = true;
		}
	}
	return retour;
}

//! \brief permet d'obtenir le pointeur de noeud qui contient un élément
//! \param[in] p_departRecherche le noeud où l'on commence la recherche récursive
//! \param[in] p_personne_it la personne recherchée.
//! \pre p_noeud non nulle
//! \pre p_personne_it non nulle
//! \return le pointeur de noeud de l'élément ou NULL si aucun noeud n'est trouvé.
ArbreGenealogique::Noeud * ArbreGenealogique::trouverPositionEntree(ArbreGenealogique::Noeud * p_departRecherche, const ArbreGenealogique::pEntree p_personne_it) const
{
	if (p_departRecherche == NULL)
	{
		throw new invalid_argument("p_departRecherche est NULL");
	}
	if (p_personne_it._Ptr == NULL)
	{
		throw new invalid_argument("p_personne_it est NULL");
	}

	Noeud* retour = NULL;

	if (p_departRecherche->m_personne_it == p_personne_it)
	{
		retour = p_departRecherche;
	}
	else
	{
		for(std::list<ArbreGenealogique::Noeud *>::const_iterator iter = p_departRecherche->m_enfants.begin(); iter != p_departRecherche->m_enfants.end() && retour == NULL; iter++)
		{
			retour = this->trouverPositionEntree(*iter, p_personne_it);
		}
	}
	return retour;
}

//! \brief supprime un noeud ainsi que tous ces noeuds enfants.
//! \param[in] p_noeud le noeud à supprimer
//! \pre p_noeud non nulle
void ArbreGenealogique::supprimerNoeudEtSousNoeud(ArbreGenealogique::Noeud* p_noeud)
{
	if (p_noeud == NULL)
	{
		throw new invalid_argument("p_noeud est NULL");
	}

	for(std::list<Noeud*>::iterator iter = p_noeud->m_enfants.begin(); iter != p_noeud->m_enfants.end();iter++)
	{
		supprimerNoeudEtSousNoeud(*iter);
	}
	delete p_noeud;
	p_noeud = NULL;
}

//! \brief effectue une copie profonde du noeud
//! \param[in] p_noeud le noeud à copier
//! \pre p_noeud non nulle
//! \return la copie du noeud.
ArbreGenealogique::Noeud* ArbreGenealogique::copierPronfondementNoeud(Noeud* p_noeud)
{
	if (p_noeud == NULL)
	{
		throw new invalid_argument("p_noeud est NULL");
	}

	Noeud* noeudCopie = new Noeud(p_noeud->m_personne_it);
	for(std::list<Noeud*>::iterator iter = p_noeud->m_enfants.begin(); iter != p_noeud->m_enfants.end();iter++)
	{
		noeudCopie->m_enfants.push_back(copierPronfondementNoeud(*iter));
	}
	return noeudCopie;
}




