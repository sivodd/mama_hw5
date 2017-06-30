#!/bin/bash
#######################################################################################################
## Function name: change_extensions.sh
## Function description: 
## Parameters:  $1 - folder name
##	       		$2 - current extension
##              $3 - new extension
## Return value: None.
#######################################################################################################
ls -1 "$1" > temp.log 
while read line
do
	mv "$1/$line" "$1/${line%%$2}$3"
done < temp.log