#ifndef _MAZE_DEF_
#define _MAZE_DEF_

#define MAZESIZE_X (16)
#define MAZESIZE_Y (16)

#define GOAL_X (7)
#define GOAL_Y (7)

enum class WallMask{
    USE_WALL_MASK   = 0b00000000,
    UNUSE_WALL_MASK = 0b11111111
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