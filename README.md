# About
This example, based on the libmosquitto library and implemented in the C language, demonstrates the process of communication between an MQTT publisher and an MQTT subscriber.

In this scenario, a simulated terminal device acts as an MQTT publisher, reporting the collected data. Subsequently, the central station acts as an MQTT subscriber, subscribing to the topic of this message. Upon successfully receiving the reported data, it notifies the simulated terminal device.

# Installation and Run
1. install and start MQTT broker
```
sudo apt install mosquitto
```
2. install MQTT development library
```
sudo apt install libmosquitto-dev
sudo apt install libssl-dev
```
3. compile
```
make
```
4. firstly run a MQTT subscriber
```
cd src
./subscriber
```
5. then run a MQTT publisher
```
./publisher
```