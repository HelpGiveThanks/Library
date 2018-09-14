September 13, 2018 14:05:25 Library.fmp12 - restartDatabase -1-
startclose: restartDatabase
#
#This script is necessary to
#halt any scripts that may be running (paused).
#
#By placing the halt command in this script
#instead of the end of the start script, the All
#Apps window script, that is used to open
#libraries, will be able to finish and close its
#window, instead of being halted from doing so
#by this library's start script when it is opened
#from another apps All Apps window.
Perform Script [ “startDatabase (update)” ]
#
#Halt any scripts that may be running after
#the user elects to restart the library.
Halt Script
#
