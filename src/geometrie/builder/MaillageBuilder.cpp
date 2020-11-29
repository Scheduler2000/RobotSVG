#include "../inc/MaillageBuilder.hpp"

MaillageBuilder::MaillageBuilder() {}

MaillageBuilder::~MaillageBuilder() {}

MaillageBuilder MaillageBuilder::AjouterRobot(Robot *robot)
{
    m_robots.push_back(robot);
    return *this;
}

MaillageBuilder MaillageBuilder::AjouterDecor(Forme *decor)
{
    m_decors.push_back(decor);
    return *this;
}

Maillage MaillageBuilder::Build(double largeur, double hauteur)
{
    return Maillage(m_robots, m_decors, largeur, hauteur);
}