#include "../inc/Sommet.hpp"
#include "../inc/SvgFile.hpp"

Sommet::Sommet(double posX, double posY) : m_position(posX, posY) {}

Sommet::~Sommet() {}

void Sommet::Dessiner(Svgfile &dessinVec) const
{
    dessinVec.addDisk(m_position.getX(), m_position.getY(), 3, Svgfile::makeRGB(0, 255, 0));
}

Coords Sommet::GetCoords() const
{
    return m_position;
}

void Sommet::Translater(Coords &vecteur)
{
    m_position.Translater(vecteur);
}

void Sommet::SetPosX(double x) { m_position.SetX(x); }

void Sommet::SetPosY(double y) { m_position.SetY(y); }