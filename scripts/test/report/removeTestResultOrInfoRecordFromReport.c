January 15, 2018 15:57:16 Library.fmp12 - removeTestResultOrInfoRecordFromReport -1-
test: report: removeTestResultOrInfoRecordFromReport
#
#If user is trying to clear a blank field
#stop the script
If [ Get (ActiveFieldContents) = "" ]
Go to Field [ ]
Halt Script
End If
#
#
#Copy tag record's key; then clear it
#from its current slot.
Set Variable [ $clear; Value:Get ( ActiveFieldContents ) ]
Clear [ ]
[ Select ]
Go to Field [ ]
#
#
#Find this cleared tag record
#in the Tag Menus window.
Select Window [ Name: "Tag Menus"; Current file ]
#
#Turn off record load script.
Set Variable [ $$stopLoadTestResultRecord; Value:1 ]
#
#First, check if record is a test result.
If [ Get (LayoutName) ≠ "reportTestResult" ]
#
#Find all test results for this subsection.
Go to Layout [ “reportTestResult” (testlearnReportTags) ]
Enter Find Mode [ ]
Set Field [ testlearnReportTags::ktestSubject; TEMP::kdefaultNodeTestSubject ]
Set Field [ testlearnReportTags::ktestSubsection; TEMP::ktestSubsection ]
Set Field [ testlearnReportTags::kreportNumber; TEMP::reportNumber ]
Perform Find [ ]
Set Variable [ $$citationMatch; Value:"testResult" ]
#
#Sort based on users current sort for
#test result records.
If [ TEMP::TLTestSort = "" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearnReportTags::date; descending
testlearnReportTags::timestamp; descending ]
[ Restore; No dialog ]
Else
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearnReportTags::orderTestResult; based on value
list: “testPulldownListANDsortOrderList”
testlearnReportTags::timestamp; descending ]
[ Restore; No dialog ]
End If
End If
Go to Field [ ]
#
#If it not selected, find and select it.
If [ $clear ≠ testlearnReportTags::_Ltestlearn ]
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ $clear = testlearnReportTags::_Ltestlearn ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
End If
#
#Turn back on record load script.
Set Variable [ $$stopLoadTestResultRecord ]
#
#If it is a test result record, return to the
#Report window and halt this script allowing
#the user to continue editing the report.
If [ $clear = testlearnReportTags::_Ltestlearn ]
#If it is a test result record, note that
#it is not in use.
Set Field [ testlearnReportTags::kcInUseOnReportSubsection; "" ]
#
Perform Script [ “loadReportTestResultRecord” ]
Refresh Window
#
Select Window [ Name: "Report"; Current file ]
Halt Script
End If
#
#
#
#If it is not a test result record, then it must
#be an info record. Find this record and
#then return to the Report window and halt
#this script.
If [ $clear ≠ testlearnReportTags::_Ltestlearn ]
#
#Turn off record load script and find
#all info records for this test section.
Set Variable [ $$stopPart3InProgress; Value:1 ]
Perform Script [ “reportTagInfo” ]
#
#Find and select cleared test info record.
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ $clear = testlearnReportTags::_Ltestlearn ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Start to remove its key from this info record's
#keychain of pasted info records pasted
#on reports.
Set Variable [ $inUse; Value:testlearnReportTags::kcInUseOnReportSubsection ]
#
#Find out how many times its was used on the
#same report as a user can copy a learn record
#and paste it multiple times.
Set Variable [ $numberOfTimesUsedOnSameReport; Value:ValueCount ( FilterValues ( testlearnReportTags::
kcInUseOnReportSubsection ; $$testSubsection & $$testSubject & $$reportNumber & ¶ ) ) ]
#
#Remove all copies of the key.
Set Field [ testlearnReportTags::kcInUseOnReportSubsection; Substitute ( testlearnReportTags::kcInUseOnReportSubsection ; $
$testSubsection & $$testSubject & $$reportNumber & ¶ ; "" ) ]
Set Variable [ $inUse; Value:testlearnReportTags::kcInUseOnReportSubsection ]
#
#If it was used more than 1 time, put back
#the other copies still in use.
If [ $numberOfTimesUsedOnSameReport - 1 > 0 ]
Set Variable [ $countDown; Value:$numberOfTimesUsedOnSameReport - 1 ]
Loop
Set Field [ testlearnReportTags::kcInUseOnReportSubsection; $inUse & $$testSubsection & $$testSubject & $
$reportNumber & ¶ ]
Set Variable [ $inUse; Value:testlearnReportTags::kcInUseOnReportSubsection ]
Set Variable [ $countDown; Value:$countDown - 1 ]
Exit Loop If [ $countDown = 0 ]
End Loop
End If
#
#Turn back on record load script.
Set Variable [ $$stopPart3InProgress ]
#
#Reset conditional formatting variables, then
#return to the Report window and halt
#this script.
Perform Script [ “loadTestInfo” ]
#
Select Window [ Name: "Report"; Current file ]
Halt Script
End If
#
