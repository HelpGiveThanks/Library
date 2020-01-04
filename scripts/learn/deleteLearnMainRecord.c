December 18, 2019 19:51:18 Library.fmp12 - deleteLearnMainRecord -1-
learn: deleteLearnMainRecord
#
#
#If node that created this record as its primary
#creator is currenlty locked then stop script,
#inform user.
If [ tagTLNodePrimary::orderOrLock ≠ "" ]
Show Custom Dialog [ Message: "The node that created this record, " & tagTLNodePrimary::tag & ", is locked, so all this node's
records are locked too. Go back to Setup to unlock it."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
#
#If in find mode, exit script.
If [ $$findMode ≠ "" ]
Show Custom Dialog [ Message: "Currently in find mode. Click done in the tag menus window to exit find mode, and then click
this button."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
#
#Exit field so user can see red delete
#formatting later on.
Go to Field [ ]
#
#If either the brainstorm or test fields are filled show
#message below.
If [ testlearn::kcbrainstorm ≠ "" and testlearn::kctestSubsectionInfo ≠ "" ]
If [ TEMP::InventoryLibraryYN = "" ]
Show Custom Dialog [ Message: "Tagged by brainstorm and test tags. Remove these tags to delete. 1) Click the
'brainstorm' button. 2) Scroll to the highlighted tags. 3) Click the square buttons next to each. 4) Click the 'test' button
and repeat steps 2 and 3."; Default Button: “OK”, Commit: “Yes” ]
Else
Show Custom Dialog [ Message: "Tagged by inventory list and test tags. Remove these tags to delete. 1) Click the
'inventory list' button. 2) Scroll to the highlighted tags. 3) Click the square buttons next to each. 4) Click the 'test' button
and repeat steps 2 and 3."; Default Button: “OK”, Commit: “Yes” ]
End If
Exit Script [ ]
Else If [ //The following tests insures that paragraph returns with no numbes in them will not prevent delete. So field can be full of
paragraph returns, but have no ID numers, and so can be deleted.
testlearn::kcbrainstorm ≠ "" and Length ( testlearn::kcbrainstorm ) ≠ ValueCount ( testlearn::kcbrainstorm ) ]
If [ TEMP::InventoryLibraryYN = "" ]
Show Custom Dialog [ Message: "Tagged by brainstorm tags. Remove these tags to delete. 1) Click the 'brainstorm' button.
2) Scroll to the highlighted tags. 3) Click the square buttons next to each."; Default Button: “OK”, Commit: “Yes” ]
Else
Show Custom Dialog [ Message: "Tagged by inventory list tags. Remove these tags to delete. 1) Click the 'inventory list'
button. 2) Scroll to the highlighted tags. 3) Click the square buttons next to each."; Default Button: “OK”, Commit: “Yes” ]
End If
Exit Script [ ]
Else If [ testlearn::kctestSubsectionInfo ≠ "" ]
Show Custom Dialog [ Message: "Tagged by test tags. Remove these tags to delete. 1) Click the 'test' button. 2) Scroll to the
highlighted tags. 3) Click the square buttons next to each."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
#
#
#
#
#If the library is not an inventory library, and
#if the record has references or links to other
#Learn records, ask the user if they would like
#to remove these or delete the selected record.
If [ TEMP::InventoryLibraryYN = "" ]
If [ refLearn::referenceShort ≠ ""
 or
refTestLearn::concatenateLong ≠ ""
 or
Filter ( testlearn::kcreference ; "L" ) ≠ "" ]
#
#
# If references and links ...
If [ refLearn::referenceShort ≠ "" and refTestLearn::concatenateLong ≠ ""
 or
refLearn::referenceShort ≠ "" and Filter ( testlearn::kcreference ; "L" ) ≠ "" ]
Show Custom Dialog [ Message: "Remove record's references, links to other Learn records, or delete this record.
NOTE: You be given the chance to cancel after answering this question."; Default Button: “references”, Commit:
“Yes”; Button 2: “links”, Commit: “No”; Button 3: “delete”, Commit: “No” ]
If [ Get ( LastMessageChoice ) = 1 ]
Set Variable [ $remove; Value:"1c" ]
End If
If [ Get ( LastMessageChoice ) = 2 ]
Set Variable [ $remove; Value:"2c" ]
End If
#
# If only references ...
Else If [ refLearn::referenceShort ≠ "" ]
Show Custom Dialog [ Message: "Remove record's references or delete this record."; Default Button: “references”,
Commit: “Yes”; Button 2: “delete”, Commit: “No”; Button 3: “cancel”, Commit: “No” ]
If [ Get ( LastMessageChoice ) = 1 ]
Set Variable [ $remove; Value:1 ]
End If
#
# If cancel is selected, then cancel this script.
If [ Get ( LastMessageChoice ) = 3 ]
Exit Script [ ]
End If
#
# If only links ...
Else If [ refTestLearn::concatenateLong ≠ ""
 or
Filter ( testlearn::kcreference ; "L" ) ≠ "" ]
Show Custom Dialog [ Message: "Remove links to other Learn records or delete this record."; Default Button: “links”,
Commit: “Yes”; Button 2: “delete”, Commit: “No”; Button 3: “cancel”, Commit: “No” ]
If [ Get ( LastMessageChoice ) = 1 ]
Set Variable [ $remove; Value:2 ]
End If
#
# If cancel is selected, then cancel this script.
If [ Get ( LastMessageChoice ) = 3 ]
Exit Script [ ]
End If
End If
#
#
#If they select references, then remove all
#reference record ID numbers.
If [ $remove = 1 or $remove = "1c" ]
#
If [ $remove = "1c" ]
Show Custom Dialog [ Message: "Are you sure you want to remove this record's references?"; Default Button:
“yes”, Commit: “Yes”; Button 2: “cancel”, Commit: “No” ]
#
# If cancel is selected, then cancel this script.
If [ Get ( LastMessageChoice ) = 2 ]
Exit Script [ ]
End If
End If
#
Set Variable [ $$stoploadCitation; Value:1 ]
Set Variable [ $count; Value:ValueCount ( testlearn::kcreference ) ]
Loop
If [ Filter ( GetValue ( testlearn::kcreference ; $count ) ; "L" ) ≠ "L" ]
Set Field [ testlearn::kcreference; //last item in list has no paragraph mark, so a valuecount test needs to be
done and if item is not removed, then the removal calc without the paragraph mark is used
If ( ValueCount ( testlearn::kcreference) ≠ ValueCount ( Substitute ( testlearn::kcreference ; GetValue
( testlearn::kcreference ; $count ) & "¶" ; "" ) ) ;
Substitute ( testlearn::kcreference ; GetValue ( testlearn::kcreference ; $count ) & "¶" ; "" ) ;
Substitute ( testlearn::kcreference ; GetValue ( testlearn::kcreference ; $count ); "" )
) ]
End If
Set Variable [ $count; Value:$count - 1 ]
Exit Loop If [ $count = 0 ]
End Loop
Set Variable [ $$stoploadCitation ]
#
#Exit script once removal is completed.
Perform Script [ “loadLearnOrRefMainRecord” ]
Exit Script [ ]
End If
#
#
#If they select links, then remove all
#Learn record ID numbers.
If [ $remove = 2 or $remove = "2c" ]
#
If [ $remove = "2c" ]
Show Custom Dialog [ Message: "Are you sure you want to remove this record's links to other Learn records?";
Default Button: “yes”, Commit: “Yes”; Button 2: “cancel”, Commit: “No” ]
#
# If cancel is selected, then cancel this script.
If [ Get ( LastMessageChoice ) = 2 ]
Exit Script [ ]
End If
End If
#
Set Variable [ $$stoploadCitation; Value:1 ]
Set Variable [ $count; Value:ValueCount ( testlearn::kcreference ) ]
Loop
If [ Filter ( GetValue ( testlearn::kcreference ; $count ) ; "L" ) = "L" ]
Set Field [ testlearn::kcreference; //last item in list has no paragraph mark, so a valuecount test needs to be
done and if item is not removed, then the removal calc without the paragraph mark is used
If ( ValueCount ( testlearn::kcreference) ≠ ValueCount ( Substitute ( testlearn::kcreference ; GetValue
( testlearn::kcreference ; $count ) & "¶" ; "" ) ) ;
Substitute ( testlearn::kcreference ; GetValue ( testlearn::kcreference ; $count ) & "¶" ; "" ) ;
Substitute ( testlearn::kcreference ; GetValue ( testlearn::kcreference ; $count ); "" )
) ]
End If
Set Variable [ $count; Value:$count - 1 ]
Exit Loop If [ $count = 0 ]
End Loop
Set Variable [ $$stoploadCitation ]
#
#Exit script once removal is completed.
Perform Script [ “loadLearnOrRefMainRecord” ]
Exit Script [ ]
End If
End If
End If
#
#
#
#
#Prevent all record load scripts (they slow down
#this script and are uneccessary).
Set Variable [ $$stoploadCitation; Value:1 ]
#
#Set variables to conditionally format section to
#be deleted, and its record number so if the
#user cancels the delete, the system can return
#to this record.
Set Variable [ $delete; Value:testlearn::_Ltestlearn ]
Set Variable [ $deleteName; Value:testlearn::_Number ]
Set Variable [ $recordNumber; Value:Get (RecordNumber) ]
#
#Because there may be no records found, stop
#the system from informing the user of this.
Allow User Abort [ Off ]
Set Error Capture [ On ]
#
#Open a new window and look for record being
#cited or used as a reference by another record.
New Window [ Style: Document; Height: 1; Width: 1; Top: 10000; Left: 10000; Close: Yes; Minimize: Yes; Maximize: Yes; Resize: Yes ]
#
#See if learn record is used by any learn
#records as a reference.
Go to Layout [ “tableTestLearn” (testlearn) ]
Enter Find Mode [ ]
Set Field [ testlearn::kcreference; $delete ]
Perform Find [ ]
#
If [ Get (LastError) ≠ 401 ]
If [ $inUse ≠ "" ]
Set Variable [ $addToInUse; Value:$inUse ]
Set Variable [ $inUse; Value:$addToInUse & ", " & Get (FoundCount) & " Learn" ]
Else If [ $inUse = "" ]
Set Variable [ $inUse; Value:Get (FoundCount) & " Learn" ]
End If
End If
#
#See if learn record is used by any tag records
#as a picture. NOTE: The ability to add learn
#record pictures is no longer possible since
#version 3.
Go to Layout [ “tableTag” (tagTable) ]
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
Set Variable [ $inUse; Value:$addToInUse & ", " & ($tagFound1 + $tagFound2 + $tagFound3) & " tag menu picture(s) (" &
$tagName & ")" ]
Else If [ $inUse = "" ]
Set Variable [ $inUse; Value:($tagFound1 + $tagFound2 + $tagFound3) & " tag menu picture(s) (" & $tagName & ")" ]
End If
End If
#
Set Variable [ $tagFound1 ]
Set Variable [ $tagFound2 ]
Set Variable [ $tagFound3 ]
Set Variable [ $tagNameADD ]
Set Variable [ $tagName ]
#
#See if learn record is used by any tag records
#as a web link. NOTE: Since version 3 this
#function is no longer available.
Go to Layout [ “tableTag” (tagTable) ]
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
Set Variable [ $inUse; Value:$addToInUse & ", " & ($tagFound1 + $tagFound2 + $tagFound3) & " tag menu link(s) (" &
$tagName & ")" ]
Else If [ $inUse = "" ]
Set Variable [ $inUse; Value:($tagFound1 + $tagFound2 + $tagFound3) & " tag menu link(s) (" & $tagName & ")" ]
End If
End If
#
Set Variable [ $tagFound1 ]
Set Variable [ $tagFound2 ]
Set Variable [ $tagFound3 ]
Set Variable [ $tagNameADD ]
Set Variable [ $tagName ]
#
#
Close Window [ Current Window ]
#
#
#
#
#Report on findings and if none found
#delete record.
#
#If record was found tell user.
If [ $inUse ≠ "" ]
Set Variable [ $delete ]
Refresh Window
If [ $$LinkedLearnRecords ≠ "" ]
Show Custom Dialog [ Message: "Record cannot be deleted as it in use in these windows: " & $inUse & ". To see them 1)
Click 'find' (above). 2) Click 'linked' in the popup window."; Default Button: “OK”, Commit: “Yes” ]
Else
Show Custom Dialog [ Message: "Record cannot be deleted as it in use in these windows: " & $inUse & "."; Default Button:
“OK”, Commit: “Yes” ]
End If
Set Variable [ $$addTagToCitation ]
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
Exit Script [ ]
End If
#
#If the record being deleted was not found in
#use make sure the user really wants it deleted.
Set Variable [ $group ]
Refresh Window
If [ Filter ( testlearn::kcreference ; "L" ) ≠ "" and TEMP::InventoryLibraryYN = ""
or
$$LinkedLearnRecords ≠ "" and TEMP::InventoryLibraryYN = "" ]
Show Custom Dialog [ Message: "NOTE: This record has links to other learn records. Are you sure you want to delete it? To
see them 1) click 'cancel'. 2) Click 'find' (above). 3) Click 'linked' in the popup window."; Default Button: “cancel”, Commit:
“Yes”; Button 2: “delete”, Commit: “No” ]
Else
Show Custom Dialog [ Message: "Delete current record?"; Default Button: “cancel”, Commit: “No”; Button 2: “delete”, Commit:
“No” ]
End If
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
#If the user says yes, then delete the record.
Else If [ Get ( LastMessageChoice ) = 2 ]
Delete Record/Request
[ No dialog ]
#
End If
Set Variable [ $delete ]
Set Variable [ $group ]
Refresh Window
Set Variable [ $$addTagToCitation ]
Set Variable [ $$stopLoadCitation ]
Set Variable [ $$stopLoadTagRecord ]
#
Perform Script [ “loadLearnOrRefMainRecord” ]
#
#
