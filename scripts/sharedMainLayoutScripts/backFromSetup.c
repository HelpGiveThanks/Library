sharedMainLayoutScripts: backFromSetup
Set Error Capture [ On ]
Allow User Abort [ Off ]
#
#Insure that all locked fields are revereted back if changed.
Select Window [ Name: "Tag Menus"; Current file ]
Perform Script [ “insureEqualityOfSpellFields” ]
Select Window [ Name: "Setup"; Current file ]
Perform Script [ “insureEqualityOfSpellFields” ]
#
#Return to default setup module from...
If [ Left ( $$module ; 1 ) = "l" ]
Perform Script [ “backToLearnOrDefaultSetup” ]
Select Window [ Name: "Tag Menus"; Current file ]
Go to Layout [ “learnMenu1” (tagMenus) ]
Perform Script [ “menuTest” ]
Set Variable [ $$module ]
Exit Script [ ]
Else If [ Left ( $$module ; 1 ) = "d" ]
#
#For returning from the test setup module, find
#and delete all temp records that may have been
#created while setuping up or deleting tests and
#then create one new temp record to show the user
#the default selections from the global fields whose
#contents cannot be deleted even when all records
#containing them are deleted. With a new record
#any info in their global fields will go into a
#newly created record.
Go to Layout [ “defaultSetup” (tempSetup) ]
Show All Records
Delete All Records
[ No dialog ]
New Record/Request
Go to Field [ ]
#
#Return to test setup layout on the Tag Menus
#window, and clear the global fields needed for
#creating and deleting tests in the test setup module.
Select Window [ Name: "Tag Menus"; Current file ]
Go to Layout [ “defaultTest” (tagTestSubjectLocation) ]
Set Field [ TEMP::ktest; "" ]
Set Field [ TEMP::ktestItemList; "" ]
Set Field [ TEMP::ktestItemListOLD; "" ]
Set Field [ TEMP::ktestListtTestName; "" ]
#
#Refind all test sections and sort them.
Allow User Abort [ Off ]
Set Error Capture [ On ]
Enter Find Mode [ ]
Set Field [ tagTestSubjectLocation::ksection; TEMP::ksection ]
Perform Find [ ]
#
#Sort
Sort Records [ Specified Sort Order: tagTestSubject::tag; ascending
tagTestSubjectLocation::reportNumber; ascending
tagTestSubjectLocation::order; based on value list: “order”
tagTestSubjectLocation::focusName; ascending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
#
Exit Script [ ]
End If
Perform Script [ “returnToSetup” ]
December 11, ଘ౮27 11:36:58 Library.fp7 - backFromSetup -1-
