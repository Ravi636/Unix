#!/usr/bin/bash

#Path of home directory
echo $HOME

#Creating directory sturcture
mkdir $HOME/ece282
mkdir $HOME/ece282/labs/lab01
mkdir $HOME/ece282/labs/lab02
mkdir $HOME/ece282/labs/lab03
mkdir $HOME/ece282/labs/lab04
mkdir $HOME/ece282/labs/lab05
mkdir $HOME/ece282/labs/lab06
mkdir $HOME/ece282/labs/lab07
mkdir $HOME/ece282/labs/lab08
mkdir $HOME/ece282/labs/lab09
mkdir $HOME/ece282/labs/lab10

#Going to home directory
cd
#Path of current directory
pwd
#Contests of current directory
ls -al

#Username
echo $USER

#Shell type of user
echo $SHELL

#Name of the computer
echo $HOST

#Interacting with user
ASK_NAME = "What is your name"
echo $ASK_NAME
read NAME
echo "Hi $NAME!"



#Basic if statement
echo "Pick a number between 1 - 10."
read ans
if [ ans -eq 3 ]
then
	echo You are right.
else
	echo You picked the incorrect number 
fi

date

