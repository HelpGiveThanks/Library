January 20, 2018 17:57:46 Library.fmp12 - deleteCPPPBtags -1-
tagMenu: deleteCPPPBtags
#Delete copyright, publication, publisher,
#path, and brainstorm tags.
#
If [ tagCreatorLock::orderOrLock ≠ "" and tagMenus::orderOrLock ≠ "lock" and tagMenus::match = "brainstorm" or
tagCreatorLock::orderOrLock ≠ "" and tagMenus::orderOrLock ≠ "lock" and tagMenus::match = "copyright" or
tagCreatorLock::orderOrLock ≠ "" and tagMenus::orderOrLock ≠ "lock" and tagMenus::match = "test" ]
Show Custom Dialog [ Message: "This record is locked. Go the node that created it — " & tagCreatorLock::tag & " — in the
setup tag window and enter the password to unlock it."; Default Button: “OK”, Commit: “No” ]
Exit Script [ ]
Else If [ tagMenus::orderOrLock ≠ "" and tagMenus::orderOrLock = "lock" and tagMenus::match = "copyright" ]
If [ tagMenuGroup::_Lgroup = "92020171119521809" ]
Show Custom Dialog [ Message: "This is the Library " & TEMP::versionNumber & " trademark tag. It cannot be deleted.
Click the 'web' button to see the source of information used to create this tag."; Default Button: “OK”, Commit: “Yes” ]
Else
Show Custom Dialog [ Message: "This is a Library " & TEMP::versionNumber & " copy of a copyright and cannot be deleted.
Click the 'web' button to see the original."; Default Button: “OK”, Commit: “Yes” ]
End If
Exit Script [ ]
End If
#
#If the copyright being checked for deletion is in use
#as a default copyright then stop the script and inform
#the user of this fact.
If [ FilterValues ( TEMP::kdefaultCopyright ; tagMenus::_Ltag & "¶" ) ]
Show Custom Dialog [ Message: "This copyright is currently selected as the default and cannot be deleted."; Default Button:
“OK”, Commit: “Yes” ]
Exit Script [ ]
End If
#
If [ $$citationMatch = "brainstorm" and $$atLeastOneRecord ≠ "" ]
If [ TEMP::InventoryLibraryYN = "" ]
Show Custom Dialog [ Message: "You can delete this brainstom after you untag it from each record using it (highlighted
blue) in the Learn window."; Default Button: “OK”, Commit: “Yes” ]
Else
Show Custom Dialog [ Message: "You can delete this inventory list after you untag it from each record using it (highlighted
blue) in the Learn window."; Default Button: “OK”, Commit: “Yes” ]
End If
Exit Script [ ]
End If
#
#Prevent all record load scripts (they slow down
#this script and are uneccessary).
Set Variable [ $$stoploadCitation; Value:1 ]
#
#Exit field so user can see red delete
#formatting later on.
Go to Field [ ]
#
#Get all variables needed to preform script.
Set Variable [ $tag; Value:tagMenus::_Ltag ]
Set Variable [ $name; Value:tagMenus::tag ]
#
#Open a new window and look for tag in both
#primary and other keyword fields.
If [ $$citationMatch ≠ "brainstorm" ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
// New Window [ Name: "Delete Tag"; Height: 1; Width: 1; Top: -10000; Left: -10000; Style: Document; Close: “Yes”; Minimize:
“Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
New Window [ Name: "Delete Tag"; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”;
Resize: “Yes” ]
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
Else If [ $$citationMatch = "publisher" ]
Set Field [ reference::kpublisher; $tag ]
Else If [ $$citationMatch = "publication" ]
Set Field [ reference::kpublication; $tag ]
Else If [ $$citationMatch = "copyright" ]
Set Field [ reference::kCopyright; $tag ]
End If
#
#
Perform Find [ ]
Set Variable [ $refLastError; Value:Get (LastError) ]
#
#
#Find copyright tagged node records. Node
#records when used to to create new records,
#are given a copyright applied to all such
#records, which the user can change.
If [ $$citationMatch = "copyright" ]
Go to Layout [ “tableTag” (tagTable) ]
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
#
#
Set Field [ tagTable::notesOrCopyright; $tag ]
Set Field [ tagTable::match; "node" ]
#
#
Perform Find [ ]
Set Variable [ $nodeCopyright; Value:Get (LastError) ]
#
#
Go to Record/Request/Page
[ First ]
Loop
Set Variable [ $nodeNames; Value:Case ( $nodeNamesPlus = "" ; tagTable::tag ; $nodeNamesPlus & "; " & tagTable::
tag) ]
Go to Record/Request/Page
[ Next; Exit after last ]
Set Variable [ $nodeNamesPlus; Value:$nodeNames ]
End Loop
#
#
#
End If
#
Set Variable [ $$stopLoadTagRecord ]
End If
#
#If records are found using this tag tell user
#that it must be removed from all records
#before it can be deleted.
If [ $nodeCopyright ≠ 401 and $nodeCopyright ≠ 400 and $nodeCopyright ≠ "" and $$citationMatch ≠ "brainstorm"
or
$refLastError ≠ 401 and $refLastError ≠ 400 and $refLastError ≠ "" and $$citationMatch ≠ "brainstorm" ]
Close Window [ Name: "Delete Tag"; Current file ]
If [ $refLastError = 0 ]
Show Custom Dialog [ Message: "In use by Reference records. Must be removed before deleting. Click the 'find' button and
then the square button next to '" & Left ( $name ; 20 ) & If ( Length ( $name ) > 20 ; "..." ; "" ) & "' to find all records
using this tag."; Default Button: “OK”, Commit: “Yes” ]
Else If [ $nodeCopyright = 0 ]
Show Custom Dialog [ Message: "In use by node records: " & $nodeNames & ". Select a new copryight for them, then you
can delete this copyright."; Default Button: “OK”, Commit: “Yes” ]
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
$TLLastError = 401 and $refLastError = 401 or
$$citationMatch = "brainstorm" ]
Select Window [ Name: "Tag Menus"; Current file ]
Set Variable [ $delete; Value:tagMenus::_Ltag ]
Refresh Window
Set Variable [ $group; Value:tagMenus::kGroupOrTest ]
Show Custom Dialog [ Message: "Delete " & $name & "?"; Default Button: “Cancel”, Commit: “Yes”; Button 2: “Delete”, Commit:
“No” ]
#
#If the user says yes, first make sure the record
#is not the last record in a group. If it is and
#the system deleted the record without deleting
#the group too, this group would become
#an orphan as only groups that have records
#attached to them show up for the user to add
#more records under them. So the group
#record must also be deleted if this is the last
#record under it.
If [ Get ( LastMessageChoice ) = 2 ]
#
If [ $$citationMatch = "brainstorm" ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
New Window [ Name: "Delete Tag"; Top: -10000; Left: -10000; Style: Document; Close: “Yes”; Minimize: “Yes”;
Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
Else
Select Window [ Name: "delete tag"; Current file ]
End If
#
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
Set Variable [ $$stopLoadTagRecord ]
Delete Record/Request
[ No dialog ]
Set Variable [ $delete ]
Set Variable [ $group ]
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
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenuGroup::orderOrLibraryType; based on
value list: “order Pulldown List”
tagMenuGroup::name; ascending
tagMenus::orderOrLock; based on value list: “order Pulldown List”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Else If [ TEMP::sortPath ≠ "cat" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenuGroup::orderOrLibraryType; based on
value list: “order Pulldown List”
tagMenuGroup::name; ascending
tagMenus::orderOrLock; based on value list: “order Pulldown List”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Else If [ TEMP::sortPublisher ≠ "cat" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenuGroup::orderOrLibraryType; based on
value list: “order Pulldown List”
tagMenuGroup::name; ascending
tagMenus::orderOrLock; based on value list: “order Pulldown List”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Else If [ TEMP::sortCopyright ≠ "cat" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenuGroup::orderOrLibraryType; based on
value list: “order Pulldown List”
tagMenuGroup::name; ascending
tagMenus::orderOrLock; based on value list: “order Pulldown List”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Else If [ TEMP::sortPublication ≠ "cat" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenuGroup::orderOrLibraryType; based on
value list: “order Pulldown List”
tagMenuGroup::name; ascending
tagMenus::orderOrLock; based on value list: “order Pulldown List”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
End If
#
#
Show Custom Dialog [ Message: "Deleting " & Left ( $name ; 20 ) & If ( Length ( $name ) > 20 ; "..." ; "" ) & " will also
delete its group as it is the last item in this group."; Default Button: “Cancel”, Commit: “Yes”; Button 2: “Delete”,
Commit: “No” ]
#
#If the user says yes, then delete both the tag and
#the category record.
If [ Get ( LastMessageChoice ) = 2 ]
Delete Record/Request
[ No dialog ]
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
End If
#
#No matter what the user decides (delete or cancel)
#return the user to the window they where looking
#at and restore the sort to what the user orginally
#had selected.
Close Window [ Name: "Delete Tag"; Current file ]
Set Variable [ $delete ]
Set Variable [ $group ]
#
#Turn back on record load variables.
Set Variable [ $$stoploadCitation ]
Set Variable [ $$stopLoadTagRecord ]
#
If [ $$citationMatch = "brainstorm" ]
Perform Script [ “loadBrainstormTags” ]
Else
Refresh Window
End If
