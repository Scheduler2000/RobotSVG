#include "../inc/Rectangle.hpp"
#include "../inc/Logger.hpp"
#include <algorithm>

using namespace Rom;

/*4 points : haut gauche, haut droit, bas gauche, bas droit*/
Rectangle::Rectangle(std::string const &id, std::vector<Sommet *> const &sommets, std::string const &couleur)
    : Forme(id, sommets, couleur, FormeType::Rectangle) {}

Rectangle::~Rectangle()
{
    Logger logger;
    logger.Log("Rectangle dctor destroyed !", LoggerPriority::Debug);
}

Coords Rectangle::GetCentre() const
{
    Coords topLeft = _sommets[0]->GetCoords();
    Coords topRight = _sommets[1]->GetCoords();
    Coords bottomLeft = _sommets[2]->GetCoords();
    Coords bottomRight = _sommets[3]->GetCoords();
    Coords somme = topLeft + topRight + bottomLeft + bottomRight;
    return Coords(somme.getX() / 4, somme.getY() / 4);
}

void Rectangle::Dessiner(Svgfile &dessinVec, bool afficherInfo) const
{
    Coords topLeft = _sommets[0]->GetCoords();
    Coords topRight = _sommets[1]->GetCoords();
    Coords bottomLeft = _sommets[2]->GetCoords();
    Coords bottomRight = _sommets[3]->GetCoords();
    Coords somme = topLeft + topRight + bottomLeft + bottomRight;

    dessinVec.AddRectangle(topLeft, topRight, bottomRight, bottomLeft, _couleur);

    if (afficherInfo)
    {
        std::for_each(_sommets.begin(), _sommets.end(), [&dessinVec](Sommet *s) -> void {
            s->Dessiner(dessinVec);
        });
        dessinVec.addText(somme.getX() / 4, somme.getY() / 4, GetId());
    }
}
