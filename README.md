# cpu_temp

Simple program that searches through /sys/class/hwmon for Tctl sensor and then saving that temperature to ~/.cpu_temp. I created this because i3status doesnt know which temperature is my cpu temperature so it just ends up picking the first one, that's why i created this program that searches for tctl sensor path and copies the value to ~/.cpu_temp. That way i can just do this:

```
...
cpu_temperature 0 {
    # instead of just manually searching for the tctl temperature file and pasting it's path in the `path` variable i can just do this
    path = "~/.cpu_temp"
}
...
```

and now i3status is always gonna know my cpu temperature.

I dont know if this is a stupid way of doing things and that there's other way of doing this, but if there is an other way then please let me know by creating an issue (I doubt anybody is gonna read this lolollolol).

# Quick start
You'll need C++23 for this.
```sh
$ make
```

Now you can create a user daemon that starts this up or you can make it run whenever you login or smth.
