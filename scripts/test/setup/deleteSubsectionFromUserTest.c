July 21, 2018 14:45:05 Library.fmp12 - deleteSubsectionFromUserTest -1-
test: setup: deleteSubsectionFromUserTest
#
#If there are no records, halt this script.
If [ testSectionCreatedFromATemplate::_LtestSection = "" ]
Halt Script
End If
#
#If the sub-section has test results, halt the
#script and explain to the user why.
If [ testSectionCreatedFromATemplate::inUse ≠ "" ]
Show Custom Dialog [ Message: "Delete all test results made in this section before deleting it. To do this, 1) click its green test
button. 2) Click on each sub-section with test results. 3) Delete all results you find."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
#
#
#Test subject is locked.
If [ testSubjectName::orderOrLock ≠ "" ]
Set Variable [ $$highlightTestSubject; Value:1 ]
Refresh Window
#
#Get the current test subject's name.
Show Custom Dialog [ Message: "The test subject — " & testSubjectName::tag & " — is locked. To unlock, A) go back to the
setup node tag menu. B) Select this test subject. C) Click 'lock' and enter the password."; Default Button: “OK”, Commit:
“Yes” ]
Set Variable [ $$highlightTestSubject ]
Refresh Window
Halt Script
End If
#
#
#Highlight sub-section and ask user if they
#really want to delete it.
Set Variable [ $testSubject; Value:testSectionCreatedFromATemplate::ktestSubjectNode ]
Set Variable [ $reportNumber; Value:testSectionCreatedFromATemplate::reportNumber ]
Set Variable [ $delete; Value:testSectionCreatedFromATemplate::_LtestSection ]
Go to Field [ ]
Refresh Window
Show Custom Dialog [ Message: "Delete test section " & Quote ( testSectionCreatedFromATemplate::name ) & " for " &
testSubjectName::tag & "'s test #" & testSectionCreatedFromATemplate::reportNumber & "?"; Default Button: “Cancel”, Commit:
“Yes”; Button 2: “Delete”, Commit: “No” ]
#
#If the user cancels the delete, then everything
#goes back to the way it was before the delete
#was started.
If [ Get ( LastMessageChoice ) = 1 ]
Set Variable [ $delete ]
Set Variable [ $deleteGroup ]
Refresh Window
Exit Script [ ]
End If
#
#If the user presses 'delete' the system will now
#check if it is the last sub-section in for
#this test.
If [ Get ( LastMessageChoice ) = 2 ]
Set Variable [ $$stopLoadTestRecord; Value:1 ]
New Window [ Height: 1; Width: 1; Top: -1000; Left: -1000; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”;
Zoom Control Area: “Yes”; Resize: “Yes” ]
// New Window [ Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
Set Variable [ $$stopLoadTestRecord ]
#
#Find all sub-sections for this test.
Enter Find Mode [ ]
Set Field [ testSectionCreatedFromATemplate::ktestSubjectNode; $testSubject ]
Set Field [ testSectionCreatedFromATemplate::reportNumber; $reportNumber ]
Perform Find [ ]
Set Variable [ $foundCount; Value:Get (FoundCount) ]
Close Window [ Current Window ]
#
#If this is the last subjection, let the user know
#that if deleted this test will also be deleted.
If [ $foundCount = 1 ]
Set Variable [ $deleteGroup; Value:$delete ]
Refresh Window
Show Custom Dialog [ Message: "If you delete test# " & $reportNumber & "'s last section, it will also be deleted."; Default
Button: “Cancel”, Commit: “Yes”; Button 2: “Delete”, Commit: “No” ]
#
#If the user cancels the delete, then everything
#goes back to the way it was before the delete
#was started.
If [ Get ( LastMessageChoice ) = 1 ]
Set Variable [ $delete ]
Set Variable [ $deleteGroup ]
Refresh Window
Exit Script [ ]
End If
End If
End If
#
#If the user approves of the delete, then delete
#this sub-section. NOTE: There really is no
#test that any sub-section belongs to. The
#sort is simply grouping all sub-sections by
#their report number, so it looks like they are
#under a group. Thus, deleting the last sub-
#section with particular test number will also
#cause the appearance of its test number to
#disappear.
Delete Record/Request
[ No dialog ]
#
