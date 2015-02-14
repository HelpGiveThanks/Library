tagMenu: menuFind: menuPathFind
#
#Set citationMatch to color menu button with inUse color.
Set Variable [ $$citationMatch; Value:"path" ]
#
#Goto correct layout.
If [ Left (Get (LayoutName) ; 1) = "l" ]
Go to Layout [ “learnFind” (tagMenus) ]
Else If [ Left (Get (LayoutName) ; 1) = "r" ]
Go to Layout [ “ReferenceMenuFind” (tagMenus) ]
End If
#
#Find Path tags. Path tags are available to all library sections.
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ tagMenus::match; "Path" ]
Perform Find [ ]
#
#Sort according to current users wishes. By default
#the sort will be by category which is set by editCitation script.
If [ TEMP::sortPath = "cat" or TEMP::sortPath = "" ]
Sort Records [ Specified Sort Order: ruleTagMenuGroups::order; based on value list: “order”
ruleTagMenuGroups::name; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Else If [ TEMP::sortPath = "abc" ]
Sort Records [ Specified Sort Order: tagMenus::tag; ascending ]
[ Restore; No dialog ]
End If
#
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
Set Variable [ $$stopLoadTagRecord ]
January 7, 平成26 16:55:02 Imagination Quality Management.fp7 - menuPathFind -1-
