January 15, 2018 15:08:39 Library.fmp12 - identifyTestsThatHaveResults -1-
test: test: identifyTestsThatHaveResults
#
#Stop script if user just navigated/clicked
#to this record.
If [ $$stopLoadingTestSubSection = 1 ]
Set Variable [ $$stopLoadingTestSubSection ]
Exit Script [ ]
End If
#
#If there are no test results, exit this script.
If [ testResultsReportSection::countOfALLSubsectionsTestResults = "" ]
Exit Script [ ]
End If
#
#Set variables to conditionally format record to
#to be deleted and to supply name for warning
#messages, and to speed up script.
Set Variable [ $delete; Value:testSubsectionForSubject::_LtestSubsection ]
Refresh Window
Set Variable [ $$tagTest; Value:testSubsectionForSubject::_LtestSubsection ]
Set Variable [ $$ID; Value:"ignore" ]
Set Variable [ $subSection; Value:testSubsectionForSubject::name ]
Go to Field [ ]
Set Variable [ $$stopLoadTestResultRecord; Value:1 ]
Set Variable [ $$stopLoadTestRecord; Value:1 ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Set Variable [ $$stopDeleteTest; Value:1 ]
Set Variable [ $$stopTest; Value:1 ]
#
#Find all test results for every instance of this
#subsection used by this test.
New Window [ Name: " "; Height: 1; Width: 1; Top: -10000; Left: -10000; Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize:
“Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
// New Window [ Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
#
#Insure current test subsection has correct
#number of results.
Go to Layout [ “testSCRIPTloops” (testlearn) ]
Enter Find Mode [ ]
Set Field [ testlearn::ktestSubsection; $$testSubsection ]
Set Field [ testlearn::ktestSubject; $$testSubject ]
Set Field [ testlearn::ktestSection; $$testSection ]
Set Error Capture [ On ]
Allow User Abort [ Off ]
Perform Find [ ]
Go to Record/Request/Page
[ First ]
Set Variable [ $number; Value:Get (FoundCount) ]
Loop
Set Field [ testlearn::countOfONESubsectionsTestResults; $number ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Prepare test result summary layout by deleting
#the last result summaries.
Go to Layout [ “TestResultSections” (TEMP) ]
Show All Records
Delete All Records
[ No dialog ]
#
#Find all current test results in all subsections
#for this subject's test section.
Go to Layout [ “reportTestResult” (testlearnReportTags) ]
Enter Find Mode [ ]
Set Field [ testlearnReportTags::ktestSubsection; $delete ]
Set Field [ testlearnReportTags::ktestSubject; $$testSubject ]
Set Field [ testlearnReportTags::kreportNumber; $$reportNumber ]
#
#This find range will insure only records with numbers
#will be found (no NA or OK records).
Set Field [ testlearnReportTags::countOfONESubsectionsTestResults; "0...99999999999999" ]
Set Error Capture [ On ]
Allow User Abort [ Off ]
Perform Find [ ]
#
#Capture found count to update total upon
#returning to the testing subsection menu.
Set Variable [ $updateTotalTestResults; Value:Get (FoundCount) ]
#
#If test results are found, then tell the
#user on which reports they where found.
If [ Get (FoundCount) ≠ 0 ]
#
Loop
Set Variable [ $useList; Value:testlearnReportTags::countOfONESubsectionsTestResults & " in " &
TextColor( TextStyleAdd ( tagReportTestSubjectSectionNAME::name; "" ) ;RGB(0;0;0)) ]
Set Variable [ $sortBySectionName; Value:tagReportTestSubjectSectionNAME::name ]
Set Variable [ $keepIdenticallySpelledSectionsSeparate; Value:testlearnReportTags::ktestSection ]
Go to Layout [ “TestResultSections” (TEMP) ]
New Record/Request
Set Field [ TEMP::DeleteMessageInTempWindow2[2]; $useList ]
Set Field [ TEMP::DeleteMessageInTempWindow2; $sortBySectionName ]
Set Field [ TEMP::DeleteMessageInTempWindow1; $keepIdenticallySpelledSectionsSeparate ]
Go to Layout [ “reportTestResult” (testlearnReportTags) ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
Go to Layout [ “TestResultSections” (TEMP) ]
Sort Records [ Keep records in sorted order; Specified Sort Order: TEMP::DeleteMessageInTempWindow2; ascending
TEMP::DeleteMessageInTempWindow1; ascending ]
[ Restore; No dialog ]
View As
[ View as List ]
#
#Due to a bug in FM13, window must first be
#moved back into the screen area before the
#calculation of the current screen's
#dimensions can be taken.
Move/Resize Window [ Current Window; Top: 0; Left: 0 ]
Move/Resize Window [ Current Window; Height: Get ( ScreenHeight ); Width: 360; Top: 0; Left: Get ( ScreenWidth ) - ( Get
( ScreenWidth )/2 + 360) ]
Set Field [ TEMP::Message; "Sub-section " & $subSection & " has test results in the following sections of test " &
testSubsectionForSubject::kgreportNumber & "." ]
Pause/Resume Script [ Indefinitely ]
Set Variable [ $$stopLoadingTestSubSection ]
Set Variable [ $$stopLoadTestResultRecord ]
Set Variable [ $$stopLoadTestRecord ]
Set Variable [ $$stopLoadTagRecord ]
Set Variable [ $$stopDeleteTest ]
Set Variable [ $$stopTest ]
Set Variable [ $$tagTest ]
Set Variable [ $$ID; Value:testSubsectionTemplate::_LtestSubsection ]
Else
Set Variable [ $$stopLoadingTestSubSection ]
Set Variable [ $$stopLoadTestResultRecord ]
Set Variable [ $$stopLoadTestRecord ]
Set Variable [ $$stopLoadTagRecord ]
Set Variable [ $$stopDeleteTest ]
Set Variable [ $$stopTest ]
Set Variable [ $$ID; Value:testSubsectionTemplate::_LtestSubsection ]
End If
#
#Close the summary report window, return user
#to the testing sections menu and update the
#total of test results for all subsections in this
#users current test.
Close Window [ Current Window ]
Select Window [ Name: "Test"; Current file ]
Set Field [ testResultsReportSection::countOfALLSubsectionsTestResults; $updateTotalTestResults ]
#
#
