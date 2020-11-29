#ifndef __TRIANGLE__
#define __TRIANGLE__
#include "../inc/Sommet.hpp"
#include "../inc/Couleur.hpp"
#include "../inc/SvgFile.hpp"
#include "../inc/Forme.hpp"
#include <vector>

class Triangle : public Forme
{
public:
    ~Triangle();
    Triangle(std::string const &id, std::vector<Sommet *> const &sommet, std::string const &couleur);

    void Dessiner(Svgfile &dessinVec, bool afficherInfo) const override;
    Coords GetCentre() const override;
};

#endif // __TRIANGLE__
