#include "Adachi.hpp"
//#include "debug.hpp"

Adachi::Adachi(){
    is_run_plan=false;
    for(int x=0;x<MAZESIZE_X;x++){
        for(int y=0;y<MAZESIZE_Y;y++){
            map[x][y]=0;
            step_map[x][y]=0;
        }
    }
}

void Adachi::Update(){

}

int Adachi::GetMinArrayIndex(int* array, int length){
    int temp_min_val=array[0];
    int temp_min_index=0;
    for(int i=1;i<length;i++){
        if(array[temp_min_index]>array[i])temp_min_index=i;
    }
    return temp_min_index;
}


Dirction Adachi::GetNextDirection(int x, int y, Dirction dir){
    int north_step = default_step_value;
    int west_step  = default_step_value;
    int south_step = default_step_value;
    int east_step  = default_step_value;
    if((map[x][y] & B10001000 ) == B10000000){
        north_step=step_map[x][y+1];
    }
    if((map[x][y] & B01000100 ) == B01000000){
        west_step=step_map[x-1][y];
    }
    if((map[x][y] & B00100010 ) == B00100000){
        south_step=step_map[x][y-1];
    }
    if((map[x][y] & B00010001 ) == B00010000){
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

    //int minIndex = std::distance(step_array, std::min_element(step_array, step_array + 4));
    int minIndex = GetMinArrayIndex(step_array,4);
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


void Adachi::InitMaze(InitialWall inital_wall,int data[MAZESIZE_X][MAZESIZE_Y]){
    int wall_mask=B00000000;
    if(inital_wall==KNOWN)wall_mask=B11110000;

    for(int i_x=0;i_x<MAZESIZE_X;i_x++){
        for(int i_y=0;i_y<MAZESIZE_Y;i_y++){
            map[i_x][i_y] =(wall_mask) | data[i_x][i_y];
        }
    }

    for(int i_x=0;i_x<MAZESIZE_X;i_x++){
        map[i_x][0]            |= B00100010;
        map[i_x][MAZESIZE_Y-1] |= B10001000;
    }
    for(int i_y=0;i_y<MAZESIZE_Y;i_y++){
        map[0][i_y]            |= B01000100;
        map[MAZESIZE_X-1][i_y] |= B00010001;
    }
    map[0][0]=B11110111;   
}

void Adachi::InitStepMap(int target_x, int target_y){
    for(int i_x=0;i_x<MAZESIZE_X;i_x++){
        for(int i_y=0;i_y<MAZESIZE_Y;i_y++){
            step_map[i_x][i_y]=default_step_value;
        }
    }
    if(0 < target_x && target_x < MAZESIZE_X && 0 < target_y && target_y < MAZESIZE_Y){
        step_map[target_x][target_y]=0;
    }else{
        step_map[0][0]=0;
    }
}

void Adachi::MakeStepMap(int target_x, int target_y, WallMask mask){
    InitStepMap(target_x,target_y);

    bool update_flag=true;
    while(update_flag == true){
        update_flag = false;

        for(int i_x=0; i_x<MAZESIZE_X; i_x++){
            for(int i_y=0; i_y<MAZESIZE_Y; i_y++){
                if(step_map[i_x][i_y]==default_step_value)continue;

                if(i_y < MAZESIZE_Y -1){
                    //No Wall to the North
                    if(( (map[i_x][i_y] & B10001000) == (B10000000) ) || 
                       (int)mask*( (map[i_x][i_y] & B10000000) == (B00000000) ) ){
//                    if((map[i_x][i_y] & B10001000) != (B10001000) ){
                        if(step_map[i_x][i_y+1] == default_step_value){
                            step_map[i_x][i_y+1]=step_map[i_x][i_y]+1;
                            update_flag=true;
                        }
                    }
                }

                if(i_x < MAZESIZE_X -1){
                    //No Wall to the East
                    if(( (map[i_x][i_y] & B00010001) == (B00010000) ) ||
                       (int)mask*( (map[i_x][i_y] & B00010000 ) == (B00000000) ) ){
//                    if((map[i_x][i_y] & B00010001 ) != (B00010001) ){
                        if(step_map[i_x+1][i_y] == default_step_value){
                            step_map[i_x+1][i_y]=step_map[i_x][i_y]+1;
                            update_flag=true;
                        }
                    }
                }

                if(i_y > 0){
                    //No Wall to the South
                    if(( (map[i_x][i_y] & B00100010) == (B00100000) ) ||
                       (int)mask*( (map[i_x][i_y] & B00100000 ) == (B00000000) ) ){
//                    if((map[i_x][i_y] & B00100010 ) != (B00100010)){
                        if(step_map[i_x][i_y-1] == default_step_value){
                            step_map[i_x][i_y-1]=step_map[i_x][i_y]+1;
                            update_flag=true;
                        }
                    }
                }

                if(i_x > 0){
                    //No Wall to the West
                    if(( (map[i_x][i_y] & B01000100) == (B01000000) ) ||
                       (int)mask*( (map[i_x][i_y] & B01000000) == (B00000000) ) ){
//                    if((map[i_x][i_y] & B01000100 ) != (B01000100)){
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
            map[x][y]=data[x][y];
        }
    }
}

void Adachi::SetMap(int x, int y, int wall_data_4bit , Dirction dir){
    wall_data_4bit &= B00001111;
    switch(dir){
        case North:
            if(x>0)            map[x-1][y] |=B00010000 | (((wall_data_4bit & B0100) == B0100 )<<0);
            if(x<MAZESIZE_X-1) map[x+1][y] |=B01000000 | (((wall_data_4bit & B0001) == B0001 )<<2);
            if(y>0)            map[x][y-1] |=B10000000 | (((wall_data_4bit & B0010) == B0010 )<<3);
            if(y<MAZESIZE_Y-1) map[x][y+1] |=B00100000 | (((wall_data_4bit & B1000) == B1000 )<<1);
            map[x][y]|=B11010000 | (wall_data_4bit & B1101);
            break;
        case West:
            if(x>0)            map[x-1][y] |=B00010000 | (((wall_data_4bit & B0100) == B0100 )<<0);
            if(x<MAZESIZE_X-1) map[x+1][y] |=B01000000 | (((wall_data_4bit & B0001) == B0001 )<<2);
            if(y>0)            map[x][y-1] |=B10000000 | (((wall_data_4bit & B0010) == B0010 )<<3);
            if(y<MAZESIZE_Y-1) map[x][y+1] |=B00100000 | (((wall_data_4bit & B1000) == B1000 )<<1);
//            if(x>0)map[x-1][y]|=B00010000;
            //if(x<MAZESIZE_X-1)map[x+1][y]|=B01000000;
//            if(y>0)map[x][y-1]|=B10000000;
//            if(y<MAZESIZE_Y-1)map[x][y+1]|=B00100000;

            map[x][y]|=B11100000 | (wall_data_4bit & B1110);
            break;
        case South:
            if(x>0)            map[x-1][y] |=B00010000 | (((wall_data_4bit & B0100) == B0100 )<<0);
            if(x<MAZESIZE_X-1) map[x+1][y] |=B01000000 | (((wall_data_4bit & B0001) == B0001 )<<2);
            if(y>0)            map[x][y-1] |=B10000000 | (((wall_data_4bit & B0010) == B0010 )<<3);
            if(y<MAZESIZE_Y-1) map[x][y+1] |=B00100000 | (((wall_data_4bit & B1000) == B1000 )<<1);

//            if(x>0)map[x-1][y]|=B00010000;
//            if(x<MAZESIZE_X-1)map[x+1][y]|=B01000000;
//            if(y>0)map[x][y-1]|=B10000000;
            //if(y<MAZESIZE_Y-1)map[x][y+1]|=B00100000;
            map[x][y]|=B01110000 | (wall_data_4bit & B0111);
            break;
        case East:
            if(x>0)            map[x-1][y] |=B00010000 | (((wall_data_4bit & B0100) == B0100 )<<0);
            if(x<MAZESIZE_X-1) map[x+1][y] |=B01000000 | (((wall_data_4bit & B0001) == B0001 )<<2);
            if(y>0)            map[x][y-1] |=B10000000 | (((wall_data_4bit & B0010) == B0010 )<<3);
            if(y<MAZESIZE_Y-1) map[x][y+1] |=B00100000 | (((wall_data_4bit & B1000) == B1000 )<<1);

            //if(x>0)map[x-1][y]|=B00010000;
//            if(x<MAZESIZE_X-1)map[x+1][y]|=B01000000;
//            if(y>0)map[x][y-1]|=B10000000;
//            if(y<MAZESIZE_Y-1)map[x][y+1]|=B00100000;
            map[x][y]|=B10110000 | (wall_data_4bit & B1011);
            break;
    }
}

int Adachi::MakePathPlan(int start_x, int start_y, Dirction start_dir, int target_x, int target_y){
    int x=start_x;
    int y=start_y;
    Dirction dir=start_dir;
    int index=0;
    MakeStepMap(target_x, target_y,UNUSE_UNKOWN_WALL_MASK);

    while(x!=target_x || y!=target_y){
//	SCI_printf("(%d,%d)\r\n",x,y);

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
        index++;
    }
    step_plan_length=index;
    is_run_plan=true;
    return step_plan_length;

}

int Adachi::MakeRunPlan(int path_length, Dirction initial_dir){
    if(is_run_plan==false)return -1;
    Dirction pre_dir=initial_dir;
    for(int index=0;index<path_length;index++){
        switch( ((int)step_plan[index] - (int)pre_dir )){
            case -3:
                run_plan[index]=TurnLeft;
                break;
            case -2:
                run_plan[index]=Turn;
                break;
            case -1:
                run_plan[index]=TurnRight;
                break;
            case 0:
                run_plan[index]=Forward;
                break;
            case 1:
                run_plan[index]=TurnLeft;
                break;
            case 2:
                run_plan[index]=Turn;
                break;
            case 3:
                run_plan[index]=TurnRight;
                break;
            default:
                run_plan[index]=Turn;
                break;

        }
        pre_dir=step_plan[index];
    }
    return 1;
}

