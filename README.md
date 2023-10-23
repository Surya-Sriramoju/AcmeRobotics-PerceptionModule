# Acme Robotics: Human Obstacle Detection and Tracking System

![GitHub CI](https://github.com/tarunreddyy/AcmeRobotics-PerceptionModule/actions/workflows/ci.yml/badge.svg)
[![codecov](https://codecov.io/gh/tarunreddyy/AcmeRobotics-PerceptionModule/branch/main/graph/badge.svg?token=639bc142-78af-47ce-9058-b08dd74ae79c)](https://codecov.io/gh/tarunreddyy/AcmeRobotics-PerceptionModule)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

Acme Robotics introduces an innovative solution aimed at revolutionizing robot-human interactions in shared environments. The core of this solution is the Perception Module, which focuses on detecting and tracking human obstacles using the YOLO (You Only Look Once) framework and a monocular camera.

## Team Details

| Team 11 |
|---|
| Sprint 1 |
| **Tarun Trilokesh - 118450766** (Driver) |
| **Sai Surya Sriramoju - 119224113** (Navigator) |
| Sprint 2 |
| **Tarun Trilokesh - 118450766** (Navigator) |
| **Sai Surya Sriramoju - 119224113** (Driver) |


## Installation and Execution

Follow the steps below to set up and run the Human Obstacle Detection and Tracking system:

```bash
# Clone the repository:
  git clone https://github.com/tarunreddyy/AcmeRobotics-PerceptionModule.git
  cd AcmeRobotics-PerceptionModule

# Build the project:
  cmake -S ./ -B build/
  cmake --build build/

# Execute the program:
  ./build/PerceptionModule
```

## UML Diagram

The UML diagram provides a detailed view of the class structures, dependencies, and interactions within the Perception Module.
![HumanObstacleDetection UML diagram](UML/UML_diagram.pdf)

## Activity Diagram

The activity diagram showcases the workflow of the Perception Module, detailing the steps involved in human detection and tracking.
![Detection and Tracking activity diagram](UML/UML_activity_diagram.pdf)

## Quad Chard

Quad chart visualizing our robot's human detection and tracking project, showcasing key components and progress.
![Quad Chart for human detection and tracking project](UML/quad_chart.png)

## The video explanation of the phase zero of this project can be found [here](https://drive.google.com/file/d/1l0VtLcwZwrXFP7Ti_4hcNFPFEvkQYVFW/view?usp=sharing)

## Technologies and Tools

- **Programming Language**: C++14
- **Build System**: CMake
- **Unit Testing**: Google Test framework
- **Static Analysis**: cppcheck
- **Coding Standard**: Google C++ Styleguide with cpplint validation
- **Documentation**: Doxygen

## External Libraries

- **YOLO (You Only Look Once)**: Used for real-time human detection and tracking.
- **OpenCV**: Employed for supplementary image processing tasks.

All libraries integrated are open-source, ensuring smooth integration and eliminating potential legal complications.

## Key Features

- Robust Human Obstacle Detection and Tracking using the YOLO framework.
- Comprehensive documentation and unit tests.
- UML and activity diagrams detailing system design and workflow.
- GitHub repository with continuous integration setup.
- Demonstrations showcasing the module's real-world application.

## Collaboration Strategy

Our development process emphasizes pair programming to ensure high-quality code and foster team collaboration. Regular sprint reviews and retrospectives align our efforts with Acme Robotics' vision and project milestones.
