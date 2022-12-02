#ifndef _MAZE_DEF_
#define _MAZE_DEF_

#define MAZESIZE_X (16)
#define MAZESIZE_Y (16)

#define GOAL_X (7)
#define GOAL_Y (7)

enum class WallMask{
    USE_UNKOWN_WALL_MASK   = 1,
    UNUSE_UNKOWN_WALL_MASK = 0
};
enum Dirction{
    North,
    West,
    South,
    East
};

enum RunPlan{
    Forward,
    TurnRight,
    TurnLeft
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