January 15, 2018 15:05:17 Library.fmp12 - gotoTestSubsections -1-
test: test: gotoTestSubsections
#
#If there is no report number or test subject
#name, halt the script.
If [ TEMP::reportNumber = "" ]
Go to Field [ TEMP::reportNumber ]
[ Select/perform ]
Halt Script
Else If [ testSectionCreatedFromATemplate::name = "" ]
Halt Script
End If
#
#basic administration tasks
Set Error Capture [ On ]
Allow User Abort [ Off ]
Set Variable [ $$TSRecordNumber; Value:Get (RecordNumber) ]
Go to Field [ ]
#
#This variable stops the info button's script in
#the Test and Report sections from opening a
#Reference window, which is useful in idea
#libraries to show references of ideas. In a
#things library, reference records are used as
#location records and each learn record can
#have only one location, so showing a Reference
#window in an inventory library would not be useful.
If [ TEMP::InventoryLibraryYN ≠ "" ]
Set Variable [ $$doNotOpenReferenceWindow; Value:1 ]
Else
Set Variable [ $$doNotOpenReferenceWindow ]
End If
#
#If test subject is locked, note this by getting
#the name for display in warning messages.
If [ testSubjectName::orderOrLock ≠ "" ]
Set Variable [ $$testSubjectIsLocked; Value:testSubjectName::tag ]
Set Field [ tempSetup::testSubjectNodeIsLocked; 1 ]
Else
Set Variable [ $$testSubjectIsLocked ]
Set Field [ tempSetup::testSubjectNodeIsLocked; "" ]
End If
#
#Change the default to the selected subject.
Set Field [ TEMP::kdefaultNodeTestSubject; testSectionCreatedFromATemplate::ktestSubjectNode ]
Set Field [ TEMP::DEFAULTNodeTestSubjectName; testSubjectName::tag ]
Set Variable [ $status; Value:testSectionCreatedFromATemplate::inUse ]
Set Variable [ $$timeRecord; Value:Get ( RecordNumber ) ]
Set Variable [ $$pictureWIndowColor; Value:"test" ]
#
#!!!need to go through database and remove all variables like $$reportnumber that are used in mulitple scripts and make it a temp field.
Set Variable [ $$reportnumber; Value:testSectionCreatedFromATemplate::reportNumber ]
Set Field [ TEMP::reportNumber; testSectionCreatedFromATemplate::reportNumber ]
Set Variable [ $$testSubject; Value:TEMP::kdefaultNodeTestSubject ]
#
#note general or canned location user identified
Set Variable [ $$testSectionName; Value: TextStyleAdd ( testSectionCreatedFromATemplate::name ; Titlecase ) ]
Set Field [ TEMP::testSubsectionNameForSubject; TextStyleAdd ( $$testSectionName ; Titlecase ) ]
#
#note new location ID number and name user created for this specific location in the contact's building
Set Variable [ $$testSection; Value:testSectionCreatedFromATemplate::_LtestSection ]
Set Variable [ $$testSectionTemplate; Value:testSectionCreatedFromATemplate::ksectionTemplate ]
#
#Goto no tag layout in Tag Menus as the test
#selection screen does not show any records
#that the user might want to tag.
#
#I thought about closing the Tag Menus
#window, but in testing it was odd, and so better
#just to keep the window open and show no tags
#but do change its layout to the look and feel
#of the layouts the user will see in test mode
#in the Tag Menus window.
Select Window [ Name: "Tag Menus"; Current file ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Go to Layout [ “testMenuNoTag” (TEMP) ]
Set Variable [ $$stopLoadTagRecord ]
#
#Return to main window to complete script.
Select Window [ Name: "Setup"; Current file ]
Set Field [ TEMP::testAndReportMainWindowHeader; tempSetup::userLibraryName & " | " & TEMP::
DEFAULTNodeTestSubjectName ]
Set Window Title [ Current Window; New Title: "Test" ]
Go to Layout [ “testingSubsectionMenu” (testSubsectionForSubject) ]
Enter Find Mode [ ]
#
#Now find and show all canned inspection
#test-subsections that are part of this test section.
Set Field [ testSubsectionForSubject::kcsections; $$testSectionTemplate ]
Perform Find [ ]
If [ Get ( FoundCount ) = 0 ]
Go to Layout [ “defaultTest” (testSectionCreatedFromATemplate) ]
Perform Script [ “returnToTestSetup (update name change returnToStep2)” ]
Show Custom Dialog [ Message: "This test section has no subsections to test. To add some, 1) click 'edit/newtemplate'. 2)
Select a subsection. 3) In the Tag Menus window, click the button next to this test section to add it. Repeat 2 and 3 to add
additional subsections."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
Sort Records [ Keep records in sorted order; Specified Sort Order: testSubsectionGroupForSubject::name; ascending
testSubsectionForSubject::order; based on value list: “order Pulldown List” ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
Set Variable [ $$stopLoadingTestSubSection ]
Set Field [ testSubsectionForSubject::gtestSectionNameGlobal; $$testSectionName ]
Set Field [ testSubsectionForSubject::kgtestSection; $$testSection ]
Set Field [ testSubsectionForSubject::gtestSubjectNameGlobal; $$testsubjectName ]
Set Field [ testSubsectionForSubject::kgreportNumber; $$reportNumber ]
Set Field [ testSubsectionForSubject::kgtestSubject; TEMP::kdefaultNodeTestSubject ]
If [ $status = "" ]
Set Field [ testSubsectionForSubject::gprogressGlobal; "status: pending" ]
Scroll Window
[ Home ]
Exit Script [ ]
Else If [ $status = "t" ]
Set Field [ testSubsectionForSubject::gprogressGlobal; "status: in progress" ]
Scroll Window
[ Home ]
Exit Script [ ]
End If
Set Field [ testSubsectionForSubject::gprogressGlobal; "status: done" ]
Scroll Window
[ Home ]
