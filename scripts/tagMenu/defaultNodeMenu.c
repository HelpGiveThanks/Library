tagMenu: defaultNodeMenu
#
#A section must be selected before nodes
#can be assigned.
If [ TEMP::ksection = "" ]
Perform Script [ “defaultSectionMenu” ]
Show Custom Dialog [ Message: "All nodes are assigned to a library. You need to go the backup layout in admin mode and type in the words New Library, and then restart this database."; Buttons: “OK” ]
Exit Script [ ]
End If
#
#Make sure creator node's group is part of section group.
Perform Script [ “addBackSectionCreatorNode” ]
#
#Set citationMatch to color menu button with inUse color.
Set Variable [ $$citationMatch; Value:"node" ]
Select Window [ Name: "Setup"; Current ﬁle ]
Set Variable [ $$citationitem; Value:tempSetup::kdefaultNodePrimary ]
Set Variable [ $$testSubject; Value:tempSetup::kdefaultNodeTestSubject ]
Set Variable [ $$node; Value:tempSetup::kdefaultNodeOther ]
Set Field [ TEMP::mTag; "node" ]
Refresh Window
Select Window [ Name: "Tag Menus"; Current ﬁle ]
#
#Find all node records.
If [ tempSetup::DefaultmoreORLessLayoutNode = "" ]
Go to Layout [ “defaultNode1” (tagMenus) ]
Set Field [ TEMP::DefaultmoreORLessLayoutNode; "more" & Get (LayoutName) ]
Else If [ tempSetup::DefaultmoreORLessLayoutNode ≠ "" ]
Go to Layout [ Middle ( TEMP::DefaultmoreORLessLayoutNode ; 5 ; 42 ) ]
End If
Allow User Abort [ Off ]
Set Error Capture [ On ]
Enter Find Mode [ ]
Set Field [ tagMenus::match; $$citationMatch ]
Set Field [ ruleTagMenuGroups::ksection; "==" & TEMP::ksection ]
Perform Find [ ]
#
#Sort according to current users wishes. By default
#the sort will be by category which is set by editCitation script.
If [ TEMP::sortNode = "cat"
 or
TEMP::sortNode = "" ]
Sort Records [ Speciﬁed Sort Order: ruleTagMenuGroups::order; based on value list: “order”
ruleTagMenuGroups::name; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Set Field [ TEMP::sortNode; "cat" ]
Else If [ TEMP::sortNode = "abc" ]
Sort Records [ Speciﬁed Sort Order: ruleTagSectionName::name; ascending
tagMenus::tag; ascending ]
[ Restore; No dialog ]
End If
#
#
#Go to citation record's current selection or to ﬁrst record.
#Because user may click anywhere to go to a record
#all keys for all menu items must uploaded
#until one is found that matches and then the
#$$citationItem variable can be set.
#Like when the user clicks in a non ﬁeld area
#a space between ﬁelds that then tells ﬁlemaker
#to go that record but not to ﬁeld belonging to
#that record.
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ $$citationitem = tagMenus::_Ltag ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
If [ $$citationitem ≠ tagMenus::_Ltag ]
Go to Record/Request/Page
[ First ]
End If
#
#Inform user of items use on both screens.
Set Variable [ $$stopLoadTagRecord ]
Refresh Window
#
#
#Just in case user was in nonTag ﬁeld on this
#window when user clicked a menu button on
#the other window, exit all ﬁelds.
Select Window [ Name: "Setup"; Current ﬁle ]
Refresh Window
#
#goto Tag Menus window
Select Window [ Name: "Tag Menus"; Current ﬁle ]
#
January 28, 平成26 15:54:56 Empty Library copy.fp7 - defaultNodeMenu -1-
