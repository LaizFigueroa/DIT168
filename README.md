# DIT168 - GP13



## Introduction
(1 paragraph)


## Organization
At this point of the project, the start, the repository is divided into five main folders: 

**1. Documentation:** Where all the documentation created along the project will be listed. 

**2. DockerImages:** Where you will find all the docker images created for the project.

**3. ProductionCode:** Where all the code will be available. Probably this folder will have subfolders when the development phase is advancing.

**4. TestEnvironment:** Folder to contain tests built for the project.

**5. Resources:** Libraries, images, anything used as a resource to the project will be available in this folder.

Outside this folders, there are documents that are important for the project's organization, existence, and maintenance, such as the code conventions used to build the project, the license, the contributing and the code of conduct.

## Getting Started
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Cloning
The project can be cloned using the URL provided in the github webpage of the project or you can clone the project by adding the following command on your terminal/bash:
```
git clone https://github.com/LaizFigueroa/DIT168.git
```
### Building
The Docker builds the project following the instructions in the dockerfile. A docker container is launched by running a docker image that will be loaded to the minature car. The docker image loaded is an executable package to run an application–the code, a runtime, libraries, environment variables, and configuration files.

### Runnind the tests
Automated tests:There will be automated tests generated working hand-in-hand with the production code.
Manual Tests:  upon pull request and integration testing, the features implemented will be tested in the simulation environment first. Afterwards, at each milestone  the current version of the development stage  will be uploaded to the car as docker image. Hence, the manual testing can be automatically executed by testing the behaviour of the car.

