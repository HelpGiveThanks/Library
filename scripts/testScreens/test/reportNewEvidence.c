testScreens: test: reportNewEvidence
#
#basic administration tasks
Set Error Capture [ On ]
Allow User Abort [ Off ]
If [ testlearnReportTags::gkaudienceLocation = "" ]
Show Custom Dialog [ Title: "!"; Message: "Select a test section by 1) clicking on the USE button under a picture or by 2) clicking the test section button (next to new button)."; Buttons: “OK” ]
Halt Script
End If
#
#
New Record/Request
Set Field [ testlearnReportTags::ktestSubject; $$contact ]
Set Field [ testlearnReportTags::kaudienceLocation; TEMP::kuserLocation ]
Set Field [ testlearnReportTags::kcsection; TEMP::ksection ]
Set Field [ testlearnReportTags::kreportNumber; TEMP::reportNumber ]
Set Field [ testlearnReportTags::Location; TEMP::LocationName ]
Set Field [ testlearnReportTags::ktest; TEMP::ktest ]
Set Field [ testlearnReportTags::timestamp; TEMP::TimeStamp ]
Set Field [ testlearn::kRecordCreatorNode; TEMP::kdefaultNodePrimary ]
Set Field [ testlearn::RecordModifyDate; Get ( CurrentTimeStamp ) ]
Set Field [ testlearn::kHealth; TEMP::kdefaultHealth ]
#
#note the new record id so when after you sort the
#the records you will be able to put the focus back on
#this newly created record in a loop at the end of this script.
Set Variable [ $kpn; Value:testlearnReportTags::_Ltestlearn ]
#
#increase number of ﬁndings for item for this contact's location
Go to Layout [ “discoveries” (testlearn) ]
Enter Find Mode [ ]
Set Field [ testlearn::ktestSubject; $$contact ]
Set Field [ testlearn::kaudienceLocation; $$location ]
Set Field [ testlearn::ktest; $$item ]
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
#increase number of ﬁndings for item
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
#lock item location so it cannot be deleted unless all ﬁndings for it are deleted
Go to Layout [ “tableTestSubjectFocus” (tagTestSubjectLocation) ]
Enter Find Mode [ ]
Set Field [ tagTestSubjectLocation::_LtestSubjectLocation; $$location ]
Perform Find [ ]
Set Field [ tagTestSubjectLocation::inUse; "t" ]
#
#reﬁnd all location records for this session
Enter Find Mode [ ]
Set Field [ tagTestSubjectLocation::knode; $$contact ]
Set Field [ tagTestSubjectLocation::ksection; $$Library ]
Set Field [ tagTestSubjectLocation::reportNumber; $$ReportNumber ]
Perform Find [ ]
Go to Layout [ original layout ]
Sort Records [ Speciﬁed Sort Order: testlearnReportTags::Location; ascending
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
January 7, 平成26 12:49:13 Imagination Quality Management.fp7 - reportNewEvidence -1-
