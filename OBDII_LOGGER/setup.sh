#!/bin/bash
ip link set can1 type can bitrate 500000
ifconfig can1 up