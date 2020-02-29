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
$ cd paho.mqtt.cpp
$ cmake -Bbuild -H.
$ sudo cmake --build build/ --target install
$ sudo ldconfig
$ 
$ mkdir build
$ cd build 
$ cmake ..
$ cd build
$ make
```

## Usage

```console
$ ./bhoot --help                                  
bhootd is a daemon that runs on nodes and sends CPU usage data to an MQTT message broker.
Allowed Options:
  --help                Print help messages
  --broker-addr arg     <IP address of broker e.g. 127.0.0.1>
  --node-id arg         ID of this node
  --see-stats           display stats

```

## Components

- Boost 1.65
- Eclipse Paho™ MQTT C++ Client v1.1


