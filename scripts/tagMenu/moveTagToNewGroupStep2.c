tagMenu: moveTagToNewGroupStep2
#
Allow User Abort [ Off ]
Set Error Capture [ On ]
// If [ ValueCount ( ruleTagMenuGroups::ksection ) > 1 ]
// Exit Script [ ]
// End If
#
#
If [ tagMenus::kGroupOrTest = "" ]
Set Field [ tagMenus::kGroupOrTest; $$groupOLD ]
Go to Field [ ]
Exit Script [ ]
End If
#
#Check field contents against valid keys, and  
#if invalid then put back old key and exit.
If [ FilterValues ( ValueListItems ( Get ( FileName ) ; "tagGroup" ) ; tagMenus::kGroupOrTest & ¶ ) ≠ tagMenus::kGroupOrTest & ¶ ]
Set Field [ tagMenus::kGroupOrTest; $$groupOLD ]
Go to Field [ ]
Exit Script [ ]
End If
#
#
#
#Stop test record load script to speed up script.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
#
#Get the newly selected group's ID number.
Set Variable [ $newGroup; Value:tagMenus::kGroupOrTest ]
Set Variable [ $$moveItem; Value:tagMenus::_Ltag ]
Refresh Window
Sort Records [ ]
[ No dialog ]
#
If [ ValueCount ( ruleTagMenuGroups::ksection ) > 1 ]
#
#If group user is moving tag onto is in more than
#one section of the database, then warn user that
#if the go ahead with the move, they will be unable
#to reverse their decision after moving.
Go to Field [ ]
Show Custom Dialog [ Title: "!"; Message: "WARNING: Once the " & tagMenus::tag & " move is finished it cannot be undone.
The group it is being moved to is in more than one section of this database. Tags cannot be moved out of these types of
groups. So are you really sure about this move?"; Buttons: “undo move”, “I am sure!” ]
If [ Get ( LastMessageChoice ) = 1 ]
#
#Reset the tag's group ID with its old group ID
#number grabbed by the system in part 1 of
#this script.
Set Field [ tagMenus::kGroupOrTest; $$groupOLD ]
Set Variable [ $$moveItem ]
Set Variable [ $$groupOLD ]
Refresh Window
Go to Field [ ]
#
#Turn back on the loadrecord script. The current
#record's info does not need to be reloaded of course
#because it is still the current record.
Set Variable [ $$stopLoadTagRecord ]
Halt Script
End If
End If
#
#Reset the tag's group ID with its old group ID
#number grabbed by the system in part 1 of
#this script, just in case the user decides to cancel
#move and the test needs to stay put.
Set Field [ tagMenus::kGroupOrTest; $$groupOLD ]
Sort Records [ ]
[ No dialog ]
Go to Field [ ]
#
#Check if this is the last test in the test group.
New Window [ ]
Go to Layout [ “tableTag” (tagTable) ]
Enter Find Mode [ ]
Set Field [ tagTable::kGroupOrTest; $$groupOLD ]
Perform Find [ ]
If [ Get (FoundCount) = 1 ]
Close Window [ Current Window ]
Set Variable [ $group; Value:$$groupOLD ]
Refresh Window
#
#If it is the last item inform user that after the move
#the old group will be deleted unless the user
#creates a new item for this group before moving
#the old item.
Show Custom Dialog [ Title: "!"; Message: "After " & tagMenus::tag & " is moved its old group will be deleted. If you want to keep
this group then create a new tag for the old group before the last tag out of it."; Buttons: “Cancel”, “move” ]
If [ Get ( LastMessageChoice ) = 1 ]
Set Variable [ $newGroup ]
Set Variable [ $$groupOLD ]
Set Variable [ $$moveItem ]
Refresh Window
#
#Turn back on the loadrecord script. The current
#record's info does not need to be reloaded of course
#because it is still the current record.
Set Variable [ $$stopLoadTagRecord ]
Halt Script
End If
#
#If the user decides to go ahead with the move,
#first delete the old group.
New Window [ ]
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
Set Field [ tagMenus::kGroupOrTest; $newGroup ]
Set Variable [ $$groupOLD ]
Set Variable [ $$moveItem ]
Set Variable [ $category ]
Refresh Window
Go to Field [ ]
#
#Turn back on the loadrecord script. The current
#record's info does not need to be reloaded of course
#because it is still the current record.
Set Variable [ $$stopLoadTagRecord ]
#
Halt Script
#
December 31, ଘ౮27 14:16:11 Library.fp7 - moveTagToNewGroupStep2 -1-
