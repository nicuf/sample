#ifndef IREVERSIBLECOMMAND_H
#define IREVERSIBLECOMMAND_H

namespace Robot
{
class IReversibleCommand
{
public:
    virtual void Execute() = 0;
    virtual void Undo() = 0;
    virtual ~IReversibleCommand(){}
};

}

#endif // IREVERSIBLECOMMAND_H
