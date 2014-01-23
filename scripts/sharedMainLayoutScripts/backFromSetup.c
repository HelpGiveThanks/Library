sharedMainLayoutScripts: backFromSetup
Set Error Capture [ On ]
Allow User Abort [ Off ]
#
#Insure that all locked ﬁelds are revereted back if changed.
Select Window [ Name: "Tag Menus"; Current ﬁle ]
Perform Script [ “insureEqualityOfSpellFields” ]
Select Window [ Name: "Setup"; Current ﬁle ]
Perform Script [ “insureEqualityOfSpellFields” ]
#
#Return to default setup module from...
If [ Left ( $$module ; 1 ) = "l" ]
Perform Script [ “backToLearnOrDefaultSetup” ]
Select Window [ Name: "Tag Menus"; Current ﬁle ]
Go to Layout [ “learnMenu1” (tagMenus) ]
Perform Script [ “menuTest” ]
Set Variable [ $$module ]
Exit Script [ ]
Else If [ Left ( $$module ; 1 ) = "d" ]
#
#For returning from the test setup module, ﬁnd
#and delete all temp records that may have been
#created while setuping up or deleting tests and
#then create one new temp record to show the user
#the default selections from the global ﬁelds whose
#contents cannot be deleted even when all records
#containing them are deleted. With a new record
#any info in their global ﬁelds will go into a
#newly created record.
Go to Layout [ “defaultSetup” (tempSetup) ]
Show All Records
Delete All Records
[ No dialog ]
New Record/Request
Go to Field [ ]
#
#Return to test setup layout on the Tag Menus
#window, and clear the global ﬁelds needed for
#creating and deleting tests in the test setup module.
Select Window [ Name: "Tag Menus"; Current ﬁle ]
Go to Layout [ “defaultTest” (tagTestSubjectLocation) ]
Set Field [ TEMP::ktest; "" ]
Set Field [ TEMP::ktestItemList; "" ]
Set Field [ TEMP::ktestItemListOLD; "" ]
Set Field [ TEMP::ktestListtTestName; "" ]
Exit Script [ ]
End If
Perform Script [ “returnToSetup” ]
January 7, 平成26 18:06:26 Imagination Quality Management.fp7 - backFromSetup -1-
