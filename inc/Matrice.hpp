#if !defined(__MATRICE__)
#define __MATRICE__
#include <array>
#include "../inc/Coords.hpp"

class Matrice
{
private:
    /// Les coefficients de la matrice !
    std::array<Coords, 2> m_mat;

public:
    /// Constructeur avec tous les coefficients
    Matrice(std::array<Coords, 2> mat);

    /// Fabrique de matrice transposée
    Matrice transpose() const;

    /// Fabrique de matrice de rotation, angle radians, sens trigo
    static Matrice rotation(double angle);

    /// Fabrique de matrice de symetrie
    static Matrice symetrie(double angle);

    /// Produit matrice vecteur (appliquer la matrice)
    friend Coords operator*(const Matrice &mat, const Coords &v);

    /// Produit matrice matrice : composition (au sens maths)
    friend Matrice operator*(const Matrice &a, const Matrice &b);
};

#endif // __MATRICE__
