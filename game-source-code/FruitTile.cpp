#include "FruitTile.h"
#include "Maze.h"

void FruitTile::activate()
{
    notify(Observer::Event::FRUIT_EATEN);
    Maze::decrementFoodCount();
    remove();
}
