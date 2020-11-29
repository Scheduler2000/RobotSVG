#if !defined(__TRANSFORMATION__)
#define __TRANSFORMATION__

#include "../inc/Coords.hpp"
#include "../inc/Matrice.hpp"

struct Rotation
{
    Coords centre;
    double angle;
};

struct Symetrie
{
    Coords centre;
    double angle;
};

class Transformation
{
private:
    Matrice m_matrice;
    Coords m_centre;
    Coords m_translation;

public:
    Transformation(const Rotation &rotation);
    Transformation(const Symetrie &symetrie);
    Coords resultat(const Coords &c) const;
};

#endif // __TRANSFORMATION__
