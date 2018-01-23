January 15, 2018 16:24:02 Library.fmp12 - menuMedium -1-
tagMenu: menuMedium
#
#
#Clear brainstorm and test tags so there conditional
#formatting in the Learn window is removed.
If [ $$citationMatch = "brainstorm" or $$citationMatch = "test" ]
Select Window [ Name: "Learn"; Current file ]
Go to Field [ ]
Set Variable [ $$tagBrainstorm ]
Set Variable [ $$tagtest ]
Set Variable [ $$tagRecordID ]
Set Variable [ $$tagEdit ]
End If
Sort Records [ Keep records in sorted order; Specified Sort Order: testlearn::date; descending
testlearn::timestamp; descending ]
[ Restore; No dialog ]
#
#Conditionally format Tag Menu button.
Select Window [ Name: "Tag Menus"; Current file ]
Set Variable [ $$citationMatch; Value:"medium" ]
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
#Turn off the loadtagrecord script to speed up the
#loop portion of the script.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
#
#Goto correct layout.
#If in add mode ...
If [ $$add = 1 ]
Go to Layout [ “addMenu1” (tagMenus) ]
#
#If in learn mode ...
Else If [ Left (Get (LayoutName) ; 1) = "l" ]
Go to Layout [ “learnMenu1” (tagMenus) ]
#
#If in reference mode ...
Else If [ Left (Get (LayoutName) ; 1) = "r" ]
Go to Layout [ “ReferenceMenu1” (tagMenus) ]
End If
#
#Find medium tags. Medium tags are available to all library sections.
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
If [ TEMP::sortMedium = "cat" or TEMP::sortMedium = "" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenuGroup::orderOrLibraryType; based on value list:
“order Pulldown List”
tagMenuGroup::name; ascending
tagMenus::orderOrLock; based on value list: “order Pulldown List”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Else If [ TEMP::sortMedium = "abc" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenus::tag; ascending ]
[ Restore; No dialog ]
End If
#
#Go to citation record's current selection or to first record.
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ $$medium = tagMenus::_Ltag ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Turn loadtagrecord script back on.
Set Variable [ $$stopLoadTagRecord ]
#
If [ $$medium ≠ tagMenus::_Ltag ]
Go to Record/Request/Page
[ First ]
// Exit Script [ ]
End If
#
#Inform user of items use on both screens.
Set Variable [ $$citationItem; Value:tagMenus::_Ltag ]
Refresh Window
#
#Just in case user was in nonTag field on this
#window when user clicked a menu button on
#the other window, exit all fields.
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
Go to Field [ ]
Else If [ Get (LastError) ≠ 112 ]
Go to Field [ ]
#
#If in add mode, find only records tagged with
#current $$citationmatch.
If [ $$add = 1 ]
#
#But, give user option to keep the records currently
#showing in the main window.
Show Custom Dialog [ Message: "In the main window, show only records with pictures and links added to medium tags, or
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
Set Field [ reference::filterFind; "medium" ]
Perform Find [ ]
#
#find on learn layout ...
Else If [ Left (Get (LayoutName) ; 1) = "l" ]
Enter Find Mode [ ]
Set Field [ testlearn::filterFind; "medium" ]
Perform Find [ ]
End If
End If
End If
Refresh Window
Select Window [ Name: "Tag Menus"; Current file ]
