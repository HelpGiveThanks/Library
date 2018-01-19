January 15, 2018 15:46:28 Library.fmp12 - deleteTestSectionTemplate -1-
test: report: deleteTestSectionTemplate
#
#
#If there are no section templates, then stop
#this script.
If [ Get (FoundCount) = 0 ]
Exit Script [ ]
End If
#
Set Error Capture [ On ]
Allow User Abort [ Off ]
Set Variable [ $testSection; Value:testSection::_Ltag ]
Set Variable [ $recordNumber; Value:Get (RecordNumber) ]
#
If [ testSectionCreatorLock::orderOrLock ≠ "" ]
Show Custom Dialog [ Message: "This record is locked. Go the node that created it — " & testSectionCreatorLock::tag & " — in
the setup tag window and enter the password to unlock it so that you can delete it."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
#
#Highlight section template user is trying to delete.
Set Variable [ $delete; Value:testSection::_Ltag ]
#
Go to Layout [ “TEMP” (TEMP) ]
Show All Records
Delete All Records
[ No dialog ]
#
Go to Layout [ “tableTestSectionFromTemplate” (testSectionCreatedFromATemplate) ]
Enter Find Mode [ ]
Set Field [ testSectionCreatedFromATemplate::ksectionTemplate; $testSection ]
Perform Find [ ]
#
#If section's using this template then inform
#user of where and prevent its deletion.
If [ Get (LastError) ≠ 401 ]
Loop
Set Variable [ $useList; Value:TextColor(
testSubjectName::tag &
¶ &
"test " &
testSectionCreatedFromATemplate::reportNumber & " | " ;
RGB(102;102;102)) &
testSectionCreatedFromATemplate::name ]
Go to Layout [ “TEMP” (TEMP) ]
New Record/Request
Set Field [ TEMP::DeleteMessageInTempWindow1; $useList ]
Go to Layout [ “tableTestSectionFromTemplate” (testSectionCreatedFromATemplate) ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
Go to Layout [ original layout ]
New Window [ Name: " "; Width: 360; Left: Get ( WindowWidth ) - 360; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize:
“Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
Go to Layout [ “TEMP” (TEMP) ]
View As
[ View as List ]
#
#Eliminate duplicate template records.
Sort Records [ Keep records in sorted order; Specified Sort Order: TEMP::DeleteMessageInTempWindow1; ascending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
Loop
Set Variable [ $testSection; Value:TEMP::DeleteMessageInTempWindow1 ]
Go to Record/Request/Page
[ Next; Exit after last ]
If [ TEMP::DeleteMessageInTempWindow1 = $testSection ]
Omit Record
#
#NOTE: Omit by default moves to the next record
#so to go to the next record after an omission,
#the script must go to the previous record.
Go to Record/Request/Page
[ Previous ]
End If
End Loop
#
Show/Hide Toolbars
[ Lock; Hide ]
Show/Hide Text Ruler
[ Hide ]
#
#Due to a bug in FM13, window must first be
#moved back into the screen area before the
#calculation of the current screen's
#dimensions can be taken.
Move/Resize Window [ Current Window; Top: 0; Left: 0 ]
Set Field [ TEMP::Message; "This section template has been used to create test-subject, custom-named, test sections shown
below. 1) Click 'back'. 2) Click 'edit/new'. 3) Click on a section, shown below. 4) Click 'x'. 5) Repeat until all are deleted." ]
Pause/Resume Script [ Indefinitely ]
Close Window [ Current Window ]
Set Variable [ $delete ]
Refresh Window
Exit Script [ ]
End If
#
#If the section template is not in use, then
#make sure user really wants to delete it.
Go to Layout [ original layout ]
Go to Field [ ]
Go to Record/Request/Page [ $recordNumber ]
[ No dialog ]
Set Variable [ $delete; Value:testSection::_Ltag ]
Set Variable [ $name; Value:testSection::tag ]
Refresh Window
Show Custom Dialog [ Title: "!"; Message: "Delete " & $name & "?"; Default Button: “Cancel”, Commit: “Yes”; Button 2: “Delete”,
Commit: “No” ]
#
// If [ Get (FoundCount) = 1 ]
// Show Custom Dialog [ Title: "!"; Message: "Delete " & $name & "?"; Default Button: “Cancel”, Commit: “Yes”; Button 2:
“Delete”, Commit: “No” ]
// End If
#
#If user decides to delete it then do so.
If [ Get ( LastMessageChoice ) = 2 ]
#
#First remove its key from all test records that
#have it.
New Window [ Height: 1; Width: 1; Top: 10000; Left: 10000; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”;
Zoom Control Area: “Yes”; Resize: “Yes” ]
Go to Layout [ “tableTestSubsectionTemplates” (testSubsectionTemplate) ]
Enter Find Mode [ ]
Set Field [ testSubsectionTemplate::kcsections; $delete ]
Perform Find [ ]
Loop
Set Field [ testSubsectionTemplate::kcsections; //last item in list has no paragraph mark, so a valuecount test needs to be
done and if item is not removed, then the removal calc without the paragraph mark is used
If ( ValueCount ( testSubsectionTemplate::kcsections ) ≠ ValueCount ( Substitute ( testSubsectionTemplate::kcsections ;
$delete & "¶" ; "" ) ) ;
Substitute ( testSubsectionTemplate::kcsections ; $delete & "¶" ; "" ) ;
Substitute ( testSubsectionTemplate::kcsections ; $delete ; "" )
) ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
Close Window [ Current Window ]
#
#Delete this test section template.
Delete Record/Request
[ No dialog ]
End If
#
#If user cancels delete, then stop the delete process.
Set Variable [ $delete ]
Refresh Window
#
