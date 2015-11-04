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
	if (!p_fichierEntree.good())
	{
		throw logic_error("Le fichier p_fichierEntree n'est pas ouvert correctement");
	}

	this->m_listeArbreGene = list<ArbreGenealogique>();
	do
	{
		std::string ligneLu;
		std::getline(p_fichierEntree, ligneLu);
		if (ligneLu == "$")
		{
			std::string nomParent;
			std::string prenomParent;
			std::string dateNaissanceParent;
			std::string nomEnfant;
			std::string prenomEnfant;
			std::string dateNaissanceEnfant;
			std::getline(p_fichierEntree, nomParent);
			std::getline(p_fichierEntree, prenomParent);
			std::getline(p_fichierEntree, dateNaissanceParent);
			std::getline(p_fichierEntree, nomEnfant);
			std::getline(p_fichierEntree, prenomEnfant);
			std::getline(p_fichierEntree, dateNaissanceEnfant);
			Personne parent = Personne(nomParent, prenomParent, this->convertirStringInt(dateNaissanceParent));
			Personne enfant = Personne(nomEnfant, prenomEnfant, this->convertirStringInt(dateNaissanceEnfant));
			std::map<Personne,Adresse>::iterator iteratorParent =this->m_bottin.find(parent);
			std::map<Personne,Adresse>::iterator iteratorEnfant =this->m_bottin.find(enfant);


			bool arbreParentExiste = false;
			bool arbreEnfantExiste = false;
			for (std::list<ArbreGenealogique>::iterator iter = this->m_listeArbreGene.begin(); iter != this->m_listeArbreGene.end();iter++)
			{

				if (!arbreEnfantExiste && iter->appartient(iteratorEnfant))
				{
					arbreEnfantExiste = true;
				}
				if (iter->reqNom() == iteratorParent->first.reqNom())
				{
					arbreParentExiste = true;
					iter->ajouterEnfant(iteratorParent, iteratorEnfant);
				}
			}
			if (!arbreParentExiste)
			{
				ArbreGenealogique nouvelleArbre = ArbreGenealogique(iteratorParent);
				nouvelleArbre.ajouterEnfant(iteratorParent,iteratorEnfant);
				this->m_listeArbreGene.push_front(nouvelleArbre);
			}
		}
		else if (ligneLu != "")
		{
			std::string nom = ligneLu;
			std::string prenom;
			std::string dateNaissance;
			std::string numero;
			std::string rue;
			std::string ville;
			std::getline(p_fichierEntree, prenom);
			std::getline(p_fichierEntree, dateNaissance);
			std::getline(p_fichierEntree, numero);
			std::getline(p_fichierEntree, rue);
			std::getline(p_fichierEntree, ville);
			Personne personne = Personne(nom, prenom, this->convertirStringInt(dateNaissance));
			Adresse adresse = Adresse(this->convertirStringInt(numero),rue,ville);
			this->inscrire(personne, adresse);
		}
	}while(p_fichierEntree.good());
}

//! \brief pour inscrire une personne dans l'annuaire
//! \param[in] p_personne la personne à àjouter.
//! \param[in] p_adresse de la personne à inscrire
void Annuaire::inscrire(const Personne & p_personne, const Adresse& p_adresse)
{
	this->m_bottin.insert(std::pair<Personne,Adresse>(p_personne, p_adresse));
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
	std::map<Personne,Adresse>::iterator entreeParent = this->m_bottin.find(p_parent);
	if (entreeParent == this->m_bottin.end())
	{
		throw logic_error("Le parent n'existe pas dans le bottin");
	}
	
	std::map<Personne,Adresse>::iterator entreeEnfant = this->m_bottin.find(p_enfant);
	if (entreeEnfant == this->m_bottin.end())
	{
		throw logic_error("L'enfant n'existe pas dans le bottin");
	}

	bool trouve = false;
	std::list<ArbreGenealogique>::iterator iter = this->m_listeArbreGene.begin();
	for (; iter != this->m_listeArbreGene.end() && trouve == false; iter++)
	{
		trouve = iter->reqNom() == p_parent.reqNom();
	}

	if (trouve)
	{
		iter->ajouterEnfant(entreeParent, entreeEnfant);
	}
	else
	{
		ArbreGenealogique arbre =  ArbreGenealogique(entreeParent);
		arbre.ajouterEnfant(entreeParent,entreeEnfant);
		this->m_listeArbreGene.push_front(arbre);
	}

}

//! \fn std::ostream & Annuaire::operator <<(std::ostream & p_out, const Annuaire & p_annuaire)
//! \brief operateur de sortie du contenu de l'annuaire formatage des infos dans un string puis sortie
//! \param[in] p_annuaire l'annuaire a sortir.
//! \pre l'annuaire n'est pas vide
//! \param[out] p_out le flux de sortie contenant l'annuaire .
//! \exception logic_error Le bottin est vide
//! \return un flux de sortie pour les appel en cascade.
std::ostream & operator <<(std::ostream & p_out, const Annuaire & p_annuaire)
{
	if(p_annuaire.m_bottin.empty())
	{
		throw logic_error("Le bottin est vide");
	}
	p_out << std::endl << "bottin : " << std::endl;
	for(std::map<Personne, Adresse>::const_iterator iter = p_annuaire.m_bottin.begin();iter != p_annuaire.m_bottin.end(); iter++)
	{
		p_out << std::endl << iter->first <<endl << iter->second;
	}
	p_out << std::endl << std::endl << "arbres généalogiques :" << std::endl;
	for(std::list<ArbreGenealogique>::const_iterator iter = p_annuaire.m_listeArbreGene.begin(); iter != p_annuaire.m_listeArbreGene.end(); iter++)
	{
		p_out << endl << *iter;
	}
	p_out << std::endl;
	return p_out;
}

//! \brief Convertion simple de string en int.
//! \param[in] p_string la string a convertir.
//! \return le résultat de l'opérateur >> de stringsteam qui devrait être le int du texte si valide
//! \sa std::stringsteam.operator>>
int Annuaire::convertirStringInt(std::string p_string)
{
	std::stringstream ss;
	int entier = 0;
	std::stringstream(p_string) >> entier;
	return entier;
}
