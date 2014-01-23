testScreens: testReport: openDetailWindow !!! FINISH LATER !!!
Go to Field [ ]
Set Variable [ $$ID; Value:test::_Ltest ]
Set Variable [ $workwindow; Value:Get (WindowName) ]
Set Variable [ $left; Value:Get ( WindowLeft ) ]
Set Variable [ $width; Value:Get ( WindowWidth) ]
Select Window [ Name: $workwindow; Current ﬁle ]
Set Field [ TEMP::ktestItemList; test::ktestItemList ]
Set Field [ TEMP::ktestItemListOLD; test::ktestItemList ]
Set Field [ TEMP::ktest; test::_Ltest ]
Set Field [ TEMP::testName; test::testName ]
Set Field [ TEMP::ksection; test::ksection ]
Set Field [ TEMP::sectionName; ruleSection::name ]
Select Window [ Name: "Details"; Current ﬁle ]
If [ Get (LastError) = 112 ]
If [ Get (WindowZoomLevel) = 100 ]
New Window [ Name: "Details"; Height: Get (ScreenHeight); Width: 333; Left: If ( $left + $width + 333 > Get ( ScreenWidth ) ; Get ( ScreenWidth ) - 333 ; $left + $width ) ]
Else If [ Get (WindowZoomLevel) = 150 ]
New Window [ Name: "Details"; Height: Get (ScreenHeight); Width: 490; Left: If ( $left + $width > Get ( ScreenWidth ) - 490; Get ( ScreenWidth ) - 490 ; $left + $width ) ]
End If
Go to Layout [ “setupTestItem” (tagMenus) ]
End If
#
Set Variable [ $layout; Value:Get (LayoutName) ]
Set Variable [ $$attributeReturnLayout; Value:Get (LayoutName) ]
#Find all details for this item.
Go to Layout [ “testMenuTestItemMORE” (tagMenus) ]
// Set Variable [ $$citationMatch; Value:test::_Ltest ]
#
#Find detail tags for library section.
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ tagMenus::kGroupOrTest; TEMP::ktestItemList ]
Perform Find [ ]
#
#If no records exist then create one.
If [ Get (FoundCount)=0 ]
Perform Script [ “newCitationMenuGroup” ]
End If
#
Sort Records [ Speciﬁed Sort Order: ruleTagMenuTestGroups::order; based on value list: “order”
ruleTagMenuTestGroups::name; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
#
Go to Record/Request/Page
[ First ]
#
#Find all locations for this item.
#New items will not have any locations assigned so
#error caputer needs to be turned on.
Set Error Capture [ On ]
Allow User Abort [ Off ]
Go to Layout [ “setupTestFocus” (tagLocation) ]
View As
[ View as Form ]
Enter Find Mode [ ]
Set Field [ test::_Ltest; $$ID ]
Perform Find [ ]
#
Go to Layout [ $layout ]
Refresh Window
January 7, 平成26 14:45:18 Imagination Quality Management.fp7 - openDetailWindow !!! FINISH LATER !!! -1-
