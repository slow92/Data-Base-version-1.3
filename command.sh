#!/bin/bash
git init
git add main.cpp
git add include
git add src
git add command.sh
git commit -m "firs version data base"
git remote add origin https://github.com/slow92/Data-Base-version-1.3.git
git push origin master -f