# CarND-Controls-PID
Self-Driving Car Engineer Nanodegree Program

---
## PID Control
PID controllers are simple reactive controllers that are widely used. The difference between the measured and the desired value (setpoint) of a process variable of a system is fed into the PID controller as an error signal. Depending on the PID parameters a control output is generated  to steer the system closer to the setpoint. In the present project, a car simulator produces the error signal as the distance between the actual car position on the road and a reference trajectory, known as cross-track error (cte). The PID controller is designed to minimize the distance to this reference trajectory. The primary control output of the PID controller here is the steering angle. 

### P - proportional gain 
The proportional term computes an output proportional to the cross-track error. A pure P - controller is unstable and at best oscillates about the setpoint. The proportional gain contributes a control output to the steering angle of the form  `-K_p cte` with a positive constant `K_p`.

### D - differential gain
The oscillations caused by purely D control can be mitigated by a term proportional to the derivative of the cross-track error.
The derivative gain contributes a control output of the form `-K_d d/dt cte`, with a positive constant `K_d`. 

### I - integral gain 
A third contribution is given by the integral gain which simply sums up the cross-track error over time. The corresponding contribution to the steering angle is given by `-K_i sum(cte)`. Thereby, biases can be mitigated, for instance if a zero steering angle does not correspond to a straight trajectory. At high speeds this term can also be useful to accumulate a large error signal quickly, for instance when the car is carried out sideways from the reference trajectory. This allows to reduce proportional gain, which causes oscillations at high speeds. It is also beneficial to limit the memory of this term to avoid overshooting. Here, we used an exponentially weighted moving average for this purpose. 

### Extensions
#### Linear parameter-varying control
Using a single PID controller can result in suboptimal performance at different speeds. We therefore implemented the possibility to accomodate different setpoints and to vary the parameters linearly according to the speed the car. For example the coefficient `K_i` is increased linearly as a function of the speed of the car: `K_i = alpha_i * v`. 

#### Smoothened steering angle
The output of the PID controller can result in jerky steering, causing the car to oscillate. A simple heuristic measure to mitigate this instability was to simply use a weighted average of the previous and the current steering angle. While this measure reduces reactivity, it makes the ride much smoother and allows to achieve higher speeds. 

#### Emergency braking
In case the cross-track error increase too quickly a simple emergency measure was to reduce throttle to zero for a few iterations. More severe measures like braking can also be implemented in the same way and lead to reduced cross-track errors at the cost of reduced speed. 

## Hyperparameter Tuning
All parameters were tuned manually. The reason for this approach was that slightly wrong parameters quickly lead to unrecoverable crashes of the car and require a manual restart of the simulator. A more systematic and algorithmic approach including automatic restarts of the simulator can be taken, but here I decided to take the pedestrian approach, because it provides an intuitive understanding of thethe importance of the different contributions. The algorithm used was roughly as follows. 

1. single P controller for one setpoint, with K_i and K_d = 0
2. increase K_d until oscillations subside. 
3. in case of crashes: find cause.
   a) if slow reactivity is the cause -> reduce steering angle smoothing, increase K_p or K_i
   b) if oscillations are the cause -> reduce K_p, K_i or brake 
   
Rounds topping out at speeds of 95mph can be acheived this way, but a much safer ride is obtained when the target speed is set to 70mph. This is what is shown in the video linked below. 

## Dependencies

* cmake >= 3.5
 * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools]((https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* [uWebSockets](https://github.com/uWebSockets/uWebSockets) == 0.13, but the master branch will probably work just fine
  * Follow the instructions in the [uWebSockets README](https://github.com/uWebSockets/uWebSockets/blob/master/README.md) to get setup for your platform. You can download the zip of the appropriate version from the [releases page](https://github.com/uWebSockets/uWebSockets/releases). Here's a link to the [v0.13 zip](https://github.com/uWebSockets/uWebSockets/archive/v0.13.0.zip).
  * If you run OSX and have homebrew installed you can just run the ./install-mac.sh script to install this
* Simulator. You can download these from the [project intro page](https://github.com/udacity/CarND-PID-Control-Project/releases) in the classroom.

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./pid`. 

## Editor Settings

We've purposefully kept editor configuration files out of this repo in order to
keep it as simple and environment agnostic as possible. However, we recommend
using the following settings:

* indent using spaces
* set tab width to 2 spaces (keeps the matrices in source code aligned)

## Code Style

Please (do your best to) stick to [Google's C++ style guide](https://google.github.io/styleguide/cppguide.html).

## Project Instructions and Rubric

Note: regardless of the changes you make, your project must be buildable using
cmake and make!

More information is only accessible by people who are already enrolled in Term 2
of CarND. If you are enrolled, see [the project page](https://classroom.udacity.com/nanodegrees/nd013/parts/40f38239-66b6-46ec-ae68-03afd8a601c8/modules/f1820894-8322-4bb3-81aa-b26b3c6dcbaf/lessons/e8235395-22dd-4b87-88e0-d108c5e5bbf4/concepts/6a4d8d42-6a04-4aa6-b284-1697c0fd6562)
for instructions and the project rubric.

## Hints!

* You don't have to follow this directory structure, but if you do, your work
  will span all of the .cpp files here. Keep an eye out for TODOs.

## Call for IDE Profiles Pull Requests

Help your fellow students!

We decided to create Makefiles with cmake to keep this project as platform
agnostic as possible. Similarly, we omitted IDE profiles in order to we ensure
that students don't feel pressured to use one IDE or another.

However! I'd love to help people get up and running with their IDEs of choice.
If you've created a profile for an IDE that you think other students would
appreciate, we'd love to have you add the requisite profile files and
instructions to ide_profiles/. For example if you wanted to add a VS Code
profile, you'd add:

* /ide_profiles/vscode/.vscode
* /ide_profiles/vscode/README.md

The README should explain what the profile does, how to take advantage of it,
and how to install it.

Frankly, I've never been involved in a project with multiple IDE profiles
before. I believe the best way to handle this would be to keep them out of the
repo root to avoid clutter. My expectation is that most profiles will include
instructions to copy files to a new location to get picked up by the IDE, but
that's just a guess.

One last note here: regardless of the IDE used, every submitted project must
still be compilable with cmake and make./
