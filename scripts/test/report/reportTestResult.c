January 21, 2018 11:05:28 Library.fmp12 - reportTestResult -1-
test: report: reportTestResult
#
#
#If there are information records, then set this
#variable below to inform the user of this fact
#by highlighting the info button on the
#Test Menus layout, but only if user is on the
#testInfo layout.
If [ Get(LayoutName) = "testInfo" or Get(LayoutName) = "reportTagInfo" ]
If [ Get (FoundCount) ≠ 0 ]
Set Variable [ $$thereIsInfoForThisSubsection; Value:1 ]
Else
Set Variable [ $$thereIsInfoForThisSubsection ]
End If
End If
#
#
#Find all test results for this subsection.
Set Variable [ $$stopLoadTestResultRecord; Value:1 ]
Go to Layout [ “reportTestResult” (testlearnReportTags) ]
Enter Find Mode [ ]
Set Field [ testlearnReportTags::ktestSubject; TEMP::kdefaultNodeTestSubject ]
Set Field [ testlearnReportTags::ktestSubsection; TEMP::ktestSubsection ]
Set Field [ testlearnReportTags::kreportNumber; TEMP::reportNumber ]
Perform Find [ ]
Set Variable [ $$citationMatch; Value:"testResult" ]
#
#
#Go to the locked layout if the primary node
#is locked.
If [ TEMP::primaryNodeIsLocked ≠ ""
// or
// TEMP::primaryNodesCreatorNodeIsLocked ≠ "" ]
Go to Layout [ “reportTestResultLocked” (testlearnReportTags) ]
End If
#
#
#Go to the locked layout if the test subject
#is locked.
If [ ReportResultTestSubject::orderOrLock ≠ "" ]
Go to Layout [ “reportTestResultLocked” (testlearnReportTags) ]
End If
#
#
#Sort based on users current sort for
#test result records.
If [ TEMP::TLTestSort = "" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearnReportTags::date; descending
testlearnReportTags::timestamp; descending ]
[ Restore; No dialog ]
Else
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearnReportTags::orderTestResult; based on value list:
“testPulldownListANDsortOrderList”
testlearnReportTags::timestamp; descending ]
[ Restore; No dialog ]
End If
#
Go to Record/Request/Page
[ First ]
Set Field [ TEMP::TimeStamp; "" ]
Set Variable [ $$main ]
Set Variable [ $$stopLoadTestResultRecord ]
#
#Load up the variables for the current record,
#and if neccessary resize the windows.
Perform Script [ “loadReportTestResultRecord” ]
#
#
