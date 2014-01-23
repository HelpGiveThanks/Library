tagMenu: menuFind: menuCopyistFind
#
#Set citationMatch to color menu button with inUse color.
Set Variable [ $$citationMatch; Value:"copyist" ]
#
#Goto correct layout.
Go to Layout [ “ReferenceMenuFind” (tagMenus) ]
#
#Find copyist tags. Copyist tags are available to all library sections.
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ tagMenus::match; $$citationMatch ]
Perform Find [ ]
#
#Sort according to current users wishes. By default
#the sort will be by category which is set by editCitation script.
If [ TEMP::sortCopyist = "cat" or TEMP::sortCopyist = "" ]
Sort Records [ Speciﬁed Sort Order: ruleTagMenuGroups::order; based on value list: “order”
ruleTagMenuGroups::name; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Else If [ TEMP::sortCopyist = "abc" ]
Sort Records [ Speciﬁed Sort Order: tagMenus::tag; ascending ]
[ Restore; No dialog ]
End If
#
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
Set Variable [ $$stopLoadTagRecord ]
January 7, 平成26 16:54:34 Imagination Quality Management.fp7 - menuCopyistFind -1-
