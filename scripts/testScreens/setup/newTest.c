testScreens: setup: newTest
#
#If node is currenlty locked then stop script, inform user.
If [ TEMP::nodeLock ≠ "" ]
Show Custom Dialog [ Message: "The default record creation node -- " & TEMP::DEFAULTNodePrimaryName & " -- is locked. Select this node in the setuptag window and enter the password to unlock it so that you can create new records attributed to it."; Buttons: “OK” ]
Exit Script [ ]
End If
#
#Stop spell check script.
Set Variable [ $$stopTest; Value:1 ]
#
#If there are no tests, then create a new test
#group ﬁrst and then a test for that group.
#All tests belong to a test groups.
If [ Get (FoundCount) = 0 ]
Perform Script [ “newTestGroup” ]
Exit Script [ ]
End If
#
#Set variables needed to create new item.
Set Variable [ $$ID; Value:"ignore" ]
Set Variable [ $group; Value:test::ktestGroup ]
#
#new test
New Record/Request
Set Field [ test::ksection; TEMP::ksection ]
#( a test group ﬁeld is neccessary because a section
# may have more than one test group, and so trying
# to ﬁnd a test group using the section key and
# the testGroup match ﬁeld would ﬁnd all groups
# when we need the system to ﬁnd one group. )
Set Field [ test::ktestGroup; $group ]
#
#A new test-item list is created with each new test.
#This key ﬁeld can be changed so that the test-item
#list for another test can be used.
Set Field [ test::ktestItemList; test::_Ltest ]
#
#Tests do not need unique names. Unlike other
#names, the names of tests if named the same
#will not confuse the system. I don't think it will
#confuse the user either, but I am including steps to
#require a unique name so when locked name can
#be revereted back to orignal name.
Set Field [ test::testName; "test" ]
Set Field [ test::testNameRevert; "test" ]
Set Field [ test::kRecordCreatorNode; TEMP::kdefaultNodePrimary ]
#
#
#
#Set temp variables for next part of script.
#
#The test item list temp ﬁelds allow users to switch
#from their current list to another list.
Set Field [ TEMP::ktestItemList; test::ktestItemList ]
Set Field [ TEMP::ktestItemListOLD; test::ktestItemList ]
#
#Used on tag menus to unlock buttons and link
#new records to test.
Set Field [ TEMP::ktest; test::_Ltest ]
#
#Used on Tag Menus window item layout for switch.
Set Field [ TEMP::testName; test::testName ]
#
#Used on Tag Menus window focus layout for conditional
#formatting.
Set Variable [ $$focuses; Value:test::kcfocusALL ]
#
#
#Go to the tag menus window.
Select Window [ Name: "Tag Menus"; Current ﬁle ]
If [ Get (LastError) = 112 ]
New Window [ Name: "Tag Menus"; Height: Get (ScreenHeight); Width: Get (ScreenWidth) / 2; Left: Get (ScreenWidth) / 2 ]
Go to Layout [ “setupTestFocus” (tagLocation) ]
End If
#
#Remember layout user is currently seeing in
#the tag menu window, so user can be returned
#to it at the end of the script.
Set Variable [ $layout; Value:Get (LayoutName) ]
#
#Assign focus to test item as each test must have
#at least one focus.
Perform Script [ “editSectionFocuses” ]
Go to Record/Request/Page
[ First ]
Perform Script [ “linkTestFocusOrUnlinkTestFocus” ]
#
// #Create test item as each test must have at least
// #one test item.
// Set Variable [ $$stopLoadTagRecord; Value:1 ]
// Perform Script [ “menuTestItem” ]
// Perform Script [ “newTestItemGroup” ]
// Set Field [ tagMenus::tag; "test item" ]
// Go to Field [ ]
#
#Go to selected tag menu window layout.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Select Window [ Name: "Tag Menus"; Current ﬁle ]
Set Variable [ $$stopLoadTagRecord ]
Go to Layout [ $layout ]
#
#Set variables for new record.
Select Window [ Name: "setup"; Current ﬁle ]
Set Variable [ $$ID; Value:test::_Ltest ]
#
#Sort records.
Sort Records [ Speciﬁed Sort Order: ruleSection::name; ascending
groupTest::order; based on value list: “order”
groupTest::name; ascending
test::order; based on value list: “order”
test::testName; ascending ]
[ Restore; No dialog ]
Go to Field [ test::testName ]
[ Select/perform ]
#
#Start spell check script.
Set Variable [ $$stopTest ]
January 7, 平成26 12:16:43 Imagination Quality Management.fp7 - newTest -1-
