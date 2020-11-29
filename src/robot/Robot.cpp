#include "../inc/Robot.hpp"
#include "../inc/Logger.hpp"
#include <iostream>
#include <algorithm>

Robot::Robot(std::string const &nom, std::string const &mood, std::map<RobotComposant, Forme *> &composants, std::vector<Forme *> &visage)
    : m_nom(nom), m_mood(mood)
{
    m_visage = visage;
    m_composants.insert(std::make_move_iterator(composants.begin()),
                        std::make_move_iterator(composants.end()));
}

Robot::~Robot()
{
    Logger logger;
    logger.Log("Robot dctor destroyed !\n", LoggerPriority::Debug);
}

std::string Robot::ObtenirNom() const
{
    return m_nom;
}

std::string Robot::ObtenirMood() const { return m_mood; }

Coords Robot::ObtenirCentreRobot() const
{
    Logger logger;
    Coords centre{0, 0};
    Forme *forme = ObtenirForme(RobotComposant::HautDuCorps);
    if (forme != nullptr)
        centre = forme->GetCentre();
    else
        logger.Log("La partie du corps obtenue est null !", LoggerPriority::Warn);
    return centre;
}

Forme *Robot::ObtenirForme(RobotComposant partieDuCorps) const
{
    Forme *forme = nullptr;

    for (auto keyVal : m_composants)
        if (keyVal.first == partieDuCorps)
            forme = keyVal.second;

    return forme;
}

const std::vector<Forme *> &Robot::ObtenirVisage() const
{
    return m_visage;
}

Forme *Robot::ObtenirForme(std::string const &id) const
{
    Forme *forme = nullptr;

    for (auto keyVal : m_composants)
        if (keyVal.second->GetId() == id)
            forme = keyVal.second;

    return forme;
}

const std::map<RobotComposant, Forme *> &Robot::ObtenirComposants() const { return m_composants; }

void Robot::Construire(Svgfile &dessinVec, bool afficherInfo) const
{
    for (auto it = m_composants.cbegin(); it != m_composants.cend(); it++)
        it->second->Dessiner(dessinVec, afficherInfo);
    for (auto v : m_visage)
        v->Dessiner(dessinVec, afficherInfo);
}

void Robot::Deplacer(double valeur)
{
    for (auto pair : m_composants)
        for (auto sommet : pair.second->GetSommets())
        {
            Coords coord(valeur, 0);
            sommet->Translater(coord);
        }
    for (auto v : m_visage)
        for (auto sommet : v->GetSommets())
        {
            Coords coord(valeur, 0);
            sommet->Translater(coord);
        }
}