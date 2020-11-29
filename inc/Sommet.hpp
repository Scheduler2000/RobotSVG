#ifndef __SOMMET__
#define __SOMMET__
#include "../inc/Coords.hpp"
#include "../inc/SvgFile.hpp"

class Sommet
{
private:
    Coords m_position;

public:
    ~Sommet();
    Sommet(double posX, double posY);

    void Dessiner(Svgfile &dessinVec) const;
    void Translater(Coords &vecteur);
    void SetPosX(double value);
    void SetPosY(double value);
    Coords GetCoords() const;
};

#endif // __SOMMET__
