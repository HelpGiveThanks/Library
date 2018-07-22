July 21, 2018 14:46:03 Library.fmp12 - newTestResult -1-
test: test: newTestResult
#
#If node is currenlty locked then stop script,
#and inform the user.
Perform Script [ “stopNewRecordsBeingCreatedByLockedNode” ]
#
#basic administration tasks
Set Error Capture [ On ]
Allow User Abort [ Off ]
Set Variable [ $$stopLoadTestRecord; Value:1 ]
#
#If there is a possible form in the current
#record's text field that the user may want
#to insert into the new record copy it.
Set Variable [ $noteForPossibleUseInNewRecord; Value:testlearn::note ]
#
#Find the NA record for this test subsection if
#there is one.
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ testlearn::ktestSubject; $$testSubject ]
Set Field [ testlearn::ktestSubsection; $$testSubsection ]
Set Field [ testlearn::kreportNumber; $$reportNumber ]
Set Field [ testlearn::countOfONESubsectionsTestResults; "N/A" ]
Perform Find [ ]
#
#Find the OK record for this test subsection if
#there is one.
Enter Find Mode [ ]
Set Field [ testlearn::ktestSubject; $$testSubject ]
Set Field [ testlearn::ktestSubsection; $$testSubsection ]
Set Field [ testlearn::kreportNumber; $$reportNumber ]
Set Field [ testlearn::countOfONESubsectionsTestResults; "OK" ]
Extend Found Set [ ]
#
#Delete the OK or NA record if found. This
#action removes what is now a useless record.
#
If [ testlearn::ktestSection = $$testSection and testlearn::countOfONESubsectionsTestResults = "N/A" and testlearn::kreportNumber =
$$reportNumber or
testlearn::ktestSection = $$testSection and testlearn::countOfONESubsectionsTestResults = "OK" and testlearn::kreportNumber
= $$reportNumber or
testlearn::ktestSection = $$testSection and testlearn::countOfONESubsectionsTestResults = "̣" and testlearn::
kreportNumber = $$reportNumber ]
Delete Record/Request
[ No dialog ]
End If
#
#Create a new test result for this subsection.
New Record/Request
Set Field [ testlearn::ktestSubject; $$testSubject ]
Set Field [ testlearn::ktestSection; $$testSection ]
Set Field [ testlearn::kreportNumber; $$reportNumber ]
Set Field [ testlearn::subsectionCustomName; $$testSubsectionName ]
Set Field [ testlearn::ktestSubsection; $$testSubsection ]
Set Field [ testlearn::kRecordCreatorNode; TEMP::kdefaultNodePrimary ]
Set Field [ testlearn::dateModify; Get ( CurrentTimeStamp ) ]
Set Field [ testlearn::kcopyright; TEMP::kdefaultCopyright ]
#
#Get this new records ID number.
Set Variable [ $newRecordID; Value:testlearn::_Ltestlearn ]
#
#Increase number of results for this subsection.
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
#Increase number of results for ALL subsections
#in this test.
Go to Layout [ “testSCRIPTloops” (testlearn) ]
Set Error Capture [ On ]
Enter Find Mode [ ]
Set Field [ testlearn::ktestSubsection; $$testSubsection ]
Set Field [ testlearn::ktestSubject; $$testSubject ]
Set Field [ testlearn::kreportNumber; $$reportNumber ]
#
#This find range will insure only test result
#records will be found (no NA or OK records).
Set Field [ testlearn::countOfONESubsectionsTestResults; "0...99999999999999" ]
Perform Find [ ]
#
Set Variable [ $number; Value:Get (FoundCount) ]
#
#Now find all the subject's report section records
#including NA and OK records update total
#results amount. NOTE: This done because in
#some test sections there may only be an NA or
#OK record in which to display test result totals
#that inlcude other sections.
Enter Find Mode [ ]
Set Field [ testlearn::ktestSubsection; $$testSubsection ]
Set Field [ testlearn::ktestSubject; $$testSubject ]
Set Field [ testlearn::kreportNumber; $$reportNumber ]
Go to Record/Request/Page
[ First ]
Perform Find [ ]
#
#Update the total results number for all subsections.
Loop
Set Field [ testlearn::countOfALLSubsectionsTestResults; $number ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Now refind just the test results records for this
#test subsection for the user to view.
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
#
#Set conditional formatting on main test layout
#informing user that this subsection has results.
Go to Layout [ “tableTestSectionFromTemplate” (testSectionCreatedFromATemplate) ]
Enter Find Mode [ ]
Set Field [ testSectionCreatedFromATemplate::_LtestSection; $$testSection ]
Perform Find [ ]
Set Field [ testSectionCreatedFromATemplate::inUse; "t" ]
#
#Now refind all subsections user has created on
#the main test layout.
Enter Find Mode [ ]
Set Field [ testSectionCreatedFromATemplate::ktestSubjectNode; $$testSubject ]
Set Field [ testSectionCreatedFromATemplate::reportNumber; $$ReportNumber ]
Perform Find [ ]
#
#See if a report record exists for this subsection.
Set Variable [ $$stopLoadReportRecord; Value:1 ]
Go to Layout [ “PrintReportEdit” (report) ]
Enter Find Mode [ ]
Set Field [ report::ktestSubject; $$testSubject ]
Set Field [ report::ktestSubsection; $$testSubsection ]
Set Field [ report::kreportNumber; $$reportNumber ]
Perform Find [ ]
#
#Create new report record if none exists.
If [ Get (LastError) = 401 ]
New Record/Request
Set Field [ report::ktestSubject; $$testSubject ]
Set Field [ report::ktestSubsection; $$testSubsection ]
Set Field [ report::kreportNumber; $$reportNumber ]
End If
#
#Make test status is changed from pending to
#in progress.
Set Variable [ $$stopLoadReportRecord ]
Go to Layout [ “testingSubsectionMenu” (testSubsectionForSubject) ]
Set Field [ testSubsectionForSubject::gprogressGlobal; "status: in progress" ]
#Return to the test results layout and go to
#new record.
Go to Layout [ "testResult" & Right ( TEMP::layoutTmain ; 1) ]
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::timestamp; ascending
testlearn::subsectionCustomName; ascending
testlearn::_Number; ascending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ Last ]
#
#Make sure it is the new record.
If [ $newRecordID ≠ testlearn::_Ltestlearn ]
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ $newRecordID = testlearn::_Ltestlearn ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
End If
#
#Load new record's variables.
Set Variable [ $$stopLoadTestRecord ]
Set Field [ testlearn::recordcountglobal; Get (FoundCount) ]
#
Set Field [ testlearn::recordnumberglobal; Get (RecordNumber) ]
#
#If this subsection has test items for a form
#then put the form into this new test items
#note field, unless there was copy of the form
#in the previous record, in which case ask the
#user if they want to use this previous copy
#or load a fresh form.
If [ $$noFT_ItemsFound = "" ]
If [ $noteForPossibleUseInNewRecord ≠ "" ]
Set Field [ testlearn::note; $noteForPossibleUseInNewRecord ]
Show Custom Dialog [ Message: "Use a copy the form you where just viewing (now shown), OR create a new form for this
record?"; Default Button: “copy”, Commit: “Yes”; Button 2: “new”, Commit: “No” ]
#Use Copy
If [ Get ( LastMessageChoice ) = 1 ]
If [ Filter ( $noteForPossibleUseInNewRecord ; "!" ) ≠ "" ]
Show Custom Dialog [ Message: "Remove exclamation points — ! — from the copied form? (Remove them if you
use them to indicated you completed an item on the form)"; Default Button: “remove”, Commit: “Yes”; Button 2:
“keep”, Commit: “No” ]
If [ Get ( LastMessageChoice ) = 1 ]
Set Field [ testlearn::note; Substitute ( $noteForPossibleUseInNewRecord ; "!" ; "" ) ]
End If
End If
#Create New
Else
Set Field [ testlearn::note; "" ]
Set Variable [ $$addFormToNewTestResult; Value:1 ]
End If
Else
Set Variable [ $$addFormToNewTestResult; Value:1 ]
End If
End If
#
#Load up the variables for this new test result.
Perform Script [ “loadTestResultRecord” ]
#
#
