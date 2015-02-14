tagMenu: deleteMHOCSPtags
#
If [ nodeLockTagMenus::orderOrLock ≠ "" and tagMenus::match = "sample" or
nodeLockTagMenus::orderOrLock ≠ "" and tagMenus::match = "health" or
nodeLockTagMenus::orderOrLock ≠ "" and tagMenus::match = "test" ]
Show Custom Dialog [ Message: "This record is currently locked. Select the node that created it and enter the password to unlock it, then you will able to start the delete process."; Buttons: “OK” ]
Exit Script [ ]
Else If [ tagMenus::orderOrLock ≠ "" and tagMenus::match = "health" ]
Show Custom Dialog [ Message: "This record is locked by the system."; Buttons: “OK” ]
Exit Script [ ]
End If
#
#If the copyright being checked for deletion is in use
#as a default copyright then stop the script and inform
#the user of this fact.
If [ FilterValues ( TEMP::kdefaultHealth ; tagMenus::_Ltag & "¶" ) ]
Show Custom Dialog [ Message: "This copyright is currently selected as the default and cannot be deleted."; Buttons: “OK” ]
Exit Script [ ]
End If
#
#Exit field so user can see red delete
#formatting later on.
Go to Field [ ]
#
#Prevent all record load scripts (they slow down
#this script and are uneccessary).
Set Variable [ $$stoploadCitation; Value:1 ]
#
#Get all variables needed to preform script.
Set Variable [ $tag; Value:tagMenus::_Ltag ]
Set Variable [ $name; Value:tagMenus::tag ]
#
#Open a new window and look for tag in both
#primary and other keyword fields.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
New Window [ Name: "Delete Tag" ]
#
#Find tagged Reference records.
Go to Layout [ “Reference” (reference) ]
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
#
#
If [ $$citationMatch = "medium" ]
Set Field [ reference::kmedium; $tag ]
Else If [ $$citationMatch = "path" ]
Set Field [ reference::kfolderpath; $tag ]
Else If [ $$citationMatch = "copyist" ]
Set Field [ reference::kcopyist; $tag ]
Else If [ $$citationMatch = "organ" ]
Set Field [ reference::korgan; $tag ]
Else If [ $$citationMatch = "health" ]
Set Field [ reference::kHealth; $tag ]
End If
#
#
Perform Find [ ]
Set Variable [ $refLastError; Value:Get (LastError) ]
#
#
#Find tagged TestLearn records.
Go to Layout [ “learn1” (testlearn) ]
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
#
#
If [ $$citationMatch = "medium" ]
Set Field [ testlearn::kmedium; $tag ]
Else If [ $$citationMatch = "path" ]
Set Field [ testlearn::kfolderPath; $tag ]
Else If [ $$citationMatch = "sample" ]
Set Field [ testlearn::kcsample; "*" & $tag & ¶ ]
Else If [ $$citationMatch = "health" ]
Set Field [ testlearn::kHealth; $tag ]
End If
#
#
Perform Find [ ]
Set Variable [ $TLLastError; Value:Get (LastError) ]
Set Variable [ $$stopLoadTagRecord ]
#
#If records are found using this tag tell user
#that it must be removed from all records
#before it can be deleted.
// If [ $TLLastError ≠ 401 and $refLastError ≠ 401 or
$TLLastError ≠ 401 and $TLLastError ≠ 400 and $refLastError ≠ 401 ]
If [ $TLLastError ≠ 401 and $TLLastError ≠ 400 or $refLastError ≠ 401 ]
Close Window [ Name: "Delete Tag"; Current file ]
If [ $refLastError ≠ 401 and $TLLastError ≠ 401 ]
Show Custom Dialog [ Message: "In use by Reference and Test Learn records. Must be removed before deleting. Click the 'find' button and then the square button next to '" & Left ( $name ; 20 ) & If ( Length ( $name ) > 20 ; "..." ; "" ) & "' to find all records using this tag. Go to all
sections if not found here."; Buttons: “OK” ]
Else If [ $refLastError ≠ 401 ]
Show Custom Dialog [ Message: "In use by Reference records. Must be removed before deleting. Click the 'find' button and then the square button next to '" & Left ( $name ; 20 ) & If ( Length ( $name ) > 20 ; "..." ; "" ) & "' to find all records using this tag. Go to all sections if not
found here."; Buttons: “OK” ]
Else If [ $TLLastError ≠ 401 ]
Show Custom Dialog [ Message: "In use by Test Learn records. Must be removed before deleting. Click the 'find' button and then the square button next to '" & Left ( $name ; 20 ) & If ( Length ( $name ) > 20 ; "..." ; "" ) & "' to find all records using this tag. Go to all sections if not
found here."; Buttons: “OK” ]
End If
Set Variable [ $delete ]
Refresh Window
Set Variable [ $$stoploadCitation ]
Exit Script [ ]
#
#If records are not found using this tag make
#sure user wants to delete it.
Else If [ $TLLastError = 401 and $refLastError ≠ 0 or
$TLLastError ≠ 0 and $refLastError = 401 or
$TLLastError = 401 and $refLastError = 401 ]
Select Window [ Name: "Tag Menus"; Current file ]
Set Variable [ $delete; Value:tagMenus::_Ltag ]
Refresh Window
Set Variable [ $category; Value:tagMenus::kGroupOrTest ]
Show Custom Dialog [ Title: "!"; Message: "Delete " & $name & "?"; Buttons: “Cancel”, “Delete” ]
#
#If the user says yes, first make sure the record
#is not the last record in a category. If it is and
#the system deleted the record without deleting
January 7, 平成26 16:33:49 Imagination Quality Management.fp7 - deleteMHOCSPtags -1-tagMenu: deleteMHOCSPtags
#the category too, this category would become
#an orphan as only categories that have records
#attached to them show up for the user to add
#more records uner them. So the category
#record must also be deleted if this is the last
#record under it.
If [ Get ( LastMessageChoice ) = 2 ]
Select Window [ Name: "delete tag"; Current file ]
Go to Layout [ “tableTag” (tagTable) ]
Enter Find Mode [ ]
Set Field [ tagTable::kGroupOrTest; $category ]
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
Set Variable [ $category ]
Refresh Window
Set Variable [ $$stoploadCitation ]
Exit Script [ ]
#
#BUT if only one record is found user is asked
#if they want to delete the category too.
Else If [ Get (FoundCount) = 1 ]
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
#
#
#The records are sorted by category to show
#the user which category is going to be deleted.
If [ TEMP::sortMedium ≠ "cat" ]
Sort Records [ Specified Sort Order: ruleTagMenuGroups::order; based on value list: “order”
ruleTagMenuGroups::name; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Else If [ TEMP::sortPath ≠ "cat" ]
Sort Records [ Specified Sort Order: ruleTagMenuGroups::order; based on value list: “order”
ruleTagMenuGroups::name; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Else If [ TEMP::sortCopyist ≠ "cat" ]
Sort Records [ Specified Sort Order: ruleTagMenuGroups::order; based on value list: “order”
ruleTagMenuGroups::name; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Else If [ TEMP::sortHealth ≠ "cat" ]
Sort Records [ Specified Sort Order: ruleTagMenuGroups::order; based on value list: “order”
ruleTagMenuGroups::name; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Else If [ TEMP::sortOrgan ≠ "cat" ]
Sort Records [ Specified Sort Order: ruleTagMenuGroups::order; based on value list: “order”
ruleTagMenuGroups::name; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
End If
#
#
Show Custom Dialog [ Title: "!"; Message: "Deleting " & Left ( $name ; 20 ) & If ( Length ( $name ) > 20 ; "..." ; "" ) & " will also delete its category as it is the last item in this category."; Buttons: “Cancel”, “Delete” ]
#
#If the user says yes, then delete both the tag and
#the category record.
If [ Get ( LastMessageChoice ) = 2 ]
Delete Record/Request
[ No dialog ]
Select Window [ Name: "delete tag"; Current file ]
Go to Layout [ “tableGroupTag” (groupTest) ]
Enter Find Mode [ ]
Set Field [ groupTest::_Lgroup; $category ]
Perform Find [ ]
Delete Record/Request
[ No dialog ]
End If
End If
End If
End If
#
#No matter what the user decides (delete or cancel)
#return the user to the window they where looking
#at and restore the sort to what the user orginally
#had selected.
Close Window [ Name: "Delete Tag"; Current file ]
Set Variable [ $delete ]
Set Variable [ $category ]
#
#
If [ TEMP::sortMedium ≠ "cat" ]
Sort Records [ Specified Sort Order: tagMenus::tag; ascending ]
[ Restore; No dialog ]
Else If [ TEMP::sortPath ≠ "cat" ]
Sort Records [ Specified Sort Order: tagMenus::tag; ascending ]
[ Restore; No dialog ]
Else If [ TEMP::sortCopyist ≠ "cat" ]
Sort Records [ Specified Sort Order: tagMenus::tag; ascending ]
[ Restore; No dialog ]
Else If [ TEMP::sortHealth ≠ "cat" ]
Sort Records [ Specified Sort Order: tagMenus::tag; ascending ]
[ Restore; No dialog ]
Else If [ TEMP::sortOrgan ≠ "cat" ]
Sort Records [ Specified Sort Order: tagMenus::tag; ascending ]
[ Restore; No dialog ]
End If
#
#
Refresh Window
Set Variable [ $$stoploadCitation ]
January 7, 平成26 16:33:49 Imagination Quality Management.fp7 - deleteMHOCSPtags -2-
