#ifndef BULLET_H
#define BULLET_H

#include "Object.h"
#include "Actor.h"


/** a bullet that flies through the air to hit it's target with merciless acurracy */
struct Bullet
{
  /** the bullet's display object thing */
  struct Object *object;
  /** the bullet's x velocity */
  float vx;
  /** the bullet's y velocity */
  float vy;
  /** the bullet's z velocity */
  float vz;
  /** the default speed the bullet moves at */
  float speed;
  /* fixed x acceleration of the bullet */
  float gx;
  /* fixed y acceleration of the bullet */
  float gy;
  /* fixed z acceleration of the bullet */
  float gz;
  /** the origin of the bullet who can not be hit by it */
  struct Actor const *master;
};


/** loads in all the default bullets for you :) */
void Bullet_init();


/** grabs you a default bullet based on it's name
 * @param key is the name of the bullet you want to get
 * @return the bullet. it's const since it's only needed as a mother */
struct Bullet const *Bullet_get(char const *key);


#endif
