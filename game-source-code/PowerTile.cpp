#include "PowerTile.h"
#include "Maze.h"

void PowerTile::activate()
{
    notify(Observer::Event::POWER_PELLET_EATEN);
    Maze::decrementFoodCount();
    remove();
}
