January 15, 2018 17:09:05 Library.fmp12 - defaultCopyrightMenu -1-
tagMenu: defaultCopyrightMenu
#
#Insure user selects a default node first, so
#they get credit if they want to create any
#copyright records, as the default node
#is the creator of all new records.
If [ tempSetup::kdefaultNodePrimary = "" ]
Show Custom Dialog [ Message: "Select yourself (the node responsible for creating new records) by clicking the node button.";
Default Button: “OK”, Commit: “No” ]
Halt Script
End If
#
#Set citationMatch to color menu button with inUse color.
Set Variable [ $$citationMatch; Value:"copyright" ]
Select Window [ Name: "Setup"; Current file ]
Set Variable [ $$citationitem; Value:tempSetup::kdefaultCopyright ]
Set Field [ TEMP::mTag; "copyright" ]
Refresh Window
Select Window [ Name: "Tag Menus"; Current file ]
#
#Turn off the loadtagrecord script to speed up the
#loop portion of the script.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Set Variable [ $$stopTest; Value:1 ]
#
#Speed up script by going to layout with no
#pictures to load.
Go to Layout [ “ltagNK1” (tagMenus) ]
#
#Find all node records.
Allow User Abort [ Off ]
Set Error Capture [ On ]
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
#Goto correct layout.
Go to Layout [ “defaultCopyright” (tagMenus) ]
#
#Turn loadtagrecord script back on.
Set Variable [ $$stopLoadTagRecord ]
Set Variable [ $$stopTest ]
#
#Inform user of items use on both screens.
Perform Script [ “loadTagRecord” ]
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
