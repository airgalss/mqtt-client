# About
This example, based on the libmosquitto library and implemented in the C language, demonstrates the process of communication between an MQTT publisher and an MQTT subscriber.

In this scenario, a simulated terminal device acts as an MQTT publisher, reporting the collected data. Subsequently, the central station acts as an MQTT subscriber, subscribing to the topic of this message. Upon successfully receiving the reported data, it notifies the simulated terminal device.

# local deploy
1. Clone this project and its submodules
```
git clone --recurse-submodule https://github.com/airgalss/mqtt-example
```
Or:
```
git clone https://github.com/airgalss/mqtt-example
git submodule update --init
```
2. Install and start MQTT broker.
```
sudo apt install mosquitto
```
3. Install dependency, which usually is installed default on most distros.
```
sudo apt install libssl-dev
```
3. Compile, default dynamic linking.
```
make
```
Otherwise, you can compile with static linking
```
make static
```
4. Change directory to the location of the executable file.
```
cd src
```
5. Firstly run as a MQTT subscriber.
```
./subscriber
```
6. Then open a new tab and run as a MQTT publisher.
```
./publisher
```

# docker deploy
1. Download [docker-compose](https://github.com/docker/compose) and deploy it with just one command
```
docker-compose up
```

# License
MIT license