January 20, 2018 19:11:22 Library.fmp12 - menuCopyrightFind -1-
tagMenu: menuFind: menuCopyrightFind
#
#Set citationMatch to color menu button with inUse color.
Set Variable [ $$citationMatch; Value:"copyright" ]
#
#Goto correct layout.
If [ Left (Get (LayoutName) ; 1) = "l" ]
Go to Layout [ “learnFind” (tagMenus) ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “learnSFind” (tagMenus) ]
End If
Else If [ Left (Get (LayoutName) ; 1) = "r" ]
Go to Layout [ “ReferenceMenuFind” (tagMenus) ]
End If
#
#Find Permission tags. Permission tags are available to all library sections.
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ tagMenus::match; $$citationMatch ]
Perform Find [ ]
#
#Sort according to current users wishes.
If [ TEMP::sortCopyright = "cat" or TEMP::sortCopyright = "" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenuGroup::orderOrLibraryType; based on value list:
“order Pulldown List”
tagMenuGroup::name; ascending
tagMenus::orderOrLock; based on value list: “order Pulldown List”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Else If [ TEMP::sortCopyright = "abc" ]
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenus::tag; ascending ]
[ Restore; No dialog ]
End If
#
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
Set Variable [ $$stopLoadTagRecord ]
#
