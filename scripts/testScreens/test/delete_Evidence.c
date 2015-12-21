testScreens: test: delete_Evidence
#
If [ testlearn::_Ltestlearn = "" ]
Halt Script
End If
#
#Prevent test results in use on report from
#being deleted. Tell users how to remove
#them from the report.
If [ testlearn::inUse ≠ "" ]
Show Custom Dialog [ Message: "Remove from report " & testlearn::kreportNumber & " to delete. 1) Go back to the main test
window. 2) Click the 'report' button. In the Report window, 3) click the 'switchtest' button. 4) Select '" & $$itemName & "'. 5)
Scroll down to find and click the 'x' button next to " & testlearn::_Number & "."; Buttons: “OK” ]
Exit Script [ ]
End If
#
Set Variable [ $delete; Value:testlearn::_Ltestlearn ]
Set Variable [ $record; Value:Get (RecordNumber) ]
Set Variable [ $TempLocation; Value:testlearn::kaudienceLocation ]
Set Variable [ $TempReportNumber; Value:testlearn::kreportNumber ]
Set Variable [ $TempContact; Value:testlearn::ktestSubject ]
Set Variable [ $$step3_OpenOneItem; Value:1 ]
Go to Field [ ]
Refresh Window
#
Show Custom Dialog [ Message: "Delete test result " & testlearn::_Number & " ?"; Buttons: “Cancel”, “Delete” ]
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
Set Field [ report::ktestSubject; $TempContact ]
Set Field [ report::ktest; $$item ]
Set Field [ report::kreportNumber; $TempReportNumber ]
Set Field [ report::ksection; $$Library ]
Perform Find [ ]
Delete All Records
[ No dialog ]
Set Variable [ $delete ]
#
#Mark the section template as no longer in use.
#First, see if there are any N/A, or OK records.
Go to Layout [ “discoveries” (testlearn) ]
Enter Find Mode [ ]
Set Field [ testlearn::kaudienceLocation; $TempLocation ]
Set Field [ testlearn::kreportNumber; $TempReportNumber ]
Perform Find [ ]
#
#If there are no records at all mark in use "".
If [ Get ( LastError ) = 401 ]
Go to Layout [ “tableTestSubjectFocus” (tagTestSubjectLocation) ]
Enter Find Mode [ ]
Set Field [ tagTestSubjectLocation::_LtestSubjectLocation; $TempLocation ]
Set Field [ tagTestSubjectLocation::reportNumber; $TempReportNumber ]
Perform Find [ ]
Set Field [ tagTestSubjectLocation::inUse; "" ]
#
#Refind all template records with this report number.
Enter Find Mode [ ]
Set Field [ tagTestSubjectLocation::knode; $TempContact ]
Set Field [ tagTestSubjectLocation::reportNumber; $$reportNumber ]
Set Field [ tagTestSubjectLocation::ksection; $$Library ]
Perform Find [ ]
Go to Layout [ “step3_InspectionItems” (InspectItems) ]
#
#Because no test results where found mark the
#status as pending.
If [ InspectItems::kgaudienceLocation = $TempLocation ]
Set Field [ InspectItems::gprogressGlobal; "status: pending" ]
End If
End If
#
#
#
#
#Decrease number of results for this test on
#ALL test templates for subject's test number x.
Go to Layout [ “discoveries” (testlearn) ]
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
Set Variable [ $number; Value:Get (FoundCount) ]
#
#Now find all the subject's report section records
#including NA and OK records and update total
#results amount.
Enter Find Mode [ ]
Set Field [ testlearn::ktest; $$item ]
Set Field [ testlearn::ktestSubject; $$contact ]
Set Field [ testlearn::kreportNumber; $$reportNumber ]
Go to Record/Request/Page
[ First ]
Perform Find [ ]
Loop
Set Field [ testlearn::InspectionItemCount; $number ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
Go to Layout [ “step4_InspectionFinding” (testlearn) ]
#
Go to Layout [ “step3_InspectionItems” (InspectItems) ]
Set Field [ InspectItems::glocationNameGlobal; $$locationName ]
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
#
#Decrease number of results for this test on
#ALL test templates for subject's test number x.
Go to Layout [ “discoveries” (testlearn) ]
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
Set Variable [ $number; Value:Get (FoundCount) ]
#
#Now find all the subject's report section records
#including NA and OK records and update total
#results amount.
Enter Find Mode [ ]
Set Field [ testlearn::ktest; $$item ]
Set Field [ testlearn::ktestSubject; $$contact ]
Set Field [ testlearn::kreportNumber; $$reportNumber ]
Go to Record/Request/Page
[ First ]
Perform Find [ ]
Loop
Set Field [ testlearn::InspectionItemCount; $number ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
Go to Layout [ “step4_InspectionFinding” (testlearn) ]
#
#Load new record to set variables.
Set Variable [ $$stopLoadTestRecord ]
Perform Script [ “loadTestRecord” ]
#
Exit Script [ ]
End If
#
#If users cancels the delete then reset the window.
Set Variable [ $delete ]
Set Variable [ $$step3_OpenOneItem ]
Refresh Window
#
December 21, ଘ౮27 14:00:52 Library.fp7 - delete_Evidence -1-
