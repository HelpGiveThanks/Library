January 21, 2018 11:50:59 Library.fmp12 - testTemplatesSectionButton -1-
tagMenu: testTemplatesSectionButton
#
#
#When user leaves this menu, revert all
#spellings that where changed by dragging
#text into them.
If [ Get (LayoutName) = "setupTestItem" ]
Perform Script [ “CHUNK_checkForDraggedPasteChanges” ]
End If
#
#
#Go to the test Item window from the
#test section window.
Select Window [ Name: "Tag Menus"; Current file ]
If [ $$citationMatch = "testItem" ]
Perform Script [ “menuTestSection” ]
End If
#
#
