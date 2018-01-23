January 15, 2018 17:18:19 Library.fmp12 - duplicateBrainstorm -1-
tagMenu: duplicateBrainstorm
#
#If node is currenlty locked then stop script,
#and inform the user.
Go to Field [ ]
Perform Script [ “stopNewRecordsBeingCreatedByLockedNode” ]
#
If [ tempSetup::kdefaultNodePrimary = "" ]
Show Custom Dialog [ Message: "Select yourself (the node responsible) from Tag Menus window."; Default Button: “OK”,
Commit: “No” ]
Halt Script
End If
#
#So instead of asking the user if they really
#want to duplicate a tag, which makes a user
#seem stupid, this question performs the
#same function (are you sure) by asking them
#if they want to include a version number or
#not in their duplicate or cancel this script.
If [ TEMP::InventoryLibraryYN = "" ]
Show Custom Dialog [ Message: "Add verson number (v2, v3, v4, etc.) placeholder ' v# ' for you to help tell duplicate brainstorms
apart? NOTE: If there is already a version# click 'no' and update the existing #."; Default Button: “yes”, Commit: “Yes”; Button
2: “no”, Commit: “No”; Button 3: “cancel”, Commit: “No” ]
Else
Show Custom Dialog [ Message: "Add verson number (v2, v3, v4, etc.) placeholder ' v# ' for you to help tell duplicate inventory
lists apart? NOTE: If there is already a version# click 'no' and update the existing #."; Default Button: “yes”, Commit: “Yes”;
Button 2: “no”, Commit: “No”; Button 3: “cancel”, Commit: “No” ]
End If
#
#Exit script if user clicks cancel.
If [ Get ( LastMessageChoice ) = 3 ]
Exit Script [ ]
End If
#
#Either get just the current brainstorm's name
#or get the name plus add a v# to the end of it
#for the duplicate record.
If [ Get ( LastMessageChoice ) = 2 ]
Set Variable [ $brainstormName; Value:tagMenus::tag ]
Else
Set Variable [ $brainstormName; Value:tagMenus::tag & ", v?" ]
End If
#
Set Variable [ $brainstormCopyright; Value:tagMenus::notesOrCopyright ]
#
#Prepare to find old tags at bottom of script.
Set Variable [ $brainstormOld; Value:tagMenus::_Ltag ]
#
#Stop spelling check script.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
New Record/Request
Set Field [ tagMenus::kGroupOrTest; GetNthRecord ( tagMenus::kGroupOrTest ; Get (RecordNumber) - 1 ) ]
Set Field [ tagMenus::kRecordCreatorNode; TEMP::kdefaultNodePrimary ]
Set Field [ tagMenus::tag; $brainstormName ]
Set Field [ tagMenus::tagSpelling; $brainstormName ]
Set Field [ tagMenus::notesOrCopyright; $brainstormCopyright ]
#
#Prepare to add new brainstorm key to orignal
#brainstorms tagged learn records.
Set Variable [ $brainstormNew; Value:tagMenus::_Ltag ]
Set Field [ tagMenus::match; "brainstorm" ]
#
#Open a new window to now add the key to
#tagged learn records.
New Window [ Height: 3; Width: 3; Top: -1000; Left: -1000; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom
Control Area: “Yes”; Resize: “Yes” ]
Set Variable [ $$stoploadCitation; Value:1 ]
Go to Layout [ “learn2” (testlearn) ]
#
#Find tagged learn records if there are any.
Allow User Abort [ Off ]
Set Error Capture [ On ]
Enter Find Mode [ ]
Set Field [ testlearn::kcbrainstorm; "*" & $brainstormOld & ¶ ]
Perform Find [ ]
#
#Add new brainstorm key to original brainstorm's
#tagged learn records.
Go to Record/Request/Page
[ First ]
Loop
Set Variable [ $allPointsEvidence; Value:testlearn::kcbrainstorm ]
Set Field [ testlearn::kcbrainstorm; testlearn::orderTestInformation & $brainstormNew & ¶ & $allPointsEvidence ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
Set Variable [ $$stoploadCitation ]
Set Variable [ $$brainstorm; Value:testlearn::kcbrainstorm ]
Close Window [ Current Window ]
#
#Load new brainstorm.
Set Variable [ $$tagbrainstorm; Value:tagMenus::_Ltag ]
Set Field [ TEMP::kcbrainstorm; tagMenus::_Ltag ]
If [ $$atLeastOneRecord ≠ "" ]
Set Variable [ $$atLeastOneRecord; Value:tagMenus::_Ltag ]
End If
Set Variable [ $$BrainstormOrTestID; Value:Get (RecordID) ]
Commit Records/Requests
Refresh Window
Set Variable [ $$stopLoadTagRecord ]
Scroll Window
[ Home ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenuGroup::name; ascending
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Go to Field [ tagMenus::tag ]
#
