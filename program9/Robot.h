#ifndef ROBOT_H
#define ROBOT_H

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

class Robot {

    public:
        // exceptions

            class Crash{}; // thrown if robot crashes

        Robot();
            // initializes to full battery, no reporting, speed
            // 0, direction 0, height 0, in recharge state;

        Robot(unsigned long charge);
            // initializes to battery with specified charge, no
            // reporting, speed 0, direction 0, height 0, in
            // recharge state;

        void execute(unsigned char command) throw(Crash);
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

        // commands -- first 4 bits of command character.  Second
        // 4 bits represent supplementary information (e.g.
        // units)

        enum RobotCommand {stop=0, on=1, recharge=2, accelerate=3,
             decelerate=4, raise=5, lower=6, left=7, right=8,
             reportspeed=9, reportheight=10, reportdirection=11,
             reportbattery=12, reporttime=13, operate=14};

        enum OnOff {turnOn=1, turnOff=0};

            // note: reporting, if active, is done at the end of each
            // command.  All commands print a message stating
            // what the command is and what it is doing.

            // stop
                // causes robot lower to height 0, decelerate to
                // speed 0, turn to direction 0 (north), staying
                // in on state.  ignored if already stopped or in
                // recharge state

            // on 
                // takes out of recharge state, ignored if not in
                // recharge state

            // recharge
                // puts into recharge state.  ignored if not
                // speed and height 0.

            // accelerate units
                // increases speed by specified number of units
                // up to maximum speed of 15.  Excess reported
                // and ignored

            // decelerate units
                // decreases speed by specified number of units
                // down to minimum speed of 0. Excess reported
                // and ignored

            // raise units
                // increases height by specified number of units
                // up to maximum height of 15.  Excess reported
                // and ignored

            // lower units
                // decreases height by specified number of units
                // down to minimum height of 0.  Excess reported
                // and ignored

            // right points
                // turns to right (increasing points) up to 15
                // points (337.5 degrees).  Note north is 0, East
                // is 4, south is 8, west is 12.  Each point is
                // 22.5 degrees (1/16th of a full circle).

            // left points
                // turns to left (decreasing points) up to 15
                // points

            // operate timeUnits
                // causes current speed and height to be
                // maintained at current direction, or amount of
                // time for recharge or stopped state.

            // reportspeed 0/1
                // 0 turns speed reporting off, 1 turns it on.
                // if already in that state report and ignore

            // reportheight 0/1
                // 0 turns height reporting off, 1 turns it on.
                // if already in that state report and ignore

            // reportdirection 0/1
                // 0 turns direction reporting off, 1 turns it on.
                // if already in that state report and ignore

            // reportbattery 0/1
                // 0 turns battery units left reporting off, 1
                // turns it on.  if already in that state report
                // and ignore

            // reporttime 0/1
                // 0 turns battery time left reporting off, 1 turns it on.
                // if already in that state report and ignore

            // operate timeunits
                // causes robot to continue for specified time
                // units at current activity level.  Reporting,
                // if active, is done at end of time specified.

    private:

        unsigned long state;
            // contains all the robot state information
            //  on/recharge -- 1 bit
            //  speed       -- 4 bits (0-15)
            //  height      -- 4 bits (0-15)
            //  direction   -- 4 bits (0-15)
            //  reporting   -- 5 bits (1 bit each, speed,
            //                         direction, height,
            //                         battery, timeleft)
            //  battery     -- 14 bits (integer)

        void doOn();
            // turns on, error message if already on;

        void doRecharge();
            // puts into recharge state if at 0 height and 0
            // speed.  Message otherwise

        void doSpeedReporting(unsigned long arg);
        void doDirectionReporting(unsigned long arg);
        void doHeightReporting(unsigned long arg);
        void doBatteryReporting(unsigned long arg);
        void doTimeLeftReporting(unsigned long arg);
            // turns on or off depending on argument
            // error message if already on

        void doOperate(unsigned long arg);
            // continues current operating state for specified
            // time.  determines power consumption

        void doAccelerate(unsigned long arg);
            // accelerates by amount of argument

        void doDecelerate(unsigned long arg);
            // decelerates by amount of argument

        void doRaise(unsigned long arg);
            // raises by amount of argument

        void doLower(unsigned long arg);
            // lowers by amount of argument

        void doLeft(unsigned long arg);
            // turns left

        void doRight(unsigned long arg);
            // turns right

        void doStop();
            // causes robot do go to 0 speed, 0 height, direction
            // 0

        unsigned long getTimeLeft() const;
            // returns estimate of battery time left at current
            // speed and height.  Note, if recharging, returns
            // time left until full recharge.  If stopped,
            // returns 2^32-1

        void doCrash() throw(Crash);
            // check speed/height if battery goes to 0, if both
            // not 0, robot crashes.
};

#endif
