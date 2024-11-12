#!/bin/bash

sleep 1

ifconfig eth1 192.168.0.2 netmask 255.255.255.0 up
ip link set can1 type can bitrate 500000
ip link set can1 up
ip link set can0 type can bitrate 1000000 dbitrate 2000000 fd on
ip link set can0 up

# ./v2x-server -i 192.168.0.1 -p 50000 -f 0 -c 1 -s 1 -c 0 &

