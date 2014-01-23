testScreens: test: delete_Evidence
#
If [ testlearn::_Ltestlearn = "" ]
Halt Script
End If
Set Variable [ $delete; Value:testlearn::_Ltestlearn ]
Set Variable [ $record; Value:Get (RecordNumber) ]
Set Variable [ $TempLocation; Value:testlearn::kaudienceLocation ]
Set Variable [ $TempReportNumber; Value:testlearn::kreportNumber ]
Set Variable [ $TempContact; Value:testlearn::ktestSubject ]
Set Variable [ $$step3_OpenOneItem; Value:1 ]
Go to Field [ ]
Refresh Window
// If [ $TempLocation = $$location ]
Show Custom Dialog [ Title: "!"; Message: "Delete evidence number " & testlearn::_Number & " ?"; Buttons: “Cancel”, “Delete” ]
#THIS IS DISABLED AND SHOULD EVENTUALLY
#BE DELETED AFTER TESTING. THERE USE TO BE
#A FAVORITE FIELD THAT HAS BEEN REMOVED.
#SEE EARLIER VERSIONS FOR HOW THIS FUNCTIONED.
#IN SHORT, IT DID WHAT MAKE INFO BUTTON
#NOW DOES.
// Else If [ $TempLocation ≠ $$location ]
// Show Custom Dialog [ Title: "!"; Message: "Delete evidence number " & testlearn::_Number & " ? NOTE: This piece of evidence belongs to " & tagTLTestSubject::<Field Missing> & "' evidence collection number " & testlearn::kreportNumber & " ."; Buttons: “Cancel”, “Delete” ]
// End If
If [ Get ( LastMessageChoice ) = 2 ]
#basic administration tasks
Set Error Capture [ On ]
Allow User Abort [ Off ]
Set Variable [ $$stopLoadTestRecord; Value:1 ]
#user may be showing favorites, so ﬁrst make sure
#only this reports records are showing in case this is
#the last record for this item in which case the report
#page for this item also needs to be deleted.
If [ $TempLocation = $$location ]
Enter Find Mode [ ]
Set Field [ testlearn::ktest; $$item ]
Set Field [ testlearn::kreportNumber; $TempReportNumber ]
Set Field [ testlearn::ktestSubject; $TempContact ]
Perform Find [ ]
End If
Go to Record/Request/Page
[ Last ]
If [ Get (RecordNumber) = 1 ]
Delete Record/Request
[ No dialog ]
Go to Layout [ “PrintReportEdit” (report) ]
Enter Find Mode [ ]
Set Field [ report::ktestSubject; $TempContact ]
Set Field [ report::ktest; $$item ]
Set Field [ report::kreportNumber; $TempReportNumber ]
Set Field [ report::ksection; $$Library ]
Perform Find [ ]
Delete All Records
[ No dialog ]
Set Variable [ $delete ]
#Unlock Item Location IF this was the last item
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
#reﬁnd all location records for current library report number
Enter Find Mode [ ]
Set Field [ tagTestSubjectLocation::knode; $TempContact ]
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
#THIS IS DISABLED AND SHOULD EVENTUALLY
#BE DELETED AFTER TESTING. THERE USE TO BE
#A FAVORITE FIELD THAT HAS BEEN REMOVED.
#SEE EARLIER VERSIONS FOR HOW THIS FUNCTIONED.
#IN SHORT, IT DID WHAT MAKE INFO BUTTON
#NOW DOES.
// #If this is a favorite item and it is the only one then delete the report page created for it.
// If [ $TempLocation ≠ $$location ]
// Enter Find Mode [ ]
// Set Field [ testlearn::ktest; $$item ]
// Set Field [ testlearn::kreportNumber; $TempReportNumber ]
// Set Field [ testlearn::ktestSubject; $TempContact ]
// Perform Find [ ]
// If [ Get (LastError) = 401 ]
// Go to Layout [ “PrintReportEdit” (report) ]
// Enter Find Mode [ ]
// Set Field [ report::ktestSubject; $TempContact ]
// Set Field [ report::ktest; $$item ]
// Set Field [ report::kreportNumber; $TempReportNumber ]
// Set Field [ report::ksection; $$Library ]
// Perform Find [ ]
// Delete All Records
[ No dialog ]
// Set Variable [ $delete ]
// End If
// End If
#GET ID INFO as is from different location
#Unlock Item Location
#zero out ﬁndings for item for this contact's location
#
#decrease number of ﬁndings for item for this contact's location
Go to Layout [ “discoveries” (testlearn) ]
Enter Find Mode [ ]
January 7, 平成26 12:34:49 Imagination Quality Management.fp7 - delete_Evidence -1-testScreens: test: delete_Evidence
Set Field [ testlearn::kaudienceLocation; $TempLocation ]
Set Field [ testlearn::kreportNumber; $TempReportNumber ]
Perform Find [ ]
#Unlock Item Location
If [ Get ( LastError ) = 401 ]
Go to Layout [ “tableTestSubjectFocus” (tagTestSubjectLocation) ]
Enter Find Mode [ ]
Set Field [ tagTestSubjectLocation::_LtestSubjectLocation; $TempLocation ]
Perform Find [ ]
Set Field [ tagTestSubjectLocation::inUse; "" ]
#reﬁnd all location records for this session
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
Set Field [ testlearn::kreportNumber; $TempReportNumber ]
Perform Find [ ]
Go to Record/Request/Page
[ First ]
Set Variable [ $number; Value:Get (FoundCount) ]
Loop
Set Field [ testlearn::InspectionItemCountLocation; $number ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
End If
Go to Layout [ “step4_InspectionFinding” (testlearn) ]
Enter Find Mode [ ]
Set Field [ testlearn::ktest; $$item ]
Set Field [ testlearn::kreportNumber; $TempReportNumber ]
Set Field [ testlearn::ktestSubject; $TempContact ]
Perform Find [ ]
Set Variable [ $number; Value:Get (FoundCount) ]
Go to Record/Request/Page
[ First ]
Loop
Set Field [ testlearn::InspectionItemCount; $number ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#THIS IS DISABLED AND SHOULD EVENTUALLY
#BE DELETED AFTER TESTING. THERE USE TO BE
#A FAVORITE FIELD THAT HAS BEEN REMOVED.
#SEE EARLIER VERSIONS FOR HOW THIS FUNCTIONED.
#IN SHORT, IT DID WHAT MAKE INFO BUTTON
#NOW DOES.
// If [ $TempLocation ≠ $$location ]
// Enter Find Mode [ ]
// Set Field [ testlearn::ktestSubject; $$contact ]
// Set Field [ testlearn::ktest; $$item ]
// Set Field [ testlearn::kreportNumber; $$reportNumber ]
// Perform Find [ ]
// #since this was a favorite record that was deleted, show any favorite records that remain
// Enter Find Mode [ ]
// Set Field [ testlearn::ktest; $$item ]
// Extend Found Set [ ]
// Sort Records [ Speciﬁed Sort Order: testlearn::kcsection; ascending
testlearn::kreportNumber; ascending ]
[ Restore; No dialog ]
// Go to Record/Request/Page
[ Last ]
// End If
Set Field [ testlearn::recordnumberglobal; Get (RecordNumber) ]
Set Field [ testlearn::recordcountglobal; Get (FoundCount) ]
Go to Layout [ “step4_InspectionFinding” (testlearn) ]
#
#
#Load new record to set variables.
Set Variable [ $$stopLoadTestRecord ]
Perform Script [ “loadTestRecord” ]
#
Exit Script [ ]
End If
Set Variable [ $delete ]
Set Variable [ $$step3_OpenOneItem ]
Refresh Window
January 7, 平成26 12:34:49 Imagination Quality Management.fp7 - delete_Evidence -2-
