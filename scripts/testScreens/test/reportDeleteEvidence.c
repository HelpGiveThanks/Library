testScreens: test: reportDeleteEvidence
#basic administration tasks
Set Error Capture [ On ]
Allow User Abort [ Off ]
#
If [ testlearnReportTags::_Ltestlearn = "" ]
Halt Script
End If
If [ testlearnReportTags::inUse ≠ "" ]
Show Custom Dialog [ Title: "!"; Message: testlearnReportTags::_Number & " is in use on " & testlearnReportTags::inUseNumberOfTimes & If ( testlearnReportTags::inUseNumberOfTimes = 1 ; " report and must be removed before it can be deleted." ; " reports and must be removed from all
of them before it can be deleted." ); Buttons: “OK” ]
Exit Script [ ]
End If
#
#make to be deleted record red and capture info for delete
Set Variable [ $delete; Value:testlearnReportTags::_Ltestlearn ]
Set Variable [ $record; Value:Get (RecordNumber) ]
Set Variable [ $TempLocation; Value:testlearnReportTags::kaudienceLocation ]
Set Variable [ $TempReportNumber; Value:testlearnReportTags::kreportNumber ]
Set Variable [ $TempContact; Value:testlearnReportTags::ktestSubject ]
Go to Field [ ]
Refresh Window
If [ testlearnReportTags::ktestSubject + testlearnReportTags::kreportNumber = $$contact + $$reportNumber ]
Show Custom Dialog [ Title: "!"; Message: "Delete evidence number " & testlearnReportTags::_Number & " ?"; Buttons: “Cancel”, “Delete” ]
#THIS IS DISABLED AND SHOULD EVENTUALLY
#BE DELETED AFTER TESTING. THERE USE TO BE
#A FAVORITE FIELD THAT HAS BEEN REMOVED.
#SEE EARLIER VERSIONS FOR HOW THIS FUNCTIONED.
#IN SHORT, IT DID WHAT MAKE INFO BUTTON
#NOW DOES.
// Else If [ testlearnReportTags::ktestSubject + testlearnReportTags::kreportNumber ≠ $$contact + $$reportNumber ]
// Show Custom Dialog [ Title: "!"; Message: "Delete evidence number " & testlearnReportTags::_Number & " ? NOTE: THIS EVIDENCE IS A FAVORITE BELONGING A DIFFERENT REPORT."; Buttons: “Cancel”, “Delete” ]
End If
If [ Get ( LastMessageChoice ) = 2 ]
#user may be showing favorites, so ﬁrst make sure
#only this reports records are showing in case this is
#the last record for this item in which case the report
#page for this item also needs to be deleted.
If [ testlearnReportTags::ktestSubject + testlearnReportTags::kreportNumber = $$contact + $$reportNumber ]
Go to Layout [ “discoveries” (testlearn) ]
Enter Find Mode [ ]
Set Field [ testlearn::ktest; $$item ]
Set Field [ testlearn::kreportNumber; $TempReportNumber ]
Set Field [ testlearn::ktestSubject; $TempContact ]
Perform Find [ ]
End If
Go to Record/Request/Page
[ Last ]
If [ Get (RecordNumber) = 1 ]
#switch back to this layout to preserve found record
#set in case more than one record was found
Go to Layout [ “reportTagDiscovery” (testlearnReportTags) ]
Show Custom Dialog [ Title: "!"; Message: "Deleting this last piece of evidence will delete this page of the report too, do you wish to proceed? If you wish to keep this report page then add new evidence before deleting this evidence."; Buttons: “Cancel”, “Delete” ]
If [ Get ( LastMessageChoice ) = 2 ]
Go to Layout [ “discoveries” (testlearn) ]
Delete Record/Request
[ No dialog ]
Else If [ Get ( LastMessageChoice ) = 1 ]
Set Variable [ $delete ]
Refresh Window
Exit Script [ ]
End If
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
Close Window [ Name: "Report"; Current ﬁle ]
Close Window [ Name: "Recommendations"; Current ﬁle ]
Perform Script [ “EditReport” ]
Exit Script [ ]
End If
#switch back to this layout so don't have reassign
#ﬁelds for inspection layout. (script was written for
#ﬁndings layout)
Go to Layout [ “reportTagDiscovery” (testlearnReportTags) ]
Go to Record/Request/Page [ $record ]
[ No dialog ]
Delete Record/Request
[ No dialog ]
Go to Layout [ “discoveries” (testlearn) ]
#THIS IS DISABLED AND SHOULD EVENTUALLY
#BE DELETED AFTER TESTING. THERE USE TO BE
#A FAVORITE FIELD THAT HAS BEEN REMOVED.
#SEE EARLIER VERSIONS FOR HOW THIS FUNCTIONED.
#IN SHORT, IT DID WHAT MAKE INFO BUTTON
#NOW DOES.
// #If this is a favorite item and it is the only one then delete the report page created for it.
// If [ testlearnReportTags::ktestSubject + testlearnReportTags::kreportNumber ≠ $$contact + $$reportNumber ]
// Enter Find Mode [ ]
// Set Field [ testlearn::ktest; $$item ]
January 7, 平成26 12:49:45 Imagination Quality Management.fp7 - reportDeleteEvidence -1-testScreens: test: reportDeleteEvidence
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
// #reﬁnd all location records for this session
// Enter Find Mode [ ]
// Set Field [ tagTestSubjectLocation::knode; $$contact ]
// Set Field [ tagTestSubjectLocation::reportNumber; $$reportNumber ]
// Set Field [ tagTestSubjectLocation::ksection; $$Library ]
// Perform Find [ ]
// Go to Layout [ “step3_InspectionItems” (InspectItems) ]
// If [ InspectItems::kgaudienceLocation = $TempLocation ]
// Set Field [ InspectItems::gprogressGlobal; "status: pending" ]
// End If
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
End If
Go to Layout [ “reportTagDiscovery” (testlearnReportTags) ]
Set Variable [ $delete ]
Refresh Window
January 7, 平成26 12:49:45 Imagination Quality Management.fp7 - reportDeleteEvidence -2-
