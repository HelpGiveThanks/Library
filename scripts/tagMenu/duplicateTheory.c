tagMenu: duplicateTheory
#
#If node is currenlty locked then stop script, inform user.
If [ TEMP::nodeLock ≠ "" ]
Show Custom Dialog [ Message: "The default node selected is locked. Select this node in the setup window and enter the
password to unlock it, then you will able to create new records assigned to this node."; Buttons: “OK” ]
Exit Script [ ]
End If
If [ tempSetup::kdefaultNodePrimary = "" ]
Show Custom Dialog [ Message: "Select yourself (the node responsible) from Tag Menus window."; Buttons: “OK” ]
Halt Script
End If
#
#So instead of asking the user if they really
#want to duplicate a tag, which makes a user
#seem stupid, this question performs the
#same function (are you sure) by asking them
#if they want to include a version number or
#not in their duplicate or cancel this script.
Show Custom Dialog [ Message: "Add verson number (v2, v3, v4, etc.) placeholder ' v# ' for you to help tell duplicate brainstorm tags
apart? NOTE: If there is already a version# click 'no' and update the existing #."; Buttons: “yes”, “no”, “cancel” ]
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
Set Variable [ $theoryName; Value:tagMenus::tag ]
Else
Set Variable [ $theoryName; Value:tagMenus::tag & ", v?" ]
End If
#
Set Variable [ $theoryHealth; Value:tagMenus::notesOrHealth ]
#
#Prepare to find old tags at bottom of script.
Set Variable [ $theoryOld; Value:tagMenus::_Ltag ]
#
#Stop spelling check script.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
New Record/Request
Set Field [ tagMenus::kGroupOrTest; GetNthRecord ( tagMenus::kGroupOrTest ; Get (RecordNumber) - 1 ) ]
Set Field [ tagMenus::kRecordCreatorNode; TEMP::kdefaultNodePrimary ]
Set Field [ tagMenus::tag; $theoryName ]
Set Field [ tagMenus::tagSpelling; $theoryName ]
Set Field [ tagMenus::notesOrHealth; $theoryHealth ]
#
#Prepare to add new brainstorm key to orignal
#brainstorms tagged learn records.
Set Variable [ $theoryNew; Value:tagMenus::_Ltag ]
Set Field [ tagMenus::match; "sample" ]
#
#Open a new window to now add the key to
#tagged learn records.
New Window [ Height: 3; Width: 3; Top: -1000; Left: -1000 ]
Set Variable [ $$stoploadCitation; Value:1 ]
Go to Layout [ “learn1” (testlearn) ]
#
#Find tagged learn records if there are any.
Allow User Abort [ Off ]
Set Error Capture [ On ]
Enter Find Mode [ ]
Set Field [ testlearn::kcsection; TEMP::ksection ]
Set Field [ testlearn::kcsample; "*" & $theoryOld & ¶ ]
Perform Find [ ]
#
#Add new brainstorm key to original brainstorm's
#tagged learn records.
Go to Record/Request/Page
[ First ]
Loop
Set Variable [ $allPointsEvidence; Value:testlearn::kcsample ]
Set Field [ testlearn::kcsample; testlearn::orderTest & $theoryNew & ¶ & $allPointsEvidence ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
Set Variable [ $$stoploadCitation ]
Set Variable [ $$sample; Value:testlearn::kcsample ]
Close Window [ Current Window ]
#
#Load new theory.
Set Variable [ $$tagsample; Value:tagMenus::_Ltag ]
Set Field [ TEMP::kcsample; tagMenus::_Ltag ]
If [ $$atLeastOneRecord ≠ "" ]
Set Variable [ $$atLeastOneRecord; Value:tagMenus::_Ltag ]
End If
Set Variable [ $$SampleOrTestID; Value:Get (RecordID) ]
Refresh Window
Set Variable [ $$stopLoadTagRecord ]
#
December 10, ଘ౮27 16:56:22 Library.fp7 - duplicateTheory -1-
