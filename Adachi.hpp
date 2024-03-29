#ifndef _ADACHI_HPP_
#define _ADACHI_HPP_
#include "MazeDef.hpp"

class Adachi{
private:
    static const int default_step_value=255;
    static const int plan_max_num=255;
    int is_run_plan;
    int step_map[MAZESIZE_X][MAZESIZE_Y];

    int GetMinArrayIndex(int* array, int length);    
public:
    int map[MAZESIZE_X][MAZESIZE_Y];
    Dirction step_plan[plan_max_num];
    int step_plan_length;
    RunPlan run_plan[plan_max_num];
    RunPattern fast_pattern[plan_max_num];

    Adachi();
    void Update();
    Dirction GetNextDirection(int x, int y, Dirction dir);

    void SetMapArray(int data[MAZESIZE_X][MAZESIZE_Y]);
    void SetMap(int x, int y,int wall_data_4bit, Dirction dir);
    void SetStepMap(int x, int y, int step){step_map[x][y]=step;}
    int CalBit(bool bit, int pos){return bit<<pos;}

    int GetMapData(int x, int y){return map[x][y];}
    int GetStepData(int x, int y){return step_map[x][y];}

    void InitMaze(InitialWall inital_wall,int data[MAZESIZE_X][MAZESIZE_Y]);
    void InitStepMap(int target_x, int target_y);
    void MakeStepMap(int target_x, int target_y, WallMask mask);

    int MakePathPlan(int start_x, int start_y, Dirction start_dir, int target_x, int target_y);
    int MakeRunPlan(int path_length, Dirction initial_dir);
};

#endif //_ADACHI_HPP_
