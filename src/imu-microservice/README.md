# IMU

This folder contains the Inertial Measurement Unit (IMU) microservice to be used directly on the car. 

**Steps:**

1. Add this folder to your car;

2. On your terminal: $`cd imu-microservice`

3. Then, $`make`

4. Finally, $`./imu`

The log printer are the IMU readings, connected to it this microservice the UDP sender will make the data available to the UDP Receiver microservice, named imu-receiver-microservice.
