tagMenu: menuKey
#
#Clear sample and test tags so there conditional
#formatting in the Learn window is removed.
If [ $$citationMatch = "sample" or $$citationMatch = "test" ]
Select Window [ Name: "Learn"; Current ﬁle ]
Go to Field [ ]
Set Variable [ $$tagSample ]
Set Variable [ $$tagtest ]
Set Variable [ $$tagRecordID ]
Set Variable [ $$tagEdit ]
End If
Sort Records [ Speciﬁed Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
Select Window [ Name: "Tag Menus"; Current ﬁle ]
#
#Set citationMatch to color menu button with inUse color.
Set Variable [ $$citationMatch; Value:"key" ]
#
#Set match temp tag ﬁeld to limit move pulldown
#to just the groups for this section and item type.
#( if you're wondering why this temp ﬁeld is a
# a dupllicate of the citation match variable it
# is because I didn't need it until a year into
# writing this database. At some point, it would
# probably be good to get rid of the variable. )
Set Field [ TEMP::mTag; $$citationMatch ]
#
#Do not load tag records until the end of script
#to prevent ﬂashing of window and to speed up
#script.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
#
#Goto correct layout.
#If in add mode ...
If [ $$add = 1 ]
Go to Layout [ “addMenuNodeKeyword” (tagMenus) ]
#
#If user has elected to show only the tag ...
Else If [ TEMP::layoutRtagK = "" or TEMP::layoutLtagK = "" ]
If [ Left (Get (LayoutName) ; 1) = "l" ]
Go to Layout [ “ltagNK2” (tagMenus) ]
Set Field [ TEMP::layoutLtagK; "more" & Get (LayoutName) ]
Else If [ Left (Get (LayoutName) ; 1) = "r" ]
Go to Layout [ “ReferenceMenu2keywordOrNode1” (tagMenus) ]
Set Field [ TEMP::layoutRtagK; "more" & Get (LayoutName) ]
End If
#
#If user has elected to show some pictures ...
Else If [ TEMP::layoutRtagK ≠ "" or TEMP::layoutLtagK ≠ "" ]
If [ Left (Get (LayoutName) ; 1) = "l" ]
Go to Layout [ Middle ( TEMP::layoutLtagK ; 5 ; 42 ) ]
Else If [ Left (Get (LayoutName) ; 1) = "r" ]
Go to Layout [ Middle ( TEMP::layoutRtagK ; 5 ; 42 ) ]
End If
End If
#
#Find key tags for library section.
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ tagMenus::match; $$citationMatch ]
Set Field [ ruleTagMenuGroups::ksection; "==" & TEMP::ksection ]
Perform Find [ ]
#
// #If no records exist then create one.
// If [ Get (FoundCount)=0 ]
// Perform Script [ “newCitationMenuGroup” ]
// End If
#
#Sort according to current users wishes. By default
#the sort will be by category which is set by editCitation script.
If [ TEMP::sortKey = "cat" or TEMP::sortKey = "" ]
Sort Records [ Speciﬁed Sort Order: ruleTagMenuGroups::order; based on value list: “order”
ruleTagMenuGroups::name; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Else If [ TEMP::sortKey = "abc" ]
Sort Records [ Speciﬁed Sort Order: tagMenus::tag; ascending ]
[ Restore; No dialog ]
End If
#
#Decided not do this as user may be going to
#node menus to add an node tag to a citation
#the user is planning on adding to a tag
#which means the user may want to remain in
#add to tag mode when clicking on the node menu
#item. In the ﬁrst phase of developement
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
// Perform Script [ “AddLinksPicturesToTagsMode” ]
// End If
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
Scroll Window
[ Home ]
Loop
Exit Loop If [ $$primaryKey = tagMenus::_Ltag ]
January 7, 平成26 15:57:29 Imagination Quality Management.fp7 - menuKey -1-tagMenu: menuKey
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
If [ $$primaryKey ≠ tagMenus::_Ltag ]
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
End If
#
#Inform user of items use on both screens.
Set Variable [ $$stopLoadTagRecord ]
Perform Script [ “loadTagRecord” ]
#
#Just in case user was in nonTag ﬁeld on this
#window when user clicked a menu button on
#the other window, exit all ﬁelds.
Select Window [ Name: "References"; Current ﬁle ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current ﬁle ]
Go to Field [ ]
Set Variable [ $$citationItem; Value:testlearn::kKeywordPrimary ]
Else If [ Get (LastError) ≠ 112 ]
Go to Field [ ]
Set Variable [ $$citationItem; Value:reference::kkeywordPrimary ]
#
#If in add mode, ﬁnd only records tagged with
#current $$citationmatch.
If [ $$add = 1 ]
#
#But, give user option to keep the records currently
#showing in the main window.
Show Custom Dialog [ Message: "In the main window, show only records with pictures and links added to keyword tags, or keep the current records shown?"; Buttons: “keep”, “show” ]
If [ Get ( LastMessageChoice ) = 1 ]
Refresh Window
Select Window [ Name: "Tag Menus"; Current ﬁle ]
Exit Script [ ]
End If
#
#ﬁnd on learn layout ...
If [ Left (Get (LayoutName) ; 1) = "l" ]
Enter Find Mode [ ]
Set Field [ testlearn::kcsection; TEMP::ksection ]
Set Field [ testlearn::ﬁlterFind; "key" ]
Perform Find [ ]
#
#ﬁnd on reference layout ...
Else If [ Left (Get (LayoutName) ; 1) = "r" ]
Enter Find Mode [ ]
Set Field [ reference::kcsection; TEMP::ksection ]
Set Field [ reference::ﬁlterFind; "key" ]
Perform Find [ ]
End If
End If
#
End If
Refresh Window
#
Select Window [ Name: "Tag Menus"; Current ﬁle ]
Refresh Window
January 7, 平成26 15:57:29 Imagination Quality Management.fp7 - menuKey -2-
