July 20, 2018 21:50:11 Library.fmp12 - deleteReference -1-
reference: deleteReference
#
#
#NOTE: some if this code is used in the script
#CHUNKcheckIfReferencePicIsInUse for the
#purpose of figuring out if a picture is in use.
#SO if there is a problem with this code then
#check to make sure it is also addressed in
#that script too.
#
#
#If record is locked, which all default
#copyright symbols used for locked
#copyright tags are, then exit the script.
If [ reference::lock = "lock" ]
Show Custom Dialog [ Message: "This record is used by default copyright tags and so is locked."; Default Button: “OK”, Commit:
“No” ]
Exit Script [ ]
End If
#
#
#If node is currenlty locked then stop script, inform user.
If [ refCreatorNode::orderOrLock ≠ "" ]
Show Custom Dialog [ Message: "This record was created by " & $$lockedMainRefRecord & ", a node which is locked. Select
this node in the setup window and enter the password to unlock it, then you will able to delete records created by this node.";
Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
#
#
#If in find mode, exit script.
If [ $$findMode ≠ "" ]
Show Custom Dialog [ Message: "Currently in find mode. Click done in the tag menus window to exit find mode, and then click
this button."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
#
#
#If user is in tag field and has changed spelling
#exit this tag record, otherwise current reference record
#will get deleted by the spelling check script.
If [ TEMP::InventoryLibraryYN = "" ]
Select Window [ Name: "Tag Menus"; Current file ]
Go to Field [ ]
Select Window [ Name: "References"; Current file ]
End If
#
If [ TEMP::InventoryLibraryYN = "" ]
#
#If reference is sorted by ...
If [ $$referenceSort = "" ]
#keyword
Sort Records [ Keep records in sorted order; Specified Sort Order: tagKeywordPrimary::orderOrLock; based on value list:
“order Pulldown List”
tagKeywordPrimary::tag; ascending
reference::referenceShort; ascending ]
[ Restore; No dialog ]
Else If [ $$referenceSort = "author" ]
#author
Sort Records [ Keep records in sorted order; Specified Sort Order: reference::sortByAuthor; ascending
reference::referenceShort; ascending ]
[ Restore; No dialog ]
Else If [ $$referenceSort = "dateCreated" ]
#dateCreated
Sort Records [ Keep records in sorted order; Specified Sort Order: reference::createDate; descending
reference::referenceShort; ascending ]
[ Restore; No dialog ]
Else If [ $$referenceSort = "dateModified" ]
#dateModified
Sort Records [ Keep records in sorted order; Specified Sort Order: reference::modifyDate; descending
reference::referenceShort; ascending ]
[ Restore; No dialog ]
Else If [ $$referenceSort = "datePublished" ]
#datePublished
Sort Records [ Keep records in sorted order; Specified Sort Order: reference::sortByDatePublished; ascending
reference::referenceShort; ascending ]
[ Restore; No dialog ]
Else If [ $$referenceSort = "publication" ]
#publication title
Sort Records [ Keep records in sorted order; Specified Sort Order: reference::sortByPublication; ascending
reference::referenceShort; ascending ]
[ Restore; No dialog ]
Else If [ $$referenceSort = "publisher" ]
#publisher's name
Sort Records [ Keep records in sorted order; Specified Sort Order: tagPublisher::tag; ascending
reference::referenceShort; ascending ]
[ Restore; No dialog ]
Else If [ $$referenceSort = "title" ]
#title
Sort Records [ Keep records in sorted order; Specified Sort Order: reference::sortByTitle; ascending ]
[ Restore; No dialog ]
End If
End If
#
#
#Exit field so user can see red delete
#formatting later on.
Go to Field [ ]
#
#
#Prevent all record load scripts (they slow down
#this script and are uneccessary).
Set Variable [ $$stoploadCitation; Value:1 ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
#
#
#Set variables to conditionally format section to
#be deleted, and its record number so if the
#user cancels the delete, the system can return
#to this record.
Set Variable [ $delete; Value:reference::_Lreference ]
Set Variable [ $deleteName; Value:reference::_Number ]
Set Variable [ $recordNumber; Value:Get (RecordNumber) ]
#
#
#Because there may be no records found, stop
#the system from informing the user of this.
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#
#Open a new window and look for record being
#cited or used as a reference by another record.
New Window [ Height: 1; Width: 1; Top: -10000; Left: -10000; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom
Control Area: “Yes”; Resize: “Yes” ]
#
#
#See if reference is used by any learn records as a
#reference.
Go to Layout [ “tableTestLearn” (testlearn) ]
Enter Find Mode [ ]
Set Field [ testlearn::kcreference; $delete ]
Perform Find [ ]
#
If [ Get (LastError) ≠ 401 ]
If [ $inUse ≠ "" ]
Set Variable [ $addToInUse; Value:$inUse ]
If [ Get (FoundCount) = 1 ]
Set Variable [ $inUse; Value:$addToInUse & " | " & Get (FoundCount) & " Learn record" ]
Else
Set Variable [ $inUse; Value:$addToInUse & " | " & Get (FoundCount) & " Learn records" ]
End If
Else If [ $inUse = "" ]
If [ Get (FoundCount) = 1 ]
Set Variable [ $inUse; Value:Get (FoundCount) & " Learn record" ]
Else
Set Variable [ $inUse; Value:Get (FoundCount) & " Learn records" ]
End If
End If
End If
#
#
#See if reference is used by any reference records as a
#citation.
Go to Layout [ “Reference” (reference) ]
Enter Find Mode [ ]
Set Field [ reference::kcitation; $delete ]
Perform Find [ ]
#
If [ Get (LastError) ≠ 401 ]
If [ $inUse ≠ "" ]
Set Variable [ $addToInUse; Value:$inUse ]
If [ Get (FoundCount) = 1 ]
Set Variable [ $inUse; Value:$addToInUse & " | " & Get (FoundCount) & " cite tag for a reference" ]
Else
Set Variable [ $inUse; Value:$addToInUse & " | " & Get (FoundCount) & " Cite tags for references" ]
End If
Else If [ $inUse = "" ]
If [ Get (FoundCount) = 1 ]
Set Variable [ $inUse; Value:Get (FoundCount) & " Cite tag for a reference" ]
Else
Set Variable [ $inUse; Value:Get (FoundCount) & " Cite tags for references" ]
End If
End If
End If
#
#
#See if reference record's media
#is used by any tag records.
#There are three pictures per record.
Go to Layout [ “tableTag” (tagTable) ]
#
#picture1
Enter Find Mode [ ]
Set Field [ tagTable::Kpicture1; $delete ]
Perform Find [ ]
Set Variable [ $tagFound1; Value:Get (FoundCount) ]
If [ Get (FoundCount) > 0 ]
Go to Record/Request/Page
[ First ]
Loop
Set Variable [ $tagNameADD; Value:$tagName ]
Set Variable [ $tagName; Value:Case (
$tagNameAdd = "" ;
tagTable::tag ;
$tagNameAdd & "; " & tagTable::tag ) ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
End If
#
#picture2
Enter Find Mode [ ]
Set Field [ tagTable::Kpicture2; $delete ]
Perform Find [ ]
Set Variable [ $tagFound2; Value:Get (FoundCount) ]
If [ Get (FoundCount) > 0 ]
Go to Record/Request/Page
[ First ]
Loop
Set Variable [ $tagNameADD; Value:$tagName ]
Set Variable [ $tagName; Value:Case (
$tagNameAdd = "" ;
tagTable::tag ;
$tagNameAdd & "; " & tagTable::tag ) ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
End If
#
#picture3
Enter Find Mode [ ]
Set Field [ tagTable::Kpicture3; $delete ]
Perform Find [ ]
Set Variable [ $tagFound3; Value:Get (FoundCount) ]
If [ Get (FoundCount) > 0 ]
Go to Record/Request/Page
[ First ]
Loop
Set Variable [ $tagNameADD; Value:$tagName ]
Set Variable [ $tagName; Value:Case (
$tagNameAdd = "" ;
tagTable::tag ;
$tagNameAdd & "; " & tagTable::tag ) ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
End If
#
If [ $tagFound1 + $tagFound2 + $tagFound3 ≠ 0 ]
If [ $inUse ≠ "" ]
Set Variable [ $addToInUse; Value:$inUse ]
If [ $tagFound1 + $tagFound2 + $tagFound3 = 1 ]
Set Variable [ $inUse; Value:$addToInUse & " | " & ($tagFound1 + $tagFound2 + $tagFound3) & " Picture for tag " &
$tagName ]
Else
Set Variable [ $inUse; Value:$addToInUse & " | " & ($tagFound1 + $tagFound2 + $tagFound3) & " Pictures for tags " &
$tagName ]
End If
Else If [ $inUse = "" ]
If [ $tagFound1 + $tagFound2 + $tagFound3 = 1 ]
Set Variable [ $inUse; Value:($tagFound1 + $tagFound2 + $tagFound3) & " Picture for tag " & $tagName ]
Else
Set Variable [ $inUse; Value:($tagFound1 + $tagFound2 + $tagFound3) & " Pictures for tags " & $tagName ]
End If
End If
End If
#
#
#Clear tag variables or use with link tags next.
Set Variable [ $tagFound1 ]
Set Variable [ $tagFound2 ]
Set Variable [ $tagFound3 ]
Set Variable [ $tagNameADD ]
Set Variable [ $tagName ]
#
#
#See if reference record's web link
#is used by any tag records.
#There are link fields per record.
Go to Layout [ “tableTag” (tagTable) ]
#
#link1
Enter Find Mode [ ]
Set Field [ tagTable::Ktitle1; $delete ]
Perform Find [ ]
Set Variable [ $tagFound1; Value:Get (FoundCount) ]
If [ Get (FoundCount) > 0 ]
Go to Record/Request/Page
[ First ]
Loop
Set Variable [ $tagNameADD; Value:$tagName ]
Set Variable [ $tagName; Value:Case (
$tagNameAdd = "" ;
tagTable::tag ;
$tagNameAdd & "; " & tagTable::tag ) ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
End If
#
#link2
Enter Find Mode [ ]
Set Field [ tagTable::Ktitle2; $delete ]
Perform Find [ ]
Set Variable [ $tagFound2; Value:Get (FoundCount) ]
If [ Get (FoundCount) > 0 ]
Go to Record/Request/Page
[ First ]
Loop
Set Variable [ $tagNameADD; Value:$tagName ]
Set Variable [ $tagName; Value:Case (
$tagNameAdd = "" ;
tagTable::tag ;
$tagNameAdd & "; " & tagTable::tag ) ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
End If
#
#link3
Enter Find Mode [ ]
Set Field [ tagTable::Ktitle3; $delete ]
Perform Find [ ]
Set Variable [ $tagFound3; Value:Get (FoundCount) ]
If [ Get (FoundCount) > 0 ]
Go to Record/Request/Page
[ First ]
Loop
Set Variable [ $tagNameADD; Value:$tagName ]
Set Variable [ $tagName; Value:Case (
$tagNameAdd = "" ;
tagTable::tag ;
$tagNameAdd & "; " & tagTable::tag ) ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
End If
#
If [ $tagFound1 + $tagFound2 + $tagFound3 ≠ 0 ]
If [ $inUse ≠ "" ]
Set Variable [ $addToInUse; Value:$inUse ]
If [ $tagFound1 + $tagFound2 + $tagFound3 = 1 ]
Set Variable [ $inUse; Value:$addToInUse & " | " & ($tagFound1 + $tagFound2 + $tagFound3) & " Web link for tag " &
$tagName ]
Else
Set Variable [ $inUse; Value:$addToInUse & " | " & ($tagFound1 + $tagFound2 + $tagFound3) & " Web links for tags "
& $tagName ]
End If
Else If [ $inUse = "" ]
If [ $tagFound1 + $tagFound2 + $tagFound3 = 1 ]
Set Variable [ $inUse; Value:($tagFound1 + $tagFound2 + $tagFound3) & " Web link for tag " & $tagName ]
Else
Set Variable [ $inUse; Value:($tagFound1 + $tagFound2 + $tagFound3) & " Web links for tags " & $tagName ]
End If
End If
End If
#
#
#Close window used to find records
#that might be using the reference.
Close Window [ Current Window ]
#
#
#Report on findings, or, if therer are none,
#proceed to delete reference record.
If [ $inUse ≠ "" ]
Set Variable [ $delete ]
Refresh Window
If [ GetAsNumber ( $inuse ) = 1 ]
Show Custom Dialog [ Message: "Reference is in use by " & $inUse & " record and cannot be deleted."; Default Button:
“OK”, Commit: “Yes” ]
Else
Show Custom Dialog [ Message: "Reference is in use by X number of records and cannot be deleted: " & $inUse & ".";
Default Button: “OK”, Commit: “Yes” ]
End If
Set Variable [ $$addTagToCitation ]
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
Exit Script [ ]
End If
#
#
#If the record being deleted was not found,
#make sure the user really wants it deleted.
Refresh Window
Show Custom Dialog [ Message: "Delete current record?"; Default Button: “cancel”, Commit: “Yes”; Button 2: “delete”, Commit: “No” ]
#
#
#If the user cancels, stop the delete.
If [ Get ( LastMessageChoice ) = 1 ]
Go to Field [ ]
Set Variable [ $delete ]
Refresh Window
Refresh Window
Set Variable [ $$addTagToCitation ]
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
Exit Script [ ]
#
#
#If the user says yes, then delete the record.
Else If [ Get ( LastMessageChoice ) = 2 ]
Delete Record/Request
[ No dialog ]
#
#
#After the delete, load up the newly selected
#reference record's information.
Set Variable [ $$addTagToCitation ]
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
If [ TEMP::InventoryLibraryYN = "" ]
Perform Script [ “loadLearnOrRefMainRecord” ]
Else
Perform Script [ “loadTagRecord” ]
End If
End If
#
