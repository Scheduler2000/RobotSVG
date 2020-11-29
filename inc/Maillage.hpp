#ifndef __MAILLAGE__
#define __MAILLAGE__
#include <vector>

#include <string>
#include "../inc/Robot.hpp"
#include "../inc/SvgFile.hpp"
#include "../inc/CollisionObserver.hpp"
#include "../inc/CollisionManager.hpp"

class Maillage
{
private:
    CollisionObserver m_collisionObserver;
    CollisionManager m_collisionManager;
    std::vector<Robot *> m_robots;
    std::vector<Forme *> m_decors;
    double m_largeur;
    double m_hauteur;

public:
    Maillage(std::vector<Robot *> &robots, std::vector<Forme *> &decors, double largeur, double hauteur);
    Maillage(Maillage const &maillage);
    ~Maillage();

    void Dessiner(Svgfile &dessinVec, bool afficherInfo) const;

    double ObtenirLargeur() const;
    double ObtenirHauteur() const;

    std::vector<Forme *> const &ObtenirFormes() const;
    std::vector<Robot *> const &ObtenirRobots() const;

    Robot *ObtenirRobot(std::string const &nom) const;
    Forme *ObtenirDecor(std::string const &nom) const;
};

#endif // __MAILLAGE__
