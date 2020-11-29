#include "../inc/Coords.hpp"
#include "../inc/Util.hpp"
#include <iostream>

Coords::Coords(double x, double y)
    : m_x{x}, m_y{y}
{
}

Coords::Coords()
    : m_x{0}, m_y{0}
{
}

Coords Coords::aleatoire(double amplitude)
{
    return {Util::alea(-amplitude, amplitude),
            Util::alea(-amplitude, amplitude)};
}

void Coords::afficher() const
{
    std::cout << "(" << m_x << ", " << m_y << ")";
}

double Coords::getX() const
{
    return m_x;
}

double Coords::getY() const
{
    return m_y;
}

/// Positions relatives
bool Coords::estAGauche(const Coords &autre) const
{
    return m_x < autre.m_x;
}

bool Coords::estADroite(const Coords &autre) const
{
    return m_x > autre.m_x;
}

bool Coords::estAuDessus(const Coords &autre) const
{
    return m_y < autre.m_y;
}

bool Coords::estAuDessous(const Coords &autre) const
{
    return m_y > autre.m_y;
}

/// Somme vectorielle
Coords operator+(const Coords &c1, const Coords &c2)
{
    return {c1.m_x + c2.m_x, c1.m_y + c2.m_y};
}

/// Soustraction vectorielle
Coords operator-(const Coords &c1, const Coords &c2)
{
    return {c1.m_x - c2.m_x, c1.m_y - c2.m_y};
}

/// Produit vectoriel
double operator*(const Coords &c1, const Coords &c2)
{
    return c1.m_x * c2.m_x + c1.m_y * c2.m_y;
}

/// Multiplication par un réel
Coords operator*(double m, const Coords &c)
{
    return {m * c.m_x, m * c.m_y};
}

void Coords::Translater(Coords &vecteur)
{
    m_x += vecteur.getX();
    m_y += vecteur.getY();
}

void Coords::SetX(double x) { m_x = x; }

void Coords::SetY(double y) { m_y = y; }