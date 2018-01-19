January 15, 2018 15:19:24 Library.fmp12 - reportNewTestResult -1-
test: test: reportNewTestResult
#
#If node is currenlty locked then stop script,
#and inform the user.
Perform Script [ “stopNewRecordsBeingCreatedByLockedNode (new)” ]
#
#basic administration tasks
Set Error Capture [ On ]
Allow User Abort [ Off ]
If [ testlearnReportTags::kgtestSection = "" ]
Show Custom Dialog [ Title: "!"; Message: "Select a test section by 1) clicking on the USE button under a picture or by 2) clicking
the test section button (next to new button)."; Default Button: “OK”, Commit: “Yes” ]
Halt Script
End If
#
#
Set Variable [ $$stopLoadTestResultRecord; Value:1 ]
#
New Record/Request
Set Field [ testlearnReportTags::ktestSubject; $$testSubject ]
Set Field [ testlearnReportTags::ktestSection; TEMP::ktestSection ]
Set Field [ testlearnReportTags::kreportNumber; TEMP::reportNumber ]
Set Field [ testlearnReportTags::subsectionCustomName; $$subsectionCustomName ]
Set Field [ testlearnReportTags::ktestSubsection; TEMP::ktestSubsection ]
Set Field [ testlearnReportTags::timestamp; TEMP::TimeStamp ]
Set Field [ testlearnReportTags::kNodePrimary; TEMP::kdefaultNodePrimary ]
Set Field [ testlearnReportTags::kRecordCreatorNode; TEMP::kdefaultNodePrimary ]
Set Field [ testlearnReportTags::dateModify; Get ( CurrentTimeStamp ) ]
Set Field [ testlearnReportTags::kcopyright; TEMP::kdefaultCopyright ]
#
#Note the new record ID so after sort the
#the database will be able to select it.
Set Variable [ $kpn; Value:testlearnReportTags::_Ltestlearn ]
#
#Increase number of findings for item for
#this subject's location.
Go to Layout [ “testSCRIPTloops” (testlearn) ]
Enter Find Mode [ ]
Set Field [ testlearn::ktestSubject; $$testSubject ]
Set Field [ testlearn::ktestSection; $$testSection ]
Set Field [ testlearn::ktestSubsection; $$testSubsection ]
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
#Increase number of test results.
Enter Find Mode [ ]
Set Field [ testlearn::ktestSubject; $$testSubject ]
Set Field [ testlearn::ktestSubsection; $$testSubsection ]
Set Field [ testlearn::kreportNumber; $$reportNumber ]
Perform Find [ ]
Go to Record/Request/Page
[ First ]
Set Variable [ $number; Value:Get (FoundCount) ]
Loop
Set Field [ testlearn::countOfALLSubsectionsTestResults; $number ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Lock item's section so it cannot be deleted
#unless all findings for it are deleted.
Go to Layout [ “tableTestSectionFromTemplate” (testSectionCreatedFromATemplate) ]
Enter Find Mode [ ]
Set Field [ testSectionCreatedFromATemplate::_LtestSection; $$testSection ]
Perform Find [ ]
Set Field [ testSectionCreatedFromATemplate::inUse; "t" ]
#
#Refind all section records for this session.
Enter Find Mode [ ]
Set Field [ testSectionCreatedFromATemplate::ktestSubjectNode; $$testSubject ]
Set Field [ testSectionCreatedFromATemplate::reportNumber; $$ReportNumber ]
Perform Find [ ]
Go to Layout [ original layout ]
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearnReportTags::subsectionCustomName; ascending
testlearnReportTags::timestamp; ascending
testlearnReportTags::_Ltestlearn; ascending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ testlearnReportTags::_Ltestlearn = $kpn ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Set conditional formatting variables, turn on
#the load script, and then go to the result's
#note field.
Set Variable [ $$RecordID; Value:Get (RecordID) ]
Set Variable [ $$main; Value:testlearnReportTags::_Ltestlearn ]
Set Variable [ $$stopLoadTestResultRecord ]
Go to Field [ testlearnReportTags::note ]
#
