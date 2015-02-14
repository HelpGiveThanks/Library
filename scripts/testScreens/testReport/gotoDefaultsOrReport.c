testScreens: testReport: gotoDefaultsOrReport
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
Select Window [ Name: "References"; Current file ]
Select Window [ Name: "Learn"; Current file ]
If [ $$referenceSort = 2 ]
Sort Records [ Specified Sort Order: reference::modifyDate; descending
reference::referenceForReferenceSort; ascending ]
[ Restore; No dialog ]
Else If [ $$referenceSort = "" ]
Sort Records [ Specified Sort Order: tagKeywordPrimary::tag; ascending
reference::referenceForReferenceSort; ascending ]
[ Restore; No dialog ]
Else If [ $$referenceSort = 1 ]
Sort Records [ Specified Sort Order: reference::createDate; descending
reference::referenceForReferenceSort; ascending ]
[ Restore; No dialog ]
End If
#
#Addtotag... script is activated by the load record
#trigger. This script needs to be turned off until
#the section record is looped selected by the user.
Set Variable [ $$stopAddTagToCitation; Value:1 ]
#
Go to Layout [ “defaultSetup” (tempSetup) ]
Show All Records
Delete All Records
[ No dialog ]
New Record/Request
Set Window Title [ Current Window; New Title: "Setup" ]
Move/Resize Window [ Current Window; Height: Get (ScreenHeight); Width: Get (ScreenWidth) / 2; Top: 0; Left: 0 ]
#
#goto Tag Menus window
Select Window [ Name: "Tag Menus"; Current file ]
If [ Get (LastError) = 112 ]
New Window [ Name: "Tag Menus"; Height: Get (ScreenHeight); Width: Get (ScreenWidth) / 2; Top: 0; Left: Get (ScreenWidth) / 2 ]
End If
Select Window [ Name: "Setup"; Current file ]
Set Variable [ $$citationitem; Value:tempSetup::ksection ]
Set Variable [ $$citationMatch; Value:"section" ]
Refresh Window
Go to Field [ ]
Set Variable [ $$node ]
Set Variable [ $$tagSample ]
Set Variable [ $$tagTest ]
Set Variable [ $$citationRecord ]
Set Variable [ $$primaryNode ]
Set Variable [ $$medium ]
Set Variable [ $$health ]
Set Variable [ $$Path ]
Set Variable [ $$cite ]
Set Variable [ $$ref ]
Set Variable [ $$PrimaryKey ]
Set Variable [ $$Key ]
Set Variable [ $$OtherKey ]
Set Variable [ $$RecordID ]
#
Set Field [ TEMP::ktest; "" ]
#
Set Variable [ $$findMode ]
Set Variable [ $$firstFind ]
Set Variable [ $$firstFindOther ]
Set Variable [ $$found ]
Set Variable [ $$foundOther ]
Set Variable [ $$findLayout ]
Select Window [ Name: "Tag Menus"; Current file ]
#
#Set citationMatch to color menu button with inUse color.
Set Variable [ $$citationMatch; Value:"section" ]
#
Go to Layout [ “defaultSections” (ruleSection) ]
Allow User Abort [ Off ]
Set Error Capture [ On ]
Enter Find Mode [ ]
Set Field [ ruleSection::match; "section" ]
Perform Find [ ]
#
Sort Records [ Specified Sort Order: ruleSection::name; ascending ]
[ Restore; No dialog ]
#
#Go to citation record's current selection or to first record.
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ TEMP::ksection = ruleSection::ksection ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
If [ TEMP::ksection ≠ ruleSection::ksection ]
Go to Record/Request/Page
[ First ]
End If
Set Variable [ $$stopAddTagToCitation ]
Perform Script [ “addTagToMainRecord” ]
Refresh Window
Exit Script [ ]
Else If [ $$learnRecord ≠ "" and $$testTagRecord = "" ]
Set Window Title [ Current Window; New Title: "Report" ]
Go to Layout [ “PrintReportEdit” (report) ]
Scroll Window
[ Home ]
#
Enter Find Mode [ ]
Set Field [ report::ktestSubject; $$contact ]
Set Field [ report::kreportNumber; $$reportNumber ]
Set Field [ report::ksection; $$library ]
Set Field [ report::ktest; $$returnItem ]
Perform Find [ ]
Sort Records [ Specified Sort Order: report::ktest; ascending ]
[ Restore; No dialog ]
#
View As
[ View as List ]
Scroll Window
[ Home ]
January 7, 平成26 14:40:27 Imagination Quality Management.fp7 - gotoDefaultsOrReport -1-testScreens: testReport: gotoDefaultsOrReport
#
#Just in case user went to a different item before
#returning to this item, put the item being tested
#back in the temp field.
Set Field [ TEMP::ktest; $$returnItem ]
Set Field [ TEMP::testName; $$returnItemName ]
#
#Now find discoveries for this report item.
Select Window [ Name: "Tag Menus"; Current file ]
Set Variable [ $$stoploadtestinfo; Value:1 ]
Go to Layout [ “reportTagInfo” (testlearnReportTags) ]
Perform Script [ “reportTagInfo” ]
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
Perform Script [ “loadtestinfo” ]
#
Else If [ $$learnRecord = "" and $$testTagRecord ≠ "" ]
Set Window Title [ Current Window; New Title: "Test" ]
#
#Prevent test records from loading to speed up
#this script.
Set Variable [ $$stopLoadTestRecord; Value:1 ]
#
#find and show all test records.
Go to Layout [ “step4_InspectionFinding” (testlearn) ]
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ testlearn::ktestSubject; $$contact ]
Set Field [ testlearn::ktest; $$returnItem ]
Set Field [ testlearn::kcsection; $$library ]
Set Field [ testlearn::kreportNumber; $$reportNumber ]
Perform Find [ ]
#
#Just in case user went to a different item before
#returning to this item, put the item being tested
#back in the temp field.
Set Field [ TEMP::ktest; $$returnItem ]
Set Field [ TEMP::testName; $$returnItemName ]
#
#This field does show up elsewhere but I am not
#sure after what it does. My bad for not making
#thorough comments during earlier developement.
Set Field [ InspectItems::glocationNameGlobal;
TextStyleAdd ( TEMP::LocationName ; Lowercase ) ]
#
#Create new test record if there are none.
#( I know, there where records here when the
# the user went to edit them, but the user
# could have deleted all of them, so it makes
# to leave this step in for in case that unlikely
# thing happened ).
If [ Get (LastError) = 401 ]
Perform Script [ “newTestRecord” ]
#
#If there is OK or NA record, change it into a test
#record. (NA and OK records tell the user they
#have inspected an item and found it OK or not
#needing to be tested. If OK, the user has decided
#not to record any details. So a record exist
#but it is not being used to record details.
#These next steps will turn that non-test record
#into a test record.)
Else If [ Get (FoundCount) = 1 and $$Location = testlearn::kaudienceLocation and testlearn::kreportNumber = $$reportNumber and
testlearn::InspectionItemCountLocation = "N/A" or
Get (FoundCount) = 1 and $$Location = testlearn::kaudienceLocation and testlearn::kreportNumber = $$reportNumber and
testlearn::InspectionItemCountLocation = "OK" or
Get (FoundCount) = 1 and $$Location = testlearn::kaudienceLocation and testlearn::kreportNumber = $$reportNumber and
testlearn::InspectionItemCountLocation = "★" ]
#
#If there is OK or NA record, change it into a test
#by change NA or OK to 1, as in 1 test record.
Set Field [ testlearn::InspectionItemCountLocation; 1 ]
#
#increase number of test records for item overall
#from zero to 1.
Set Field [ testlearn::InspectionItemCount; 1 ]
Go to Layout [ “step4_InspectionFinding” (testlearn) ]
End If
#
#Group records by test subject location.
Sort Records [ Specified Sort Order: testlearn::Location; ascending
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
If [ testlearn::InspectionItemCountLocation = "N/A" or
testlearn::InspectionItemCountLocation = "OK" or
testlearn::InspectionItemCountLocation = "★" ]
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
January 7, 平成26 14:40:27 Imagination Quality Management.fp7 - gotoDefaultsOrReport -2-testScreens: testReport: gotoDefaultsOrReport Go to Record/Request/Page
[ Previous; Exit after last ]
End Loop
#
#Set the numbers for the navigation arrows
#at the top of the screen: record # / total #.
Set Field [ testlearn::recordnumberglobal; Get (RecordNumber) ]
Set Field [ testlearn::recordcountglobal; Get (FoundCount) ]
#
#Conditionally format current test record and tags.
Set Variable [ $$sopLoadTestRecord ]
Perform Script [ “loadTestRecord” ]
#
#Find all details for this item.
Select Window [ Name: "Tag Menus"; Current file ]
Perform Script [ “reportTagInfo” ]
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
Set Variable [ $$stoploadtestinfo ]
Perform Script [ “loadtestinfo” ]
#
#
Set Variable [ $$returnItem ]
Set Variable [ $$testTagRecord ]
Set Variable [ $$testLearnRecord ]
#
End If
January 7, 平成26 14:40:27 Imagination Quality Management.fp7 - gotoDefaultsOrReport -3-
