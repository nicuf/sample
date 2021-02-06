#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <vector>
#include <iostream>

namespace Robot
{

struct WareHouseState
{

    std::vector<int> mContainerStack;

    //other things that are relevant saving

    WareHouseState(std::vector<int> containerStack) : mContainerStack(containerStack){}
};

class Warehouse
{
    Warehouse(int floorSpace, int maxContainersPerStack) :
        mFloorSpace(floorSpace),
        mMaxContainersPerStack(maxContainersPerStack),
        mContainerStack(mFloorSpace * maxContainersPerStack, 0)
    {}

    static Warehouse& getInstanceIntern(int floorSpace = 0, int maxContainersPerStack = 0)
    {
        static Warehouse instance(floorSpace, maxContainersPerStack);
        return instance;
    }

public:
    const int mFloorSpace;
    const int mMaxContainersPerStack = 0;
    std::vector<int> mContainerStack;

    Warehouse() = delete;

    static void init(int floorSpace, int maxContainersPerStack)
    {
        std::cout << "Warehouse initialized" << std::endl;
        getInstanceIntern(floorSpace, maxContainersPerStack);
    }

    static Warehouse& getInstance()
    {
        return getInstanceIntern();
    }

    WareHouseState getState()
    {
        return WareHouseState(mContainerStack);
    }

    void restoreState(WareHouseState& state)
    {
        mContainerStack = state.mContainerStack;
    }

};
}

#endif // WAREHOUSE_H
