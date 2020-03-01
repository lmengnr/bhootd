# `bhootd`
_Bhoot are a deamons. We can't see them, but they can see us._

`bhootd` is a daemon that runs on nodes and sends CPU usage data to an MQTT message broker. `bhoot` can display this data too.


## Build
```console
$ sudo apt update
$ sudo apt install -y libboost1.65-all-dev build-essential gcc make cmake cmake-gui cmake-curses-gui libssl-dev doxygen graphviz
$ cd thirdparty
$ git clone -b v1.3.1 https://github.com/eclipse/paho.mqtt.c.git
$ git clone -b v1.1 https://github.com/eclipse/paho.mqtt.cpp
$ pushd paho.mqtt.c
$ cmake -Bbuild -H. -DPAHO_WITH_SSL=ON -DPAHO_ENABLE_TESTING=OFF
$ sudo cmake --build build/ --target install
$ sudo ldconfig
$ popd
$ pushd paho.mqtt.cpp
$ cmake -Bbuild -H.
$ sudo cmake --build build/ --target install
$ sudo ldconfig
$ popd
$ 
$ mkdir build
$ cd build 
$ cmake ..
$ make
```

## Broker Setup
Here's how you can setup an MQTT broker for yourself.

Open a terminal and run the following command
```console
docker run -it -p 1883:1883 -p 9001:9001 eclipse-mosquitto
```

Now on seperate terminals run:
```console
mosquitto_sub -t cpu/json 
```

```console
mosquitto_sub -t cpu/usage 
```

This will create subscribers on which you can publish. The subscriber topic is "cpu", with 2 subtopics "json" and "usage". 
You can also setup a subscriber on your phones which will also be able to recieve the published messages. There are a number of apps for it. Now you are ready to publish, look at the usage below.


## Usage

```console
$ ./bhoot --help                                  
bhootd is a daemon that runs on nodes and sends CPU usage data to an MQTT message broker.
Allowed Options:
  --help                Print help messages
  --broker-addr arg     <IP address of broker e.g. 127.0.0.1>
  --node-id arg         ID of this node

```

## Components

- Boost 1.65
- Eclipse Paho™ MQTT C++ Client v1.1


