#if !defined(__FICHIER_LOADER__)
#define __FICHIER_LOADER__

#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include "../inc/RobotBuilder.hpp"
#include "../inc/MaillageBuilder.hpp"

#include "../inc/Robot.hpp"
#include "../inc/RobotBuilder.hpp"
#include "../inc/Cercle.hpp"
#include "../inc/Triangle.hpp"
#include "../inc/Ligne.hpp"
#include "../inc/Ellipse.hpp"
#include "../inc/Rectangle.hpp"
#include "../inc/MaillageBuilder.hpp"
#include "../inc/Ellipse.hpp"

class FichierLoader
{
private:
    FILE *m_ficher;
    std::string m_nomFichier;
    MaillageBuilder m_maillageBuilder;

    std::vector<std::string> parse_ligne(char *ligne) const;
    RobotComposant parse_composant(std::string const &composant) const;
    Forme *parse_forme(std::string const &geometrie, std::string const &id, double posX, double posY, double largeur, double hateur, std::string couleur) const;

    void parse_ground(double &largeur, double &hauteur);
    void parse_robot(double largeur, double hauteur, char *ligne);
    void parse_decor(double largeur, double hauteur, char *ligne);

public:
    FichierLoader(std::string const &nomFichier);
    ~FichierLoader();

    Maillage Load();
};

#endif // __SCENE_BUILDER__
