testScreens: test: newTestRecord
#
#basic administration tasks
Set Error Capture [ On ]
Allow User Abort [ Off ]
Set Variable [ $$stopLoadTestRecord; Value:1 ]
#
#create new inspection record setting all fields with neccessary key copies
#to unlock data
Go to Layout [ “step4_InspectionFinding” (testlearn) ]
#
#see if a finding record already exists as an N/A, OK or ★ record
#because system does not change one of these
#records when user clicks to see test records
#unless there is only one record.
Enter Find Mode [ ]
#
#find and show all inspection findings
Set Field [ testlearn::ktestSubject; $$contact ]
Set Field [ testlearn::ktest; $$item ]
Set Field [ testlearn::kreportNumber; $$reportNumber ]
Perform Find [ ]
#
// If [ Get (FoundCount) = 1 and testlearn::InspectionItemCountLocation = "N/A" and testlearn::kreportNumber = $$reportNumber or
Get (FoundCount) = 1 and testlearn::InspectionItemCountLocation = "OK" and testlearn::kreportNumber = $$reportNumber or
Get (FoundCount) = 1 and testlearn::InspectionItemCountLocation = "★" and testlearn::kreportNumber = $$reportNumber ]
Go to Record/Request/Page
[ First ]
Loop
If [ testlearn::kaudienceLocation = $$Location and testlearn::InspectionItemCountLocation = "N/A" and testlearn::kreportNumber = $$reportNumber or
testlearn::kaudienceLocation = $$Location and testlearn::InspectionItemCountLocation = "OK" and testlearn::kreportNumber = $$reportNumber or
testlearn::kaudienceLocation = $$Location and testlearn::InspectionItemCountLocation = "★" and testlearn::kreportNumber = $$reportNumber ]
#If a non finding OK or NA record exists, change it into the first finding record
Set Field [ testlearn::InspectionItemCountLocation; 1 ]
Set Field [ testlearn::kreportNumber; $$reportNumber ]
#
#increase number of findings for item in all locations
Enter Find Mode [ ]
Set Field [ testlearn::ktestSubject; $$contact ]
Set Field [ testlearn::ktest; $$item ]
Set Field [ testlearn::kreportNumber; $$reportNumber ]
Perform Find [ ]
Go to Record/Request/Page
[ First ]
Set Variable [ $number; Value:Get (FoundCount) ]
Loop
Set Field [ testlearn::InspectionItemCount; $number ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#first see if a report record exists for this item
Go to Layout [ “PrintReportEdit” (report) ]
Enter Find Mode [ ]
Set Field [ report::ktestSubject; $$contact ]
Set Field [ report::ktest; $$item ]
Set Field [ report::kreportNumber; $$reportNumber ]
Perform Find [ ]
#
If [ Get ( LastError ) = 401 ]
#
#create new report record and put in all required information
New Record/Request
Set Field [ report::ktestSubject; $$contact ]
Set Field [ report::ktest; $$item ]
Set Field [ report::kreportNumber; $$reportNumber ]
Set Field [ report::ksection; $$library ]
Set Field [ report::kRecordCreatorNode; TEMP::kdefaultNodePrimary ]
Set Field [ report::RecordModifyDate; Get ( CurrentTimeStamp ) ]
Set Field [ report::khealth; TEMP::kdefaultHealth ]
End If
Go to Layout [ “step3_InspectionItems” (InspectItems) ]
Set Field [ InspectItems::gprogressGlobal; "status: in progress" ]
Go to Layout [ “step4_InspectionFinding” (testlearn) ]
Set Variable [ $id; Value:testlearn::_Ltestlearn ]
Sort Records [ Specified Sort Order: ascending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ $ID = testlearn::_Ltestlearn ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
Set Field [ testlearn::recordnumberglobal; Get (RecordNumber) ]
Set Field [ testlearn::recordcountglobal; Get (FoundCount) ]
Exit Script [ ]
End If
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#
#
#
New Record/Request
Set Field [ testlearn::ktestSubject; $$contact ]
Set Field [ testlearn::kaudienceLocation; $$location ]
Set Field [ testlearn::kcsection; $$Library ]
Set Field [ testlearn::kreportNumber; $$reportNumber ]
#New test result for current test section is currently
#$$itemName. This variable name needs to be
#changed when time permits for testing to $$sectionName.
Set Field [ testlearn::Location; $$itemName ]
Set Field [ testlearn::ktest; $$item ]
Set Field [ testlearn::kRecordCreatorNode; TEMP::kdefaultNodePrimary ]
Set Field [ testlearn::RecordModifyDate; Get ( CurrentTimeStamp ) ]
Set Field [ testlearn::kHealth; TEMP::kdefaultHealth ]
#
#increase number of findings for item for this contact's location
Go to Layout [ “discoveries” (testlearn) ]
Enter Find Mode [ ]
Set Field [ testlearn::ktestSubject; $$contact ]
Set Field [ testlearn::kaudienceLocation; $$location ]
Set Field [ testlearn::ktest; $$item ]
Perform Find [ ]
Go to Record/Request/Page
[ First ]
Set Variable [ $number; Value:Get (FoundCount) ]
July 11, 平成27 19:41:45 Library.fp7 - newTestRecord -1-
testScreens: test: newTestRecord
Loop
Set Field [ testlearn::InspectionItemCountLocation; $number ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#increase number of findings for item
Enter Find Mode [ ]
Set Field [ testlearn::ktestSubject; $$contact ]
Set Field [ testlearn::ktest; $$item ]
Set Field [ testlearn::kreportNumber; $$reportNumber ]
Perform Find [ ]
Go to Record/Request/Page
[ First ]
Set Variable [ $number; Value:Get (FoundCount) ]
Loop
Set Field [ testlearn::InspectionItemCount; $number ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#lock item location so it cannot be deleted unless all findings for it are deleted
Go to Layout [ “tableTestSubjectFocus” (tagTestSubjectLocation) ]
Enter Find Mode [ ]
Set Field [ tagTestSubjectLocation::_LtestSubjectLocation; $$location ]
Perform Find [ ]
Set Field [ tagTestSubjectLocation::inUse; "t" ]
#refind all location records for this session
Enter Find Mode [ ]
Set Field [ tagTestSubjectLocation::knode; $$contact ]
Set Field [ tagTestSubjectLocation::ksection; $$Library ]
Set Field [ tagTestSubjectLocation::reportNumber; $$ReportNumber ]
Perform Find [ ]
#
#first see if a report record exists for this item
Set Variable [ $$stopLoadReportRecord; Value:1 ]
Go to Layout [ “PrintReportEdit” (report) ]
Enter Find Mode [ ]
Set Field [ report::ktestSubject; $$contact ]
Set Field [ report::ktest; $$item ]
Set Field [ report::kreportNumber; $$reportNumber ]
Perform Find [ ]
#
If [ Get (LastError) = 401 ]
#
#create new report record and put in all required information
New Record/Request
Set Field [ report::ktestSubject; $$contact ]
Set Field [ report::ktest; $$item ]
Set Field [ report::kreportNumber; $$reportNumber ]
Set Field [ report::ksection; $$library ]
End If
Set Variable [ $$stopLoadReportRecord ]
Go to Layout [ “step3_InspectionItems” (InspectItems) ]
Set Field [ InspectItems::gprogressGlobal; "status: in progress" ]
Go to Layout [ “step4_InspectionFinding” (testlearn) ]
Set Variable [ $id; Value:testlearn::_Ltestlearn ]
Sort Records [ Specified Sort Order: testlearn::Location; ascending
testlearn::_Number; ascending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ $ID = testlearn::_Ltestlearn ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
Set Field [ testlearn::recordnumberglobal; Get (RecordNumber) ]
Set Field [ testlearn::recordcountglobal; Get (FoundCount) ]
#
#Load new record to set variables.
Set Variable [ $$stopLoadTestRecord ]
Perform Script [ “loadTestRecord” ]
#
July 11, 平成27 19:41:45 Library.fp7 - newTestRecord -2-
