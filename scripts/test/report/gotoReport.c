January 15, 2018 15:35:28 Library.fmp12 - gotoReport -1-
test: report: gotoReport
#
#
#If there is no report number or test subject
#name, halt the script.
If [ TEMP::reportNumber = "" ]
Go to Field [ TEMP::reportNumber ]
[ Select/perform ]
Halt Script
Else If [ testSectionCreatedFromATemplate::name = "" ]
Halt Script
End If
#
#basic administration tasks
Set Error Capture [ On ]
Allow User Abort [ Off ]
Set Field [ TEMP::ktestSection; "" ]
Set Variable [ $$TSRecordNumber; Value:Get (RecordNumber) ]
Set Variable [ $$stopLoadReportRecord; Value:1 ]
Set Variable [ $$pictureWIndowColor; Value:"report" ]
#
#This variable stops the info button's script in
#the Test and Report sections from opening a
#Reference window, which is useful in idea
#libraries to show references of ideas. In a
#things library, reference records are used as
#location records and each learn record can
#have only one location, so showing a Reference
#window in an inventory library would not be useful.
If [ TEMP::InventoryLibraryYN ≠ "" ]
Set Variable [ $$doNotOpenReferenceWindow; Value:1 ]
Else
Set Variable [ $$doNotOpenReferenceWindow ]
End If
#
#Set subsection lock variable to prevent user
#from going to edit subsection template
#section, and set hide test edit/new button field
#which results in hiding that button, since it
#cannot be used when locked.
If [ testSubjectName::orderOrLock ≠ "" ]
Set Variable [ $$testSubjectIsLocked; Value:testSubjectName::tag ]
Set Field [ tempSetup::testSubjectNodeIsLocked; 1 ]
Else
Set Variable [ $$testSubjectIsLocked ]
Set Field [ tempSetup::testSubjectNodeIsLocked; "" ]
End If
#
#Clear sort so when user click's button it will
#resort records by order number.
Set Field [ TEMP::TLTestSort; "" ]
#
#For correct conditional formatting on report
#info screens, clear the citation variable.
Set Variable [ $$main ]
#
#used for item pulldown selection on report layout
Set Field [ TEMP::kdefaultNodeTestSubject; testSectionCreatedFromATemplate::ktestSubjectNode ]
Set Field [ TEMP::DEFAULTNodeTestSubjectName; testSubjectName::tag ]
Set Field [ TEMP::kabout; TEMP::kdefaultNodeTestSubject ]
Set Variable [ $$testSubject; Value:TEMP::kdefaultNodeTestSubject ]
#
#clear global fields for creating new discovery
#records, but put in current timestamp to help
#user understand how info should be put into
#the timestample field and for easy editing,
#changing date, time, etc.
Set Field [ testlearnReportTags::kgtestSection; "" ]
Set Field [ TEMP::testSubsectionNameForSubject; "" ]
Set Field [ TEMP::TimeStamp; Get ( CurrentTimeStamp ) ]
Set Variable [ $$reportNumber; Value:testSectionCreatedFromATemplate::reportNumber ]
Set Field [ TEMP::reportNumber; testSectionCreatedFromATemplate::reportNumber ]
#
#Get header information.
Set Field [ TEMP::testAndReportMainWindowHeader; tempSetup::userLibraryName & " | " & testSubjectName::tag & " | " & "Report "
& $$reportNumber ]
#
#Change window name to Report.
Set Window Title [ Current Window; New Title: "Report" ]
#
#Resize Report window to fit layout.
Go to Layout [ “PrintReportEdit” (report) ]
Adjust Window
[ Resize to Fit ]
#
#find all report pages first, then sort them alphabetically
#and go to the first records. Use this one to find
#only report records for this item.
Enter Find Mode [ ]
Set Field [ report::ktestSubject; $$testSubject ]
Set Field [ report::kreportNumber; $$reportNumber ]
Perform Find [ ]
If [ Get (LastError) = 401 ]
Perform Script [ “returnToTestSetup” ]
Show Custom Dialog [ Message: "No test results to report on. 1) Click any test button under this report button, and 2) then click
any test sub-section button to create reportable test-result records."; Default Button: “OK”, Commit: “Yes” ]
Set Variable [ $$stopLoadReportRecord ]
Exit Script [ ]
End If
Set Variable [ $$stopLoadReportRecord ]
Sort Records [ Keep records in sorted order; Specified Sort Order: reportSubsection::name; ascending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
#
#Use this first record to find
#only report records for this item.
Set Field [ TEMP::testSubsectionName; reportSubsection::name ]
Set Field [ TEMP::ktestSubsection; report::ktestSubsection ]
Set Field [ TEMP::ktestItemSubsection; report::ktestSubsection ]
Set Variable [ $$testSubsection; Value:report::ktestSubsection ]
Set Variable [ $$first; Value:report::ktestSubsection ]
#
#If the test subject or the primary node is
#locked then go to the locked report layout.
If [ reportTestSubjectLock::orderOrLock = "0"
or
TEMP::primaryNodeIsLocked ≠ ""
// or
//TEMP::primaryNodesCreatorNodeIsLocked ≠ "" ]
Go to Layout [ “PrintReportLock” (report) ]
End If
#
#Now find test results for the report subsection.
Perform Script [ “CHUNK_gotoTestSubsectionViaPulldown” ]
#
