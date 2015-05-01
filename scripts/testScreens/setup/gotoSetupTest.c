February 17, 2015 15:12:56 Imagination Quality Management.fmp12 - gotoSetupTest -1-
testScreens: setup: gotoSetupTest
#
#Capture record ID so system can return user
#after editing is complete.
Set Variable [ $$recordNumber; Value:Get (RecordNumber) ]
#
#Capture test and test item IDs so system can
#reset them. During edit user may go to a
#different test record, thus changing these temp IDs.
Set Variable [ $$itemID; Value:TEMP::ktest ]
Set Variable [ $$detailID; Value:TEMP::ktestItemList ]
#
#Capture layoutname so system can return user
#after editing is complete.
Set Variable [ $$module; Value:Get (LayoutName) ]
#
#Go to detail tag menu so load item record script
#below will work properly.
Go to Layout [ “setupTestItem” (tagMenus) ]
#
#Set the citation match variable to detail as that
#is the layout the system goes to and that variable
#is needed by the add script if the user should
#click on the add button.
Set Variable [ $$citationMatch; Value:"testItem" ]
#
#Capture record ID so system can return user
#after editing is complete.
Select Window [ Name: "Learn"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Setup"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Test"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Report"; Current file ]
End If
End If
Else If [ Get (LastError) ≠ 112 ]
Set Variable [ $$LearnEdit; Value:testlearn::_Ltestlearn ]
End If
#
#Take user to test setup layout and find all
#test items. If coming from Library Setup window.
Set Variable [ $$ID; Value:"ignore" ]
Go to Layout [ “testSetup” (test) ]
Sort Records [ Keep records in sorted order; Specified Sort Order: groupTest::order; based on value list: “order”
groupTest::name; ascending
test::order; based on value list: “order”
test::testName; ascending ]
[ Restore; No dialog ]
Set Window Title [ Current Window; New Title: "Setup" ]
If [ $$module ≠ "testMenuTestItem" // and $$module ≠ "reportTagItem" ]
Allow User Abort [ Off ]
Set Error Capture [ On ]
Enter Find Mode [ ]
Set Field [ test::ksection; TEMP::ksection ]
Perform Find [ ]
#
#If not test exist, then make sure Tag Menus
#also shows no items.
If [ Get (LastError) = 401 ]
Select Window [ Name: "Tag Menus"; Current file ]
Perform Find [ Specified Find Requests: Find Records; Criteria: tagMenus::_Ltag: “"findNOrecords"” ]
[ Restore ]
Select Window [ Name: "Setup"; Current file ]
Exit Script [ ]
End If
Sort Records [ Keep records in sorted order; Specified Sort Order: groupTest::order; based on value list: “order”
groupTest::name; ascending
test::order; based on value list: “order”
test::testName; ascending ]
[ Restore; No dialog ]
#
#Take user to item user clicked on to edit.
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ TEMP::ktest = test::_Ltest ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
If [ TEMP::ktest ≠ test::_Ltest ]
Go to Record/Request/Page
[ First ]
End If
#
#Conditionally format item and its tags.
Set Variable [ $$ID ]
Perform Script [ “loadSetupTestRecord” ]
Scroll Window
[ Home ]
End If
#
#If coming from the test or report module show
#user the Tag Menus window as they probably
#want to add a new tag.
If [ $$module = "testMenuTestItem" or $$module = "reportTagItem" ]
// If [ $$module = "reportTagItem" ]
Set Variable [ $$ID; Value:"ignore" ]
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ $$item = test::_Ltest ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
Set Variable [ $$ID ]
Perform Script [ “loadSetupTestRecord” ]
// End If
Select Window [ Name: "Tag Menus"; Current file ]
Go to Record/Request/Page [ $$recordNumber ]
[ No dialog ]
End If
