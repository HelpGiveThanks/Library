tagMenu: defaultHealthMenu
#
If [ tempSetup::kdefaultNodePrimary = "" ]
Show Custom Dialog [ Message: "Select yourself (the node responsible) from Tag Menus window."; Buttons: “OK” ]
Halt Script
End If
#Set citationMatch to color menu button with inUse color.
Set Variable [ $$citationMatch; Value:"health" ]
Select Window [ Name: "Setup"; Current ﬁle ]
Set Variable [ $$citationitem; Value:tempSetup::kdefaultHealth ]
Refresh Window
Select Window [ Name: "Tag Menus"; Current ﬁle ]
#
#Find all node records.
Go to Layout [ “defaultHealth” (tagMenus) ]
Allow User Abort [ Off ]
Set Error Capture [ On ]
Enter Find Mode [ ]
Set Field [ tagMenus::match; $$citationMatch ]
Perform Find [ ]
#
#Upate language for locked health tags.
Perform Script [ “CHUNKHealthLockedFields” ]
#
#Sort according to current users wishes. By default
#the sort will be by category which is set by editCitation script.
If [ TEMP::sortHealth = "cat"
 or
TEMP::sortHealth = "" ]
Sort Records [ Speciﬁed Sort Order: ruleTagSectionName::name; ascending
ruleTagMenuGroups::order; based on value list: “order”
ruleTagMenuGroups::name; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Else If [ TEMP::sortHealth = "abc" ]
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
January 7, 平成26 16:15:02 Imagination Quality Management.fp7 - defaultHealthMenu -1-
