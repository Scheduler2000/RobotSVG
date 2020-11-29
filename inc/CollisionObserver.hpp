#if !defined(__COLLISION_OBSERVER___)
#define __COLLISION_OBSERVER___
#include <vector>
#include "../inc/Robot.hpp"
#include "../inc/Forme.hpp"
#include "../inc/Coords.hpp"

class CollisionObserver
{
private:
public:
    bool Verifier(std::vector<Robot *> const &robots, std::vector<Forme *> const &decors, Coords &outCollisionPosition) const;
};

#endif // __COLLISION_OBSERVER___
