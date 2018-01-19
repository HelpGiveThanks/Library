January 15, 2018 15:20:37 Library.fmp12 - deleteReportTestResult -1-
test: test: deleteReportTestResult
#basic administration tasks
Set Error Capture [ On ]
Allow User Abort [ Off ]
#
If [ testlearnReportTags::_Ltestlearn = "" ]
Halt Script
End If
#
#If node is currenlty locked then stop script, inform user.
If [ ReportResultTestSubject::orderOrLock ≠ "" ]
Show Custom Dialog [ Message: "The test subject — " & ReportResultTestSubject::tag & " — is locked, so all this node's test
results are locked too. Go back to Setup to unlock it."; Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
#
If [ testlearnReportTags::kcInUseOnReportSubsection ≠ "" ]
Show Custom Dialog [ Title: "!"; Message: testlearnReportTags::_Number & " is in use on " & testlearnReportTags::
inUseNumberOfTimes & If ( testlearnReportTags::inUseNumberOfTimes = 1 ; " report and must be removed before it can be
deleted." ; " reports and must be removed from all of them before it can be deleted." ); Default Button: “OK”, Commit: “Yes” ]
Exit Script [ ]
End If
#
#make to be deleted record red and capture info for delete
Set Variable [ $delete; Value:testlearnReportTags::_Ltestlearn ]
Set Variable [ $record; Value:Get (RecordNumber) ]
Set Variable [ $TempTestSection; Value:testlearnReportTags::ktestSection ]
Set Variable [ $TempReportNumber; Value:testlearnReportTags::kreportNumber ]
Set Variable [ $TempTestSubject; Value:testlearnReportTags::ktestSubject ]
Go to Field [ ]
Refresh Window
#
#
If [ testlearnReportTags::ktestSubject + testlearnReportTags::kreportNumber = $$testSubject + $$reportNumber ]
Show Custom Dialog [ Message: "Delete evidence number " & testlearnReportTags::_Number & " ?"; Default Button: “Cancel”,
Commit: “Yes”; Button 2: “Delete”, Commit: “No” ]
End If
#
#
If [ Get ( LastMessageChoice ) = 2 ]
#
#
#
If [ Get ( FoundCount ) = 1 ]
Show Custom Dialog [ Title: "!"; Message: "Deleting this last piece of evidence will delete this page of the report too, do you
wish to proceed? If you wish to keep this report page then add new evidence before deleting this evidence."; Default
Button: “Cancel”, Commit: “Yes”; Button 2: “Delete”, Commit: “No” ]
If [ Get ( LastMessageChoice ) = 2 ]
Delete Record/Request
[ No dialog ]
Else If [ Get ( LastMessageChoice ) = 1 ]
Set Variable [ $delete ]
Refresh Window
Exit Script [ ]
End If
#If there is only one test result then delete the
#report page to which it belongs.
Go to Layout [ “PrintReportEdit” (report) ]
Enter Find Mode [ ]
Set Field [ report::ktestSubject; $TempTestSubject ]
Set Field [ report::ktestSubsection; $$testSubsection ]
Set Field [ report::kreportNumber; $TempReportNumber ]
Perform Find [ ]
Delete All Records
[ No dialog ]
Set Variable [ $delete ]
#See if this was the only test result.
Go to Layout [ “testSCRIPTloops” (testlearn) ]
Enter Find Mode [ ]
Set Field [ testlearn::ktestSection; $TempTestSection ]
Set Field [ testlearn::kreportNumber; $TempReportNumber ]
Perform Find [ ]
#Unlock test IF this deleted result was
#the only test result in this test section.
If [ Get ( LastError ) = 401 ]
Go to Layout [ “tableTestSectionFromTemplate” (testSectionCreatedFromATemplate) ]
Enter Find Mode [ ]
Set Field [ testSectionCreatedFromATemplate::_LtestSection; $TempTestSection ]
Set Field [ testSectionCreatedFromATemplate::reportNumber; $TempReportNumber ]
Perform Find [ ]
Set Field [ testSectionCreatedFromATemplate::inUse; "" ]
#refind all test section records for current library report number
Enter Find Mode [ ]
Set Field [ testSectionCreatedFromATemplate::ktestSubjectNode; $TempTestSubject ]
Set Field [ testSectionCreatedFromATemplate::reportNumber; $$reportNumber ]
Perform Find [ ]
Go to Layout [ “testingSubsectionMenu” (testSubsectionForSubject) ]
#Set this test as pending testing.
If [ testSubsectionForSubject::kgtestSection = $TempTestSection ]
Set Field [ testSubsectionForSubject::gprogressGlobal; "status: pending" ]
End If
End If
#See if there are any other tests in this
#report with results.
Select Window [ Name: "Report"; Current file ]
If [ ValueListItems ( Get ( FileName ) ; "reportTestSubsections" ) = "" ]
#If none, then return to main test layout.
Perform Script [ “returnToTestSetup (update name change returnToStep2)” ]
Exit Script [ ]
Else
#If there are results in other sections then go
#to the first one of those sections.
Set Variable [ $$goToFirstReportPage; Value:GetValue ( ValueListItems ( Get ( FileName ) ; "reportTestSubsections" ) ;
1 ) ]
Perform Script [ “CHUNK_gotoTestSubsectionViaPulldown (update name change from
CHUNK_gotoItemViaPulldown)” ]
Exit Script [ ]
End If
End If
#
#
#
#switch back to this layout so don't have reassign
#fields for inspection layout. (script was written for
#findings layout)
Go to Layout [ “reportTestResult” (testlearnReportTags) ]
Go to Record/Request/Page [ $record ]
[ No dialog ]
Delete Record/Request
[ No dialog ]
Go to Layout [ “testSCRIPTloops” (testlearn) ]
#GET ID INFO as is from different location
#Unlock Item Location
#zero out findings for item for this contact's location
#
#decrease number of findings for item for this contact's location
Go to Layout [ “testSCRIPTloops” (testlearn) ]
Enter Find Mode [ ]
Set Field [ testlearn::ktestSection; $TempTestSection ]
Set Field [ testlearn::kreportNumber; $TempReportNumber ]
Perform Find [ ]
#Unlock Item Location
If [ Get ( LastError ) = 401 ]
Go to Layout [ “tableTestSectionFromTemplate” (testSectionCreatedFromATemplate) ]
Enter Find Mode [ ]
Set Field [ testSectionCreatedFromATemplate::_LtestSection; $TempTestSection ]
Perform Find [ ]
Set Field [ testSectionCreatedFromATemplate::inUse; "" ]
Else If [ Get (LastError) ≠ 401 ]
Go to Layout [ “testResult0” (testlearn) ]
Enter Find Mode [ ]
Set Field [ testlearn::ktestSubsection; $$testSubsection ]
Set Field [ testlearn::ktestSection; $TempTestSection ]
Set Field [ testlearn::kreportNumber; $TempReportNumber ]
Perform Find [ ]
Go to Record/Request/Page
[ First ]
Set Variable [ $number; Value:Get (FoundCount) ]
Loop
Set Field [ testlearn::countOfONESubsectionsTestResults; $number ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
End If
Go to Layout [ “testResult0” (testlearn) ]
Enter Find Mode [ ]
Set Field [ testlearn::ktestSubsection; $$testSubsection ]
Set Field [ testlearn::kreportNumber; $TempReportNumber ]
Set Field [ testlearn::ktestSubject; $TempTestSubject ]
Perform Find [ ]
Set Variable [ $number; Value:Get (FoundCount) ]
Go to Record/Request/Page
[ First ]
Loop
Set Field [ testlearn::countOfALLSubsectionsTestResults; $number ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
End If
Go to Layout [ “reportTestResult” (testlearnReportTags) ]
Set Variable [ $delete ]
Refresh Window
