# DIT168 - GP13



## Introduction
This project is about an autonomous car that is able to be controlled via ps4 controller or by our Android app to navigate the road during driving process. The main feature of this car is a platooning system in which the car connects to other cars using the V2V-protocol and safely follow or lead the others, by sending/receiving the commands.

## Organization
This repository is divided into three main folders: 

**1. Joystick:** Where the code for the Android app is stored. 

**2. src:** Where all the source code is available, including links to other repositories forked.
      
      **2.1. Ancient:** Code that was used in the development phases and is not required anymore.
      
      **2.2. Interceptor:** This folder contains the interceptor microservice, which is responsible to handle sensors and internal communications. It is possible to build a docker image directly on this folder to run the related microservice individually.
      
      **2.3. app-server:** On this folder the server microservice to run on the car for the android application can be found.
      
      **2.4. opendlv-signal-viewer:** On this submodule, you are going to be redirected to a new repository. This code is used to visualize the data exchanged during the communication.
      
      **2.5. opendlv.miniature:** On this submodule, you can find the ps4 microservice. By clicking on that you will be redirected to a new repository. There you should select the `dit168` branch, go under `usecases/latest/test.ps4controller` and run docker-compose up.
      
      **2.6. v2v-microservice:** On this folder you can find the microservice for communication across vehicles.
      
      **2.7. docker-compose.yml & configuration:** Files to run all the microservices on the car at the same time.

**3. test:** This folder contains the TDD tests designed at the beginning of the project, but not used along the development phases and the dockerfile to build the test environment.

On the root directory, there are documents that are important for the project's organization, existence, and maintenance, such as the code conventions used to build the project, the license, the contributing, the code of conduct, scripts, Travis, git modules list.

## Getting Started
These instructions will get you a copy of the project up and run on your local machine for development and testing purposes.

### Cloning
The project can be cloned using the URL provided in the GitHub webpage of the project or you can clone the project by adding the following command on your terminal/bash:
```
git clone --recurse-submodules https://github.com/LaizFigueroa/DIT168.git
```
### Building
The Docker builds the project following the instructions in the dockerfile. A docker container is launched by running a docker image that will be loaded to the miniature car. The docker image loaded is an executable package to run an application–the code, a runtime, libraries, environment variables, and configuration files. To be able to build each microservice independently you should access `src/<microservice>` and then:

- To build and send to the car using a .tar file
```
docker build -t dockerimg -f Dockerfile.manual.

docker save dockerimg > dit168.tar

cat dit168.tar | docker load
```

- To build and send to docker hub repository
```
docker build -t dockerimg -f Dockerfile.manual.

docker tag dockerimg DOCKER_HUB_REPOSITORY/dockerimg

docker push DOCKER_HUB_REPOSITORY/dockerimg
```

### Running tests
Automated tests: There will be automated tests for the `master` generated by Travis working hand-in-hand with the production code, available on: [![Build Status](https://travis-ci.org/LaizFigueroa/DIT168.svg?branch=master)](https://travis-ci.org/LaizFigueroa/DIT168).

Manual Tests: Upon pull request and integration testing, the features implemented will be tested in the simulation environment first, this is done using the docker image created using the `test/Dockerfile` and running manually the specific tool needed. You can use it by running the following command:
```
docker build -t test .
docker run test
```
### Docker Image
A docker image for the car is available on our [V2V Docker hub repository](https://hub.docker.com/r/laiz/v2v/), [App-Server Docker hub repository](https://hub.docker.com/r/laiz/app/), [Interceptor Docker hub repository](https://hub.docker.com/r/laiz/interceptor/) and [Webview Docker hub repository](https://hub.docker.com/r/laiz/webview/)or you can add the following command to your terminal:
```
docker pull laiz/v2v
docker pull laiz/interceptor
docker pull laiz/app
docker pull laiz/webview
```
Two docker images are built for the Ubuntu, in case of need or for testing purposes. They can be found on our [Webview_Ubuntu Docker hub repository](https://hub.docker.com/r/laiz/webview_ubuntu/), and [V2V_Ubuntu Docker hub repository](https://hub.docker.com/r/laiz/v2v_ubuntu/) or you can add the following command to your terminal:

```
docker pull laiz/webview_ubuntu
docker pull laiz/v2v_ubuntu
```

### Docker Compose
The file docker-compose.yml on the `src` directory contains all project's included microservices to run on the car. Only this file is necessary to be present on the car and the following command should be added to the terminal:
```
docker-compose up
```
