#!/usr/bin/python3

import psutil
import time
import logging

logging.basicConfig(filename="cpu_temp.log", level=logging.DEBUG, format="[%(asctime)s - %(levelname)s] %(message)s")

def find_tctl_temp():
    temps = psutil.sensors_temperatures()
    k10temp = temps["k10temp"]

    for temp in k10temp:
        if temp.label == "Tctl":
            return int(temp.current * 1000)

    return None

def write_temp_to_file(tctl_temp, path):
    try:
        with open(path, "w") as f:
            f.write(f"{tctl_temp}")
    except Exception as e:
        logging.error(f"Couldnt write to {path}: {e}")

while True:
    tctl_temp = find_tctl_temp()
    if tctl_temp is None:
        logging.error("Couldnt find cpu temp")
        exit(1)

    write_temp_to_file(tctl_temp, "/run/cpu_temp")
    time.sleep(1)
