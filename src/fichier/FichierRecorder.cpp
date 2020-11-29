#include <ctime>
#include <stdlib.h>
#include "../inc/FichierRecorder.hpp"
#include "../inc/Logger.hpp"
#include "../inc/Cercle.hpp"
#include "../inc/Ellipse.hpp"
#include "../inc/Rectangle.hpp"
#include "../inc/Triangle.hpp"

FichierRecorder::FichierRecorder(Maillage *scene, std::string const &nomFichier) : m_scene(scene)
{
    Logger logger;
    time_t rawtime;
    struct tm *timeinfo;
    char buffer[80];

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer, sizeof(buffer), "%d-%m-%Y_%H-%M-%S", timeinfo);
    std::string path("scene\\" + std::string(buffer) + "_" + nomFichier);

    m_fichier.open(path);

    if (!m_fichier)
        logger.Log("Erreur : Impossible de creer le fichier .rom", LoggerPriority::Error);
    else
        logger.Log("Fichier .rom cree avec succes !", LoggerPriority::Info);
}

FichierRecorder::~FichierRecorder()
{
    Logger logger;

    logger.Log("Fichier Recorder dctor destroyed !", LoggerPriority::Debug);
    logger.Log("Fichier fermer avec succes !", LoggerPriority::Info);
    m_fichier.close();
}

void FichierRecorder::Save()
{
    double romLargeur;
    double romHauteur;

    record_ground(romLargeur, romHauteur);
    record_robots(romLargeur, romHauteur);
    record_decors(romLargeur, romHauteur);
}

std::string FichierRecorder::delctype_forme(Forme *forme, double &width, double &height) const
{
    std::string geometrie;

    switch (forme->GetType())
    {
    case FormeType::Cercle:
    {
        Cercle *cercle = dynamic_cast<Cercle *>(forme);

        geometrie = "cercle";
        width = 0;
        height = cercle->GetRayon();
    }
    break;
    case FormeType::Ellipse:
    {
        rom::Ellipse *ellipse = dynamic_cast<rom::Ellipse *>(forme);
        geometrie = "ellipse";
        width = ellipse->GetRadiusX();
        height = ellipse->GetRadiusY();
    }
    break;
    case FormeType::Rectangle:
    {
        Rom::Rectangle *rectangle = dynamic_cast<Rom::Rectangle *>(forme);
        geometrie = "rectangle";
        Sommet *tl = rectangle->GetSommets()[0];
        Sommet *tr = rectangle->GetSommets()[1];
        Sommet *bl = rectangle->GetSommets()[2];

        width = tr->GetCoords().getX() - tl->GetCoords().getX();
        height = tl->GetCoords().getY() - bl->GetCoords().getY();
    }
    break;
    case FormeType::Triangle:
    {
        Triangle *triangle = dynamic_cast<Triangle *>(forme);
        geometrie = "triangle";
        width = triangle->GetSommets()[1]->GetCoords().getX() - triangle->GetSommets()[0]->GetCoords().getX();
        height = triangle->GetSommets()[2]->GetCoords().getY() - triangle->GetSommets()[1]->GetCoords().getY();
    }
    break;
    }

    return geometrie;
}

std::string FichierRecorder::delctype_composant(RobotComposant composant) const
{
    switch (composant)
    {
    case RobotComposant::BrasDroit:
        return "bras_droit";
    case RobotComposant::BrasGauche:
        return "bras_gauche";
    case RobotComposant::HautDuCorps:
        return "haut_corps";
    case RobotComposant::JambeDroite:
        return "jambe_droite";
    case RobotComposant::JambeGauche:
        return "jambe_gauche";
    case RobotComposant::MainDroite:
        return "main_droite";
    case RobotComposant::MainGauche:
        return "main_gauche";
    case RobotComposant::Tete:
        return "tete";
    }
    return " ";
}

void FichierRecorder::record_ground(double &largeur, double &hauteur)
{
    Forme *rom = m_scene->ObtenirFormes()[0];
    Sommet *tl = rom->GetSommets()[0];
    Sommet *tr = rom->GetSommets()[1];
    Sommet *bl = rom->GetSommets()[2];
    largeur = tr->GetCoords().getX() - tl->GetCoords().getX();
    hauteur = tl->GetCoords().getY() - bl->GetCoords().getY();

    m_fichier << "id=" << rom->GetId() << " "
              << "width=" << largeur << " "
              << "height=" << abs(hauteur)
              << std::endl
              << std::endl
              << std::endl;
}

void FichierRecorder::record_decors(double largeur, double hauteur)
{
    const std::vector<Forme *> &decors = m_scene->ObtenirFormes();

    double posX_percentage;
    double posY_percentage;

    std::string id;
    std::string forme;
    double width;
    double height;

    for (size_t i = 4; i < decors.size(); i++)
    {
        id = decors[i]->GetId();

        if (id[0] == '&') /* décors associés au visage du robot */
            continue;

        posX_percentage = (decors[i]->GetSommets()[0]->GetCoords().getX()) / largeur;
        posY_percentage = (decors[i]->GetSommets()[0]->GetCoords().getY()) / hauteur;
        forme = delctype_forme(decors[i], width, height);

        m_fichier << "#Decor:posX_percentage=" << posX_percentage << " "
                  << "posY_percentage=" << 1 - abs(posY_percentage) << " "
                  << "color=" << decors[i]->GetCouleur()
                  << std::endl
                  << "{" << std::endl;

        m_fichier << "\tid=" << id << " "
                  << "forme=" << forme << " "
                  << "width=" << width << " "
                  << "height=" << abs(height) << std::endl
                  << "}" << std::endl
                  << std::endl;
    }
}

void FichierRecorder::record_robots(double largeur, double hauteur)
{
    const std::vector<Robot *> robots = m_scene->ObtenirRobots();

    double posX_percentage;
    double posY_percentage;

    std::string id;
    std::string forme;
    std::string partieCorps;
    double width;
    double height;
    for (auto robot : robots)
    {
        const std::map<RobotComposant, Forme *> composants = robot->ObtenirComposants();

        m_fichier << "$Robot:id=" << robot->ObtenirNom() << " "
                  << "mood=" << robot->ObtenirMood()
                  << "{"
                  << std::endl;

        for (auto composant : composants)
        {
            posX_percentage = (composant.second->GetSommets()[0]->GetCoords().getX()) / largeur;
            posY_percentage = (composant.second->GetSommets()[0]->GetCoords().getY()) / hauteur;
            id = composant.second->GetId();
            forme = delctype_forme(composant.second, width, height);
            partieCorps = delctype_composant(composant.first);

            m_fichier << "\t"
                      << "posX_percentage=" << posX_percentage << " "
                      << "posY_percentage=" << 1 - abs(posY_percentage) << " "
                      << "composant=" << partieCorps << " "
                      << "id=" << id << " "
                      << "forme=" << forme << " "
                      << "width=" << width << " "
                      << "height=" << abs(height) << " "
                      << "color=" << composant.second->GetCouleur()
                      << std::endl;
        }

        m_fichier << "}"
                  << std::endl
                  << std::endl;
    }
}