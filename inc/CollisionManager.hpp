#if !defined(__COLLISION_MANAGER__)
#define __COLLISION_MANAGER__

#include "../inc/Coords.hpp"

class CollisionManager
{
private:
public:
    void ExecuteCollision(Coords const &collisionPoint) const;
};

#endif // __COLLISION_MANAGER__
