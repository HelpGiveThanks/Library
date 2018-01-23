January 15, 2018 16:20:14 Library.fmp12 - menuCopyright -1-
tagMenu: menuCopyright
#
#Admin tasks.
Allow User Abort [ Off ]
Set Error Capture [ On ]
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
Set Variable [ $$doNotHaltOtherScripts ]
Set Variable [ $$citationMatch; Value:"copyright" ]
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
Set Variable [ $$stopTest; Value:1 ]
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
#
#Find Permission tags. Permission tags are available to all library sections.
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ tagMenus::match; $$citationMatch ]
Perform Find [ ]
#
#Sort to group, textstyle, and then tag,
#so that the 3.0 ND tag comes before the
#4.0 ND tag as it does for all the other Creative
#Commons tags.
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenuGroup::name; ascending
tagMenus::textStyleOrCreatorNodeFlag; ascending
tagMenus::tag; ascending ]
[ Restore; No dialog ]
#
#Go to citation record's current selection or to first record.
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ $$copyright = tagMenus::_Ltag ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
#
#Goto correct layout.
#If in add mode ...
If [ $$add = 1 ]
Go to Layout [ “addMenu1” (tagMenus) ]
#
#If in learn mode ...
Else If [ Left (Get (LayoutName) ; 1) = "l" ]
Go to Layout [ “learnMenuCopyright” (tagMenus) ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “learnMenuSCopyright” (tagMenus) ]
End If
#
#If in reference mode ...
Else If [ Left (Get (LayoutName) ; 1) = "r" ]
Go to Layout [ “ReferenceMenuCopyright” (tagMenus) ]
End If
#
If [ $$copyright ≠ tagMenus::_Ltag ]
Go to Record/Request/Page
[ First ]
#
#Turn loadtagrecord script back on.
Set Variable [ $$stopLoadTagRecord ]
Set Variable [ $$stopTest ]
Perform Script [ “loadTagRecord” ]
Exit Script [ ]
End If
#
#Turn loadtagrecord script back on.
Set Variable [ $$stopLoadTagRecord ]
Set Variable [ $$stopTest ]
#
#Inform user of items use on both screens.
Set Variable [ $$citationItem; Value:tagMenus::_Ltag ]
Perform Script [ “loadTagRecord” ]
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
#
#If in add mode, find only records tagged with
#current $$citationmatch.
If [ $$add = 1 ]
#But, give user option to keep the records currently
#showing in the main window.
Show Custom Dialog [ Message: "In the main window, show only records with pictures and links added to copyright tags, or
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
Set Field [ reference::filterFind; "copyright" ]
Perform Find [ ]
#
#find on learn layout ...
Else If [ Left (Get (LayoutName) ; 1) = "l" ]
Enter Find Mode [ ]
Set Field [ testlearn::filterFind; "copyright" ]
Perform Find [ ]
End If
End If
End If
#
Refresh Window
Select Window [ Name: "Tag Menus"; Current file ]
#
