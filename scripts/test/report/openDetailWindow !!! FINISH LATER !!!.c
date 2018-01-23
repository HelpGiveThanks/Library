January 15, 2018 15:58:28 Library.fmp12 - openDetailWindow !!! FINISH LATER !!! -1-
test: report: openDetailWindow !!! FINISH LATER !!!
Go to Field [ ]
Set Variable [ $$ID; Value:testSubsectionTemplate::_LtestSubsection ]
Set Variable [ $workwindow; Value:Get (WindowName) ]
Set Variable [ $left; Value:Get ( WindowLeft ) ]
Set Variable [ $width; Value:Get ( WindowWidth) ]
Select Window [ Name: $workwindow; Current file ]
Set Field [ TEMP::ktestItemSubsection; testSubsectionTemplate::ktestItemGroup ]
Set Field [ TEMP::ktestItemSubsectionOLD; testSubsectionTemplate::ktestItemGroup ]
Set Field [ TEMP::ktestSubsection; testSubsectionTemplate::_LtestSubsection ]
Set Field [ TEMP::testSubsectionName; testSubsectionTemplate::name ]
Set Field [ TEMP::userLibraryName; testSubsectionLibraryName::name ]
Select Window [ Name: "Details"; Current file ]
If [ Get (LastError) = 112 ]
If [ Get (WindowZoomLevel) = 100 ]
New Window [ Name: "Details"; Height: Get (ScreenHeight); Width: 333; Left: If ( $left + $width + 333 > Get ( ScreenWidth ) ;
Get ( ScreenWidth ) - 333 ; $left + $width ); Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom
Control Area: “Yes”; Resize: “Yes” ]
Else If [ Get (WindowZoomLevel) = 150 ]
New Window [ Name: "Details"; Height: Get (ScreenHeight); Width: 490; Left: If ( $left + $width > Get ( ScreenWidth ) - 490;
Get ( ScreenWidth ) - 490 ; $left + $width ); Style: Document; Close: “Yes”; Minimize: “Yes”; Maximize: “Yes”; Zoom
Control Area: “Yes”; Resize: “Yes” ]
End If
Go to Layout [ “setupTestItem” (tagMenus) ]
End If
#
Set Variable [ $layout; Value:Get (LayoutName) ]
Set Variable [ $$attributeReturnLayout; Value:Get (LayoutName) ]
#Find all details for this item.
Go to Layout [ “testMenuTestItemMORE” (tagMenus) ]
// Set Variable [ $$citationMatch; Value:testSubsectionTemplate::_LtestSubsection ]
#
#Find detail tags for library section.
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ tagMenus::kGroupOrTest; TEMP::ktestItemSubsection ]
Perform Find [ ]
#
#If no records exist then create one.
If [ Get (FoundCount)=0 ]
Perform Script [ “newTagMenuTagGroup” ]
End If
#
Sort Records [ Keep records in sorted order; Specified Sort Order: tagMenuTestItemGroup::orderOrLibraryType; based on value list:
“order Pulldown List”
tagMenuTestItemGroup::name; ascending
tagMenus::orderOrLock; based on value list: “order Pulldown List”
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
Go to Layout [ “setupTestSection” (testSection) ]
View As
[ View as Form ]
Enter Find Mode [ ]
Set Field [ testSubsectionTemplate::_LtestSubsection; $$ID ]
Perform Find [ ]
#
Go to Layout [ $layout ]
Refresh Window
