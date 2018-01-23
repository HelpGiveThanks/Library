January 12, 2018 13:47:43 Library.fmp12 - loadSetupTestSubsection -1-
test: setup: loadSetupTestSubsection
#
#
#Stop script if needed to speed up other scripts.
If [ $$ID = testSubsectionTemplate::_LtestSubsection
 or
$$ID = "ignore"
 or
$$stopDeleteTest = 1
 or
$$goBackToSetup = 1 ]
Exit Script [ ]
End If
#
#Set all variables needed for performing various
#scripts while in test setup mode.
Set Variable [ $$ID; Value:testSubsectionTemplate::_LtestSubsection ]
Set Variable [ $$stopTest; Value:1 ]
Go to Field [ ]
Set Variable [ $$stopTest ]
#
// #Remove section hightlight if turned on.
// Set Variable [ $$setupTestSection ]
#
#Note if record is locked to protect its tags.
If [ testSectionCreatorLock::orderOrLock ≠ "" ]
Set Variable [ $$lockedMainSubsectionRecord; Value:testSectionCreatorLock::tag ]
Else
Set Variable [ $$lockedMainSubsectionRecord ]
End If
#
#Get subsection's group key for the 'move'
#button script.
Set Variable [ $$subsectionGroupOLD; Value:testSubsectionTemplate::ksubsectionGroup ]
#
#The test item list temp fields allow users to switch
#from their current list to another list.
Set Field [ TEMP::ktestItemSubsection; testSubsectionTemplate::ktestItemGroup ]
Set Field [ TEMP::ktestItemSubsectionOLD; testSubsectionTemplate::ktestItemGroup ]
#
Set Field [ TEMP::ktestSubsection; testSubsectionTemplate::_LtestSubsection ]
Set Field [ TEMP::mTag; TEMP::ktestSubsection ]
#
#Used on Tag Menus window item layout for switch.
Set Field [ TEMP::testSubsectionName; testSubsectionTemplate::name ]
Set Variable [ $$subsectionSections; Value:testSubsectionTemplate::kcsections ]
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
#test's lock) then set the temp field with this test's name.
If [ testSubsectionTemplate::_LtestSubsection = testSubsectionTemplate::ktestItemGroup ]
#
#Set a temp field with this test's name. This name
#field will then be used to show this test's name on
#the Tag Menus layout for setupTestItems.
Set Field [ TEMP::ktestSubsectionName; testSubsectionTemplate::name ]
#
#If the test list does not belong to this test
#(has the key that fits A DIFFERENT test's lock)
#then set the temp field with this other test's name.
Else If [ testSubsectionTemplate::_LtestSubsection ≠ testSubsectionTemplate::ktestItemGroup ]
#
#Get the ID of the current record so it can be
#looped back to.
Set Variable [ $currentTest; Value:testSubsectionTemplate::_LtestSubsection ]
#
#Turn of the record load triggered scripts
#to speed up this loop search.
Set Variable [ $$ID; Value:"ignore" ]
Set Variable [ $$stopTest; Value:1 ]
New Window [ Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
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
#Update key used for the move pulldown.
Set Field [ TEMP::mTag; TEMP::ktestItemSubsection ]
#
#go back to current test.
Close Window [ Current Window ]
Set Variable [ $$ID; Value:$currentTest ]
Set Variable [ $$stopTest ]
Refresh Window
End If
#
#If the user has come to this screen from the test item
#window, then the itemName variable needs to be updated.
If [ $$itemName ≠ "" ]
Set Variable [ $$itemName; Value:TEMP::ktestSubsectionName ]
End If
#
Select Window [ Name: "Tag Menus"; Current file ]
If [ Get (LastError) = 112 ]
New Window [ Name: "Tag Menus"; Height: Get (ScreenHeight); Width: Get (ScreenWidth) / 2; Left: Get (ScreenWidth) / 2; Style:
Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom Control Area: “Yes”; Resize: “Yes” ]
Go to Layout [ “setupTestSection” (testSection) ]
End If
#
#Find test items for test if user is currently looking
#at test items on the Tag Menus window.
If [ Get (LayoutName) = "setupTestItem" or Get (LayoutName) = "setupTestItemLOCKED" ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
#
#If subsection is locked go the locked
#versus unlocked layout.
If [ $$lockedMainSubsectionRecord ≠ "" ]
Go to Layout [ “setupTestItemLOCKED” (tagMenus) ]
Else
Go to Layout [ “setupTestItem” (tagMenus) ]
End If
#
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ tagMenuTestItemGroup::match; TEMP::ktestItemSubsection & ¶ ]
Perform Find [ ]
Set Variable [ $$stopLoadTagRecord ]
#
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenuTestItemGroup::orderOrLibraryType; based on value
list: “order Pulldown List”
tagMenuTestItemGroup::name; ascending
tagMenuTestItemGroup::_Lgroup; ascending
tagMenus::orderOrLock; based on value list: “order Pulldown List”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Scroll Window
[ Home ]
Go to Record/Request/Page
[ First ]
#
#
#Ask the user if they would like to see the
#whole test item when they click on one or not
#(they just want to go to that tag record).
If [ $$rememberTestItemChoice ≠ 1 and Get(FoundCount) ≠ 0 ]
Show Custom Dialog [ Message: "Show all a test-item's text when you first click directly on the text, or just go to the
record?"; Default Button: “JustGo”, Commit: “No”; Button 2: “ShowAll”, Commit: “No” ]
#
If [ Get (LastMessageChoice) = 1 ]
Set Variable [ $$showAll ]
#
Else If [ Get (LastMessageChoice) = 2 ]
Set Variable [ $$showAll; Value:1 ]
End If
#
#Ask if user would like their choice to be
#remembered for this session (until the library
#is restarted).
Show Custom Dialog [ Message: "Remember this decision for this session (if yes, you will not be asked again until you
restart the library)?"; Default Button: “Remember”, Commit: “Yes”; Button 2: “Forget”, Commit: “No” ]
#
If [ Get (LastMessageChoice) = 1 ]
Set Variable [ $$rememberTestItemChoice; Value:1 ]
End If
End If
#
#
End If
#
#Refresh window in case user was on section layout.
Refresh Window
#
#Return to setup window and refresh it to highlight
#current record.
Select Window [ Name: "Test Templates"; Current file ]
Refresh Window
#
#
Perform Script [ “exit” ]
#
#Stop dragged spelling changes check. It's too
#annoying. It is run when user leaves the
#template section.
If [ $$module ≠ "testMenuTestItem" and $$module ≠ "reportTagItem" ]
Halt Script
End If
#
