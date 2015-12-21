testScreens: test: gotoTestItem
#
#Set both a variable and temp field with item ID
#or Lock number. Eventually need to pick one
#or the other, but due to current deadline that
#cleanup will have to come later.
Set Variable [ $$item; Value:InspectItems::_Ltest ]
Set Field [ TEMP::ktest; InspectItems::_Ltest ]
#
#Set initial test item list to check so when user clicks
#on the button next to an item it turns green instead
#inserting its text into the test discovery's text box.
Set Field [ TEMP::textORcheck; "check" ]
#
#Set detail temp fields for use on Tag Menus window.
Set Field [ TEMP::ktestItemList; InspectItems::ktestItemList ]
Set Field [ TEMP::ktestItemListOLD; InspectItems::ktestItemList ]
#
#Prevent test records from loading to speed up
#this script.
Set Variable [ $$stopLoadTestRecord; Value:1 ]
#
#This field does show up elsewhere but I am not
#sure after what it does. My bad for not making
#thorough comments during earlier developement.
Set Field [ InspectItems::glocationNameGlobal;
TextStyleAdd ( TEMP::LocationName ; Lowercase ) ]
#
#find and show all test records.
Go to Layout [ “step4_InspectionFinding” (testlearn) ]
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ testlearn::ktestSubject; $$contact ]
Set Field [ testlearn::ktest; $$item ]
Set Field [ testlearn::kcsection; $$library ]
Set Field [ testlearn::kreportNumber; $$reportNumber ]
#
#This find range will insure only records with numbers
#will be found (no NA or OK records).
Set Field [ testlearn::InspectionItemCountLocation; "0...99999999999999" ]
Perform Find [ ]
#
#Create new test record if there are none.
If [ Get (FoundCount) = 0 ]
Perform Script [ “newTestRecord (update)” ]
Exit Script [ ]
End If
#
#Group records by test subject location.
Go to Record/Request/Page
[ Last ]
Loop
If [ testlearn::InspectionItemCountLocation = "N/A" or
testlearn::InspectionItemCountLocation = "OK" or
testlearn::InspectionItemCountLocation = "̣" ]
Omit Record
End If
Go to Record/Request/Page
[ Previous; Exit after last ]
End Loop
Sort Records [ Specified Sort Order: testlearn::Location; ascending
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
Exit Loop If [ testlearn::kaudienceLocation = $$Location ]
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
Perform Script [ “loadTestRecord” ]
Set Variable [ $$testItem; Value:testlearn::kctestItem ]
#
#Find all details for this item.
Select Window [ Name: "Tag Menus"; Current file ]
Perform Script [ “menuTestItem” ]
#
#Return focus to Test window.
Select Window [ Name: "Test"; Current file ]
#
December 21, ଘ౮27 13:57:31 Library.fp7 - gotoTestItem -1-
