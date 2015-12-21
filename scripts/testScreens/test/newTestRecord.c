testScreens: test: newTestRecord
#
#
#basic administration tasks
Set Error Capture [ On ]
Allow User Abort [ Off ]
Set Variable [ $$stopLoadTestRecord; Value:1 ]
#
#
#Find the NA record for this test section if
#there is one.
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ testlearn::ktestSubject; $$contact ]
Set Field [ testlearn::ktest; $$item ]
Set Field [ testlearn::kcsection; $$library ]
Set Field [ testlearn::kreportNumber; $$reportNumber ]
Set Field [ testlearn::InspectionItemCountLocation; "N/A" ]
Perform Find [ ]
#
#Find the OK record for this test section if
#there is one.
Enter Find Mode [ ]
Set Field [ testlearn::ktestSubject; $$contact ]
Set Field [ testlearn::ktest; $$item ]
Set Field [ testlearn::kcsection; $$library ]
Set Field [ testlearn::kreportNumber; $$reportNumber ]
Set Field [ testlearn::InspectionItemCountLocation; "OK" ]
Extend Found Set [ ]
#
#Delete the OK or NA record if found. This
#action removes what is now a useless record.
#
If [ testlearn::kaudienceLocation = $$Location and testlearn::InspectionItemCountLocation = "N/A" and testlearn::kreportNumber = $
$reportNumber or
testlearn::kaudienceLocation = $$Location and testlearn::InspectionItemCountLocation = "OK" and testlearn::kreportNumber = $
$reportNumber or
testlearn::kaudienceLocation = $$Location and testlearn::InspectionItemCountLocation = "̣" and testlearn::kreportNumber =
$$reportNumber ]
Delete Record/Request
[ No dialog ]
End If
#
#Create a new test result record for this test section.
New Record/Request
Set Field [ testlearn::ktestSubject; $$contact ]
Set Field [ testlearn::kaudienceLocation; $$location ]
Set Field [ testlearn::kcsection; $$Library ]
Set Field [ testlearn::kreportNumber; $$reportNumber ]
#
#NOTE: The active test-result's name for the
#current test section is currently captured as
#variable $$itemName. When time permits
#change this to $$ActiveTestName
Set Field [ testlearn::Location; $$itemName ]
Set Field [ testlearn::ktest; $$item ]
Set Field [ testlearn::kRecordCreatorNode; TEMP::kdefaultNodePrimary ]
Set Field [ testlearn::RecordModifyDate; Get ( CurrentTimeStamp ) ]
Set Field [ testlearn::kHealth; TEMP::kdefaultHealth ]
#
#Increase number of results for this section.
Go to Layout [ “discoveries” (testlearn) ]
Enter Find Mode [ ]
Set Field [ testlearn::ktest; $$item ]
Set Field [ testlearn::ktestSubject; $$contact ]
Set Field [ testlearn::kaudienceLocation; $$location ]
Perform Find [ ]
Go to Record/Request/Page
[ First ]
Set Variable [ $number; Value:Get (FoundCount) ]
Loop
Set Field [ testlearn::InspectionItemCountLocation; $number ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Increase number of results for ALL sections
#with this test in them.
Go to Layout [ “discoveries” (testlearn) ]
Set Error Capture [ On ]
Enter Find Mode [ ]
Set Field [ testlearn::ktest; $$item ]
Set Field [ testlearn::ktestSubject; $$contact ]
Set Field [ testlearn::kreportNumber; $$reportNumber ]
#
#This find range will insure only test result
#records will be found (no NA or OK records).
Set Field [ testlearn::InspectionItemCountLocation; "0...99999999999999" ]
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
Set Field [ testlearn::ktest; $$item ]
Set Field [ testlearn::ktestSubject; $$contact ]
Set Field [ testlearn::kreportNumber; $$reportNumber ]
Go to Record/Request/Page
[ First ]
Perform Find [ ]
#
#Update the total results number for all sections.
Loop
Set Field [ testlearn::InspectionItemCount; $number ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Now refind just the test results records for this
#test section for the user to view.
Set Error Capture [ On ]
Enter Find Mode [ ]
Set Field [ testlearn::ktest; $$item ]
Set Field [ testlearn::ktestSubject; $$contact ]
Set Field [ testlearn::kreportNumber; $$reportNumber ]
#
#This find range will insure only records with numbers
#will be found (no NA or OK records).
Set Field [ testlearn::InspectionItemCountLocation; "0...99999999999999" ]
Perform Find [ ]
#
#Set conditional formatting on main test layout
#informing user that this test section has results.
Go to Layout [ “tableTestSubjectFocus” (tagTestSubjectLocation) ]
Enter Find Mode [ ]
Set Field [ tagTestSubjectLocation::_LtestSubjectLocation; $$location ]
Perform Find [ ]
Set Field [ tagTestSubjectLocation::inUse; "t" ]
#
#Now rerind all test sections user has created on
#the main test layout.
Enter Find Mode [ ]
Set Field [ tagTestSubjectLocation::knode; $$contact ]
Set Field [ tagTestSubjectLocation::ksection; $$Library ]
Set Field [ tagTestSubjectLocation::reportNumber; $$ReportNumber ]
Perform Find [ ]
#
#See if a report record exists for this test section.
Set Variable [ $$stopLoadReportRecord; Value:1 ]
Go to Layout [ “PrintReportEdit” (report) ]
Enter Find Mode [ ]
Set Field [ report::ktestSubject; $$contact ]
Set Field [ report::ktest; $$item ]
Set Field [ report::kreportNumber; $$reportNumber ]
Perform Find [ ]
#
#Create new report record if none exists.
If [ Get (LastError) = 401 ]
New Record/Request
Set Field [ report::ktestSubject; $$contact ]
Set Field [ report::ktest; $$item ]
Set Field [ report::kreportNumber; $$reportNumber ]
Set Field [ report::ksection; $$library ]
End If
#
#Make test status is changed from pending to
#in progress.
Set Variable [ $$stopLoadReportRecord ]
Go to Layout [ “step3_InspectionItems” (InspectItems) ]
Set Field [ InspectItems::gprogressGlobal; "status: in progress" ]
#
#Return to the test results layout and go to
#new record.
Go to Layout [ “step4_InspectionFinding” (testlearn) ]
Sort Records [ Specified Sort Order: testlearn::Location; ascending
testlearn::_Number; ascending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ Last ]
#
#Load new record's variables.
Set Variable [ $$stopLoadTestRecord ]
Set Field [ testlearn::recordcountglobal; Get (FoundCount) ]
Set Field [ testlearn::recordnumberglobal; Get (RecordNumber) ]
Perform Script [ “loadTestRecord” ]
#
December 21, ଘ౮27 14:04:58 Library.fp7 - newTestRecord -1-
