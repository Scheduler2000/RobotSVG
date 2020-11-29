#include "../inc/Triangle.hpp"
#include "../inc/SvgFile.hpp"
#include "../inc/Logger.hpp"
#include <algorithm>

Triangle::Triangle(std::string const &id, std::vector<Sommet *> const &sommets, std::string const &couleur)
    : Forme(id, sommets, couleur, FormeType::Triangle) {}

Triangle::~Triangle()
{
    Logger logger;
    logger.Log("Triangle dctor destroyed !", LoggerPriority::Debug);
}

Coords Triangle::GetCentre() const
{
    Coords c1 = _sommets[0]->GetCoords();
    Coords c2 = _sommets[1]->GetCoords();
    Coords c3 = _sommets[2]->GetCoords();
    Coords somme = c1 + c2 + c3;

    return Coords(somme.getX() / 3, somme.getY() / 3);
}

void Triangle::Dessiner(Svgfile &dessinVec, bool afficherInfo) const
{
    Coords c1 = _sommets[0]->GetCoords();
    Coords c2 = _sommets[1]->GetCoords();
    Coords c3 = _sommets[2]->GetCoords();
    Coords somme = c1 + c2 + c3;
    std::string id = GetId();

    dessinVec.addTriangle(c1.getX(), c1.getY(), c2.getX(), c2.getY(), c3.getX(), c3.getY(), _couleur);

    if (afficherInfo)
    {
        std::for_each(_sommets.begin(), _sommets.end(), [&dessinVec](Sommet *s) -> void {
            s->Dessiner(dessinVec);
        });
        dessinVec.addText(somme.getX() / 3 - id.length(), somme.getY() / 3 - id.length(), id);
    }
}
