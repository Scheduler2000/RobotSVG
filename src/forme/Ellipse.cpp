#include "../inc/Ellipse.hpp"
#include "../inc/Logger.hpp"

using namespace rom;
Ellipse::Ellipse(std::string const &id, std::vector<Sommet *> const &sommets, int rx, int ry, std::string const &couleur)
    : m_radiusX(rx), m_radiusY(ry), Forme(id, sommets, couleur, FormeType::Ellipse) {}

Ellipse::~Ellipse()
{
    Logger logger;
    logger.Log("Ellipse dctor destroyed !", LoggerPriority::Debug);
}

Coords Ellipse::GetCentre() const
{
    return _sommets[0]->GetCoords();
}

int Ellipse::GetRadiusX() const { return m_radiusX; }

int Ellipse::GetRadiusY() const { return m_radiusY; }

void Ellipse::Dessiner(Svgfile &dessinVec, bool afficherInfo) const
{
    Coords centre = GetCentre();

    dessinVec.AddEllispe(centre, m_radiusX, m_radiusY, _couleur);
    if (afficherInfo)
    {
        dessinVec.addText(centre.getX(), centre.getY(), GetId());
    }
}