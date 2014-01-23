testScreens: test: gotoTestItem
#
#Set both a variable and temp ﬁeld with item ID
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
#Set detail temp ﬁelds for use on Tag Menus window.
Set Field [ TEMP::ktestItemList; InspectItems::ktestItemList ]
Set Field [ TEMP::ktestItemListOLD; InspectItems::ktestItemList ]
#
#Prevent test records from loading to speed up
#this script.
Set Variable [ $$stopLoadTestRecord; Value:1 ]
#
#This ﬁeld does show up elsewhere but I am not
#sure after what it does. My bad for not making
#thorough comments during earlier developement.
Set Field [ InspectItems::glocationNameGlobal;
TextStyleAdd ( TEMP::LocationName ; Lowercase ) ]
#
#ﬁnd and show all test records.
Go to Layout [ “step4_InspectionFinding” (testlearn) ]
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ testlearn::ktestSubject; $$contact ]
Set Field [ testlearn::ktest; $$item ]
Set Field [ testlearn::kcsection; $$library ]
Set Field [ testlearn::kreportNumber; $$reportNumber ]
Perform Find [ ]
#
#Create new test record if there are none.
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
Sort Records [ Speciﬁed Sort Order: testlearn::Location; ascending
testlearn::_Number; ascending ]
[ Restore; No dialog ]
#
#Omit all NA, OK, and star records if any (these
#records function as visual indicators of having
#made a decision not to create a test record
#because NA = it was not applicable, OK=it was
#ﬁne, and star symbol = because a test record
#already created duplicates the ﬁnding in this
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
Select Window [ Name: "Tag Menus"; Current ﬁle ]
Perform Script [ “menuTestItem” ]
January 7, 平成26 12:26:37 Imagination Quality Management.fp7 - gotoTestItem -1-testScreens: test: gotoTestItem
#
#Return focus to Test window.
Select Window [ Name: "Test"; Current ﬁle ]
January 7, 平成26 12:26:37 Imagination Quality Management.fp7 - gotoTestItem -2-
