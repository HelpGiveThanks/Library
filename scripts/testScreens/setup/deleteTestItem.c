testScreens: setup: deleteTestItem
#
#If there are no tests, then stop this script as there
#are no test to create things for.
If [ TEMP::ktest = "" ]
Show Custom Dialog [ Message: "There are no tests."; Buttons: “OK” ]
Exit Script [ ]
End If
If [ nodeLockTagMenus::orderOrLock ≠ "" ]
Show Custom Dialog [ Message: "This record is locked. Go the node that created it -- " & nodeLockTagMenus::tag & " -- in the setup tag window and enter the password to unlock it so that you can delete it."; Buttons: “OK” ]
Exit Script [ ]
End If
If [ Get (FoundCount) = 0 ]
Exit Script [ ]
End If
#
#Get variables needed for delete and delete messages.
Set Variable [ $delete; Value:tagMenus::_Ltag ]
Set Variable [ $group; Value:ruleTagMenuTestGroups::_Lgroup ]
Set Variable [ $groupName; Value:If ( Char ( ruleTagMenuTestGroups::name ) ≤ 20 ; ruleTagMenuTestGroups::name ; Left ( ruleTagMenuTestGroups::name ; 20 ) & "..." ) ]
Set Variable [ $testItemName; Value:If ( Char ( tagMenus::tag ) ≤ 20 ; tagMenus::tag ; Left ( tagMenus::tag ; 20 ) & "..." ) ]
#
#ﬁnd and show all test records that might be using
#this item.
New Window [ Height: 1; Width: 1; Top: 1; Left: 1 ]
Set Variable [ $$stopLoadTestRecord; Value:1 ]
Go to Layout [ “step4_InspectionFinding” (testlearn) ]
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ testlearn::ktest; $$item ]
Perform Find [ ]
#
#Check if test item is in use by any discovery records.
Loop
Set Variable [ $number; Value:1 ]
Loop
If [ FilterValues ( GetValue ( testlearn::kctestItem ; $number ) ; $delete & "¶" ) = $delete & ¶ ]
Set Variable [ $addToInUse; Value:$inUse ]
Set Variable [ $inUse; Value:1 + $addToInUse ]
Set Variable [ $number; Value:"exit" ]
End If
#
#If number was set to exit or if no keys exist, then
#exit loop.
Exit Loop If [ GetValue ( testlearn::kctestItem ; $number ) = "" ]
#
#If variable looked at did not match then raise the number
#to view the next variable.
Set Variable [ $add; Value:$number ]
Set Variable [ $number; Value:$add + 1 ]
End Loop
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
Set Variable [ $$stopLoadTestRecord ]
Close Window [ Current Window ]
#
#If in use the stop script.
If [ $inUse ≠ "" ]
Show Custom Dialog [ Message: If ( $inUse = 1 ; "Current test item use = " & $inUse & ". Uncheck this item in test module from the " & $inUse & " item using it and you will then be able to delete it." ; "Current test item use = " & $inUse & ". Uncheck this item in test module from the " & $inUse
& " items using it and you will then be able to delete it." ); Buttons: “OK” ]
Exit Script [ ]
End If
#
#Exit any ﬁelds and then contionally format ﬁeld
#to be deleted by this script.
Go to Field [ ]
Refresh Window
Show Custom Dialog [ Title: "!"; Message: "Delete " & $testItemName & "?"; Buttons: “Cancel”, “Delete” ]
Refresh Window
#
#If the user says yes, ﬁrst make sure the record
#is not the last record in its group. If it is and
#the system deleted the record without deleting
#the group too, this group would become
#an orphan as only groups that have records
#attached to them show up for the user to add
#more records to them. So the group
#record must also be deleted if this is the last
#test item under it.
If [ Get ( LastMessageChoice ) = 2 ]
New Window [ Name: "delete tag"; Height: 1; Width: 1; Top: 1; Left: 1 ]
Go to Layout [ “tableTag” (tagTable) ]
Enter Find Mode [ ]
Set Field [ tagTable::kGroupOrTest; $group ]
Perform Find [ ]
#
#If there are more records under this cateogry
#then the system deletes the current record without
#any more user input.
If [ Get (FoundCount) ≠ 1 ]
Close Window [ Name: "Delete Tag"; Current ﬁle ]
Delete Record/Request
[ No dialog ]
Set Variable [ $delete ]
Set Variable [ $group ]
Refresh Window
Exit Script [ ]
#
#BUT if only one record is found user is asked
#if they want to delete the category too.
Else If [ Get (FoundCount) = 1 ]
Select Window [ Name: "Tag Menus"; Current ﬁle ]
Set Variable [ $deleteGroup; Value:$group ]
Refresh Window
#
#The records are sorted by category to show
#the user which category is going to be deleted.
If [ TEMP::sortTestItem ≠ "cat" ]
Sort Records [ Speciﬁed Sort Order: ruleTagMenuGroups::order; based on value list: “order”
ruleTagMenuGroups::name; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
End If
#
#Show user warning message dependening on
#whether or not this group is part of other test's
#test-item lists.
January 7, 平成26 12:17:45 Imagination Quality Management.fp7 - deleteTestItem -1-testScreens: setup: deleteTestItem
If [ ValueCount ( ruleTagMenuTestGroups::match ) > 1 ]
Show Custom Dialog [ Title: "!"; Message: "Deleting " & $testItemName & " will also delete its group: " & $groupName & ", which is on " & ValueCount ( ruleTagMenuTestGroups::match ) - 1 & " other test-item list(s). Option 1: delete it from all lists. Option 2: cancel delete. UNLINK
this group from this list."; Buttons: “Cancel”, “Delete” ]
Else If [ ValueCount ( ruleTagMenuTestGroups::match ) = 1 ]
Show Custom Dialog [ Title: "!"; Message: "Deleting " & $testItemName & " will also delete its group ' " & $groupName & "' as it is the last item in this group."; Buttons: “Cancel”, “Delete” ]
End If
#
#If the user says yes, then delete both the tag and
#the category record.
If [ Get ( LastMessageChoice ) = 2 ]
Delete Record/Request
[ No dialog ]
Select Window [ Name: "delete tag"; Current ﬁle ]
Go to Layout [ “tableGroupTag” (groupTest) ]
Enter Find Mode [ ]
Set Field [ groupTest::_Lgroup; $group ]
Perform Find [ ]
Delete Record/Request
[ No dialog ]
Close Window [ Name: "Delete Tag"; Current ﬁle ]
End If
End If
End If
Set Variable [ $delete ]
Set Variable [ $deleteGroup ]
Refresh Window
January 7, 平成26 12:17:45 Imagination Quality Management.fp7 - deleteTestItem -2-
