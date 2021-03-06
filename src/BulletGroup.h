#ifndef BULLET_GROUP_H
#define BULLET_GROUP_H

#include "Level.h"
#include "Bullet.h"
#include <stdlib.h>



/** a whole bunch of reusable bullets that are all of the same kind.
 * when one is destroyed, it can then be used again, and in that way, we are able to save from
 * instantiating shit all the time */
struct BulletGroup
{
  /** the size of the group */
  int nBullets;
  /** the bullet that all others are based on */
  struct Bullet const *mother;
  /** this is the lot of bullets */
  struct Bullet children[];
};


/** create a bullet group of the given size
 * @param size is the number of bullets in this group
 * @param mother is the bullet that the other bullets will be like
 * @param level is the level we are creating this in
 * @return the new bullet group */
struct BulletGroup *BulletGroup_create(int size,struct Bullet const *mother,struct Level *level);


/** destroys the bullet group, and all bullets inside it, and removes the objects from the level
 * @param group is the bullet group to destroy
 * @param level is the level it was in */
void BulletGroup_destroy(struct BulletGroup *group,struct Level *level);


/** adds a bullet to the bullet group unless it is full
 * @param x is the x position to add the bullet at
 * @param y is the y position to add the bullet at
 * @param z is the z position to add the bullet at
 * @param angle is the angle to fire it at
 * @param group is the group we are doing this for */
struct Bullet *BulletGroup_fire(float x,float y,float z,float angle,struct BulletGroup *group);


#endif
