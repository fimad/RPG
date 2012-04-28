#ifndef _DIRECTION_HPP_
#define _DIRECTION_HPP_

enum Direction{
  NORTH
  , EAST
  , WEST
  , SOUTH
  , NORTH_EAST
  , NORTH_WEST
  , SOUTH_EAST
  , SOUTH_WEST
};

const int DirectionDeltaX[] = {
  -1
  , 0
  , 0
  , 1
  , -1
  , -1
  , 1
  , 1
};

const int DirectionDeltaY[] = {
  0
  , 1
  , -1
  , 0
  , 1
  , -1
  , 1
  , -1
};

#endif

