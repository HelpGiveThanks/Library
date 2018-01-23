January 15, 2018 16:41:33 Library.fmp12 - menuPublisher -1-
tagMenu: menuPublisher
#
#
#Prevent halting of script.
Set Variable [ $$doNotHaltOtherScripts; Value:1 ]
#
#If user is in tag field and has changed spelling
#exit this tag record, otherwise current reference record
#will get deleted by the spelling check script.
Go to Field [ ]
#
#Set citationMatch to color menu button with inUse color.
Set Variable [ $$citationMatch; Value:"publisher" ]
Set Variable [ $$doNotHaltOtherScripts ]
#
#Turn off loading tag record script until end.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
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
#Goto correct layout.
#If in add mode ...
If [ $$add = 1 ]
Go to Layout [ “addMenu1” (tagMenus) ]
#
#If not in add mode ...
Else If [ $$add ≠ 1 ]
Go to Layout [ “ReferenceMenu1” (tagMenus) ]
End If
#
#Find publisher's tags.
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ tagMenus::match; $$citationMatch ]
Perform Find [ ]
#
#Sort according to current users wishes.
If [ TEMP::sortPublisher = "cat" or TEMP::sortPublisher = "" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenuGroup::orderOrLibraryType; based on value list:
“order Pulldown List”
tagMenuGroup::name; ascending
tagMenus::orderOrLock; based on value list: “order Pulldown List”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Else If [ TEMP::sortPublisher = "abc" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenus::tag; ascending ]
[ Restore; No dialog ]
End If
#
#Go to citation record's current selection or to first record.
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ $$publisher = tagMenus::_Ltag ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
If [ $$publisher ≠ tagMenus::_Ltag ]
Go to Record/Request/Page
[ First ]
#
#Set this variable to stop conditional formatting
#of unselected first Tag Menus record.
Set Variable [ $$TgotoCitationMenuWithBlankField; Value:1 ]
Else
Set Variable [ $$TgotoCitationMenuWithBlankField ]
End If
#
#Turn on loading tag record script.
Set Variable [ $$stopLoadTagRecord ]
Perform Script [ “loadTagRecord” ]
#
#Inform user of items use on both screens.
Set Variable [ $$citationItem; Value:tagMenus::_Ltag ]
Refresh Window
Select Window [ Name: "References"; Current file ]
#
#If in add mode, find only records tagged with
#current $$citationmatch on reference layout.
#The learn record is never changed.
If [ Left (Get (LayoutName) ; 1) = "r" ]
If [ $$add = 1 ]
#
#But, give user option to keep the records currently
#showing in the main window.
Show Custom Dialog [ Message: "In the main window, show only records with pictures and links added to publisher tags, or
keep the current records shown?"; Default Button: “keep”, Commit: “Yes”; Button 2: “show”, Commit: “No” ]
If [ Get ( LastMessageChoice ) = 1 ]
Refresh Window
Select Window [ Name: "Tag Menus"; Current file ]
Exit Script [ ]
End If
#
#find on reference layout ...
Enter Find Mode [ ]
Set Field [ reference::filterFind; "publisher" ]
Perform Find [ ]
End If
End If
#
#Just in case user was in nonTag field on this
#window when user clicked a menu button on
#the other window, exit all fields.
Go to Field [ ]
Refresh Window
Select Window [ Name: "Tag Menus"; Current file ]
#
