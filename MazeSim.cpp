#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>

#include <windows.h>

#include <conio.h>
#include <bitset>

#include "Adachi.hpp"
#include "MazeSolver.hpp"

//map=0b00000000
//map|north known|West known|South known|East known|north wall|West wall|South wall|East wall|


Dirction Rotate90(Dirction now){
    switch(now){
        case North:
            return West;
        case West:
            return South;
        case South:
            return East;
        case East:
            return North;
    }
}
Dirction Rotate270(Dirction now){
    switch(now){
        case North:
            return East;
        case West:
            return North;
        case South:
            return West;
        case East:
            return South;
    }
}

int is_wall(Dirction dir,int map_val){
    switch(dir){
        case North:
            if((map_val & 0b10000000)>>7){
                if((map_val & 0b1000)>>3)return 1;
                return 0;
            }else return -1;
            break;
        case West:
            if((map_val & 0b01000000)>>6){
                if((map_val & 0b0100)>>2)return 1;
                return 0;
            }else return -1;
            break;
        case South:
            if((map_val & 0b00100000)>>5){
                if((map_val & 0b0010)>>1)return 1;
                return 0;
            }else return -1;
            break;
        case East:
            if((map_val & 0b00010000)>>4){
                if((map_val & 0b0001)>>0)return 1;
                return 0;
            }else return -1;
            break;
    }

}
int mouse_pos_x=0;
int mouse_pos_y=0;
int goal_pos_x=GOAL_X;
int goal_pos_y=GOAL_Y;
Dirction mouse_dir=North;

int map_data[][16]=
{
{0b0111,0b0110,0b0011,0b0110,0b0011,0b0110,0b1010,0b1010,0b1010,0b1010,0b1010,0b0010,0b1010,0b0011,0b0110,0b0011},
{0b0100,0b1001,0b1100,0b1001,0b1100,0b0001,0b1110,0b0010,0b1010,0b1010,0b1010,0b0000,0b1010,0b0001,0b0101,0b0101},
{0b1100,0b0010,0b1010,0b0011,0b0110,0b1000,0b0010,0b1001,0b0110,0b0011,0b0110,0b0001,0b0110,0b1001,0b0101,0b0101},
{0b1110,0b0000,0b1011,0b0101,0b0101,0b0111,0b1100,0b1010,0b1001,0b1100,0b0001,0b0100,0b1001,0b0110,0b1001,0b0101},
{0b1110,0b0000,0b1011,0b0101,0b0101,0b0100,0b1010,0b1010,0b1010,0b1010,0b1000,0b1001,0b0111,0b1100,0b0011,0b0101},
{0b1110,0b0000,0b1011,0b0101,0b0101,0b0100,0b1010,0b1010,0b1010,0b1010,0b1010,0b0010,0b0001,0b0110,0b0001,0b0101},
{0b0110,0b1000,0b0011,0b1100,0b0001,0b0101,0b0110,0b1010,0b1010,0b1010,0b0010,0b1001,0b0101,0b0101,0b0101,0b0101},
{0b0101,0b0111,0b1100,0b0011,0b1101,0b0101,0b0100,0b0010,0b0011,0b0111,0b1100,0b0011,0b0101,0b0101,0b0101,0b0101},
{0b0101,0b0100,0b0011,0b1100,0b0011,0b0101,0b1101,0b1100,0b1001,0b0100,0b1010,0b1000,0b0001,0b0101,0b0101,0b0101},
{0b0101,0b0101,0b0100,0b1011,0b0101,0b0101,0b0111,0b0110,0b0011,0b1100,0b0010,0b1010,0b1000,0b1001,0b0101,0b0101},
{0b1100,0b1001,0b0101,0b0110,0b1001,0b0101,0b0100,0b1001,0b1100,0b1010,0b1001,0b0110,0b1010,0b0011,0b0101,0b0101},
{0b0110,0b1010,0b1001,0b1100,0b0011,0b0101,0b0101,0b0110,0b0011,0b0110,0b0011,0b1100,0b0011,0b1100,0b0001,0b0101},
{0b0101,0b0110,0b1010,0b1010,0b1001,0b0101,0b0100,0b0001,0b0100,0b0001,0b0100,0b0011,0b1100,0b0011,0b1101,0b0101},
{0b0100,0b0001,0b0110,0b0011,0b0110,0b0001,0b1101,0b1100,0b1001,0b1100,0b1001,0b1100,0b0011,0b1100,0b0011,0b0101},
{0b0101,0b1100,0b1001,0b1100,0b1001,0b1100,0b1010,0b1010,0b1010,0b1010,0b1010,0b1010,0b1000,0b1010,0b1000,0b0001},
{0b1100,0b1010,0b1010,0b1010,0b1010,0b1010,0b1010,0b1010,0b1010,0b1010,0b1010,0b1010,0b1010,0b1010,0b1010,0b1001}

};

void ShowMaze(MazeSolver* ms){
    std::system("cls");

    for(int i_y=MAZESIZE_Y-1;i_y>=0;i_y--){
        for(int i_x=0;i_x<MAZESIZE_X;i_x++){
            std::cout << "+";
            if(is_wall(North,ms->adachi.GetMapData(i_x,i_y))==1 ) std::cout << "---";
            if(is_wall(North,ms->adachi.GetMapData(i_x,i_y))==0 ) std::cout << "   ";
            if(is_wall(North,ms->adachi.GetMapData(i_x,i_y))==-1) std::cout << " . ";
        }
        std::cout << "+\n";

        for(int i_x=0;i_x<MAZESIZE_X;i_x++){
            if(is_wall(West,ms->adachi.GetMapData(i_x,i_y))==1 ) std::cout << "|";
            if(is_wall(West,ms->adachi.GetMapData(i_x,i_y))==0 ) std::cout << " ";
            if(is_wall(West,ms->adachi.GetMapData(i_x,i_y))==-1) std::cout << ".";
            
            if(i_x==mouse_pos_x && i_y == mouse_pos_y){
                switch(mouse_dir){
                    case North:
                        std::cout << " A ";
                        break;
                    case West:
                        std::cout << " < ";
                        break;
                    case East:
                        std::cout << " > ";
                        break;
                    case South:
                        std::cout << " v ";
                        break;
                }
            }else if(i_x==GOAL_X   && i_y == GOAL_Y  )std::cout << " G ";
            else if(i_x==GOAL_X+1 && i_y == GOAL_Y  )std::cout << " G ";
            else if(i_x==GOAL_X   && i_y == GOAL_Y+1)std::cout << " G ";
            else if(i_x==GOAL_X+1 && i_y == GOAL_Y+1)std::cout << " G ";
            else std::cout << "   ";


            //std::cout << ms->adachi.GetMapData(i_x,i_y) << " | ";
        }    
        std::cout <<"|"<< std::endl;
    }
        for(int i_y=0;i_y<MAZESIZE_Y;i_y++){
            std::cout << "+---";
        }
            std::cout << "+\n";
//            std::cout << "("<< mouse_pos_x << ", " << mouse_pos_y << ", " << mouse_dir << ") (" <<  ", " <<  ") ";
//            std::cout << "("<< mouse_pos_x << ", " << mouse_pos_y << ", " << mouse_dir << ") (" << goal_pos_x << ", " << goal_pos_y << ") ";
            std::cout << "("<< mouse_pos_x << ", " << mouse_pos_y << ") ";
            std::cout << std::showbase;
            std::cout << std::bitset<8>(ms->adachi.GetMapData(mouse_pos_x,mouse_pos_y));
            std::cout << std::noshowbase; /* 解除 */
            std::cout << "\n";

}

void ShowStep(MazeSolver* ms){

    for(int i_y=MAZESIZE_Y-1;i_y>=0;i_y--){
        for(int i_x=0;i_x<MAZESIZE_X;i_x++){
            std::cout << "+";
            if(is_wall(North,ms->adachi.GetMapData(i_x,i_y))==1 ) std::cout << "---";
            if(is_wall(North,ms->adachi.GetMapData(i_x,i_y))==0 ) std::cout << "   ";
            if(is_wall(North,ms->adachi.GetMapData(i_x,i_y))==-1) std::cout << " . ";
        }
        std::cout << "+\n";

        for(int i_x=0;i_x<MAZESIZE_X;i_x++){
            if(is_wall(West,ms->adachi.GetMapData(i_x,i_y))==1 ) std::cout << "|";
            if(is_wall(West,ms->adachi.GetMapData(i_x,i_y))==0 ) std::cout << " ";
            if(is_wall(West,ms->adachi.GetMapData(i_x,i_y))==-1) std::cout << ".";
            
            if(i_x==mouse_pos_x && i_y == mouse_pos_y){
                std::cout << " @ ";
            }else{
                std::cout << std::setw(3) << ms->adachi.GetStepData(i_x,i_y);
            }

            //std::cout << ms->adachi.GetMapData(i_x,i_y) << " | ";
        }    
        std::cout <<"|"<< std::endl;
    }
    for(int i_y=0;i_y<MAZESIZE_Y;i_y++){
        std::cout << "+---";
    }
        std::cout << "+\n";

}


int main()
{
    mouse_pos_x=0;
    mouse_pos_y=0;
    MazeSolver maze_solver;
    maze_solver.Init();
    maze_solver.adachi.SetMapArray(map_data);
    maze_solver.adachi.InitMaze(InitialWall::KNOWN);

    maze_solver.adachi.SeeMap(mouse_pos_x,mouse_pos_y,mouse_dir);

    int esc=0;
    while(esc==0){
        ShowMaze(&maze_solver);

        maze_solver.adachi.MakeStepMap(goal_pos_x,goal_pos_y,WallMask::USE_UNKOWN_WALL_MASK);
        maze_solver.adachi.SeeMap(mouse_pos_x,mouse_pos_y,mouse_dir);
        ShowStep(&maze_solver);

        int c=getch();

        if(c==0xe0){
            switch(getch()){
                case 0x4b:
                    mouse_dir=West;
                    if(mouse_pos_x==0){
                        mouse_pos_x=0;
                    }else{
                        if(is_wall(mouse_dir,maze_solver.adachi.map[mouse_pos_x][mouse_pos_y])==0)mouse_pos_x--;
                    }
                    break;
                case 0x48:
                    mouse_dir=North;
                    if(mouse_pos_y==MAZESIZE_Y-1){
                        mouse_pos_y=MAZESIZE_Y-1;
                    }else{
                        if(is_wall(mouse_dir,maze_solver.adachi.map[mouse_pos_x][mouse_pos_y])==0)mouse_pos_y++;
                    }
                    break;
                case 0x4d:
                    mouse_dir=East;
                    if(mouse_pos_x==MAZESIZE_X-1){
                        mouse_pos_x=MAZESIZE_X-1;
                    }else{
                        if(is_wall(mouse_dir,maze_solver.adachi.map[mouse_pos_x][mouse_pos_y])==0)mouse_pos_x++;
                    }
                    break;
                case 0x50:
                    mouse_dir=South;
                    if(mouse_pos_y==0){
                        mouse_pos_y=0;
                    }else{
                        if(is_wall(mouse_dir,maze_solver.adachi.map[mouse_pos_x][mouse_pos_y])==0)mouse_pos_y--;
                    }
                    break;
                default:
                    esc=1;
                    break;
            }
            maze_solver.adachi.SeeMap(mouse_pos_x,mouse_pos_y,mouse_dir);
        }else if(c=='q'){
            mouse_dir= Rotate90(mouse_dir);
        }else if(c=='e'){
            mouse_dir= Rotate270(mouse_dir);
        }else if(c=='r'){
            goal_pos_x=0;
            goal_pos_y=0;
        }else if(c=='g'){
            goal_pos_x=GOAL_X;
            goal_pos_y=GOAL_Y;
        }else if(c=='s'){
            //ShowStep(&maze_solver);

            int step_length=maze_solver.adachi.MakePathPlan(0,0,North,GOAL_X,GOAL_Y);
            std::cout << "Enter to start\r\n";
            getch();
            for(int i=0;i<step_length;i++){
            //    std::cout << (int)maze_solver.adachi.step_plan[i];
                switch(maze_solver.adachi.step_plan[i]){
                    case West:
                        mouse_dir=West;
                        if(mouse_pos_x==0){
                            mouse_pos_x=0;
                        }else{
                            if(is_wall(mouse_dir,maze_solver.adachi.map[mouse_pos_x][mouse_pos_y])==0)mouse_pos_x--;
                        }
                        break;
                    case North:
                        mouse_dir=North;
                        if(mouse_pos_y==MAZESIZE_Y-1){
                            mouse_pos_y=MAZESIZE_Y-1;
                        }else{
                            if(is_wall(mouse_dir,maze_solver.adachi.map[mouse_pos_x][mouse_pos_y])==0)mouse_pos_y++;
                        }
                        break;
                    case East:
                        mouse_dir=East;
                        if(mouse_pos_x==MAZESIZE_X-1){
                            mouse_pos_x=MAZESIZE_X-1;
                        }else{
                            if(is_wall(mouse_dir,maze_solver.adachi.map[mouse_pos_x][mouse_pos_y])==0)mouse_pos_x++;
                        }
                        break;
                    case South:
                        mouse_dir=South;
                        if(mouse_pos_y==0){
                            mouse_pos_y=0;
                        }else{
                            if(is_wall(mouse_dir,maze_solver.adachi.map[mouse_pos_x][mouse_pos_y])==0)mouse_pos_y--;
                        }
                        break;
                    default:
                        break;
                }
                ShowMaze(&maze_solver);
                Sleep(50);
            }
            maze_solver.adachi.MakeRunPlan(step_length, North);
            for(int i=0;i<step_length;i++){
                switch(maze_solver.adachi.run_plan[i]){
                case Forward:
                    std::cout << "0,";
                case TurnRight:
                    std::cout << "-90,";
                case TurnLeft:
                    std::cout << "90,";
                case Turn:
                    std::cout << "180,";
                }
            }
            getch();

        }else if(c==0x0d){

            Dirction next_dir = maze_solver.adachi.GetNextDirection(mouse_pos_x,mouse_pos_y,mouse_dir);
            switch(next_dir){
                case North:
                    mouse_dir=North;
                    mouse_pos_y++;
                    break;
                case West:
                    mouse_dir=West;
                    mouse_pos_x--;
                    break;
                case South:
                    mouse_dir=South;
                    mouse_pos_y--;
                    break;
                case East:
                    mouse_dir=East;
                    mouse_pos_x++;
                    break;
            }
        }else{
            esc=1;
        }
//        Sleep(100);


    }

    return 0;
}