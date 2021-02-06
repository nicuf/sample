
#include "Robot.h"

int main(int argc, char *argv[])
{

    Robot::Warehouse::init(4, 3);
    Robot::Robot robot;
    robot.Undo();
    robot.ExecuteCommand(std::make_unique<Robot::Move>(1, 0));
    robot.ExecuteCommand(std::make_unique<Robot::Fill>(1, 20));
    robot.ExecuteCommand(std::make_unique<Robot::Move>(2, 1));
    robot.Undo();
    robot.ExecuteCommand(std::make_unique<Robot::Move>(3, 0));
    robot.Redo();
    robot.Undo();
    robot.Undo();
    robot.Undo();
    robot.Undo();
    robot.Undo();
    robot.Undo();
    robot.Undo();
    robot.Redo();
    robot.Redo();
    robot.Redo();
    robot.Redo();
    robot.Redo();
    robot.Redo();
    robot.Redo();
    return 0;
}
