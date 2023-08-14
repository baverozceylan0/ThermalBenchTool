#!/bin/bash

echo p > basicmath/state_sqrt_task.txt

taskset -c 4 ./basicmath/basicmath_app $1 100 &
taskset -c 5 ./basicmath/basicmath_app $1 100 &
taskset -c 6 ./basicmath/basicmath_app $1 100 &


echo r > basicmath/state_sqrt_task.txt


