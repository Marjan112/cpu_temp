# cpu_temp

Simple program that searches through /sys/class/hwmon for Tctl sensor and then saving that temperature to ~/.cpu_temp. This program is for my personal use, but it can be used by anyone else if they need it. I created it because I wanted to have the cpu temperature somewhere in one place to be able to access it whenever I want. For example in i3status config file, i can just set the cpu_temperature path that doesnt change and i can plug-in some devices with temperature sensors and my cpu temperature path is not gonna get messed up.

# Quick start
You'll need C++23 for this.
```sh
$ make
```
