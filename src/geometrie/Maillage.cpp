#include <iostream>

#include "../inc/Maillage.hpp"
#include "../inc/ConsoleExtension.hpp"
#include "../inc/Logger.hpp"
#include "../inc/Cercle.hpp"
#include "../inc/Triangle.hpp"
#include "../inc/Ligne.hpp"
#include "../inc/Ellipse.hpp"
#include "../inc/Rectangle.hpp"
#include "../inc/MaillageBuilder.hpp"
#include "../inc/Ellipse.hpp"

Maillage::Maillage(std::vector<Robot *> &robot, std::vector<Forme *> &decors, double largeur, double hauteur)
    : m_robots(std::move(robot)), m_decors(std::move(decors)), m_largeur(largeur), m_hauteur(hauteur) {}

Maillage::Maillage(Maillage const &maillage)
{
    for (auto ptrRobot : maillage.m_robots)
        m_robots.push_back(new Robot(*ptrRobot));

    for (auto ptrForme : maillage.m_decors)
    {
        switch (ptrForme->GetType())
        {
        case FormeType::Cercle:
            m_decors.push_back(new Cercle(*(dynamic_cast<Cercle *>(ptrForme))));
            break;
        case FormeType::Ellipse:
            m_decors.push_back(new rom::Ellipse(*(dynamic_cast<rom::Ellipse *>(ptrForme))));
            break;
        case FormeType::Ligne:
            m_decors.push_back(new Ligne(*(dynamic_cast<Ligne *>(ptrForme))));
            break;
        case FormeType::Rectangle:
            m_decors.push_back(new Rom::Rectangle(*(dynamic_cast<Rom::Rectangle *>(ptrForme))));
            break;
        case FormeType::Triangle:
            m_decors.push_back(new Triangle(*(dynamic_cast<Triangle *>(ptrForme))));
            break;
        }
    }
}

Maillage::~Maillage()
{
    Logger logger;

    for (auto robotPtr : m_robots)
        delete robotPtr;

    for (auto decorPtr : m_decors)
        delete decorPtr;

    logger.Log("Maillage dctor destroyed !\n", LoggerPriority::Debug);
}

void Maillage::Dessiner(Svgfile &dessinVec, bool afficherInfo) const
{
    Coords collisionPosition;

    if (afficherInfo)
        dessinVec.addGrid();

    for (auto ptrDecors : m_decors)
        ptrDecors->Dessiner(dessinVec, afficherInfo);

    for (auto ptrRobot : m_robots)
        ptrRobot->Construire(dessinVec, afficherInfo);

    if (m_collisionObserver.Verifier(m_robots, m_decors, collisionPosition))
    {
        std::cout << "collision dectecter au niveau du point : "
                  << collisionPosition.getX() << " "
                  << collisionPosition.getY() << std::endl; // pour tester si c'est bon

        m_collisionManager.ExecuteCollision(collisionPosition);
    }
}

double Maillage::ObtenirLargeur() const { return m_largeur; }

double Maillage::ObtenirHauteur() const { return m_hauteur; }

Robot *Maillage::ObtenirRobot(std::string const &nom) const
{
    Logger logger;

    for (auto ptrRobot : m_robots)
        if (ptrRobot->ObtenirNom() == nom)
            return ptrRobot;

    logger.Log("L'obtention du robot a echoue, verifie l'existance du robot !", LoggerPriority::Warn);

    return nullptr;
}

Forme *Maillage::ObtenirDecor(std::string const &nom) const
{
    Logger logger;

    for (auto ptrForme : m_decors)
        if (ptrForme->GetId() == nom)
            return ptrForme;

    logger.Log("L'obtention du decor a echoue, verifie l'existance du decor !", LoggerPriority::Warn);

    return nullptr;
}

std::vector<Forme *> const &Maillage::ObtenirFormes() const
{
    return m_decors;
}

std::vector<Robot *> const &Maillage::ObtenirRobots() const { return m_robots; }