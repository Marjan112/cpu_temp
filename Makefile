cpu_temp: cpu_temp.c
	gcc -o cpu_temp cpu_temp.c

install: cpu_temp
	mv cpu_temp ~/.config/i3blocks/cpu
