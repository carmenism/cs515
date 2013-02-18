/* this program controls several conceptual robots that can move in any
 * of the standard 16 compass directions at varying speeds and
 * varying heights (all at the consumption of power).  The robots
 * are controlled through an interactive command processor, which
 * formulates single byte commands and sends them to the
 * specified robot.
 *
 * the commands are
 *
 *      on                 -- takes out of recharge state
 *      recharge           -- puts into recharge state
 *      accelerate units   -- accelerate by number of units
 *      decelerate units   -- decelerate by number of units
 *      raise units        -- increases height by number of units
 *      lower units        -- decreases height by number of units
 *      left points        -- turns left number of points
 *      right points       -- turns right number of points
 *      speed on/off       -- turns speed reporting on/off
 *      height on/off      -- turns height reporting on/off
 *      direction on/off   -- turns direction reporting on/off
 *      battery on/off     -- turns battery reporting on/off
 *      timeleft on/off    -- turns battery time reporting on/off
 *      operate time       -- causes continued activity for time
 *      stop               -- causes to lower to 0, speed to 0,
 *                            direction to 0, remains on
 *      exit -- terminates program, not a robot command
 *               causes robot to stop and go into recharge state,
 *               with all reporting turned off.
 *
 * reporting (spped, height, direction, battery, time left of
 * power) is done at the end of each command if turned on.  
 *
 * each activity takes some amount of power -- the robot
 * crashes if moving or raised and the battery drops to
 * 0 units.  The robot starts with a fully charged battery.
 * Amount of recharge depends on the amount of time recharging.
 *
 * the operate command tells the robot to continue at current
 * speed, direction, height for specified number of time units.
 * This includes if the robot is stopped or recharging.
 *
 * The program starts by asking how many robots are desired, and
 * then their names (space delimited) and initial battery charge.
 * after this information has been input, then the program enters
 * the interactive command mode.
 *
 * bad commands are reported and ignored.
*/

#include <stdlib.h>
#include <string>
#include <iostream>
using namespace std;

#include "Robot.h"

// constants used

    const string onCom = "on";
    const string rechargeCom = "recharge";
    const string accelerateCom = "accelerate";
    const string decelerateCom = "decelerate";
    const string raiseCom = "raise";
    const string lowerCom = "lower";
    const string leftCom = "left";
    const string rightCom = "right";
    const string reportSpeedCom = "speed";
    const string reportHeightCom = "height";
    const string reportDirectionCom = "direction";
    const string reportBatteryCom = "battery";
    const string reportTimeLeftCom = "timeleft";
    const string continueCom = "operate";
    const string stopCom = "stop";
    const string quitCom = "exit";

    const string turnOn = "on";
    const string turnOff = "off";

// procedures used

    unsigned char buildCom(unsigned char opCode, unsigned char argument);

int main()
{
    int numRobots;
    string * name;
    Robot ** robot;
    string which;
    int index;
    string command;
    string dummy;
    string onOff;
    int units;
    int charge;

    cerr << "how many robots ?> ";
    cin >> numRobots;

    if (numRobots <= 0) {
        cerr << "*** invalid number of robots [" << numRobots
            << "]\n";
        exit(1);
    }

    name = new string [numRobots];
    robot = new Robot *[numRobots];

    cerr << "enter robot names (space deliminated) and " 
         << "initial battery charge\n";

    for (index=0; index<numRobots; index++) {
        cerr << "?> ";
        cin >> name[index] >> charge;
        robot[index] = new Robot(charge);
    }
        
    cerr << "\nenter commands, terminate with " << quitCom << '\n';

    do {
        try {
            cerr << "?> ";
            cin >> which ;

            if (which == quitCom)
                break;

            for (index=0; index<numRobots && name[index] != which; index++);

            if (index == numRobots) {
                cerr << "    bad robot name [" << which << "]\n";
                getline(cin, dummy);
                continue;
            }

            cin >> command;

            if (command == onCom) {
                robot[index]->execute(buildCom(Robot::on,0));
                }

            else if (command == stopCom) {
                robot[index]->execute(buildCom(Robot::stop,0));
                }

            else if (command == rechargeCom) {
                robot[index]->execute(buildCom(Robot::recharge,0));
                }

            else if (command == accelerateCom) {
                cin >> units;
                robot[index]->execute(buildCom(Robot::accelerate,units));
                }

            else if (command == decelerateCom) {
                cin >> units;
                robot[index]->execute(buildCom(Robot::decelerate,units));
                }

            else if (command == raiseCom) {
                cin >> units;
                robot[index]->execute(buildCom(Robot::raise,units));
                }

            else if (command == lowerCom) {
                cin >> units;
                robot[index]->execute(buildCom(Robot::lower,units));
                }

            else if (command == leftCom) {
                cin >> units;
                robot[index]->execute(buildCom(Robot::left,units));
                }

            else if (command == rightCom) {
                cin >> units;
                robot[index]->execute(buildCom(Robot::right,units));
                }

            else if (command == continueCom) {
                cin >> units;
                robot[index]->execute(buildCom(Robot::operate,units));
                }

            else if (command == reportSpeedCom) {
                cin >> onOff;
                if (onOff == turnOn)
                    robot[index]->execute(buildCom(Robot::reportspeed,Robot::turnOn));
                else if (onOff == turnOff)
                    robot[index]->execute(buildCom(Robot::reportspeed,Robot::turnOff));
                else {
                    cerr << "** not on/off [" << onOff << "]\n";
                    getline(cin, dummy);
                    }
                }

            else if (command == reportHeightCom) {
                cin >> onOff;
                if (onOff == turnOn)
                    robot[index]->execute(buildCom(Robot::reportheight,Robot::turnOn));
                else if (onOff == turnOff)
                    robot[index]->execute(buildCom(Robot::reportheight,Robot::turnOff));
                else {
                    cerr << "** not on/off [" << onOff << "]\n";
                    getline(cin, dummy);
                    }
                }

            else if (command == reportDirectionCom) {
                cin >> onOff;
                if (onOff == turnOn)
                    robot[index]->execute(buildCom(Robot::reportdirection,Robot::turnOn));
                else if (onOff == turnOff)
                    robot[index]->execute(buildCom(Robot::reportdirection,Robot::turnOff));
                else {
                    cerr << "** not on/off [" << onOff << "]\n";
                    getline(cin, dummy);
                    }
                }

            else if (command == reportBatteryCom) {
                cin >> onOff;
                if (onOff == turnOn)
                    robot[index]->execute(buildCom(Robot::reportbattery,Robot::turnOn));
                else if (onOff == turnOff)
                    robot[index]->execute(buildCom(Robot::reportbattery,Robot::turnOff));
                else {
                    cerr << "** not on/off [" << onOff << "]\n";
                    getline(cin, dummy);
                    }
                }

            else if (command == reportTimeLeftCom) {
                cin >> onOff;
                if (onOff == turnOn)
                    robot[index]->execute(buildCom(Robot::reporttime,Robot::turnOn));
                else if (onOff == turnOff)
                    robot[index]->execute(buildCom(Robot::reporttime,Robot::turnOff));
                else {
                    cerr << "** not on/off [" << onOff << "]\n";
                    getline(cin, dummy);
                    }
                }

            else {
                cerr << "** bad command [" << command << "]\n";
                getline(cin, dummy);
                robot[index]->execute(buildCom(15,0));
            }

        } catch (Robot::Crash) {
            cerr << name[index] << " has crashed\n";
        }

    } while (command != quitCom);

    delete []name;
    for (index = 0; index<numRobots; index++) 
        delete robot[index];
    delete []robot;

    return 0;
}

// -----------------------------------------------------------
// this function builds the command from the two parts.  The op
// code is the most significant 4 bits, the argument is the
// rightmost 4 bits

unsigned char buildCom(unsigned char opCode, unsigned char argument)
{
    return (opCode << 4) | (0xF & argument);
}
