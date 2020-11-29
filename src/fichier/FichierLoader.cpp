#include "../inc/FichierLoader.hpp"
#include "../inc/Logger.hpp"

#include <iostream>
#include <cstring>

FichierLoader::FichierLoader(std::string const &nomFichier) : m_nomFichier(nomFichier), m_ficher(NULL)
{
    Logger logger;
    m_ficher = fopen(nomFichier.c_str(), "r");

    if (m_ficher == NULL)
        logger.Log("Erreur : Impossible d'ouvrir le fichier .rom", LoggerPriority::Error);
    else
        logger.Log("Fichier .rom ouvert avec succes !", LoggerPriority::Info);
}

FichierLoader::~FichierLoader()
{
    Logger logger;
    logger.Log("Fichier Loader dctor destroyed !", LoggerPriority::Debug);
    logger.Log("Fichier fermer avec succes !", LoggerPriority::Info);
    fclose(m_ficher);
}

Maillage FichierLoader::Load()
{
    double largeur;
    double hauteur;
    char ligne[201] = " ";
    parse_ground(largeur, hauteur);

    while (fgets(ligne, 200, m_ficher) != NULL)
    {
        if (ligne[0] == '#')
            parse_decor(largeur, hauteur, ligne);

        else if (ligne[0] == '$')
            parse_robot(largeur, hauteur, ligne);

        memset(ligne, ' ', 200);
    }

    return m_maillageBuilder.Build(largeur, hauteur);
}

RobotComposant FichierLoader::parse_composant(std::string const &composant) const
{
    if (composant == "tete")
        return RobotComposant::Tete;
    else if (composant == "haut_corps")
        return RobotComposant::HautDuCorps;
    else if (composant == "bras_gauche")
        return RobotComposant::BrasGauche;
    else if (composant == "bras_droit")
        return RobotComposant::BrasDroit;
    else if (composant == "jambe_droite")
        return RobotComposant::JambeDroite;
    else if (composant == "jambe_gauche")
        return RobotComposant::JambeGauche;
    else if (composant == "main_droite")
        return RobotComposant::MainDroite;
    else if (composant == "main_gauche")
        return RobotComposant::MainGauche;
    else
        return RobotComposant::Null;
}

std::vector<std::string> FichierLoader::parse_ligne(char *ligne) const
{
    std::vector<std::string> result;

    char *tokens = std::strtok(ligne, " ");
    while (tokens != NULL)
    {
        std::string info = tokens;
        result.push_back(info.erase(0, info.substr(0, info.find("=")).length() + 1));
        tokens = std::strtok(NULL, " ");
    }
    return result;
}

Forme *FichierLoader::parse_forme(std::string const &geometrie, std::string const &id,
                                  double posX, double posY, double largeur, double hauteur, std::string couleur) const
{
    Forme *forme;
    Logger logger;

    if (geometrie == "rectangle")
        forme = new Rom::Rectangle(id,
                                   {new Sommet(posX, posY),
                                    new Sommet(posX + largeur, posY),
                                    new Sommet(posX, posY + hauteur),
                                    new Sommet(posX + largeur, posY + hauteur)},
                                   couleur);

    else if (geometrie == "triangle")
        forme = new Triangle(id,
                             {new Sommet(posX, posY),
                              new Sommet(posX + largeur, posY),
                              new Sommet((2 * posX + largeur) * 0.5, posY - hauteur)},
                             couleur);

    else if (geometrie == "cercle")
        forme = new Cercle(id,
                           {new Sommet(posX, posY)},
                           hauteur, false,
                           couleur);

    else if (geometrie == "disque")
        forme = new Cercle(id,
                           {new Sommet(posX, posY)},
                           hauteur, true,
                           couleur);

    else if (geometrie == "ellipse")
        forme = new rom::Ellipse(id,
                                 {new Sommet(posX, posY)},
                                 largeur,
                                 hauteur,
                                 couleur);
    else
    {
        forme = nullptr;
        logger.Log("Forme inconnue dans le fichier .rom", LoggerPriority::Warn);
    }
    return forme;
}
void FichierLoader::parse_ground(double &largeur, double &hauteur)
{
    char header[100] = " ";
    fgets(header, 100, m_ficher);
    auto info = parse_ligne(header);

    auto id = info[0];
    largeur = atof(info[1].c_str());
    hauteur = atof(info[2].c_str());

    m_maillageBuilder = m_maillageBuilder.AjouterDecor(new Rom::Rectangle(id,
                                                                          {new Sommet(0, 0),
                                                                           new Sommet(largeur, 0),
                                                                           new Sommet(0, hauteur),
                                                                           new Sommet(largeur, hauteur)},
                                                                          Svgfile::makeRGB(242, 255, 255)))

                            .AjouterDecor(new Rom::Rectangle("MG",
                                                             {new Sommet(0, 0),
                                                              new Sommet(50, 0),
                                                              new Sommet(0, hauteur),
                                                              new Sommet(50, hauteur)},
                                                             Svgfile::makeRGB(175, 175, 175)))

                            .AjouterDecor(new Rom::Rectangle("MD",
                                                             {new Sommet(largeur - 50, 0),
                                                              new Sommet(largeur, 0),
                                                              new Sommet(largeur - 50, hauteur),
                                                              new Sommet(largeur, hauteur - 1)},
                                                             Svgfile::makeRGB(175, 175, 175)))

                            .AjouterDecor(new Rom::Rectangle("Mur sols",
                                                             {new Sommet(0, hauteur - 50),
                                                              new Sommet(largeur, hauteur - 50),
                                                              new Sommet(0, hauteur),
                                                              new Sommet(largeur, hauteur)},
                                                             Svgfile::makeRGB(175, 175, 175)));
}

void FichierLoader::parse_robot(double largeur, double hauteur, char *ligne)
{
    auto info = parse_ligne(ligne);
    auto nomRobot = info[0];
    auto humeur = info[1];
    Forme *forme;
    RobotBuilder robotBuilder;
    while (true)
    {
        memset(ligne, ' ', 200);
        fgets(ligne, 200, m_ficher);
        if (ligne[0] == '{')
            continue;
        if (ligne[0] == '}')
            break;
        info = parse_ligne(ligne);

        double posX = (largeur * atof(info[0].c_str()));
        double posY = hauteur - (hauteur * atof(info[1].c_str()));
        auto composant = parse_composant(info[2]);
        auto id = info[3];
        auto geometrie = info[4];
        double forme_largeur = atof(info[5].c_str());
        double forme_hauteur = atof(info[6].c_str());

        std::string svgColor;
        if (info[7][0] == 'r')
            svgColor = info[7];
        else
            svgColor = Svgfile::makeRGB(std::stoi(info[7].substr(0, 3)),
                                        std::stoi(info[7].substr(4, 3)),
                                        std::stoi(info[7].substr(8, 3)));

        forme = parse_forme(geometrie, id, posX, posY, forme_largeur, forme_hauteur, svgColor);

        if (forme != nullptr)
        {
            robotBuilder = robotBuilder.AjouterComposant(forme, composant);
            if (composant == RobotComposant::Tete)
            {
                robotBuilder = robotBuilder.AjouterVisage(new Cercle("o1",
                                                                     {new Sommet(posX - (forme_hauteur / 2),
                                                                                 posY - (forme_hauteur / 2))},
                                                                     3, true, Svgfile::makeRGB(0, 0, 0)))
                                   .AjouterVisage(new Cercle("o2",
                                                             {new Sommet(posX + (forme_hauteur / 2),
                                                                         posY - (forme_hauteur / 2))},
                                                             3, true, Svgfile::makeRGB(0, 0, 0)))
                                   .AjouterVisage(new Triangle("n",
                                                               {new Sommet(posX - (forme_hauteur / 3), posY + (forme_hauteur / 3.0)),
                                                                new Sommet(posX + (forme_hauteur / 3), posY + (forme_hauteur / 3.0)),
                                                                new Sommet(posX, posY - (forme_hauteur / 4.0))},
                                                               Svgfile::makeRGB(0, 0, 0)));
                if (humeur == "non_content\n")
                    robotBuilder = robotBuilder.AjouterVisage(new Ligne("b",
                                                                        {new Sommet(posX - (forme_hauteur / 1.8), posY + (forme_hauteur / 1.8)),
                                                                         new Sommet(posX + (forme_hauteur / 1.8), posY + (forme_hauteur / 1.8))},
                                                                        Svgfile::makeRGB(0, 0, 0)));
                else if (humeur == "colere\n")
                    robotBuilder = robotBuilder.AjouterVisage(new Rom::Rectangle("b",
                                                                                 {new Sommet(posX - (forme_hauteur / 1.8), posY + (forme_hauteur / 1.8)),
                                                                                  new Sommet(posX + (forme_hauteur / 1.8), posY + (forme_hauteur / 1.8)),
                                                                                  new Sommet(posX - (forme_hauteur / 1.8), posY + (forme_hauteur / 1.6)),
                                                                                  new Sommet(posX + (forme_hauteur / 1.8), posY + (forme_hauteur / 1.6))},
                                                                                 Svgfile::makeRGB(0, 0, 0)));
                else if (humeur == "ohhh!\n")
                    robotBuilder = robotBuilder.AjouterVisage(new rom::Ellipse("b",
                                                                               {new Sommet(posX, posY + (forme_hauteur / 1.6))},
                                                                               forme_hauteur / 3.0, forme_hauteur / 5.0,
                                                                               Svgfile::makeRGB(0, 0, 0)));
            }
        }
    }
    m_maillageBuilder = m_maillageBuilder.AjouterRobot(robotBuilder.Build(nomRobot, humeur));
}

void FichierLoader::parse_decor(double largeur, double hauteur, char *ligne)
{
    Logger logger;
    auto info = parse_ligne(ligne);
    double posX = (largeur * atof(info[0].c_str()));
    double posY = hauteur - (hauteur * atof(info[1].c_str()));
    std::string svgColor;
    if (info[2][0] == 'r')
        svgColor = info[2];
    else
        svgColor = Svgfile::makeRGB(std::stoi(info[2].substr(0, 3)),
                                    std::stoi(info[2].substr(4, 3)),
                                    std::stoi(info[2].substr(8, 3)));
    Forme *forme;

    while (true)
    {
        memset(ligne, ' ', 200);
        fgets(ligne, 200, m_ficher);
        if (ligne[0] == '{')
            continue;
        if (ligne[0] == '}')
            break;

        info = parse_ligne(ligne);

        auto id = info[0];
        auto geometrie = info[1];
        double forme_largeur = atof(info[2].c_str());
        double forme_hauteur = atof(info[3].c_str());

        forme = parse_forme(geometrie, id, posX, posY, forme_largeur, forme_hauteur, svgColor);

        if (forme != nullptr)
            m_maillageBuilder = m_maillageBuilder.AjouterDecor(forme);
    }
}