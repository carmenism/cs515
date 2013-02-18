/* Carmen St. Jean, CS 515, Assignment 9, November 23, 2009 */

/* this class defines a robot which will respond to a number of
 * numeric commands.  It has a battery, which is consumed at
 * different rates depending on the commands and its current
 * speed and height.  The robot can be set to report on its
 * speed, direction, height, battery power, and time left at
 * current consumption level, and this reporting can be turned
 * off.  The robot can put itself into a recharge state if the
 * power level gets too low, and can be manually put into a
 * recharge state as well.
 *
 * ALL reporting is done to STANDARD ERROR.
 */

#include "Robot.h"
#include <iostream>
using namespace std;

   // shift values
   const int speedShift = 1;
   const int heightShift = 5;
   const int directionShift = 9;
   const int rSpeedShift = 13;
   const int rDirectionShift = 14;
   const int rHeightShift = 15;
   const int rBatteryShift = 16;
   const int rTimeShift = 17;
   const int batteryShift = 18;

   // masks
   const unsigned long batteryMask = 0x3fffL;
   const unsigned long fourBits = 0xfL;
   const unsigned long oneBit = 0x1L;

   // initializes to full battery, no reporting, speed
   // 0, direction 0, height 0, in recharge state;
   Robot::Robot()
   {
      state = batteryMask << batteryShift;
   }


   // initializes to battery with specified charge, no
   // reporting, speed 0, direction 0, height 0, in
   // recharge state;
   Robot::Robot(unsigned long charge)
   {
      state = charge << batteryShift;
   }

   // causes command to be executed.  Bad commands are
   // reported to standard error and ignored.
   // each command prints a message indicating what
   // command is being executed

   // the first (most significant) 4 bits of the command
   // are the command operation code (values specified
   // below).  The second (least significant) 4 bits are
   // the extra "argument" information needed for some
   // commands.  The argument depends on the command,
   // but will either be a number (0-15) or a boolean
   // (turnOn, turnOff), depending on the situation.

   // if the battery runs out when trying to stop, or
   // decelerate or lower the appropriate amount to get to 0.
   // For any command, it is assumed that there is
   // enough residual power left in the system to
   // accomplish that command as long as there is any
   // power a the start of the command

   // the recharge, and report setting commands
   // consume no power, and can be performed when the
   // battery is at 0.  The other commands must have
   // some battery charge at the start -- if not, they
   // give an error message and do not perform their
   // function

   // there must be a power charge to turn the robot on

   // the robot does not have to be on to perform the
   // report setting commands or the operate command
   // (which is really there to simulate the passage of
   // time).  It must be on for any other commands
   // (other than on, of course).

   // if at the end of a command, the battery is at 0
   // and the robot is not at 0 height and speed the
   // robot will crash (throws exception)

   // if at the end of a command the robot is at rest (0
   // speed and height) and the battery charge is at 0,
   // the robot automatically goes into the recharge state.
   void Robot::execute(unsigned char command) throw (Crash)
   {
      int opCode = command >> 4;
      unsigned long argument = command & fourBits;

      if (opCode == stop)
      {
         cerr << "   robot stopping\n";
         doStop();
      }
      else if (opCode == on)
      {
         cerr << "   robot turning on\n";
         doOn();
      }
      else if (opCode == recharge)
      {
         cerr << "   robot recharging\n";
         doRecharge();
      }
      else if (opCode == accelerate)
      {
         cerr << "   robot accelerating\n";
         doAccelerate(argument);
      }
      else if (opCode == decelerate)
      {
         cerr << "   robot decelerating\n";
         doDecelerate(argument);
      }
      else if (opCode == raise)
      {
         cerr << "   robot rising\n";
         doRaise(argument);
      }
      else if (opCode == lower)
      {
         cerr << "   robot lowering\n";
         doLower(argument);
      }
      else if (opCode == left)
      {
         cerr << "   robot turning left\n";
         doLeft(argument);
      }
      else if (opCode == right)
      {
         cerr << "   robot turning right\n";
         doRight(argument);
      }
      else if (opCode == reportspeed)
      {
         cerr << "   robot changing speed report state\n";
         doSpeedReporting(argument);
      }
      else if (opCode == reportheight)
      {
         cerr << "   robot changing height report state\n";
         doHeightReporting(argument);
      }
      else if (opCode == reportdirection)
      {
         cerr << "   robot changing direction report state\n";
         doDirectionReporting(argument);
      }
      else if (opCode == reportbattery)
      {
         cerr << "   robot changing battery report state\n";
         doBatteryReporting(argument);
      }
      else if (opCode == reporttime)
      {
         cerr << "   robot changing time left report state\n";
         doTimeLeftReporting(argument);
      }
      else if (opCode == operate)
      {
         cerr << "   robot continuing operation\n";
         doOperate(argument);
      }
      else
      {
         cerr << "   unknown operation [" << opCode << "]\n";
      }

      if (((state & oneBit) == 1)  &&
          (((state >> batteryShift) & batteryMask) == 0) &&
          ((((state >> heightShift) & fourBits) != 0) ||
           (((state >> speedShift) & fourBits != 0))))
      {
         doCrash();
      }
      else
      {
         if (((state & oneBit) == 1)  &&
             (((state >> batteryShift) & batteryMask) == 0))
            state &= ~(oneBit);

         // reporting
         if ((state >> rSpeedShift) & oneBit)
         {
            unsigned long speed = (state >> speedShift) & fourBits;
            cerr << "   current speed: " << speed << "\n";
         }

         if ((state >> rHeightShift) & oneBit)
         {
            unsigned long height = (state >> heightShift) & fourBits;
            cerr << "   current height: " << height << "\n";
         }

         if ((state >> rDirectionShift) & oneBit)
         {
            unsigned long direction = (state >> directionShift) & fourBits;
            cerr << "   current direction: " << direction << "\n";
         }

         if ((state >> rBatteryShift) & oneBit)
         {
            unsigned long battery = (state >> batteryShift) & batteryMask;
            cerr << "   current battery: " << battery << "\n";
         }

         if ((state >> rTimeShift) & oneBit)
         {
            cerr << "   current time left: " << getTimeLeft() << "\n";
         }
      }
   }

   // turns on, error message if already on;
   void Robot::doOn()
   {
      if (state & oneBit)
      {
         cerr << "      already on\n";
      }
      else if (state >> batteryShift == 0)
      {
         cerr << "   -- battery empty, recharging\n";
      }
      else
      {
         state |= oneBit;
      }
   }

   // puts into recharge state if at 0 height and 0
   // speed.  Message otherwise
   void Robot::doRecharge()
   {
      if ((state & oneBit) == 0)
      {
         cerr << "      already recharging\n";
      }
      else if (((state >> speedShift) & fourBits) == 0 &&
               ((state >> heightShift) & fourBits) == 0)
      {
         state &= ~(oneBit);
      }
      else
      {
         cerr << "    not at rest\n";
      }
   }

   // turns on or off depending on argument
   // error message if already on
   void Robot::doSpeedReporting(unsigned long arg)
   {
      if (arg == turnOff)
      {
         state &= ~(oneBit << rSpeedShift);
      }
      else if ((state >> rSpeedShift) & oneBit)
      {
         cerr << "      already on\n";
      }
      else
      {
         state |= (oneBit << rSpeedShift);
      }
   }

   // turns on or off depending on argument
   // error message if already on
   void Robot::doDirectionReporting(unsigned long arg)
   {
      if (arg == turnOff)
      {
         state &= ~(oneBit << rDirectionShift);
      }
      else if ((state >> rDirectionShift) & oneBit)
      {
         cerr << "      already on\n";
      }
      else
      {
         state |= (oneBit << rDirectionShift);
      }
   }

   // turns on or off depending on argument
   // error message if already on
   void Robot::doHeightReporting(unsigned long arg)
   {
      if (arg == turnOff)
      {
         state &= ~(oneBit << rHeightShift);
      }
      else if ((state >> rHeightShift) & oneBit)
      {
         cerr << "      already on\n";
      }
      else
      {
         state |= (oneBit << rHeightShift);
      }
   }

   // turns on or off depending on argument
   // error message if already on
   void Robot::doBatteryReporting(unsigned long arg)
   {
      if (arg == turnOff)
      {
         state &= ~(oneBit << rBatteryShift);
      }
      else if ((state >> rBatteryShift) & oneBit)
      {
         cerr << "      already on\n";
      }
      else
      {
         state |= (oneBit << rBatteryShift);
      }
   }

   // turns on or off depending on argument
   // error message if already on
   void Robot::doTimeLeftReporting(unsigned long arg)
   {
      if (arg == turnOff)
      {
         state &= ~(oneBit << rTimeShift);
      }
      else if ((state >> rTimeShift) & oneBit)
      {
         cerr << "      already on\n";
      }
      else
      {
         state |= (oneBit << rTimeShift);
      }
   }

   // continues current operating state for specified
   // time.  determines power consumption
   void Robot::doOperate(unsigned long arg)
   {
      int currentSpeed = (state >> speedShift) & fourBits;
      int currentHeight = (state >> heightShift) & fourBits;
      int currentBattery = (state >> batteryShift) & batteryMask;

      if ((state & oneBit) == 0)
      {
         currentBattery += arg;

         if (currentBattery > 16383)
            currentBattery = 16383;
      }
      else
      {
         currentBattery -= 3*arg*currentHeight;
         currentBattery -= 2*arg*currentSpeed;

         if (currentBattery < 0)
            currentBattery = 0; // CRASH!!!!!!!!!!!!!!!!
      }

      state = (state & ~(batteryMask << batteryShift)) | ((batteryMask & currentBattery) << batteryShift);
   }

   // accelerates by amount of argument
   void Robot::doAccelerate(unsigned long arg)
   {
      int currentSpeed = (state >> speedShift) & fourBits;
      int diff, currentBattery, excess;

      if (currentSpeed + arg > 15)
      {
         diff = 15 - currentSpeed;
         currentSpeed = 15;
      }
      else
      {
         diff = arg;
         currentSpeed += arg;
      }

      if ((state & oneBit) == 0)
      {
         cerr << "     not on\n";
      }
      else
      {
         state = (state & ~(fourBits << speedShift)) | ((fourBits & currentSpeed) << speedShift);

         excess = arg - diff;

         if (excess > 0)
         {
            cerr << "      excess: " << excess << "\n";
         }

         currentBattery = (state >> batteryShift) & batteryMask;

         if (currentBattery < (diff * diff))
            currentBattery = 0;
         else
            currentBattery -= (diff * diff);

         state = (state & ~(batteryMask << batteryShift)) | ((batteryMask & currentBattery) << batteryShift);
      }
   }

   // decelerates by amount of argument
   void Robot::doDecelerate(unsigned long arg)
   {
      int currentSpeed = (state >> speedShift) & fourBits;
      int diff = currentSpeed - arg;
      int currentBattery, excess;

      if (diff < 0)
      {
         diff = currentSpeed;
         currentSpeed = 0;
      }
      else
      {
         diff = arg;
         currentSpeed -= arg;
      }

      if ((state & oneBit) == 0)
      {
         cerr << "     not on\n";
      }
      else
      {
         state = (state & ~(fourBits << speedShift)) | ((fourBits & currentSpeed) << speedShift);

         currentBattery = (state >> batteryShift) & batteryMask;

         if (currentBattery < diff)
            currentBattery = 0;
         else
            currentBattery -= diff;

         state = (state & ~(batteryMask << batteryShift)) | ((batteryMask & currentBattery) << batteryShift);

         excess = arg - diff;

         if (excess > 0)
         {
            cerr << "      excess: " << excess << "\n";
         }
      }
   }

   // raises by amount of argument
   void Robot::doRaise(unsigned long arg)
   {
      int currentHeight = (state >> heightShift) & fourBits;
      int diff, currentBattery, excess;

      if (currentHeight + arg > 15)
      {
         diff = 15 - currentHeight;
         currentHeight = 15;
      }
      else
      {
         diff = arg;
         currentHeight += arg;
      }

      if ((state & oneBit) == 0)
      {
         cerr << "     not on\n";
      }
      else
      {
         state = (state & ~(fourBits << heightShift)) | ((fourBits & currentHeight) << heightShift);

         currentBattery = (state >> batteryShift) & batteryMask;

         if (currentBattery < (diff * diff * diff))
            currentBattery = 0;
         else
            currentBattery -= (diff * diff * diff);

         state = (state & ~(batteryMask << batteryShift)) | ((batteryMask & currentBattery) << batteryShift);

         excess = arg - diff;

         if (excess > 0)
         {
            cerr << "      excess: " << excess << "\n";
         }
      }
   }

   // lowers by amount of argument
   void Robot::doLower(unsigned long arg)
   {
      int currentHeight = (state >> heightShift) & fourBits;
      int diff = currentHeight - arg;
      int currentBattery, excess;

      if (diff < 0)
      {
         diff = currentHeight;
         currentHeight = 0;
      }
      else
      {
         diff = arg;
         currentHeight -= arg;
      }

      if ((state & oneBit) == 0)
      {
         cerr << "     not on\n";
      }
      else
      {
         state = (state & ~(fourBits << heightShift)) | ((fourBits & currentHeight) << heightShift);

         currentBattery = (state >> batteryShift) & batteryMask;

         if (currentBattery < diff)
            currentBattery = 0;
         else
            currentBattery -= diff;

         state = (state & ~(batteryMask << batteryShift)) | ((batteryMask & currentBattery) << batteryShift);

         excess = arg - diff;

         if (excess > 0)
         {
            cerr << "      excess: " << excess << "\n";
         }
      }
   }

   // turns left
   void Robot::doLeft(unsigned long arg)
   {
      int currentDirection = (state >> directionShift) & fourBits;
      int currentBattery = (state >> batteryShift) & batteryMask;

      if ((state & oneBit) == 0)
      {
         cerr << "     not on\n";
      }
      else
      {
         currentDirection -= arg % 16;

         if (currentBattery < arg)
            currentBattery = 0;
         else
            currentBattery -= arg;

         state = (state & ~(fourBits << directionShift)) | ((fourBits & currentDirection) << directionShift);
         state = (state & ~(batteryMask << batteryShift)) | ((batteryMask & currentBattery) << batteryShift);
      }
   }

   // turns right
   void Robot::doRight(unsigned long arg)
   {
      int currentDirection = (state >> directionShift) & fourBits;
      int currentBattery = (state >> batteryShift) & batteryMask;

      if ((state & oneBit) == 0)
      {
         cerr << "     not on\n";
      }
      else
      {
         currentDirection += arg % 16;

         if (currentBattery < arg)
            currentBattery = 0;
         else
            currentBattery -= arg;

         state = (state & ~(fourBits << directionShift)) | ((fourBits & currentDirection) << directionShift);
         state = (state & ~(batteryMask << batteryShift)) | ((batteryMask & currentBattery) << batteryShift);
      }
   }

   // causes robot do go to 0 speed, 0 height, direction
   // 0
   void Robot::doStop()
   {
      int currentSpeed = (state >> speedShift) & fourBits;
      int currentHeight = (state >> heightShift) & fourBits;
      int currentDirection = (state >> directionShift) & fourBits;
      int currentBattery = (state >> batteryShift) & batteryMask;

      int total = currentSpeed + currentHeight + currentDirection;

      if ((state & oneBit) == 0)
      {
         cerr << "      already stopped\n";
      }
      else
      {
         if (total > currentBattery)
            currentBattery = 0;
         else
            currentBattery -= total;

         currentSpeed = 0;
         currentHeight = 0;
         currentDirection = 0;

         state = (state & ~(fourBits << speedShift)) | ((fourBits & currentSpeed) << speedShift);
         state = (state & ~(fourBits << heightShift)) | ((fourBits & currentHeight) << heightShift);
         state = (state & ~(fourBits << directionShift)) | ((fourBits & currentDirection) << directionShift);
         state = (state & ~(batteryMask << batteryShift)) | ((batteryMask & currentBattery) << batteryShift);
      }
   }


   // returns estimate of battery time left at current
   // speed and height.  Note, if recharging, returns
   // time left until full recharge.  If stopped,
   // returns 2^32-1
   unsigned long Robot::getTimeLeft() const
   {
      unsigned long battery = (state >> batteryShift) & batteryMask;

      if ((state & oneBit) == 0)
      {
         return (0x3fffUL - battery);
      }
      else if (((state >> heightShift) & fourBits) == 0 &&
           ((state >> speedShift) & fourBits) == 0)
      {
         return (0xffffffffUL);
      }
      else
      {
         int currentSpeed = (state >> speedShift) & fourBits;
         int currentHeight = (state >> heightShift) & fourBits;

         int total = 3*currentHeight + 2*currentSpeed;

         return ((battery / total) + 1);
      }
   }

   // check speed/height if battery goes to 0, if both
   // not 0, robot crashes.
   void Robot::doCrash() throw(Crash)
   {
      throw Crash();
   }

