January 15, 2018 16:16:17 Library.fmp12 - returnToSetup -1-
tagMenu: returnToSetup
#
#
#Return to last library module.
If [ $$module = "testmenudetail" ]
#
#Go to testlearn layout and loop back to record.
Set Window Title [ Current Window; New Title: "Test" ]
Go to Layout [ Middle ( TEMP::layoutTmain ; 5 ; 99 ) ]
#
#Go to Learn tag menu layout and loop back to record.
Select Window [ Name: "Tag Menus"; Current file ]
Go to Layout [ “testMenuTestItem” (tagMenus) ]
#
#Reset temp item ID and clear variable holding
#ID while editing item information.
Set Field [ TEMP::ktestSubsection; $$itemID ]
Set Field [ TEMP::ktestItemSubsection; $$detailID ]
Set Variable [ $$itemID ]
#
#Load up all test items for this subsection.
Perform Script [ “menuTestItem (update)” ]
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
Set Field [ TEMP::ktestSubsection; $$itemID ]
Set Field [ TEMP::ktestItemSubsection; $$detailID ]
Set Variable [ $$itemID ]
#
Perform Script [ “menuTestItem (update)” ]
#
Exit Script [ ]
Else If [ $$module = "defaultSections" ]
Go to Layout [ “defaultSetup” (librarySetupReferenceMain) ]
Select Window [ Name: "Tag Menus"; Current file ]
Go to Layout [ $$module ]
If [ $$module = "defaultSections" ]
Perform Script [ “defaultLibraryButton (update name change defaultSectionMenu)” ]
End If
Go to Record/Request/Page [ $$recordNumber ]
[ No dialog ]
Set Variable [ $$recordNumber ]
#
Set Field [ TEMP::ktestSubsection; "" ]
#
#
Exit Script [ ]
End If
#
#Go to testlearn layout and loop back to record.
Set Window Title [ Current Window; New Title: "Test" ]
#
#Stop load tag script until the end.
Set Variable [ $$returnToSetup; Value:1 ]
#
#Go to unlocked or locked layout depending
#lock status of the test subject.
If [ testSubsectionTestSubjectLock::orderOrLock = "0" ]
Go to Layout [ "testResultLOCKED" & Right ( TEMP::layoutTmain ; 1) ]
Else
Go to Layout [ "testResult" & Right ( TEMP::layoutTmain ; 1) ]
End If
#
#Go to test item tag menu layout and go to
#record user was on before editing test items.
Select Window [ Name: "Tag Menus"; Current file ]
Go to Layout [ “testMenuTestItem” (tagMenus) ]
#
#Load up all test items for this subsection.
Perform Script [ “menuTestItem (update)” ]
#
#Turn back on load tag script and go
#to selected tag.
Set Variable [ $$returnToSetup ]
Go to Record/Request/Page [ $$recordNumber ]
[ No dialog ]
Set Variable [ $$recordNumber ]
#
Exit Script [ ]
