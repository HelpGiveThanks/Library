testScreens: testReport: probablyNotInUse: evidenceDetailSpacetimeDELETE?????
Set Variable [ $$openedFrom; Value:Get (LayoutName) ]
Set Variable [ $left; Value:Get ( WindowLeft ) ]
Set Variable [ $width; Value:Get ( WindowWidth) ]
Set Field [ TEMP::ktestItemList; InspectItems::ktestItemList ]
Set Field [ TEMP::ktestItemListOLD; InspectItems::ktestItemList ]
Set Field [ TEMP::ktest; InspectItems::_Ltest ]
Set Field [ TEMP::ksection; InspectItems::ksection ]
Select Window [ Name: "Tag Menus"; Current file ]
If [ Get (LastError) = 112 ]
If [ Get (WindowZoomLevel) = 100 ]
New Window [ Name: "Tag Menus"; Height: Get (ScreenHeight); Width: $width; Left: //If ( $left + $width + 333 > Get ( ScreenWidth ) ; Get ( ScreenWidth ) - 333 ; $left + $width )
$width ]
Else If [ Get (WindowZoomLevel) = 150 ]
New Window [ Name: "Tag Menus"; Height: Get (ScreenHeight); Width: $width; Left: //If ( $left + $width + 333 > Get ( ScreenWidth ) ; Get ( ScreenWidth ) - 333 ; $left + $width )
$width ]
// New Window [ Name: "Tag Menus"; Height: Get (ScreenHeight); Width: 490; Left: If ( $left + $width > Get ( ScreenWidth ) - 490; Get ( ScreenWidth ) - 490 ; $left + $width ) ]
End If
Go to Layout [ “setupTestItem” (tagMenus) ]
End If
Go to Layout [ $$listlayout ]
#
#Find all details for this item.
Perform Script [ “menuTestItem” ]
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
Set Field [ test::_Ltest; $$item ]
Perform Find [ ]
Go to Layout [ $$listlayout ]
Select Window [ Name: "Test"; Current file ]
Select Window [ Name: "Setup"; Current file ]
January 7, 平成26 14:20:03 Imagination Quality Management.fp7 - evidenceDetailSpacetimeDELETE????? -1-
