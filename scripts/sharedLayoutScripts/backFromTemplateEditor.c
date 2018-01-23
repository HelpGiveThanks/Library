January 18, 2018 16:02:17 Library.fmp12 - backFromTemplateEditor -1-
sharedLayoutScripts: backFromTemplateEditor
#
// #If the optional 'back' button is clicked in the
// #Tag Menus window it will go to the
// #default Setup windows, then exit the script.
// #This optional 'back' button is visible only
// #when the user goes clicks the edit/new
// #button in the Tags Menu window, so when it
// #is clicked it will return the user to this same
// #Tags Menu window layout.
// If [ Left ( $$module ; 7 ) = "default" and Get ( WindowName ) = "Tag Menus"
or
$$module = "" and Get ( WindowName ) = "Tag Menus" ]
// Exit Script [ ]
// End If
#
#
#Admin tasks.
Set Error Capture [ On ]
Allow User Abort [ Off ]
#
#Clear main record node lock variable.
Set Variable [ $$lockedMainSubsectionRecord ]
#
#Insure that all locked fields are revereted back if changed.
Set Variable [ $$goBackToSetup; Value:1 ]
Select Window [ Name: "Tag Menus"; Current file ]
Perform Script [ “checkTestSectionSubsectionAndItemRecordSpellings” ]
Select Window [ Name: "Test Templates"; Current file ]
Perform Script [ “checkTestSectionSubsectionAndItemRecordSpellings” ]
Set Variable [ $$goBackToSetup ]
#
#Return to Learn module.
If [ Left ( $$module ; 1 ) = "l" ]
Set Variable [ $$citationMatch; Value:"test" ]
Set Variable [ $$testSubsection ]
Perform Script [ “backToLearnOrDefaultSetup” ]
Exit Script [ ]
#
#
#Return to Setup.
Else If [ Left ( $$module ; 1 ) = "d" ]
#
#For returning to the test setup module, find
#and delete all temp records that may have been
#created while setting up or deleting tests and
#then create one new temp record to show the user
#the default selections from the global fields whose
#contents cannot be deleted even when all records
#containing them are deleted. With a new record
#any info in their global fields will go into a
#newly created record.
Select Window [ Name: "Tag Menus"; Current file ]
Go to Layout [ “defaultsAll” (tempSetup) ]
Show All Records
Delete All Records
[ No dialog ]
New Record/Request
Go to Field [ ]
#
#Return to test setup layout on the Tag Menus
#window, and clear the global fields needed for
#creating and deleting tests in the test setup module.
Select Window [ Name: "Test Templates"; Current file ]
Set Window Title [ Current Window; New Title: "Setup" ]
Go to Layout [ “defaultTest” (testSectionCreatedFromATemplate) ]
#
Set Field [ TEMP::ktestSubsection; "" ]
Set Field [ TEMP::ktestItemSubsection; "" ]
Set Field [ TEMP::ktestItemSubsectionOLD; "" ]
Set Field [ TEMP::ktestSubsectionName; "" ]
#
Set Variable [ $$testSubsection ]
#
#Refind all test sections and sort them.
Allow User Abort [ Off ]
Set Error Capture [ On ]
Show All Records
#
#Sort
Sort Records [ Keep records in sorted order; Specified Sort Order: testSubjectName::tag; ascending
testSectionCreatedFromATemplate::reportNumber; descending
testSectionCreatedFromATemplate::order; based on value list: “order Pulldown List”
testSectionCreatedFromATemplate::name; ascending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
#
Exit Script [ ]
End If
#
#
#Return to Report or Test sections.
Perform Script [ “returnToSetup” ]
#
