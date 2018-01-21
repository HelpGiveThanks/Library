January 20, 2018 19:12:45 Library.fmp12 - menuTestFind -1-
tagMenu: menuFind: menuTestFind
#
#Set citationMatch to color menu button with inUse color.
Set Variable [ $$citationMatch; Value:"test" ]
#
#Goto correct layout.
If [ Left (Get (LayoutName) ; 1) = "l" ]
Go to Layout [ “learnFindTest” (testSubsectionTemplate) ]
If [ TEMP::InventoryLibraryYN ≠ "" ]
Go to Layout [ “learnFindSTest” (testSubsectionTemplate) ]
End If
Else If [ Left (Get (LayoutName) ; 1) = "r" ]
Go to Layout [ “learnFindTest” (testSubsectionTemplate) ]
End If
#
#Find test subsection tags.
Show All Records
#
#Sort into groups.
Sort Records [ Keep records in sorted order; Specified Sort Order: testSubsectionGroup::orderOrLibraryType; based on value list:
“order Pulldown List”
testSubsectionGroup::name; ascending
tagMenus::orderOrLock; based on value list: “order Pulldown List”
testSubsectionTemplate::order; ascending
testSubsectionTemplate::name; ascending ]
[ Restore; No dialog ]
#
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
Set Variable [ $$stopLoadTagRecord ]
