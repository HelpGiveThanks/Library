January 15, 2018 15:15:40 Library.fmp12 - testSubsectionNA -1-
test: test: testSubsectionNA
#
If [ $$stopLoadingTestSubSection = 1 ]
Set Variable [ $$stopLoadingTestSubSection ]
Exit Script [ ]
End If
#
#If node is currenlty locked then stop script,
#and inform the user.
Perform Script [ “stopNewRecordsBeingCreatedByLockedNode” ]
#
#This script creates test a result that is not
#shown as a test result.
# Instead, this record is used to show an
#N/A or OK next to a test subsection to indicate
#that this subsection does not apply or doesn't
#require evidence of results to indicate that it is
#OK. If the user decides to not show the OK or
#N/A, then this script deletes this test result
#record, which enables the display of the N/A
#or OK on the test subsection menu layout.
#
#
#basic administration tasks
Set Error Capture [ On ]
Allow User Abort [ Off ]
If [ testResultsTestSection::_Ltestlearn = "" ]
Freeze Window
New Window [ Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
#note item's ID number and name
Set Variable [ $$testSubsection; Value:testSubsectionForSubject::_LtestSubsection ]
Set Variable [ $$testSubsectionName; Value:testSubsectionForSubject::name ]
Set Field [ TEMP::testSubsectionName ]
Go to Layout [ “testSCRIPTloops” (testlearn) ]
New Record/Request
Set Field [ testlearn::ktestSubject; TEMP::kdefaultNodeTestSubject ]
Set Field [ testlearn::ktestSection; $$testSection ]
Set Field [ testlearn::kreportNumber; $$reportNumber ]
Set Field [ testlearn::subsectionCustomName; $$testSectionName ]
Set Field [ testlearn::ktestSubsection; $$testSubsection ]
#lock item location so it cannot be deleted unless all findings for it are deleted
Go to Layout [ “tableTestSectionFromTemplate” (testSectionCreatedFromATemplate) ]
Enter Find Mode [ ]
Set Field [ testSectionCreatedFromATemplate::_LtestSection; $$testSection ]
Perform Find [ ]
Set Field [ testSectionCreatedFromATemplate::inUse; "t" ]
#refind all location records for this session
Enter Find Mode [ ]
Set Field [ testSectionCreatedFromATemplate::ktestSubjectNode; TEMP::kdefaultNodeTestSubject ]
Perform Find [ ]
Go to Layout [ “testingSubsectionMenu” (testSubsectionForSubject) ]
Set Field [ testResultsTestSection::countOfONESubsectionsTestResults; "N/A" ]
Set Field [ testSubsectionForSubject::gprogressGlobal; "status: in progress" ]
Go to Field [ ]
Close Window [ Current Window ]
Set Variable [ $$stopLoadingTestSubSection ]
Exit Script [ ]
Else If [ testResultsTestSection::countOfONESubsectionsTestResults = "" and
testResultsTestSection::_Ltestlearn ≠ "" ]
Set Field [ testResultsTestSection::countOfONESubsectionsTestResults; "N/A" ]
Go to Layout [ “testingSubsectionMenu” (testSubsectionForSubject) ]
Set Field [ testSubsectionForSubject::gprogressGlobal; "status: in progress" ]
Set Field [ TEMP::testSubsectionName ]
Go to Field [ ]
Set Variable [ $$stopLoadingTestSubSection ]
Exit Script [ ]
Else If [ testResultsTestSection::countOfONESubsectionsTestResults = "N/A" ]
Set Field [ testResultsTestSection::countOfONESubsectionsTestResults; "OK" ]
Go to Layout [ “testingSubsectionMenu” (testSubsectionForSubject) ]
Set Field [ testSubsectionForSubject::gprogressGlobal; "status: in progress" ]
Set Field [ TEMP::testSubsectionName ]
Go to Field [ ]
Set Variable [ $$stopLoadingTestSubSection ]
Exit Script [ ]
Else If [ testResultsTestSection::countOfONESubsectionsTestResults = "N/A" or
testResultsTestSection::countOfONESubsectionsTestResults = "OK" ]
#
#
#Disable star symbol.
// If [ testResultsReportSection::countOfALLSubsectionsTestResults = "" ]
If [ testResultsReportSection::countOfALLSubsectionsTestResults = "" or testResultsReportSection::
countOfALLSubsectionsTestResults ≠ "" ]
Set Field [ TEMP::testSubsectionName ]
// Show Custom Dialog [ Title: "FYI"; Message: "Use the star symbol to referr to other assessment findings. You
currently do not have any for this item."; Default Button: “OK”, Commit: “No” ]
Set Field [ testResultsTestSection::countOfONESubsectionsTestResults; "" ]
Go to Field [ ]
Freeze Window
New Window [ Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”;
Resize: “Yes” ]
#note item's ID number and name
Set Variable [ $$testSubsection; Value:testSubsectionForSubject::_LtestSubsection ]
#
Go to Layout [ “testSCRIPTloops” (testlearn) ]
Enter Find Mode [ ]
Set Field [ testlearn::ktestSubject; TEMP::kdefaultNodeTestSubject ]
Set Field [ testlearn::ktestSection; $$testSection ]
Set Field [ testlearn::ktestSubsection; $$testSubsection ]
Perform Find [ ]
#
Delete Record/Request
[ No dialog ]
#Unlock Item Location
Enter Find Mode [ ]
Set Field [ testlearn::ktestSubject; TEMP::kdefaultNodeTestSubject ]
Set Field [ testlearn::ktestSection; $$testSection ]
Perform Find [ ]
#
If [ Get ( LastError ) = 401 ]
Go to Layout [ “tableTestSectionFromTemplate” (testSectionCreatedFromATemplate) ]
Enter Find Mode [ ]
Set Field [ testSectionCreatedFromATemplate::_LtestSection; $$testSection ]
Perform Find [ ]
Set Field [ testSectionCreatedFromATemplate::inUse; "" ]
#refind all location records for this session
Enter Find Mode [ ]
Set Field [ testSectionCreatedFromATemplate::ktestSubjectNode; TEMP::kdefaultNodeTestSubject ]
Perform Find [ ]
Go to Layout [ “testingSubsectionMenu” (testSubsectionForSubject) ]
#
Set Field [ testSubsectionForSubject::gprogressGlobal; "status: pending" ]
End If
Close Window [ Current Window ]
Set Variable [ $$stopLoadingTestSubSection ]
Exit Script [ ]
End If
Set Field [ testResultsTestSection::countOfONESubsectionsTestResults; "̣" ]
Go to Layout [ “testingSubsectionMenu” (testSubsectionForSubject) ]
Set Field [ testSubsectionForSubject::gprogressGlobal; "status: in progress" ]
Go to Field [ ]
Set Variable [ $$stopLoadingTestSubSection ]
Exit Script [ ]
Else If [ testResultsTestSection::countOfONESubsectionsTestResults ≠ "N/A" and
testResultsTestSection::countOfONESubsectionsTestResults ≠ "OK" and
testResultsTestSection::countOfONESubsectionsTestResults ≠ "̣" ]
Set Field [ TEMP::testSubsectionName ]
Go to Layout [ “testingSubsectionMenu” (testSubsectionForSubject) ]
Set Field [ testSubsectionForSubject::gprogressGlobal; "status: in progress" ]
Go to Field [ ]
Set Variable [ $$stopLoadingTestSubSection ]
Exit Script [ ]
End If
Freeze Window
New Window [ Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
#note item's ID number and name
Set Variable [ $$testSubsection; Value:testSubsectionForSubject::_LtestSubsection ]
Set Field [ TEMP::testSubsectionName ]
Go to Layout [ “testSCRIPTloops” (testlearn) ]
Enter Find Mode [ ]
Set Field [ testlearn::ktestSubject; TEMP::kdefaultNodeTestSubject ]
Set Field [ testlearn::ktestSection; $$testSection ]
Set Field [ testlearn::ktestSubsection; $$testSubsection ]
Perform Find [ ]
Delete Record/Request
[ No dialog ]
#Unlock Item Location
Enter Find Mode [ ]
Set Field [ testlearn::ktestSubject; TEMP::kdefaultNodeTestSubject ]
Set Field [ testlearn::ktestSection; $$testSection ]
Perform Find [ ]
If [ Get ( LastError ) = 401 ]
Go to Layout [ “tableTestSectionFromTemplate” (testSectionCreatedFromATemplate) ]
Enter Find Mode [ ]
Set Field [ testSectionCreatedFromATemplate::_LtestSection; $$testSection ]
Perform Find [ ]
Set Field [ testSectionCreatedFromATemplate::inUse; "" ]
#refind all location records for this session
Enter Find Mode [ ]
Set Field [ testSectionCreatedFromATemplate::ktestSubjectNode; TEMP::kdefaultNodeTestSubject ]
Perform Find [ ]
Go to Layout [ “testingSubsectionMenu” (testSubsectionForSubject) ]
Set Field [ testSubsectionForSubject::gprogressGlobal; "status: pending" ]
End If
Set Variable [ $$stopLoadingTestSubSection ]
Close Window [ Current Window ]
