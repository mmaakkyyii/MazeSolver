#include "Adachi.hpp"
#include <iostream>
#include <algorithm>
Adachi::Adachi(){

}

void Adachi::Update(){

}

Dirction Adachi::GetNextDirection(int x, int y, Dirction dir){
    int north_step = default_step_value;
    int west_step  = default_step_value;
    int south_step = default_step_value;
    int east_step  = default_step_value;
    if((map[x][y] & 0b10001000 ) == 0b10000000){
        north_step=step_map[x][y+1];
    }
    if((map[x][y] & 0b01000100 ) == 0b01000000){
        west_step=step_map[x-1][y];
    }
    if((map[x][y] & 0b00100010 ) == 0b00100000){
        south_step=step_map[x][y-1];
    }
    if((map[x][y] & 0b00010001 ) == 0b00010000){
        east_step=step_map[x+1][y];
    }
    switch(dir){
        case North:
            south_step=default_step_value-1;
            break;
        case West:
            east_step=default_step_value-1;
            break;
        case South:
            north_step=default_step_value-1;
            break;
        case East:
            west_step=default_step_value-1;
            break;
    }
    int step_array[4]={north_step,west_step,south_step,east_step};

    int minIndex = std::distance(step_array, std::min_element(step_array, step_array + 4));
    switch(dir){
        case North:
            if(step_array[minIndex]==north_step)return North;
            break;
        case West:
            if(step_array[minIndex]==west_step)return West;
            break;
        case South:
            if(step_array[minIndex]==south_step)return South;
            break;
        case East:
            if(step_array[minIndex]==east_step)return East;
            break;
    }

    switch(minIndex){
        case 0:
            return North;
        case 1:
            return West;
        case 2:
            return South;
        case 3:
            return East;
    }
}


void Adachi::InitMaze(){
    for(int i_x=0;i_x<MAZESIZE_X;i_x++){
        for(int i_y=0;i_y<MAZESIZE_Y;i_y++){
            map[i_x][i_y] &=0b00001111;
        }
    }

    for(int i_x=0;i_x<MAZESIZE_X;i_x++){
        SetMap(i_x,0,(0b00100000|map[i_x][0]));
        SetMap(i_x,MAZESIZE_Y-1,(0b10000000|map[i_x][MAZESIZE_Y-1]));
    }
    for(int i_y=0;i_y<MAZESIZE_Y;i_y++){
        SetMap(0,i_y,(0b01000000|map[0][i_y]));
        SetMap(MAZESIZE_X-1,i_y,(0b00010000|map[MAZESIZE_X-1][i_y]));
    }
    map[0][0]=0b11110111;   
}

void Adachi::InitStepMap(int target_x, int target_y){
    for(int i_x=0;i_x<MAZESIZE_X;i_x++){
        for(int i_y=0;i_y<MAZESIZE_Y;i_y++){
            step_map[i_x][i_y]=default_step_value;
        }
    }
    step_map[target_x][target_y]=0;
}

void Adachi::MakeStepMap(int target_x, int target_y, WallMask mask){
    InitStepMap(target_x,target_y);

    bool update_flag;
    while(update_flag == true){
        update_flag = false;

        for(int i_x=0; i_x<MAZESIZE_X; i_x++){
            for(int i_y=0; i_y<MAZESIZE_Y; i_y++){
                if(step_map[i_x][i_y]==default_step_value)continue;

                if(i_y < MAZESIZE_Y -1){
                    //No Wall to the North
                    if((map[i_x][i_y] & 0b10001000 ) != (0b10001000)){
                        std::cout <<"";
                        if(step_map[i_x][i_y+1] == default_step_value){
                            step_map[i_x][i_y+1]=step_map[i_x][i_y]+1;
                            update_flag=true;
                        }
                    }
                }

                if(i_x < MAZESIZE_X -1){
                    //No Wall to the East
                    if((map[i_x][i_y] & 0b00010001) != (0b00010001)){
                        if(step_map[i_x+1][i_y] == default_step_value){
                            step_map[i_x+1][i_y]=step_map[i_x][i_y]+1;
                            update_flag=true;
                        }
                    }
                }

                if(i_y > 0){
                    //No Wall to the South
                    if((map[i_x][i_y] & 0b00100010) != (0b00100010)){
                        if(step_map[i_x][i_y-1] == default_step_value){
                            step_map[i_x][i_y-1]=step_map[i_x][i_y]+1;
                            update_flag=true;
                        }
                    }
                }

                if(i_y < MAZESIZE_Y -1){
                    //No Wall to the West
                    if((map[i_x][i_y] & 0b01000100) != (0b01000100)){
                        if(step_map[i_x-1][i_y] == default_step_value){
                            step_map[i_x-1][i_y]=step_map[i_x][i_y]+1;
                            update_flag=true;
                        }
                    }
                }

            }
        }

    }
}

void Adachi::SetMapArray(int data[MAZESIZE_X][MAZESIZE_Y]){
    for(int x=0;x<MAZESIZE_X;x++){
        for(int y=0;y<MAZESIZE_Y;y++){
            map[x][y]=data[y][x];
        }
    }
}

void Adachi::SeeMap(int x, int y, Dirction dir){
    switch(dir){
        case North:
            if(x>0)map[x-1][y]|=0b00010000;
            if(x<MAZESIZE_X-1)map[x+1][y]|=0b01000000;
            //if(y>0)map[x][y-1]|=0b10000000;
            if(y<MAZESIZE_Y-1)map[x][y+1]|=0b00100000;
            map[x][y]|=0b11010000;
            break;
        case West:
            if(x>0)map[x-1][y]|=0b00010000;
            //if(x<MAZESIZE_X-1)map[x+1][y]|=0b01000000;
            if(y>0)map[x][y-1]|=0b10000000;
            if(y<MAZESIZE_Y-1)map[x][y+1]|=0b00100000;

            map[x][y]|=0b11100000;
            break;
        case South:
            if(x>0)map[x-1][y]|=0b00010000;
            if(x<MAZESIZE_X-1)map[x+1][y]|=0b01000000;
            if(y>0)map[x][y-1]|=0b10000000;
            //if(y<MAZESIZE_Y-1)map[x][y+1]|=0b00100000;
            map[x][y]|=0b01110000;
            break;
        case East:
            //if(x>0)map[x-1][y]|=0b00010000;
            if(x<MAZESIZE_X-1)map[x+1][y]|=0b01000000;
            if(y>0)map[x][y-1]|=0b10000000;
            if(y<MAZESIZE_Y-1)map[x][y+1]|=0b00100000;
            map[x][y]|=0b10110000;
            break;
    }
}

void Adachi::MakeRunPlan(int start_x, int start_y, Dirction start_dir, int target_x, int target_y){
    MakeStepMap(target_x, target_y,WallMask::UNUSE_WALL_MASK);
    int x=start_x;
    int y=start_y;
    Dirction dir=start_dir;
    int index=0;

    while(x!=target_x && y!=target_y){
        dir=GetNextDirection(x,y,dir);
        switch(dir){
            case North:
                y++;
                dir=North;
                step_plan[index]=North;
                break;
            case West:
                x--;
                dir=West;
                step_plan[index]=West;
                break;
            case South:
                y--;
                dir=South;
                step_plan[index]=South;
                break;
            case East:
                x++;
                dir=East;
                step_plan[index]=East;
                break;
        }
//        std::cout << index << "," << x <<"," << y << "," << dir <<"\n";
        index++;
    }
    step_plan_length=index;

}
