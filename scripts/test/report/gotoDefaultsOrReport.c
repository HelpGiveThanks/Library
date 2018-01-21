January 15, 2018 15:48:49 Library.fmp12 - gotoDefaultsOrReport -1-
test: report: gotoDefaultsOrReport
#
#Select window Learn, in case the user clicked
#the back button on the Test Tag Menu.
Select Window [ Name: "Learn"; Current file ]
#
#
#
#Set in copyAndpastTags script.
Set Variable [ $$copyAndpastTagsRECORD ]
#
#Clear main record node lock variable.
Set Variable [ $$lockedMainLearnRecord ]
#
#Determine what module is active and then go
#to the setup module if ...
If [ $$learnRecord = "" and $$testTagRecord = "" ]
#
#If user is in tag field and has changed spelling
#exit this tag record, otherwise current reference record
#will get deleted by the spelling check script.
Select Window [ Name: "Tag Menus"; Current file ]
Go to Field [ ]
#
#Check for any dragged changes to tag spellings.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Go to Layout [ “ltagSCRIPTloops” (tagMenus) ]
Show All Records
Set Variable [ $$stopLoadTagRecord ]
Perform Script [ “CHUNKcheckForDragPasteChanges (update)” ]
#
#Go to default tags layout
#and load up defaults.
Perform Script [ “defaultsAll (update)” ]
#
#Change main window to Setup.
Select Window [ Name: "References"; Current file ]
Select Window [ Name: "Learn"; Current file ]
Set Window Title [ Current Window; New Title: "Setup" ]
Move/Resize Window [ Current Window; Height: Get (ScreenHeight); Width: Get (ScreenWidth) / 2; Top: 0; Left: 0 ]
Go to Layout [ “defaultSetup” (librarySetupReferenceMain) ]
#
#Clear variables that where set
#in other modules.
Go to Field [ ]
Set Variable [ $$citationitem; Value:tempSetup::klibrary ]
Set Variable [ $$citationMatch ]
Set Variable [ $$node ]
Set Variable [ $$tagBrainstorm ]
Set Variable [ $$tagTest ]
Set Variable [ $$citationRecord ]
Set Variable [ $$primaryNode ]
Set Variable [ $$medium ]
Set Variable [ $$copyright ]
Set Variable [ $$Path ]
Set Variable [ $$cite ]
Set Variable [ $$ref ]
Set Variable [ $$PrimaryKey ]
Set Variable [ $$Key ]
Set Variable [ $$OtherKey ]
Set Variable [ $$RecordID ]
#
Set Field [ TEMP::ktestSubsection; "" ]
#
Set Variable [ $$findMode ]
Set Variable [ $$firstFind ]
Set Variable [ $$firstFindOther ]
Set Variable [ $$found ]
Set Variable [ $$foundOther ]
Set Variable [ $$findLayout ]
Exit Script [ ]
#
#
#
Else If [ $$learnRecord ≠ "" and $$testTagRecord = "" ]
Set Window Title [ Current Window; New Title: "Report" ]
Go to Layout [ “PrintReportEdit” (report) ]
Scroll Window
[ Home ]
#
Enter Find Mode [ ]
Set Field [ report::ktestSubject; $$testSubject ]
Set Field [ report::kreportNumber; $$reportNumber ]
Set Field [ report::ktestSubsection; $$returnItem ]
Perform Find [ ]
Sort Records [ Keep records in sorted order; Specified Sort Order: report::ktestSubsection; ascending ]
[ Restore; No dialog ]
#
View As
[ View as List ]
Scroll Window
[ Home ]
#
#Just in case user went to a different item before
#returning to this item, put the item being tested
#back in the temp field.
Set Field [ TEMP::ktestSubsection; $$returnItem ]
Set Field [ TEMP::testSubsectionName; $$returnItemName ]
#
#If user is in tag field and has changed spelling
#exit this tag record, otherwise current reference record
#will get deleted by the spelling check script.
Select Window [ Name: "Tag Menus"; Current file ]
Go to Field [ ]
#
#Check for any dragged changes to tag spellings.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Go to Layout [ “ltagSCRIPTloops” (tagMenus) ]
Show All Records
Set Variable [ $$stopLoadTagRecord ]
Perform Script [ “CHUNKcheckForDragPasteChanges (update)” ]
#
#Now find discoveries for this report item.
Set Variable [ $$stoploadtestinfo; Value:1 ]
Go to Layout [ “reportTagInfo” (testlearnReportTags) ]
Perform Script [ “reportTagInfo (update)” ]
#
#Clear this variable, which is needed only
#when going to edit Learn info records.
If [ TEMP::InventoryLibraryYN = "" ]
Set Variable [ $$doNotOpenReferenceWindow ]
End If
#
#Now go the test record the user was on.
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ testlearnReportTags::_Ltestlearn = $$learnRecord ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
Set Variable [ $$stoploadtestinfo ]
Set Variable [ $$returnItem ]
Set Variable [ $$learnRecord ]
Perform Script [ “loadTestInfo (update)” ]
#
Else If [ $$learnRecord = "" and $$testTagRecord ≠ "" ]
Set Window Title [ Current Window; New Title: "Test" ]
#
#Prevent test records from loading to speed up
#this script.
Set Variable [ $$stopLoadTestRecord; Value:1 ]
#
#find and show all test records.
Go to Layout [ “testResult0” (testlearn) ]
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ testlearn::ktestSubject; $$testSubject ]
Set Field [ testlearn::ktestSubsection; $$returnItem ]
Set Field [ testlearn::kreportNumber; $$reportNumber ]
Perform Find [ ]
#
#Just in case user went to a different item before
#returning to this item, put the item being tested
#back in the temp field.
Set Field [ TEMP::ktestSubsection; $$returnItem ]
Set Field [ TEMP::testSubsectionName; $$returnItemName ]
#
#This field does show up elsewhere but I am not
#sure after what it does. My bad for not making
#thorough comments during earlier developement.
Set Field [ testSubsectionForSubject::gtestSectionNameGlobal;
TextStyleAdd ( TEMP::testSubsectionNameForSubject ; Lowercase ) ]
#
#Create new test record if there are none.
#( I know, there where records here when the
# the user went to edit them, but the user
# could have deleted all of them, so it makes
# to leave this step in for in case that unlikely
# thing happened ).
If [ Get (LastError) = 401 ]
Perform Script [ “newTestResult (update name change newTestRecord)” ]
#
#If there is OK or NA record, change it into a test
#record. (NA and OK records tell the user they
#have inspected an item and found it OK or not
#needing to be tested. If OK, the user has decided
#not to record any details. So a record exist
#but it is not being used to record details.
#These next steps will turn that non-test record
#into a test record.)
Else If [ Get (FoundCount) = 1 and $$testSection = testlearn::ktestSection and testlearn::kreportNumber = $$reportNumber and
testlearn::countOfONESubsectionsTestResults = "N/A" or
Get (FoundCount) = 1 and $$testSection = testlearn::ktestSection and testlearn::kreportNumber = $$reportNumber and
testlearn::countOfONESubsectionsTestResults = "OK" or
Get (FoundCount) = 1 and $$testSection = testlearn::ktestSection and testlearn::kreportNumber = $$reportNumber and
testlearn::countOfONESubsectionsTestResults = "̣" ]
#
#If there is OK or NA record, change it into a test
#by change NA or OK to 1, as in 1 test record.
Set Field [ testlearn::countOfONESubsectionsTestResults; 1 ]
#
#increase number of test records for item overall
#from zero to 1.
Set Field [ testlearn::countOfALLSubsectionsTestResults; 1 ]
Go to Layout [ “testResult0” (testlearn) ]
End If
#
#Group records by test subject location.
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::subsectionCustomName; ascending
testlearn::_Number; ascending ]
[ Restore; No dialog ]
#
#Omit all NA, OK, and star records if any (these
#records function as visual indicators of having
#made a decision not to create a test record
#because NA = it was not applicable, OK=it was
#fine, and star symbol = because a test record
#already created duplicates the finding in this
#test subject location),
Go to Record/Request/Page
[ First ]
Loop
If [ testlearn::countOfONESubsectionsTestResults = "N/A" or
testlearn::countOfONESubsectionsTestResults = "OK" or
testlearn::countOfONESubsectionsTestResults = "̣" ]
Omit Record
Go to Record/Request/Page
[ Previous ]
End If
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Now go the test record the user was on.
Go to Record/Request/Page
[ Last ]
Loop
Exit Loop If [ testlearn::_Ltestlearn = $$testLearnRecord ]
Go to Record/Request/Page
[ Previous; Exit after last ]
End Loop
#
#Set the numbers for the navigation arrows
#at the top of the screen: record # / total #.
Set Field [ testlearn::recordnumberglobal; Get (RecordNumber) ]
Set Field [ testlearn::recordcountglobal; Get (FoundCount) ]
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
#Conditionally format current test record and tags.
Set Variable [ $$sopLoadTestRecord ]
Perform Script [ “loadTestResultRecord (update name change loadTestRecord)” ]
#
#Find all details for this item.
Select Window [ Name: "Tag Menus"; Current file ]
Perform Script [ “reportTagInfo (update)” ]
#
#Clear this variable, which is needed only
#when going to edit Learn info records.
If [ TEMP::InventoryLibraryYN = "" ]
Set Variable [ $$doNotOpenReferenceWindow ]
End If
#
#Now go the test record the user was on.
Set Variable [ $$stoploadtestinfo; Value:1 ]
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ testlearnReportTags::_Ltestlearn = $$testTagRecord ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Load up the current records variables.
Set Variable [ $$stoploadtestinfo ]
Perform Script [ “loadTestInfo (update)” ]
#
#Clear the variables specific to this script.
Set Variable [ $$returnItem ]
Set Variable [ $$testTagRecord ]
Set Variable [ $$testLearnRecord ]
#
End If
