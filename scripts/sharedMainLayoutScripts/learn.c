sharedMainLayoutScripts: learn
#basic administration tasks
Set Error Capture [ On ]
Allow User Abort [ Off ]
#
If [ TEMP::ksection = "" ]
Show Custom Dialog [ Message: "Select a section from the Tag Menus window for records that you create to be placed into."; Buttons: “OK” ]
Halt Script
Else If [ tempSetup::kdefaultHealth = "" ]
Show Custom Dialog [ Message: "Select a health/copyright type from the health section."; Buttons: “OK” ]
Halt Script
Else If [ tempSetup::kdefaultNodePrimary = "" ]
Show Custom Dialog [ Message: "Select yourself (the node responsible) from Tag Menus window."; Buttons: “OK” ]
Halt Script
End If
#
#
#Make sure creator node's group is part of section group.
Perform Script [ “addBackSectionCreatorNode” ]
#
Select Window [ Name: "Setup"; Current ﬁle ]
Set Window Title [ Current Window; New Title: "Learn" ]
Set Variable [ $$stoploadCitation; Value:1 ]
If [ tempSetup::layoutLmain = "" ]
Go to Layout [ “learn1” (testlearn) ]
Set Field [ TEMP::layoutLmain; "more" & Get (LayoutName) ]
Else If [ tempSetup::layoutLmain ≠ "" ]
Go to Layout [ Middle ( tempSetup::layoutLmain ; 5 ; 42 ) ]
End If
Enter Find Mode [ ]
#
#now ﬁnd and show all canned inspection items associated with this generic canned location
Set Field [ testlearn::kcsection; TEMP::ksection ]
Set Field [ testlearn::ﬁlterFind; "main" & ¶ ]
Perform Find [ ]
Sort Records [ Speciﬁed Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
Select Window [ Name: "Tag Menus"; Current ﬁle ]
Go to Layout [ “ltagNK2” (tagMenus) ]
Perform Script [ “menuKey” ]
Select Window [ Name: "Learn"; Current ﬁle ]
Set Variable [ $$stoploadCitation ]
Perform Script [ “loadCitation” ]
January 7, 平成26 18:11:10 Imagination Quality Management.fp7 - learn -1-
