#include "../inc/Forme.hpp"
#include "../inc/Logger.hpp"
#include "../inc/Transformation.hpp"

#include <iostream>
#include <cstring>

Forme::Forme(std::string const &id, std::vector<Sommet *> const &sommets, std::string const &couleur, FormeType type)
    : m_id(id), _sommets(std::move(sommets)), _couleur(couleur), m_type(type) {}

Forme::~Forme()
{
    Logger logger;
    logger.Log("Virtual dctor of Forme destroyed !\n", LoggerPriority::Debug);
}

std::vector<Sommet *> Forme::GetSommets() const { return _sommets; }

std::string Forme::GetId() const { return m_id; }

FormeType Forme::GetType() const { return m_type; }

std::string Forme::GetCouleur()
{
    if (_couleur[_couleur.size() - 1] == '\n')
        _couleur.pop_back();

    return _couleur;
}

void Forme::Deplacer(double valeur)
{
    for (auto sommet : GetSommets())
    {
        Coords coord(valeur, 0);
        sommet->Translater(coord);
    }
}

void Forme::Rotate(double angle)
{
    auto centre = GetCentre();
    for (auto sommet : _sommets)
    {

        Rotation rotation;
        rotation.angle = angle;
        rotation.centre = centre;

        Transformation transform(rotation);
        Coords coord = transform.resultat(sommet->GetCoords());
        sommet->SetPosX(coord.getX());
        sommet->SetPosY(coord.getY());
    }
}
