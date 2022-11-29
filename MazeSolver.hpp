#ifndef _MAZESOLVER_HPP_
#define _MAZESOLVER_HPP_

#include "MazeDef.hpp"
#include "Adachi.hpp"


class MazeSolver{
private:
public:
    Adachi adachi;
    MazeSolver();
    void Init();

    RunPattern Update();
};

#endif //_MAZESOLVER_HPP_