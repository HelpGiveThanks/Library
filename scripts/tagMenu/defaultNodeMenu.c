January 15, 2018 17:07:56 Library.fmp12 - defaultNodeMenu -1-
tagMenu: defaultNodeMenu
#
#Do not load tag records until the end of script
#to prevent flashing of window and to speed up
#script.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
#
#Make sure library's creator node and the
#creator node's group exists.
Perform Script [ “CHUNKcheckCreatorNodeAndPrimaryNode (update move name change addBackSectionCreatorNode)” ]
Set Variable [ $$stopLoadTagRecord; Value:1 ]
#
#Set citationMatch to color menu button with inUse color.
Set Variable [ $$citationMatch; Value:"node" ]
Select Window [ Name: "Setup"; Current file ]
Set Variable [ $$citationitem; Value:tempSetup::kdefaultNodePrimary ]
Set Variable [ $$testSubject; Value:tempSetup::kdefaultNodeTestSubject ]
Set Variable [ $$node; Value:tempSetup::kdefaultNodeOther ]
Set Field [ TEMP::mTag; "node" ]
Refresh Window
Select Window [ Name: "Tag Menus"; Current file ]
#
#Find all node records.
Go to Layout [ “defaultNode1” (tagMenus) ]
Allow User Abort [ Off ]
Set Error Capture [ On ]
Enter Find Mode [ ]
Set Field [ tagMenus::match; $$citationMatch ]
#
#In Seupt section only show creator nodes,
#as these are the only nodes that can create
#or edit library records.
Set Field [ tagMenus::textStyleOrCreatorNodeFlag; 123456789 ]
Perform Find [ ]
#
#Sort according to current users wishes.
If [ TEMP::sortNode = "cat"
 or
TEMP::sortNode = "" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenuGroup::orderOrLibraryType; based on value list:
“order Pulldown List”
tagMenuGroup::name; ascending
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Set Field [ TEMP::sortNode; "cat" ]
Else If [ TEMP::sortNode = "abc" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenus::tag; ascending ]
[ Restore; No dialog ]
End If
#
#
#Go to citation record's current selection or to first record.
#Because user may click anywhere to go to a record
#all keys for all menu items must uploaded
#until one is found that matches and then the
#$$citationItem variable can be set.
#Like when the user clicks in a non field area
#a space between fields that then tells filemaker
#to go that record but not to field belonging to
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
#Go to user's selected menu view.
If [ tempSetup::DefaultmoreORLessLayoutNode = "" ]
Go to Layout [ “defaultNode1” (tagMenus) ]
Set Field [ TEMP::DefaultmoreORLessLayoutNode; "more" & Get (LayoutName) ]
Else If [ tempSetup::DefaultmoreORLessLayoutNode ≠ "" ]
Go to Layout [ Middle ( TEMP::DefaultmoreORLessLayoutNode ; 5 ; 42 ) ]
End If
#
#Inform user of items use on both screens.
Set Variable [ $$stopLoadTagRecord ]
Perform Script [ “loadTagRecord (update)” ]
Refresh Window
#
#
#Just in case user was in nonTag field on this
#window when user clicked a menu button on
#the other window, exit all fields.
Select Window [ Name: "Setup"; Current file ]
Refresh Window
#
#goto Tag Menus window
Select Window [ Name: "Tag Menus"; Current file ]
#
#Inform user node was added back.
If [ $$creatorNodeAddedBack = 1 ]
Show Custom Dialog [ Message: "The creator node for this library was added back. You may change the name but not delete
this node."; Default Button: “OK”, Commit: “Yes” ]
Show Custom Dialog [ Message: "A newly created group was created for this node. Rename this group, or move the node to a
group of your choice."; Default Button: “OK”, Commit: “Yes” ]
Set Variable [ $$creatorNodeAddedBack ]
End If
#
#Show creator node explanation
#once per session.
If [ $$showCreatorNodemessageOnlyOnce = "" ]
Show Custom Dialog [ Message: "Node's created in this Setup section, and in the Learn section of this library, are used to create
and edit all records in this library, while node/author tags created in the Reference section can only be used to tag
Referenced works."; Default Button: “OK”, Commit: “Yes” ]
Show Custom Dialog [ Message: "NOTE: Setup and Learn record creator nodes will also show up in the Reference section,
where they can be used to tag a Reference if it is for a work authored by one or more of this library's creators."; Default
Button: “OK”, Commit: “Yes” ]
Show Custom Dialog [ Message: "This message appears only per session. Restart this library to see it again."; Default Button:
“OK”, Commit: “Yes” ]
Set Variable [ $$showCreatorNodemessageOnlyOnce; Value:1 ]
End If
#
