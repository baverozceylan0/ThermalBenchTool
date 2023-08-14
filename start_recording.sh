#!/bin/bash

echo Starting...

taskset -a -c 0-3 ./util_record &
taskset -a -c 0-3 ./temperature_record &
taskset -a -c 0-3 ./freq_record &

sleep 1

list_caja=$(pidof caja)
for p in $list
do
    taskset -a -cp 0-3 $p
done
sleep $1



echo k >> state_temperature_record.txt
echo k >> state_util_record.txt
echo k >> state_freq_record.txt
#python3 plot_util_file.py &

#python3 plot_temperature_file.py &
