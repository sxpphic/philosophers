#!bin/bash

if [ $1 == 1 ]
then
	echo "test ./philo 1 800 200 200"
	echo "The philosopher should not eat and should die"
	sleep 1
	./philo 1 800 200 200
	echo "end test"
elif [ $1 -eq 2 ]
then
	echo "test ./philo 5 800 200 200"
	echo "No philosopher should die"
	sleep 1
	./philo 5 800 200 200
	echo "end test"
elif [ $1 -eq 3 ]
then
	echo "test ./philo 5 800 200 200 7"
	echo "No philosopher should die & end after 7 eats from each one"
	sleep 1
	./philo 5 800 200 200
	echo "end test"
elif [ $1 -eq 4 ]
then
	echo "test ./philo 4 410 200 200"
	echo "No philosopher should die"
	sleep 1
	./philo 4 410 200 200
	echo "end test"
elif [ $1 -eq 5 ]
then
	echo "test ./philo 4 310 200 200"
	echo "One philosopher should die"
	sleep 1
	./philo 4 410 200 200
	echo "end test"
fi
