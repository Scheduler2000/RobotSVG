#include "../inc/Transformation.hpp"

const double PI = 3.1415926535897932384626;

static double deg2rad(double deg)
{
    return (PI / 180) * deg;
}

Transformation::Transformation(const Rotation &rotation)
    : m_matrice{Matrice::rotation(deg2rad(rotation.angle))},
      m_centre{rotation.centre},
      m_translation{} {}

Transformation::Transformation(const Symetrie &symetrie)
    : m_matrice{Matrice::symetrie(deg2rad(symetrie.angle))},
      m_centre{symetrie.centre},
      m_translation{} {}

Coords Transformation::resultat(const Coords &c) const
{
    return m_matrice * (c - m_centre) + m_centre + m_translation;
}
