# AcmeRobotics-PerceptionModul

Human obstacle detection and tracking system for robotics using a monocular camera. Utilizes Kalman Filter for real-time tracking to ensure safe robot-human interactions in shared environments.

## Group Details 

| Team 1 |
|---|
| `Tarun Trilokesh - 118450766` (Driver)|
| `Sai Surya Sriramoju - 119224113` (Navigator)|

## Standard install via command-line
```bash
# Download the code:
  git clone https://github.com/tarunreddyy/AcmeRobotics-PerceptionModule.git
  cd AcmeRobotics-PerceptionModule
# Build the project
  cmake -S ./ -B build/
  cmake --build build/
# Run program:
  ./build/PerceptionModule
```

## UML DIAGRAM

![HumanObstacleDetection UML diagram](images/Midterm_UML.png)
## ACTIVITY DIAGRAM

![Detection and Tracking activity diagram](images/Midterm_activity_diagram.png)