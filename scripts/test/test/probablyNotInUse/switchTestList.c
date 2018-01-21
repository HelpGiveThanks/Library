January 21, 2018 11:33:26 Library.fmp12 - switchTestList -1-
test: test: probablyNotInUse: switchTestList
#
#If the user selected the list currently showing then
#stop the script.
If [ TEMP::ktestItemSubsection = TEMP::ktestItemSubsectionOLD ]
Go to Field [ ]
Exit Script [ ]
End If
#
#switch to the selected test, which may or may
#not have a test-item list.
Allow User Abort [ Off ]
Set Error Capture [ On ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Enter Find Mode [ ]
Set Field [ tagMenuTestItemGroup::match; TEMP::ktestItemSubsection ]
Perform Find [ ]
#
#If there is no list, then inform the user of this fact
#at the end of the script, after the name of the list
#is updated. To do that capture the 401 error message.
If [ Get (LastError) = 401 ]
Set Variable [ $emptyList; Value:1 ]
End If
Set Variable [ $$stopLoadTagRecord ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenuTestItemGroup::orderOrLibraryType; based on value list:
“order Pulldown List”
tagMenuTestItemGroup::_Lgroup; ascending
tagMenus::orderOrLock; based on value list: “order Pulldown List”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
#
#assign newly selected test item list to test
Select Window [ Name: "Setup"; Current file ]
Set Field [ testSubsectionTemplate::ktestItemGroup; TEMP::ktestItemSubsection ]
#
#get the switched-to-test's name.
#
#The reason for this whole section of the script
#(getting a test name) is that there is no relationship
#that can be made that would match the key of
#of the named test to this test and thus unlock
#and so allow the layout to show this test name.
#This is because the key to unlock the display of
#a test's name is in a keychain field where many
#keys may exist in list. Filemaker cannot match
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
#Get the ID of the current record so it can be
#looped back to.
Set Variable [ $currentTest; Value:testSubsectionTemplate::_LtestSubsection ]
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
Exit Loop If [ testSubsectionTemplate::_LtestSubsection = TEMP::ktestItemSubsection ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Set a temp field with this test's name. This name
#field will then be used to show this test's name on
#the Tag Menus layout for setupTestItems.
Set Field [ TEMP::ktestSubsectionName; testSubsectionTemplate::name ]
#
#go back to current test.
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ testSubsectionTemplate::_LtestSubsection = $currentTest ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
Set Variable [ $$ID; Value:$currentTest ]
Refresh Window
#
#make new and old tag keys identical, so when
#a switch is made this copy can be used as the old key
#in the first part of this script. Switching automatically
#replaces the current key with whatever is selected,
#thus the need to preserve a copy now, before a switch is made.
Set Field [ TEMP::ktestItemSubsectionOLD; TEMP::ktestItemSubsection ]
#
#Update key used for the move pulldown to the new test.
Set Field [ TEMP::mTag; TEMP::ktestItemSubsection ]
#
#return to tag layout and show all selected items
Select Window [ Name: "Tag Menus"; Current file ]
Go to Layout [ “setupTestItem” (tagMenus) ]
Scroll Window
[ Home ]
Go to Field [ ]
#
#If list is empty, now tell the user this so they don't
#think the system failed because nothing was found.
If [ $emptyList = 1 ]
Show Custom Dialog [ Message: "This test-item list contains no test items. You are welcome to create new ones."; Default
Button: “OK”, Commit: “No” ]
End If
