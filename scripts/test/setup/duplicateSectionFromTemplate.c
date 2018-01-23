January 12, 2018 14:34:35 Library.fmp12 - duplicateSectionFromTemplate -1-
test: setup: duplicateSectionFromTemplate
#
#
#If there are no record's to duplicate,
#halt script.
If [ Get (FoundCount) = 0 ]
Halt Script
End If
#
#If node is currenlty locked then stop script,
#and inform the user.
Perform Script [ “stopNewRecordsBeingCreatedByLockedNode” ]
#
#If the primary default node is unselected,
#inform user and stop script.
If [ tempSetup::kdefaultNodePrimary = "" ]
Set Variable [ $$highlightTestSection; Value:1 ]
Refresh Window
Show Custom Dialog [ Message: "Select yourself (the node responsible) from Tag Menus window."; Default Button: “OK”,
Commit: “No” ]
Halt Script
End If
#
#If the defautl test-subject node is unselected,
#inform user and stop script.
If [ TEMP::kdefaultNodeTestSubject = "" ]
Set Variable [ $$highlightTestSection; Value:1 ]
Refresh Window
Show Custom Dialog [ Message: "All tests must have a test subject. 1) Click 'tag' above and then in the tags-menu window 2)
click 'node'. 3) Select a node to be your test subject, or create a new node, and then 4) click the 'TS' button next to it.";
Default Button: “OK”, Commit: “No” ]
Halt Script
End If
#
#If the defautl test-subject node doesn't
#match the selected test's test subject,
#inform the user.
If [ testSectionCreatedFromATemplate::ktestSubjectNode ≠ TEMP::kdefaultNodeTestSubject ]
Show Custom Dialog [ Message: testSubjectName::tag & "'s — test " & testSectionCreatedFromATemplate::reportNumber & "
— will be duplicated for — " & TEMP::DEFAULTNodeTestSubjectName & "."; Default Button: “OK”, Commit: “Yes”; Button 2:
“cancel”, Commit: “No” ]
Else
#
#So instead of asking the user if they really
#want to duplicate a tag, which makes a user
#seem stupid, this question performs the
#same function (are you sure) by informing
#them how long it will take, giving them
#opportunity to cancel this script.
Show Custom Dialog [ Message: "Duplicating test " & testSectionCreatedFromATemplate::reportNumber & " for — " & TEMP::
DEFAULTNodeTestSubjectName & " — will take just a few seconds."; Default Button: “OK”, Commit: “Yes”; Button 2:
“cancel”, Commit: “No” ]
End If
#
#Exit script if user clicks cancel.
If [ Get ( LastMessageChoice ) = 2 ]
Exit Script [ ]
End If
#
#Get this test's identifying keys: test subject,
#and number.
Set Variable [ $testSubjectOld; Value:testSectionCreatedFromATemplate::ktestSubjectNode ]
Set Variable [ $testNumberOld; Value:testSectionCreatedFromATemplate::reportNumber ]
#
#Get selected test subject's highest
#test number.
Set Variable [ $$stopLoadTestRecord; Value:1 ]
New Window [ Name: "Duplicate Test"; Height: 1; Width: 1; Top: 10000; Left: 10000; Style: Document; Close: “Yes”; Minimize: “Yes”;
Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
// New Window [ Name: "Duplicate Test"; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”;
Resize: “Yes” ]
Enter Find Mode [ ]
Set Field [ testSectionCreatedFromATemplate::ktestSubjectNode; TEMP::kdefaultNodeTestSubject ]
Perform Find [ ]
Sort Records [ Keep records in sorted order; Specified Sort Order: testSectionCreatedFromATemplate::reportNumber; descending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
Set Variable [ $newTestNumber; Value:testSectionCreatedFromATemplate::reportNumber + 1 ]
#
#Now get the test records to be duplicated.
Enter Find Mode [ ]
Set Field [ testSectionCreatedFromATemplate::ktestSubjectNode; $testSubjectOld ]
Set Field [ testSectionCreatedFromATemplate::reportNumber; $testNumberOld ]
Perform Find [ ]
#
#Create duplicate test records for the default
#test subject.
Go to Record/Request/Page
[ First ]
#
Loop
Set Variable [ $testSectionID; Value:testSectionCreatedFromATemplate::ksectionTemplate ]
Set Variable [ $testSectionName; Value:testSectionCreatedFromATemplate::name ]
#
Select Window [ Name: "Setup"; Current file ]
New Record/Request
#
Set Field [ testSectionCreatedFromATemplate::ksectionTemplate; $testSectionID ]
Set Field [ testSectionCreatedFromATemplate::name; $testSectionName ]
Set Field [ testSectionCreatedFromATemplate::reportNumber; $newTestNumber ]
Set Field [ testSectionCreatedFromATemplate::ktestSubjectNode; TEMP::kdefaultNodeTestSubject ]
Set Field [ testSectionCreatedFromATemplate::kcreatorNode; TEMP::kdefaultNodePrimary ]
#
Select Window [ Name: "Duplicate Test"; Current file ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Go to the duplicated test's first record.
Close Window [ Name: "Duplicate Test"; Current file ]
Sort Records [ Keep records in sorted order; Specified Sort Order: testSubjectName::tag; ascending
testSectionCreatedFromATemplate::reportNumber; descending
testSectionCreatedFromATemplate::order; based on value list: “order Pulldown List”
testSectionCreatedFromATemplate::name; ascending ]
[ Restore; No dialog ]
Scroll Window
[ Home ]
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ testSectionCreatedFromATemplate::ktestSubjectNode = TEMP::kdefaultNodeTestSubject ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Load it up.
Set Variable [ $$stopLoadTestRecord ]
Perform Script [ “loadSetupTestSection” ]
#
