#ifndef ROBOT_H
#define ROBOT_H

#include "Warehouse.h"
#include "IReversibleCommand.h"
#include "ICommandManager.h"

#include <memory>
#include <vector>
#include <string>
#include <iostream>

namespace Robot
{

class Move : public IReversibleCommand
{
    WareHouseState warehouseBeforeState;
    int mMovedContainer, mOnToContainer;
public:
    Move(int movedContainer, int ontoContainer) :
        mMovedContainer(movedContainer), mOnToContainer(ontoContainer), warehouseBeforeState(Warehouse::getInstance().getState())
    {}

    void Execute() override
    {
        warehouseBeforeState = Warehouse::getInstance().getState();
        //make room for the container
        //put the container
        std::cout << "Move( " << mMovedContainer << ", " << mOnToContainer << " )" << std::endl;

    }

    void Undo() override
    {
        Warehouse::getInstance().restoreState(warehouseBeforeState);
        std::cout << "Undo Move( " << mMovedContainer << ", " << mOnToContainer << " )" << std::endl;
    }
};

class Fill : public IReversibleCommand
{
    WareHouseState warehouseBeforeState;
    int mContainer, mAmount;
public:
    Fill(int container, int amount) : mContainer(container), mAmount(amount), warehouseBeforeState(Warehouse::getInstance().getState())
    {
    }

    void Execute() override
    {
        warehouseBeforeState = Warehouse::getInstance().getState();
        //make room above the container
        //fill the container with the amount
        std::cout << "Fill( " << mContainer << ", " << mAmount << " )" << std::endl;
    }

    void Undo() override
    {
        Warehouse::getInstance().restoreState(warehouseBeforeState);

        std::cout << "Undo Fill( " << mContainer << ", " << mAmount << " )" << std::endl;
    }
};

class Robot : public ICommandManager
{
    std::vector<std::unique_ptr<IReversibleCommand>> mExecutedCommands;
    int mExecutedCommandPosition = -1;
public:

    void ExecuteCommand(std::unique_ptr<IReversibleCommand> command) override
    {
        std::cout << "Robot executes: ";
        command->Execute();
        mExecutedCommands.resize(mExecutedCommandPosition + 1);
        mExecutedCommands.push_back(std::move(command));
        mExecutedCommandPosition++;
    }

    void Undo() override
    {

        std::cout << "Robot undo: ";
        const bool existsUndoCommand = mExecutedCommandPosition > -1;
        if(existsUndoCommand)
        {
            mExecutedCommands[mExecutedCommandPosition]->Undo();
            mExecutedCommandPosition--;
        }
        else
        {
            std::cout << "Nothing to undo." << std::endl;
        }
    }

    void Redo() override
    {

        std::cout << "Robot redo: ";
        const bool existsRedoCommands = mExecutedCommandPosition < (static_cast<int>(mExecutedCommands.size()) - 1);
        if(existsRedoCommands)
        {
            mExecutedCommands[++mExecutedCommandPosition]->Execute();
        }
        else
        {
            std::cout << "Nothing to redo." << std::endl;
        }
    }

};

}

#endif // ROBOT_H
