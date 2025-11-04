#!/usr/bin/python3

import psutil
import os
import time

def find_tctl_temp():
    temps = psutil.sensors_temperatures()
    k10temp = temps["k10temp"]

    for temp in k10temp:
        if temp.label == "Tctl":
            return int(temp.current * 1000)

    return None

def write_temp_to_file(tctl_temp, path):
    file = open(path, "w")
    file.write(f"{tctl_temp}")
    file.close()

home = os.environ["HOME"]

while True:
    tctl_temp = find_tctl_temp()
    if tctl_temp is None:
        exit(1)

    write_temp_to_file(tctl_temp, f"{home}/.cpu_temp")
    time.sleep(1)
