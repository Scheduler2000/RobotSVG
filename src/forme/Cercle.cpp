#include "../inc/Cercle.hpp"
#include "../inc/Logger.hpp"

Cercle::Cercle(std::string const &id, std::vector<Sommet *> const &centre, int rayon, bool fill, std::string const &couleur)
    : m_rayon(rayon), m_fill(fill), Forme(id, centre, couleur, FormeType::Cercle) {}

Cercle::~Cercle()
{
    Logger logger;
    logger.Log("Cercle dctor destroyed !", LoggerPriority::Debug);
}

Coords Cercle::GetCentre() const
{
    return _sommets[0]->GetCoords();
}
int Cercle::GetRayon() const { return m_rayon; }

void Cercle::Dessiner(Svgfile &dessinVec, bool afficherInfo) const
{
    Coords centre = GetCentre();

    if (m_fill)
        dessinVec.addDisk(centre.getX(), centre.getY(), m_rayon, _couleur);
    else
        dessinVec.addCircle(centre.getX(), centre.getY(), m_rayon, 3, _couleur);

    if (afficherInfo)
    {
        dessinVec.addText(centre.getX(), centre.getY(), GetId());
    }
}