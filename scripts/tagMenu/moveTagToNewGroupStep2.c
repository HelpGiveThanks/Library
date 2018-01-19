January 15, 2018 17:06:30 Library.fmp12 - moveTagToNewGroup -1-
tagMenu: moveTagToNewGroup
#
#Admin tasks.
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#
#A list of all layouts using this script and so
#requiring testing after changes is located here:
#https://github.com/HelpGiveThanks/Library/layouts/buttons/move_Layout_List_Scripts.md
#
#
#If user clicked on the group the tag is already
#in then exit this script.
If [ tagMenus::kGroupOrTest = $$groupOLD ]
Go to Field [ ]
Exit Script [ ]
End If
#
#
#BEGIN check if tag can be moved.
#
#If there is only one group, exit script.
If [ //Test for keyword and node tag layouts.
ValueCount ( ValueListItems ( Get ( FileName ) ; "tagGroup" ) ) = 1
and ( $$citationMatch = "key" or $$citationMatch = "node" ) = 1
or
//Test for copyright, publication, and publisher tag layouts.
ValueCount ( ValueListItems ( Get ( FileName ) ; "tagGroupNoSectionTagsLikePath" ) ) = 1 ]
Set Field [ tagMenus::kGroupOrTest; $$groupOLD ]
Go to Field [ ]
Exit Script [ ]
End If
#
#Check field contents for changes to keys
#made by user typing or dragging text into
#key field. If altered, put back actual key
#(group's ID#) and exit.
If [ FilterValues ( ValueListItems ( Get ( FileName ) ; "tagGroup" ) ; tagMenus::kGroupOrTest & ¶ ) ≠ tagMenus::kGroupOrTest & ¶ ]
Set Field [ tagMenus::kGroupOrTest; $$groupOLD ]
Go to Field [ ]
Exit Script [ ]
End If
#
#Get the newly selected tag group's ID number,
#and then replace it with the tag's old group ID
#until the script can determine if this tag can
#indeed be moved, which will be determined
#next.
Set Variable [ $newGroup; Value:tagMenus::kGroupOrTest ]
Set Field [ tagMenus::kGroupOrTest; $$groupOLD ]
Go to Field [ ]
#
#If the test item's tag-group creator node is
#currenlty locked then stop script, inform user.
If [ nodeLockTestTagItemGroup::orderOrLock ≠ "" and Get(LayoutName) = "setupTestItem" ]
Show Custom Dialog [ Message: "This group is locked. To move any of its items, go the node that created it — " &
nodeLockTestTagItemGroup::tag & " — in the setup tag window, click 'lock' and enter the password."; Default Button: “OK”,
Commit: “Yes” ]
Exit Script [ ]
#
#If a regular tag's creator node is currenlty
#locked then stop script, inform user.
Else If [ tagCreatorLock::orderOrLock ≠ "" ]
Show Custom Dialog [ Message: "This tag is locked. To move any of its items, go the node that created it — " &
tagCreatorLock::tag & " — in the setup tag window, click 'lock' and enter the password."; Default Button: “OK”, Commit:
“Yes” ]
Exit Script [ ]
#
#If the tag's creator node is unlocked, then
#replace the old tag-group key with the newly
#selected one, so the tag will move into it new
#tag group.
Else
Set Field [ tagMenus::kGroupOrTest; $newGroup ]
End If
#
#If this is a system admin locked record, exit script.
If [ tagMenus::orderOrLock = "lock" ]
Set Field [ tagMenus::kGroupOrTest; $$groupOLD ]
Go to Field [ ]
Show Custom Dialog [ Message: "This copyright is locked by the system admin, and cannot be moved."; Default Button: “OK”,
Commit: “Yes” ]
Exit Script [ ]
End If
#
#END check if tag can be moved.
#
#
#Stop test record load script to speed up script.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
#
#Get the newly selected group's ID number.
Set Variable [ $newGroup; Value:tagMenus::kGroupOrTest ]
Set Variable [ $$moveItem; Value:tagMenus::_Ltag ]
Refresh Window
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
// New Window [ Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
New Window [ Height: 1; Width: 1; Top: -10000; Left: -10000; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom
Control Area: “Yes”; Resize: “Yes” ]
Go to Layout [ “tableTag” (tagTable) ]
Enter Find Mode [ ]
Set Field [ tagTable::kGroupOrTest; $$groupOLD ]
Perform Find [ ]
If [ Get (FoundCount) = 1 ]
Close Window [ Current Window ]
Set Variable [ $group; Value:$$groupOLD ]
Set Variable [ $deleteGroup; Value:$$groupOLD ]
Refresh Window
#
#If it is the last item inform user that after the move
#the old group will be deleted unless the user
#creates a new item for this group before moving
#the old item.
Show Custom Dialog [ Message: "After — " & tagMenus::tag & " — is moved its old group will be deleted. If you want to keep the
old group, create a new tag under it before performing this move."; Default Button: “Cancel”, Commit: “Yes”; Button 2: “move”,
Commit: “No” ]
If [ Get ( LastMessageChoice ) = 1 ]
Set Variable [ $newGroup ]
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
New Window [ Height: 1; Width: 1; Top: -10000; Left: -10000; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”;
Zoom Control Area: “Yes”; Resize: “Yes” ]
#
Go to Layout [ “tableTagGroup” (testSubsectionGroup) ]
Enter Find Mode [ ]
Set Field [ testSubsectionGroup::_Lgroup; $$groupOLD ]
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
Set Variable [ $$groupOLD; Value:$newGroup ]
Set Variable [ $$moveItem ]
Set Variable [ $group ]
Refresh Window
Go to Field [ ]
#
#Scroll to selected record.
Scroll Window
[ Home ]
If [ $$citationMatch = "testItem" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenuTestItemGroup::orderOrLibraryType; based on value
list: “order Pulldown List”
tagMenuTestItemGroup::name; ascending
tagMenuTestItemGroup::_Lgroup; ascending
tagMenus::orderOrLock; based on value list: “order Pulldown List”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Else
Sort Records [ ]
[ No dialog ]
End If
#
#Turn back on the loadrecord script. The current
#record's info does not need to be reloaded of course
#because it is still the current record.
Set Variable [ $$stopLoadTagRecord ]
#
Halt Script
#
