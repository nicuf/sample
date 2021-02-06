#ifndef ICOMMANDMANAGER_H
#define ICOMMANDMANAGER_H

#include "IReversibleCommand.h"

#include <memory>

namespace Robot
{

class ICommandManager
{
public:
    virtual void ExecuteCommand(std::unique_ptr<IReversibleCommand>) = 0;
    virtual void Undo() = 0;
    virtual void Redo() = 0;
    virtual ~ICommandManager(){}
};
}

#endif // ICOMMANDMANAGER_H
