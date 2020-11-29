#include "../inc/Ligne.hpp"
#include "../inc/Logger.hpp"
#include <algorithm>

Ligne::Ligne(std::string const &id, std::vector<Sommet *> const &sommets, std::string const &couleur)
    : Forme(id, sommets, couleur, FormeType::Ligne) {}

Ligne::~Ligne()
{
    Logger logger;
    logger.Log("Ligne dctor destroyed !", LoggerPriority::Debug);
}

Coords Ligne::GetCentre() const
{
    auto p1 = _sommets[0]->GetCoords();
    auto p2 = _sommets[1]->GetCoords();
    auto somme = p1 + p2;

    return Coords(somme.getX() / 2, somme.getY() / 2);
}

void Ligne::Dessiner(Svgfile &dessinVec, bool afficherInfo) const
{
    auto p1 = _sommets[0]->GetCoords();
    auto p2 = _sommets[1]->GetCoords();

    dessinVec.addLine(p1.getX(), p1.getY(), p2.getX(), p2.getY(), _couleur);

    if (afficherInfo)
    {
        std::for_each(_sommets.begin(), _sommets.end(), [&dessinVec](Sommet *s) -> void {
            s->Dessiner(dessinVec);
        });
        dessinVec.addText(GetCentre().getX(), GetCentre().getY(), GetId());
    }
}