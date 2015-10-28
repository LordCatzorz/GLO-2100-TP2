/**
 * \file Annuaire.cpp
 * \brief implémantation de la classe annuaire
 * \author mario
 * \version 0.1
 * \date 2015
 */

#include "Annuaire.h"
using namespace std;

//! \brief Constructeur à partir d'un fichier en entrée.
//! \param[in] p_fichierEntree un flux d'entrée vers un fichier contenant la liste des personnes à charger.
//! \pre			Le fichier p_fichierEntree est ouvert corectement.
//! \post		Le fichier p_fichierEntree n'est pas fermé par la fonction.
//! \post		Si les préconditions sont respectées, les données contenu
//!				dans le fichier en entrée sont stockées dans l'annuaire.
//! \exception	bad_alloc si pas assez de mémoire pour contenir toute les données du fichier.
//! \exception	logic_error si le fichier p_fichierEntree n'est pas ouvert correctement.
Annuaire::Annuaire(std::ifstream & p_fichierEntree)
{
	throw exception("Not yet implemented");
}

//! \brief pour inscrire une personne dans l'annuaire
//! \param[in] p_personne la personne à àjouter.
//! \param[in] p_adresse de la personne à inscrire
void Annuaire::inscrire(const Personne & p_personne, const Adresse& p_adresse)
{
	throw exception("Not yet implemented");
}

//! \brief ajoute un enfant et un parent dans l'arbre généalogique du même nom que le parent.
//!			Le parent et l'enfant doivent exister dans le bottin pour l'insertion dans un arbre généalogique.
//! \param[in] p_parent : le parent.
//! \pre Precondition p_parent et p_enfant existent dans le bottin
//! \param[in] p_enfant : l'enfant.
//! \pre Precondition p_enfant existe dans le bottin
//! \exception logic_error le parent n'existe pas dans le bottin.
//! \exception logic_error l'enfant n'existe pas dans le bottin.

void Annuaire::ajouterParentEnfant(const Personne & p_parent,
		const Personne & p_enfant)
{
	throw exception("Not yet implemented");
}

//! \fn std::ostream & Annuaire::operator <<(std::ostream & p_out, const Annuaire & p_annuaire)
//! \brief operateur de sortie du contenu de l'annuaire formatage des infos dans un string puis sortie
//! \param[in] p_annuaire l'annuaire a sortir.
//! \pre l'annuaire n'est pas vide
//! \param[out] p_out le flux de sortie contenant l'annuaire .
//! \exception exception_name Description des raisons de l'exception (peut en avoir plusieurs ou aucune).
//! \return un flux de sortie pour les appel en cascade.
std::ostream & operator <<(std::ostream & p_out, const Annuaire & p_annuaire)
{
	throw exception("Not yet implemented");
}

