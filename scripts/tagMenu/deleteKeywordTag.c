January 20, 2018 17:55:45 Library.fmp12 - deleteKeywordTag -1-
tagMenu: deleteKeywordTag
#
#
#If user is looking at Node switch to that script.
If [ $$citationMatch = "node" ]
Perform Script [ “deleteNodeTag” ]
Exit Script [ ]
End If
#
#If record is locked, explain to user how to
#unlock and delete it.
If [ tagMenus::orderOrLock[2] ≠ "" ]
Show Custom Dialog [ Message: "This node is locked. Click the lock button above, and enter its password to unlock it."; Default
Button: “OK”, Commit: “No” ]
Halt Script
Else If [ tagCreatorLock::orderOrLock ≠ "" ]
If [ tagMenus::orderOrLock[2] = "" ]
Show Custom Dialog [ Message: "This record is locked. Go the node that created it — " & tagCreatorLock::tag & " — in the
setup tag window and enter the password to unlock it."; Default Button: “OK”, Commit: “No” ]
Else
Show Custom Dialog [ Message: "This node is locked. Click the lock button above, and enter its password to unlock it.";
Default Button: “OK”, Commit: “No” ]
End If
Halt Script
End If
#
#
#If node is currenlty locked then stop script,
#and inform the user.
If [ tempSetup::kdefaultNodePrimary ≠ "self" ]
Perform Script [ “stopLockedNodesRecordsBeingDeleted” ]
End If
#
#Exit field so user can see red delete
#formatting later on.
Go to Field [ ]
#
#Prevent all record load scripts (they slow down
#this script and are uneccessary).
Set Variable [ $$stoploadCitation; Value:1 ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
#
#Set variables to conditionally format selection to
#be deleted, and its record number so if the
#user cancels the delete, the system can return
#to this record.
Set Variable [ $delete; Value:tagMenus::_Ltag ]
Set Variable [ $deleteName; Value:tagMenus::tag ]
Set Variable [ $recordNumber; Value:Get (RecordNumber) ]
Set Variable [ $$addTagToCitation; Value:1 ]
Set Variable [ $group; Value:tagMenus::kGroupOrTest ]
#
#The check variable duplicates the $delete
#variable, and when there is time I'll remove it.
Set Variable [ $check; Value:tagMenus::_Ltag ]
#
#Because there may be no records found, stop
#the system from informing the user of this.
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#Open a new window and look for tag in both
#primary and other keyword fields.
New Window [ Height: 1; Width: 1; Top: -10000; Left: -10000; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom
Control Area: “Yes”; Resize: “Yes” ]
#
#See if keyword is used by any learn records.
#Look in main kprimary...
Go to Layout [ “tableTestLearn” (testlearn) ]
Enter Find Mode [ ]
Set Field [ testlearn::kKeywordPrimary; $check ]
Set Field [ testlearn::filterFind; "main" & ¶ ]
Perform Find [ ]
#
#Look in main kother...
Enter Find Mode [ ]
Set Field [ testlearn::kcKeywordOther; $check & ¶ ]
Set Field [ testlearn::filterFind; "main" & ¶ ]
Extend Found Set [ ]
If [ Get (FoundCount) ≠ 0 ]
Set Variable [ $inUse; Value:Get (FoundCount) & " learn" ]
End If
#
#See if keyword is used by any discovery records.
#Check in discovery primary...
Enter Find Mode [ ]
Set Field [ testlearn::kKeywordPrimary; $check ]
Set Field [ testlearn::ktestSubsection; "*" ]
Perform Find [ ]
#
#Check in other...
Enter Find Mode [ ]
Set Field [ testlearn::kcKeywordOther; $check ]
Set Field [ testlearn::ktestSubsection; "*" ]
Extend Found Set [ ]
#
#See if keyword is used by any reference records.
#Check in primary...
Go to Layout [ “Reference” (reference) ]
Enter Find Mode [ ]
Set Field [ reference::kkeywordPrimary; $check ]
Perform Find [ ]
#
#Check in other...
Enter Find Mode [ ]
Set Field [ reference::kkeywordOther; $check ]
Extend Found Set [ ]
If [ Get (FoundCount) ≠ 0 ]
If [ $inUse ≠ "" ]
Set Variable [ $addToInUse; Value:$inUse ]
Set Variable [ $inUse; Value:$addToInUse & ", " & Get (FoundCount) & " reference" ]
Else If [ $inUse = "" ]
Set Variable [ $inUse; Value:Get (FoundCount) & " reference" ]
End If
End If
#
#Close window used to find records using tag.
Close Window [ Current Window ]
#
#If the keyword being deleted was not found in
#use in make sure the user really wants
#it deleted.
If [ $inUse = "" ]
#
#If the keyword being deleted was not found in
#use in any sections of the database then before
#deleting it make sure the user really wants it deleted.
Set Variable [ $group ]
Refresh Window
Show Custom Dialog [ Message: "Delete current keyword?"; Default Button: “cancel”, Commit: “No”; Button 2: “delete”, Commit:
“No” ]
Set Variable [ $group; Value:tagMenus::kGroupOrTest ]
Set Variable [ $deleteGroup; Value:tagMenuGroup::name ]
#
#If the user cancels, stop the delete.
If [ Get ( LastMessageChoice ) = 1 ]
Go to Field [ ]
Set Variable [ $delete ]
Set Variable [ $group ]
Refresh Window
Refresh Window
Set Variable [ $$addTagToCitation ]
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
Exit Script [ ]
#
#If the user says yes, first make sure the record
#is not the last record in a group. If it is and
#the system deleted the record without deleting
#the group too, this group would become
#an orphan as only categories that have records
#attached to them show up for the user to add
#more records uner them. So the group
#record must also be deleted if this is the last
#record under it.
Else If [ Get ( LastMessageChoice ) = 2 ]
New Window [ Name: "delete tag"; Height: 1; Width: 1; Top: -10000; Left: -10000; Style: Document; Close: “Yes”; Minimize:
“Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
Go to Layout [ “tableTag” (tagTable) ]
Enter Find Mode [ ]
Set Field [ tagTable::kGroupOrTest; $group ]
Perform Find [ ]
#
#If there are more records under this cateogry
#then the system deletes the current record without
#any more user input.
If [ Get (FoundCount) ≠ 1 ]
Close Window [ Name: "Delete Tag"; Current file ]
Delete Record/Request
[ No dialog ]
Set Variable [ $delete ]
Set Variable [ $group ]
Refresh Window
Set Variable [ $$addTagToCitation ]
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
Exit Script [ ]
#
#BUT if only one record is found user is asked
#if they want to delete the group too.
Else If [ Get (FoundCount) = 1 ]
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
#
#The records are sorted by group to show
#the user which group is going to be deleted.
If [ TEMP::sortKey ≠ "cat" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenuGroup::orderOrLibraryType; based on
value list: “order Pulldown List”
tagMenuGroup::name; ascending
tagMenus::orderOrLock; based on value list: “order Pulldown List”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
End If
Show Custom Dialog [ Message: "Deleting " & $deleteName & " will also delete its group — " & $deleteGroup & " — as
it is the last tag in this group."; Default Button: “Cancel”, Commit: “Yes”; Button 2: “Delete”, Commit: “No” ]
#
#If the user says yes, then delete both the tag and
#the group record.
If [ Get ( LastMessageChoice ) = 2 ]
#
#Delete tag.
Delete Record/Request
[ No dialog ]
#
#Delete group.
Select Window [ Name: "delete tag"; Current file ]
Go to Layout [ “tableTagGroup” (testSubsectionGroup) ]
Enter Find Mode [ ]
Set Field [ testSubsectionGroup::_Lgroup; $group ]
Perform Find [ ]
Delete Record/Request
[ No dialog ]
End If
End If
End If
Close Window [ Name: "Delete Tag"; Current file ]
Set Variable [ $delete ]
Set Variable [ $group ]
Refresh Window
Set Variable [ $$addTagToCitation ]
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
#
#Load keys for tag focus is now on.
Perform Script [ “loadTagRecord” ]
End If
#
#If the keyword is found in use then tell user
#where and that it cannot be deleted.
If [ $inUse ≠ "" ]
Set Variable [ $delete ]
Set Variable [ $group ]
Refresh Window
Show Custom Dialog [ Message: "This keyword cannot be deleted as it in use x number of times in the following modules' main
windows: " & $inUse & "."; Default Button: “OK”, Commit: “Yes” ]
Set Variable [ $$addTagToCitation ]
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
End If
#
