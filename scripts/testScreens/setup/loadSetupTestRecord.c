testScreens: setup: loadSetupTestRecord
#
#Stop script if needed to speed up other scripts.
If [ $$ID = test::_Ltest
 or
$$ID = "ignore" ]
Exit Script [ ]
End If
#
#Set all variables needed for performing various
#scripts while in test setup mode.
Go to Field [ ]
Set Variable [ $$ID; Value:test::_Ltest ]
#
#The test item list temp fields allow users to switch
#from their current list to another list.
Set Field [ TEMP::ktestItemList; test::ktestItemList ]
Set Field [ TEMP::ktestItemListOLD; test::ktestItemList ]
#
Set Field [ TEMP::ktest; test::_Ltest ]
Set Field [ TEMP::mTag; TEMP::ktest ]
#
#Used on Tag Menus window item layout for switch.
Set Field [ TEMP::testName; test::testName ]
Set Variable [ $$focuses; Value:test::kcfocusALL ]
#
#
#
#Get the name of the test for the test item list
#name temp field.
#
#The reason for this whole section of the script
#(getting a test name) is that there is no relationship
#that can be made that would match the key of
#of the named test to this test and thus unlock
#and so allow the layout to show this test's name.
#This is because the key to unlock the display of
#a test's name is in a keychain field where many
#keys may exist in a list. Filemaker cannot match
#a lock in one table to list of keys in another table.
#There must be only one key in a field in order
#for Filemaker to know which key to use in a lock.
#The database does not have the intellegence or
#programming to search through a list of keys
#to make a match to a lock field in another table.
#Thus, in order to display the name of the test in use
#we must have the system put that name in a temp
#field with global storage, which then allows it
#to be displayed on any layout where that temp
#field is displayed. No relationship between the
#the temp table and the layout's table is required
#as long as the temp field is a global field, meaning
#all data in the field is the same for every record
#in the temp table.
#
#If the test list belongs (has the key that fits the
#test's lock) the set the temp field with this test's name.
If [ test::_Ltest = test::ktestItemList ]
#
#Set a temp field with this test's name. This name
#field will then be used to show this test's name on
#the Tag Menus layout for setupTestItems.
Set Field [ TEMP::ktestListtTestName; test::testName ]
#
#If the test list does not belong to this test
#(has the key that fits A DIFFERENT test's lock)
#then set the temp field with this other test's name.
Else If [ test::_Ltest ≠ test::ktestItemList ]
#
#Get the ID of the current record so it can be
#looped back to.
Set Variable [ $currentTest; Value:test::_Ltest ]
#
#Turn of the record load triggered script to speed
#up this loop search.
Set Variable [ $$ID; Value:"ignore" ]
#
#Go to the first record and then test it and every
#other record until the test in question is found.
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ test::_Ltest = TEMP::ktestItemList ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Set a temp field with this test's name. This name
#field will then be used to show this test's name on
#the Tag Menus layout for setupTestItems.
Set Field [ TEMP::ktestListtTestName; test::testName ]
#
#Update key used for the move pulldown.
Set Field [ TEMP::mTag; TEMP::ktestItemList ]
#
#go back to current test.
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ test::_Ltest = $currentTest ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
Set Variable [ $$ID; Value:$currentTest ]
Refresh Window
End If
#
#
#
Select Window [ Name: "Tag Menus"; Current file ]
If [ Get (LastError) = 112 ]
New Window [ Name: "Tag Menus"; Height: Get (ScreenHeight); Width: Get (ScreenWidth) / 2; Left: Get (ScreenWidth) / 2 ]
Go to Layout [ “setupTestFocus” (tagLocation) ]
End If
#
#Find test items for test if user is currently looking
#at test items on the Tag Menus window.
If [ Get (LayoutName) = "setupTestItem" ]
Go to Layout [ “setupTestItem” (tagMenus) ]
January 7, 平成26 12:15:41 Imagination Quality Management.fp7 - loadSetupTestRecord -1-testScreens: setup: loadSetupTestRecord
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ ruleTagMenuTestGroups::match; TEMP::ktestItemList & ¶ ]
Perform Find [ ]
#
Sort Records [ Specified Sort Order: ruleTagMenuTestGroups::order; based on value list: “order”
ruleTagMenuTestGroups::name; ascending
ruleTagMenuTestGroups::_Lgroup; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
End If
#
#Refresh window in case user was on focus layout.
Refresh Window
#
#Return to setup window and refresh it to highlight
#current record.
Select Window [ Name: "Setup"; Current file ]
Refresh Window
January 7, 平成26 12:15:41 Imagination Quality Management.fp7 - loadSetupTestRecord -2-
