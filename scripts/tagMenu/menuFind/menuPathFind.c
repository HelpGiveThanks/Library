January 21, 2018 12:01:07 Library.fmp12 - menuPathFind -1-
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
#Sort according to current users wishes.
If [ TEMP::sortPath = "cat" or TEMP::sortPath = "" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenuGroup::orderOrLibraryType; based on value list:
“order Pulldown List”
tagMenuGroup::name; ascending
tagMenus::orderOrLock; based on value list: “order Pulldown List”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Else If [ TEMP::sortPath = "abc" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenus::tag; ascending ]
[ Restore; No dialog ]
End If
#
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
Set Variable [ $$stopLoadTagRecord ]
