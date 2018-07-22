July 21, 2018 14:16:11 Library.fmp12 - menuKey -1-
tagMenu: menuKey
#
#Prevent halting of script.
Set Variable [ $$doNotHaltOtherScripts; Value:1 ]
#
#Clear brainstorm and test tags so there conditional
#formatting in the Learn window is removed.
Select Window [ Name: "Learn"; Current file ]
Go to Field [ ]
Set Variable [ $$tagBrainstorm ]
Set Variable [ $$tagtest ]
Set Variable [ $$tagRecordID ]
Set Variable [ $$tagEdit ]
If [ $$primaryKey = "" ]
Set Variable [ $firstOtherKeyword; Value:Case ( Middle ( testlearn::OtherKeyWords ; Length ( LeftWords ( testlearn::
OtherKeyWords ; 1 ) ) + 1 ; 1 ) = "," ;
LeftWords ( testlearn::OtherKeyWords ; 1 ) ;
Middle ( testlearn::OtherKeyWords ; Length ( LeftWords ( testlearn::OtherKeyWords ; 2 ) ) + 1 ; 1 ) = "," ;
LeftWords ( testlearn::OtherKeyWords ; 2 ) ;
Middle ( testlearn::OtherKeyWords ; Length ( LeftWords ( testlearn::OtherKeyWords ; 3 ) ) + 1 ; 1 ) = "," ;
LeftWords ( testlearn::OtherKeyWords ; 3 ) ;
Middle ( testlearn::OtherKeyWords ; Length ( LeftWords ( testlearn::OtherKeyWords ; 4 ) ) + 1 ; 1 ) = "," ;
LeftWords ( testlearn::OtherKeyWords ; 4 ) ;
LeftWords ( testlearn::OtherKeyWords ; 5 ) ) ]
End If
#
#Sort the records by date field, if current sort is
#by brainstorm or test order numbers.
If [ $$citationMatch = "brainstorm" or $$citationMatch = "test" ]
If [ TEMP::TLTestSort = 1 or TEMP::TLBrainstormSort = 1 ]
If [ TEMP::InventoryLibraryYN = "" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
Else
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::note; ascending ]
[ Restore; No dialog ]
End If
#
#Set the sort preference field to date.
If [ $$citationMatch = "brainstorm" ]
Set Field [ TEMP::TLBrainstormSort; "" ]
Else If [ $$citationMatch = "test" ]
Set Field [ TEMP::TLTestSort; "" ]
End If
End If
End If
#
#Exit fields in current tag menu to run
#neccessary scripts.
Select Window [ Name: "Tag Menus"; Current file ]
Go to Field [ ]
#
#Conditionally format Tag Menu button.
Set Variable [ $$citationMatch; Value:"key" ]
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
Go to Layout [ “ReferenceMenu2SkeywordOrNode3” (tagMenus) ]
End If
End If
#
#Find key tags for library section if not found.
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ tagMenus::match; $$citationMatch ]
Perform Find [ ]
#
// #If no records exist then create one.
// If [ Get (FoundCount)=0 ]
// Perform Script [ “newTagMenuTagGroup” ]
// End If
#
#Sort according to current users wishes.
If [ TEMP::sortKey = "cat" or TEMP::sortKey = "" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenuGroup::orderOrLibraryType; based on value list:
“order Pulldown List”
tagMenuGroup::name; ascending
tagMenus::orderOrLock; based on value list: “order Pulldown List”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Else If [ TEMP::sortKey = "abc" ]
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
// If [ $$add = 1 and $$addcitationMatch = "node" ]
// Perform Script [ “addLinksPicturesToTagsMode” ]
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
Scroll Window
[ Home ]
If [ $$primaryKey ≠ "" ]
Loop
Exit Loop If [ $$primaryKey = tagMenus::_Ltag ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
Else If [ $firstOtherKeyword ≠ "" ]
Loop
Exit Loop If [ $firstOtherKeyword = LeftWords ( tagMenus::tag ; 5 ) ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
End If
#
#Goto correct layout.
#If in add mode ...
If [ $$add = 1 ]
Go to Layout [ “addMenuNodeKeyword” (tagMenus) ]
#
#If user has elected to show only the tag ...
Else If [ TEMP::layoutRtagK = "" and Left (Get (LayoutName) ; 1) = "r" or
TEMP::layoutLtagK = "" and Left (Get (LayoutName) ; 1) = "l" ]
If [ Left (Get (LayoutName) ; 1) = "l" ]
Go to Layout [ “ltagNK2” (tagMenus) ]
Set Field [ TEMP::layoutLtagK; "less" & Get (LayoutName) ]
Else If [ Left (Get (LayoutName) ; 1) = "r" ]
Go to Layout [ “ReferenceMenu2keywordOrNode2” (tagMenus) ]
Set Field [ TEMP::layoutRtagK; "less" & Get (LayoutName) ]
End If
#
#If user has elected to show some pictures ...
Else If [ TEMP::layoutRtagK ≠ "" and Left (Get (LayoutName) ; 1) = "r" or
TEMP::layoutLtagK ≠ "" and Left (Get (LayoutName) ; 1) = "l" ]
If [ Left (Get (LayoutName) ; 1) = "l" ]
Go to Layout [ Middle ( TEMP::layoutLtagK ; 5 ; 42 ) ]
Else If [ Left (Get (LayoutName) ; 1) = "r" ]
Go to Layout [ Middle ( TEMP::layoutRtagK ; 5 ; 42 ) ]
End If
End If
#
#Inform user of items use on both screens.
Set Variable [ $$stopLoadTagRecord ]
#
#Prevent halting to loadTagRecord script.
Set Variable [ $$doNotHaltOtherScripts; Value:1 ]
Perform Script [ “loadTagRecord” ]
Set Variable [ $$doNotHaltOtherScripts ]
#
#Just in case user was in nonTag field on this
#window when user clicked a menu button on
#the other window, exit all fields.
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
Go to Field [ ]
Set Variable [ $$citationItem; Value:testlearn::kKeywordPrimary ]
Else If [ Get (LastError) ≠ 112 ]
Go to Field [ ]
Set Variable [ $$citationItem; Value:reference::kkeywordPrimary ]
#
#If in add mode, find only records tagged with
#current $$citationmatch.
If [ $$add = 1 ]
#
#But, give user option to keep the records currently
#showing in the main window.
Show Custom Dialog [ Message: "In the main window, show only records with pictures and links added to keyword tags, or
keep the current records shown?"; Default Button: “keep”, Commit: “Yes”; Button 2: “show”, Commit: “No” ]
If [ Get ( LastMessageChoice ) = 1 ]
Refresh Window
Select Window [ Name: "Tag Menus"; Current file ]
Exit Script [ ]
End If
#
#find on learn layout ...
If [ Left (Get (LayoutName) ; 1) = "l" ]
Enter Find Mode [ ]
Set Field [ testlearn::filterFind; "key" ]
Perform Find [ ]
#
#find on reference layout ...
Else If [ Left (Get (LayoutName) ; 1) = "r" ]
Enter Find Mode [ ]
Set Field [ reference::filterFind; "key" ]
Perform Find [ ]
End If
End If
#
End If
Refresh Window
#
Select Window [ Name: "Tag Menus"; Current file ]
Refresh Window
#
#
