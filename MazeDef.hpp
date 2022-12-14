#ifndef _MAZE_DEF_
#define _MAZE_DEF_

#include "bin.hpp"

#define MAZESIZE_X (16)
#define MAZESIZE_Y (16)

#define GOAL_X (7)
#define GOAL_Y (7)

enum InitialWall{
    KNOWN,
    UNKNOWN
};


enum WallMask{
    USE_UNKOWN_WALL_MASK   = 1,
    UNUSE_UNKOWN_WALL_MASK = 0
};
enum Dirction{
    North=0,
    West=1,
    South=2,
    East=3
};

enum RunPlan{
    Forward,
    TurnRight,
    TurnLeft,
    Turn
};

enum RunMode{
    SerchSpin,
    SerchSlalom,
    FastSpin,
    FastSlalom,
    FastDiagonal
};

enum RunPattern{
    Straight
};

#endif //_MAZE_DEF_