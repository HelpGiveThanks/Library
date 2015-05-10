tagMenu: menuNode #
#If user is in tag field and has changed spelling
#exit this tag record, otherwise current reference record
#will get deleted by the spelling check script.
Go to Field [ ] #
#Clear sample and test tags so there conditional
#formatting in the Learn window is removed.
If [ $$citationMatch = "sample" or $$citationMatch = "test" ]
Select Window [ Name: "Learn"; Current file ]
Go to Field [ ]
Set Variable [ $$citationItem; Value:testlearn::kNodePrimary ]
Set Variable [ $$tagSample ]
Set Variable [ $$tagtest ]
Set Variable [ $$tagRecordID ]
Set Variable [ $$tagEdit ] #
#Sort the records by date field, if current sort is
#by order number.
If [ TEMP::TLTestSort = "order" or TEMP::TLSampleSort = "order" ]
Sort Records [ Specified Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
#
#Set the sort preference field to date.
If [ $$citationMatch = "sample" ]
Set Field [ TEMP::TLSampleSort; "" ]
Else If [ $$citationMatch = "test" ]
Set Field [ TEMP::TLTestSort; "" ]
End If #
End If
End If
Select Window [ Name: "Tag Menus"; Current file ] #
#Set citationMatch to color menu button with inUse color.
Set Variable [ $$citationMatch; Value:"node" ] #
#Set match temp tag field to limit move pulldown
#to just the groups for this section and item type.
#( if you're wondering why this temp field is a
# a dupllicate of the citation match variable it
# is because I didn't need it until a year into
# writing this database. At some point, it would
# probably be good to get rid of the variable. )
Set Field [ TEMP::mTag; $$citationMatch ] #
#Do not load tag records until the end of script
#to prevent flashing of window and to speed up
#script.
Set Variable [ $$stopLoadTagRecord; Value:1 ] #
#Goto correct layout.
#If in add mode ...
If [ $$add = 1 ]
Go to Layout [ “addMenuNodeKeyword” (tagMenus) ] #
#If user has elected to show only the tag ...
Else If [ TEMP::layoutRtagN = "" or TEMP::layoutLtagN = "" ]
If [ Left (Get (LayoutName) ; 1) = "l" ]
Go to Layout [ “ltagNK2” (tagMenus) ]
If [ TEMP::InventoryLibaryYN
≠ "" ]
Go to Layout [ “ltagNKs2” (tagMenus) ]
End If
Set Field [ TEMP::layoutLtagN; "more" & Get (LayoutName) ]
Else If [ Left (Get (LayoutName) ; 1) = "r" ]
Go to Layout [ “ReferenceMenu2keywordOrNode1” (tagMenus) ]
Set Field [ TEMP::layoutRtagN; "more" & Get (LayoutName) ]
End If #
#If user has elected to show some pictures ...
Else If [ TEMP::layoutRtagN
≠ "" or TEMP::layoutLtagN
≠ "" ]
If [ Left (Get (LayoutName) ; 1) = "l" ]
Go to Layout [ Middle ( TEMP::layoutLtagN ; 5 ; 42 ) ]
Else If [ Left (Get (LayoutName) ; 1) = "r" ]
Go to Layout [ Middle ( TEMP::layoutRtagN ; 5 ; 42 ) ]
End If
End If #
#Find node tags.
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ tagMenus::match; $$citationMatch ]
Set Field [ ruleTagMenuGroups::ksection; "==" & TEMP::ksection ]
Perform Find [ ] #
// #If no records exist then create one.
// If [ Get (FoundCount)=0 ]
// Perform Script [ “newCitationMenuGroup” ]
// End If #
#Sort according to current users wishes. By default
#the sort will be by category which is set by editCitation script.
If [ TEMP::sortNode = "cat" or TEMP::sortNode = "" ]
Sort Records [ Specified Sort Order: ruleTagMenuGroups::order; based on value list: “order”
ruleTagMenuGroups::name; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Else If [ TEMP::sortNode = "abc" ]
Sort Records [ Specified Sort Order: tagMenus::tag; ascending ]
[ Restore; No dialog ]
End If #
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
May 4, 平成27 21:34:25 Library.fp7 - menuNode -1-
tagMenu: menuNode
#in this mode when both might be needed.
// #If user was in Add mode for keyword, then reset
// #mode back to citation mode (or adding node
// #tags to citations instead of the other way around).
// If [ $$add = 1 and $$addcitationMatch = "key" ]
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
Loop
Exit Loop If [ $$primarykey = tagMenus::_Ltag ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
If [ $$primarykey ≠ tagMenus::_Ltag ]
Go to Record/Request/Page
[ First ]
End If
#
#Decided this override of above loop is to confusing
#and the proper way to do keep record user wants
#to add to in focus is to open a third window.
#I'm not doing that for now.
// #If in add mode then go to addRecord.
// If [ $$add = 1 ]
// Go to Record/Request/Page
[ First ]
// Loop
// Exit Loop If [ $$addRecordID = tagMenus::_Ltag ]
// Go to Record/Request/Page
[ Next; Exit after last ]
// End Loop
// End If
#
#Inform user of items use on both screens.
Set Variable [ $$stopLoadTagRecord ]
Perform Script [ “loadTagRecord” ]
#
#Just in case user was in nonTag field on this
#window when user clicked a menu button on
#the other window, exit all fields.
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
Go to Field [ ]
Set Variable [ $$citationItem; Value:testlearn::kNodePrimary ]
Set Variable [ $$tagSample ]
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
Show Custom Dialog [ Message: "In the main window, show only records with pictures and links added to node tags, or keep the current records shown?"; Buttons: “keep”, “show” ]
If [ Get ( LastMessageChoice ) = 1 ]
Refresh Window
Select Window [ Name: "Tag Menus"; Current file ]
Exit Script [ ]
End If
#
#find on reference layout ...
If [ Left (Get (LayoutName) ; 1) = "r" ]
Enter Find Mode [ ]
Set Field [ reference::kcsection; TEMP::ksection ]
Set Field [ reference::filterFind; "node" ]
Perform Find [ ]
#
#find on learn layout ...
Else If [ Left (Get (LayoutName) ; 1) = "l" ]
Enter Find Mode [ ]
Set Field [ testlearn::kcsection; TEMP::ksection ]
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
May 4, 平成27 21:34:25 Library.fp7 - menuNode -2-
