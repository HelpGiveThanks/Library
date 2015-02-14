tagMenu: menuTestItem
#
If [ TEMP::ktest = "" ]
Exit Script [ ]
Show Custom Dialog [ Message: "There are no tests."; Buttons: “OK” ]
End If
#
#Goto correct layout.
#If in add mode ...
If [ $$add = 1 ]
Go to Layout [ “addMenuTestItem” (tagMenus) ]
#
#If user has elected to show only the tag ...
Else If [ TEMP::DetailmoreORLessLayout = "" and Left ( Get ( LayoutName ) ; 5 ) = "setup" ]
Go to Layout [ “setupTestItem” (tagMenus) ]
Else If [ TEMP::DetailmoreORLessLayout ≠ "" and Left ( Get ( LayoutName ) ; 5 ) = "setup" ]
Go to Layout [ “setupTestItem” (tagMenus) ]
#
#If user has elected to show some pictures ...
Else If [ TEMP::DetailmoreORLessLayout = "" and Left ( Get ( LayoutName ) ; 4 ) = "test" ]
Go to Layout [ “testMenuTestItem” (tagMenus) ]
Else If [ TEMP::DetailmoreORLessLayout ≠ "" and Left ( Get ( LayoutName ) ; 4 ) = "test" ]
Go to Layout [ “testMenuTestItem” (tagMenus) ]
#
Else If [ Left ( Get (LayoutName) ; 6 ) = "report" ]
#
#Find test list key as it may be different from test key.
Set Variable [ $$stopLoadTagRecord; Value:1 ]
Set Variable [ $$stopTest; Value:1 ]
Set Variable [ $$ID; Value:"ignore" ]
Go to Layout [ “testSetup” (test) ]
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ test::_Ltest; TEMP::ktest ]
Perform Find [ ]
Set Field [ TEMP::ktestItemList; test::ktestItemList ]
Go to Layout [ “reportTagItem” (tagMenus) ]
Set Variable [ $$stopLoadTagRecord ]
Set Variable [ $$stopTest ]
Set Variable [ $$ID ]
#
End If
Set Variable [ $$citationMatch; Value:"testItem" ]
Set Field [ TEMP::mTag; TEMP::ktest ]
#
#Find test items for section.
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ ruleTagMenuTestGroups::match; TEMP::ktestItemList & ¶ ]
Perform Find [ ]
#
Sort Records [ Specified Sort Order: ruleTagMenuTestGroups::order; based on value list: “order”
ruleTagMenuTestGroups::name; ascending
ruleTagMenuTestGroups::_Lgroup; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
#
Go to Record/Request/Page
[ First ]
#
#Just in case user was in nonTag field on this
#window when user clicked a menu button on
#the other window, exit all fields.
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
Go to Field [ ]
Else If [ Get (LastError) ≠ 112 ]
#
#If in add mode, find only records tagged with
#current $$citationmatch.
If [ $$add = 1 ]
#
#But, give user option to keep the records currently
#showing in the main window.
Show Custom Dialog [ Message: "In the main window, show only records with pictures and links added to test item tags, or keep the current records shown?"; Buttons: “keep”, “show” ]
If [ Get ( LastMessageChoice ) = 1 ]
Refresh Window
Select Window [ Name: "Tag Menus"; Current file ]
Exit Script [ ]
End If
#
#find on learn layout ...
If [ Left (Get (LayoutName) ; 1) = "l" ]
Enter Find Mode [ ]
Set Field [ testlearn::kcsection; TEMP::ksection ]
Set Field [ testlearn::filterFind; "testItem" ]
Perform Find [ ]
#
#find on reference layout ...
Else If [ Left (Get (LayoutName) ; 1) = "r" ]
Enter Find Mode [ ]
Set Field [ reference::kcsection; TEMP::ksection ]
Set Field [ reference::filterFind; "testItem" ]
Perform Find [ ]
End If
End If
#
End If
Refresh Window
Select Window [ Name: "Tag Menus"; Current file ]
January 7, 平成26 15:59:32 Imagination Quality Management.fp7 - menuTestItem -1-
