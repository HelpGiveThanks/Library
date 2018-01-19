January 15, 2018 15:04:00 Library.fmp12 - gotoTestResults -1-
test: test: gotoTestResults
#
If [ $$stopLoadingTestSubSection = 1 ]
Set Variable [ $$stopLoadingTestSubSection ]
Exit Script [ ]
End If
#
#Do not allow a test that has no results to be
#started if its test subject is locked.
If [ testSubsectionTestSubjectLock::orderOrLock = "0" and testResultsReportSection::countOfALLSubsectionsTestResults = "" ]
Show Custom Dialog [ Message: "The test subject — " & $$testSubjectIsLocked & " — is locked. To unlock, A) go back to the
setup node tag menu. B) Select this test subject. C) Click 'lock' and enter the password."; Default Button: “OK”, Commit:
“Yes” ]
Exit Script [ ]
End If
#
#
#Set both a variable and temp field with item ID
#or Lock number. Eventually need to pick one
#or the other, but due to current deadline that
#cleanup will have to come later.
Set Variable [ $$testSubsection; Value:testSubsectionForSubject::_LtestSubsection ]
Set Field [ TEMP::ktestSubsection; testSubsectionForSubject::_LtestSubsection ]
#
#Set initial test item list to check so when user clicks
#on the button next to an item it turns green instead
#inserting its text into the test discovery's text box.
Set Field [ TEMP::textORcheck; "check" ]
#
#Set detail temp fields for use on Tag Menus window.
Set Field [ TEMP::ktestItemSubsection; testSubsectionForSubject::ktestItemGroup ]
Set Field [ TEMP::ktestItemSubsectionOLD; testSubsectionForSubject::ktestItemGroup ]
#
#Set subsection lock variable to prevent user
#from going to edit subsection template
#section, and set hide test edit/new button field
#which results in hiding that button, since it
#cannot be used when locked.
If [ testSubsectionGroupNodeLock2::orderOrLock ≠ "" ]
Set Variable [ $$testSubsectionIsLocked; Value:testSubsectionGroupNodeLock2::tag ]
Set Field [ TEMP::testItemMenuShowTheWordLock; "Lock" ]
Else If [ testSubsectionGroupNodeLock2::orderOrLock = "" ]
Set Variable [ $$testSubsectionIsLocked ]
Set Field [ TEMP::testItemMenuShowTheWordLock; "" ]
End If
#
#Prevent test records from loading to speed up
#this script.
Set Variable [ $$stopLoadTestRecord; Value:1 ]
#
#This field does show up elsewhere but I am not
#sure after what it does. My bad for not making
#thorough comments during earlier developement.
Set Field [ testSubsectionForSubject::gtestSectionNameGlobal;
TextStyleAdd ( TEMP::testSubsectionNameForSubject ; Lowercase ) ]
#
#Find and show all test records.
If [ TEMP::layoutTmain = "" ]
Set Field [ TEMP::layoutTmain; "moretestResult0" ]
End If
#
#If the test subject or the primary node is
#locked go the locked layout.
If [ testSubsectionTestSubjectLock::orderOrLock = "0"
or
TEMP::primaryNodeIsLocked ≠ ""
// or
//TEMP::primaryNodesCreatorNodeIsLocked ≠ "" ]
Go to Layout [ "testResultLOCKED" & Right ( TEMP::layoutTmain ; 1) ]
Else
Go to Layout [ "testResult" & Right ( TEMP::layoutTmain ; 1) ]
End If
#
#Prevent error messages when no records
#are found.
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
#
#See if there are any informational
#(Learn module) records tagged
#to this test subsection.
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
#Now find all test results for this test in all
#subsections using this subsection template.
Enter Find Mode [ ]
Set Field [ testlearn::ktestSubject; $$testSubject ]
Set Field [ testlearn::ktestSubsection; $$testSubsection ]
Set Field [ testlearn::kreportNumber; $$reportNumber ]
#
#This find range will insure only records with numbers
#will be found (no NA or OK records).
Set Field [ testlearn::countOfONESubsectionsTestResults; "0...99999999999999" ]
Perform Find [ ]
#
#Create new test record if there are none.
If [ Get (FoundCount) = 0 ]
#If node is currenlty locked then stop script,
#and inform the user.
Perform Script [ “stopNewRecordsBeingCreatedByLockedNode (new)” ]
Perform Script [ “newTestResult (update name change newTestRecord)” ]
#
#Find all test items for this test result.
Select Window [ Name: "Tag Menus"; Current file ]
Perform Script [ “menuTestItem (update)” ]
#
#Return to Test window.
Select Window [ Name: "Test"; Current file ]
Exit Script [ ]
End If
#
#Group records by test subject location.
Go to Record/Request/Page
[ Last ]
Loop
If [ testlearn::countOfONESubsectionsTestResults = "N/A" or
testlearn::countOfONESubsectionsTestResults = "OK" or
testlearn::countOfONESubsectionsTestResults = "̣" ]
Omit Record
End If
Go to Record/Request/Page
[ Previous; Exit after last ]
End Loop
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::subsectionCustomName; ascending
testlearn::_Number; ascending ]
[ Restore; No dialog ]
#
#Now go the last test record for this test location
#if any. It will be conditionally formatted green,
#while other location records will be yellow and
#records from other tests for this item will be blue.
#Blue records indicate a favorite record.
Go to Record/Request/Page
[ Last ]
Loop
Exit Loop If [ testlearn::ktestSection = $$testSection ]
Go to Record/Request/Page
[ Previous; Exit after last ]
End Loop
#
#Set the numbers for the navigation arrows
#at the top of the screen: record # / total #.
Set Field [ testlearn::recordnumberglobal; Get (RecordNumber) ]
Set Field [ testlearn::recordcountglobal; Get (FoundCount) ]
#
#Conditionally format current test record and tags.
Set Variable [ $$stopLoadTestRecord ]
Perform Script [ “loadTestResultRecord (update name change loadTestRecord)” ]
Set Variable [ $$loadTestItemRecord; Value:testlearn::kctestResultCheckedItems ]
#
#Find all test items for this test result.
Select Window [ Name: "Tag Menus"; Current file ]
Perform Script [ “menuTestItem (update)” ]
#
#Return to Test window.
Select Window [ Name: "Test"; Current file ]
#
