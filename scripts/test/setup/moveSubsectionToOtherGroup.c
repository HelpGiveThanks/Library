January 12, 2018 14:17:30 Library.fmp12 - moveSubsectionToOtherGroup -1-
test: setup: moveSubsectionToOtherGroup
#
#This script is for moving a test subsection
#to a different group.
#
#
#Admin tasks.
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#If there is only one group, exit script.
If [ ValueCount ( ValueListItems ( Get ( FileName ) ; "templateSubsectionGroups" ) ) = 1 ]
Go to Field [ ]
Exit Script [ ]
End If
#
#If node is currenlty locked then stop script, inform user.
If [ testSectionCreatorLock::orderOrLock ≠ "" ]
Set Field [ testSubsectionTemplate::ksubsectionGroup; $$subsectionGroupOLD ]
Go to Field [ ]
Show Custom Dialog [ Message: "This record is locked. Go the node that created it -- " & testSectionCreatorLock::tag & " -- in
the setup tag window and enter the password to unlock it so that you can move it."; Default Button: “OK”, Commit: “No” ]
Exit Script [ ]
End If
#
Set Variable [ $$moveItem; Value:testSubsectionTemplate::_LtestSubsection ]
Refresh Window
#
#Stop test record load script to speed up script.
Set Variable [ $$ID; Value:"ignore" ]
Set Variable [ $$stopTest; Value:1 ]
#
#Get the newly selected group's ID number.
Set Variable [ $newSubSectionGroup; Value:testSubsectionTemplate::ksubsectionGroup ]
#
#Reset the test's group ID with its old group ID
#number grabbed by the system in part 1 of
#this script, just in case the user decides to cancel
#move and the test needs to stay put.
Set Field [ testSubsectionTemplate::ksubsectionGroup; $$subsectionGroupOLD ]
Go to Field [ ]
#
#Check if this is the last test in the test group.
New Window [ Height: 1; Width: 1; Top: -10000; Left: -10000; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom
Control Area: “Yes”; Resize: “Yes” ]
Go to Layout [ “tableTestSubsectionTemplates” (testSubsectionTemplate) ]
Enter Find Mode [ ]
Set Field [ testSubsectionTemplate::ksubsectionGroup; $$subsectionGroupOLD ]
Perform Find [ ]
If [ Get (FoundCount) = 1 ]
Close Window [ Current Window ]
Set Variable [ $deleteGroup; Value:TEMP::ktestSubsection ]
Refresh Window
#
#If it is the last item inform user that after the move
#the old group will be deleted unless the user
#creates a new item for this group before moving
#the old item.
Show Custom Dialog [ Title: "!"; Message: "The group — " & testSubsectionGroup::name & " — will be deleted if you complete
this move. If you want to keep it: 1) click cancel, 2) create a new general inquiry for this group, then 3) perform the move.";
Default Button: “Cancel”, Commit: “Yes”; Button 2: “move”, Commit: “No” ]
If [ Get ( LastMessageChoice ) = 1 ]
Set Variable [ $$stopTest ]
Set Variable [ $$moveItem ]
Set Variable [ $deleteGroup ]
Set Variable [ $$ID; Value:testSubsectionTemplate::_LtestSubsection ]
Refresh Window
Go to Field [ ]
Exit Script [ ]
End If
#
#If the user decides to go ahead with the move,
#first delete the old group.
New Window [ Height: 1; Width: 1; Top: -10000; Left: -10000; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”;
Zoom Control Area: “Yes”; Resize: “Yes” ]
#
Go to Layout [ “tableTagGroup” (testSubsectionGroup) ]
Enter Find Mode [ ]
Set Field [ testSubsectionGroup::_Lgroup; $$subsectionGroupOLD ]
Perform Find [ ]
Delete Record/Request
[ No dialog ]
#
End If
#
#Close window opened to perform find, and then
#set group ID of test with the new groups ID number.
Close Window [ Current Window ]
Set Field [ testSubsectionTemplate::ksubsectionGroup; $newSubSectionGroup ]
Set Variable [ $$subsectionGroupOLD; Value:testSubsectionTemplate::ksubsectionGroup ]
Go to Field [ ]
#
#Section window on selected record.
Scroll Window
[ Home ]
Sort Records [ Keep records in sorted order; Specified Sort Order: testSubsectionGroup::orderOrLibraryType; based on value list:
“order Pulldown List”
testSubsectionGroup::name; ascending
testSubsectionTemplate::order; based on value list: “order Pulldown List”
testSubsectionTemplate::name; ascending ]
[ Restore; No dialog ]
#
#Turn back on the loadrecord script. The current
#record's info does not need to be reloaded of course
#because it is still the current record.
Set Variable [ $$stopTest ]
Set Variable [ $$ID; Value:testSubsectionTemplate::_LtestSubsection ]
Go to Field [ ]
#
#Turn off the move highlight.
Set Variable [ $$moveItem ]
Refresh Window
#
