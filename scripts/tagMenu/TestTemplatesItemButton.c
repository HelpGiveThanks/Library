January 15, 2018 16:56:11 Library.fmp12 - testTemplatesItemButton -1-
tagMenu: testTemplatesItemButton
#
#
#If the user clicked the show tagged
#subsections button, turn off this conditional
#formatting variable and reset the conditional
#formatting in the Test Templates window.
If [ $$setupTestSection ≠ "" ]
Set Variable [ $$setupTestSection ]
Select Window [ Name: "Test Templates"; Current file ]
Refresh Window
End If
#
#
#When user leaves this menu, revert all
#spellings that where changed by dragging
#text into them.
If [ Get (LayoutName) = "setupTestSection" ]
Perform Script [ “checkTestSectionSubsectionAndItemRecordSpellings (update)” ]
End If
#
#
#Go to the test section window from
#the test item window.
Select Window [ Name: "Tag Menus"; Current file ]
If [ $$citationMatch ≠ "testItem" ]
Perform Script [ “menuTestItem (update)” ]
End If
#
#
