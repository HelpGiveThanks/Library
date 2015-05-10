tagMenu: menuFind: menuTestFind #
#Set citationMatch to color menu button with inUse color.
Set Variable [ $$citationMatch; Value:"test" ] #
#Goto correct layout.
If [ Left (Get (LayoutName) ; 1) = "l" ]
Go to Layout [ “learnFindTest” (test) ]
If [ TEMP::InventoryLibaryYN
≠ "" ]
Go to Layout [ “learnFindSTest” (test) ]
End If
Else If [ Left (Get (LayoutName) ; 1) = "r" ]
Go to Layout [ “learnFindTest” (test) ]
End If #
#Find section tags. Section tags are library
#sections and any brainstorm or evidence record
#can be tagged with any section item record SO
#find all library sections current record is
#assigned to.
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ test::ksection; TEMP::ksection ]
Perform Find [ ]
Sort Records [ Specified Sort Order: ruleSection::name; ascending
groupTest::name; ascending
test::testName; ascending ]
[ Restore; No dialog ]
#
// #If no records exist then create one.
// If [ Get (FoundCount)=0 ]
// Perform Script [ “newCitationMenuGroup” ]
// End If #
// #Sort according to current users wishes. By default
// #the sort will be by category which is set by editCitation script.
// If [ TEMP::sortMedium = "cat" ]
// Sort Records [ Specified Sort Order: ruleTagMenuGroups::order; based on value list: “order”
ruleTagMenuGroups::name; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
// Else If [ TEMP::sortMedium = "abc" ]
// Sort Records [ Specified Sort Order: tagMenus::tag; ascending ]
[ Restore; No dialog ]
// End If #
#Go to citation record's current selection or to first record.
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ $$section = test::_Ltest ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
If [ $$section
≠ test::_Ltest ]
Go to Record/Request/Page
[ First ]
Exit Script [ ]
End If
Set Variable [ $$ID; Value:test::_Ltest ] #
#Go to citation record's current selection or to first record.
Go to Record/Request/Page
[ First ]
Loop
Exit Loop If [ $$citationItem = ruleSection::_Lgroup ]
Go to Record/Request/Page
[ Next; Exit after last ]
End Loop
If [ $$citationItem
≠ test::_Ltest ]
Go to Record/Request/Page
[ First ]
Exit Script [ ]
End If #
#Inform user of items use on both screens.
Set Variable [ $$citationItem; Value:test::_Ltest ]
Refresh Window
#Just in case user was in nonTag field on this
#window when user clicked a menu button on
#the other window, exit all fields.
Select Window [ Name: "References"; Current file ]
If [ Get (LastError) = 112 ]
Select Window [ Name: "Learn"; Current file ]
End If
Go to Field [ ]
Refresh Window
Select Window [ Name: "Tag Menus"; Current file ] #
#Set citationMatch to color menu button with inUse color.
Set Variable [ $$citationMatch; Value:"test" ] #
#Goto correct layout.
If [ Left (Get (LayoutName) ; 1) = "l" ]
Go to Layout [ “learnFindTest” (test) ]
Else If [ Left (Get (LayoutName) ; 1) = "r" ]
Go to Layout [ “learnFindTest” (test) ]
End If #
#Find section tags. Test tags are section
#items. Any brainstorm or evidence record
#can be tagged with any section item record SO
#find all library sections current record is
#assigned to.
Set Error Capture [ On ]
Allow User Abort [ Off ]
Enter Find Mode [ ]
Set Field [ ruleSection::match; "section" ]
Perform Find [ ]
Sort Records [ Specified Sort Order: ruleSection::name; ascending
groupTest::name; ascending
test::testName; ascending ]
[ Restore; No dialog ]
#
Go to Record/Request/Page
[ First ]
Scroll Window
[ Home ]
Set Variable [ $$stopLoadTagRecord ]
May 10, 平成27 10:53:28 Library.fp7 - menuTestFind -1-
