January 20, 2018 19:07:54 Library.fmp12 - menuBrainstormFind -1-
tagMenu: menuFind: menuBrainstormFind
#
#Set citationMatch to color menu button with inUse color.
Set Variable [ $$citationMatch; Value:"brainstorm" ]
#
#Goto correct layout.
If [ Left (Get (LayoutName) ; 1) = "l" ]
Go to Layout [ “learnFindBrainstorm” (tagMenus) ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “learnFindStuffBrainstorm” (tagMenus) ]
End If
Else If [ Left (Get (LayoutName) ; 1) = "r" ]
Go to Layout [ “learnFindBrainstorm” (tagMenus) ]
End If
#
#Find brainstorm tags.
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ tagMenus::match; $$citationMatch ]
Perform Find [ ]
#
#Sort into groups.
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenuGroup::orderOrLibraryType; based on value list: “order
Pulldown List”
tagMenuGroup::name; ascending
tagMenus::tag; ascending ]
[ Restore; No dialog ]
#
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
Set Variable [ $$stopLoadTagRecord ]
