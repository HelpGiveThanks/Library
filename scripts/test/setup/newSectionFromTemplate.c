January 12, 2018 14:28:01 Library.fmp12 - newSectionFromTemplate -1-
test: setup: newSectionFromTemplate
#
#Pause prevents accidental click of
#section pulldown button after 'edit/newtest'
#button is clicked on main test layout.
If [ $$pause = 1 ]
Exit Script [ ]
End If
#
#If node is currenlty locked then stop script,
#and inform the user.
Perform Script [ “stopNewRecordsBeingCreatedByLockedNode” ]
#
#Do not allow user to create a new section if...
#
#...section is not selected.
If [ TEMP::kdefaultSectionTemplate= "" or TEMP::DEFAULTSectionName = "" ]
Set Variable [ $$highlightTestSection; Value:1 ]
Refresh Window
If [ ValueListItems ( Get ( FileName ) ; "defaultSectionTemplates" ) = "" ]
Show Custom Dialog [ Message: "There are no test-section templates available for creating new test sections. To create
some 1) click 'back', then 2) click 'section-templatesetup' and finally 3) click 'new' to create your first test-section
template. 4) Customize it to meet your needs."; Default Button: “OK”, Commit: “Yes” ]
Halt Script
End If
If [ TEMP::DEFAULTSectionName = "" ]
Show Custom Dialog [ Message: "Click 'select test section' now highlighted for you, and then select a test-section template
from the pulldown menu that will appear. Your selected template will be used to create sections that you can add to any
test."; Default Button: “OK”, Commit: “Yes” ]
Else
Show Custom Dialog [ Message: "Click '" & TEMP::DEFAULTSectionName & "', and then re-select a test-section template
from the pulldown menu that will appear."; Default Button: “OK”, Commit: “Yes” ]
End If
Halt Script
#
#...report number is not selected.
Else If [ TEMP::reportNumber = "" ]
Set Variable [ $$highlightTestSection; Value:1 ]
Refresh Window
Show Custom Dialog [ Message: "Click '#' now highlighted for you, and then select the test's number that you want to add a new
test-section to from the pulldown menu that will appear."; Default Button: “OK”, Commit: “Yes” ]
Halt Script
#
#...test subject is not selected.
Else If [ TEMP::kdefaultNodeTestSubject = "" ]
Set Variable [ $$highlightTestSection; Value:1 ]
Refresh Window
Show Custom Dialog [ Message: "All tests must have a test subject. 1) Click 'tag' above and then in the tags-menu window 2)
click 'node'. 3) Select a node to be your test subject, or create a new node, and then 4) click the 'TS' button next to it.";
Default Button: “OK”, Commit: “Yes” ]
Halt Script
#
#...test subject is selected, but is locked.
Else If [ testSubjectName::orderOrLock ≠ "" ]
Set Variable [ $$highlightTestSection; Value:1 ]
Refresh Window
#
#Get the current test subject's name.
Show Custom Dialog [ Message: "The test subject — " & testSubjectName::tag & " — is locked. To unlock, A) go back to the
setup node tag menu. B) Select this test subject. C) Click 'lock' and enter the password."; Default Button: “OK”, Commit:
“Yes” ]
Halt Script
End If
#
#If the defautl test-subject node doesn't
#match the current users selected test
#section's test-subject, inform the user.
If [ testSectionCreatedFromATemplate::ktestSubjectNode ≠ TEMP::kdefaultNodeTestSubject ]
Show Custom Dialog [ Message: "This new test section will be created for " & TEMP::DEFAULTNodeTestSubjectName & ".";
Default Button: “OK”, Commit: “No”; Button 2: “cancel”, Commit: “No” ]
If [ Get (LastMessageChoice) = 2 ]
Halt Script
End If
End If
#
#Had to capture report number as variable or
#stop record load script which would replace
#the default number selection with nothing
#upon new record creation.
Set Variable [ $reportNumber; Value:TEMP::reportNumber ]
#
#Load up new record after it is fully created.
Set Variable [ $$stopLoadTestRecord; Value:1 ]
#
#Create new record.
New Record/Request
Set Field [ testSectionCreatedFromATemplate::ksectionTemplate; TEMP::kdefaultSectionTemplate ]
Set Field [ testSectionCreatedFromATemplate::reportNumber; $reportNumber ]
Set Field [ testSectionCreatedFromATemplate::name; TEMP::DEFAULTSectionName ]
Set Field [ testSectionCreatedFromATemplate::ktestSubjectNode; TEMP::kdefaultNodeTestSubject ]
Set Field [ testSectionCreatedFromATemplate::kcreatorNode; TEMP::kdefaultNodePrimary ]
#
#Sort records so if user had selected a record
#under a different test subject than the one
#the record was just created for, this new
#record will re-sort under its test subject.
Sort Records [ Keep records in sorted order; Specified Sort Order: testSubjectName::tag; ascending
testSectionCreatedFromATemplate::reportNumber; descending
testSectionCreatedFromATemplate::order; based on value list: “order Pulldown List”
testSectionCreatedFromATemplate::name; ascending ]
[ Restore; No dialog ]
#
#Load up this new test section.
Set Variable [ $$stopLoadTestRecord ]
Perform Script [ “loadSetupTestSection” ]
#
#Allow the user the change
#this section's name.
Go to Field [ testSectionCreatedFromATemplate::name ]
#
