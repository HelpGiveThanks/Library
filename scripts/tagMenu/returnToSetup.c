tagMenu: returnToSetup
// If [ $$learnEdit ≠ "" and $$defaultMode ≠ 1 ]
// #Go to testlearn layout and loop back to record.
// Set Window Title [ Current Window; New Title: "Learn" ]
// Go to Layout [ “learn1” (testlearn) ]
// #
// #Go to Learn tag menu layout and loop back to record.
// Select Window [ Name: "Tag Menus"; Current file ]
// Go to Layout [ “defaultSections” (ruleSection) ]
// Perform Script [ “defaultSectionMenu” ]
// Select Window [ Name: "Learn"; Current file ]
// Go to Field [ ]
// Refresh Window
// #
// Set Field [ TEMP::ktest; "" ]
// #
// Exit Script [ ]
If [ $$module = "testmenudetail" ]
#
#Go to testlearn layout and loop back to record.
Set Window Title [ Current Window; New Title: "Test" ]
Go to Layout [ “step4_InspectionFinding” (testlearn) ]
#
#Go to Learn tag menu layout and loop back to record.
Select Window [ Name: "Tag Menus"; Current file ]
Go to Layout [ “testMenuTestItem” (tagMenus) ]
#
#Reset temp item ID and clear variable holding
#ID while editing item information.
Set Field [ TEMP::ktest; $$itemID ]
Set Field [ TEMP::ktestItemList; $$detailID ]
Set Variable [ $$itemID ]
#
Perform Script [ “menuTestItem” ]
#
Exit Script [ ]
Else If [ $$module = "reportTagItem" ]
#
#Go to testlearn layout and loop back to record.
Set Window Title [ Current Window; New Title: "Report" ]
Go to Layout [ “PrintReportEdit” (report) ]
#
#Go to Learn tag menu layout and loop back to record.
Select Window [ Name: "Tag Menus"; Current file ]
Go to Layout [ “reportTagItem” (tagMenus) ]
#
#Reset temp item ID and clear variable holding
#ID while editing item information.
Set Field [ TEMP::ktest; $$itemID ]
Set Field [ TEMP::ktestItemList; $$detailID ]
Set Variable [ $$itemID ]
#
Perform Script [ “menuTestItem” ]
#
Exit Script [ ]
Else If [ $$module = "defaultSections" ]
Go to Layout [ “defaultSetup” (tempSetup) ]
Select Window [ Name: "Tag Menus"; Current file ]
Go to Layout [ $$module ]
If [ $$module = "defaultSections" ]
Perform Script [ “defaultSectionMenu” ]
End If
Go to Record/Request/Page [ $$recordNumber ]
[ No dialog ]
Set Variable [ $$recordNumber ]
#
Set Field [ TEMP::ktest; "" ]
#
#
Exit Script [ ]
End If
#
#Go to testlearn layout and loop back to record.
Set Window Title [ Current Window; New Title: "Test" ]
Go to Layout [ “step4_InspectionFinding” (testlearn) ]
#
#Go to Learn tag menu layout and loop back to record.
Select Window [ Name: "Tag Menus"; Current file ]
Go to Layout [ “testMenuTestItem” (tagMenus) ]
Sort Records [ Specified Sort Order: ruleTagMenuTestGroups::order; based on value list: “order”
ruleTagMenuTestGroups::name; ascending
tagMenus::orderOrLock; based on value list: “order”
tagMenus::tag; ascending ]
[ Restore; No dialog ]
Go to Record/Request/Page [ $$recordNumber ]
[ No dialog ]
Set Variable [ $$recordNumber ]
#
Exit Script [ ]
January 7, 平成26 15:56:26 Imagination Quality Management.fp7 - returnToSetup -1-
