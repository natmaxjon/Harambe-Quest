#include "SuperTile.h"
#include "Maze.h"

void SuperTile::activate()
{
    notify(Observer::Event::SUPER_PELLET_EATEN);
    Maze::decrementFoodCount();
    remove();
}
