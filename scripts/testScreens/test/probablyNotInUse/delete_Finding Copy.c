testScreens: test: probablyNotInUse: delete_Finding Copy
#
If [ testlearn::_Ltestlearn = "" ]
Halt Script
End If
Set Variable [ $delete; Value:testlearn::_Ltestlearn ]
Set Variable [ $record; Value:Get (RecordNumber) ]
Set Variable [ $TempLocation; Value:testlearn::kaudienceLocation ]
Set Variable [ $TempReportNumber; Value:testlearn::kreportNumber ]
Go to Field [ ]
Refresh Window
Show Custom Dialog [ Title: "!"; Message: "Delete finding number " & testlearn::recordnumberglobal & "?"; Buttons: “Cancel”, “Delete” ]
If [ Get ( LastMessageChoice ) = 2 ]
#basic administration tasks
Set Error Capture [ On ]
Allow User Abort [ Off ]
#create new inspection record setting all fields with neccessary key copies
#to unlock data
Go to Record/Request/Page
[ Last ]
If [ Get (RecordNumber) = 1 ]
Delete Record/Request
[ No dialog ]
Go to Layout [ “PrintReportEdit” (report) ]
Enter Find Mode [ ]
Set Field [ report::ktestSubject; $$contact ]
Set Field [ report::ktest; $$item ]
Set Field [ report::kreportNumber; $TempReportNumber ]
Set Field [ report::ksection; $$Library ]
Perform Find [ ]
Delete All Records
[ No dialog ]
Set Variable [ $delete ]
#Unlock Item Location
Go to Layout [ “discoveries” (testlearn) ]
Enter Find Mode [ ]
Set Field [ testlearn::kaudienceLocation; $TempLocation ]
Set Field [ testlearn::kreportNumber; $TempReportNumber ]
Perform Find [ ]
If [ Get ( LastError ) = 401 ]
Go to Layout [ “tableTestSubjectFocus” (tagTestSubjectLocation) ]
Enter Find Mode [ ]
Set Field [ tagTestSubjectLocation::_LtestSubjectLocation; $TempLocation ]
Set Field [ tagTestSubjectLocation::reportNumber; $TempReportNumber ]
Perform Find [ ]
Set Field [ tagTestSubjectLocation::inUse; "" ]
#refind all location records for current library report number
Enter Find Mode [ ]
Set Field [ tagTestSubjectLocation::knode; $$contact ]
Set Field [ tagTestSubjectLocation::reportNumber; $$reportNumber ]
Set Field [ tagTestSubjectLocation::ksection; $$Library ]
Perform Find [ ]
Go to Layout [ “step3_InspectionItems” (InspectItems) ]
If [ InspectItems::kgaudienceLocation = $TempLocation ]
Set Field [ InspectItems::gprogressGlobal; "status: pending" ]
End If
End If
Go to Layout [ “step3_InspectionItems” (InspectItems) ]
Set Field [ InspectItems::glocationNameGlobal; $$locationName ]
Exit Script [ ]
End If
Go to Record/Request/Page [ $record ]
[ No dialog ]
Delete Record/Request
[ No dialog ]
#If this is a favorite item and it is the only one then delete the report page created for it.
If [ $TempLocation ≠ $$location ]
Enter Find Mode [ ]
[ Pause ]
Set Field [ testlearn::ktest; $$item ]
Set Field [ testlearn::kreportNumber; $TempReportNumber ]
Perform Find [ ]
Go to Record/Request/Page
[ Last ]
If [ Get (RecordNumber) = 1 ]
Go to Layout [ “PrintReportEdit” (report) ]
Enter Find Mode [ ]
Set Field [ report::ktestSubject; $$contact ]
Set Field [ report::ktest; $$item ]
Set Field [ report::kreportNumber; $TempReportNumber ]
Set Field [ report::ksection; $$Library ]
Perform Find [ ]
Delete All Records
[ No dialog ]
Set Variable [ $delete ]
End If
End If
#GET ID INFO as is from different location
#Unlock Item Location
#zero out findings for item for this contact's location
#
#decrease number of findings for item for this contact's location
Go to Layout [ “discoveries” (testlearn) ]
Enter Find Mode [ ]
Set Field [ testlearn::kaudienceLocation; $TempLocation ]
Perform Find [ ]
#Unlock Item Location
If [ Get ( LastError ) = 401 ]
Go to Layout [ “tableTestSubjectFocus” (tagTestSubjectLocation) ]
Enter Find Mode [ ]
Set Field [ tagTestSubjectLocation::_LtestSubjectLocation; $TempLocation ]
Perform Find [ ]
Set Field [ tagTestSubjectLocation::inUse; "" ]
#refind all location records for this session
Enter Find Mode [ ]
Set Field [ tagTestSubjectLocation::knode; $$contact ]
Set Field [ tagTestSubjectLocation::reportNumber; $$reportNumber ]
Set Field [ tagTestSubjectLocation::ksection; $$Library ]
Perform Find [ ]
Go to Layout [ “step3_InspectionItems” (InspectItems) ]
If [ InspectItems::kgaudienceLocation = $TempLocation ]
Set Field [ InspectItems::gprogressGlobal; "status: pending" ]
End If
Else If [ Get (LastError) ≠ 401 ]
Go to Layout [ “step4_InspectionFinding” (testlearn) ]
Enter Find Mode [ ]
Set Field [ testlearn::ktest; $$item ]
Set Field [ testlearn::kaudienceLocation; $TempLocation ]
Perform Find [ ]
Go to Record/Request/Page
[ First ]
January 7, 平成26 12:39:10 Imagination Quality Management.fp7 - delete_Finding Copy -1-testScreens: test: probablyNotInUse: delete_Finding Copy
Set Variable [ $number; Value:Get (FoundCount) ]
Loop
Set Field [ testlearn::InspectionItemCountLocation; $number ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
End If
Go to Layout [ “step4_InspectionFinding” (testlearn) ]
Enter Find Mode [ ]
Set Field [ testlearn::ktestSubject; $$contact ]
Set Field [ testlearn::ktest; $$item ]
Set Field [ testlearn::kreportNumber; $$reportNumber ]
Perform Find [ ]
Set Variable [ $number; Value:Get (FoundCount) ]
Go to Record/Request/Page
[ First ]
Loop
Set Field [ testlearn::InspectionItemCount; $number ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
Set Field [ testlearn::recordnumberglobal; Get (RecordNumber) ]
Set Field [ testlearn::recordcountglobal; Get (FoundCount) ]
Go to Layout [ “step4_InspectionFinding” (testlearn) ]
Exit Script [ ]
End If
Set Variable [ $delete ]
Refresh Window
January 7, 平成26 12:39:10 Imagination Quality Management.fp7 - delete_Finding Copy -2-
