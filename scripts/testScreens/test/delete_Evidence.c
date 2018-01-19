January 15, 2018 15:14:16 Library.fmp12 - deleteTestResult -1-
test: test: deleteTestResult
#
If [ testlearn::_Ltestlearn = "" ]
Halt Script
End If
#
#If node is currenlty locked then stop script, inform user.
If [ tagTLTestSubject::orderOrLock ≠ "" ]
Show Custom Dialog [ Message: "The test subject — " & tagTLTestSubject::tag & " — is locked, so all this node's test results are
locked too. Go back to Setup to unlock it."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
#
#Prevent test results in use on report from
#being deleted. Tell users how to remove
#them from the report.
If [ testlearn::kcInUseOnReportSubsection ≠ "" ]
Show Custom Dialog [ Message: "Remove from report " & testlearn::kreportNumber & " to delete. 1) Go back to the main test
window. 2) Click the 'report' button. In the Report window, 3) click the 'switchtest' button. 4) Select this section. 5) Scroll
down to find and click the 'x' button next to result " & testlearn::_Number & "."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
#
Set Variable [ $delete; Value:testlearn::_Ltestlearn ]
Set Variable [ $record; Value:Get (RecordNumber) ]
Set Variable [ $TempTestSection; Value:testlearn::ktestSection ]
Set Variable [ $TempReportNumber; Value:testlearn::kreportNumber ]
Set Variable [ $TempTestSubject; Value:testlearn::ktestSubject ]
Go to Field [ ]
Refresh Window
#
#Tell user what section they are about to delete
#result from, and give them the opportunity to
#cancel the delete.
If [ testlearn::ktestSection = $$testSection ]
Show Custom Dialog [ Message: "Delete this section's number " & testlearn::recordnumberglobal & " test result?"; Default Button:
“Cancel”, Commit: “Yes”; Button 2: “Delete”, Commit: “No” ]
Else
Show Custom Dialog [ Message: "Delete another section's (" & testSectionTemplateName::name & ") number " & testlearn::
recordnumberglobal & " test result?"; Default Button: “Cancel”, Commit: “Yes”; Button 2: “Delete”, Commit: “No” ]
End If
#
#If users cancels the delete then reset the window.
If [ Get ( LastMessageChoice ) = 1 ]
Set Variable [ $delete ]
Refresh Window
Exit Script [ ]
End If
#
#If the result has test items checked off its list,
#then inform the user of this and see if they
#really want to delete it.
If [ ValueCount ( testlearn::kctestResultCheckedItems ) ≠ 0 ]
Set Variable [ $testItemsCheckedOffTheList; Value:ValueCount ( testlearn::kctestResultCheckedItems ) ]
Select Window [ Name: "Tag Menus"; Current file ]
If [ $testItemsCheckedOffTheList = 1 ]
Show Custom Dialog [ Message: "Just to be sure, so far " & $testItemsCheckedOffTheList & " checklist item has been
checked off this test result's list. Continue deleting it?"; Default Button: “Cancel”, Commit: “Yes”; Button 2: “Delete”,
Commit: “No” ]
Else
Show Custom Dialog [ Message: "Just to be sure, so far " & $testItemsCheckedOffTheList & " checklist items have been
checked off this test result's list. Continue deleting it?"; Default Button: “Cancel”, Commit: “Yes”; Button 2: “Delete”,
Commit: “No” ]
End If
Select Window [ Name: "Test"; Current file ]
End If
#
#Delete record if user clicks 'delete'.
If [ Get ( LastMessageChoice ) = 2 ]
Set Variable [ $$stopLoadTestRecord; Value:1 ]
Go to Record/Request/Page
[ Last ]
#
#If last test result, then delete report page for it.
If [ Get (RecordNumber) = 1 ]
Delete Record/Request
[ No dialog ]
Go to Layout [ “PrintReportEdit” (report) ]
#
Enter Find Mode [ ]
Set Field [ report::ktestSubject; $TempTestSubject ]
Set Field [ report::ktestSubsection; $$testSubsection ]
Set Field [ report::kreportNumber; $TempReportNumber ]
Perform Find [ ]
Delete All Records
[ No dialog ]
Set Variable [ $delete ]
#
#Mark the template as no longer in use.
#First, see if there are any N/A, or OK records.
Allow User Abort [ Off ]
Set Error Capture [ On ]
Go to Layout [ “testSCRIPTloops” (testlearn) ]
Enter Find Mode [ ]
Set Field [ testlearn::ktestSection; $TempTestSection ]
Set Field [ testlearn::kreportNumber; $TempReportNumber ]
Perform Find [ ]
#
#If there are no records at all mark in use "".
If [ Get ( LastError ) = 401 ]
Go to Layout [ “tableTestSectionFromTemplate” (testSectionCreatedFromATemplate) ]
Enter Find Mode [ ]
Set Field [ testSectionCreatedFromATemplate::_LtestSection; $TempTestSection ]
Set Field [ testSectionCreatedFromATemplate::reportNumber; $TempReportNumber ]
Perform Find [ ]
Set Field [ testSectionCreatedFromATemplate::inUse; "" ]
#
#Refind all template records with this report number.
Enter Find Mode [ ]
Set Field [ testSectionCreatedFromATemplate::ktestSubjectNode; $TempTestSubject ]
Set Field [ testSectionCreatedFromATemplate::reportNumber; $$reportNumber ]
Perform Find [ ]
Go to Layout [ “testingSubsectionMenu” (testSubsectionForSubject) ]
#
#Because no test results where found mark the
#status as pending.
If [ testSubsectionForSubject::kgtestSection = $TempTestSection ]
Set Field [ testSubsectionForSubject::gprogressGlobal; "status: pending" ]
End If
End If
#
#
#
#
#Decrease number of results for this test on
#ALL test templates for subject's test number x.
Go to Layout [ “testSCRIPTloops” (testlearn) ]
Set Error Capture [ On ]
Enter Find Mode [ ]
Set Field [ testlearn::ktestSubsection; $$testSubsection ]
Set Field [ testlearn::ktestSubject; $$testSubject ]
Set Field [ testlearn::kreportNumber; $$reportNumber ]
#
#This find range will insure only records with numbers
#will be found (no NA or OK records).
Set Field [ testlearn::countOfONESubsectionsTestResults; "0...99999999999999" ]
Perform Find [ ]
Set Variable [ $number; Value:Get (FoundCount) ]
#
#Now find all the subject's report section records
#including NA and OK records and update total
#results amount.
Enter Find Mode [ ]
Set Field [ testlearn::ktestSubsection; $$testSubsection ]
Set Field [ testlearn::ktestSubject; $$testSubject ]
Set Field [ testlearn::kreportNumber; $$reportNumber ]
Go to Record/Request/Page
[ First ]
Perform Find [ ]
Loop
Set Field [ testlearn::countOfALLSubsectionsTestResults; $number ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
Go to Layout [ “testResult0” (testlearn) ]
#
Go to Layout [ “testingSubsectionMenu” (testSubsectionForSubject) ]
Set Field [ testSubsectionForSubject::gtestSectionNameGlobal; $$testSectionName ]
#
#Change the Tag Menus window to the
#blank layout and return to Test window.
Select Window [ Name: "Tag Menus"; Current file ]
Go to Layout [ “testMenuNoTag” (TEMP) ]
Select Window [ Name: "Test"; Current file ]
Exit Script [ ]
End If
#
#If there is more than one record then just
#delete this one.
Go to Record/Request/Page [ $record ]
[ No dialog ]
Delete Record/Request
[ No dialog ]
#
#Decrease number of test results shown.
Set Field [ testlearn::recordnumberglobal; Get (RecordNumber) ]
Set Field [ testlearn::recordcountglobal; Get (FoundCount) ]
#
#Decrease number of results for this test on this
#ONE test template for this test subject.
Set Error Capture [ On ]
Go to Layout [ “testSCRIPTloops” (testlearn) ]
Enter Find Mode [ ]
Set Field [ testlearn::ktestSubsection; $$testSubsection ]
Set Field [ testlearn::ktestSubject; $$testSubject ]
Set Field [ testlearn::ktestSection; $$testSection ]
Perform Find [ ]
Go to Record/Request/Page
[ First ]
Set Variable [ $number; Value:Get (FoundCount) ]
Loop
Set Field [ testlearn::countOfONESubsectionsTestResults; $number ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#
#Decrease number of results for this test on
#ALL test templates for subject's test number x.
Go to Layout [ “testSCRIPTloops” (testlearn) ]
Set Error Capture [ On ]
Enter Find Mode [ ]
Set Field [ testlearn::ktestSubsection; $$testSubsection ]
Set Field [ testlearn::ktestSubject; $$testSubject ]
Set Field [ testlearn::kreportNumber; $$reportNumber ]
#
#This find range will insure only records with numbers
#will be found (no NA or OK records).
Set Field [ testlearn::countOfONESubsectionsTestResults; "0...99999999999999" ]
Perform Find [ ]
Set Variable [ $number; Value:Get (FoundCount) ]
#
#Now find all the subject's report records
#including NA and OK records and update total
#results amount.
Enter Find Mode [ ]
Set Field [ testlearn::ktestSubsection; $$testSubsection ]
Set Field [ testlearn::ktestSubject; $$testSubject ]
Set Field [ testlearn::kreportNumber; $$reportNumber ]
Go to Record/Request/Page
[ First ]
Perform Find [ ]
Loop
Set Field [ testlearn::countOfALLSubsectionsTestResults; $number ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
Go to Layout [ "testResult" & Right ( TEMP::layoutTmain ; 1) ]
#
#Go to the record showing after delete and load
#its set of variables.
Go to Record/Request/Page [ testlearn::recordnumberglobal ]
[ No dialog ]
Set Variable [ $$stopLoadTestRecord ]
Perform Script [ “loadTestResultRecord (update name change loadTestRecord)” ]
#
Exit Script [ ]
End If
#
#If users cancels the delete then reset the window.
Set Variable [ $delete ]
Refresh Window
#
