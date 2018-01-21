January 15, 2018 15:37:36 Library.fmp12 - CHUNK_gotoTestSubsectionViaPulldown -1-
test: report: CHUNK_gotoTestSubsectionViaPulldown
#
#basic administration tasks
Set Error Capture [ On ]
Allow User Abort [ Off ]
Set Field [ TEMP::ktestSection; "" ]
#
#clear the $$finding and $window variables
Set Variable [ $$finding ]
Set Variable [ $$window ]
Set Variable [ $testSubject; Value:report::ktestSubject ]
#
#Determine report page to go to.
If [ $$goToFirstReportPage = "" ]
Set Variable [ $testSubsection; Value:TEMP::ktestSubsection ]
Else
Set Variable [ $testSubsection; Value:$$goToFirstReportPage ]
Set Variable [ $$goToFirstReportPage ]
End If
#
#clear global fields for creating new test result
#records, but put in current timestamp to help
#user understand how info sould be put into
#the timestample field and for easy editing,
#changing date, time, etc.
Set Field [ testlearnReportTags::kgtestSection; "" ]
Set Field [ TEMP::testSubsectionNameForSubject; "" ]
Set Field [ TEMP::TimeStamp; Get ( CurrentTimeStamp ) ]
Enter Find Mode [ ]
Set Field [ report::ktestSubject; $testSubject ]
Set Field [ report::ktestSubsection; $testSubsection ]
Set Field [ report::kreportNumber; $$reportNumber ]
Perform Find [ ]
Sort Records [ Keep records in sorted order; Specified Sort Order: report::ktestSubsection; ascending ]
[ Restore; No dialog ]
#
Set Field [ TEMP::showFavorites; "" ]
Set Field [ TEMP::ktestSubsection; report::ktestSubsection ]
Set Variable [ $$testSubsection; Value:report::ktestSubsection ]
Set Field [ TEMP::ktestItemSubsection; report::ktestSubsection ]
Set Field [ TEMP::ktestItemSubsection; reportSubsection::ktestItemGroup ]
Set Field [ TEMP::testSubsectionName; reportSubsection::name ]
#
#Close info reference window if open.
Close Window [ Name: "Reference"; Current file ]
#
Select Window [ Name: "Tag Menus"; Current file ]
If [ Get (LastError) = 112 ]
New Window [ Name: "Tag Menus"; Height: Get ( ScreenHeight ); Width: 330; Left: 0; Style: Document; Close: “Yes”; Minimize:
“Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
End If
#
#Resize window just in case user was looking
#at a test info record with references.
Move/Resize Window [ Name: "Tag Menus"; Current file; Width: Get (ScreenWidth) - 594; Left: 594 ]
#
#See if there are any informational
#(Learn module) records tagged
#to this test subsection.
Go to Layout [ “tableTestLearn” (testlearn) ]
Enter Find Mode [ ]
Set Field [ testlearn::kctestSubsectionInfo; "###" & $$testSubsection ]
Perform Find [ ]
#
#If there are information records, then set this
#variable below to inform the user of this fact
#by highlighting the info button on the
#Test Menus layout.
If [ Get (FoundCount) ≠ 0 ]
Set Variable [ $$thereIsInfoForThisSubsection; Value:1 ]
Else
Set Variable [ $$thereIsInfoForThisSubsection ]
End If
#
#
#Now find test results for this subsection.
Set Variable [ $$stopLoadTestResultRecord; Value:1 ]
Go to Layout [ “reportTestResult” (testlearnReportTags) ]
Enter Find Mode [ ]
Set Field [ testlearnReportTags::ktestSubject; TEMP::kdefaultNodeTestSubject ]
Set Field [ testlearnReportTags::ktestSubsection; TEMP::ktestSubsection ]
Set Field [ testlearnReportTags::kreportNumber; TEMP::reportNumber ]
Perform Find [ ]
#
#Go to the locked layout if the test subject, primary node, or primary nodes creator is locked.
If [ ReportResultTestSubject::orderOrLock ≠ ""
 or
TEMP::primaryNodeIsLocked ≠ ""
//or
//TEMP::primaryNodesCreatorNodeIsLocked ≠ "" ]
Go to Layout [ “reportTestResultLocked” (testlearnReportTags) ]
End If
#
#Sort button script uses the "order" text to tell
#it to perform the next sort by date instead of
#by order number which is the default sort.
Set Variable [ $$citationMatch; Value:"testResult" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearnReportTags::orderTestResult; based on value list:
“testPulldownListANDsortOrderList”
testlearnReportTags::timestamp; descending ]
[ Restore; No dialog ]
#
#Load up test results variables.
Set Variable [ $$stopLoadTestResultRecord; Value:1 ]
Go to Record/Request/Page
[ First ]
#
#Reset test result temp fields.
Set Field [ TEMP::TLTestSort; "order" ]
Set Field [ TEMP::TimeStamp; "" ]
#
#Return to report window.
Select Window [ Name: "Report"; Current file ]
#
#Set subsection lock variable to prevent user
#from going to edit subsection template,
#and hide edit/new button as user cannot edit
#locked subsection info or test-item records.
If [ testSubsectionGroupNodeLock3::orderOrLock ≠ "" or $$testSubjectIsLocked ≠ "" ]
Set Field [ TEMP::testItemMenuShowTheWordLock; "Lock" ]
Else If [ testSubsectionGroupNodeLock3::orderOrLock = "" and $$testSubjectIsLocked = "" ]
Set Field [ TEMP::testItemMenuShowTheWordLock; "" ]
End If
#
#Get name of node who locked subsection.
If [ testSubsectionGroupNodeLock3::orderOrLock ≠ "" ]
Set Variable [ $$testSubsectionIsLocked; Value:testSubsectionGroupNodeLock3::tag ]
Else If [ testSubsectionGroupNodeLock3::orderOrLock = "" ]
Set Variable [ $$testSubsectionIsLocked ]
End If
#
#
