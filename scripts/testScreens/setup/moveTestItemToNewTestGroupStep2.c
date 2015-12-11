testScreens: setup: moveTestItemToNewTestGroupStep2
#
#This script is for moving a general inquiry to different group.
#
#WHEN TIME PERMITS the vocabuary for scripts,
#variable, fields, layouts, etc. needs to be updated
#to reflect that a 'test' is now a 'general inquiry'
#and an 'item' is now a 'specific inquiry' and a 'focus'
#is now a test 'section', etc. A complete look at
#the DDR to insure all vocabulary is updated
#everywhere followed by testing for each
#update is required.
#
#
#Stop test record load script to speed up script.
Set Variable [ $$ID; Value:"ignore" ]
#
#Get the newly selected group's ID number.
Set Variable [ $newGroup; Value:test::ktestGroup ]
#
#Reset the test's group ID with its old group ID
#number grabbed by the system in part 1 of
#this script, just in case the user decides to cancel
#move and the test needs to stay put.
Set Field [ test::ktestGroup; $$groupOLD ]
Go to Field [ ]
#
#Check if this is the last test in the test group.
New Window [ Height: 1; Width: 1; Top: -10000; Left: -10000 ]
Go to Layout [ “tableTest” (test) ]
Enter Find Mode [ ]
Set Field [ test::ktestGroup; $$groupOLD ]
Perform Find [ ]
If [ Get (FoundCount) = 1 ]
Close Window [ Current Window ]
Set Variable [ $deleteGroup; Value:TEMP::ktest ]
Refresh Window
#
#If it is the last item inform user that after the move
#the old group will be deleted unless the user
#creates a new item for this group before moving
#the old item.
Show Custom Dialog [ Title: "!"; Message: "The group — " & groupTest::name & " — will be deleted if you complete this move. If you want to keep it: 1) click cancel, 2) create a new general inquiry for this group, then 3) perform the move."; Buttons: “Cancel”, “move” ]
If [ Get ( LastMessageChoice ) = 1 ]
Set Variable [ $deleteGroup ]
Set Variable [ $$groupOLD ]
Refresh Window
Go to Field [ ]
Exit Script [ ]
End If
#
#If the user decides to go ahead with the move,
#first delete the old group.
New Window [ Height: 1; Width: 1; Top: -10000; Left: -10000 ]
#
Go to Layout [ “tableGroupTag” (groupTest) ]
Enter Find Mode [ ]
Set Field [ groupTest::_Lgroup; $$groupOLD ]
Perform Find [ ]
Delete Record/Request
[ No dialog ]
#
End If
#
#Close window opened to perform find, and then
#set group ID of test with the new groups ID number.
Close Window [ Current Window ]
Set Field [ test::ktestGroup; $newGroup ]
Set Variable [ $$groupOLD ]
Go to Field [ ]
#
#Turn back on the loadrecord script. The current
#record's info does not need to be reloaded of course
#because it is still the current record.
Set Variable [ $$ID; Value:test::_Ltest ]
#
December 9, ଘ౮27 20:00:53 Library.fp7 - moveTestItemToNewTestGroupStep2 -1-
