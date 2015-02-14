tagMenu: duplicateTheory
#
#If node is currenlty locked then stop script, inform user.
If [ TEMP::nodeLock ≠ "" ]
Show Custom Dialog [ Message: "The default node selected is locked. Select this node in the setup window and enter the password to unlock it, then you will able to create new records assigned to this node."; Buttons: “OK” ]
Exit Script [ ]
End If
If [ tempSetup::kdefaultNodePrimary = "" ]
Show Custom Dialog [ Message: "Select yourself (the node responsible) from Tag Menus window."; Buttons: “OK” ]
Halt Script
End If
If [ Get (FoundCount) = 0 ]
Perform Script [ “newCitationMenuGroup” ]
Exit Script [ ]
End If
#
#Duplicate name and copyright of old theory.
Set Variable [ $theoryName; Value:tagMenus::tag & " " & tagMenus::_Ltag ]
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
#Prepare to add new theory key to old theories points
#and evidence records.
Set Variable [ $theoryNew; Value:tagMenus::_Ltag ]
Set Field [ tagMenus::match; "sample" ]
Go to Object [ Object Name: "tag" ]
#
#Go to the other window and start the find process.
Select Window [ Name: "Learn"; Current file ]
Set Variable [ $$stoploadCitation; Value:1 ]
Allow User Abort [ Off ]
Set Error Capture [ On ]
Enter Find Mode [ ]
Set Field [ testlearn::kcsection; TEMP::ksection ]
Set Field [ testlearn::kcsample; "*" & $theoryOld & ¶ ]
Perform Find [ ]
#
#Add new theory key to old theories points and evidence.
Go to Record/Request/Page
[ First ]
Loop
Set Variable [ $allPointsEvidence; Value:testlearn::kcsample ]
Set Field [ testlearn::kcsample; testlearn::orderTest & $theoryNew & ¶ & $allPointsEvidence ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Refind all section records.
Enter Find Mode [ ]
Set Field [ testlearn::kcsection; TEMP::ksection ]
Perform Find [ ]
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ testlearn::_Ltestlearn = $$citationRecord ]
Go to Record/Request/Page
[ Next ]
End Loop
Set Variable [ $$stoploadCitation ]
#
#Load new theory.
Select Window [ Name: "Tag Menus"; Current file ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Perform Script [ “loadItemRecordForSampleTagMenu” ]
Show Custom Dialog [ Message: "Change the tag ID number to the current verson number (v2, v3, v4, etc.) of this theory."; Buttons: “OK” ]
#
January 7, 平成26 16:21:03 Imagination Quality Management.fp7 - duplicateTheory -1-
