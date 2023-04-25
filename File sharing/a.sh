#!/bin/bash

#process a to lock the file and substract 20 from its value

flock --verbose Update.dat ./update.sh '-20'
