# `bhootd`
_Bhoot are a deamons. We can't see them, but they can see us._

`bhootd` is a daemon that runs on nodes and sends CPU usage data to an MQTT message broker. `bhoot` can display this data too.


## Usage

```
$ ./bhoot   --help                Print help messages
            --broker-addr arg     <IP address of broker e.g. 127.0.0.1>
            --node-id arg         ID of this node
            --see-stats           display stats
```

## Project Tasks
- Learn how to get cpu usage in Linux.
- Write a c++ program to get cpu usage/statistics and save the results in JSON.
- Parse the data.
- Send the data to MQTT broker.
- Repeat.

### Things Learned and Used
- Boost
- CLI
- Refactoring and good formatting
- include/header guarding
- Github actions
- Github branch rules


