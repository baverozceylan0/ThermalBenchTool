#!/bin/bash

echo p > state_sqrt_task.txt

taskset -c 4 ./sqrt_task $(($1*2)) 100 &
taskset -c 5 ./sqrt_task $(($1*2)) 100 &
taskset -c 6 ./sqrt_task $(($1*2)) 100 &
#taskset -c 7 ./sqrt_task $(($1*2)) 100 &

pid_set=$(pidof sqrt_task)

for _pid in $pid_set; do
    kill -SIGSTOP $_pid
done 

duration=$(($1*1000))


sleep 5

start_time=$(date +%s%3N)
curr_time=0
echo r > state_sqrt_task.txt
while [ $curr_time -le $duration ]
do 
    for _pid in $pid_set; do
        kill -SIGCONT $_pid
    done 
    sleep 0.06
    for _pid in $pid_set; do
        kill -SIGSTOP $_pid
    done
    sleep 0.01
    
    curr_time=$(($(date +%s%3N) - $start_time))
done

for _pid in $pid_set; do
        kill $_pid
    done


