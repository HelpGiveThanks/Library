January 15, 2018 16:18:07 Library.fmp12 - menuNode -1-
tagMenu: menuNode
#
#Prevent halting of script.
Set Variable [ $$doNotHaltOtherScripts; Value:1 ]
#
#If user is in tag field and has changed spelling
#exit this tag record, otherwise current reference record
#will get deleted by the spelling check script.
Go to Field [ ]
#
#Clear brainstorm and test tags so there conditional
#formatting in the Learn window is removed.
If [ $$citationMatch = "brainstorm" or $$citationMatch = "test" ]
Select Window [ Name: "Learn"; Current file ]
Go to Field [ ]
Set Variable [ $$citationItem; Value:testlearn::kNodePrimary ]
Set Variable [ $$tagBrainstorm ]
Set Variable [ $$tagtest ]
Set Variable [ $$tagRecordID ]
Set Variable [ $$tagEdit ]
#
#Sort the records by date field, if current sort is
#by order number.
If [ TEMP::TLTestSort = "order" or TEMP::TLBrainstormSort = "order" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
#
#Set the sort preference field to date.
If [ $$citationMatch = "brainstorm" ]
Set Field [ TEMP::TLBrainstormSort; "" ]
Else If [ $$citationMatch = "test" ]
Set Field [ TEMP::TLTestSort; "" ]
End If
#
End If
End If
#
#Conditionally format Tag Menu button.
Select Window [ Name: "Tag Menus"; Current file ]
Set Variable [ $$citationMatch; Value:"node" ]
#
#Set match temp tag field to limit move pulldown
#to just the groups for this section and item type.
#( if you're wondering why this temp field is a
# a dupllicate of the citation match variable it
# is because I didn't need it until a year into
# writing this database. At some point, it would
# probably be good to get rid of the variable. )
Set Field [ TEMP::mTag; $$citationMatch ]
#
#Do not load tag records until the end of script
#to prevent flashing of window and to speed up
#script.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
#
#Speed up script by going to layout with no
#pictures to load.
If [ Left (Get (LayoutName) ; 1) = "l" ]
If [ TEMP::InventoryLibraryYN = "" ]
Go to Layout [ “ltagNK1” (tagMenus) ]
Else
Go to Layout [ “ltagNKs1” (tagMenus) ]
End If
Else
If [ TEMP::InventoryLibraryYN = "" ]
Go to Layout [ “ReferenceMenu2keywordOrNode2” (tagMenus) ]
Else
End If
End If
#
#Find node tags.
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ tagMenus::match; $$citationMatch ]
#
#In Learn section only show creator nodes,
#as these are the only nodes that can create
#or edit learn records.
If [ Left (Get (LayoutName) ; 1) = "l" ]
Set Field [ tagMenus::textStyleOrCreatorNodeFlag; 123456789 ]
End If
Perform Find [ ]
#
#Sort according to current users wishes.
If [ TEMP::sortNode = "cat" or TEMP::sortNode = "" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenuGroup::orderOrLibraryType; based on value list:
“order Pulldown List”
tagMenuGroup::name; ascending
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Else If [ TEMP::sortNode = "abc" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenus::tag; ascending ]
[ Restore; No dialog ]
End If
#
#Decided not do this as user may be going to
#node menus to add an node tag to a citation
#the user is planning on adding to a tag
#which means the user may want to remain in
#add to tag mode when clicking on the node menu
#item. In the first phase of developement
#I thought if the user activitated the add mode
#in either the keyword or node menu that the
#user would not want to see the add button showing
#green in the other window (keyword or node).
#I was trying to keep the add button's on state
#associated only with the menu item where it
#was activitated. This in testing did not seem
#useful at limited access to node or keyword
#in this mode when both might be needed.
// #If user was in Add mode for keyword, then reset
// #mode back to citation mode (or adding node
// #tags to citations instead of the other way around).
// If [ $$add = 1 and $$addcitationMatch = "key" ]
// Perform Script [ “addLinksPicturesToTagsMode (update)” ]
// End If
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
Exit Loop If [ $$primaryNode = tagMenus::_Ltag ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
If [ $$primaryNode ≠ tagMenus::_Ltag ]
Go to Record/Request/Page
[ First ]
End If
#
#Goto correct layout.
#If in add mode ...
If [ $$add = 1 ]
Go to Layout [ “addMenuNodeKeyword” (tagMenus) ]
#
#If user has elected to show only the tag ...
Else If [ TEMP::layoutRtagN = "" and Left (Get (LayoutName) ; 1) = "r" or
TEMP::layoutLtagN = "" and Left (Get (LayoutName) ; 1) = "l" ]
If [ Left (Get (LayoutName) ; 1) = "l" ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “ltagNKs2” (tagMenus) ]
Else
Go to Layout [ “ltagNK2” (tagMenus) ]
End If
Set Field [ TEMP::layoutLtagN; "less" & Get (LayoutName) ]
Else If [ Left (Get (LayoutName) ; 1) = "r" ]
Go to Layout [ “ReferenceMenu2keywordOrNode2” (tagMenus) ]
Set Field [ TEMP::layoutRtagN; "less" & Get (LayoutName) ]
End If
#
#If user has elected to show some pictures ...
Else If [ TEMP::layoutRtagN ≠ "" and Left (Get (LayoutName) ; 1) = "r" or
TEMP::layoutLtagN ≠ "" and Left (Get (LayoutName) ; 1) = "l" ]
If [ Left (Get (LayoutName) ; 1) = "l" ]
Go to Layout [ Middle ( TEMP::layoutLtagN ; 5 ; 42 ) ]
Else If [ Left (Get (LayoutName) ; 1) = "r" ]
Go to Layout [ Middle ( TEMP::layoutRtagN ; 5 ; 42 ) ]
End If
End If
#
#Inform user of items use on both screens.
Set Variable [ $$stopLoadTagRecord ]
Set Variable [ $$doNotHaltOtherScripts; Value:1 ]
Perform Script [ “loadTagRecord (update)” ]
Set Variable [ $$doNotHaltOtherScripts ]
#
#Just in case user was in nonTag field on this
#window when user clicked a menu button on
#the other window, exit all fields.
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
Go to Field [ ]
Set Variable [ $$citationItem; Value:testlearn::kNodePrimary ]
Set Variable [ $$tagBrainstorm ]
Set Variable [ $$tagRecordID ]
Set Variable [ $$tagEdit ]
Else If [ Get (LastError) ≠ 112 ]
#
#If in add mode, find only records tagged with
#current $$citationmatch.
If [ $$add = 1 ]
#
#But, give user option to keep the records currently
#showing in the main window.
Show Custom Dialog [ Message: "In the main window, show only records with pictures and links added to node tags, or
keep the current records shown?"; Default Button: “keep”, Commit: “Yes”; Button 2: “show”, Commit: “No” ]
If [ Get ( LastMessageChoice ) = 1 ]
Refresh Window
Select Window [ Name: "Tag Menus"; Current file ]
Exit Script [ ]
End If
#
#find on reference layout ...
If [ Left (Get (LayoutName) ; 1) = "r" ]
Enter Find Mode [ ]
Set Field [ reference::filterFind; "node" ]
Perform Find [ ]
#
#find on learn layout ...
Else If [ Left (Get (LayoutName) ; 1) = "l" ]
Enter Find Mode [ ]
Set Field [ testlearn::filterFind; "node" ]
Perform Find [ ]
End If
End If
Set Variable [ $$citationItem; Value:reference::knodePrimary ]
End If
Refresh Window
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
#
#Show creator node explanation
#once per session.
If [ $$showCreatorNodemessageOnlyOnce = "" ]
Show Custom Dialog [ Message: "Library setup and learn sections require creator nodes to create and edit records in this library
and to be the subjects of tests. Author nodes are used in the reference section to tag referenced works as their authors.";
Default Button: “OK”, Commit: “Yes” ]
Show Custom Dialog [ Message: "NOTE: Creator nodes are listed in the reference section, where they can be used to tag a
reference as an author. Author nodes are never listed in the setup or learn sections."; Default Button: “OK”, Commit: “Yes” ]
Show Custom Dialog [ Message: "These messages appear only per session. Restart this library to see them again."; Default
Button: “OK”, Commit: “Yes” ]
Set Variable [ $$showCreatorNodemessageOnlyOnce; Value:1 ]
End If
#
